
--------------------------------
-- @module PageView
-- @extend Layout
-- @parent_module ccui

--------------------------------
-- brief Query the custom scroll threshold of the PageView.<br>
-- return Custom scroll threshold in float.
-- @function [parent=#PageView] getCustomScrollThreshold 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Gets current displayed page index.<br>
-- return current page index.
-- @function [parent=#PageView] getCurPageIndex 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- Add a widget as a page of PageView in a given index.<br>
-- param widget    Widget to be added to pageview.<br>
-- param pageIdx   A given index.<br>
-- param forceCreate   If `forceCreate` is true and `widget` isn't exists, pageview would create a default page and add it.
-- @function [parent=#PageView] addWidgetToPage 
-- @param self
-- @param #ccui.Widget widget
-- @param #long pageIdx
-- @param #bool forceCreate
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- brief Query whether use user defined scroll page threshold or not.<br>
-- return True if using custom scroll threshold, false otherwise.
-- @function [parent=#PageView] isUsingCustomScrollThreshold 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief Get a page at a given index<br>
-- param index A given index.<br>
-- return A layout pointer in PageView container.
-- @function [parent=#PageView] getPage 
-- @param self
-- @param #long index
-- @return Layout#Layout ret (return value: ccui.Layout)
        
--------------------------------
-- Remove a page of PageView.<br>
-- param page  Page to be removed.
-- @function [parent=#PageView] removePage 
-- @param self
-- @param #ccui.Layout page
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- brief Add a page turn callback to PageView, then when one page is turning, the callback will be called.<br>
-- param callback A page turning callback.
-- @function [parent=#PageView] addEventListener 
-- @param self
-- @param #function callback
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- brief Set using user defined scroll page threshold or not.<br>
-- If you set it to false, then the default scroll threshold is pageView.width / 2<br>
-- param flag True if using custom scroll threshold, false otherwise.
-- @function [parent=#PageView] setUsingCustomScrollThreshold 
-- @param self
-- @param #bool flag
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- brief If you don't specify the value, the pageView will turn page when scrolling at the half width of a page.<br>
-- param threshold  A threshold in float.
-- @function [parent=#PageView] setCustomScrollThreshold 
-- @param self
-- @param #float threshold
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- Insert a page into PageView at a given index.<br>
-- param page  Page to be inserted.<br>
-- param idx   A given index.
-- @function [parent=#PageView] insertPage 
-- @param self
-- @param #ccui.Layout page
-- @param #int idx
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- Scroll to a page with a given index.<br>
-- param idx   A given index in the PageView.
-- @function [parent=#PageView] scrollToPage 
-- @param self
-- @param #long idx
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- Remove a page at a given index of PageView.<br>
-- param index  A given index.
-- @function [parent=#PageView] removePageAtIndex 
-- @param self
-- @param #long index
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- brief Get all the pages in the PageView.<br>
-- return A vector of Layout pionters.
-- @function [parent=#PageView] getPages 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- brief Remove all pages of the PageView.
-- @function [parent=#PageView] removeAllPages 
-- @param self
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- Insert a page into the end of PageView.<br>
-- param page Page to be inserted.
-- @function [parent=#PageView] addPage 
-- @param self
-- @param #ccui.Layout page
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- Create an empty PageView.<br>
-- return A PageView instance.
-- @function [parent=#PageView] create 
-- @param self
-- @return PageView#PageView ret (return value: ccui.PageView)
        
--------------------------------
-- 
-- @function [parent=#PageView] createInstance 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- 
-- @function [parent=#PageView] getLayoutType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#PageView] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#PageView] update 
-- @param self
-- @param #float dt
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- 
-- @function [parent=#PageView] setLayoutType 
-- @param self
-- @param #int type
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- Default constructor<br>
-- js ctor<br>
-- lua new
-- @function [parent=#PageView] PageView 
-- @param self
-- @return PageView#PageView self (return value: ccui.PageView)
        
return nil
