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

local guiSceneManager =  {}
guiSceneManager.currentUISceneIdx = 1

local UIScene = class("UIScene")
UIScene.__index = UIScene
UIScene._uiLayer= nil
UIScene._widget = nil
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

    self._widget = GUIReader:shareReader():widgetFromJsonFile("cocosui/UITest/UITest.json")
    self._uiLayer:addWidget(self._widget)

    self._sceneTitle = self._uiLayer:getWidgetByName("UItest")

    local back_label = self._uiLayer:getWidgetByName("back")
    back_label:setVisible(false)

    local function previousCallback(sender, eventType)
        if eventType == ccs.TouchEventType.ended then
            self._uiLayer:removeFromParentAndCleanup(true)
            CCDirector:sharedDirector():replaceScene(guiSceneManager.previousUIScene())
        end
    end

    local left_button = self._uiLayer:getWidgetByName("left_Button")
    left_button:addTouchEventListener(previousCallback)

    local function restartCallback(sender, eventType)
         if eventType == ccs.TouchEventType.ended then
             self._uiLayer:removeFromParentAndCleanup(true)
             CCDirector:sharedDirector():replaceScene(guiSceneManager.currentUIScene())
         end
    end

    local middle_button = self._uiLayer:getWidgetByName("middle_Button")
    middle_button:addTouchEventListener(restartCallback)

    local function nextCallback(sender, eventType)
        if eventType == ccs.TouchEventType.ended then
            self._uiLayer:removeFromParentAndCleanup(true)
            CCDirector:sharedDirector():replaceScene(guiSceneManager.nextUIScene())
        end
    end

    local right_button = self._uiLayer:getWidgetByName("right_Button")
    right_button:addTouchEventListener(nextCallback)

    local function menuCloseCallback( sender,eventType)
        if eventType == ccs.TouchEventType.ended then
            self._uiLayer:removeFromParentAndCleanup(true)
            local scene = CocoStudioTest()
            if scene ~= nil then
                CCDirector:sharedDirector():replaceScene(scene)
            end
        end
    end

    local winSize = CCDirector:sharedDirector():getWinSize()
    local scale   = winSize.height / 320
    self._uiLayer:setAnchorPoint(ccp(0,0))
    self._uiLayer:setScale(scale)
    self._uiLayer:setPosition(ccp((winSize.width - 480 * scale) / 2, (winSize.height - 320 * scale) / 2))

    local backMenuLabel = Label:create()
    backMenuLabel:setText("Back")
    backMenuLabel:setFontSize(20)
    backMenuLabel:setTouchScaleChangeEnabled(true)
    backMenuLabel:setPosition(CCPoint(430,30))
    backMenuLabel:setTouchEnabled(true)
    backMenuLabel:addTouchEventListener(menuCloseCallback)
    self._uiLayer:addWidget(backMenuLabel) 
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

function UIButtonTest:initExtend()
    self:init()

    local widgetSize = self._widget:getSize()
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addWidget(self._displayValueLabel)        
        
    local alert = Label:create()
    alert:setText("Button")
    alert:setFontName(getFont())
    alert:setFontSize(30)        
    alert:setColor(ccc3(159, 168, 176))                
        
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)        
    
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
    local button = Button:create()
    button:setTouchEnabled(true)
    button:loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "")
    button:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0))        
    button:addTouchEventListener(touchEvent)
    self._uiLayer:addWidget(button)
end

function UIButtonTest.create()
    local scene = CCScene:create()
    local layer = UIButtonTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene   
end


local UIButtonScale9Test = class("UIButtonScale9Test",UIScene)
UIButtonScale9Test._displayValueLabel = nil

function UIButtonScale9Test.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIButtonScale9Test)
    return target
end

function UIButtonScale9Test:initExtend()

    self:init()

    local widgetSize = self._widget:getSize()
        
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addWidget(self._displayValueLabel)
        
    local alert = Label:create()
    alert:setText("Button scale9 render")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)

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
        
    local button = Button:create()
    button:setTouchEnabled(true)
    button:setScale9Enabled(true)
    button:loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "")
    button:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0))
    button:setSize(CCSize(150, button:getContentSize().height * 1.5))
    button:addTouchEventListener(touchEvent)
    self._uiLayer:addWidget(button)
end

function UIButtonScale9Test.create()
    local scene = CCScene:create()
    local layer = UIButtonScale9Test.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene 
end

local UIButtonPressedActionTest = class("UIButtonPressedActionTest",UIScene)
UIButtonPressedActionTest._displayValueLabel = nil

function UIButtonPressedActionTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIButtonPressedActionTest)
    return target
end

function UIButtonPressedActionTest:initExtend()

    self:init()

    local widgetSize = self._widget:getSize()
        
    
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addWidget(self._displayValueLabel)
        
    local alert = Label:create()
    alert:setText("Button Pressed Action")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))    
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)

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
        
    local button = Button:create()
    button:setTouchEnabled(true)
    button:setPressedActionEnabled(true)
    button:loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "")
    button:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0))
    button:addTouchEventListener(touchEvent)        
    self._uiLayer:addWidget(button)
end

function UIButtonPressedActionTest.create()
    local scene = CCScene:create()
    local layer = UIButtonPressedActionTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene  
end

local UITextButtonTest = class("UITextButtonTest",UIScene)
UITextButtonTest._displayValueLabel = nil

function UITextButtonTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UITextButtonTest)
    return target
end

function UITextButtonTest:initExtend()

    self:init()

    local widgetSize = self._widget:getSize()
        
    
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addWidget(self._displayValueLabel)
        
    local alert = Label:create()
    alert:setText("TextButton")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))    
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)

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
        
    local textButton = Button:create()
    textButton:setTouchEnabled(true)
    textButton:loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "")
    textButton:setTitleText("Text Button")
    textButton:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0))
    textButton:addTouchEventListener(touchEvent)        
    self._uiLayer:addWidget(textButton)
end

function UITextButtonTest.create()
    local scene = CCScene:create()
    local layer = UITextButtonTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene
end

local UITextButtonScale9Test = class("UITextButtonScale9Test",UIScene)
UITextButtonScale9Test._displayValueLabel = nil

function UITextButtonScale9Test.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UITextButtonScale9Test)
    return target
end

function UITextButtonScale9Test:initExtend()

    self:init()

    local widgetSize = self._widget:getSize()
          
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addWidget(self._displayValueLabel)
        
    local alert = Label:create()
    alert:setText("TextButton scale9 render")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))    
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)

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
        
    local textButton = Button:create()
    textButton:setTouchEnabled(true)
    textButton:setScale9Enabled(true)
    textButton:loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "")
    textButton:setSize(CCSize(180, textButton:getContentSize().height * 1.5))
    textButton:setTitleText("Text Button scale9 render")
    textButton:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0))
    textButton:addTouchEventListener(touchEvent)        
    self._uiLayer:addWidget(textButton)
end

function UITextButtonScale9Test.create()
    local scene = CCScene:create()
    local layer = UITextButtonScale9Test.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene 
end

local UICheckBoxTest = class("UICheckBoxTest",UIScene)
UICheckBoxTest._displayValueLabel = nil

function UICheckBoxTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UICheckBoxTest)
    return target
end

function UICheckBoxTest:initExtend()

    self:init()

    local widgetSize = self._widget:getSize()
          
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addWidget(self._displayValueLabel)
        
    local alert = Label:create()
    alert:setText("CheckBox")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))    
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)

    local function selectedEvent(sender,eventType)
        if eventType == ccs.CheckBoxEventType.selected then
            self._displayValueLabel:setText("Selected")
        elseif eventType == ccs.CheckBoxEventType.unselected then
            self._displayValueLabel:setText("Unselected")
        end
    end  
        
    local checkBox = CheckBox:create()
    checkBox:setTouchEnabled(true)
    checkBox:loadTextures("cocosui/check_box_normal.png",
                               "cocosui/check_box_normal_press.png",
                               "cocosui/check_box_active.png",
                               "cocosui/check_box_normal_disable.png",
                               "cocosui/check_box_active_disable.png")
    checkBox:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0))
        
    checkBox:addEventListenerCheckBox(selectedEvent)  

    self._uiLayer:addWidget(checkBox)
end

function UICheckBoxTest.create()
    local scene = CCScene:create()
    local layer = UICheckBoxTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene  
end

local UISliderTest = class("UISliderTest",UIScene)
UISliderTest._displayValueLabel = nil

function UISliderTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UISliderTest)
    return target
end

function UISliderTest:initExtend()

    self:init()

    local widgetSize = self._widget:getSize()
          
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("Move the slider thumb")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addWidget(self._displayValueLabel)
        
    local alert = Label:create()
    alert:setText("Slider")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))    
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)

    local function percentChangedEvent(sender,eventType)
        if eventType == ccs.SliderEventType.percent_changed then
            local slider = tolua.cast(sender,"Slider")
            local percent = "Percent " .. slider:getPercent()
            self._displayValueLabel:setText(percent)
        end
    end  
        
    local slider = Slider:create()
    slider:setTouchEnabled(true)
    slider:loadBarTexture("cocosui/sliderTrack.png")
    slider:loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "")
    slider:loadProgressBarTexture("cocosui/sliderProgress.png")
    slider:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0))
    slider:addEventListenerSlider(percentChangedEvent)

    self._uiLayer:addWidget(slider)
end

function UISliderTest.create()
    local scene = CCScene:create()
    local layer = UISliderTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene   
end

local UISliderScale9Test = class("UISliderScale9Test",UIScene)
UISliderScale9Test._displayValueLabel = nil

function UISliderScale9Test.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UISliderScale9Test)
    return target
end

function UISliderScale9Test:initExtend()

    self:init()

    local widgetSize = self._widget:getSize()
          
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("Move the slider thumb")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addWidget(self._displayValueLabel)
        
    local alert = Label:create()
    alert:setText("Slider scale9 render")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))    
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)

    local function percentChangedEvent(sender,eventType)
        if eventType == ccs.SliderEventType.percent_changed then
            local slider = tolua.cast(sender,"Slider")
            local percent = "Percent " .. slider:getPercent()
            self._displayValueLabel:setText(percent)
        end
    end  
        
    local slider = Slider:create()
    slider:setTouchEnabled(true)
    slider:loadBarTexture("cocosui/sliderTrack2.png")
    slider:loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "")
    slider:loadProgressBarTexture("cocosui/slider_bar_active_9patch.png")
    slider:setScale9Enabled(true)
    slider:setCapInsets(CCRect(0, 0, 0, 0))
    slider:setSize(CCSize(250, 10))
    slider:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0))
    slider:addEventListenerSlider(percentChangedEvent)

    self._uiLayer:addWidget(slider)
