
--------------------------------
-- @module TextBMFont
-- @extend Widget
-- @parent_module ccui

--------------------------------
--  init a bitmap font atlas with an initial string and the FNT file 
-- @function [parent=#TextBMFont] setFntFile 
-- @param self
-- @param #string fileName
        
--------------------------------
-- Gets the string length of the label.<br>
-- Note: This length will be larger than the raw string length,<br>
-- if you want to get the raw string length, you should call this->getString().size() instead<br>
-- return  string length.
-- @function [parent=#TextBMFont] getStringLength 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- 
-- @function [parent=#TextBMFont] setString 
-- @param self
-- @param #string value
        
--------------------------------
-- 
-- @function [parent=#TextBMFont] getString 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @overload self, string, string         
-- @overload self         
-- @function [parent=#TextBMFont] create
-- @param self
-- @param #string text
-- @param #string filename
-- @return TextBMFont#TextBMFont ret (return value: ccui.TextBMFont)

--------------------------------
-- 
-- @function [parent=#TextBMFont] createInstance 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- 
-- @function [parent=#TextBMFont] getVirtualRenderer 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- Returns the "class name" of widget.
-- @function [parent=#TextBMFont] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#TextBMFont] getVirtualRendererSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- Default constructor
-- @function [parent=#TextBMFont] TextBMFont 
-- @param self
        
return nil
