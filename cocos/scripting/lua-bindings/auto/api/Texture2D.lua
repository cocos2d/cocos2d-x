
--------------------------------
-- @module Texture2D
-- @extend Ref
-- @parent_module cc

--------------------------------
-- @function [parent=#Texture2D] getMaxT 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Texture2D] getStringForFormat 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- @overload self, cc.Image, int         
-- @overload self, cc.Image         
-- @function [parent=#Texture2D] initWithImage
-- @param self
-- @param #cc.Image image
-- @param #int pixelformat
-- @return bool#bool ret (retunr value: bool)

--------------------------------
-- @function [parent=#Texture2D] getMaxS 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Texture2D] releaseGLTexture 
-- @param self
        
--------------------------------
-- @function [parent=#Texture2D] hasPremultipliedAlpha 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Texture2D] getPixelsHigh 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @overload self, int         
-- @overload self         
-- @function [parent=#Texture2D] getBitsPerPixelForFormat
-- @param self
-- @param #int pixelformat
-- @return unsigned int#unsigned int ret (retunr value: unsigned int)

--------------------------------
-- @function [parent=#Texture2D] getName 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- @overload self, char, cc.FontDefinition         
-- @overload self, char, string, float, size_table, int, int         
-- @function [parent=#Texture2D] initWithString
-- @param self
-- @param #char char
-- @param #string str
-- @param #float float
-- @param #size_table size
-- @param #int texthalignment
-- @param #int textvalignment
-- @return bool#bool ret (retunr value: bool)

--------------------------------
-- @function [parent=#Texture2D] setMaxT 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#Texture2D] drawInRect 
-- @param self
-- @param #rect_table rect
        
--------------------------------
-- @function [parent=#Texture2D] getContentSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#Texture2D] setAliasTexParameters 
-- @param self
        
--------------------------------
-- @function [parent=#Texture2D] setAntiAliasTexParameters 
-- @param self
        
--------------------------------
-- @function [parent=#Texture2D] generateMipmap 
-- @param self
        
--------------------------------
-- @function [parent=#Texture2D] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#Texture2D] getPixelFormat 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#Texture2D] setGLProgram 
-- @param self
-- @param #cc.GLProgram glprogram
        
--------------------------------
-- @function [parent=#Texture2D] getContentSizeInPixels 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#Texture2D] getPixelsWide 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#Texture2D] drawAtPoint 
-- @param self
-- @param #vec2_table vec2
        
--------------------------------
-- @function [parent=#Texture2D] getGLProgram 
-- @param self
-- @return GLProgram#GLProgram ret (return value: cc.GLProgram)
        
--------------------------------
-- @function [parent=#Texture2D] hasMipmaps 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Texture2D] setMaxS 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#Texture2D] setDefaultAlphaPixelFormat 
-- @param self
-- @param #int pixelformat
        
--------------------------------
-- @function [parent=#Texture2D] getDefaultAlphaPixelFormat 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#Texture2D] Texture2D 
-- @param self
        
return nil
