require "luaScript/CocoStudioTest/CocoStudioGUITest/UIScene"

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
    self._uiLayer = ccs.UILayer:create()
    self:addChild(self._uiLayer)

    self._widget = ccs.CCSGUIReader:getInstance():widgetFromJsonFile("cocosgui/UITest/UITest.json")
    self._uiLayer:addWidget(self._widget)

    self._sceneTitle = self._uiLayer:getWidgetByName("UItest")

    local back_label = self._uiLayer:getWidgetByName("back")
    back_label:setVisible(false)

    local function previousCallback(sender, eventType)
        if eventType == ccs.TouchEventType.ended then
            self._uiLayer:removeFromParent()
            cc.Director:getInstance():replaceScene(guiSceneManager.previousUIScene())
        end
    end

    local left_button = self._uiLayer:getWidgetByName("left_Button")
    left_button:addTouchEventListener(previousCallback)

    local function restartCallback(sender, eventType)
         if eventType == ccs.TouchEventType.ended then
             self._uiLayer:removeFromParent()
             cc.Director:getInstance():replaceScene(guiSceneManager.currentUIScene())
         end
    end

    local middle_button = self._uiLayer:getWidgetByName("middle_Button")
    middle_button:addTouchEventListener(restartCallback)

    local function nextCallback(sender, eventType)
        if eventType == ccs.TouchEventType.ended then
            self._uiLayer:removeFromParent()
            cc.Director:getInstance():replaceScene(guiSceneManager.nextUIScene())
        end
    end

    local right_button = self._uiLayer:getWidgetByName("right_Button")
    right_button:addTouchEventListener(nextCallback)

    local function menuCloseCallback( sender,eventType)
        if eventType == ccs.TouchEventType.ended then
            self._uiLayer:removeFromParent()
            local scene = CocoStudioTestMain()
            if scene ~= nil then
                cc.Director:getInstance():replaceScene(scene)
            end
        end
    end

    local mainMenuLabel = ccs.UILabel:create()
    mainMenuLabel:setText("MainMenu")
    mainMenuLabel:setFontSize(20)
    mainMenuLabel:setTouchScaleChangeEnabled(true)
    mainMenuLabel:setPosition(cc.p(430,30))
    mainMenuLabel:setTouchEnabled(true)
    mainMenuLabel:addTouchEventListener(menuCloseCallback)
    self._uiLayer:addWidget(mainMenuLabel)  
end

function UIScene.create()
    local scene = UIScene.extend(cc.Scene:create())
    scene:init()
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
        
    self._displayValueLabel = ccs.UILabel:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(font_UIButtonTest)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addWidget(self._displayValueLabel)        
        
    local alert = ccs.UILabel:create()
    alert:setText("Button")
    alert:setFontName(font_UIButtonTest)
    alert:setFontSize(30)        
    alert:setColor(cc.c3b(159, 168, 176))                
        
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
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
    local button = ccs.UIButton:create()
    button:setTouchEnabled(true)
    button:loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "")
    button:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))        
    button:addTouchEventListener(touchEvent)
    self._uiLayer:addWidget(button)
end

function UIButtonTest.create()
    local scene = UIButtonTest.extend(cc.Scene:create())
    scene:initExtend()
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
        
    self._displayValueLabel = ccs.UILabel:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(font_UIButtonTest)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addWidget(self._displayValueLabel)
        
    local alert = ccs.UILabel:create()
    alert:setText("Button scale9 render")
    alert:setFontName(font_UIButtonTest)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
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
        
    local button = ccs.UIButton:create()
    button:setTouchEnabled(true)
    button:setScale9Enabled(true)
    button:loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "")
    button:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    button:setSize(cc.size(150, button:getContentSize().height * 1.5))
    button:addTouchEventListener(touchEvent)
    self._uiLayer:addWidget(button)
end

function UIButtonScale9Test.create()
    local scene = UIButtonScale9Test.extend(cc.Scene:create())
    scene:initExtend()
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
        
    
    self._displayValueLabel = ccs.UILabel:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(font_UIButtonTest)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addWidget(self._displayValueLabel)
        
    local alert = ccs.UILabel:create()
    alert:setText("Button Pressed Action")
    alert:setFontName(font_UIButtonTest)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))    
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
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
        
    local button = ccs.UIButton:create()
    button:setTouchEnabled(true)
    button:setPressedActionEnabled(true)
    button:loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "")
    button:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    button:addTouchEventListener(touchEvent)        
    self._uiLayer:addWidget(button)