end

function UISliderScale9Test.create()
    local scene = CCScene:create()
    local layer = UISliderScale9Test.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene  
end

local UIImageViewTest = class("UIImageViewTest",UIScene)

function UIImageViewTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIImageViewTest)
    return target
end

function UIImageViewTest:initExtend()

    self:init()

    local widgetSize = self._widget:getSize()
        
    local alert = Label:create()
    alert:setText("ImageView")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))    
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)
        
    local imageView = ImageView:create()
    imageView:loadTexture("cocosui/ccicon.png")
    imageView:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 + imageView:getSize().height / 4.0))
    self._uiLayer:addWidget(imageView)
end

function UIImageViewTest.create()
    local scene = CCScene:create()
    local layer = UIImageViewTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene  
end


local UIImageViewScale9Test = class("UIImageViewScale9Test",UIScene)

function UIImageViewScale9Test.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIImageViewScale9Test)
    return target
end

function UIImageViewScale9Test:initExtend()

    self:init()

    local widgetSize = self._widget:getSize()
        
    local alert = Label:create()
    alert:setText("ImageView scale9 render")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))    
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)
        
    local imageView = ImageView:create()
    imageView:setScale9Enabled(true)
    imageView:loadTexture("cocosui/buttonHighlighted.png")
    imageView:setSize(CCSize(200, 85))
    imageView:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 + imageView:getSize().height / 4.0))
    self._uiLayer:addWidget(imageView)
end

function UIImageViewScale9Test.create()
    local scene = CCScene:create()
    local layer = UIImageViewScale9Test.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene    
end

local UILoadingBarLeftTest = class("UILoadingBarLeftTest",UIScene)
UILoadingBarLeftTest._count = 0

function UILoadingBarLeftTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UILoadingBarLeftTest)
    return target
end

function UILoadingBarLeftTest:initExtend()
    
    self._uiLayer = TouchGroup:create()
    self:addChild(self._uiLayer)

    local winSize = CCDirector:sharedDirector():getWinSize()
    local scale   = winSize.height / 320
    self._uiLayer:setAnchorPoint(ccp(0,0))
    self._uiLayer:setScale(scale)
    self._uiLayer:setPosition(ccp((winSize.width - 480 * scale) / 2, (winSize.height - 320 * scale) / 2))

    self._widget = GUIReader:shareReader():widgetFromJsonFile("cocosui/UITest/UITest.json")
    self._uiLayer:addWidget(self._widget)

    self._sceneTitle = self._uiLayer:getWidgetByName("UItest")

    local back_label = self._uiLayer:getWidgetByName("back")
    back_label:setVisible(false)

    local widgetSize = self._widget:getSize()
        
    local alert = Label:create()
    alert:setText("LoadingBar")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))    
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)
        
    local loadingBar = LoadingBar:create()
    loadingBar:setName("LoadingBar")
    loadingBar:loadTexture("cocosui/sliderProgress.png")
    loadingBar:setPercent(0)
        
    loadingBar:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 + loadingBar:getSize().height / 4.0))
    self._uiLayer:addWidget(loadingBar)

    local function update(delta)
        self._count = self._count + 1
        if self._count > 100 then
            self._count = 0
        end

        if self._uiLayer ~= nil then
            local loadingBar = tolua.cast(self._uiLayer:getWidgetByName("LoadingBar"), "LoadingBar")
            loadingBar:setPercent(self._count)
        end
    end

    self:scheduleUpdateWithPriorityLua(update, 0)

    local function onNodeEvent(tag)
        if tag == "exit" then
            self:unscheduleUpdate()
        end
    end

    self:registerScriptHandler(onNodeEvent)

    local function previousCallback(sender, eventType)
        if eventType == ccs.TouchEventType.ended then
            self:unscheduleUpdate()
            self._uiLayer:removeFromParentAndCleanup(true)
            CCDirector:sharedDirector():replaceScene(guiSceneManager.previousUIScene())
        end
    end

    local left_button = self._uiLayer:getWidgetByName("left_Button")
    left_button:addTouchEventListener(previousCallback)

    local function restartCallback(sender, eventType)
         if eventType == ccs.TouchEventType.ended then
             self:unscheduleUpdate()
             self._uiLayer:removeFromParentAndCleanup(true)
             CCDirector:sharedDirector():replaceScene(guiSceneManager.currentUIScene())
         end
    end

    local middle_button = self._uiLayer:getWidgetByName("middle_Button")
    middle_button:addTouchEventListener(restartCallback)

    local function nextCallback(sender, eventType)
        if eventType == ccs.TouchEventType.ended then
            self:unscheduleUpdate()
            self._uiLayer:removeFromParentAndCleanup(true)
            CCDirector:sharedDirector():replaceScene(guiSceneManager.nextUIScene())
        end
    end

    local right_button = self._uiLayer:getWidgetByName("right_Button")
    right_button:addTouchEventListener(nextCallback)

    local function menuCloseCallback( sender,eventType)
        if eventType == ccs.TouchEventType.ended then
            self:unscheduleUpdate()
            self._uiLayer:removeFromParentAndCleanup(true)
            local scene = CocoStudioTest()
            if scene ~= nil then
                CCDirector:sharedDirector():replaceScene(scene)
            end
        end
    end

    local mainMenuLabel = Label:create()
    mainMenuLabel:setText("Back")
    mainMenuLabel:setFontSize(20)
    mainMenuLabel:setTouchScaleChangeEnabled(true)
    mainMenuLabel:setPosition(CCPoint(430,30))
    mainMenuLabel:setTouchEnabled(true)
    mainMenuLabel:addTouchEventListener(menuCloseCallback)
    self._uiLayer:addWidget(mainMenuLabel)  
end

function UILoadingBarLeftTest.create()
    local scene = CCScene:create()
    local layer = UILoadingBarLeftTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene  
end

local UILoadingBarRightTest = class("UILoadingBarRightTest",UIScene)
UILoadingBarRightTest._count = 0

function UILoadingBarRightTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UILoadingBarRightTest)
    return target
end

function UILoadingBarRightTest:initExtend()

    self._uiLayer = TouchGroup:create()
    local winSize = CCDirector:sharedDirector():getWinSize()
    local scale   = winSize.height / 320
    self._uiLayer:setAnchorPoint(ccp(0,0))
    self._uiLayer:setScale(scale)
    self._uiLayer:setPosition(ccp((winSize.width - 480 * scale) / 2, (winSize.height - 320 * scale) / 2))

    self:addChild(self._uiLayer)

    self._widget = GUIReader:shareReader():widgetFromJsonFile("cocosui/UITest/UITest.json")
    self._uiLayer:addWidget(self._widget)

    self._sceneTitle = self._uiLayer:getWidgetByName("UItest")

    local back_label = self._uiLayer:getWidgetByName("back")
    back_label:setVisible(false)

    local widgetSize = self._widget:getSize()
        
    local alert = Label:create()
    alert:setText("LoadingBar")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))    
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)
        
    local loadingBar = LoadingBar:create()
    loadingBar:setName("LoadingBar")
    loadingBar:loadTexture("cocosui/sliderProgress.png")
    loadingBar:setDirection(ccs.LoadingBarType.right)
    loadingBar:setPercent(0)
        
    loadingBar:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 + loadingBar:getSize().height / 4.0))
    self._uiLayer:addWidget(loadingBar)

    local function update(delta)
        self._count = self._count + 1
        if self._count > 100 then
            self._count = 0
        end

        if self._uiLayer ~= nil then
            local loadingBar = tolua.cast(self._uiLayer:getWidgetByName("LoadingBar"), "LoadingBar")
            loadingBar:setPercent(self._count)
        end
    end

    self:scheduleUpdateWithPriorityLua(update, 0)

    local function onNodeEvent(tag)
        if tag == "exit" then
            self:unscheduleUpdate()
        end
    end

    self:registerScriptHandler(onNodeEvent)

    local function previousCallback(sender, eventType)
        if eventType == ccs.TouchEventType.ended then
            self:unscheduleUpdate()
            self._uiLayer:removeFromParentAndCleanup(true)
            CCDirector:sharedDirector():replaceScene(guiSceneManager.previousUIScene())
        end
    end

    local left_button = self._uiLayer:getWidgetByName("left_Button")
    left_button:addTouchEventListener(previousCallback)

    local function restartCallback(sender, eventType)
         if eventType == ccs.TouchEventType.ended then
             self:unscheduleUpdate()
             self._uiLayer:removeFromParentAndCleanup(true)
             CCDirector:sharedDirector():replaceScene(guiSceneManager.currentUIScene())
         end
    end

    local middle_button = self._uiLayer:getWidgetByName("middle_Button")
    middle_button:addTouchEventListener(restartCallback)

    local function nextCallback(sender, eventType)
        if eventType == ccs.TouchEventType.ended then
            self:unscheduleUpdate()
            self._uiLayer:removeFromParentAndCleanup(true)
            CCDirector:sharedDirector():replaceScene(guiSceneManager.nextUIScene())
        end
    end

    local right_button = self._uiLayer:getWidgetByName("right_Button")
    right_button:addTouchEventListener(nextCallback)

    local function menuCloseCallback( sender,eventType)
        if eventType == ccs.TouchEventType.ended then
            self:unscheduleUpdate()
            self._uiLayer:removeFromParentAndCleanup(true)
            local scene = CocoStudioTest()
            if scene ~= nil then
                CCDirector:sharedDirector():replaceScene(scene)
            end
        end
    end

    local mainMenuLabel = Label:create()
    mainMenuLabel:setText("Back")
    mainMenuLabel:setFontSize(20)
    mainMenuLabel:setTouchScaleChangeEnabled(true)
    mainMenuLabel:setPosition(CCPoint(430,30))
    mainMenuLabel:setTouchEnabled(true)
    mainMenuLabel:addTouchEventListener(menuCloseCallback)
    self._uiLayer:addWidget(mainMenuLabel)  
