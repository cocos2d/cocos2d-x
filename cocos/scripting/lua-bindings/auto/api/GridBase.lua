
--------------------------------
-- @module GridBase
-- @extend Ref
-- @parent_module cc

--------------------------------
-- @function [parent=#GridBase] setGridSize 
-- @param self
-- @param #size_table size
        
--------------------------------
-- @function [parent=#GridBase] calculateVertexPoints 
-- @param self
        
--------------------------------
-- @function [parent=#GridBase] afterDraw 
-- @param self
-- @param #cc.Node node
        
--------------------------------
-- @function [parent=#GridBase] beforeDraw 
-- @param self
        
--------------------------------
-- @function [parent=#GridBase] isTextureFlipped 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#GridBase] getGridSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#GridBase] getStep 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#GridBase] set2DProjection 
-- @param self
        
--------------------------------
-- @function [parent=#GridBase] setStep 
-- @param self
-- @param #vec2_table vec2
        
--------------------------------
-- @function [parent=#GridBase] setTextureFlipped 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#GridBase] blit 
-- @param self
        
--------------------------------
-- @function [parent=#GridBase] setActive 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#GridBase] getReuseGrid 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @overload self, size_table         
-- @overload self, size_table, cc.Texture2D, bool         
-- @function [parent=#GridBase] initWithSize
-- @param self
-- @param #size_table size
-- @param #cc.Texture2D texture2d
-- @param #bool bool
-- @return bool#bool ret (retunr value: bool)

--------------------------------
-- @function [parent=#GridBase] setReuseGrid 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#GridBase] isActive 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#GridBase] reuse 
-- @param self
        
--------------------------------
-- @overload self, size_table         
-- @overload self, size_table, cc.Texture2D, bool         
-- @function [parent=#GridBase] create
-- @param self
-- @param #size_table size
-- @param #cc.Texture2D texture2d
-- @param #bool bool
-- @return GridBase#GridBase ret (retunr value: cc.GridBase)

return nil
