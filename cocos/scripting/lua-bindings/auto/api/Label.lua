
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
-- Enable shadow effect to Label.<br>
-- todo Support blur for shadow effect.
-- @function [parent=#Label] enableShadow 
-- @param self
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
--  Sets the untransformed size of the Label in a more efficient way. 
-- @function [parent=#Label] setDimensions 
-- @param self
-- @param #float width
-- @param #float height
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
--  Return the text the Label is displaying.
-- @function [parent=#Label] getString 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#Label] getHeight 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Disable all effect to Label.
-- @function [parent=#Label] disableEffect 
-- @param self
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
-- Sets a new TTF configuration to Label.<br>
-- see `TTFConfig`
-- @function [parent=#Label] setTTFConfig 
-- @param self
-- @param #cc._ttfConfig ttfConfig
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Returns the text color of the Label.
-- @function [parent=#Label] getTextColor 
-- @param self
-- @return color4b_table#color4b_table ret (return value: color4b_table)
        
--------------------------------
-- Makes the Label exactly this untransformed width.<br>
-- The Label's width be used for text align if the value not equal zero.
-- @function [parent=#Label] setWidth 
-- @param self
-- @param #float width
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
-- 
-- @function [parent=#Label] getMaxLineWidth 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Returns the Label's text horizontal alignment.
-- @function [parent=#Label] getHorizontalAlignment 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Makes the Label to clip upper and lower margin for reduce height of Label.
-- @function [parent=#Label] setClipMarginEnabled 
-- @param self
-- @param #bool clipEnabled
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
--  Sets the text that this Label is to display.
-- @function [parent=#Label] setString 
-- @param self
-- @param #string text
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
-- Sets a new system font to Label.<br>
-- param font A font file or a font family name.<br>
-- warning
-- @function [parent=#Label] setSystemFontName 
-- @param self
-- @param #string font
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
--  Sets a new bitmap font to Label 
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
--  Sets the line height of the Label.<br>
-- warning Not support system font.<br>
-- since v3.2.0
-- @function [parent=#Label] setLineHeight 
-- @param self
-- @param #float height
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
-- 
-- @function [parent=#Label] setSystemFontSize 
-- @param self
-- @param #float fontSize
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
--  Update content immediately.
-- @function [parent=#Label] updateContent 
-- @param self
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
-- 
-- @function [parent=#Label] getStringLength 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Specify what happens when a line is too long for Label.<br>
-- param breakWithoutSpace Lines are automatically broken between words if this value is false.
-- @function [parent=#Label] setLineBreakWithoutSpace 
-- @param self
-- @param #bool breakWithoutSpace
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
-- 
-- @function [parent=#Label] getStringNumLines 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Enable outline effect to Label.<br>
-- warning Limiting use to only when the Label created with true type font or system font.
-- @function [parent=#Label] enableOutline 
-- @param self
-- @param #color4b_table outlineColor
-- @param #int outlineSize
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
-- Returns the additional kerning of the Label.<br>
-- warning Not support system font.<br>
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
-- Makes the Label at most this line untransformed width.<br>
-- The Label's max line width be used for force line breaks if the value not equal zero.
-- @function [parent=#Label] setMaxLineWidth 
-- @param self
-- @param #float maxLineWidth
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
--  Returns the system font used by the Label.
-- @function [parent=#Label] getSystemFontName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
--  Sets the Label's text vertical alignment.
-- @function [parent=#Label] setVerticalAlignment 
-- @param self
-- @param #int vAlignment
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
-- Returns the line height of this Label.<br>
-- warning Not support system font.<br>
-- since v3.2.0
-- @function [parent=#Label] getLineHeight 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Returns the TTF configuration object used by the Label.<br>
-- see `TTFConfig`
-- @function [parent=#Label] getTTFConfig 
-- @param self
-- @return _ttfConfig#_ttfConfig ret (return value: cc._ttfConfig)
        
--------------------------------
--  Returns the Label's text vertical alignment.
-- @function [parent=#Label] getVerticalAlignment 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Sets the text color of Label.<br>
-- The text color is different from the color of Node.<br>
-- warning Limiting use to only when the Label created with true type font or system font. 
-- @function [parent=#Label] setTextColor 
-- @param self
-- @param #color4b_table color
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
-- Makes the Label exactly this untransformed height.<br>
-- The Label's height be used for text align if the value not equal zero.<br>
-- The text will display of incomplete when the size of Label not enough to support display all text.
-- @function [parent=#Label] setHeight 
-- @param self
-- @param #float height
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
-- 
-- @function [parent=#Label] getWidth 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Enable glow effect to Label.<br>
-- warning Limiting use to only when the Label created with true type font.
-- @function [parent=#Label] enableGlow 
-- @param self
-- @param #color4b_table glowColor
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
-- Provides a way to treats each character like a Sprite.<br>
-- warning No support system font.
-- @function [parent=#Label] getLetter 
-- @param self
-- @param #int lettetIndex
-- @return Sprite#Sprite ret (return value: cc.Sprite)
        
--------------------------------
-- Sets the additional kerning of the Label.<br>
-- warning Not support system font.<br>
-- since v3.2.0
-- @function [parent=#Label] setAdditionalKerning 
-- @param self
-- @param #float space
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
--  Returns the bitmap font path used by the Label.
-- @function [parent=#Label] getSystemFontSize 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Returns the Label's text horizontal alignment.
-- @function [parent=#Label] getTextAlignment 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Returns the bitmap font used by the Label.
-- @function [parent=#Label] getBMFontFilePath 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
--  Sets the Label's text horizontal alignment.
-- @function [parent=#Label] setHorizontalAlignment 
-- @param self
-- @param #int hAlignment
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
-- @overload self, int, int         
-- @overload self, int         
-- @function [parent=#Label] setAlignment
-- @param self
-- @param #int hAlignment
-- @param #int vAlignment
-- @return Label#Label self (return value: cc.Label)

--------------------------------
-- warning This method is not recommended for game developers.
-- @function [parent=#Label] requestSystemFontRefresh 
-- @param self
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
-- Allocates and initializes a Label, with a bitmap font file.<br>
-- param bmfontPath A bitmap font file, it's a FNT format.<br>
-- param text The initial text.<br>
-- param hAlignment Text horizontal alignment.<br>
-- param maxLineWidth The max line width.<br>
-- param imageOffset <br>
-- return An automatically released Label object.<br>
-- see setBMFontFilePath setMaxLineWidth
-- @function [parent=#Label] createWithBMFont 
-- @param self
-- @param #string bmfontPath
-- @param #string text
-- @param #int hAlignment
-- @param #int maxLineWidth
-- @param #vec2_table imageOffset
-- @return Label#Label ret (return value: cc.Label)
        
--------------------------------
-- Allocates and initializes a Label, with default settings.<br>
-- return An automatically released Label object.
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
-- Allocates and initializes a Label, base on platform-dependent API.<br>
-- param text The initial text.<br>
-- param font A font file or a font family name.<br>
-- param fontSize The font size. This value must be > 0.<br>
-- param dimensions <br>
-- param hAlignment The text horizontal alignment.<br>
-- param vAlignment The text vertical alignment.<br>
-- warning It will generate texture by the platform-dependent code.<br>
-- return An automatically released Label object.
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
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
-- 
-- @function [parent=#Label] addChild 
-- @param self
-- @param #cc.Node child
-- @param #int zOrder
-- @param #int tag
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
-- 
-- @function [parent=#Label] setScaleY 
-- @param self
-- @param #float scaleY
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
-- 
-- @function [parent=#Label] setScaleX 
-- @param self
-- @param #float scaleX
-- @return Label#Label self (return value: cc.Label)
        
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
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
-- 
-- @function [parent=#Label] visit 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table parentTransform
-- @param #unsigned int parentFlags
-- @return Label#Label self (return value: cc.Label)
        
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
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
-- 
-- @function [parent=#Label] setScale 
-- @param self
-- @param #float scale
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
-- 
-- @function [parent=#Label] sortAllChildren 
-- @param self
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
-- 
-- @function [parent=#Label] updateDisplayedOpacity 
-- @param self
-- @param #unsigned char parentOpacity
-- @return Label#Label self (return value: cc.Label)
        
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
-- @return Label#Label self (return value: cc.Label)
        
--------------------------------
-- 
-- @function [parent=#Label] setCameraMask 
-- @param self
-- @param #unsigned short mask
-- @param #bool applyChildren
-- @return Label#Label self (return value: cc.Label)
        
return nil
