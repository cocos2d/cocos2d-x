
--------------------------------
-- @module LabelAtlas
-- @extend AtlasNode,LabelProtocol
-- @parent_module cc

--------------------------------
-- @function [parent=#LabelAtlas] setString 
-- @param self
-- @param #string str
        
--------------------------------
-- @overload self, string, string         
-- @overload self, string, string, int, int, int         
-- @overload self, string, cc.Texture2D, int, int, int         
-- @function [parent=#LabelAtlas] initWithString
-- @param self
-- @param #string str
-- @param #cc.Texture2D texture2d
-- @param #int int
-- @param #int int
-- @param #int int
-- @return bool#bool ret (retunr value: bool)

--------------------------------
-- @function [parent=#LabelAtlas] updateAtlasValues 
-- @param self
        
--------------------------------
-- @function [parent=#LabelAtlas] getString 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @overload self, string, string, int, int, int         
-- @overload self         
-- @overload self, string, string         
-- @function [parent=#LabelAtlas] create
-- @param self
-- @param #string str
-- @param #string str
-- @param #int int
-- @param #int int
-- @param #int int
-- @return LabelAtlas#LabelAtlas ret (retunr value: cc.LabelAtlas)

--------------------------------
-- @function [parent=#LabelAtlas] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
return nil
