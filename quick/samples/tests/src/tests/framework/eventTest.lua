
local EventTestScene = game.createSceneClass("EventTestScene")

function EventTestScene:ctor()
    self:prepare({
        description = "Please check console output"
    })

    local items = {
        "addEventListener",
        "removeEventListener",
        "removeAllListener",
        "removeCoin",
        "sendEvent"
    }
    self:addChild(game.createMenu(items, handler(self, self.runTest)))

    self:init()
end

function EventTestScene:init()

    self.idx = 0
    self.node = display.newNode()
    self.node:addTo(self)
    self.coin = display.newSprite("Coin0001.png",
        display.left + 100, display.cy,
        {size = cc.size(200, 200)})
    :addTo(self)

    cc(self.node):addComponent("components.behavior.EventProtocol"):exportMethods()
    self.node:removeComponent("components.behavior.EventProtocol")
    self.node:addComponent("components.behavior.EventProtocol"):exportMethods()
    self.eventProxy = cc.EventProxy.new(self.node, self.coin)
    local scene, eventHandle2 = self.eventProxy
        :addEventListener("EventTest1", function(event) print("event listener 1") dump(event) end, "tag1")
        :addEventListener("EventTest2", function(event) print("event listener 2") dump(event) end, 1001)
    self.eventHandle2 = eventHandle2
end

function EventTestScene:addEventListenerTest()
    self.eventProxy:addEventListener("EventTest3", function(event) print("event listener 3") dump(event) end, "tag3")
    self.eventProxy:addEventListener("EventTest4", function(event) print("event listener 4") dump(event) end)
end

function EventTestScene:removeEventListenerTest()
    self.eventProxy:removeEventListener(self.eventHandle2)
    local eventHandle1 = self.eventProxy:getEventHandle("EventTest1")
    self.eventProxy:removeEventListener(eventHandle1)
    self.eventProxy:removeAllEventListenersForEvent("EventTest3")
end

function EventTestScene:removeAllListenerTest()
    self.eventProxy:removeAllEventListeners()
end

function EventTestScene:removeCoinTest()
    self.coin:removeSelf()
end

function EventTestScene:sendEventTest()
    self.idx = self.idx + 1
    if self.idx > 4 then
        self.idx = 1
    end
    self.node:dispatchEvent({name = "EventTest" .. self.idx})
end

return EventTestScene
