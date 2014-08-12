
--------------------------------
-- @module Skin
-- @extend Sprite
-- @parent_module ccs

--------------------------------
-- @function [parent=#Skin] getBone 
-- @param self
-- @return Bone#Bone ret (return value: ccs.Bone)
        
--------------------------------
-- @function [parent=#Skin] getNodeToWorldTransformAR 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- @function [parent=#Skin] initWithFile 
-- @param self
-- @param #string str
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Skin] getDisplayName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#Skin] updateArmatureTransform 
-- @param self
        
--------------------------------
-- @function [parent=#Skin] initWithSpriteFrameName 
-- @param self
-- @param #string str
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Skin] setBone 
-- @param self
-- @param #ccs.Bone bone
        
--------------------------------
-- @overload self, string         
-- @overload self         
-- @function [parent=#Skin] create
-- @param self
-- @param #string str
-- @return Skin#Skin ret (retunr value: ccs.Skin)

--------------------------------
-- @function [parent=#Skin] createWithSpriteFrameName 
-- @param self
-- @param #string str
-- @return Skin#Skin ret (return value: ccs.Skin)
        
--------------------------------
-- @function [parent=#Skin] updateTransform 
-- @param self
        
--------------------------------
-- @function [parent=#Skin] getNodeToWorldTransform 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- @function [parent=#Skin] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table mat4
-- @param #unsigned int int
        
--------------------------------
-- @function [parent=#Skin] Skin 
-- @param self
        
return nil
