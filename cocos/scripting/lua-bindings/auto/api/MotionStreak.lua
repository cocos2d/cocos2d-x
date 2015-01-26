
--------------------------------
-- @module MotionStreak
-- @extend Node,TextureProtocol
-- @parent_module cc

--------------------------------
--  Remove all living segments of the ribbon 
-- @function [parent=#MotionStreak] reset 
-- @param self
-- @return MotionStreak#MotionStreak self (return value: cc.MotionStreak)
        
--------------------------------
-- 
-- @function [parent=#MotionStreak] setTexture 
-- @param self
-- @param #cc.Texture2D texture
-- @return MotionStreak#MotionStreak self (return value: cc.MotionStreak)
        
--------------------------------
-- 
-- @function [parent=#MotionStreak] getTexture 
-- @param self
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)
        
--------------------------------
--  color used for the tint 
-- @function [parent=#MotionStreak] tintWithColor 
-- @param self
-- @param #color3b_table colors
-- @return MotionStreak#MotionStreak self (return value: cc.MotionStreak)
        
--------------------------------
-- js NA<br>
-- lua NA
-- @function [parent=#MotionStreak] setBlendFunc 
-- @param self
-- @param #cc.BlendFunc blendFunc
-- @return MotionStreak#MotionStreak self (return value: cc.MotionStreak)
        
--------------------------------
-- 
-- @function [parent=#MotionStreak] setStartingPositionInitialized 
-- @param self
-- @param #bool bStartingPositionInitialized
-- @return MotionStreak#MotionStreak self (return value: cc.MotionStreak)
        
--------------------------------
-- js NA<br>
-- lua NA
-- @function [parent=#MotionStreak] getBlendFunc 
-- @param self
-- @return BlendFunc#BlendFunc ret (return value: cc.BlendFunc)
        
--------------------------------
-- 
-- @function [parent=#MotionStreak] isStartingPositionInitialized 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  When fast mode is enabled, new points are added faster but with lower precision 
-- @function [parent=#MotionStreak] isFastMode 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#MotionStreak] setFastMode 
-- @param self
-- @param #bool bFastMode
-- @return MotionStreak#MotionStreak self (return value: cc.MotionStreak)
        
--------------------------------
-- @overload self, float, float, float, color3b_table, cc.Texture2D         
-- @overload self, float, float, float, color3b_table, string         
-- @function [parent=#MotionStreak] create
-- @param self
-- @param #float fade
-- @param #float minSeg
-- @param #float stroke
-- @param #color3b_table color
-- @param #string path
-- @return MotionStreak#MotionStreak ret (return value: cc.MotionStreak)

--------------------------------
-- 
-- @function [parent=#MotionStreak] isOpacityModifyRGB 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#MotionStreak] setPositionY 
-- @param self
-- @param #float y
-- @return MotionStreak#MotionStreak self (return value: cc.MotionStreak)
        
--------------------------------
-- 
-- @function [parent=#MotionStreak] setPositionX 
-- @param self
-- @param #float x
-- @return MotionStreak#MotionStreak self (return value: cc.MotionStreak)
        
--------------------------------
-- 
-- @function [parent=#MotionStreak] getPositionY 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#MotionStreak] getPositionX 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#MotionStreak] setOpacity 
-- @param self
-- @param #unsigned char opacity
-- @return MotionStreak#MotionStreak self (return value: cc.MotionStreak)
        
--------------------------------
-- 
-- @function [parent=#MotionStreak] setOpacityModifyRGB 
-- @param self
-- @param #bool value
-- @return MotionStreak#MotionStreak self (return value: cc.MotionStreak)
        
--------------------------------
-- 
-- @function [parent=#MotionStreak] getOpacity 
-- @param self
-- @return unsigned char#unsigned char ret (return value: unsigned char)
        
--------------------------------
-- @overload self, float, float         
-- @overload self, vec2_table         
-- @function [parent=#MotionStreak] setPosition
-- @param self
-- @param #float x
-- @param #float y
-- @return MotionStreak#MotionStreak self (return value: cc.MotionStreak)

--------------------------------
-- @overload self, float, float         
-- @overload self         
-- @function [parent=#MotionStreak] getPosition
-- @param self
-- @param #float x
-- @param #float y
-- @return MotionStreak#MotionStreak self (return value: cc.MotionStreak)

return nil
