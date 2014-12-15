
local TowerProperties = require("app.properties.TowerProperties")

local BehaviorBase = require("app.map.behaviors.BehaviorBase")
local TowerBehavior = class("TowerBehavior", BehaviorBase)

function TowerBehavior:ctor()
    local depends = {
        "DestroyedBehavior",
        "FireBehavior",
        "DecorateBehavior",
    }
    TowerBehavior.super.ctor(self, "TowerBehavior", depends, 100)
end

function TowerBehavior:bind(object)
    object.towerId_ = object.state_.towerId
    if type(object.towerId_) ~= "string" then object.towerId_ = "" end

    local function getTowerId(object)
        return object.towerId_
    end
    object:bindMethod(self, "getTowerId", getTowerId)

    local function setTowerId(object, towerId)
        object.towerId_ = towerId

        local define = TowerProperties.get(object.towerId_)
        if not define then
            object.towerId_ = object.defineId_ .. "L01"
            define = TowerProperties.get(object.towerId_)
        end
        if define then
            for k, v in pairs(define) do
                local kn = k .. "_"
                object[kn] = v
                object.state_[k] = v
            end
        end

        if object.staticIndex_ then
            local index = object.staticIndex_

            if type(object.state_.offsetX) == "table" then
                object.offsetX_ = object.state_.offsetX[index]
            end
            if type(object.state_.offsetY) == "table" then
                object.offsetY_ = object.state_.offsetY[index]
            end
            if type(object.state_.radiusOffsetX) == "table" then
                object.radiusOffsetX_ = object.state_.radiusOffsetX[index]
            end
            if type(object.state_.radiusOffsetY) == "table" then
                object.radiusOffsetY_ = object.state_.radiusOffsetY[index]
            end
            if type(object.state_.radius) == "table" then
                object.radius_ = object.state_.radius[index]
            end
            if type(object.state_.imageName)  == "table" then
                object.imageName_ = object.state_.imageName[index]
            end
            if type(object.state_.fireOffsetX) == "table" then
                object.fireOffsetX_ = object.state_.fireOffsetX[index]
            end
            if type(object.state_.fireOffsetY) == "table" then
                object.fireOffsetY_ = object.state_.fireOffsetY[index]
            end
        end
    end
    object:bindMethod(self, "setTowerId", setTowerId)

    local function showDestroyedStatus(object, skipAnim)
        object:getView():setVisible(false)
        object:getDecoration(object.defineId_ .. "Destroyed"):getView():setVisible(true)

        local decorationName = object:getDefineId() .. "Fire"
        if object:isDecorationExists(decorationName) then
            local decoration = object:getDecoration(decorationName)
            decoration:setVisible(false)
        end

        local decorationName = object:getDefineId() .. "Fire2"
        if object:isDecorationExists(decorationName) then
            local decoration = object:getDecoration(decorationName)
            decoration:setVisible(false)
        end
    end
    object:bindMethod(self, "showDestroyedStatus", showDestroyedStatus)

    local function hideDestroyedStatus(object, skipAnim)
        object:getView():setVisible(true)
        object:getDecoration(object.defineId_ .. "Destroyed"):getView():setVisible(false)
    end
    object:bindMethod(self, "hideDestroyedStatus", hideDestroyedStatus)

    local function vardump(object, state)
        state.towerId = object.towerId_
        return state
    end
    object:bindMethod(self, "vardump", vardump)
end

function TowerBehavior:unbind(object)
    object.towerId_ = nil

    object:unbindMethod(self, "getTowerId")
    object:unbindMethod(self, "setTowerId")
    object:unbindMethod(self, "showDestroyedStatus")
    object:unbindMethod(self, "hideDestroyedStatus")
    object:unbindMethod(self, "vardump")
end

function TowerBehavior:reset(object)
    object:setTowerId(object:getTowerId())
end

return TowerBehavior
