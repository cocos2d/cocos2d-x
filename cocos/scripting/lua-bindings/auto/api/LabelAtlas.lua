
--------------------------------
-- @module LabelAtlas
-- @extend AtlasNode,LabelProtocol
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#LabelAtlas] setString 
-- @param self
-- @param #string label
-- @return LabelAtlas#LabelAtlas self (return value: cc.LabelAtlas)
        
--------------------------------
-- @overload self, string, string         
-- @overload self, string, string, int, int, int         
-- @overload self, string, cc.Texture2D, int, int, int         
-- @function [parent=#LabelAtlas] initWithString
-- @param self
-- @param #string string
-- @param #cc.Texture2D texture
-- @param #int itemWidth
-- @param #int itemHeight
-- @param #int startCharMap
-- @return bool#bool ret (return value: bool)

--------------------------------
-- 
-- @function [parent=#LabelAtlas] getString 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @overload self, string, string, int, int, int         
-- @overload self         
-- @overload self, string, string         
-- @function [parent=#LabelAtlas] create
-- @param self
-- @param #string string
-- @param #string charMapFile
-- @param #int itemWidth
-- @param #int itemHeight
-- @param #int startCharMap
-- @return LabelAtlas#LabelAtlas ret (return value: cc.LabelAtlas)

--------------------------------
-- 
-- @function [parent=#LabelAtlas] updateAtlasValues 
-- @param self
-- @return LabelAtlas#LabelAtlas self (return value: cc.LabelAtlas)
        
--------------------------------
-- 
-- @function [parent=#LabelAtlas] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
return nil
