--
-- Author: SunLightJuly
-- Date: 2014-07-31 11:16:16
--
local Hero = class("Hero", function()
    return ccs.Armature:create("hero")
end)

function Hero:changeMount(armature)
    if nil == armature then
        --note
        self:retain()

        self:playWithIndex(0)
        self._mount:getBone("hero"):removeDisplay(0)
        self._mount:stopAllActions()
        self:setPosition(self._mount:getPosition())
        self._layer:addChild(self)
        self:release()
        self._mount = armature
    else
        self._mount = armature
        self:retain()
        self:removeFromParent(false)
        local bone = armature:getBone("hero")
        bone:addDisplay(self, 0)
        bone:changeDisplayWithIndex(0, true)
        bone:setIgnoreMovementBoneData(true)
        self:setPosition(cc.p(0,0))
        self:playWithIndex(1)
        self:setScale(1)
        self:release()
    end
end

function Hero:playWithIndex(index)
    self:getAnimation():playWithIndex(index)
    if nil ~= self._mount then
        self._mount:getAnimation():playWithIndex(index)
    end
end

return Hero