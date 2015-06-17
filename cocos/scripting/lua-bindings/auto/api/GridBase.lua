
--------------------------------
-- @module GridBase
-- @extend Ref
-- @parent_module cc

--------------------------------
-- Set the size of the grid.
-- @function [parent=#GridBase] setGridSize 
-- @param self
-- @param #size_table gridSize
-- @return GridBase#GridBase self (return value: cc.GridBase)
        
--------------------------------
-- 
-- @function [parent=#GridBase] afterBlit 
-- @param self
-- @return GridBase#GridBase self (return value: cc.GridBase)
        
--------------------------------
-- 
-- @function [parent=#GridBase] afterDraw 
-- @param self
-- @param #cc.Node target
-- @return GridBase#GridBase self (return value: cc.GridBase)
        
--------------------------------
-- @{<br>
-- Init and reset the status when render effects by using the grid.
-- @function [parent=#GridBase] beforeDraw 
-- @param self
-- @return GridBase#GridBase self (return value: cc.GridBase)
        
--------------------------------
-- Interface, Calculate the vertices used for the blit.
-- @function [parent=#GridBase] calculateVertexPoints 
-- @param self
-- @return GridBase#GridBase self (return value: cc.GridBase)
        
--------------------------------
--  is texture flipped. 
-- @function [parent=#GridBase] isTextureFlipped 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Size of the grid. 
-- @function [parent=#GridBase] getGridSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
--  Pixels between the grids. 
-- @function [parent=#GridBase] getStep 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Change projection to 2D for grabbing.
-- @function [parent=#GridBase] set2DProjection 
-- @param self
-- @return GridBase#GridBase self (return value: cc.GridBase)
        
--------------------------------
-- Get the pixels between the grids.
-- @function [parent=#GridBase] setStep 
-- @param self
-- @param #vec2_table step
-- @return GridBase#GridBase self (return value: cc.GridBase)
        
--------------------------------
-- Set the texture flipped or not.
-- @function [parent=#GridBase] setTextureFlipped 
-- @param self
-- @param #bool flipped
-- @return GridBase#GridBase self (return value: cc.GridBase)
        
--------------------------------
-- Interface used to blit the texture with grid to screen.
-- @function [parent=#GridBase] blit 
-- @param self
-- @return GridBase#GridBase self (return value: cc.GridBase)
        
--------------------------------
-- 
-- @function [parent=#GridBase] setActive 
-- @param self
-- @param #bool active
-- @return GridBase#GridBase self (return value: cc.GridBase)
        
--------------------------------
--  Get number of times that the grid will be reused. 
-- @function [parent=#GridBase] getReuseGrid 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @overload self, size_table         
-- @overload self, size_table, cc.Texture2D, bool         
-- @function [parent=#GridBase] initWithSize
-- @param self
-- @param #size_table gridSize
-- @param #cc.Texture2D texture
-- @param #bool flipped
-- @return bool#bool ret (return value: bool)

--------------------------------
-- @{<br>
-- Interface for custom action when before or after draw.<br>
-- js NA
-- @function [parent=#GridBase] beforeBlit 
-- @param self
-- @return GridBase#GridBase self (return value: cc.GridBase)
        
--------------------------------
--  Set number of times that the grid will be reused. 
-- @function [parent=#GridBase] setReuseGrid 
-- @param self
-- @param #int reuseGrid
-- @return GridBase#GridBase self (return value: cc.GridBase)
        
--------------------------------
-- @} @{<br>
-- Getter and setter of the active state of the grid.
-- @function [parent=#GridBase] isActive 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Interface, Reuse the grid vertices.
-- @function [parent=#GridBase] reuse 
-- @param self
-- @return GridBase#GridBase self (return value: cc.GridBase)
        
--------------------------------
-- @overload self, size_table         
-- @overload self, size_table, cc.Texture2D, bool         
-- @function [parent=#GridBase] create
-- @param self
-- @param #size_table gridSize
-- @param #cc.Texture2D texture
-- @param #bool flipped
-- @return GridBase#GridBase ret (return value: cc.GridBase)

return nil
