
--------------------------------
-- @module Image
-- @extend Ref
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#Image] hasPremultipliedAlpha 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief    Save Image data to the specified file, with specified format.<br>
-- param    filePath        the file's absolute path, including file suffix.<br>
-- param    isToRGB        whether the image is saved as RGB format.
-- @function [parent=#Image] saveToFile 
-- @param self
-- @param #string filename
-- @param #bool isToRGB
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Image] hasAlpha 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Image] isCompressed 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Image] getHeight 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- brief Load the image from the specified path.<br>
-- param path   the absolute file path.<br>
-- return true if loaded correctly.
-- @function [parent=#Image] initWithImageFile 
-- @param self
-- @param #string path
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Image] getWidth 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#Image] getBitPerPixel 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#Image] getFileType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#Image] getNumberOfMipmaps 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#Image] getRenderFormat 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  treats (or not) PVR files as if they have alpha premultiplied.<br>
-- Since it is impossible to know at runtime if the PVR images have the alpha channel premultiplied, it is<br>
-- possible load them as if they have (or not) the alpha channel premultiplied.<br>
-- By default it is disabled.
-- @function [parent=#Image] setPVRImagesHavePremultipliedAlpha 
-- @param self
-- @param #bool haveAlphaPremultiplied
-- @return Image#Image self (return value: cc.Image)
        
--------------------------------
-- js ctor
-- @function [parent=#Image] Image 
-- @param self
-- @return Image#Image self (return value: cc.Image)
        
return nil
