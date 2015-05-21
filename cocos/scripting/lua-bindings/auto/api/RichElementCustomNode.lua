
--------------------------------
-- @module RichElementCustomNode
-- @extend RichElement
-- @parent_module ccui

--------------------------------
-- brief Initialize a RichElementCustomNode with various arguments.<br>
-- param tag A integer tag value.<br>
-- param color A color in Color3B.<br>
-- param opacity A opacity in GLubyte.<br>
-- param customNode A custom node pointer.<br>
-- return True if initialize success, false otherwise.
-- @function [parent=#RichElementCustomNode] init 
-- @param self
-- @param #int tag
-- @param #color3b_table color
-- @param #unsigned char opacity
-- @param #cc.Node customNode
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief Create a RichElementCustomNode with various arguments.<br>
-- param tag A integer tag value.<br>
-- param color A color in Color3B.<br>
-- param opacity A opacity in GLubyte.<br>
-- param customNode A custom node pointer.<br>
-- return A RichElementCustomNode instance.
-- @function [parent=#RichElementCustomNode] create 
-- @param self
-- @param #int tag
-- @param #color3b_table color
-- @param #unsigned char opacity
-- @param #cc.Node customNode
-- @return RichElementCustomNode#RichElementCustomNode ret (return value: ccui.RichElementCustomNode)
        
--------------------------------
-- brief Default constructor.<br>
-- js ctor<br>
-- lua new
-- @function [parent=#RichElementCustomNode] RichElementCustomNode 
-- @param self
-- @return RichElementCustomNode#RichElementCustomNode self (return value: ccui.RichElementCustomNode)
        
return nil
