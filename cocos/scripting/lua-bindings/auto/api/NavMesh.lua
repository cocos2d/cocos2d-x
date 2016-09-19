
--------------------------------
-- @module NavMesh
-- @extend Ref
-- @parent_module cc

--------------------------------
--  remove a obstacle from navmesh. 
-- @function [parent=#NavMesh] removeNavMeshObstacle 
-- @param self
-- @param #cc.NavMeshObstacle obstacle
-- @return NavMesh#NavMesh self (return value: cc.NavMesh)
        
--------------------------------
--  remove a agent from navmesh. 
-- @function [parent=#NavMesh] removeNavMeshAgent 
-- @param self
-- @param #cc.NavMeshAgent agent
-- @return NavMesh#NavMesh self (return value: cc.NavMesh)
        
--------------------------------
--  update navmesh. 
-- @function [parent=#NavMesh] update 
-- @param self
-- @param #float dt
-- @return NavMesh#NavMesh self (return value: cc.NavMesh)
        
--------------------------------
--  Check enabled debug draw. 
-- @function [parent=#NavMesh] isDebugDrawEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  add a agent to navmesh. 
-- @function [parent=#NavMesh] addNavMeshAgent 
-- @param self
-- @param #cc.NavMeshAgent agent
-- @return NavMesh#NavMesh self (return value: cc.NavMesh)
        
--------------------------------
--  add a obstacle to navmesh. 
-- @function [parent=#NavMesh] addNavMeshObstacle 
-- @param self
-- @param #cc.NavMeshObstacle obstacle
-- @return NavMesh#NavMesh self (return value: cc.NavMesh)
        
--------------------------------
--  Enable debug draw or disable. 
-- @function [parent=#NavMesh] setDebugDrawEnable 
-- @param self
-- @param #bool enable
-- @return NavMesh#NavMesh self (return value: cc.NavMesh)
        
--------------------------------
--  Internal method, the updater of debug drawing, need called each frame. 
-- @function [parent=#NavMesh] debugDraw 
-- @param self
-- @param #cc.Renderer renderer
-- @return NavMesh#NavMesh self (return value: cc.NavMesh)
        
--------------------------------
-- Create navmesh<br>
-- param navFilePath The NavMesh File path.<br>
-- param geomFilePath The geometry File Path,include offmesh information,etc.
-- @function [parent=#NavMesh] create 
-- @param self
-- @param #string navFilePath
-- @param #string geomFilePath
-- @return NavMesh#NavMesh ret (return value: cc.NavMesh)
        
--------------------------------
-- 
-- @function [parent=#NavMesh] NavMesh 
-- @param self
-- @return NavMesh#NavMesh self (return value: cc.NavMesh)
        
return nil
