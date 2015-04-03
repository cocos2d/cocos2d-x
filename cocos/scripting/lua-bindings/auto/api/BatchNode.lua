
--------------------------------
-- @module BatchNode
-- @extend Node
-- @parent_module ccs

--------------------------------
-- js NA
-- @function [parent=#BatchNode] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#BatchNode] create 
-- @param self
-- @return BatchNode#BatchNode ret (return value: ccs.BatchNode)
        
--------------------------------
-- @overload self, cc.Node, int, string         
-- @overload self, cc.Node, int, int         
-- @function [parent=#BatchNode] addChild
-- @param self
-- @param #cc.Node pChild
-- @param #int zOrder
-- @param #int tag
-- @return BatchNode#BatchNode self (return value: ccs.BatchNode)

--------------------------------
-- 
-- @function [parent=#BatchNode] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
-- @return BatchNode#BatchNode self (return value: ccs.BatchNode)
        
--------------------------------
-- 
-- @function [parent=#BatchNode] removeChild 
-- @param self
-- @param #cc.Node child
-- @param #bool cleanup
-- @return BatchNode#BatchNode self (return value: ccs.BatchNode)
        
return nil
