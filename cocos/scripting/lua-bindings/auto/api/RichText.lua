
--------------------------------
-- @module RichText
-- @extend Widget
-- @parent_module ccui

--------------------------------
-- brief Insert a RichElement at a given index.<br>
-- param element A RichElement type.<br>
-- param index A given index.
-- @function [parent=#RichText] insertElement 
-- @param self
-- @param #ccui.RichElement element
-- @param #int index
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
--  @brief enable the outline of a-tag 
-- @function [parent=#RichText] setAnchorTextOutline 
-- @param self
-- @param #bool enable
-- @param #color3b_table outlineColor
-- @param #int outlineSize
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- 
-- @function [parent=#RichText] getFontSize 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- brief Add a RichElement at the end of RichText.<br>
-- param element A RichElement instance.
-- @function [parent=#RichText] pushBackElement 
-- @param self
-- @param #ccui.RichElement element
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- 
-- @function [parent=#RichText] setAnchorTextBold 
-- @param self
-- @param #bool enable
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- 
-- @function [parent=#RichText] getAnchorFontColor 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#RichText] getAnchorTextShadowBlurRadius 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  @brief enable the shadow of a-tag 
-- @function [parent=#RichText] setAnchorTextShadow 
-- @param self
-- @param #bool enable
-- @param #color3b_table shadowColor
-- @param #size_table offset
-- @param #int blurRadius
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- 
-- @function [parent=#RichText] isAnchorTextItalicEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#RichText] setAnchorFontColor 
-- @param self
-- @param #string color
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- 
-- @function [parent=#RichText] setFontFace 
-- @param self
-- @param #string face
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- 
-- @function [parent=#RichText] setAnchorTextGlow 
-- @param self
-- @param #bool enable
-- @param #color3b_table glowColor
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- 
-- @function [parent=#RichText] getHorizontalAlignment 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#RichText] setHorizontalAlignment 
-- @param self
-- @param #int a
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- 
-- @function [parent=#RichText] setAnchorTextDel 
-- @param self
-- @param #bool enable
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- 
-- @function [parent=#RichText] getAnchorTextOutlineColor3B 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- 
-- @function [parent=#RichText] stringWithColor4B 
-- @param self
-- @param #color4b_table color4b
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#RichText] initWithXML 
-- @param self
-- @param #string xml
-- @param #map_table defaults
-- @param #function handleOpenUrl
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#RichText] getAnchorFontColor3B 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- brief Rearrange all RichElement in the RichText.<br>
-- It's usually called internally.
-- @function [parent=#RichText] formatText 
-- @param self
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- 
-- @function [parent=#RichText] getAnchorTextGlowColor3B 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- 
-- @function [parent=#RichText] openUrl 
-- @param self
-- @param #string url
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- 
-- @function [parent=#RichText] getFontFace 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#RichText] setFontColor 
-- @param self
-- @param #string color
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- 
-- @function [parent=#RichText] isAnchorTextGlowEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#RichText] getDefaults 
-- @param self
-- @return map_table#map_table ret (return value: map_table)
        
--------------------------------
-- 
-- @function [parent=#RichText] isAnchorTextUnderlineEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#RichText] getFontColor 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#RichText] isAnchorTextShadowEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#RichText] getAnchorTextOutlineSize 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- brief Set vertical space between each RichElement.<br>
-- param space Point in float.
-- @function [parent=#RichText] setVerticalSpace 
-- @param self
-- @param #float space
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- 
-- @function [parent=#RichText] isAnchorTextDelEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#RichText] setDefaults 
-- @param self
-- @param #map_table defaults
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- 
-- @function [parent=#RichText] setWrapMode 
-- @param self
-- @param #int wrapMode
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- 
-- @function [parent=#RichText] setFontSize 
-- @param self
-- @param #float size
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- @overload self, ccui.RichElement         
-- @overload self, int         
-- @function [parent=#RichText] removeElement
-- @param self
-- @param #int index
-- @return RichText#RichText self (return value: ccui.RichText)

--------------------------------
-- 
-- @function [parent=#RichText] setAnchorTextItalic 
-- @param self
-- @param #bool enable
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- 
-- @function [parent=#RichText] getAnchorTextShadowOffset 
-- @param self
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
-- 
-- @function [parent=#RichText] isAnchorTextBoldEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#RichText] getAnchorTextShadowColor3B 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- 
-- @function [parent=#RichText] stringWithColor3B 
-- @param self
-- @param #color3b_table color3b
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#RichText] isAnchorTextOutlineEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#RichText] getFontColor3B 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- 
-- @function [parent=#RichText] getWrapMode 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#RichText] setAnchorTextUnderline 
-- @param self
-- @param #bool enable
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- 
-- @function [parent=#RichText] color3BWithString 
-- @param self
-- @param #string color
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- brief Create a empty RichText.<br>
-- return RichText instance.
-- @function [parent=#RichText] create 
-- @param self
-- @return RichText#RichText ret (return value: ccui.RichText)
        
--------------------------------
-- brief Create a RichText from an XML<br>
-- return RichText instance.
-- @function [parent=#RichText] createWithXML 
-- @param self
-- @param #string xml
-- @param #map_table defaults
-- @param #function handleOpenUrl
-- @return RichText#RichText ret (return value: ccui.RichText)
        
--------------------------------
-- 
-- @function [parent=#RichText] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#RichText] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#RichText] ignoreContentAdaptWithSize 
-- @param self
-- @param #bool ignore
-- @return RichText#RichText self (return value: ccui.RichText)
        
--------------------------------
-- brief Default constructor.<br>
-- js ctor<br>
-- lua new
-- @function [parent=#RichText] RichText 
-- @param self
-- @return RichText#RichText self (return value: ccui.RichText)
        
return nil
