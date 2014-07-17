
--------------------------------
-- @module TMXTiledMap
-- @extend Node
-- @parent_module ccexp

--------------------------------
-- @function [parent=#TMXTiledMap] setObjectGroups 
-- @param self
-- @param #array_table array
        
--------------------------------
-- @function [parent=#TMXTiledMap] getProperty 
-- @param self
-- @param #string str
-- @return Value#Value ret (return value: cc.Value)
        
--------------------------------
-- @function [parent=#TMXTiledMap] setMapSize 
-- @param self
-- @param #size_table size
        
--------------------------------
-- @function [parent=#TMXTiledMap] getObjectGroup 
-- @param self
-- @param #string str
-- @return TMXObjectGroup#TMXObjectGroup ret (return value: cc.TMXObjectGroup)
        
--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#TMXTiledMap] getObjectGroups
-- @param self
-- @return array_table#array_table ret (retunr value: array_table)

--------------------------------
-- @function [parent=#TMXTiledMap] getTileSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#TMXTiledMap] getMapSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#TMXTiledMap] getProperties 
-- @param self
-- @return map_table#map_table ret (return value: map_table)
        
--------------------------------
-- @function [parent=#TMXTiledMap] getPropertiesForGID 
-- @param self
-- @param #int int
-- @return Value#Value ret (return value: cc.Value)
        
--------------------------------
-- @function [parent=#TMXTiledMap] setTileSize 
-- @param self
-- @param #size_table size
        
--------------------------------
-- @function [parent=#TMXTiledMap] setProperties 
-- @param self
-- @param #map_table map
        
--------------------------------
-- @function [parent=#TMXTiledMap] getLayer 
-- @param self
-- @param #string str
-- @return experimental::TMXLayer#experimental::TMXLayer ret (return value: cc.experimental::TMXLayer)
        
--------------------------------
-- @function [parent=#TMXTiledMap] getMapOrientation 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#TMXTiledMap] setMapOrientation 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#TMXTiledMap] create 
-- @param self
-- @param #string str
-- @return experimental::TMXTiledMap#experimental::TMXTiledMap ret (return value: cc.experimental::TMXTiledMap)
        
--------------------------------
-- @function [parent=#TMXTiledMap] createWithXML 
-- @param self
-- @param #string str
-- @param #string str
-- @return experimental::TMXTiledMap#experimental::TMXTiledMap ret (return value: cc.experimental::TMXTiledMap)
        
--------------------------------
-- @function [parent=#TMXTiledMap] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
return nil
