
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
-- @param #int uniformLocation
-- @param #unsigned int textureId
-- @return GLProgramState#GLProgramState self (return value: cc.GLProgramState)

--------------------------------
-- @overload self, int, mat4_table         
-- @overload self, string, mat4_table         
-- @function [parent=#GLProgramState] setUniformMat4
-- @param self
-- @param #string uniformName
-- @param #mat4_table value
-- @return GLProgramState#GLProgramState self (return value: cc.GLProgramState)

--------------------------------
-- 
-- @function [parent=#GLProgramState] applyUniforms 
-- @param self
-- @return GLProgramState#GLProgramState self (return value: cc.GLProgramState)
        
--------------------------------
-- 
-- @function [parent=#GLProgramState] applyGLProgram 
-- @param self
-- @param #mat4_table modelView
-- @return GLProgramState#GLProgramState self (return value: cc.GLProgramState)
        
--------------------------------
-- 
-- @function [parent=#GLProgramState] getUniformCount 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- apply vertex attributes<br>
-- param applyAttribFlags Call GL::enableVertexAttribs(_vertexAttribsFlags) or not
-- @function [parent=#GLProgramState] applyAttributes 
-- @param self
-- @return GLProgramState#GLProgramState self (return value: cc.GLProgramState)
        
--------------------------------
-- @overload self, int, float         
-- @overload self, string, float         
-- @function [parent=#GLProgramState] setUniformFloat
-- @param self
-- @param #string uniformName
-- @param #float value
-- @return GLProgramState#GLProgramState self (return value: cc.GLProgramState)

--------------------------------
-- @overload self, int, vec3_table         
-- @overload self, string, vec3_table         
-- @function [parent=#GLProgramState] setUniformVec3
-- @param self
-- @param #string uniformName
-- @param #vec3_table value
-- @return GLProgramState#GLProgramState self (return value: cc.GLProgramState)

--------------------------------
-- @overload self, int, int         
-- @overload self, string, int         
-- @function [parent=#GLProgramState] setUniformInt
-- @param self
-- @param #string uniformName
-- @param #int value
-- @return GLProgramState#GLProgramState self (return value: cc.GLProgramState)

--------------------------------
-- 
-- @function [parent=#GLProgramState] getVertexAttribCount 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- @overload self, int, vec4_table         
-- @overload self, string, vec4_table         
-- @function [parent=#GLProgramState] setUniformVec4
-- @param self
-- @param #string uniformName
-- @param #vec4_table value
-- @return GLProgramState#GLProgramState self (return value: cc.GLProgramState)

--------------------------------
-- 
-- @function [parent=#GLProgramState] setGLProgram 
-- @param self
-- @param #cc.GLProgram glprogram
-- @return GLProgramState#GLProgramState self (return value: cc.GLProgramState)
        
--------------------------------
-- @overload self, int, vec2_table         
-- @overload self, string, vec2_table         
-- @function [parent=#GLProgramState] setUniformVec2
-- @param self
-- @param #string uniformName
-- @param #vec2_table value
-- @return GLProgramState#GLProgramState self (return value: cc.GLProgramState)

--------------------------------
-- 
-- @function [parent=#GLProgramState] getVertexAttribsFlags 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- 
-- @function [parent=#GLProgramState] apply 
-- @param self
-- @param #mat4_table modelView
-- @return GLProgramState#GLProgramState self (return value: cc.GLProgramState)
        
--------------------------------
-- 
-- @function [parent=#GLProgramState] getGLProgram 
-- @param self
-- @return GLProgram#GLProgram ret (return value: cc.GLProgram)
        
--------------------------------
--  returns a new instance of GLProgramState for a given GLProgram 
-- @function [parent=#GLProgramState] create 
-- @param self
-- @param #cc.GLProgram glprogram
-- @return GLProgramState#GLProgramState ret (return value: cc.GLProgramState)
        
--------------------------------
--  gets-or-creates an instance of GLProgramState for a given GLProgramName 
-- @function [parent=#GLProgramState] getOrCreateWithGLProgramName 
-- @param self
-- @param #string glProgramName
-- @return GLProgramState#GLProgramState ret (return value: cc.GLProgramState)
        
--------------------------------
--  gets-or-creates an instance of GLProgramState for a given GLProgram 
-- @function [parent=#GLProgramState] getOrCreateWithGLProgram 
-- @param self
-- @param #cc.GLProgram glprogram
-- @return GLProgramState#GLProgramState ret (return value: cc.GLProgramState)
        
return nil
