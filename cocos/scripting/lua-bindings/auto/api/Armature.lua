
--------------------------------
-- @module Armature
-- @extend Node,BlendProtocol
-- @parent_module ccs

--------------------------------
-- Get a bone with the specified name<br>
-- param name The bone's name you want to get
-- @function [parent=#Armature] getBone 
-- @param self
-- @param #string name
-- @return Bone#Bone ret (return value: ccs.Bone)
        
--------------------------------
-- Change a bone's parent with the specified parent name.<br>
-- param bone The bone you want to change parent<br>
-- param parentName The new parent's name.
-- @function [parent=#Armature] changeBoneParent 
-- @param self
-- @param #ccs.Bone bone
-- @param #string parentName
        
--------------------------------
-- 
-- @function [parent=#Armature] setAnimation 
-- @param self
-- @param #ccs.ArmatureAnimation animation
        
--------------------------------
-- 
-- @function [parent=#Armature] getBoneAtPoint 
-- @param self
-- @param #float x
-- @param #float y
-- @return Bone#Bone ret (return value: ccs.Bone)
        
--------------------------------
-- 
-- @function [parent=#Armature] getArmatureTransformDirty 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Armature] setVersion 
-- @param self
-- @param #float version
        
--------------------------------
-- Set contentsize and Calculate anchor point.
-- @function [parent=#Armature] updateOffsetPoint 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#Armature] getParentBone 
-- @param self
-- @return Bone#Bone ret (return value: ccs.Bone)
        
--------------------------------
-- Remove a bone with the specified name. If recursion it will also remove child Bone recursionly.<br>
-- param bone The bone you want to remove<br>
-- param recursion Determine whether remove the bone's child  recursion.
-- @function [parent=#Armature] removeBone 
-- @param self
-- @param #ccs.Bone bone
-- @param #bool recursion
        
--------------------------------
-- 
-- @function [parent=#Armature] getBatchNode 
-- @param self
-- @return BatchNode#BatchNode ret (return value: ccs.BatchNode)
        
--------------------------------
-- @overload self, string         
-- @overload self         
-- @overload self, string, ccs.Bone         
-- @function [parent=#Armature] init
-- @param self
-- @param #string name
-- @param #ccs.Bone parentBone
-- @return bool#bool ret (retunr value: bool)

--------------------------------
-- 
-- @function [parent=#Armature] setParentBone 
-- @param self
-- @param #ccs.Bone parentBone
        
--------------------------------
-- 
-- @function [parent=#Armature] drawContour 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#Armature] setBatchNode 
-- @param self
-- @param #ccs.BatchNode batchNode
        
--------------------------------
-- 
-- @function [parent=#Armature] setArmatureData 
-- @param self
-- @param #ccs.ArmatureData armatureData
        
--------------------------------
-- Add a Bone to this Armature,<br>
-- param bone  The Bone you want to add to Armature<br>
-- param parentName   The parent Bone's name you want to add to . If it's  nullptr, then set Armature to its parent
-- @function [parent=#Armature] addBone 
-- @param self
-- @param #ccs.Bone bone
-- @param #string parentName
        
--------------------------------
-- 
-- @function [parent=#Armature] getArmatureData 
-- @param self
-- @return ArmatureData#ArmatureData ret (return value: ccs.ArmatureData)
        
--------------------------------
-- 
-- @function [parent=#Armature] getVersion 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Armature] getAnimation 
-- @param self
-- @return ArmatureAnimation#ArmatureAnimation ret (return value: ccs.ArmatureAnimation)
        
--------------------------------
-- 
-- @function [parent=#Armature] getOffsetPoints 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Get Armature's bone dictionary<br>
-- return Armature's bone dictionary
-- @function [parent=#Armature] getBoneDic 
-- @param self
-- @return map_table#map_table ret (return value: map_table)
        
--------------------------------
-- @overload self, string         
-- @overload self         
-- @overload self, string, ccs.Bone         
-- @function [parent=#Armature] create
-- @param self
-- @param #string name
-- @param #ccs.Bone parentBone
-- @return Armature#Armature ret (retunr value: ccs.Armature)

--------------------------------
-- 
-- @function [parent=#Armature] setAnchorPoint 
-- @param self
-- @param #vec2_table point
        
--------------------------------
-- 
-- @function [parent=#Armature] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
        
--------------------------------
-- 
-- @function [parent=#Armature] getAnchorPointInPoints 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
-- @function [parent=#Armature] update 
-- @param self
-- @param #float dt
        
--------------------------------
-- 
-- @function [parent=#Armature] getNodeToParentTransform 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- This boundingBox will calculate all bones' boundingBox every time
-- @function [parent=#Armature] getBoundingBox 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- js ctor
-- @function [parent=#Armature] Armature 
-- @param self
        
return nil
