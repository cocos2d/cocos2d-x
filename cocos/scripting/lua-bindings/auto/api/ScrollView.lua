
--------------------------------
-- @module ScrollView
-- @extend Layout,UIScrollInterface

--------------------------------
-- @function [parent=#ScrollView] scrollToTop 
-- @param self
-- @param #float float
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ScrollView] scrollToPercentHorizontal 
-- @param self
-- @param #float float
-- @param #float float
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ScrollView] isInertiaScrollEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ScrollView] scrollToPercentBothDirection 
-- @param self
-- @param #point_table point
-- @param #float float
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ScrollView] getDirection 
-- @param self
-- @return SCROLLVIEW_DIR#SCROLLVIEW_DIR ret (return value: ccui.SCROLLVIEW_DIR)
        
--------------------------------
-- @function [parent=#ScrollView] scrollToBottomLeft 
-- @param self
-- @param #float float
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ScrollView] getInnerContainer 
-- @param self
-- @return Layout#Layout ret (return value: ccui.Layout)
        
--------------------------------
-- @function [parent=#ScrollView] jumpToBottom 
-- @param self
        
--------------------------------
-- @function [parent=#ScrollView] setDirection 
-- @param self
-- @param #ccui.SCROLLVIEW_DIR scrollview_dir
        
--------------------------------
-- @function [parent=#ScrollView] scrollToTopLeft 
-- @param self
-- @param #float float
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ScrollView] jumpToTopRight 
-- @param self
        
--------------------------------
-- @function [parent=#ScrollView] jumpToBottomLeft 
-- @param self
        
--------------------------------
-- @function [parent=#ScrollView] setInnerContainerSize 
-- @param self
-- @param #size_table size
        
--------------------------------
-- @function [parent=#ScrollView] getInnerContainerSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#ScrollView] isBounceEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ScrollView] jumpToPercentVertical 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#ScrollView] setInertiaScrollEnabled 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ScrollView] jumpToTopLeft 
-- @param self
        
--------------------------------
-- @function [parent=#ScrollView] jumpToPercentHorizontal 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#ScrollView] jumpToBottomRight 
-- @param self
        
--------------------------------
-- @function [parent=#ScrollView] setBounceEnabled 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ScrollView] jumpToTop 
-- @param self
        
--------------------------------
-- @function [parent=#ScrollView] scrollToLeft 
-- @param self
-- @param #float float
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ScrollView] jumpToPercentBothDirection 
-- @param self
-- @param #point_table point
        
--------------------------------
-- @function [parent=#ScrollView] scrollToPercentVertical 
-- @param self
-- @param #float float
-- @param #float float
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ScrollView] scrollToBottom 
-- @param self
-- @param #float float
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ScrollView] scrollToBottomRight 
-- @param self
-- @param #float float
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ScrollView] jumpToLeft 
-- @param self
        
--------------------------------
-- @function [parent=#ScrollView] scrollToRight 
-- @param self
-- @param #float float
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ScrollView] jumpToRight 
-- @param self
        
--------------------------------
-- @function [parent=#ScrollView] scrollToTopRight 
-- @param self
-- @param #float float
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ScrollView] create 
-- @param self
-- @return ScrollView#ScrollView ret (return value: ccui.ScrollView)
        
--------------------------------
-- @function [parent=#ScrollView] createInstance 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- overload function: addChild(cc.Node, int)
--          
-- overload function: addChild(cc.Node)
--          
-- overload function: addChild(cc.Node, int, int)
--          
-- @function [parent=#ScrollView] addChild
-- @param self
-- @param #cc.Node node
-- @param #int int
-- @param #int int

--------------------------------
-- @function [parent=#ScrollView] getChildByName 
-- @param self
-- @param #char char
-- @return Widget#Widget ret (return value: ccui.Widget)
        
--------------------------------
-- @function [parent=#ScrollView] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#ScrollView] update 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#ScrollView] getLayoutType 
-- @param self
-- @return LayoutType#LayoutType ret (return value: ccui.LayoutType)
        
--------------------------------
-- @function [parent=#ScrollView] removeAllChildrenWithCleanup 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ScrollView] removeAllChildren 
-- @param self
        
--------------------------------
-- @function [parent=#ScrollView] removeChild 
-- @param self
-- @param #cc.Node node
-- @param #bool bool
        
--------------------------------
-- overload function: getChildren()
--          
-- overload function: getChildren()
--          
-- @function [parent=#ScrollView] getChildren
-- @param self
-- @return array_table#array_table ret (retunr value: array_table)

--------------------------------
-- @function [parent=#ScrollView] getChildByTag 
-- @param self
-- @param #int int
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- @function [parent=#ScrollView] getChildrenCount 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- @function [parent=#ScrollView] setLayoutType 
-- @param self
-- @param #ccui.LayoutType layouttype
        
--------------------------------
-- @function [parent=#ScrollView] ScrollView 
-- @param self
        
return nil