end

function UILoadingBarRightTest.create()
    local scene = CCScene:create()
    local layer = UILoadingBarRightTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene 
end

local UILoadingBarLeftScale9Test = class("UILoadingBarLeftScale9Test",UIScene)
UILoadingBarLeftScale9Test._count = 0

function UILoadingBarLeftScale9Test.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UILoadingBarLeftScale9Test)
    return target
end

function UILoadingBarLeftScale9Test:initExtend()

    self._uiLayer = TouchGroup:create()

    local winSize = CCDirector:sharedDirector():getWinSize()
    local scale   = winSize.height / 320
    self._uiLayer:setAnchorPoint(ccp(0,0))
    self._uiLayer:setScale(scale)
    self._uiLayer:setPosition(ccp((winSize.width - 480 * scale) / 2, (winSize.height - 320 * scale) / 2))

    self:addChild(self._uiLayer)

    self._widget = GUIReader:shareReader():widgetFromJsonFile("cocosui/UITest/UITest.json")
    self._uiLayer:addWidget(self._widget)

    self._sceneTitle = self._uiLayer:getWidgetByName("UItest")

    local back_label = self._uiLayer:getWidgetByName("back")
    back_label:setVisible(false)

    local widgetSize = self._widget:getSize()
        
    local alert = Label:create()
    alert:setText("LoadingBar Scale9 Render")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))    
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)
        
    local loadingBar = LoadingBar:create()
    loadingBar:setName("LoadingBar")
    loadingBar:loadTexture("cocosui/slider_bar_active_9patch.png")
    loadingBar:setScale9Enabled(true)
    loadingBar:setCapInsets(CCRect(0, 0, 0, 0))
    loadingBar:setSize(CCSize(300, 30))
    loadingBar:setPercent(0)
        
    loadingBar:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 + loadingBar:getSize().height / 4.0))
    self._uiLayer:addWidget(loadingBar)

    local function update(delta)
        self._count = self._count + 1
        if self._count > 100 then
            self._count = 0
        end

        if self._uiLayer ~= nil then
            local loadingBar = tolua.cast(self._uiLayer:getWidgetByName("LoadingBar"), "LoadingBar")
            loadingBar:setPercent(self._count)
        end
    end

    self:scheduleUpdateWithPriorityLua(update, 0)

    local function onNodeEvent(tag)
        if tag == "exit" then
            self:unscheduleUpdate()
        end
    end

    self:registerScriptHandler(onNodeEvent)

    local function previousCallback(sender, eventType)
        if eventType == ccs.TouchEventType.ended then
            self:unscheduleUpdate()
            self._uiLayer:removeFromParentAndCleanup(true)
            CCDirector:sharedDirector():replaceScene(guiSceneManager.previousUIScene())
        end
    end

    local left_button = self._uiLayer:getWidgetByName("left_Button")
    left_button:addTouchEventListener(previousCallback)

    local function restartCallback(sender, eventType)
         if eventType == ccs.TouchEventType.ended then
             self:unscheduleUpdate()
             self._uiLayer:removeFromParentAndCleanup(true)
             CCDirector:sharedDirector():replaceScene(guiSceneManager.currentUIScene())
         end
    end

    local middle_button = self._uiLayer:getWidgetByName("middle_Button")
    middle_button:addTouchEventListener(restartCallback)

    local function nextCallback(sender, eventType)
        if eventType == ccs.TouchEventType.ended then
            self:unscheduleUpdate()
            self._uiLayer:removeFromParentAndCleanup(true)
            CCDirector:sharedDirector():replaceScene(guiSceneManager.nextUIScene())
        end
    end

    local right_button = self._uiLayer:getWidgetByName("right_Button")
    right_button:addTouchEventListener(nextCallback)

    local function menuCloseCallback( sender,eventType)
        if eventType == ccs.TouchEventType.ended then
            self:unscheduleUpdate()
            self._uiLayer:removeFromParentAndCleanup(true)
            local scene = CocoStudioTest()
            if scene ~= nil then
                CCDirector:sharedDirector():replaceScene(scene)
            end
        end
    end

    local mainMenuLabel = Label:create()
    mainMenuLabel:setText("Back")
    mainMenuLabel:setFontSize(20)
    mainMenuLabel:setTouchScaleChangeEnabled(true)
    mainMenuLabel:setPosition(CCPoint(430,30))
    mainMenuLabel:setTouchEnabled(true)
    mainMenuLabel:addTouchEventListener(menuCloseCallback)
    self._uiLayer:addWidget(mainMenuLabel)  
end

function UILoadingBarLeftScale9Test.create()
    local scene = CCScene:create()
    local layer = UILoadingBarLeftScale9Test.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene  
end

local UILoadingBarRightScale9Test = class("UILoadingBarRightScale9Test",UIScene)
UILoadingBarRightScale9Test._count = 0

function UILoadingBarRightScale9Test.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UILoadingBarRightScale9Test)
    return target
end

function UILoadingBarRightScale9Test:initExtend()

    self._uiLayer = TouchGroup:create()

    local winSize = CCDirector:sharedDirector():getWinSize()
    local scale   = winSize.height / 320
    self._uiLayer:setAnchorPoint(ccp(0,0))
    self._uiLayer:setScale(scale)
    self._uiLayer:setPosition(ccp((winSize.width - 480 * scale) / 2, (winSize.height - 320 * scale) / 2))
    
    self:addChild(self._uiLayer)

    self._widget = GUIReader:shareReader():widgetFromJsonFile("cocosui/UITest/UITest.json")
    self._uiLayer:addWidget(self._widget)

    self._sceneTitle = self._uiLayer:getWidgetByName("UItest")

    local back_label = self._uiLayer:getWidgetByName("back")
    back_label:setVisible(false)

    local widgetSize = self._widget:getSize()
        
    local alert = Label:create()
    alert:setText("LoadingBar Scale9 Render")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))    
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)
        
    local loadingBar = LoadingBar:create()
    loadingBar:setName("LoadingBar")
    loadingBar:loadTexture("cocosui/slider_bar_active_9patch.png")
    loadingBar:setScale9Enabled(true)
    loadingBar:setCapInsets(CCRect(0, 0, 0, 0))
    loadingBar:setSize(CCSize(300, 30))
    loadingBar:setDirection(ccs.LoadingBarType.right)
    loadingBar:setPercent(0)
        
    loadingBar:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 + loadingBar:getSize().height / 4.0))
    self._uiLayer:addWidget(loadingBar)

    local function update(delta)
        self._count = self._count + 1
        if self._count > 100 then
            self._count = 0
        end

        if self._uiLayer ~= nil then
            local loadingBar = tolua.cast(self._uiLayer:getWidgetByName("LoadingBar"), "LoadingBar")
            loadingBar:setPercent(self._count)
        end
    end

    self:scheduleUpdateWithPriorityLua(update, 0)

    local function onNodeEvent(tag)
        if tag == "exit" then
            self:unscheduleUpdate()
        end
    end

    self:registerScriptHandler(onNodeEvent)

    local function previousCallback(sender, eventType)
        if eventType == ccs.TouchEventType.ended then
            self:unscheduleUpdate()
            self._uiLayer:removeFromParentAndCleanup(true)
            CCDirector:sharedDirector():replaceScene(guiSceneManager.previousUIScene())
        end
    end

    local left_button = self._uiLayer:getWidgetByName("left_Button")
    left_button:addTouchEventListener(previousCallback)

    local function restartCallback(sender, eventType)
         if eventType == ccs.TouchEventType.ended then
             self:unscheduleUpdate()
             self._uiLayer:removeFromParentAndCleanup(true)
             CCDirector:sharedDirector():replaceScene(guiSceneManager.currentUIScene())
         end
    end

    local middle_button = self._uiLayer:getWidgetByName("middle_Button")
    middle_button:addTouchEventListener(restartCallback)

    local function nextCallback(sender, eventType)
        if eventType == ccs.TouchEventType.ended then
            self:unscheduleUpdate()
            self._uiLayer:removeFromParentAndCleanup(true)
            CCDirector:sharedDirector():replaceScene(guiSceneManager.nextUIScene())
        end
    end

    local right_button = self._uiLayer:getWidgetByName("right_Button")
    right_button:addTouchEventListener(nextCallback)

    local function menuCloseCallback( sender,eventType)
        if eventType == ccs.TouchEventType.ended then
            self:unscheduleUpdate()
            self._uiLayer:removeFromParentAndCleanup(true)
            local scene = CocoStudioTest()
            if scene ~= nil then
                CCDirector:sharedDirector():replaceScene(scene)
            end
        end
    end

    local mainMenuLabel = Label:create()
    mainMenuLabel:setText("Back")
    mainMenuLabel:setFontSize(20)
    mainMenuLabel:setTouchScaleChangeEnabled(true)
    mainMenuLabel:setPosition(CCPoint(430,30))
    mainMenuLabel:setTouchEnabled(true)
    mainMenuLabel:addTouchEventListener(menuCloseCallback)
    self._uiLayer:addWidget(mainMenuLabel)  
end

function UILoadingBarRightScale9Test.create()
    local scene = CCScene:create()
    local layer = UILoadingBarRightScale9Test.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene   
end

local UILabelAtlasTest = class("UILabelAtlasTest",UIScene)

function UILabelAtlasTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UILabelAtlasTest)
    return target
end

function UILabelAtlasTest:initExtend()

    self:init()
    local widgetSize = self._widget:getSize()
        
    local alert = Label:create()
    alert:setText("LabelAtlas")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)
        

    local labelAtlas = LabelAtlas:create()
    labelAtlas:setProperty("1234567890", "cocosui/labelatlas.png", 17, 22, "0")
    labelAtlas:setPosition(CCPoint((widgetSize.width) / 2, widgetSize.height / 2.0))        
        
    self._uiLayer:addWidget(labelAtlas) 
end

function UILabelAtlasTest.create()
    local scene = CCScene:create()
    local layer = UILabelAtlasTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene 
end

local UILabelBMFontTest = class("UILabelBMFontTest",UIScene)

function UILabelBMFontTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UILabelBMFontTest)
    return target
end

