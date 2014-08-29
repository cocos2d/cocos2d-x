
--------------------------------
-- @module ActionObject
-- @extend Ref
-- @parent_module ccs

--------------------------------
-- @function [parent=#ActionObject] setCurrentTime 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#ActionObject] pause 
-- @param self
        
--------------------------------
-- @function [parent=#ActionObject] setName 
-- @param self
-- @param #char char
        
--------------------------------
-- @function [parent=#ActionObject] setUnitTime 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#ActionObject] getTotalTime 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#ActionObject] getName 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- @function [parent=#ActionObject] stop 
-- @param self
        
--------------------------------
-- @overload self, cc.CallFunc         
-- @overload self         
-- @function [parent=#ActionObject] play
-- @param self
-- @param #cc.CallFunc callfunc

--------------------------------
-- @function [parent=#ActionObject] getCurrentTime 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#ActionObject] removeActionNode 
-- @param self
-- @param #ccs.ActionNode actionnode
        
--------------------------------
-- @function [parent=#ActionObject] getLoop 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ActionObject] addActionNode 
-- @param self
-- @param #ccs.ActionNode actionnode
        
--------------------------------
-- @function [parent=#ActionObject] getUnitTime 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#ActionObject] isPlaying 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ActionObject] updateToFrameByTime 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#ActionObject] setLoop 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ActionObject] simulationActionUpdate 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#ActionObject] ActionObject 
-- @param self
        
return nil
