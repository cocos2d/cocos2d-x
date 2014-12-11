
--------------------------------
-- @module TileMapAtlas
-- @extend AtlasNode
-- @parent_module cc

--------------------------------
--  initializes a TileMap with a tile file (atlas) with a map file and the width and height of each tile in points.<br>
-- The file will be loaded using the TextureMgr.
-- @function [parent=#TileMapAtlas] initWithTileFile 
-- @param self
-- @param #string tile
-- @param #string mapFile
-- @param #int tileWidth
-- @param #int tileHeight
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  dealloc the map from memory 
-- @function [parent=#TileMapAtlas] releaseMap 
-- @param self
        
--------------------------------
--  returns a tile from position x,y.<br>
-- For the moment only channel R is used
-- @function [parent=#TileMapAtlas] getTileAt 
-- @param self
-- @param #vec2_table position
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
--  sets a tile at position x,y.<br>
-- For the moment only channel R is used
-- @function [parent=#TileMapAtlas] setTile 
-- @param self
-- @param #color3b_table tile
-- @param #vec2_table position
        
--------------------------------
--  creates a TileMap with a tile file (atlas) with a map file and the width and height of each tile in points.<br>
-- The tile file will be loaded using the TextureMgr.
-- @function [parent=#TileMapAtlas] create 
-- @param self
-- @param #string tile
-- @param #string mapFile
-- @param #int tileWidth
-- @param #int tileHeight
-- @return TileMapAtlas#TileMapAtlas ret (return value: cc.TileMapAtlas)
        
--------------------------------
-- js ctor
-- @function [parent=#TileMapAtlas] TileMapAtlas 
-- @param self
        
return nil
