local guiSceneManager =  {}
guiSceneManager.currentUISceneIdx = 1
local font_TextName   =  "fonts/Marker Felt.ttf"

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
    self._uiLayer = cc.Layer:create()
    self:addChild(self._uiLayer)

    self._widget = ccs.GUIReader:getInstance():widgetFromJsonFile("cocosui/UITest/UITest.json")
    self._uiLayer:addChild(self._widget)

    local root = self._uiLayer:getChildByTag(81)

    self._sceneTitle = root:getChildByName("UItest")

    local back_label = root:getChildByName("back")--getWidgetByName
    back_label:setVisible(false)

    local function previousCallback(sender, eventType)
        if eventType == ccui.TouchEventType.ended then
            cc.Director:getInstance():replaceScene(guiSceneManager.previousUIScene())
        end
    end

    local left_button = root:getChildByName("left_Button")
    left_button:addTouchEventListener(previousCallback)

    local function restartCallback(sender, eventType)
         if eventType == ccui.TouchEventType.ended then
             cc.Director:getInstance():replaceScene(guiSceneManager.currentUIScene())
         end
    end

    local middle_button = root:getChildByName("middle_Button")
    middle_button:addTouchEventListener(restartCallback)

    local function nextCallback(sender, eventType)
        if eventType == ccui.TouchEventType.ended then
            cc.Director:getInstance():replaceScene(guiSceneManager.nextUIScene())
        end
    end

    local right_button = root:getChildByName("right_Button")
    right_button:addTouchEventListener(nextCallback)

    local function menuCloseCallback( sender,eventType)
        if eventType == ccui.TouchEventType.ended then
            local scene = CocoStudioTestMain()
            if scene ~= nil then
                cc.Director:getInstance():replaceScene(scene)
            end
        end
    end

    local backMenuLabel = ccui.Text:create()
    backMenuLabel:setString("Back")
    backMenuLabel:setFontSize(20)
    backMenuLabel:setTouchScaleChangeEnabled(true)
    backMenuLabel:setPosition(cc.p(430,30))
    backMenuLabel:setTouchEnabled(true)
    backMenuLabel:addTouchEventListener(menuCloseCallback)
    self._uiLayer:addChild(backMenuLabel) 

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

function UIButtonTest:initExtend()
    self:init()

    local widgetSize = self._widget:getContentSize()
        
    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("No Event")
    self._displayValueLabel:setFontName(font_TextName)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addChild(self._displayValueLabel)        
        
    local alert = ccui.Text:create()
    alert:setString("Button")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)        
    alert:setColor(cc.c3b(159, 168, 176))                
        
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 1.75))
    self._uiLayer:addChild(alert)        
    
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
    local button = ccui.Button:create()
    button:setTouchEnabled(true)
    button:loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "")
    button:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))        
    button:addTouchEventListener(touchEvent)
    self._uiLayer:addChild(button)
end

function UIButtonTest.create()
    local scene = cc.Scene:create()
    local layer = UIButtonTest.extend(cc.Layer:create())
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

    local widgetSize = self._widget:getContentSize()
        
    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("No Event")
    self._displayValueLabel:setFontName(font_TextName)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addChild(self._displayValueLabel)
        
    local alert = ccui.Text:create()
    alert:setString("Button scale9 render")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 1.75))
    self._uiLayer:addChild(alert)

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
        
    local button = ccui.Button:create()
    button:setTouchEnabled(true)
    button:setScale9Enabled(true)
    button:loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "")
    button:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    button:setContentSize(cc.size(150, button:getVirtualRendererSize().height * 1.5))
    button:addTouchEventListener(touchEvent)
    self._uiLayer:addChild(button)
end

function UIButtonScale9Test.create()
    local scene = cc.Scene:create()
    local layer = UIButtonScale9Test.extend(cc.Layer:create())
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

    local widgetSize = self._widget:getContentSize()
        
    
    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("No Event")
    self._displayValueLabel:setFontName(font_TextName)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addChild(self._displayValueLabel)
        
    local alert = ccui.Text:create()
    alert:setString("Button Pressed Action")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))    
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 1.75))
    self._uiLayer:addChild(alert)

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
        
    local button = ccui.Button:create()
    button:setTouchEnabled(true)
    button:setPressedActionEnabled(true)
    button:loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "")
    button:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    button:addTouchEventListener(touchEvent)        
    self._uiLayer:addChild(button)
end

function UIButtonPressedActionTest.create()
    local scene = cc.Scene:create()
    local layer = UIButtonPressedActionTest.extend(cc.Layer:create())
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

    local widgetSize = self._widget:getContentSize()
        
    
    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("No Event")
    self._displayValueLabel:setFontName(font_TextName)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addChild(self._displayValueLabel)
        
    local alert = ccui.Text:create()
    alert:setString("TextButton")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))    
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 1.75))
    self._uiLayer:addChild(alert)

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
        
    local textButton = ccui.Button:create()
    textButton:setTouchEnabled(true)
    textButton:loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "")
    textButton:setTitleText("Text Button")
    textButton:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    textButton:addTouchEventListener(touchEvent)        
    self._uiLayer:addChild(textButton)
end

function UITextButtonTest.create()
    local scene = cc.Scene:create()
    local layer = UITextButtonTest.extend(cc.Layer:create())
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

    local widgetSize = self._widget:getContentSize()
          
    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("No Event")
    self._displayValueLabel:setFontName(font_TextName)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addChild(self._displayValueLabel)
        
    local alert = ccui.Text:create()
    alert:setString("TextButton scale9 render")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))    
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 1.75))
    self._uiLayer:addChild(alert)

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
        
    local textButton = ccui.Button:create()
    textButton:setTouchEnabled(true)
    textButton:setScale9Enabled(true)
    textButton:loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "")
    textButton:setContentSize(cc.size(180, textButton:getVirtualRendererSize().height * 1.5))
    textButton:setTitleText("Text Button scale9 render")
    textButton:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    textButton:addTouchEventListener(touchEvent)        
    self._uiLayer:addChild(textButton)
end

function UITextButtonScale9Test.create()
    local scene = cc.Scene:create()
    local layer = UITextButtonScale9Test.extend(cc.Layer:create())
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

    local widgetSize = self._widget:getContentSize()
          
    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("No Event")
    self._displayValueLabel:setFontName(font_TextName)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addChild(self._displayValueLabel)
        
    local alert = ccui.Text:create()
    alert:setString("CheckBox")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))    
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 1.75))
    self._uiLayer:addChild(alert)

    local function selectedEvent(sender,eventType)
        if eventType == ccui.CheckBoxEventType.selected then
            self._displayValueLabel:setString("Selected")
        elseif eventType == ccui.CheckBoxEventType.unselected then
            self._displayValueLabel:setString("Unselected")
        end
    end  
        
    local checkBox = ccui.CheckBox:create()
    checkBox:setTouchEnabled(true)
    checkBox:setSelectedState(true)
    checkBox:loadTextures("cocosui/check_box_normal.png",
                               "cocosui/check_box_normal_press.png",
                               "cocosui/check_box_active.png",
                               "cocosui/check_box_normal_disable.png",
                               "cocosui/check_box_active_disable.png")
    checkBox:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
        
    checkBox:addEventListener(selectedEvent)  

    self._uiLayer:addChild(checkBox)
end

function UICheckBoxTest.create()
    local scene = cc.Scene:create()
    local layer = UICheckBoxTest.extend(cc.Layer:create())
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

    local widgetSize = self._widget:getContentSize()
          
    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("Move the slider thumb")
    self._displayValueLabel:setFontName(font_TextName)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addChild(self._displayValueLabel)
        
    local alert = ccui.Text:create()
    alert:setString("Slider")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))    
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 1.75))
    self._uiLayer:addChild(alert)

    local function percentChangedEvent(sender,eventType)
        if eventType == ccui.SliderEventType.percentChanged then
            local slider = sender
            local percent = "Percent " .. slider:getPercent()
            self._displayValueLabel:setString(percent)
        end
    end  
        
    local slider = ccui.Slider:create()
    slider:setTouchEnabled(true)
    slider:loadBarTexture("cocosui/sliderTrack.png")
    slider:loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "")
    slider:loadProgressBarTexture("cocosui/sliderProgress.png")
    slider:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    slider:addEventListener(percentChangedEvent)

    self._uiLayer:addChild(slider)
end

function UISliderTest.create()
    local scene = cc.Scene:create()
    local layer = UISliderTest.extend(cc.Layer:create())
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

    local widgetSize = self._widget:getContentSize()
          
    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("Move the slider thumb")
    self._displayValueLabel:setFontName(font_TextName)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addChild(self._displayValueLabel)
        
    local alert = ccui.Text:create()
    alert:setString("Slider scale9 render")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))    
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 1.75))
    self._uiLayer:addChild(alert)

    local function percentChangedEvent(sender,eventType)
        if eventType == ccui.SliderEventType.percentChanged then
            local slider = sender
            local percent = "Percent " .. slider:getPercent()
            self._displayValueLabel:setString(percent)
        end
    end  
        
    local slider = ccui.Slider:create()
    slider:setTouchEnabled(true)
    slider:loadBarTexture("cocosui/sliderTrack2.png")
    slider:loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "")
    slider:loadProgressBarTexture("cocosui/slider_bar_active_9patch.png")
    slider:setScale9Enabled(true)
    slider:setCapInsets(cc.rect(0, 0, 0, 0))
    slider:setContentSize(cc.size(250, 10))
    slider:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    slider:addEventListener(percentChangedEvent)

    self._uiLayer:addChild(slider)
end

function UISliderScale9Test.create()
    local scene = cc.Scene:create()
    local layer = UISliderScale9Test.extend(cc.Layer:create())
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

    local widgetSize = self._widget:getContentSize()
        
    local alert = ccui.Text:create()
    alert:setString("ImageView")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))    
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 1.75))
    self._uiLayer:addChild(alert)
        
    local imageView = ccui.ImageView:create()
    imageView:loadTexture("cocosui/ccicon.png")
    imageView:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + imageView:getContentSize().height / 4.0))
    self._uiLayer:addChild(imageView)
end

function UIImageViewTest.create()
    local scene = cc.Scene:create()
    local layer = UIImageViewTest.extend(cc.Layer:create())
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

    local widgetSize = self._widget:getContentSize()
        
    local alert = ccui.Text:create()
    alert:setString("ImageView scale9 render")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))    
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 1.75))
    self._uiLayer:addChild(alert)
        
    local imageView = ccui.ImageView:create()
    imageView:setScale9Enabled(true)
    imageView:loadTexture("cocosui/buttonHighlighted.png")
    imageView:setContentSize(cc.size(200, 85))
    imageView:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + imageView:getContentSize().height / 4.0))
    self._uiLayer:addChild(imageView)
end

function UIImageViewScale9Test.create()
    local scene = cc.Scene:create()
    local layer = UIImageViewScale9Test.extend(cc.Layer:create())
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

    self._uiLayer = cc.Layer:create()
    self:addChild(self._uiLayer)

    self._widget = ccs.GUIReader:getInstance():widgetFromJsonFile("cocosui/UITest/UITest.json")
    self._uiLayer:addChild(self._widget)

    local root = self._uiLayer:getChildByTag(81)
    self._sceneTitle = root:getChildByName("UItest")

    local back_label = root:getChildByName("back")
    back_label:setVisible(false)

    local widgetSize = self._widget:getContentSize()
        
    local alert = ccui.Text:create()
    alert:setString("LoadingBar")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))    
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 1.75))
    self._uiLayer:addChild(alert)
        
    local loadingBar = ccui.LoadingBar:create()
    loadingBar:setTag(0)
    loadingBar:setName("LoadingBar")
    loadingBar:loadTexture("cocosui/sliderProgress.png")
    loadingBar:setPercent(0)
        
    loadingBar:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + loadingBar:getContentSize().height / 4.0))
    self._uiLayer:addChild(loadingBar)

    local function update(delta)
        self._count = self._count + 1
        if self._count > 100 then
            self._count = 0
        end

        if self._uiLayer ~= nil then
            local loadingBar = self._uiLayer:getChildByTag(0)
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
        if eventType == ccui.TouchEventType.ended then
            self:unscheduleUpdate()
            cc.Director:getInstance():replaceScene(guiSceneManager.previousUIScene())
        end
    end

    local left_button = root:getChildByName("left_Button")
    left_button:addTouchEventListener(previousCallback)

    local function restartCallback(sender, eventType)
         if eventType == ccui.TouchEventType.ended then
             self:unscheduleUpdate()
             cc.Director:getInstance():replaceScene(guiSceneManager.currentUIScene())
         end
    end

    local middle_button = root:getChildByName("middle_Button")
    middle_button:addTouchEventListener(restartCallback)

    local function nextCallback(sender, eventType)
        if eventType == ccui.TouchEventType.ended then
            self:unscheduleUpdate()
            cc.Director:getInstance():replaceScene(guiSceneManager.nextUIScene())
        end
    end

    local right_button = root:getChildByName("right_Button")
    right_button:addTouchEventListener(nextCallback)

    local function menuCloseCallback( sender,eventType)
        if eventType == ccui.TouchEventType.ended then
            self:unscheduleUpdate()
            local scene = CocoStudioTestMain()
            if scene ~= nil then
                cc.Director:getInstance():replaceScene(scene)
            end
        end
    end

    local mainMenuLabel = ccui.Text:create()
    mainMenuLabel:setString("Back")
    mainMenuLabel:setFontSize(20)
    mainMenuLabel:setTouchScaleChangeEnabled(true)
    mainMenuLabel:setPosition(cc.p(430,30))
    mainMenuLabel:setTouchEnabled(true)
    mainMenuLabel:addTouchEventListener(menuCloseCallback)
    self._uiLayer:addChild(mainMenuLabel)  
