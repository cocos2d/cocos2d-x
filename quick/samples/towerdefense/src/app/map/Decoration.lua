
local StaticObjectsDecorationProperties = require("app.properties.StaticObjectsDecorationProperties")

local Decoration = class("Decoration")

function Decoration:ctor(decorationName, staticIndex)
    local define = StaticObjectsDecorationProperties.get(decorationName)
    assert(define,
           string.format("Decoration.ctor() - invalid decoration %s", decorationName))

    for k,v in pairs(define) do
        self[k .. "_"] = v
    end
    if staticIndex then
        if type(self.imageName_) == "table" then
            self.imageName_ = self.imageName_[staticIndex]
        end
        if type(self.offsetX_) == "table" then
            self.offsetX_ = self.offsetX_[staticIndex]
        end
        if type(self.offsetY_) == "table" then
            self.offsetY_ = self.offsetY_[staticIndex]
        end
    end

    self.name_    = decorationName
    self.zorder_  = checkint(self.zorder_)
    self.offsetX_ = checkint(self.offsetX_)
    self.offsetY_ = checkint(self.offsetY_)
    self.delay_   = checknumber(self.delay_)
    self.actions_ = {}

    self.scale_    = checknumber(self.scale_)
    if self.scale_ == 0 then
        self.scale_ = 1
    end

    if type(self.visible_) ~= "boolean" then
        self.visible_ = true
    end
end

function Decoration:release()
    if self.animation_ then
        self.animation_:release()
        self.animation_ = nil
    end
end

function Decoration:setDelay(delay)
    self.delay_ = delay
end

function Decoration:createView(batch)
    if self.framesName_ then
        self.frames_ = display.newFrames(self.framesName_, self.framesBegin_, self.framesLength_, self.framesReversed_)
        self.animation_ = display.newAnimation(self.frames_, self.framesTime_)
        self.animation_:retain()
        self.sprite_ = display.newSprite(self.frames_[1])
    else
        local imageName = self.imageName_
        if type(imageName) == "table" then
            imageName = imageName[1]
        end
        self.sprite_ = display.newSprite(imageName)
    end
    self.sprite_:setScale(self.scale_)

    if not self.visible_ then
        self.sprite_:setVisible(false)
    end

    batch:addChild(self.sprite_)

    if not self.autoplay_ then return end

    if self.playForever_ then
        self:playAnimationForever()
    else
        self:playAnimationOnce()
    end

    self.sprite_:addNodeEventListener(cc.NODE_EVENT, function(event)
        if event.name == "exit" then
            self:release()
        end
    end)
end

function Decoration:removeView()
    self:stopAnimation()
    self:release()
    if self.sprite_ then
        self.sprite_:removeSelf()
        self.sprite_ = nil
    end
end

function Decoration:getView()
    return self.sprite_
end

function Decoration:isVisible()
    return self.visible_
end

function Decoration:setVisible(visible)
    self.sprite_:setVisible(visible)
    self.visible_ = visible
end

function Decoration:playAnimationOnce(onComplete)
    self:stopAnimation()
    if self.removeAfterPlay_ then
        local userOnComplete = onComplete
        onComplete = function()
            if userOnComplete then userOnComplete() end
            self:removeView()
        end
    end
    local action = self.sprite_:playAnimationOnce(self.animation_, self.removeAfterPlay_, onComplete, self.delay_)
    self.actions_[#self.actions_ + 1] = action
end

function Decoration:playAnimationOnceAndRemove(onComplete)
    self:stopAnimation()
    local userOnComplete = onComplete
    onComplete = function()
        if userOnComplete then userOnComplete() end
        self:removeView()
    end
    local action = self.sprite_:playAnimationOnce(self.animation_, self.removeAfterPlay_, onComplete, self.delay_)
    self.actions_[#self.actions_ + 1] = action
end

function Decoration:playAnimationForever()
    self:stopAnimation()
    local action = self.sprite_:playAnimationForever(self.animation_, true, self.delay_)
    self.actions_[#self.actions_ + 1] = action
end

function Decoration:stopAnimation()
    for i, action in ipairs(self.actions_) do
        if not tolua.isnull(action) then transition.removeAction(action) end
    end
    self.actions_ = {}
end

function Decoration:fadeOutAndStopAnimation(time, onComplete)
    local action = transition.fadeOut(self.sprite_, {
        time = time,
        onComplete = function()
            if onComplete then onComplete() end
            self:stopAnimation()
        end
    })
    self.actions_[#self.actions_ + 1] = action
end

function Decoration:setDisplayFrameIndex(index)
    if self.frames_ then
        self.sprite_:setDisplayFrame(self.frames_[index])
    end
end

return Decoration
