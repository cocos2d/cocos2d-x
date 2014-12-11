
--------------------------------
-- @module GridBase
-- @extend Ref
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#GridBase] setGridSize 
-- @param self
-- @param #size_table gridSize
        
--------------------------------
-- 
-- @function [parent=#GridBase] afterBlit 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#GridBase] afterDraw 
-- @param self
-- @param #cc.Node target
        
--------------------------------
-- 
-- @function [parent=#GridBase] beforeDraw 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#GridBase] calculateVertexPoints 
-- @param self
        
--------------------------------
--  is texture flipped 
-- @function [parent=#GridBase] isTextureFlipped 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  size of the grid 
-- @function [parent=#GridBase] getGridSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
--  pixels between the grids 
-- @function [parent=#GridBase] getStep 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
-- @function [parent=#GridBase] set2DProjection 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#GridBase] setStep 
-- @param self
-- @param #vec2_table step
        
--------------------------------
-- 
-- @function [parent=#GridBase] setTextureFlipped 
-- @param self
-- @param #bool flipped
        
--------------------------------
-- 
-- @function [parent=#GridBase] blit 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#GridBase] setActive 
-- @param self
-- @param #bool active
        
--------------------------------
--  number of times that the grid will be reused 
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
-- 
-- @function [parent=#GridBase] beforeBlit 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#GridBase] setReuseGrid 
-- @param self
-- @param #int reuseGrid
        
--------------------------------
--  whether or not the grid is active 
-- @function [parent=#GridBase] isActive 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#GridBase] reuse 
-- @param self
        
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
