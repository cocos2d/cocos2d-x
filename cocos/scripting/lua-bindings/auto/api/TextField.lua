
--------------------------------
-- @module TextField
-- @extend Widget
-- @parent_module ccui

--------------------------------
-- 
-- @function [parent=#TextField] setAttachWithIME 
-- @param self
-- @param #bool attach
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- 
-- @function [parent=#TextField] getFontSize 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#TextField] getString 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#TextField] setPasswordStyleText 
-- @param self
-- @param #char styleText
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- 
-- @function [parent=#TextField] getDeleteBackward 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#TextField] getPlaceHolder 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#TextField] getAttachWithIME 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#TextField] setFontName 
-- @param self
-- @param #string name
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- 
-- @function [parent=#TextField] getInsertText 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#TextField] setInsertText 
-- @param self
-- @param #bool insertText
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- 
-- @function [parent=#TextField] setString 
-- @param self
-- @param #string text
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- 
-- @function [parent=#TextField] getDetachWithIME 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#TextField] setTextVerticalAlignment 
-- @param self
-- @param #int alignment
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- 
-- @function [parent=#TextField] addEventListener 
-- @param self
-- @param #function callback
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- 
-- @function [parent=#TextField] didNotSelectSelf 
-- @param self
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- 
-- @function [parent=#TextField] getFontName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#TextField] setTextAreaSize 
-- @param self
-- @param #size_table size
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- 
-- @function [parent=#TextField] attachWithIME 
-- @param self
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- 
-- @function [parent=#TextField] getStringLength 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#TextField] getAutoRenderSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- 
-- @function [parent=#TextField] setPasswordEnabled 
-- @param self
-- @param #bool enable
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- 
-- @function [parent=#TextField] getPlaceHolderColor 
-- @param self
-- @return color4b_table#color4b_table ret (return value: color4b_table)
        
--------------------------------
-- 
-- @function [parent=#TextField] getPasswordStyleText 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- 
-- @function [parent=#TextField] setMaxLengthEnabled 
-- @param self
-- @param #bool enable
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- 
-- @function [parent=#TextField] isPasswordEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#TextField] setDeleteBackward 
-- @param self
-- @param #bool deleteBackward
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- 
-- @function [parent=#TextField] setFontSize 
-- @param self
-- @param #int size
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- 
-- @function [parent=#TextField] setPlaceHolder 
-- @param self
-- @param #string value
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- @overload self, color4b_table         
-- @overload self, color3b_table         
-- @function [parent=#TextField] setPlaceHolderColor
-- @param self
-- @param #color3b_table color
-- @return TextField#TextField self (return value: ccui.TextField)

--------------------------------
-- 
-- @function [parent=#TextField] setTextHorizontalAlignment 
-- @param self
-- @param #int alignment
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- 
-- @function [parent=#TextField] setTextColor 
-- @param self
-- @param #color4b_table textColor
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- 
-- @function [parent=#TextField] getMaxLength 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#TextField] isMaxLengthEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#TextField] setDetachWithIME 
-- @param self
-- @param #bool detach
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- 
-- @function [parent=#TextField] setTouchAreaEnabled 
-- @param self
-- @param #bool enable
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- 
-- @function [parent=#TextField] hitTest 
-- @param self
-- @param #vec2_table pt
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#TextField] setMaxLength 
-- @param self
-- @param #int length
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- 
-- @function [parent=#TextField] setTouchSize 
-- @param self
-- @param #size_table size
-- @return TextField#TextField self (return value: ccui.TextField)
        
--------------------------------
-- 
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
-- @function [parent=#TextField] getVirtualRendererSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- 
-- @function [parent=#TextField] TextField 
-- @param self
-- @return TextField#TextField self (return value: ccui.TextField)
        
return nil
