
--------------------------------
-- @module PhysicsShape
-- @extend Ref
-- @parent_module cc

--------------------------------
-- Get this shape's friction.<br>
-- return A float number.
-- @function [parent=#PhysicsShape] getFriction 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Set the group of body.<br>
-- Collision groups let you specify an integral group index. You can have all fixtures with the same group index always collide (positive index) or never collide (negative index).<br>
-- param group An interger number, it have high priority than bit masks.
-- @function [parent=#PhysicsShape] setGroup 
-- @param self
-- @param #int group
-- @return PhysicsShape#PhysicsShape self (return value: cc.PhysicsShape)
        
--------------------------------
-- Set this shape's density.<br>
-- It will change the body's mass this shape attaches.<br>
-- param density A float number.
-- @function [parent=#PhysicsShape] setDensity 
-- @param self
-- @param #float density
-- @return PhysicsShape#PhysicsShape self (return value: cc.PhysicsShape)
        
--------------------------------
-- Get the mass of this shape.<br>
-- return A float number.
-- @function [parent=#PhysicsShape] getMass 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Get this shape's PhysicsMaterial object.<br>
-- return A PhysicsMaterial object reference.
-- @function [parent=#PhysicsShape] getMaterial 
-- @param self
-- @return PhysicsMaterial#PhysicsMaterial ret (return value: cc.PhysicsMaterial)
        
--------------------------------
-- 
-- @function [parent=#PhysicsShape] setSensor 
-- @param self
-- @param #bool sensor
-- @return PhysicsShape#PhysicsShape self (return value: cc.PhysicsShape)
        
--------------------------------
-- Get a mask that defines which categories of physics bodies can collide with this physics body.<br>
-- return An interger number.
-- @function [parent=#PhysicsShape] getCollisionBitmask 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Return this shape's area.<br>
-- return A float number.
-- @function [parent=#PhysicsShape] getArea 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Set a mask that defines which categories this physics body belongs to.<br>
-- Every physics body in a scene can be assigned to up to 32 different categories, each corresponding to a bit in the bit mask. You define the mask values used in your game. In conjunction with the collisionBitMask and contactTestBitMask properties, you define which physics bodies interact with each other and when your game is notified of these interactions.<br>
-- param bitmask An interger number, the default value is 0xFFFFFFFF (all bits set).
-- @function [parent=#PhysicsShape] setCategoryBitmask 
-- @param self
-- @param #int bitmask
-- @return PhysicsShape#PhysicsShape self (return value: cc.PhysicsShape)
        
--------------------------------
-- Get the group of body.<br>
-- return An interger number.
-- @function [parent=#PhysicsShape] getGroup 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Set this shape's moment.<br>
-- It will change the body's moment this shape attaches.<br>
-- param moment A float number.
-- @function [parent=#PhysicsShape] setMoment 
-- @param self
-- @param #float moment
-- @return PhysicsShape#PhysicsShape self (return value: cc.PhysicsShape)
        
--------------------------------
-- Test point is inside this shape or not.<br>
-- param point A Vec2 object.<br>
-- return A bool object.
-- @function [parent=#PhysicsShape] containsPoint 
-- @param self
-- @param #vec2_table point
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Get a mask that defines which categories this physics body belongs to.<br>
-- return An interger number.
-- @function [parent=#PhysicsShape] getCategoryBitmask 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#PhysicsShape] isSensor 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Return this shape's type.<br>
-- return A Type object.
-- @function [parent=#PhysicsShape] getType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Get a mask that defines which categories of bodies cause intersection notifications with this physics body.<br>
-- return An interger number.
-- @function [parent=#PhysicsShape] getContactTestBitmask 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Get this shape's center position.<br>
-- This function should be overrided in inherit classes.<br>
-- return A Vec2 object.
-- @function [parent=#PhysicsShape] getCenter 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Get this shape's density.<br>
-- return A float number.
-- @function [parent=#PhysicsShape] getDensity 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Set this shape's mass.<br>
-- It will change the body's mass this shape attaches.<br>
-- param mass A float number.
-- @function [parent=#PhysicsShape] setMass 
-- @param self
-- @param #float mass
-- @return PhysicsShape#PhysicsShape self (return value: cc.PhysicsShape)
        
--------------------------------
-- Get this shape's tag.<br>
-- return An interger number.
-- @function [parent=#PhysicsShape] getTag 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Calculate the default moment value.<br>
-- This function should be overrided in inherit classes.<br>
-- return A float number, equals 0.0.
-- @function [parent=#PhysicsShape] calculateDefaultMoment 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- A mask that defines which categories of physics bodies can collide with this physics body.<br>
-- When two physics bodies contact each other, a collision may occur. This body’s collision mask is compared to the other body’s category mask by performing a logical AND operation. If the result is a non-zero value, then this body is affected by the collision. Each body independently chooses whether it wants to be affected by the other body. For example, you might use this to avoid collision calculations that would make negligible changes to a body’s velocity.<br>
-- param bitmask An interger number, the default value is 0xFFFFFFFF (all bits set).
-- @function [parent=#PhysicsShape] setCollisionBitmask 
-- @param self
-- @param #int bitmask
-- @return PhysicsShape#PhysicsShape self (return value: cc.PhysicsShape)
        
--------------------------------
-- Get this shape's moment.<br>
-- return A float number.
-- @function [parent=#PhysicsShape] getMoment 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Get this shape's position offset.<br>
-- This function should be overrided in inherit classes.<br>
-- return A Vec2 object.
-- @function [parent=#PhysicsShape] getOffset 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Get this shape's restitution.<br>
-- return A float number.
-- @function [parent=#PhysicsShape] getRestitution 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Set this shape's friction.<br>
-- It will change the shape's friction.<br>
-- param friction A float number.
-- @function [parent=#PhysicsShape] setFriction 
-- @param self
-- @param #float friction
-- @return PhysicsShape#PhysicsShape self (return value: cc.PhysicsShape)
        
--------------------------------
-- Set this shape's material.<br>
-- It will change the shape's mass, elasticity and friction.<br>
-- param material A PhysicsMaterial object.
-- @function [parent=#PhysicsShape] setMaterial 
-- @param self
-- @param #cc.PhysicsMaterial material
-- @return PhysicsShape#PhysicsShape self (return value: cc.PhysicsShape)
        
--------------------------------
-- Set this shape's tag.<br>
-- param tag An interger number that identifies a shape object.
-- @function [parent=#PhysicsShape] setTag 
-- @param self
-- @param #int tag
-- @return PhysicsShape#PhysicsShape self (return value: cc.PhysicsShape)
        
--------------------------------
-- A mask that defines which categories of bodies cause intersection notifications with this physics body.<br>
-- When two bodies share the same space, each body’s category mask is tested against the other body’s contact mask by performing a logical AND operation. If either comparison results in a non-zero value, an PhysicsContact object is created and passed to the physics world’s delegate. For best performance, only set bits in the contacts mask for interactions you are interested in.<br>
-- param bitmask An interger number, the default value is 0x00000000 (all bits cleared).
-- @function [parent=#PhysicsShape] setContactTestBitmask 
-- @param self
-- @param #int bitmask
-- @return PhysicsShape#PhysicsShape self (return value: cc.PhysicsShape)
        
--------------------------------
-- Set this shape's restitution.<br>
-- It will change the shape's elasticity.<br>
-- param restitution A float number.
-- @function [parent=#PhysicsShape] setRestitution 
-- @param self
-- @param #float restitution
-- @return PhysicsShape#PhysicsShape self (return value: cc.PhysicsShape)
        
--------------------------------
-- Get the body that this shape attaches.<br>
-- return A PhysicsBody object pointer.
-- @function [parent=#PhysicsShape] getBody 
-- @param self
-- @return PhysicsBody#PhysicsBody ret (return value: cc.PhysicsBody)
        
return nil
