
--------------------------------
-- @module ActionObject
-- @extend Ref
-- @parent_module ccs

--------------------------------
-- Sets the current time of frame.<br>
-- param fTime   the current time of frame
-- @function [parent=#ActionObject] setCurrentTime 
-- @param self
-- @param #float fTime
-- @return ActionObject#ActionObject self (return value: ccs.ActionObject)
        
--------------------------------
-- Pause the action.
-- @function [parent=#ActionObject] pause 
-- @param self
-- @return ActionObject#ActionObject self (return value: ccs.ActionObject)
        
--------------------------------
-- Sets name for object<br>
-- param name    name of object
-- @function [parent=#ActionObject] setName 
-- @param self
-- @param #char name
-- @return ActionObject#ActionObject self (return value: ccs.ActionObject)
        
--------------------------------
-- Sets the time interval of frame.<br>
-- param fTime   the time interval of frame
-- @function [parent=#ActionObject] setUnitTime 
-- @param self
-- @param #float fTime
-- @return ActionObject#ActionObject self (return value: ccs.ActionObject)
        
--------------------------------
-- Gets the total time of frame.<br>
-- return the total time of frame
-- @function [parent=#ActionObject] getTotalTime 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Gets name of object<br>
-- return name of object
-- @function [parent=#ActionObject] getName 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- Stop the action.
-- @function [parent=#ActionObject] stop 
-- @param self
-- @return ActionObject#ActionObject self (return value: ccs.ActionObject)
        
--------------------------------
-- @overload self, cc.CallFunc         
-- @overload self         
-- @function [parent=#ActionObject] play
-- @param self
-- @param #cc.CallFunc func
-- @return ActionObject#ActionObject self (return value: ccs.ActionObject)

--------------------------------
-- Gets the current time of frame.<br>
-- return the current time of frame
-- @function [parent=#ActionObject] getCurrentTime 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Removes a ActionNode which play the action.<br>
-- param node    the ActionNode which play the action
-- @function [parent=#ActionObject] removeActionNode 
-- @param self
-- @param #ccs.ActionNode node
-- @return ActionObject#ActionObject self (return value: ccs.ActionObject)
        
--------------------------------
-- Gets if the action will loop play.<br>
-- return   that if the action will loop play
-- @function [parent=#ActionObject] getLoop 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Adds a ActionNode to play the action.<br>
-- param node    the ActionNode which will play the action
-- @function [parent=#ActionObject] addActionNode 
-- @param self
-- @param #ccs.ActionNode node
-- @return ActionObject#ActionObject self (return value: ccs.ActionObject)
        
--------------------------------
-- Gets the time interval of frame.<br>
-- return the time interval of frame
-- @function [parent=#ActionObject] getUnitTime 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Return if the action is playing.<br>
-- return true if the action is playing, false the otherwise
-- @function [parent=#ActionObject] isPlaying 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ActionObject] updateToFrameByTime 
-- @param self
-- @param #float fTime
-- @return ActionObject#ActionObject self (return value: ccs.ActionObject)
        
--------------------------------
-- Sets if the action will loop play.<br>
-- param bLoop     that if the action will loop play
-- @function [parent=#ActionObject] setLoop 
-- @param self
-- @param #bool bLoop
-- @return ActionObject#ActionObject self (return value: ccs.ActionObject)
        
--------------------------------
-- 
-- @function [parent=#ActionObject] simulationActionUpdate 
-- @param self
-- @param #float dt
-- @return ActionObject#ActionObject self (return value: ccs.ActionObject)
        
--------------------------------
-- Default constructor
-- @function [parent=#ActionObject] ActionObject 
-- @param self
-- @return ActionObject#ActionObject self (return value: ccs.ActionObject)
        
return nil
