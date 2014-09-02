
--------------------------------
-- @module Button
-- @extend Widget
-- @parent_module ccui

--------------------------------
-- 
-- @function [parent=#Button] getTitleText 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#Button] setTitleFontSize 
-- @param self
-- @param #float size
        
--------------------------------
-- Sets if button is using scale9 renderer.<br>
-- param true that using scale9 renderer, false otherwise.
-- @function [parent=#Button] setScale9Enabled 
-- @param self
-- @param #bool able
        
--------------------------------
-- brief Return a zoom scale 
-- @function [parent=#Button] getZoomScale 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Button] getCapInsetsDisabledRenderer 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- 
-- @function [parent=#Button] setTitleColor 
-- @param self
-- @param #color3b_table color
        
--------------------------------
-- Sets capinsets for button, if button is using scale9 renderer.<br>
-- param capInsets    capinsets for button
-- @function [parent=#Button] setCapInsetsDisabledRenderer 
-- @param self
-- @param #rect_table capInsets
        
--------------------------------
-- Sets capinsets for button, if button is using scale9 renderer.<br>
-- param capInsets    capinsets for button
-- @function [parent=#Button] setCapInsets 
-- @param self
-- @param #rect_table capInsets
        
--------------------------------
-- Load dark state texture for button.<br>
-- param disabled    dark state texture.<br>
-- param texType    @see TextureResType
-- @function [parent=#Button] loadTextureDisabled 
-- @param self
-- @param #string disabled
-- @param #int texType
        
--------------------------------
-- 
-- @function [parent=#Button] setTitleText 
-- @param self
-- @param #string text
        
--------------------------------
-- Sets capinsets for button, if button is using scale9 renderer.<br>
-- param capInsets    capinsets for button
-- @function [parent=#Button] setCapInsetsNormalRenderer 
-- @param self
-- @param #rect_table capInsets
        
--------------------------------
-- Load selected state texture for button.<br>
-- param selected    selected state texture.<br>
-- param texType    @see TextureResType
-- @function [parent=#Button] loadTexturePressed 
-- @param self
-- @param #string selected
-- @param #int texType
        
--------------------------------
-- 
-- @function [parent=#Button] setTitleFontName 
-- @param self
-- @param #string fontName
        
--------------------------------
-- 
-- @function [parent=#Button] getCapInsetsNormalRenderer 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- 
-- @function [parent=#Button] getCapInsetsPressedRenderer 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- Load textures for button.<br>
-- param normal    normal state texture name.<br>
-- param selected    selected state texture name.<br>
-- param disabled    disabled state texture name.<br>
-- param texType    @see TextureResType
-- @function [parent=#Button] loadTextures 
-- @param self
-- @param #string normal
-- @param #string selected
-- @param #string disabled
-- @param #int texType
        
--------------------------------
-- 
-- @function [parent=#Button] isScale9Enabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Load normal state texture for button.<br>
-- param normal    normal state texture.<br>
-- param texType    @see TextureResType
-- @function [parent=#Button] loadTextureNormal 
-- @param self
-- @param #string normal
-- @param #int texType
        
--------------------------------
-- Sets capinsets for button, if button is using scale9 renderer.<br>
-- param capInsets    capinsets for button
-- @function [parent=#Button] setCapInsetsPressedRenderer 
-- @param self
-- @param #rect_table capInsets
        
--------------------------------
-- 
-- @function [parent=#Button] getTitleFontSize 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Button] getTitleFontName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#Button] getTitleColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- Changes if button can be clicked zoom effect.<br>
-- param true that can be clicked zoom effect, false otherwise.
-- @function [parent=#Button] setPressedActionEnabled 
-- @param self
-- @param #bool enabled
        
--------------------------------
--  When user pressed the button, the button will zoom to a scale.<br>
-- The final scale of the button  equals (button original scale + _zoomScale)
-- @function [parent=#Button] setZoomScale 
-- @param self
-- @param #float scale
        
--------------------------------
-- @overload self, string, string, string, int         
-- @overload self         
-- @function [parent=#Button] create
-- @param self
-- @param #string normalImage
-- @param #string selectedImage
-- @param #string disableImage
-- @param #int texType
-- @return Button#Button ret (retunr value: ccui.Button)

--------------------------------
-- 
-- @function [parent=#Button] createInstance 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- 
-- @function [parent=#Button] getVirtualRenderer 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- Returns the "class name" of widget.
-- @function [parent=#Button] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#Button] getVirtualRendererSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- 
-- @function [parent=#Button] ignoreContentAdaptWithSize 
-- @param self
-- @param #bool ignore
        
--------------------------------
-- Default constructor
-- @function [parent=#Button] Button 
-- @param self
        
return nil
