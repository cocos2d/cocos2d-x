
--------------------------------
-- @module NodeGrid
-- @extend Node
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#NodeGrid] setTarget 
-- @param self
-- @param #cc.Node target
        
--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#NodeGrid] getGrid
-- @param self
-- @return GridBase#GridBase ret (retunr value: cc.GridBase)

--------------------------------
-- Changes a grid object that is used when applying effects<br>
-- param grid  A Grid object that is used when applying effects
-- @function [parent=#NodeGrid] setGrid 
-- @param self
-- @param #cc.GridBase grid
        
--------------------------------
-- 
-- @function [parent=#NodeGrid] create 
-- @param self
-- @return NodeGrid#NodeGrid ret (return value: cc.NodeGrid)
        
--------------------------------
-- 
-- @function [parent=#NodeGrid] visit 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table parentTransform
-- @param #unsigned int parentFlags
        
return nil
