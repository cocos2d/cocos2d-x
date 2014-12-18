
--------------------------------
-- @module LoadingBar
-- @extend Widget
-- @parent_module ccui

--------------------------------
-- Changes the progress direction of loadingbar.<br>
-- param percent    percent value from 1 to 100.
-- @function [parent=#LoadingBar] setPercent 
-- @param self
-- @param #float percent
        
--------------------------------
-- Load texture for loadingbar.<br>
-- param texture   file name of texture.<br>
-- param texType    @see TextureResType
-- @function [parent=#LoadingBar] loadTexture 
-- @param self
-- @param #string texture
-- @param #int texType
        
--------------------------------
-- Changes the progress direction of loadingbar.<br>
-- see Direction  LEFT means progress left to right, RIGHT otherwise.<br>
-- param direction Direction
-- @function [parent=#LoadingBar] setDirection 
-- @param self
-- @param #int direction
        
--------------------------------
-- Sets if loadingbar is using scale9 renderer.<br>
-- param enabled true that using scale9 renderer, false otherwise.
-- @function [parent=#LoadingBar] setScale9Enabled 
-- @param self
-- @param #bool enabled
        
--------------------------------
-- Sets capinsets for loadingbar, if loadingbar is using scale9 renderer.<br>
-- param capInsets    capinsets for loadingbar
-- @function [parent=#LoadingBar] setCapInsets 
-- @param self
-- @param #rect_table capInsets
        
--------------------------------
-- Gets the progress direction of loadingbar.<br>
-- see Direction  LEFT means progress left to right, RIGHT otherwise.<br>
-- return Direction
-- @function [parent=#LoadingBar] getDirection 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#LoadingBar] getCapInsets 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- 
-- @function [parent=#LoadingBar] isScale9Enabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Gets the progress direction of loadingbar.<br>
-- return percent value from 1 to 100.
-- @function [parent=#LoadingBar] getPercent 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @overload self, string, float         
-- @overload self         
-- @overload self, string, int, float         
-- @function [parent=#LoadingBar] create
-- @param self
-- @param #string textureName
-- @param #int texType
-- @param #float percentage
-- @return LoadingBar#LoadingBar ret (return value: ccui.LoadingBar)

--------------------------------
-- 
-- @function [parent=#LoadingBar] createInstance 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- 
-- @function [parent=#LoadingBar] getVirtualRenderer 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- Returns the "class name" of widget.
-- @function [parent=#LoadingBar] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LoadingBar] getVirtualRendererSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- 
-- @function [parent=#LoadingBar] ignoreContentAdaptWithSize 
-- @param self
-- @param #bool ignore
        
--------------------------------
-- Default constructor
-- @function [parent=#LoadingBar] LoadingBar 
-- @param self
        
return nil
