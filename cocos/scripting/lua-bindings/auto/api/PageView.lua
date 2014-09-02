
--------------------------------
-- @module PageView
-- @extend Layout
-- @parent_module ccui

--------------------------------
-- brief Return user defined scroll page threshold
-- @function [parent=#PageView] getCustomScrollThreshold 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Gets current page index.<br>
-- return current page index.
-- @function [parent=#PageView] getCurPageIndex 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- Add a widget to a page of pageview.<br>
-- param widget    widget to be added to pageview.<br>
-- param pageIdx   index of page.<br>
-- param forceCreate   if force create and there is no page exsit, pageview would create a default page for adding widget.
-- @function [parent=#PageView] addWidgetToPage 
-- @param self
-- @param #ccui.Widget widget
-- @param #long pageIdx
-- @param #bool forceCreate
        
--------------------------------
-- brief Query whether we are using user defined scroll page threshold or not
-- @function [parent=#PageView] isUsingCustomScrollThreshold 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#PageView] getPage 
-- @param self
-- @param #long index
-- @return Layout#Layout ret (return value: ccui.Layout)
        
--------------------------------
-- Remove a page of pageview.<br>
-- param page    page which will be removed.
-- @function [parent=#PageView] removePage 
-- @param self
-- @param #ccui.Layout page
        
--------------------------------
-- 
-- @function [parent=#PageView] addEventListener 
-- @param self
-- @param #function callback
        
--------------------------------
-- brief Set using user defined scroll page threshold or not<br>
-- If you set it to false, then the default scroll threshold is pageView.width / 2
-- @function [parent=#PageView] setUsingCustomScrollThreshold 
-- @param self
-- @param #bool flag
        
--------------------------------
-- brief If you don't specify the value, the pageView will scroll when half pageview width reached
-- @function [parent=#PageView] setCustomScrollThreshold 
-- @param self
-- @param #float threshold
        
--------------------------------
-- Insert a page to pageview.<br>
-- param page    page to be added to pageview.
-- @function [parent=#PageView] insertPage 
-- @param self
-- @param #ccui.Layout page
-- @param #int idx
        
--------------------------------
-- scroll pageview to index.<br>
-- param idx    index of page.
-- @function [parent=#PageView] scrollToPage 
-- @param self
-- @param #long idx
        
--------------------------------
-- Remove a page at index of pageview.<br>
-- param index    index of page.
-- @function [parent=#PageView] removePageAtIndex 
-- @param self
-- @param #long index
        
--------------------------------
-- 
-- @function [parent=#PageView] getPages 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- 
-- @function [parent=#PageView] removeAllPages 
-- @param self
        
--------------------------------
-- Push back a page to pageview.<br>
-- param page    page to be added to pageview.
-- @function [parent=#PageView] addPage 
-- @param self
-- @param #ccui.Layout page
        
--------------------------------
-- Allocates and initializes.
-- @function [parent=#PageView] create 
-- @param self
-- @return PageView#PageView ret (return value: ccui.PageView)
        
--------------------------------
-- 
-- @function [parent=#PageView] createInstance 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- Gets LayoutType.<br>
-- see LayoutType<br>
-- return LayoutType
-- @function [parent=#PageView] getLayoutType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Returns the "class name" of widget.
-- @function [parent=#PageView] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#PageView] update 
-- @param self
-- @param #float dt
        
--------------------------------
-- Sets LayoutType.<br>
-- see LayoutType<br>
-- param type LayoutType
-- @function [parent=#PageView] setLayoutType 
-- @param self
-- @param #int type
        
--------------------------------
-- Default constructor
-- @function [parent=#PageView] PageView 
-- @param self
        
return nil
