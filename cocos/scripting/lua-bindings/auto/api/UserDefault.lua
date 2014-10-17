
--------------------------------
-- @module UserDefault
-- @parent_module cc

--------------------------------
-- brief Set integer value by key.<br>
-- js NA
-- @function [parent=#UserDefault] setIntegerForKey 
-- @param self
-- @param #char pKey
-- @param #int value
        
--------------------------------
-- @overload self, char, float         
-- @overload self, char         
-- @function [parent=#UserDefault] getFloatForKey
-- @param self
-- @param #char pKey
-- @param #float defaultValue
-- @return float#float ret (return value: float)

--------------------------------
-- @overload self, char, bool         
-- @overload self, char         
-- @function [parent=#UserDefault] getBoolForKey
-- @param self
-- @param #char pKey
-- @param #bool defaultValue
-- @return bool#bool ret (return value: bool)

--------------------------------
-- brief Set double value by key.<br>
-- js NA
-- @function [parent=#UserDefault] setDoubleForKey 
-- @param self
-- @param #char pKey
-- @param #double value
        
--------------------------------
-- brief Set float value by key.<br>
-- js NA
-- @function [parent=#UserDefault] setFloatForKey 
-- @param self
-- @param #char pKey
-- @param #float value
        
--------------------------------
-- @overload self, char, string         
-- @overload self, char         
-- @function [parent=#UserDefault] getStringForKey
-- @param self
-- @param #char pKey
-- @param #string defaultValue
-- @return string#string ret (return value: string)

--------------------------------
-- brief Set string value by key.<br>
-- js NA
-- @function [parent=#UserDefault] setStringForKey 
-- @param self
-- @param #char pKey
-- @param #string value
        
--------------------------------
-- brief Save content to xml file<br>
-- js NA
-- @function [parent=#UserDefault] flush 
-- @param self
        
--------------------------------
-- @overload self, char, int         
-- @overload self, char         
-- @function [parent=#UserDefault] getIntegerForKey
-- @param self
-- @param #char pKey
-- @param #int defaultValue
-- @return int#int ret (return value: int)

--------------------------------
-- @overload self, char, double         
-- @overload self, char         
-- @function [parent=#UserDefault] getDoubleForKey
-- @param self
-- @param #char pKey
-- @param #double defaultValue
-- @return double#double ret (return value: double)

--------------------------------
-- brief Set bool value by key.<br>
-- js NA
-- @function [parent=#UserDefault] setBoolForKey 
-- @param self
-- @param #char pKey
-- @param #bool value
        
--------------------------------
-- js NA
-- @function [parent=#UserDefault] destroyInstance 
-- @param self
        
--------------------------------
-- js NA
-- @function [parent=#UserDefault] getXMLFilePath 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- js NA
-- @function [parent=#UserDefault] isXMLFileExist 
-- @param self
-- @return bool#bool ret (return value: bool)
        
return nil
