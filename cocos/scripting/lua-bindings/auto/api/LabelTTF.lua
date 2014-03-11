
--------------------------------
-- @module LabelTTF
--------------------------------
-- @function [parent=#LabelTTF] enableShadow 
-- @param self
-- @param #size_table size
-- @param #float float
-- @param #float float
-- @param #bool bool
        
--------------------------------
-- @function [parent=#LabelTTF] setDimensions 
-- @param self
-- @param #size_table size
        
--------------------------------
-- @function [parent=#LabelTTF] getFontSize 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#LabelTTF] getString 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#LabelTTF] setTextDefinition 
-- @param self
-- @param #cc.FontDefinition fontdefinition
        
--------------------------------
-- @function [parent=#LabelTTF] setFontName 
-- @param self
-- @param #string str
        
--------------------------------
-- @function [parent=#LabelTTF] getHorizontalAlignment 
-- @param self
-- @return TextHAlignment#TextHAlignment ret (return value: cc.TextHAlignment)
        
--------------------------------
-- @function [parent=#LabelTTF] initWithStringAndTextDefinition 
-- @param self
-- @param #string str
-- @param #cc.FontDefinition fontdefinition
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#LabelTTF] setString 
-- @param self
-- @param #string str
        
--------------------------------
-- overload function: initWithString(string, string, float, size_table, cc.TextHAlignment)
--          
-- overload function: initWithString(string, string, float)
--          
-- overload function: initWithString(string, string, float, size_table, cc.TextHAlignment, cc.TextVAlignment)
--          
-- @function [parent=#LabelTTF] initWithString
-- @param self
-- @param #string str
-- @param #string str
-- @param #float float
-- @param #size_table size
-- @param #cc.TextHAlignment texthalignment
-- @param #cc.TextVAlignment textvalignment
-- @return bool#bool ret (retunr value: bool)

--------------------------------
-- @function [parent=#LabelTTF] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#LabelTTF] setFontFillColor 
-- @param self
-- @param #color3B_table color3b
-- @param #bool bool
        
--------------------------------
-- @function [parent=#LabelTTF] enableStroke 
-- @param self
-- @param #color3B_table color3b
-- @param #float float
-- @param #bool bool
        
--------------------------------
-- @function [parent=#LabelTTF] getDimensions 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#LabelTTF] setVerticalAlignment 
-- @param self
-- @param #cc.TextVAlignment textvalignment
        
--------------------------------
-- @function [parent=#LabelTTF] setFontSize 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#LabelTTF] getVerticalAlignment 
-- @param self
-- @return TextVAlignment#TextVAlignment ret (return value: cc.TextVAlignment)
        
--------------------------------
-- @function [parent=#LabelTTF] getTextDefinition 
-- @param self
-- @return FontDefinition#FontDefinition ret (return value: cc.FontDefinition)
        
--------------------------------
-- @function [parent=#LabelTTF] getFontName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#LabelTTF] setHorizontalAlignment 
-- @param self
-- @param #cc.TextHAlignment texthalignment
        
--------------------------------
-- @function [parent=#LabelTTF] disableShadow 
-- @param self
        
--------------------------------
-- @function [parent=#LabelTTF] disableStroke 
-- @param self
        
--------------------------------
-- overload function: create(string, string, float, size_table, cc.TextHAlignment)
--          
-- overload function: create(string, string, float)
--          
-- overload function: create(string, string, float, size_table, cc.TextHAlignment, cc.TextVAlignment)
--          
-- overload function: create()
--          
-- @function [parent=#LabelTTF] create
-- @param self
-- @param #string str
-- @param #string str
-- @param #float float
-- @param #size_table size
-- @param #cc.TextHAlignment texthalignment
-- @param #cc.TextVAlignment textvalignment
-- @return LabelTTF#LabelTTF ret (retunr value: cc.LabelTTF)

--------------------------------
-- @function [parent=#LabelTTF] createWithFontDefinition 
-- @param self
-- @param #string str
-- @param #cc.FontDefinition fontdefinition
-- @return LabelTTF#LabelTTF ret (return value: cc.LabelTTF)
        
--------------------------------
-- @function [parent=#LabelTTF] LabelTTF 
-- @param self
        
return nil
