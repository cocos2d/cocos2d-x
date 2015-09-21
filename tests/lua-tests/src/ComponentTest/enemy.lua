
--require "scene"

local enemy = {
    onEnter = function(self)
        local director = cc.Director:getInstance()
        local winSize = director:getVisibleSize()
        local visibleOrigin = director:getVisibleOrigin()
        local owner = self:getOwner()
        local contentSize = owner:getContentSize()
        local minY = contentSize.height / 2
        local maxY = winSize.height - contentSize.height/2
        local rangeY = maxY - minY
        local actualY = math.random(1000) % rangeY + minY
        owner:setPosition(winSize.width + contentSize.width/2, visibleOrigin.y + actualY)

        local minDuration = 2;
        local maxDuration = 4;
        local rangeDuration = maxDuration - minDuration
        local actualDuration = math.random(1000) % rangeDuration + minDuration
        local actionMove = cc.MoveTo:create(actualDuration * 2, cc.p(0 - contentSize.width/2, actualY))
        local sceneScriptComponent = tolua.cast(owner:getParent():getComponent("sceneLuaComponent"), "cc.ComponentLua")
        local sceneScript = sceneScriptComponent:getScriptObject()
        local actionMoveDone = cc.CallFunc:create(sceneScript.looseGame)
        owner:runAction(cc.Sequence:create(actionMove, actionMoveDone))
    end,

    onExit = function(self)
        -- body
    end
}

return enemy
