
--------------------------------
-- @module ScrollView
-- @extend Layer,ActionTweenDelegate
-- @parent_module cc

--------------------------------
-- Determines whether it clips its children or not.
-- @function [parent=#ScrollView] isClippingToBounds 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] setContainer 
-- @param self
-- @param #cc.Node pContainer
-- @return ScrollView#ScrollView self (return value: cc.ScrollView)
        
--------------------------------
-- Sets a new content offset. It ignores max/min offset. It just sets what's given. (just like UIKit's UIScrollView)<br>
-- You can override the animation duration with this method.<br>
-- param offset    The new offset.<br>
-- param dt        The animation duration.
-- @function [parent=#ScrollView] setContentOffsetInDuration 
-- @param self
-- @param #vec2_table offset
-- @param #float dt
-- @return ScrollView#ScrollView self (return value: cc.ScrollView)
        
--------------------------------
-- Sets a new scale for container in a given duration.<br>
-- param s     The new scale value<br>
-- param dt    The animation duration
-- @function [parent=#ScrollView] setZoomScaleInDuration 
-- @param self
-- @param #float s
-- @param #float dt
-- @return ScrollView#ScrollView self (return value: cc.ScrollView)
        
--------------------------------
-- CCActionTweenDelegate
-- @function [parent=#ScrollView] updateTweenAction 
-- @param self
-- @param #float value
-- @param #string key
-- @return ScrollView#ScrollView self (return value: cc.ScrollView)
        
--------------------------------
-- Set max scale<br>
-- param maxScale max scale
-- @function [parent=#ScrollView] setMaxScale 
-- @param self
-- @param #float maxScale
-- @return ScrollView#ScrollView self (return value: cc.ScrollView)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] hasVisibleParents 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- direction allowed to scroll. ScrollViewDirectionBoth by default.
-- @function [parent=#ScrollView] getDirection 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] getContainer 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- Set min scale<br>
-- param minScale min scale
-- @function [parent=#ScrollView] setMinScale 
-- @param self
-- @param #float minScale
-- @return ScrollView#ScrollView self (return value: cc.ScrollView)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] getZoomScale 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] updateInset 
-- @param self
-- @return ScrollView#ScrollView self (return value: cc.ScrollView)
        
--------------------------------
-- Returns a scroll view object<br>
-- param size view size<br>
-- param container parent object<br>
-- return scroll view object
-- @function [parent=#ScrollView] initWithViewSize 
-- @param self
-- @param #size_table size
-- @param #cc.Node container
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] pause 
-- @param self
-- @param #cc.Ref sender
-- @return ScrollView#ScrollView self (return value: cc.ScrollView)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] setDirection 
-- @param self
-- @param #int eDirection
-- @return ScrollView#ScrollView self (return value: cc.ScrollView)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] setBounceable 
-- @param self
-- @param #bool bBounceable
-- @return ScrollView#ScrollView self (return value: cc.ScrollView)
        
--------------------------------
-- Sets a new content offset. It ignores max/min offset. It just sets what's given. (just like UIKit's UIScrollView)<br>
-- param offset    The new offset.<br>
-- param animated  If true, the view will scroll to the new offset.
-- @function [parent=#ScrollView] setContentOffset 
-- @param self
-- @param #vec2_table offset
-- @param #bool animated
-- @return ScrollView#ScrollView self (return value: cc.ScrollView)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] isDragging 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] isTouchEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] isBounceable 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] setTouchEnabled 
-- @param self
-- @param #bool enabled
-- @return ScrollView#ScrollView self (return value: cc.ScrollView)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] getContentOffset 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] resume 
-- @param self
-- @param #cc.Ref sender
-- @return ScrollView#ScrollView self (return value: cc.ScrollView)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] setClippingToBounds 
-- @param self
-- @param #bool bClippingToBounds
-- @return ScrollView#ScrollView self (return value: cc.ScrollView)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] setViewSize 
-- @param self
-- @param #size_table size
-- @return ScrollView#ScrollView self (return value: cc.ScrollView)
        
--------------------------------
-- size to clip. Node boundingBox uses contentSize directly.<br>
-- It's semantically different what it actually means to common scroll views.<br>
-- Hence, this scroll view will use a separate size property.
-- @function [parent=#ScrollView] getViewSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- Returns the current container's maximum offset. You may want this while you animate scrolling by yourself
-- @function [parent=#ScrollView] maxContainerOffset 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] isTouchMoved 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Determines if a given node's bounding box is in visible bounds<br>
-- returns true if it is in visible bounds
-- @function [parent=#ScrollView] isNodeVisible 
-- @param self
-- @param #cc.Node node
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Returns the current container's minimum offset. You may want this while you animate scrolling by yourself
-- @function [parent=#ScrollView] minContainerOffset 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @overload self, float, bool         
-- @overload self, float         
-- @function [parent=#ScrollView] setZoomScale
-- @param self
-- @param #float s
-- @param #bool animated
-- @return ScrollView#ScrollView self (return value: cc.ScrollView)

--------------------------------
-- @overload self         
-- @overload self, size_table, cc.Node         
-- @function [parent=#ScrollView] create
-- @param self
-- @param #size_table size
-- @param #cc.Node container
-- @return ScrollView#ScrollView ret (return value: cc.ScrollView)

--------------------------------
-- 
-- @function [parent=#ScrollView] onTouchMoved 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
-- @return ScrollView#ScrollView self (return value: cc.ScrollView)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] onTouchEnded 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
-- @return ScrollView#ScrollView self (return value: cc.ScrollView)
        
--------------------------------
-- @overload self, cc.Node, int, string         
-- @overload self, cc.Node, int, int         
-- @function [parent=#ScrollView] addChild
-- @param self
-- @param #cc.Node child
-- @param #int zOrder
-- @param #int tag
-- @return ScrollView#ScrollView self (return value: cc.ScrollView)

--------------------------------
-- 
-- @function [parent=#ScrollView] removeAllChildrenWithCleanup 
-- @param self
-- @param #bool cleanup
-- @return ScrollView#ScrollView self (return value: cc.ScrollView)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] onTouchCancelled 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
-- @return ScrollView#ScrollView self (return value: cc.ScrollView)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] onTouchBegan 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] removeAllChildren 
-- @param self
-- @return ScrollView#ScrollView self (return value: cc.ScrollView)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] removeChild 
-- @param self
-- @param #cc.Node child
-- @param #bool cleaup
-- @return ScrollView#ScrollView self (return value: cc.ScrollView)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] getContentSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- 
-- @function [parent=#ScrollView] setContentSize 
-- @param self
-- @param #size_table size
-- @return ScrollView#ScrollView self (return value: cc.ScrollView)
        
--------------------------------
-- js ctor<br>
-- lua new
-- @function [parent=#ScrollView] ScrollView 
-- @param self
-- @return ScrollView#ScrollView self (return value: cc.ScrollView)
        
return nil
