
--------------------------------
-- @module ActionManagerEx
-- @extend Ref
-- @parent_module ccs

--------------------------------
-- overload function: playActionByName(char, char, cc.CallFunc)
--          
-- overload function: playActionByName(char, char)
--          
-- @function [parent=#ActionManagerEx] playActionByName
-- @param self
-- @param #char char
-- @param #char char
-- @param #cc.CallFunc callfunc
-- @return ActionObject#ActionObject ret (retunr value: ccs.ActionObject)

--------------------------------
-- @function [parent=#ActionManagerEx] getActionByName 
-- @param self
-- @param #char char
-- @param #char char
-- @return ActionObject#ActionObject ret (return value: ccs.ActionObject)
        
--------------------------------
-- @function [parent=#ActionManagerEx] initWithBinary 
-- @param self
-- @param #char char
-- @param #cc.Ref ref
-- @param #ccs.CocoLoader cocoloader
-- @param #ccs.stExpCocoNode stexpcoconode
        
--------------------------------
-- @function [parent=#ActionManagerEx] releaseActions 
-- @param self
        
--------------------------------
-- @function [parent=#ActionManagerEx] destroyInstance 
-- @param self
        
--------------------------------
-- @function [parent=#ActionManagerEx] getInstance 
-- @param self
-- @return ActionManagerEx#ActionManagerEx ret (return value: ccs.ActionManagerEx)
        
return nil
