
--------------------------------
-- @module EditBox
-- @extend Widget,IMEDelegate
-- @parent_module ccui

--------------------------------
-- js NA<br>
-- lua NA
-- @function [parent=#EditBox] keyboardDidShow 
-- @param self
-- @param #cc.IMEKeyboardNotificationInfo info
-- @return EditBox#EditBox self (return value: ccui.EditBox)
        
--------------------------------
-- get a script Handler<br>
-- js NA<br>
-- lua NA
-- @function [parent=#EditBox] getScriptEditBoxHandler 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Get the text entered in the edit box.<br>
-- return The text entered in the edit box.
-- @function [parent=#EditBox] getText 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- js NA<br>
-- lua NA
-- @function [parent=#EditBox] keyboardDidHide 
-- @param self
-- @param #cc.IMEKeyboardNotificationInfo info
-- @return EditBox#EditBox self (return value: ccui.EditBox)
        
--------------------------------
-- Set the placeholder's font name.<br>
-- param pFontName The font name.
-- @function [parent=#EditBox] setPlaceholderFontName 
-- @param self
-- @param #char pFontName
-- @return EditBox#EditBox self (return value: ccui.EditBox)
        
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
-- @return EditBox#EditBox self (return value: ccui.EditBox)
        
--------------------------------
-- Registers a script function that will be called for EditBox events.<br>
-- This handler will be removed automatically after onExit() called.<br>
-- code<br>
-- -- lua sample<br>
-- local function editboxEventHandler(eventType)<br>
-- if eventType == "began" then<br>
-- -- triggered when an edit box gains focus after keyboard is shown<br>
-- elseif eventType == "ended" then<br>
-- -- triggered when an edit box loses focus after keyboard is hidden.<br>
-- elseif eventType == "changed" then<br>
-- -- triggered when the edit box text was changed.<br>
-- elseif eventType == "return" then<br>
-- -- triggered when the return button was pressed or the outside area of keyboard was touched.<br>
-- end<br>
-- end<br>
-- local editbox = EditBox:create(Size(...), Scale9Sprite:create(...))<br>
-- editbox = registerScriptEditBoxHandler(editboxEventHandler)<br>
-- endcode<br>
-- param handler A number that indicates a lua function.<br>
-- js NA<br>
-- lua NA
-- @function [parent=#EditBox] registerScriptEditBoxHandler 
-- @param self
-- @param #int handler
-- @return EditBox#EditBox self (return value: ccui.EditBox)
        
--------------------------------
-- Set the placeholder's font size.<br>
-- param fontSize The font size.
-- @function [parent=#EditBox] setPlaceholderFontSize 
-- @param self
-- @param #int fontSize
-- @return EditBox#EditBox self (return value: ccui.EditBox)
        
--------------------------------
-- Set the input mode of the edit box.<br>
-- param inputMode One of the EditBox::InputMode constants.
-- @function [parent=#EditBox] setInputMode 
-- @param self
-- @param #int inputMode
-- @return EditBox#EditBox self (return value: ccui.EditBox)
        
--------------------------------
-- Unregisters a script function that will be called for EditBox events.<br>
-- js NA<br>
-- lua NA
-- @function [parent=#EditBox] unregisterScriptEditBoxHandler 
-- @param self
-- @return EditBox#EditBox self (return value: ccui.EditBox)
        
--------------------------------
-- js NA<br>
-- lua NA
-- @function [parent=#EditBox] keyboardWillShow 
-- @param self
-- @param #cc.IMEKeyboardNotificationInfo info
-- @return EditBox#EditBox self (return value: ccui.EditBox)
        
--------------------------------
-- Set the font color of the placeholder text when the edit box is empty.<br>
-- Not supported on IOS.
-- @function [parent=#EditBox] setPlaceholderFontColor 
-- @param self
-- @param #color3b_table color
-- @return EditBox#EditBox self (return value: ccui.EditBox)
        
--------------------------------
-- Set the font color of the widget's text.
-- @function [parent=#EditBox] setFontColor 
-- @param self
-- @param #color3b_table color
-- @return EditBox#EditBox self (return value: ccui.EditBox)
        
--------------------------------
-- js NA<br>
-- lua NA
-- @function [parent=#EditBox] keyboardWillHide 
-- @param self
-- @param #cc.IMEKeyboardNotificationInfo info
-- @return EditBox#EditBox self (return value: ccui.EditBox)
        
--------------------------------
-- 
-- @function [parent=#EditBox] touchDownAction 
-- @param self
-- @param #cc.Ref sender
-- @param #int controlEvent
-- @return EditBox#EditBox self (return value: ccui.EditBox)
        
--------------------------------
-- Set the placeholder's font.<br>
-- param pFontName The font name.<br>
-- param fontSize The font size.
-- @function [parent=#EditBox] setPlaceholderFont 
-- @param self
-- @param #char pFontName
-- @param #int fontSize
-- @return EditBox#EditBox self (return value: ccui.EditBox)
        
--------------------------------
-- Set the font size.<br>
-- param fontSize The font size.
-- @function [parent=#EditBox] setFontSize 
-- @param self
-- @param #int fontSize
-- @return EditBox#EditBox self (return value: ccui.EditBox)
        
--------------------------------
-- @overload self, size_table, ccui.Scale9Sprite         
-- @overload self, size_table, string, int         
-- @function [parent=#EditBox] initWithSizeAndBackgroundSprite
-- @param self
-- @param #size_table size
-- @param #string pNormal9SpriteBg
-- @param #int texType
-- @return bool#bool ret (return value: bool)

--------------------------------
-- Set a text in the edit box that acts as a placeholder when an<br>
-- edit box is empty.<br>
-- param pText The given text.
-- @function [parent=#EditBox] setPlaceHolder 
-- @param self
-- @param #char pText
-- @return EditBox#EditBox self (return value: ccui.EditBox)
        
--------------------------------
-- Set the return type that are to be applied to the edit box.<br>
-- param returnType One of the EditBox::KeyboardReturnType constants.
-- @function [parent=#EditBox] setReturnType 
-- @param self
-- @param #int returnType
-- @return EditBox#EditBox self (return value: ccui.EditBox)
        
--------------------------------
-- Set the input flags that are to be applied to the edit box.<br>
-- param inputFlag One of the EditBox::InputFlag constants.
-- @function [parent=#EditBox] setInputFlag 
-- @param self
-- @param #int inputFlag
-- @return EditBox#EditBox self (return value: ccui.EditBox)
        
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
-- @return EditBox#EditBox self (return value: ccui.EditBox)
        
--------------------------------
-- Sets the maximum input length of the edit box.<br>
-- Setting this value enables multiline input mode by default.<br>
-- Available on Android, iOS and Windows Phone.<br>
-- param maxLength The maximum length.
-- @function [parent=#EditBox] setMaxLength 
-- @param self
-- @param #int maxLength
-- @return EditBox#EditBox self (return value: ccui.EditBox)
        
--------------------------------
-- Set the font.<br>
-- param pFontName The font name.<br>
-- param fontSize The font size.
-- @function [parent=#EditBox] setFont 
-- @param self
-- @param #char pFontName
-- @param #int fontSize
-- @return EditBox#EditBox self (return value: ccui.EditBox)
        
--------------------------------
-- @overload self, size_table, string, int         
-- @overload self, size_table, ccui.Scale9Sprite, ccui.Scale9Sprite, ccui.Scale9Sprite         
-- @function [parent=#EditBox] create
-- @param self
-- @param #size_table size
-- @param #ccui.Scale9Sprite normalSprite
-- @param #ccui.Scale9Sprite pressedSprite
-- @param #ccui.Scale9Sprite disabledSprite
-- @return EditBox#EditBox ret (return value: ccui.EditBox)

--------------------------------
-- 
-- @function [parent=#EditBox] setAnchorPoint 
-- @param self
-- @param #vec2_table anchorPoint
-- @return EditBox#EditBox self (return value: ccui.EditBox)
        
--------------------------------
-- Returns the "class name" of widget.
-- @function [parent=#EditBox] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#EditBox] setPosition 
-- @param self
-- @param #vec2_table pos
-- @return EditBox#EditBox self (return value: ccui.EditBox)
        
--------------------------------
-- 
-- @function [parent=#EditBox] setVisible 
-- @param self
-- @param #bool visible
-- @return EditBox#EditBox self (return value: ccui.EditBox)
        
--------------------------------
-- 
-- @function [parent=#EditBox] setContentSize 
-- @param self
-- @param #size_table size
-- @return EditBox#EditBox self (return value: ccui.EditBox)
        
--------------------------------
-- Constructor.<br>
-- js ctor
-- @function [parent=#EditBox] EditBox 
-- @param self
-- @return EditBox#EditBox self (return value: ccui.EditBox)
        
return nil
