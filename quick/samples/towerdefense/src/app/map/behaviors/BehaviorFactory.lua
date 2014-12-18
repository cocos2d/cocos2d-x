
local behaviorsClass = {
    CollisionBehavior          = require("app.map.behaviors.CollisionBehavior"),
    CampBehavior               = require("app.map.behaviors.CampBehavior"),
    DecorateBehavior           = require("app.map.behaviors.DecorateBehavior"),
    BuildingBehavior           = require("app.map.behaviors.BuildingBehavior"),
    FireBehavior               = require("app.map.behaviors.FireBehavior"),
    MovableBehavior            = require("app.map.behaviors.MovableBehavior"),
    DestroyedBehavior          = require("app.map.behaviors.DestroyedBehavior"),
    TowerBehavior              = require("app.map.behaviors.TowerBehavior"),
    NPCBehavior                = require("app.map.behaviors.NPCBehavior"),

    PathEditorBehavior         = require("app.map.behaviors.PathEditorBehavior"),
    RangeEditorBehavior        = require("app.map.behaviors.RangeEditorBehavior"),
    StaticObjectEditorBehavior = require("app.map.behaviors.StaticObjectEditorBehavior"),
}

local BehaviorFactory = {}

function BehaviorFactory.createBehavior(behaviorName)
    local class = behaviorsClass[behaviorName]
    assert(class ~= nil, string.format("BehaviorFactory.createBehavior() - Invalid behavior name \"%s\"", tostring(behaviorName)))
    return class.new()
end

local allStaticObjectBehaviors = {
    BuildingBehavior  = true,
    CampBehavior      = true,
    CollisionBehavior = true,
    DecorateBehavior  = true,
    DestroyedBehavior = true,
    FireBehavior      = true,
    MovableBehavior   = true,
    NPCBehavior       = true,
    TowerBehavior     = true,
}

function BehaviorFactory.getAllStaticObjectBehaviorsName()
    return table.keys(allStaticObjectBehaviors)
end

function BehaviorFactory.isStaticObjectBehavior(behaviorName)
    return allStaticObjectBehaviors[behaviorName]
end

return BehaviorFactory
