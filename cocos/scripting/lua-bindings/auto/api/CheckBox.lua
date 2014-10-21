
--------------------------------
-- @module CheckBox
-- @extend Widget
-- @parent_module ccui

--------------------------------
-- Load backGroundSelected texture for checkbox.<br>
-- param backGroundSelected     backGround selected state texture.<br>
-- param texType    @see TextureResType
-- @function [parent=#CheckBox] loadTextureBackGroundSelected 
-- @param self
-- @param #string backGroundSelected
-- @param #int texType
        
--------------------------------
-- Load backGroundDisabled texture for checkbox.<br>
-- param backGroundDisabled    backGroundDisabled texture.<br>
-- param texType    @see TextureResType
-- @function [parent=#CheckBox] loadTextureBackGroundDisabled 
-- @param self
-- @param #string backGroundDisabled
-- @param #int texType
        
--------------------------------
-- 
-- @function [parent=#CheckBox] setSelected 
-- @param self
-- @param #bool selected
        
--------------------------------
-- 
-- @function [parent=#CheckBox] addEventListener 
-- @param self
-- @param #function callback
        
--------------------------------
-- Load cross texture for checkbox.<br>
-- param cross    cross texture.<br>
-- param texType    @see TextureResType
-- @function [parent=#CheckBox] loadTextureFrontCross 
-- @param self
-- @param #string 
-- @param #int texType
        
--------------------------------
-- 
-- @function [parent=#CheckBox] isSelected 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Load textures for checkbox.<br>
-- param backGround    backGround texture.<br>
-- param backGroundSelected    backGround selected state texture.<br>
-- param cross    cross texture.<br>
-- param frontCrossDisabled    cross dark state texture.<br>
-- param texType    @see TextureResType
-- @function [parent=#CheckBox] loadTextures 
-- @param self
-- @param #string backGround
-- @param #string backGroundSelected
-- @param #string cross
-- @param #string backGroundDisabled
-- @param #string frontCrossDisabled
-- @param #int texType
        
--------------------------------
-- Load backGround texture for checkbox.<br>
-- param backGround    backGround texture.<br>
-- param texType    @see TextureResType
-- @function [parent=#CheckBox] loadTextureBackGround 
-- @param self
-- @param #string backGround
-- @param #int type
        
--------------------------------
-- Load frontCrossDisabled texture for checkbox.<br>
-- param frontCrossDisabled    frontCrossDisabled texture.<br>
-- param texType    @see TextureResType
-- @function [parent=#CheckBox] loadTextureFrontCrossDisabled 
-- @param self
-- @param #string frontCrossDisabled
-- @param #int texType
        
--------------------------------
-- @overload self, string, string, string, string, string, int         
-- @overload self         
-- @function [parent=#CheckBox] create
-- @param self
-- @param #string backGround
-- @param #string backGroundSeleted
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
-- Returns the "class name" of widget.
-- @function [parent=#CheckBox] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#CheckBox] getVirtualRendererSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- Default constructor
-- @function [parent=#CheckBox] CheckBox 
-- @param self
        
return nil
