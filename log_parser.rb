#!/usr/bin/env ruby

class Image
   
   attr_accessor :name, :path, :base, :size, :oep
   
   def initialize(path, base, size, oep)
      @path, @base, @size, @ope = path, size, base, oep
      @name = File.basename(@path)
   end

   def add_method(method)
      @methods ||= {}
      @methods[method.name] = method
   end
end

class Method
   
   attr_accessor :name, :address, :count, :calls

   def initialize( name, address )
      @name, @address = name, address
      @call_count = 0
      @calls = []
   end

   def called( call )
      @call_count += 1
      @calls<< call
   end

end

class Thread

   attr_reader :methods, :id
   
   def initialize( id )
      @id = id
      @methods = {}
   end

   def called(call)
      @methods[call.name] ||= []
      @methods[call.name]<< call
   end

end

def MethodCall
   
   attr_accessor :name, :arguments, :thread, :ret

   def initialize( name, arguments, thread)
      @name, @arguments, @thread = name, arguments, thread
      @ret = nil
   end

   def returned( values)
      @ret = values
   end
end

class Parser
   
   DELIM = '|'

   def initialize( source) 
      @src = source
      @threads = {}
      @images = {}
      @methods = {}
      @calls = {}
      @last_call = {}
   end

   def onImage( data )
      parts = data.split(DELIM)
      path = parts[1]
      base = parts[2].split('@')[1]
      size = parts[3].split('@')[1]
      oep = parts[4].split('@')[1]

      img = Image.new(path, base, size, oep)
      @images[img.name] = img
   end
   
   def onThread( data )
      thr, fn_name, event, params = data.split(DELIM)
      th_id = thr.split('=')[1].to_i(16)
      
      @threads[th_id] = Thread.new(th_id)

      case event
      
      when 'CALL'
         @last_call[th_id] = MethodCall.new(fn_name, __params_hash(params), @threads[th_id])

      when 'RETN'
         if @last_call[th_id].ret != nil
            puts "[!] Unexpected #{data}" 
         else
            @last_call[th_id].returned( __params_hash(params) )
            @threads[th_id].called( @last_call )
         end
      end
   end

   def __params_hash( params )
      params = [params] if params.is_a?(String)
      return nil if not params.is_a?(Array)

      args = {}
      params.each do |param| 
         name,value = params.split('=')
         args[name] = value
      end

      return args
   end

   def onSymbol( data )
      img, fn_name, addr = data.split(DELIM)

      method = Method.new(fn_name,addr.split('@')[1])
      (@images.has_key(img))?@images[img].add_method(method): puts "[!] Missing Image #{img} with Method #{fn_name}"
      @methods[method.name] = method
   end

   def parse
      
   end
end
