
--------------------------------
-- @module AnimationCache
-- @extend Ref
-- @parent_module cc

--------------------------------
--  Returns a Animation that was previously added.<br>
-- If the name is not found it will return nil.<br>
-- You should retain the returned copy if you are going to use it.
-- @function [parent=#AnimationCache] getAnimation 
-- @param self
-- @param #string name
-- @return Animation#Animation ret (return value: cc.Animation)
        
--------------------------------
--  Adds a Animation with a name.
-- @function [parent=#AnimationCache] addAnimation 
-- @param self
-- @param #cc.Animation animation
-- @param #string name
        
--------------------------------
-- 
-- @function [parent=#AnimationCache] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Adds an animation from an NSDictionary<br>
-- Make sure that the frames were previously loaded in the SpriteFrameCache.<br>
-- param plist The path of the relative file,it use to find the plist path for load SpriteFrames.<br>
-- since v1.1
-- @function [parent=#AnimationCache] addAnimationsWithDictionary 
-- @param self
-- @param #map_table dictionary
-- @param #string plist
        
--------------------------------
--  Deletes a Animation from the cache.
-- @function [parent=#AnimationCache] removeAnimation 
-- @param self
-- @param #string name
        
--------------------------------
--  Adds an animation from a plist file.<br>
-- Make sure that the frames were previously loaded in the SpriteFrameCache.<br>
-- since v1.1<br>
-- js addAnimations<br>
-- lua addAnimations
-- @function [parent=#AnimationCache] addAnimationsWithFile 
-- @param self
-- @param #string plist
        
--------------------------------
--  Purges the cache. It releases all the Animation objects and the shared instance.
-- @function [parent=#AnimationCache] destroyInstance 
-- @param self
        
--------------------------------
--  Returns the shared instance of the Animation cache 
-- @function [parent=#AnimationCache] getInstance 
-- @param self
-- @return AnimationCache#AnimationCache ret (return value: cc.AnimationCache)
        
--------------------------------
-- js ctor
-- @function [parent=#AnimationCache] AnimationCache 
-- @param self
        
return nil