end

function UILoadingBarLeftTest.create()
    local scene = cc.Scene:create()
    local layer = UILoadingBarLeftTest.extend(cc.Layer:create())
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

    self._uiLayer = cc.Layer:create()
    self:addChild(self._uiLayer)

    self._widget = ccs.GUIReader:getInstance():widgetFromJsonFile("cocosui/UITest/UITest.json")
    self._uiLayer:addChild(self._widget)

    local root = self._uiLayer:getChildByTag(81)
    self._sceneTitle = root:getChildByName("UItest")

    local back_label = root:getChildByName("back")
    back_label:setVisible(false)

    local widgetSize = self._widget:getContentSize()
        
    local alert = ccui.Text:create()
    alert:setString("LoadingBar")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))    
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 1.75))
    self._uiLayer:addChild(alert)
        
    local loadingBar = ccui.LoadingBar:create()
    loadingBar:setTag(0)
    loadingBar:setName("LoadingBar")
    loadingBar:loadTexture("cocosui/sliderProgress.png")
    loadingBar:setDirection(ccui.LoadingBarDirection.RIGHT)
    loadingBar:setPercent(0)
        
    loadingBar:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + loadingBar:getContentSize().height / 4.0))
    self._uiLayer:addChild(loadingBar)

    local function update(delta)
        self._count = self._count + 1
        if self._count > 100 then
            self._count = 0
        end

        if self._uiLayer ~= nil then
            local loadingBar = self._uiLayer:getChildByTag(0)
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
        if eventType == ccui.TouchEventType.ended then
            self:unscheduleUpdate()
            cc.Director:getInstance():replaceScene(guiSceneManager.previousUIScene())
        end
    end

    local left_button = root:getChildByName("left_Button")
    left_button:addTouchEventListener(previousCallback)

    local function restartCallback(sender, eventType)
         if eventType == ccui.TouchEventType.ended then
             self:unscheduleUpdate()
             cc.Director:getInstance():replaceScene(guiSceneManager.currentUIScene())
         end
    end

    local middle_button = root:getChildByName("middle_Button")
    middle_button:addTouchEventListener(restartCallback)

    local function nextCallback(sender, eventType)
        if eventType == ccui.TouchEventType.ended then
            self:unscheduleUpdate()
            cc.Director:getInstance():replaceScene(guiSceneManager.nextUIScene())
        end
    end

    local right_button = root:getChildByName("right_Button")
    right_button:addTouchEventListener(nextCallback)

    local function menuCloseCallback( sender,eventType)
        if eventType == ccui.TouchEventType.ended then
            self:unscheduleUpdate()
            local scene = CocoStudioTestMain()
            if scene ~= nil then
                cc.Director:getInstance():replaceScene(scene)
            end
        end
    end

    local mainMenuLabel = ccui.Text:create()
    mainMenuLabel:setString("Back")
    mainMenuLabel:setFontSize(20)
    mainMenuLabel:setTouchScaleChangeEnabled(true)
    mainMenuLabel:setPosition(cc.p(430,30))
    mainMenuLabel:setTouchEnabled(true)
    mainMenuLabel:addTouchEventListener(menuCloseCallback)
    self._uiLayer:addChild(mainMenuLabel)  
end

function UILoadingBarRightTest.create()
    local scene = cc.Scene:create()
    local layer = UILoadingBarRightTest.extend(cc.Layer:create())
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

    self._uiLayer = cc.Layer:create()
    self:addChild(self._uiLayer)

    self._widget = ccs.GUIReader:getInstance():widgetFromJsonFile("cocosui/UITest/UITest.json")
    self._uiLayer:addChild(self._widget)

    local root = self._uiLayer:getChildByTag(81)
    self._sceneTitle = root:getChildByName("UItest")

    local back_label = root:getChildByName("back")
    back_label:setVisible(false)

    local widgetSize = self._widget:getContentSize()
        
    local alert = ccui.Text:create()
    alert:setString("LoadingBar Scale9 Render")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))    
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 1.75))
    self._uiLayer:addChild(alert)
        
    local loadingBar = ccui.LoadingBar:create()
    loadingBar:setTag(0)
    loadingBar:setName("LoadingBar")
    loadingBar:loadTexture("cocosui/slider_bar_active_9patch.png")
    loadingBar:setScale9Enabled(true)
    loadingBar:setCapInsets(cc.rect(0, 0, 0, 0))
    loadingBar:setContentSize(cc.size(300, 30))
    loadingBar:setPercent(0)
        
    loadingBar:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + loadingBar:getContentSize().height / 4.0))
    self._uiLayer:addChild(loadingBar)

    local function update(delta)
        self._count = self._count + 1
        if self._count > 100 then
            self._count = 0
        end

        if self._uiLayer ~= nil then
            local loadingBar = self._uiLayer:getChildByTag(0)
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
        if eventType == ccui.TouchEventType.ended then
            self:unscheduleUpdate()
            cc.Director:getInstance():replaceScene(guiSceneManager.previousUIScene())
        end
    end

    local left_button = root:getChildByName("left_Button")
    left_button:addTouchEventListener(previousCallback)

    local function restartCallback(sender, eventType)
         if eventType == ccui.TouchEventType.ended then
             self:unscheduleUpdate()
             cc.Director:getInstance():replaceScene(guiSceneManager.currentUIScene())
         end
    end

    local middle_button = root:getChildByName("middle_Button")
    middle_button:addTouchEventListener(restartCallback)

    local function nextCallback(sender, eventType)
        if eventType == ccui.TouchEventType.ended then
            self:unscheduleUpdate()
            cc.Director:getInstance():replaceScene(guiSceneManager.nextUIScene())
        end
    end

    local right_button = root:getChildByName("right_Button")
    right_button:addTouchEventListener(nextCallback)

    local function menuCloseCallback( sender,eventType)
        if eventType == ccui.TouchEventType.ended then
            self:unscheduleUpdate()
            local scene = CocoStudioTestMain()
            if scene ~= nil then
                cc.Director:getInstance():replaceScene(scene)
            end
        end
    end

    local mainMenuLabel = ccui.Text:create()
    mainMenuLabel:setString("Back")
    mainMenuLabel:setFontSize(20)
    mainMenuLabel:setTouchScaleChangeEnabled(true)
    mainMenuLabel:setPosition(cc.p(430,30))
    mainMenuLabel:setTouchEnabled(true)
    mainMenuLabel:addTouchEventListener(menuCloseCallback)
    self._uiLayer:addChild(mainMenuLabel)  
end

function UILoadingBarLeftScale9Test.create()
    local scene = cc.Scene:create()
    local layer = UILoadingBarLeftScale9Test.extend(cc.Layer:create())
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

    self._uiLayer = cc.Layer:create()
    self:addChild(self._uiLayer)

    self._widget = ccs.GUIReader:getInstance():widgetFromJsonFile("cocosui/UITest/UITest.json")
    self._uiLayer:addChild(self._widget)

    local root = self._uiLayer:getChildByTag(81)
    self._sceneTitle = root:getChildByName("UItest")

    local back_label = root:getChildByName("back")
    back_label:setVisible(false)

    local widgetSize = self._widget:getContentSize()
        
    local alert = ccui.Text:create()
    alert:setString("LoadingBar Scale9 Render")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))    
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 1.75))
    self._uiLayer:addChild(alert)
        
    local loadingBar = ccui.LoadingBar:create()
    loadingBar:setTag(0)
    loadingBar:setName("LoadingBar")
    loadingBar:loadTexture("cocosui/slider_bar_active_9patch.png")
    loadingBar:setScale9Enabled(true)
    loadingBar:setCapInsets(cc.rect(0, 0, 0, 0))
    loadingBar:setContentSize(cc.size(300, 30))
    loadingBar:setDirection(ccui.LoadingBarDirection.RIGHT)
    loadingBar:setPercent(0)
        
    loadingBar:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + loadingBar:getContentSize().height / 4.0))
    self._uiLayer:addChild(loadingBar)

    local function update(delta)
        self._count = self._count + 1
        if self._count > 100 then
            self._count = 0
        end

        if self._uiLayer ~= nil then
            local loadingBar = self._uiLayer:getChildByTag(0)
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
        if eventType == ccui.TouchEventType.ended then
            self:unscheduleUpdate()
            cc.Director:getInstance():replaceScene(guiSceneManager.previousUIScene())
        end
    end

    local left_button = root:getChildByName("left_Button")
    left_button:addTouchEventListener(previousCallback)

    local function restartCallback(sender, eventType)
         if eventType == ccui.TouchEventType.ended then
             self:unscheduleUpdate()
             cc.Director:getInstance():replaceScene(guiSceneManager.currentUIScene())
         end
    end

    local middle_button = root:getChildByName("middle_Button")
    middle_button:addTouchEventListener(restartCallback)

    local function nextCallback(sender, eventType)
        if eventType == ccui.TouchEventType.ended then
            self:unscheduleUpdate()
            cc.Director:getInstance():replaceScene(guiSceneManager.nextUIScene())
        end
    end

    local right_button = root:getChildByName("right_Button")
    right_button:addTouchEventListener(nextCallback)

    local function menuCloseCallback( sender,eventType)
        if eventType == ccui.TouchEventType.ended then
            self:unscheduleUpdate()
            local scene = CocoStudioTestMain()
            if scene ~= nil then
                cc.Director:getInstance():replaceScene(scene)
            end
        end
    end

    local mainMenuLabel = ccui.Text:create()
    mainMenuLabel:setString("Back")
    mainMenuLabel:setFontSize(20)
    mainMenuLabel:setTouchScaleChangeEnabled(true)
    mainMenuLabel:setPosition(cc.p(430,30))
    mainMenuLabel:setTouchEnabled(true)
    mainMenuLabel:addTouchEventListener(menuCloseCallback)
    self._uiLayer:addChild(mainMenuLabel)  
end

function UILoadingBarRightScale9Test.create()
    local scene = cc.Scene:create()
    local layer = UILoadingBarRightScale9Test.extend(cc.Layer:create())
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
    local widgetSize = self._widget:getContentSize()
        
    local alert = ccui.Text:create()
    alert:setString("LabelAtlas")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 1.75))
    self._uiLayer:addChild(alert)
        

    local labelAtlas = ccui.TextAtlas:create()
    labelAtlas:setProperty("1234567890", "cocosui/labelatlas.png", 17, 22, "0")
    labelAtlas:setPosition(cc.p((widgetSize.width) / 2, widgetSize.height / 2.0))        
        
    self._uiLayer:addChild(labelAtlas) 
end

function UILabelAtlasTest.create()
    local scene = cc.Scene:create()
    local layer = UILabelAtlasTest.extend(cc.Layer:create())
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
    local widgetSize = self._widget:getContentSize()
        
    local alert = ccui.Text:create()
    alert:setString("LabelBMFont")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 1.75))
    self._uiLayer:addChild(alert)
        

    local labelBMFont = ccui.TextBMFont:create()
    labelBMFont:setFntFile("cocosui/bitmapFontTest2.fnt")
    labelBMFont:setString("BMFont")
    labelBMFont:setPosition(cc.p(widgetSize.width / 2, widgetSize.height / 2.0 + labelBMFont:getContentSize().height / 8.0))        
        
    self._uiLayer:addChild(labelBMFont) 
end

function UILabelBMFontTest.create()
    local scene = cc.Scene:create()
    local layer = UILabelBMFontTest.extend(cc.Layer:create())
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
    local widgetSize = self._widget:getContentSize()
        
    local alert = ccui.Text:create()
    alert:setString("Label")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 1.75))
    self._uiLayer:addChild(alert)
        
    local label = ccui.Text:create()
    label:setString("Label")
    label:setFontName("AmericanTypewriter")
    label:setFontSize(30)
    label:setPosition(cc.p(widgetSize.width / 2, widgetSize.height / 2 + label:getContentSize().height / 4))    
    self._uiLayer:addChild(label) 
end

function UILabelTest.create()
    local scene = cc.Scene:create()
    local layer = UILabelTest.extend(cc.Layer:create())
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
    local widgetSize = self._widget:getContentSize()
        
    local alert = ccui.Text:create()
    alert:setString("TextArea")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 1.75))
    self._uiLayer:addChild(alert)
        
    local textArea = ccui.Text:create()
    textArea:ignoreContentAdaptWithSize(false)
    textArea:setContentSize(cc.size(280, 150))
    textArea:setTextHorizontalAlignment(cc.TEXT_ALIGNMENT_CENTER)
    textArea:setString("TextArea widget can line wrap")
    textArea:setFontName("AmericanTypewriter")
    textArea:setFontSize(32)
    textArea:setPosition(cc.p(widgetSize.width / 2, widgetSize.height / 2 - textArea:getContentSize().height / 8))  
    self._uiLayer:addChild(textArea) 
