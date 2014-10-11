
--------------------------------
-- @module Animation
-- @extend Ref
-- @parent_module cc

--------------------------------
--  Gets the times the animation is going to loop. 0 means animation is not animated. 1, animation is executed one time, ... 
-- @function [parent=#Animation] getLoops 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
--  Adds a SpriteFrame to a Animation.<br>
-- The frame will be added with one "delay unit".
-- @function [parent=#Animation] addSpriteFrame 
-- @param self
-- @param #cc.SpriteFrame frame
        
--------------------------------
--  Sets whether to restore the original frame when animation finishes 
-- @function [parent=#Animation] setRestoreOriginalFrame 
-- @param self
-- @param #bool restoreOriginalFrame
        
--------------------------------
-- 
-- @function [parent=#Animation] clone 
-- @param self
-- @return Animation#Animation ret (return value: cc.Animation)
        
--------------------------------
--  Gets the duration in seconds of the whole animation. It is the result of totalDelayUnits * delayPerUnit 
-- @function [parent=#Animation] getDuration 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Sets the array of AnimationFrames 
-- @function [parent=#Animation] setFrames 
-- @param self
-- @param #array_table frames
        
--------------------------------
--  Gets the array of AnimationFrames 
-- @function [parent=#Animation] getFrames 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
--  Sets the times the animation is going to loop. 0 means animation is not animated. 1, animation is executed one time, ... 
-- @function [parent=#Animation] setLoops 
-- @param self
-- @param #unsigned int loops
        
--------------------------------
--  Sets the delay in seconds of the "delay unit" 
-- @function [parent=#Animation] setDelayPerUnit 
-- @param self
-- @param #float delayPerUnit
        
--------------------------------
--  Adds a frame with an image filename. Internally it will create a SpriteFrame and it will add it.<br>
-- The frame will be added with one "delay unit".<br>
-- Added to facilitate the migration from v0.8 to v0.9.
-- @function [parent=#Animation] addSpriteFrameWithFile 
-- @param self
-- @param #string filename
        
--------------------------------
--  Gets the total Delay units of the Animation. 
-- @function [parent=#Animation] getTotalDelayUnits 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Gets the delay in seconds of the "delay unit" 
-- @function [parent=#Animation] getDelayPerUnit 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Checks whether to restore the original frame when animation finishes. 
-- @function [parent=#Animation] getRestoreOriginalFrame 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Adds a frame with a texture and a rect. Internally it will create a SpriteFrame and it will add it.<br>
-- The frame will be added with one "delay unit".<br>
-- Added to facilitate the migration from v0.8 to v0.9.
-- @function [parent=#Animation] addSpriteFrameWithTexture 
-- @param self
-- @param #cc.Texture2D pobTexture
-- @param #rect_table rect
        
--------------------------------
-- @overload self, array_table, float, unsigned int         
-- @overload self         
-- @function [parent=#Animation] create
-- @param self
-- @param #array_table arrayOfAnimationFrameNames
-- @param #float delayPerUnit
-- @param #unsigned int loops
-- @return Animation#Animation ret (retunr value: cc.Animation)

--------------------------------
-- 
-- @function [parent=#Animation] createWithSpriteFrames 
-- @param self
-- @param #array_table arrayOfSpriteFrameNames
-- @param #float delay
-- @param #unsigned int loops
-- @return Animation#Animation ret (return value: cc.Animation)
        
return nil
