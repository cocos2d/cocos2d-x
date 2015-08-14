
--------------------------------
-- @module ClippingRectangleNode
-- @extend Node
-- @parent_module cc

--------------------------------
-- brief Get whether the clipping is enabled or not.<br>
-- return Whether the clipping is enabled or not. Default is true.
-- @function [parent=#ClippingRectangleNode] isClippingEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief Enable/Disable the clipping.<br>
-- param enabled Pass true to enable clipping. Pass false to disable clipping.
-- @function [parent=#ClippingRectangleNode] setClippingEnabled 
-- @param self
-- @param #bool enabled
-- @return ClippingRectangleNode#ClippingRectangleNode self (return value: cc.ClippingRectangleNode)
        
--------------------------------
-- brief Get the clipping rectangle.<br>
-- return The clipping rectangle.
-- @function [parent=#ClippingRectangleNode] getClippingRegion 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- brief Set the clipping rectangle. The rectangle is base on screen coordinate, so ClippingRectangleNode's region doesn't support any transforms, such as setScale, setRotate and so on.<br>
-- param clippingRegion Specify the clipping rectangle.
-- @function [parent=#ClippingRectangleNode] setClippingRegion 
-- @param self
-- @param #rect_table clippingRegion
-- @return ClippingRectangleNode#ClippingRectangleNode self (return value: cc.ClippingRectangleNode)
        
--------------------------------
-- @overload self         
-- @overload self, rect_table         
-- @function [parent=#ClippingRectangleNode] create
-- @param self
-- @param #rect_table clippingRegion
-- @return ClippingRectangleNode#ClippingRectangleNode ret (return value: cc.ClippingRectangleNode)

--------------------------------
-- 
-- @function [parent=#ClippingRectangleNode] visit 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table parentTransform
-- @param #unsigned int parentFlags
-- @return ClippingRectangleNode#ClippingRectangleNode self (return value: cc.ClippingRectangleNode)
        
return nil
