
--------------------------------
-- @module TMXLayer
-- @extend Node
-- @parent_module ccexp

--------------------------------
-- @function [parent=#TMXLayer] getPositionAt 
-- @param self
-- @param #vec2_table vec2
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @function [parent=#TMXLayer] setLayerOrientation 
-- @param self
-- @param #int int
        
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
-- @param #vec2_table vec2
        
--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#TMXLayer] getProperties
-- @param self
-- @return map_table#map_table ret (retunr value: map_table)

--------------------------------
-- @function [parent=#TMXLayer] setupTiles 
-- @param self
        
--------------------------------
-- @function [parent=#TMXLayer] setupTileSprite 
-- @param self
-- @param #cc.Sprite sprite
-- @param #vec2_table vec2
-- @param #int int
        
--------------------------------
-- @overload self, int, vec2_table, int         
-- @overload self, int, vec2_table         
-- @function [parent=#TMXLayer] setTileGID
-- @param self
-- @param #int int
-- @param #vec2_table vec2
-- @param #int tmxtileflags_

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
-- @function [parent=#TMXLayer] getTileAt 
-- @param self
-- @param #vec2_table vec2
-- @return Sprite#Sprite ret (return value: cc.Sprite)
        
--------------------------------
-- @function [parent=#TMXLayer] create 
-- @param self
-- @param #cc.TMXTilesetInfo tmxtilesetinfo
-- @param #cc.TMXLayerInfo tmxlayerinfo
-- @param #cc.TMXMapInfo map
-- @return experimental::TMXLayer#experimental::TMXLayer ret (return value: cc.experimental::TMXLayer)
        
--------------------------------
-- @function [parent=#TMXLayer] removeChild 
-- @param self
-- @param #cc.Node node
-- @param #bool bool
        
--------------------------------
-- @function [parent=#TMXLayer] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table mat4
-- @param #unsigned int int
        
--------------------------------
-- @function [parent=#TMXLayer] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#TMXLayer] TMXLayer 
-- @param self
        
return nil
