
--------------------------------
-- @module PhysicsBody
-- @extend Ref
-- @parent_module cc

--------------------------------
-- @function [parent=#PhysicsBody] isGravityEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#PhysicsBody] resetForces 
-- @param self
        
--------------------------------
-- @function [parent=#PhysicsBody] getVelocityLimit 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#PhysicsBody] setGroup 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#PhysicsBody] getMass 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#PhysicsBody] getCollisionBitmask 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#PhysicsBody] getRotationOffset 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#PhysicsBody] getRotation 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#PhysicsBody] getMoment 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- overload function: applyImpulse(vec2_table, vec2_table)
--          
-- overload function: applyImpulse(vec2_table)
--          
-- @function [parent=#PhysicsBody] applyImpulse
-- @param self
-- @param #vec2_table vec2
-- @param #vec2_table vec2

--------------------------------
-- @function [parent=#PhysicsBody] setRotationOffset 
-- @param self
-- @param #float float
        
--------------------------------
-- overload function: applyForce(vec2_table, vec2_table)
--          
-- overload function: applyForce(vec2_table)
--          
-- @function [parent=#PhysicsBody] applyForce
-- @param self
-- @param #vec2_table vec2
-- @param #vec2_table vec2

--------------------------------
-- @function [parent=#PhysicsBody] addShape 
-- @param self
-- @param #cc.PhysicsShape physicsshape
-- @param #bool bool
-- @return PhysicsShape#PhysicsShape ret (return value: cc.PhysicsShape)
        
--------------------------------
-- @function [parent=#PhysicsBody] applyTorque 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#PhysicsBody] getAngularVelocityLimit 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#PhysicsBody] setAngularVelocityLimit 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#PhysicsBody] getVelocity 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#PhysicsBody] getLinearDamping 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#PhysicsBody] removeAllShapes 
-- @param self
        
--------------------------------
-- @function [parent=#PhysicsBody] setAngularDamping 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#PhysicsBody] setVelocityLimit 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#PhysicsBody] setResting 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#PhysicsBody] getPositionOffset 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#PhysicsBody] setCategoryBitmask 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#PhysicsBody] getWorld 
-- @param self
-- @return PhysicsWorld#PhysicsWorld ret (return value: cc.PhysicsWorld)
        
--------------------------------
-- @function [parent=#PhysicsBody] getAngularVelocity 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#PhysicsBody] getPosition 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#PhysicsBody] setEnable 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#PhysicsBody] setGravityEnable 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#PhysicsBody] getGroup 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#PhysicsBody] setMoment 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#PhysicsBody] getTag 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#PhysicsBody] local2World 
-- @param self
-- @param #vec2_table vec2
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#PhysicsBody] getCategoryBitmask 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#PhysicsBody] setDynamic 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#PhysicsBody] getFirstShape 
-- @param self
-- @return PhysicsShape#PhysicsShape ret (return value: cc.PhysicsShape)
        
--------------------------------
-- @function [parent=#PhysicsBody] getShapes 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- @function [parent=#PhysicsBody] getContactTestBitmask 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#PhysicsBody] setAngularVelocity 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#PhysicsBody] world2Local 
-- @param self
-- @param #vec2_table vec2
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#PhysicsBody] isEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- overload function: removeShape(int, bool)
--          
-- overload function: removeShape(cc.PhysicsShape, bool)
--          
-- @function [parent=#PhysicsBody] removeShape
-- @param self
-- @param #cc.PhysicsShape physicsshape
-- @param #bool bool

--------------------------------
-- @function [parent=#PhysicsBody] setMass 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#PhysicsBody] addMoment 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#PhysicsBody] setVelocity 
-- @param self
-- @param #vec2_table vec2
        
--------------------------------
-- @function [parent=#PhysicsBody] setLinearDamping 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#PhysicsBody] setCollisionBitmask 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#PhysicsBody] setPositionOffset 
-- @param self
-- @param #vec2_table vec2
        
--------------------------------
-- @function [parent=#PhysicsBody] setRotationEnable 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#PhysicsBody] isRotationEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#PhysicsBody] getAngularDamping 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#PhysicsBody] getVelocityAtLocalPoint 
-- @param self
-- @param #vec2_table vec2
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#PhysicsBody] isResting 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#PhysicsBody] addMass 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#PhysicsBody] getShape 
-- @param self
-- @param #int int
-- @return PhysicsShape#PhysicsShape ret (return value: cc.PhysicsShape)
        
--------------------------------
-- @function [parent=#PhysicsBody] setTag 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#PhysicsBody] getVelocityAtWorldPoint 
-- @param self
-- @param #vec2_table vec2
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#PhysicsBody] setContactTestBitmask 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#PhysicsBody] removeFromWorld 
-- @param self
        
--------------------------------
-- @function [parent=#PhysicsBody] isDynamic 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#PhysicsBody] getNode 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- @function [parent=#PhysicsBody] createBox 
-- @param self
-- @param #size_table size
-- @param #cc.PhysicsMaterial physicsmaterial
-- @param #vec2_table vec2
-- @return PhysicsBody#PhysicsBody ret (return value: cc.PhysicsBody)
        
--------------------------------
-- @function [parent=#PhysicsBody] createEdgeSegment 
-- @param self
-- @param #vec2_table vec2
-- @param #vec2_table vec2
-- @param #cc.PhysicsMaterial physicsmaterial
-- @param #float float
-- @return PhysicsBody#PhysicsBody ret (return value: cc.PhysicsBody)
        
--------------------------------
-- overload function: create(float)
--          
-- overload function: create()
--          
-- overload function: create(float, float)
--          
-- @function [parent=#PhysicsBody] create
-- @param self
-- @param #float float
-- @param #float float
-- @return PhysicsBody#PhysicsBody ret (retunr value: cc.PhysicsBody)

--------------------------------
-- @function [parent=#PhysicsBody] createEdgeBox 
-- @param self
-- @param #size_table size
-- @param #cc.PhysicsMaterial physicsmaterial
-- @param #float float
-- @param #vec2_table vec2
-- @return PhysicsBody#PhysicsBody ret (return value: cc.PhysicsBody)
        
--------------------------------
-- @function [parent=#PhysicsBody] createCircle 
-- @param self
-- @param #float float
-- @param #cc.PhysicsMaterial physicsmaterial
-- @param #vec2_table vec2
-- @return PhysicsBody#PhysicsBody ret (return value: cc.PhysicsBody)
        
return nil
