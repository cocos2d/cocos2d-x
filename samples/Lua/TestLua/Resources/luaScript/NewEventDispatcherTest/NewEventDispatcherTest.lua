local itemTagBasic = 1000

local testArray =
{
    TouchableSprite = 1,
    FixedPriority = 2,
    RemoveListenerWhenDispatching = 3,
    CustomEvent = 4,
    LabelKeyboardEvent = 5,
    SpriteAccelerationEvent = 6,
    RemoveAndRetainNode = 7,
    RemoveListenerAfterAdding = 8,
}

local curLayerIdx   = testArray.TouchableSprite

local EventDispatcherScene = class("EventDispatcherScene")
EventDispatcherScene.__index = EventDispatcherScene

function EventDispatcherScene.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, EventDispatcherScene)
    return target
end

function EventDispatcherScene.create()
    local scene = EventDispatcherScene.extend(cc.Scene:create())
    return scene
end


local EventDispatcherTestDemo = class("EventDispatcherTestDemo")
EventDispatcherTestDemo.__index = EventDispatcherTestDemo
EventDispatcherTestDemo._backItem   = nil
EventDispatcherTestDemo._restarItem = nil
EventDispatcherTestDemo._nextItem   = nil

function EventDispatcherTestDemo:onEnter()

end

function EventDispatcherTestDemo.title(idx)
    if testArray.TouchableSprite == idx then
        return "Touchable Sprite Test"
    elseif testArray.FixedPriority   == idx then
        return "Fixed priority test"
    elseif testArray.RemoveListenerWhenDispatching == idx then
        return "Add and remove listener\n when dispatching event"
    elseif testArray.CustomEvent == idx then
        return "Send custom event"
    elseif testArray.LabelKeyboardEvent == idx then
        return "Label Receives Keyboard Event"
    elseif testArray.SpriteAccelerationEvent == idx then
        return "Sprite Receives Acceleration Event"
    elseif testArray.RemoveAndRetainNode == idx then
        return "RemoveAndRetainNodeTest"
    elseif testArray.RemoveListenerAfterAdding == idx then
        return "RemoveListenerAfterAddingTest"
    end
end

function EventDispatcherTestDemo.subTitle(idx)
    if testArray.TouchableSprite == idx then
        return "Please drag the blocks"
    elseif testArray.FixedPriority   == idx then
        return "Fixed Priority, Blue: 30, Red: 20, Yellow: 10\n The lower value the higher priority will be."
    elseif testArray.RemoveListenerWhenDispatching == idx then
        return ""
    elseif testArray.CustomEvent == idx then
        return ""
    elseif testArray.LabelKeyboardEvent == idx then
        return "Please click keyboard\n(Only available on Desktop and Android)"
    elseif testArray.SpriteAccelerationEvent == idx then
        return "Please move your device\n(Only available on mobile)"
    elseif testArray.RemoveAndRetainNode == idx then
        return "Sprite should be removed after 5s, add to scene again after 5s"
    elseif testArray.RemoveListenerAfterAdding == idx then
        return "Should not crash!"
    end
end

