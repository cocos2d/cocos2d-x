
--------------------------------
-- @module RenderTexture
-- @extend Node

--------------------------------
-- @function [parent=#RenderTexture] setVirtualViewport 
-- @param self
-- @param #cc.Vec2 vec2
-- @param #rect_table rect
-- @param #rect_table rect
        
--------------------------------
-- @function [parent=#RenderTexture] clearStencil 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#RenderTexture] getClearDepth 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#RenderTexture] getClearStencil 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#RenderTexture] end 
-- @param self
        
--------------------------------
-- @function [parent=#RenderTexture] setClearStencil 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#RenderTexture] setSprite 
-- @param self
-- @param #cc.Sprite sprite
        
--------------------------------
-- @function [parent=#RenderTexture] getSprite 
-- @param self
-- @return Sprite#Sprite ret (return value: cc.Sprite)
        
--------------------------------
-- @function [parent=#RenderTexture] isAutoDraw 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#RenderTexture] setKeepMatrix 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#RenderTexture] setClearFlags 
-- @param self
-- @param #unsigned int int
        
--------------------------------
-- @function [parent=#RenderTexture] begin 
-- @param self
        
--------------------------------
-- overload function: saveToFile(string, cc.Image::Format)
--          
-- overload function: saveToFile(string)
--          
-- @function [parent=#RenderTexture] saveToFile
-- @param self
-- @param #string str
-- @param #cc.Image::Format format
-- @return bool#bool ret (retunr value: bool)

--------------------------------
-- @function [parent=#RenderTexture] setAutoDraw 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#RenderTexture] setClearColor 
-- @param self
-- @param #color4f_table color4f
        
--------------------------------
-- @function [parent=#RenderTexture] endToLua 
-- @param self
        
--------------------------------
-- overload function: beginWithClear(float, float, float, float, float)
--          
-- overload function: beginWithClear(float, float, float, float)
--          
-- overload function: beginWithClear(float, float, float, float, float, int)
--          
-- @function [parent=#RenderTexture] beginWithClear
-- @param self
-- @param #float float
-- @param #float float
-- @param #float float
-- @param #float float
-- @param #float float
-- @param #int int

--------------------------------
-- @function [parent=#RenderTexture] clearDepth 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#RenderTexture] getClearColor 
-- @param self
-- @return color4f_table#color4f_table ret (return value: color4f_table)
        
--------------------------------
-- @function [parent=#RenderTexture] clear 
-- @param self
-- @param #float float
-- @param #float float
-- @param #float float
-- @param #float float
        
--------------------------------
-- @function [parent=#RenderTexture] getClearFlags 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- @function [parent=#RenderTexture] newImage 
-- @param self
-- @return Image#Image ret (return value: cc.Image)
        
--------------------------------
-- @function [parent=#RenderTexture] setClearDepth 
-- @param self
-- @param #float float
        
--------------------------------
-- overload function: initWithWidthAndHeight(int, int, cc.Texture2D::PixelFormat, unsigned int)
--          
-- overload function: initWithWidthAndHeight(int, int, cc.Texture2D::PixelFormat)
--          
-- @function [parent=#RenderTexture] initWithWidthAndHeight
-- @param self
-- @param #int int
-- @param #int int
-- @param #cc.Texture2D::PixelFormat pixelformat
-- @param #unsigned int int
-- @return bool#bool ret (retunr value: bool)

--------------------------------
-- overload function: create(int, int, cc.Texture2D::PixelFormat)
--          
-- overload function: create(int, int, cc.Texture2D::PixelFormat, unsigned int)
--          
-- overload function: create(int, int)
--          
-- @function [parent=#RenderTexture] create
-- @param self
-- @param #int int
-- @param #int int
-- @param #cc.Texture2D::PixelFormat pixelformat
-- @param #unsigned int int
-- @return RenderTexture#RenderTexture ret (retunr value: cc.RenderTexture)

--------------------------------
-- @function [parent=#RenderTexture] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #cc.Mat4 mat4
-- @param #bool bool
        
--------------------------------
-- @function [parent=#RenderTexture] visit 
-- @param self
-- @param #cc.Renderer renderer
-- @param #cc.Mat4 mat4
-- @param #bool bool
        
--------------------------------
-- @function [parent=#RenderTexture] RenderTexture 
-- @param self
        
return nil
