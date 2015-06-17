local TMoveBy = class("TMoveBy")
TMoveBy._tag = -1
TMoveBy._duration = 0
TMoveBy._x  = 0
TMoveBy._y  = 0
TMoveBy._reverse = false
function TMoveBy:ctor()
    self._tag = -1
    self._duration = 0.0
    self._x  = 0
    self._y  = 0
    self._reverse = false
end

function TMoveBy:init()
    return true
end

function TMoveBy:done()
    local node = ccs.SceneReader:getInstance():getNodeByTag(self._tag)
    if nil == node then
        return
    end
    local  actionBy = cc.MoveBy:create(self._duration, cc.p(self._x, self._y))
    if nil == actionBy then
        return
    end

    if true == self._reverse then
        local actionByBack = actionBy:reverse()
        node:runAction(cc.Sequence:create(actionBy, actionByBack))
    else
        node:runAction(actionBy)
    end
end

function TMoveBy:serialize(value)
    local dataItems = value["dataitems"]
    if nil ~= dataItems then
        local count = table.getn(dataItems)
        for i = 1, count do
            local subDict =  dataItems[i]
            local key = subDict["key"]
            if key == "Tag" then
                self._tag = subDict["value"]
            elseif key == "Duration" then
                self._duration = subDict["value"]
            elseif key == "x" then
                self._x = subDict["value"]
            elseif key == "y" then
                self._y = subDict["value"]
            elseif key == "IsReverse" then
                self._reverse = subDict["value"]
            end
        end
    end
end

function TMoveBy:removeAll()
    local node = ccs.SceneReader:getInstance():getNodeByTag(self._tag)
    node:getActionManager():removeAllActions()
    print("TMoveBy::removeAll")
end

local TScaleTo = class("TScaleTo")
TScaleTo._tag  = -1
TScaleTo._duration = 0
TScaleTo._scaleX = 0
TScaleTo._scaleY = 0

function TScaleTo:ctor()
    self._tag = -1
    self._duration = 0
    self._scaleX = 0
    self._scaleY = 0
end

function TScaleTo:init()
    return true
end

function TScaleTo:done()
    local node = ccs.SceneReader:getInstance():getNodeByTag(self._tag)
    if nil == node then
        return
    end

    local actionTo = cc.ScaleTo:create(self._duration, self._scaleX, self._scaleY)
    if nil == actionTo then
        return
    end

    node:runAction(actionTo)
end

function TScaleTo:serialize(value)
    local dataItems = value["dataitems"]
    if nil ~= dataItems then
        local count = table.getn(dataItems)
        for i = 1, count do
            local subDict =  dataItems[i]
            local key = subDict["key"]
            if key == "Tag" then
                self._tag = subDict["value"]
            elseif key == "Duration" then
                self._duration = subDict["value"]
            elseif key == "ScaleX" then
                self._scaleX = subDict["value"]
            elseif key == "ScaleY" then
                self._scaleY = subDict["value"]
            end
        end
    end
end

function TScaleTo:removeAll()
    print("TScaleTo::removeAll")
end


local TriggerState = class("TriggerState")
TriggerState._id  = -1
TriggerState._state = 0

function TriggerState:ctor()
    self._id    = -1
    self._state = 0
end

function TriggerState:init()
    return true
end

function TriggerState:done()
    local obj = ccs.TriggerMng.getInstance():getTriggerObj(self._id)
    if nil ~= obj then
        if self._state == 0 then
            obj:setEnable(false)
        elseif self._state == 1 then
            obj:setEnable(true)
        elseif self._state == 2 then
            ccs.TriggerMng.getInstance():removeTriggerObj(self._id)
        end
    end
end

function TriggerState:serialize(value)
    local dataItems = value["dataitems"]
    if nil ~= dataItems then
        local count = table.getn(dataItems)
        for i = 1, count do
            local subDict =  dataItems[i]
            local key = subDict["key"]
            if key == "ID" then
                self._id = subDict["value"]
            elseif key == "State" then
                self._state = subDict["value"]
            end
        end
    end
end

function TriggerState:removeAll()
    print("TriggerState::removeAll")
end


ccs.registerTriggerClass("TScaleTo",TScaleTo.new)
ccs.registerTriggerClass("TMoveBy",TMoveBy.new)
ccs.registerTriggerClass("TriggerState",TriggerState.new)
