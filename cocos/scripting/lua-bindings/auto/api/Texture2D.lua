
--------------------------------
-- @module Texture2D
-- @extend Ref

--------------------------------
-- @function [parent=#Texture2D] getShaderProgram 
-- @param self
-- @return GLProgram#GLProgram ret (return value: cc.GLProgram)
        
--------------------------------
-- @function [parent=#Texture2D] getMaxT 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Texture2D] getStringForFormat 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- overload function: initWithImage(cc.Image, cc.Texture2D::PixelFormat)
--          
-- overload function: initWithImage(cc.Image)
--          
-- @function [parent=#Texture2D] initWithImage
-- @param self
-- @param #cc.Image image
-- @param #cc.Texture2D::PixelFormat pixelformat
-- @return bool#bool ret (retunr value: bool)

--------------------------------
-- @function [parent=#Texture2D] setShaderProgram 
-- @param self
-- @param #cc.GLProgram glprogram
        
--------------------------------
-- @function [parent=#Texture2D] getMaxS 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#Texture2D] updateWithData 
-- @param self
-- @param #void void
-- @param #int int
-- @param #int int
-- @param #int int
-- @param #int int
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Texture2D] hasPremultipliedAlpha 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Texture2D] initWithMipmaps 
-- @param self
-- @param #cc._MipmapInfo map
-- @param #int int
-- @param #cc.Texture2D::PixelFormat pixelformat
-- @param #int int
-- @param #int int
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#Texture2D] getPixelsHigh 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- overload function: getBitsPerPixelForFormat(cc.Texture2D::PixelFormat)
--          
-- overload function: getBitsPerPixelForFormat()
--          
-- @function [parent=#Texture2D] getBitsPerPixelForFormat
-- @param self
-- @param #cc.Texture2D::PixelFormat pixelformat
-- @return unsigned int#unsigned int ret (retunr value: unsigned int)

--------------------------------
-- @function [parent=#Texture2D] getName 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- overload function: initWithString(char, cc.FontDefinition)
--          
-- overload function: initWithString(char, char, float, size_table, cc.TextHAlignment, cc.TextVAlignment)
--          
-- @function [parent=#Texture2D] initWithString
-- @param self
-- @param #char char
-- @param #char char
-- @param #float float
-- @param #size_table size
-- @param #cc.TextHAlignment texthalignment
-- @param #cc.TextVAlignment textvalignment
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
-- @return Texture2D::PixelFormat#Texture2D::PixelFormat ret (return value: cc.Texture2D::PixelFormat)
        
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
-- @param #point_table point
        
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
-- @param #cc.Texture2D::PixelFormat pixelformat
        
--------------------------------
-- @function [parent=#Texture2D] getDefaultAlphaPixelFormat 
-- @param self
-- @return Texture2D::PixelFormat#Texture2D::PixelFormat ret (return value: cc.Texture2D::PixelFormat)
        
--------------------------------
-- @function [parent=#Texture2D] PVRImagesHavePremultipliedAlpha 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#Texture2D] Texture2D 
-- @param self
        
return nil
