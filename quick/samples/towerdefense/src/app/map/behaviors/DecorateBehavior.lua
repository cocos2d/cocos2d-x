
local MapConstants = require("app.map.MapConstants")
local Decoration = require("app.map.Decoration")

local BehaviorBase = require("app.map.behaviors.BehaviorBase")
local DecorateBehavior = class("DecorateBehavior", BehaviorBase)

function DecorateBehavior:ctor()
    DecorateBehavior.super.ctor(self, "DecorateBehavior", nil, 1)
end

function DecorateBehavior:bind(object)
    object.decorations_ = {}
    for i,k in ipairs(checktable(object.state_.decorations)) do
        object.decorations_[k] = false
    end

    object.decorationsMore_ = {}
    for i,k in ipairs(checktable(object.state_.decorationsMore)) do
        object.decorationsMore_[k] = false
    end

    local function isDecorationExists(object, decorationName)
        return object.decorations_[decorationName] ~= nil
    end
    object:bindMethod(self, "isDecorationExists", isDecorationExists)

    local function getDecoration(object, decorationName)
        return object.decorations_[decorationName]
    end
    object:bindMethod(self, "getDecoration", getDecoration)

    local function updateView(object)
        local objectZOrder = object:getView():getLocalZOrder()
        local batch        = object.batch_
        local x, y         = object.x_, object.y_
        local flip         = object.flipSprite_

        local function updateView_(source)
            if not source then return end
            for decorationName, decoration in pairs(source) do
                if not decoration then
                    decoration = Decoration.new(decorationName, object.staticIndex_)
                    source[decorationName] = decoration
                    decoration:createView(batch)
                end

                local view = decoration:getView()
                batch:reorderChild(view, objectZOrder + decoration.zorder_)
                view:setPosition(x + decoration.offsetX_, y + decoration.offsetY_)
                view:setFlippedX(flip)
            end
        end

        updateView_(object.decorations_)
        updateView_(object.decorationsMore_)
    end
    object:bindMethod(self, "updateView", updateView)

    local function fastUpdateView_(source, x, y, objectZOrder, batch)
        if not source then return end

        for decorationName, decoration in pairs(source) do
            local view = decoration:getView()
            batch:reorderChild(view, objectZOrder + decoration.zorder_)
            view:setPosition(x + decoration.offsetX_, y + decoration.offsetY_)
            view:setFlippedX(flip)
        end
    end

    local function fastUpdateView(object)
        if not object.updated__ then return end

        local objectZOrder = object:getView():getLocalZOrder()
        local batch        = object.batch_
        local x, y         = object.x_, object.y_
        local flip         = object.flipSprite_

        fastUpdateView_(object.decorations_, x, y, objectZOrder, batch, flip)
        fastUpdateView_(object.decorationsMore_, x, y, objectZOrder, batch, flip)
    end
    object:bindMethod(self, "fastUpdateView", fastUpdateView)

    local function removeView(object)
        local function removeView_(source)
            if not source then return end
            for decorationName, decoration in pairs(source) do
                if decoration then decoration:removeView() end
                source[decorationName] = false
            end
        end
        removeView_(object.decorations_)
        removeView_(object.decorationsMore_)
    end
    object:bindMethod(self, "removeView", removeView)

    local function setVisible(object, visible)
        for decorationName, decoration in pairs(object.decorations_) do
            if decoration then
                local view = decoration:getView()
                view:setVisible(decoration.visible_ and visible)
            end
        end
    end
    object:bindMethod(self, "setVisible", setVisible)

    local function fadeTo(object, opacity, time)
        transition.fadeTo(object:getView(), {opacity = opacity, time = time})
        for decorationName, decoration in pairs(object.decorations_) do
            if decoration then
                local view = decoration:getView()
                if view:isVisible() then
                    transition.fadeTo(view, {opacity = opacity, time = time})
                end
            end
        end
    end
    object:bindMethod(self, "fadeTo", fadeTo)

    local function vardump(object, state)
        if object.decorationsMore_ then
            state.decorationsMore = table.keys(object.decorationsMore_)
        end
        return state
    end
    object:bindMethod(self, "vardump", vardump)
end

function DecorateBehavior:unbind(object)
    object.decorations_ = nil

    object:unbindMethod(self, "isDecorationExists")
    object:unbindMethod(self, "getDecoration")
    object:unbindMethod(self, "updateView")
    object:unbindMethod(self, "fastUpdateView")
    object:unbindMethod(self, "removeView")
    object:unbindMethod(self, "setVisible")
    object:unbindMethod(self, "fadeTo")
    object:unbindMethod(self, "vardump")
end

return DecorateBehavior