end

function UIButtonPressedActionTest.create()
    local scene = UIButtonPressedActionTest.extend(cc.Scene:create())
    scene:initExtend()
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
        
    
    self._displayValueLabel = ccs.UILabel:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(font_UIButtonTest)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addWidget(self._displayValueLabel)
        
    local alert = ccs.UILabel:create()
    alert:setText("TextButton")
    alert:setFontName(font_UIButtonTest)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))    
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
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
        
    local textButton = ccs.UIButton:create()
    textButton:setTouchEnabled(true)
    textButton:loadTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "")
    textButton:setTitleText("Text Button")
    textButton:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    textButton:addTouchEventListener(touchEvent)        
    self._uiLayer:addWidget(textButton)
end

function UITextButtonTest.create()
    local scene = UITextButtonTest.extend(cc.Scene:create())
    scene:initExtend()
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
          
    self._displayValueLabel = ccs.UILabel:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(font_UIButtonTest)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addWidget(self._displayValueLabel)
        
    local alert = ccs.UILabel:create()
    alert:setText("TextButton scale9 render")
    alert:setFontName(font_UIButtonTest)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))    
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
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
        
    local textButton = ccs.UIButton:create()
    textButton:setTouchEnabled(true)
    textButton:setScale9Enabled(true)
    textButton:loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "")
    textButton:setSize(cc.size(180, textButton:getContentSize().height * 1.5))
    textButton:setTitleText("Text Button scale9 render")
    textButton:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    textButton:addTouchEventListener(touchEvent)        
    self._uiLayer:addWidget(textButton)
end

function UITextButtonScale9Test.create()
    local scene = UITextButtonScale9Test.extend(cc.Scene:create())
    scene:initExtend()
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
          
    self._displayValueLabel = ccs.UILabel:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(font_UIButtonTest)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addWidget(self._displayValueLabel)
        
    local alert = ccs.UILabel:create()
    alert:setText("CheckBox")
    alert:setFontName(font_UICheckBoxTest)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))    
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)

    local function selectedEvent(sender,eventType)
        if eventType == ccs.CheckBoxEventType.selected then
            self._displayValueLabel:setText("Selected")
        elseif eventType == ccs.CheckBoxEventType.unselected then
            self._displayValueLabel:setText("Unselected")
        end
    end  
        
    local checkBox = ccs.UICheckBox:create()
    checkBox:setTouchEnabled(true)
    checkBox:loadTextures("cocosgui/check_box_normal.png",
                               "cocosgui/check_box_normal_press.png",
                               "cocosgui/check_box_active.png",
                               "cocosgui/check_box_normal_disable.png",
                               "cocosgui/check_box_active_disable.png")
    checkBox:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
        
    checkBox:addEventListener(selectedEvent)  

    self._uiLayer:addWidget(checkBox)
end

function UICheckBoxTest.create()
    local scene = UICheckBoxTest.extend(cc.Scene:create())
    scene:initExtend()
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
          
    self._displayValueLabel = ccs.UILabel:create()
    self._displayValueLabel:setText("Move the slider thumb")
    self._displayValueLabel:setFontName(font_UISliderTest)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addWidget(self._displayValueLabel)
        
    local alert = ccs.UILabel:create()
    alert:setText("Slider")
    alert:setFontName(font_UISliderTest)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))    
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)

    local function percentChangedEvent(sender,eventType)
        if eventType == ccs.SliderEventType.percent_changed then
            local slider = tolua.cast(sender,"UISlider")
            local percent = "Percent " .. slider:getPercent()
            self._displayValueLabel:setText(percent)
        end
    end  
        
    local slider = ccs.UISlider:create()
    slider:setTouchEnabled(true)
    slider:loadBarTexture("cocosgui/sliderTrack.png")
    slider:loadSlidBallTextures("cocosgui/sliderThumb.png", "cocosgui/sliderThumb.png", "")
    slider:loadProgressBarTexture("cocosgui/sliderProgress.png")
    slider:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    slider:addEventListener(percentChangedEvent)

    self._uiLayer:addWidget(slider)
end

