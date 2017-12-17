
--------------------------------
-- @module TabControl
-- @extend Widget
-- @parent_module ccui

--------------------------------
-- set header width, affect all tab<br>
-- param headerWidth each tab header's width
-- @function [parent=#TabControl] setHeaderWidth 
-- @param self
-- @param #float headerWidth
-- @return TabControl#TabControl self (return value: ccui.TabControl)
        
--------------------------------
-- remove the tab from this TabControl<br>
-- param index The index of tab
-- @function [parent=#TabControl] removeTab 
-- @param self
-- @param #int index
-- @return TabControl#TabControl self (return value: ccui.TabControl)
        
--------------------------------
-- get the count of tabs in this TabControl<br>
-- return the count of tabs
-- @function [parent=#TabControl] getTabCount 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- 
-- @function [parent=#TabControl] getHeaderDockPlace 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- get current selected tab's index<br>
-- return the current selected tab index
-- @function [parent=#TabControl] getSelectedTabIndex 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- insert tab, and init the position of header and container<br>
-- param index The index tab should be<br>
-- param header The header Button, will be a protected child in TabControl<br>
-- param container The container, will be a protected child in TabControl
-- @function [parent=#TabControl] insertTab 
-- @param self
-- @param #int index
-- @param #ccui.TabHeader header
-- @param #ccui.Layout container
-- @return TabControl#TabControl self (return value: ccui.TabControl)
        
--------------------------------
-- ignore the textures' size in header, scale them with _headerWidth and _headerHeight<br>
-- param ignore is `true`, the header's texture scale with _headerWidth and _headerHeight<br>
-- ignore is `false`, use the texture's size, do not scale them
-- @function [parent=#TabControl] ignoreHeadersTextureSize 
-- @param self
-- @param #bool ignore
-- @return TabControl#TabControl self (return value: ccui.TabControl)
        
--------------------------------
-- get tab header's width<br>
-- return header's width
-- @function [parent=#TabControl] getHeaderWidth 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- the header dock place of header in TabControl<br>
-- param dockPlace The strip place
-- @function [parent=#TabControl] setHeaderDockPlace 
-- @param self
-- @param #int dockPlace
-- @return TabControl#TabControl self (return value: ccui.TabControl)
        
--------------------------------
-- @overload self, ccui.TabHeader         
-- @overload self, int         
-- @function [parent=#TabControl] setSelectTab
-- @param self
-- @param #int index
-- @return TabControl#TabControl self (return value: ccui.TabControl)

--------------------------------
-- get TabHeader<br>
-- param index The index of tab
-- @function [parent=#TabControl] getTabHeader 
-- @param self
-- @param #int index
-- @return TabHeader#TabHeader ret (return value: ccui.TabHeader)
        
--------------------------------
-- get whether ignore the textures' size in header, scale them with _headerWidth and _headerHeight<br>
-- return whether ignore the textures' size in header
-- @function [parent=#TabControl] isIgnoreHeadersTextureSize 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Add a callback function which would be called when selected tab changed<br>
-- param callback A std::function with type @see `ccTabControlCallback`
-- @function [parent=#TabControl] setTabChangedEventListener 
-- @param self
-- @param #function callback
-- @return TabControl#TabControl self (return value: ccui.TabControl)
        
--------------------------------
-- set the delta zoom of selected tab<br>
-- param zoom The delta zoom
-- @function [parent=#TabControl] setHeaderSelectedZoom 
-- @param self
-- @param #float zoom
-- @return TabControl#TabControl self (return value: ccui.TabControl)
        
--------------------------------
-- set header height, affect all tab<br>
-- param headerHeight each tab header's height
-- @function [parent=#TabControl] setHeaderHeight 
-- @param self
-- @param #float headerHeight
-- @return TabControl#TabControl self (return value: ccui.TabControl)
        
--------------------------------
-- get the index of tabCell in TabView, return -1 if not exists in.<br>
-- return the index of tabCell in TabView, `-1` means not exists in.
-- @function [parent=#TabControl] indexOfTabHeader 
-- @param self
-- @param #ccui.TabHeader tabCell
-- @return int#int ret (return value: int)
        
--------------------------------
-- get Container<br>
-- param index The index of tab
-- @function [parent=#TabControl] getTabContainer 
-- @param self
-- @param #int index
-- @return Layout#Layout ret (return value: ccui.Layout)
        
--------------------------------
-- get the delta zoom of selected tab<br>
-- return zoom, the delta zoom
-- @function [parent=#TabControl] getHeaderSelectedZoom 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- get tab header's height<br>
-- return header's height
-- @function [parent=#TabControl] getHeaderHeight 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#TabControl] create 
-- @param self
-- @return TabControl#TabControl ret (return value: ccui.TabControl)
        
return nil
