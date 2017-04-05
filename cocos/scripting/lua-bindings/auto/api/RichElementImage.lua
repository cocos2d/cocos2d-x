
--------------------------------
-- @module RichElementImage
-- @extend RichElement
-- @parent_module ccui

--------------------------------
-- 
-- @function [parent=#RichElementImage] setHeight 
-- @param self
-- @param #int height
-- @return RichElementImage#RichElementImage self (return value: ccui.RichElementImage)
        
--------------------------------
-- brief Initialize a RichElementImage with various arguments.<br>
-- param tag A integer tag value.<br>
-- param color A color in Color3B.<br>
-- param opacity A opacity in GLubyte.<br>
-- param filePath A image file name.<br>
-- param url uniform resource locator<br>
-- return True if initialize success, false otherwise.
-- @function [parent=#RichElementImage] init 
-- @param self
-- @param #int tag
-- @param #color3b_table color
-- @param #unsigned char opacity
-- @param #string filePath
-- @param #string url
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#RichElementImage] setWidth 
-- @param self
-- @param #int width
-- @return RichElementImage#RichElementImage self (return value: ccui.RichElementImage)
        
--------------------------------
-- 
-- @function [parent=#RichElementImage] setUrl 
-- @param self
-- @param #string url
-- @return RichElementImage#RichElementImage self (return value: ccui.RichElementImage)
        
--------------------------------
-- brief Create a RichElementImage with various arguments.<br>
-- param tag A integer tag value.<br>
-- param color A color in Color3B.<br>
-- param opacity A opacity in GLubyte.<br>
-- param filePath A image file name.<br>
-- param url uniform resource locator<br>
-- return A RichElementImage instance.
-- @function [parent=#RichElementImage] create 
-- @param self
-- @param #int tag
-- @param #color3b_table color
-- @param #unsigned char opacity
-- @param #string filePath
-- @param #string url
-- @return RichElementImage#RichElementImage ret (return value: ccui.RichElementImage)
        
--------------------------------
-- brief Default constructor.<br>
-- js ctor<br>
-- lua new
-- @function [parent=#RichElementImage] RichElementImage 
-- @param self
-- @return RichElementImage#RichElementImage self (return value: ccui.RichElementImage)
        
return nil
