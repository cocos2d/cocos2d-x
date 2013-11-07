UIScene = class("UIScene")
UIScene.__index = UIScene
UIScene._uiLayer= nil
UIScene._widget=nil
UIScene._sceneTitle=nil
UIScene._topDisplayLabel=nil
UIScene._bottomDisplayLabel=nil

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
    self._uiLayer:scheduleUpdate()
    self:addChild(this._uiLayer)

    self._widget = ccs.UIHelper:getInstance():createWidgetFromJsonFile("res/cocosgui/UITest/UITest.json")
    self._uiLayer:addWidget(self._widget)

    self._sceneTitle = self._uiLayer:getWidgetByName("UItest")

    local back_label = self._uiLayer:getWidgetByName("back")
    --back_label:addTouchEventListener(this.toExtensionsMainLayer, this)

    local left_button = self._uiLayer:getWidgetByName("left_Button")
    --left_button:addTouchEventListener(this.previousCallback ,this)

    local middle_button = self._uiLayer:getWidgetByName("middle_Button")
    --middle_button.addTouchEventListener(this.restartCallback ,this)

    local right_button = self._uiLayer:getWidgetByName("right_Button")
    --right_button.addTouchEventListener(this.nextCallback ,this)

    local winSize = cc.Director:getInstance():getWinSize()
    local scale = winSize.height / 320
    self._uiLayer:setAnchorPoint(cc.p(0,0))
    self._uiLayer:setScale(scale)
    self._uiLayer:setPosition(cc.p((winSize.width - 480 * scale) / 2, (winSize.height - 320 * scale) / 2))

    local widgetSize = self._widget.getRect().size
    local eventLabel = ccs.UILabel:create()
    eventLabel:setText("")
    eventLabel:setFontName("Marker Felt")
    eventLabel:setFontSize(32)
    eventLabel:setAnchorPoint(cc.p(0.5, -1))
    eventLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0))
    self._uiLayer:addWidget(eventLabel)
    self._topDisplayLabel = eventLabel

    local uiLabel = ccs.UILabel:create()
    uiLabel:setText("")
    uiLabel:setFontName("Marker Felt")
    uiLabel:setFontSize(30)
    uiLabel:setColor(cc.c3b(159, 168, 176))
    uiLabel:setPosition(cc.p(widgetSize.width / 2.0, widgetSize.height / 2.0 - uiLabel.getRect().size.height * 1.75))
    self._uiLayer.addWidget(uiLabel)
    self._bottomDisplayLabel = uiLabel   
end

function UIScene.create()
    local scene = UIScene.extend(cc.Scene:create())
    scene:init()
    return scene   
end