
--------------------------------
-- @module Bone
-- @extend Node
-- @parent_module ccs

--------------------------------
-- 
-- @function [parent=#Bone] isTransformDirty 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Bone] setBlendFunc 
-- @param self
-- @param #cc.BlendFunc blendFunc
-- @return Bone#Bone self (return value: ccs.Bone)
        
--------------------------------
-- 
-- @function [parent=#Bone] isIgnoreMovementBoneData 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Update zorder
-- @function [parent=#Bone] updateZOrder 
-- @param self
-- @return Bone#Bone self (return value: ccs.Bone)
        
--------------------------------
-- 
-- @function [parent=#Bone] getDisplayRenderNode 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#Bone] isBlendDirty 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Add a child to this bone, and it will let this child call setParent(Bone *parent) function to set self to it's parent<br>
-- param 	child  the child you want to add
-- @function [parent=#Bone] addChildBone 
-- @param self
-- @param #ccs.Bone child
-- @return Bone#Bone self (return value: ccs.Bone)
        
--------------------------------
-- 
-- @function [parent=#Bone] getWorldInfo 
-- @param self
-- @return BaseData#BaseData ret (return value: ccs.BaseData)
        
--------------------------------
-- 
-- @function [parent=#Bone] getTween 
-- @param self
-- @return Tween#Tween ret (return value: ccs.Tween)
        
--------------------------------
-- Get parent bone<br>
-- return parent bone
-- @function [parent=#Bone] getParentBone 
-- @param self
-- @return Bone#Bone ret (return value: ccs.Bone)
        
--------------------------------
--  Update color to render display
-- @function [parent=#Bone] updateColor 
-- @param self
-- @return Bone#Bone self (return value: ccs.Bone)
        
--------------------------------
-- 
-- @function [parent=#Bone] setTransformDirty 
-- @param self
-- @param #bool dirty
-- @return Bone#Bone self (return value: ccs.Bone)
        
--------------------------------
-- 
-- @function [parent=#Bone] getDisplayRenderNodeType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#Bone] removeDisplay 
-- @param self
-- @param #int index
-- @return Bone#Bone self (return value: ccs.Bone)
        
--------------------------------
-- 
-- @function [parent=#Bone] setBoneData 
-- @param self
-- @param #ccs.BoneData boneData
-- @return Bone#Bone self (return value: ccs.Bone)
        
--------------------------------
-- @overload self, string         
-- @overload self         
-- @function [parent=#Bone] init
-- @param self
-- @param #string name
-- @return bool#bool ret (return value: bool)

--------------------------------
-- Set parent bone.<br>
-- If parent is NUll, then also remove this bone from armature.<br>
-- It will not set the Armature, if you want to add the bone to a Armature, you should use Armature::addBone(Bone *bone, const char* parentName).<br>
-- param parent  the parent bone.<br>
-- nullptr : remove this bone from armature
-- @function [parent=#Bone] setParentBone 
-- @param self
-- @param #ccs.Bone parent
-- @return Bone#Bone self (return value: ccs.Bone)
        
--------------------------------
-- @overload self, cc.Node, int         
-- @overload self, ccs.DisplayData, int         
-- @function [parent=#Bone] addDisplay
-- @param self
-- @param #ccs.DisplayData displayData
-- @param #int index
-- @return Bone#Bone self (return value: ccs.Bone)

--------------------------------
-- 
-- @function [parent=#Bone] getBlendFunc 
-- @param self
-- @return BlendFunc#BlendFunc ret (return value: cc.BlendFunc)
        
--------------------------------
-- Remove itself from its parent.<br>
-- param recursion    whether or not to remove childBone's display
-- @function [parent=#Bone] removeFromParent 
-- @param self
-- @param #bool recursion
-- @return Bone#Bone self (return value: ccs.Bone)
        
--------------------------------
-- 
-- @function [parent=#Bone] getColliderDetector 
-- @param self
-- @return ColliderDetector#ColliderDetector ret (return value: ccs.ColliderDetector)
        
--------------------------------
-- 
-- @function [parent=#Bone] getChildArmature 
-- @param self
-- @return Armature#Armature ret (return value: ccs.Armature)
        
--------------------------------
-- 
-- @function [parent=#Bone] getTweenData 
-- @param self
-- @return FrameData#FrameData ret (return value: ccs.FrameData)
        
--------------------------------
-- 
-- @function [parent=#Bone] changeDisplayWithIndex 
-- @param self
-- @param #int index
-- @param #bool force
-- @return Bone#Bone self (return value: ccs.Bone)
        
--------------------------------
-- 
-- @function [parent=#Bone] changeDisplayWithName 
-- @param self
-- @param #string name
-- @param #bool force
-- @return Bone#Bone self (return value: ccs.Bone)
        
--------------------------------
-- 
-- @function [parent=#Bone] setArmature 
-- @param self
-- @param #ccs.Armature armature
-- @return Bone#Bone self (return value: ccs.Bone)
        
--------------------------------
-- 
-- @function [parent=#Bone] setBlendDirty 
-- @param self
-- @param #bool dirty
-- @return Bone#Bone self (return value: ccs.Bone)
        
--------------------------------
-- Removes a child Bone<br>
-- param 	bone   the bone you want to remove
-- @function [parent=#Bone] removeChildBone 
-- @param self
-- @param #ccs.Bone bone
-- @param #bool recursion
-- @return Bone#Bone self (return value: ccs.Bone)
        
--------------------------------
-- 
-- @function [parent=#Bone] setChildArmature 
-- @param self
-- @param #ccs.Armature childArmature
-- @return Bone#Bone self (return value: ccs.Bone)
        
--------------------------------
-- 
-- @function [parent=#Bone] getNodeToArmatureTransform 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- 
-- @function [parent=#Bone] getDisplayManager 
-- @param self
-- @return DisplayManager#DisplayManager ret (return value: ccs.DisplayManager)
        
--------------------------------
-- 
-- @function [parent=#Bone] getArmature 
-- @param self
-- @return Armature#Armature ret (return value: ccs.Armature)
        
--------------------------------
-- 
-- @function [parent=#Bone] getBoneData 
-- @param self
-- @return BoneData#BoneData ret (return value: ccs.BoneData)
        
--------------------------------
-- @overload self, string         
-- @overload self         
-- @function [parent=#Bone] create
-- @param self
-- @param #string name
-- @return Bone#Bone ret (return value: ccs.Bone)

--------------------------------
-- 
-- @function [parent=#Bone] updateDisplayedColor 
-- @param self
-- @param #color3b_table parentColor
-- @return Bone#Bone self (return value: ccs.Bone)
        
--------------------------------
-- 
-- @function [parent=#Bone] setLocalZOrder 
-- @param self
-- @param #int zOrder
-- @return Bone#Bone self (return value: ccs.Bone)
        
--------------------------------
-- 
-- @function [parent=#Bone] getNodeToWorldTransform 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- 
-- @function [parent=#Bone] update 
-- @param self
-- @param #float delta
-- @return Bone#Bone self (return value: ccs.Bone)
        
--------------------------------
-- 
-- @function [parent=#Bone] updateDisplayedOpacity 
-- @param self
-- @param #unsigned char parentOpacity
-- @return Bone#Bone self (return value: ccs.Bone)
        
--------------------------------
-- js ctor
-- @function [parent=#Bone] Bone 
-- @param self
-- @return Bone#Bone self (return value: ccs.Bone)
        
return nil