end

function UITextAreaTest.create()
    local scene = cc.Scene:create()
    local layer = UITextAreaTest.extend(cc.Layer:create())
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
    local widgetSize = self._widget:getContentSize()

    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("No Event")
    self._displayValueLabel:setFontName(font_TextName)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + self._displayValueLabel:getContentSize().height * 1.5))
    self._uiLayer:addChild(self._displayValueLabel)  
        
    local alert = ccui.Text:create()
    alert:setString("TextField")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 1.75))
    self._uiLayer:addChild(alert)

    local function textFieldEvent(sender, eventType)
        if eventType == ccui.TextFiledEventType.attach_with_ime then
            local textField = sender
            local screenSize = cc.Director:getInstance():getWinSize()
            textField:runAction(cc.MoveTo:create(0.225,cc.p(screenSize.width / 2.0, screenSize.height / 2.0 + textField:getContentSize().height / 2.0)))
            self._displayValueLabel:setString("attach with IME")
        elseif eventType == ccui.TextFiledEventType.detach_with_ime then
            local textField = sender
            local screenSize = cc.Director:getInstance():getWinSize()
            textField:runAction(cc.MoveTo:create(0.175, cc.p(screenSize.width / 2.0, screenSize.height / 2.0)))
            self._displayValueLabel:setString("detach with IME")
        elseif eventType == ccui.TextFiledEventType.insert_text then
            self._displayValueLabel:setString("insert words")
        elseif eventType == ccui.TextFiledEventType.delete_backward then
            self._displayValueLabel:setString("delete word")
        end
    end
        
    local textField = ccui.TextField:create()
    textField:setTouchEnabled(true)
    textField:setFontName(font_TextName)
    textField:setFontSize(30)
    textField:setPlaceHolder("input words here")
    textField:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    textField:addEventListener(textFieldEvent) 
    self._uiLayer:addChild(textField) 
end

function UITextFieldTest.create()
    local scene = cc.Scene:create()
    local layer = UITextFieldTest.extend(cc.Layer:create())
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
    local widgetSize = self._widget:getContentSize()

    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("No Event")
    self._displayValueLabel:setFontName(font_TextName)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + self._displayValueLabel:getContentSize().height * 1.5))
    self._uiLayer:addChild(self._displayValueLabel)  
        
    local alert = ccui.Text:create()
    alert:setString("TextField max length")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 1.75))
    self._uiLayer:addChild(alert)

    local function textFieldEvent(sender, eventType)
        if eventType == ccui.TextFiledEventType.attach_with_ime then
            local textField = sender
            local screenSize = cc.Director:getInstance():getWinSize()
            textField:runAction(cc.MoveTo:create(0.225,cc.p(screenSize.width / 2.0, screenSize.height / 2.0 + textField:getContentSize().height / 2.0)))
            local info = string.format("attach with IME max length %d",textField:getMaxLength())
            self._displayValueLabel:setString(info)
        elseif eventType == ccui.TextFiledEventType.detach_with_ime then
            local textField = sender
            local screenSize = cc.Director:getInstance():getWinSize()
            textField:runAction(cc.MoveTo:create(0.175, cc.p(screenSize.width / 2.0, screenSize.height / 2.0)))
            local info = string.format("detach with IME max length %d",textField:getMaxLength())
            self._displayValueLabel:setString(info)
        elseif eventType == ccui.TextFiledEventType.insert_text then
            local textField = sender
            local info = string.format("insert words max length %d",textField:getMaxLength())
            self._displayValueLabel:setString(info)
        elseif eventType == ccui.TextFiledEventType.delete_backward then
            local textField = sender
            local info = string.format("delete word max length %d",textField:getMaxLength())
            self._displayValueLabel:setString(info)
        end
    end
        
    local textField = ccui.TextField:create()
    textField:setMaxLengthEnabled(true)
    textField:setMaxLength(3)
    textField:setTouchEnabled(true)
    textField:setFontName(font_TextName)
    textField:setFontSize(30)
    textField:setPlaceHolder("input words here")
    textField:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    textField:addEventListener(textFieldEvent) 
    self._uiLayer:addChild(textField) 
end

function UITextFieldMaxLengthTest.create()
    local scene = cc.Scene:create()
    local layer = UITextFieldMaxLengthTest.extend(cc.Layer:create())
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
    local widgetSize = self._widget:getContentSize()

    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("No Event")
    self._displayValueLabel:setFontName(font_TextName)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + self._displayValueLabel:getContentSize().height * 1.5))
    self._uiLayer:addChild(self._displayValueLabel)  
        
    local alert = ccui.Text:create()
    alert:setString("TextField password")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 1.75))
    self._uiLayer:addChild(alert)

    local function textFieldEvent(sender, eventType)
        if eventType == ccui.TextFiledEventType.attach_with_ime then
            local textField = sender
            local screenSize = cc.Director:getInstance():getWinSize()
            textField:runAction(cc.MoveTo:create(0.175, cc.p(screenSize.width / 2.0, screenSize.height / 2.0)))
            self._displayValueLabel:setString("detach with IME password")
        elseif eventType == ccui.TextFiledEventType.detach_with_ime then
            local textField = sender
            local screenSize = cc.Director:getInstance():getWinSize()
            textField:runAction(cc.MoveTo:create(0.175, cc.p(screenSize.width / 2.0, screenSize.height / 2.0)))
            self._displayValueLabel:setString("detach with IME password")
        elseif eventType == ccui.TextFiledEventType.insert_text then
            self._displayValueLabel:setString("insert words password")
        elseif eventType == ccui.TextFiledEventType.delete_backward then
            self._displayValueLabel:setString("delete word password")
        end
    end
        
    local textField = ccui.TextField:create()
    textField:setPasswordEnabled(true)
    textField:setPasswordStyleText("*")
    textField:setTouchEnabled(true)
    textField:setFontName(font_TextName)
    textField:setFontSize(30)
    textField:setPlaceHolder("input password here")
    textField:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    textField:addEventListener(textFieldEvent) 
    self._uiLayer:addChild(textField) 
end

function UITextFieldPasswordTest.create()
    local scene = cc.Scene:create()
    local layer = UITextFieldPasswordTest.extend(cc.Layer:create())
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

    local widgetSize = self._widget:getContentSize()
        
    local alert = ccui.Text:create()
    alert:setString("Panel")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 1.75))
    self._uiLayer:addChild(alert)

    local root = self._uiLayer:getChildByTag(81)
    local background = root:getChildByName("background_Panel")
    
    local layout = ccui.Layout:create()
    layout:setContentSize(cc.size(280, 150))
    local backgroundSize = background:getContentSize()
    layout:setPosition(cc.p((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout:getContentSize().width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout:getContentSize().height) / 2))
    self._uiLayer:addChild(layout)
        
    local button = ccui.Button:create()
    button:setTouchEnabled(true)
    button:loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "")
    button:setPosition(cc.p(button:getContentSize().width / 2, layout:getContentSize().height - button:getContentSize().height / 2))
    layout:addChild(button)
        
    local textButton = ccui.Button:create()
    textButton:setTouchEnabled(true)
    textButton:loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "")
    textButton:setTitleText("Text Button")
    textButton:setPosition(cc.p(layout:getContentSize().width / 2, layout:getContentSize().height / 2))
    layout:addChild(textButton)
        
    local button_scale9 = ccui.Button:create()
    button_scale9:setTouchEnabled(true)
    button_scale9:loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "")
    button_scale9:setScale9Enabled(true)
    button_scale9:setContentSize(cc.size(100, button_scale9:getVirtualRendererSize().height))
    button_scale9:setPosition(cc.p(layout:getContentSize().width - button_scale9:getContentSize().width / 2, button_scale9:getContentSize().height / 2))
    layout:addChild(button_scale9)  
end

function UIPanelTest.create()
    local scene = cc.Scene:create()
    local layer = UIPanelTest.extend(cc.Layer:create())
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

    local widgetSize = self._widget:getContentSize()
        
    local alert = ccui.Text:create()
    alert:setString("Panel color render")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 2.925))
    self._uiLayer:addChild(alert)

    local root = self._uiLayer:getChildByTag(81)
    local background = root:getChildByName("background_Panel")
    
    local layout = ccui.Layout:create()
    layout:setBackGroundColorType(ccui.LayoutBackGroundColorType.solid)
    layout:setBackGroundColor(cc.c3b(128, 128, 128))
    layout:setContentSize(cc.size(280, 150))
    local backgroundSize = background:getContentSize()
    layout:setPosition(cc.p((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout:getContentSize().width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout:getContentSize().height) / 2))
    self._uiLayer:addChild(layout)
        
    local button = ccui.Button:create()
    button:setTouchEnabled(true)
    button:loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "")
    button:setPosition(cc.p(button:getContentSize().width / 2, layout:getContentSize().height - button:getContentSize().height / 2))
    layout:addChild(button)
        
    local textButton = ccui.Button:create()
    textButton:setTouchEnabled(true)
    textButton:loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "")
    textButton:setTitleText("Text Button")
    textButton:setPosition(cc.p(layout:getContentSize().width / 2, layout:getContentSize().height / 2))
    layout:addChild(textButton)
        
    local button_scale9 = ccui.Button:create()
    button_scale9:setTouchEnabled(true)
    button_scale9:loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "")
    button_scale9:setScale9Enabled(true)
    button_scale9:setContentSize(cc.size(100, button_scale9:getVirtualRendererSize().height))
    button_scale9:setPosition(cc.p(layout:getContentSize().width - button_scale9:getContentSize().width / 2, button_scale9:getContentSize().height / 2))
    layout:addChild(button_scale9)  
end

function UIPanelColorTest.create()
    local scene = cc.Scene:create()
    local layer = UIPanelColorTest.extend(cc.Layer:create())
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

    local widgetSize = self._widget:getContentSize()
        
    local alert = ccui.Text:create()
    alert:setString("Panel color Gradient")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 2.925))
    self._uiLayer:addChild(alert)

    local root = self._uiLayer:getChildByTag(81)
    local background = root:getChildByName("background_Panel")
    
    local layout = ccui.Layout:create()
    layout:setBackGroundColorType(ccui.LayoutBackGroundColorType.gradient)
    layout:setBackGroundColor(cc.c3b(64, 64, 64), cc.c3b(192, 192, 192))
    layout:setContentSize(cc.size(280, 150))
    local backgroundSize = background:getContentSize()
    layout:setPosition(cc.p((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout:getContentSize().width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout:getContentSize().height) / 2))
    self._uiLayer:addChild(layout)
        
    local button = ccui.Button:create()
    button:setTouchEnabled(true)
    button:loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "")
    button:setPosition(cc.p(button:getContentSize().width / 2, layout:getContentSize().height - button:getContentSize().height / 2))
    layout:addChild(button)
        
    local textButton = ccui.Button:create()
    textButton:setTouchEnabled(true)
    textButton:loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "")
    textButton:setTitleText("Text Button")
    textButton:setPosition(cc.p(layout:getContentSize().width / 2, layout:getContentSize().height / 2))
    layout:addChild(textButton)
        
    local button_scale9 = ccui.Button:create()
    button_scale9:setTouchEnabled(true)
    button_scale9:loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "")
    button_scale9:setScale9Enabled(true)
    button_scale9:setContentSize(cc.size(100, button_scale9:getVirtualRendererSize().height))
    button_scale9:setPosition(cc.p(layout:getContentSize().width - button_scale9:getContentSize().width / 2, button_scale9:getContentSize().height / 2))
    layout:addChild(button_scale9)  
end

function UIPanelGradientTest.create()
    local scene = cc.Scene:create()
    local layer = UIPanelGradientTest.extend(cc.Layer:create())
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

    local widgetSize = self._widget:getContentSize()
        
    local alert = ccui.Text:create()
    alert:setString("Panel background image")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 2.925))
    self._uiLayer:addChild(alert)
        
    local root = self._uiLayer:getChildByTag(81)
    local background = root:getChildByName("background_Panel")
        
    local layout = ccui.Layout:create()
    layout:setClippingEnabled(true)
    layout:setBackGroundImage("cocosui/Hello.png")
    layout:setContentSize(cc.size(280, 150))
    local backgroundSize = background:getContentSize()
    layout:setPosition(cc.p((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout:getContentSize().width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout:getContentSize().height) / 2))
    self._uiLayer:addChild(layout)
        
    local button = ccui.Button:create()
    button:setTouchEnabled(true)
    button:loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "")
    button:setPosition(cc.p(button:getContentSize().width / 2, layout:getContentSize().height - button:getContentSize().height / 2))
    layout:addChild(button)
        
    local textButton = ccui.Button:create()
    textButton:setTouchEnabled(true)
    textButton:loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "")
    textButton:setTitleText("Text Button")
    textButton:setPosition(cc.p(layout:getContentSize().width / 2, layout:getContentSize().height / 2))
    layout:addChild(textButton)
        
    local button_scale9 = ccui.Button:create()
    button_scale9:setTouchEnabled(true)
    button_scale9:loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "")
    button_scale9:setScale9Enabled(true)
    button_scale9:setContentSize(cc.size(100, button_scale9:getVirtualRendererSize().height))
    button_scale9:setPosition(cc.p(layout:getContentSize().width - button_scale9:getContentSize().width / 2, button_scale9:getContentSize().height / 2))
    layout:addChild(button_scale9)   
