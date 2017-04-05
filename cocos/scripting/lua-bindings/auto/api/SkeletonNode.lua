
--------------------------------
-- @module SkeletonNode
-- @extend BoneNode
-- @parent_module ccs

--------------------------------
-- get bonenode in skeleton node by bone name
-- @function [parent=#SkeletonNode] getBoneNode 
-- @param self
-- @param #string boneName
-- @return BoneNode#BoneNode ret (return value: ccs.BoneNode)
        
--------------------------------
-- @overload self, string         
-- @overload self, map_table         
-- @function [parent=#SkeletonNode] changeSkins
-- @param self
-- @param #map_table boneSkinNameMap
-- @return SkeletonNode#SkeletonNode self (return value: ccs.SkeletonNode)

--------------------------------
-- brief: add a boneSkinNameMap as a SkinGroup named groupName<br>
-- param: groupName, key<br>
-- param: boneSkinNameMap, map <name of bone, name of skin to display which added to bone>
-- @function [parent=#SkeletonNode] addSkinGroup 
-- @param self
-- @param #string groupName
-- @param #map_table boneSkinNameMap
-- @return SkeletonNode#SkeletonNode self (return value: ccs.SkeletonNode)
        
--------------------------------
-- get All bones in this skeleton, <bone's name, BoneNode>
-- @function [parent=#SkeletonNode] getAllSubBonesMap 
-- @param self
-- @return map_table#map_table ret (return value: map_table)
        
--------------------------------
-- 
-- @function [parent=#SkeletonNode] create 
-- @param self
-- @return SkeletonNode#SkeletonNode ret (return value: ccs.SkeletonNode)
        
--------------------------------
-- 
-- @function [parent=#SkeletonNode] getBoundingBox 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- 
-- @function [parent=#SkeletonNode] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#SkeletonNode] SkeletonNode 
-- @param self
-- @return SkeletonNode#SkeletonNode self (return value: ccs.SkeletonNode)
        
return nil
