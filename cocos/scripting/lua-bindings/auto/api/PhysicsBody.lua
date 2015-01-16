
--------------------------------
-- @module PhysicsBody
-- @extend Ref
-- @parent_module cc

--------------------------------
--  whether this physics body is affected by the physics world’s gravitational force. 
-- @function [parent=#PhysicsBody] isGravityEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  reset all the force applied to body. 
-- @function [parent=#PhysicsBody] resetForces 
-- @param self
        
--------------------------------
--  get the max of velocity 
-- @function [parent=#PhysicsBody] getVelocityLimit 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- set the group of body<br>
-- Collision groups let you specify an integral group index. You can have all fixtures with the same group index always collide (positive index) or never collide (negative index)<br>
-- it have high priority than bit masks
-- @function [parent=#PhysicsBody] setGroup 
-- @param self
-- @param #int group
        
--------------------------------
--  get the body mass. 
-- @function [parent=#PhysicsBody] getMass 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Return bitmask of first shape, if there is no shape in body, return default value.(0xFFFFFFFF) 
-- @function [parent=#PhysicsBody] getCollisionBitmask 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  set the body rotation offset 
-- @function [parent=#PhysicsBody] getRotationOffset 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  get the body rotation. 
-- @function [parent=#PhysicsBody] getRotation 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  get the body moment of inertia. 
-- @function [parent=#PhysicsBody] getMoment 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @overload self, vec2_table, vec2_table         
-- @overload self, vec2_table         
-- @function [parent=#PhysicsBody] applyImpulse
-- @param self
-- @param #vec2_table impulse
-- @param #vec2_table offset

--------------------------------
--  set body rotation offset, it's the rotation witch relative to node 
-- @function [parent=#PhysicsBody] setRotationOffset 
-- @param self
-- @param #float rotation
        
--------------------------------
-- @overload self, vec2_table, vec2_table         
-- @overload self, vec2_table         
-- @function [parent=#PhysicsBody] applyForce
-- @param self
-- @param #vec2_table force
-- @param #vec2_table offset

--------------------------------
-- 
-- @function [parent=#PhysicsBody] addShape 
-- @param self
-- @param #cc.PhysicsShape shape
-- @param #bool addMassAndMoment
-- @return PhysicsShape#PhysicsShape ret (return value: cc.PhysicsShape)
        
--------------------------------
--  Applies a torque force to body. 
-- @function [parent=#PhysicsBody] applyTorque 
-- @param self
-- @param #float torque
        
--------------------------------
--  get the max of angular velocity 
-- @function [parent=#PhysicsBody] getAngularVelocityLimit 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  set the max of angular velocity 
-- @function [parent=#PhysicsBody] setAngularVelocityLimit 
-- @param self
-- @param #float limit
        
--------------------------------
--  get the velocity of a body 
-- @function [parent=#PhysicsBody] getVelocity 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  get linear damping. 
-- @function [parent=#PhysicsBody] getLinearDamping 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#PhysicsBody] removeAllShapes 
-- @param self
        
--------------------------------
-- set angular damping.<br>
-- it is used to simulate fluid or air friction forces on the body.<br>
-- the value is 0.0f to 1.0f.
-- @function [parent=#PhysicsBody] setAngularDamping 
-- @param self
-- @param #float damping
        
--------------------------------
--  set the max of velocity 
-- @function [parent=#PhysicsBody] setVelocityLimit 
-- @param self
-- @param #float limit
        
--------------------------------
--  set body to rest 
-- @function [parent=#PhysicsBody] setResting 
-- @param self
-- @param #bool rest
        
--------------------------------
--  get body position offset. 
-- @function [parent=#PhysicsBody] getPositionOffset 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- A mask that defines which categories this physics body belongs to.<br>
-- Every physics body in a scene can be assigned to up to 32 different categories, each corresponding to a bit in the bit mask. You define the mask values used in your game. In conjunction with the collisionBitMask and contactTestBitMask properties, you define which physics bodies interact with each other and when your game is notified of these interactions.<br>
-- The default value is 0xFFFFFFFF (all bits set).
-- @function [parent=#PhysicsBody] setCategoryBitmask 
-- @param self
-- @param #int bitmask
        
--------------------------------
--  get the world body added to. 
-- @function [parent=#PhysicsBody] getWorld 
-- @param self
-- @return PhysicsWorld#PhysicsWorld ret (return value: cc.PhysicsWorld)
        
--------------------------------
--  get the angular velocity of a body 
-- @function [parent=#PhysicsBody] getAngularVelocity 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  get the body position. 
-- @function [parent=#PhysicsBody] getPosition 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- set the enable value.<br>
-- if the body it isn't enabled, it will not has simulation by world
-- @function [parent=#PhysicsBody] setEnable 
-- @param self
-- @param #bool enable
        
--------------------------------
--  set the body is affected by the physics world's gravitational force or not. 
-- @function [parent=#PhysicsBody] setGravityEnable 
-- @param self
-- @param #bool enable
        
--------------------------------
--  Return group of first shape, if there is no shape in body, return default value.(0) 
-- @function [parent=#PhysicsBody] getGroup 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- brief set the body moment of inertia.<br>
-- note if you need add/subtract moment to body, don't use setMoment(getMoment() +/- moment), because the moment of body may be equal to PHYSICS_INFINITY, it will cause some unexpected result, please use addMoment() instead.
-- @function [parent=#PhysicsBody] setMoment 
-- @param self
-- @param #float moment
        
--------------------------------
--  get the body's tag 
-- @function [parent=#PhysicsBody] getTag 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  convert the local point to world 
-- @function [parent=#PhysicsBody] local2World 
-- @param self
-- @param #vec2_table point
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Return bitmask of first shape, if there is no shape in body, return default value.(0xFFFFFFFF) 
-- @function [parent=#PhysicsBody] getCategoryBitmask 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- brief set dynamic to body.<br>
-- a dynamic body will effect with gravity.
-- @function [parent=#PhysicsBody] setDynamic 
-- @param self
-- @param #bool dynamic
        
--------------------------------
-- 
-- @function [parent=#PhysicsBody] getFirstShape 
-- @param self
-- @return PhysicsShape#PhysicsShape ret (return value: cc.PhysicsShape)
        
--------------------------------
-- 
-- @function [parent=#PhysicsBody] getShapes 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
--  Return bitmask of first shape, if there is no shape in body, return default value.(0x00000000) 
-- @function [parent=#PhysicsBody] getContactTestBitmask 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  set the angular velocity of a body 
-- @function [parent=#PhysicsBody] setAngularVelocity 
-- @param self
-- @param #float velocity
        
--------------------------------
--  convert the world point to local 
-- @function [parent=#PhysicsBody] world2Local 
-- @param self
-- @param #vec2_table point
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- whether the body is enabled<br>
-- if the body it isn't enabled, it will not has simulation by world
-- @function [parent=#PhysicsBody] isEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @overload self, int, bool         
-- @overload self, cc.PhysicsShape, bool         
-- @function [parent=#PhysicsBody] removeShape
-- @param self
-- @param #cc.PhysicsShape shape
-- @param #bool reduceMassAndMoment

--------------------------------
-- brief set the body mass.<br>
-- note if you need add/subtract mass to body, don't use setMass(getMass() +/- mass), because the mass of body may be equal to PHYSICS_INFINITY, it will cause some unexpected result, please use addMass() instead.
-- @function [parent=#PhysicsBody] setMass 
-- @param self
-- @param #float mass
        
--------------------------------
-- brief add moment of inertia to body.<br>
-- if _moment(moment of the body) == PHYSICS_INFINITY, it remains.<br>
-- if moment == PHYSICS_INFINITY, _moment will be PHYSICS_INFINITY.<br>
-- if moment == -PHYSICS_INFINITY, _moment will not change.<br>
-- if moment + _moment <= 0, _moment will equal to MASS_DEFAULT(1.0)<br>
-- other wise, moment = moment + _moment;
-- @function [parent=#PhysicsBody] addMoment 
-- @param self
-- @param #float moment
        
--------------------------------
--  set the velocity of a body 
-- @function [parent=#PhysicsBody] setVelocity 
-- @param self
-- @param #vec2_table velocity
        
--------------------------------
-- set linear damping.<br>
-- it is used to simulate fluid or air friction forces on the body. <br>
-- the value is 0.0f to 1.0f. 
-- @function [parent=#PhysicsBody] setLinearDamping 
-- @param self
-- @param #float damping
        
--------------------------------
-- A mask that defines which categories of physics bodies can collide with this physics body.<br>
-- When two physics bodies contact each other, a collision may occur. This body’s collision mask is compared to the other body’s category mask by performing a logical AND operation. If the result is a non-zero value, then this body is affected by the collision. Each body independently chooses whether it wants to be affected by the other body. For example, you might use this to avoid collision calculations that would make negligible changes to a body’s velocity.<br>
-- The default value is 0xFFFFFFFF (all bits set).
-- @function [parent=#PhysicsBody] setCollisionBitmask 
-- @param self
-- @param #int bitmask
        
--------------------------------
--  set body position offset, it's the position witch relative to node 
-- @function [parent=#PhysicsBody] setPositionOffset 
-- @param self
-- @param #vec2_table position
        
--------------------------------
--  set the body is allow rotation or not 
-- @function [parent=#PhysicsBody] setRotationEnable 
-- @param self
-- @param #bool enable
        
--------------------------------
--  whether the body can rotation 
-- @function [parent=#PhysicsBody] isRotationEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#PhysicsBody] getCPBody 
-- @param self
-- @return cpBody#cpBody ret (return value: cpBody)
        
--------------------------------
--  get angular damping. 
-- @function [parent=#PhysicsBody] getAngularDamping 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  get the angular velocity of a body at a local point 
-- @function [parent=#PhysicsBody] getVelocityAtLocalPoint 
-- @param self
-- @param #vec2_table point
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  whether the body is at rest 
-- @function [parent=#PhysicsBody] isResting 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief add mass to body.<br>
-- if _mass(mass of the body) == PHYSICS_INFINITY, it remains.<br>
-- if mass == PHYSICS_INFINITY, _mass will be PHYSICS_INFINITY.<br>
-- if mass == -PHYSICS_INFINITY, _mass will not change.<br>
-- if mass + _mass <= 0, _mass will equal to MASS_DEFAULT(1.0)<br>
-- other wise, mass = mass + _mass;
-- @function [parent=#PhysicsBody] addMass 
-- @param self
-- @param #float mass
        
--------------------------------
-- 
-- @function [parent=#PhysicsBody] getShape 
-- @param self
-- @param #int tag
-- @return PhysicsShape#PhysicsShape ret (return value: cc.PhysicsShape)
        
--------------------------------
--  set the body's tag 
-- @function [parent=#PhysicsBody] setTag 
-- @param self
-- @param #int tag
        
--------------------------------
--  get the angular velocity of a body at a world point 
-- @function [parent=#PhysicsBody] getVelocityAtWorldPoint 
-- @param self
-- @param #vec2_table point
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- A mask that defines which categories of bodies cause intersection notifications with this physics body.<br>
-- When two bodies share the same space, each body’s category mask is tested against the other body’s contact mask by performing a logical AND operation. If either comparison results in a non-zero value, an PhysicsContact object is created and passed to the physics world’s delegate. For best performance, only set bits in the contacts mask for interactions you are interested in.<br>
-- The default value is 0x00000000 (all bits cleared).
-- @function [parent=#PhysicsBody] setContactTestBitmask 
-- @param self
-- @param #int bitmask
        
--------------------------------
--  remove the body from the world it added to 
-- @function [parent=#PhysicsBody] removeFromWorld 
-- @param self
        
--------------------------------
-- brief test the body is dynamic or not.<br>
-- a dynamic body will effect with gravity.
-- @function [parent=#PhysicsBody] isDynamic 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  get the sprite the body set to. 
-- @function [parent=#PhysicsBody] getNode 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
--  Create a body contains a box shape. 
-- @function [parent=#PhysicsBody] createBox 
-- @param self
-- @param #size_table size
-- @param #cc.PhysicsMaterial material
-- @param #vec2_table offset
-- @return PhysicsBody#PhysicsBody ret (return value: cc.PhysicsBody)
        
--------------------------------
--  Create a body contains a EdgeSegment shape. 
-- @function [parent=#PhysicsBody] createEdgeSegment 
-- @param self
-- @param #vec2_table a
-- @param #vec2_table b
-- @param #cc.PhysicsMaterial material
-- @param #float border
-- @return PhysicsBody#PhysicsBody ret (return value: cc.PhysicsBody)
        
--------------------------------
-- @overload self, float         
-- @overload self         
-- @overload self, float, float         
-- @function [parent=#PhysicsBody] create
-- @param self
-- @param #float mass
-- @param #float moment
-- @return PhysicsBody#PhysicsBody ret (return value: cc.PhysicsBody)

--------------------------------
--  Create a body contains a EdgeBox shape. 
-- @function [parent=#PhysicsBody] createEdgeBox 
-- @param self
-- @param #size_table size
-- @param #cc.PhysicsMaterial material
-- @param #float border
-- @param #vec2_table offset
-- @return PhysicsBody#PhysicsBody ret (return value: cc.PhysicsBody)
        
--------------------------------
--  Create a body contains a circle shape. 
-- @function [parent=#PhysicsBody] createCircle 
-- @param self
-- @param #float radius
-- @param #cc.PhysicsMaterial material
-- @param #vec2_table offset
-- @return PhysicsBody#PhysicsBody ret (return value: cc.PhysicsBody)
        
return nil