end

function UIPanelBackGroundImageTest.create()
    local scene = cc.Scene:create()
    local layer = UIPanelBackGroundImageTest.extend(cc.Layer:create())
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

    local widgetSize = self._widget:getContentSize()
        
    local alert = ccui.Text:create()
    alert:setString("Panel background image scale9")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 2.925))
    self._uiLayer:addChild(alert)

    local root = self._uiLayer:getChildByTag(81)
    local background = root:getChildByName("background_Panel")
    
    local layout = ccui.Layout:create()
    layout:setBackGroundImageScale9Enabled(true)
    layout:setBackGroundImage("cocosui/green_edit.png")
    layout:setContentSize(cc.size(280, 150))
    local backgroundSize = background:getContentSize()
    layout:setPosition(cc.p((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout:getContentSize().width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout:getContentSize().height) / 2))
    self._uiLayer:addChild(layout)
        
    local button = ccui.Button:create()
    button:setTouchEnabled(true)
    button:loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "")
    button:setPosition(cc.p(button:getContentSize().width / 2, layout:getContentSize().height - button:getContentSize().height / 2))
    layout:addChild(button)
        
    local textButton = ccui.Button:create()
    textButton:setTouchEnabled(true)
    textButton:loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "")
    textButton:setTitleText("Text Button")
    textButton:setPosition(cc.p(layout:getContentSize().width / 2, layout:getContentSize().height / 2))
    layout:addChild(textButton)
        
    local button_scale9 = ccui.Button:create()
    button_scale9:setTouchEnabled(true)
    button_scale9:loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "")
    button_scale9:setScale9Enabled(true)
    button_scale9:setContentSize(cc.size(100, button_scale9:getVirtualRendererSize().height))
    button_scale9:setPosition(cc.p(layout:getContentSize().width - button_scale9:getContentSize().width / 2, button_scale9:getContentSize().height / 2))
    layout:addChild(button_scale9)  
end

function UIPanelBackGroundImageScale9Test.create()
    local scene = cc.Scene:create()
    local layer = UIPanelBackGroundImageScale9Test.extend(cc.Layer:create())
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

    local widgetSize = self._widget:getContentSize()
        
    local alert = ccui.Text:create()
    alert:setString("Panel Layout Linear Vertical")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 2.925))
    self._uiLayer:addChild(alert)

    local root = self._uiLayer:getChildByTag(81)
    local background = root:getChildByName("background_Panel")
    
    local layout = ccui.Layout:create()
    layout:setLayoutType(ccui.LayoutType.VERTICAL)
    layout:setContentSize(cc.size(280, 150))
    local backgroundSize = background:getContentSize()
    layout:setPosition(cc.p((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout:getContentSize().width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout:getContentSize().height) / 2))
    self._uiLayer:addChild(layout)
        
    local button = ccui.Button:create()
    button:setTouchEnabled(true)
    button:loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "")
    layout:addChild(button)
        
    local lp1 = ccui.LinearLayoutParameter:create()
    button:setLayoutParameter(lp1)
    lp1:setGravity(ccui.LinearGravity.centerHorizontal)
    lp1:setMargin({ left = 0, top = 5, right = 0, bottom = 10 })
        
        
    local textButton = ccui.Button:create()
    textButton:setTouchEnabled(true)
    textButton:loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "")
    textButton:setTitleText("Text Button")
    layout:addChild(textButton)
        
    local lp2 = ccui.LinearLayoutParameter:create()
    textButton:setLayoutParameter(lp2)
    lp2:setGravity(ccui.LinearGravity.centerHorizontal)
    lp2:setMargin({left = 0, top = 10, right = 0, bottom  = 10} )
        
        
    local button_scale9 = ccui.Button:create()
    button_scale9:setTouchEnabled(true)
    button_scale9:loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "")
    button_scale9:setScale9Enabled(true)
    button_scale9:setContentSize(cc.size(100, button_scale9:getVirtualRendererSize().height))
    layout:addChild(button_scale9)
        
    local lp3 = ccui.LinearLayoutParameter:create()
    button_scale9:setLayoutParameter(lp3)
    lp3:setGravity(ccui.LinearGravity.centerHorizontal)
    lp3:setMargin({ left = 0, top = 10, right = 0, bottom  = 10 } )
end

function UIPanelLayoutLinearVerticalTest.create()
    local scene = cc.Scene:create()
    local layer = UIPanelLayoutLinearVerticalTest.extend(cc.Layer:create())
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

    local widgetSize = self._widget:getContentSize()
        
    local alert = ccui.Text:create()
    alert:setString("Panel Layout Linear Horizontal")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 2.925))
    self._uiLayer:addChild(alert)

    local root = self._uiLayer:getChildByTag(81)
    local background = root:getChildByName("background_Panel")
    
    local layout = ccui.Layout:create()
    layout:setLayoutType(ccui.LayoutType.HORIZONTAL)
    layout:setClippingEnabled(true)
    layout:setContentSize(cc.size(280, 150))
    local backgroundSize = background:getContentSize()
    layout:setPosition(cc.p((widgetSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - layout:getContentSize().width) / 2,
                                (widgetSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - layout:getContentSize().height) / 2))
    self._uiLayer:addChild(layout)
        
    local button = ccui.Button:create()
    button:setTouchEnabled(true)
    button:loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "")
    layout:addChild(button)
        
    local lp1 = ccui.LinearLayoutParameter:create()
    button:setLayoutParameter(lp1)
    lp1:setGravity(ccui.LinearGravity.centerVertical)
    lp1:setMargin({left = 0, top  = 10, right = 0, bottom = 10} )
        
        
    local textButton = ccui.Button:create()
    textButton:setTouchEnabled(true)
    textButton:loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "")
    textButton:setTitleText("Text Button")
    layout:addChild(textButton)
        
    local lp2 = ccui.LinearLayoutParameter:create()
    textButton:setLayoutParameter(lp2)
    lp2:setGravity(ccui.LinearGravity.centerVertical)
    lp2:setMargin({left = 0,top = 10,right = 0,bottom = 10})
        
        
    local button_scale9 = ccui.Button:create()
    button_scale9:setTouchEnabled(true)
    button_scale9:loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "")
    button_scale9:setScale9Enabled(true)
    button_scale9:setContentSize(cc.size(100, button_scale9:getVirtualRendererSize().height))
    layout:addChild(button_scale9)
        
    local lp3 = ccui.LinearLayoutParameter:create()
    button_scale9:setLayoutParameter(lp3)
    lp3:setGravity(ccui.LinearGravity.centerVertical)
    lp3:setMargin({left = 0, top = 10, right = 0, bottom = 10})
end

function UIPanelLayoutLinearHorizontalTest.create()
    local scene = cc.Scene:create()
    local layer = UIPanelLayoutLinearHorizontalTest.extend(cc.Layer:create())
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

    local widgetSize = self._widget:getContentSize()
        
    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("Move by vertical direction")
    self._displayValueLabel:setFontName(font_TextName)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + self._displayValueLabel:getContentSize().height * 1.5))
    self._uiLayer:addChild(self._displayValueLabel)
        
    local alert = ccui.Text:create()
    alert:setString("ScrollView")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 2.925))
    self._uiLayer:addChild(alert)
    
    local root = self._uiLayer:getChildByTag(81)  
    local background = root:getChildByName("background_Panel")
        
    local scrollView = ccui.ScrollView:create()
    scrollView:setTouchEnabled(true)
    scrollView:setContentSize(cc.size(280, 150))        
    local backgroundSize = background:getContentSize()
    scrollView:setPosition(cc.p((widgetSize.width - backgroundSize.width) / 2 +
                               (backgroundSize.width - scrollView:getContentSize().width) / 2,
                               (widgetSize.height - backgroundSize.height) / 2 +
                               (backgroundSize.height - scrollView:getContentSize().height) / 2))
    self._uiLayer:addChild(scrollView)
        
    local imageView = ccui.ImageView:create()
    imageView:loadTexture("cocosui/ccicon.png")
        
    local innerWidth = scrollView:getContentSize().width
    local innerHeight = scrollView:getContentSize().height + imageView:getContentSize().height
        
    scrollView:setInnerContainerSize(cc.size(innerWidth, innerHeight))                
        
    local button = ccui.Button:create()
    button:setTouchEnabled(true)
    button:loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "")
    button:setPosition(cc.p(innerWidth / 2, scrollView:getInnerContainerSize().height - button:getContentSize().height / 2))
    scrollView:addChild(button)
        
    local textButton = ccui.Button:create()
    textButton:setTouchEnabled(true)
    textButton:loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "")
    textButton:setTitleText("Text Button")
    textButton:setPosition(cc.p(innerWidth / 2, button:getBottomBoundary() - button:getContentSize().height))
    scrollView:addChild(textButton)
        
    local button_scale9 = ccui.Button:create()
    button_scale9:setTouchEnabled(true)
    button_scale9:setScale9Enabled(true)
    button_scale9:loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "")
    button_scale9:setContentSize(cc.size(100, button_scale9:getVirtualRendererSize().height))
    button_scale9:setPosition(cc.p(innerWidth / 2, textButton:getBottomBoundary() - textButton:getContentSize().height))
    scrollView:addChild(button_scale9)
        
    imageView:setPosition(cc.p(innerWidth / 2, imageView:getContentSize().height / 2))
    scrollView:addChild(imageView)
end

function UIScrollViewVerticalTest.create()
    local scene = cc.Scene:create()
    local layer = UIScrollViewVerticalTest.extend(cc.Layer:create())
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

    local widgetSize = self._widget:getContentSize()
        
    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("Move by horizontal direction")
    self._displayValueLabel:setFontName(font_TextName)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + self._displayValueLabel:getContentSize().height * 1.5))
    self._uiLayer:addChild(self._displayValueLabel)            
        
    local alert = ccui.Text:create()
    alert:setString("ScrollView")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 2.925))
    self._uiLayer:addChild(alert)
    
    local root = self._uiLayer:getChildByTag(81)      
    local background = root:getChildByName("background_Panel")
        
    local scrollView = ccui.ScrollView:create()
    scrollView:setBounceEnabled(true)
    scrollView:setDirection(ccui.ScrollViewDir.horizontal)
    scrollView:setTouchEnabled(true)
    scrollView:setContentSize(cc.size(280, 150))
    scrollView:setInnerContainerSize(scrollView:getContentSize())
    local backgroundSize = background:getContentSize()
    scrollView:setPosition(cc.p((widgetSize.width - backgroundSize.width) / 2 +
                                    (backgroundSize.width - scrollView:getContentSize().width) / 2,
                                    (widgetSize.height - backgroundSize.height) / 2 +
                                    (backgroundSize.height - scrollView:getContentSize().height) / 2))
    self._uiLayer:addChild(scrollView)
        
    local imageView = ccui.ImageView:create()
    imageView:loadTexture("cocosui/ccicon.png")
        
    local innerWidth = scrollView:getContentSize().width + imageView:getContentSize().width
    local innerHeight = scrollView:getContentSize().height
        
    scrollView:setInnerContainerSize(cc.size(innerWidth, innerHeight))
        
    local button = ccui.Button:create()
    button:setTouchEnabled(true)
    button:loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "")
    button:setPosition(cc.p(button:getContentSize().width / 2,
                                scrollView:getInnerContainerSize().height - button:getContentSize().height / 2))
    scrollView:addChild(button)
        
    local textButton = ccui.Button:create()
    textButton:setTouchEnabled(true)
    textButton:loadTextures("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png", "")
    textButton:setTitleText("Text Button")
    textButton:setPosition(cc.p(button:getRightBoundary() + button:getContentSize().width / 2,
                                    button:getBottomBoundary() - button:getContentSize().height / 2))
    scrollView:addChild(textButton)
        
    local button_scale9 = ccui.Button:create()
    button_scale9:setTouchEnabled(true)
    button_scale9:setScale9Enabled(true)
    button_scale9:loadTextures("cocosui/button.png", "cocosui/buttonHighlighted.png", "")
    button_scale9:setContentSize(cc.size(100, button_scale9:getVirtualRendererSize().height))
    button_scale9:setPosition(cc.p(textButton:getRightBoundary() + textButton:getContentSize().width / 2,
                                       textButton:getBottomBoundary() - textButton:getContentSize().height / 2))
    scrollView:addChild(button_scale9)                
                
    imageView:setPosition(cc.p(innerWidth - imageView:getContentSize().width / 2,
                                   button_scale9:getBottomBoundary() - button_scale9:getContentSize().height / 2))
    scrollView:addChild(imageView)  
end

