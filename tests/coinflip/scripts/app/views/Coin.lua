
local Levels = import("..data.Levels")

local Coin = class("Coin", function(nodeType)
    local index = 1
    if nodeType == Levels.NODE_IS_BLACK then
        index = 8
    end
    local sprite = display.newSprite(string.format("#Coin%04d.png", index))
    sprite.isWhite = index == 1
    return sprite
end)

function Coin:flip(onComplete)
    local frames = display.newFrames("Coin%04d.png", 1, 8, not self.isWhite)
    local animation = display.newAnimation(frames, 0.3 / 8)
    self:playAnimationOnce(animation, false, onComplete)

    self:runAction(transition.sequence({
        CCScaleTo:create(0.15, 1.5),
        CCScaleTo:create(0.1, 1.0),
        CCCallFunc:create(function()
            local actions = {}
            local scale = 1.1
            local time = 0.04
            for i = 1, 5 do
                actions[#actions + 1] = CCScaleTo:create(time, scale, 1.0)
                actions[#actions + 1] = CCScaleTo:create(time, 1.0, scale)
                scale = scale * 0.95
                time = time * 0.8
            end
            actions[#actions + 1] = CCScaleTo:create(0, 1.0, 1.0)
            self:runAction(transition.sequence(actions))
        end)
    }))

    self.isWhite = not self.isWhite
end

return Coin
