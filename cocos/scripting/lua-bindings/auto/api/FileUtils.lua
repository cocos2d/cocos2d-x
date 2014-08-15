
--------------------------------
-- @module FileUtils
-- @parent_module cc

--------------------------------
-- @function [parent=#FileUtils] fullPathForFilename 
-- @param self
-- @param #string str
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#FileUtils] getStringFromFile 
-- @param self
-- @param #string str
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#FileUtils] setFilenameLookupDictionary 
-- @param self
-- @param #map_table map
        
--------------------------------
-- @function [parent=#FileUtils] removeFile 
-- @param self
-- @param #string str
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FileUtils] isAbsolutePath 
-- @param self
-- @param #string str
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FileUtils] renameFile 
-- @param self
-- @param #string str
-- @param #string str
-- @param #string str
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FileUtils] loadFilenameLookupDictionaryFromFile 
-- @param self
-- @param #string str
        
--------------------------------
-- @function [parent=#FileUtils] isPopupNotify 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FileUtils] getValueVectorFromFile 
-- @param self
-- @param #string str
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- @function [parent=#FileUtils] getSearchPaths 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- @function [parent=#FileUtils] writeToFile 
-- @param self
-- @param #map_table map
-- @param #string str
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FileUtils] getValueMapFromFile 
-- @param self
-- @param #string str
-- @return map_table#map_table ret (return value: map_table)
        
--------------------------------
-- @function [parent=#FileUtils] getValueMapFromData 
-- @param self
-- @param #char char
-- @param #int int
-- @return map_table#map_table ret (return value: map_table)
        
--------------------------------
-- @function [parent=#FileUtils] removeDirectory 
-- @param self
-- @param #string str
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FileUtils] setSearchPaths 
-- @param self
-- @param #array_table array
        
--------------------------------
-- @function [parent=#FileUtils] getFileSize 
-- @param self
-- @param #string str
-- @return long#long ret (return value: long)
        
--------------------------------
-- @function [parent=#FileUtils] setSearchResolutionsOrder 
-- @param self
-- @param #array_table array
        
--------------------------------
-- @function [parent=#FileUtils] addSearchResolutionsOrder 
-- @param self
-- @param #string str
-- @param #bool bool
        
--------------------------------
-- @function [parent=#FileUtils] addSearchPath 
-- @param self
-- @param #string str
-- @param #bool bool
        
--------------------------------
-- @function [parent=#FileUtils] isFileExist 
-- @param self
-- @param #string str
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FileUtils] purgeCachedEntries 
-- @param self
        
--------------------------------
-- @function [parent=#FileUtils] fullPathFromRelativeFile 
-- @param self
-- @param #string str
-- @param #string str
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#FileUtils] setPopupNotify 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#FileUtils] isDirectoryExist 
-- @param self
-- @param #string str
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FileUtils] getSearchResolutionsOrder 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- @function [parent=#FileUtils] createDirectory 
-- @param self
-- @param #string str
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#FileUtils] getWritablePath 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#FileUtils] destroyInstance 
-- @param self
        
--------------------------------
-- @function [parent=#FileUtils] getInstance 
-- @param self
-- @return FileUtils#FileUtils ret (return value: cc.FileUtils)
        
return nil
