
--------------------------------
-- @module FadeOutUpTiles
-- @extend FadeOutTRTiles
-- @parent_module cc

--------------------------------
-- brief Create the action with the grid size and the duration.<br>
-- param duration Specify the duration of the FadeOutUpTiles action. It's a value in seconds.<br>
-- param gridSize Specify the size of the grid.<br>
-- return If the creation success, return a pointer of FadeOutUpTiles action; otherwise, return nil.
-- @function [parent=#FadeOutUpTiles] create 
-- @param self
-- @param #float duration
-- @param #size_table gridSize
-- @return FadeOutUpTiles#FadeOutUpTiles ret (return value: cc.FadeOutUpTiles)
        
--------------------------------
-- 
-- @function [parent=#FadeOutUpTiles] clone 
-- @param self
-- @return FadeOutUpTiles#FadeOutUpTiles ret (return value: cc.FadeOutUpTiles)
        
--------------------------------
-- 
-- @function [parent=#FadeOutUpTiles] transformTile 
-- @param self
-- @param #vec2_table pos
-- @param #float distance
-- @return FadeOutUpTiles#FadeOutUpTiles self (return value: cc.FadeOutUpTiles)
        
--------------------------------
-- 
-- @function [parent=#FadeOutUpTiles] testFunc 
-- @param self
-- @param #size_table pos
-- @param #float time
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#FadeOutUpTiles] FadeOutUpTiles 
-- @param self
-- @return FadeOutUpTiles#FadeOutUpTiles self (return value: cc.FadeOutUpTiles)
        
return nil
