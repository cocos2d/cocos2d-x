
--------------------------------
-- @module CheckBox
-- @extend Widget
-- @parent_module ccui

--------------------------------
-- Load background selected state texture for checkbox.<br>
-- param backGroundSelected    The background selected state image name.<br>
-- param texType    @see `Widget::TextureResType`
-- @function [parent=#CheckBox] loadTextureBackGroundSelected 
-- @param self
-- @param #string backGroundSelected
-- @param #int texType
-- @return CheckBox#CheckBox self (return value: ccui.CheckBox)
        
--------------------------------
-- Load background disabled state texture for checkbox.<br>
-- param backGroundDisabled    The background disabled state texture name.<br>
-- param texType    @see `Widget::TextureResType`
-- @function [parent=#CheckBox] loadTextureBackGroundDisabled 
-- @param self
-- @param #string backGroundDisabled
-- @param #int texType
-- @return CheckBox#CheckBox self (return value: ccui.CheckBox)
        
--------------------------------
-- Change CheckBox state.<br>
-- Set to true will cause the CheckBox's state to "selected", false otherwise.<br>
-- param selected Set to true will change CheckBox to selected state, false otherwise.
-- @function [parent=#CheckBox] setSelected 
-- @param self
-- @param #bool selected
-- @return CheckBox#CheckBox self (return value: ccui.CheckBox)
        
--------------------------------
-- Add a callback function which would be called when checkbox is selected or unselected.<br>
-- param callback A std::function with type @see `ccCheckBoxCallback`
-- @function [parent=#CheckBox] addEventListener 
-- @param self
-- @param #function callback
-- @return CheckBox#CheckBox self (return value: ccui.CheckBox)
        
--------------------------------
-- Load cross texture for checkbox.<br>
-- param crossTextureName    The cross texture name.<br>
-- param texType    @see `Widget::TextureResType`
-- @function [parent=#CheckBox] loadTextureFrontCross 
-- @param self
-- @param #string crossTextureName
-- @param #int texType
-- @return CheckBox#CheckBox self (return value: ccui.CheckBox)
        
--------------------------------
-- Query whether CheckBox is selected or not.<br>
-- return true means "selected", false otherwise.
-- @function [parent=#CheckBox] isSelected 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#CheckBox] init 
-- @param self
-- @param #string backGround
-- @param #string backGroundSeleted
-- @param #string cross
-- @param #string backGroundDisabled
-- @param #string frontCrossDisabled
-- @param #int texType
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Load all textures for initializing a checkbox.<br>
-- param background    The background image name.<br>
-- param backgroundSelected    The background selected image name.<br>
-- param cross    The cross image name.<br>
-- param backgroundDisabled    The background disabled state texture.<br>
-- param frontCrossDisabled    The front cross disabled state image name.<br>
-- param texType    @see `Widget::TextureResType`
-- @function [parent=#CheckBox] loadTextures 
-- @param self
-- @param #string background
-- @param #string backgroundSelected
-- @param #string cross
-- @param #string backgroundDisabled
-- @param #string frontCrossDisabled
-- @param #int texType
-- @return CheckBox#CheckBox self (return value: ccui.CheckBox)
        
--------------------------------
-- brief Return a zoom scale<br>
-- return A zoom scale of Checkbox.<br>
-- since v3.3
-- @function [parent=#CheckBox] getZoomScale 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Load background texture for checkbox.<br>
-- param backGround   The background image name.<br>
-- param type    @see `Widget::TextureResType`
-- @function [parent=#CheckBox] loadTextureBackGround 
-- @param self
-- @param #string backGround
-- @param #int type
-- @return CheckBox#CheckBox self (return value: ccui.CheckBox)
        
--------------------------------
--  When user pressed the CheckBox, the button will zoom to a scale.<br>
-- The final scale of the CheckBox  equals (CheckBox original scale + _zoomScale)<br>
-- since v3.3
-- @function [parent=#CheckBox] setZoomScale 
-- @param self
-- @param #float scale
-- @return CheckBox#CheckBox self (return value: ccui.CheckBox)
        
--------------------------------
-- Load frontcross disabled texture for checkbox.<br>
-- param frontCrossDisabled    The front cross disabled state texture name.<br>
-- param texType    @see `Widget::TextureResType`
-- @function [parent=#CheckBox] loadTextureFrontCrossDisabled 
-- @param self
-- @param #string frontCrossDisabled
-- @param #int texType
-- @return CheckBox#CheckBox self (return value: ccui.CheckBox)
        
--------------------------------
-- @overload self, string, string, string, string, string, int         
-- @overload self         
-- @overload self, string, string, int         
-- @function [parent=#CheckBox] create
-- @param self
-- @param #string backGround
-- @param #string backGroundSelected
-- @param #string cross
-- @param #string backGroundDisabled
-- @param #string frontCrossDisabled
-- @param #int texType
-- @return CheckBox#CheckBox ret (return value: ccui.CheckBox)

--------------------------------
-- 
-- @function [parent=#CheckBox] createInstance 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- 
-- @function [parent=#CheckBox] getVirtualRenderer 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#CheckBox] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#CheckBox] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#CheckBox] getVirtualRendererSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- Default constructor.<br>
-- lua new
-- @function [parent=#CheckBox] CheckBox 
-- @param self
-- @return CheckBox#CheckBox self (return value: ccui.CheckBox)
        
return nil