function UISliderTest.create()
    local scene = UISliderTest.extend(cc.Scene:create())
    scene:initExtend()
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
          
    self._displayValueLabel = ccs.UILabel:create()
    self._displayValueLabel:setText("Move the slider thumb")
    self._displayValueLabel:setFontName(font_UISliderTest)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addWidget(self._displayValueLabel)
        
    local alert = ccs.UILabel:create()
    alert:setText("Slider scale9 render")
    alert:setFontName(font_UISliderTest)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))    
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)

    local function percentChangedEvent(sender,eventType)
        if eventType == ccs.SliderEventType.percent_changed then
            local slider = tolua.cast(sender,"UISlider")
            local percent = "Percent " .. slider:getPercent()
            self._displayValueLabel:setText(percent)
        end
    end  
        
    local slider = ccs.UISlider:create()
    slider:setTouchEnabled(true)
    slider:loadBarTexture("cocosgui/sliderTrack2.png")
    slider:loadSlidBallTextures("cocosgui/sliderThumb.png", "cocosgui/sliderThumb.png", "")
    slider:loadProgressBarTexture("cocosgui/slider_bar_active_9patch.png")
    slider:setScale9Enabled(true)
    slider:setCapInsets(cc.rect(0, 0, 0, 0))
    slider:setSize(cc.size(250, 10))
    slider:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    slider:addEventListener(percentChangedEvent)

    self._uiLayer:addWidget(slider)
end

function UISliderScale9Test.create()
    local scene = UISliderScale9Test.extend(cc.Scene:create())
    scene:initExtend()
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
        
    local alert = ccs.UILabel:create()
    alert:setText("ImageView")
    alert:setFontName(font_UIImageViewTest)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))    
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)
        
    local imageView = ccs.UIImageView:create()
    imageView:loadTexture("cocosgui/ccicon.png")
    imageView:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + imageView:getSize().height / 4.0))
    self._uiLayer:addWidget(imageView)
end

function UIImageViewTest.create()
    local scene = UIImageViewTest.extend(cc.Scene:create())
    scene:initExtend()
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
        
    local alert = ccs.UILabel:create()
    alert:setText("ImageView scale9 render")
    alert:setFontName(font_UIImageViewTest)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))    
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)
        
    local imageView = ccs.UIImageView:create()
    imageView:setScale9Enabled(true)
    imageView:loadTexture("cocosgui/buttonHighlighted.png")
    imageView:setSize(cc.size(200, 85))
    imageView:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + imageView:getSize().height / 4.0))
    self._uiLayer:addWidget(imageView)
end

function UIImageViewScale9Test.create()
    local scene = UIImageViewScale9Test.extend(cc.Scene:create())
    scene:initExtend()
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

    self._uiLayer = ccs.UILayer:create()
    self:addChild(self._uiLayer)

    self._widget = ccs.CCSGUIReader:getInstance():widgetFromJsonFile("cocosgui/UITest/UITest.json")
    self._uiLayer:addWidget(self._widget)

    self._sceneTitle = self._uiLayer:getWidgetByName("UItest")

    local back_label = self._uiLayer:getWidgetByName("back")
    back_label:setVisible(false)

    local widgetSize = self._widget:getSize()
        
    local alert = ccs.UILabel:create()
    alert:setText("LoadingBar")
    alert:setFontName(font_UILoadingBarTest)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))    
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)
        
    local loadingBar = ccs.UILoadingBar:create()
    loadingBar:setName("LoadingBar")
    loadingBar:loadTexture("cocosgui/sliderProgress.png")
    loadingBar:setPercent(0)
        
    loadingBar:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + loadingBar:getSize().height / 4.0))
    self._uiLayer:addWidget(loadingBar)

    local function update(delta)
        self._count = self._count + 1
        if self._count > 100 then
            self._count = 0
        end

        if self._uiLayer ~= nil then
            local loadingBar = tolua.cast(self._uiLayer:getWidgetByName("LoadingBar"), "UILoadingBar")
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
            self._uiLayer:removeFromParent()
            cc.Director:getInstance():replaceScene(guiSceneManager.previousUIScene())
        end
    end

    local left_button = self._uiLayer:getWidgetByName("left_Button")
    left_button:addTouchEventListener(previousCallback)

    local function restartCallback(sender, eventType)
         if eventType == ccs.TouchEventType.ended then
             self:unscheduleUpdate()
             self._uiLayer:removeFromParent()
             cc.Director:getInstance():replaceScene(guiSceneManager.currentUIScene())
         end
    end

    local middle_button = self._uiLayer:getWidgetByName("middle_Button")
    middle_button:addTouchEventListener(restartCallback)

    local function nextCallback(sender, eventType)
        if eventType == ccs.TouchEventType.ended then
            self:unscheduleUpdate()
            self._uiLayer:removeFromParent()
            cc.Director:getInstance():replaceScene(guiSceneManager.nextUIScene())
        end
    end

    local right_button = self._uiLayer:getWidgetByName("right_Button")
    right_button:addTouchEventListener(nextCallback)

    local function menuCloseCallback( sender,eventType)
        if eventType == ccs.TouchEventType.ended then
            self:unscheduleUpdate()
            self._uiLayer:removeFromParent()
            local scene = CocoStudioTestMain()
            if scene ~= nil then
                cc.Director:getInstance():replaceScene(scene)
            end
        end
    end

    local mainMenuLabel = ccs.UILabel:create()
    mainMenuLabel:setText("MainMenu")
    mainMenuLabel:setFontSize(20)
    mainMenuLabel:setTouchScaleChangeEnabled(true)
    mainMenuLabel:setPosition(cc.p(430,30))
    mainMenuLabel:setTouchEnabled(true)
    mainMenuLabel:addTouchEventListener(menuCloseCallback)
    self._uiLayer:addWidget(mainMenuLabel)  
