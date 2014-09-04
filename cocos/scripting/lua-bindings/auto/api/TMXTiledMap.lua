
--------------------------------
-- @module TMXTiledMap
-- @extend Node
-- @parent_module ccexp

--------------------------------
-- 
-- @function [parent=#TMXTiledMap] setObjectGroups 
-- @param self
-- @param #array_table groups
        
--------------------------------
--  return the value for the specific property name 
-- @function [parent=#TMXTiledMap] getProperty 
-- @param self
-- @param #string propertyName
-- @return Value#Value ret (return value: cc.Value)
        
--------------------------------
-- 
-- @function [parent=#TMXTiledMap] setMapSize 
-- @param self
-- @param #size_table mapSize
        
--------------------------------
--  return the TMXObjectGroup for the specific group 
-- @function [parent=#TMXTiledMap] getObjectGroup 
-- @param self
-- @param #string groupName
-- @return TMXObjectGroup#TMXObjectGroup ret (return value: cc.TMXObjectGroup)
        
--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#TMXTiledMap] getObjectGroups
-- @param self
-- @return array_table#array_table ret (retunr value: array_table)

--------------------------------
--  the tiles's size property measured in pixels 
-- @function [parent=#TMXTiledMap] getTileSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
--  the map's size property measured in tiles 
-- @function [parent=#TMXTiledMap] getMapSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
--  properties 
-- @function [parent=#TMXTiledMap] getProperties 
-- @param self
-- @return map_table#map_table ret (return value: map_table)
        
--------------------------------
--  return properties dictionary for tile GID 
-- @function [parent=#TMXTiledMap] getPropertiesForGID 
-- @param self
-- @param #int GID
-- @return Value#Value ret (return value: cc.Value)
        
--------------------------------
-- 
-- @function [parent=#TMXTiledMap] setTileSize 
-- @param self
-- @param #size_table tileSize
        
--------------------------------
-- 
-- @function [parent=#TMXTiledMap] setProperties 
-- @param self
-- @param #map_table properties
        
--------------------------------
--  return the FastTMXLayer for the specific layer 
-- @function [parent=#TMXTiledMap] getLayer 
-- @param self
-- @param #string layerName
-- @return experimental::TMXLayer#experimental::TMXLayer ret (return value: cc.experimental::TMXLayer)
        
--------------------------------
--  map orientation 
-- @function [parent=#TMXTiledMap] getMapOrientation 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#TMXTiledMap] setMapOrientation 
-- @param self
-- @param #int mapOrientation
        
--------------------------------
--  creates a TMX Tiled Map with a TMX file.
-- @function [parent=#TMXTiledMap] create 
-- @param self
-- @param #string tmxFile
-- @return experimental::TMXTiledMap#experimental::TMXTiledMap ret (return value: cc.experimental::TMXTiledMap)
        
--------------------------------
--  initializes a TMX Tiled Map with a TMX formatted XML string and a path to TMX resources 
-- @function [parent=#TMXTiledMap] createWithXML 
-- @param self
-- @param #string tmxString
-- @param #string resourcePath
-- @return experimental::TMXTiledMap#experimental::TMXTiledMap ret (return value: cc.experimental::TMXTiledMap)
        
--------------------------------
-- 
-- @function [parent=#TMXTiledMap] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
return nil
