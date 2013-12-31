require "json"
require "luaScript/extern"
require "TriggerObj"

TriggerMng = class("TriggerMng")
TriggerMng._eventTriggers = nil
TriggerMng._triggerObjs = nil
TriggerMng._movementDispatches =  nil
TriggerMng._instance  = nil

function TriggerMng:ctor()
    self._triggerObjs = {}
    self._movementDispatches = {}
    self._eventTriggers = {}
end

function TriggerMng.getInstance()
    if TriggerMng._instance == nil then
        TriggerMng._instance = TriggerMng.new()
    end

    return TriggerMng._instance
end

function TriggerMng.destroyInstance()
    if TriggerMng._instance ~= nil then
        TriggerMng._instance:removeAll()
        TriggerMng._instance = nil
    end
end

function TriggerMng:triggerMngVersion()
    return "1.0.0.0"
end

function TriggerMng:parse(jsonStr)
    local parseTable = json.decode(jsonStr,1)
    if nil == parseTable then
        return
    end

    local count = table.getn(parseTable)
    for i = 1, count do
        local subDict = parseTable[i]
        local triggerObj = TriggerObj.new()
        triggerObj:serialize(subDict)
        local events = triggerObj:getEvents()
        for j = 1, table.getn(events) do
            local event = events[j]
            self:add(event, triggerObj)
        end

        self._triggerObjs[triggerObj:getId()] =  triggerObj
    end
end

function TriggerMng:get(event)
    return self._eventTriggers[event]
end

function TriggerMng:getTriggerObj(id)
    return self._triggerObjs[id]
end

function TriggerMng:add(event,triggerObj)
    local eventTriggers = self._eventTriggers[event]
    if nil == eventTriggers then
        eventTriggers = {}
    end

    local exist = false
    for i = 1, table.getn(eventTriggers) do
        if eventTriggers[i] == triggers then
            exist = true
            break
        end
    end

    if not exist then
        table.insert(eventTriggers,triggerObj)
        self._eventTriggers[event] = eventTriggers
    end
end

function TriggerMng:remvoeAll( )
    for k in pairs(self._eventTriggers) do
        local triObjArr = self._eventTriggers[k]
        for j = 1, table.getn(triObjArr) do
            local  obj = triObjArr[j]
            obj:remvoeAll()
        end
    end
    self._eventTriggers = {}
end

function TriggerMng:remove(event, obj)

    if nil ~= obj then
        return self:removeObjByEvent(event, obj)
    end

    assert(event >= 0,"event must be larger than 0")
    if nil == self._eventTriggers then
        return false
    end

    local triObjects =  self._eventTriggers[event]
    if nil == triObjects then
        return false
    end

    for i = 1, table.getn(triObjects) do
        local triObject = triggers[i]
        if nil ~= triObject then
            triObject:remvoeAll()
        end
    end

    self._eventTriggers[event] = nil
    return true
end

function TriggerMng:removeObjByEvent(event, obj)
    assert(event >= 0,"event must be larger than 0")
    if nil == self._eventTriggers then
        return false
    end

    local triObjects = self._eventTriggers[event]
    if nil == triObjects then
        return false
    end

    for i = 1,table.getn(triObjects) do
        local triObject = triObjects[i]
        if  nil ~= triObject and triObject == obj then
            triObject:remvoeAll()
            table.remove(triObjects, i)
            return true
        end
    end
end

function TriggerMng:removeTriggerObj(id)
    local obj = self.getTriggerObj(id)
    
    if nil == obj then
        return false
    end

    local events = obj:getEvents()
    for i = 1, table.getn(events) do
        self:remove(events[i],obj)
    end

    return true
end

function TriggerMng:isEmpty()
    return (not (nil == self._eventTriggers)) or table.getn(self._eventTriggers) <= 0
end
