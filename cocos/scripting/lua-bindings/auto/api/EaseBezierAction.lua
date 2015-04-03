
--------------------------------
-- @module EaseBezierAction
-- @extend ActionEase
-- @parent_module cc

--------------------------------
-- brief Set the bezier parameters.
-- @function [parent=#EaseBezierAction] setBezierParamer 
-- @param self
-- @param #float p0
-- @param #float p1
-- @param #float p2
-- @param #float p3
-- @return EaseBezierAction#EaseBezierAction self (return value: cc.EaseBezierAction)
        
--------------------------------
-- brief Create the action with the inner action.<br>
-- param action The pointer of the inner action.<br>
-- return A pointer of EaseBezierAction action. If creation failed, return nil.
-- @function [parent=#EaseBezierAction] create 
-- @param self
-- @param #cc.ActionInterval action
-- @return EaseBezierAction#EaseBezierAction ret (return value: cc.EaseBezierAction)
        
--------------------------------
-- 
-- @function [parent=#EaseBezierAction] clone 
-- @param self
-- @return EaseBezierAction#EaseBezierAction ret (return value: cc.EaseBezierAction)
        
--------------------------------
-- 
-- @function [parent=#EaseBezierAction] update 
-- @param self
-- @param #float time
-- @return EaseBezierAction#EaseBezierAction self (return value: cc.EaseBezierAction)
        
--------------------------------
-- 
-- @function [parent=#EaseBezierAction] reverse 
-- @param self
-- @return EaseBezierAction#EaseBezierAction ret (return value: cc.EaseBezierAction)
        
return nil
