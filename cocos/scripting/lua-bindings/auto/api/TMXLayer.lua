
--------------------------------
-- @module TMXLayer
-- @extend Node
-- @parent_module ccexp

--------------------------------
--  returns the position in points of a given tile coordinate 
-- @function [parent=#TMXLayer] getPositionAt 
-- @param self
-- @param #vec2_table tileCoordinate
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
-- @function [parent=#TMXLayer] setLayerOrientation 
-- @param self
-- @param #int orientation
        
--------------------------------
--  size of the layer in tiles 
-- @function [parent=#TMXLayer] getLayerSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- 
-- @function [parent=#TMXLayer] setMapTileSize 
-- @param self
-- @param #size_table size
        
--------------------------------
--  Layer orientation, which is the same as the map orientation 
-- @function [parent=#TMXLayer] getLayerOrientation 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#TMXLayer] setProperties 
-- @param self
-- @param #map_table properties
        
--------------------------------
-- 
-- @function [parent=#TMXLayer] setLayerName 
-- @param self
-- @param #string layerName
        
--------------------------------
--  removes a tile at given tile coordinate 
-- @function [parent=#TMXLayer] removeTileAt 
-- @param self
-- @param #vec2_table tileCoordinate
        
--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#TMXLayer] getProperties
-- @param self
-- @return map_table#map_table ret (retunr value: map_table)

--------------------------------
--  Creates the tiles 
-- @function [parent=#TMXLayer] setupTiles 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#TMXLayer] setupTileSprite 
-- @param self
-- @param #cc.Sprite sprite
-- @param #vec2_table pos
-- @param #int gid
        
--------------------------------
-- @overload self, int, vec2_table, int         
-- @overload self, int, vec2_table         
-- @function [parent=#TMXLayer] setTileGID
-- @param self
-- @param #int gid
-- @param #vec2_table tileCoordinate
-- @param #int flags

--------------------------------
--  size of the map's tile (could be different from the tile's size) 
-- @function [parent=#TMXLayer] getMapTileSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
--  return the value for the specific property name 
-- @function [parent=#TMXLayer] getProperty 
-- @param self
-- @param #string propertyName
-- @return Value#Value ret (return value: cc.Value)
        
--------------------------------
-- 
-- @function [parent=#TMXLayer] setLayerSize 
-- @param self
-- @param #size_table size
        
--------------------------------
-- 
-- @function [parent=#TMXLayer] getLayerName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#TMXLayer] setTileSet 
-- @param self
-- @param #cc.TMXTilesetInfo info
        
--------------------------------
--  Tileset information for the layer 
-- @function [parent=#TMXLayer] getTileSet 
-- @param self
-- @return TMXTilesetInfo#TMXTilesetInfo ret (return value: cc.TMXTilesetInfo)
        
--------------------------------
--  returns the tile (Sprite) at a given a tile coordinate.<br>
-- The returned Sprite will be already added to the TMXLayer. Don't add it again.<br>
-- The Sprite can be treated like any other Sprite: rotated, scaled, translated, opacity, color, etc.<br>
-- You can remove either by calling:<br>
-- - layer->removeChild(sprite, cleanup);
-- @function [parent=#TMXLayer] getTileAt 
-- @param self
-- @param #vec2_table tileCoordinate
-- @return Sprite#Sprite ret (return value: cc.Sprite)
        
--------------------------------
--  creates a FastTMXLayer with an tileset info, a layer info and a map info 
-- @function [parent=#TMXLayer] create 
-- @param self
-- @param #cc.TMXTilesetInfo tilesetInfo
-- @param #cc.TMXLayerInfo layerInfo
-- @param #cc.TMXMapInfo mapInfo
-- @return experimental::TMXLayer#experimental::TMXLayer ret (return value: cc.experimental::TMXLayer)
        
--------------------------------
-- 
-- @function [parent=#TMXLayer] removeChild 
-- @param self
-- @param #cc.Node child
-- @param #bool cleanup
        
--------------------------------
-- 
-- @function [parent=#TMXLayer] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
        
--------------------------------
-- 
-- @function [parent=#TMXLayer] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- js ctor
-- @function [parent=#TMXLayer] TMXLayer 
-- @param self
        
return nil
