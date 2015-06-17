
--------------------------------
-- @module SpritePolygon
-- @extend Node
-- @parent_module ccexp

--------------------------------
-- @overload self, cc.Texture2D         
-- @overload self, string         
-- @function [parent=#SpritePolygon] setTexture
-- @param self
-- @param #string filename
-- @return experimental::SpritePolygon#experimental::SpritePolygon self (return value: cc.experimental::SpritePolygon)

--------------------------------
-- 
-- @function [parent=#SpritePolygon] initWithTexture 
-- @param self
-- @param #cc.Texture2D texture
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#SpritePolygon] showDebug 
-- @param self
-- @param #bool val
-- @return experimental::SpritePolygon#experimental::SpritePolygon self (return value: cc.experimental::SpritePolygon)
        
--------------------------------
--  returns the Texture2D object used by the sprite 
-- @function [parent=#SpritePolygon] getTexture 
-- @param self
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)
        
--------------------------------
-- 
-- @function [parent=#SpritePolygon] getArea 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#SpritePolygon] initWithCache 
-- @param self
-- @param #string file
-- @param #cc._SpritePolygonInfo info
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#SpritePolygon] getVertCount 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- 
-- @function [parent=#SpritePolygon] getTrianglesCount 
-- @param self
-- @return long#long ret (return value: long)
        
return nil
