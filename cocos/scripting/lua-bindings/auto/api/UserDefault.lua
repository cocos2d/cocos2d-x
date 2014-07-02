
--------------------------------
-- @module UserDefault
-- @parent_module cc

--------------------------------
-- @function [parent=#UserDefault] setIntegerForKey 
-- @param self
-- @param #char char
-- @param #int int
        
--------------------------------
-- overload function: getFloatForKey(char, float)
--          
-- overload function: getFloatForKey(char)
--          
-- @function [parent=#UserDefault] getFloatForKey
-- @param self
-- @param #char char
-- @param #float float
-- @return float#float ret (retunr value: float)

--------------------------------
-- overload function: getBoolForKey(char, bool)
--          
-- overload function: getBoolForKey(char)
--          
-- @function [parent=#UserDefault] getBoolForKey
-- @param self
-- @param #char char
-- @param #bool bool
-- @return bool#bool ret (retunr value: bool)

--------------------------------
-- @function [parent=#UserDefault] setDoubleForKey 
-- @param self
-- @param #char char
-- @param #double double
        
--------------------------------
-- @function [parent=#UserDefault] setFloatForKey 
-- @param self
-- @param #char char
-- @param #float float
        
--------------------------------
-- overload function: getStringForKey(char, string)
--          
-- overload function: getStringForKey(char)
--          
-- @function [parent=#UserDefault] getStringForKey
-- @param self
-- @param #char char
-- @param #string str
-- @return string#string ret (retunr value: string)

--------------------------------
-- @function [parent=#UserDefault] setStringForKey 
-- @param self
-- @param #char char
-- @param #string str
        
--------------------------------
-- @function [parent=#UserDefault] flush 
-- @param self
        
--------------------------------
-- overload function: getIntegerForKey(char, int)
--          
-- overload function: getIntegerForKey(char)
--          
-- @function [parent=#UserDefault] getIntegerForKey
-- @param self
-- @param #char char
-- @param #int int
-- @return int#int ret (retunr value: int)

--------------------------------
-- overload function: getDoubleForKey(char, double)
--          
-- overload function: getDoubleForKey(char)
--          
-- @function [parent=#UserDefault] getDoubleForKey
-- @param self
-- @param #char char
-- @param #double double
-- @return double#double ret (retunr value: double)

--------------------------------
-- @function [parent=#UserDefault] setBoolForKey 
-- @param self
-- @param #char char
-- @param #bool bool
        
--------------------------------
-- @function [parent=#UserDefault] destroyInstance 
-- @param self
        
--------------------------------
-- @function [parent=#UserDefault] getXMLFilePath 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#UserDefault] isXMLFileExist 
-- @param self
-- @return bool#bool ret (return value: bool)
        
return nil
