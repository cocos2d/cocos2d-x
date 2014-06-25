
--------------------------------
-- @module ImageView
-- @extend Widget
-- @parent_module ccui

--------------------------------
-- @function [parent=#ImageView] loadTexture 
-- @param self
-- @param #string str
-- @param #ccui.Widget::TextureResType texturerestype
        
--------------------------------
-- @function [parent=#ImageView] setScale9Enabled 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ImageView] setTextureRect 
-- @param self
-- @param #rect_table rect
        
--------------------------------
-- @function [parent=#ImageView] setCapInsets 
-- @param self
-- @param #rect_table rect
        
--------------------------------
-- @function [parent=#ImageView] getCapInsets 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- @function [parent=#ImageView] isScale9Enabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- overload function: create(string, ccui.Widget::TextureResType)
--          
-- overload function: create()
--          
-- @function [parent=#ImageView] create
-- @param self
-- @param #string str
-- @param #ccui.Widget::TextureResType texturerestype
-- @return ImageView#ImageView ret (retunr value: ccui.ImageView)

--------------------------------
-- @function [parent=#ImageView] createInstance 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- @function [parent=#ImageView] getVirtualRenderer 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- @function [parent=#ImageView] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#ImageView] getVirtualRendererSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#ImageView] ignoreContentAdaptWithSize 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ImageView] ImageView 
-- @param self
        
return nil