function EventDispatcherTestDemo.create()
    local layer = EventDispatcherTestDemo.extend(cc.Layer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:onEnter()
        layer:creatTitleAndSubTitle(curLayerIdx)
    end

    return layer
end

function EventDispatcherTestDemo.backCallback()
    local newScene = EventDispatcherScene.create()
    newScene:addChild(backEventDispatcherTest())
    newScene:addChild(CreateBackMenuItem())
    cc.Director:getInstance():replaceScene(newScene)
end

function EventDispatcherTestDemo.restartCallback()
    local newScene = EventDispatcherScene.create()
    newScene:addChild(restartEventDispatcherTest())
    newScene:addChild(CreateBackMenuItem())
    cc.Director:getInstance():replaceScene(newScene)
end

function EventDispatcherTestDemo.nextCallback()
    local newScene = EventDispatcherScene.create()
    newScene:addChild(nextEventDispatcherTest())
    newScene:addChild(CreateBackMenuItem())
    cc.Director:getInstance():replaceScene(newScene)
end

function EventDispatcherTestDemo:createMenu()
    local menu = cc.Menu:create()

    self._backItem = cc.MenuItemImage:create(s_pPathB1, s_pPathB2)
    self._backItem:registerScriptTapHandler(self.backCallback)
    menu:addChild(self._backItem,itemTagBasic)
    self._restarItem = cc.MenuItemImage:create(s_pPathR1, s_pPathR2)
    self._restarItem:registerScriptTapHandler(self.restartCallback)
    menu:addChild(self._restarItem,itemTagBasic)
    self._nextItem = cc.MenuItemImage:create(s_pPathF1, s_pPathF2)
    menu:addChild(self._nextItem,itemTagBasic)
    self._nextItem:registerScriptTapHandler(self.nextCallback)

    local size = cc.Director:getInstance():getWinSize()
    self._backItem:setPosition(cc.p(size.width / 2 - self._restarItem:getContentSize().width * 2, self._restarItem:getContentSize().height / 2))
    self._restarItem:setPosition(cc.p(size.width / 2, self._restarItem:getContentSize().height / 2))
    self._nextItem:setPosition(cc.p(size.width / 2 + self._restarItem:getContentSize().width * 2, self._restarItem:getContentSize().height / 2))

    menu:setPosition(cc.p(0, 0))

    self:addChild(menu)
end

function EventDispatcherTestDemo:creatTitleAndSubTitle(idx)
    local title = cc.LabelTTF:create(EventDispatcherTestDemo.title(idx),"Arial",18)
    title:setColor(cc.c3b(128,128,0))
    self:addChild(title, 1, 10000)
    title:setPosition( cc.p(VisibleRect:center().x, VisibleRect:top().y - 30))
    local subTitle = nil
    if "" ~= EventDispatcherTestDemo.subTitle(idx) then
        local subTitle = cc.LabelTTF:create(EventDispatcherTestDemo.subTitle(idx), "Arial", 18)
        subTitle:setColor(cc.c3b(128,128,0))
        self:addChild(subTitle, 1, 10001)
        subTitle:setPosition( cc.p(VisibleRect:center().x, VisibleRect:top().y - 60) )
    end
end


local TouchableSpriteTest = class("TouchableSpriteTest",EventDispatcherTestDemo)
TouchableSpriteTest.__index = TouchableSpriteTest

function TouchableSpriteTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TouchableSpriteTest)
    return target
end

function TouchableSpriteTest:onEnter()
    local origin = cc.Director:getInstance():getVisibleOrigin()
    local size = cc.Director:getInstance():getVisibleSize()

    local sprite1 = cc.Sprite:create("Images/CyanSquare.png")
    sprite1:setPosition(cc.p(origin.x + size.width/2 - 80, origin.y + size.height/2 + 80))
    self:addChild(sprite1, 10)

    local sprite2 = cc.Sprite:create("Images/MagentaSquare.png")
    sprite2:setPosition(cc.p(origin.x + size.width/2, origin.x + size.height/2))
    self:addChild(sprite2, 20)

    local sprite3 = cc.Sprite:create("Images/YellowSquare.png")
    sprite3:setPosition(cc.p(0, 0))
    sprite2:addChild(sprite3, 1)

    local function onTouchBegan(touch, event)
        local target = tolua.cast(event:getCurrentTarget(),"cc.Sprite")
        
        local locationInNode = target:convertToNodeSpace(touch:getLocation())
        local s = target:getContentSize()
        local rect = cc.rect(0, 0, s.width, s.height)
        
        if cc.rectContainsPoint(rect, locationInNode) then
            print(string.format("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y))
            target:setOpacity(180)
            return true
        end
        return false
    end

    local function onTouchMoved(touch, event)
        local target = tolua.cast(event:getCurrentTarget(), "cc.Sprite")
        local posX,posY = target:getPosition()
        local delta = touch:getDelta()
        target:setPosition(cc.p(posX + delta.x, posY + delta.y))
    end

    local function onTouchEnded(touch, event)
        local target = tolua.cast(event:getCurrentTarget(), "cc.Sprite")
        print("sprite onTouchesEnded..")
        target:setOpacity(255)
        if target == sprite2 then
            sprite1:setLocalZOrder(100)
        elseif target == sprite1 then
            sprite1:setLocalZOrder(0)
        end
    end

    local listener1 = cc.EventListenerTouchOneByOne:create()
    listener1:setSwallowTouches(true)
    listener1:registerScriptHandler(onTouchBegan,cc.Handler.EVENT_TOUCH_BEGAN )
    listener1:registerScriptHandler(onTouchMoved,cc.Handler.EVENT_TOUCH_MOVED )
    listener1:registerScriptHandler(onTouchEnded,cc.Handler.EVENT_TOUCH_ENDED )
    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener1, sprite1)

    local listener2 = listener1:clone()
    listener2:registerScriptHandler(onTouchBegan,cc.Handler.EVENT_TOUCH_BEGAN)
    listener2:registerScriptHandler(onTouchMoved,cc.Handler.EVENT_TOUCH_MOVED)
    listener2:registerScriptHandler(onTouchEnded,cc.Handler.EVENT_TOUCH_ENDED )
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener2, sprite2)


    local listener3 = listener1:clone()
    listener3:registerScriptHandler(onTouchBegan,cc.Handler.EVENT_TOUCH_BEGAN )
    listener3:registerScriptHandler(onTouchMoved,cc.Handler.EVENT_TOUCH_MOVED )
    listener3:registerScriptHandler(onTouchEnded,cc.Handler.EVENT_TOUCH_ENDED )
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener3, sprite3)

    local function removeAllTouchItem(tag, sender)
        sender:setString("Only Next item could be clicked")
        eventDispatcher:removeEventListeners(cc.EVENT_TOUCH_ONE_BY_ONE)

        local nextMenuItem = cc.MenuItemFont:create("Next")
        nextMenuItem:setFontSizeObj(16)
        nextMenuItem:setPosition(cc.p(VisibleRect:right().x - 100, VisibleRect:right().y - 30))
        nextMenuItem:registerScriptTapHandler(self.nextCallback)
        
        local menu2 = cc.Menu:create(nextMenuItem)
        menu2:setPosition(cc.p(0, 0))
        menu2:setAnchorPoint(cc.p(0, 0))
        self:addChild(menu2)
    end

    local menuItem = cc.MenuItemFont:create("Remove All Touch Listeners")
    menuItem:setFontSizeObj(16)
    menuItem:setPosition(cc.p(VisibleRect:right().x - 100, VisibleRect:right().y))
    menuItem:registerScriptTapHandler(removeAllTouchItem)

    local menu  = cc.Menu:create(menuItem)
    menu:setPosition(cc.p(0, 0))
    menu:setAnchorPoint(cc.p(0, 0))
    self:addChild(menu)