function UIScrollViewHorizontalTest.create()
    local scene = cc.Scene:create()
    local layer = UIScrollViewHorizontalTest.extend(cc.Layer:create())
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

    local widgetSize = self._widget:getContentSize()
        
    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("Move by horizontal direction")
    self._displayValueLabel:setFontName(font_TextName)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + self._displayValueLabel:getContentSize().height * 1.5))
    self._uiLayer:addChild(self._displayValueLabel)
        
    local alert = ccui.Text:create()
    alert:setString("PageView")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 2.925))
    self._uiLayer:addChild(alert)
     
    local root = self._uiLayer:getChildByTag(81)      
    local background = root:getChildByName("background_Panel")   
        
    local pageView = ccui.PageView:create()
    pageView:setTouchEnabled(true)
    pageView:setContentSize(cc.size(240, 130))
    local backgroundSize = background:getContentSize()
    pageView:setPosition(cc.p((widgetSize.width - backgroundSize.width) / 2 +
                                  (backgroundSize.width - pageView:getContentSize().width) / 2,
                                  (widgetSize.height - backgroundSize.height) / 2 +
                                  (backgroundSize.height - pageView:getContentSize().height) / 2))
      
    for i = 1 , 3 do
        local layout = ccui.Layout:create()
        layout:setContentSize(cc.size(240, 130))
            
        local imageView = ccui.ImageView:create()
        imageView:setTouchEnabled(true)
        imageView:setScale9Enabled(true)
        imageView:loadTexture("cocosui/scrollviewbg.png")
        imageView:setContentSize(cc.size(240, 130))
        imageView:setPosition(cc.p(layout:getContentSize().width / 2, layout:getContentSize().height / 2))
        layout:addChild(imageView)
            
        local label = ccui.Text:create()
        local pageInfo = string.format("page %d", i)
        label:setString(pageInfo)
        label:setFontName(font_TextName)
        label:setFontSize(30)
        label:setColor(cc.c3b(192, 192, 192))
        label:setPosition(cc.p(layout:getContentSize().width / 2, layout:getContentSize().height / 2))
        layout:addChild(label)
            
        pageView:addPage(layout)

    end 

    local function pageViewEvent(sender, eventType)
        if eventType == ccui.PageViewEventType.turning then
            local pageView = sender
            local pageInfo = string.format("page %d " , pageView:getCurPageIndex() + 1)
            self._displayValueLabel:setString(pageInfo)
        end
    end 

    pageView:addEventListener(pageViewEvent)
        
    self._uiLayer:addChild(pageView)
  
end

function UIPageViewTest.create()
    local scene = cc.Scene:create()
    local layer = UIPageViewTest.extend(cc.Layer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene    
end

local UIListViewVerticalTest = class("UIListViewVerticalTest",UIScene)
UIListViewVerticalTest._displayValueLabel = nil

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

    local widgetSize = self._widget:getContentSize()
        
    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("Move by vertical direction")
    self._displayValueLabel:setFontName(font_TextName)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + self._displayValueLabel:getContentSize().height * 1.5))
    self._uiLayer:addChild(self._displayValueLabel)
        
    local alert = ccui.Text:create()
    alert:setString("ListView")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 2.925))
    self._uiLayer:addChild(alert)

    local root = self._uiLayer:getChildByTag(81)
        
    local background = root:getChildByName("background_Panel")
    local backgroundSize = background:getContentSize()

    local array = {}
    for i = 1,20 do
        array[i] = string.format("ListView_item_%d",i - 1)
    end

    local function listViewEvent(sender, eventType)
        if eventType == ccui.ListViewEventType.ONSELECTEDITEM_START then
            print("select child index = ",sender:getCurSelectedIndex())
        end
    end

    local function scrollViewEvent(sender, evenType)
        if evenType == ccui.ScrollviewEventType.scrollToBottom then
            print("SCROLL_TO_BOTTOM")
        elseif evenType ==  ccui.ScrollviewEventType.scrollToTop then
            print("SCROLL_TO_TOP")
        end
    end

    local listView = ccui.ListView:create()
    -- set list view ex direction
    listView:setDirection(ccui.ScrollViewDir.vertical)
    listView:setBounceEnabled(true)
    listView:setBackGroundImage("cocosui/green_edit.png")
    listView:setBackGroundImageScale9Enabled(true)
    listView:setContentSize(cc.size(240, 130))
    listView:setPosition(cc.p((widgetSize.width - backgroundSize.width) / 2.0 +
                              (backgroundSize.width - listView:getContentSize().width) / 2.0,
                              (widgetSize.height - backgroundSize.height) / 2.0 +
                              (backgroundSize.height - listView:getContentSize().height) / 2.0))
    listView:addEventListener(listViewEvent)
    listView:addScrollViewEventListener(scrollViewEvent)
    self._uiLayer:addChild(listView)


    -- create model
    local default_button = ccui.Button:create("cocosui/backtotoppressed.png", "cocosui/backtotopnormal.png")
    default_button:setName("Title Button")
    
    local default_item = ccui.Layout:create()
    default_item:setTouchEnabled(true)
    default_item:setContentSize(default_button:getContentSize())
    default_button:setPosition(cc.p(default_item:getContentSize().width / 2.0, default_item:getContentSize().height / 2.0))
    default_item:addChild(default_button)

    --set model
    listView:setItemModel(default_item)
    
    --add default item
    local count = table.getn(array)
    for i = 1,math.floor(count / 4) do
        listView:pushBackDefaultItem()
    end
    --insert default item
    for i = 1,math.floor(count / 4) do
        listView:insertDefaultItem(0)
    end

    listView:removeAllChildren()

    local testSprite = cc.Sprite:create("cocosui/backtotoppressed.png")
    testSprite:setPosition(cc.p(200,200))
    listView:addChild(testSprite)
      
    --add custom item
    for i = 1,math.floor(count / 4) do
        local custom_button = ccui.Button:create("cocosui/button.png", "cocosui/buttonHighlighted.png")
        custom_button:setName("Title Button")
        custom_button:setScale9Enabled(true)
        custom_button:setContentSize(default_button:getContentSize())
        
        local custom_item = ccui.Layout:create()
        custom_item:setContentSize(custom_button:getContentSize())
        custom_button:setPosition(cc.p(custom_item:getContentSize().width / 2.0, custom_item:getContentSize().height / 2.0))
        custom_item:addChild(custom_button)
        
        listView:addChild(custom_item) 
    end

    --insert custom item
    local items = listView:getItems()
    local items_count = table.getn(items)
    for i = 1, math.floor(count / 4) do
        local custom_button = ccui.Button:create("cocosui/button.png", "cocosui/buttonHighlighted.png")
        custom_button:setName("Title Button")
        custom_button:setScale9Enabled(true)
        custom_button:setContentSize(default_button:getContentSize())
        
        local custom_item = ccui.Layout:create()
        custom_item:setContentSize(custom_button:getContentSize())
        custom_button:setPosition(cc.p(custom_item:getContentSize().width / 2.0, custom_item:getContentSize().height / 2.0))
        custom_item:addChild(custom_button)
        custom_item:setTag(1)
        
        listView:insertCustomItem(custom_item, items_count)
    end
    
    -- set item data
    items_count = table.getn(listView:getItems())
    for i = 1,items_count do
        local item = listView:getItem(i - 1)
        local button = item:getChildByName("Title Button")
        local index = listView:getIndex(item)
        button:setTitleText(array[index + 1])
    end
    
    -- remove last item
    listView:removeChildByTag(1)
    
    -- remove item by index
    items_count = table.getn(listView:getItems())
    listView:removeItem(items_count - 1)
    
    -- set all items layout gravity
    listView:setGravity(ccui.ListViewGravity.centerVertical)
    
    --set items margin
    listView:setItemsMargin(2.0)
end

function UIListViewVerticalTest.create()
    local scene = cc.Scene:create()
    local layer = UIListViewVerticalTest.extend(cc.Layer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene   
end

local UIListViewHorizontalTest = class("UIListViewHorizontalTest",UIScene)
UIListViewHorizontalTest._displayValueLabel = nil

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

    local widgetSize = self._widget:getContentSize()
        
    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("Move by vertical direction")
    self._displayValueLabel:setFontName(font_TextName)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + self._displayValueLabel:getContentSize().height * 1.5))
    self._uiLayer:addChild(self._displayValueLabel)
        
    local alert = ccui.Text:create()
    alert:setString("ListView")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 2.925))
    self._uiLayer:addChild(alert)
        

    local root = self._uiLayer:getChildByTag(81)
        
    local background = root:getChildByName("background_Panel")
    local backgroundSize = background:getContentSize()

    local array = {}
    for i = 1,20 do
        array[i] = string.format("ListView_item_%d",i - 1)
    end

    local function listViewEvent(sender, eventType)
        if eventType == ccui.ListViewEventType.ons_selected_item then
            print("select child index = ",sender:getCurSelectedIndex())
        end
    end

    local listView = ccui.ListView:create()
    -- set list view ex direction
    listView:setDirection(ccui.ScrollViewDir.horizontal)
    listView:setTouchEnabled(true)
    listView:setBounceEnabled(true)
    listView:setBackGroundImage("cocosui/green_edit.png")
    listView:setBackGroundImageScale9Enabled(true)
    listView:setContentSize(cc.size(240, 130))
    listView:setPosition(cc.p((widgetSize.width - backgroundSize.width) / 2.0 +
                              (backgroundSize.width - listView:getContentSize().width) / 2.0,
                              (widgetSize.height - backgroundSize.height) / 2.0 +
                              (backgroundSize.height - listView:getContentSize().height) / 2.0))
    listView:addEventListener(listViewEvent)
    self._uiLayer:addChild(listView)


    -- create model
    local default_button = ccui.Button:create("cocosui/backtotoppressed.png", "cocosui/backtotopnormal.png")
    default_button:setName("Title Button")
    
    local default_item = ccui.Layout:create()
    default_item:setTouchEnabled(true)
    default_item:setContentSize(default_button:getContentSize())
    default_button:setPosition(cc.p(default_item:getContentSize().width / 2.0, default_item:getContentSize().height / 2.0))
    default_item:addChild(default_button)

    --set model
    listView:setItemModel(default_item)
    
    --add default item
    local count = table.getn(array)
    for i = 1,math.floor(count / 4) do
        listView:pushBackDefaultItem()
    end
    --insert default item
    for i = 1,math.floor(count / 4) do
        listView:insertDefaultItem(0)
    end
      
    --add custom item
    for i = 1,math.floor(count / 4) do
        local custom_button = ccui.Button:create("cocosui/button.png", "cocosui/buttonHighlighted.png")
        custom_button:setName("Title Button")
        custom_button:setScale9Enabled(true)
        custom_button:setContentSize(default_button:getContentSize())
        
        local custom_item = ccui.Layout:create()
        custom_item:setContentSize(custom_button:getContentSize())
        custom_button:setPosition(cc.p(custom_item:getContentSize().width / 2.0, custom_item:getContentSize().height / 2.0))
        custom_item:addChild(custom_button)
        
        listView:pushBackCustomItem(custom_item) 
    end

    --insert custom item
    local items = listView:getItems()
    local items_count = table.getn(items)
    for i = 1, math.floor(count / 4) do
        local custom_button = ccui.Button:create("cocosui/button.png", "cocosui/buttonHighlighted.png")
        custom_button:setName("Title Button")
        custom_button:setScale9Enabled(true)
        custom_button:setContentSize(default_button:getContentSize())
        
        local custom_item = ccui.Layout:create()
        custom_item:setContentSize(custom_button:getContentSize())
        custom_button:setPosition(cc.p(custom_item:getContentSize().width / 2.0, custom_item:getContentSize().height / 2.0))
        custom_item:addChild(custom_button)
        
        listView:insertCustomItem(custom_item, items_count)
    end
    
    -- set item data
    items_count = table.getn(listView:getItems())
    print("items_count", items_count)
    for i = 1,items_count do
        local item = listView:getItem(i - 1)
        local button = item:getChildByName("Title Button")
        local index = listView:getIndex(item)
        print("index is ", index)
        button:setTitleText(array[index + 1])
    end
    
    -- remove last item
    listView:removeLastItem()
    
    -- remove item by index
    items_count = table.getn(listView:getItems())
    listView:removeItem(items_count - 1)
    
    -- set all items layout gravity
    listView:setGravity(ccui.ListViewGravity.centerVertical)
    
    --set items margin
    listView:setItemsMargin(2.0)
end

function UIListViewHorizontalTest.create()
    local scene = cc.Scene:create()
    local layer = UIListViewHorizontalTest.extend(cc.Layer:create())
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

    local widgetSize = self._widget:getContentSize()
        
    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("No Event")
    self._displayValueLabel:setFontName(font_TextName)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + self._displayValueLabel:getContentSize().height * 1.5))
    self._uiLayer:addChild(self._displayValueLabel)
        
    local alert = ccui.Text:create()
    alert:setString("DragPanel")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 2.925))
    self._uiLayer:addChild(alert)
        
    local sc = ccui.ScrollView:create()
    sc:setBackGroundColor(cc.c3b(0,255,0))
    sc:setBackGroundColorType(ccui.LayoutBackGroundColorType.solid)
    sc:setDirection(ccui.ScrollViewDir.both)
    sc:setInnerContainerSize(cc.size(480, 320))
    sc:setContentSize(cc.size(100,100))
    sc:setPosition(cc.p(100,100))
    sc:scrollToPercentBothDirection(cc.p(50, 50), 1, true)
    local iv = ccui.ImageView:create()
    iv:loadTexture("cocosui/Hello.png")
    iv:setPosition(cc.p(240, 160))
    sc:addChild(iv)
    self._uiLayer:addChild(sc)

