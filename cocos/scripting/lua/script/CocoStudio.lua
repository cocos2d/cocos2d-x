require "json"
require "extern"

function sendTriggerEvent(event)
    local triggerObjArr = TriggerMng.getInstance():get(event)
    
    if nil == triggerObjArr then
        return
    end

    for i = 1, table.getn(triggerObjArr) do
        local triObj = triggerObjArr[i]
        if nil ~= triObj and triObj:detect() then
            triObj:done()
        end
    end
end

function registerTriggerClass(className, createFunc)
    TInfo.new(className,createFunc)
end

TInfo = class("TInfo")
TInfo._className = ""
TInfo._fun = nil

function TInfo:ctor(c,f)
     -- @param {String|ccs.TInfo}c
     -- @param {Function}f
    if nil ~= f then
        self._className = c
        self._fun       = f
    else
        self._className = c._className
        self._fun       = c._fun
    end

    ObjectFactory.getInstance():registerType(self)
end

ObjectFactory = class("ObjectFactory")
ObjectFactory._typeMap = nil
ObjectFactory._instance = nil

function ObjectFactory:ctor()
    self._typeMap = {}
end

function ObjectFactory.getInstance()
    if nil == ObjectFactory._instance then
        ObjectFactory._instance = ObjectFactory.new()
    end

    return ObjectFactory._instance
end

function ObjectFactory.destroyInstance()
    ObjectFactory._instance = nil
end

function ObjectFactory:createObject(classname)
    local obj = nil
    local t   = self._typeMap[classname]
    if nil ~= t then
        obj = t._fun()
    end

    return obj
end

function ObjectFactory:registerType(t)
    self._typeMap[t._className] = t
end

TriggerObj = class("TriggerObj")
TriggerObj._cons = {}
TriggerObj._acts = {}
TriggerObj._enable = false
TriggerObj._id   = 0
TriggerObj._vInt = {}

function TriggerObj.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TriggerObj)
    return target
end

function TriggerObj:ctor()
    self:init()
end

function TriggerObj:init()
    self._id = 0
    self._enable = true
    self._cons = {}
    self._acts = {}
    self._vInt = {}
end

function TriggerObj:detect()
    if (not self._enable) or (table.getn(self._cons) == 0) then
        return true
    end 

    local ret = true
    local obj = nil
    for i = 1 , table.getn(self._cons) do
        obj = self._cons[i]
        if nil ~= obj and nil ~= obj.detect then
            ret = ret and obj:detect()
        end
    end
    return ret
end

function TriggerObj:done()
    if (not self._enable) or (table.getn(self._acts) == 0) then
        return
    end

    local obj = nil
    for i = 1, table.getn(self._acts) do
        obj = self._acts[i]
        if nil ~= obj and obj.done then
            obj:done()
        end
    end
end

function TriggerObj:removeAll()
    local obj = nil
    for i=1, table.getn(self._cons) do
        obj = self._cons[i]
        if nil ~= obj then
            obj:removeAll()
        end
    end
    self._cons = {}

    for i=1, table.getn(self._acts) do
        obj = self._acts[i]
        if nil ~= obj then
            obj:removeAll()
        end
    end
    self._acts = {}
end

function TriggerObj:serialize(jsonValue)
    self._id = jsonValue["id"]
    local count = 0

    --condition
    local cons = jsonValue["conditions"]
    if nil ~= cons then
        count = table.getn(cons)
        for i = 1, count do
            local subDict = cons[i]
            local className = subDict["classname"]
            if nil ~= className then
                local obj = ObjectFactory.getInstance():createObject(className)
                assert(nil ~= obj, string.format("class named %s can not implement!",className))
                obj:serialize(subDict)
                obj:init()
                table.insert(self._cons, obj)
            end
        end
    end

    local actions =  jsonValue["actions"]
    if nil ~= actions then
        count = table.getn(actions)
        for i = 1,count do
            local  subAction = actions[i]
            local  className = subAction["classname"]
            if nil ~= className then
                local act = ObjectFactory.getInstance():createObject(className)
                assert(nil ~= act ,string.format("class named %s can not implement!",className))
                act:serialize(subAction)
                act:init()
                table.insert(self._acts,act)
            end
        end
    end

    local events = jsonValue["events"]
    if nil ~= events then
        count = table.getn(events)
        for i = 1, count do
            local subEveent = events[i]
            local eventID   = subEveent["id"]
            if eventID >= 0 then
                table.insert(self._vInt,eventID)
            end
        end
    end
end

function TriggerObj:getId()
    return self._id
end

function TriggerObj:setEnable(enable)
    self._enable = enable
end

function TriggerObj:getEvents()
    return self._vInt
end

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

function TriggerMng:removeAll( )
    for k in pairs(self._eventTriggers) do
        local triObjArr = self._eventTriggers[k]
        for j = 1, table.getn(triObjArr) do
            local  obj = triObjArr[j]
            obj:removeAll()
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
            triObject:removeAll()
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
            triObject:removeAll()
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
