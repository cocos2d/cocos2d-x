
--------------------------------
-- @module Label
-- @extend SpriteBatchNode,LabelProtocol
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#Label] isClipMarginEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Enable shadow for the label<br>
-- todo support blur for shadow effect
-- @function [parent=#Label] enableShadow 
-- @param self
        
--------------------------------
--  Sets the untransformed size of the label in a more efficient way. 
-- @function [parent=#Label] setDimensions 
-- @param self
-- @param #unsigned int width
-- @param #unsigned int height
        
--------------------------------
-- 
-- @function [parent=#Label] getString 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#Label] getHeight 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
--  disable shadow/outline/glow rendering 
-- @function [parent=#Label] disableEffect 
-- @param self
        
--------------------------------
--  set TTF configuration for Label 
-- @function [parent=#Label] setTTFConfig 
-- @param self
-- @param #cc._ttfConfig ttfConfig
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Returns the text color of this label<br>
-- Only support for TTF and system font<br>
-- warning Different from the color of Node.
-- @function [parent=#Label] getTextColor 
-- @param self
-- @return color4b_table#color4b_table ret (return value: color4b_table)
        
--------------------------------
--  Sets the untransformed size of the label.<br>
-- The label's width be used for text align if the set value not equal zero.<br>
-- The label's max line width will be equal to the same value.
-- @function [parent=#Label] setWidth 
-- @param self
-- @param #unsigned int width
        
--------------------------------
-- 
-- @function [parent=#Label] getMaxLineWidth 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- 
-- @function [parent=#Label] getHorizontalAlignment 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  clip upper and lower margin for reduce height of label.
-- @function [parent=#Label] setClipMarginEnabled 
-- @param self
-- @param #bool clipEnabled
        
--------------------------------
--  changes the string to render<br>
-- warning It is as expensive as changing the string if you haven't set up TTF/BMFont/CharMap for the label.
-- @function [parent=#Label] setString 
-- @param self
-- @param #string text
        
--------------------------------
-- 
-- @function [parent=#Label] setSystemFontName 
-- @param self
-- @param #string systemFont
        
--------------------------------
-- 
-- @function [parent=#Label] setBMFontFilePath 
-- @param self
-- @param #string bmfontFilePath
-- @param #vec2_table imageOffset
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Label] getFontAtlas 
-- @param self
-- @return FontAtlas#FontAtlas ret (return value: cc.FontAtlas)
        
--------------------------------
--  Sets the line height of the label<br>
-- warning Not support system font<br>
-- since v3.2.0
-- @function [parent=#Label] setLineHeight 
-- @param self
-- @param #float height
        
--------------------------------
-- 
-- @function [parent=#Label] setSystemFontSize 
-- @param self
-- @param #float fontSize
        
--------------------------------
--  update content immediately.
-- @function [parent=#Label] updateContent 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#Label] getStringLength 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#Label] setLineBreakWithoutSpace 
-- @param self
-- @param #bool breakWithoutSpace
        
--------------------------------
-- 
-- @function [parent=#Label] getStringNumLines 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  only support for TTF 
-- @function [parent=#Label] enableOutline 
-- @param self
-- @param #color4b_table outlineColor
-- @param #int outlineSize
        
--------------------------------
--  Returns the additional kerning of this label<br>
-- warning Not support system font<br>
-- since v3.2.0
-- @function [parent=#Label] getAdditionalKerning 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @overload self, cc.Texture2D, int, int, int         
-- @overload self, string, int, int, int         
-- @overload self, string         
-- @function [parent=#Label] setCharMap
-- @param self
-- @param #string charMapFile
-- @param #int itemWidth
-- @param #int itemHeight
-- @param #int startCharMap
-- @return bool#bool ret (return value: bool)

--------------------------------
-- 
-- @function [parent=#Label] getDimensions 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
--  Sets the max line width of the label.<br>
-- The label's max line width be used for force line breaks if the set value not equal zero.<br>
-- The label's width and max line width has not always to be equal.
-- @function [parent=#Label] setMaxLineWidth 
-- @param self
-- @param #unsigned int maxLineWidth
        
--------------------------------
-- 
-- @function [parent=#Label] getSystemFontName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#Label] setVerticalAlignment 
-- @param self
-- @param #int vAlignment
        
--------------------------------
--  Returns the line height of this label<br>
-- warning Not support system font
-- @function [parent=#Label] getLineHeight 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Label] getTTFConfig 
-- @param self
-- @return _ttfConfig#_ttfConfig ret (return value: cc._ttfConfig)
        
--------------------------------
-- 
-- @function [parent=#Label] getVerticalAlignment 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Sets the text color of the label<br>
-- Only support for TTF and system font<br>
-- warning Different from the color of Node.
-- @function [parent=#Label] setTextColor 
-- @param self
-- @param #color4b_table color
        
--------------------------------
--  Sets the untransformed size of the label.<br>
-- The label's height be used for text align if the set value not equal zero.<br>
-- The text will display of incomplete when the size of label not enough to support display all text.
-- @function [parent=#Label] setHeight 
-- @param self
-- @param #unsigned int height
        
--------------------------------
-- 
-- @function [parent=#Label] getWidth 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
--  only support for TTF 
-- @function [parent=#Label] enableGlow 
-- @param self
-- @param #color4b_table glowColor
        
--------------------------------
-- 
-- @function [parent=#Label] getLetter 
-- @param self
-- @param #int lettetIndex
-- @return Sprite#Sprite ret (return value: cc.Sprite)
        
--------------------------------
--  Sets the additional kerning of the label<br>
-- warning Not support system font<br>
-- since v3.2.0
-- @function [parent=#Label] setAdditionalKerning 
-- @param self
-- @param #float space
        
--------------------------------
-- 
-- @function [parent=#Label] getSystemFontSize 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Label] getTextAlignment 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#Label] getBMFontFilePath 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#Label] setHorizontalAlignment 
-- @param self
-- @param #int hAlignment
        
--------------------------------
-- @overload self, int, int         
-- @overload self, int         
-- @function [parent=#Label] setAlignment
-- @param self
-- @param #int hAlignment
-- @param #int vAlignment

--------------------------------
-- 
-- @function [parent=#Label] requestSystemFontRefresh 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#Label] createWithBMFont 
-- @param self
-- @param #string bmfontFilePath
-- @param #string text
-- @param #int alignment
-- @param #int maxLineWidth
-- @param #vec2_table imageOffset
-- @return Label#Label ret (return value: cc.Label)
        
--------------------------------
-- 
-- @function [parent=#Label] create 
-- @param self
-- @return Label#Label ret (return value: cc.Label)
        
--------------------------------
-- @overload self, cc.Texture2D, int, int, int         
-- @overload self, string, int, int, int         
-- @overload self, string         
-- @function [parent=#Label] createWithCharMap
-- @param self
-- @param #string charMapFile
-- @param #int itemWidth
-- @param #int itemHeight
-- @param #int startCharMap
-- @return Label#Label ret (return value: cc.Label)

--------------------------------
--  Creates a label with an initial string,font[font name or font file],font size, dimension in points, horizontal alignment and vertical alignment.<br>
-- warning It will generate texture by the platform-dependent code
-- @function [parent=#Label] createWithSystemFont 
-- @param self
-- @param #string text
-- @param #string font
-- @param #float fontSize
-- @param #size_table dimensions
-- @param #int hAlignment
-- @param #int vAlignment
-- @return Label#Label ret (return value: cc.Label)
        
--------------------------------
-- 
-- @function [parent=#Label] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
        
--------------------------------
-- 
-- @function [parent=#Label] addChild 
-- @param self
-- @param #cc.Node child
-- @param #int zOrder
-- @param #int tag
        
--------------------------------
-- 
-- @function [parent=#Label] setScaleY 
-- @param self
-- @param #float scaleY
        
--------------------------------
-- 
-- @function [parent=#Label] setScaleX 
-- @param self
-- @param #float scaleX
        
--------------------------------
-- 
-- @function [parent=#Label] isOpacityModifyRGB 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Label] getScaleY 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Label] setBlendFunc 
-- @param self
-- @param #cc.BlendFunc blendFunc
        
--------------------------------
-- 
-- @function [parent=#Label] visit 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table parentTransform
-- @param #unsigned int parentFlags
        
--------------------------------
-- 
-- @function [parent=#Label] getScaleX 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Label] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#Label] setOpacityModifyRGB 
-- @param self
-- @param #bool isOpacityModifyRGB
        
--------------------------------
-- 
-- @function [parent=#Label] setScale 
-- @param self
-- @param #float scale
        
--------------------------------
-- 
-- @function [parent=#Label] sortAllChildren 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#Label] updateDisplayedOpacity 
-- @param self
-- @param #unsigned char parentOpacity
        
--------------------------------
-- 
-- @function [parent=#Label] getContentSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- 
-- @function [parent=#Label] getBoundingBox 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- 
-- @function [parent=#Label] updateDisplayedColor 
-- @param self
-- @param #color3b_table parentColor
        
return nil
