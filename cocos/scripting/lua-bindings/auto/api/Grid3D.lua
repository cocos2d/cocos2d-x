
--------------------------------
-- @module Grid3D
-- @extend GridBase
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#Grid3D] getNeedDepthTestForBlit 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @{<br>
-- Getter and Setter for depth test state when blit.<br>
-- js NA
-- @function [parent=#Grid3D] setNeedDepthTestForBlit 
-- @param self
-- @param #bool neededDepthTest
-- @return Grid3D#Grid3D self (return value: cc.Grid3D)
        
--------------------------------
-- @overload self, size_table, rect_table         
-- @overload self, size_table         
-- @overload self, size_table, cc.Texture2D, bool         
-- @overload self, size_table, cc.Texture2D, bool, rect_table         
-- @function [parent=#Grid3D] create
-- @param self
-- @param #size_table gridSize
-- @param #cc.Texture2D texture
-- @param #bool flipped
-- @param #rect_table rect
-- @return Grid3D#Grid3D ret (return value: cc.Grid3D)

--------------------------------
-- 
-- @function [parent=#Grid3D] calculateVertexPoints 
-- @param self
-- @return Grid3D#Grid3D self (return value: cc.Grid3D)
        
--------------------------------
-- @{<br>
-- Implementations for interfaces in base class.
-- @function [parent=#Grid3D] beforeBlit 
-- @param self
-- @return Grid3D#Grid3D self (return value: cc.Grid3D)
        
--------------------------------
-- 
-- @function [parent=#Grid3D] afterBlit 
-- @param self
-- @return Grid3D#Grid3D self (return value: cc.Grid3D)
        
--------------------------------
-- 
-- @function [parent=#Grid3D] reuse 
-- @param self
-- @return Grid3D#Grid3D self (return value: cc.Grid3D)
        
--------------------------------
-- 
-- @function [parent=#Grid3D] blit 
-- @param self
-- @return Grid3D#Grid3D self (return value: cc.Grid3D)
        
--------------------------------
-- Constructor.<br>
-- js ctor
-- @function [parent=#Grid3D] Grid3D 
-- @param self
-- @return Grid3D#Grid3D self (return value: cc.Grid3D)
        
return nil
