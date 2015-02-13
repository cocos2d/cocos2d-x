
--------------------------------
-- @module ParallaxNode
-- @extend Node
-- @parent_module cc

--------------------------------
-- 
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
-- 
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
