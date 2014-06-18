local LINE_SPACE = 40
local ITEM_TAG_BASIC = 1000

local targetPlatform = CCApplication:sharedApplication():getTargetPlatform()

local function getFont()
    if kTargetIphone == targetPlatform or kTargetIpad == targetPlatform then
        return "Marker Felt"
    else
        return "cocosui/Marker Felt.ttf"
    end
end

local ccs = ccs or {}

ccs.TouchEventType = 
{
    began = 0,
    moved = 1,
    ended = 2,
    canceled = 3,
}

ccs.LoadingBarType = 
{ 
    left = 0, 
    right = 1,
}

ccs.CheckBoxEventType = 
{
    selected = 0,
    unselected = 1,
}

ccs.SliderEventType = 
{
    percent_changed = 0
}

ccs.TextFiledEventType = 
{
    attach_with_ime = 0,
    detach_with_ime = 1,
    insert_text = 2,
    delete_backward = 3,
}

ccs.LayoutBackGroundColorType = 
{
    none = 0,
    solid = 1,
    gradient = 2,
}

ccs.LayoutType = 
{
    absolute = 0,
    linearVertical = 1,
    linearHorizontal = 2,
    relative = 3,
}

ccs.UILinearGravity = 
{
    none = 0,
    left = 1,
    top = 2,
    right = 3,
    bottom = 4,
    centerVertical = 5,
    centerHorizontal = 6,
}

ccs.SCROLLVIEW_DIR = {
    none = 0,
    vertical = 1,
    horizontal = 2,
    both = 3,
}

ccs.PageViewEventType = {
   turning = 0,  
}

ccs.ListViewEventType = {
    init_child = 0,
    update_child = 1,
}

ccs.ListViewDirection = {
    none = 0,
    vertical = 1,
    horizontal = 2,
}

local cc = cc or {}
cc.TEXT_ALIGNMENT_CENTER = 0x1
cc.TEXT_ALIGNMENT_LEFT  = 0x0
cc.TEXT_ALIGNMENT_RIGHT = 0x2


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
    self._uiLayer = TouchGroup:create()
    self:addChild(self._uiLayer)
end