end

function UIDragPanelTest.create()
    local scene = cc.Scene:create()
    local layer = UIDragPanelTest.extend(cc.Layer:create())
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

    local widgetSize = self._widget:getContentSize()

    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("No Event")
    self._displayValueLabel:setFontName(font_TextName)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + self._displayValueLabel:getContentSize().height * 1.5))
    self._uiLayer:addChild(self._displayValueLabel)        
        

    local alert = ccui.Text:create()
    alert:setString("DragPanel Bounce")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 2.925))
    self._uiLayer:addChild(alert)
        
    local sc = ccui.ScrollView:create()
    sc:setBackGroundColor(cc.c3b(0, 255 , 0))
    sc:setBackGroundColorType(ccui.LayoutBackGroundColorType.solid)
    sc:setBounceEnabled(true)
    sc:setDirection(ccui.ScrollViewDir.both)
    sc:setInnerContainerSize(cc.size(480, 320))
    sc:setContentSize(cc.size(100,100))
    sc:setPosition(cc.p(100,100))
    sc:scrollToPercentBothDirection(cc.p(50, 50), 1, true)
    local iv = ccui.ImageView:create()
    iv:loadTexture("cocosui/Hello.png")
    iv:setPosition(cc.p(240, 160))
    sc:addChild(iv)
    self._uiLayer:addChild(sc)
end

function UIDragPanelBounceTest.create()
    local scene = cc.Scene:create()
    local layer = UIDragPanelBounceTest.extend(cc.Layer:create())
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

    local widgetSize = self._widget:getContentSize()
    print("setFontName before")
    self._displayValueLabel = ccui.Text:create()
    self._displayValueLabel:setString("NodeContainer Add CCNode")
    self._displayValueLabel:setFontName(font_TextName)
    self._displayValueLabel:setFontSize(32)
    self._displayValueLabel:setAnchorPoint(cc.p(0.5, -1))
    self._displayValueLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + self._displayValueLabel:getContentSize().height * 1.5))
    self._uiLayer:addChild(self._displayValueLabel)
        
    local alert = ccui.Text:create()
    alert:setString("NodeContainer")
    alert:setFontName(font_TextName)
    alert:setFontSize(30)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 1.75))
    self._uiLayer:addChild(alert)
        
    local nodeContainer = ccui.Widget:create()
    nodeContainer:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addChild(nodeContainer)
        
    local sprite = cc.Sprite:create("cocosui/ccicon.png")
    sprite:setPosition(cc.p(0, sprite:getBoundingBox().height / 4))
    nodeContainer:addChild(sprite)
end

function UINodeContainerTest.create()
    local scene = cc.Scene:create()
    local layer = UINodeContainerTest.extend(cc.Layer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene   
end

local UIRichTextTest = class("UIRichTextTest",UIScene)

function UIRichTextTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIRichTextTest)
    return target
end

function UIRichTextTest:initExtend()
    
    self:init()

    local widgetSize = self._widget:getContentSize()

    local alert = ccui.Text:create("RichText", "fonts/Marker Felt.ttf", 30)
    alert:setFontName(font_TextName)
    alert:setColor(cc.c3b(159, 168, 176))
    alert:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - alert:getContentSize().height * 3.125))
    self._widget:addChild(alert)


    local function touchEvent(sender, eventType)
        if eventType == ccui.TouchEventType.ended then
            if self._richText:isIgnoreContentAdaptWithSize() then
                self._richText:ignoreContentAdaptWithSize(false)
                self._richText:setContentSize(cc.size(100, 100))
            else
                self._richText:ignoreContentAdaptWithSize(true)
            end
        end
    end

    local button = ccui.Button:create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png")
    button:setTouchEnabled(true)
    button:setTitleText("switch")
    button:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 + button:getContentSize().height * 2.5))
    button:addTouchEventListener(touchEvent)
    button:setLocalZOrder(10)
    self._widget:addChild(button)

    self._richText = ccui.RichText:create()
    self._richText:ignoreContentAdaptWithSize(false)
    self._richText:setContentSize(cc.size(100, 100))

    local re1 = ccui.RichElementText:create(1, cc.c3b(255, 255, 255), 255, "This color is white. ", "Helvetica", 10)
    local re2 = ccui.RichElementText:create(2, cc.c3b(255, 255,   0), 255, "And this is yellow. ", "Helvetica", 10)
    local re3 = ccui.RichElementText:create(3, cc.c3b(0,   0, 255), 255, "This one is blue. ", "Helvetica", 10)
    local re4 = ccui.RichElementText:create(4, cc.c3b(0, 255,   0), 255, "And green. ", "Helvetica", 10)
    local re5 = ccui.RichElementText:create(5, cc.c3b(255,  0,   0), 255, "Last one is red ", "Helvetica", 10)

    local reimg = ccui.RichElementImage:create(6, cc.c3b(255, 255, 255), 255, "cocosui/sliderballnormal.png")

    ccs.ArmatureDataManager:getInstance():addArmatureFileInfo("cocosui/100/100.ExportJson")
    local arr = ccs.Armature:create("100")
    arr:getAnimation():play("Animation1")

    local recustom = ccui.RichElementCustomNode:create(1, cc.c3b(255, 255, 255), 255, arr)
    local re6 = ccui.RichElementText:create(7, cc.c3b(255, 127,   0), 255, "Have fun!! ", "Helvetica", 10)
    self._richText:pushBackElement(re1)
    self._richText:insertElement(re2, 1)
    self._richText:pushBackElement(re3)
    self._richText:pushBackElement(re4)
    self._richText:pushBackElement(re5)
    self._richText:insertElement(reimg, 2)
    self._richText:pushBackElement(recustom)
    self._richText:pushBackElement(re6)
    
    self._richText:setPosition(cc.p(widgetSize.width / 2, widgetSize.height / 2))
    self._richText:setLocalZOrder(10)
    
    
    self._widget:addChild(self._richText)

end

function UIRichTextTest.create()
    local scene = cc.Scene:create()
    local layer = UIRichTextTest.extend(cc.Layer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene   
end

local UIFocusTestHorizontal = class("UIFocusTestHorizontal",UIScene)
function UIFocusTestHorizontal.extend( target )
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIFocusTestHorizontal)
    return target
end

function UIFocusTestHorizontal:initExtend()
    self:init()

    local root = self._uiLayer:getChildByTag(81)
    local background = root:getChildByName("background_Panel")
    background:removeFromParent(true)

    local function onLeftKeyPressed()
        local event = cc.EventKeyboard:new(cc.KeyCode.KEY_DPAD_LEFT, false)
        cc.Director:getInstance():getEventDispatcher():dispatchEvent(event)
    end

    local function onRightKeyPressed()
        local event = cc.EventKeyboard:new(cc.KeyCode.KEY_DPAD_RIGHT, false)
        cc.Director:getInstance():getEventDispatcher():dispatchEvent(event)
    end

    local function onUpKeyPressed()
        local event = cc.EventKeyboard:new(cc.KeyCode.KEY_DPAD_UP, false)
        cc.Director:getInstance():getEventDispatcher():dispatchEvent(event)
    end

    local function onDownKeyPressed()
        local event = cc.EventKeyboard:new(cc.KeyCode.KEY_DPAD_DOWN, false)
        cc.Director:getInstance():getEventDispatcher():dispatchEvent(event)
    end

    self._dpadMenu = cc.Menu:create()
    local winSize = cc.Director:getInstance():getVisibleSize()

    local leftItem = cc.MenuItemFont:create("Left")
    leftItem:setPosition(cc.p(winSize.width - 100, winSize.height/2))
    leftItem:registerScriptTapHandler(onLeftKeyPressed)
    self._dpadMenu:addChild(leftItem)

    local rightItem = cc.MenuItemFont:create("Right")
    rightItem:setPosition(cc.p(winSize.width - 30, winSize.height/2))
    rightItem:registerScriptTapHandler(onRightKeyPressed)
    self._dpadMenu:addChild(rightItem)

    local upItem = cc.MenuItemFont:create("Up")
    upItem:setPosition(cc.p(winSize.width - 60, winSize.height/2 + 50))
    upItem:registerScriptTapHandler(onUpKeyPressed)
    self._dpadMenu:addChild(upItem)

    local downItem = cc.MenuItemFont:create("Down")
    downItem:setPosition(cc.p(winSize.width - 60, winSize.height/2 - 50))
    downItem:registerScriptTapHandler(onDownKeyPressed)
    self._dpadMenu:addChild(downItem)
    self._dpadMenu:setPosition(cc.p(0, 0))
    self._uiLayer:addChild(self._dpadMenu)

    ccui.Widget:enableDpadNavigation(true)

    local function onFocusChanged(widgetLostFocus,widgetGetFocus)
        if nil ~= widgetGetFocus and widgetGetFocus:isFocusEnabled() then
             widgetGetFocus:setColor(cc.c3b(255, 0, 0))
        end

        if nil ~= widgetLostFocus and widgetLostFocus:isFocusEnabled() then
            widgetLostFocus:setColor(cc.c3b(255, 255, 255))
        end
    
        if nil ~= widgetLostFocus and nil ~= widgetGetFocus then
            print(string.format("on focus change, %d widget get focus, %d widget lose focus", widgetGetFocus:getTag(),  widgetLostFocus:getTag()))
        end
    end

    local eventListener = cc.EventListenerFocus:create()
    eventListener:registerScriptHandler(onFocusChanged)
    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithFixedPriority(eventListener, 1)

    local winSize = cc.Director:getInstance():getVisibleSize()
    self._horizontalLayout = ccui.HBox:create()
    self._horizontalLayout:setPosition(cc.p(20, winSize.height / 2 + 40))
    self._uiLayer:addChild(self._horizontalLayout)

    self._horizontalLayout:setFocused(true)
    self._horizontalLayout:setLoopFocus(true)
    self._horizontalLayout:setTag(100)
    self._firstFocusedWidget = self._horizontalLayout

    local function onImageViewClicked(sender, eventType)
        if eventType == ccui.TouchEventType.ended then
            local w = sender
            if w:isFocusEnabled() then
                w:setFocusEnabled(false)
                w:setColor(cc.c3b(255, 255,   0))
            else
                w:setFocusEnabled(true)
                w:setColor(cc.c3b(255, 255, 255))
            end
        end
    end

    local count = 3
    for i = 1, count do
        local imageView = ccui.ImageView:create("cocosui/scrollviewbg.png")
        imageView:setTouchEnabled(true)
        imageView:setTag(i)
        imageView:addTouchEventListener(onImageViewClicked)
        self._horizontalLayout:addChild(imageView)
    end

    self._loopText = ccui.Text:create("loop enabled", "Airal", 20)
    self._loopText:setPosition(cc.p(winSize.width/2, winSize.height - 50))
    self._loopText:setColor(cc.c3b(255, 0 ,0))
    self:addChild(self._loopText)

    local function toggleFocusLoop(sender, eventType)
        if eventType == ccui.TouchEventType.ended then
            self._horizontalLayout:setLoopFocus(not self._horizontalLayout:isLoopFocus())
            if self._horizontalLayout:isLoopFocus() then
                self._loopText:setString("loop enabled")
            else
                self._loopText:setString("loop disabled")
            end
        end
    end

    local btn = ccui.Button:create("cocosui/switch-mask.png")
    btn:setTitleText("Toggle Loop")
    btn:setPosition(cc.p(60, winSize.height - 50))
    btn:setTitleColor(cc.c3b(0, 255, 0))
    btn:addTouchEventListener(toggleFocusLoop)
    self:addChild(btn)
end

function UIFocusTestHorizontal.create()
    local scene = cc.Scene:create()
    local layer = UIFocusTestHorizontal.extend(cc.Layer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene   
end

local UIFocusTestVertical = class("UIFocusTestVertical",UIScene)

function UIFocusTestVertical.extend( target )
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIFocusTestVertical)
    return target
end

