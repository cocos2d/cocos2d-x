
--------------------------------
-- @module Pass
-- @extend RenderState
-- @parent_module cc

--------------------------------
--  Unbinds the Pass.<br>
-- This method must be called AFTER calling the actuall draw call
-- @function [parent=#Pass] unbind 
-- @param self
-- @return Pass#Pass self (return value: cc.Pass)
        
--------------------------------
-- @overload self, mat4_table, bool         
-- @overload self, mat4_table         
-- @function [parent=#Pass] bind
-- @param self
-- @param #mat4_table modelView
-- @param #bool bindAttributes
-- @return Pass#Pass self (return value: cc.Pass)

--------------------------------
-- Returns a clone (deep-copy) of this instance 
-- @function [parent=#Pass] clone 
-- @param self
-- @return Pass#Pass ret (return value: cc.Pass)
        
--------------------------------
--  Returns the GLProgramState 
-- @function [parent=#Pass] getGLProgramState 
-- @param self
-- @return GLProgramState#GLProgramState ret (return value: cc.GLProgramState)
        
--------------------------------
-- Returns the vertex attribute binding for this pass.<br>
-- return The vertex attribute binding for this pass.
-- @function [parent=#Pass] getVertexAttributeBinding 
-- @param self
-- @return VertexAttribBinding#VertexAttribBinding ret (return value: cc.VertexAttribBinding)
        
--------------------------------
-- 
-- @function [parent=#Pass] getHash 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- Sets a vertex attribute binding for this pass.<br>
-- When a mesh binding is set, the VertexAttribBinding will be automatically<br>
-- bound when the bind() method is called for the pass.<br>
-- param binding The VertexAttribBinding to set (or NULL to remove an existing binding).
-- @function [parent=#Pass] setVertexAttribBinding 
-- @param self
-- @param #cc.VertexAttribBinding binding
-- @return Pass#Pass self (return value: cc.Pass)
        
--------------------------------
-- 
-- @function [parent=#Pass] create 
-- @param self
-- @param #cc.Technique parent
-- @return Pass#Pass ret (return value: cc.Pass)
        
--------------------------------
--  Creates a Pass with a GLProgramState.
-- @function [parent=#Pass] createWithGLProgramState 
-- @param self
-- @param #cc.Technique parent
-- @param #cc.GLProgramState programState
-- @return Pass#Pass ret (return value: cc.Pass)
        
return nil
