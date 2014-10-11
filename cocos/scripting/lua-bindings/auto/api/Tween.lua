
--------------------------------
-- @module Tween
-- @extend ProcessBase
-- @parent_module ccs

--------------------------------
-- 
-- @function [parent=#Tween] getAnimation 
-- @param self
-- @return ArmatureAnimation#ArmatureAnimation ret (return value: ccs.ArmatureAnimation)
        
--------------------------------
-- 
-- @function [parent=#Tween] gotoAndPause 
-- @param self
-- @param #int frameIndex
        
--------------------------------
-- Start the Process<br>
-- param  movementBoneData  the MovementBoneData include all FrameData<br>
-- param  durationTo the number of frames changing to this animation needs.<br>
-- param  durationTween  the number of frames this animation actual last.<br>
-- param  loop   whether the animation is loop<br>
-- loop < 0 : use the value from MovementData get from Action Editor<br>
-- loop = 0 : this animation is not loop<br>
-- loop > 0 : this animation is loop<br>
-- param  tweenEasing    tween easing is used for calculate easing effect<br>
-- TWEEN_EASING_MAX : use the value from MovementData get from Action Editor<br>
-- -1 : fade out<br>
-- 0  : line<br>
-- 1  : fade in<br>
-- 2  : fade in and out
-- @function [parent=#Tween] play 
-- @param self
-- @param #ccs.MovementBoneData movementBoneData
-- @param #int durationTo
-- @param #int durationTween
-- @param #int loop
-- @param #int tweenEasing
        
--------------------------------
-- 
-- @function [parent=#Tween] gotoAndPlay 
-- @param self
-- @param #int frameIndex
        
--------------------------------
-- Init with a Bone<br>
-- param bone the Bone Tween will bind to
-- @function [parent=#Tween] init 
-- @param self
-- @param #ccs.Bone bone
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Tween] setAnimation 
-- @param self
-- @param #ccs.ArmatureAnimation animation
        
--------------------------------
-- Create with a Bone<br>
-- param bone the Bone Tween will bind to
-- @function [parent=#Tween] create 
-- @param self
-- @param #ccs.Bone bone
-- @return Tween#Tween ret (return value: ccs.Tween)
        
--------------------------------
-- 
-- @function [parent=#Tween] Tween 
-- @param self
        
return nil