end

function UILoadingBarLeftTest.create()
    local scene = UILoadingBarLeftTest.extend(cc.Scene:create())
    scene:initExtend()
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

    self._uiLayer = ccs.UILayer:create()
    self:addChild(self._uiLayer)

    self._widget = ccs.CCSGUIReader:getInstance():widgetFromJsonFile("cocosgui/UITest/UITest.json")
    self._uiLayer:addWidget(self._widget)

    self._sceneTitle = self._uiLayer:getWidgetByName("UItest")

    local back_label = self._uiLayer:getWidgetByName("back")
    back_label:setVisible(false)

    local widgetSize = self._widget:getSize()
        
    local alert = ccs.UILabel:create()
    alert:setText("LoadingBar")
    alert:setFontName(font_UILoadingBarTest)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))    
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)
        
    local loadingBar = ccs.UILoadingBar:create()
    loadingBar:setName("LoadingBar")
    loadingBar:loadTexture("cocosgui/sliderProgress.png")
    loadingBar:setDirection(ccs.LoadingBarType.right)
    loadingBar:setPercent(0)
        
    loadingBar:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + loadingBar:getSize().height / 4.0))
    self._uiLayer:addWidget(loadingBar)

    local function update(delta)
        self._count = self._count + 1
        if self._count > 100 then
            self._count = 0
        end

        if self._uiLayer ~= nil then
            local loadingBar = tolua.cast(self._uiLayer:getWidgetByName("LoadingBar"), "UILoadingBar")
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
            self._uiLayer:removeFromParent()
            cc.Director:getInstance():replaceScene(guiSceneManager.previousUIScene())
        end
    end

    local left_button = self._uiLayer:getWidgetByName("left_Button")
    left_button:addTouchEventListener(previousCallback)

    local function restartCallback(sender, eventType)
         if eventType == ccs.TouchEventType.ended then
             self:unscheduleUpdate()
             self._uiLayer:removeFromParent()
             cc.Director:getInstance():replaceScene(guiSceneManager.currentUIScene())
         end
    end

    local middle_button = self._uiLayer:getWidgetByName("middle_Button")
    middle_button:addTouchEventListener(restartCallback)

    local function nextCallback(sender, eventType)
        if eventType == ccs.TouchEventType.ended then
            self:unscheduleUpdate()
            self._uiLayer:removeFromParent()
            cc.Director:getInstance():replaceScene(guiSceneManager.nextUIScene())
        end
    end

    local right_button = self._uiLayer:getWidgetByName("right_Button")
    right_button:addTouchEventListener(nextCallback)

    local function menuCloseCallback( sender,eventType)
        if eventType == ccs.TouchEventType.ended then
            self:unscheduleUpdate()
            self._uiLayer:removeFromParent()
            local scene = CocoStudioTestMain()
            if scene ~= nil then
                cc.Director:getInstance():replaceScene(scene)
            end
        end
    end

    local mainMenuLabel = ccs.UILabel:create()
    mainMenuLabel:setText("MainMenu")
    mainMenuLabel:setFontSize(20)
    mainMenuLabel:setTouchScaleChangeEnabled(true)
    mainMenuLabel:setPosition(cc.p(430,30))
    mainMenuLabel:setTouchEnabled(true)
    mainMenuLabel:addTouchEventListener(menuCloseCallback)
    self._uiLayer:addWidget(mainMenuLabel)  
end