end

function TouchableSpriteTest.create()
    local layer = TouchableSpriteTest.extend(cc.Layer:create())

    local function onNodeEvent(event)
        if event == "enter" then
            layer:onEnter()
        elseif event == "exit" then
        end
    end
    
    layer:createMenu()
    layer:creatTitleAndSubTitle(curLayerIdx)
    layer:registerScriptHandler(onNodeEvent)
    return layer
end

local TouchableSpriteWithFixedPriority = class("TouchableSpriteWithFixedPriority")
TouchableSpriteWithFixedPriority.__index = TouchableSpriteWithFixedPriority
TouchableSpriteWithFixedPriority._listener = nil
TouchableSpriteWithFixedPriority._fixedPriority = 0
TouchableSpriteWithFixedPriority._useNodePriority = false

function TouchableSpriteWithFixedPriority.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TouchableSpriteWithFixedPriority)
    return target
end

function TouchableSpriteWithFixedPriority:onEnter()
    local function onTouchBegan(touch, event)
        local locationInNode = self:convertToNodeSpace(touch:getLocation())
        local s = self:getContentSize()
        local rect = cc.rect(0, 0, s.width, s.height)
            
        if cc.rectContainsPoint(rect, locationInNode) then
            self:setColor(cc.c3b(255, 0, 0))
            return true
        end

        return false    
    end

    local function onTouchMoved(touch, event)
        
    end

    local  function onTouchEnded(touch, event)
        self:setColor(cc.c3b(255, 255, 255))
    end

    local listener = cc.EventListenerTouchOneByOne:create()
    self._listener = listener
    listener:setSwallowTouches(true)
    
    listener:registerScriptHandler(onTouchBegan,cc.Handler.EVENT_TOUCH_BEGAN )
    listener:registerScriptHandler(onTouchMoved,cc.Handler.EVENT_TOUCH_MOVED )
    listener:registerScriptHandler(onTouchEnded,cc.Handler.EVENT_TOUCH_ENDED )

    local eventDispatcher = self:getEventDispatcher()
    if self._useNodePriority then
        eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)
    else
        eventDispatcher:addEventListenerWithFixedPriority(listener,self._fixedPriority)
    end
end

