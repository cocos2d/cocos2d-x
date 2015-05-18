
--------------------------------
-- @module GLProgramState
-- @extend Ref
-- @parent_module cc

--------------------------------
--  Get the flag of vertex attribs used by OR operation.
-- @function [parent=#GLProgramState] getVertexAttribsFlags 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- @overload self, int, vec4_table         
-- @overload self, string, vec4_table         
-- @function [parent=#GLProgramState] setUniformVec4
-- @param self
-- @param #string uniformName
-- @param #vec4_table value
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
-- @overload self, int, vec3_table         
-- @overload self, string, vec3_table         
-- @function [parent=#GLProgramState] setUniformVec3
-- @param self
-- @param #string uniformName
-- @param #vec3_table value
-- @return GLProgramState#GLProgramState self (return value: cc.GLProgramState)

--------------------------------
-- Apply GLProgram, attributes and uniforms.<br>
-- param modelView The applied modelView matrix to shader.
-- @function [parent=#GLProgramState] apply 
-- @param self
-- @param #mat4_table modelView
-- @return GLProgramState#GLProgramState self (return value: cc.GLProgramState)
        
--------------------------------
-- @overload self, int, long, vec4_table         
-- @overload self, string, long, vec4_table         
-- @function [parent=#GLProgramState] setUniformVec4v
-- @param self
-- @param #string uniformName
-- @param #long size
-- @param #vec4_table pointer
-- @return GLProgramState#GLProgramState self (return value: cc.GLProgramState)

--------------------------------
-- Apply GLProgram, and built in uniforms.<br>
-- param modelView The applied modelView matrix to shader.
-- @function [parent=#GLProgramState] applyGLProgram 
-- @param self
-- @param #mat4_table modelView
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
-- @overload self, int, long, vec2_table         
-- @overload self, string, long, vec2_table         
-- @function [parent=#GLProgramState] setUniformVec2v
-- @param self
-- @param #string uniformName
-- @param #long size
-- @param #vec2_table pointer
-- @return GLProgramState#GLProgramState self (return value: cc.GLProgramState)

--------------------------------
-- Get the number of user defined uniform count.
-- @function [parent=#GLProgramState] getUniformCount 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- Apply attributes.<br>
-- param applyAttribFlags Call GL::enableVertexAttribs(_vertexAttribsFlags) or not.
-- @function [parent=#GLProgramState] applyAttributes 
-- @param self
-- @return GLProgramState#GLProgramState self (return value: cc.GLProgramState)
        
--------------------------------
--  Returns a new copy of the GLProgramState. The GLProgram is reused 
-- @function [parent=#GLProgramState] clone 
-- @param self
-- @return GLProgramState#GLProgramState ret (return value: cc.GLProgramState)
        
--------------------------------
-- @{ <br>
-- Setter and Getter of the owner GLProgram binded in this program state.
-- @function [parent=#GLProgramState] setGLProgram 
-- @param self
-- @param #cc.GLProgram glprogram
-- @return GLProgramState#GLProgramState self (return value: cc.GLProgramState)
        
--------------------------------
-- @overload self, int, long, float         
-- @overload self, string, long, float         
-- @function [parent=#GLProgramState] setUniformFloatv
-- @param self
-- @param #string uniformName
-- @param #long size
-- @param #float pointer
-- @return GLProgramState#GLProgramState self (return value: cc.GLProgramState)

--------------------------------
-- 
-- @function [parent=#GLProgramState] getGLProgram 
-- @param self
-- @return GLProgram#GLProgram ret (return value: cc.GLProgram)
        
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
-- Apply user defined uniforms.
-- @function [parent=#GLProgramState] applyUniforms 
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
-- @overload self, int, mat4_table         
-- @overload self, string, mat4_table         
-- @function [parent=#GLProgramState] setUniformMat4
-- @param self
-- @param #string uniformName
-- @param #mat4_table value
-- @return GLProgramState#GLProgramState self (return value: cc.GLProgramState)

--------------------------------
-- @overload self, int, long, vec3_table         
-- @overload self, string, long, vec3_table         
-- @function [parent=#GLProgramState] setUniformVec3v
-- @param self
-- @param #string uniformName
-- @param #long size
-- @param #vec3_table pointer
-- @return GLProgramState#GLProgramState self (return value: cc.GLProgramState)

--------------------------------
-- Get the number of vertex attributes.
-- @function [parent=#GLProgramState] getVertexAttribCount 
-- @param self
-- @return long#long ret (return value: long)
        
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
        
--------------------------------
--  gets-or-creates an instance of GLProgramState for given shaders 
-- @function [parent=#GLProgramState] getOrCreateWithShaders 
-- @param self
-- @param #string vertexShader
-- @param #string fragShader
-- @param #string compileTimeDefines
-- @return GLProgramState#GLProgramState ret (return value: cc.GLProgramState)
        
return nil
