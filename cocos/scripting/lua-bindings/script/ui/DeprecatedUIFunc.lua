--tip
local function deprecatedTip(old_name,new_name)
    print("\n********** \n"..old_name.." was deprecated please use ".. new_name .. " instead.\n**********")
end

--functions of ccui.Text will be deprecated begin
local TextDeprecated = { }
function TextDeprecated.setText(self, str)
    deprecatedTip("ccui.Text:setText","ccui.Text:setString")
    return self:setString(str)
end
rawset(ccui.Text,"setText", TextDeprecated.setText)

function TextDeprecated.getStringValue(self)
    deprecatedTip("ccui.Text:getStringValue","ccui.Text:getString")
    return self:getString()
end
rawset(ccui.Text,"getStringValue", TextDeprecated.getStringValue)

--functions of ccui.Text will be deprecated begin

--functions of ccui.TextAtlas will be deprecated begin
local TextAtlasDeprecated = { }
function TextAtlasDeprecated.setStringValue(self, str)
    deprecatedTip("ccui.TextAtlas:setStringValue","ccui.TextAtlas:setString")
    return self:setString(str)
end
rawset(ccui.TextAtlas,"setStringValue", TextAtlasDeprecated.setStringValue)

function TextAtlasDeprecated.getStringValue(self)
    deprecatedTip("ccui.TextAtlas:getStringValue","ccui.TextAtlas:getString")
    return self:getString()
end
rawset(ccui.TextAtlas,"getStringValue", TextAtlasDeprecated.getStringValue)
--functions of ccui.TextAtlas will be deprecated begin


--functions of ccui.TextBMFont will be deprecated begin
local TextBMFontDeprecated = { }
function TextBMFontDeprecated.setText(self, str)
    deprecatedTip("ccui.TextBMFont:setText","ccui.TextBMFont:setString")
    return self:setString(str)
end
rawset(ccui.TextBMFont,"setText", TextBMFontDeprecated.setText)

function TextBMFontDeprecated.getStringValue(self)
    deprecatedTip("ccui.Text:getStringValue","ccui.TextBMFont:getString")
    return self:getString()
end
rawset(ccui.Text,"getStringValue", TextBMFontDeprecated.getStringValue)
--functions of ccui.TextBMFont will be deprecated begin

--functions of cc.ShaderCache will be deprecated begin
local ShaderCacheDeprecated = { }
function ShaderCacheDeprecated.getProgram(self,strShader)
    deprecatedTip("cc.ShaderCache:getProgram","cc.ShaderCache:getGLProgram")
    return self:getGLProgram(strShader)
end
rawset(cc.ShaderCache,"getProgram", ShaderCacheDeprecated.getProgram)
--functions of ccui.TextBMFont will be deprecated begin

--functions of ccui.Widget will be deprecated begin
local UIWidgetDeprecated = { }
function UIWidgetDeprecated.getLeftInParent(self)
    deprecatedTip("ccui.Widget:getLeftInParent","ccui.Widget:getLeftBoundary")
    return self:getLeftBoundary()
end
rawset(ccui.Widget,"getLeftInParent", UIWidgetDeprecated.getLeftInParent)

function UIWidgetDeprecated.getBottomInParent(self)
    deprecatedTip("ccui.Widget:getBottomInParent","ccui.Widget:getBottomBoundary")
    return self:getBottomBoundary()
end
rawset(ccui.Widget,"getBottomInParent", UIWidgetDeprecated.getBottomInParent)

function UIWidgetDeprecated.getRightInParent(self)
    deprecatedTip("ccui.Widget:getRightInParent","ccui.Widget:getRightBoundary")
    return self:getRightBoundary()
end
rawset(ccui.Widget,"getRightInParent", UIWidgetDeprecated.getRightInParent)

function UIWidgetDeprecated.getTopInParent(self)
    deprecatedTip("ccui.Widget:getTopInParent","ccui.Widget:getTopBoundary")
    return self:getTopBoundary()
end
rawset(ccui.Widget,"getTopInParent", UIWidgetDeprecated.getTopInParent)

function UIWidgetDeprecated.getSize(self)
    deprecatedTip("ccui.Widget:getSize","ccui.Widget:getContentSize")
    return self:getContentSize()
end
rawset(ccui.Widget,"getSize", UIWidgetDeprecated.getSize)