function TouchableSpriteWithFixedPriority:onExit()
    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:removeEventListener(self._listener)
end

function TouchableSpriteWithFixedPriority:setPriority(fixedPriority)
    self._fixedPriority = fixedPriority
    self._useNodePriority = false
end

function TouchableSpriteWithFixedPriority:setPriorityWithThis(useNodePriority)
    self._fixedPriority = 0
    self._useNodePriority = useNodePriority
end

function TouchableSpriteWithFixedPriority.create()
    local touchableSprite = TouchableSpriteWithFixedPriority.extend(cc.Sprite:create())

    local function onNodeEvent(event)
        if event == "enter" then
            touchableSprite:onEnter()
        elseif event == "exit" then
            touchableSprite:onExit()
        end
    end
    
    touchableSprite:registerScriptHandler(onNodeEvent)
    return touchableSprite
end

local FixedPriorityTest = class("FixedPriorityTest",EventDispatcherTestDemo)
FixedPriorityTest.__index = FixedPriorityTest

function FixedPriorityTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, FixedPriorityTest)
    return target
end

function FixedPriorityTest:onEnter()
    local origin = cc.Director:getInstance():getVisibleOrigin()
    local size = cc.Director:getInstance():getVisibleSize()

    local sprite1 = TouchableSpriteWithFixedPriority.create()
    sprite1:setTexture("Images/CyanSquare.png")
    sprite1:setPriority(30)
    sprite1:setPosition(cc.p(origin.x + size.width/2 - 80, origin.y + size.height/2 + 40))
    self:addChild(sprite1, 10)

    local sprite2 = TouchableSpriteWithFixedPriority.create()
    sprite2:setTexture("Images/MagentaSquare.png")
    sprite2:setPriority(20)
    sprite2:setPosition(cc.p(origin.x + size.width/2, origin.y + size.height/2) )
    self:addChild(sprite2, 20)

    local sprite3 = TouchableSpriteWithFixedPriority:create()
    sprite3:setTexture("Images/YellowSquare.png")
    sprite3:setPriority(10)
    sprite3:setPosition(cc.p(0, 0))
    sprite2:addChild(sprite3, 1)
end

function FixedPriorityTest.create()
    local layer = FixedPriorityTest.extend(cc.Layer:create())

    local function onNodeEvent(event)
        if event == "enter" then
            layer:onEnter()
        elseif event == "exit" then
        end
    end
    
    layer:createMenu()
    layer:creatTitleAndSubTitle(curLayerIdx)
    layer:registerScriptHandler(onNodeEvent)
    return layer
end

local RemoveListenerWhenDispatchingTest = class("RemoveListenerWhenDispatchingTest",EventDispatcherTestDemo)
RemoveListenerWhenDispatchingTest.__index = RemoveListenerWhenDispatchingTest

function RemoveListenerWhenDispatchingTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, RemoveListenerWhenDispatchingTest)
    return target
end

function RemoveListenerWhenDispatchingTest:onEnter()
    local origin = cc.Director:getInstance():getVisibleOrigin()
    local size = cc.Director:getInstance():getVisibleSize()

    local sprite1 = cc.Sprite:create("Images/CyanSquare.png")
    sprite1:setPosition(cc.p(origin.x + size.width/2, origin.y + size.height/2))
    self:addChild(sprite1, 10)

    local function onTouchBegan(touch, event)
        local locationInNode = sprite1:convertToNodeSpace(touch:getLocation())
        local s = sprite1:getContentSize()
        local rect = cc.rect(0, 0, s.width, s.height)

         if cc.rectContainsPoint(rect, locationInNode) then
            sprite1:setColor(cc.c3b(255, 0, 0))
            return true
        end
        
        return false
    end

    local function onTouchEnded(touch, event)
        sprite1:setColor(cc.c3b(255, 255, 255))
    end

    local listener1 = cc.EventListenerTouchOneByOne:create()
    listener1:setSwallowTouches(true)
    self:setUserObject(listener1)

    listener1:registerScriptHandler(onTouchBegan,cc.Handler.EVENT_TOUCH_BEGAN )
    listener1:registerScriptHandler(onTouchEnded,cc.Handler.EVENT_TOUCH_ENDED )

    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener1, sprite1)

    local statusLabel = cc.LabelTTF:create("The sprite could be touched!", "", 20)
    statusLabel:setPosition(cc.p(origin.x + size.width/2, origin.y + size.height - 90))
    self:addChild(statusLabel)

    local enable = true
    local function toggleCallback(tag, sender)
        if enable then
            eventDispatcher:removeEventListener(listener1)
            statusLabel:setString("The sprite could not be touched!")
            enable = false
        else
            eventDispatcher:addEventListenerWithSceneGraphPriority(listener1, sprite1)
            statusLabel:setString("The sprite could be touched!")
            enable = true
        end
    end

    local toggleItem = cc.MenuItemToggle:create(cc.MenuItemFont:create("Enabled"), cc.MenuItemFont:create("Disabled"))
    toggleItem:setPosition(cc.p(origin.x + size.width/2, origin.y + 80))
    toggleItem:registerScriptTapHandler(toggleCallback)
    local menu = cc.Menu:create(toggleItem)
    menu:setPosition(cc.p(0, 0))
    menu:setAnchorPoint(cc.p(0, 0))
    self:addChild(menu, -1)
