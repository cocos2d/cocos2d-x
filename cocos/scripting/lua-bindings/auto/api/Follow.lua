
--------------------------------
-- @module Follow
-- @extend Action
-- @parent_module cc

--------------------------------
--  Alter behavior - turn on/off boundary. <br>
-- param value Turn on/off boundary.
-- @function [parent=#Follow] setBoundarySet 
-- @param self
-- @param #bool value
-- @return Follow#Follow self (return value: cc.Follow)
        
--------------------------------
-- Initializes the action with a set boundary or with no boundary.<br>
-- param followedNode  The node to be followed.<br>
-- param rect  The boundary. If \p rect is equal to Rect::ZERO, it'll work<br>
-- with no boundary.
-- @function [parent=#Follow] initWithTarget 
-- @param self
-- @param #cc.Node followedNode
-- @param #rect_table rect
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Return boundarySet.<br>
-- return Return boundarySet.
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
-- param dt in seconds.<br>
-- js NA
-- @function [parent=#Follow] step 
-- @param self
-- @param #float dt
-- @return Follow#Follow self (return value: cc.Follow)
        
--------------------------------
-- 
-- @function [parent=#Follow] clone 
-- @param self
-- @return Follow#Follow ret (return value: cc.Follow)
        
--------------------------------
-- 
-- @function [parent=#Follow] stop 
-- @param self
-- @return Follow#Follow self (return value: cc.Follow)
        
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
        
--------------------------------
-- js ctor
-- @function [parent=#Follow] Follow 
-- @param self
-- @return Follow#Follow self (return value: cc.Follow)
        
return nil
