
--------------------------------
-- @module ColliderManager
-- @extend Node
-- @parent_module creator

--------------------------------
--  Register/unregister a callback. `key` is used to unregister because can not compare std::function<>.
-- @function [parent=#ColliderManager] registerCollitionCallback 
-- @param self
-- @param #function callback
-- @param #string key
-- @return ColliderManager#ColliderManager self (return value: creator.ColliderManager)
        
--------------------------------
-- 
-- @function [parent=#ColliderManager] unregisterCollisionCallback 
-- @param self
-- @param #function callback
-- @param #string key
-- @return ColliderManager#ColliderManager self (return value: creator.ColliderManager)
        
--------------------------------
-- 
-- @function [parent=#ColliderManager] isDebugDrawEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ColliderManager] enableDebugDraw 
-- @param self
-- @param #bool enabled
-- @return ColliderManager#ColliderManager self (return value: creator.ColliderManager)
        
--------------------------------
-- 
-- @function [parent=#ColliderManager] enableAABBDebugDraw 
-- @param self
-- @param #bool value
-- @return ColliderManager#ColliderManager self (return value: creator.ColliderManager)
        
--------------------------------
-- 
-- @function [parent=#ColliderManager] removeCollider 
-- @param self
-- @param #creator.Collider collider
-- @return ColliderManager#ColliderManager self (return value: creator.ColliderManager)
        
--------------------------------
-- 
-- @function [parent=#ColliderManager] isAABBDebugDrawEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
return nil