end


function RemoveListenerWhenDispatchingTest.create()
    local layer = RemoveListenerWhenDispatchingTest.extend(cc.Layer:create())

    local function onNodeEvent(event)
        if event == "enter" then
            layer:onEnter()
        elseif event == "exit" then
        end
    end
    
    layer:createMenu()
    layer:creatTitleAndSubTitle(curLayerIdx)
    layer:registerScriptHandler(onNodeEvent)
    return layer
end

local CustomEventTest = class("CustomEventTest",EventDispatcherTestDemo)
CustomEventTest.__index = CustomEventTest
CustomEventTest._listener1 = nil
CustomEventTest._listener2 = nil

function CustomEventTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, CustomEventTest)
    return target
end

function CustomEventTest:onEnter()
    local origin = cc.Director:getInstance():getVisibleOrigin()
    local size = cc.Director:getInstance():getVisibleSize()
    local count1 = 0
    local count2 = 0
    
    cc.MenuItemFont:setFontSize(20)

    local statusLabel1 = cc.LabelTTF:create("No custom event 1 received!", "", 20)
    statusLabel1:setPosition(cc.p(origin.x + size.width/2, origin.y + size.height-90 ))
    self:addChild(statusLabel1)

    local function eventCustomListener1(event)
        local str = "Custom event 1 received, "..event._usedata.." times"
        statusLabel1:setString(str)
    end

    local listener1 = cc.EventListenerCustom:create("game_custom_event1",eventCustomListener1)
    self._listener1 = listener1
    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithFixedPriority(listener1, 1)

    local function sendCallback1(tag, sender)
        count1 = count1 + 1
        
        local event = cc.EventCustom:new("game_custom_event1")
        event._usedata = string.format("%d",count1)
        eventDispatcher:dispatchEvent(event)
    end
    local sendItem1 = cc.MenuItemFont:create("Send Custom Event 1")
    sendItem1:registerScriptTapHandler(sendCallback1)
    sendItem1:setPosition(cc.p(origin.x + size.width/2, origin.y + size.height/2))

    local statusLabel2 = cc.LabelTTF:create("No custom event 2 received!", "", 20)
    statusLabel2:setPosition(cc.p(origin.x + size.width/2, origin.y + size.height-120 ))
    self:addChild(statusLabel2)

    local function eventCustomListener2(event)
        local str = "Custom event 2 received, "..event._usedata.." times"
        statusLabel2:setString(str)
    end

    local listener2 = cc.EventListenerCustom:create("game_custom_event2",eventCustomListener2)
    CustomEventTest._listener2 = listener2
    eventDispatcher:addEventListenerWithFixedPriority(listener2, 1)

    local function sendCallback2(tag, sender)
        count2 = count2 + 1
        
        local event = cc.EventCustom:new("game_custom_event2")
        event._usedata = string.format("%d",count2)
        eventDispatcher:dispatchEvent(event)
    end
    local sendItem2 = cc.MenuItemFont:create("Send Custom Event 2")
    sendItem2:registerScriptTapHandler(sendCallback2)
    sendItem2:setPosition(cc.p(origin.x + size.width/2, origin.y + size.height/2 - 40))

    local menu = cc.Menu:create(sendItem1, sendItem2)
    menu:setPosition(cc.p(0, 0))
    menu:setAnchorPoint(cc.p(0, 0))
    self:addChild(menu, -1)
end

