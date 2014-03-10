
--------------------------------
-- @module Label
--------------------------------
-- @function [parent=#Label] enableShadow 
-- @param self
        
--------------------------------
-- @function [parent=#Label] setDimensions 
-- @param self
-- @param #unsigned int int
-- @param #unsigned int int
        
--------------------------------
-- @function [parent=#Label] getString 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#Label] disableEffect 
-- @param self
        
--------------------------------
-- @function [parent=#Label] getWidth 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- @function [parent=#Label] getCommonLineHeight 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#Label] setWidth 
-- @param self
-- @param #unsigned int int
        
--------------------------------
-- @function [parent=#Label] getMaxLineWidth 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- @function [parent=#Label] getHorizontalAlignment 
-- @param self
-- @return TextHAlignment#TextHAlignment ret (return value: cc.TextHAlignment)
        
--------------------------------
-- @function [parent=#Label] setString 
-- @param self
-- @param #string str
        
--------------------------------
-- @function [parent=#Label] getHeight 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- @function [parent=#Label] setBMFontFilePath 
-- @param self
-- @param #string str
-- @param #point_table point
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Label] getStringLength 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#Label] setLineBreakWithoutSpace 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Label] getStringNumLines 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#Label] enableOutline 
-- @param self
-- @param #color4B_table color4b
-- @param #int int
        
--------------------------------
-- overload function: setCharMap(cc.Texture2D, int, int, int)
--          
-- overload function: setCharMap(string, int, int, int)
--          
-- overload function: setCharMap(string)
--          
-- @function [parent=#Label] setCharMap
-- @param self
-- @param #string str
-- @param #int int
-- @param #int int
-- @param #int int
-- @return bool#bool ret (retunr value: bool)

--------------------------------
-- @function [parent=#Label] setMaxLineWidth 
-- @param self
-- @param #unsigned int int
        
--------------------------------
-- @function [parent=#Label] setVerticalAlignment 
-- @param self
-- @param #cc.TextVAlignment textvalignment
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Label] getVerticalAlignment 
-- @param self
-- @return TextVAlignment#TextVAlignment ret (return value: cc.TextVAlignment)
        
--------------------------------
-- @function [parent=#Label] setHeight 
-- @param self
-- @param #unsigned int int
        
--------------------------------
-- @function [parent=#Label] enableGlow 
-- @param self
-- @param #color3B_table color3b
        
--------------------------------
-- @function [parent=#Label] getLetter 
-- @param self
-- @param #int int
-- @return Sprite#Sprite ret (return value: cc.Sprite)
        
--------------------------------
-- @function [parent=#Label] getTextAlignment 
-- @param self
-- @return TextHAlignment#TextHAlignment ret (return value: cc.TextHAlignment)
        
--------------------------------
-- @function [parent=#Label] setHorizontalAlignment 
-- @param self
-- @param #cc.TextHAlignment texthalignment
-- @param #bool bool
        
--------------------------------
-- overload function: setAlignment(cc.TextHAlignment, cc.TextVAlignment, bool)
--          
-- overload function: setAlignment(cc.TextHAlignment, bool)
--          
-- @function [parent=#Label] setAlignment
-- @param self
-- @param #cc.TextHAlignment texthalignment
-- @param #cc.TextVAlignment textvalignment
-- @param #bool bool

--------------------------------
-- @function [parent=#Label] createWithBMFont 
-- @param self
-- @param #string str
-- @param #string str
-- @param #cc.TextHAlignment texthalignment
-- @param #int int
-- @param #point_table point
-- @return Label#Label ret (return value: cc.Label)
        
--------------------------------
-- @function [parent=#Label] create 
-- @param self
-- @return Label#Label ret (return value: cc.Label)
        
--------------------------------
-- overload function: createWithCharMap(cc.Texture2D, int, int, int)
--          
-- overload function: createWithCharMap(string, int, int, int)
--          
-- overload function: createWithCharMap(string)
--          
-- @function [parent=#Label] createWithCharMap
-- @param self
-- @param #string str
-- @param #int int
-- @param #int int
-- @param #int int
-- @return Label#Label ret (retunr value: cc.Label)

return nil
