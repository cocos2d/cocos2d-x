
--------------------------------
-- @module Timeline
-- @extend Ref
-- @parent_module ccs

--------------------------------
-- 
-- @function [parent=#Timeline] clone 
-- @param self
-- @return Timeline#Timeline ret (return value: ccs.Timeline)
        
--------------------------------
-- 
-- @function [parent=#Timeline] gotoFrame 
-- @param self
-- @param #int frameIndex
-- @return Timeline#Timeline self (return value: ccs.Timeline)
        
--------------------------------
-- 
-- @function [parent=#Timeline] setNode 
-- @param self
-- @param #cc.Node node
-- @return Timeline#Timeline self (return value: ccs.Timeline)
        
--------------------------------
-- 
-- @function [parent=#Timeline] getActionTimeline 
-- @param self
-- @return ActionTimeline#ActionTimeline ret (return value: ccs.ActionTimeline)
        
--------------------------------
-- 
-- @function [parent=#Timeline] insertFrame 
-- @param self
-- @param #ccs.Frame frame
-- @param #int index
-- @return Timeline#Timeline self (return value: ccs.Timeline)
        
--------------------------------
-- 
-- @function [parent=#Timeline] setActionTag 
-- @param self
-- @param #int tag
-- @return Timeline#Timeline self (return value: ccs.Timeline)
        
--------------------------------
-- 
-- @function [parent=#Timeline] addFrame 
-- @param self
-- @param #ccs.Frame frame
-- @return Timeline#Timeline self (return value: ccs.Timeline)
        
--------------------------------
-- 
-- @function [parent=#Timeline] getFrames 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- 
-- @function [parent=#Timeline] getActionTag 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#Timeline] getNode 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#Timeline] removeFrame 
-- @param self
-- @param #ccs.Frame frame
-- @return Timeline#Timeline self (return value: ccs.Timeline)
        
--------------------------------
-- 
-- @function [parent=#Timeline] setActionTimeline 
-- @param self
-- @param #ccs.ActionTimeline action
-- @return Timeline#Timeline self (return value: ccs.Timeline)
        
--------------------------------
-- 
-- @function [parent=#Timeline] stepToFrame 
-- @param self
-- @param #int frameIndex
-- @return Timeline#Timeline self (return value: ccs.Timeline)
        
--------------------------------
-- 
-- @function [parent=#Timeline] create 
-- @param self
-- @return Timeline#Timeline ret (return value: ccs.Timeline)
        
--------------------------------
-- 
-- @function [parent=#Timeline] Timeline 
-- @param self
-- @return Timeline#Timeline self (return value: ccs.Timeline)
        
return nil
