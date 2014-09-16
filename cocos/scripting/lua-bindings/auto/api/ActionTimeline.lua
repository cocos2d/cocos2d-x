
--------------------------------
-- @module ActionTimeline
-- @extend Action
-- @parent_module ccs

--------------------------------
-- 
-- @function [parent=#ActionTimeline] getTimelines 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
--  Get current frame. 
-- @function [parent=#ActionTimeline] getCurrentFrame 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Start frame index of this action
-- @function [parent=#ActionTimeline] getStartFrame 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Pause the animation. 
-- @function [parent=#ActionTimeline] pause 
-- @param self
        
--------------------------------
--  Set ActionTimeline's frame event callback function 
-- @function [parent=#ActionTimeline] setFrameEventCallFunc 
-- @param self
-- @param #function listener
        
--------------------------------
--  Resume the animation. 
-- @function [parent=#ActionTimeline] resume 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#ActionTimeline] getDuration 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  add Timeline to ActionTimeline 
-- @function [parent=#ActionTimeline] addTimeline 
-- @param self
-- @param #ccs.Timeline timeline
        
--------------------------------
--  End frame of this action.<br>
-- When action play to this frame, if action is not loop, then it will stop, <br>
-- or it will play from start frame again. 
-- @function [parent=#ActionTimeline] getEndFrame 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Set current frame index, this will cause action plays to this frame. 
-- @function [parent=#ActionTimeline] setCurrentFrame 
-- @param self
-- @param #int frameIndex
        
--------------------------------
--  Set the animation speed, this will speed up or slow down the speed. 
-- @function [parent=#ActionTimeline] setTimeSpeed 
-- @param self
-- @param #float speed
        
--------------------------------
-- 
-- @function [parent=#ActionTimeline] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  duration of the whole action
-- @function [parent=#ActionTimeline] setDuration 
-- @param self
-- @param #int duration
        
--------------------------------
--  Get current animation speed. 
-- @function [parent=#ActionTimeline] getTimeSpeed 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Goto the specified frame index, and pause at this index.<br>
-- param startIndex The animation will pause at this index.
-- @function [parent=#ActionTimeline] gotoFrameAndPause 
-- @param self
-- @param #int startIndex
        
--------------------------------
--  Whether or not Action is playing. 
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
-- @param #int startIndex
-- @param #int endIndex
-- @param #int currentFrameIndex
-- @param #bool loop

--------------------------------
-- 
-- @function [parent=#ActionTimeline] removeTimeline 
-- @param self
-- @param #ccs.Timeline timeline
        
--------------------------------
-- 
-- @function [parent=#ActionTimeline] clearFrameEventCallFunc 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#ActionTimeline] create 
-- @param self
-- @return ActionTimeline#ActionTimeline ret (return value: ccs.ActionTimeline)
        
--------------------------------
-- 
-- @function [parent=#ActionTimeline] step 
-- @param self
-- @param #float delta
        
--------------------------------
-- 
-- @function [parent=#ActionTimeline] startWithTarget 
-- @param self
-- @param #cc.Node target
        
--------------------------------
--  Returns a clone of ActionTimeline 
-- @function [parent=#ActionTimeline] clone 
-- @param self
-- @return ActionTimeline#ActionTimeline ret (return value: ccs.ActionTimeline)
        
--------------------------------
--  Returns a reverse of ActionTimeline. <br>
-- Not implement yet.
-- @function [parent=#ActionTimeline] reverse 
-- @param self
-- @return ActionTimeline#ActionTimeline ret (return value: ccs.ActionTimeline)
        
--------------------------------
-- 
-- @function [parent=#ActionTimeline] isDone 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ActionTimeline] ActionTimeline 
-- @param self
        
return nil
