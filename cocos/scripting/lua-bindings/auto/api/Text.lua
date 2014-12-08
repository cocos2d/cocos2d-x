
--------------------------------
-- @module Text
-- @extend Widget
-- @parent_module ccui

--------------------------------
-- Enable shadow for the label<br>
-- todo support blur for shadow effect
-- @function [parent=#Text] enableShadow 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#Text] getFontSize 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#Text] getString 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
--  disable shadow/outline/glow rendering 
-- @function [parent=#Text] disableEffect 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#Text] getTextColor 
-- @param self
-- @return color4b_table#color4b_table ret (return value: color4b_table)
        
--------------------------------
-- 
-- @function [parent=#Text] setTextVerticalAlignment 
-- @param self
-- @param #int alignment
        
--------------------------------
-- Sets the font name of label.<br>
-- If you are trying to use a system font, you could just pass a font name<br>
-- If you are trying to use a TTF, you should pass a file path to the TTF file<br>
-- Usage:  Text *text = Text::create("Hello", "Arial", 20);create a system font UIText<br>
-- text->setFontName("Marfelt"); it will change the font  to  system font no matter the previous font type is TTF or system font<br>
-- text->setFontName("xxxx/xxx.ttf");it will change the font  to TTF font no matter the previous font type is TTF or system font<br>
-- param name font name.
-- @function [parent=#Text] setFontName 
-- @param self
-- @param #string name
        
--------------------------------
-- Sets the touch scale enabled of label.<br>
-- param enabled touch scale enabled of label.
-- @function [parent=#Text] setTouchScaleChangeEnabled 
-- @param self
-- @param #bool enabled
        
--------------------------------
-- 
-- @function [parent=#Text] setString 
-- @param self
-- @param #string text
        
--------------------------------
-- Gets the touch scale enabled of label.<br>
-- return  touch scale enabled of label.
-- @function [parent=#Text] isTouchScaleChangeEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Text] getFontName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Set the rendering size of the text, you should call this method<br>
-- along with calling `ignoreContentAdaptWithSize(false)`, otherwise the text area<br>
-- size is caculated by the real size of the text content<br>
-- param size   The text rendering area size
-- @function [parent=#Text] setTextAreaSize 
-- @param self
-- @param #size_table size
        
--------------------------------
-- Gets the string length of the label.<br>
-- Note: This length will be larger than the raw string length,<br>
-- if you want to get the raw string length, you should call this->getString().size() instead<br>
-- return  string length.
-- @function [parent=#Text] getStringLength 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- Enable outline for the label<br>
-- It only works on IOS and Android when you use System fonts
-- @function [parent=#Text] enableOutline 
-- @param self
-- @param #color4b_table outlineColor
-- @param #int outlineSize
        
--------------------------------
-- 
-- @function [parent=#Text] getType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#Text] getTextHorizontalAlignment 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Sets the font size of label.<br>
-- param size font size.
-- @function [parent=#Text] setFontSize 
-- @param self
-- @param #int size
        
--------------------------------
-- 
-- @function [parent=#Text] setTextColor 
-- @param self
-- @param #color4b_table color
        
--------------------------------
--  only support for TTF 
-- @function [parent=#Text] enableGlow 
-- @param self
-- @param #color4b_table glowColor
        
--------------------------------
-- 
-- @function [parent=#Text] getTextVerticalAlignment 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#Text] getTextAreaSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- 
-- @function [parent=#Text] setTextHorizontalAlignment 
-- @param self
-- @param #int alignment
        
--------------------------------
-- @overload self, string, string, int         
-- @overload self         
-- @function [parent=#Text] create
-- @param self
-- @param #string textContent
-- @param #string fontName
-- @param #int fontSize
-- @return Text#Text ret (return value: ccui.Text)

--------------------------------
-- 
-- @function [parent=#Text] createInstance 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- 
-- @function [parent=#Text] getVirtualRenderer 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- Returns the "class name" of widget.
-- @function [parent=#Text] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#Text] getVirtualRendererSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- Default constructor
-- @function [parent=#Text] Text 
-- @param self
        
return nil
