
--------------------------------
-- @module ComponentPhysics2d
-- @extend Component
-- @parent_module cc

--------------------------------
-- Set physics body of this physics component. If the physics body is set to<br>
-- another physics component before, will set another physics component's physics<br>
-- body to null.<br>
-- param physicsBody The physics body belongs to this component.
-- @function [parent=#ComponentPhysics2d] setPhysicsBody 
-- @param self
-- @param #cc.PhysicsBody physicsBody
-- @return ComponentPhysics2d#ComponentPhysics2d self (return value: cc.ComponentPhysics2d)
        
--------------------------------
-- Get the physics body of this component.<br>
-- return The physics body of this component.
-- @function [parent=#ComponentPhysics2d] getPhysicsBody 
-- @param self
-- @return PhysicsBody#PhysicsBody ret (return value: cc.PhysicsBody)
        
--------------------------------
-- @overload self, cc.PhysicsBody         
-- @overload self         
-- @function [parent=#ComponentPhysics2d] create
-- @param self
-- @param #cc.PhysicsBody physicsBody
-- @return ComponentPhysics2d#ComponentPhysics2d ret (return value: cc.ComponentPhysics2d)

--------------------------------
-- 
-- @function [parent=#ComponentPhysics2d] setEnabled 
-- @param self
-- @param #bool value
-- @return ComponentPhysics2d#ComponentPhysics2d self (return value: cc.ComponentPhysics2d)
        
--------------------------------
-- 
-- @function [parent=#ComponentPhysics2d] onRemove 
-- @param self
-- @return ComponentPhysics2d#ComponentPhysics2d self (return value: cc.ComponentPhysics2d)
        
--------------------------------
-- 
-- @function [parent=#ComponentPhysics2d] onEnter 
-- @param self
-- @return ComponentPhysics2d#ComponentPhysics2d self (return value: cc.ComponentPhysics2d)
        
--------------------------------
-- 
-- @function [parent=#ComponentPhysics2d] onExit 
-- @param self
-- @return ComponentPhysics2d#ComponentPhysics2d self (return value: cc.ComponentPhysics2d)
        
--------------------------------
-- 
-- @function [parent=#ComponentPhysics2d] onAdd 
-- @param self
-- @return ComponentPhysics2d#ComponentPhysics2d self (return value: cc.ComponentPhysics2d)
        
--------------------------------
-- @overload self, cc.PhysicsBody         
-- @overload self         
-- @function [parent=#ComponentPhysics2d] ComponentPhysics2d
-- @param self
-- @param #cc.PhysicsBody phsicsBody
-- @return ComponentPhysics2d#ComponentPhysics2d self (return value: cc.ComponentPhysics2d)

return nil
