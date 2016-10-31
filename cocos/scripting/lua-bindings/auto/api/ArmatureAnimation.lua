
--------------------------------
-- @module ArmatureAnimation
-- @extend ProcessBase
-- @parent_module ccs

--------------------------------
-- 
-- @function [parent=#ArmatureAnimation] getSpeedScale 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Play animation by animation name.<br>
-- param  animationName  The animation name you want to play<br>
-- param  durationTo The frames between two animation changing-over.<br>
-- It's meaning is changing to this animation need how many frames<br>
-- -1 : use the value from MovementData get from flash design panel<br>
-- param  loop   Whether the animation is loop<br>
-- loop < 0 : use the value from MovementData get from flash design panel<br>
-- loop = 0 : this animation is not loop<br>
-- loop > 0 : this animation is loop
-- @function [parent=#ArmatureAnimation] play 
-- @param self
-- @param #string animationName
-- @param #int durationTo
-- @param #int loop
-- @return ArmatureAnimation#ArmatureAnimation self (return value: ccs.ArmatureAnimation)
        
--------------------------------
-- Go to specified frame and pause current movement.
-- @function [parent=#ArmatureAnimation] gotoAndPause 
-- @param self
-- @param #int frameIndex
-- @return ArmatureAnimation#ArmatureAnimation self (return value: ccs.ArmatureAnimation)
        
--------------------------------
-- 
-- @function [parent=#ArmatureAnimation] playWithIndexes 
-- @param self
-- @param #array_table movementIndexes
-- @param #int durationTo
-- @param #bool loop
-- @return ArmatureAnimation#ArmatureAnimation self (return value: ccs.ArmatureAnimation)
        
--------------------------------
-- 
-- @function [parent=#ArmatureAnimation] setAnimationData 
-- @param self
-- @param #ccs.AnimationData data
-- @return ArmatureAnimation#ArmatureAnimation self (return value: ccs.ArmatureAnimation)
        
--------------------------------
-- Scale animation play speed.<br>
-- param animationScale Scale value
-- @function [parent=#ArmatureAnimation] setSpeedScale 
-- @param self
-- @param #float speedScale
-- @return ArmatureAnimation#ArmatureAnimation self (return value: ccs.ArmatureAnimation)
        
--------------------------------
-- 
-- @function [parent=#ArmatureAnimation] getAnimationData 
-- @param self
-- @return AnimationData#AnimationData ret (return value: ccs.AnimationData)
        
--------------------------------
-- Go to specified frame and play current movement.<br>
-- You need first switch to the movement you want to play, then call this function.<br>
-- example : playByIndex(0);<br>
-- gotoAndPlay(0);<br>
-- playByIndex(1);<br>
-- gotoAndPlay(0);<br>
-- gotoAndPlay(15);
-- @function [parent=#ArmatureAnimation] gotoAndPlay 
-- @param self
-- @param #int frameIndex
-- @return ArmatureAnimation#ArmatureAnimation self (return value: ccs.ArmatureAnimation)
        
--------------------------------
-- Init with a Armature<br>
-- param armature The Armature ArmatureAnimation will bind to
-- @function [parent=#ArmatureAnimation] init 
-- @param self
-- @param #ccs.Armature armature
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ArmatureAnimation] playWithNames 
-- @param self
-- @param #array_table movementNames
-- @param #int durationTo
-- @param #bool loop
-- @return ArmatureAnimation#ArmatureAnimation self (return value: ccs.ArmatureAnimation)
        
--------------------------------
-- Get movement count
-- @function [parent=#ArmatureAnimation] getMovementCount 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#ArmatureAnimation] playWithIndex 
-- @param self
-- @param #int animationIndex
-- @param #int durationTo
-- @param #int loop
-- @return ArmatureAnimation#ArmatureAnimation self (return value: ccs.ArmatureAnimation)
        
--------------------------------
-- Get current movementID<br>
-- return The name of current movement
-- @function [parent=#ArmatureAnimation] getCurrentMovementID 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Create with a Armature<br>
-- param armature The Armature ArmatureAnimation will bind to
-- @function [parent=#ArmatureAnimation] create 
-- @param self
-- @param #ccs.Armature armature
-- @return ArmatureAnimation#ArmatureAnimation ret (return value: ccs.ArmatureAnimation)
        
--------------------------------
-- Pause the Process
-- @function [parent=#ArmatureAnimation] pause 
-- @param self
-- @return ArmatureAnimation#ArmatureAnimation self (return value: ccs.ArmatureAnimation)
        
--------------------------------
-- Stop the Process
-- @function [parent=#ArmatureAnimation] stop 
-- @param self
-- @return ArmatureAnimation#ArmatureAnimation self (return value: ccs.ArmatureAnimation)
        
--------------------------------
-- 
-- @function [parent=#ArmatureAnimation] update 
-- @param self
-- @param #float dt
-- @return ArmatureAnimation#ArmatureAnimation self (return value: ccs.ArmatureAnimation)
        
--------------------------------
-- Resume the Process
-- @function [parent=#ArmatureAnimation] resume 
-- @param self
-- @return ArmatureAnimation#ArmatureAnimation self (return value: ccs.ArmatureAnimation)
        
--------------------------------
-- js ctor
-- @function [parent=#ArmatureAnimation] ArmatureAnimation 
-- @param self
-- @return ArmatureAnimation#ArmatureAnimation self (return value: ccs.ArmatureAnimation)
        
return nil