function UILoadingBarRightTest.create()
    local scene = UILoadingBarRightTest.extend(cc.Scene:create())
    scene:initExtend()
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

    self._uiLayer = ccs.UILayer:create()
    self:addChild(self._uiLayer)

    self._widget = ccs.CCSGUIReader:getInstance():widgetFromJsonFile("cocosgui/UITest/UITest.json")
    self._uiLayer:addWidget(self._widget)

    self._sceneTitle = self._uiLayer:getWidgetByName("UItest")

    local back_label = self._uiLayer:getWidgetByName("back")
    back_label:setVisible(false)

    local widgetSize = self._widget:getSize()
        
    local alert = ccs.UILabel:create()
    alert:setText("LoadingBar Scale9 Render")
    alert:setFontName(font_UILoadingBarTest)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))    
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)
        
    local loadingBar = ccs.UILoadingBar:create()
    loadingBar:setName("LoadingBar")
    loadingBar:loadTexture("cocosgui/slider_bar_active_9patch.png")
    loadingBar:setScale9Enabled(true)
    loadingBar:setCapInsets(cc.rect(0, 0, 0, 0))
    loadingBar:setSize(cc.size(300, 30))
    loadingBar:setPercent(0)
        
    loadingBar:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + loadingBar:getSize().height / 4.0))
    self._uiLayer:addWidget(loadingBar)

    local function update(delta)
        self._count = self._count + 1
        if self._count > 100 then
            self._count = 0
        end

        if self._uiLayer ~= nil then
            local loadingBar = tolua.cast(self._uiLayer:getWidgetByName("LoadingBar"), "UILoadingBar")
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
            self._uiLayer:removeFromParent()
            cc.Director:getInstance():replaceScene(guiSceneManager.previousUIScene())
        end
    end

    local left_button = self._uiLayer:getWidgetByName("left_Button")
    left_button:addTouchEventListener(previousCallback)

    local function restartCallback(sender, eventType)
         if eventType == ccs.TouchEventType.ended then
             self:unscheduleUpdate()
             self._uiLayer:removeFromParent()
             cc.Director:getInstance():replaceScene(guiSceneManager.currentUIScene())
         end
    end

    local middle_button = self._uiLayer:getWidgetByName("middle_Button")
    middle_button:addTouchEventListener(restartCallback)

    local function nextCallback(sender, eventType)
        if eventType == ccs.TouchEventType.ended then
            self:unscheduleUpdate()
            self._uiLayer:removeFromParent()
            cc.Director:getInstance():replaceScene(guiSceneManager.nextUIScene())
        end
    end

    local right_button = self._uiLayer:getWidgetByName("right_Button")
    right_button:addTouchEventListener(nextCallback)

    local function menuCloseCallback( sender,eventType)
        if eventType == ccs.TouchEventType.ended then
            self:unscheduleUpdate()
            self._uiLayer:removeFromParent()
            local scene = CocoStudioTestMain()
            if scene ~= nil then
                cc.Director:getInstance():replaceScene(scene)
            end
        end
    end

    local mainMenuLabel = ccs.UILabel:create()
    mainMenuLabel:setText("MainMenu")
    mainMenuLabel:setFontSize(20)
    mainMenuLabel:setTouchScaleChangeEnabled(true)
    mainMenuLabel:setPosition(cc.p(430,30))
    mainMenuLabel:setTouchEnabled(true)
    mainMenuLabel:addTouchEventListener(menuCloseCallback)
    self._uiLayer:addWidget(mainMenuLabel)  
end

