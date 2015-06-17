
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
-- @overload self, string, string, string, string, string, string         
-- @overload self         
-- @function [parent=#Skybox] init
-- @param self
-- @param #string positive_x
-- @param #string negative_x
-- @param #string positive_y
-- @param #string negative_y
-- @param #string positive_z
-- @param #string negative_z
-- @return bool#bool ret (return value: bool)

--------------------------------
-- texture getter and setter
-- @function [parent=#Skybox] setTexture 
-- @param self
-- @param #cc.TextureCube 
-- @return Skybox#Skybox self (return value: cc.Skybox)
        
--------------------------------
-- @overload self, string, string, string, string, string, string         
-- @overload self         
-- @function [parent=#Skybox] create
-- @param self
-- @param #string positive_x
-- @param #string negative_x
-- @param #string positive_y
-- @param #string negative_y
-- @param #string positive_z
-- @param #string negative_z
-- @return Skybox#Skybox ret (return value: cc.Skybox)

--------------------------------
--  draw Skybox object 
-- @function [parent=#Skybox] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
-- @return Skybox#Skybox self (return value: cc.Skybox)
        
--------------------------------
-- Constructor.
-- @function [parent=#Skybox] Skybox 
-- @param self
-- @return Skybox#Skybox self (return value: cc.Skybox)
        
return nil