function CustomEventTest:onExit()
    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:removeEventListener(self._listener1)
    eventDispatcher:removeEventListener(self._listener2)
end

function CustomEventTest.create()
    local layer = CustomEventTest.extend(cc.Layer:create())

    local function onNodeEvent(event)
        if event == "enter" then
            layer:onEnter()
        elseif event == "exit" then
            layer:onExit()
        end
    end
    
    layer:createMenu()
    layer:creatTitleAndSubTitle(curLayerIdx)
    layer:registerScriptHandler(onNodeEvent)
    return layer
end



local LabelKeyboardEventTest = class("LabelKeyboardEventTest",EventDispatcherTestDemo)
LabelKeyboardEventTest.__index = LabelKeyboardEventTest

function LabelKeyboardEventTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, LabelKeyboardEventTest)
    return target
end

function LabelKeyboardEventTest:onEnter()
    local origin = cc.Director:getInstance():getVisibleOrigin()
    local size = cc.Director:getInstance():getVisibleSize()
    
    local statusLabel = cc.LabelTTF:create("No keyboard event received!", "", 20)
    statusLabel:setPosition(cc.p(origin.x + size.width/2,origin.y + size.height/2))
    self:addChild(statusLabel)

    local function onKeyPressed(keyCode, event)
        local buf = string.format("Key %s was pressed!",string.char(keyCode))
        local label = event:getCurrentTarget()
        label:setString(buf)
    end

    local function onKeyReleased(keyCode, event)
        local buf = string.format("Key %s was released!",string.char(keyCode))
        local label = event:getCurrentTarget()
        label:setString(buf)
    end

    local listener = cc.EventListenerKeyboard:create()
    listener:registerScriptHandler(onKeyPressed, cc.Handler.EVENT_KEYBOARD_PRESSED )
    listener:registerScriptHandler(onKeyReleased, cc.Handler.EVENT_KEYBOARD_RELEASED )

    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, statusLabel)
end


function LabelKeyboardEventTest.create()
    local layer = LabelKeyboardEventTest.extend(cc.Layer:create())

    local function onNodeEvent(event)
        if event == "enter" then
            layer:onEnter()
        elseif event == "exit" then
        end
    end
    
    layer:createMenu()
    layer:creatTitleAndSubTitle(curLayerIdx)
    layer:registerScriptHandler(onNodeEvent)
    return layer
end

local SpriteAccelerationEventTest = class("SpriteAccelerationEventTest",EventDispatcherTestDemo)
SpriteAccelerationEventTest.__index = SpriteAccelerationEventTest

function SpriteAccelerationEventTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, SpriteAccelerationEventTest)
    return target
end

function SpriteAccelerationEventTest:onEnter()
    self:setAccelerometerEnabled(true)
    local origin = cc.Director:getInstance():getVisibleOrigin()
    local size   = cc.Director:getInstance():getVisibleSize()
    local sprite = cc.Sprite:create("Images/ball.png")
    sprite:setPosition(cc.p(VisibleRect:center().x, VisibleRect:center().y))
    self:addChild(sprite)

    local function accelerometerListener(event,x,y,z,timestamp)
        local target  = event:getCurrentTarget()
        local ballSize = target:getContentSize()
        local ptNowX,ptNowY    = target:getPosition()
        ptNowX = ptNowX + x * 9.81
        ptNowY = ptNowY + y * 9.81

        local minX  = math.floor(VisibleRect:left().x + ballSize.width / 2.0)
        local maxX  = math.floor(VisibleRect:right().x - ballSize.width / 2.0)
        if ptNowX <   minX then
            ptNowX = minX
        elseif ptNowX > maxX then
            ptNowX = maxX
        end
      
        local minY  = math.floor(VisibleRect:bottom().y + ballSize.height / 2.0)
        local maxY  = math.floor(VisibleRect:top().y   - ballSize.height / 2.0)
        if ptNowY <   minY then
            ptNowY = minY
        elseif ptNowY > maxY then
            ptNowY = maxY
        end

        target:setPosition(cc.p(ptNowX , ptNowY))
    end

    local listerner  = cc.EventListenerAcceleration:create(accelerometerListener)

    self:getEventDispatcher():addEventListenerWithSceneGraphPriority(listerner,sprite)
end

function SpriteAccelerationEventTest:onExit()
    self:setAccelerometerEnabled(false)
end

