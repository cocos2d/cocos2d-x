
--------------------------------
-- @module ReuseGrid
-- @extend ActionInstant
-- @parent_module cc

--------------------------------
-- brief Initializes an action with the number of times that the current grid will be reused.<br>
-- param times Specify times the grid will be reused.<br>
-- return If the initialization sucess, return true; otherwise, return false.
-- @function [parent=#ReuseGrid] initWithTimes 
-- @param self
-- @param #int times
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief Create an action with the number of times that the current grid will be reused.<br>
-- param times Specify times the grid will be reused.<br>
-- return Return a pointer of ReuseGrid. When the creation failed, return nil.
-- @function [parent=#ReuseGrid] create 
-- @param self
-- @param #int times
-- @return ReuseGrid#ReuseGrid ret (return value: cc.ReuseGrid)
        
--------------------------------
-- 
-- @function [parent=#ReuseGrid] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return ReuseGrid#ReuseGrid self (return value: cc.ReuseGrid)
        
--------------------------------
-- 
-- @function [parent=#ReuseGrid] clone 
-- @param self
-- @return ReuseGrid#ReuseGrid ret (return value: cc.ReuseGrid)
        
--------------------------------
-- 
-- @function [parent=#ReuseGrid] reverse 
-- @param self
-- @return ReuseGrid#ReuseGrid ret (return value: cc.ReuseGrid)
        
--------------------------------
-- 
-- @function [parent=#ReuseGrid] ReuseGrid 
-- @param self
-- @return ReuseGrid#ReuseGrid self (return value: cc.ReuseGrid)
        
return nil