function UIScene.create()
    local scene = CCScene:create()
    local layer = UIScene.extend(CCLayer:create())
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
    local screenSize = CCDirector:sharedDirector():getWinSize()
    local rootSize = self._layout:getSize()
    -- self._uiLayer:setPosition(ccp((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = tolua.cast((self._uiLayer:getWidgetByName("root_Panel")), "Layout")    
    local sceneTitle = tolua.cast(UIHelper:seekWidgetByName(root, "UItest"), "Label")

    local function toGUIEditorTestScene(sender,eventType)
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  tolua.cast(UIHelper:seekWidgetByName(root, "back"), "Label")
    back_label:addTouchEventListener(toGUIEditorTestScene)

    local function touchEvent(sender,eventType)
        if eventType == ccs.TouchEventType.began then
            self._displayValueLabel:setText("Touch Down")
        elseif eventType == ccs.TouchEventType.moved then
            self._displayValueLabel:setText("Touch Move")
        elseif eventType == ccs.TouchEventType.ended then
            self._displayValueLabel:setText("Touch Up")
        elseif eventType == ccs.TouchEventType.canceled then
            self._displayValueLabel:setText("Touch Cancelled")
        end
    end
    
    local button = tolua.cast(UIHelper:seekWidgetByName(root, "Button_123"), "Button")
    button:addTouchEventListener(touchEvent)
    
    local title_button = tolua.cast(UIHelper:seekWidgetByName(root, "Button_126"), "Button")
    title_button:addTouchEventListener(touchEvent)
    
    local scale9_button = tolua.cast(UIHelper:seekWidgetByName(root, "Button_129"), "Button")
    scale9_button:addTouchEventListener(touchEvent)
end

function UIButtonTest:initExtend()
    self:init()
    self._layout = tolua.cast(GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UIButton_Editor/UIButton_Editor_1.json"), "Layout")
    self._uiLayer:addWidget(self._layout)
    self:configureGUIScene()

    function switchLoadMethod(tag,sender)
        local item = tolua.cast(sender,"CCMenuItemToggle")
        if item:getSelectedIndex() == 0 then
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end
            
            self._layout = GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UIButton_Editor/UIButton_Editor_1.json")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        else
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end

            self._layout = GUIReader:shareReader():widgetFromBinaryFile("cocosui/UIEditorTest/UIButton_Editor/UIButton_Editor_1.csb")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        end
    end

    local loadJsonItem = CCMenuItemFont:create("Switch to Binary Load")
    loadJsonItem:setTag(1)
    local loadBinaryItem =  CCMenuItemFont:create("Switch to Json Load")
    loadBinaryItem:setTag(2)
    local switchitem = CCMenuItemToggle:create(loadJsonItem)
    switchitem:addSubItem(loadBinaryItem)
    switchitem:setPosition(ccp(VisibleRect:right().x - 150, VisibleRect:top().y - 50))
    switchitem:registerScriptTapHandler(switchLoadMethod)
    switchitem:setSelectedIndex(0)
    local menu = CCMenu:create()
    menu:addChild(switchitem)
    menu:setPosition(ccp(0, 0))
    self._uiLayer:addChild(menu, 1)

    -- local widgetSize = self._widget:getSize()
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(ccp(self._layout:getSize().width / 2,
                                            self._layout:getSize().height - self._displayValueLabel:getSize().height * 2))
    self._uiLayer:addWidget(self._displayValueLabel)
end

function UIButtonTest.create()
    local scene = CCScene:create()
    local layer = UIButtonTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    CCDirector:sharedDirector():replaceScene(scene) 
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
    local screenSize = CCDirector:sharedDirector():getWinSize()
    local rootSize = self._layout:getSize()
    --self._uiLayer:setPosition(ccp((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = tolua.cast((self._uiLayer:getWidgetByName("root_Panel")), "Layout")    
    local sceneTitle = tolua.cast(UIHelper:seekWidgetByName(root, "UItest"), "Label")

    local function toGUIEditorTestScene(sender,eventType)
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  tolua.cast(UIHelper:seekWidgetByName(root, "back"), "Label")
    back_label:addTouchEventListener(toGUIEditorTestScene)

    local function selectedStateEvent(sender,eventType)
        if eventType == ccs.CheckBoxEventType.selected then
            self._displayValueLabel:setText("Selected")
        elseif eventType == ccs.CheckBoxEventType.unselected then
            self._displayValueLabel:setText("Unselected")
        end
    end

    local checkbox = tolua.cast(UIHelper:seekWidgetByName(root, "CheckBox_540"), "CheckBox")
    checkbox:addEventListenerCheckBox(selectedStateEvent)
end

function UICheckBoxEditorTest:initExtend()
    self:init()
    self._layout = tolua.cast(GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UICheckBox_Editor/ui_checkbox_editor_1.json"), "Layout")
    self._uiLayer:addWidget(self._layout)
    self:configureGUIScene()

    function switchLoadMethod(tag,sender)
        local item = tolua.cast(sender,"CCMenuItemToggle")
        if item:getSelectedIndex() == 0 then
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end
            
            self._layout = GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UICheckBox_Editor/ui_checkbox_editor_1.json")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        else
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end

            self._layout = GUIReader:shareReader():widgetFromBinaryFile("cocosui/UIEditorTest/UICheckBox_Editor/ui_checkbox_editor_1.csb")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        end
    end

    local loadJsonItem = CCMenuItemFont:create("Switch to Binary Load")
    loadJsonItem:setTag(1)
    local loadBinaryItem =  CCMenuItemFont:create("Switch to Json Load")
    loadBinaryItem:setTag(2)
    local switchitem = CCMenuItemToggle:create(loadJsonItem)
    switchitem:addSubItem(loadBinaryItem)
    switchitem:setPosition(ccp(VisibleRect:right().x - 150, VisibleRect:top().y - 50))
    switchitem:registerScriptTapHandler(switchLoadMethod)
    switchitem:setSelectedIndex(0)
    local menu = CCMenu:create()
    menu:addChild(switchitem)
    menu:setPosition(ccp(0, 0))
    self._uiLayer:addChild(menu, 1)

    -- local widgetSize = self._widget:getSize()
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(ccp(self._layout:getSize().width / 2,
                                            self._layout:getSize().height - self._displayValueLabel:getSize().height * 2))
    self._uiLayer:addWidget(self._displayValueLabel)
end

function UICheckBoxEditorTest.create()
    local scene = CCScene:create()
    local layer = UICheckBoxEditorTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    CCDirector:sharedDirector():replaceScene(scene) 
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
    local screenSize = CCDirector:sharedDirector():getWinSize()
    local rootSize = self._layout:getSize()
    --self._uiLayer:setPosition(ccp((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = tolua.cast((self._uiLayer:getWidgetByName("root_Panel")), "Layout")    
    local sceneTitle = tolua.cast(UIHelper:seekWidgetByName(root, "UItest"), "Label")

    local function toGUIEditorTestScene(sender,eventType)
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  tolua.cast(UIHelper:seekWidgetByName(root, "back"), "Label")
    back_label:addTouchEventListener(toGUIEditorTestScene)

    local function sliderEvent(sender,eventType)
        if eventType == ccs.SliderEventType.percent_changed then
            local slider = tolua.cast(sender,"Slider")
            local percent = "Percent " .. slider:getPercent()
            self._displayValueLabel:setText(percent)
        end
    end

    local slider = tolua.cast(UIHelper:seekWidgetByName(root, "Slider_738"), "Slider")
    slider:addEventListenerSlider(sliderEvent)

    local scaleSlider = tolua.cast(UIHelper:seekWidgetByName(root, "Slider_740"), "Slider")
    scaleSlider:addEventListenerSlider(sliderEvent)
end

function UISliderEditorTest:initExtend()
    self:init()
    self._layout = tolua.cast(GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UISlider_Editor/ui_slider_editor_1.json"), "Layout")
    self._uiLayer:addWidget(self._layout)
    self:configureGUIScene()

    function switchLoadMethod(tag,sender)
        local item = tolua.cast(sender,"CCMenuItemToggle")
        if item:getSelectedIndex() == 0 then
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end
            
            self._layout = GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UISlider_Editor/ui_slider_editor_1.json")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        else
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end

            self._layout = GUIReader:shareReader():widgetFromBinaryFile("cocosui/UIEditorTest/UISlider_Editor/ui_slider_editor_1.csb")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        end
    end

    local loadJsonItem = CCMenuItemFont:create("Switch to Binary Load")
    loadJsonItem:setTag(1)
    local loadBinaryItem =  CCMenuItemFont:create("Switch to Json Load")
    loadBinaryItem:setTag(2)
    local switchitem = CCMenuItemToggle:create(loadJsonItem)
    switchitem:addSubItem(loadBinaryItem)
    switchitem:setPosition(ccp(VisibleRect:right().x - 150, VisibleRect:top().y - 50))
    switchitem:registerScriptTapHandler(switchLoadMethod)
    switchitem:setSelectedIndex(0)
    local menu = CCMenu:create()
    menu:addChild(switchitem)
    menu:setPosition(ccp(0, 0))
    self._uiLayer:addChild(menu, 1)

    -- local widgetSize = self._widget:getSize()
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(ccp(self._layout:getSize().width / 2,
                                            self._layout:getSize().height - self._displayValueLabel:getSize().height * 2))
    self._uiLayer:addWidget(self._displayValueLabel)
end

function UISliderEditorTest.create()
    local scene = CCScene:create()
    local layer = UISliderEditorTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    CCDirector:sharedDirector():replaceScene(scene) 
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
    local screenSize = CCDirector:sharedDirector():getWinSize()
    local rootSize = self._layout:getSize()
    --self._uiLayer:setPosition(ccp((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = tolua.cast((self._uiLayer:getWidgetByName("root_Panel")), "Layout")    
    local sceneTitle = tolua.cast(UIHelper:seekWidgetByName(root, "UItest"), "Label")

    local function toGUIEditorTestScene(sender,eventType)
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  tolua.cast(UIHelper:seekWidgetByName(root, "back"), "Label")
    back_label:addTouchEventListener(toGUIEditorTestScene)
end

function UIImageViewEditorTest:initExtend()
    self:init()
    self._layout = tolua.cast(GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UIImageView_Editor/ui_ImageView_editor_1.json"), "Layout")
    self._uiLayer:addWidget(self._layout)
    self:configureGUIScene()

    function switchLoadMethod(tag,sender)
        local item = tolua.cast(sender,"CCMenuItemToggle")
        if item:getSelectedIndex() == 0 then
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end
            
            self._layout = GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UIImageView_Editor/ui_ImageView_editor_1.json")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        else
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end

            self._layout = GUIReader:shareReader():widgetFromBinaryFile("cocosui/UIEditorTest/UIImageView_Editor/ui_ImageView_editor_1.csb")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        end
    end

    local loadJsonItem = CCMenuItemFont:create("Switch to Binary Load")
    loadJsonItem:setTag(1)
    local loadBinaryItem =  CCMenuItemFont:create("Switch to Json Load")
    loadBinaryItem:setTag(2)
    local switchitem = CCMenuItemToggle:create(loadJsonItem)
    switchitem:addSubItem(loadBinaryItem)
    switchitem:setPosition(ccp(VisibleRect:right().x - 150, VisibleRect:top().y - 50))
    switchitem:registerScriptTapHandler(switchLoadMethod)
    switchitem:setSelectedIndex(0)
    local menu = CCMenu:create()
    menu:addChild(switchitem)
    menu:setPosition(ccp(0, 0))
    self._uiLayer:addChild(menu, 1)

    -- local widgetSize = self._widget:getSize()
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(ccp(self._layout:getSize().width / 2,
                                            self._layout:getSize().height - self._displayValueLabel:getSize().height * 2))
    self._uiLayer:addWidget(self._displayValueLabel)
end

function UIImageViewEditorTest.create()
    local scene = CCScene:create()
    local layer = UIImageViewEditorTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    CCDirector:sharedDirector():replaceScene(scene) 
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
    local screenSize = CCDirector:sharedDirector():getWinSize()
    local rootSize = self._layout:getSize()
    --self._uiLayer:setPosition(ccp((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = tolua.cast((self._uiLayer:getWidgetByName("root_Panel")), "Layout")    
    local sceneTitle = tolua.cast(UIHelper:seekWidgetByName(root, "UItest"), "Label")

    local function toGUIEditorTestScene(sender,eventType)
        self:unscheduleUpdate()
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  tolua.cast(UIHelper:seekWidgetByName(root, "back"), "Label")
    back_label:addTouchEventListener(toGUIEditorTestScene)

    local loadingBar_left_to_right = tolua.cast(UIHelper:seekWidgetByName(root, "LoadingBar_856"), "LoadingBar")
    loadingBar_left_to_right:setPercent(0)
    
    local loadingBar_right_to_left =tolua.cast(UIHelper:seekWidgetByName(root, "LoadingBar_857"), "LoadingBar")
    loadingBar_right_to_left:setPercent(0)
end

function LoadingBarEditorTest:initExtend()
    self:init()
    self._layout = tolua.cast(GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UILoadingBar_Editor/ui_loadingbar_editor_1.json"), "Layout")
    self._uiLayer:addWidget(self._layout)
    self:configureGUIScene()

    function switchLoadMethod(tag,sender)
        local item = tolua.cast(sender,"CCMenuItemToggle")
        if item:getSelectedIndex() == 0 then
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end
            
            self._layout = GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UILoadingBar_Editor/ui_loadingbar_editor_1.json")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        else
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end

            self._layout = GUIReader:shareReader():widgetFromBinaryFile("cocosui/UIEditorTest/UILoadingBar_Editor/ui_loadingbar_editor_1.csb")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        end
    end

    local loadJsonItem = CCMenuItemFont:create("Switch to Binary Load")
    loadJsonItem:setTag(1)
    local loadBinaryItem =  CCMenuItemFont:create("Switch to Json Load")
    loadBinaryItem:setTag(2)
    local switchitem = CCMenuItemToggle:create(loadJsonItem)
    switchitem:addSubItem(loadBinaryItem)
    switchitem:setPosition(ccp(VisibleRect:right().x - 150, VisibleRect:top().y - 50))
    switchitem:registerScriptTapHandler(switchLoadMethod)
    switchitem:setSelectedIndex(0)
    local menu = CCMenu:create()
    menu:addChild(switchitem)
    menu:setPosition(ccp(0, 0))
    self._uiLayer:addChild(menu, 1)

    -- local widgetSize = self._widget:getSize()
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(ccp(self._layout:getSize().width / 2,
                                            self._layout:getSize().height - self._displayValueLabel:getSize().height * 2))
    self._uiLayer:addWidget(self._displayValueLabel)
    self._count = 0

    local function update(delta)
        self._count = self._count + 1
        if self._count > 100 then
            self._count = 0
        end

        local root = tolua.cast(self._uiLayer:getWidgetByName("root_Panel"),"Layout")
    
        local loadingBar_left_to_right = tolua.cast(UIHelper:seekWidgetByName(root, "LoadingBar_856"), "LoadingBar")
        loadingBar_left_to_right:setPercent(self._count)
    
        local loadingBar_right_to_left = tolua.cast(UIHelper:seekWidgetByName(root, "LoadingBar_857"), "LoadingBar")
        loadingBar_right_to_left:setPercent(self._count)
    end

    self:scheduleUpdateWithPriorityLua(update, 0)
end

function LoadingBarEditorTest.create()
    local scene = CCScene:create()
    local layer = LoadingBarEditorTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    CCDirector:sharedDirector():replaceScene(scene) 
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
    local screenSize = CCDirector:sharedDirector():getWinSize()
    local rootSize = self._layout:getSize()
    --self._uiLayer:setPosition(ccp((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = tolua.cast((self._uiLayer:getWidgetByName("root_Panel")), "Layout")    
    local sceneTitle = tolua.cast(UIHelper:seekWidgetByName(root, "UItest"), "Label")

    local function toGUIEditorTestScene(sender,eventType)
        self:unscheduleUpdate()
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  tolua.cast(UIHelper:seekWidgetByName(root, "back"), "Label")
    back_label:addTouchEventListener(toGUIEditorTestScene)
end

function LabelAtalsEditorTest:initExtend()
    self:init()
    self._layout = tolua.cast(GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UILabelAtlas_Editor/ui_labelatlas_editor_1.json"), "Layout")
    self._uiLayer:addWidget(self._layout)
    self:configureGUIScene()

    function switchLoadMethod(tag,sender)
        local item = tolua.cast(sender,"CCMenuItemToggle")
        if item:getSelectedIndex() == 0 then
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end
            
            self._layout = GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UILabelAtlas_Editor/ui_labelatlas_editor_1.json")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        else
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end

            self._layout = GUIReader:shareReader():widgetFromBinaryFile("cocosui/UIEditorTest/UILabelAtlas_Editor/ui_labelatlas_editor_1.csb")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        end
    end

    local loadJsonItem = CCMenuItemFont:create("Switch to Binary Load")
    loadJsonItem:setTag(1)
    local loadBinaryItem =  CCMenuItemFont:create("Switch to Json Load")
    loadBinaryItem:setTag(2)
    local switchitem = CCMenuItemToggle:create(loadJsonItem)
    switchitem:addSubItem(loadBinaryItem)
    switchitem:setPosition(ccp(VisibleRect:right().x - 150, VisibleRect:top().y - 50))
    switchitem:registerScriptTapHandler(switchLoadMethod)
    switchitem:setSelectedIndex(0)
    local menu = CCMenu:create()
    menu:addChild(switchitem)
    menu:setPosition(ccp(0, 0))
    self._uiLayer:addChild(menu, 1)

    -- local widgetSize = self._widget:getSize()
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(ccp(self._layout:getSize().width / 2,
                                            self._layout:getSize().height - self._displayValueLabel:getSize().height * 2))
    self._uiLayer:addWidget(self._displayValueLabel)
end

function LabelAtalsEditorTest.create()
    local scene = CCScene:create()
    local layer = LabelAtalsEditorTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    CCDirector:sharedDirector():replaceScene(scene) 
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
    local screenSize = CCDirector:sharedDirector():getWinSize()
    local rootSize = self._layout:getSize()
    --self._uiLayer:setPosition(ccp((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = tolua.cast((self._uiLayer:getWidgetByName("root_Panel")), "Layout")    
    local sceneTitle = tolua.cast(UIHelper:seekWidgetByName(root, "UItest"), "Label")

    local function toGUIEditorTestScene(sender,eventType)
        self:unscheduleUpdate()
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  tolua.cast(UIHelper:seekWidgetByName(root, "back"), "Label")
    back_label:addTouchEventListener(toGUIEditorTestScene)
end

function LabelEditorTest:initExtend()
    self:init()
    self._layout = tolua.cast(GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UILabel_Editor/ui_label_editor_1.json"), "Layout")
    self._uiLayer:addWidget(self._layout)
    self:configureGUIScene()

    function switchLoadMethod(tag,sender)
        local item = tolua.cast(sender,"CCMenuItemToggle")
        if item:getSelectedIndex() == 0 then
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end
            
            self._layout = GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UILabel_Editor/ui_label_editor_1.json")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        else
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end

            self._layout = GUIReader:shareReader():widgetFromBinaryFile("cocosui/UIEditorTest/UILabel_Editor/ui_label_editor_1.csb")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        end
    end

    local loadJsonItem = CCMenuItemFont:create("Switch to Binary Load")
    loadJsonItem:setTag(1)
    local loadBinaryItem =  CCMenuItemFont:create("Switch to Json Load")
    loadBinaryItem:setTag(2)
    local switchitem = CCMenuItemToggle:create(loadJsonItem)
    switchitem:addSubItem(loadBinaryItem)
    switchitem:setPosition(ccp(VisibleRect:right().x - 150, VisibleRect:top().y - 50))
    switchitem:registerScriptTapHandler(switchLoadMethod)
    switchitem:setSelectedIndex(0)
    local menu = CCMenu:create()
    menu:addChild(switchitem)
    menu:setPosition(ccp(0, 0))
    self._uiLayer:addChild(menu, 1)

    -- local widgetSize = self._widget:getSize()
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(ccp(self._layout:getSize().width / 2,
                                            self._layout:getSize().height - self._displayValueLabel:getSize().height * 2))
    self._uiLayer:addWidget(self._displayValueLabel)
end

function LabelEditorTest.create()
    local scene = CCScene:create()
    local layer = LabelEditorTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    CCDirector:sharedDirector():replaceScene(scene) 
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
    local screenSize = CCDirector:sharedDirector():getWinSize()
    local rootSize = self._layout:getSize()
    --self._uiLayer:setPosition(ccp((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = tolua.cast((self._uiLayer:getWidgetByName("root_Panel")), "Layout")    
    local sceneTitle = tolua.cast(UIHelper:seekWidgetByName(root, "UItest"), "Label")

    local function toGUIEditorTestScene(sender,eventType)
        self:unscheduleUpdate()
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  tolua.cast(UIHelper:seekWidgetByName(root, "back"), "Label")
    back_label:addTouchEventListener(toGUIEditorTestScene)
end

function LabelBMFontEditorTest:initExtend()
    self:init()
    self._layout = tolua.cast(GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UILabelBMFont_Editor/ui_labelbmfont_editor_1.json"), "Layout")
    self._uiLayer:addWidget(self._layout)
    self:configureGUIScene()

    function switchLoadMethod(tag,sender)
        local item = tolua.cast(sender,"CCMenuItemToggle")
        if item:getSelectedIndex() == 0 then
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end
            
            self._layout = GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UILabelBMFont_Editor/ui_labelbmfont_editor_1.json")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        else
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end

            self._layout = GUIReader:shareReader():widgetFromBinaryFile("cocosui/UIEditorTest/UILabelBMFont_Editor/ui_labelbmfont_editor_1.csb")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        end
    end

    local loadJsonItem = CCMenuItemFont:create("Switch to Binary Load")
    loadJsonItem:setTag(1)
    local loadBinaryItem =  CCMenuItemFont:create("Switch to Json Load")
    loadBinaryItem:setTag(2)
    local switchitem = CCMenuItemToggle:create(loadJsonItem)
    switchitem:addSubItem(loadBinaryItem)
    switchitem:setPosition(ccp(VisibleRect:right().x - 150, VisibleRect:top().y - 50))
    switchitem:registerScriptTapHandler(switchLoadMethod)
    switchitem:setSelectedIndex(0)
    local menu = CCMenu:create()
    menu:addChild(switchitem)
    menu:setPosition(ccp(0, 0))
    self._uiLayer:addChild(menu, 1)

    -- local widgetSize = self._widget:getSize()
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(ccp(self._layout:getSize().width / 2,
                                            self._layout:getSize().height - self._displayValueLabel:getSize().height * 2))
    self._uiLayer:addWidget(self._displayValueLabel)
end

function LabelBMFontEditorTest.create()
    local scene = CCScene:create()
    local layer = LabelBMFontEditorTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    CCDirector:sharedDirector():replaceScene(scene) 
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
    local screenSize = CCDirector:sharedDirector():getWinSize()
    local rootSize = self._layout:getSize()
    --self._uiLayer:setPosition(ccp((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = tolua.cast((self._uiLayer:getWidgetByName("root_Panel")), "Layout")    
    local sceneTitle = tolua.cast(UIHelper:seekWidgetByName(root, "UItest"), "Label")

    local function toGUIEditorTestScene(sender,eventType)
        self:unscheduleUpdate()
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  tolua.cast(UIHelper:seekWidgetByName(root, "back"), "Label")
    back_label:addTouchEventListener(toGUIEditorTestScene)

    local function textFieldEvent(sender, eventType)
        if eventType == ccs.TextFiledEventType.attach_with_ime then
            self._displayValueLabel:setText("attach with IME")
        elseif eventType == ccs.TextFiledEventType.detach_with_ime then
            self._displayValueLabel:setText("detach with IME")
        elseif eventType == ccs.TextFiledEventType.insert_text then
            self._displayValueLabel:setText("insert words")
        elseif eventType == ccs.TextFiledEventType.delete_backward then
            self._displayValueLabel:setText("delete word")
        end
    end

    local textField_normal = tolua.cast(UIHelper:seekWidgetByName(root, "TextField_1109"), "TextField")
    textField_normal:addEventListenerTextField(textFieldEvent)
    
    local textField_max_character = tolua.cast(UIHelper:seekWidgetByName(root, "TextField_1110"), "TextField")
    textField_max_character:addEventListenerTextField(textFieldEvent)
    
    local textField_password = tolua.cast(UIHelper:seekWidgetByName(root, "TextField_1107"), "TextField")
    textField_password:addEventListenerTextField(textFieldEvent)
end

function TextFieldEditorTest:initExtend()
    self:init()
    self._layout = tolua.cast(GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UITextField_Editor/ui_textfield_editor_1.json"), "Layout")
    self._uiLayer:addWidget(self._layout)
    self:configureGUIScene()

    function switchLoadMethod(tag,sender)
        local item = tolua.cast(sender,"CCMenuItemToggle")
        if item:getSelectedIndex() == 0 then
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end
            
            self._layout = GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UITextField_Editor/ui_textfield_editor_1.json")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        else
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end

            self._layout = GUIReader:shareReader():widgetFromBinaryFile("cocosui/UIEditorTest/UITextField_Editor/ui_textfield_editor_1.csb")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        end
    end

    local loadJsonItem = CCMenuItemFont:create("Switch to Binary Load")
    loadJsonItem:setTag(1)
    local loadBinaryItem =  CCMenuItemFont:create("Switch to Json Load")
    loadBinaryItem:setTag(2)
    local switchitem = CCMenuItemToggle:create(loadJsonItem)
    switchitem:addSubItem(loadBinaryItem)
    switchitem:setPosition(ccp(VisibleRect:right().x - 150, VisibleRect:top().y - 50))
    switchitem:registerScriptTapHandler(switchLoadMethod)
    switchitem:setSelectedIndex(0)
    local menu = CCMenu:create()
    menu:addChild(switchitem)
    menu:setPosition(ccp(0, 0))
    self._uiLayer:addChild(menu, 1)

    -- local widgetSize = self._widget:getSize()
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(ccp(self._layout:getSize().width / 2,
                                            self._layout:getSize().height - self._displayValueLabel:getSize().height * 2))
    self._uiLayer:addWidget(self._displayValueLabel)
end

function TextFieldEditorTest.create()
    local scene = CCScene:create()
    local layer = TextFieldEditorTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    CCDirector:sharedDirector():replaceScene(scene) 
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
    local screenSize = CCDirector:sharedDirector():getWinSize()
    local rootSize = self._layout:getSize()
    --self._uiLayer:setPosition(ccp((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = tolua.cast((self._uiLayer:getWidgetByName("root_Panel")), "Layout")    
    local sceneTitle = tolua.cast(UIHelper:seekWidgetByName(root, "UItest"), "Label")

    local function toGUIEditorTestScene(sender,eventType)
        self:unscheduleUpdate()
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  tolua.cast(UIHelper:seekWidgetByName(root, "back"), "Label")
    back_label:addTouchEventListener(toGUIEditorTestScene)

    -- local left_button = Button:create()
    -- left_button:loadTextures("Images/b1.png", "Images/b2.png", "")
    -- left_button:setPosition(ccp(self._layout:getSize().width / 2 - left_button:getSize().width,
    --                              left_button:getSize().height))
    -- left_button:setTouchEnabled(true)
    -- left_button:addTouchEventListener(this, toucheventselector(UIScene_Editor:previousCallback))
    -- left_button:setZOrder(_layout:getZOrder() + 1)
    -- self._layout:addChild(left_button)
    
    -- local right_button = Button:create()
    -- right_button:loadTextures("Images/f1.png", "Images/f2.png", "")
    -- right_button:setPosition(ccp(self._layout:getSize().width / 2 + right_button:getSize().width,
    --                               right_button:getSize().height))
    -- right_button:setTouchEnabled(true)
    -- right_button:setZOrder(self._layout:getZOrder() + 1)
    -- right_button:addTouchEventListener(this, toucheventselector(UIScene_Editor:nextCallback))
    -- self._layout:addChild(right_button)
end

function LayoutEditorTest:initExtend()
    self:init()
    self._layout = tolua.cast(GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Editor/ui_layout_editor_1.json"), "Layout")
    self._uiLayer:addWidget(self._layout)
    self:configureGUIScene()

    function switchLoadMethod(tag,sender)
        local item = tolua.cast(sender,"CCMenuItemToggle")
        if item:getSelectedIndex() == 0 then
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end
            
            self._layout = GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Editor/ui_layout_editor_1.json")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        else
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end

            self._layout = GUIReader:shareReader():widgetFromBinaryFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Editor/ui_layout_editor_1.csb")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        end
    end

    local loadJsonItem = CCMenuItemFont:create("Switch to Binary Load")
    loadJsonItem:setTag(1)
    local loadBinaryItem =  CCMenuItemFont:create("Switch to Json Load")
    loadBinaryItem:setTag(2)
    local switchitem = CCMenuItemToggle:create(loadJsonItem)
    switchitem:addSubItem(loadBinaryItem)
    switchitem:setPosition(ccp(VisibleRect:right().x - 150, VisibleRect:top().y - 50))
    switchitem:registerScriptTapHandler(switchLoadMethod)
    switchitem:setSelectedIndex(0)
    local menu = CCMenu:create()
    menu:addChild(switchitem)
    menu:setPosition(ccp(0, 0))
    self._uiLayer:addChild(menu, 1)

    -- local widgetSize = self._widget:getSize()
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(ccp(self._layout:getSize().width / 2,
                                            self._layout:getSize().height - self._displayValueLabel:getSize().height * 2))
    self._uiLayer:addWidget(self._displayValueLabel)
end

function LayoutEditorTest.create()
    local scene = CCScene:create()
    local layer = LayoutEditorTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    CCDirector:sharedDirector():replaceScene(scene) 
end

local function runLayoutEditorTestScene()
    LayoutEditorTest.create()
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
    local screenSize = CCDirector:sharedDirector():getWinSize()
    local rootSize = self._layout:getSize()
    --self._uiLayer:setPosition(ccp((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = tolua.cast((self._uiLayer:getWidgetByName("root_Panel")), "Layout")    
    local sceneTitle = tolua.cast(UIHelper:seekWidgetByName(root, "UItest"), "Label")

    local function toGUIEditorTestScene(sender,eventType)
        self:unscheduleUpdate()
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  tolua.cast(UIHelper:seekWidgetByName(root, "back"), "Label")
    back_label:addTouchEventListener(toGUIEditorTestScene)
end

function ScrollViewEditorTest:initExtend()
    self:init()
    self._layout = tolua.cast(GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UIScrollView_Editor/UIScrollView_Vertical_Editor/ui_scrollview_editor_1.json"), "Layout")
    self._uiLayer:addWidget(self._layout)
    self:configureGUIScene()

    function switchLoadMethod(tag,sender)
        local item = tolua.cast(sender,"CCMenuItemToggle")
        if item:getSelectedIndex() == 0 then
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end
            
            self._layout = GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UIScrollView_Editor/UIScrollView_Vertical_Editor/ui_scrollview_editor_1.json")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        else
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end

            self._layout = GUIReader:shareReader():widgetFromBinaryFile("cocosui/UIEditorTest/UIScrollView_Editor/UIScrollView_Vertical_Editor/ui_scrollview_editor_1.csb")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        end
    end

    local loadJsonItem = CCMenuItemFont:create("Switch to Binary Load")
    loadJsonItem:setTag(1)
    local loadBinaryItem =  CCMenuItemFont:create("Switch to Json Load")
    loadBinaryItem:setTag(2)
    local switchitem = CCMenuItemToggle:create(loadJsonItem)
    switchitem:addSubItem(loadBinaryItem)
    switchitem:setPosition(ccp(VisibleRect:right().x - 150, VisibleRect:top().y - 50))
    switchitem:registerScriptTapHandler(switchLoadMethod)
    switchitem:setSelectedIndex(0)
    local menu = CCMenu:create()
    menu:addChild(switchitem)
    menu:setPosition(ccp(0, 0))
    self._uiLayer:addChild(menu, 1)

    -- local widgetSize = self._widget:getSize()
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(ccp(self._layout:getSize().width / 2,
                                            self._layout:getSize().height - self._displayValueLabel:getSize().height * 2))
    self._uiLayer:addWidget(self._displayValueLabel)
end

function ScrollViewEditorTest.create()
    local scene = CCScene:create()
    local layer = ScrollViewEditorTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    CCDirector:sharedDirector():replaceScene(scene) 
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
    local screenSize = CCDirector:sharedDirector():getWinSize()
    local rootSize = self._layout:getSize()
    --self._uiLayer:setPosition(ccp((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = tolua.cast((self._uiLayer:getWidgetByName("root_Panel")), "Layout")    
    local sceneTitle = tolua.cast(UIHelper:seekWidgetByName(root, "UItest"), "Label")

    local function toGUIEditorTestScene(sender,eventType)
        self:unscheduleUpdate()
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  tolua.cast(UIHelper:seekWidgetByName(root, "back"), "Label")
    back_label:addTouchEventListener(toGUIEditorTestScene)
end

function PageViewEditorTest:initExtend()
    self:init()
    self._layout = tolua.cast(GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UIPageView_Editor/ui_pageview_editor_1.json"), "Layout")
    self._uiLayer:addWidget(self._layout)
    self:configureGUIScene()

    function switchLoadMethod(tag,sender)
        local item = tolua.cast(sender,"CCMenuItemToggle")
        if item:getSelectedIndex() == 0 then
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end
            
            self._layout = GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UIPageView_Editor/ui_pageview_editor_1.json")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        else
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end

            self._layout = GUIReader:shareReader():widgetFromBinaryFile("cocosui/UIEditorTest/UIPageView_Editor/ui_pageview_editor_1.csb")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        end
    end

    local loadJsonItem = CCMenuItemFont:create("Switch to Binary Load")
    loadJsonItem:setTag(1)
    local loadBinaryItem =  CCMenuItemFont:create("Switch to Json Load")
    loadBinaryItem:setTag(2)
    local switchitem = CCMenuItemToggle:create(loadJsonItem)
    switchitem:addSubItem(loadBinaryItem)
    switchitem:setPosition(ccp(VisibleRect:right().x - 150, VisibleRect:top().y - 50))
    switchitem:registerScriptTapHandler(switchLoadMethod)
    switchitem:setSelectedIndex(0)
    local menu = CCMenu:create()
    menu:addChild(switchitem)
    menu:setPosition(ccp(0, 0))
    self._uiLayer:addChild(menu, 1)

    -- local widgetSize = self._widget:getSize()
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(ccp(self._layout:getSize().width / 2,
                                            self._layout:getSize().height - self._displayValueLabel:getSize().height * 2))
    self._uiLayer:addWidget(self._displayValueLabel)
end

function PageViewEditorTest.create()
    local scene = CCScene:create()
    local layer = PageViewEditorTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    CCDirector:sharedDirector():replaceScene(scene) 
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
    local screenSize = CCDirector:sharedDirector():getWinSize()
    local rootSize = self._layout:getSize()
    --self._uiLayer:setPosition(ccp((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = tolua.cast((self._uiLayer:getWidgetByName("root_Panel")), "Layout")    
    local sceneTitle = tolua.cast(UIHelper:seekWidgetByName(root, "UItest"), "Label")

    local function toGUIEditorTestScene(sender,eventType)
        self:unscheduleUpdate()
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  tolua.cast(UIHelper:seekWidgetByName(root, "back"), "Label")
    back_label:addTouchEventListener(toGUIEditorTestScene)

    local listView = tolua.cast(UIHelper:seekWidgetByName(root, "ListView_1214"), "ListView")
    if nil ~= listView then
        print("listView isBounceEnabled ", listView:isBounceEnabled())
    end
end

function ListViewEditorTest:initExtend()
    self:init()
    self._layout = tolua.cast(GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UIListView_Editor/UIListView_Vertical_Editor/ui_listview_editor_1.json"), "Layout")
    self._uiLayer:addWidget(self._layout)
    self:configureGUIScene()

    function switchLoadMethod(tag,sender)
        local item = tolua.cast(sender,"CCMenuItemToggle")
        if item:getSelectedIndex() == 0 then
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end
            
            self._layout = GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UIListView_Editor/UIListView_Vertical_Editor/ui_listview_editor_1.json")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        else
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end

            self._layout = GUIReader:shareReader():widgetFromBinaryFile("cocosui/UIEditorTest/UIListView_Editor/UIListView_Vertical_Editor/ui_listview_editor_1.csb")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        end
    end

    local loadJsonItem = CCMenuItemFont:create("Switch to Binary Load")
    loadJsonItem:setTag(1)
    local loadBinaryItem =  CCMenuItemFont:create("Switch to Json Load")
    loadBinaryItem:setTag(2)
    local switchitem = CCMenuItemToggle:create(loadJsonItem)
    switchitem:addSubItem(loadBinaryItem)
    switchitem:setPosition(ccp(VisibleRect:right().x - 150, VisibleRect:top().y - 50))
    switchitem:registerScriptTapHandler(switchLoadMethod)
    switchitem:setSelectedIndex(0)
    local menu = CCMenu:create()
    menu:addChild(switchitem)
    menu:setPosition(ccp(0, 0))
    self._uiLayer:addChild(menu, 1)

    -- local widgetSize = self._widget:getSize()
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(ccp(self._layout:getSize().width / 2,
                                            self._layout:getSize().height - self._displayValueLabel:getSize().height * 2))
    self._uiLayer:addWidget(self._displayValueLabel)
end

function ListViewEditorTest.create()
    local scene = CCScene:create()
    local layer = ListViewEditorTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    CCDirector:sharedDirector():replaceScene(scene) 
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
    local screenSize = CCDirector:sharedDirector():getWinSize()
    local rootSize = self._layout:getSize()
    --self._uiLayer:setPosition(ccp((screenSize.width - rootSize.width) / 2, (screenSize.height - rootSize.height) / 2))
    
    local root = tolua.cast((self._uiLayer:getWidgetByName("root_Panel")), "Layout")    
    local sceneTitle = tolua.cast(UIHelper:seekWidgetByName(root, "UItest"), "Label")

    local function toGUIEditorTestScene(sender,eventType)
        self:unscheduleUpdate()
        runCocoStudioUIEditorTestScene()
    end
    local back_label =  tolua.cast(UIHelper:seekWidgetByName(root, "back"), "Label")
    back_label:addTouchEventListener(toGUIEditorTestScene)

    
    local widget = Widget:create()
    widget:setPosition(ccp(rootSize.width / 2.0, rootSize.height / 2.0))
    widget:setZOrder(self._layout:getZOrder() + 1)
    self._layout:addChild(widget)
    
    local sprite = CCSprite:create("cocosui/ccicon.png")
    widget:addNode(sprite)
end

function WidgetAddNodeEditorTest:initExtend()
    self:init()
    self._layout = tolua.cast(GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UIWidgetAddNode_Editor/ui_widget_add_node_editor.json"), "Layout")
    self._uiLayer:addWidget(self._layout)
    self:configureGUIScene()

    function switchLoadMethod(tag,sender)
        local item = tolua.cast(sender,"CCMenuItemToggle")
        if item:getSelectedIndex() == 0 then
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end
            
            self._layout = GUIReader:shareReader():widgetFromJsonFile("cocosui/UIEditorTest/UIWidgetAddNode_Editor/ui_widget_add_node_editor.json")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        else
            if self._layout ~= nil then
                self._layout:removeFromParentAndCleanup(true)
            end

            self._layout = GUIReader:shareReader():widgetFromBinaryFile("cocosui/UIEditorTest/UIWidgetAddNode_Editor/ui_widget_add_node_editor.csb")
            self._uiLayer:addWidget(self._layout)

            self:configureGUIScene()
        end
    end

    local loadJsonItem = CCMenuItemFont:create("Switch to Binary Load")
    loadJsonItem:setTag(1)
    local loadBinaryItem =  CCMenuItemFont:create("Switch to Json Load")
    loadBinaryItem:setTag(2)
    local switchitem = CCMenuItemToggle:create(loadJsonItem)
    switchitem:addSubItem(loadBinaryItem)
    switchitem:setPosition(ccp(VisibleRect:right().x - 150, VisibleRect:top().y - 50))
    switchitem:registerScriptTapHandler(switchLoadMethod)
    switchitem:setSelectedIndex(0)
    local menu = CCMenu:create()
    menu:addChild(switchitem)
    menu:setPosition(ccp(0, 0))
    self._uiLayer:addChild(menu, 1)

    -- local widgetSize = self._widget:getSize()
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(ccp(self._layout:getSize().width / 2,
                                            self._layout:getSize().height - self._displayValueLabel:getSize().height * 2))
    self._uiLayer:addWidget(self._displayValueLabel)
end

function WidgetAddNodeEditorTest.create()
    local scene = CCScene:create()
    local layer = WidgetAddNodeEditorTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    CCDirector:sharedDirector():replaceScene(scene) 
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
    local scene = CocoStudioUIEditorTestScene.extend(CCScene:create())
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
    local index = sender:getZOrder() - ITEM_TAG_BASIC
    UIEditorTestItemNames[index].testScene()
end

function CocoStudioUIEditorTestLayer:createMenu()

    local winSize = CCDirector:sharedDirector():getWinSize()

    local menu = CCMenu:create()
    menu:setPosition(CCPoint(0,0))
    CCMenuItemFont:setFontName("Arial")
    CCMenuItemFont:setFontSize(24)

    for i = 1, table.getn(UIEditorTestItemNames) do
        local menuItem = CCMenuItemFont:create(UIEditorTestItemNames[i].itemTitle)
        menuItem:setPosition(CCPoint(winSize.width / 2, winSize.height - (i + 1) * LINE_SPACE))
        menuItem:registerScriptTapHandler(CocoStudioUIEditorTestLayer.onMenuCallback)
        menu:addChild(menuItem, ITEM_TAG_BASIC + i)
    end

    self:addChild(menu)

    -- handling touch events
    local function onTouchBegan(x, y)
        BeginPos = {x = x, y = y}
        -- CCTOUCHBEGAN event must return true
        return true
    end

    local function onTouchMoved(x, y)
        local nMoveY = y - BeginPos.y
        local curPosx, curPosy = menu:getPosition()
        local nextPosy = curPosy + nMoveY
        local winSize = CCDirector:sharedDirector():getWinSize()
        if nextPosy < 0 then
            menu:setPosition(0, 0)
            return
        end

        if nextPosy > ((#UIEditorTestItemNames + 1) * LINE_SPACE - winSize.height) then
            menu:setPosition(0, ((#UIEditorTestItemNames + 1) * LINE_SPACE - winSize.height))
            return
        end

        menu:setPosition(curPosx, nextPosy)
        BeginPos = {x = x, y = y}
        CurPos = {x = curPosx, y = nextPosy}
    end

    local function onTouch(eventType, x, y)
        if eventType == "began" then
            return onTouchBegan(x, y)
        elseif eventType == "moved" then
            return onTouchMoved(x, y)
        end
    end

    self:setTouchEnabled(true)
    self:registerScriptTouchHandler(onTouch)
end

function CocoStudioUIEditorTestLayer.create()
    local layer = CocoStudioUIEditorTestLayer.extend(CCLayer:create())

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
    CCDirector:sharedDirector():replaceScene(newScene)
end