function UILoadingBarLeftScale9Test.create()
    local scene = UILoadingBarLeftScale9Test.extend(cc.Scene:create())
    scene:initExtend()
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

    self._uiLayer = ccs.UILayer:create()
    self:addChild(self._uiLayer)

    self._widget = ccs.CCSGUIReader:getInstance():widgetFromJsonFile("cocosgui/UITest/UITest.json")
    self._uiLayer:addWidget(self._widget)

    self._sceneTitle = self._uiLayer:getWidgetByName("UItest")

    local back_label = self._uiLayer:getWidgetByName("back")
    back_label:setVisible(false)

    local widgetSize = self._widget:getSize()
        
    local alert = ccs.UILabel:create()
    alert:setText("LoadingBar Scale9 Render")
    alert:setFontName(font_UILoadingBarTest)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))    
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)
        
    local loadingBar = ccs.UILoadingBar:create()
    loadingBar:setName("LoadingBar")
    loadingBar:loadTexture("cocosgui/slider_bar_active_9patch.png")
    loadingBar:setScale9Enabled(true)
    loadingBar:setCapInsets(cc.rect(0, 0, 0, 0))
    loadingBar:setSize(cc.size(300, 30))
    loadingBar:setDirection(ccs.LoadingBarType.right)
    loadingBar:setPercent(0)
        
    loadingBar:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + loadingBar:getSize().height / 4.0))
    self._uiLayer:addWidget(loadingBar)

    local function update(delta)
        self._count = self._count + 1
        if self._count > 100 then
            self._count = 0
        end

        if self._uiLayer ~= nil then
            local loadingBar = tolua.cast(self._uiLayer:getWidgetByName("LoadingBar"), "UILoadingBar")
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
            self._uiLayer:removeFromParent()
            cc.Director:getInstance():replaceScene(guiSceneManager.previousUIScene())
        end
    end

    local left_button = self._uiLayer:getWidgetByName("left_Button")
    left_button:addTouchEventListener(previousCallback)

    local function restartCallback(sender, eventType)
         if eventType == ccs.TouchEventType.ended then
             self:unscheduleUpdate()
             self._uiLayer:removeFromParent()
             cc.Director:getInstance():replaceScene(guiSceneManager.currentUIScene())
         end
    end

    local middle_button = self._uiLayer:getWidgetByName("middle_Button")
    middle_button:addTouchEventListener(restartCallback)

    local function nextCallback(sender, eventType)
        if eventType == ccs.TouchEventType.ended then
            self:unscheduleUpdate()
            self._uiLayer:removeFromParent()
            cc.Director:getInstance():replaceScene(guiSceneManager.nextUIScene())
        end
    end

    local right_button = self._uiLayer:getWidgetByName("right_Button")
    right_button:addTouchEventListener(nextCallback)

    local function menuCloseCallback( sender,eventType)
        if eventType == ccs.TouchEventType.ended then
            self:unscheduleUpdate()
            self._uiLayer:removeFromParent()
            local scene = CocoStudioTestMain()
            if scene ~= nil then
                cc.Director:getInstance():replaceScene(scene)
            end
        end
    end

    local mainMenuLabel = ccs.UILabel:create()
    mainMenuLabel:setText("MainMenu")
    mainMenuLabel:setFontSize(20)
    mainMenuLabel:setTouchScaleChangeEnabled(true)
    mainMenuLabel:setPosition(cc.p(430,30))
    mainMenuLabel:setTouchEnabled(true)
    mainMenuLabel:addTouchEventListener(menuCloseCallback)
    self._uiLayer:addWidget(mainMenuLabel)  
end

function UILoadingBarRightScale9Test.create()
    local scene = UILoadingBarRightScale9Test.extend(cc.Scene:create())
    scene:initExtend()
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
        
    local alert = ccs.UILabel:create()
    alert:setText("LabelAtlas")
    alert:setFontName(font_UILabelAtlasTest)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)
        

    local labelAtlas = ccs.UILabelAtlas:create()
    labelAtlas:setProperty("1234567890", "cocosgui/labelatlas.png", 17, 22, "0")
    labelAtlas:setPosition(cc.p((widgetSize.width) / 2, widgetSize.height / 2.0))        
        
    self._uiLayer:addWidget(labelAtlas) 
end

function UILabelAtlasTest.create()
    local scene = UILabelAtlasTest.extend(cc.Scene:create())
    scene:initExtend()
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
        
    local alert = ccs.UILabel:create()
    alert:setText("LabelBMFont")
    alert:setFontName(font_UILabelBMFontTest)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)
        

    local labelBMFont = ccs.UILabelBMFont:create()
    labelBMFont:setFntFile("cocosgui/bitmapFontTest2.fnt")
    labelBMFont:setText("BMFont")
    labelBMFont:setPosition(cc.p(widgetSize.width / 2, widgetSize.height / 2.0 + labelBMFont:getSize().height / 8.0))        
        
    self._uiLayer:addWidget(labelBMFont) 
end

function UILabelBMFontTest.create()
    local scene = UILabelBMFontTest.extend(cc.Scene:create())
    scene:initExtend()
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
        
    local alert = ccs.UILabel:create()
    alert:setText("Label")
    alert:setFontName(font_UILabelTest)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)
        
    local label = ccs.UILabel:create()
    label:setText("Label")
    label:setFontName("AmericanTypewriter")
    label:setFontSize(30)
    label:setPosition(cc.p(widgetSize.width / 2, widgetSize.height / 2 + label:getSize().height / 4))    
    self._uiLayer:addWidget(label) 
end

