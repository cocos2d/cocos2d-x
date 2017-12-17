
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
-- @function [parent=#SkeletonRenderer] initWithData 
-- @param self
-- @param #spSkeletonData skeletonData
-- @param #bool ownsSkeletonData
-- @return SkeletonRenderer#SkeletonRenderer self (return value: sp.SkeletonRenderer)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] setDebugSlotsEnabled 
-- @param self
-- @param #bool enabled
-- @return SkeletonRenderer#SkeletonRenderer self (return value: sp.SkeletonRenderer)
        
--------------------------------
-- @overload self, string, string, float         
-- @overload self, string, spAtlas, float         
-- @function [parent=#SkeletonRenderer] initWithJsonFile
-- @param self
-- @param #string skeletonDataFile
-- @param #spAtlas atlas
-- @param #float scale
-- @return SkeletonRenderer#SkeletonRenderer self (return value: sp.SkeletonRenderer)

--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] setSlotsToSetupPose 
-- @param self
-- @return SkeletonRenderer#SkeletonRenderer self (return value: sp.SkeletonRenderer)
        
--------------------------------
-- @overload self, string, string, float         
-- @overload self, string, spAtlas, float         
-- @function [parent=#SkeletonRenderer] initWithBinaryFile
-- @param self
-- @param #string skeletonDataFile
-- @param #spAtlas atlas
-- @param #float scale
-- @return SkeletonRenderer#SkeletonRenderer self (return value: sp.SkeletonRenderer)

--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] setToSetupPose 
-- @param self
-- @return SkeletonRenderer#SkeletonRenderer self (return value: sp.SkeletonRenderer)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] setDebugMeshesEnabled 
-- @param self
-- @param #bool enabled
-- @return SkeletonRenderer#SkeletonRenderer self (return value: sp.SkeletonRenderer)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] isTwoColorTint 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] getBlendFunc 
-- @param self
-- @return BlendFunc#BlendFunc ret (return value: cc.BlendFunc)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] initialize 
-- @param self
-- @return SkeletonRenderer#SkeletonRenderer self (return value: sp.SkeletonRenderer)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] setDebugBonesEnabled 
-- @param self
-- @param #bool enabled
-- @return SkeletonRenderer#SkeletonRenderer self (return value: sp.SkeletonRenderer)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] getDebugBonesEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] getTimeScale 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] setTwoColorTint 
-- @param self
-- @param #bool enabled
-- @return SkeletonRenderer#SkeletonRenderer self (return value: sp.SkeletonRenderer)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] getDebugMeshesEnabled 
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
-- @function [parent=#SkeletonRenderer] setVertexEffect 
-- @param self
-- @param #spVertexEffect effect
-- @return SkeletonRenderer#SkeletonRenderer self (return value: sp.SkeletonRenderer)
        
--------------------------------
-- @overload self, char         
-- @overload self, string         
-- @function [parent=#SkeletonRenderer] setSkin
-- @param self
-- @param #string skinName
-- @return bool#bool ret (return value: bool)

--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] getSkeleton 
-- @param self
-- @return spSkeleton#spSkeleton ret (return value: spSkeleton)
        
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
-- @function [parent=#SkeletonRenderer] create 
-- @param self
-- @return SkeletonRenderer#SkeletonRenderer ret (return value: sp.SkeletonRenderer)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] onEnter 
-- @param self
-- @return SkeletonRenderer#SkeletonRenderer self (return value: sp.SkeletonRenderer)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] onExit 
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
-- @function [parent=#SkeletonRenderer] getBoundingBox 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- 
-- @function [parent=#SkeletonRenderer] isOpacityModifyRGB 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @overload self, spSkeletonData, bool         
-- @overload self         
-- @overload self, string, spAtlas, float         
-- @overload self, string, string, float         
-- @function [parent=#SkeletonRenderer] SkeletonRenderer
-- @param self
-- @param #string skeletonDataFile
-- @param #string atlasFile
-- @param #float scale
-- @return SkeletonRenderer#SkeletonRenderer self (return value: sp.SkeletonRenderer)

return nil