function UILabelBMFontTest:initExtend()

    self:init()
    local widgetSize = self._widget:getSize()
        
    local alert = Label:create()
    alert:setText("LabelBMFont")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)
        

    local labelBMFont = LabelBMFont:create()
    labelBMFont:setFntFile("cocosui/bitmapFontTest2.fnt")
    labelBMFont:setText("BMFont")
    labelBMFont:setPosition(CCPoint(widgetSize.width / 2, widgetSize.height / 2.0 + labelBMFont:getSize().height / 8.0))        
        
    self._uiLayer:addWidget(labelBMFont) 
end

function UILabelBMFontTest.create()
    local scene = CCScene:create()
    local layer = UILabelBMFontTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene   
end

local UILabelTest = class("UILabelTest",UIScene)

function UILabelTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UILabelTest)
    return target
end

function UILabelTest:initExtend()

    self:init()
    local widgetSize = self._widget:getSize()
        
    local alert = Label:create()
    alert:setText("Label")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)
        
    local label = Label:create()
    label:setText("Label")
    label:setFontName("AmericanTypewriter")
    label:setFontSize(30)
    label:setPosition(CCPoint(widgetSize.width / 2, widgetSize.height / 2 + label:getSize().height / 4))    
    self._uiLayer:addWidget(label) 
end

function UILabelTest.create()
    local scene = CCScene:create()
    local layer = UILabelTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene   
end

local UITextAreaTest = class("UITextAreaTest",UIScene)

function UITextAreaTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UITextAreaTest)
    return target
end

function UITextAreaTest:initExtend()

    self:init()
    local widgetSize = self._widget:getSize()
        
    local alert = Label:create()
    alert:setText("TextArea")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)
        
    local textArea = Label:create()
    textArea:setTextAreaSize(CCSize(280, 150))
    textArea:setTextHorizontalAlignment(cc.TEXT_ALIGNMENT_CENTER)
    textArea:setText("TextArea widget can line wrap")
    textArea:setFontName("AmericanTypewriter")
    textArea:setFontSize(32)
    textArea:setPosition(CCPoint(widgetSize.width / 2, widgetSize.height / 2 - textArea:getSize().height / 8))  
    self._uiLayer:addWidget(textArea) 
end

function UITextAreaTest.create()
    local scene = CCScene:create()
    local layer = UITextAreaTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene   
end

local UITextFieldTest = class("UITextFieldTest",UIScene)
UITextFieldTest._displayValueLabel = nil

function UITextFieldTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UITextFieldTest)
    return target
end

function UITextFieldTest:initExtend()

    self:init()
    local widgetSize = self._widget:getSize()

    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 + self._displayValueLabel:getSize().height * 1.5))
    self._uiLayer:addWidget(self._displayValueLabel)  
        
    local alert = Label:create()
    alert:setText("TextField")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)

    local function textFieldEvent(sender, eventType)
        if eventType == ccs.TextFiledEventType.attach_with_ime then
            local textField = tolua.cast(sender,"TextField")
            local screenSize = CCDirector:sharedDirector():getWinSize()
            textField:runAction(CCMoveTo:create(0.225,CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 + textField:getContentSize().height / 2.0)))
            self._displayValueLabel:setText("attach with IME")
        elseif eventType == ccs.TextFiledEventType.detach_with_ime then
            local textField = tolua.cast(sender,"TextField")
            local screenSize = CCDirector:sharedDirector():getWinSize()
            textField:runAction(CCMoveTo:create(0.175, CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0)))
            self._displayValueLabel:setText("detach with IME")
        elseif eventType == ccs.TextFiledEventType.insert_text then
            self._displayValueLabel:setText("insert words")
        elseif eventType == ccs.TextFiledEventType.delete_backward then
            self._displayValueLabel:setText("delete word")
        end
    end
        
    local textField = TextField:create()
    textField:setTouchEnabled(true)
    textField:setFontName(getFont())
    textField:setFontSize(30)
    textField:setPlaceHolder("input words here")
    textField:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0))
    textField:addEventListenerTextField(textFieldEvent) 
    self._uiLayer:addWidget(textField) 
end

function UITextFieldTest.create()
    local scene = CCScene:create()
    local layer = UITextFieldTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene  
end

local UITextFieldMaxLengthTest = class("UITextFieldMaxLengthTest",UIScene)
UITextFieldMaxLengthTest._displayValueLabel = nil

function UITextFieldMaxLengthTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UITextFieldMaxLengthTest)
    return target
end

function UITextFieldMaxLengthTest:initExtend()

    self:init()
    local widgetSize = self._widget:getSize()

    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 + self._displayValueLabel:getSize().height * 1.5))
    self._uiLayer:addWidget(self._displayValueLabel)  
        
    local alert = Label:create()
    alert:setText("TextField max length")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)

    local function textFieldEvent(sender, eventType)
        if eventType == ccs.TextFiledEventType.attach_with_ime then
            local textField = tolua.cast(sender,"TextField")
            local screenSize = CCDirector:sharedDirector():getWinSize()
            textField:runAction(CCMoveTo:create(0.225,CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 + textField:getContentSize().height / 2.0)))
            local info = string.format("attach with IME max length %d",textField:getMaxLength())
            self._displayValueLabel:setText(info)
        elseif eventType == ccs.TextFiledEventType.detach_with_ime then
            local textField = tolua.cast(sender,"TextField")
            local screenSize = CCDirector:sharedDirector():getWinSize()
            textField:runAction(CCMoveTo:create(0.175, CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0)))
            local info = string.format("detach with IME max length %d",textField:getMaxLength())
            self._displayValueLabel:setText(info)
        elseif eventType == ccs.TextFiledEventType.insert_text then
            local textField = tolua.cast(sender,"TextField")
            local info = string.format("insert words max length %d",textField:getMaxLength())
            self._displayValueLabel:setText(info)
        elseif eventType == ccs.TextFiledEventType.delete_backward then
            local textField = tolua.cast(sender,"TextField")
            local info = string.format("delete word max length %d",textField:getMaxLength())
            self._displayValueLabel:setText(info)
        end
    end
        
    local textField = TextField:create()
    textField:setMaxLengthEnabled(true)
    textField:setMaxLength(3)
    textField:setTouchEnabled(true)
    textField:setFontName(getFont())
    textField:setFontSize(30)
    textField:setPlaceHolder("input words here")
    textField:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0))
    textField:addEventListenerTextField(textFieldEvent) 
    self._uiLayer:addWidget(textField) 
end

function UITextFieldMaxLengthTest.create()
    local scene = CCScene:create()
    local layer = UITextFieldMaxLengthTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene  
end

local UITextFieldPasswordTest = class("UITextFieldPasswordTest",UIScene)
UITextFieldPasswordTest._displayValueLabel = nil

function UITextFieldPasswordTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UITextFieldPasswordTest)
    return target
end

function UITextFieldPasswordTest:initExtend()

    self:init()
    local widgetSize = self._widget:getSize()

    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 + self._displayValueLabel:getSize().height * 1.5))
    self._uiLayer:addWidget(self._displayValueLabel)  
        
    local alert = Label:create()
    alert:setText("TextField password")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)

    local function textFieldEvent(sender, eventType)
        if eventType == ccs.TextFiledEventType.attach_with_ime then
            local textField = tolua.cast(sender,"TextField")
            textField:runAction(CCMoveTo:create(0.175, CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0)))
            self._displayValueLabel:setText("detach with IME password")
        elseif eventType == ccs.TextFiledEventType.detach_with_ime then
            local textField = tolua.cast(sender,"TextField")
            textField:runAction(CCMoveTo:create(0.175, CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0)))
            self._displayValueLabel:setText("detach with IME password")
        elseif eventType == ccs.TextFiledEventType.insert_text then
            self._displayValueLabel:setText("insert words password")
        elseif eventType == ccs.TextFiledEventType.delete_backward then
            self._displayValueLabel:setText("delete word password")
        end
    end
        
    local textField = TextField:create()
    textField:setPasswordEnabled(true)
    textField:setPasswordStyleText("*")
    textField:setTouchEnabled(true)
    textField:setFontName(getFont())
    textField:setFontSize(30)
    textField:setPlaceHolder("input password here")
    textField:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0))
    textField:addEventListenerTextField(textFieldEvent) 
    self._uiLayer:addWidget(textField) 
end

function UITextFieldPasswordTest.create()
    local scene = CCScene:create()
    local layer = UITextFieldPasswordTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene  
end

local UIPanelTest = class("UIPanelTest",UIScene)

function UIPanelTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIPanelTest)
    return target
end

function UIPanelTest:initExtend()

    self:init()

    local widgetSize = self._widget:getSize()
        
    local alert = Label:create()
    alert:setText("Panel")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)

    local background = self._uiLayer:getWidgetByName("background_Panel")
    
    local layout = Layout:create()
    layout:setSize(CCSize(280, 150))
    local backgroundSize = background:getSize()
    layout:setPosition(CCPoint((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout:getSize().width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout:getSize().height) / 2))
    self._uiLayer:addWidget(layout)
        
    local button = Button:create()
    button:setTouchEnabled(true)
    button:loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "")
    button:setPosition(CCPoint(button:getSize().width / 2, layout:getSize().height - button:getSize().height / 2))
    layout:addChild(button)
        
    local textButton = Button:create()
    textButton:setTouchEnabled(true)
    textButton:loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "")
    textButton:setTitleText("Text Button")
    textButton:setPosition(CCPoint(layout:getSize().width / 2, layout:getSize().height / 2))
    layout:addChild(textButton)
        
    local button_scale9 = Button:create()
    button_scale9:setTouchEnabled(true)
    button_scale9:loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "")
    button_scale9:setScale9Enabled(true)
    button_scale9:setSize(CCSize(100, button_scale9:getContentSize().height))
    button_scale9:setPosition(CCPoint(layout:getSize().width - button_scale9:getSize().width / 2, button_scale9:getSize().height / 2))
    layout:addChild(button_scale9)  
end

function UIPanelTest.create()
    local scene = CCScene:create()
    local layer = UIPanelTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene    
end

local UIPanelColorTest = class("UIPanelColorTest",UIScene)

function UIPanelColorTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIPanelColorTest)
    return target
end

