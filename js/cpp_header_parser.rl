=begin
cpp_header_parser.rl
(c) Rolando Abarca, 2011

very simple c++ header parser, used mainly for generating bindings for JavaScriptCore
=end

require 'rubygems'
require 'ruby-debug'

%%{
  # % - fix syntax highlight

	machine cpp_header_parser;
	white = [\t ];
	visibility_token = ('public' | 'private' | 'protected') white* ':';
  c_comment := 
    any* :>> '*/'
    @{ fgoto main; };

  main := |*
    'class'          { parser.found_token(:class, p) };
    'enum'           { parser.found_token(:enum, p) };
    'static'         { parser.found_token(:static, p) };
    visibility_token { parser.found_token(:public, p) };
    '*'              { parser.found_token(:star, p) };
    ':'              { parser.found_token(:colon, p) };
    ','              { parser.found_token(:comma, p) };
    ';'              { parser.found_token(:semicolon, p) };
    '{'              { parser.found_token(:open_bracket, p) };
    '}'              { parser.found_token(:close_bracket, p) };
    '};'             { parser.found_token(:close_class, p) };
    '('              { parser.found_token(:open_parenthesis, p) };
    ')'              { parser.found_token(:close_parenthesis, p) };
    '='              { parser.found_token(:equals, p) };
    '::'             { parser.found_token(:ns_sep, p) };

    # values
    ([0-9]+) > { parser.token_begin(:number, p) } { parser.found_token(:number, p) };
    ([a-zA-Z_] [a-zA-Z0-9_]*) > { parser.token_begin(:id, p) } { parser.found_token(:id, p) };

  	# Comments and whitespace
  	'/*' { fgoto c_comment; };
  	'//' [^\n]* '\n';
  	( any - 33..126 )+;
  *|;

}%%
# % - fix fynxtax highlight

%% write data;
# % fix syntax highlight

class CppEnum
  @@enum_series = 0

  def initialize(parser)
    @parser = parser
    @last_value = 0
    @waiting_for = nil
    @name = nil
    @keys = []
  end

  # the enums should be global, and if they have a name, then a
  # "namespace" is created, e.g.:
  #
  # typedef enum {
  #   ValOne,
  #   ValTwo,
  #   ValThree
  # } someEnum;
  #
  # will be translated to the following in js:
  #
  # someEnum = {};
  # someEnum.ValOne = 0;
  # someEnum.ValTwo = 1;
  # someEnum.ValThree = 2;
  #
  # The above generated using the JavaScriptCore API
  def generate_binding_code
    str = ""
    object = "GLOBAL_OBJECT"
    if @name
      object = "__js__#{@name}"
      str << "static JSObjectRef #{object} = JSObjectMake(GLOBAL_CTX, NULL, NULL);\n";
    end
    str << "void registerEnum#{@enum_id}()\n{\n"
    str << "\tJSStringRef __tmp;\n"
    @keys.each do |key|
      str << "\t__tmp = JSStringCreateWithUTF8CString(\"#{key[:name]}\");\n"
      str << "\tJSObjectSetProperty(GLOBAL_CTX, #{object}, __tmp, JSValueMakeNumber(GLOBAL_CTX, #{key[:value]}), kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete, NULL);\n"
      str << "\tJSStringRelease(__tmp);\n"
    end
    if @name
      str << "\t__tmp = JSStringCreateWithUTF8CString(\"#{@name}\");\n"
      str << "\tJSObjectSetProperty(GLOBAL_CTX, GLOBAL_OBJ, __tmp, #{object}, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete, NULL);\n"
      str << "\tJSStringRelease(__tmp);\n"
    end
    str << "}\n\n"
    str
  end

  def generate_header_code
    "void registerEnum#{@enum_id}();\n"
  end

  def process_token(token, token_type)
    # puts "got token #{token_type}"
    case token_type
    when :id
      if @waiting_for == :id
        @keys << {:name => token, :value => @last_value}
        @last_value += 1
      elsif @waiting_for == :value
        @keys[-1][:value] = token
        @waiting_for = :id
      elsif @waiting_for == :enum_name
        @name = token
        @waiting_for = :semicolon
      else
        raise "parser error (invalid token in enum: #{token_type})"
      end
    when :equals
      @waiting_for = :value
    when :number
      val = token.to_i
      @keys[-1][:value] = val
      @last_value  = val + 1
    when :open_bracket, :comma
      @waiting_for = :id
    when :close_bracket
      @waiting_for = :enum_name
    when :semicolon
      raise "parser error (invalid token in enum)" unless @waiting_for == :semicolon
      @enum_id = @@enum_series
      @@enum_series += 1
      @parser.enum_ended(self)
    else
      raise "parser error (invalid token in enum: #{token_type})"
    end
  end

  def to_s
    {:name => @name, :keys => @keys}.inspect
  end
