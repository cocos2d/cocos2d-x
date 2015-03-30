
--------------------------------
-- @module ParallaxNode
-- @extend Node
-- @parent_module cc

--------------------------------
--  Adds a child to the container with a local z-order, parallax ratio and position offset.<br>
-- param child A child node.<br>
-- param z Z order for drawing priority.<br>
-- param parallaxRatio A given parallax ratio.<br>
-- param positionOffset A given position offset.
-- @function [parent=#ParallaxNode] addChild 
-- @param self
-- @param #cc.Node child
-- @param #int z
-- @param #vec2_table parallaxRatio
-- @param #vec2_table positionOffset
-- @return ParallaxNode#ParallaxNode self (return value: cc.ParallaxNode)
        
--------------------------------
-- 
-- @function [parent=#ParallaxNode] removeAllChildrenWithCleanup 
-- @param self
-- @param #bool cleanup
-- @return ParallaxNode#ParallaxNode self (return value: cc.ParallaxNode)
        
--------------------------------
--  Create a Parallax node. <br>
-- return An autoreleased ParallaxNode object.
-- @function [parent=#ParallaxNode] create 
-- @param self
-- @return ParallaxNode#ParallaxNode ret (return value: cc.ParallaxNode)
        
--------------------------------
-- @overload self, cc.Node, int, string         
-- @overload self, cc.Node, int, int         
-- @function [parent=#ParallaxNode] addChild
-- @param self
-- @param #cc.Node child
-- @param #int zOrder
-- @param #int tag
-- @return ParallaxNode#ParallaxNode self (return value: cc.ParallaxNode)

--------------------------------
-- 
-- @function [parent=#ParallaxNode] visit 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table parentTransform
-- @param #unsigned int parentFlags
-- @return ParallaxNode#ParallaxNode self (return value: cc.ParallaxNode)
        
--------------------------------
-- 
-- @function [parent=#ParallaxNode] removeChild 
-- @param self
-- @param #cc.Node child
-- @param #bool cleanup
-- @return ParallaxNode#ParallaxNode self (return value: cc.ParallaxNode)
        
return nil
