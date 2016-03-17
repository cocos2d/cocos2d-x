
--------------------------------
-- @module PageView
-- @extend ListView
-- @parent_module ccui

--------------------------------
-- brief Set space between page indicator's index nodes.<br>
-- param spaceBetweenIndexNodes Space between nodes in pixel.
-- @function [parent=#PageView] setIndicatorSpaceBetweenIndexNodes 
-- @param self
-- @param #float spaceBetweenIndexNodes
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- brief Set color of page indicator's selected index.<br>
-- param spaceBetweenIndexNodes Space between nodes in pixel.
-- @function [parent=#PageView] setIndicatorSelectedIndexColor 
-- @param self
-- @param #color3b_table color
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- brief Get the color of page indicator's selected index.<br>
-- return color
-- @function [parent=#PageView] getIndicatorSelectedIndexColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- brief Get the page indicator's position as anchor point.<br>
-- return positionAsAnchorPoint
-- @function [parent=#PageView] getIndicatorPositionAsAnchorPoint 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- brief Set the page indicator's position in page view.<br>
-- param position The position in page view
-- @function [parent=#PageView] setIndicatorPosition 
-- @param self
-- @param #vec2_table position
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- brief Get the page indicator's position.<br>
-- return positionAsAnchorPoint
-- @function [parent=#PageView] getIndicatorPosition 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Insert a page into PageView at a given index.<br>
-- param page  Page to be inserted.<br>
-- param idx   A given index.
-- @function [parent=#PageView] insertPage 
-- @param self
-- @param #ccui.Widget page
-- @param #int idx
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- Gets current displayed page index.<br>
-- return current page index.
-- @function [parent=#PageView] getCurrentPageIndex 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- Remove a page of PageView.<br>
-- param page  Page to be removed.
-- @function [parent=#PageView] removePage 
-- @param self
-- @param #ccui.Widget page
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- brief Add a page turn callback to PageView, then when one page is turning, the callback will be called.<br>
-- param callback A page turning callback.
-- @function [parent=#PageView] addEventListener 
-- @param self
-- @param #function callback
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- Jump to a page with a given index without scrolling.<br>
-- This is the different between scrollToPage.<br>
-- param index A given index in PageView. Index start from 0 to pageCount -1.
-- @function [parent=#PageView] setCurrentPageIndex 
-- @param self
-- @param #long index
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- brief Query page indicator state.<br>
-- return True if page indicator is enabled, false otherwise.
-- @function [parent=#PageView] getIndicatorEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Scroll to a page with a given index.<br>
-- param idx   A given index in the PageView. Index start from 0 to pageCount -1.
-- @function [parent=#PageView] scrollToPage 
-- @param self
-- @param #long idx
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- brief Set the page indicator's position using anchor point.<br>
-- param positionAsAnchorPoint The position as anchor point.
-- @function [parent=#PageView] setIndicatorPositionAsAnchorPoint 
-- @param self
-- @param #vec2_table positionAsAnchorPoint
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- Scroll to a page with a given index.<br>
-- param idx   A given index in the PageView. Index start from 0 to pageCount -1.
-- @function [parent=#PageView] scrollToItem 
-- @param self
-- @param #long itemIndex
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- brief Toggle page indicator enabled.<br>
-- param enabled True if enable page indicator, false otherwise.
-- @function [parent=#PageView] setIndicatorEnabled 
-- @param self
-- @param #bool enabled
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- Insert a page into the end of PageView.<br>
-- param page Page to be inserted.
-- @function [parent=#PageView] addPage 
-- @param self
-- @param #ccui.Widget page
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- brief Get the space between page indicator's index nodes.<br>
-- return spaceBetweenIndexNodes
-- @function [parent=#PageView] getIndicatorSpaceBetweenIndexNodes 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- brief Remove all pages of the PageView.
-- @function [parent=#PageView] removeAllPages 
-- @param self
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- Remove a page at a given index of PageView.<br>
-- param index  A given index.
-- @function [parent=#PageView] removePageAtIndex 
-- @param self
-- @param #long index
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
-- @function [parent=#PageView] doLayout 
-- @param self
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- 
-- @function [parent=#PageView] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#PageView] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Changes direction<br>
-- Direction Direction::VERTICAL means vertical scroll, Direction::HORIZONTAL means horizontal scroll.<br>
-- param direction Set the page view's scroll direction.
-- @function [parent=#PageView] setDirection 
-- @param self
-- @param #int direction
-- @return PageView#PageView self (return value: ccui.PageView)
        
--------------------------------
-- Default constructor<br>
-- js ctor<br>
-- lua new
-- @function [parent=#PageView] PageView 
-- @param self
-- @return PageView#PageView self (return value: ccui.PageView)
        
return nil
