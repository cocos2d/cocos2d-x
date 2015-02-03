
--------------------------------
-- @module SkeletonRenderer
-- @extend Node,BlendProtocol
-- @parent_module sp

--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] setTimeScale 
-- @param self
-- @param #float scale
-- @return SkeletonRenderer#SkeletonRenderer self (return value: sp.SkeletonRenderer)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] isOpacityModifyRGB 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] setDebugSlotsEnabled 
-- @param self
-- @param #bool enabled
-- @return SkeletonRenderer#SkeletonRenderer self (return value: sp.SkeletonRenderer)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] getDebugSlotsEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] setBonesToSetupPose 
-- @param self
-- @return SkeletonRenderer#SkeletonRenderer self (return value: sp.SkeletonRenderer)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] setSlotsToSetupPose 
-- @param self
-- @return SkeletonRenderer#SkeletonRenderer self (return value: sp.SkeletonRenderer)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] getBlendFunc 
-- @param self
-- @return BlendFunc#BlendFunc ret (return value: cc.BlendFunc)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] setSkin 
-- @param self
-- @param #string skinName
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] setToSetupPose 
-- @param self
-- @return SkeletonRenderer#SkeletonRenderer self (return value: sp.SkeletonRenderer)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] setOpacityModifyRGB 
-- @param self
-- @param #bool value
-- @return SkeletonRenderer#SkeletonRenderer self (return value: sp.SkeletonRenderer)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] setDebugBonesEnabled 
-- @param self
-- @param #bool enabled
-- @return SkeletonRenderer#SkeletonRenderer self (return value: sp.SkeletonRenderer)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] getSkeleton 
-- @param self
-- @return spSkeleton#spSkeleton ret (return value: spSkeleton)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] getDebugBonesEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] setBlendFunc 
-- @param self
-- @param #cc.BlendFunc blendFunc
-- @return SkeletonRenderer#SkeletonRenderer self (return value: sp.SkeletonRenderer)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] getTimeScale 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @overload self, string, string, float         
-- @overload self, string, spAtlas, float         
-- @function [parent=#SkeletonRenderer] createWithFile
-- @param self
-- @param #string skeletonDataFile
-- @param #spAtlas atlas
-- @param #float scale
-- @return SkeletonRenderer#SkeletonRenderer ret (return value: sp.SkeletonRenderer)

--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] getBoundingBox 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
return nil
