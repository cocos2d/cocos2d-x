
--------------------------------
-- @module RichText
-- @extend Widget
-- @parent_module ccui

--------------------------------
-- brief Insert a RichElement at a given index.<br>
-- param element A RichElement type.<br>
-- param index A given index.
-- @function [parent=#RichText] insertElement 
-- @param self
-- @param #ccui.RichElement element
-- @param #int index
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- brief Add a RichElement at the end of RichText.<br>
-- param element A RichElement instance.
-- @function [parent=#RichText] pushBackElement 
-- @param self
-- @param #ccui.RichElement element
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
--  @brief sets the wrapping mode: WRAP_PER_CHAR or WRAP_PER_WORD
-- @function [parent=#RichText] setWrapMode 
-- @param self
-- @param #int wrapMode
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- brief Set vertical space between each RichElement.<br>
-- param space Point in float.
-- @function [parent=#RichText] setVerticalSpace 
-- @param self
-- @param #float space
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
--  @brief returns the current wrapping mode 
-- @function [parent=#RichText] getWrapMode 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- brief Rearrange all RichElement in the RichText.<br>
-- It's usually called internally.
-- @function [parent=#RichText] formatText 
-- @param self
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- 
-- @function [parent=#RichText] initWithXML 
-- @param self
-- @param #string xml
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @overload self, ccui.RichElement         
-- @overload self, int         
-- @function [parent=#RichText] removeElement
-- @param self
-- @param #int index
-- @return RichText#RichText self (return value: ccui.RichText)

--------------------------------
-- brief Create a empty RichText.<br>
-- return RichText instance.
-- @function [parent=#RichText] create 
-- @param self
-- @return RichText#RichText ret (return value: ccui.RichText)
        
--------------------------------
-- brief Create a RichText from an XML<br>
-- return RichText instance.
-- @function [parent=#RichText] createWithXML 
-- @param self
-- @param #string xml
-- @return RichText#RichText ret (return value: ccui.RichText)
        
--------------------------------
-- 
-- @function [parent=#RichText] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#RichText] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#RichText] ignoreContentAdaptWithSize 
-- @param self
-- @param #bool ignore
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- brief Default constructor.<br>
-- js ctor<br>
-- lua new
-- @function [parent=#RichText] RichText 
-- @param self
-- @return RichText#RichText self (return value: ccui.RichText)
        
return nil
