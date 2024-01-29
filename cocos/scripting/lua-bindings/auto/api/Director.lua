
--------------------------------
-- @module Director
-- @parent_module cc

--------------------------------
--  Pauses the running scene.<br>
-- The running scene will be _drawed_ but all scheduled timers will be paused.<br>
-- While paused, the draw rate will be 4 FPS to reduce CPU consumption.
-- @function [parent=#Director] pause 
-- @param self
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
-- Clones a projection matrix and put it to the top of projection matrix stack.<br>
-- param index The index of projection matrix stack.<br>
-- js NA
-- @function [parent=#Director] pushProjectionMatrix 
-- @param self
-- @param #unsigned int index
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
--  Pops the top matrix of the projection matrix stack.<br>
-- param index The index of projection matrix stack.<br>
-- js NA
-- @function [parent=#Director] popProjectionMatrix 
-- @param self
-- @param #unsigned int index
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
--  Sets the EventDispatcher associated with this director.<br>
-- since v3.0<br>
-- js NA
-- @function [parent=#Director] setEventDispatcher 
-- @param self
-- @param #cc.EventDispatcher dispatcher
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
--  Adds an identity matrix to the top of projection matrix stack.<br>
-- param index The index of projection matrix stack.<br>
-- js NA
-- @function [parent=#Director] loadProjectionIdentityMatrix 
-- @param self
-- @param #unsigned int index
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
--  The size in pixels of the surface. It could be different than the screen size.<br>
-- High-res devices might have a higher surface size than the screen size.<br>
-- Only available when compiled using SDK >= 4.0.<br>
-- since v0.99.4
-- @function [parent=#Director] setContentScaleFactor 
-- @param self
-- @param #float scaleFactor
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
-- 
-- @function [parent=#Director] getDeltaTime 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Gets content scale factor.<br>
-- see Director::setContentScaleFactor()
-- @function [parent=#Director] getContentScaleFactor 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Returns the size of the OpenGL view in pixels. 
-- @function [parent=#Director] getWinSizeInPixels 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- Returns safe area rectangle of the OpenGL view in points.
-- @function [parent=#Director] getSafeAreaRect 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
--  Sets the OpenGL default values.<br>
-- It will enable alpha blending, disable depth test.<br>
-- js NA
-- @function [parent=#Director] setGLDefaultValues 
-- @param self
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
--  Sets the ActionManager associated with this director.<br>
-- since v2.0
-- @function [parent=#Director] setActionManager 
-- @param self
-- @param #cc.ActionManager actionManager
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
--  Enables/disables OpenGL alpha blending. 
-- @function [parent=#Director] setAlphaBlending 
-- @param self
-- @param #bool on
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
-- Pops out all scenes from the stack until the root scene in the queue.<br>
-- This scene will replace the running one.<br>
-- Internally it will call `popToSceneStackLevel(1)`.
-- @function [parent=#Director] popToRootScene 
-- @param self
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
-- Adds a matrix to the top of specified type of matrix stack.<br>
-- param type Matrix type.<br>
-- param mat The matrix that to be added.<br>
-- js NA
-- @function [parent=#Director] loadMatrix 
-- @param self
-- @param #int type
-- @param #mat4_table mat
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
--  This object will be visited after the main scene is visited.<br>
-- This object MUST implement the "visit" function.<br>
-- Useful to hook a notification object, like Notifications (http:github.com/manucorporat/CCNotifications)<br>
-- since v0.99.5
-- @function [parent=#Director] getNotificationNode 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
--  Returns the size of the OpenGL view in points. 
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
--  Returns visible origin coordinate of the OpenGL view in points. 
-- @function [parent=#Director] getVisibleOrigin 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @overload self, float         
-- @overload self         
-- @function [parent=#Director] mainLoop
-- @param self
-- @param #float dt
-- @return Director#Director self (return value: cc.Director)

--------------------------------
--  Enables/disables OpenGL depth test. 
-- @function [parent=#Director] setDepthTest 
-- @param self
-- @param #bool on
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
-- Gets Frame Rate.<br>
-- js NA
-- @function [parent=#Director] getFrameRate 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Get seconds per frame. 
-- @function [parent=#Director] getSecondsPerFrame 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Clear all types of matrix stack, and add identity matrix to these matrix stacks.<br>
-- js NA
-- @function [parent=#Director] resetMatrixStack 
-- @param self
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
-- Converts an OpenGL coordinate to a screen coordinate.<br>
-- Useful to convert node points to window points for calls such as glScissor.
-- @function [parent=#Director] convertToUI 
-- @param self
-- @param #vec2_table point
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Clones a specified type matrix and put it to the top of specified type of matrix stack.<br>
-- js NA
-- @function [parent=#Director] pushMatrix 
-- @param self
-- @param #int type
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
--  Sets the default values based on the Configuration info. 
-- @function [parent=#Director] setDefaultValues 
-- @param self
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
-- 
-- @function [parent=#Director] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Sets the Scheduler associated with this director.<br>
-- since v2.0
-- @function [parent=#Director] setScheduler 
-- @param self
-- @param #cc.Scheduler scheduler
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
-- Multiplies a matrix to the top of projection matrix stack.<br>
-- param mat The matrix that to be multiplied.<br>
-- param index The index of projection matrix stack.<br>
-- js NA
-- @function [parent=#Director] multiplyProjectionMatrix 
-- @param self
-- @param #mat4_table mat
-- @param #unsigned int index
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
-- Gets the top matrix of specified type of matrix stack.<br>
-- js NA
-- @function [parent=#Director] getMatrix 
-- @param self
-- @param #int type
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- returns whether or not the Director is in a valid state
-- @function [parent=#Director] isValid 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  The main loop is triggered again.<br>
-- Call this function only if [stopAnimation] was called earlier.<br>
-- warning Don't call this function to start the main loop. To run the main loop call runWithScene.
-- @function [parent=#Director] startAnimation 
-- @param self
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
-- Get the GLView.<br>
-- lua NA
-- @function [parent=#Director] getOpenGLView 
-- @param self
-- @return GLView#GLView ret (return value: cc.GLView)
        
--------------------------------
--  Gets current running Scene. Director can only run one Scene at a time. 
-- @function [parent=#Director] getRunningScene 
-- @param self
-- @return Scene#Scene ret (return value: cc.Scene)
        
--------------------------------
--  Sets the glViewport.
-- @function [parent=#Director] setViewport 
-- @param self
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
--  Stops the animation. Nothing will be drawn. The main loop won't be triggered anymore.<br>
-- If you don't want to pause your animation call [pause] instead.
-- @function [parent=#Director] stopAnimation 
-- @param self
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
--  Pops out all scenes from the stack until it reaches `level`.<br>
-- If level is 0, it will end the director.<br>
-- If level is 1, it will pop all scenes until it reaches to root scene.<br>
-- If level is <= than the current stack level, it won't do anything.
-- @function [parent=#Director] popToSceneStackLevel 
-- @param self
-- @param #int level
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
--  Resumes the paused scene.<br>
-- The scheduled timers will be activated again.<br>
-- The "delta time" will be 0 (as if the game wasn't paused).
-- @function [parent=#Director] resume 
-- @param self
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
--  Whether or not `_nextDeltaTimeZero` is set to 0. 
-- @function [parent=#Director] isNextDeltaTimeZero 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Sets clear values for the color buffers,<br>
-- value range of each element is [0.0, 1.0].<br>
-- js NA
-- @function [parent=#Director] setClearColor 
-- @param self
-- @param #color4f_table clearColor
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
--  Ends the execution, releases the running scene.<br>
-- lua endToLua
-- @function [parent=#Director] end 
-- @param self
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
-- Sets the GLView. <br>
-- lua NA
-- @function [parent=#Director] setOpenGLView 
-- @param self
-- @param #cc.GLView openGLView
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
-- Converts a screen coordinate to an OpenGL coordinate.<br>
-- Useful to convert (multi) touch coordinates to the current layout (portrait or landscape).
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
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
--  How many frames were called since the director started 
-- @function [parent=#Director] getTotalFrames 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- Enters the Director's main loop with the given Scene.<br>
-- Call it to run only your FIRST scene.<br>
-- Don't call it if there is already a running scene.<br>
-- It will call pushScene: and then it will call startAnimation<br>
-- js NA
-- @function [parent=#Director] runWithScene 
-- @param self
-- @param #cc.Scene scene
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
-- Sets the notification node.<br>
-- see Director::getNotificationNode()
-- @function [parent=#Director] setNotificationNode 
-- @param self
-- @param #cc.Node node
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
--  Draw the scene.<br>
-- This method is called every frame. Don't call it manually.
-- @function [parent=#Director] drawScene 
-- @param self
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
-- 
-- @function [parent=#Director] restart 
-- @param self
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
-- Pops out a scene from the stack.<br>
-- This scene will replace the running one.<br>
-- The running scene will be deleted. If there are no more scenes in the stack the execution is terminated.<br>
-- ONLY call it if there is a running scene.
-- @function [parent=#Director] popScene 
-- @param self
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
--  Adds an identity matrix to the top of specified type of matrix stack.<br>
-- js NA
-- @function [parent=#Director] loadIdentityMatrix 
-- @param self
-- @param #int type
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
--  Whether or not displaying the FPS on the bottom-left corner of the screen. 
-- @function [parent=#Director] isDisplayStats 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Sets OpenGL projection. 
-- @function [parent=#Director] setProjection 
-- @param self
-- @param #int projection
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
--  Returns the Console associated with this director.<br>
-- since v3.0<br>
-- js NA
-- @function [parent=#Director] getConsole 
-- @param self
-- @return Console#Console ret (return value: cc.Console)
        
--------------------------------
-- Multiplies a matrix to the top of specified type of matrix stack.<br>
-- param type Matrix type.<br>
-- param mat The matrix that to be multiplied.<br>
-- js NA
-- @function [parent=#Director] multiplyMatrix 
-- @param self
-- @param #int type
-- @param #mat4_table mat
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
-- Gets the distance between camera and near clipping frame.<br>
-- It is correct for default camera that near clipping frame is same as the screen.
-- @function [parent=#Director] getZEye 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Sets the delta time between current frame and next frame is 0.<br>
-- This value will be used in Schedule, and will affect all functions that are using frame delta time, such as Actions.<br>
-- This value will take effect only one time.
-- @function [parent=#Director] setNextDeltaTimeZero 
-- @param self
-- @param #bool nextDeltaTimeZero
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
--  Pops the top matrix of the specified type of matrix stack.<br>
-- js NA
-- @function [parent=#Director] popMatrix 
-- @param self
-- @param #int type
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
-- Returns visible size of the OpenGL view in points.<br>
-- The value is equal to `Director::getWinSize()` if don't invoke `GLView::setDesignResolutionSize()`.
-- @function [parent=#Director] getVisibleSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- Adds a matrix to the top of projection matrix stack.<br>
-- param mat The matrix that to be added.<br>
-- param index The index of projection matrix stack.<br>
-- js NA
-- @function [parent=#Director] loadProjectionMatrix 
-- @param self
-- @param #mat4_table mat
-- @param #unsigned int index
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
-- Init the projection matrix stack.<br>
-- param stackCount The size of projection matrix stack.<br>
-- js NA
-- @function [parent=#Director] initProjectionMatrixStack 
-- @param self
-- @param #unsigned int stackCount
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
--  Gets the Scheduler associated with this director.<br>
-- since v2.0
-- @function [parent=#Director] getScheduler 
-- @param self
-- @return Scheduler#Scheduler ret (return value: cc.Scheduler)
        
--------------------------------
-- Suspends the execution of the running scene, pushing it on the stack of suspended scenes.<br>
-- The new scene will be executed.<br>
-- Try to avoid big stacks of pushed scenes to reduce memory allocation. <br>
-- ONLY call it if there is a running scene.
-- @function [parent=#Director] pushScene 
-- @param self
-- @param #cc.Scene scene
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
--  Gets the FPS value. 
-- @function [parent=#Director] getAnimationInterval 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Gets clear values for the color buffers.<br>
-- js NA
-- @function [parent=#Director] getClearColor 
-- @param self
-- @return color4f_table#color4f_table ret (return value: color4f_table)
        
--------------------------------
--  Whether or not the Director is paused. 
-- @function [parent=#Director] isPaused 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Display the FPS on the bottom-left corner of the screen. 
-- @function [parent=#Director] setDisplayStats 
-- @param self
-- @param #bool displayStats
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
--  Gets the EventDispatcher associated with this director.<br>
-- since v3.0<br>
-- js NA
-- @function [parent=#Director] getEventDispatcher 
-- @param self
-- @return EventDispatcher#EventDispatcher ret (return value: cc.EventDispatcher)
        
--------------------------------
--  Replaces the running scene with a new one. The running scene is terminated.<br>
-- ONLY call it if there is a running scene.<br>
-- js NA
-- @function [parent=#Director] replaceScene 
-- @param self
-- @param #cc.Scene scene
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
--  Sets the FPS value. FPS = 1/interval. 
-- @function [parent=#Director] setAnimationInterval 
-- @param self
-- @param #float interval
-- @return Director#Director self (return value: cc.Director)
        
--------------------------------
--  Gets the ActionManager associated with this director.<br>
-- since v2.0
-- @function [parent=#Director] getActionManager 
-- @param self
-- @return ActionManager#ActionManager ret (return value: cc.ActionManager)
        
--------------------------------
-- Returns a shared instance of the director. <br>
-- js _getInstance
-- @function [parent=#Director] getInstance 
-- @param self
-- @return Director#Director ret (return value: cc.Director)
        
return nil
