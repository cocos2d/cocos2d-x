
--------------------------------
-- @module EditBox
-- @extend ControlButton,IMEDelegate
-- @parent_module cc

--------------------------------
-- Get the text entered in the edit box.<br>
-- return The text entered in the edit box.
-- @function [parent=#EditBox] getText 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- Set the placeholder's font name.<br>
-- param pFontName The font name.
-- @function [parent=#EditBox] setPlaceholderFontName 
-- @param self
-- @param #char pFontName
        
--------------------------------
-- Get a text in the edit box that acts as a placeholder when an<br>
-- edit box is empty.
-- @function [parent=#EditBox] getPlaceHolder 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- Set the font name.<br>
-- param pFontName The font name.
-- @function [parent=#EditBox] setFontName 
-- @param self
-- @param #char pFontName
        
--------------------------------
-- Set the placeholder's font size.<br>
-- param fontSize The font size.
-- @function [parent=#EditBox] setPlaceholderFontSize 
-- @param self
-- @param #int fontSize
        
--------------------------------
-- Set the input mode of the edit box.<br>
-- param inputMode One of the EditBox::InputMode constants.
-- @function [parent=#EditBox] setInputMode 
-- @param self
-- @param #int inputMode
        
--------------------------------
-- Set the font color of the placeholder text when the edit box is empty.<br>
-- Not supported on IOS.
-- @function [parent=#EditBox] setPlaceholderFontColor 
-- @param self
-- @param #color3b_table color
        
--------------------------------
-- Set the font color of the widget's text.
-- @function [parent=#EditBox] setFontColor 
-- @param self
-- @param #color3b_table color
        
--------------------------------
-- Set the placeholder's font.<br>
-- param pFontName The font name.<br>
-- param fontSize The font size.
-- @function [parent=#EditBox] setPlaceholderFont 
-- @param self
-- @param #char pFontName
-- @param #int fontSize
        
--------------------------------
-- Set the font size.<br>
-- param fontSize The font size.
-- @function [parent=#EditBox] setFontSize 
-- @param self
-- @param #int fontSize
        
--------------------------------
-- Init edit box with specified size. This method should be invoked right after constructor.<br>
-- param size The size of edit box.
-- @function [parent=#EditBox] initWithSizeAndBackgroundSprite 
-- @param self
-- @param #size_table size
-- @param #cc.Scale9Sprite pNormal9SpriteBg
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Set a text in the edit box that acts as a placeholder when an<br>
-- edit box is empty.<br>
-- param pText The given text.
-- @function [parent=#EditBox] setPlaceHolder 
-- @param self
-- @param #char pText
        
--------------------------------
-- Set the return type that are to be applied to the edit box.<br>
-- param returnType One of the EditBox::KeyboardReturnType constants.
-- @function [parent=#EditBox] setReturnType 
-- @param self
-- @param #int returnType
        
--------------------------------
-- Set the input flags that are to be applied to the edit box.<br>
-- param inputFlag One of the EditBox::InputFlag constants.
-- @function [parent=#EditBox] setInputFlag 
-- @param self
-- @param #int inputFlag
        
--------------------------------
-- Gets the maximum input length of the edit box.<br>
-- return Maximum input length.
-- @function [parent=#EditBox] getMaxLength 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Set the text entered in the edit box.<br>
-- param pText The given text.
-- @function [parent=#EditBox] setText 
-- @param self
-- @param #char pText
        
--------------------------------
-- Sets the maximum input length of the edit box.<br>
-- Setting this value enables multiline input mode by default.<br>
-- Available on Android, iOS and Windows Phone.<br>
-- param maxLength The maximum length.
-- @function [parent=#EditBox] setMaxLength 
-- @param self
-- @param #int maxLength
        
--------------------------------
-- Set the font.<br>
-- param pFontName The font name.<br>
-- param fontSize The font size.
-- @function [parent=#EditBox] setFont 
-- @param self
-- @param #char pFontName
-- @param #int fontSize
        
--------------------------------
-- create a edit box with size.<br>
-- return An autorelease pointer of EditBox, you don't need to release it only if you retain it again.
-- @function [parent=#EditBox] create 
-- @param self
-- @param #size_table size
-- @param #cc.Scale9Sprite pNormal9SpriteBg
-- @param #cc.Scale9Sprite pPressed9SpriteBg
-- @param #cc.Scale9Sprite pDisabled9SpriteBg
-- @return EditBox#EditBox ret (return value: cc.EditBox)
        
--------------------------------
-- 
-- @function [parent=#EditBox] setAnchorPoint 
-- @param self
-- @param #vec2_table anchorPoint
        
--------------------------------
-- 
-- @function [parent=#EditBox] setPosition 
-- @param self
-- @param #vec2_table pos
        
--------------------------------
-- 
-- @function [parent=#EditBox] setVisible 
-- @param self
-- @param #bool visible
        
--------------------------------
-- 
-- @function [parent=#EditBox] setContentSize 
-- @param self
-- @param #size_table size
        
--------------------------------
-- Constructor.<br>
-- js ctor
-- @function [parent=#EditBox] EditBox 
-- @param self
        
return nil
