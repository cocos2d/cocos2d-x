
--------------------------------
-- @module DisplayManager
-- @extend Ref

--------------------------------
-- @function [parent=#DisplayManager] getDisplayRenderNode 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- @function [parent=#DisplayManager] getAnchorPointInPoints 
-- @param self
-- @return Vec2#Vec2 ret (return value: cc.Vec2)
        
--------------------------------
-- @function [parent=#DisplayManager] getDisplayRenderNodeType 
-- @param self
-- @return DisplayType#DisplayType ret (return value: ccs.DisplayType)
        
--------------------------------
-- @function [parent=#DisplayManager] removeDisplay 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#DisplayManager] setForceChangeDisplay 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#DisplayManager] init 
-- @param self
-- @param #ccs.Bone bone
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#DisplayManager] getContentSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#DisplayManager] getBoundingBox 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- overload function: addDisplay(cc.Node, int)
--          
-- overload function: addDisplay(ccs.DisplayData, int)
--          
-- @function [parent=#DisplayManager] addDisplay
-- @param self
-- @param #ccs.DisplayData displaydata
-- @param #int int

--------------------------------
-- overload function: containPoint(float, float)
--          
-- overload function: containPoint(cc.Vec2)
--          
-- @function [parent=#DisplayManager] containPoint
-- @param self
-- @param #float float
-- @param #float float
-- @return bool#bool ret (retunr value: bool)

--------------------------------
-- @function [parent=#DisplayManager] changeDisplayWithIndex 
-- @param self
-- @param #int int
-- @param #bool bool
        
--------------------------------
-- @function [parent=#DisplayManager] changeDisplayWithName 
-- @param self
-- @param #string str
-- @param #bool bool
        
--------------------------------
-- @function [parent=#DisplayManager] isForceChangeDisplay 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#DisplayManager] getCurrentDisplayIndex 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#DisplayManager] getAnchorPoint 
-- @param self
-- @return Vec2#Vec2 ret (return value: cc.Vec2)
        
--------------------------------
-- @function [parent=#DisplayManager] getDecorativeDisplayList 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- @function [parent=#DisplayManager] isVisible 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#DisplayManager] setVisible 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#DisplayManager] create 
-- @param self
-- @param #ccs.Bone bone
-- @return DisplayManager#DisplayManager ret (return value: ccs.DisplayManager)
        
--------------------------------
-- @function [parent=#DisplayManager] DisplayManager 
-- @param self
        
return nil
