
--------------------------------
-- @module Slider
-- @extend Widget
-- @parent_module ccui

--------------------------------
-- Changes the progress direction of slider.<br>
-- param percent    percent value from 1 to 100.
-- @function [parent=#Slider] setPercent 
-- @param self
-- @param #int percent
        
--------------------------------
-- Load dark state texture for slider ball.<br>
-- param disabled    dark state texture.<br>
-- param texType    @see TextureResType
-- @function [parent=#Slider] loadSlidBallTextureDisabled 
-- @param self
-- @param #string disabled
-- @param #int texType
        
--------------------------------
-- Load normal state texture for slider ball.<br>
-- param normal    normal state texture.<br>
-- param texType    @see TextureResType
-- @function [parent=#Slider] loadSlidBallTextureNormal 
-- @param self
-- @param #string normal
-- @param #int texType
        
--------------------------------
-- Load texture for slider bar.<br>
-- param fileName   file name of texture.<br>
-- param texType    @see TextureResType
-- @function [parent=#Slider] loadBarTexture 
-- @param self
-- @param #string fileName
-- @param #int texType
        
--------------------------------
-- Load dark state texture for slider progress bar.<br>
-- param fileName    file path of texture.<br>
-- param texType    @see TextureResType
-- @function [parent=#Slider] loadProgressBarTexture 
-- @param self
-- @param #string fileName
-- @param #int texType
        
--------------------------------
-- Load textures for slider ball.<br>
-- param slider ball normal    normal state texture.<br>
-- param slider ball selected    selected state texture.<br>
-- param slider ball disabled    dark state texture.<br>
-- param texType    @see TextureResType
-- @function [parent=#Slider] loadSlidBallTextures 
-- @param self
-- @param #string normal
-- @param #string pressed
-- @param #string disabled
-- @param #int texType
        
--------------------------------
-- Sets capinsets for slider, if slider is using scale9 renderer.<br>
-- param capInsets    capinsets for slider
-- @function [parent=#Slider] setCapInsetProgressBarRebderer 
-- @param self
-- @param #rect_table capInsets
        
--------------------------------
-- Sets capinsets for slider, if slider is using scale9 renderer.<br>
-- param capInsets    capinsets for slider
-- @function [parent=#Slider] setCapInsetsBarRenderer 
-- @param self
-- @param #rect_table capInsets
        
--------------------------------
-- 
-- @function [parent=#Slider] getCapInsetsProgressBarRebderer 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- Sets if slider is using scale9 renderer.<br>
-- param true that using scale9 renderer, false otherwise.
-- @function [parent=#Slider] setScale9Enabled 
-- @param self
-- @param #bool able
        
--------------------------------
-- Sets capinsets for slider, if slider is using scale9 renderer.<br>
-- param capInsets    capinsets for slider
-- @function [parent=#Slider] setCapInsets 
-- @param self
-- @param #rect_table capInsets
        
--------------------------------
-- 
-- @function [parent=#Slider] addEventListener 
-- @param self
-- @param #function callback
        
--------------------------------
-- Load selected state texture for slider ball.<br>
-- param selected    selected state texture.<br>
-- param texType    @see TextureResType
-- @function [parent=#Slider] loadSlidBallTexturePressed 
-- @param self
-- @param #string pressed
-- @param #int texType
        
--------------------------------
-- 
-- @function [parent=#Slider] isScale9Enabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Slider] getCapInsetsBarRenderer 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- Gets the progress direction of slider.<br>
-- return percent    percent value from 1 to 100.
-- @function [parent=#Slider] getPercent 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Allocates and initializes.
-- @function [parent=#Slider] create 
-- @param self
-- @return Slider#Slider ret (return value: ccui.Slider)
        
--------------------------------
-- 
-- @function [parent=#Slider] createInstance 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- 
-- @function [parent=#Slider] getVirtualRenderer 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#Slider] ignoreContentAdaptWithSize 
-- @param self
-- @param #bool ignore
        
--------------------------------
-- Returns the "class name" of widget.
-- @function [parent=#Slider] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#Slider] hitTest 
-- @param self
-- @param #vec2_table pt
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Slider] getVirtualRendererSize 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- Default constructor
-- @function [parent=#Slider] Slider 
-- @param self
        
return nil
