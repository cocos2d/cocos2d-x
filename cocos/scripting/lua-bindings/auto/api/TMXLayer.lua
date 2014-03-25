
--------------------------------
-- @module TMXLayer
-- @extend SpriteBatchNode

--------------------------------
-- @function [parent=#TMXLayer] getTileGIDAt 
-- @param self
-- @param #point_table point
-- @param #cc.TMXTileFlags_ tmxtileflags_
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- @function [parent=#TMXLayer] getPositionAt 
-- @param self
-- @param #point_table point
-- @return point_table#point_table ret (return value: point_table)
        
--------------------------------
-- @function [parent=#TMXLayer] setLayerOrientation 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#TMXLayer] releaseMap 
-- @param self
        
--------------------------------
-- @function [parent=#TMXLayer] setTiles 
-- @param self
-- @param #unsigned int int
        
--------------------------------
-- @function [parent=#TMXLayer] getLayerSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#TMXLayer] setMapTileSize 
-- @param self
-- @param #size_table size
        
--------------------------------
-- @function [parent=#TMXLayer] getLayerOrientation 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#TMXLayer] setProperties 
-- @param self
-- @param #map_table map
        
--------------------------------
-- @function [parent=#TMXLayer] setLayerName 
-- @param self
-- @param #string str
        
--------------------------------
-- @function [parent=#TMXLayer] removeTileAt 
-- @param self
-- @param #point_table point
        
--------------------------------
-- @function [parent=#TMXLayer] initWithTilesetInfo 
-- @param self
-- @param #cc.TMXTilesetInfo tmxtilesetinfo
-- @param #cc.TMXLayerInfo tmxlayerinfo
-- @param #cc.TMXMapInfo map
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#TMXLayer] setupTiles 
-- @param self
        
--------------------------------
-- overload function: setTileGID(unsigned int, point_table, cc.TMXTileFlags_)
--          
-- overload function: setTileGID(unsigned int, point_table)
--          
-- @function [parent=#TMXLayer] setTileGID
-- @param self
-- @param #unsigned int int
-- @param #point_table point
-- @param #cc.TMXTileFlags_ tmxtileflags_

--------------------------------
-- @function [parent=#TMXLayer] getMapTileSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#TMXLayer] getProperty 
-- @param self
-- @param #string str
-- @return Value#Value ret (return value: cc.Value)
        
--------------------------------
-- @function [parent=#TMXLayer] setLayerSize 
-- @param self
-- @param #size_table size
        
--------------------------------
-- @function [parent=#TMXLayer] getLayerName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#TMXLayer] setTileSet 
-- @param self
-- @param #cc.TMXTilesetInfo tmxtilesetinfo
        
--------------------------------
-- @function [parent=#TMXLayer] getTileSet 
-- @param self
-- @return TMXTilesetInfo#TMXTilesetInfo ret (return value: cc.TMXTilesetInfo)
        
--------------------------------
-- overload function: getProperties()
--          
-- overload function: getProperties()
--          
-- @function [parent=#TMXLayer] getProperties
-- @param self
-- @return map_table#map_table ret (retunr value: map_table)

--------------------------------
-- @function [parent=#TMXLayer] getTileAt 
-- @param self
-- @param #point_table point
-- @return Sprite#Sprite ret (return value: cc.Sprite)
        
--------------------------------
-- @function [parent=#TMXLayer] create 
-- @param self
-- @param #cc.TMXTilesetInfo tmxtilesetinfo
-- @param #cc.TMXLayerInfo tmxlayerinfo
-- @param #cc.TMXMapInfo map
-- @return TMXLayer#TMXLayer ret (return value: cc.TMXLayer)
        
--------------------------------
-- @function [parent=#TMXLayer] addChild 
-- @param self
-- @param #cc.Node node
-- @param #int int
-- @param #int int
        
--------------------------------
-- @function [parent=#TMXLayer] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#TMXLayer] removeChild 
-- @param self
-- @param #cc.Node node
-- @param #bool bool
        
--------------------------------
-- @function [parent=#TMXLayer] TMXLayer 
-- @param self
        
return nil
