
--------------------------------
-- @module GLProgram
-- @extend Ref

--------------------------------
-- @function [parent=#GLProgram] getFragmentShaderLog 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#GLProgram] initWithByteArrays 
-- @param self
-- @param #char char
-- @param #char char
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#GLProgram] initWithFilenames 
-- @param self
-- @param #string str
-- @param #string str
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#GLProgram] use 
-- @param self
        
--------------------------------
-- @function [parent=#GLProgram] getVertexShaderLog 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- overload function: setUniformsForBuiltins(mat4_table)
--          
-- overload function: setUniformsForBuiltins()
--          
-- @function [parent=#GLProgram] setUniformsForBuiltins
-- @param self
-- @param #mat4_table mat4

--------------------------------
-- @function [parent=#GLProgram] updateUniforms 
-- @param self
        
--------------------------------
-- @function [parent=#GLProgram] setUniformLocationWith1i 
-- @param self
-- @param #int int
-- @param #int int
        
--------------------------------
-- @function [parent=#GLProgram] reset 
-- @param self
        
--------------------------------
-- @function [parent=#GLProgram] bindAttribLocation 
-- @param self
-- @param #string str
-- @param #unsigned int int
        
--------------------------------
-- @function [parent=#GLProgram] getAttribLocation 
-- @param self
-- @param #string str
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#GLProgram] link 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#GLProgram] createWithByteArrays 
-- @param self
-- @param #char char
-- @param #char char
-- @return GLProgram#GLProgram ret (return value: cc.GLProgram)
        
--------------------------------
-- @function [parent=#GLProgram] createWithFilenames 
-- @param self
-- @param #string str
-- @param #string str
-- @return GLProgram#GLProgram ret (return value: cc.GLProgram)
        
--------------------------------
-- @function [parent=#GLProgram] GLProgram 
-- @param self
        
return nil
