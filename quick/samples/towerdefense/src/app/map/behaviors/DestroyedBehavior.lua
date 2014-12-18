
local MapConstants = require("app.map.MapConstants")
local BehaviorBase = require("app.map.behaviors.BehaviorBase")

local DestroyedBehavior = class("DestroyedBehavior", BehaviorBase)

function DestroyedBehavior:ctor()
    DestroyedBehavior.super.ctor(self, "DestroyedBehavior", {"CampBehavior", "CollisionBehavior"}, 1)
end

function DestroyedBehavior:bind(object)
    local function isDestroyed(object)
        return object.destroyed_
    end
    object:bindMethod(self, "isDestroyed", isDestroyed)

    local function getMaxHp(object)
        return object.maxHp_
    end
    object:bindMethod(self, "getMaxHp", getMaxHp)

    local function setMaxHp(object, maxHp)
        maxHp = checkint(maxHp)
        assert(maxHp > 0, string.format("DestroyedBehavior.setMaxHp() - invalid maxHp %s", tostring(maxHp)))
        object.maxHp_ = maxHp
    end
    object:bindMethod(self, "setMaxHp", setMaxHp)

    local function getHp(object)
        return object.hp_
    end
    object:bindMethod(self, "getHp", getHp)

    local function setHp(object, hp)
        hp = checknumber(hp)
        assert(hp >= 0 and hp <= object.maxHp_,
               string.format("DestroyedBehavior.setHp() - invalid hp %s", tostring(hp)))
        object.hp_ = hp
        object.destroyed_ = object.hp_ <= 0
        object.hp__ = nil
    end
    object:bindMethod(self, "setHp", setHp)

    local function decreaseHp(object, amount)
        amount = checknumber(amount)
        assert(amount >= 0, string.format("DestroyedBehavior.decreaseHp() - invalid amount %s", tostring(amount)))
        object.hp_ = object.hp_ - amount
        if object.hp_ <= 0 then
            object.hp_ = 0
        end
        object.destroyed_ = object.hp_ <= 0
    end
    object:bindMethod(self, "decreaseHp", decreaseHp)

    local function increaseHp(object, amount)
        amount = checknumber(amount)
        assert(amount >= 0, string.format("DestroyedBehavior.increaseHp() - invalid amount %s", tostring(amount)))
        object.hp_ = object.hp_ + amount
        if object.hp_ >= object.maxHp_ then
            object.hp_ = object.maxHp_
        end
        object.destroyed_ = object.hp_ <= 0
    end
    object:bindMethod(self, "increaseHp", increaseHp)

    local function createView(object, batch, marksLayer, debugLayer)
        object.hpOutlineSprite_ = display.newSprite(string.format("#ObjectHpOutline.png"))
        batch:addChild(object.hpOutlineSprite_, MapConstants.HP_BAR_ZORDER)

        if object:getCampId() == MapConstants.PLAYER_CAMP then
            object.hpSprite_ = display.newSprite("#FriendlyHp.png")
        else
            object.hpSprite_ = display.newSprite("#EnemyHp.png")
        end
        object.hpSprite_:align(display.LEFT_CENTER, 0, 0)
        batch:addChild(object.hpSprite_, MapConstants.HP_BAR_ZORDER + 1)
    end
    object:bindMethod(self, "createView", createView)

    local function removeView(object)
        object.hpOutlineSprite_:removeSelf()
        object.hpOutlineSprite_ = nil
        object.hpSprite_:removeSelf()
        object.hpSprite_ = nil
    end
    object:bindMethod(self, "removeView", removeView, true)

    local function updateView(object)
        object.hp__ = object.hp_
        if object.hp_ > 0 then
            local x, y = object.x_, object.y_
            local radiusOffsetX, radiusOffsetY = object.radiusOffsetX_, object.radiusOffsetY_
            local x2 = x + radiusOffsetX - object.hpSprite_:getContentSize().width / 2
            local y2 = y + radiusOffsetY + object.radius_ + MapConstants.HP_BAR_OFFSET_Y
            object.hpSprite_:setPosition(x2, y2)
            object.hpSprite_:setScaleX(object.hp_ / object.maxHp_)
            object.hpSprite_:setVisible(true)
            object.hpOutlineSprite_:setPosition(x + radiusOffsetX, y2)
            object.hpOutlineSprite_:setVisible(true)
        else
            object.hpSprite_:setVisible(false)
            object.hpOutlineSprite_:setVisible(false)
        end
    end
    object:bindMethod(self, "updateView", updateView)

    local function fastUpdateView(object)
        if not object.updated__ and object.hp__ == object.hp_ then return end
        updateView(object)
    end
    object:bindMethod(self, "fastUpdateView", fastUpdateView)

    self:reset(object)
end

function DestroyedBehavior:unbind(object)
    object.hitOffsetX_ = nil
    object.hitOffsetY_ = nil
    object.maxHp_      = nil
    object.destroyed_  = nil
    object.hp_         = nil

    object:unbindMethod(self, "isDestroyed")
    object:unbindMethod(self, "setDestroyed")
    object:unbindMethod(self, "getMaxHp")
    object:unbindMethod(self, "setMaxHp")
    object:unbindMethod(self, "getHp")
    object:unbindMethod(self, "setHp")
    object:unbindMethod(self, "decreaseHp")
    object:unbindMethod(self, "increaseHp")
    object:unbindMethod(self, "createView")
    object:unbindMethod(self, "removeView")
    object:unbindMethod(self, "updateView")
    object:unbindMethod(self, "fastUpdateView")
end

function DestroyedBehavior:reset(object)
    object.hitOffsetX_ = checkint(object.state_.hitOffsetX)
    object.hitOffsetY_ = checkint(object.state_.hitOffsetY)
    object.maxHp_      = checkint(object.state_.maxHp)

    if object.maxHp_ < 1 then object.maxHp_ = 1 end
    object.hp_        = object.maxHp_
    object.destroyed_ = object.hp_ <= 0
    object.hp__       = nil
end

return DestroyedBehavior