function UIPanelColorTest:initExtend()

    self:init()

    local widgetSize = self._widget:getSize()
        
    local alert = Label:create()
    alert:setText("Panel color render")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 2.925))
    self._uiLayer:addWidget(alert)

    local background = self._uiLayer:getWidgetByName("background_Panel")
    
    local layout = Layout:create()
    layout:setBackGroundColorType(ccs.LayoutBackGroundColorType.solid)
    layout:setBackGroundColor(ccc3(128, 128, 128))
    layout:setSize(CCSize(280, 150))
    local backgroundSize = background:getContentSize()
    layout:setPosition(CCPoint((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout:getSize().width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout:getSize().height) / 2))
    self._uiLayer:addWidget(layout)
        
    local button = Button:create()
    button:setTouchEnabled(true)
    button:loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "")
    button:setPosition(CCPoint(button:getSize().width / 2, layout:getSize().height - button:getSize().height / 2))
    layout:addChild(button)
        
    local textButton = Button:create()
    textButton:setTouchEnabled(true)
    textButton:loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "")
    textButton:setTitleText("Text Button")
    textButton:setPosition(CCPoint(layout:getSize().width / 2, layout:getSize().height / 2))
    layout:addChild(textButton)
        
    local button_scale9 = Button:create()
    button_scale9:setTouchEnabled(true)
    button_scale9:loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "")
    button_scale9:setScale9Enabled(true)
    button_scale9:setSize(CCSize(100, button_scale9:getContentSize().height))
    button_scale9:setPosition(CCPoint(layout:getSize().width - button_scale9:getSize().width / 2, button_scale9:getSize().height / 2))
    layout:addChild(button_scale9)  
end

function UIPanelColorTest.create()
    local scene = CCScene:create()
    local layer = UIPanelColorTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene    
end

local UIPanelGradientTest = class("UIPanelGradientTest",UIScene)

function UIPanelGradientTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIPanelGradientTest)
    return target
end

function UIPanelGradientTest:initExtend()

    self:init()

    local widgetSize = self._widget:getSize()
        
    local alert = Label:create()
    alert:setText("Panel color Gradient")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 2.925))
    self._uiLayer:addWidget(alert)

    local background = self._uiLayer:getWidgetByName("background_Panel")
    
    local layout = Layout:create()
    layout:setBackGroundColorType(ccs.LayoutBackGroundColorType.gradient)
    layout:setBackGroundColor(ccc3(64, 64, 64), ccc3(192, 192, 192))
    layout:setSize(CCSize(280, 150))
    local backgroundSize = background:getContentSize()
    layout:setPosition(CCPoint((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout:getSize().width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout:getSize().height) / 2))
    self._uiLayer:addWidget(layout)
        
    local button = Button:create()
    button:setTouchEnabled(true)
    button:loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "")
    button:setPosition(CCPoint(button:getSize().width / 2, layout:getSize().height - button:getSize().height / 2))
    layout:addChild(button)
        
    local textButton = Button:create()
    textButton:setTouchEnabled(true)
    textButton:loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "")
    textButton:setTitleText("Text Button")
    textButton:setPosition(CCPoint(layout:getSize().width / 2, layout:getSize().height / 2))
    layout:addChild(textButton)
        
    local button_scale9 = Button:create()
    button_scale9:setTouchEnabled(true)
    button_scale9:loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "")
    button_scale9:setScale9Enabled(true)
    button_scale9:setSize(CCSize(100, button_scale9:getContentSize().height))
    button_scale9:setPosition(CCPoint(layout:getSize().width - button_scale9:getSize().width / 2, button_scale9:getSize().height / 2))
    layout:addChild(button_scale9)  
end

function UIPanelGradientTest.create()
    local scene = CCScene:create()
    local layer = UIPanelGradientTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene  
end

local UIPanelBackGroundImageTest = class("UIPanelBackGroundImageTest",UIScene)

function UIPanelBackGroundImageTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIPanelBackGroundImageTest)
    return target
end

function UIPanelBackGroundImageTest:initExtend()

    self:init()

    local widgetSize = self._widget:getSize()
        
    local alert = Label:create()
    alert:setText("Panel background image")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 2.925))
    self._uiLayer:addWidget(alert)
        
    local background = self._uiLayer:getWidgetByName("background_Panel")
        
    local layout = Layout:create()
    layout:setClippingEnabled(true)
    layout:setBackGroundImage("cocosui/Hello.png")
    layout:setSize(CCSize(280, 150))
    local backgroundSize = background:getContentSize()
    layout:setPosition(CCPoint((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout:getSize().width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout:getSize().height) / 2))
    self._uiLayer:addWidget(layout)
        
    local button = Button:create()
    button:setTouchEnabled(true)
    button:loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "")
    button:setPosition(CCPoint(button:getSize().width / 2, layout:getSize().height - button:getSize().height / 2))
    layout:addChild(button)
        
    local textButton = Button:create()
    textButton:setTouchEnabled(true)
    textButton:loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "")
    textButton:setTitleText("Text Button")
    textButton:setPosition(CCPoint(layout:getSize().width / 2, layout:getSize().height / 2))
    layout:addChild(textButton)
        
    local button_scale9 = Button:create()
    button_scale9:setTouchEnabled(true)
    button_scale9:loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "")
    button_scale9:setScale9Enabled(true)
    button_scale9:setSize(CCSize(100, button_scale9:getContentSize().height))
    button_scale9:setPosition(CCPoint(layout:getSize().width - button_scale9:getSize().width / 2, button_scale9:getSize().height / 2))
    layout:addChild(button_scale9)   
end

function UIPanelBackGroundImageTest.create()
    local scene = CCScene:create()
    local layer = UIPanelBackGroundImageTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene     
end

local UIPanelBackGroundImageScale9Test = class("UIPanelBackGroundImageScale9Test",UIScene)

function UIPanelBackGroundImageScale9Test.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIPanelBackGroundImageScale9Test)
    return target
end

function UIPanelBackGroundImageScale9Test:initExtend()

    self:init()

    local widgetSize = self._widget:getSize()
        
    local alert = Label:create()
    alert:setText("Panel background image scale9")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 2.925))
    self._uiLayer:addWidget(alert)

    local background = self._uiLayer:getWidgetByName("background_Panel")
    
    local layout = Layout:create()
    layout:setBackGroundImageScale9Enabled(true)
    layout:setBackGroundImage("cocosui/green_edit.png")
    layout:setSize(CCSize(280, 150))
    local backgroundSize = background:getContentSize()
    layout:setPosition(CCPoint((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout:getSize().width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout:getSize().height) / 2))
    self._uiLayer:addWidget(layout)
        
    local button = Button:create()
    button:setTouchEnabled(true)
    button:loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "")
    button:setPosition(CCPoint(button:getSize().width / 2, layout:getSize().height - button:getSize().height / 2))
    layout:addChild(button)
        
    local textButton = Button:create()
    textButton:setTouchEnabled(true)
    textButton:loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "")
    textButton:setTitleText("Text Button")
    textButton:setPosition(CCPoint(layout:getSize().width / 2, layout:getSize().height / 2))
    layout:addChild(textButton)
        
    local button_scale9 = Button:create()
    button_scale9:setTouchEnabled(true)
    button_scale9:loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "")
    button_scale9:setScale9Enabled(true)
    button_scale9:setSize(CCSize(100, button_scale9:getContentSize().height))
    button_scale9:setPosition(CCPoint(layout:getSize().width - button_scale9:getSize().width / 2, button_scale9:getSize().height / 2))
    layout:addChild(button_scale9)  
end

function UIPanelBackGroundImageScale9Test.create()
    local scene = CCScene:create()
    local layer = UIPanelBackGroundImageScale9Test.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene    
end

local UIPanelLayoutLinearVerticalTest = class("UIPanelLayoutLinearVerticalTest",UIScene)

function UIPanelLayoutLinearVerticalTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIPanelLayoutLinearVerticalTest)
    return target
end

function UIPanelLayoutLinearVerticalTest:initExtend()

    self:init()

    local widgetSize = self._widget:getSize()
        
    local alert = Label:create()
    alert:setText("Panel Layout Linear Vertical")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 2.925))
    self._uiLayer:addWidget(alert)

    local background = self._uiLayer:getWidgetByName("background_Panel")
    
    local layout = Layout:create()
    layout:setLayoutType(ccs.LayoutType.linearVertical)
    layout:setSize(CCSize(280, 150))
    local backgroundSize = background:getContentSize()
    layout:setPosition(CCPoint((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout:getSize().width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout:getSize().height) / 2))
    self._uiLayer:addWidget(layout)
        
    local button = Button:create()
    button:setTouchEnabled(true)
    button:loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "")
    layout:addChild(button)
        
    local lp1 = LinearLayoutParameter:create()
    button:setLayoutParameter(lp1)
    lp1:setGravity(ccs.UILinearGravity.centerHorizontal)
    lp1:setMargin({ left = 0, top = 5, right = 0, bottom = 10 })
        
        
    local textButton = Button:create()
    textButton:setTouchEnabled(true)
    textButton:loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "")
    textButton:setTitleText("Text Button")
    layout:addChild(textButton)
        
    local lp2 = LinearLayoutParameter:create()
    textButton:setLayoutParameter(lp2)
    lp2:setGravity(ccs.UILinearGravity.centerHorizontal)
    lp2:setMargin({left = 0, top = 10, right = 0, bottom  = 10} )
        
        
    local button_scale9 = Button:create()
    button_scale9:setTouchEnabled(true)
    button_scale9:loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "")
    button_scale9:setScale9Enabled(true)
    button_scale9:setSize(CCSize(100, button_scale9:getContentSize().height))
    layout:addChild(button_scale9)
        
    local lp3 = LinearLayoutParameter:create()
    button_scale9:setLayoutParameter(lp3)
    lp3:setGravity(ccs.UILinearGravity.centerHorizontal)
    lp3:setMargin({ left = 0, top = 10, right = 0, bottom  = 10 } )

end

function UIPanelLayoutLinearVerticalTest.create()
    local scene = CCScene:create()
    local layer = UIPanelLayoutLinearVerticalTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene   
end

local UIPanelLayoutLinearHorizontalTest = class("UIPanelLayoutLinearHorizontalTest",UIScene)

function UIPanelLayoutLinearHorizontalTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIPanelLayoutLinearHorizontalTest)
    return target
end

function UIPanelLayoutLinearHorizontalTest:initExtend()

    self:init()

    local widgetSize = self._widget:getSize()
        
    local alert = Label:create()
    alert:setText("Panel Layout Linear Horizontal")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 2.925))
    self._uiLayer:addWidget(alert)

    local background = self._uiLayer:getWidgetByName("background_Panel")
    
    local layout = Layout:create()
    layout:setLayoutType(ccs.LayoutType.linearHorizontal)
    layout:setClippingEnabled(true)
    layout:setSize(CCSize(280, 150))
    local backgroundSize = background:getContentSize()
    layout:setPosition(CCPoint((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout:getSize().width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout:getSize().height) / 2))
    self._uiLayer:addWidget(layout)
        
    local button = Button:create()
    button:setTouchEnabled(true)
    button:loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "")
    layout:addChild(button)
        
    local lp1 = LinearLayoutParameter:create()
    button:setLayoutParameter(lp1)
    lp1:setGravity(ccs.UILinearGravity.centerVertical)
    lp1:setMargin({left = 0, top  = 10, right = 0, bottom = 10} )
        
        
    local textButton = Button:create()
    textButton:setTouchEnabled(true)
    textButton:loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "")
    textButton:setTitleText("Text Button")
    layout:addChild(textButton)
        
    local lp2 = LinearLayoutParameter:create()
    textButton:setLayoutParameter(lp2)
    lp2:setGravity(ccs.UILinearGravity.centerVertical)
    lp2:setMargin({left = 0,top = 10,right = 0,bottom = 10})
        
        
    local button_scale9 = Button:create()
    button_scale9:setTouchEnabled(true)
    button_scale9:loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "")
    button_scale9:setScale9Enabled(true)
    button_scale9:setSize(CCSize(100, button_scale9:getContentSize().height))
    layout:addChild(button_scale9)
        
    local lp3 = LinearLayoutParameter:create()
    button_scale9:setLayoutParameter(lp3)
    lp3:setGravity(ccs.UILinearGravity.centerVertical)
    lp3:setMargin({left = 0, top = 10, right = 0, bottom = 10})

end

function UIPanelLayoutLinearHorizontalTest.create()
    local scene = CCScene:create()
    local layer = UIPanelLayoutLinearHorizontalTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene  
end

local UIScrollViewVerticalTest = class("UIScrollViewVerticalTest",UIScene)
UIScrollViewVerticalTest._displayValueLabel = nil

function UIScrollViewVerticalTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIScrollViewVerticalTest)
    return target
end

function UIScrollViewVerticalTest:initExtend()

    self:init()

    local widgetSize = self._widget:getSize()
        
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("Move by vertical direction")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 + self._displayValueLabel:getContentSize().height * 1.5))
    self._uiLayer:addWidget(self._displayValueLabel)
        
    local alert = Label:create()
    alert:setText("ScrollView")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 2.925))
    self._uiLayer:addWidget(alert)
        
    local background = self._uiLayer:getWidgetByName("background_Panel")
        
    local scrollView = ScrollView:create()
    scrollView:setTouchEnabled(true)
    scrollView:setSize(CCSize(280, 150))        
    local backgroundSize = background:getContentSize()
    scrollView:setPosition(CCPoint((widgetSize.width - backgroundSize.width) / 2 +
                               (backgroundSize.width - scrollView:getSize().width) / 2,
                               (widgetSize.height - backgroundSize.height) / 2 +
                               (backgroundSize.height - scrollView:getSize().height) / 2))
    self._uiLayer:addWidget(scrollView)
        
    local imageView = ImageView:create()
    imageView:loadTexture("cocosui/ccicon.png")
        
    local innerWidth = scrollView:getSize().width
    local innerHeight = scrollView:getSize().height + imageView:getSize().height
        
    scrollView:setInnerContainerSize(CCSize(innerWidth, innerHeight))                
        
    local button = Button:create()
    button:setTouchEnabled(true)
    button:loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "")
    button:setPosition(CCPoint(innerWidth / 2, scrollView:getInnerContainerSize().height - button:getSize().height / 2))
    scrollView:addChild(button)
        
    local textButton = Button:create()
    textButton:setTouchEnabled(true)
    textButton:loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "")
    textButton:setTitleText("Text Button")
    textButton:setPosition(CCPoint(innerWidth / 2, button:getBottomInParent() - button:getSize().height))
    scrollView:addChild(textButton)
        
    local button_scale9 = Button:create()
    button_scale9:setTouchEnabled(true)
    button_scale9:setScale9Enabled(true)
    button_scale9:loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "")
    button_scale9:setSize(CCSize(100, button_scale9:getContentSize().height))
    button_scale9:setPosition(CCPoint(innerWidth / 2, textButton:getBottomInParent() - textButton:getSize().height))
    scrollView:addChild(button_scale9)
        
    imageView:setPosition(CCPoint(innerWidth / 2, imageView:getSize().height / 2))
    scrollView:addChild(imageView)
end

function UIScrollViewVerticalTest.create()
    local scene = CCScene:create()
    local layer = UIScrollViewVerticalTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene  
end

local UIScrollViewHorizontalTest = class("UIScrollViewHorizontalTest",UIScene)
UIScrollViewHorizontalTest._displayValueLabel = nil

function UIScrollViewHorizontalTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIScrollViewHorizontalTest)
    return target
end

function UIScrollViewHorizontalTest:initExtend()
    
    self:init()

    local widgetSize = self._widget:getSize()
        
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("Move by horizontal direction")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 + self._displayValueLabel:getContentSize().height * 1.5))
    self._uiLayer:addWidget(self._displayValueLabel)            
        
    local alert = Label:create()
    alert:setText("ScrollView")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 2.925))
    self._uiLayer:addWidget(alert)
        
    local background = self._uiLayer:getWidgetByName("background_Panel")
        
    local scrollView = ScrollView:create()
    scrollView:setBounceEnabled(true)
    scrollView:setDirection(ccs.SCROLLVIEW_DIR.horizontal)
    scrollView:setTouchEnabled(true)
    scrollView:setSize(CCSize(280, 150))
    scrollView:setInnerContainerSize(scrollView:getSize())
    local backgroundSize = background:getContentSize()
    scrollView:setPosition(CCPoint((widgetSize.width - backgroundSize.width) / 2 +
                                    (backgroundSize.width - scrollView:getSize().width) / 2,
                                    (widgetSize.height - backgroundSize.height) / 2 +
                                    (backgroundSize.height - scrollView:getSize().height) / 2))
    self._uiLayer:addWidget(scrollView)
        
    local imageView = ImageView:create()
    imageView:loadTexture("cocosui/ccicon.png")
        
    local innerWidth = scrollView:getSize().width + imageView:getSize().width
    local innerHeight = scrollView:getSize().height
        
    scrollView:setInnerContainerSize(CCSize(innerWidth, innerHeight))
        
    local button = Button:create()
    button:setTouchEnabled(true)
    button:loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "")
    button:setPosition(CCPoint(button:getSize().width / 2,
                                scrollView:getInnerContainerSize().height - button:getSize().height / 2))
    scrollView:addChild(button)
        
    local textButton = Button:create()
    textButton:setTouchEnabled(true)
    textButton:loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "")
    textButton:setTitleText("Text Button")
    textButton:setPosition(CCPoint(button:getRightInParent() + button:getSize().width / 2,
                                    button:getBottomInParent() - button:getSize().height / 2))
    scrollView:addChild(textButton)
        
    local button_scale9 = Button:create()
    button_scale9:setTouchEnabled(true)
    button_scale9:setScale9Enabled(true)
    button_scale9:loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "")
    button_scale9:setSize(CCSize(100, button_scale9:getContentSize().height))
    button_scale9:setPosition(CCPoint(textButton:getRightInParent() + textButton:getSize().width / 2,
                                       textButton:getBottomInParent() - textButton:getSize().height / 2))
    scrollView:addChild(button_scale9)                
                
    imageView:setPosition(CCPoint(innerWidth - imageView:getSize().width / 2,
                                   button_scale9:getBottomInParent() - button_scale9:getSize().height / 2))
    scrollView:addChild(imageView)  
end

function UIScrollViewHorizontalTest.create()
    local scene = CCScene:create()
    local layer = UIScrollViewHorizontalTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene   
end

local UIPageViewTest = class("UIPageViewTest",UIScene)
UIPageViewTest._displayValueLabel = nil

function UIPageViewTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIPageViewTest)
    return target
end

function UIPageViewTest:initExtend()
    
    self:init()

    local widgetSize = self._widget:getSize()
        
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("Move by horizontal direction")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 + self._displayValueLabel:getContentSize().height * 1.5))
    self._uiLayer:addWidget(self._displayValueLabel)
        
    local alert = Label:create()
    alert:setText("PageView")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 2.925))
    self._uiLayer:addWidget(alert)
        
    local background = self._uiLayer:getWidgetByName("background_Panel")
        
    local pageView = PageView:create()
    pageView:setTouchEnabled(true)
    pageView:setSize(CCSize(240, 130))
    local backgroundSize = background:getContentSize()
    pageView:setPosition(CCPoint((widgetSize.width - backgroundSize.width) / 2 +
                                  (backgroundSize.width - pageView:getSize().width) / 2,
                                  (widgetSize.height - backgroundSize.height) / 2 +
                                  (backgroundSize.height - pageView:getSize().height) / 2))
      
    for i = 1 , 3 do
        local layout = Layout:create()
        layout:setSize(CCSize(240, 130))
            
        local imageView = ImageView:create()
        imageView:setTouchEnabled(true)
        imageView:setScale9Enabled(true)
        imageView:loadTexture("cocosui/scrollviewbg.png")
        imageView:setSize(CCSize(240, 130))
        imageView:setPosition(CCPoint(layout:getSize().width / 2, layout:getSize().height / 2))
        layout:addChild(imageView)
            
        local label = Label:create()
        local pageInfo = string.format("page %d", i)
        label:setText(pageInfo)
        label:setFontName(getFont())
        label:setFontSize(30)
        label:setColor(ccc3(192, 192, 192))
        label:setPosition(CCPoint(layout:getSize().width / 2, layout:getSize().height / 2))
        layout:addChild(label)
            
        pageView:addPage(layout)

    end 

    local function pageViewEvent(sender, eventType)
        if eventType == ccs.PageViewEventType.turning then
            local pageView = tolua.cast(sender, "PageView")
            local pageInfo = string.format("page %d " , pageView:getCurPageIndex() + 1)
            self._displayValueLabel:setText(pageInfo)
        end
    end 

    pageView:addEventListenerPageView(pageViewEvent)
        
    self._uiLayer:addWidget(pageView)
  
