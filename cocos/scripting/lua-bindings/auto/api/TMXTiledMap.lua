
--------------------------------
-- @module TMXTiledMap
-- @extend Node
-- @parent_module cc

--------------------------------
--  Set the object groups. <br>
-- param groups The object groups.
-- @function [parent=#TMXTiledMap] setObjectGroups 
-- @param self
-- @param #array_table groups
-- @return TMXTiledMap#TMXTiledMap self (return value: cc.TMXTiledMap)
        
--------------------------------
--  Return the value for the specific property name. <br>
-- param propertyName The specific property name.<br>
-- return Return the value for the specific property name.
-- @function [parent=#TMXTiledMap] getProperty 
-- @param self
-- @param #string propertyName
-- @return Value#Value ret (return value: cc.Value)
        
--------------------------------
--  Set the map's size property measured in tiles. <br>
-- param mapSize The map's size property measured in tiles.
-- @function [parent=#TMXTiledMap] setMapSize 
-- @param self
-- @param #size_table mapSize
-- @return TMXTiledMap#TMXTiledMap self (return value: cc.TMXTiledMap)
        
--------------------------------
--  Return the TMXObjectGroup for the specific group. <br>
-- param groupName The group Name.<br>
-- return A Type of TMXObjectGroup.
-- @function [parent=#TMXTiledMap] getObjectGroup 
-- @param self
-- @param #string groupName
-- @return TMXObjectGroup#TMXObjectGroup ret (return value: cc.TMXObjectGroup)
        
--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#TMXTiledMap] getObjectGroups
-- @param self
-- @return array_table#array_table ret (return value: array_table)

--------------------------------
--  initializes a TMX Tiled Map with a TMX formatted XML string and a path to TMX resources 
-- @function [parent=#TMXTiledMap] initWithXML 
-- @param self
-- @param #string tmxString
-- @param #string resourcePath
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  initializes a TMX Tiled Map with a TMX file 
-- @function [parent=#TMXTiledMap] initWithTMXFile 
-- @param self
-- @param #string tmxFile
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  The tiles's size property measured in pixels. <br>
-- return The tiles's size property measured in pixels.
-- @function [parent=#TMXTiledMap] getTileSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
--  The map's size property measured in tiles. <br>
-- return The map's size property measured in tiles.
-- @function [parent=#TMXTiledMap] getMapSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
--  Properties. <br>
-- return Properties.
-- @function [parent=#TMXTiledMap] getProperties 
-- @param self
-- @return map_table#map_table ret (return value: map_table)
        
--------------------------------
--  Set the tiles's size property measured in pixels. <br>
-- param tileSize The tiles's size property measured in pixels.
-- @function [parent=#TMXTiledMap] setTileSize 
-- @param self
-- @param #size_table tileSize
-- @return TMXTiledMap#TMXTiledMap self (return value: cc.TMXTiledMap)
        
--------------------------------
--  Set the properties.<br>
-- param properties A  Type of ValueMap to set the properties.
-- @function [parent=#TMXTiledMap] setProperties 
-- @param self
-- @param #map_table properties
-- @return TMXTiledMap#TMXTiledMap self (return value: cc.TMXTiledMap)
        
--------------------------------
--  Return the TMXLayer for the specific layer. <br>
-- param layerName A specific layer.<br>
-- return The TMXLayer for the specific layer.
-- @function [parent=#TMXTiledMap] getLayer 
-- @param self
-- @param #string layerName
-- @return TMXLayer#TMXLayer ret (return value: cc.TMXLayer)
        
--------------------------------
--  Map orientation. <br>
-- return Map orientation.
-- @function [parent=#TMXTiledMap] getMapOrientation 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Set map orientation. <br>
-- param mapOrientation The map orientation.
-- @function [parent=#TMXTiledMap] setMapOrientation 
-- @param self
-- @param #int mapOrientation
-- @return TMXTiledMap#TMXTiledMap self (return value: cc.TMXTiledMap)
        
--------------------------------
--  Creates a TMX Tiled Map with a TMX file.<br>
-- param tmxFile A TMX file.<br>
-- return An autorelease object.
-- @function [parent=#TMXTiledMap] create 
-- @param self
-- @param #string tmxFile
-- @return TMXTiledMap#TMXTiledMap ret (return value: cc.TMXTiledMap)
        
--------------------------------
--  Initializes a TMX Tiled Map with a TMX formatted XML string and a path to TMX resources. <br>
-- param tmxString A TMX formatted XML string.<br>
-- param resourcePath The path to TMX resources.<br>
-- return An autorelease object.<br>
-- js NA
-- @function [parent=#TMXTiledMap] createWithXML 
-- @param self
-- @param #string tmxString
-- @param #string resourcePath
-- @return TMXTiledMap#TMXTiledMap ret (return value: cc.TMXTiledMap)
        
--------------------------------
--  Get the description.<br>
-- js NA
-- @function [parent=#TMXTiledMap] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- js ctor
-- @function [parent=#TMXTiledMap] TMXTiledMap 
-- @param self
-- @return TMXTiledMap#TMXTiledMap self (return value: cc.TMXTiledMap)
        
return nil
