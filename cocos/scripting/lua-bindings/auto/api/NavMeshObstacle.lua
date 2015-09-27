
--------------------------------
-- @module NavMeshObstacle
-- @extend Component
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#NavMeshObstacle] getSyncFlag 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#NavMeshObstacle] initWith 
-- @param self
-- @param #float radius
-- @param #float height
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  synchronize parameter to obstacle. 
-- @function [parent=#NavMeshObstacle] syncToObstacle 
-- @param self
-- @return NavMeshObstacle#NavMeshObstacle self (return value: cc.NavMeshObstacle)
        
--------------------------------
--  synchronize parameter to node. 
-- @function [parent=#NavMeshObstacle] syncToNode 
-- @param self
-- @return NavMeshObstacle#NavMeshObstacle self (return value: cc.NavMeshObstacle)
        
--------------------------------
--  Get height of obstacle 
-- @function [parent=#NavMeshObstacle] getHeight 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- synchronization between node and obstacle is time consuming, you can skip some synchronization using this function
-- @function [parent=#NavMeshObstacle] setSyncFlag 
-- @param self
-- @param #int flag
-- @return NavMeshObstacle#NavMeshObstacle self (return value: cc.NavMeshObstacle)
        
--------------------------------
--  Get radius of obstacle 
-- @function [parent=#NavMeshObstacle] getRadius 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Create obstacle, shape is cylinder<br>
-- param radius The radius of obstacle.<br>
-- param height The height of obstacle.
-- @function [parent=#NavMeshObstacle] create 
-- @param self
-- @param #float radius
-- @param #float height
-- @return NavMeshObstacle#NavMeshObstacle ret (return value: cc.NavMeshObstacle)
        
--------------------------------
-- 
-- @function [parent=#NavMeshObstacle] getNavMeshObstacleComponentName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#NavMeshObstacle] onEnter 
-- @param self
-- @return NavMeshObstacle#NavMeshObstacle self (return value: cc.NavMeshObstacle)
        
--------------------------------
-- 
-- @function [parent=#NavMeshObstacle] onExit 
-- @param self
-- @return NavMeshObstacle#NavMeshObstacle self (return value: cc.NavMeshObstacle)
        
--------------------------------
-- 
-- @function [parent=#NavMeshObstacle] NavMeshObstacle 
-- @param self
-- @return NavMeshObstacle#NavMeshObstacle self (return value: cc.NavMeshObstacle)
        
return nil