function UILabelTest.create()
    local scene = UILabelTest.extend(cc.Scene:create())
    scene:initExtend()
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
        
    local alert = ccs.UILabel:create()
    alert:setText("TextArea")
    alert:setFontName(font_UITextAreaTest)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)
        
    local textArea = ccs.UILabel:create()
    textArea:setTextAreaSize(cc.size(280, 150))
    textArea:setTextHorizontalAlignment(cc.TEXT_ALIGNMENT_CENTER)
    textArea:setText("TextArea widget can line wrap")
    textArea:setFontName("AmericanTypewriter")
    textArea:setFontSize(32)
    textArea:setPosition(cc.p(widgetSize.width / 2, widgetSize.height / 2 - textArea:getSize().height / 8))  
    self._uiLayer:addWidget(textArea) 
end

function UITextAreaTest.create()
    local scene = UITextAreaTest.extend(cc.Scene:create())
    scene:initExtend()
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

    self._displayValueLabel = ccs.UILabel:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(font_UITextFieldTest)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + self._displayValueLabel:getSize().height * 1.5))
    self._uiLayer:addWidget(self._displayValueLabel)  
        
    local alert = ccs.UILabel:create()
    alert:setText("TextField")
    alert:setFontName(font_UITextFieldTest)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)

    local function textFieldEvent(sender, eventType)
        if eventType == ccs.TextFiledEventType.attach_with_ime then
            local textField = tolua.cast(sender,"UITextField")
            local screenSize = cc.Director:getInstance():getWinSize()
            textField:runAction(cc.MoveTo:create(0.225,cc.p(screenSize.width / 2.0, screenSize.height / 2.0 + textField:getContentSize().height / 2.0)))
            self._displayValueLabel:setText("attach with IME")
        elseif eventType == ccs.TextFiledEventType.detach_with_ime then
            local textField = tolua.cast(sender,"UITextField")
            local screenSize = cc.Director:getInstance():getWinSize()
            textField:runAction(cc.MoveTo:create(0.175, cc.p(screenSize.width / 2.0, screenSize.height / 2.0)))
            self._displayValueLabel:setText("detach with IME")
        elseif eventType == ccs.TextFiledEventType.insert_text then
            self._displayValueLabel:setText("insert words")
        elseif eventType == ccs.TextFiledEventType.delete_backward then
            self._displayValueLabel:setText("delete word")
        end
    end
        
    local textField = ccs.UITextField:create()
    textField:setTouchEnabled(true)
    textField:setFontName(font_UITextFieldTest)
    textField:setFontSize(30)
    textField:setPlaceHolder("input words here")
    textField:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    textField:addEventListener(textFieldEvent) 
    self._uiLayer:addWidget(textField) 
end

function UITextFieldTest.create()
    local scene = UITextFieldTest.extend(cc.Scene:create())
    scene:initExtend()
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

    self._displayValueLabel = ccs.UILabel:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(font_UITextFieldTest)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + self._displayValueLabel:getSize().height * 1.5))
    self._uiLayer:addWidget(self._displayValueLabel)  
        
    local alert = ccs.UILabel:create()
    alert:setText("TextField max length")
    alert:setFontName(font_UITextFieldTest)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)

    local function textFieldEvent(sender, eventType)
        if eventType == ccs.TextFiledEventType.attach_with_ime then
            local textField = tolua.cast(sender,"UITextField")
            local screenSize = cc.Director:getInstance():getWinSize()
            textField:runAction(cc.MoveTo:create(0.225,cc.p(screenSize.width / 2.0, screenSize.height / 2.0 + textField:getContentSize().height / 2.0)))
            local info = string.format("attach with IME max length %d",textField:getMaxLength())
            self._displayValueLabel:setText(info)
        elseif eventType == ccs.TextFiledEventType.detach_with_ime then
            local textField = tolua.cast(sender,"UITextField")
            local screenSize = cc.Director:getInstance():getWinSize()
            textField:runAction(cc.MoveTo:create(0.175, cc.p(screenSize.width / 2.0, screenSize.height / 2.0)))
            local info = string.format("detach with IME max length %d",textField:getMaxLength())
            self._displayValueLabel:setText(info)
        elseif eventType == ccs.TextFiledEventType.insert_text then
            local textField = tolua.cast(sender,"UITextField")
            local info = string.format("insert words max length %d",textField:getMaxLength())
            self._displayValueLabel:setText(info)
        elseif eventType == ccs.TextFiledEventType.delete_backward then
            local textField = tolua.cast(sender,"UITextField")
            local info = string.format("delete word max length %d",textField:getMaxLength())
            self._displayValueLabel:setText(info)
        end
    end
        
    local textField = ccs.UITextField:create()
    textField:setMaxLengthEnabled(true)
    textField:setMaxLength(3)
    textField:setTouchEnabled(true)
    textField:setFontName(font_UITextFieldTest)
    textField:setFontSize(30)
    textField:setPlaceHolder("input words here")
    textField:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    textField:addEventListener(textFieldEvent) 
    self._uiLayer:addWidget(textField) 
