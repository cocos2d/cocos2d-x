
--------------------------------
-- @module GLProgramState
-- @extend Ref
-- @parent_module cc

--------------------------------
-- overload function: setUniformTexture(string, unsigned int)
--          
-- overload function: setUniformTexture(string, cc.Texture2D)
--          
-- overload function: setUniformTexture(int, cc.Texture2D)
--          
-- overload function: setUniformTexture(int, unsigned int)
--          
-- @function [parent=#GLProgramState] setUniformTexture
-- @param self
-- @param #int int
-- @param #unsigned int int

--------------------------------
-- overload function: setUniformMat4(int, mat4_table)
--          
-- overload function: setUniformMat4(string, mat4_table)
--          
-- @function [parent=#GLProgramState] setUniformMat4
-- @param self
-- @param #string str
-- @param #mat4_table mat4

--------------------------------
-- @function [parent=#GLProgramState] applyUniforms 
-- @param self
        
--------------------------------
-- @function [parent=#GLProgramState] applyGLProgram 
-- @param self
-- @param #mat4_table mat4
        
--------------------------------
-- @function [parent=#GLProgramState] getUniformCount 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- @function [parent=#GLProgramState] applyAttributes 
-- @param self
        
--------------------------------
-- overload function: setUniformFloat(int, float)
--          
-- overload function: setUniformFloat(string, float)
--          
-- @function [parent=#GLProgramState] setUniformFloat
-- @param self
-- @param #string str
-- @param #float float

--------------------------------
-- overload function: setUniformVec3(int, vec3_table)
--          
-- overload function: setUniformVec3(string, vec3_table)
--          
-- @function [parent=#GLProgramState] setUniformVec3
-- @param self
-- @param #string str
-- @param #vec3_table vec3

--------------------------------
-- overload function: setUniformInt(int, int)
--          
-- overload function: setUniformInt(string, int)
--          
-- @function [parent=#GLProgramState] setUniformInt
-- @param self
-- @param #string str
-- @param #int int

--------------------------------
-- @function [parent=#GLProgramState] getVertexAttribCount 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- overload function: setUniformVec4(int, vec4_table)
--          
-- overload function: setUniformVec4(string, vec4_table)
--          
-- @function [parent=#GLProgramState] setUniformVec4
-- @param self
-- @param #string str
-- @param #vec4_table vec4

--------------------------------
-- @function [parent=#GLProgramState] setGLProgram 
-- @param self
-- @param #cc.GLProgram glprogram
        
--------------------------------
-- overload function: setUniformVec2(int, vec2_table)
--          
-- overload function: setUniformVec2(string, vec2_table)
--          
-- @function [parent=#GLProgramState] setUniformVec2
-- @param self
-- @param #string str
-- @param #vec2_table vec2

--------------------------------
-- @function [parent=#GLProgramState] getVertexAttribsFlags 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- @function [parent=#GLProgramState] apply 
-- @param self
-- @param #mat4_table mat4
        
--------------------------------
-- @function [parent=#GLProgramState] getGLProgram 
-- @param self
-- @return GLProgram#GLProgram ret (return value: cc.GLProgram)
        
--------------------------------
-- @function [parent=#GLProgramState] create 
-- @param self
-- @param #cc.GLProgram glprogram
-- @return GLProgramState#GLProgramState ret (return value: cc.GLProgramState)
        
--------------------------------
-- @function [parent=#GLProgramState] getOrCreateWithGLProgramName 
-- @param self
-- @param #string str
-- @return GLProgramState#GLProgramState ret (return value: cc.GLProgramState)
        
--------------------------------
-- @function [parent=#GLProgramState] getOrCreateWithGLProgram 
-- @param self
-- @param #cc.GLProgram glprogram
-- @return GLProgramState#GLProgramState ret (return value: cc.GLProgramState)
        
return nil
