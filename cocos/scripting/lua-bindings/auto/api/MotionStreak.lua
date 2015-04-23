
--------------------------------
-- @module MotionStreak
-- @extend Node,TextureProtocol
-- @parent_module cc

--------------------------------
--  Remove all living segments of the ribbon.
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
--  Color used for the tint.<br>
-- param colors The color used for the tint.
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
--  Sets the starting position initialized or not.<br>
-- param bStartingPositionInitialized True if initialized the starting position.
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
--  Is the starting position initialized or not.<br>
-- return True if the starting position is initialized.
-- @function [parent=#MotionStreak] isStartingPositionInitialized 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  When fast mode is enabled, new points are added faster but with lower precision. <br>
-- return True if fast mode is enabled.
-- @function [parent=#MotionStreak] isFastMode 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Get stroke.<br>
-- return float stroke.
-- @function [parent=#MotionStreak] getStroke 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Sets fast mode or not.<br>
-- param bFastMode True if enabled fast mode.
-- @function [parent=#MotionStreak] setFastMode 
-- @param self
-- @param #bool bFastMode
-- @return MotionStreak#MotionStreak self (return value: cc.MotionStreak)
        
--------------------------------
--  Set stroke.<br>
-- param stroke The width of stroke.
-- @function [parent=#MotionStreak] setStroke 
-- @param self
-- @param #float stroke
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
-- @function [parent=#MotionStreak] setOpacity 
-- @param self
-- @param #unsigned char opacity
-- @return MotionStreak#MotionStreak self (return value: cc.MotionStreak)
        
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
-- @function [parent=#MotionStreak] getPosition3D 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
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
