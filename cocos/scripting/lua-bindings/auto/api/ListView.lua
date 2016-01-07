
--------------------------------
-- @module ListView
-- @extend ScrollView
-- @parent_module ccui

--------------------------------
-- Set the gravity of ListView.<br>
-- see `ListViewGravity`
-- @function [parent=#ListView] setGravity 
-- @param self
-- @param #int gravity
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- Removes the last item of ListView.
-- @function [parent=#ListView] removeLastItem 
-- @param self
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- brief Query the center item<br>
-- return A item instance.
-- @function [parent=#ListView] getCenterItemInCurrentView 
-- @param self
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- brief Query current selected widget's idnex.<br>
-- return A index of a selected item.
-- @function [parent=#ListView] getCurSelectedIndex 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- brief Query margin between each item in ListView.<br>
-- return A margin in float.
-- @function [parent=#ListView] getItemsMargin 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- brief Jump to specific item<br>
-- param itemIndex Specifies the item's index<br>
-- param positionRatioInView Specifies the position with ratio in list view's content size.<br>
-- param itemAnchorPoint Specifies an anchor point of each item for position to calculate distance.
-- @function [parent=#ListView] jumpToItem 
-- @param self
-- @param #long itemIndex
-- @param #vec2_table positionRatioInView
-- @param #vec2_table itemAnchorPoint
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- Set magnetic type of ListView.<br>
-- see `MagneticType`
-- @function [parent=#ListView] setMagneticType 
-- @param self
-- @param #int magneticType
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- Return the index of specified widget.<br>
-- param item  A widget pointer.<br>
-- return The index of a given widget in ListView.
-- @function [parent=#ListView] getIndex 
-- @param self
-- @param #ccui.Widget item
-- @return long#long ret (return value: long)
        
--------------------------------
-- Insert a  custom item into the end of ListView.<br>
-- param item A item in `Widget*`.
-- @function [parent=#ListView] pushBackCustomItem 
-- @param self
-- @param #ccui.Widget item
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- Insert a default item(create by cloning model) into listview at a give index.<br>
-- param index  A index in ssize_t.
-- @function [parent=#ListView] insertDefaultItem 
-- @param self
-- @param #long index
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- Set magnetic allowed out of boundary.
-- @function [parent=#ListView] setMagneticAllowedOutOfBoundary 
-- @param self
-- @param #bool magneticAllowedOutOfBoundary
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- Add a event click callback to ListView, then one item of Listview is clicked, the callback will be called.<br>
-- param callback A callback function with type of `ccListViewCallback`.
-- @function [parent=#ListView] addEventListener 
-- @param self
-- @param #function callback
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- 
-- @function [parent=#ListView] doLayout 
-- @param self
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- brief Query the topmost item in horizontal list<br>
-- return A item instance.
-- @function [parent=#ListView] getTopmostItemInCurrentView 
-- @param self
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- brief Remove all items in current ListView.
-- @function [parent=#ListView] removeAllItems 
-- @param self
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- brief Query the bottommost item in horizontal list<br>
-- return A item instance.
-- @function [parent=#ListView] getBottommostItemInCurrentView 
-- @param self
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- Return all items in a ListView.<br>
-- returns A vector of widget pointers.
-- @function [parent=#ListView] getItems 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- brief Query the leftmost item in horizontal list<br>
-- return A item instance.
-- @function [parent=#ListView] getLeftmostItemInCurrentView 
-- @param self
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- Set the margin between each item in ListView.<br>
-- param margin
-- @function [parent=#ListView] setItemsMargin 
-- @param self
-- @param #float margin
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- Get magnetic type of ListView.
-- @function [parent=#ListView] getMagneticType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Return a item at a given index.<br>
-- param index A given index in ssize_t.<br>
-- return A widget instance.
-- @function [parent=#ListView] getItem 
-- @param self
-- @param #long index
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- Remove a item at given index.<br>
-- param index A given index in ssize_t.
-- @function [parent=#ListView] removeItem 
-- @param self
-- @param #long index
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- @overload self, long, vec2_table, vec2_table, float         
-- @overload self, long, vec2_table, vec2_table         
-- @function [parent=#ListView] scrollToItem
-- @param self
-- @param #long itemIndex
-- @param #vec2_table positionRatioInView
-- @param #vec2_table itemAnchorPoint
-- @param #float timeInSec
-- @return ListView#ListView self (return value: ccui.ListView)

--------------------------------
-- Insert a default item(create by a cloned model) at the end of the listview.
-- @function [parent=#ListView] pushBackDefaultItem 
-- @param self
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- Query whether the magnetic out of boundary is allowed.
-- @function [parent=#ListView] getMagneticAllowedOutOfBoundary 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief Query the closest item to a specific position in inner container.<br>
-- param targetPosition Specifies the target position in inner container's coordinates.<br>
-- param itemAnchorPoint Specifies an anchor point of each item for position to calculate distance.<br>
-- return A item instance if list view is not empty. Otherwise, returns null.
-- @function [parent=#ListView] getClosestItemToPosition 
-- @param self
-- @param #vec2_table targetPosition
-- @param #vec2_table itemAnchorPoint
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- brief Query the rightmost item in horizontal list<br>
-- return A item instance.
-- @function [parent=#ListView] getRightmostItemInCurrentView 
-- @param self
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- brief Query the closest item to a specific position in current view.<br>
-- For instance, to find the item in the center of view, call 'getClosestItemToPositionInCurrentView(Vec2::ANCHOR_MIDDLE, Vec2::ANCHOR_MIDDLE)'.<br>
-- param positionRatioInView Specifies the target position with ratio in list view's content size.<br>
-- param itemAnchorPoint Specifies an anchor point of each item for position to calculate distance.<br>
-- return A item instance if list view is not empty. Otherwise, returns null.
-- @function [parent=#ListView] getClosestItemToPositionInCurrentView 
-- @param self
-- @param #vec2_table positionRatioInView
-- @param #vec2_table itemAnchorPoint
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- Set a item model for listview.<br>
-- When calling `pushBackDefaultItem`, the model will be used as a blueprint and new model copy will be inserted into ListView.<br>
-- param model  Model in `Widget*`.
-- @function [parent=#ListView] setItemModel 
-- @param self
-- @param #ccui.Widget model
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- brief Insert a custom widget into ListView at a given index.<br>
-- param item A widget pointer to be inserted.<br>
-- param index A given index in ssize_t.
-- @function [parent=#ListView] insertCustomItem 
-- @param self
-- @param #ccui.Widget item
-- @param #long index
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- Create an empty ListView.<br>
-- return A ListView instance.
-- @function [parent=#ListView] create 
-- @param self
-- @return ListView#ListView ret (return value: ccui.ListView)
        
--------------------------------
-- 
-- @function [parent=#ListView] createInstance 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- @overload self, cc.Node, int         
-- @overload self, cc.Node         
-- @overload self, cc.Node, int, int         
-- @overload self, cc.Node, int, string         
-- @function [parent=#ListView] addChild
-- @param self
-- @param #cc.Node child
-- @param #int zOrder
-- @param #string name
-- @return ListView#ListView self (return value: ccui.ListView)

--------------------------------
-- Override functions
-- @function [parent=#ListView] jumpToBottom 
-- @param self
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- 
-- @function [parent=#ListView] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Changes scroll direction of scrollview.<br>
-- Direction Direction::VERTICAL means vertical scroll, Direction::HORIZONTAL means horizontal scroll.<br>
-- param dir Set the list view's scroll direction.
-- @function [parent=#ListView] setDirection 
-- @param self
-- @param #int dir
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- 
-- @function [parent=#ListView] jumpToTopRight 
-- @param self
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- 
-- @function [parent=#ListView] jumpToLeft 
-- @param self
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- 
-- @function [parent=#ListView] removeAllChildrenWithCleanup 
-- @param self
-- @param #bool cleanup
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- 
-- @function [parent=#ListView] requestDoLayout 
-- @param self
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- 
-- @function [parent=#ListView] removeAllChildren 
-- @param self
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- 
-- @function [parent=#ListView] jumpToTopLeft 
-- @param self
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- 
-- @function [parent=#ListView] removeChild 
-- @param self
-- @param #cc.Node child
-- @param #bool cleaup
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- 
-- @function [parent=#ListView] jumpToBottomRight 
-- @param self
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- 
-- @function [parent=#ListView] jumpToTop 
-- @param self
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- 
-- @function [parent=#ListView] jumpToBottomLeft 
-- @param self
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- 
-- @function [parent=#ListView] jumpToPercentBothDirection 
-- @param self
-- @param #vec2_table percent
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- 
-- @function [parent=#ListView] jumpToPercentHorizontal 
-- @param self
-- @param #float percent
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- 
-- @function [parent=#ListView] jumpToRight 
-- @param self
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- 
-- @function [parent=#ListView] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#ListView] jumpToPercentVertical 
-- @param self
-- @param #float percent
-- @return ListView#ListView self (return value: ccui.ListView)
        
--------------------------------
-- Default constructor<br>
-- js ctor<br>
-- lua new
-- @function [parent=#ListView] ListView 
-- @param self
-- @return ListView#ListView self (return value: ccui.ListView)
        
return nil