function UIFocusTestVertical:initExtend()
    self:init()

    local root = self._uiLayer:getChildByTag(81)
    local background = root:getChildByName("background_Panel")
    background:removeFromParent(true)

    local function onLeftKeyPressed()
        local event = cc.EventKeyboard:new(cc.KeyCode.KEY_DPAD_LEFT, false)
        cc.Director:getInstance():getEventDispatcher():dispatchEvent(event)
    end

    local function onRightKeyPressed()
        local event = cc.EventKeyboard:new(cc.KeyCode.KEY_DPAD_RIGHT, false)
        cc.Director:getInstance():getEventDispatcher():dispatchEvent(event)
    end

    local function onUpKeyPressed()
        local event = cc.EventKeyboard:new(cc.KeyCode.KEY_DPAD_UP, false)
        cc.Director:getInstance():getEventDispatcher():dispatchEvent(event)
    end

    local function onDownKeyPressed()
        local event = cc.EventKeyboard:new(cc.KeyCode.KEY_DPAD_DOWN, false)
        cc.Director:getInstance():getEventDispatcher():dispatchEvent(event)
    end

    self._dpadMenu = cc.Menu:create()
    local winSize = cc.Director:getInstance():getVisibleSize()

    local leftItem = cc.MenuItemFont:create("Left")
    leftItem:setPosition(cc.p(winSize.width - 100, winSize.height/2))
    leftItem:registerScriptTapHandler(onLeftKeyPressed)
    self._dpadMenu:addChild(leftItem)

    local rightItem = cc.MenuItemFont:create("Right")
    rightItem:setPosition(cc.p(winSize.width - 30, winSize.height/2))
    rightItem:registerScriptTapHandler(onRightKeyPressed)
    self._dpadMenu:addChild(rightItem)

    local upItem = cc.MenuItemFont:create("Up")
    upItem:setPosition(cc.p(winSize.width - 60, winSize.height/2 + 50))
    upItem:registerScriptTapHandler(onUpKeyPressed)
    self._dpadMenu:addChild(upItem)

    local downItem = cc.MenuItemFont:create("Down")
    downItem:setPosition(cc.p(winSize.width - 60, winSize.height/2 - 50))
    downItem:registerScriptTapHandler(onDownKeyPressed)
    self._dpadMenu:addChild(downItem)
    self._dpadMenu:setPosition(cc.p(0, 0))
    self._uiLayer:addChild(self._dpadMenu)

    ccui.Widget:enableDpadNavigation(true)

    local function onFocusChanged(widgetLostFocus,widgetGetFocus)
        if nil ~= widgetGetFocus and widgetGetFocus:isFocusEnabled() then
             widgetGetFocus:setColor(cc.c3b(255, 0, 0))
        end

        if nil ~= widgetLostFocus and widgetLostFocus:isFocusEnabled() then
            widgetLostFocus:setColor(cc.c3b(255, 255, 255))
        end
    
        if nil ~= widgetLostFocus and nil ~= widgetGetFocus then
            print(string.format("on focus change, %d widget get focus, %d widget lose focus", widgetGetFocus:getTag(),  widgetLostFocus:getTag()))
        end
    end

    local eventListener = cc.EventListenerFocus:create()
    eventListener:registerScriptHandler(onFocusChanged)
    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithFixedPriority(eventListener, 1)

    local winSize = cc.Director:getInstance():getVisibleSize()
    self._verticalLayout = ccui.VBox:create()
    self._verticalLayout:setPosition(cc.p(winSize.width/2 - 100, winSize.height - 70))
    self._uiLayer:addChild(self._verticalLayout)

    self._verticalLayout:setFocused(true)
    self._verticalLayout:setLoopFocus(true)
    self._verticalLayout:setTag(100)
    self._verticalLayout:setScale(0.5)
    self._firstFocusedWidget = self._verticalLayout

    local function onImageViewClicked(sender, eventType)
        if eventType == ccui.TouchEventType.ended then
            local w = sender
            if w:isFocusEnabled() then
                w:setFocusEnabled(false)
                w:setColor(cc.c3b(255, 255,   0))
            else
                w:setFocusEnabled(true)
                w:setColor(cc.c3b(255, 255, 255))
            end
        end
    end

    local count = 3
    for i = 1, count do
        local imageView = ccui.ImageView:create("cocosui/scrollviewbg.png")
        imageView:setTouchEnabled(true)
        imageView:setTag(i)
        imageView:addTouchEventListener(onImageViewClicked)
        self._verticalLayout:addChild(imageView)
    end

    self._loopText = ccui.Text:create("loop enabled", "Airal", 20)
    self._loopText:setPosition(cc.p(winSize.width/2, winSize.height - 50))
    self._loopText:setColor(cc.c3b(255, 0 ,0))
    self:addChild(self._loopText)

    local function toggleFocusLoop(sender, eventType)
        if eventType == ccui.TouchEventType.ended then
            self._verticalLayout:setLoopFocus(not self._verticalLayout:isLoopFocus())
            if self._verticalLayout:isLoopFocus() then
                self._loopText:setString("loop enabled")
            else
                self._loopText:setString("loop disabled")
            end
        end
    end

    local btn = ccui.Button:create("cocosui/switch-mask.png")
    btn:setTitleText("Toggle Loop")
    btn:setPosition(cc.p(60, winSize.height - 50))
    btn:setTitleColor(cc.c3b(0, 255, 0))
    btn:addTouchEventListener(toggleFocusLoop)
    self:addChild(btn)
end

function UIFocusTestVertical.create()
    local scene = cc.Scene:create()
    local layer = UIFocusTestVertical.extend(cc.Layer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene   
end

local UIFocusTestNestedLayout1 = class("UIFocusTestNestedLayout1",UIScene)

function UIFocusTestNestedLayout1.extend( target )
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIFocusTestNestedLayout1)
    return target
end

function UIFocusTestNestedLayout1:initExtend()
    self:init()

    local root = self._uiLayer:getChildByTag(81)
    local background = root:getChildByName("background_Panel")
    background:removeFromParent(true)

    local function onLeftKeyPressed()
        local event = cc.EventKeyboard:new(cc.KeyCode.KEY_DPAD_LEFT, false)
        cc.Director:getInstance():getEventDispatcher():dispatchEvent(event)
    end

    local function onRightKeyPressed()
        local event = cc.EventKeyboard:new(cc.KeyCode.KEY_DPAD_RIGHT, false)
        cc.Director:getInstance():getEventDispatcher():dispatchEvent(event)
    end

    local function onUpKeyPressed()
        local event = cc.EventKeyboard:new(cc.KeyCode.KEY_DPAD_UP, false)
        cc.Director:getInstance():getEventDispatcher():dispatchEvent(event)
    end

    local function onDownKeyPressed()
        local event = cc.EventKeyboard:new(cc.KeyCode.KEY_DPAD_DOWN, false)
        cc.Director:getInstance():getEventDispatcher():dispatchEvent(event)
    end

    self._dpadMenu = cc.Menu:create()
    local winSize = cc.Director:getInstance():getVisibleSize()

    local leftItem = cc.MenuItemFont:create("Left")
    leftItem:setPosition(cc.p(winSize.width - 100, winSize.height/2))
    leftItem:registerScriptTapHandler(onLeftKeyPressed)
    self._dpadMenu:addChild(leftItem)

    local rightItem = cc.MenuItemFont:create("Right")
    rightItem:setPosition(cc.p(winSize.width - 30, winSize.height/2))
    rightItem:registerScriptTapHandler(onRightKeyPressed)
    self._dpadMenu:addChild(rightItem)

    local upItem = cc.MenuItemFont:create("Up")
    upItem:setPosition(cc.p(winSize.width - 60, winSize.height/2 + 50))
    upItem:registerScriptTapHandler(onUpKeyPressed)
    self._dpadMenu:addChild(upItem)

    local downItem = cc.MenuItemFont:create("Down")
    downItem:setPosition(cc.p(winSize.width - 60, winSize.height/2 - 50))
    downItem:registerScriptTapHandler(onDownKeyPressed)
    self._dpadMenu:addChild(downItem)
    self._dpadMenu:setPosition(cc.p(0, 0))
    self._uiLayer:addChild(self._dpadMenu)

    ccui.Widget:enableDpadNavigation(true)

    local function onFocusChanged(widgetLostFocus,widgetGetFocus)
        if nil ~= widgetGetFocus and widgetGetFocus:isFocusEnabled() then
             widgetGetFocus:setColor(cc.c3b(255, 0, 0))
        end

        if nil ~= widgetLostFocus and widgetLostFocus:isFocusEnabled() then
            widgetLostFocus:setColor(cc.c3b(255, 255, 255))
        end
    
        if nil ~= widgetLostFocus and nil ~= widgetGetFocus then
            print(string.format("on focus change, %d widget get focus, %d widget lose focus", widgetGetFocus:getTag(),  widgetLostFocus:getTag()))
        end
    end

    local eventListener = cc.EventListenerFocus:create()
    eventListener:registerScriptHandler(onFocusChanged)
    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithFixedPriority(eventListener, 1)

    local winSize = cc.Director:getInstance():getVisibleSize()

    self._verticalLayout = ccui.VBox:create()
    self._verticalLayout:setPosition(cc.p(winSize.width/2 - 80, winSize.height - 70))
    self._uiLayer:addChild(self._verticalLayout)
    self._verticalLayout:setScale(0.5)

    self._verticalLayout:setFocused(true)
    self._verticalLayout:setLoopFocus(true)
    self._verticalLayout:setTag(100)
    self._firstFocusedWidget = self._verticalLayout

    local function onImageViewClicked(sender, eventType)
        if eventType == ccui.TouchEventType.ended then
            local w = sender
            if w:isFocusEnabled() then
                w:setFocusEnabled(false)
                w:setColor(cc.c3b(255, 255,   0))
            else
                w:setFocusEnabled(true)
                w:setColor(cc.c3b(255, 255, 255))
            end
        end
    end

    local count1 = 1
    for i = 1, count1 do
        local imageView = ccui.ImageView:create("cocosui/scrollviewbg.png")
        imageView:setAnchorPoint(cc.p(0, 0))
        imageView:setTouchEnabled(true)
        imageView:setScaleX(2.5)
        imageView:setTag(i - 1 + count1)
        imageView:addTouchEventListener(onImageViewClicked)
        self._verticalLayout:addChild(imageView)
    end

    local hbox = ccui.HBox:create()
    hbox:setScale(0.8)
    hbox:setTag(101)
    self._verticalLayout:addChild(hbox)

    local count2 = 2
    for i = 1, count2 do
        local imageView = ccui.ImageView:create("cocosui/scrollviewbg.png")
        imageView:setAnchorPoint(cc.p(0, 1))
        imageView:setScaleY(2.0)
        imageView:setTouchEnabled(true)
        imageView:setTag(i - 1 + count1 + count2)
        imageView:addTouchEventListener(onImageViewClicked)
        hbox:addChild(imageView)
    end

    local innerVBox = ccui.VBox:create()
    hbox:addChild(innerVBox)
    innerVBox:setTag(102)

    local count3 = 2
    for i = 1, count3 do
        local imageView = ccui.ImageView:create("cocosui/scrollviewbg.png")
        imageView:setTouchEnabled(true)
        imageView:setTag(i - 1 + count1 + count2 + count3)
        imageView:addTouchEventListener(onImageViewClicked)
        innerVBox:addChild(imageView)
    end

    self._loopText = ccui.Text:create("loop enabled", "Airal", 20)
    self._loopText:setPosition(cc.p(winSize.width/2, winSize.height - 50))
    self._loopText:setColor(cc.c3b(255, 0 ,0))
    self:addChild(self._loopText)

    local function toggleFocusLoop(sender, eventType)
        if eventType == ccui.TouchEventType.ended then
            self._verticalLayout:setLoopFocus(not self._verticalLayout:isLoopFocus())
            if self._verticalLayout:isLoopFocus() then
                self._loopText:setString("loop enabled")
            else
                self._loopText:setString("loop disabled")
            end
        end
    end

    local btn = ccui.Button:create("cocosui/switch-mask.png")
    btn:setTitleText("Toggle Loop")
    btn:setPosition(cc.p(60, winSize.height - 50))
    btn:setTitleColor(cc.c3b(0, 255, 0))
    btn:addTouchEventListener(toggleFocusLoop)
    self:addChild(btn)
end

function UIFocusTestNestedLayout1.create()
    local scene = cc.Scene:create()
    local layer = UIFocusTestNestedLayout1.extend(cc.Layer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene   
end

local UIFocusTestNestedLayout2 = class("UIFocusTestNestedLayout2",UIScene)

function UIFocusTestNestedLayout2.extend( target )
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIFocusTestNestedLayout2)
    return target
end

