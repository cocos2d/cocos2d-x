
--------------------------------
-- @module LoadingBar
-- @extend Widget
-- @parent_module ccui

--------------------------------
-- Changes the progress value of LoadingBar.<br>
-- param percent   Percent value from 1 to 100.
-- @function [parent=#LoadingBar] setPercent 
-- @param self
-- @param #float percent
-- @return LoadingBar#LoadingBar self (return value: ccui.LoadingBar)
        
--------------------------------
-- Load texture for LoadingBar.<br>
-- param texture   File name of texture.<br>
-- param texType   Texture resource type,@see TextureResType.
-- @function [parent=#LoadingBar] loadTexture 
-- @param self
-- @param #string texture
-- @param #int texType
-- @return LoadingBar#LoadingBar self (return value: ccui.LoadingBar)
        
--------------------------------
-- Change the progress direction of LoadingBar.<br>
-- see Direction  `LEFT` means progress left to right, `RIGHT` otherwise.<br>
-- param direction Direction
-- @function [parent=#LoadingBar] setDirection 
-- @param self
-- @param #int direction
-- @return LoadingBar#LoadingBar self (return value: ccui.LoadingBar)
        
--------------------------------
-- 
-- @function [parent=#LoadingBar] getRenderFile 
-- @param self
-- @return ResourceData#ResourceData ret (return value: cc.ResourceData)
        
--------------------------------
-- Enable scale9 renderer.<br>
-- param enabled Set to true will use scale9 renderer, false otherwise.
-- @function [parent=#LoadingBar] setScale9Enabled 
-- @param self
-- @param #bool enabled
-- @return LoadingBar#LoadingBar self (return value: ccui.LoadingBar)
        
--------------------------------
-- Set capInsets for LoadingBar.<br>
-- This setting only take effect when enable scale9 renderer.<br>
-- param capInsets CapInset in `Rect`.
-- @function [parent=#LoadingBar] setCapInsets 
-- @param self
-- @param #rect_table capInsets
-- @return LoadingBar#LoadingBar self (return value: ccui.LoadingBar)
        
--------------------------------
-- Get the progress direction of LoadingBar.<br>
-- see Direction  `LEFT` means progress left to right, `RIGHT` otherwise.<br>
-- return LoadingBar progress direction.
-- @function [parent=#LoadingBar] getDirection 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- brief Query LoadingBar's capInsets.<br>
-- return CapInsets of LoadingBar.
-- @function [parent=#LoadingBar] getCapInsets 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- brief Query whether LoadingBar is using scale9 renderer or not.<br>
-- return Whether LoadingBar uses scale9 renderer or not.
-- @function [parent=#LoadingBar] isScale9Enabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Get the progress value of LoadingBar.<br>
-- return Progress value from 1 to 100.
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
-- 
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
-- @return LoadingBar#LoadingBar self (return value: ccui.LoadingBar)
        
--------------------------------
-- Default constructor.<br>
-- js ctor<br>
-- lua new
-- @function [parent=#LoadingBar] LoadingBar 
-- @param self
-- @return LoadingBar#LoadingBar self (return value: ccui.LoadingBar)
        
return nil
