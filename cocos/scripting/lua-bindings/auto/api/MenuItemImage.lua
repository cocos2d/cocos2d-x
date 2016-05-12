
--------------------------------
-- @module MenuItemImage
-- @extend MenuItemSprite
-- @parent_module cc

--------------------------------
--  Sets the sprite frame for the disabled image. 
-- @function [parent=#MenuItemImage] setDisabledSpriteFrame 
-- @param self
-- @param #cc.SpriteFrame frame
-- @return MenuItemImage#MenuItemImage self (return value: cc.MenuItemImage)
        
--------------------------------
--  Sets the sprite frame for the selected image. 
-- @function [parent=#MenuItemImage] setSelectedSpriteFrame 
-- @param self
-- @param #cc.SpriteFrame frame
-- @return MenuItemImage#MenuItemImage self (return value: cc.MenuItemImage)
        
--------------------------------
--  Sets the sprite frame for the normal image. 
-- @function [parent=#MenuItemImage] setNormalSpriteFrame 
-- @param self
-- @param #cc.SpriteFrame frame
-- @return MenuItemImage#MenuItemImage self (return value: cc.MenuItemImage)
        
--------------------------------
-- 
-- @function [parent=#MenuItemImage] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Initializes a menu item with a normal, selected and disabled image with a callable object. 
-- @function [parent=#MenuItemImage] initWithNormalImage 
-- @param self
-- @param #string normalImage
-- @param #string selectedImage
-- @param #string disabledImage
-- @param #function callback
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- js ctor
-- @function [parent=#MenuItemImage] MenuItemImage 
-- @param self
-- @return MenuItemImage#MenuItemImage self (return value: cc.MenuItemImage)
        
return nil
