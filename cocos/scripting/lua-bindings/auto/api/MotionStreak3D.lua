
--------------------------------
-- @module MotionStreak3D
-- @extend Node,TextureProtocol
-- @parent_module cc

--------------------------------
--  Remove all living segments of the ribbon.
-- @function [parent=#MotionStreak3D] reset 
-- @param self
-- @return MotionStreak3D#MotionStreak3D self (return value: cc.MotionStreak3D)
        
--------------------------------
-- 
-- @function [parent=#MotionStreak3D] setTexture 
-- @param self
-- @param #cc.Texture2D texture
-- @return MotionStreak3D#MotionStreak3D self (return value: cc.MotionStreak3D)
        
--------------------------------
-- 
-- @function [parent=#MotionStreak3D] getTexture 
-- @param self
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)
        
--------------------------------
--  Color used for the tint.<br>
-- param colors The color used for the tint.
-- @function [parent=#MotionStreak3D] tintWithColor 
-- @param self
-- @param #color3b_table colors
-- @return MotionStreak3D#MotionStreak3D self (return value: cc.MotionStreak3D)
        
--------------------------------
-- Get the direction of sweeping line segment
-- @function [parent=#MotionStreak3D] getSweepAxis 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
-- js NA<br>
-- lua NA
-- @function [parent=#MotionStreak3D] setBlendFunc 
-- @param self
-- @param #cc.BlendFunc blendFunc
-- @return MotionStreak3D#MotionStreak3D self (return value: cc.MotionStreak3D)
        
--------------------------------
--  Sets the starting position initialized or not.<br>
-- param bStartingPositionInitialized True if initialized the starting position.
-- @function [parent=#MotionStreak3D] setStartingPositionInitialized 
-- @param self
-- @param #bool bStartingPositionInitialized
-- @return MotionStreak3D#MotionStreak3D self (return value: cc.MotionStreak3D)
        
--------------------------------
-- js NA<br>
-- lua NA
-- @function [parent=#MotionStreak3D] getBlendFunc 
-- @param self
-- @return BlendFunc#BlendFunc ret (return value: cc.BlendFunc)
        
--------------------------------
--  Is the starting position initialized or not.<br>
-- return True if the starting position is initialized.
-- @function [parent=#MotionStreak3D] isStartingPositionInitialized 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Get stroke.<br>
-- return float stroke.
-- @function [parent=#MotionStreak3D] getStroke 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @overload self, float, float, float, color3b_table, cc.Texture2D         
-- @overload self, float, float, float, color3b_table, string         
-- @function [parent=#MotionStreak3D] initWithFade
-- @param self
-- @param #float fade
-- @param #float minSeg
-- @param #float stroke
-- @param #color3b_table color
-- @param #string path
-- @return bool#bool ret (return value: bool)

--------------------------------
-- Set the direction of sweeping line segment.<br>
-- param sweepAxis Direction of sweeping line segment
-- @function [parent=#MotionStreak3D] setSweepAxis 
-- @param self
-- @param #vec3_table sweepAxis
-- @return MotionStreak3D#MotionStreak3D self (return value: cc.MotionStreak3D)
        
--------------------------------
--  Set stroke.<br>
-- param stroke The width of stroke.
-- @function [parent=#MotionStreak3D] setStroke 
-- @param self
-- @param #float stroke
-- @return MotionStreak3D#MotionStreak3D self (return value: cc.MotionStreak3D)
        
--------------------------------
-- @overload self, float, float, float, color3b_table, cc.Texture2D         
-- @overload self, float, float, float, color3b_table, string         
-- @function [parent=#MotionStreak3D] create
-- @param self
-- @param #float fade
-- @param #float minSeg
-- @param #float stroke
-- @param #color3b_table color
-- @param #string path
-- @return MotionStreak3D#MotionStreak3D ret (return value: cc.MotionStreak3D)

--------------------------------
-- js NA<br>
-- lua NA
-- @function [parent=#MotionStreak3D] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
-- @return MotionStreak3D#MotionStreak3D self (return value: cc.MotionStreak3D)
        
--------------------------------
-- 
-- @function [parent=#MotionStreak3D] setOpacityModifyRGB 
-- @param self
-- @param #bool value
-- @return MotionStreak3D#MotionStreak3D self (return value: cc.MotionStreak3D)
        
--------------------------------
-- 
-- @function [parent=#MotionStreak3D] setPositionY 
-- @param self
-- @param #float y
-- @return MotionStreak3D#MotionStreak3D self (return value: cc.MotionStreak3D)
        
--------------------------------
-- 
-- @function [parent=#MotionStreak3D] setRotation3D 
-- @param self
-- @param #vec3_table rotation
-- @return MotionStreak3D#MotionStreak3D self (return value: cc.MotionStreak3D)
        
--------------------------------
-- 
-- @function [parent=#MotionStreak3D] setPositionX 
-- @param self
-- @param #float x
-- @return MotionStreak3D#MotionStreak3D self (return value: cc.MotionStreak3D)
        
--------------------------------
-- 
-- @function [parent=#MotionStreak3D] setPosition3D 
-- @param self
-- @param #vec3_table position
-- @return MotionStreak3D#MotionStreak3D self (return value: cc.MotionStreak3D)
        
--------------------------------
-- 
-- @function [parent=#MotionStreak3D] getPositionY 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#MotionStreak3D] getPositionX 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#MotionStreak3D] getPosition3D 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
-- 
-- @function [parent=#MotionStreak3D] setOpacity 
-- @param self
-- @param #unsigned char opacity
-- @return MotionStreak3D#MotionStreak3D self (return value: cc.MotionStreak3D)
        
--------------------------------
-- lua NA
-- @function [parent=#MotionStreak3D] update 
-- @param self
-- @param #float delta
-- @return MotionStreak3D#MotionStreak3D self (return value: cc.MotionStreak3D)
        
--------------------------------
-- 
-- @function [parent=#MotionStreak3D] setRotationQuat 
-- @param self
-- @param #cc.Quaternion quat
-- @return MotionStreak3D#MotionStreak3D self (return value: cc.MotionStreak3D)
        
--------------------------------
-- 
-- @function [parent=#MotionStreak3D] getOpacity 
-- @param self
-- @return unsigned char#unsigned char ret (return value: unsigned char)
        
--------------------------------
-- @overload self, float, float         
-- @overload self, vec2_table         
-- @function [parent=#MotionStreak3D] setPosition
-- @param self
-- @param #float x
-- @param #float y
-- @return MotionStreak3D#MotionStreak3D self (return value: cc.MotionStreak3D)

--------------------------------
-- @overload self, float, float         
-- @overload self         
-- @function [parent=#MotionStreak3D] getPosition
-- @param self
-- @param #float x
-- @param #float y
-- @return MotionStreak3D#MotionStreak3D self (return value: cc.MotionStreak3D)

--------------------------------
-- 
-- @function [parent=#MotionStreak3D] isOpacityModifyRGB 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#MotionStreak3D] MotionStreak3D 
-- @param self
-- @return MotionStreak3D#MotionStreak3D self (return value: cc.MotionStreak3D)
        
return nil
