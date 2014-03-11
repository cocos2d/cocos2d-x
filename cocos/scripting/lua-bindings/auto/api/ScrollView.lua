
--------------------------------
-- @module ScrollView
--------------------------------
-- @function [parent=#ScrollView] isClippingToBounds 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ScrollView] setContainer 
-- @param self
-- @param #cc.Node node
        
--------------------------------
-- @function [parent=#ScrollView] onTouchEnded 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
        
--------------------------------
-- @function [parent=#ScrollView] setContentOffsetInDuration 
-- @param self
-- @param #point_table point
-- @param #float float
        
--------------------------------
-- @function [parent=#ScrollView] setZoomScaleInDuration 
-- @param self
-- @param #float float
-- @param #float float
        
--------------------------------
-- @function [parent=#ScrollView] setBounceable 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ScrollView] getDirection 
-- @param self
-- @return ScrollView::Direction#ScrollView::Direction ret (return value: cc.ScrollView::Direction)
        
--------------------------------
-- @function [parent=#ScrollView] getContainer 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- @function [parent=#ScrollView] updateTweenAction 
-- @param self
-- @param #float float
-- @param #string str
        
--------------------------------
-- @function [parent=#ScrollView] getZoomScale 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#ScrollView] updateInset 
-- @param self
        
--------------------------------
-- @function [parent=#ScrollView] initWithViewSize 
-- @param self
-- @param #size_table size
-- @param #cc.Node node
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ScrollView] pause 
-- @param self
-- @param #cc.Ref ref
        
--------------------------------
-- @function [parent=#ScrollView] setDirection 
-- @param self
-- @param #cc.ScrollView::Direction direction
        
--------------------------------
-- @function [parent=#ScrollView] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ScrollView] setContentOffset 
-- @param self
-- @param #point_table point
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ScrollView] isDragging 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ScrollView] isTouchEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ScrollView] isBounceable 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ScrollView] setTouchEnabled 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ScrollView] onTouchMoved 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
        
--------------------------------
-- @function [parent=#ScrollView] getContentOffset 
-- @param self
-- @return point_table#point_table ret (return value: point_table)
        
--------------------------------
-- @function [parent=#ScrollView] resume 
-- @param self
-- @param #cc.Ref ref
        
--------------------------------
-- @function [parent=#ScrollView] setClippingToBounds 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ScrollView] setViewSize 
-- @param self
-- @param #size_table size
        
--------------------------------
-- @function [parent=#ScrollView] onTouchCancelled 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
        
--------------------------------
-- @function [parent=#ScrollView] getViewSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#ScrollView] maxContainerOffset 
-- @param self
-- @return point_table#point_table ret (return value: point_table)
        
--------------------------------
-- @function [parent=#ScrollView] onTouchBegan 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ScrollView] isTouchMoved 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ScrollView] isNodeVisible 
-- @param self
-- @param #cc.Node node
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ScrollView] minContainerOffset 
-- @param self
-- @return point_table#point_table ret (return value: point_table)
        
--------------------------------
-- overload function: setZoomScale(float, bool)
--          
-- overload function: setZoomScale(float)
--          
-- @function [parent=#ScrollView] setZoomScale
-- @param self
-- @param #float float
-- @param #bool bool

--------------------------------
-- overload function: create()
--          
-- overload function: create(size_table, cc.Node)
--          
-- @function [parent=#ScrollView] create
-- @param self
-- @param #size_table size
-- @param #cc.Node node
-- @return ScrollView#ScrollView ret (retunr value: cc.ScrollView)

--------------------------------
-- @function [parent=#ScrollView] ScrollView 
-- @param self
        
return nil