end

function UIPageViewTest.create()
    local scene = CCScene:create()
    local layer = UIPageViewTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene    
end

local UIListViewVerticalTest = class("UIListViewVerticalTest",UIScene)
UIListViewVerticalTest._displayValueLabel = nil
UIListViewVerticalTest._count   = 0
UIListViewVerticalTest._array   = nil

function UIListViewVerticalTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIListViewVerticalTest)
    return target
end

function UIListViewVerticalTest:initExtend()
    
    self:init()

    local widgetSize = self._widget:getSize()
        
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("Move by vertical direction")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 + self._displayValueLabel:getContentSize().height * 1.5))
    self._uiLayer:addWidget(self._displayValueLabel)
        
    local alert = Label:create()
    alert:setText("ListView")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 2.925))
    self._uiLayer:addWidget(alert)

    local background = self._uiLayer:getWidgetByName("background_Panel")

    self._count = 0
    self._array = CCArray:create()
    self._array:retain()

    for i = 0,19 do
        local objectInfo = string.format("object_%d",i) 
        self._array:addObject(CCString:create(objectInfo))
    end
        
        
    local lv = ListView:create()
    lv:setDirection(ccs.ListViewDirection.vertical)
    lv:setTouchEnabled(true)
    lv:setBounceEnabled(true)
    lv:setBackGroundImageScale9Enabled(true)
    lv:setBackGroundImage("cocosui/green_edit.png")
    lv:setSize(CCSizeMake(240, 130))

    local backgroundSize = background:getContentSize()
    lv:setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                              (backgroundSize.width - lv:getSize().width) / 2,
                              (widgetSize.height - backgroundSize.height) / 2 +
                              (backgroundSize.height - lv:getSize().height) / 2))

    local function listViewEvent(sender, eventType)
        if eventType == LISTVIEW_ONSELECTEDITEM_START then
            print("select child index = ",sender:getCurSelectedIndex())
        elseif eventType == LISTVIEW_ONSELECTEDITEM_END then
            print("select child index = ",sender:getCurSelectedIndex())
        end
    end
    lv:addEventListenerListView(listViewEvent)
    self._uiLayer:addWidget(lv)

    --create model
    local default_button = Button:create()
    default_button:setName("TextButton")
    default_button:setTouchEnabled(true)
    default_button:loadTextures("cocosui/backtotoppressed.png", "cocosui/backtotopnormal.png", "")
        
    local default_item = Layout:create()
    default_item:setTouchEnabled(true)
    default_item:setSize(default_button:getSize())
    default_button:setPosition(ccp(default_item:getSize().width / 2, default_item:getSize().height / 2))
    default_item:addChild(default_button)
        
    --set model
    lv:setItemModel(default_item)
        
    --add default item
    local count = self._array:count()
    for i = 1, math.floor(count / 4) do
        lv:pushBackDefaultItem()
    end

    --insert default item
    for i = 1 ,math.floor(count/4) do
        lv:insertDefaultItem(0)
    end
        
    --add custom item
    for i = 1, math.floor(count / 4) do
        local custom_button = Button:create()
        custom_button:setName("TextButton")
        custom_button:setTouchEnabled(true)
        custom_button:loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "")
        custom_button:setScale9Enabled(true)
        custom_button:setSize(default_button:getSize())
        
        local custom_item = Layout:create()
        custom_item:setSize(custom_button:getSize())
        custom_button:setPosition(ccp(custom_item:getSize().width / 2, custom_item:getSize().height / 2))
        custom_item:addChild(custom_button)
        
        lv:pushBackCustomItem(custom_item) 
    end

    --insert custom item
    local items = lv:getItems()
    local items_count = items:count()
    for i = 1, math.floor(count / 4) do
        local custom_button = Button:create()
        custom_button:setName("TextButton")
        custom_button:setTouchEnabled(true)
        custom_button:loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "")
        custom_button:setScale9Enabled(true)
        custom_button:setSize(default_button:getSize())
        
        local custom_item = Layout:create()
        custom_item:setSize(custom_button:getSize())
        custom_button:setPosition(ccp(custom_item:getSize().width / 2, custom_item:getSize().height / 2))
        custom_item:addChild(custom_button)
        
        lv:insertCustomItem(custom_item, items_count) 
    end
    
    --set item data
    items_count = items:count()
    for i = 1,math.floor(items_count) do
        local item = lv:getItem(i - 1)
        local button = tolua.cast(item:getChildByName("TextButton"),"Button")
        local index = lv:getIndex(item)
        button:setTitleText(self._array:objectAtIndex(index):getCString())
    end

    
    --remove last item
    lv:removeLastItem()
    
    --remove item by index
    items_count = items:count()
    lv:removeItem(items_count - 1)
    
    --set all items layout gravity
    lv:setGravity(LISTVIEW_GRAVITY_CENTER_VERTICAL)
end

function UIListViewVerticalTest.create()
    local scene = CCScene:create()
    local layer = UIListViewVerticalTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene   
end

local UIListViewHorizontalTest = class("UIListViewHorizontalTest",UIScene)
UIListViewHorizontalTest._displayValueLabel = nil
UIListViewHorizontalTest._count = 0
UIListViewHorizontalTest._array = nil

function UIListViewHorizontalTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIListViewHorizontalTest)
    return target
end

function UIListViewHorizontalTest:initExtend()
    
    self:init()

    local widgetSize = self._widget:getSize()
        
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("Move by horizontal direction")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 + self._displayValueLabel:getContentSize().height * 1.5))
    self._uiLayer:addWidget(self._displayValueLabel)
        
    local alert = Label:create()
    alert:setText("ListView")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 2.925))
    self._uiLayer:addWidget(alert)
        

    local background = self._uiLayer:getWidgetByName("background_Panel")

    self._count = 0
    self._array = CCArray:create()
    self._array:retain()

    for i=0,19 do
        local objectInfo = string.format("object_%d",i) 
        self._array:addObject(CCString:create(objectInfo))
    end
        
        
    local lv = ListView:create()
    lv:setDirection(SCROLLVIEW_DIR_HORIZONTAL)
    lv:setTouchEnabled(true)
    lv:setBounceEnabled(true)
    lv:setBackGroundImageScale9Enabled(true)
    lv:setBackGroundImage("cocosui/green_edit.png")
    lv:setSize(CCSizeMake(240, 130))

    local backgroundSize = background:getContentSize()
    lv:setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                              (backgroundSize.width - lv:getSize().width) / 2,
                              (widgetSize.height - backgroundSize.height) / 2 +
                              (backgroundSize.height - lv:getSize().height) / 2))

    local function listViewEvent(sender, eventType)
        if eventType == LISTVIEW_ONSELECTEDITEM_START then
            print("select child index = ",sender:getCurSelectedIndex())
        elseif eventType == LISTVIEW_ONSELECTEDITEM_END then
            print("select child index = ",sender:getCurSelectedIndex())
        end
    end
    lv:addEventListenerListView(listViewEvent)
    self._uiLayer:addWidget(lv)

    --create model
    local default_button = Button:create()
    default_button:setName("TextButton")
    default_button:setTouchEnabled(true)
    default_button:loadTextures("cocosui/backtotoppressed.png", "cocosui/backtotopnormal.png", "")
    
    local default_item = Layout:create()
    default_item:setTouchEnabled(true)
    default_item:setSize(default_button:getSize())
    default_button:setPosition(ccp(default_item:getSize().width / 2, default_item:getSize().height / 2))
    default_item:addChild(default_button)
    
    --set model
    lv:setItemModel(default_item)
    
    --add default item
    local count = self._array:count()
    for i = 1,math.floor(count / 4 ) do
        lv:pushBackDefaultItem()
    end

    -- insert default item
    for i = 1,math.floor(count / 4) do
        lv:insertDefaultItem(0)
    end

    
    -- add custom item
    for i = 1,math.floor(count / 4) do
        local custom_button = Button:create()
        custom_button:setName("TextButton")
        custom_button:setTouchEnabled(true)
        custom_button:loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "")
        custom_button:setScale9Enabled(true)
        custom_button:setSize(default_button:getSize())
        
        local custom_item = Layout:create()
        custom_item:setSize(custom_button:getSize())
        custom_button:setPosition(ccp(custom_item:getSize().width / 2, custom_item:getSize().height / 2))
        custom_item:addChild(custom_button)
        
        lv:pushBackCustomItem(custom_item)
    end

    --insert custom item
    local items = lv:getItems()
    local items_count = items:count()
    for i = 1, math.floor(count/4) do
        local custom_button = Button:create()
        custom_button:setName("TextButton")
        custom_button:setTouchEnabled(true)
        custom_button:loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "")
        custom_button:setScale9Enabled(true)
        custom_button:setSize(default_button:getSize())
        
        local custom_item = Layout:create()
        custom_item:setSize(custom_button:getSize())
        custom_button:setPosition(ccp(custom_item:getSize().width / 2, custom_item:getSize().height / 2))
        custom_item:addChild(custom_button)
        
        lv:insertCustomItem(custom_item, items_count) 
    end
    
    --set item data
    items_count = items:count()
    for i = 1, items_count do
        local item = lv:getItem(i - 1)
        local button = tolua.cast(item:getChildByName("TextButton"),"Button")
        local index = lv:getIndex(item)
        button:setTitleText(self._array:objectAtIndex(index):getCString())
    end
    
    -- remove last item
    lv:removeLastItem()
    
    --remove item by index
    items_count = items:count()
    lv:removeItem(items_count - 1)        
    
    --set all items layout gravity
    lv:setGravity(LISTVIEW_GRAVITY_CENTER_VERTICAL)
    
    --set items margin
    lv:setItemsMargin(2)
end