end

class CppMethod
  NATIVE_TYPES = %w(int long char float bool short)
  NUMBER_TYPES = %w(int long float long\ long unsigned\ int signed\ int short)
  CC_TYPES     = %w(CCPoint CCSize)
  attr_reader :static, :name, :arguments
  attr_accessor :min_arg_count

  def initialize(parser, static = false)
    @parser = parser
    @waiting_for = :return_type
    @static = static
    @name = nil
    @return_type = []
    @arguments = []
    @min_arg_count = 0
    @current_argument = []
  end

  # this generates a static method that returns a JSValueRef
  # encapsulating the original method. The method then needs to be
  # registered for the class
  def generate_binding_code(klass, indent_level = 1, conent_only = false)
    indent = "\t" * indent_level
    str = ""
    str << "JS_STATIC_FUNC_IMP(#{klass.js_name}, js_#{@name})\n{\n" unless conent_only
    # need to cast arguments from JS to native
    if @arguments.size == @min_arg_count
      str << "#{indent}if (argumentCount == #{@arguments.size}) {\n"
    else
      str << "#{indent}if (argumentCount >= #{@min_arg_count}) {\n"
    end
    unless @static || @name == klass.name
      str << "#{indent}\t#{klass.name}* self = (#{klass.name} *)JSObjectGetPrivate(thisObject);\n"
    end

    @arguments.each_with_index do |arg, i|
      optional_arg = false
      if NUMBER_TYPES.include?(arg[:type])
        str << "#{indent}\t#{arg[:type]} arg#{i} = JSValueToNumber(ctx, arguments[#{i}], NULL);\n"
      elsif arg[:type].downcase == "bool"
        str << "#{indent}\tbool arg#{i} = JSValueToBoolean(ctx, arguments[#{i}]);\n"
      elsif arg[:type] == "std::string"
        str << "#{indent}\tJSStringRef __tmp_#{i} = JSValueToStringCopy(ctx, arguments[#{i}], NULL);\n"
        str << "#{indent}\tsize_t len_#{i} = JSStringGetLength(__tmp_#{i})+1;\n"
        str << "#{indent}\tchar *buff_#{i} = (char *)calloc(len_#{i}, 1);\n"
        str << "#{indent}\tJSStringGetUTF8CString(__tmp_#{i}, buff_#{i}, len_#{i});\n"
        str << "#{indent}\tstd::string arg#{i}(buff_#{i});\n"
        str << "#{indent}\tJSStringRelease(__tmp_#{i});\n"
        str << "#{indent}\tfree(buff_#{i});\n"
      else
        # treat cc types as pointers
        arg[:type] << "*" if CC_TYPES.include?(arg[:type])
        str << "#{indent}\t#{arg[:type]} arg#{i} = (#{arg[:type]})JSObjectGetPrivate((JSObjectRef)arguments[#{i}]);\n"
      end
    end
    # do the call
    arg_len = @arguments.length
    arg_list = (["arg"] * arg_len).zip( (0...arg_len) ).map { |a| a.join }.join(", ")
    if @name == klass.name
      str << "#{indent}\t#{klass.name}::#{@name}(#{arg_list});\n"
    else
      str << "#{indent}\t#{@return_type} ret = #{klass.name}::#{@name}(#{arg_list});\n"
      if NUMBER_TYPES.include?(@return_type)
        str << "#{indent}\treturn JSValueMakeNumber(ctx, ret);\n"
      elsif CC_TYPES.include?(@return_type)
        str << "#{@return_type}* retObj = new #{@return_type}();\n"
        str << "#{@return_type}_COPY(ret, retObj);"
      elsif @return_type.downcase == "bool"
        str << "#{indent}\treturn JSValueMakeBoolean(ctx, ret);\n"
      elsif @return_type == "std::string"
        str << "#{indent}\tJSStringRef retStr = JSStringCreateWithUTF8CString(ret.c_str());\n"
        str << "#{indent}\tJSValueRef retVal = JSValueMakeString(ctx, retStr);\n"
        str << "#{indent}\tJSStringRelease(retStr);\n"
        str << "#{indent}\treturn retVal;\n"
      end
    end
    str << "#{indent}}\n"
    str << "#{indent}return JSValueMakeUndefined(ctx);\n"
    str << "}\n" unless conent_only
    str
  end

  def append_current_argument
    len = @current_argument.size
    raise "invalid argument" if len < 2
    @arguments << {:type => @current_argument[0, len-1].join(" "), :name => @current_argument[-1]}
    @current_argument = []
  end

  def process_token(token, token_type)
    case token_type
    when :id, :star, :ns_sep
      case @waiting_for
      when :return_type
        case token_type
        when :id
          last_type = @return_type[-1]
          if last_type && last_type[-1] == ":"
            @return_type[-1] = last_type + token
          else
            @return_type << token
          end
        else
          @return_type[-1] = @return_type[-1] + (token_type == :star ? '*' : '::')
        end
      when :argument
        case token_type
        when :id
          last_type = @current_argument[-1]
          if last_type && last_type[-1] == ":"
            @current_argument[-1] = last_type + token
          else
            @current_argument << token
          end
        else
          @current_argument[-1] = @current_argument[-1] + (token_type == :star ? '*' : '::')
        end
      else
        raise "invalid token: #{token}"
      end
    when :open_parenthesis
      @name = @return_type[-1]
      @return_type = @return_type[0, @return_type.length - 1].join(" ")
      @waiting_for = :argument
    when :comma
      append_current_argument
      @waiting_for = :argument
    when :close_parenthesis
      append_current_argument if @current_argument.size > 0
      @waiting_for = :semicolon
    when :semicolon
      @parser.method_ended(self)
    end
  end
  
  def to_s
    "{:name => #{@name.inspect}, :static => #{@static}, :return => #{@return_type.inspect}, :arguments => #{@arguments.inspect}}"
  end
