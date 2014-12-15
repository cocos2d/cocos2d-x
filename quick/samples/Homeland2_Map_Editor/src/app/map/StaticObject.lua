
local StaticObjectsProperties = require("app.properties.StaticObjectsProperties")

local ObjectBase = require("app.map.ObjectBase")
local StaticObject = class("StaticObject", ObjectBase)

function StaticObject:ctor(id, state, map)
    assert(state.defineId ~= nil, "StaticObject:ctor() - invalid state.defineId")
    local define = StaticObjectsProperties.get(state.defineId)
    for k, v in pairs(define) do
        if state[k] == nil then
            state[k] = v
        end
    end
    StaticObject.super.ctor(self, id, state, map)

    self.radiusOffsetX_ = checkint(self.radiusOffsetX_)
    self.radiusOffsetY_ = checkint(self.radiusOffsetY_)
    self.radius_        = checkint(self.radius_)
    self.flipSprite_    = checkbool(self.flipSprite_)
    self.visible_       = true
    self.valid_         = true
    self.sprite_        = nil
    self.spriteSize_    = nil
end

function StaticObject:getDefineId()
    return self.defineId_
end

function StaticObject:getRadius()
    return self.radius_
end

function StaticObject:isFlipSprite()
    return self.flipSprite_
end

function StaticObject:setFlipSprite(flipSprite)
    self.flipSprite_ = flipSprite
end

function StaticObject:getView()
    return self.sprite_
end

function StaticObject:createView(batch, marksLayer, debugLayer)
    StaticObject.super.createView(self, batch, marksLayer, debugLayer)

    if self.framesName_ then
        local frames = display.newFrames(self.framesName_, self.framesBegin_, self.framesLength_)
        self.sprite_ = display.newSprite(frames[1])
        self.sprite_:playAnimationForever(display.newAnimation(frames, self.framesTime_))
    else
        local imageName = self.imageName_
        if type(imageName) == "table" then
            imageName = imageName[1]
        end
        self.sprite_ = display.newSprite(imageName)
    end

    local size = self.sprite_:getContentSize()
    self.spriteSize_ = {size.width, size.height}

    if self.scale_ then
        self.sprite_:setScale(self.scale_)
    end

    batch:addChild(self.sprite_)
end

function StaticObject:removeView()
    if not self.sprite_ then
        return
    end

    self.sprite_:removeSelf()
    self.sprite_ = nil
    StaticObject.super.removeView(self)
end

function StaticObject:updateView()
    if not self.sprite_ then
        return
    end

    local sprite = self.sprite_
    sprite:setPosition(math.floor(self.x_ + self.offsetX_), math.floor(self.y_ + self.offsetY_))
    sprite:setFlippedX(self.flipSprite_)
end

function StaticObject:fastUpdateView()
    if not self.updated__ then return end
    local sprite = self.sprite_
    sprite:setPosition(self.x_ + self.offsetX_, self.y_ + self.offsetY_)
    sprite:setFlippedX(self.flipSprite_)
end

function StaticObject:isVisible()
    return self.visible_
end

function StaticObject:setVisible(visible)
    self.sprite_:setVisible(visible)
    self.visible_ = visible
end

function StaticObject:preparePlay()
end

function StaticObject:vardump()
    local state = StaticObject.super.vardump(self)
    state.defineId    = self.defineId_
    state.flipSprite  = self.flipSprite_
    return state
end

return StaticObject
