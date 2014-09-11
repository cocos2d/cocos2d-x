
--------------------------------
-- @module ScrollView
-- @extend Layout
-- @parent_module ccui

--------------------------------
-- Scroll inner container to top boundary of scrollview.
-- @function [parent=#ScrollView] scrollToTop 
-- @param self
-- @param #float time
-- @param #bool attenuated
        
--------------------------------
-- Scroll inner container to horizontal percent position of scrollview.
-- @function [parent=#ScrollView] scrollToPercentHorizontal 
-- @param self
-- @param #float percent
-- @param #float time
-- @param #bool attenuated
        
--------------------------------
-- 
-- @function [parent=#ScrollView] isInertiaScrollEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Scroll inner container to both direction percent position of scrollview.
-- @function [parent=#ScrollView] scrollToPercentBothDirection 
-- @param self
-- @param #vec2_table percent
-- @param #float time
-- @param #bool attenuated
        
--------------------------------
-- Gets scroll direction of scrollview.<br>
-- see Direction      Direction::VERTICAL means vertical scroll, Direction::HORIZONTAL means horizontal scroll<br>
-- return Direction
-- @function [parent=#ScrollView] getDirection 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Scroll inner container to bottom and left boundary of scrollview.
-- @function [parent=#ScrollView] scrollToBottomLeft 
-- @param self
-- @param #float time
-- @param #bool attenuated
        
--------------------------------
-- Gets inner container of scrollview.<br>
-- Inner container is the container of scrollview's children.<br>
-- return inner container.
-- @function [parent=#ScrollView] getInnerContainer 
-- @param self
-- @return Layout#Layout ret (return value: ccui.Layout)
        
--------------------------------
-- Move inner container to bottom boundary of scrollview.
-- @function [parent=#ScrollView] jumpToBottom 
-- @param self
        
--------------------------------
-- Changes scroll direction of scrollview.<br>
-- see Direction      Direction::VERTICAL means vertical scroll, Direction::HORIZONTAL means horizontal scroll<br>
-- param dir
-- @function [parent=#ScrollView] setDirection 
-- @param self
-- @param #int dir
        
--------------------------------
-- Scroll inner container to top and left boundary of scrollview.
-- @function [parent=#ScrollView] scrollToTopLeft 
-- @param self
-- @param #float time
-- @param #bool attenuated
        
--------------------------------
-- Move inner container to top and right boundary of scrollview.
-- @function [parent=#ScrollView] jumpToTopRight 
-- @param self
        
--------------------------------
-- Move inner container to bottom and left boundary of scrollview.
-- @function [parent=#ScrollView] jumpToBottomLeft 
-- @param self
        
--------------------------------
-- Changes inner container size of scrollview.<br>
-- Inner container size must be larger than or equal scrollview's size.<br>
-- param inner container size.
-- @function [parent=#ScrollView] setInnerContainerSize 
-- @param self
-- @param #size_table size
        
--------------------------------
-- Gets inner container size of scrollview.<br>
-- Inner container size must be larger than or equal scrollview's size.<br>
-- return inner container size.
-- @function [parent=#ScrollView] getInnerContainerSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] isBounceEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Move inner container to vertical percent position of scrollview.
-- @function [parent=#ScrollView] jumpToPercentVertical 
-- @param self
-- @param #float percent
        
--------------------------------
-- 
-- @function [parent=#ScrollView] addEventListener 
-- @param self
-- @param #function callback
        
--------------------------------
-- 
-- @function [parent=#ScrollView] setInertiaScrollEnabled 
-- @param self
-- @param #bool enabled
        
--------------------------------
-- Move inner container to top and left boundary of scrollview.
-- @function [parent=#ScrollView] jumpToTopLeft 
-- @param self
        
--------------------------------
-- Move inner container to horizontal percent position of scrollview.
-- @function [parent=#ScrollView] jumpToPercentHorizontal 
-- @param self
-- @param #float percent
        
--------------------------------
-- Move inner container to bottom and right boundary of scrollview.
-- @function [parent=#ScrollView] jumpToBottomRight 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#ScrollView] setBounceEnabled 
-- @param self
-- @param #bool enabled
        
--------------------------------
-- Move inner container to top boundary of scrollview.
-- @function [parent=#ScrollView] jumpToTop 
-- @param self
        
--------------------------------
-- Scroll inner container to left boundary of scrollview.
-- @function [parent=#ScrollView] scrollToLeft 
-- @param self
-- @param #float time
-- @param #bool attenuated
        
--------------------------------
-- Move inner container to both direction percent position of scrollview.
-- @function [parent=#ScrollView] jumpToPercentBothDirection 
-- @param self
-- @param #vec2_table percent
        
--------------------------------
-- Scroll inner container to vertical percent position of scrollview.
-- @function [parent=#ScrollView] scrollToPercentVertical 
-- @param self
-- @param #float percent
-- @param #float time
-- @param #bool attenuated
        
--------------------------------
-- Scroll inner container to bottom boundary of scrollview.
-- @function [parent=#ScrollView] scrollToBottom 
-- @param self
-- @param #float time
-- @param #bool attenuated
        
--------------------------------
-- Scroll inner container to bottom and right boundary of scrollview.
-- @function [parent=#ScrollView] scrollToBottomRight 
-- @param self
-- @param #float time
-- @param #bool attenuated
        
--------------------------------
-- Move inner container to left boundary of scrollview.
-- @function [parent=#ScrollView] jumpToLeft 
-- @param self
        
--------------------------------
-- Scroll inner container to right boundary of scrollview.
-- @function [parent=#ScrollView] scrollToRight 
-- @param self
-- @param #float time
-- @param #bool attenuated
        
--------------------------------
-- Move inner container to right boundary of scrollview.
-- @function [parent=#ScrollView] jumpToRight 
-- @param self
        
--------------------------------
-- Scroll inner container to top and right boundary of scrollview.
-- @function [parent=#ScrollView] scrollToTopRight 
-- @param self
-- @param #float time
-- @param #bool attenuated
        
--------------------------------
-- Allocates and initializes.
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
-- @param #int zOrder
-- @param #string name

--------------------------------
-- 
-- @function [parent=#ScrollView] getChildByName 
-- @param self
-- @param #string name
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- Returns the "class name" of widget.
-- @function [parent=#ScrollView] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] update 
-- @param self
-- @param #float dt
        
--------------------------------
-- Gets LayoutType.<br>
-- see LayoutType<br>
-- return LayoutType
-- @function [parent=#ScrollView] getLayoutType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] removeAllChildrenWithCleanup 
-- @param self
-- @param #bool cleanup
        
--------------------------------
-- 
-- @function [parent=#ScrollView] removeAllChildren 
-- @param self
        
--------------------------------
-- When a widget is in a layout, you could call this method to get the next focused widget within a specified direction.<br>
-- If the widget is not in a layout, it will return itself<br>
-- param dir the direction to look for the next focused widget in a layout<br>
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
        
--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#ScrollView] getChildren
-- @param self
-- @return array_table#array_table ret (retunr value: array_table)

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
-- Sets LayoutType.<br>
-- see LayoutType<br>
-- param LayoutType
-- @function [parent=#ScrollView] setLayoutType 
-- @param self
-- @param #int type
        
--------------------------------
-- Default constructor
-- @function [parent=#ScrollView] ScrollView 
-- @param self
        
return nil
