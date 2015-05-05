
--------------------------------
-- @module NodeGrid
-- @extend Node
-- @parent_module cc

--------------------------------
--  Set the Grid Target. <br>
-- param target A Node is used to set the Grid Target.
-- @function [parent=#NodeGrid] setTarget 
-- @param self
-- @param #cc.Node target
-- @return NodeGrid#NodeGrid self (return value: cc.NodeGrid)
        
--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#NodeGrid] getGrid
-- @param self
-- @return GridBase#GridBase ret (return value: cc.GridBase)

--------------------------------
-- Changes a grid object that is used when applying effects.<br>
-- param grid  A Grid object that is used when applying effects.
-- @function [parent=#NodeGrid] setGrid 
-- @param self
-- @param #cc.GridBase grid
-- @return NodeGrid#NodeGrid self (return value: cc.NodeGrid)
        
--------------------------------
--  Create a Grid Node.<br>
-- return An autorelease Grid Node.
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
-- @return NodeGrid#NodeGrid self (return value: cc.NodeGrid)
        
--------------------------------
-- 
-- @function [parent=#NodeGrid] NodeGrid 
-- @param self
-- @return NodeGrid#NodeGrid self (return value: cc.NodeGrid)
        
return nil
