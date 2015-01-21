
--------------------------------
-- @module RichText
-- @extend Widget
-- @parent_module ccui

--------------------------------
-- 
-- @function [parent=#RichText] insertElement 
-- @param self
-- @param #ccui.RichElement element
-- @param #int index
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- 
-- @function [parent=#RichText] setAnchorPoint 
-- @param self
-- @param #vec2_table pt
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- 
-- @function [parent=#RichText] pushBackElement 
-- @param self
-- @param #ccui.RichElement element
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- 
-- @function [parent=#RichText] ignoreContentAdaptWithSize 
-- @param self
-- @param #bool ignore
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- 
-- @function [parent=#RichText] setVerticalSpace 
-- @param self
-- @param #float space
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- 
-- @function [parent=#RichText] formatText 
-- @param self
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- @overload self, ccui.RichElement         
-- @overload self, int         
-- @function [parent=#RichText] removeElement
-- @param self
-- @param #int index
-- @return RichText#RichText self (return value: ccui.RichText)

--------------------------------
-- 
-- @function [parent=#RichText] create 
-- @param self
-- @return RichText#RichText ret (return value: ccui.RichText)
        
--------------------------------
-- 
-- @function [parent=#RichText] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#RichText] getVirtualRendererSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- 
-- @function [parent=#RichText] RichText 
-- @param self
-- @return RichText#RichText self (return value: ccui.RichText)
        
return nil
