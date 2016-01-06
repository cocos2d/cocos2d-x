
--------------------------------
-- @module ImageView
-- @extend Widget
-- @parent_module ccui

--------------------------------
-- Load texture for imageview.<br>
-- param fileName   file name of texture.<br>
-- param texType    @see `Widget::TextureResType`
-- @function [parent=#ImageView] loadTexture 
-- @param self
-- @param #string fileName
-- @param #int texType
-- @return ImageView#ImageView self (return value: ccui.ImageView)
        
--------------------------------
-- 
-- @function [parent=#ImageView] init 
-- @param self
-- @param #string imageFileName
-- @param #int texType
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Enable scale9 renderer.<br>
-- param enabled Set to true will use scale9 renderer, false otherwise.
-- @function [parent=#ImageView] setScale9Enabled 
-- @param self
-- @param #bool enabled
-- @return ImageView#ImageView self (return value: ccui.ImageView)
        
--------------------------------
-- Updates the texture rect of the ImageView in points.<br>
-- It will call setTextureRect:rotated:untrimmedSize with rotated = NO, and utrimmedSize = rect.size.
-- @function [parent=#ImageView] setTextureRect 
-- @param self
-- @param #rect_table rect
-- @return ImageView#ImageView self (return value: ccui.ImageView)
        
--------------------------------
-- Sets capInsets for imageview.<br>
-- The capInsets affects the ImageView's renderer only if `setScale9Enabled(true)` is called.<br>
-- param capInsets    capinsets for imageview
-- @function [parent=#ImageView] setCapInsets 
-- @param self
-- @param #rect_table capInsets
-- @return ImageView#ImageView self (return value: ccui.ImageView)
        
--------------------------------
-- 
-- @function [parent=#ImageView] getRenderFile 
-- @param self
-- @return ResourceData#ResourceData ret (return value: cc.ResourceData)
        
--------------------------------
-- Get ImageView's capInsets size.<br>
-- return Query capInsets size in Rect<br>
-- see `setCapInsets(const Rect&)`
-- @function [parent=#ImageView] getCapInsets 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- Query whether button is using scale9 renderer or not.<br>
-- return whether button use scale9 renderer or not.
-- @function [parent=#ImageView] isScale9Enabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @overload self, string, int         
-- @overload self         
-- @function [parent=#ImageView] create
-- @param self
-- @param #string imageFileName
-- @param #int texType
-- @return ImageView#ImageView ret (return value: ccui.ImageView)

--------------------------------
-- 
-- @function [parent=#ImageView] createInstance 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- 
-- @function [parent=#ImageView] getVirtualRenderer 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#ImageView] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ImageView] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#ImageView] getVirtualRendererSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- 
-- @function [parent=#ImageView] ignoreContentAdaptWithSize 
-- @param self
-- @param #bool ignore
-- @return ImageView#ImageView self (return value: ccui.ImageView)
        
--------------------------------
-- Default constructor<br>
-- js ctor<br>
-- lua new
-- @function [parent=#ImageView] ImageView 
-- @param self
-- @return ImageView#ImageView self (return value: ccui.ImageView)
        
return nil