function UIFocusTestNestedLayout2:initExtend()
    self:init()

    local root = self._uiLayer:getChildByTag(81)
    local background = root:getChildByName("background_Panel")
    background:removeFromParent(true)

    local function onLeftKeyPressed()
        local event = cc.EventKeyboard:new(cc.KeyCode.KEY_DPAD_LEFT, false)
        cc.Director:getInstance():getEventDispatcher():dispatchEvent(event)
    end

    local function onRightKeyPressed()
        local event = cc.EventKeyboard:new(cc.KeyCode.KEY_DPAD_RIGHT, false)
        cc.Director:getInstance():getEventDispatcher():dispatchEvent(event)
    end

    local function onUpKeyPressed()
        local event = cc.EventKeyboard:new(cc.KeyCode.KEY_DPAD_UP, false)
        cc.Director:getInstance():getEventDispatcher():dispatchEvent(event)
    end

    local function onDownKeyPressed()
        local event = cc.EventKeyboard:new(cc.KeyCode.KEY_DPAD_DOWN, false)
        cc.Director:getInstance():getEventDispatcher():dispatchEvent(event)
    end

    self._dpadMenu = cc.Menu:create()
    local winSize = cc.Director:getInstance():getVisibleSize()

    local leftItem = cc.MenuItemFont:create("Left")
    leftItem:setPosition(cc.p(winSize.width - 100, winSize.height/2))
    leftItem:registerScriptTapHandler(onLeftKeyPressed)
    self._dpadMenu:addChild(leftItem)

    local rightItem = cc.MenuItemFont:create("Right")
    rightItem:setPosition(cc.p(winSize.width - 30, winSize.height/2))
    rightItem:registerScriptTapHandler(onRightKeyPressed)
    self._dpadMenu:addChild(rightItem)

    local upItem = cc.MenuItemFont:create("Up")
    upItem:setPosition(cc.p(winSize.width - 60, winSize.height/2 + 50))
    upItem:registerScriptTapHandler(onUpKeyPressed)
    self._dpadMenu:addChild(upItem)

    local downItem = cc.MenuItemFont:create("Down")
    downItem:setPosition(cc.p(winSize.width - 60, winSize.height/2 - 50))
    downItem:registerScriptTapHandler(onDownKeyPressed)
    self._dpadMenu:addChild(downItem)
    self._dpadMenu:setPosition(cc.p(0, 0))
    self._uiLayer:addChild(self._dpadMenu)

    ccui.Widget:enableDpadNavigation(true)

    local function onFocusChanged(widgetLostFocus,widgetGetFocus)
        if nil ~= widgetGetFocus and widgetGetFocus:isFocusEnabled() then
             widgetGetFocus:setColor(cc.c3b(255, 0, 0))
        end

        if nil ~= widgetLostFocus and widgetLostFocus:isFocusEnabled() then
            widgetLostFocus:setColor(cc.c3b(255, 255, 255))
        end
    
        if nil ~= widgetLostFocus and nil ~= widgetGetFocus then
            print(string.format("on focus change, %d widget get focus, %d widget lose focus", widgetGetFocus:getTag(),  widgetLostFocus:getTag()))
        end
    end

    local eventListener = cc.EventListenerFocus:create()
    eventListener:registerScriptHandler(onFocusChanged)
    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithFixedPriority(eventListener, 1)

    local winSize = cc.Director:getInstance():getVisibleSize()

    self._horizontalLayout = ccui.HBox:create()
    self._horizontalLayout:setPosition(cc.p(winSize.width/2 - 200, winSize.height - 70))
    self._uiLayer:addChild(self._horizontalLayout)
    self._horizontalLayout:setScale(0.6)

    self._horizontalLayout:setFocused(true)
    self._horizontalLayout:setLoopFocus(true)
    self._horizontalLayout:setTag(100)
    self._firstFocusedWidget = self._horizontalLayout

    local function onImageViewClicked(sender, eventType)
        if eventType == ccui.TouchEventType.ended then
            local w = sender
            if w:isFocusEnabled() then
                w:setFocusEnabled(false)
                w:setColor(cc.c3b(255, 255,   0))
            else
                w:setFocusEnabled(true)
                w:setColor(cc.c3b(255, 255, 255))
            end
        end
    end

    local count1 = 2
    for i = 1, count1 do
        local imageView = ccui.ImageView:create("cocosui/scrollviewbg.png")
        imageView:setAnchorPoint(cc.p(0, 1))
        imageView:setTouchEnabled(true)
        imageView:setScaleY(2.4)
        imageView:setTag(i - 1 + count1)
        imageView:addTouchEventListener(onImageViewClicked)
        self._horizontalLayout:addChild(imageView)
    end

    local vbox = ccui.VBox:create()
    vbox:setScale(0.8)
    vbox:setTag(101)
    self._horizontalLayout:addChild(vbox)

    local count2 = 2
    for i = 1, count2 do
        local imageView = ccui.ImageView:create("cocosui/scrollviewbg.png")
        imageView:setAnchorPoint(cc.p(0, 1))
        imageView:setScaleX(2.0)
        imageView:setTouchEnabled(true)
        imageView:setTag(i - 1 + count1 + count2)
        imageView:addTouchEventListener(onImageViewClicked)
        vbox:addChild(imageView)
    end

    local innerVBox = ccui.HBox:create()
    vbox:addChild(innerVBox)
    innerVBox:setTag(102)

    local count3 = 2
    for i = 1, count3 do
        local imageView = ccui.ImageView:create("cocosui/scrollviewbg.png")
        imageView:setTouchEnabled(true)
        imageView:setTag(i - 1 + count1 + count2 + count3)
        imageView:addTouchEventListener(onImageViewClicked)
        innerVBox:addChild(imageView)
    end

    self._loopText = ccui.Text:create("loop enabled", "Airal", 20)
    self._loopText:setPosition(cc.p(winSize.width/2, winSize.height - 50))
    self._loopText:setColor(cc.c3b(255, 0 ,0))
    self:addChild(self._loopText)

    local function toggleFocusLoop(sender, eventType)
        if eventType == ccui.TouchEventType.ended then
            self._horizontalLayout:setLoopFocus(not self._horizontalLayout:isLoopFocus())
            if self._horizontalLayout:isLoopFocus() then
                self._loopText:setString("loop enabled")
            else
                self._loopText:setString("loop disabled")
            end
        end
    end

    local btn = ccui.Button:create("cocosui/switch-mask.png")
    btn:setTitleText("Toggle Loop")
    btn:setPosition(cc.p(60, winSize.height - 50))
    btn:setTitleColor(cc.c3b(0, 255, 0))
    btn:addTouchEventListener(toggleFocusLoop)
    self:addChild(btn)
end

function UIFocusTestNestedLayout2.create()
    local scene = cc.Scene:create()
    local layer = UIFocusTestNestedLayout2.extend(cc.Layer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene   
end

local UIFocusTestNestedLayout3 = class("UIFocusTestNestedLayout3",UIScene)

function UIFocusTestNestedLayout3.extend( target )
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIFocusTestNestedLayout3)
    return target
end

function UIFocusTestNestedLayout3:initExtend()
    self:init()

    local root = self._uiLayer:getChildByTag(81)
    local background = root:getChildByName("background_Panel")
    background:removeFromParent(true)

    local function onLeftKeyPressed()
        local event = cc.EventKeyboard:new(cc.KeyCode.KEY_DPAD_LEFT, false)
        cc.Director:getInstance():getEventDispatcher():dispatchEvent(event)
    end

    local function onRightKeyPressed()
        local event = cc.EventKeyboard:new(cc.KeyCode.KEY_DPAD_RIGHT, false)
        cc.Director:getInstance():getEventDispatcher():dispatchEvent(event)
    end

    local function onUpKeyPressed()
        local event = cc.EventKeyboard:new(cc.KeyCode.KEY_DPAD_UP, false)
        cc.Director:getInstance():getEventDispatcher():dispatchEvent(event)
    end

    local function onDownKeyPressed()
        local event = cc.EventKeyboard:new(cc.KeyCode.KEY_DPAD_DOWN, false)
        cc.Director:getInstance():getEventDispatcher():dispatchEvent(event)
    end

    self._dpadMenu = cc.Menu:create()
    local winSize = cc.Director:getInstance():getVisibleSize()

    local leftItem = cc.MenuItemFont:create("Left")
    leftItem:setPosition(cc.p(winSize.width - 100, winSize.height/2))
    leftItem:registerScriptTapHandler(onLeftKeyPressed)
    self._dpadMenu:addChild(leftItem)

    local rightItem = cc.MenuItemFont:create("Right")
    rightItem:setPosition(cc.p(winSize.width - 30, winSize.height/2))
    rightItem:registerScriptTapHandler(onRightKeyPressed)
    self._dpadMenu:addChild(rightItem)

    local upItem = cc.MenuItemFont:create("Up")
    upItem:setPosition(cc.p(winSize.width - 60, winSize.height/2 + 50))
    upItem:registerScriptTapHandler(onUpKeyPressed)
    self._dpadMenu:addChild(upItem)

    local downItem = cc.MenuItemFont:create("Down")
    downItem:setPosition(cc.p(winSize.width - 60, winSize.height/2 - 50))
    downItem:registerScriptTapHandler(onDownKeyPressed)
    self._dpadMenu:addChild(downItem)
    self._dpadMenu:setPosition(cc.p(0, 0))
    self._uiLayer:addChild(self._dpadMenu)

    ccui.Widget:enableDpadNavigation(true)

    local function onFocusChanged(widgetLostFocus,widgetGetFocus)
        if nil ~= widgetGetFocus and widgetGetFocus:isFocusEnabled() then
             widgetGetFocus:setColor(cc.c3b(255, 0, 0))
        end

        if nil ~= widgetLostFocus and widgetLostFocus:isFocusEnabled() then
            widgetLostFocus:setColor(cc.c3b(255, 255, 255))
        end
    
        if nil ~= widgetLostFocus and nil ~= widgetGetFocus then
            print(string.format("on focus change, %d widget get focus, %d widget lose focus", widgetGetFocus:getTag(),  widgetLostFocus:getTag()))
        end
    end

    local eventListener = cc.EventListenerFocus:create()
    eventListener:registerScriptHandler(onFocusChanged)
    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithFixedPriority(eventListener, 1)

    local winSize = cc.Director:getInstance():getVisibleSize()

    self._verticalLayout = ccui.VBox:create()
    self._verticalLayout:setPosition(cc.p(40, winSize.height - 70))
    self._uiLayer:addChild(self._verticalLayout)
    self._verticalLayout:setScale(0.8)

    self._verticalLayout:setFocused(true)
    self._verticalLayout:setLoopFocus(true)
    self._verticalLayout:setTag(-1000)
    self._firstFocusedWidget = self._verticalLayout

    local upperHBox = ccui.HBox:create()
    upperHBox:setTag(-200)
    self._verticalLayout:addChild(upperHBox)

    local params = ccui.LinearLayoutParameter:create()
    params:setMargin({left = 0, top = 0, right = 50, bottom = 0})
        
    local vparams = ccui.LinearLayoutParameter:create()
    vparams:setMargin({left = 10, top = 0, right = 0, bottom = 140})
    upperHBox:setLayoutParameter(vparams)

    local function onImageViewClicked(sender, eventType)
        if eventType == ccui.TouchEventType.ended then
            local w = sender
            if w:isFocusEnabled() then
                w:setFocusEnabled(false)
                w:setColor(cc.c3b(255, 255,   0))
            else
                w:setFocusEnabled(true)
                w:setColor(cc.c3b(255, 255, 255))
            end
        end
    end

    local count = 3
    for i = 1, count do
        local firstVbox = ccui.VBox:create()
        firstVbox:setScale(0.5)
        firstVbox:setLayoutParameter(params)
        firstVbox:setTag(i * 100)

        local count1 = 3
        for j = 1, count1 do
            local imageView = ccui.ImageView:create("cocosui/scrollviewbg.png")
            imageView:setTouchEnabled(true)
            imageView:setTag(j + firstVbox:getTag())
            imageView:addTouchEventListener(onImageViewClicked)
            firstVbox:addChild(imageView)
        end

        upperHBox:addChild(firstVbox)
    end

    local bottomHBox = ccui.HBox:create()
    bottomHBox:setScale(0.5)
    bottomHBox:setTag(600)
    bottomHBox:setLayoutParameter(vparams)

    count = 3
    local bottomParams = ccui.LinearLayoutParameter:create()
    bottomParams:setMargin({left = 0, top = 0, right = 8, bottom = 0})
    for i = 1, count do
        local imageView = ccui.ImageView:create("cocosui/scrollviewbg.png")
        imageView:setLayoutParameter(bottomParams)
        imageView:setTouchEnabled(true)
        imageView:setTag(i + 600)
        imageView:addTouchEventListener(onImageViewClicked)
        bottomHBox:addChild(imageView)
    end

    self._verticalLayout:addChild(bottomHBox)

    self._loopText = ccui.Text:create("loop enabled", "Airal", 20)
    self._loopText:setPosition(cc.p(winSize.width/2, winSize.height - 50))
    self._loopText:setColor(cc.c3b(255, 0 ,0))
    self:addChild(self._loopText)

    local function toggleFocusLoop(sender, eventType)
        if eventType == ccui.TouchEventType.ended then
            self._verticalLayout:setLoopFocus(not self._verticalLayout:isLoopFocus())
            if self._verticalLayout:isLoopFocus() then
                self._loopText:setString("loop enabled")
            else
                self._loopText:setString("loop disabled")
            end
        end
    end

    local btn = ccui.Button:create("cocosui/switch-mask.png")
    btn:setTitleText("Toggle Loop")
    btn:setPosition(cc.p(60, winSize.height - 50))
    btn:setTitleColor(cc.c3b(0, 255, 0))
    btn:addTouchEventListener(toggleFocusLoop)
    self:addChild(btn)
end

function UIFocusTestNestedLayout3.create()
    local scene = cc.Scene:create()
    local layer = UIFocusTestNestedLayout3.extend(cc.Layer:create())
    layer:initExtend()
    scene:addChild(layer)
    return scene   
end

local cocoStudioGuiArray = 
{
    {
        title = "UIFocusTestHorizontal",
        func  = function () 
            return UIFocusTestHorizontal.create()
        end,
    },

    {
        title = "UIFocusTestVertical",
        func  = function () 
            return UIFocusTestVertical.create()
        end,
    },

    {
        title = "UIFocusTestNestedLayout1",
        func  = function () 
            return UIFocusTestNestedLayout1.create()
        end,
    },

    {
        title = "UIFocusTestNestedLayout2",
        func  = function () 
            return UIFocusTestNestedLayout2.create()
        end,
    },

    {
        title = "UIFocusTestNestedLayout3",
        func  = function () 
            return UIFocusTestNestedLayout3.create()
        end,
    },

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

    {
        title = "UIRichTextTest",
        func  = function()
            return UIRichTextTest.create()
        end
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
