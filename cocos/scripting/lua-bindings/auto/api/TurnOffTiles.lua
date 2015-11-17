
--------------------------------
-- @module TurnOffTiles
-- @extend TiledGrid3DAction
-- @parent_module cc

--------------------------------
-- brief Show the tile at specified position.<br>
-- param pos The position index of the tile should be shown.
-- @function [parent=#TurnOffTiles] turnOnTile 
-- @param self
-- @param #vec2_table pos
-- @return TurnOffTiles#TurnOffTiles self (return value: cc.TurnOffTiles)
        
--------------------------------
-- brief Hide the tile at specified position.<br>
-- param pos The position index of the tile should be hide.
-- @function [parent=#TurnOffTiles] turnOffTile 
-- @param self
-- @param #vec2_table pos
-- @return TurnOffTiles#TurnOffTiles self (return value: cc.TurnOffTiles)
        
--------------------------------
-- brief Initializes the action with grid size, random seed and duration.<br>
-- param duration Specify the duration of the TurnOffTiles action. It's a value in seconds.<br>
-- param gridSize Specify the size of the grid.<br>
-- param seed Specify the random seed.<br>
-- return If the Initialization success, return true; otherwise, return false.
-- @function [parent=#TurnOffTiles] initWithDuration 
-- @param self
-- @param #float duration
-- @param #size_table gridSize
-- @param #unsigned int seed
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @overload self, float, size_table, unsigned int         
-- @overload self, float, size_table         
-- @function [parent=#TurnOffTiles] create
-- @param self
-- @param #float duration
-- @param #size_table gridSize
-- @param #unsigned int seed
-- @return TurnOffTiles#TurnOffTiles ret (return value: cc.TurnOffTiles)

--------------------------------
-- 
-- @function [parent=#TurnOffTiles] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return TurnOffTiles#TurnOffTiles self (return value: cc.TurnOffTiles)
        
--------------------------------
-- 
-- @function [parent=#TurnOffTiles] clone 
-- @param self
-- @return TurnOffTiles#TurnOffTiles ret (return value: cc.TurnOffTiles)
        
--------------------------------
-- 
-- @function [parent=#TurnOffTiles] update 
-- @param self
-- @param #float time
-- @return TurnOffTiles#TurnOffTiles self (return value: cc.TurnOffTiles)
        
--------------------------------
-- 
-- @function [parent=#TurnOffTiles] TurnOffTiles 
-- @param self
-- @return TurnOffTiles#TurnOffTiles self (return value: cc.TurnOffTiles)
        
return nil
