
--------------------------------
-- @module FastTMXLayer
-- @extend Node
-- @parent_module cc

--------------------------------
-- @function [parent=#FastTMXLayer] getPositionAt 
-- @param self
-- @param #vec2_table vec2
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#FastTMXLayer] setLayerOrientation 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#FastTMXLayer] getLayerSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#FastTMXLayer] setMapTileSize 
-- @param self
-- @param #size_table size
        
--------------------------------
-- @function [parent=#FastTMXLayer] getLayerOrientation 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#FastTMXLayer] setProperties 
-- @param self
-- @param #map_table map
        
--------------------------------
-- @function [parent=#FastTMXLayer] setLayerName 
-- @param self
-- @param #string str
        
--------------------------------
-- @function [parent=#FastTMXLayer] removeTileAt 
-- @param self
-- @param #vec2_table vec2
        
--------------------------------
-- overload function: getProperties()
--          
-- overload function: getProperties()
--          
-- @function [parent=#FastTMXLayer] getProperties
-- @param self
-- @return map_table#map_table ret (retunr value: map_table)

--------------------------------
-- @function [parent=#FastTMXLayer] setupTiles 
-- @param self
        
--------------------------------
-- @function [parent=#FastTMXLayer] setupTileSprite 
-- @param self
-- @param #cc.Sprite sprite
-- @param #vec2_table vec2
-- @param #int int
        
--------------------------------
-- overload function: setTileGID(int, vec2_table, cc.TMXTileFlags_)
--          
-- overload function: setTileGID(int, vec2_table)
--          
-- @function [parent=#FastTMXLayer] setTileGID
-- @param self
-- @param #int int
-- @param #vec2_table vec2
-- @param #cc.TMXTileFlags_ tmxtileflags_

--------------------------------
-- @function [parent=#FastTMXLayer] getMapTileSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#FastTMXLayer] getProperty 
-- @param self
-- @param #string str
-- @return Value#Value ret (return value: cc.Value)
        
--------------------------------
-- @function [parent=#FastTMXLayer] setLayerSize 
-- @param self
-- @param #size_table size
        
--------------------------------
-- @function [parent=#FastTMXLayer] getLayerName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#FastTMXLayer] setTileSet 
-- @param self
-- @param #cc.TMXTilesetInfo tmxtilesetinfo
        
--------------------------------
-- @function [parent=#FastTMXLayer] getTileSet 
-- @param self
-- @return TMXTilesetInfo#TMXTilesetInfo ret (return value: cc.TMXTilesetInfo)
        
--------------------------------
-- @function [parent=#FastTMXLayer] getTileAt 
-- @param self
-- @param #vec2_table vec2
-- @return Sprite#Sprite ret (return value: cc.Sprite)
        
--------------------------------
-- @function [parent=#FastTMXLayer] create 
-- @param self
-- @param #cc.TMXTilesetInfo tmxtilesetinfo
-- @param #cc.TMXLayerInfo tmxlayerinfo
-- @param #cc.TMXMapInfo map
-- @return FastTMXLayer#FastTMXLayer ret (return value: cc.FastTMXLayer)
        
--------------------------------
-- @function [parent=#FastTMXLayer] removeChild 
-- @param self
-- @param #cc.Node node
-- @param #bool bool
        
--------------------------------
-- @function [parent=#FastTMXLayer] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table mat4
-- @param #unsigned int int
        
--------------------------------
-- @function [parent=#FastTMXLayer] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#FastTMXLayer] FastTMXLayer 
-- @param self
        
return nil
