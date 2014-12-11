
--------------------------------
-- @module RenderTexture
-- @extend Node
-- @parent_module cc

--------------------------------
-- Used for grab part of screen to a texture.rtBegin: the position of renderTexture on the fullRectfullRect: the total size of screenfullViewport: the total viewportSize
-- @function [parent=#RenderTexture] setVirtualViewport 
-- @param self
-- @param #vec2_table rtBegin
-- @param #rect_table fullRect
-- @param #rect_table fullViewport
        
--------------------------------
--  clears the texture with a specified stencil value 
-- @function [parent=#RenderTexture] clearStencil 
-- @param self
-- @param #int stencilValue
        
--------------------------------
--  Value for clearDepth. Valid only when "autoDraw" is true. 
-- @function [parent=#RenderTexture] getClearDepth 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Value for clear Stencil. Valid only when "autoDraw" is true 
-- @function [parent=#RenderTexture] getClearStencil 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  ends grabbing
-- @function [parent=#RenderTexture] end 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#RenderTexture] setClearStencil 
-- @param self
-- @param #int clearStencil
        
--------------------------------
--  Sets the Sprite being used. 
-- @function [parent=#RenderTexture] setSprite 
-- @param self
-- @param #cc.Sprite sprite
        
--------------------------------
--  Gets the Sprite being used. 
-- @function [parent=#RenderTexture] getSprite 
-- @param self
-- @return Sprite#Sprite ret (return value: cc.Sprite)
        
--------------------------------
--  When enabled, it will render its children into the texture automatically. Disabled by default for compatiblity reasons.<br>
-- Will be enabled in the future.
-- @function [parent=#RenderTexture] isAutoDraw 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#RenderTexture] setKeepMatrix 
-- @param self
-- @param #bool keepMatrix
        
--------------------------------
-- 
-- @function [parent=#RenderTexture] setClearFlags 
-- @param self
-- @param #unsigned int clearFlags
        
--------------------------------
--  starts grabbing 
-- @function [parent=#RenderTexture] begin 
-- @param self
        
--------------------------------
-- @overload self, string, int, bool, function         
-- @overload self, string, bool, function         
-- @function [parent=#RenderTexture] saveToFile
-- @param self
-- @param #string filename
-- @param #int format
-- @param #bool isRGBA
-- @param #function callback
-- @return bool#bool ret (return value: bool)

--------------------------------
-- 
-- @function [parent=#RenderTexture] setAutoDraw 
-- @param self
-- @param #bool isAutoDraw
        
--------------------------------
-- 
-- @function [parent=#RenderTexture] setClearColor 
-- @param self
-- @param #color4f_table clearColor
        
--------------------------------
--  end is key word of lua, use other name to export to lua. 
-- @function [parent=#RenderTexture] endToLua 
-- @param self
        
--------------------------------
-- @overload self, float, float, float, float, float         
-- @overload self, float, float, float, float         
-- @overload self, float, float, float, float, float, int         
-- @function [parent=#RenderTexture] beginWithClear
-- @param self
-- @param #float r
-- @param #float g
-- @param #float b
-- @param #float a
-- @param #float depthValue
-- @param #int stencilValue

--------------------------------
--  clears the texture with a specified depth value 
-- @function [parent=#RenderTexture] clearDepth 
-- @param self
-- @param #float depthValue
        
--------------------------------
--  Clear color value. Valid only when "autoDraw" is true. 
-- @function [parent=#RenderTexture] getClearColor 
-- @param self
-- @return color4f_table#color4f_table ret (return value: color4f_table)
        
--------------------------------
--  clears the texture with a color 
-- @function [parent=#RenderTexture] clear 
-- @param self
-- @param #float r
-- @param #float g
-- @param #float b
-- @param #float a
        
--------------------------------
--  Valid flags: GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT. They can be OR'ed. Valid when "autoDraw" is true. 
-- @function [parent=#RenderTexture] getClearFlags 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- 
-- @function [parent=#RenderTexture] newImage 
-- @param self
-- @return Image#Image ret (return value: cc.Image)
        
--------------------------------
-- 
-- @function [parent=#RenderTexture] setClearDepth 
-- @param self
-- @param #float clearDepth
        
--------------------------------
-- @overload self, int, int, int, unsigned int         
-- @overload self, int, int, int         
-- @function [parent=#RenderTexture] initWithWidthAndHeight
-- @param self
-- @param #int w
-- @param #int h
-- @param #int format
-- @param #unsigned int depthStencilFormat
-- @return bool#bool ret (return value: bool)

--------------------------------
-- @overload self, int, int, int         
-- @overload self, int, int, int, unsigned int         
-- @overload self, int, int         
-- @function [parent=#RenderTexture] create
-- @param self
-- @param #int w
-- @param #int h
-- @param #int format
-- @param #unsigned int depthStencilFormat
-- @return RenderTexture#RenderTexture ret (return value: cc.RenderTexture)

--------------------------------
-- 
-- @function [parent=#RenderTexture] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
        
--------------------------------
-- 
-- @function [parent=#RenderTexture] visit 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table parentTransform
-- @param #unsigned int parentFlags
        
--------------------------------
-- 
-- @function [parent=#RenderTexture] RenderTexture 
-- @param self
        
return nil
