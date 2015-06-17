
--------------------------------
-- @module PolygonInfo
-- @parent_module cc

--------------------------------
-- get sum of all triangle area size<br>
-- return sum of all triangle area size
-- @function [parent=#PolygonInfo] getArea 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- get triangles count<br>
-- return number of triangles
-- @function [parent=#PolygonInfo] getTriaglesCount 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- get vertex count<br>
-- return number of vertices
-- @function [parent=#PolygonInfo] getVertCount 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- set the data to be a pointer to a quad<br>
-- the member verts will not be released when this PolygonInfo destructs<br>
-- as the verts memory are managed by other objects<br>
-- param quad  a pointer to the V3F_C4B_T2F_Quad obje
-- @function [parent=#PolygonInfo] setQuad 
-- @param self
-- @param #cc.V3F_C4B_T2F_Quad quad
-- @return PolygonInfo#PolygonInfo self (return value: cc.PolygonInfo)
        
--------------------------------
-- / @name Creators/ @{<br>
-- Creates an empty Polygon info<br>
-- memberof PolygonInfo<br>
-- return PolygonInfo object
-- @function [parent=#PolygonInfo] PolygonInfo 
-- @param self
-- @return PolygonInfo#PolygonInfo self (return value: cc.PolygonInfo)
        
return nil