function UIListViewHorizontalTest.create()
    local scene = CCScene:create()
    local layer = UIListViewHorizontalTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene  
end

local UIDragPanelTest = class("UIDragPanelTest",UIScene)
UIDragPanelTest._displayValueLabel = nil

function UIDragPanelTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIDragPanelTest)
    return target
end

function UIDragPanelTest:initExtend()
    
    self:init()

    local widgetSize = self._widget:getSize()
        
    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 + self._displayValueLabel:getSize().height * 1.5))
    self._uiLayer:addWidget(self._displayValueLabel)
        
    local alert = Label:create()
    alert:setText("DragPanel")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 2.925))
    self._uiLayer:addWidget(alert)
        
    local sc = ScrollView:create()
    sc:setBackGroundColor(ccc3(0,255,0))
    sc:setBackGroundColorType(ccs.LayoutBackGroundColorType.solid)
    sc:setDirection(ccs.SCROLLVIEW_DIR.both)
    sc:setInnerContainerSize(CCSize(480, 320))
    sc:setSize(CCSize(100,100))
    sc:setPosition(CCPoint(100,100))
    sc:scrollToPercentBothDirection(CCPoint(50, 50), 1, true)
    local iv = ImageView:create()
    iv:loadTexture("cocosui/Hello.png")
    iv:setPosition(CCPoint(240, 160))
    sc:addChild(iv)
    self._uiLayer:addWidget(sc)

end

function UIDragPanelTest.create()
    local scene = CCScene:create()
    local layer = UIDragPanelTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene
end

local UIDragPanelBounceTest = class("UIDragPanelBounceTest",UIScene)
UIDragPanelBounceTest._displayValueLabel = nil

function UIDragPanelBounceTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIDragPanelBounceTest)
    return target
end

function UIDragPanelBounceTest:initExtend()
    
    self:init()

    local widgetSize = self._widget:getSize()

    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 + self._displayValueLabel:getSize().height * 1.5))
    self._uiLayer:addWidget(self._displayValueLabel)        
        

    local alert = Label:create()
    alert:setText("DragPanel Bounce")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 2.925))
    self._uiLayer:addWidget(alert)
        
    local sc = ScrollView:create()
    sc:setBackGroundColor(ccc3(0, 255 , 0))
    sc:setBackGroundColorType(ccs.LayoutBackGroundColorType.solid)
    sc:setBounceEnabled(true)
    sc:setDirection(ccs.SCROLLVIEW_DIR.both)
    sc:setInnerContainerSize(CCSize(480, 320))
    sc:setSize(CCSize(100,100))
    sc:setPosition(CCPoint(100,100))
    sc:scrollToPercentBothDirection(CCPoint(50, 50), 1, true)
    local iv = ImageView:create()
    iv:loadTexture("cocosui/Hello.png")
    iv:setPosition(CCPoint(240, 160))
    sc:addChild(iv)
    self._uiLayer:addWidget(sc)
end

function UIDragPanelBounceTest.create()
    local scene = CCScene:create()
    local layer = UIDragPanelBounceTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene  
end

local UINodeContainerTest = class("UINodeContainerTest",UIScene)
UINodeContainerTest._displayValueLabel = nil

function UINodeContainerTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UINodeContainerTest)
    return target
end

function UINodeContainerTest:initExtend()
    
    self:init()

    local widgetSize = self._widget:getSize()

    self._displayValueLabel = Label:create()
    self._displayValueLabel:setText("NodeContainer Add CCNode")
    self._displayValueLabel:setFontName(getFont())
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(CCPoint(0.5, -1))
    self._displayValueLabel:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 + self._displayValueLabel:getContentSize().height * 1.5))
    self._uiLayer:addWidget(self._displayValueLabel)
        
    local alert = Label:create()
    alert:setText("NodeContainer")
    alert:setFontName(getFont())
    alert:setFontSize(30)
    alert:setColor(ccc3(159, 168, 176))
    alert:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)
        
    local nodeContainer = Widget:create()
    nodeContainer:setPosition(CCPoint(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addWidget(nodeContainer)
        
    -- local sprite = CCSprite:create("cocosui/ccicon.png")
    -- sprite:setPosition(CCPoint(0, sprite:boundingBox().size.height / 4))
    -- nodeContainer:addRenderer(sprite, 0)
end

function UINodeContainerTest.create()
    local scene = CCScene:create()
    local layer = UINodeContainerTest.extend(CCLayer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene   
end

local cocoStudioGuiArray = 
{
    {
        title = "UIButtonTest",
        func  = function () 
            return UIButtonTest.create()
        end,
    },

    {
        title = "UIButtonScale9Test",
        func  = function ()
            return UIButtonScale9Test.create()
        end,
    },

    {
        title = "ButtonPressedActionTest",
        func  = function ()
            return UIButtonPressedActionTest.create()
        end,
    },

    {
        title = "UITextButtonTest",
        func  = function ()
            return UITextButtonTest.create()
        end,
    },

    {
        title = "UITextButtonScale9Test",
        func  = function ()
            return UITextButtonScale9Test.create()
        end,
    },

    {
        title = "UICheckBoxTest",
        func  = function ()
            return UICheckBoxTest.create()
        end,
    },

    {
        title = "UISliderTest",
        func  = function ()
            return UISliderTest.create()
        end,
    },

    {
        title = "UISliderScale9Test",
        func  = function ()
            return UISliderScale9Test.create()
        end,
    },

    {
        title = "UIImageViewTest",
        func  = function ( )
            return UIImageViewTest.create()
        end,
    },

    {
        title = "UIImageViewScale9Test",
        func  = function ( )
            return UIImageViewScale9Test.create()
        end,
    },

    {
        title = "UILoadingBarLeftTest",
        func  = function ( )
            return UILoadingBarLeftTest.create()
        end,
    },

    {
        title = "UILoadingBarRightTest",
        func  = function ( )
            return UILoadingBarRightTest.create()
        end,
    },

    {
        title = "UILoadingBarLeftScale9Test",
        func  = function ( )
            return UILoadingBarLeftScale9Test.create()
        end,
    },

    {
        title = "UILoadingBarRightScale9Test",
        func  = function ( )
            return UILoadingBarRightScale9Test.create()
        end,
    },

    {
        title = "UILabelAtlasTest",
        func  = function ( )
            return UILabelAtlasTest.create()
        end,
    },

    {
        title = "UILabelBMFontTest",
        func  = function ( )
            return UILabelBMFontTest.create()
        end,
    },

    {
        title = "UILabelTest",
        func  = function ( )
            return UILabelTest.create()
        end,
    },

    {
        title = "UITextAreaTest",
        func  = function ( )
            return UITextAreaTest.create()
        end,
    },

    {
        title = "UITextFieldTest",
        func  = function ( )
            return UITextFieldTest.create()
        end,
    },

    {
        title = "UITextFieldMaxLengthTest",
        func  = function ( )
            return UITextFieldMaxLengthTest.create()
        end,
    },

    {
        title = "UITextFieldPasswordTest",
        func  = function ( )
            return UITextFieldPasswordTest.create()
        end,
    },

    {
        title = "UIPanelTest",
        func  = function ( )
            return UIPanelTest.create()
        end,
    },

    {
        title = "UIPanelColorTest",
        func  = function ( )
            return UIPanelColorTest.create()
        end,
    },

    {
        title = "UIPanelGradientTest",
        func  = function ( )
            return UIPanelGradientTest.create()
        end,
    },

    {
        title = "UIPanelBackGroundImageTest",
        func  = function ( )
            return UIPanelBackGroundImageTest.create()
        end,
    },

    {
        title = "UIPanelBackGroundImageScale9Test",
        func  = function ( )
            return UIPanelBackGroundImageScale9Test.create()
        end,
    },

    {
        title = "UIPanelLayoutLinearVerticalTest",
        func  = function ( )
            return UIPanelLayoutLinearVerticalTest.create()
        end,
    },

    {
        title = "UIPanelLayoutLinearHorizontalTest",
        func  = function ( )
            return UIPanelLayoutLinearHorizontalTest.create()
        end,
    },

    {
        title = "UIScrollViewVerticalTest",
        func  = function ( )
            return UIScrollViewVerticalTest.create()
        end,
    },

    {
        title = "UIScrollViewHorizontalTest",
        func  = function ( )
            return UIScrollViewHorizontalTest.create()
        end,
    },

    {
        title = "UIPageViewTest",
        func  = function ( )
            return UIPageViewTest.create()
        end,
    },

    {
        title = "UIListViewVerticalTest",
        func  = function ()
            return UIListViewVerticalTest.create()
        end,
    },

    {
        title = "UIListViewHorizontalTest",
        func  = function ()
            return UIListViewHorizontalTest.create()
        end,
    },

    {
        title = "UIDragPanelTest",
        func  = function ()
            return UIDragPanelTest.create()
        end,
    },

    {
        title = "UIDragPanelBounceTest",
        func  = function ()
            return UIDragPanelBounceTest.create()
        end,
    },

    {
        title = "UINodeContainerTest",
        func  = function ()
            return UINodeContainerTest.create()
        end,
    },
}

function guiSceneManager.nextUIScene()
    guiSceneManager.currentUISceneIdx = (guiSceneManager.currentUISceneIdx + 1) % table.getn(cocoStudioGuiArray)
    if 0 == guiSceneManager.currentUISceneIdx  then
        guiSceneManager.currentUISceneIdx  = table.getn(cocoStudioGuiArray)
    end

    return cocoStudioGuiArray[guiSceneManager.currentUISceneIdx].func()
end

function guiSceneManager.previousUIScene()

    guiSceneManager.currentUISceneIdx = guiSceneManager.currentUISceneIdx - 1
    if guiSceneManager.currentUISceneIdx <= 0 then
        guiSceneManager.currentUISceneIdx = guiSceneManager.currentUISceneIdx + table.getn(cocoStudioGuiArray)
    end

    return cocoStudioGuiArray[guiSceneManager.currentUISceneIdx].func()
end

function guiSceneManager.currentUIScene()
    return cocoStudioGuiArray[guiSceneManager.currentUISceneIdx].func()
end



function runCocosGUITestScene()
   local scene = guiSceneManager.currentUIScene()
   CCDirector:sharedDirector():replaceScene(scene)
end
