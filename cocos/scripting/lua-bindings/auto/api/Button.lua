
--------------------------------
-- @module Button
-- @extend Widget
-- @parent_module ccui

--------------------------------
-- 
-- @function [parent=#Button] getNormalTextureSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- Query the button title content.<br>
-- return Get the button's title content.
-- @function [parent=#Button] getTitleText 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Change the font size of button's title<br>
-- param size Title font size in float.
-- @function [parent=#Button] setTitleFontSize 
-- @param self
-- @param #float size
-- @return Button#Button self (return value: ccui.Button)
        
--------------------------------
-- 
-- @function [parent=#Button] resetPressedRender 
-- @param self
-- @return Button#Button self (return value: ccui.Button)
        
--------------------------------
-- Enable scale9 renderer.<br>
-- param enable Set to true will use scale9 renderer, false otherwise.
-- @function [parent=#Button] setScale9Enabled 
-- @param self
-- @param #bool enable
-- @return Button#Button self (return value: ccui.Button)
        
--------------------------------
-- 
-- @function [parent=#Button] resetDisabledRender 
-- @param self
-- @return Button#Button self (return value: ccui.Button)
        
--------------------------------
-- Return the inner title renderer of Button.<br>
-- return The button title.<br>
-- since v3.3
-- @function [parent=#Button] getTitleRenderer 
-- @param self
-- @return Label#Label ret (return value: cc.Label)
        
--------------------------------
-- brief Return the nine-patch sprite of clicked state<br>
-- return the nine-patch sprite of clicked state<br>
-- since v3.9
-- @function [parent=#Button] getRendererClicked 
-- @param self
-- @return Scale9Sprite#Scale9Sprite ret (return value: ccui.Scale9Sprite)
        
--------------------------------
-- 
-- @function [parent=#Button] getDisabledFile 
-- @param self
-- @return ResourceData#ResourceData ret (return value: cc.ResourceData)
        
--------------------------------
-- brief Return a zoom scale<br>
-- return the zoom scale in float<br>
-- since v3.3
-- @function [parent=#Button] getZoomScale 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Return the capInsets of disabled state scale9sprite.<br>
-- return The disabled scale9 renderer capInsets.
-- @function [parent=#Button] getCapInsetsDisabledRenderer 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- Change the color of button's title.<br>
-- param color The title color in Color3B.
-- @function [parent=#Button] setTitleColor 
-- @param self
-- @param #color3b_table color
-- @return Button#Button self (return value: ccui.Button)
        
--------------------------------
-- 
-- @function [parent=#Button] getNormalFile 
-- @param self
-- @return ResourceData#ResourceData ret (return value: cc.ResourceData)
        
--------------------------------
-- 
-- @function [parent=#Button] resetNormalRender 
-- @param self
-- @return Button#Button self (return value: ccui.Button)
        
--------------------------------
-- brief Return the nine-patch sprite of disabled state<br>
-- return the nine-patch sprite of disabled state<br>
-- since v3.9
-- @function [parent=#Button] getRendererDisabled 
-- @param self
-- @return Scale9Sprite#Scale9Sprite ret (return value: ccui.Scale9Sprite)
        
--------------------------------
-- Sets capInsets for button, only the disabled state scale9 renderer will be affected.<br>
-- param capInsets  capInsets in Rect.
-- @function [parent=#Button] setCapInsetsDisabledRenderer 
-- @param self
-- @param #rect_table capInsets
-- @return Button#Button self (return value: ccui.Button)
        
--------------------------------
-- Sets capInsets for button.<br>
-- The capInset affects  all button scale9 renderer only if `setScale9Enabled(true)` is called<br>
-- param capInsets    capInset in Rect.
-- @function [parent=#Button] setCapInsets 
-- @param self
-- @param #rect_table capInsets
-- @return Button#Button self (return value: ccui.Button)
        
--------------------------------
-- Load disabled state texture for button.<br>
-- param disabled    dark state texture.<br>
-- param texType    @see `TextureResType`
-- @function [parent=#Button] loadTextureDisabled 
-- @param self
-- @param #string disabled
-- @param #int texType
-- @return Button#Button self (return value: ccui.Button)
        
--------------------------------
-- 
-- @function [parent=#Button] init 
-- @param self
-- @param #string normalImage
-- @param #string selectedImage
-- @param #string disableImage
-- @param #int texType
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Change the content of button's title.<br>
-- param text The title in std::string.
-- @function [parent=#Button] setTitleText 
-- @param self
-- @param #string text
-- @return Button#Button self (return value: ccui.Button)
        
--------------------------------
-- Sets capInsets for button, only the normal state scale9 renderer will be affected.<br>
-- param capInsets    capInsets in Rect.
-- @function [parent=#Button] setCapInsetsNormalRenderer 
-- @param self
-- @param #rect_table capInsets
-- @return Button#Button self (return value: ccui.Button)
        
--------------------------------
-- Load selected state texture for button.<br>
-- param selected    selected state texture.<br>
-- param texType    @see `TextureResType`
-- @function [parent=#Button] loadTexturePressed 
-- @param self
-- @param #string selected
-- @param #int texType
-- @return Button#Button self (return value: ccui.Button)
        
--------------------------------
-- Change the font name of button's title<br>
-- param fontName a font name string.
-- @function [parent=#Button] setTitleFontName 
-- @param self
-- @param #string fontName
-- @return Button#Button self (return value: ccui.Button)
        
--------------------------------
-- Return the capInsets of normal state scale9sprite.<br>
-- return The normal scale9 renderer capInsets.
-- @function [parent=#Button] getCapInsetsNormalRenderer 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- @overload self, int, int         
-- @overload self, int         
-- @function [parent=#Button] setTitleAlignment
-- @param self
-- @param #int hAlignment
-- @param #int vAlignment
-- @return Button#Button self (return value: ccui.Button)

--------------------------------
-- Return the capInsets of pressed state scale9sprite.<br>
-- return The pressed scale9 renderer capInsets.
-- @function [parent=#Button] getCapInsetsPressedRenderer 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- Load textures for button.<br>
-- param normal    normal state texture name.<br>
-- param selected    selected state texture name.<br>
-- param disabled    disabled state texture name.<br>
-- param texType    @see `TextureResType`
-- @function [parent=#Button] loadTextures 
-- @param self
-- @param #string normal
-- @param #string selected
-- @param #string disabled
-- @param #int texType
-- @return Button#Button self (return value: ccui.Button)
        
--------------------------------
-- Query whether button is using scale9 renderer or not.<br>
-- return whether button use scale9 renderer or not.
-- @function [parent=#Button] isScale9Enabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Load normal state texture for button.<br>
-- param normal    normal state texture.<br>
-- param texType    @see `TextureResType`
-- @function [parent=#Button] loadTextureNormal 
-- @param self
-- @param #string normal
-- @param #int texType
-- @return Button#Button self (return value: ccui.Button)
        
--------------------------------
-- Sets capInsets for button, only the pressed state scale9 renderer will be affected.<br>
-- param capInsets    capInsets in Rect
-- @function [parent=#Button] setCapInsetsPressedRenderer 
-- @param self
-- @param #rect_table capInsets
-- @return Button#Button self (return value: ccui.Button)
        
--------------------------------
-- 
-- @function [parent=#Button] getPressedFile 
-- @param self
-- @return ResourceData#ResourceData ret (return value: cc.ResourceData)
        
--------------------------------
-- Query the font size of button title<br>
-- return font size in float.
-- @function [parent=#Button] getTitleFontSize 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- brief Return the nine-patch sprite of normal state<br>
-- return the nine-patch sprite of normal state<br>
-- since v3.9
-- @function [parent=#Button] getRendererNormal 
-- @param self
-- @return Scale9Sprite#Scale9Sprite ret (return value: ccui.Scale9Sprite)
        
--------------------------------
-- Query the font name of button's title<br>
-- return font name in std::string
-- @function [parent=#Button] getTitleFontName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Query the button title color.<br>
-- return Color3B of button title.
-- @function [parent=#Button] getTitleColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- Enable zooming action when button is pressed.<br>
-- param enabled Set to true will enable zoom effect, false otherwise.
-- @function [parent=#Button] setPressedActionEnabled 
-- @param self
-- @param #bool enabled
-- @return Button#Button self (return value: ccui.Button)
        
--------------------------------
--  @brief When user pressed the button, the button will zoom to a scale.<br>
-- The final scale of the button  equals (button original scale + _zoomScale)<br>
-- since v3.3
-- @function [parent=#Button] setZoomScale 
-- @param self
-- @param #float scale
-- @return Button#Button self (return value: ccui.Button)
        
--------------------------------
-- @overload self, string, string, string, int         
-- @overload self         
-- @function [parent=#Button] create
-- @param self
-- @param #string normalImage
-- @param #string selectedImage
-- @param #string disableImage
-- @param #int texType
-- @return Button#Button ret (return value: ccui.Button)

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
-- 
-- @function [parent=#Button] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
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
-- @return Button#Button self (return value: ccui.Button)
        
--------------------------------
-- Default constructor.
-- @function [parent=#Button] Button 
-- @param self
-- @return Button#Button self (return value: ccui.Button)
        
return nil
