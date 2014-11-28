
--------------------------------
-- @module Follow
-- @extend Action
-- @parent_module cc

--------------------------------
--  alter behavior - turn on/off boundary 
-- @function [parent=#Follow] setBoundarySet 
-- @param self
-- @param #bool value
        
--------------------------------
-- 
-- @function [parent=#Follow] isBoundarySet 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Creates the action with a set boundary or with no boundary.<br>
-- param followedNode  The node to be followed.<br>
-- param rect  The boundary. If \p rect is equal to Rect::ZERO, it'll work<br>
-- with no boundary.
-- @function [parent=#Follow] create 
-- @param self
-- @param #cc.Node followedNode
-- @param #rect_table rect
-- @return Follow#Follow ret (return value: cc.Follow)
        
--------------------------------
-- 
-- @function [parent=#Follow] step 
-- @param self
-- @param #float dt
        
--------------------------------
-- 
-- @function [parent=#Follow] clone 
-- @param self
-- @return Follow#Follow ret (return value: cc.Follow)
        
--------------------------------
-- 
-- @function [parent=#Follow] stop 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#Follow] reverse 
-- @param self
-- @return Follow#Follow ret (return value: cc.Follow)
        
--------------------------------
-- 
-- @function [parent=#Follow] isDone 
-- @param self
-- @return bool#bool ret (return value: bool)
        
return nil
