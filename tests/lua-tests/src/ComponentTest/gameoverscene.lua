local GameOverLayer = {
    
    create = function(self, content)
        local label = cc.Label:createWithTTF(content, "fonts/Marker Felt.ttf", 32)
        local winSize = cc.Director:getInstance():getWinSize()
        label:setColor(cc.c3b(0, 0, 0))
        label:setPosition(winSize.width/2, winSize.height/2)

        local layer = cc.LayerColor:create(cc.c4b(0, 128, 255, 255))
        layer:addChild(label)
        layer:runAction(cc.Sequence:create(cc.DelayTime:create(3), cc.CallFunc:create(self.gameOverDone)))

        return layer
    end,

    gameOverDone = function(self, node)
        -- send event
        cc.Director:getInstance():getEventDispatcher():dispatchCustomEvent("component game over")
    end
}

GameOverScene = {
    create = function(label)
        local scene = cc.Scene:create()
        local layer = GameOverLayer:create(label)
        scene:addChild(layer)

        return scene
    end
}