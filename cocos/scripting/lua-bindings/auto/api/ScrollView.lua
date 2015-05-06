
--------------------------------
-- @module ScrollView
-- @extend Layout
-- @parent_module ccui

--------------------------------
-- Scroll inner container to top boundary of scrollview.<br>
-- param second Time in seconds.<br>
-- param attenuated Whether scroll speed attenuate or not.
-- @function [parent=#ScrollView] scrollToTop 
-- @param self
-- @param #float second
-- @param #bool attenuated
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- Scroll inner container to horizontal percent position of scrollview.<br>
-- param percent A value between 0 and 100.<br>
-- param second Time in seconds.<br>
-- param attenuated Whether scroll speed attenuate or not.
-- @function [parent=#ScrollView] scrollToPercentHorizontal 
-- @param self
-- @param #float percent
-- @param #float second
-- @param #bool attenuated
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- brief Query inertia scroll state.<br>
-- return True if inertia is enabled, false otherwise.
-- @function [parent=#ScrollView] isInertiaScrollEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Scroll inner container to both direction percent position of scrollview.<br>
-- param percent A value between 0 and 100.<br>
-- param second Time in seconds.<br>
-- param attenuated Whether scroll speed attenuate or not.
-- @function [parent=#ScrollView] scrollToPercentBothDirection 
-- @param self
-- @param #vec2_table percent
-- @param #float second
-- @param #bool attenuated
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- Query scroll direction of scrollview.<br>
-- see `Direction`      Direction::VERTICAL means vertical scroll, Direction::HORIZONTAL means horizontal scroll<br>
-- return Scrollview scroll direction.
-- @function [parent=#ScrollView] getDirection 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Scroll inner container to bottom and left boundary of scrollview.<br>
-- param second Time in seconds.<br>
-- param attenuated Whether scroll speed attenuate or not.
-- @function [parent=#ScrollView] scrollToBottomLeft 
-- @param self
-- @param #float second
-- @param #bool attenuated
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- Get inner container of scrollview.<br>
-- Inner container is a child of scrollview.<br>
-- return Inner container pointer.
-- @function [parent=#ScrollView] getInnerContainer 
-- @param self
-- @return Layout#Layout ret (return value: ccui.Layout)
        
--------------------------------
-- Move inner container to bottom boundary of scrollview.
-- @function [parent=#ScrollView] jumpToBottom 
-- @param self
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- Changes scroll direction of scrollview.<br>
-- see `Direction`<br>
-- param dir Scroll direction enum.
-- @function [parent=#ScrollView] setDirection 
-- @param self
-- @param #int dir
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- Scroll inner container to top and left boundary of scrollview.<br>
-- param second Time in seconds.<br>
-- param attenuated Whether scroll speed attenuate or not.
-- @function [parent=#ScrollView] scrollToTopLeft 
-- @param self
-- @param #float second
-- @param #bool attenuated
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- Move inner container to top and right boundary of scrollview.
-- @function [parent=#ScrollView] jumpToTopRight 
-- @param self
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- Move inner container to bottom and left boundary of scrollview.
-- @function [parent=#ScrollView] jumpToBottomLeft 
-- @param self
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- Change inner container size of scrollview.<br>
-- Inner container size must be larger than or equal scrollview's size.<br>
-- param size Inner container size.
-- @function [parent=#ScrollView] setInnerContainerSize 
-- @param self
-- @param #size_table size
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- Get inner container size of scrollview.<br>
-- Inner container size must be larger than or equal scrollview's size.<br>
-- return The inner container size.
-- @function [parent=#ScrollView] getInnerContainerSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- brief Query bounce state.<br>
-- return True if bounce is enabled, false otherwise.
-- @function [parent=#ScrollView] isBounceEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Move inner container to vertical percent position of scrollview.<br>
-- param percent A value between 0 and 100.
-- @function [parent=#ScrollView] jumpToPercentVertical 
-- @param self
-- @param #float percent
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- Add callback function which will be called  when scrollview event triggered.<br>
-- param callback A callback function with type of `ccScrollViewCallback`.
-- @function [parent=#ScrollView] addEventListener 
-- @param self
-- @param #function callback
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- brief Toggle whether enable scroll inertia while scrolling.<br>
-- param enabled True if enable inertia, false otherwise.
-- @function [parent=#ScrollView] setInertiaScrollEnabled 
-- @param self
-- @param #bool enabled
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- Move inner container to top and left boundary of scrollview.
-- @function [parent=#ScrollView] jumpToTopLeft 
-- @param self
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- Move inner container to horizontal percent position of scrollview.<br>
-- param percent   A value between 0 and 100.
-- @function [parent=#ScrollView] jumpToPercentHorizontal 
-- @param self
-- @param #float percent
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- Move inner container to bottom and right boundary of scrollview.
-- @function [parent=#ScrollView] jumpToBottomRight 
-- @param self
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- brief Toggle bounce enabled when scroll to the edge.<br>
-- param enabled True if enable bounce, false otherwise.
-- @function [parent=#ScrollView] setBounceEnabled 
-- @param self
-- @param #bool enabled
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- Move inner container to top boundary of scrollview.
-- @function [parent=#ScrollView] jumpToTop 
-- @param self
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- Scroll inner container to left boundary of scrollview.<br>
-- param second Time in seconds.<br>
-- param attenuated Whether scroll speed attenuate or not.
-- @function [parent=#ScrollView] scrollToLeft 
-- @param self
-- @param #float second
-- @param #bool attenuated
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- Move inner container to both direction percent position of scrollview.<br>
-- param percent   A value between 0 and 100.
-- @function [parent=#ScrollView] jumpToPercentBothDirection 
-- @param self
-- @param #vec2_table percent
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- Scroll inner container to vertical percent position of scrollview.<br>
-- param percent A value between 0 and 100.<br>
-- param second Time in seconds.<br>
-- param attenuated Whether scroll speed attenuate or not.
-- @function [parent=#ScrollView] scrollToPercentVertical 
-- @param self
-- @param #float percent
-- @param #float second
-- @param #bool attenuated
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- Scroll inner container to bottom boundary of scrollview.<br>
-- param second Time in seconds.<br>
-- param attenuated Whether scroll speed attenuate or not.
-- @function [parent=#ScrollView] scrollToBottom 
-- @param self
-- @param #float second
-- @param #bool attenuated
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- Scroll inner container to bottom and right boundary of scrollview.<br>
-- param second Time in seconds<br>
-- param attenuated Whether scroll speed attenuate or not.
-- @function [parent=#ScrollView] scrollToBottomRight 
-- @param self
-- @param #float time
-- @param #bool attenuated
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- Move inner container to left boundary of scrollview.
-- @function [parent=#ScrollView] jumpToLeft 
-- @param self
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- Scroll inner container to right boundary of scrollview.<br>
-- param second Time in seconds.<br>
-- param attenuated Whether scroll speed attenuate or not.
-- @function [parent=#ScrollView] scrollToRight 
-- @param self
-- @param #float time
-- @param #bool attenuated
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- Move inner container to right boundary of scrollview.
-- @function [parent=#ScrollView] jumpToRight 
-- @param self
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- Scroll inner container to top and right boundary of scrollview.<br>
-- param second Time in seconds.<br>
-- param attenuated Whether scroll speed attenuate or not.
-- @function [parent=#ScrollView] scrollToTopRight 
-- @param self
-- @param #float time
-- @param #bool attenuated
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- Create an empty ScrollView.<br>
-- return A ScrollView instance.
-- @function [parent=#ScrollView] create 
-- @param self
-- @return ScrollView#ScrollView ret (return value: ccui.ScrollView)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] createInstance 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- @overload self, cc.Node, int         
-- @overload self, cc.Node         
-- @overload self, cc.Node, int, int         
-- @overload self, cc.Node, int, string         
-- @function [parent=#ScrollView] addChild
-- @param self
-- @param #cc.Node child
-- @param #int localZOrder
-- @param #string name
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)

--------------------------------
-- 
-- @function [parent=#ScrollView] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] getChildByName 
-- @param self
-- @param #string name
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- Return the "class name" of widget.
-- @function [parent=#ScrollView] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] update 
-- @param self
-- @param #float dt
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- Get the layout type for scrollview.<br>
-- see `Layout::Type`<br>
-- return LayoutType
-- @function [parent=#ScrollView] getLayoutType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] removeAllChildrenWithCleanup 
-- @param self
-- @param #bool cleanup
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] removeAllChildren 
-- @param self
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- When a widget is in a layout, you could call this method to get the next focused widget within a specified direction.<br>
-- If the widget is not in a layout, it will return itself<br>
-- param direction the direction to look for the next focused widget in a layout<br>
-- param current  the current focused widget<br>
-- return the next focused widget in a layout
-- @function [parent=#ScrollView] findNextFocusedWidget 
-- @param self
-- @param #int direction
-- @param #ccui.Widget current
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] removeChild 
-- @param self
-- @param #cc.Node child
-- @param #bool cleaup
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#ScrollView] getChildren
-- @param self
-- @return array_table#array_table ret (return value: array_table)

--------------------------------
-- 
-- @function [parent=#ScrollView] getChildByTag 
-- @param self
-- @param #int tag
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] getChildrenCount 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- Set layout type for scrollview.<br>
-- see `Layout::Type`<br>
-- param type  Layout type enum.
-- @function [parent=#ScrollView] setLayoutType 
-- @param self
-- @param #int type
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
--------------------------------
-- Default constructor<br>
-- js ctor<br>
-- lua new
-- @function [parent=#ScrollView] ScrollView 
-- @param self
-- @return ScrollView#ScrollView self (return value: ccui.ScrollView)
        
return nil
