
local DisplayTestScene = game.createSceneClass("DisplayTestScene")

function DisplayTestScene:ctor()
    self:prepare({
        description = "Please check console output"
    })

    local items = {
        "addImageAsync",
        "scale9Sprite",
        "tilesSprite",
        "tiledBatchNode",
        "drawNode",
        "progress",
        "layerMultiTouch"
    }
    self:addChild(game.createMenu(items, handler(self, self.runTest)))

    display.setTexturePixelFormat("Coin0001.png", cc.TEXTURE2D_PIXEL_FORMAT_RGB565)
    display.setTexturePixelFormat("blocks9ss.png", cc.TEXTURE2D_PIXEL_FORMAT_RGB565)

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

    if self.tilesSprite_ then
        self.tilesSprite_:removeSelf()
        self.tilesSprite_ = nil
    end

    if self.tiledBatchNode_ then
        self.tiledBatchNode_:removeSelf()
        self.tiledBatchNode_ = nil
    end

    if self.drawNode_ then
        self.drawNode_:removeSelf()
        self.drawNode_ = nil
    end

    if self.progressNode_ then
        self.progressNode_:removeSelf()
        self.progressNode_ = nil
    end
end

function DisplayTestScene:addImageAsyncTest()
    print("display.removeSpriteFrameByImageName(\"Coin0001.png\")")
    display.removeSpriteFrameByImageName("Coin0001.png")
    print("display.addImageAsync(\"Coin0001.png\")")

    display.addImageAsync("Coin0001.png", function(event, texture)
        printf("display.addImageAsync(\"Coin0001.png\") - event = %s, texture = %s", tostring(event), tostring(texture))
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

function DisplayTestScene:tilesSpriteTest()
    self.tilesSprite_ = display.newTilesSprite("close.png", cc.rect(10, 10, 100, 100))
        :pos(display.left + 10, display.bottom + 10)
        :addTo(self)
end

function DisplayTestScene:tiledBatchNodeTest()
    local cb = function(plist, image)
        self.tiledBatchNode_ = display.newTiledBatchNode("#blocks9.png", "blocks9ss.png", cc.size(170, 170), 10, 10)
            :pos(display.left + 10, display.bottom + 150)
            :addTo(self)
    end
    display.addSpriteFrames("blocks9ss.plist", "blocks9ss.png", cb)
end

function DisplayTestScene:drawNodeTest()
    local node = display.newNode()
        :addTo(self)
    self.drawNode_ = node

    display.newSolidCircle(20,
        {x = 30, y = 50, color = cc.c4f(1, 1, 1, 1)})
        :addTo(node, 100, 101)

    display.newCircle(50,
        {x = display.right - 100, y = display.bottom + 100,
        fillColor = cc.c4f(1, 0, 0, 1),
        borderColor = cc.c4f(0, 1, 0, 1),
        borderWidth = 2})
        :addTo(node, 100)

    display.newRect(cc.rect(30, 200, 80, 80),
        {fillColor = cc.c4f(1,0,0,1), borderColor = cc.c4f(0,1,0,1), borderWidth = 5})
        :addTo(node, 100, 101)

    display.newLine(
        {
            {10, 10},
            {200, 30}
        },
        {
            borderColor = cc.c4f(1.0, 0.0, 0.0, 1.0),
            borderWidth = 1
        })
        :addTo(node, 100, 101)

    local points = {
        {10, 120},  -- point 1
        {50, 160},  -- point 2
        {100, 120}, -- point 3
    }
    display.newPolygon(points,
        {
            borderColor = cc.c4f(0, 1, 0, 1)
        })
        :addTo(node, 100)

end

function DisplayTestScene:progressTest()
    local progress = display.newProgressTimer("Coin0001.png", display.PROGRESS_TIMER_RADIAL)
        :pos(100, 100)
        :addTo(self)
    progress:setPercentage(60)
    self.progressNode_ = progress
end

function DisplayTestScene:onExit()
    display.removeSpriteFramesWithFile("blocks9ss.plist", "blocks9ss.png")
    display.removeUnusedSpriteFrames()
end

return DisplayTestScene
