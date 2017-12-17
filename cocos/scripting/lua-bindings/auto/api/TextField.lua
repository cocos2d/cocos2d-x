
--------------------------------
-- @module TextField
-- @extend Widget
-- @parent_module ccui

--------------------------------
-- brief Toggle attach with IME.<br>
-- param attach True if attach with IME, false otherwise.
-- @function [parent=#TextField] setAttachWithIME 
-- @param self
-- @param #bool attach
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- brief Query the font size.<br>
-- return The integer font size.
-- @function [parent=#TextField] getFontSize 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Query the content of TextField.<br>
-- return The string value of TextField.
-- @function [parent=#TextField] getString 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- brief Change password style text.<br>
-- param styleText The styleText for password mask, the default value is "*".
-- @function [parent=#TextField] setPasswordStyleText 
-- @param self
-- @param #char styleText
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- brief Whether it is ready to delete backward in TextField.<br>
-- return True is the delete backward is enabled, false otherwise.
-- @function [parent=#TextField] getDeleteBackward 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief Query the text string color.<br>
-- return The color of the text.
-- @function [parent=#TextField] getTextColor 
-- @param self
-- @return color4b_table#color4b_table ret (return value: color4b_table)
        
--------------------------------
-- brief Get the placeholder of TextField.<br>
-- return A placeholder string.
-- @function [parent=#TextField] getPlaceHolder 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- brief Query whether the IME is attached or not.<br>
-- return True if IME is attached, false otherwise.
-- @function [parent=#TextField] getAttachWithIME 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief Change the font name of TextField.<br>
-- param name The font name string.
-- @function [parent=#TextField] setFontName 
-- @param self
-- @param #string name
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- brief Whether it is ready to get the inserted text or not.<br>
-- return True if the insert text is ready, false otherwise.
-- @function [parent=#TextField] getInsertText 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief Toggle enable insert text mode<br>
-- param insertText True if enable insert text, false otherwise.
-- @function [parent=#TextField] setInsertText 
-- @param self
-- @param #bool insertText
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- Change content of TextField.<br>
-- param text A string content.
-- @function [parent=#TextField] setString 
-- @param self
-- @param #string text
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- brief Query whether IME is detached or not.<br>
-- return True if IME is detached, false otherwise.
-- @function [parent=#TextField] getDetachWithIME 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief Change the vertical text alignment.<br>
-- param alignment A alignment arguments in @see `TextVAlignment`.
-- @function [parent=#TextField] setTextVerticalAlignment 
-- @param self
-- @param #int alignment
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- Add a event listener to TextField, when some predefined event happens, the callback will be called.<br>
-- param callback A callback function with type of `ccTextFieldCallback`.
-- @function [parent=#TextField] addEventListener 
-- @param self
-- @param #function callback
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- brief Detach the IME.
-- @function [parent=#TextField] didNotSelectSelf 
-- @param self
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- brief Query the TextField's font name.<br>
-- return The font name string.
-- @function [parent=#TextField] getFontName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- brief Change the text area size.<br>
-- param size A delimitation zone.
-- @function [parent=#TextField] setTextAreaSize 
-- @param self
-- @param #size_table size
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- brief Attach the IME for inputing.
-- @function [parent=#TextField] attachWithIME 
-- @param self
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- brief Query the input string length.<br>
-- return A integer length value.
-- @function [parent=#TextField] getStringLength 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- brief Get the renderer size in auto mode.<br>
-- return A delimitation zone.
-- @function [parent=#TextField] getAutoRenderSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- brief Toggle enable password input mode.<br>
-- param enable True if enable password input mode, false otherwise.
-- @function [parent=#TextField] setPasswordEnabled 
-- @param self
-- @param #bool enable
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- brief Query the placeholder string color.<br>
-- return The color of placeholder.
-- @function [parent=#TextField] getPlaceHolderColor 
-- @param self
-- @return color4b_table#color4b_table ret (return value: color4b_table)
        
--------------------------------
-- brief Query the password style text.<br>
-- return A password style text.
-- @function [parent=#TextField] getPasswordStyleText 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- brief Toggle maximize length enable<br>
-- param enable True if enable maximize length, false otherwise.
-- @function [parent=#TextField] setMaxLengthEnabled 
-- @param self
-- @param #bool enable
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- brief Query whether password is enabled or not.<br>
-- return True if password is enabled, false otherwise.
-- @function [parent=#TextField] isPasswordEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief Toggle enable delete backward mode.<br>
-- param deleteBackward True is delete backward is enabled, false otherwise.
-- @function [parent=#TextField] setDeleteBackward 
-- @param self
-- @param #bool deleteBackward
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- Set cursor position, if enabled<br>
-- js NA
-- @function [parent=#TextField] setCursorPosition 
-- @param self
-- @param #unsigned int cursorPosition
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- brief Inquire the horizontal alignment<br>
-- return The horizontal alignment
-- @function [parent=#TextField] getTextHorizontalAlignment 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- brief Change font size of TextField.<br>
-- param size The integer font size.
-- @function [parent=#TextField] setFontSize 
-- @param self
-- @param #int size
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- brief Set placeholder of TextField.<br>
-- param value The string value of placeholder.
-- @function [parent=#TextField] setPlaceHolder 
-- @param self
-- @param #string value
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- Set cursor position to hit letter, if enabled<br>
-- js NA
-- @function [parent=#TextField] setCursorFromPoint 
-- @param self
-- @param #vec2_table point
-- @param #cc.Camera camera
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- @overload self, color4b_table         
-- @overload self, color3b_table         
-- @function [parent=#TextField] setPlaceHolderColor
-- @param self
-- @param #color3b_table color
-- @return TextField#TextField self (return value: ccui.TextField)

--------------------------------
-- brief Change horizontal text alignment.<br>
-- param alignment A alignment arguments in @see `TextHAlignment`.
-- @function [parent=#TextField] setTextHorizontalAlignment 
-- @param self
-- @param #int alignment
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- brief Change the text color.<br>
-- param textColor The color value in `Color4B`.
-- @function [parent=#TextField] setTextColor 
-- @param self
-- @param #color4b_table textColor
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- Set char showing cursor.<br>
-- js NA
-- @function [parent=#TextField] setCursorChar 
-- @param self
-- @param #char cursor
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- brief Query maximize input length of TextField.<br>
-- return The integer value of maximize input length.
-- @function [parent=#TextField] getMaxLength 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- brief Query whether max length is enabled or not.<br>
-- return True if maximize length is enabled, false otherwise.
-- @function [parent=#TextField] isMaxLengthEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief Toggle detach with IME.<br>
-- param detach True if detach with IME, false otherwise.
-- @function [parent=#TextField] setDetachWithIME 
-- @param self
-- @param #bool detach
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- brief Inquire the horizontal alignment<br>
-- return The horizontal alignment
-- @function [parent=#TextField] getTextVerticalAlignment 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- brief Toggle enable touch area.<br>
-- param enable True if enable touch area, false otherwise.
-- @function [parent=#TextField] setTouchAreaEnabled 
-- @param self
-- @param #bool enable
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- brief Change maximize input length limitation.<br>
-- param length A character count in integer.
-- @function [parent=#TextField] setMaxLength 
-- @param self
-- @param #int length
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- Set enable cursor use.<br>
-- js NA
-- @function [parent=#TextField] setCursorEnabled 
-- @param self
-- @param #bool enabled
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- brief Set the touch size<br>
-- The touch size is used for @see `hitTest`.<br>
-- param size A delimitation zone.
-- @function [parent=#TextField] setTouchSize 
-- @param self
-- @param #size_table size
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- brief Get current touch size of TextField.<br>
-- return The TextField's touch size.
-- @function [parent=#TextField] getTouchSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @overload self, string, string, int         
-- @overload self         
-- @function [parent=#TextField] create
-- @param self
-- @param #string placeholder
-- @param #string fontName
-- @param #int fontSize
-- @return TextField#TextField ret (return value: ccui.TextField)

--------------------------------
-- 
-- @function [parent=#TextField] createInstance 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- 
-- @function [parent=#TextField] getVirtualRenderer 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- Returns the "class name" of widget.
-- @function [parent=#TextField] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#TextField] update 
-- @param self
-- @param #float dt
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- 
-- @function [parent=#TextField] hitTest 
-- @param self
-- @param #vec2_table pt
-- @param #cc.Camera camera
-- @param #vec3_table p
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#TextField] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#TextField] getVirtualRendererSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- brief Default constructor.
-- @function [parent=#TextField] TextField 
-- @param self
-- @return TextField#TextField self (return value: ccui.TextField)
        
return nil
