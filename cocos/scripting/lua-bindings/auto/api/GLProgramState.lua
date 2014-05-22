
--------------------------------
-- @module GLProgramState
-- @extend Ref

--------------------------------
-- overload function: setUniformTexture(string, unsigned int)
--          
-- overload function: setUniformTexture(string, cc.Texture2D)
--          
-- @function [parent=#GLProgramState] setUniformTexture
-- @param self
-- @param #string str
-- @param #cc.Texture2D texture2d

--------------------------------
-- @function [parent=#GLProgramState] setUniformMat4 
-- @param self
-- @param #string str
-- @param #cc.Mat4 mat4
        
--------------------------------
-- @function [parent=#GLProgramState] getUniformCount 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- @function [parent=#GLProgramState] setUniformFloat 
-- @param self
-- @param #string str
-- @param #float float
        
--------------------------------
-- @function [parent=#GLProgramState] setUniformVec3 
-- @param self
-- @param #string str
-- @param #cc.Vec3 vec3
        
--------------------------------
-- @function [parent=#GLProgramState] setGLProgram 
-- @param self
-- @param #cc.GLProgram glprogram
        
--------------------------------
-- @function [parent=#GLProgramState] setUniformVec4 
-- @param self
-- @param #string str
-- @param #cc.Vec4 vec4
        
--------------------------------
-- @function [parent=#GLProgramState] getVertexAttribCount 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- @function [parent=#GLProgramState] setUniformInt 
-- @param self
-- @param #string str
-- @param #int int
        
--------------------------------
-- @function [parent=#GLProgramState] setUniformVec2 
-- @param self
-- @param #string str
-- @param #cc.Vec2 vec2
        
--------------------------------
-- @function [parent=#GLProgramState] getVertexAttribsFlags 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- @function [parent=#GLProgramState] apply 
-- @param self
-- @param #cc.Mat4 mat4
        
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
