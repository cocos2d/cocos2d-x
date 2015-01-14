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
    local rootSize = self._layout:getSize()
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
    self._layout = ccs.GUIReader:getInstance():widgetFromBinaryFile("cocosui/UIEditorTest/UIButton/windows_UIButton_Editor_1.csb")
    self._uiLayer:addChild(self._layout)
    self:configureGUIScene()

    -- local widgetSize = self._widget:getSize()
    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("No Event")
    self._displayValueLabel:setFontName("fonts/Marker Felt.ttf")
    self._displayValueLabel:setFontSize(30)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(self._layout:getSize().width / 2,
                                            self._layout:getSize().height - self._displayValueLabel:getSize().height * 2))
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
    local rootSize = self._layout:getSize()
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
    self._layout = ccs.GUIReader:getInstance():widgetFromBinaryFile("cocosui/UIEditorTest/UICheckBox/windows_ui_checkbox_editor_1.csb")
    self._uiLayer:addChild(self._layout)
    self:configureGUIScene()

    -- local widgetSize = self._widget:getSize()
    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("No Event")
    self._displayValueLabel:setFontName("fonts/Marker Felt.ttf")
    self._displayValueLabel:setFontSize(30)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(self._layout:getSize().width / 2,
                                            self._layout:getSize().height - self._displayValueLabel:getSize().height * 2))
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
    local rootSize = self._layout:getSize()
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

    local scaleSlider = ccui.Helper:seekWidgetByName(root, "Slider_740")
    scaleSlider:addEventListener(sliderEvent)
end

function UISliderEditorTest:initExtend()
    self:init()
    self._layout = ccs.GUIReader:getInstance():widgetFromBinaryFile("cocosui/UIEditorTest/UISlider/windows_ui_slider_editor_1.csb")
    self._uiLayer:addChild(self._layout)
    self:configureGUIScene()

    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("No Event")
    self._displayValueLabel:setFontName("fonts/Marker Felt.ttf")
    self._displayValueLabel:setFontSize(30)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(self._layout:getSize().width / 2,
                                            self._layout:getSize().height - self._displayValueLabel:getSize().height * 2))
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
    local rootSize = self._layout:getSize()
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
    self._layout = ccs.GUIReader:getInstance():widgetFromBinaryFile("cocosui/UIEditorTest/UIImageView/windows_ui_ImageView_editor_1.csb")
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
    local rootSize = self._layout:getSize()
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
    self._layout = ccs.GUIReader:getInstance():widgetFromBinaryFile("cocosui/UIEditorTest/UILoadingBar/windows_ui_loadingbar_editor_1.csb")
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
    local rootSize = self._layout:getSize()
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
    self._layout = ccs.GUIReader:getInstance():widgetFromBinaryFile("cocosui/UIEditorTest/UILabelAtlas/windows_ui_labelatlas_editor_1.csb")
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
    local rootSize = self._layout:getSize()
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
    self._layout = ccs.GUIReader:getInstance():widgetFromBinaryFile("cocosui/UIEditorTest/UILabel/windows_ui_label_editor_1.csb")
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
    local rootSize = self._layout:getSize()
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
    self._layout = ccs.GUIReader:getInstance():widgetFromBinaryFile("cocosui/UIEditorTest/UILabelBMFont/windows_ui_labelbmfont_editor_1.csb")
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
    local rootSize = self._layout:getSize()
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
    self._layout = ccs.GUIReader:getInstance():widgetFromBinaryFile("cocosui/UIEditorTest/UITextField/windows_ui_textfield_editor_1.csb")
    self._uiLayer:addChild(self._layout)
    self:configureGUIScene()

    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("No Event")
    self._displayValueLabel:setFontName("fonts/Marker Felt.ttf")
    self._displayValueLabel:setFontSize(30)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(self._layout:getSize().width / 2,
                                            self._layout:getSize().height - self._displayValueLabel:getSize().height * 2))
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
    local rootSize = self._layout:getSize()
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
    self._layout = ccs.GUIReader:getInstance():widgetFromBinaryFile("cocosui/UIEditorTest/UILayout/Layout/windows_ui_layout_editor_1.csb")
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

    self._displayValueLabel = ccui.Text:create("UILayoutComponentTest_Editor", "", 20)
    self._displayValueLabel:setPosition(cc.p(screenSize.width / 2, screenSize.height - self._displayValueLabel:getContentSize().height / 2))
    self._uiLayer:addChild(self._displayValueLabel)

    local back_label = ccui.Text:create("Back", "", 20)
    back_label:setTouchEnabled(true)
    local labelLayout = ccui.LayoutComponent:bindLayoutComponent(back_label)
    labelLayout:setHorizontalEdge(ccui.LayoutComponent.HorizontalEdge.Right)
    labelLayout:setVerticalEdge(ccui.LayoutComponent.VerticalEdge.Bottom)
    back_label:addTouchEventListener(function(sender, eventType)
        if eventType == ccui.TouchEventType.ended then
            self:unscheduleUpdate()
            runCocoStudioUIEditorTestScene()
        end
    end)
    self._layout:addChild(back_label)
end

function LayoutComponentTest:initExtend()
    self:init()
    local screenSize = cc.Director:getInstance():getWinSize()
    self._layout = ccui.Layout:create()
    self._uiLayer:addChild(self._layout)
    self._layout:setContentSize(screenSize)

    local node = cc.CSLoader:createNode("cocosui/UIEditorTest/UILayout/LayoutComponent/Scene.csb")
    node:setContentSize(screenSize)
    self._layout:addChild(node)
    self:configureGUIScene()
    ccui.Helper:doLayout(self._layout)
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
    local rootSize = self._layout:getSize()
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
    self._layout = ccs.GUIReader:getInstance():widgetFromBinaryFile("cocosui/UIEditorTest/UIScrollView/Vertical/windows_ui_scrollview_editor_1.csb")
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
    local rootSize = self._layout:getSize()
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
    self._layout = ccs.GUIReader:getInstance():widgetFromBinaryFile("cocosui/UIEditorTest/UIPageView/windows_ui_pageview_editor_1.csb")
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
    local rootSize = self._layout:getSize()
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

function ListViewEditorTest:initExtend()
    self:init()
    self._layout = ccs.GUIReader:getInstance():widgetFromBinaryFile("cocosui/UIEditorTest/UIListView/Vertical/windows_ui_listview_editor_1.csb")
    self._uiLayer:addChild(self._layout)
    self:configureGUIScene()
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
    local rootSize = self._layout:getSize()
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
    self._layout = ccs.GUIReader:getInstance():widgetFromBinaryFile("cocosui/UIEditorTest/UIWidgetAddNode/windows_ui_widget_add_node_editor.csb")
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

    {
        itemTitle = "gui Editor LabelAtalsTest",
        testScene = function () 
            runLabelAtalsEditorTestScene()
        end
    },

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
