#!/usr/bin/env ruby
require 'config'

class AppImage
  
  attr_accessor :name, :path, :base, :size, :oep
  
  def initialize(path, base, size, oep)
    @path, @base, @size, @oep = path, base, size, oep
    
    @name = @path[@path.rindex('\\')+1..-1].upcase
  end

  def add_method(method)
    @methods ||= {}
    @methods[method.name] = method
  end

  def to_stdout
    str = "Image: #{@name} [Base Address: #{@base}, MappeSize: #{@size}, Entry Point: #{@oep}]\n"
    str += "\tPath: #{@path}\n"
    if @methods
      str += "\tMethods: \n"
      @methods.each_pair { |name,method| str += "\t\t#{method.address} => #{name} \n"}
    end
    str += "\n"
  end
  
  def to_xml( less = [] )
    str = "<image name=\"#{@name}\">\n"
    str += "<path>#{@path}</path>\n"
    str += "<base>#{@base}</base>\n"
    str += "<mapped-size>#{@size}</mapped-size>\n"
    str += "<entry-point>#{@oep}</entry-point>\n"
  
    if @methods
      str += "<methods>"
      @methods.each_pair { |name,method| str += "<method address=\"#{method.address}\">#{name}</method>\n"}
      str += "</methods>"
    end

    str += "</image>"
  end
end

class AppMethod
  attr_accessor :name, :address, :count, :calls
  def initialize( name, address )
    @name, @address = name, address
    @count = 0
    @calls = []
  end

  def called( call )
    @count += 1
    @calls<< call
  end

  def to_stdout
    str = "#{@name} #{@count}\n"
    str += "\t Calls: \n"
    @calls.each { |call| str += call.to_stdout}
    str += "\n"
  end
  
  def to_xml( less = [] )
    "<method call-count=\"#{@count}\">#{@name}</method>"
  end
end

class AppThread
  
  attr_reader :calls, :id
  
  def initialize( id )
    @id = id
    @calls = []
  end

  def called( call )
    @calls << call
  end

  def to_stdout
    str = "Thread: 0x#{@id.to_s(16)}\n"
    str += "\tCalled:\n"
    @calls.each { |call| str += call.to_stdout}
    str += "\n"
  end

  def to_xml( less = [] )
    xml = "<thread id=\"#{@id.to_s(16)}\" calls=\"#{@calls.size}\">"
    @calls.each_index { |i| xml += @calls[i].to_xml}
    xml += "</thread>"
  end
end

class AppCall
  
  attr_accessor :name, :arguments, :thread, :ret

  def initialize( name, arguments, thread)
    @name, @arguments, @thread = name, arguments, thread
    @ret = nil
  end

  def returned( values)
    @ret = values
  end

  def to_stdout
    str = "#{@name}\n"
    str += "\tThread: 0x#{@thread.id.to_s(16)}\n"
    
    if @arguments && @arguments.size > 0
      str += "\tInput Parameters: #{@arguments.to_s}\n"
    end
    
    if @ret && @ret.size>0
      str += "\t Returned: #{@ret.to_s}\n"
    end

    str += "\n"
  end

  def to_xml( less = [] )
    str = "<call thread=\"#{@thread.id.to_s(16)}\">"
    str += "<name>#{@name}</name>"

    if @arguments && @arguments.size > 0
      str += "<call-params>"
      @arguments.each_pair {|name, value| str += "<param name=\"#{name}\" value=\"#{value}\"/>"}
      str += "</call-params>"
    else
      str += "<call-params/>"
    end

    if @ret && @ret.size > 0
      str += "<return-params>"
      @ret.each_pair {|name,value| str += "<param name=\"#{name}\" value=\"#{value}\"/>"}
      str += "</return-params>"
    else
      str += "<return-params/>"
    end

    str += "</call>"
  end
end

class Parser
  DELIM = '|'
  def initialize( source)
    @src = source
    @threads = {}
    @images = {}
    @methods = {}
    @calls = []
    @last_call = {}
  end

  def on_image( data )
    parts = data.split(DELIM)
    path = parts[1]
    base = parts[2].split('@')[1]
    size = parts[3].split('@')[1]
    oep = parts[4].split('@')[1]

    img = AppImage.new(path, base, size, oep)
    @images[img.name] = img
  end

  def on_thread( data )
    thr, fn_name, event, *params = data.split(DELIM)
    th_id = thr.split('=')[1].to_i(16)

    @threads[th_id] ||= AppThread.new(th_id)

    case event

    when 'CALL'
      call = AppCall.new(fn_name, __params_hash(params), @threads[th_id])
      @last_call[th_id] = call
      @calls<< call
      @methods[call.name].called( call ) if @methods[call.name]
    when 'RETN'
      if @last_call[th_id].ret != nil
        puts "[!] Unexpected #{data}"
      else
        @last_call[th_id].returned( __params_hash(params) )
        @threads[th_id].called( @last_call[th_id] )
      end
    end
  end

  def __params_hash( params )
    params = [params] if params.is_a?(String)
    return nil if not params.is_a?(Array)
    args = {}
    params.each do |param|
      next unless param.include?('=')
      name,value = param.split('=')
      args[name] = value
    end

    return args
  end

  def on_symbol( data )
    cmd, img, fn_name, addr = data.split(DELIM)
    method = AppMethod.new(fn_name,addr.split('@')[1])

    if @images.key?(img)
      @images[img].add_method(method)
    else
      puts "[!] Missing Image #{img} with Method #{fn_name}"
    end

    @methods[method.name] = method
  end

  def parse
    File.open(@src,"r") do |file|
      while line = file.gets
        next if line.strip.size == 0 or line.start_with?( "[*]Done" )
        if line.match(/^Image*/)
          on_image( line.strip )
        elsif line.match(/^Thread*/)
          on_thread( line.strip )
        elsif line.match(/^SYMBOL*/)
          on_symbol( line.strip )
        end
      end
    end

    return self
  end

  def to_stdout
    puts "[*] #{@images.size} Loaded Images...\n"
    @images.each_value {|img| puts img.to_stdout}
    puts "[*] Threads #{@threads.size}"
    @threads.each_value {|th| puts th.to_stdout}
    puts "[*] Methods #{@methods.size}"
    @methods.each_value { |method| puts method.to_stdout}
  end

  def xmlize ( io )

    io.write( "<puncture>" )
    
    io.write( "<images count=\"#{@images.size}\">" )
    @images.each_value {|image| io.write( image.to_xml )}
    io.write( "</images>" )

    io.write( "<methods count=\"#{@methods.size}\">" )
    @methods.each_value { |method| io.write( method.to_xml )}
    io.write( "</methods>" )

    io.write( "<calls count=\"#{@calls.size}\">")
    @calls.each { |call| io.write( call.to_xml )}
    io.write( "</calls>" )

    io.write( "<threads count=\"#{@threads.size}\">" )
    @threads.each_value {|thrd| io.write( thrd.to_xml )}
    io.write( "</threads>" )

    io.write( "</puncture>" )
    io.flush
  end
end

if $0 == __FILE__
  parser = Parser.new($config['LOG_FILE']).parse
  #parser.to_stdout
  File.open("puncture.xml","w") { |file| 
    file.write("<?xml version=\"1.0\" ?>\n")
    parser.xmlize( file )
  }
  
  puts "[*] Done."
end
