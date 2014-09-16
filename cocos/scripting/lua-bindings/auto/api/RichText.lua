
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
        
--------------------------------
-- 
-- @function [parent=#RichText] setAnchorPoint 
-- @param self
-- @param #vec2_table pt
        
--------------------------------
-- 
-- @function [parent=#RichText] pushBackElement 
-- @param self
-- @param #ccui.RichElement element
        
--------------------------------
-- 
-- @function [parent=#RichText] ignoreContentAdaptWithSize 
-- @param self
-- @param #bool ignore
        
--------------------------------
-- 
-- @function [parent=#RichText] setVerticalSpace 
-- @param self
-- @param #float space
        
--------------------------------
-- 
-- @function [parent=#RichText] formatText 
-- @param self
        
--------------------------------
-- @overload self, ccui.RichElement         
-- @overload self, int         
-- @function [parent=#RichText] removeElement
-- @param self
-- @param #int index

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
        
return nil
