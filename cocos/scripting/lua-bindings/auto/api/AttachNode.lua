
--------------------------------
-- @module AttachNode
-- @extend Node
-- @parent_module cc

--------------------------------
-- creates an AttachNode<br>
-- param attachBone The bone to which the AttachNode is going to attach, the attacheBone must be a bone of the AttachNode's parent
-- @function [parent=#AttachNode] create 
-- @param self
-- @param #cc.Bone3D attachBone
-- @return AttachNode#AttachNode ret (return value: cc.AttachNode)
        
--------------------------------
-- 
-- @function [parent=#AttachNode] visit 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table parentTransform
-- @param #unsigned int parentFlags
        
--------------------------------
-- 
-- @function [parent=#AttachNode] getWorldToNodeTransform 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- 
-- @function [parent=#AttachNode] getNodeToWorldTransform 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
return nil
