
--------------------------------
-- @module Skybox
-- @extend Node
-- @parent_module cc

--------------------------------
--  reload sky box after GLESContext reconstructed.
-- @function [parent=#Skybox] reload 
-- @param self
-- @return Skybox#Skybox self (return value: cc.Skybox)
        
--------------------------------
-- texture getter and setter
-- @function [parent=#Skybox] setTexture 
-- @param self
-- @param #cc.TextureCube 
-- @return Skybox#Skybox self (return value: cc.Skybox)
        
--------------------------------
-- 
-- @function [parent=#Skybox] create 
-- @param self
-- @return Skybox#Skybox ret (return value: cc.Skybox)
        
--------------------------------
--  draw Skybox object 
-- @function [parent=#Skybox] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
-- @return Skybox#Skybox self (return value: cc.Skybox)
        
return nil
