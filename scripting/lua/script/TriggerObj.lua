require "luascript/CocoStudioTest/CocoStudioSceneTest/TriggerCode/acts"
require "luascript/CocoStudioTest/CocoStudioSceneTest/TriggerCode/cons"
require "luascript/CocoStudioTest/CocoStudioSceneTest/TriggerCode/eventDef"

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
        if nil ~= obj and obj.detect then
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
