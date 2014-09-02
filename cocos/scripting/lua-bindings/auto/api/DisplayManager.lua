
--------------------------------
-- @module DisplayManager
-- @extend Ref
-- @parent_module ccs

--------------------------------
-- 
-- @function [parent=#DisplayManager] getDisplayRenderNode 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#DisplayManager] getAnchorPointInPoints 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
-- @function [parent=#DisplayManager] getDisplayRenderNodeType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#DisplayManager] removeDisplay 
-- @param self
-- @param #int index
        
--------------------------------
-- 
-- @function [parent=#DisplayManager] setForceChangeDisplay 
-- @param self
-- @param #bool force
        
--------------------------------
-- 
-- @function [parent=#DisplayManager] init 
-- @param self
-- @param #ccs.Bone bone
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#DisplayManager] getContentSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- 
-- @function [parent=#DisplayManager] getBoundingBox 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- @overload self, cc.Node, int         
-- @overload self, ccs.DisplayData, int         
-- @function [parent=#DisplayManager] addDisplay
-- @param self
-- @param #ccs.DisplayData displayData
-- @param #int index

--------------------------------
-- @overload self, float, float         
-- @overload self, vec2_table         
-- @function [parent=#DisplayManager] containPoint
-- @param self
-- @param #float x
-- @param #float y
-- @return bool#bool ret (retunr value: bool)

--------------------------------
-- Change display by index. You can just use this method to change display in the display list.<br>
-- The display list is just used for this bone, and it is the displays you may use in every frame.<br>
-- Note : if index is the same with prev index, the method will not effect<br>
-- param index The index of the display you want to change<br>
-- param force If true, then force change display to specified display, or current display will set to  display index edit in the flash every key frame.
-- @function [parent=#DisplayManager] changeDisplayWithIndex 
-- @param self
-- @param #int index
-- @param #bool force
        
--------------------------------
-- 
-- @function [parent=#DisplayManager] changeDisplayWithName 
-- @param self
-- @param #string name
-- @param #bool force
        
--------------------------------
-- 
-- @function [parent=#DisplayManager] isForceChangeDisplay 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#DisplayManager] getCurrentDisplayIndex 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#DisplayManager] getAnchorPoint 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
-- @function [parent=#DisplayManager] getDecorativeDisplayList 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- Determines if the display is visible<br>
-- see setVisible(bool)<br>
-- return true if the node is visible, false if the node is hidden.
-- @function [parent=#DisplayManager] isVisible 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Sets whether the display is visible<br>
-- The default value is true, a node is default to visible<br>
-- param visible   true if the node is visible, false if the node is hidden.
-- @function [parent=#DisplayManager] setVisible 
-- @param self
-- @param #bool visible
        
--------------------------------
-- 
-- @function [parent=#DisplayManager] create 
-- @param self
-- @param #ccs.Bone bone
-- @return DisplayManager#DisplayManager ret (return value: ccs.DisplayManager)
        
--------------------------------
-- 
-- @function [parent=#DisplayManager] DisplayManager 
-- @param self
        
return nil
