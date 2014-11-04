
local LuabindingTestScene = game.createSceneClass("LuabindingTestScene")

function LuabindingTestScene:ctor()
    self:prepare({
        description = "Please check console output"
    })

    local items = {
        "avoidPeertableGC",
        "getCppFunction",
    }
    self:addChild(game.createMenu(items, handler(self, self.runTest)))
end

function LuabindingTestScene:avoidPeertableGCTest()
    local node = display.newNode()
    node:addNodeEventListener(cc.NODE_EVENT, function(event)
        printf("node event %s", event.name)
    end)
    node.customVar = 1
    node:setTag(1)
    self:addChild(node)

    printf("1. node.customVar = %s, expected = 1", tostring(node.customVar)) -- 1
    collectgarbage()
    collectgarbage()
    printf("2. node.customVar = %s, expected = 1", tostring(node.customVar)) -- 1

    self:performWithDelay(function()
        printf("3. node.customVar = %s, expected = 1", tostring(self:getChildByTag(1).customVar)) -- 1
        local node2 = self:getChildByTag(1)
        collectgarbage()
        collectgarbage()
        printf("4. node.customVar = %s, expected = 1", tostring(node2.customVar)) -- 1
        self:removeChildByTag(1)
        printf("5. node = %s, expected = nil", tostring(self:getChildByTag(1))) -- nil
        printf("6. node.customVar = %s, expected = nil", tostring(node2.customVar)) -- nil
    end, 1.0)
end

function LuabindingTestScene:getCppFunctionTest()
    -- override C++ class method
    function cc.Node:setPosition(x, y)
        printf("cc.Node:setPosition(%0.2f, %0.2f)", x, y)
        -- call origin C++ method
        local cfunction = tolua.getcfunction(cc.Node, "setPosition")
        cfunction(self, x, y)
    end

    local node = display.newNode()
    self:addChild(node)
    print("expected 'cc.Node:setPosition(100.00, 100.00)'")
    node:setPosition(100, 100) -- cc.Node:setPosition(100.00, 100.00)
    local x, y = node:getPosition()
    printf("x, y = %0.2f, %0.2f, expected 100.00, 100.00", x, y)

    -- restore C++ method
    tolua.resetcfunction(cc.Node, "setPosition")
    print("expected - no output")
    node:setPosition(100, 100)
end

return LuabindingTestScene