end

class CppClass
  attr_reader :public_methods, :name
  attr_accessor :constructor, :begin

  def initialize(name)
    @name = name
    @begin = false
    @constructor = nil
    @public_methods = []
    @all_static = false
  end

  def js_name
    return "S_#{@name}"
  end
  
  def check_all_static
    @all_static = true
    @public_methods.each { |m| @all_static = false unless m.static }
    @all_static
  end

  def generate_header_code
    check_all_static
    str = ""
    str << 
    str << "extern JSClassRef __js_#{@name};\n"
    str << <<-EOS
class #{js_name}
{
public:
\tstatic JSObjectRef jsConstructor(JSContextRef ctx, JSObjectRef constructor, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
\tstatic bool jsHasProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName);
\tstatic JSValueRef jsGetProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyNameJS, JSValueRef* exception);
\tstatic JSStaticFunction *jsStaticFunctions();
    EOS
    unless @all_static
      str << <<-EOS
// constructor
#{js_name}(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[]);
      EOS
    end
    str << "\n"
    @public_methods.each do |method|
      str << "\tJS_STATIC_FUNC_DEF(js_#{method.name});\n"
    end
    str << "};\n\n"
    str
  end

  def generate_binding_code
    check_all_static
    str = ""
    str << "JSClassRef __js_#{@name};\n"
    str << <<-EOS
JSObjectRef #{js_name}::jsConstructor(JSContextRef ctx, JSObjectRef constructor, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
    EOS
    unless @all_static
      str << <<-EOS
\tJSObjectRef obj = JSObjectMake(ctx, js_#{js_name}_class, NULL);
\t#{js_name} *cobj = new #{js_name}();
\tif (cobj && cobj->initWithContext(ctx, obj, argumentCount, arguments)) {
\t\tJSObjectSetPrivate(obj, cobj);
\t\treturn obj;
\t}
      EOS
    end
    str << <<-EOS
\treturn NULL;
}
bool #{js_name}::jsHasProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName)
{
\treturn false;
}
JSValueRef #{js_name}::jsGetProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyNameJS, JSValueRef* exception)
{
\treturn JSValueMakeUndefined(ctx);
}
    EOS

    unless @all_static
    str << <<-EOS
#{js_name}::#{js_name}(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
#{@constructor.generate_binding_code(self, 1, true) unless @constructor.nil?}
}
      EOS
    end
    str << "JSStaticFunction *#{self.js_name}::jsStaticFunctions()\n"
    str << "{\n"
    str << "\tstatic JSStaticFunction funcs[] = {\n"
    @public_methods.each do |method|
      if method.static
        str << "\t\t{\"#{method.name}\", #{self.js_name}::js_#{method.name}, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},\n"
      end
    end
    str << "\t\t{0, 0, 0}\n"
    str << "\t};\n"
    str << "\treturn funcs;\n"
    str << "}\n\n"

    @public_methods.each do |method|
      str << method.generate_binding_code(self)
    end
    str << "\n"
    str
  end
end

