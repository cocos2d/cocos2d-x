
--------------------------------
-- @module GLView
-- @extend Ref
-- @parent_module cc

--------------------------------
-- Set the frame size of EGL view.<br>
-- param width The width of the fram size.<br>
-- param height The height of the fram size.
-- @function [parent=#GLView] setFrameSize 
-- @param self
-- @param #float width
-- @param #float height
-- @return GLView#GLView self (return value: cc.GLView)
        
--------------------------------
-- Get the opengl view port rectangle.<br>
-- return Return the opengl view port rectangle.
-- @function [parent=#GLView] getViewPortRect 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
--  Only works on ios platform. Set Content Scale of the Factor. 
-- @function [parent=#GLView] setContentScaleFactor 
-- @param self
-- @param #float scaleFactor
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Only works on ios platform. Get Content Scale of the Factor. 
-- @function [parent=#GLView] getContentScaleFactor 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Open or close IME keyboard , subclass must implement this method. <br>
-- param open Open or close IME keyboard.
-- @function [parent=#GLView] setIMEKeyboardState 
-- @param self
-- @param #bool open
-- @return GLView#GLView self (return value: cc.GLView)
        
--------------------------------
-- Set Scissor rectangle with points.<br>
-- param x Set the points of x.<br>
-- param y Set the points of y.<br>
-- param w Set the width of  the view port<br>
-- param h Set the Height of the view port.
-- @function [parent=#GLView] setScissorInPoints 
-- @param self
-- @param #float x
-- @param #float y
-- @param #float w
-- @param #float h
-- @return GLView#GLView self (return value: cc.GLView)
        
--------------------------------
--  Get the view name.<br>
-- return The view name.
-- @function [parent=#GLView] getViewName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
--  Get whether opengl render system is ready, subclass must implement this method. 
-- @function [parent=#GLView] isOpenGLReady 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Hide or Show the mouse cursor if there is one.<br>
-- param isVisible Hide or Show the mouse cursor if there is one.
-- @function [parent=#GLView] setCursorVisible 
-- @param self
-- @param #bool isVisible
-- @return GLView#GLView self (return value: cc.GLView)
        
--------------------------------
--  Force destroying EGL view, subclass must implement this method. 
-- @function [parent=#GLView] end 
-- @param self
-- @return GLView#GLView self (return value: cc.GLView)
        
--------------------------------
-- Get scale factor of the vertical direction.<br>
-- return Scale factor of the vertical direction.
-- @function [parent=#GLView] getScaleY 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Get scale factor of the horizontal direction.<br>
-- return Scale factor of the horizontal direction.
-- @function [parent=#GLView] getScaleX 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Get the visible origin point of opengl viewport.<br>
-- return The visible origin point of opengl viewport.
-- @function [parent=#GLView] getVisibleOrigin 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Get the frame size of EGL view.<br>
-- In general, it returns the screen size since the EGL view is a fullscreen view.<br>
-- return The frame size of EGL view.
-- @function [parent=#GLView] getFrameSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
--  Set zoom factor for frame. This methods are for<br>
-- debugging big resolution (e.g.new ipad) app on desktop.<br>
-- param zoomFactor The zoom factor for frame.
-- @function [parent=#GLView] setFrameZoomFactor 
-- @param self
-- @param #float zoomFactor
-- @return GLView#GLView self (return value: cc.GLView)
        
--------------------------------
--  Get zoom factor for frame. This methods are for<br>
-- debugging big resolution (e.g.new ipad) app on desktop.<br>
-- return The zoom factor for frame.
-- @function [parent=#GLView] getFrameZoomFactor 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Get design resolution size.<br>
-- Default resolution size is the same as 'getFrameSize'.<br>
-- return The design resolution size.
-- @function [parent=#GLView] getDesignResolutionSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
--  When the window is closed, it will return false if the platforms is Ios or Android.<br>
-- If the platforms is windows or Mac,it will return true.<br>
-- return In ios and android it will return false,if in windows or Mac it will return true.
-- @function [parent=#GLView] windowShouldClose 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Exchanges the front and back buffers, subclass must implement this method. 
-- @function [parent=#GLView] swapBuffers 
-- @param self
-- @return GLView#GLView self (return value: cc.GLView)
        
--------------------------------
-- Set the design resolution size.<br>
-- param width Design resolution width.<br>
-- param height Design resolution height.<br>
-- param resolutionPolicy The resolution policy desired, you may choose:<br>
-- [1] EXACT_FIT Fill screen by stretch-to-fit: if the design resolution ratio of width to height is different from the screen resolution ratio, your game view will be stretched.<br>
-- [2] NO_BORDER Full screen without black border: if the design resolution ratio of width to height is different from the screen resolution ratio, two areas of your game view will be cut.<br>
-- [3] SHOW_ALL  Full screen with black border: if the design resolution ratio of width to height is different from the screen resolution ratio, two black borders will be shown.
-- @function [parent=#GLView] setDesignResolutionSize 
-- @param self
-- @param #float width
-- @param #float height
-- @param #int resolutionPolicy
-- @return GLView#GLView self (return value: cc.GLView)
        
--------------------------------
--  Returns the current Resolution policy.<br>
-- return The current Resolution policy.
-- @function [parent=#GLView] getResolutionPolicy 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Returns whether or not the view is in Retina Display mode.<br>
-- return Returns whether or not the view is in Retina Display mode.
-- @function [parent=#GLView] isRetinaDisplay 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Set opengl view port rectangle with points.<br>
-- param x Set the points of x.<br>
-- param y Set the points of y.<br>
-- param w Set the width of  the view port<br>
-- param h Set the Height of the view port.
-- @function [parent=#GLView] setViewPortInPoints 
-- @param self
-- @param #float x
-- @param #float y
-- @param #float w
-- @param #float h
-- @return GLView#GLView self (return value: cc.GLView)
        
--------------------------------
-- Get the current scissor rectangle.<br>
-- return The current scissor rectangle.
-- @function [parent=#GLView] getScissorRect 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
--  Get retina factor.<br>
-- return The retina factor.
-- @function [parent=#GLView] getRetinaFactor 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Set the view name. <br>
-- param viewname A string will be set to the view as name.
-- @function [parent=#GLView] setViewName 
-- @param self
-- @param #string viewname
-- @return GLView#GLView self (return value: cc.GLView)
        
--------------------------------
-- Get the visible rectangle of opengl viewport.<br>
-- return The visible rectangle of opengl viewport.
-- @function [parent=#GLView] getVisibleRect 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- Get the visible area size of opengl viewport.<br>
-- return The visible area size of opengl viewport.
-- @function [parent=#GLView] getVisibleSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- Get whether GL_SCISSOR_TEST is enable.<br>
-- return Whether GL_SCISSOR_TEST is enable.
-- @function [parent=#GLView] isScissorEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Polls the events. 
-- @function [parent=#GLView] pollEvents 
-- @param self
-- @return GLView#GLView self (return value: cc.GLView)
        
--------------------------------
--  Static method and member so that we can modify it on all platforms before create OpenGL context. <br>
-- param glContextAttrs The OpenGL context attrs.
-- @function [parent=#GLView] setGLContextAttrs 
-- @param self
-- @param #GLContextAttrs glContextAttrs
-- @return GLView#GLView self (return value: cc.GLView)
        
--------------------------------
--  Return the OpenGL context attrs. <br>
-- return Return the OpenGL context attrs.
-- @function [parent=#GLView] getGLContextAttrs 
-- @param self
-- @return GLContextAttrs#GLContextAttrs ret (return value: GLContextAttrs)
        
return nil
