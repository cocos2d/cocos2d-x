
--------------------------------
-- @module RichElementImage
-- @extend RichElement
-- @parent_module ccui

--------------------------------
-- brief Initialize a RichElementImage with various arguments.<br>
-- param tag A integer tag value.<br>
-- param color A color in Color3B.<br>
-- param opacity A opacity in GLubyte.<br>
-- param filePath A image file name.<br>
-- return True if initialize success, false otherwise.
-- @function [parent=#RichElementImage] init 
-- @param self
-- @param #int tag
-- @param #color3b_table color
-- @param #unsigned char opacity
-- @param #string filePath
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief Create a RichElementImage with various arguments.<br>
-- param tag A integer tag value.<br>
-- param color A color in Color3B.<br>
-- param opacity A opacity in GLubyte.<br>
-- param filePath A image file name.<br>
-- return A RichElementImage instance.
-- @function [parent=#RichElementImage] create 
-- @param self
-- @param #int tag
-- @param #color3b_table color
-- @param #unsigned char opacity
-- @param #string filePath
-- @return RichElementImage#RichElementImage ret (return value: ccui.RichElementImage)
        
--------------------------------
-- brief Default constructor.<br>
-- js ctor<br>
-- lua new
-- @function [parent=#RichElementImage] RichElementImage 
-- @param self
-- @return RichElementImage#RichElementImage self (return value: ccui.RichElementImage)
        
return nil
