
--------------------------------
-- @module GLView
-- @extend Ref
-- @parent_module cc

--------------------------------
-- Set the frame size of EGL view.
-- @function [parent=#GLView] setFrameSize 
-- @param self
-- @param #float width
-- @param #float height
-- @return GLView#GLView self (return value: cc.GLView)
        
--------------------------------
-- Get the opengl view port rectangle.
-- @function [parent=#GLView] getViewPortRect 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
--  only works on ios platform
-- @function [parent=#GLView] setContentScaleFactor 
-- @param self
-- @param #float scaleFactor
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#GLView] getContentScaleFactor 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Open or close IME keyboard , subclass must implement this method. 
-- @function [parent=#GLView] setIMEKeyboardState 
-- @param self
-- @param #bool open
-- @return GLView#GLView self (return value: cc.GLView)
        
--------------------------------
-- Set Scissor rectangle with points.
-- @function [parent=#GLView] setScissorInPoints 
-- @param self
-- @param #float x
-- @param #float y
-- @param #float w
-- @param #float h
-- @return GLView#GLView self (return value: cc.GLView)
        
--------------------------------
-- 
-- @function [parent=#GLView] getViewName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
--  Get whether opengl render system is ready, subclass must implement this method. 
-- @function [parent=#GLView] isOpenGLReady 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Force destroying EGL view, subclass must implement this method. 
-- @function [parent=#GLView] end 
-- @param self
-- @return GLView#GLView self (return value: cc.GLView)
        
--------------------------------
-- Get scale factor of the vertical direction.
-- @function [parent=#GLView] getScaleY 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Get scale factor of the horizontal direction.
-- @function [parent=#GLView] getScaleX 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Get the visible origin point of opengl viewport.
-- @function [parent=#GLView] getVisibleOrigin 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Get the frame size of EGL view.<br>
-- In general, it returns the screen size since the EGL view is a fullscreen view.
-- @function [parent=#GLView] getFrameSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
--  Set and get zoom factor for frame. This two methods are for<br>
-- debugging big resolution (e.g.new ipad) app on desktop.
-- @function [parent=#GLView] setFrameZoomFactor 
-- @param self
-- @param #float zoomFactor
-- @return GLView#GLView self (return value: cc.GLView)
        
--------------------------------
-- 
-- @function [parent=#GLView] getFrameZoomFactor 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Get design resolution size.<br>
-- Default resolution size is the same as 'getFrameSize'.
-- @function [parent=#GLView] getDesignResolutionSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- 
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
--  returns the current Resolution policy 
-- @function [parent=#GLView] getResolutionPolicy 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  returns whether or not the view is in Retina Display mode 
-- @function [parent=#GLView] isRetinaDisplay 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Set opengl view port rectangle with points.
-- @function [parent=#GLView] setViewPortInPoints 
-- @param self
-- @param #float x
-- @param #float y
-- @param #float w
-- @param #float h
-- @return GLView#GLView self (return value: cc.GLView)
        
--------------------------------
-- Get the current scissor rectangle
-- @function [parent=#GLView] getScissorRect 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
--  Get retina factor 
-- @function [parent=#GLView] getRetinaFactor 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#GLView] setViewName 
-- @param self
-- @param #string viewname
-- @return GLView#GLView self (return value: cc.GLView)
        
--------------------------------
-- Get the visible rectangle of opengl viewport.
-- @function [parent=#GLView] getVisibleRect 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- Get the visible area size of opengl viewport.
-- @function [parent=#GLView] getVisibleSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- Get whether GL_SCISSOR_TEST is enable
-- @function [parent=#GLView] isScissorEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#GLView] pollEvents 
-- @param self
-- @return GLView#GLView self (return value: cc.GLView)
        
--------------------------------
-- 
-- @function [parent=#GLView] setGLContextAttrs 
-- @param self
-- @param #GLContextAttrs glContextAttrs
-- @return GLView#GLView self (return value: cc.GLView)
        
--------------------------------
-- 
-- @function [parent=#GLView] getGLContextAttrs 
-- @param self
-- @return GLContextAttrs#GLContextAttrs ret (return value: GLContextAttrs)
        
return nil
