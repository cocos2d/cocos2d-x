
local BuildingProperties = require("app.properties.BuildingProperties")

local BehaviorBase = require("app.map.behaviors.BehaviorBase")
local BuildingBehavior = class("BuildingBehavior", BehaviorBase)

function BuildingBehavior:ctor()
    local depends = {
        "DestroyedBehavior",
        "CollisionBehavior",
        "DecorateBehavior",
    }
    BuildingBehavior.super.ctor(self, "BuildingBehavior", depends, 100)
end

function BuildingBehavior:bind(object)
    object.buildingId_ = object.state_.buildingId
    if type(object.buildingId_) ~= "string" then object.buildingId_ = "" end

    local function getBuildingId(object)
        return object.buildingId_
    end
    object:bindMethod(self, "getBuildingId", getBuildingId)

    local function setBuildingId(object, buildingId)
        object.buildingId_ = buildingId

        local define = BuildingProperties.get(object.buildingId_)
        if not define then
            if object.campId_ == 1 then
                object.buildingId_ = "BuildingP001"
            else
                object.buildingId_ = "BuildingN001"
            end
            define = BuildingProperties.get(object.buildingId_)
        end
        for k, v in pairs(define) do
            local kn = k .. "_"
            object[kn] = v
            object.state_[k] = v
        end
    end
    object:bindMethod(self, "setBuildingId", setBuildingId)

    local function showDestroyedStatus(object, skipAnim)
        object:getView():setVisible(false)
        object:getDecoration(object.defineId_ .. "Destroyed"):getView():setVisible(true)
    end
    object:bindMethod(self, "showDestroyedStatus", showDestroyedStatus)

    local function vardump(object, state)
        state.buildingId = object.buildingId_
        return state
    end
    object:bindMethod(self, "vardump", vardump)
end

function BuildingBehavior:unbind(object)
    object.buildingId_ = nil

    object:unbindMethod(self, "getBuildingId")
    object:unbindMethod(self, "setBuildingId")
    object:unbindMethod(self, "showDestroyedStatus")
    object:unbindMethod(self, "vardump")
end

function BuildingBehavior:reset(object)
    object:setBuildingId(object:getBuildingId())
end

return BuildingBehavior
