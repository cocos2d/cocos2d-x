require "CocoStudio"

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
    local node = SceneReader:sharedSceneReader():getNodeByTag(self._tag)
    if nil == node then
        return
    end

    local  actionBy = CCMoveBy:create(self._duration, ccp(self._x, self._y))
    if nil == actionBy then
        return
    end

    if false == self._reverse then
        local actionByBack = actionBy:reverse()
        local arr = CCArray:create()
        arr:addObject(actionBy)
        arr:addObject(actionByBack)
        node:runAction(CCSequence:create(arr))
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
    local node = SceneReader:sharedSceneReader():getNodeByTag(self._tag)
    if nil == node then
        return
    end

    local actionTo = CCScaleTo:create(self._duration, self._scaleX, self._scaleY)
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

registerTriggerClass("TScaleTo",TScaleTo.new)
registerTriggerClass("TMoveBy",TMoveBy.new)
