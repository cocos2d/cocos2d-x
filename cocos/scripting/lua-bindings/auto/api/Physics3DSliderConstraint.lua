
--------------------------------
-- @module Physics3DSliderConstraint
-- @extend Physics3DConstraint
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] setPoweredAngMotor 
-- @param self
-- @param #bool onOff
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] getDampingLimAng 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] setRestitutionOrthoLin 
-- @param self
-- @param #float restitutionOrthoLin
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] setRestitutionDirLin 
-- @param self
-- @param #float restitutionDirLin
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] getLinearPos 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- get A's frame offset
-- @function [parent=#Physics3DSliderConstraint] getFrameOffsetA 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- get B's frame offset
-- @function [parent=#Physics3DSliderConstraint] getFrameOffsetB 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] setPoweredLinMotor 
-- @param self
-- @param #bool onOff
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] getDampingDirAng 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] getRestitutionLimLin 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] getSoftnessOrthoAng 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] setSoftnessOrthoLin 
-- @param self
-- @param #float softnessOrthoLin
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] setSoftnessLimLin 
-- @param self
-- @param #float softnessLimLin
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] getAngularPos 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] setRestitutionLimAng 
-- @param self
-- @param #float restitutionLimAng
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- set upper linear limit
-- @function [parent=#Physics3DSliderConstraint] setUpperLinLimit 
-- @param self
-- @param #float upperLimit
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] setDampingDirLin 
-- @param self
-- @param #float dampingDirLin
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- get upper anglular limit
-- @function [parent=#Physics3DSliderConstraint] getUpperAngLimit 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] getDampingDirLin 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] getSoftnessDirAng 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] getPoweredAngMotor 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- set lower angualr limit
-- @function [parent=#Physics3DSliderConstraint] setLowerAngLimit 
-- @param self
-- @param #float lowerLimit
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- set upper anglular limit
-- @function [parent=#Physics3DSliderConstraint] setUpperAngLimit 
-- @param self
-- @param #float upperLimit
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] setTargetLinMotorVelocity 
-- @param self
-- @param #float targetLinMotorVelocity
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] setDampingLimAng 
-- @param self
-- @param #float dampingLimAng
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] getRestitutionLimAng 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  access for UseFrameOffset
-- @function [parent=#Physics3DSliderConstraint] getUseFrameOffset 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] getSoftnessOrthoLin 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] getDampingOrthoAng 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- set use frame offset
-- @function [parent=#Physics3DSliderConstraint] setUseFrameOffset 
-- @param self
-- @param #bool frameOffsetOnOff
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- set lower linear limit
-- @function [parent=#Physics3DSliderConstraint] setLowerLinLimit 
-- @param self
-- @param #float lowerLimit
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] getRestitutionDirLin 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] getTargetLinMotorVelocity 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- get lower linear limit
-- @function [parent=#Physics3DSliderConstraint] getLowerLinLimit 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] getSoftnessLimLin 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] setDampingOrthoAng 
-- @param self
-- @param #float dampingOrthoAng
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] setSoftnessDirAng 
-- @param self
-- @param #float softnessDirAng
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] getPoweredLinMotor 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] setRestitutionOrthoAng 
-- @param self
-- @param #float restitutionOrthoAng
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] setDampingDirAng 
-- @param self
-- @param #float dampingDirAng
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- set frames for rigid body A and B
-- @function [parent=#Physics3DSliderConstraint] setFrames 
-- @param self
-- @param #mat4_table frameA
-- @param #mat4_table frameB
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] getRestitutionOrthoAng 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] getMaxAngMotorForce 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] getDampingOrthoLin 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- get upper linear limit
-- @function [parent=#Physics3DSliderConstraint] getUpperLinLimit 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] setMaxLinMotorForce 
-- @param self
-- @param #float maxLinMotorForce
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] getRestitutionOrthoLin 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] setTargetAngMotorVelocity 
-- @param self
-- @param #float targetAngMotorVelocity
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] getSoftnessLimAng 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] setRestitutionDirAng 
-- @param self
-- @param #float restitutionDirAng
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] getDampingLimLin 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- get lower angular limit
-- @function [parent=#Physics3DSliderConstraint] getLowerAngLimit 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] getRestitutionDirAng 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] getTargetAngMotorVelocity 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] setRestitutionLimLin 
-- @param self
-- @param #float restitutionLimLin
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] getMaxLinMotorForce 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] setDampingOrthoLin 
-- @param self
-- @param #float dampingOrthoLin
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] setSoftnessOrthoAng 
-- @param self
-- @param #float softnessOrthoAng
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] setDampingLimLin 
-- @param self
-- @param #float dampingLimLin
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] setSoftnessDirLin 
-- @param self
-- @param #float softnessDirLin
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] setMaxAngMotorForce 
-- @param self
-- @param #float maxAngMotorForce
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] getSoftnessDirLin 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] setSoftnessLimAng 
-- @param self
-- @param #float softnessLimAng
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- use A's frame as linear refference
-- @function [parent=#Physics3DSliderConstraint] getUseLinearReferenceFrameA 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- create slider constraint<br>
-- param rbA rigid body A<br>
-- param rbB rigid body B<br>
-- param frameInA frame in A's local space<br>
-- param frameInB frame in B's local space<br>
-- param useLinearReferenceFrameA use fixed frame A for linear limits
-- @function [parent=#Physics3DSliderConstraint] create 
-- @param self
-- @param #cc.Physics3DRigidBody rbA
-- @param #cc.Physics3DRigidBody rbB
-- @param #mat4_table frameInA
-- @param #mat4_table frameInB
-- @param #bool useLinearReferenceFrameA
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint ret (return value: cc.Physics3DSliderConstraint)
        
--------------------------------
-- 
-- @function [parent=#Physics3DSliderConstraint] Physics3DSliderConstraint 
-- @param self
-- @return Physics3DSliderConstraint#Physics3DSliderConstraint self (return value: cc.Physics3DSliderConstraint)
        
return nil