end

function UITextFieldMaxLengthTest.create()
    local scene = UITextFieldMaxLengthTest.extend(cc.Scene:create())
    scene:initExtend()
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

    self._displayValueLabel = ccs.UILabel:create()
    self._displayValueLabel:setText("No Event")
    self._displayValueLabel:setFontName(font_UITextFieldTest)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + self._displayValueLabel:getSize().height * 1.5))
    self._uiLayer:addWidget(self._displayValueLabel)  
        
    local alert = ccs.UILabel:create()
    alert:setText("TextField password")
    alert:setFontName(font_UITextFieldTest)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)

    local function textFieldEvent(sender, eventType)
        if eventType == ccs.TextFiledEventType.attach_with_ime then
            local textField = tolua.cast(sender,"UITextField")
            local screenSize = cc.Director:getInstance():getWinSize()
            textField:runAction(cc.MoveTo:create(0.175, cc.p(screenSize.width / 2.0, screenSize.height / 2.0)))
            self._displayValueLabel:setText("detach with IME password")
        elseif eventType == ccs.TextFiledEventType.detach_with_ime then
            local textField = tolua.cast(sender,"UITextField")
            local screenSize = cc.Director:getInstance():getWinSize()
            textField:runAction(cc.MoveTo:create(0.175, cc.p(screenSize.width / 2.0, screenSize.height / 2.0)))
            self._displayValueLabel:setText("detach with IME password")
        elseif eventType == ccs.TextFiledEventType.insert_text then
            self._displayValueLabel:setText("insert words password")
        elseif eventType == ccs.TextFiledEventType.delete_backward then
            self._displayValueLabel:setText("delete word password")
        end
    end
        
    local textField = ccs.UITextField:create()
    textField:setPasswordEnabled(true)
    textField:setPasswordStyleText("*")
    textField:setTouchEnabled(true)
    textField:setFontName(font_UITextFieldTest)
    textField:setFontSize(30)
    textField:setPlaceHolder("input password here")
    textField:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    textField:addEventListener(textFieldEvent) 
    self._uiLayer:addWidget(textField) 
end

function UITextFieldPasswordTest.create()
    local scene = UITextFieldPasswordTest.extend(cc.Scene:create())
    scene:initExtend()
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
        
    local alert = ccs.UILabel:create()
    alert:setText("Panel")
    alert:setFontName(font_UIPanelTest)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getSize().height * 1.75))
    self._uiLayer:addWidget(alert)

    local background = self._uiLayer:getWidgetByName("background_Panel")
    
    local layout = ccs.UILayout:create()
    layout:setSize(cc.size(280, 150))
    local backgroundSize = background:getSize()
    layout:setPosition(cc.p((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout:getSize().width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout:getSize().height) / 2))
    self._uiLayer:addWidget(layout)
        
    local button = ccs.UIButton:create()
    button:setTouchEnabled(true)
    button:loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "")
    button:setPosition(cc.p(button:getSize().width / 2, layout:getSize().height - button:getSize().height / 2))
    layout:addChild(button)
        
    local textButton = UIButton:create()
    textButton:setTouchEnabled(true)
    textButton:loadTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "")
    textButton:setTitleText("Text Button")
    textButton:setPosition(cc.p(layout:getSize().width / 2, layout:getSize().height / 2))
    layout:addChild(textButton)
        
    local button_scale9 = UIButton:create()
    button_scale9:setTouchEnabled(true)
    button_scale9:loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "")
    button_scale9:setScale9Enabled(true)
    button_scale9:setSize(cc.size(100, button_scale9:getContentSize().height))
    button_scale9:setPosition(cc.p(layout:getSize().width - button_scale9:getSize().width / 2, button_scale9:getSize().height / 2))
    layout:addChild(button_scale9)  
end

function UIPanelTest.create()
    local scene = UIPanelTest.extend(cc.Scene:create())
    scene:initExtend()
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
   cc.Director:getInstance():replaceScene(scene)
end
