
--------------------------------
-- @module PhysicsShape
-- @extend Ref
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#PhysicsShape] getFriction 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- set the group of body<br>
-- Collision groups let you specify an integral group index. You can have all fixtures with the same group index always collide (positive index) or never collide (negative index)<br>
-- it have high priority than bit masks
-- @function [parent=#PhysicsShape] setGroup 
-- @param self
-- @param #int group
-- @return PhysicsShape#PhysicsShape self (return value: cc.PhysicsShape)
        
--------------------------------
-- 
-- @function [parent=#PhysicsShape] setDensity 
-- @param self
-- @param #float density
-- @return PhysicsShape#PhysicsShape self (return value: cc.PhysicsShape)
        
--------------------------------
--  get mass 
-- @function [parent=#PhysicsShape] getMass 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#PhysicsShape] getMaterial 
-- @param self
-- @return PhysicsMaterial#PhysicsMaterial ret (return value: cc.PhysicsMaterial)
        
--------------------------------
-- 
-- @function [parent=#PhysicsShape] getCollisionBitmask 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  return the area of this shape 
-- @function [parent=#PhysicsShape] getArea 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- A mask that defines which categories this physics body belongs to.<br>
-- Every physics body in a scene can be assigned to up to 32 different categories, each corresponding to a bit in the bit mask. You define the mask values used in your game. In conjunction with the collisionBitMask and contactTestBitMask properties, you define which physics bodies interact with each other and when your game is notified of these interactions.<br>
-- The default value is 0xFFFFFFFF (all bits set).
-- @function [parent=#PhysicsShape] setCategoryBitmask 
-- @param self
-- @param #int bitmask
-- @return PhysicsShape#PhysicsShape self (return value: cc.PhysicsShape)
        
--------------------------------
-- 
-- @function [parent=#PhysicsShape] getGroup 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Set moment, it will change the body's moment this shape attaches 
-- @function [parent=#PhysicsShape] setMoment 
-- @param self
-- @param #float moment
-- @return PhysicsShape#PhysicsShape self (return value: cc.PhysicsShape)
        
--------------------------------
--  Test point is in shape or not 
-- @function [parent=#PhysicsShape] containsPoint 
-- @param self
-- @param #vec2_table point
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#PhysicsShape] getCategoryBitmask 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Return the type of this shape 
-- @function [parent=#PhysicsShape] getType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#PhysicsShape] getContactTestBitmask 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Get center of this shape 
-- @function [parent=#PhysicsShape] getCenter 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
-- @function [parent=#PhysicsShape] getDensity 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Set mass, it will change the body's mass this shape attaches 
-- @function [parent=#PhysicsShape] setMass 
-- @param self
-- @param #float mass
-- @return PhysicsShape#PhysicsShape self (return value: cc.PhysicsShape)
        
--------------------------------
-- 
-- @function [parent=#PhysicsShape] getTag 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Calculate the default moment value 
-- @function [parent=#PhysicsShape] calculateDefaultMoment 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- A mask that defines which categories of physics bodies can collide with this physics body.<br>
-- When two physics bodies contact each other, a collision may occur. This body’s collision mask is compared to the other body’s category mask by performing a logical AND operation. If the result is a non-zero value, then this body is affected by the collision. Each body independently chooses whether it wants to be affected by the other body. For example, you might use this to avoid collision calculations that would make negligible changes to a body’s velocity.<br>
-- The default value is 0xFFFFFFFF (all bits set).
-- @function [parent=#PhysicsShape] setCollisionBitmask 
-- @param self
-- @param #int bitmask
-- @return PhysicsShape#PhysicsShape self (return value: cc.PhysicsShape)
        
--------------------------------
--  get moment 
-- @function [parent=#PhysicsShape] getMoment 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Get offset 
-- @function [parent=#PhysicsShape] getOffset 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
-- @function [parent=#PhysicsShape] getRestitution 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#PhysicsShape] setFriction 
-- @param self
-- @param #float friction
-- @return PhysicsShape#PhysicsShape self (return value: cc.PhysicsShape)
        
--------------------------------
-- 
-- @function [parent=#PhysicsShape] setMaterial 
-- @param self
-- @param #cc.PhysicsMaterial material
-- @return PhysicsShape#PhysicsShape self (return value: cc.PhysicsShape)
        
--------------------------------
-- 
-- @function [parent=#PhysicsShape] setTag 
-- @param self
-- @param #int tag
-- @return PhysicsShape#PhysicsShape self (return value: cc.PhysicsShape)
        
--------------------------------
-- A mask that defines which categories of bodies cause intersection notifications with this physics body.<br>
-- When two bodies share the same space, each body’s category mask is tested against the other body’s contact mask by performing a logical AND operation. If either comparison results in a non-zero value, an PhysicsContact object is created and passed to the physics world’s delegate. For best performance, only set bits in the contacts mask for interactions you are interested in.<br>
-- The default value is 0x00000000 (all bits cleared).
-- @function [parent=#PhysicsShape] setContactTestBitmask 
-- @param self
-- @param #int bitmask
-- @return PhysicsShape#PhysicsShape self (return value: cc.PhysicsShape)
        
--------------------------------
-- 
-- @function [parent=#PhysicsShape] setRestitution 
-- @param self
-- @param #float restitution
-- @return PhysicsShape#PhysicsShape self (return value: cc.PhysicsShape)
        
--------------------------------
--  Get the body that this shape attaches 
-- @function [parent=#PhysicsShape] getBody 
-- @param self
-- @return PhysicsBody#PhysicsBody ret (return value: cc.PhysicsBody)
        
return nil
