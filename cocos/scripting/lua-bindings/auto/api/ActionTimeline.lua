
--------------------------------
-- @module ActionTimeline
-- @extend Action
-- @parent_module ccs

--------------------------------
-- @function [parent=#ActionTimeline] getTimelines 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- @function [parent=#ActionTimeline] getCurrentFrame 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#ActionTimeline] getStartFrame 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#ActionTimeline] pause 
-- @param self
        
--------------------------------
-- @function [parent=#ActionTimeline] setFrameEventCallFunc 
-- @param self
-- @param #function func
        
--------------------------------
-- @function [parent=#ActionTimeline] resume 
-- @param self
        
--------------------------------
-- @function [parent=#ActionTimeline] getDuration 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#ActionTimeline] addTimeline 
-- @param self
-- @param #ccs.Timeline timeline
        
--------------------------------
-- @function [parent=#ActionTimeline] getEndFrame 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#ActionTimeline] setCurrentFrame 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#ActionTimeline] setTimeSpeed 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#ActionTimeline] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ActionTimeline] setDuration 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#ActionTimeline] getTimeSpeed 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#ActionTimeline] gotoFrameAndPause 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#ActionTimeline] isPlaying 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @overload self, int, bool         
-- @overload self, int         
-- @overload self, int, int, bool         
-- @overload self, int, int, int, bool         
-- @function [parent=#ActionTimeline] gotoFrameAndPlay
-- @param self
-- @param #int int
-- @param #int int
-- @param #int int
-- @param #bool bool

--------------------------------
-- @function [parent=#ActionTimeline] removeTimeline 
-- @param self
-- @param #ccs.Timeline timeline
        
--------------------------------
-- @function [parent=#ActionTimeline] clearFrameEventCallFunc 
-- @param self
        
--------------------------------
-- @function [parent=#ActionTimeline] create 
-- @param self
-- @return ActionTimeline#ActionTimeline ret (return value: ccs.ActionTimeline)
        
--------------------------------
-- @function [parent=#ActionTimeline] step 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#ActionTimeline] startWithTarget 
-- @param self
-- @param #cc.Node node
        
--------------------------------
-- @function [parent=#ActionTimeline] clone 
-- @param self
-- @return ActionTimeline#ActionTimeline ret (return value: ccs.ActionTimeline)
        
--------------------------------
-- @function [parent=#ActionTimeline] reverse 
-- @param self
-- @return ActionTimeline#ActionTimeline ret (return value: ccs.ActionTimeline)
        
--------------------------------
-- @function [parent=#ActionTimeline] isDone 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ActionTimeline] ActionTimeline 
-- @param self
        
return nil
