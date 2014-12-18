
local MapConstants = require("app.map.MapConstants")

local BehaviorBase = require("app.map.behaviors.BehaviorBase")
local CampBehavior = class("CampBehavior", BehaviorBase)

function CampBehavior:ctor()
    CampBehavior.super.ctor(self, "CampBehavior", nil, 1)
end

function CampBehavior:bind(object)
    object.campId_ = checkint(object.state_.campId)
    if object.campId_ ~= MapConstants.ENEMY_CAMP and object.campId_ ~= MapConstants.PLAYER_CAMP then
        object.campId_ = MapConstants.ENEMY_CAMP
    end

    local function getCampId(object)
        return object.campId_
    end
    object:bindMethod(self, "getCampId", getCampId)

    local function vardump(object, state)
        state.campId = object.campId_
        return state
    end
    object:bindMethod(self, "vardump", vardump)
end

function CampBehavior:unbind(object)
    object.campId_ = nil
    object:unbindMethod(self, "getCampId")
    object:unbindMethod(self, "vardump")
end

return CampBehavior
