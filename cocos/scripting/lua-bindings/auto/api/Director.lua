
--------------------------------
-- @module Director
-- @parent_module cc

--------------------------------
--  Pauses the running scene.<br>
-- The running scene will be _drawed_ but all scheduled timers will be paused<br>
-- While paused, the draw rate will be 4 FPS to reduce CPU consumption
-- @function [parent=#Director] pause 
-- @param self
        
--------------------------------
--  Sets the EventDispatcher associated with this director <br>
-- since v3.0
-- @function [parent=#Director] setEventDispatcher 
-- @param self
-- @param #cc.EventDispatcher dispatcher
        
--------------------------------
--  Suspends the execution of the running scene, pushing it on the stack of suspended scenes.<br>
-- The new scene will be executed.<br>
-- Try to avoid big stacks of pushed scenes to reduce memory allocation. <br>
-- ONLY call it if there is a running scene.
-- @function [parent=#Director] pushScene 
-- @param self
-- @param #cc.Scene scene
        
--------------------------------
-- 
-- @function [parent=#Director] getDeltaTime 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Director] getContentScaleFactor 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  returns the size of the OpenGL view in pixels.
-- @function [parent=#Director] getWinSizeInPixels 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
--  Returns the Console <br>
-- since v3.0
-- @function [parent=#Director] getConsole 
-- @param self
-- @return Console#Console ret (return value: cc.Console)
        
--------------------------------
-- 
-- @function [parent=#Director] pushMatrix 
-- @param self
-- @param #int type
        
--------------------------------
--  sets the OpenGL default values 
-- @function [parent=#Director] setGLDefaultValues 
-- @param self
        
--------------------------------
--  Sets the ActionManager associated with this director<br>
-- since v2.0
-- @function [parent=#Director] setActionManager 
-- @param self
-- @param #cc.ActionManager actionManager
        
--------------------------------
--  enables/disables OpenGL alpha blending 
-- @function [parent=#Director] setAlphaBlending 
-- @param self
-- @param #bool on
        
--------------------------------
--  Pops out all scenes from the stack until the root scene in the queue.<br>
-- This scene will replace the running one.<br>
-- Internally it will call `popToSceneStackLevel(1)`
-- @function [parent=#Director] popToRootScene 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#Director] loadMatrix 
-- @param self
-- @param #int type
-- @param #mat4_table mat
        
--------------------------------
--  This object will be visited after the main scene is visited.<br>
-- This object MUST implement the "visit" selector.<br>
-- Useful to hook a notification object, like Notifications (http:github.com/manucorporat/CCNotifications)<br>
-- since v0.99.5
-- @function [parent=#Director] getNotificationNode 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
--  returns the size of the OpenGL view in points.
-- @function [parent=#Director] getWinSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- 
-- @function [parent=#Director] getTextureCache 
-- @param self
-- @return TextureCache#TextureCache ret (return value: cc.TextureCache)
        
--------------------------------
--  Whether or not the replaced scene will receive the cleanup message.<br>
-- If the new scene is pushed, then the old scene won't receive the "cleanup" message.<br>
-- If the new scene replaces the old one, the it will receive the "cleanup" message.<br>
-- since v0.99.0
-- @function [parent=#Director] isSendCleanupToScene 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  returns visible origin of the OpenGL view in points.
-- @function [parent=#Director] getVisibleOrigin 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
-- @function [parent=#Director] mainLoop 
-- @param self
        
--------------------------------
--  enables/disables OpenGL depth test 
-- @function [parent=#Director] setDepthTest 
-- @param self
-- @param #bool on
        
--------------------------------
-- get Frame Rate
-- @function [parent=#Director] getFrameRate 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  seconds per frame 
-- @function [parent=#Director] getSecondsPerFrame 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  converts an OpenGL coordinate to a UIKit coordinate<br>
-- Useful to convert node points to window points for calls such as glScissor
-- @function [parent=#Director] convertToUI 
-- @param self
-- @param #vec2_table point
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  sets the default values based on the Configuration info 
-- @function [parent=#Director] setDefaultValues 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#Director] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Sets the Scheduler associated with this director<br>
-- since v2.0
-- @function [parent=#Director] setScheduler 
-- @param self
-- @param #cc.Scheduler scheduler
        
--------------------------------
--  The main loop is triggered again.<br>
-- Call this function only if [stopAnimation] was called earlier<br>
-- warning Don't call this function to start the main loop. To run the main loop call runWithScene
-- @function [parent=#Director] startAnimation 
-- @param self
        
--------------------------------
--  Get the GLView, where everything is rendered<br>
-- js NA<br>
-- lua NA
-- @function [parent=#Director] getOpenGLView 
-- @param self
-- @return GLView#GLView ret (return value: cc.GLView)
        
--------------------------------
--  Get current running Scene. Director can only run one Scene at a time 
-- @function [parent=#Director] getRunningScene 
-- @param self
-- @return Scene#Scene ret (return value: cc.Scene)
        
--------------------------------
--  Sets the glViewport
-- @function [parent=#Director] setViewport 
-- @param self
        
--------------------------------
--  Stops the animation. Nothing will be drawn. The main loop won't be triggered anymore.<br>
-- If you don't want to pause your animation call [pause] instead.
-- @function [parent=#Director] stopAnimation 
-- @param self
        
--------------------------------
--  The size in pixels of the surface. It could be different than the screen size.<br>
-- High-res devices might have a higher surface size than the screen size.<br>
-- Only available when compiled using SDK >= 4.0.<br>
-- since v0.99.4
-- @function [parent=#Director] setContentScaleFactor 
-- @param self
-- @param #float scaleFactor
        
--------------------------------
--  Pops out all scenes from the stack until it reaches `level`.<br>
-- If level is 0, it will end the director.<br>
-- If level is 1, it will pop all scenes until it reaches to root scene.<br>
-- If level is <= than the current stack level, it won't do anything.
-- @function [parent=#Director] popToSceneStackLevel 
-- @param self
-- @param #int level
        
--------------------------------
--  Resumes the paused scene<br>
-- The scheduled timers will be activated again.<br>
-- The "delta time" will be 0 (as if the game wasn't paused)
-- @function [parent=#Director] resume 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#Director] isNextDeltaTimeZero 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Ends the execution, releases the running scene.<br>
-- It doesn't remove the OpenGL view from its parent. You have to do it manually.<br>
-- lua endToLua
-- @function [parent=#Director] end 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#Director] setOpenGLView 
-- @param self
-- @param #cc.GLView openGLView
        
--------------------------------
--  converts a UIKit coordinate to an OpenGL coordinate<br>
-- Useful to convert (multi) touch coordinates to the current layout (portrait or landscape)
-- @function [parent=#Director] convertToGL 
-- @param self
-- @param #vec2_table point
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Removes all cocos2d cached data.<br>
-- It will purge the TextureCache, SpriteFrameCache, LabelBMFont cache<br>
-- since v0.99.3
-- @function [parent=#Director] purgeCachedData 
-- @param self
        
--------------------------------
--  How many frames were called since the director started 
-- @function [parent=#Director] getTotalFrames 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
--  Enters the Director's main loop with the given Scene.<br>
-- Call it to run only your FIRST scene.<br>
-- Don't call it if there is already a running scene.<br>
-- It will call pushScene: and then it will call startAnimation
-- @function [parent=#Director] runWithScene 
-- @param self
-- @param #cc.Scene scene
        
--------------------------------
-- 
-- @function [parent=#Director] setNotificationNode 
-- @param self
-- @param #cc.Node node
        
--------------------------------
--  Draw the scene.<br>
-- This method is called every frame. Don't call it manually.
-- @function [parent=#Director] drawScene 
-- @param self
        
--------------------------------
-- / FIXME: missing description 
-- @function [parent=#Director] getZEye 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Director] getMatrix 
-- @param self
-- @param #int type
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
--  Pops out a scene from the stack.<br>
-- This scene will replace the running one.<br>
-- The running scene will be deleted. If there are no more scenes in the stack the execution is terminated.<br>
-- ONLY call it if there is a running scene.
-- @function [parent=#Director] popScene 
-- @param self
        
--------------------------------
--  Whether or not to display the FPS on the bottom-left corner 
-- @function [parent=#Director] isDisplayStats 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Director] setProjection 
-- @param self
-- @param #int projection
        
--------------------------------
-- 
-- @function [parent=#Director] loadIdentityMatrix 
-- @param self
-- @param #int type
        
--------------------------------
-- 
-- @function [parent=#Director] setNextDeltaTimeZero 
-- @param self
-- @param #bool nextDeltaTimeZero
        
--------------------------------
-- 
-- @function [parent=#Director] resetMatrixStack 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#Director] popMatrix 
-- @param self
-- @param #int type
        
--------------------------------
--  returns visible size of the OpenGL view in points.<br>
-- the value is equal to getWinSize if don't invoke<br>
-- GLView::setDesignResolutionSize()
-- @function [parent=#Director] getVisibleSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
--  Gets the Scheduler associated with this director<br>
-- since v2.0
-- @function [parent=#Director] getScheduler 
-- @param self
-- @return Scheduler#Scheduler ret (return value: cc.Scheduler)
        
--------------------------------
--  Set the FPS value. 
-- @function [parent=#Director] setAnimationInterval 
-- @param self
-- @param #double interval
        
--------------------------------
--  Get the FPS value 
-- @function [parent=#Director] getAnimationInterval 
-- @param self
-- @return double#double ret (return value: double)
        
--------------------------------
--  Whether or not the Director is paused 
-- @function [parent=#Director] isPaused 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Display the FPS on the bottom-left corner 
-- @function [parent=#Director] setDisplayStats 
-- @param self
-- @param #bool displayStats
        
--------------------------------
--  Gets the EventDispatcher associated with this director <br>
-- since v3.0
-- @function [parent=#Director] getEventDispatcher 
-- @param self
-- @return EventDispatcher#EventDispatcher ret (return value: cc.EventDispatcher)
        
--------------------------------
--  Replaces the running scene with a new one. The running scene is terminated.<br>
-- ONLY call it if there is a running scene.
-- @function [parent=#Director] replaceScene 
-- @param self
-- @param #cc.Scene scene
        
--------------------------------
-- 
-- @function [parent=#Director] multiplyMatrix 
-- @param self
-- @param #int type
-- @param #mat4_table mat
        
--------------------------------
--  Gets the ActionManager associated with this director<br>
-- since v2.0
-- @function [parent=#Director] getActionManager 
-- @param self
-- @return ActionManager#ActionManager ret (return value: cc.ActionManager)
        
--------------------------------
--  returns a shared instance of the director 
-- @function [parent=#Director] getInstance 
-- @param self
-- @return Director#Director ret (return value: cc.Director)
        
return nil
