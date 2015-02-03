
local DeadBugSprite = class("DeadBugSprite", function(imageFilename)
    local texture = display.getImage(imageFilename)
    local frameWidth = texture:getPixelsWide() / 3
    local frameHeight = texture:getPixelsHigh()
    local spriteFrame = display.newSpriteFrame(texture, cc.rect(frameWidth * 2, 0, frameWidth, frameHeight))
    return display.newSprite(spriteFrame)
end)

return DeadBugSprite
