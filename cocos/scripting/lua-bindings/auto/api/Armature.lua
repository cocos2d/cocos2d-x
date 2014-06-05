
--------------------------------
-- @module Armature
-- @extend Node,BlendProtocol

--------------------------------
-- @function [parent=#Armature] getBone 
-- @param self
-- @param #string str
-- @return Bone#Bone ret (return value: ccs.Bone)
        
--------------------------------
-- @function [parent=#Armature] changeBoneParent 
-- @param self
-- @param #ccs.Bone bone
-- @param #string str
        
--------------------------------
-- @function [parent=#Armature] setAnimation 
-- @param self
-- @param #ccs.ArmatureAnimation armatureanimation
        
--------------------------------
-- @function [parent=#Armature] getBoneAtPoint 
-- @param self
-- @param #float float
-- @param #float float
-- @return Bone#Bone ret (return value: ccs.Bone)
        
--------------------------------
-- @function [parent=#Armature] getArmatureTransformDirty 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Armature] setVersion 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#Armature] updateOffsetPoint 
-- @param self
        
--------------------------------
-- @function [parent=#Armature] getParentBone 
-- @param self
-- @return Bone#Bone ret (return value: ccs.Bone)
        
--------------------------------
-- @function [parent=#Armature] setArmatureData 
-- @param self
-- @param #ccs.ArmatureData armaturedata
        
--------------------------------
-- @function [parent=#Armature] removeBone 
-- @param self
-- @param #ccs.Bone bone
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Armature] getBatchNode 
-- @param self
-- @return BatchNode#BatchNode ret (return value: ccs.BatchNode)
        
--------------------------------
-- @function [parent=#Armature] getName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- overload function: init(string)
--          
-- overload function: init()
--          
-- overload function: init(string, ccs.Bone)
--          
-- @function [parent=#Armature] init
-- @param self
-- @param #string str
-- @param #ccs.Bone bone
-- @return bool#bool ret (retunr value: bool)

--------------------------------
-- @function [parent=#Armature] setParentBone 
-- @param self
-- @param #ccs.Bone bone
        
--------------------------------
-- @function [parent=#Armature] drawContour 
-- @param self
        
--------------------------------
-- @function [parent=#Armature] setBatchNode 
-- @param self
-- @param #ccs.BatchNode batchnode
        
--------------------------------
-- @function [parent=#Armature] setName 
-- @param self
-- @param #string str
        
--------------------------------
-- @function [parent=#Armature] addBone 
-- @param self
-- @param #ccs.Bone bone
-- @param #string str
        
--------------------------------
-- @function [parent=#Armature] getArmatureData 
-- @param self
-- @return ArmatureData#ArmatureData ret (return value: ccs.ArmatureData)
        
--------------------------------
-- @function [parent=#Armature] getVersion 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Armature] getAnimation 
-- @param self
-- @return ArmatureAnimation#ArmatureAnimation ret (return value: ccs.ArmatureAnimation)
        
--------------------------------
-- @function [parent=#Armature] getBoneDic 
-- @param self
-- @return map_table#map_table ret (return value: map_table)
        
--------------------------------
-- overload function: create(string)
--          
-- overload function: create()
--          
-- overload function: create(string, ccs.Bone)
--          
-- @function [parent=#Armature] create
-- @param self
-- @param #string str
-- @param #ccs.Bone bone
-- @return Armature#Armature ret (retunr value: ccs.Armature)

--------------------------------
-- @function [parent=#Armature] setAnchorPoint 
-- @param self
-- @param #vec2_table vec2
        
--------------------------------
-- @function [parent=#Armature] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table mat4
-- @param #unsigned int int
        
--------------------------------
-- @function [parent=#Armature] getAnchorPointInPoints 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#Armature] update 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#Armature] getNodeToParentTransform 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- @function [parent=#Armature] getBoundingBox 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- @function [parent=#Armature] Armature 
-- @param self
        
return nil
