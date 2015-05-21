local LINE_SPACE = 40
local ITEM_TAG_BASIC = 1000
local CurPos = {x = 0, y = 0}
local BeginPos = {x = 0, y = 0}

local targetPlatform = cc.Application:getInstance():getTargetPlatform()

local function getFont()
    if kTargetIphone == targetPlatform or kTargetIpad == targetPlatform then
        return "Marker Felt"
    else
        return "cocosui/Marker Felt.ttf"
    end
end


local UIScene = class("UIScene")
UIScene.__index = UIScene
UIScene._uiLayer= nil
UIScene._sceneTitle = nil

function UIScene.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIScene)
    return target
end

function UIScene:init()
    self._uiLayer = cc.Layer:create()
    self:addChild(self._uiLayer)
end

function UIScene.create()
    local scene = cc.Scene:create()
    local layer = UIScene.extend(cc.Layer:create())
    layer:init()
    scene:addChild(layer)
    return scene   
end

local UIButtonTest = class("UIButtonTest",UIScene)
UIButtonTest._displayValueLabel = nil

function UIButtonTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIButtonTest)
    return target
end

function UIButtonTest:configureGUIScene()
    local screenSize = cc.Director:getInstance():getWinSize()
    local rootSize = self._layout:getContentSize()
    self._uiLayer:setPosition(cc.p((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = self._layout:getChildByName("root_Panel")  
    local sceneTitle = ccui.Helper:seekWidgetByName(root, "UItest")

    local function toGUIEditorTestScene(sender,eventType)
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  ccui.Helper:seekWidgetByName(root, "back")
    back_label:addTouchEventListener(toGUIEditorTestScene)

    local function touchEvent(sender,eventType)
        if eventType == ccui.TouchEventType.began then
            self._displayValueLabel:setString("Touch Down")
        elseif eventType == ccui.TouchEventType.moved then
            self._displayValueLabel:setString("Touch Move")
        elseif eventType == ccui.TouchEventType.ended then
            self._displayValueLabel:setString("Touch Up")
        elseif eventType == ccui.TouchEventType.canceled then
            self._displayValueLabel:setString("Touch Cancelled")
        end
    end
    
    local button = ccui.Helper:seekWidgetByName(root, "Button_123")
    button:addTouchEventListener(touchEvent)
    
    local title_button = ccui.Helper:seekWidgetByName(root, "Button_126")
    title_button:addTouchEventListener(touchEvent)
    
    local scale9_button = ccui.Helper:seekWidgetByName(root, "Button_129")
    scale9_button:addTouchEventListener(touchEvent)
end

function UIButtonTest:initExtend()
    self:init()

    local node = cc.CSLoader:createNode("cocosui/UIEditorTest/UIButton/res.csb")
    local child = node:getChildByTag(4)
    child:removeFromParent()
    self._layout = child
    self._uiLayer:addChild(self._layout)
    self:configureGUIScene()

    -- local widgetSize = self._widget:getSize()
    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("No Event")
    self._displayValueLabel:setFontName("fonts/Marker Felt.ttf")
    self._displayValueLabel:setFontSize(30)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(self._layout:getContentSize().width / 2,
                                            self._layout:getContentSize().height - self._displayValueLabel:getContentSize().height * 2))
    self._uiLayer:addChild(self._displayValueLabel)
end

function UIButtonTest.create()
    local scene = cc.Scene:create()
    local layer = UIButtonTest.extend(cc.Layer:create())
    layer:initExtend()
    scene:addChild(layer)
    cc.Director:getInstance():replaceScene(scene) 
end

local function runEditButtonTestScene()
    UIButtonTest.create()
end

local UICheckBoxEditorTest = class("UICheckBoxEditorTest",UIScene)
UICheckBoxEditorTest._displayValueLabel = nil

function UICheckBoxEditorTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UICheckBoxEditorTest)
    return target
end

function UICheckBoxEditorTest:configureGUIScene()
    local screenSize = cc.Director:getInstance():getWinSize()
    local rootSize = self._layout:getContentSize()
    self._uiLayer:setPosition(cc.p((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = self._layout:getChildByName("root_Panel")   
    local sceneTitle = ccui.Helper:seekWidgetByName(root, "UItest")

    local function toGUIEditorTestScene(sender,eventType)
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  ccui.Helper:seekWidgetByName(root, "back")
    back_label:addTouchEventListener(toGUIEditorTestScene)

    local function selectedStateEvent(sender,eventType)
        if eventType == ccui.CheckBoxEventType.selected then
            self._displayValueLabel:setString("Selected")
        elseif eventType == ccui.CheckBoxEventType.unselected then
            self._displayValueLabel:setString("Unselected")
        end
    end

    local checkbox = ccui.Helper:seekWidgetByName(root, "CheckBox_540")
    checkbox:addEventListener(selectedStateEvent)
end

function UICheckBoxEditorTest:initExtend()
    self:init()

    local node = cc.CSLoader:createNode("cocosui/UIEditorTest/UICheckBox/res.csb")
    local child = node:getChildByTag(5)
    child:removeFromParent()
    self._layout = child
    self._uiLayer:addChild(self._layout)
    self:configureGUIScene()

    -- local widgetSize = self._widget:getSize()
    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("No Event")
    self._displayValueLabel:setFontName("fonts/Marker Felt.ttf")
    self._displayValueLabel:setFontSize(30)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(self._layout:getContentSize().width / 2,
                                            self._layout:getContentSize().height - self._displayValueLabel:getContentSize().height * 2))
    self._uiLayer:addChild(self._displayValueLabel)
end

function UICheckBoxEditorTest.create()
    local scene = cc.Scene:create()
    local layer = UICheckBoxEditorTest.extend(cc.Layer:create())
    layer:initExtend()
    scene:addChild(layer)
    cc.Director:getInstance():replaceScene(scene) 
end

local function runEditButtonEditorTestScene()
    UICheckBoxEditorTest.create()
end


local UISliderEditorTest = class("UISliderEditorTest",UIScene)
UISliderEditorTest._displayValueLabel = nil

function UISliderEditorTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UISliderEditorTest)
    return target
end

function UISliderEditorTest:configureGUIScene()
    local screenSize = cc.Director:getInstance():getWinSize()
    local rootSize = self._layout:getContentSize()
    self._uiLayer:setPosition(cc.p((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = self._layout:getChildByName("root_Panel")
    local sceneTitle = ccui.Helper:seekWidgetByName(root, "UItest")

    local function toGUIEditorTestScene(sender,eventType)
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  ccui.Helper:seekWidgetByName(root, "back")
    back_label:addTouchEventListener(toGUIEditorTestScene)

    local function sliderEvent(sender,eventType)
        if eventType == ccui.SliderEventType.percentChanged then
            local slider = sender
            local percent = "Percent " .. slider:getPercent()
            self._displayValueLabel:setString(percent)
        end
    end

    local slider = ccui.Helper:seekWidgetByName(root, "Slider_738")
    slider:addEventListener(sliderEvent)
end

function UISliderEditorTest:initExtend()
    self:init()

    local node = cc.CSLoader:createNode("cocosui/UIEditorTest/UISlider/res.csb")
    local child = node:getChildByTag(5)
    child:removeFromParent()
    self._layout = child
    self._uiLayer:addChild(self._layout)
    self:configureGUIScene()

    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("No Event")
    self._displayValueLabel:setFontName("fonts/Marker Felt.ttf")
    self._displayValueLabel:setFontSize(30)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(self._layout:getContentSize().width / 2,
                                            self._layout:getContentSize().height - self._displayValueLabel:getContentSize().height * 2))
    self._uiLayer:addChild(self._displayValueLabel)
end

function UISliderEditorTest.create()
    local scene = cc.Scene:create()
    local layer = UISliderEditorTest.extend(cc.Layer:create())
    layer:initExtend()
    scene:addChild(layer)
    cc.Director:getInstance():replaceScene(scene) 
end

local function runSliderEditorTestScene()
    UISliderEditorTest.create()
end

local UIImageViewEditorTest = class("UIImageViewEditorTest",UIScene)
UIImageViewEditorTest._displayValueLabel = nil

function UIImageViewEditorTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIImageViewEditorTest)
    return target
end

function UIImageViewEditorTest:configureGUIScene()
    local screenSize = cc.Director:getInstance():getWinSize()
    local rootSize = self._layout:getContentSize()
    self._uiLayer:setPosition(cc.p((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = self._layout:getChildByName("root_Panel")
    local sceneTitle = ccui.Helper:seekWidgetByName(root, "UItest")

    local function toGUIEditorTestScene(sender,eventType)
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  ccui.Helper:seekWidgetByName(root, "back")
    back_label:addTouchEventListener(toGUIEditorTestScene)
end

function UIImageViewEditorTest:initExtend()
    self:init()

    local node = cc.CSLoader:createNode("cocosui/UIEditorTest/UIImageView/res.csb")
    local child = node:getChildByTag(5)
    child:removeFromParent()
    self._layout = child
    self._uiLayer:addChild(self._layout)
    self:configureGUIScene()
end

function UIImageViewEditorTest.create()
    local scene = cc.Scene:create()
    local layer = UIImageViewEditorTest.extend(cc.Layer:create())
    layer:initExtend()
    scene:addChild(layer)
    cc.Director:getInstance():replaceScene(scene) 
end

local function runImageViewEditorTestScene()
    UIImageViewEditorTest.create()
end

local LoadingBarEditorTest = class("LoadingBarEditorTest",UIScene)
LoadingBarEditorTest._displayValueLabel = nil

function LoadingBarEditorTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, LoadingBarEditorTest)
    return target
end

function LoadingBarEditorTest:configureGUIScene()
    local screenSize = cc.Director:getInstance():getWinSize()
    local rootSize = self._layout:getContentSize()
    self._uiLayer:setPosition(cc.p((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = self._layout:getChildByName("root_Panel")    
    local sceneTitle = ccui.Helper:seekWidgetByName(root, "UItest")

    local function toGUIEditorTestScene(sender,eventType)
        self:unscheduleUpdate()
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  ccui.Helper:seekWidgetByName(root, "back")
    back_label:addTouchEventListener(toGUIEditorTestScene)

    local loadingBar_left_to_right = ccui.Helper:seekWidgetByName(root, "LoadingBar_856")
    loadingBar_left_to_right:setPercent(0)
    
    local loadingBar_right_to_left = ccui.Helper:seekWidgetByName(root, "LoadingBar_857")
    loadingBar_right_to_left:setPercent(0)
end

function LoadingBarEditorTest:initExtend()
    self:init()

    local node = cc.CSLoader:createNode("cocosui/UIEditorTest/UILoadingBar/res.csb")
    local child = node:getChildByTag(5)
    child:removeFromParent()
    self._layout = child
    self._uiLayer:addChild(self._layout)
    self:configureGUIScene()

    self._count = 0

    local function update(delta)
        self._count = self._count + 1
        if self._count > 100 then
            self._count = 0
        end

        local root = self._layout:getChildByName("root_Panel")
    
        local loadingBar_left_to_right = ccui.Helper:seekWidgetByName(root, "LoadingBar_856")
        loadingBar_left_to_right:setPercent(self._count)
    
        local loadingBar_right_to_left = ccui.Helper:seekWidgetByName(root, "LoadingBar_857")
        loadingBar_right_to_left:setPercent(self._count)
    end

    self:scheduleUpdateWithPriorityLua(update, 0)
end

function LoadingBarEditorTest.create()
    local scene = cc.Scene:create()
    local layer = LoadingBarEditorTest.extend(cc.Layer:create())
    layer:initExtend()
    scene:addChild(layer)
    cc.Director:getInstance():replaceScene(scene) 
end

local function runLoadingBarEditorTestScene()
    LoadingBarEditorTest.create()
end

local LabelAtalsEditorTest = class("LabelAtalsEditorTest",UIScene)
LabelAtalsEditorTest._displayValueLabel = nil

function LabelAtalsEditorTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, LabelAtalsEditorTest)
    return target
end

function LabelAtalsEditorTest:configureGUIScene()
    local screenSize = cc.Director:getInstance():getWinSize()
    local rootSize = self._layout:getContentSize()
    self._uiLayer:setPosition(cc.p((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = self._layout:getChildByName("root_Panel")
    local sceneTitle = ccui.Helper:seekWidgetByName(root, "UItest")

    local function toGUIEditorTestScene(sender,eventType)
        self:unscheduleUpdate()
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  ccui.Helper:seekWidgetByName(root, "back")
    back_label:addTouchEventListener(toGUIEditorTestScene)
end

function LabelAtalsEditorTest:initExtend()
    self:init()

    local node = cc.CSLoader:createNode("cocosui/UIEditorTest/UILabelAtlas/res.csb")
    local child = node:getChildByTag(5)
    child:removeFromParent()
    self._layout = child
    self._uiLayer:addChild(self._layout)
    self:configureGUIScene()
end

function LabelAtalsEditorTest.create()
    local scene = cc.Scene:create()
    local layer = LabelAtalsEditorTest.extend(cc.Layer:create())
    layer:initExtend()
    scene:addChild(layer)
    cc.Director:getInstance():replaceScene(scene) 
end

local function runLabelAtalsEditorTestScene()
    LabelAtalsEditorTest.create()
end

local LabelEditorTest = class("LabelEditorTest",UIScene)
LabelEditorTest._displayValueLabel = nil

function LabelEditorTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, LabelEditorTest)
    return target
end

function LabelEditorTest:configureGUIScene()
    local screenSize = cc.Director:getInstance():getWinSize()
    local rootSize = self._layout:getContentSize()
    self._uiLayer:setPosition(cc.p((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = self._layout:getChildByName("root_Panel")   
    local sceneTitle = ccui.Helper:seekWidgetByName(root, "UItest")

    local function toGUIEditorTestScene(sender,eventType)
        self:unscheduleUpdate()
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  ccui.Helper:seekWidgetByName(root, "back")
    back_label:addTouchEventListener(toGUIEditorTestScene)
end

function LabelEditorTest:initExtend()
    self:init()

    local node = cc.CSLoader:createNode("cocosui/UIEditorTest/UILabel/res.csb")
    local child = node:getChildByTag(5)
    child:removeFromParent()
    self._layout = child
    self._uiLayer:addChild(self._layout)
    self:configureGUIScene()
end

function LabelEditorTest.create()
    local scene = cc.Scene:create()
    local layer = LabelEditorTest.extend(cc.Layer:create())
    layer:initExtend()
    scene:addChild(layer)
    cc.Director:getInstance():replaceScene(scene) 
end

local function runLabelEditorTestScene()
    LabelEditorTest.create()
end

local LabelBMFontEditorTest = class("LabelBMFontEditorTest",UIScene)
LabelBMFontEditorTest._displayValueLabel = nil

function LabelBMFontEditorTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, LabelBMFontEditorTest)
    return target
end

function LabelBMFontEditorTest:configureGUIScene()
    local screenSize = cc.Director:getInstance():getWinSize()
    local rootSize = self._layout:getContentSize()
    self._uiLayer:setPosition(cc.p((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = self._layout:getChildByName("root_Panel")
    local sceneTitle = ccui.Helper:seekWidgetByName(root, "UItest")

    local function toGUIEditorTestScene(sender,eventType)
        self:unscheduleUpdate()
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  ccui.Helper:seekWidgetByName(root, "back")
    back_label:addTouchEventListener(toGUIEditorTestScene)
end

function LabelBMFontEditorTest:initExtend()
    self:init()

    local node = cc.CSLoader:createNode("cocosui/UIEditorTest/UILabelBMFont/res.csb")
    local child = node:getChildByTag(5)
    child:removeFromParent()
    self._layout = child
    self._uiLayer:addChild(self._layout)
    self:configureGUIScene()
end

function LabelBMFontEditorTest.create()
    local scene = cc.Scene:create()
    local layer = LabelBMFontEditorTest.extend(cc.Layer:create())
    layer:initExtend()
    scene:addChild(layer)
    cc.Director:getInstance():replaceScene(scene) 
end

local function runLabelBMFontEditorTestScene()
    LabelBMFontEditorTest.create()
end

local TextFieldEditorTest = class("TextFieldEditorTest",UIScene)
TextFieldEditorTest._displayValueLabel = nil

function TextFieldEditorTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TextFieldEditorTest)
    return target
end

function TextFieldEditorTest:configureGUIScene()
    local screenSize = cc.Director:getInstance():getWinSize()
    local rootSize = self._layout:getContentSize()
    self._uiLayer:setPosition(cc.p((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = self._layout:getChildByName("root_Panel") 
    local sceneTitle = ccui.Helper:seekWidgetByName(root, "UItest")

    local function toGUIEditorTestScene(sender,eventType)
        self:unscheduleUpdate()
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  ccui.Helper:seekWidgetByName(root, "back")
    back_label:addTouchEventListener(toGUIEditorTestScene)

    local function textFieldEvent(sender, eventType)
        if eventType == ccui.TextFiledEventType.attach_with_ime then
            self._displayValueLabel:setString("attach with IME")
        elseif eventType == ccui.TextFiledEventType.detach_with_ime then
            self._displayValueLabel:setString("detach with IME")
        elseif eventType == ccui.TextFiledEventType.insert_text then
            self._displayValueLabel:setString("insert words")
        elseif eventType == ccui.TextFiledEventType.delete_backward then
            self._displayValueLabel:setString("delete word")
        end
    end

    local textField_normal = ccui.Helper:seekWidgetByName(root, "TextField_1109")
    textField_normal:addEventListener(textFieldEvent)
    
    local textField_max_character = ccui.Helper:seekWidgetByName(root, "TextField_1110")
    textField_max_character:addEventListener(textFieldEvent)
    
    local textField_password = ccui.Helper:seekWidgetByName(root, "TextField_1107")
    textField_password:addEventListener(textFieldEvent)
end

function TextFieldEditorTest:initExtend()
    self:init()

    local node = cc.CSLoader:createNode("cocosui/UIEditorTest/UITextField/res.csb")
    local child = node:getChildByTag(5)
    child:removeFromParent()
    self._layout = child
    self._uiLayer:addChild(self._layout)
    self:configureGUIScene()

    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("No Event")
    self._displayValueLabel:setFontName("fonts/Marker Felt.ttf")
    self._displayValueLabel:setFontSize(30)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(self._layout:getContentSize().width / 2,
                                            self._layout:getContentSize().height - self._displayValueLabel:getContentSize().height * 2))
    self._uiLayer:addChild(self._displayValueLabel)
end

function TextFieldEditorTest.create()
    local scene = cc.Scene:create()
    local layer = TextFieldEditorTest.extend(cc.Layer:create())
    layer:initExtend()
    scene:addChild(layer)
    cc.Director:getInstance():replaceScene(scene) 
end

local function runTextFieldEditorTestScene()
    TextFieldEditorTest.create()
end

local LayoutEditorTest = class("LayoutEditorTest",UIScene)
LayoutEditorTest._displayValueLabel = nil

function LayoutEditorTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, LayoutEditorTest)
    return target
end

function LayoutEditorTest:configureGUIScene()
    local screenSize = cc.Director:getInstance():getWinSize()
    local rootSize = self._layout:getContentSize()
    self._uiLayer:setPosition(cc.p((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = self._layout:getChildByName("root_Panel")  
    local sceneTitle = ccui.Helper:seekWidgetByName(root, "UItest")

    local function toGUIEditorTestScene(sender,eventType)
        self:unscheduleUpdate()
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  ccui.Helper:seekWidgetByName(root, "back")
    back_label:addTouchEventListener(toGUIEditorTestScene)
end

function LayoutEditorTest:initExtend()
    self:init()

    local node = cc.CSLoader:createNode("cocosui/UIEditorTest/UILayout/Layout/res.csb")
    local child = node:getChildByTag(5)
    child:removeFromParent()
    self._layout = child
    self._uiLayer:addChild(self._layout)
    self:configureGUIScene()
end

function LayoutEditorTest.create()
    local scene = cc.Scene:create()
    local layer = LayoutEditorTest.extend(cc.Layer:create())
    layer:initExtend()
    scene:addChild(layer)
    cc.Director:getInstance():replaceScene(scene) 
end

local function runLayoutEditorTestScene()
    LayoutEditorTest.create()
end

local LayoutComponentTest = class("LayoutComponentTest",UIScene)
LayoutComponentTest._displayValueLabel = nil

function LayoutComponentTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, LayoutComponentTest)
    return target
end

function LayoutComponentTest:configureGUIScene()
    
    local screenSize = cc.Director:getInstance():getWinSize()
    local rootSize   = self._layout:getContentSize()
    self._uiLayer:setPosition(cc.p((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))


    local scheduler = cc.Director:getInstance():getScheduler()
    local schedulerEntry = 0

    local root = self._layout:getChildByName("root_Panel")

    local back_label = ccui.Helper:seekWidgetByName(root, "back")
    back_label:addTouchEventListener(function(sender, eventType)
        scheduler:unscheduleScriptEntry(schedulerEntry)
        schedulerEntry = 0
        runCocoStudioUIEditorTestScene()
    end)

    local sceneTitle = ccui.Helper:seekWidgetByName(root, "UItest")


    local hUnchecked = ccui.Helper:seekWidgetByName(root, "Button_h_unchecked")
    local vUnchecked = ccui.Helper:seekWidgetByName(root, "Button_v_unchecked")
    local hChecked   = ccui.Helper:seekWidgetByName(root, "Button_h_checked")
    local vChecked   = ccui.Helper:seekWidgetByName(root, "Button_v_checked")
    local lPinUnchecked = ccui.Helper:seekWidgetByName(root, "Button_Pin_Left")
    local rPinUnchecked = ccui.Helper:seekWidgetByName(root, "Button_Pin_Right")
    local tPinUnchecked = ccui.Helper:seekWidgetByName(root, "Button_Pin_Top")
    local bPinUnchecked = ccui.Helper:seekWidgetByName(root, "Button_Pin_Bottom")
    local lPinChecked   = ccui.Helper:seekWidgetByName(root, "Button_Pin_Left_Checked")
    local rPinChecked   = ccui.Helper:seekWidgetByName(root, "Button_Pin_Right_Checked")
    local tPinChecked   = ccui.Helper:seekWidgetByName(root, "Button_Pin_Top_Checked")
    local bPinChecked   = ccui.Helper:seekWidgetByName(root, "Button_Pin_Bottom_Checked")

    local textPin = ccui.Helper:seekWidgetByName(root, "Text_Pin")
    local textStretch = ccui.Helper:seekWidgetByName(root, "Text_Stretch")
    local widget = ccui.Helper:seekWidgetByName(root, "Image_Widget")
    local container = ccui.Helper:seekWidgetByName(root, "background_Panel")

    local strenchStartIndex = 0
    local function onChangeLayoutComponent(sender)
        local statusStretch = textStretch:getString()
        --if statusStretch == nil
        local statusPin = textPin:getString()
        local hPinStatus = " Left"
        local vPinStatus = " Bottom" 

        if sender == hUnchecked then
            hUnchecked:setVisible(false)
            hChecked:setVisible(true)
            statusStretch = statusStretch .. " Horizontal"
            textStretch:setString(statusStretch)
        elseif sender == hChecked then
            hChecked:setVisible(false)
            hUnchecked:setVisible(true)
            strenchStartIndex = string.find(statusStretch, " Horizontal")
            if strenchStartIndex ~= nil then
                statusStretch = string.gsub(statusStretch, " Horizontal", "")
            end
            textStretch:setString(statusStretch)
        elseif sender == vUnchecked then
            vUnchecked:setVisible(false)
            vChecked:setVisible(true)
            statusStretch = statusStretch .. " Vertical"
            textStretch:setString(statusStretch)
        elseif sender == vChecked then
            vChecked:setVisible(false)
            vUnchecked:setVisible(true)
            strenchStartIndex = string.find(statusStretch, " Vertical")
            if strenchStartIndex ~= nil then
                statusStretch = string.gsub(statusStretch, " Vertical", "")
            end
            textStretch:setString(statusStretch)
        elseif sender == lPinUnchecked then
            lPinUnchecked:setVisible(false)
            lPinChecked:setVisible(true)
        elseif sender == lPinChecked then
            lPinChecked:setVisible(false)
            lPinUnchecked:setVisible(true)
        elseif sender == rPinUnchecked then
            rPinUnchecked:setVisible(false)
            rPinChecked:setVisible(true)
        elseif sender == rPinChecked then
            rPinChecked:setVisible(false)
            rPinUnchecked:setVisible(true)
        elseif sender == tPinUnchecked then
            tPinUnchecked:setVisible(false)
            tPinChecked:setVisible(true)
        elseif sender == tPinChecked then
            tPinChecked:setVisible(false)
            tPinUnchecked:setVisible(true)
        elseif sender == bPinUnchecked then
            bPinUnchecked:setVisible(false)
            bPinChecked:setVisible(true)
        elseif (sender == bPinChecked) then
            bPinChecked:setVisible(false)
            bPinUnchecked:setVisible(true)
        end

        if rPinChecked:isVisible() then
            if lPinChecked:isVisible() then
                hPinStatus = " Left Right"
            else
                hPinStatus = " Right"
            end
        end

        if tPinChecked:isVisible() then
            if bPinChecked:isVisible() then
                vPinStatus = " Top Bottom"
            else
                vPinStatus = " Top"
            end
        end

        statusPin = string.format("Pin:%s%s", hPinStatus, vPinStatus)
        textPin:setString(statusPin)

        local layoutComponent = ccui.LayoutComponent:bindLayoutComponent(widget)
        local widthEnableFlag = false
        if string.find(statusStretch, "Horizontal") ~= nil then
            widthEnableFlag = true
        end
        layoutComponent:setStretchWidthEnabled(widthEnableFlag)

        local heightEnableFlag = false
        if string.find(statusStretch, "Vertical") ~= nil then
            heightEnableFlag = true
        end
        layoutComponent:setStretchHeightEnabled(heightEnableFlag)

        local horizontalEdgeType = ccui.LayoutComponent.HorizontalEdge.None
        if string.find(statusPin, "Left") ~= nil and string.find(statusPin, "Right") == nil then
            horizontalEdgeType = ccui.LayoutComponent.HorizontalEdge.Left
        elseif string.find(statusPin, "Left") == nil and string.find(statusPin, "Right") ~= nil then
            horizontalEdgeType = ccui.LayoutComponent.HorizontalEdge.Right
        elseif string.find(statusPin, "Left") ~= nil and string.find(statusPin, "Right") ~= nil then
            horizontalEdgeType = ccui.LayoutComponent.HorizontalEdge.Center
        end
        layoutComponent:setHorizontalEdge(horizontalEdgeType)

        local verticalEdgeType = ccui.LayoutComponent.VerticalEdge.None
        if string.find(statusPin, "Top") ~= nil and string.find(statusPin, "Bottom") == nil then
            verticalEdgeType = ccui.LayoutComponent.VerticalEdge.Top
        elseif string.find(statusPin, "Top") == nil and string.find(statusPin, "Bottom") ~= nil then
            verticalEdgeType = ccui.LayoutComponent.VerticalEdge.Bottom
        elseif string.find(statusPin, "Top") ~= nil and string.find(statusPin, "Bottom") ~= nil then
            verticalEdgeType = ccui.LayoutComponent.VerticalEdge.Center
        end
        layoutComponent:setVerticalEdge(verticalEdgeType)
    end

    hUnchecked:addClickEventListener(onChangeLayoutComponent)
    vUnchecked:addClickEventListener(onChangeLayoutComponent)
    hChecked:addClickEventListener(onChangeLayoutComponent)
    vChecked:addClickEventListener(onChangeLayoutComponent)
    lPinUnchecked:addClickEventListener(onChangeLayoutComponent)
    rPinUnchecked:addClickEventListener(onChangeLayoutComponent)
    tPinUnchecked:addClickEventListener(onChangeLayoutComponent)
    bPinUnchecked:addClickEventListener(onChangeLayoutComponent)
    lPinChecked:addClickEventListener(onChangeLayoutComponent)
    rPinChecked:addClickEventListener(onChangeLayoutComponent)
    tPinChecked:addClickEventListener(onChangeLayoutComponent)
    bPinChecked:addClickEventListener(onChangeLayoutComponent)

    local btnSwitch = ccui.Helper:seekWidgetByName(root, "Button_Switch")
    local scheduleTimes = 0
    btnSwitch:addClickEventListener(function(sender)
        local layoutController = ccui.Helper:seekWidgetByName(root, "Panel_Controller")
        local size = container:getContentSize()
        local switchButton = ccui.Helper:seekWidgetByName(root, "Button_Switch")
        switchButton:setEnabled(false)
        switchButton:setBright(false)

        if size.width < 200 then
            layoutController:setVisible(false)

            scheduler:unscheduleScriptEntry(schedulerEntry)

            schedulerEntry = scheduler:scheduleScriptFunc(function(dt)

                local increaseSize = container:getContentSize()
                increaseSize.width = increaseSize.width + 303.0 / 40.0
                increaseSize.height = increaseSize.height + 70.0 / 40.0
                container:setContentSize(increaseSize)
                ccui.Helper:doLayout(container)

                if increaseSize.width > 390 then
                    switchButton:setEnabled(true)
                    switchButton:setBright(true)
                    scheduler:unscheduleScriptEntry(schedulerEntry)
                    schedulerEntry = 0
                end
            end, 0.025, false)
        else
            layoutController:setVisible(true)

            scheduler:unscheduleScriptEntry(schedulerEntry)
            schedulerEntry = scheduler:scheduleScriptFunc(function(dt)

                local decreaseSize = container:getContentSize()
                decreaseSize.width = decreaseSize.width - 303.0 / 40.0
                decreaseSize.height = decreaseSize.height - 70.0 / 40.0
                container:setContentSize(decreaseSize)
                ccui.Helper:doLayout(container)

                if decreaseSize.width < 110 then
                    switchButton:setEnabled(true)
                    switchButton:setBright(true)
                    scheduler:unscheduleScriptEntry(schedulerEntry)
                    schedulerEntry = 0
                end
            end, 0.025, false)
        end
    end)
end

function LayoutComponentTest:initExtend()
    self:init()

    local node = cc.CSLoader:createNode("cocosui/UIEditorTest/UILayout/LayoutComponent/res.csb")
    local child = node:getChildByTag(5)
    child:removeFromParent()
    self._layout = child
    self._uiLayer:addChild(self._layout)
    self:configureGUIScene()
end

function LayoutComponentTest.create()
    local scene = cc.Scene:create()
    local layer = LayoutComponentTest.extend(cc.Layer:create())
    layer:initExtend()
    scene:addChild(layer)
    cc.Director:getInstance():replaceScene(scene) 
end

local function runLayoutComponentTestScene()
    LayoutComponentTest.create()
end

local ScrollViewEditorTest = class("ScrollViewEditorTest",UIScene)
ScrollViewEditorTest._displayValueLabel = nil

function ScrollViewEditorTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, ScrollViewEditorTest)
    return target
end

function ScrollViewEditorTest:configureGUIScene()
    local screenSize = cc.Director:getInstance():getWinSize()
    local rootSize = self._layout:getContentSize()
    self._uiLayer:setPosition(cc.p((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = self._layout:getChildByName("root_Panel")    
    local sceneTitle = ccui.Helper:seekWidgetByName(root, "UItest")

    local function toGUIEditorTestScene(sender,eventType)
        self:unscheduleUpdate()
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  ccui.Helper:seekWidgetByName(root, "back")
    back_label:addTouchEventListener(toGUIEditorTestScene)
end

function ScrollViewEditorTest:initExtend()
    self:init()

    local node = cc.CSLoader:createNode("cocosui/UIEditorTest/UIScrollView/Vertical/res.csb")
    local child = node:getChildByTag(5)
    child:removeFromParent()
    self._layout = child
    self._uiLayer:addChild(self._layout)
    self:configureGUIScene()
end

function ScrollViewEditorTest.create()
    local scene = cc.Scene:create()
    local layer = ScrollViewEditorTest.extend(cc.Layer:create())
    layer:initExtend()
    scene:addChild(layer)
    cc.Director:getInstance():replaceScene(scene) 
end

local function runScrollViewEditorTestScene()
    ScrollViewEditorTest.create()
end

local PageViewEditorTest = class("PageViewEditorTest",UIScene)
PageViewEditorTest._displayValueLabel = nil

function PageViewEditorTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, PageViewEditorTest)
    return target
end

function PageViewEditorTest:configureGUIScene()
    local screenSize = cc.Director:getInstance():getWinSize()
    local rootSize = self._layout:getContentSize()
    self._uiLayer:setPosition(cc.p((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = self._layout:getChildByName("root_Panel") 
    local sceneTitle = ccui.Helper:seekWidgetByName(root, "UItest")

    local function toGUIEditorTestScene(sender,eventType)
        self:unscheduleUpdate()
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  ccui.Helper:seekWidgetByName(root, "back")
    back_label:addTouchEventListener(toGUIEditorTestScene)
end

function PageViewEditorTest:initExtend()
    self:init()

    local node = cc.CSLoader:createNode("cocosui/UIEditorTest/UIPageView/res.csb")
    local child = node:getChildByTag(5)
    child:removeFromParent()
    self._layout = child
    self._uiLayer:addChild(self._layout)
    self:configureGUIScene()
end

function PageViewEditorTest.create()
    local scene = cc.Scene:create()
    local layer = PageViewEditorTest.extend(cc.Layer:create())
    layer:initExtend()
    scene:addChild(layer)
    cc.Director:getInstance():replaceScene(scene) 
end

local function runPageViewEditorTestScene()
    PageViewEditorTest.create()
end

local ListViewEditorTest = class("ListViewEditorTest",UIScene)
ListViewEditorTest._displayValueLabel = nil

function ListViewEditorTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, ListViewEditorTest)
    return target
end

function ListViewEditorTest:configureGUIScene()
    local screenSize = cc.Director:getInstance():getWinSize()
    local rootSize = self._layout:getContentSize()
    self._uiLayer:setPosition(cc.p((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = self._layout:getChildByName("root_Panel")   
    local sceneTitle = ccui.Helper:seekWidgetByName(root, "UItest")

    local function toGUIEditorTestScene(sender,eventType)
        self:unscheduleUpdate()
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  ccui.Helper:seekWidgetByName(root, "back")
    back_label:addTouchEventListener(toGUIEditorTestScene)

    -- local listView = ccui.Helper:seekWidgetByName(root, "ListView_1214")
    -- if nil ~= listView then
    --     print("listView isBounceEnabled ", listView:isBounceEnabled())
    -- end
end

function ListViewEditorTest:setupListView(listView)
    local scale = 0.5
    local itemMargin = listView:getItemsMargin()

    local item0 = ccui.Text:create()
    item0:setString(string.format("Item margin: %d", math.floor(itemMargin)))
    listView:addChild(item0)

    local item1 = ccui.Layout:create()
    local checkbox = ccui.CheckBox:create("selected01.png", "selected01.png", "selected02.png", "selected01.png", "selected01.png")
    checkbox:setPosition(cc.p(checkbox:getCustomSize().width / 2, checkbox:getCustomSize().height / 2))
    item1:addChild(checkbox)
    local checkboxText = ccui.Text:create()
    checkboxText:setString("CheckBox")
    checkboxText:setFontSize(checkbox:getCustomSize().width * 0.8)
    checkboxText:setPosition(cc.p(checkbox:getCustomSize().width + checkboxText:getCustomSize().width / 2, checkbox:getCustomSize().height / 2))
    item1:addChild(checkboxText)
    local item1Width = scale * (checkbox:getCustomSize().width + checkboxText:getCustomSize().width)
    local item1Height = scale * checkbox:getCustomSize().height
    item1:setContentSize(cc.size(item1Width, item1Height))
    item1:setScale(scale)
    listView:addChild(item1)

    local item2 = ccui.Text:create()
    item2:setString("Text2")
    item2:setFontSize(checkbox:getCustomSize().width * 0.4)
    item2:setTextColor(cc.c4b(0, 255, 0, 255))
    listView:addChild(item2)

    local item3 = ccui.Layout:create()
    local imageview0 = ccui.ImageView:create("image.png")
    local imageview1 = ccui.ImageView:create("image.png")
    imageview1:setPositionX(imageview1:getCustomSize().width * 2)
    imageview0:setAnchorPoint(cc.p(0, 0))
    imageview1:setAnchorPoint(cc.p(0, 0))
    item3:setContentSize(cc.size(imageview0:getCustomSize().width * 3 * scale, imageview0:getCustomSize().height * scale))
    item3:addChild(imageview0)
    item3:addChild(imageview1)
    item3:setScale(scale)
    listView:addChild(item3)

    local item4 = ccui.Button:create("button.png", "button_p.png")
    item4:setTitleText("Button")
    listView:pushBackCustomItem(item4)

    local itemModel = ccui.Text:create()
    itemModel:setTextColor(cc.c4b(255, 0, 0, 125))
    itemModel:setString("List item model")
    listView:setItemModel(itemModel)
    listView:pushBackDefaultItem()
    listView:pushBackDefaultItem()
end

function ListViewEditorTest:initExtend()
    self:init()

    local node = cc.CSLoader:createNode("cocosui/UIEditorTest/UIListView/New/resV.csb")
    local child = node:getChildByTag(5)
    child:removeFromParent()
    self._layout = child
    self._uiLayer:addChild(self._layout)
    self:configureGUIScene()

    local listView1 = ccui.Helper:seekWidgetByName(self._layout, "ListView1")
    local listView2 = ccui.Helper:seekWidgetByName(self._layout, "ListView2")
    local listView3 = ccui.Helper:seekWidgetByName(self._layout, "ListView3")
    self:setupListView(listView1)
    self:setupListView(listView2)
    self:setupListView(listView3)
end

function ListViewEditorTest.create()
    local scene = cc.Scene:create()
    local layer = ListViewEditorTest.extend(cc.Layer:create())
    layer:initExtend()
    scene:addChild(layer)
    cc.Director:getInstance():replaceScene(scene) 
end

local function runListViewEditorTestScene()
    ListViewEditorTest.create()
end

local WidgetAddNodeEditorTest = class("WidgetAddNodeEditorTest",UIScene)
WidgetAddNodeEditorTest._displayValueLabel = nil

function WidgetAddNodeEditorTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, WidgetAddNodeEditorTest)
    return target
end

function WidgetAddNodeEditorTest:configureGUIScene()
    local screenSize = cc.Director:getInstance():getWinSize()
    local rootSize = self._layout:getContentSize()
    self._uiLayer:setPosition(cc.p((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = self._layout:getChildByName("root_Panel")   
    local sceneTitle = ccui.Helper:seekWidgetByName(root, "UItest")

    local function toGUIEditorTestScene(sender,eventType)
        self:unscheduleUpdate()
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  ccui.Helper:seekWidgetByName(root, "back")
    back_label:addTouchEventListener(toGUIEditorTestScene)

    
    local widget = ccui.Widget:create()
    widget:setPosition(cc.p(rootSize.width / 2.0, rootSize.height / 2.0))
    widget:setLocalZOrder(self._layout:getLocalZOrder() + 1)
    self._layout:addChild(widget)
    
    local sprite = cc.Sprite:create("cocosui/ccicon.png")
    widget:addChild(sprite)
end

function WidgetAddNodeEditorTest:initExtend()
    self:init()
    
    local node = cc.CSLoader:createNode("cocosui/UIEditorTest/UIWidgetAddNode/res.csb")
    local child = node:getChildByTag(5)
    child:removeFromParent()
    self._layout = child
    self._uiLayer:addChild(self._layout)
    self:configureGUIScene()
end

function WidgetAddNodeEditorTest.create()
    local scene = cc.Scene:create()
    local layer = WidgetAddNodeEditorTest.extend(cc.Layer:create())
    layer:initExtend()
    scene:addChild(layer)
    cc.Director:getInstance():replaceScene(scene) 
end

local function runWidgetAddNodeEditorTestScene()
    WidgetAddNodeEditorTest.create()
end

local UIEditorTestItemNames = 
{
    {
        itemTitle = "gui Editor ButtonTest",
        testScene = function () 
            runEditButtonTestScene()
        end
    },

    {
        itemTitle = "gui Editor CheckBoxTest",
        testScene = function () 
            runEditButtonEditorTestScene()
        end
    },

    {
        itemTitle = "gui Editor SliderTest",
        testScene = function () 
            runSliderEditorTestScene()
        end
    },

    {
        itemTitle = "gui Editor ImageViewTest",
        testScene = function () 
            runImageViewEditorTestScene()
        end
    },

    {
        itemTitle = "gui Editor LoadingBarTest",
        testScene = function () 
            runLoadingBarEditorTestScene()
        end
    },

    -- {
    --     itemTitle = "gui Editor LabelAtalsTest",
    --     testScene = function () 
    --         runLabelAtalsEditorTestScene()
    --     end
    -- },

    {
        itemTitle = "gui Editor LabelTest",
        testScene = function () 
            runLabelEditorTestScene()
        end
    },

    {
        itemTitle = "gui Editor LabelBMFontTest",
        testScene = function () 
            runLabelBMFontEditorTestScene()
        end
    },

    {
        itemTitle = "gui Editor TextFieldTest",
        testScene = function () 
            runTextFieldEditorTestScene()
        end
    },

    {
        itemTitle = "gui Editor LayoutTest",
        testScene = function () 
            runLayoutEditorTestScene()
        end
    },

    {
        itemTitle = "gui Editor UILayoutComponentTest",
        testScene = function () 
            runLayoutComponentTestScene()
        end
    },

    {
        itemTitle = "gui Editor ScrollViewTest",
        testScene = function () 
            runScrollViewEditorTestScene()
        end
    },

    {
        itemTitle = "gui Editor PageViewTest",
        testScene = function () 
            runPageViewEditorTestScene()
        end
    },

    {
        itemTitle = "gui Editor ListViewTest",
        testScene = function () 
            runListViewEditorTestScene()
        end
    },

    {
        itemTitle = "gui Editor WidgetAddNodeTest",
        testScene = function () 
            runWidgetAddNodeEditorTestScene()
        end
    },
} 

local CocoStudioUIEditorTestScene = class("CocoStudioUIEditorTestScene")
CocoStudioUIEditorTestScene.__index = CocoStudioUIEditorTestScene

function CocoStudioUIEditorTestScene.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, CocoStudioUIEditorTestScene)
    return target
end

function CocoStudioUIEditorTestScene:runThisTest()

end

function CocoStudioUIEditorTestScene.create()
    local scene = CocoStudioUIEditorTestScene.extend(cc.Scene:create())
    return scene   
end

local CocoStudioUIEditorTestLayer = class("CocoStudioUIEditorTestLayer")
CocoStudioUIEditorTestLayer.__index = CocoStudioUIEditorTestLayer

function CocoStudioUIEditorTestLayer.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, CocoStudioUIEditorTestLayer)
    return target
end

function CocoStudioUIEditorTestLayer.onMenuCallback(tag,sender)
    local index = sender:getLocalZOrder() - ITEM_TAG_BASIC
    UIEditorTestItemNames[index].testScene()
end

function CocoStudioUIEditorTestLayer:createMenu()

    local winSize = cc.Director:getInstance():getWinSize()

    local menu = cc.Menu:create()
    menu:setContentSize(cc.size(winSize.width, (#UIEditorTestItemNames + 1) * (LINE_SPACE)))
    menu:setPosition(CurPos.x, CurPos.y)
    cc.MenuItemFont:setFontName("Arial")
    cc.MenuItemFont:setFontSize(24)

    for i = 1, #UIEditorTestItemNames do
        local menuItem = cc.MenuItemFont:create(UIEditorTestItemNames[i].itemTitle)
        menuItem:setPosition(cc.p(winSize.width / 2, winSize.height - i* LINE_SPACE))
        menuItem:registerScriptTapHandler(CocoStudioUIEditorTestLayer.onMenuCallback)
        menu:addChild(menuItem, ITEM_TAG_BASIC + i)
    end

    self:addChild(menu)

    -- handling touch events
    local function onTouchBegan(touch, event)
        BeginPos = touch:getLocation()
        return true
    end

    local function onTouchMoved(touch, event)
        local location = touch:getLocation()
        local nMoveY = location.y - BeginPos.y
        local curPosx, curPosy = menu:getPosition()
        local nextPosy = curPosy + nMoveY
        if nextPosy < 0 then
            menu:setPosition(0, 0)
            return
        end

        if nextPosy > ((#UIEditorTestItemNames + 1) * LINE_SPACE - winSize.height) then
            menu:setPosition(0, ((#UIEditorTestItemNames + 1) * LINE_SPACE - winSize.height))
            return
        end

        menu:setPosition(curPosx, nextPosy)
        BeginPos = {x = location.x, y = location.y}
        CurPos = {x = curPosx, y = nextPosy}
    end

    local listener = cc.EventListenerTouchOneByOne:create()
    listener:registerScriptHandler(onTouchBegan,cc.Handler.EVENT_TOUCH_BEGAN )
    listener:registerScriptHandler(onTouchMoved,cc.Handler.EVENT_TOUCH_MOVED )
    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)
end

function CocoStudioUIEditorTestLayer.create()
    local layer = CocoStudioUIEditorTestLayer.extend(cc.Layer:create())

    if nil ~= layer then
        layer:createMenu()
    end 
    return layer
end

-------------------------------------
--CocoStudioUIEditorTest
-------------------------------------
function runCocoStudioUIEditorTestScene()
    local newScene = CocoStudioUIEditorTestScene.create()
    newScene:addChild(CreateBackMenuItem())
    newScene:addChild(CocoStudioUIEditorTestLayer.create())
    cc.Director:getInstance():replaceScene(newScene)
end
