
--------------------------------
-- @module ActionManagerEx
-- @extend Ref
-- @parent_module ccs

--------------------------------
-- Stop an Action with a name.<br>
-- param jsonName  UI file name<br>
-- param actionName  action name in teh UIfile.<br>
-- return  ActionObject which named as the param name
-- @function [parent=#ActionManagerEx] stopActionByName 
-- @param self
-- @param #char jsonName
-- @param #char actionName
-- @return ActionObject#ActionObject ret (return value: ccs.ActionObject)
        
--------------------------------
-- Gets an ActionObject with a name.<br>
-- param jsonName  UI file name<br>
-- param actionName  action name in the UI file.<br>
-- return  ActionObject which named as the param name
-- @function [parent=#ActionManagerEx] getActionByName 
-- @param self
-- @param #char jsonName
-- @param #char actionName
-- @return ActionObject#ActionObject ret (return value: ccs.ActionObject)
        
--------------------------------
-- @overload self, char, char, cc.CallFunc         
-- @overload self, char, char         
-- @function [parent=#ActionManagerEx] playActionByName
-- @param self
-- @param #char jsonName
-- @param #char actionName
-- @param #cc.CallFunc func
-- @return ActionObject#ActionObject ret (return value: ccs.ActionObject)

--------------------------------
-- Release all actions.
-- @function [parent=#ActionManagerEx] releaseActions 
-- @param self
        
--------------------------------
-- Purges ActionManager point.<br>
-- js purge<br>
-- lua destroyActionManager
-- @function [parent=#ActionManagerEx] destroyInstance 
-- @param self
        
--------------------------------
-- Gets the static instance of ActionManager.<br>
-- js getInstance<br>
-- lua getInstance
-- @function [parent=#ActionManagerEx] getInstance 
-- @param self
-- @return ActionManagerEx#ActionManagerEx ret (return value: ccs.ActionManagerEx)
        
return nil
