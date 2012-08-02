#!/usr/bin/env ruby

DEBUG = 1

class AppImage
  attr_accessor :name, :path, :base, :size, :oep
  def initialize(path, base, size, oep)
    @path, @base, @size, @oep = path, size, base, oep
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
end

class AppThread
  attr_reader :methods, :id
  
  def initialize( id )
    @id = id
    @methods = {}
  end

  def called(call)
    @methods[call.name] ||= []
    @methods[call.name]<< call
  end

  def to_stdout
    str = "Thread: 0x#{@id.to_s(16)}\n"
    str += "\tCalled:\n"
    @methods.each_key { |name| str += "\t #{name}\n"}
    str += "\n"
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

  def onImage( data )
    parts = data.split(DELIM)
    path = parts[1]
    base = parts[2].split('@')[1]
    size = parts[3].split('@')[1]
    oep = parts[4].split('@')[1]

    img = AppImage.new(path, base, size, oep)
 #   puts "[?] added image #{img.name}"
    @images[img.name] = img
  end

  def onThread( data )
    thr, fn_name, event, *params = data.split(DELIM)
    th_id = thr.split('=')[1].to_i(16)

    @threads[th_id] = AppThread.new(th_id)

    case event

    when 'CALL'
      @last_call[th_id] = AppCall.new(fn_name, __params_hash(params), @threads[th_id])
      @calls<< @last_call[th_id]
      @methods[@last_call[th_id].name].called( @last_call[th_id] ) if @methods[@last_call[th_id].name]
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
    #    puts params.inspect if DEBUG == 1
    args = {}
    params.each do |param|
      next unless param.include?('=')
      name,value = param.split('=')
      args[name] = value
    end

    return args
  end

  def onSymbol( data )
#    puts data.inspect
    img, fn_name, addr = data.split(DELIM)
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
#        puts line if DEBUG == 1
        if line.match(/^Image*/)
          onImage( line.strip )
        elsif line.match(/^Thread*/)
          onThread( line.strip )
        else
          onSymbol( line.strip ) #unless line.match (  )
        end
      end
    end

    return self
  end

  def result
#    puts "[*] #{@images.size} Loaded Images...\n"
#    @images.each_value {|img| puts img.to_stdout}
    puts "[*] Threads #{@threads.size}"
    @threads.each_value {|th| puts th.to_stdout}
    #puts "[*] Calls #{@calls.size}"
    puts "[*] Methods #{@methods.size}"
    @methods.each_value { |method| puts method.to_stdout}
  end
end

if $0 == __FILE__
  parser = Parser.new("E:\\GitRepos\\Github\\puncture\\LogFile.txt").parse
  parser.result
end