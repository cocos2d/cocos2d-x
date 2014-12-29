
--------------------------------
-- @module ActionTimelineNode
-- @extend Node
-- @parent_module ccs

--------------------------------
-- 
-- @function [parent=#ActionTimelineNode] getRoot 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#ActionTimelineNode] getActionTimeline 
-- @param self
-- @return ActionTimeline#ActionTimeline ret (return value: ccs.ActionTimeline)
        
--------------------------------
-- 
-- @function [parent=#ActionTimelineNode] setActionTimeline 
-- @param self
-- @param #ccs.ActionTimeline action
        
--------------------------------
-- @overload self, cc.Node, ccs.ActionTimeline         
-- @overload self         
-- @function [parent=#ActionTimelineNode] init
-- @param self
-- @param #cc.Node root
-- @param #ccs.ActionTimeline action
-- @return bool#bool ret (return value: bool)

--------------------------------
-- 
-- @function [parent=#ActionTimelineNode] setRoot 
-- @param self
-- @param #cc.Node root
        
--------------------------------
-- 
-- @function [parent=#ActionTimelineNode] create 
-- @param self
-- @param #cc.Node root
-- @param #ccs.ActionTimeline action
-- @return ActionTimelineNode#ActionTimelineNode ret (return value: ccs.ActionTimelineNode)
        
--------------------------------
-- 
-- @function [parent=#ActionTimelineNode] ActionTimelineNode 
-- @param self
        
return nil
