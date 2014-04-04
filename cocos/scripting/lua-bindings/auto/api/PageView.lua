
--------------------------------
-- @module PageView
-- @extend Layout,UIScrollInterface

--------------------------------
-- @function [parent=#PageView] getCurPageIndex 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- @function [parent=#PageView] addWidgetToPage 
-- @param self
-- @param #ccui.Widget widget
-- @param #long long
-- @param #bool bool
        
--------------------------------
-- @function [parent=#PageView] getPage 
-- @param self
-- @param #long long
-- @return Layout#Layout ret (return value: ccui.Layout)
        
--------------------------------
-- @function [parent=#PageView] removePage 
-- @param self
-- @param #ccui.Layout layout
        
--------------------------------
-- @function [parent=#PageView] insertPage 
-- @param self
-- @param #ccui.Layout layout
-- @param #int int
        
--------------------------------
-- @function [parent=#PageView] scrollToPage 
-- @param self
-- @param #long long
        
--------------------------------
-- @function [parent=#PageView] removePageAtIndex 
-- @param self
-- @param #long long
        
--------------------------------
-- @function [parent=#PageView] getPages 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- @function [parent=#PageView] removeAllPages 
-- @param self
        
--------------------------------
-- @function [parent=#PageView] addPage 
-- @param self
-- @param #ccui.Layout layout
        
--------------------------------
-- @function [parent=#PageView] create 
-- @param self
-- @return PageView#PageView ret (return value: ccui.PageView)
        
--------------------------------
-- @function [parent=#PageView] createInstance 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- @function [parent=#PageView] getLayoutType 
-- @param self
-- @return LayoutType#LayoutType ret (return value: ccui.LayoutType)
        
--------------------------------
-- @function [parent=#PageView] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#PageView] update 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#PageView] setLayoutType 
-- @param self
-- @param #ccui.LayoutType layouttype
        
--------------------------------
-- @function [parent=#PageView] PageView 
-- @param self
        
return nil