function SpriteAccelerationEventTest.create()
    local layer = SpriteAccelerationEventTest.extend(cc.Layer:create())

    local function onNodeEvent(event)
        if event == "enter" then
            layer:onEnter()
        elseif event == "exit" then
            layer:onExit()
        end
    end
    
    layer:createMenu()
    layer:creatTitleAndSubTitle(curLayerIdx)
    layer:registerScriptHandler(onNodeEvent)
    return layer
end


local RemoveAndRetainNodeTest = class("RemoveAndRetainNodeTest",EventDispatcherTestDemo)
RemoveAndRetainNodeTest.__index = RemoveAndRetainNodeTest
RemoveAndRetainNodeTest._spriteSaved = false
RemoveAndRetainNodeTest._sprite      = nil

function RemoveAndRetainNodeTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, RemoveAndRetainNodeTest)
    return target
end

function RemoveAndRetainNodeTest:onEnter()
    self._spriteSaved = false
    local origin = cc.Director:getInstance():getVisibleOrigin()
    local size = cc.Director:getInstance():getVisibleSize()

    local sprite = cc.Sprite:create("Images/CyanSquare.png")
    sprite:setPosition(cc.p(origin.x + size.width/2, origin.y + size.height/2))
    self._sprite = sprite
    self:addChild(sprite, 10)

    local function onTouchBegan(touch,event)
        local target = event:getCurrentTarget()
        local locationInNode = target:convertToNodeSpace(touch:getLocation())
        local s = target:getContentSize()
        local rect = cc.rect(0, 0, s.width, s.height)
        
        if cc.rectContainsPoint(rect, locationInNode) then
            print(string.format("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y))
            target:setOpacity(180)
            return true
        end
        return false 
    end

    local function onTouchMoved(touch,event)
        local target = event:getCurrentTarget()
        local posX,posY = target:getPosition()
        local delta = touch:getDelta()
        target:setPosition(cc.p(posX + delta.x, posY + delta.y))
    end

    local function onTouchEnded(touch,event)
        local target = event:getCurrentTarget()
        print("sprite onTouchesEnded.. ")
        target:setOpacity(255)
    end

    local listener1 = cc.EventListenerTouchOneByOne:create()
    listener1:setSwallowTouches(true)
    listener1:registerScriptHandler(onTouchBegan,cc.Handler.EVENT_TOUCH_BEGAN)
    listener1:registerScriptHandler(onTouchMoved,cc.Handler.EVENT_TOUCH_MOVED)
    listener1:registerScriptHandler(onTouchEnded,cc.Handler.EVENT_TOUCH_ENDED)
    self:getEventDispatcher():addEventListenerWithSceneGraphPriority(listener1, sprite)

    local function retainSprite()
        self._spriteSaved = true
        self._sprite:retain()
        self._sprite:removeFromParent()
    end

    local function releaseSprite()
        self._spriteSaved = false
        self:addChild(self._sprite)
        self._sprite:release()
    end

    self:runAction( cc.Sequence:create(cc.DelayTime:create(5.0),
                                     cc.CallFunc:create(retainSprite),
                                     cc.DelayTime:create(5.0),
                                     cc.CallFunc:create(releaseSprite)
                                    ))

end

function RemoveAndRetainNodeTest:onExit()
    if self._spriteSaved then
        self._sprite:release()
    end
end

function RemoveAndRetainNodeTest.create()
    local layer = RemoveAndRetainNodeTest.extend(cc.Layer:create())

    local function onNodeEvent(event)
        if event == "enter" then
            layer:onEnter()
        elseif event == "exit" then
            layer:onExit()
        end
    end
    
    layer:createMenu()
    layer:creatTitleAndSubTitle(curLayerIdx)
    layer:registerScriptHandler(onNodeEvent)
    return layer
end

local RemoveListenerAfterAddingTest = class("RemoveListenerAfterAddingTest",EventDispatcherTestDemo)
RemoveListenerAfterAddingTest.__index = RemoveListenerAfterAddingTest


function RemoveListenerAfterAddingTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, RemoveListenerAfterAddingTest)
    return target
end

function RemoveListenerAfterAddingTest:onEnter()

    local eventDispatcher = self:getEventDispatcher()

    local function item1Callback(tag, sender)

        local function onTouchBegan(touch, event)
            CCASSERT(false, "Should not come here!")
            return true
        end

        local listener = cc.EventListenerTouchOneByOne:create()
        listener:registerScriptHandler(onTouchBegan, cc.Handler.EVENT_TOUCH_BEGAN)
        eventDispatcher:addEventListenerWithFixedPriority(listener, -1)
        eventDispatcher:removeEventListener(listener)
    end

    local item1 = cc.MenuItemFont:create("Click Me 1")
    item1:registerScriptTapHandler(item1Callback)
    item1:setPosition(cc.p(VisibleRect:center().x, VisibleRect:center().y + 80))

    local function addNextButton()

        local function nextButtonCallback(tag, sender)
            self.restartCallback()
        end

        local nextButton = cc.MenuItemFont:create("Please Click Me To Reset!")
        nextButton:registerScriptTapHandler(nextButtonCallback)
        nextButton:setPosition(cc.p(VisibleRect:center().x,  VisibleRect:center().y - 40))
        
        local menu = cc.Menu:create(nextButton)
        menu:setPosition(VisibleRect:leftBottom())
        menu:setAnchorPoint(cc.p(0,0))
        self:addChild(menu)
    end

    local function item2Callback( tag, sender )

        local function onTouchBegan(touch, event)
            print("Should not come here!")
            return true
        end

        local listener = cc.EventListenerTouchOneByOne:create()
        listener:registerScriptHandler(onTouchBegan,cc.Handler.EVENT_TOUCH_BEGAN)
        
        eventDispatcher:addEventListenerWithFixedPriority(listener, -1)
        eventDispatcher:removeEventListeners(cc.EVENT_TOUCH_ONE_BY_ONE)
        
        addNextButton()

    end

    local item2 = cc.MenuItemFont:create("Click Me 2")
    item2:registerScriptTapHandler(item2Callback)
    item2:setPosition(cc.p(VisibleRect:center().x, VisibleRect:center().y + 40))

    local function item3Callback( tag, sender )

        local function onTouchBegan(touch, event)
            print("Should not come here!")
            return true
        end

        local listener = cc.EventListenerTouchOneByOne:create()
        listener:registerScriptHandler(onTouchBegan,cc.Handler.EVENT_TOUCH_BEGAN)
        
        eventDispatcher:addEventListenerWithFixedPriority(listener, -1)
        eventDispatcher:removeAllEventListeners()
        
        addNextButton()

    end

    local item3 = cc.MenuItemFont:create("Click Me 3")
    item3:registerScriptTapHandler(item3Callback)
    item3:setPosition(VisibleRect:center())

    local menu = cc.Menu:create(item1, item2, item3)
    menu:setPosition(VisibleRect:leftBottom())
    menu:setAnchorPoint(cc.p(0,0))

    self:addChild(menu)
end

function RemoveListenerAfterAddingTest:onExit()

end

function RemoveListenerAfterAddingTest.create()
    local layer = RemoveListenerAfterAddingTest.extend(cc.Layer:create())

    local function onNodeEvent(event)
        if event == "enter" then
            layer:onEnter()
        elseif event == "exit" then
            layer:onExit()
        end
    end
    
    layer:createMenu()
    layer:creatTitleAndSubTitle(curLayerIdx)
    layer:registerScriptHandler(onNodeEvent)
    return layer
end


local createFunction =
{
    TouchableSpriteTest.create,
    FixedPriorityTest.create,
    RemoveListenerWhenDispatchingTest.create,
    CustomEventTest.create,
    LabelKeyboardEventTest.create,
    SpriteAccelerationEventTest.create,
    RemoveAndRetainNodeTest.create,
    RemoveListenerAfterAddingTest.create,
}

function nextEventDispatcherTest()
    curLayerIdx = curLayerIdx + 1
    curLayerIdx = curLayerIdx % table.getn(createFunction)
    if 0 == curLayerIdx then
        curLayerIdx = table.getn(createFunction)
    end
    return createFunction[curLayerIdx]()
end

function backEventDispatcherTest()
    curLayerIdx = curLayerIdx - 1
    if curLayerIdx <= 0 then
        curLayerIdx = curLayerIdx + table.getn(createFunction)
    end

    return createFunction[curLayerIdx]()
end

function restartEventDispatcherTest()
    return createFunction[curLayerIdx]()
end


function NewEventDispatcherTest()
    local scene = EventDispatcherScene.create()
    curLayerIdx   = testArray.TouchableSprite
    scene:addChild(restartEventDispatcherTest())
    scene:addChild(CreateBackMenuItem())
    return scene
end
