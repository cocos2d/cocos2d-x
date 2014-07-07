
--------------------------------
-- @module ListView
-- @extend ScrollView
-- @parent_module ccui

--------------------------------
-- @function [parent=#ListView] getIndex 
-- @param self
-- @param #ccui.Widget widget
-- @return long#long ret (return value: long)
        
--------------------------------
-- @function [parent=#ListView] removeAllItems 
-- @param self
        
--------------------------------
-- @function [parent=#ListView] setGravity 
-- @param self
-- @param #ccui.ListView::Gravity gravity
        
--------------------------------
-- @function [parent=#ListView] pushBackCustomItem 
-- @param self
-- @param #ccui.Widget widget
        
--------------------------------
-- @function [parent=#ListView] getItems 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- @function [parent=#ListView] removeItem 
-- @param self
-- @param #long long
        
--------------------------------
-- @function [parent=#ListView] getCurSelectedIndex 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- @function [parent=#ListView] insertDefaultItem 
-- @param self
-- @param #long long
        
--------------------------------
-- @function [parent=#ListView] requestRefreshView 
-- @param self
        
--------------------------------
-- @function [parent=#ListView] setItemsMargin 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#ListView] refreshView 
-- @param self
        
--------------------------------
-- @function [parent=#ListView] removeLastItem 
-- @param self
        
--------------------------------
-- @function [parent=#ListView] getItemsMargin 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#ListView] addEventListener 
-- @param self
-- @param #function func
        
--------------------------------
-- @function [parent=#ListView] getItem 
-- @param self
-- @param #long long
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- @function [parent=#ListView] setItemModel 
-- @param self
-- @param #ccui.Widget widget
        
--------------------------------
-- @function [parent=#ListView] doLayout 
-- @param self
        
--------------------------------
-- @function [parent=#ListView] pushBackDefaultItem 
-- @param self
        
--------------------------------
-- @function [parent=#ListView] insertCustomItem 
-- @param self
-- @param #ccui.Widget widget
-- @param #long long
        
--------------------------------
-- @function [parent=#ListView] create 
-- @param self
-- @return ListView#ListView ret (return value: ccui.ListView)
        
--------------------------------
-- @function [parent=#ListView] createInstance 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- overload function: addChild(cc.Node, int)
--          
-- overload function: addChild(cc.Node)
--          
-- overload function: addChild(cc.Node, int, int)
--          
-- overload function: addChild(cc.Node, int, string)
--          
-- @function [parent=#ListView] addChild
-- @param self
-- @param #cc.Node node
-- @param #int int
-- @param #string str

--------------------------------
-- @function [parent=#ListView] setDirection 
-- @param self
-- @param #ccui.ScrollView::Direction direction
        
--------------------------------
-- @function [parent=#ListView] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#ListView] removeAllChildrenWithCleanup 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ListView] removeAllChildren 
-- @param self
        
--------------------------------
-- @function [parent=#ListView] removeChild 
-- @param self
-- @param #cc.Node node
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ListView] ListView 
-- @param self
        
return nil
