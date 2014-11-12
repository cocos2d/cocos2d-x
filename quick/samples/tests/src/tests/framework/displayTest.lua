
local DisplayTestScene = game.createSceneClass("DisplayTestScene")

function DisplayTestScene:ctor()
    self:prepare({
        description = "Please check console output"
    })

    local items = {
        "addImageAsync",
        "scale9Sprite",
        "layerMultiTouch",
    }
    self:addChild(game.createMenu(items, handler(self, self.runTest)))
end

function DisplayTestScene:beforeRunTest()
    if self.coin then
        self.coin:removeSelf()
        self.coin = nil
    end

    if self.scale9sprite then
        self.scale9sprite:removeSelf()
        self.scale9sprite = nil
    end

    if self.layerTouch then
        self.layerTouch:removeSelf()
        self.layerTouch = nil
    end
end

function DisplayTestScene:addImageAsyncTest()
    print("display.removeSpriteFrameByImageName(\"Coin0001.png\")")
    display.removeSpriteFrameByImageName("Coin0001.png")
    print("display.addImageAsync(\"Coin0001.png\")")

    display.addImageAsync("Coin0001.png", function(event, texture)
        printf("display.addImageAsync(\"Coin0001.png\") - event = %s, texture = %s", event, tostring(texture))
        self.coin = display.newSprite("Coin0001.png", display.left + 100, display.cy)
        self:addChild(self.coin)
    end)
end

function DisplayTestScene:scale9SpriteTest()
    self.scale9sprite = display.newScale9Sprite("GreenButton.png")
    self:addChild(self.scale9sprite)

    self.scale9sprite:setContentSize(cc.size(140, 300))
    self.scale9sprite:setPosition(display.left + 100, display.cy)
    transition.fadeOut(self.scale9sprite, {time = 1.5, delay = 1})
    transition.fadeIn(self.scale9sprite, {time = 1.5, delay = 3})
end

function DisplayTestScene:layerMultiTouchTest()
    local function onTouch(event, points)
        print("----------------------------------------")
        print(event)
        for i = 1, #points, 3 do
            local x = points[i]
            local y = points[i + 1]
            local id = points[i + 2]
            print(x, y, id)
        end

        return true
    end

    self.onTouch = onTouch
    self.layerTouch = display.newLayer()
    self.layerTouch:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        return self:onTouch(event.name, event.points)
    end)
    self.layerTouch:setTouchEnabled(true)
    self:addChild(self.layerTouch)
end

return DisplayTestScene
