
--------------------------------
-- @module GLView
-- @extend Ref
-- @parent_module cc

--------------------------------
-- @function [parent=#GLView] setFrameSize 
-- @param self
-- @param #float float
-- @param #float float
        
--------------------------------
-- @function [parent=#GLView] getViewPortRect 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- @function [parent=#GLView] setContentScaleFactor 
-- @param self
-- @param #float float
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#GLView] getContentScaleFactor 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#GLView] setIMEKeyboardState 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#GLView] setScissorInPoints 
-- @param self
-- @param #float float
-- @param #float float
-- @param #float float
-- @param #float float
        
--------------------------------
-- @function [parent=#GLView] getViewName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#GLView] isOpenGLReady 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#GLView] end 
-- @param self
        
--------------------------------
-- @function [parent=#GLView] getScaleY 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#GLView] getScaleX 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#GLView] getVisibleOrigin 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#GLView] getFrameSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#GLView] setFrameZoomFactor 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#GLView] getFrameZoomFactor 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#GLView] getDesignResolutionSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#GLView] windowShouldClose 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#GLView] swapBuffers 
-- @param self
        
--------------------------------
-- @function [parent=#GLView] setDesignResolutionSize 
-- @param self
-- @param #float float
-- @param #float float
-- @param #int resolutionpolicy
        
--------------------------------
-- @function [parent=#GLView] getResolutionPolicy 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#GLView] isRetinaDisplay 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#GLView] setViewPortInPoints 
-- @param self
-- @param #float float
-- @param #float float
-- @param #float float
-- @param #float float
        
--------------------------------
-- @function [parent=#GLView] getScissorRect 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- @function [parent=#GLView] getRetinaFactor 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#GLView] setViewName 
-- @param self
-- @param #string str
        
--------------------------------
-- @function [parent=#GLView] getVisibleRect 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- @function [parent=#GLView] getVisibleSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#GLView] isScissorEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#GLView] pollEvents 
-- @param self
        
--------------------------------
-- @function [parent=#GLView] setGLContextAttrs 
-- @param self
-- @param #GLContextAttrs glcontextattrs
        
--------------------------------
-- @function [parent=#GLView] getGLContextAttrs 
-- @param self
-- @return GLContextAttrs#GLContextAttrs ret (return value: GLContextAttrs)
        
return nil
