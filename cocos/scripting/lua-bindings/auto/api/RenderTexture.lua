
--------------------------------
-- @module RenderTexture
-- @extend Node
-- @parent_module cc

--------------------------------
-- Used for grab part of screen to a texture. <br>
-- param rtBegin The position of renderTexture on the fullRect.<br>
-- param fullRect The total size of screen.<br>
-- param fullViewport The total viewportSize.
-- @function [parent=#RenderTexture] setVirtualViewport 
-- @param self
-- @param #vec2_table rtBegin
-- @param #rect_table fullRect
-- @param #rect_table fullViewport
-- @return RenderTexture#RenderTexture self (return value: cc.RenderTexture)
        
--------------------------------
--  Clears the texture with a specified stencil value.<br>
-- param A specified stencil value.
-- @function [parent=#RenderTexture] clearStencil 
-- @param self
-- @param #int stencilValue
-- @return RenderTexture#RenderTexture self (return value: cc.RenderTexture)
        
--------------------------------
--  Value for clearDepth. Valid only when "autoDraw" is true. <br>
-- return Value for clearDepth.
-- @function [parent=#RenderTexture] getClearDepth 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Value for clear Stencil. Valid only when "autoDraw" is true.<br>
-- return Value for clear Stencil.
-- @function [parent=#RenderTexture] getClearStencil 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Ends grabbing. 
-- @function [parent=#RenderTexture] end 
-- @param self
-- @return RenderTexture#RenderTexture self (return value: cc.RenderTexture)
        
--------------------------------
--  Set Value for clear Stencil.<br>
-- param clearStencil Value for clear Stencil.
-- @function [parent=#RenderTexture] setClearStencil 
-- @param self
-- @param #int clearStencil
-- @return RenderTexture#RenderTexture self (return value: cc.RenderTexture)
        
--------------------------------
--  Sets the Sprite being used. <br>
-- param A Sprite.
-- @function [parent=#RenderTexture] setSprite 
-- @param self
-- @param #cc.Sprite sprite
-- @return RenderTexture#RenderTexture self (return value: cc.RenderTexture)
        
--------------------------------
--  Gets the Sprite being used. <br>
-- return A Sprite.
-- @function [parent=#RenderTexture] getSprite 
-- @param self
-- @return Sprite#Sprite ret (return value: cc.Sprite)
        
--------------------------------
--  When enabled, it will render its children into the texture automatically. Disabled by default for compatiblity reasons.<br>
-- Will be enabled in the future.<br>
-- return Return the autoDraw value.
-- @function [parent=#RenderTexture] isAutoDraw 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Flag: Use stack matrix computed from scene hierarchy or generate new modelView and projection matrix.<br>
-- param keepMatrix Wether or not use stack matrix computed from scene hierarchy or generate new modelView and projection matrix.
-- @function [parent=#RenderTexture] setKeepMatrix 
-- @param self
-- @param #bool keepMatrix
-- @return RenderTexture#RenderTexture self (return value: cc.RenderTexture)
        
--------------------------------
--  Set flags.<br>
-- param clearFlags Valid flags: GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT.
-- @function [parent=#RenderTexture] setClearFlags 
-- @param self
-- @param #unsigned int clearFlags
-- @return RenderTexture#RenderTexture self (return value: cc.RenderTexture)
        
--------------------------------
--  Starts grabbing. 
-- @function [parent=#RenderTexture] begin 
-- @param self
-- @return RenderTexture#RenderTexture self (return value: cc.RenderTexture)
        
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
--  Set a valve to control whether or not render its children into the texture automatically. <br>
-- param isAutoDraw Whether or not render its children into the texture automatically.
-- @function [parent=#RenderTexture] setAutoDraw 
-- @param self
-- @param #bool isAutoDraw
-- @return RenderTexture#RenderTexture self (return value: cc.RenderTexture)
        
--------------------------------
--  Set color value. <br>
-- param clearColor Color value.
-- @function [parent=#RenderTexture] setClearColor 
-- @param self
-- @param #color4f_table clearColor
-- @return RenderTexture#RenderTexture self (return value: cc.RenderTexture)
        
--------------------------------
--  End is key word of lua, use other name to export to lua. 
-- @function [parent=#RenderTexture] endToLua 
-- @param self
-- @return RenderTexture#RenderTexture self (return value: cc.RenderTexture)
        
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
-- @return RenderTexture#RenderTexture self (return value: cc.RenderTexture)

--------------------------------
--  Clears the texture with a specified depth value. <br>
-- param A specified depth value.
-- @function [parent=#RenderTexture] clearDepth 
-- @param self
-- @param #float depthValue
-- @return RenderTexture#RenderTexture self (return value: cc.RenderTexture)
        
--------------------------------
--  Clear color value. Valid only when "autoDraw" is true. <br>
-- return Color value.
-- @function [parent=#RenderTexture] getClearColor 
-- @param self
-- @return color4f_table#color4f_table ret (return value: color4f_table)
        
--------------------------------
--  Clears the texture with a color. <br>
-- param r Red.<br>
-- param g Green.<br>
-- param b Blue.<br>
-- param a Alpha.
-- @function [parent=#RenderTexture] clear 
-- @param self
-- @param #float r
-- @param #float g
-- @param #float b
-- @param #float a
-- @return RenderTexture#RenderTexture self (return value: cc.RenderTexture)
        
--------------------------------
--  Valid flags: GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT. They can be OR'ed. Valid when "autoDraw" is true. <br>
-- return Clear flags.
-- @function [parent=#RenderTexture] getClearFlags 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- 
-- @function [parent=#RenderTexture] newImage 
-- @param self
-- @return Image#Image ret (return value: cc.Image)
        
--------------------------------
--  Set Value for clearDepth.<br>
-- param clearDepth Value for clearDepth.
-- @function [parent=#RenderTexture] setClearDepth 
-- @param self
-- @param #float clearDepth
-- @return RenderTexture#RenderTexture self (return value: cc.RenderTexture)
        
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
-- @return RenderTexture#RenderTexture self (return value: cc.RenderTexture)
        
--------------------------------
-- 
-- @function [parent=#RenderTexture] visit 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table parentTransform
-- @param #unsigned int parentFlags
-- @return RenderTexture#RenderTexture self (return value: cc.RenderTexture)
        
--------------------------------
--  FIXME: should be procted.<br>
-- but due to a bug in PowerVR + Android,<br>
-- the constructor is public again.
-- @function [parent=#RenderTexture] RenderTexture 
-- @param self
-- @return RenderTexture#RenderTexture self (return value: cc.RenderTexture)
        
return nil
