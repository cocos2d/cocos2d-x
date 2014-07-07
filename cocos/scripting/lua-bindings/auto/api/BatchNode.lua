
--------------------------------
-- @module BatchNode
-- @extend Node
-- @parent_module ccs

--------------------------------
-- @function [parent=#BatchNode] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#BatchNode] create 
-- @param self
-- @return BatchNode#BatchNode ret (return value: ccs.BatchNode)
        
--------------------------------
-- overload function: addChild(cc.Node, int, string)
--          
-- overload function: addChild(cc.Node, int, int)
--          
-- @function [parent=#BatchNode] addChild
-- @param self
-- @param #cc.Node node
-- @param #int int
-- @param #int int

--------------------------------
-- @function [parent=#BatchNode] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table mat4
-- @param #unsigned int int
        
--------------------------------
-- @function [parent=#BatchNode] removeChild 
-- @param self
-- @param #cc.Node node
-- @param #bool bool
        
return nil
