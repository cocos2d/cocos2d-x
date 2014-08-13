
--------------------------------
-- @module GLProgramState
-- @extend Ref
-- @parent_module cc

--------------------------------
-- @overload self, string, unsigned int         
-- @overload self, string, cc.Texture2D         
-- @overload self, int, cc.Texture2D         
-- @overload self, int, unsigned int         
-- @function [parent=#GLProgramState] setUniformTexture
-- @param self
-- @param #int int
-- @param #unsigned int int

--------------------------------
-- @overload self, int, mat4_table         
-- @overload self, string, mat4_table         
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
-- @overload self, int, float         
-- @overload self, string, float         
-- @function [parent=#GLProgramState] setUniformFloat
-- @param self
-- @param #string str
-- @param #float float

--------------------------------
-- @overload self, int, vec3_table         
-- @overload self, string, vec3_table         
-- @function [parent=#GLProgramState] setUniformVec3
-- @param self
-- @param #string str
-- @param #vec3_table vec3

--------------------------------
-- @overload self, int, int         
-- @overload self, string, int         
-- @function [parent=#GLProgramState] setUniformInt
-- @param self
-- @param #string str
-- @param #int int

--------------------------------
-- @function [parent=#GLProgramState] getVertexAttribCount 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- @overload self, int, vec4_table         
-- @overload self, string, vec4_table         
-- @function [parent=#GLProgramState] setUniformVec4
-- @param self
-- @param #string str
-- @param #vec4_table vec4

--------------------------------
-- @function [parent=#GLProgramState] setGLProgram 
-- @param self
-- @param #cc.GLProgram glprogram
        
--------------------------------
-- @overload self, int, vec2_table         
-- @overload self, string, vec2_table         
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
