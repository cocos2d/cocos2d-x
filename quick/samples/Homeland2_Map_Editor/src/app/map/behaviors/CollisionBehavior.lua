
local BehaviorBase = require("app.map.behaviors.BehaviorBase")

local CollisionBehavior = class("CollisionBehavior", BehaviorBase)

function CollisionBehavior:ctor()
    CollisionBehavior.super.ctor(self, "CollisionBehavior", nil, 1)
end

function CollisionBehavior:bind(object)
    object.collisionLock_ = 0
    object.collisionEnabled_ = object.state_.collisionEnabled
    if type(object.collisionEnabled_) ~= "boolean" then
        object.collisionEnabled_ = true
    end

    local function isCollisionEnabled(object)
        return object.collisionEnabled_
    end
    object:bindMethod(self, "isCollisionEnabled", isCollisionEnabled)

    local function setCollisionEnabled(object, enabled)
        object.collisionEnabled_ = enabled
    end
    object:bindMethod(self, "setCollisionEnabled", setCollisionEnabled)

    local function addCollisionLock(object)
        object.collisionLock_ = object.collisionLock_ + 1
    end
    object:bindMethod(self, "addCollisionLock", addCollisionLock)

    local function removeCollisionLock(object)
        object.collisionLock_ = object.collisionLock_ - 1
        assert(object.collisionLock_ >= 0,
               "CollisionBehavior.removeCollisionLock() - object.collisionLock_ must >= 0")
    end
    object:bindMethod(self, "removeCollisionLock", removeCollisionLock)

    local function vardump(object, state)
        state.collisionEnabled = object.collisionEnabled_
        return state
    end
    object:bindMethod(self, "vardump", vardump)
end

function CollisionBehavior:unbind(object)
    object.collisionEnabled_ = nil
    object:unbindMethod(self, "isCollisionEnabled")
    object:unbindMethod(self, "setCollisionEnabled")
    object:unbindMethod(self, "addCollisionLock")
    object:unbindMethod(self, "removeCollisionLock")
    object:unbindMethod(self, "vardump")
end

return CollisionBehavior
