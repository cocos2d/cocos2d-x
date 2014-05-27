
--------------------------------
-- @module ClippingNode
-- @extend Node

--------------------------------
-- @function [parent=#ClippingNode] isInverted 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ClippingNode] setInverted 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ClippingNode] setStencil 
-- @param self
-- @param #cc.Node node
        
--------------------------------
-- @function [parent=#ClippingNode] getAlphaThreshold 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#ClippingNode] getStencil 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- @function [parent=#ClippingNode] setAlphaThreshold 
-- @param self
-- @param #float float
        
--------------------------------
-- overload function: create(cc.Node)
--          
-- overload function: create()
--          
-- @function [parent=#ClippingNode] create
-- @param self
-- @param #cc.Node node
-- @return ClippingNode#ClippingNode ret (retunr value: cc.ClippingNode)

--------------------------------
-- @function [parent=#ClippingNode] visit 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table mat4
-- @param #bool bool
        
return nil
