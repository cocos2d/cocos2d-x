
--------------------------------
-- @module LoadingBar
-- @extend Widget
-- @parent_module ccui

--------------------------------
-- @function [parent=#LoadingBar] setPercent 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#LoadingBar] loadTexture 
-- @param self
-- @param #string str
-- @param #int texturerestype
        
--------------------------------
-- @function [parent=#LoadingBar] setDirection 
-- @param self
-- @param #int direction
        
--------------------------------
-- @function [parent=#LoadingBar] setScale9Enabled 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#LoadingBar] setCapInsets 
-- @param self
-- @param #rect_table rect
        
--------------------------------
-- @function [parent=#LoadingBar] getDirection 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#LoadingBar] getCapInsets 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- @function [parent=#LoadingBar] isScale9Enabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#LoadingBar] getPercent 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @overload self, string, float         
-- @overload self         
-- @function [parent=#LoadingBar] create
-- @param self
-- @param #string str
-- @param #float float
-- @return LoadingBar#LoadingBar ret (retunr value: ccui.LoadingBar)

--------------------------------
-- @function [parent=#LoadingBar] createInstance 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- @function [parent=#LoadingBar] getVirtualRenderer 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- @function [parent=#LoadingBar] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @function [parent=#LoadingBar] getVirtualRendererSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- @function [parent=#LoadingBar] ignoreContentAdaptWithSize 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#LoadingBar] LoadingBar 
-- @param self
        
return nil
