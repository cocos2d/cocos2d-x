
--------------------------------
-- @module MotionStreak
-- @extend Node,TextureProtocol
-- @parent_module cc

--------------------------------
-- @function [parent=#MotionStreak] reset 
-- @param self
        
--------------------------------
-- @function [parent=#MotionStreak] setTexture 
-- @param self
-- @param #cc.Texture2D texture2d
        
--------------------------------
-- @function [parent=#MotionStreak] getTexture 
-- @param self
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)
        
--------------------------------
-- @function [parent=#MotionStreak] tintWithColor 
-- @param self
-- @param #color3b_table color3b
        
--------------------------------
-- @function [parent=#MotionStreak] setStartingPositionInitialized 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#MotionStreak] isStartingPositionInitialized 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#MotionStreak] isFastMode 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#MotionStreak] setFastMode 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @overload self, float, float, float, color3b_table, cc.Texture2D         
-- @overload self, float, float, float, color3b_table, string         
-- @function [parent=#MotionStreak] create
-- @param self
-- @param #float float
-- @param #float float
-- @param #float float
-- @param #color3b_table color3b
-- @param #string str
-- @return MotionStreak#MotionStreak ret (retunr value: cc.MotionStreak)

--------------------------------
-- @function [parent=#MotionStreak] isOpacityModifyRGB 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#MotionStreak] setPositionY 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#MotionStreak] setPositionX 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#MotionStreak] getPositionY 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#MotionStreak] getPositionX 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#MotionStreak] setOpacity 
-- @param self
-- @param #unsigned char char
        
--------------------------------
-- @function [parent=#MotionStreak] setOpacityModifyRGB 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#MotionStreak] getOpacity 
-- @param self
-- @return unsigned char#unsigned char ret (return value: unsigned char)
        
--------------------------------
-- @overload self, float, float         
-- @overload self, vec2_table         
-- @function [parent=#MotionStreak] setPosition
-- @param self
-- @param #float float
-- @param #float float

--------------------------------
-- @overload self, float, float         
-- @overload self         
-- @function [parent=#MotionStreak] getPosition
-- @param self
-- @param #float float
-- @param #float float

return nil
