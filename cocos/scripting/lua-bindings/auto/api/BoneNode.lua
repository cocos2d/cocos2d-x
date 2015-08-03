
--------------------------------
-- @module BoneNode
-- @extend Node,BlendProtocol
-- @parent_module ccs

--------------------------------
-- 
-- @function [parent=#BoneNode] getDebugDrawWidth 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#BoneNode] getChildBones
-- @param self
-- @return array_table#array_table ret (return value: array_table)

--------------------------------
-- 
-- @function [parent=#BoneNode] getBlendFunc 
-- @param self
-- @return BlendFunc#BlendFunc ret (return value: cc.BlendFunc)
        
--------------------------------
-- brief: get all bones in this bone tree
-- @function [parent=#BoneNode] getAllSubBones 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- 
-- @function [parent=#BoneNode] setBlendFunc 
-- @param self
-- @param #cc.BlendFunc blendFunc
-- @return BoneNode#BoneNode self (return value: ccs.BoneNode)
        
--------------------------------
-- 
-- @function [parent=#BoneNode] setDebugDrawEnabled 
-- @param self
-- @param #bool isDebugDraw
-- @return BoneNode#BoneNode self (return value: ccs.BoneNode)
        
--------------------------------
-- get displayings rect in self transform
-- @function [parent=#BoneNode] getVisibleSkinsRect 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- brief: get all skins in this bone tree
-- @function [parent=#BoneNode] getAllSubSkins 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- @overload self, string, bool         
-- @overload self, cc.Node, bool         
-- @function [parent=#BoneNode] displaySkin
-- @param self
-- @param #cc.Node skin
-- @param #bool hideOthers
-- @return BoneNode#BoneNode self (return value: ccs.BoneNode)

--------------------------------
-- 
-- @function [parent=#BoneNode] isDebugDrawEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @overload self, cc.Node, bool, bool         
-- @overload self, cc.Node, bool         
-- @function [parent=#BoneNode] addSkin
-- @param self
-- @param #cc.Node skin
-- @param #bool display
-- @param #bool hideOthers
-- @return BoneNode#BoneNode self (return value: ccs.BoneNode)

--------------------------------
-- 
-- @function [parent=#BoneNode] getRootSkeletonNode 
-- @param self
-- @return SkeletonNode#SkeletonNode ret (return value: ccs.SkeletonNode)
        
--------------------------------
-- 
-- @function [parent=#BoneNode] setDebugDrawLength 
-- @param self
-- @param #float length
-- @return BoneNode#BoneNode self (return value: ccs.BoneNode)
        
--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#BoneNode] getSkins
-- @param self
-- @return array_table#array_table ret (return value: array_table)

--------------------------------
-- 
-- @function [parent=#BoneNode] getVisibleSkins 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- 
-- @function [parent=#BoneNode] setDebugDrawWidth 
-- @param self
-- @param #float width
-- @return BoneNode#BoneNode self (return value: ccs.BoneNode)
        
--------------------------------
-- 
-- @function [parent=#BoneNode] getDebugDrawLength 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#BoneNode] setDebugDrawColor 
-- @param self
-- @param #color4f_table color
-- @return BoneNode#BoneNode self (return value: ccs.BoneNode)
        
--------------------------------
-- 
-- @function [parent=#BoneNode] getDebugDrawColor 
-- @param self
-- @return color4f_table#color4f_table ret (return value: color4f_table)
        
--------------------------------
-- @overload self, int         
-- @overload self         
-- @function [parent=#BoneNode] create
-- @param self
-- @param #int length
-- @return BoneNode#BoneNode ret (return value: ccs.BoneNode)

--------------------------------
-- @overload self, cc.Node, int, int         
-- @overload self, cc.Node, int, string         
-- @function [parent=#BoneNode] addChild
-- @param self
-- @param #cc.Node child
-- @param #int localZOrder
-- @param #string name
-- @return BoneNode#BoneNode self (return value: ccs.BoneNode)

--------------------------------
-- 
-- @function [parent=#BoneNode] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
-- @return BoneNode#BoneNode self (return value: ccs.BoneNode)
        
--------------------------------
-- 
-- @function [parent=#BoneNode] setName 
-- @param self
-- @param #string name
-- @return BoneNode#BoneNode self (return value: ccs.BoneNode)
        
--------------------------------
-- 
-- @function [parent=#BoneNode] setAnchorPoint 
-- @param self
-- @param #vec2_table anchorPoint
-- @return BoneNode#BoneNode self (return value: ccs.BoneNode)
        
--------------------------------
-- 
-- @function [parent=#BoneNode] setLocalZOrder 
-- @param self
-- @param #int localZOrder
-- @return BoneNode#BoneNode self (return value: ccs.BoneNode)
        
--------------------------------
-- 
-- @function [parent=#BoneNode] removeChild 
-- @param self
-- @param #cc.Node child
-- @param #bool cleanup
-- @return BoneNode#BoneNode self (return value: ccs.BoneNode)
        
--------------------------------
-- 
-- @function [parent=#BoneNode] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#BoneNode] getBoundingBox 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- 
-- @function [parent=#BoneNode] setContentSize 
-- @param self
-- @param #size_table contentSize
-- @return BoneNode#BoneNode self (return value: ccs.BoneNode)
        
--------------------------------
-- 
-- @function [parent=#BoneNode] setVisible 
-- @param self
-- @param #bool visible
-- @return BoneNode#BoneNode self (return value: ccs.BoneNode)
        
--------------------------------
-- 
-- @function [parent=#BoneNode] BoneNode 
-- @param self
-- @return BoneNode#BoneNode self (return value: ccs.BoneNode)
        
return nil
