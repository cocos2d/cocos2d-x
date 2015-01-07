
local BugSprite = class("BugSprite", function(imageFilename)
    local texture = display.getImage(imageFilename)
    local frameWidth = texture:getPixelsWide() / 3
    local frameHeight = texture:getPixelsHigh()

    local spriteFrame = display.newSpriteFrame(texture, cc.rect(0, 0, frameWidth, frameHeight))
    local sprite = display.newSprite(spriteFrame)
    sprite.animationName_ = imageFilename
    sprite.frameWidth_ = frameWidth
    sprite.frameHeight_ = frameHeight
    return sprite
end)

function BugSprite:ctor(imageFilename, bugModel)
    self.model_ = bugModel
end

function BugSprite:getModel()
    return self.model_
end

function BugSprite:start(destination)
    self.model_:setDestination(destination)
    self:updatePosition()
    self:playAnimationForever(display.getAnimationCache(self.animationName_))
    return self
end

function BugSprite:step(dt)
    self.model_:step(dt)
    self:updatePosition()
    return self
end

function BugSprite:updatePosition()
    self:move(self.model_:getPosition())
        :rotate(self.model_:getRotation())
end

return BugSprite