function UIWidgetDeprecated.setSize(self, ...)
    deprecatedTip("ccui.Widget:setSize","ccui.Widget:setContentSize")
    return self:setContentSize(...)
end
rawset(ccui.Widget,"setSize", UIWidgetDeprecated.setSize)

--functions of ccui.Widget will be deprecated end

--functions of ccui.CheckBox will be deprecated begin
local UICheckBoxDeprecated = { }
function UICheckBoxDeprecated.addEventListenerCheckBox(self,handler)
    deprecatedTip("ccui.CheckBox:addEventListenerCheckBox","ccui.CheckBox:addEventListener")
    return self:addEventListener(handler)
end
rawset(ccui.CheckBox,"addEventListenerCheckBox", UICheckBoxDeprecated.addEventListenerCheckBox)

function UICheckBoxDeprecated.setSelectedState(self,flag)
   deprecatedTip("ccui.CheckBox:setSelectedState", "ccui.CheckBox:setSelected")
   return self:setSelected(flag)
end
rawset(ccui.CheckBox, "setSelectedState", UICheckBoxDeprecated.setSelectedState)

function UICheckBoxDeprecated.getSelectedState(self)
   deprecatedTip("ccui.CheckBox:getSelectedState", "ccui.CheckBox:getSelected")
   return self:getSelected()
end
rawset(ccui.CheckBox, "getSelectedState", UICheckBoxDeprecated.setSelectedState)

--functions of ccui.CheckBox will be deprecated end

--functions of ccui.Slider will be deprecated begin
local UISliderDeprecated = { }
function UISliderDeprecated.addEventListenerSlider(self,handler)
    deprecatedTip("ccui.Slider:addEventListenerSlider","ccui.Slider:addEventListener")
    return self:addEventListener(handler)
end
rawset(ccui.Slider,"addEventListenerSlider", UISliderDeprecated.addEventListenerSlider)
--functions of ccui.Slider will be deprecated end

--functions of ccui.TextField will be deprecated begin
local UITextFieldDeprecated = { }
function UITextFieldDeprecated.addEventListenerTextField(self,handler)
    deprecatedTip("ccui.TextField:addEventListenerTextField","ccui.TextField:addEventListener")
    return self:addEventListener(handler)
end
rawset(ccui.TextField,"addEventListenerTextField", UITextFieldDeprecated.addEventListenerTextField)

function UITextFieldDeprecated.setText(self, str)
    deprecatedTip("ccui.TextField:setText","ccui.TextField:setString")
    return self:setString(str)
end
rawset(ccui.TextField,"setText", UITextFieldDeprecated.setText)

function UITextFieldDeprecated.getStringValue(self)
    deprecatedTip("ccui.TextField:getStringValue","ccui.TextField:getString")
    return self:getString()
end
rawset(ccui.TextField,"getStringValue", UITextFieldDeprecated.getStringValue)
--functions of ccui.TextField will be deprecated end

--functions of ccui.PageView will be deprecated begin
local UIPageViewDeprecated = { }
function UIPageViewDeprecated.addEventListenerPageView(self,handler)
    deprecatedTip("ccui.PageView:addEventListenerPageView","ccui.PageView:addEventListener")
    return self:addEventListener(handler)
end
rawset(ccui.PageView,"addEventListenerPageView", UIPageViewDeprecated.addEventListenerPageView)
--functions of ccui.PageView will be deprecated end

--functions of ccui.ScrollView will be deprecated begin
local UIScrollViewDeprecated = { }
function UIScrollViewDeprecated.addEventListenerScrollView(self,handler)
    deprecatedTip("ccui.ScrollView:addEventListenerScrollView","ccui.ScrollView:addEventListener")
    return self:addEventListener(handler)
end
rawset(ccui.ScrollView,"addEventListenerScrollView", UIScrollViewDeprecated.addEventListenerScrollView)
--functions of ccui.ScrollView will be deprecated end

--functions of ccui.ListView will be deprecated begin
local UIListViewDeprecated = { }
function UIListViewDeprecated.addEventListenerListView(self,handler)
    deprecatedTip("ccui.ListView:addEventListenerListView","ccui.ListView:addEventListener")
    return self:addEventListener(handler)
end
rawset(ccui.ListView,"addEventListenerListView", UIListViewDeprecated.addEventListenerListView)
--functions of ccui.ListView will be deprecated end
