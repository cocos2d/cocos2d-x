
--------------------------------
-- @module Physics3DComponent
-- @extend Component
-- @parent_module cc

--------------------------------
-- add this component to physics world, called by scene
-- @function [parent=#Physics3DComponent] addToPhysicsWorld 
-- @param self
-- @param #cc.Physics3DWorld world
-- @return Physics3DComponent#Physics3DComponent self (return value: cc.Physics3DComponent)
        
--------------------------------
-- align node and physics according to physics object
-- @function [parent=#Physics3DComponent] syncToPhysics 
-- @param self
-- @return Physics3DComponent#Physics3DComponent self (return value: cc.Physics3DComponent)
        
--------------------------------
-- align node and physics according to node
-- @function [parent=#Physics3DComponent] syncToNode 
-- @param self
-- @return Physics3DComponent#Physics3DComponent self (return value: cc.Physics3DComponent)
        
--------------------------------
-- get physics object
-- @function [parent=#Physics3DComponent] getPhysics3DObject 
-- @param self
-- @return Physics3DObject#Physics3DObject ret (return value: cc.Physics3DObject)
        
--------------------------------
-- set Physics object to the component
-- @function [parent=#Physics3DComponent] setPhysics3DObject 
-- @param self
-- @param #cc.Physics3DObject physicsObj
-- @return Physics3DComponent#Physics3DComponent self (return value: cc.Physics3DComponent)
        
--------------------------------
-- synchronization between node and physics is time consuming, you can skip some synchronization using this function
-- @function [parent=#Physics3DComponent] setSyncFlag 
-- @param self
-- @param #int syncFlag
-- @return Physics3DComponent#Physics3DComponent self (return value: cc.Physics3DComponent)
        
--------------------------------
-- get the component name, it is used to find whether it is Physics3DComponent
-- @function [parent=#Physics3DComponent] getPhysics3DComponentName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- set it enable or not
-- @function [parent=#Physics3DComponent] setEnabled 
-- @param self
-- @param #bool b
-- @return Physics3DComponent#Physics3DComponent self (return value: cc.Physics3DComponent)
        
--------------------------------
-- 
-- @function [parent=#Physics3DComponent] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Physics3DComponent] onEnter 
-- @param self
-- @return Physics3DComponent#Physics3DComponent self (return value: cc.Physics3DComponent)
        
--------------------------------
-- 
-- @function [parent=#Physics3DComponent] onExit 
-- @param self
-- @return Physics3DComponent#Physics3DComponent self (return value: cc.Physics3DComponent)
        
--------------------------------
-- 
-- @function [parent=#Physics3DComponent] Physics3DComponent 
-- @param self
-- @return Physics3DComponent#Physics3DComponent self (return value: cc.Physics3DComponent)
        
return nil