class CppHeaderParser
  attr_accessor :data

  def initialize(data)
    @last_token_position = nil
    @last_token = nil
    @current_class = nil
    @current_method = nil
    @current_enum = nil
    @in_public = false
    @enums = []
    @classes = []
    @data = data
  end

  def token_begin(token, pos)
    if token == :id
      @last_token_begin = pos
    elsif token == :number
      @last_number_begin = pos
    end
  end

  def method_ended(method)
    # puts "found method: #{@current_method}"
    if @current_method.name =~ /^init/ || @current_method.name == @current_class.name
      if @current_class.constructor
        @current_method.min_arg_count = [@current_method.arguments.size, @current_class.constructor.arguments.size].min
      end
      @current_class.constructor = @current_method
    else
      @current_class.public_methods << @current_method
    end
    @current_method = nil
  end

  def enum_ended(enum)
    # puts "found enum: #{enum}"
    @enums << @current_enum
    @current_enum = nil
  end

  def found_token(token, pos)
    # puts "found token: #{token}"
    case token
    when :id
      process_id(pos)
    when :number
      raise "parser error" if !@current_enum
      token_val = @data[@last_number_begin, pos - @last_number_begin + 1]
      @current_enum.process_token(token_val, :number)
    when :static
      raise "parsing error" if @current_method
      @current_method = CppMethod.new(self, true) if @in_public
    when :enum
      raise "parsing error" if @current_enum || @current_class
      @current_enum = CppEnum.new(self)
    when :close_class
      # puts @current_class.inspect
      @classes << @current_class
      @current_class = nil
    when :open_bracket
      if @current_class and !@current_class.begin
        @current_class.begin = true
      else
        @current_method.process_token(token.to_s, token) if @current_method
        @current_enum.process_token(token.to_s, token) if @current_enum
      end
    when :public
      if @current_class and @current_class.begin
        @in_public = true
      end
    when :private, :protected
      if @current_class and @current_class.begin
        @in_public = false
      end
    else
      @current_method.process_token(token.to_s, token) if @current_method
      @current_enum.process_token(token.to_s, token) if @current_enum
    end
    @last_token = token
  end

  def generate_binding_code(header_file)
    outname = File.basename(header_file, ".h")
    out = File.open("#{outname}_generated.cpp", "w+")
    header = File.open("#{outname}_generated.h", "w+")
    # output constants used across code
    out.puts "#include <JavaScriptCore/JavaScriptCore.h>"
    out.puts "#include \"cocos2d.h\""
    out.puts "#include \"ScriptingCore.h\""
    out.puts "#include \"#{header_file}\"\n\n"
    out.puts "static JSGlobalContextRef GLOBAL_CTX = ScriptingCore::getInstance().getGlobalContext();"
    out.puts "static JSObjectRef GLOBAL_OBJ = ScriptingCore::getInstance().getGlobalObject();\n\n"
    out.puts "#define CCPoint_COPY(val, ptr) do {ptr->x = val.x; ptr->y = val.y} while(0)"
    out.puts "#define CCSize_COPY(val, ptr) do {ptr->width = val.width; ptr->height = val.height} while(0)\n\n"

    # first, output the enums
    @enums.each do |enum|
      header.puts enum.generate_header_code
      out.puts enum.generate_binding_code
    end

    header.puts "\n"
    out.puts "\n"

    # now the classes
    @classes.each do |klass|
      out.puts klass.generate_binding_code
      header.puts klass.generate_header_code
    end
    out.close
    header.close
  end

  def process_id(pos)
    token_val = @data[@last_token_begin, pos - @last_token_begin + 1]
    case @last_token
    when :class
      @current_class = CppClass.new(token_val)
    else
      if @current_class && @in_public
        if @current_method.nil?
          @current_method = CppMethod.new(self)
        end
        @current_method.process_token(token_val, :id)
      elsif @current_enum
        @current_enum.process_token(token_val, :id)
      end
    end
  end
end

def run_machine(parser, fname)
  data = parser.data
  eof = data.length
  line_no = 1

  begin
    %% write init;
    %% write exec;
  rescue => err
    puts "Parser error at line #{line_no}"
    puts err
  end

  if (cs != cpp_header_parser_error)
    parser.generate_binding_code(fname)
  else
    $stderr.puts "error parsing at line #{line_no}"
    $stderr.puts ">> p: #{p} pe: #{pe}; p[p-5,5]: '#{data[p-5,5]}'"
    exit(1)
  end
end

while fname = ARGV.shift
  parser = CppHeaderParser.new(File.read(fname))
  run_machine(parser, File.basename(fname))
end
