
--------------------------------
-- @module TableView
-- @extend ScrollView,ScrollViewDelegate
-- @parent_module cc

--------------------------------
-- Updates the content of the cell at a given index.<br>
-- param idx index to find a cell
-- @function [parent=#TableView] updateCellAtIndex 
-- @param self
-- @param #long idx
        
--------------------------------
-- determines how cell is ordered and filled in the view.
-- @function [parent=#TableView] setVerticalFillOrder 
-- @param self
-- @param #int order
        
--------------------------------
-- 
-- @function [parent=#TableView] scrollViewDidZoom 
-- @param self
-- @param #cc.ScrollView view
        
--------------------------------
-- 
-- @function [parent=#TableView] _updateContentSize 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#TableView] getVerticalFillOrder 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Removes a cell at a given index<br>
-- param idx index to find a cell
-- @function [parent=#TableView] removeCellAtIndex 
-- @param self
-- @param #long idx
        
--------------------------------
-- 
-- @function [parent=#TableView] initWithViewSize 
-- @param self
-- @param #size_table size
-- @param #cc.Node container
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#TableView] scrollViewDidScroll 
-- @param self
-- @param #cc.ScrollView view
        
--------------------------------
-- reloads data from data source.  the view will be refreshed.
-- @function [parent=#TableView] reloadData 
-- @param self
        
--------------------------------
-- Inserts a new cell at a given index<br>
-- param idx location to insert
-- @function [parent=#TableView] insertCellAtIndex 
-- @param self
-- @param #long idx
        
--------------------------------
-- Returns an existing cell at a given index. Returns nil if a cell is nonexistent at the moment of query.<br>
-- param idx index<br>
-- return a cell at a given index
-- @function [parent=#TableView] cellAtIndex 
-- @param self
-- @param #long idx
-- @return TableViewCell#TableViewCell ret (return value: cc.TableViewCell)
        
--------------------------------
-- Dequeues a free cell if available. nil if not.<br>
-- return free cell
-- @function [parent=#TableView] dequeueCell 
-- @param self
-- @return TableViewCell#TableViewCell ret (return value: cc.TableViewCell)
        
--------------------------------
-- 
-- @function [parent=#TableView] onTouchMoved 
-- @param self
-- @param #cc.Touch pTouch
-- @param #cc.Event pEvent
        
--------------------------------
-- 
-- @function [parent=#TableView] onTouchEnded 
-- @param self
-- @param #cc.Touch pTouch
-- @param #cc.Event pEvent
        
--------------------------------
-- 
-- @function [parent=#TableView] onTouchCancelled 
-- @param self
-- @param #cc.Touch pTouch
-- @param #cc.Event pEvent
        
--------------------------------
-- 
-- @function [parent=#TableView] onTouchBegan 
-- @param self
-- @param #cc.Touch pTouch
-- @param #cc.Event pEvent
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- js ctor
-- @function [parent=#TableView] TableView 
-- @param self
        
return nil
