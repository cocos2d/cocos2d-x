
local BehaviorFactory = require("app.map.behaviors.BehaviorFactory")

local ObjectBase = class("ObjectBase")

ObjectBase.CLASS_INDEX_PATH        = 1
ObjectBase.CLASS_INDEX_RANGE       = 2
ObjectBase.CLASS_INDEX_STATIC      = 3

ObjectBase.CLASS_INDEX = {
    path       = ObjectBase.CLASS_INDEX_PATH,
    range      = ObjectBase.CLASS_INDEX_RANGE,
    static     = ObjectBase.CLASS_INDEX_STATIC,
}

function ObjectBase:ctor(id, state, map)
    assert(type(state) == "table", "ObejctBase:ctor() - invalid state")

    for k, v in pairs(state) do
        local kn = k .. "_"
        self[kn] = v
    end

    local classId, index = unpack(string.split(id, ":"))
    self.map_        = map
    self.id_         = id
    self.classId_    = classId
    self.classIndex_ = ObjectBase.CLASS_INDEX[classId]
    self.index_      = checkint(index)
    self.x_          = checkint(self.x_)
    self.y_          = checkint(self.y_)
    self.offsetX_    = checkint(self.offsetX_)
    self.offsetY_    = checkint(self.offsetY_)
    self.state_      = state
    self.valid_      = false
    self.play_       = false
    self.tag_        = 0
    self.sprite_     = nil
    self.debug_      = false
    self.debugViewEnabled_ = false
    if type(self.viewZOrdered_) ~= "boolean" then
        self.viewZOrdered_ = true
    end
end

function ObjectBase:init()
    if not self.behaviors_ then return end

    local behaviors
    if type(self.behaviors_) == "string" then
        behaviors = string.split(self.behaviors_, ",")
    else
        behaviors = self.behaviors_
    end

    for i, behaviorName in ipairs(behaviors) do
        behaviorName = string.trim(behaviorName)
        if behaviorName ~= "" then self:bindBehavior(behaviorName) end
    end
end

function ObjectBase:isDebug()
    return self.debug_
end

function ObjectBase:setDebug(isDebugEnabled)
    self.debug_ = isDebugEnabled
end

function ObjectBase:isDebugViewEnabled()
    return self.debugViewEnabled_
end

function ObjectBase:setDebugViewEnabled(isDebugViewEnabled)
    self.debugViewEnabled_ = isDebugViewEnabled
end

function ObjectBase:getId()
    return self.id_
end

function ObjectBase:getClassId()
    return self.classId_
end

function ObjectBase:getIndex()
    return self.index_
end

function ObjectBase:validate()
end

function ObjectBase:isValid()
    return self.valid_
end

function ObjectBase:getTag()
    return self.tag_
end

function ObjectBase:setTag(tag)
    self.tag_ = tag
end

function ObjectBase:getPosition()
    return self.x_, self.y_
end

function ObjectBase:setPosition(x, y)
    self.x_, self.y_ = x, y
end

function ObjectBase:isViewCreated()
    return self.sprite_ ~= nil
end

function ObjectBase:isViewZOrdered()
    return self.viewZOrdered_
end

function ObjectBase:getView()
    return nil
end

function ObjectBase:createView(batch, marksLayer, debugLayer)
    assert(self.batch_ == nil, "ObjectBase:createView() - view already created")
    self.batch_      = batch
    self.marksLayer_ = marksLayer
    self.debugLayer_ = debugLayer
end

function ObjectBase:removeView()
    assert(self.batch_ ~= nil, "ObjectBase:removeView() - view not exists")
    self.batch_      = nil
    self.marksLayer_ = nil
    self.debugLayer_ = nil
end

function ObjectBase:updateView()
end

function ObjectBase:preparePlay()
end

function ObjectBase:startPlay()
    self.play_ = true
end

function ObjectBase:stopPlay()
    self.play_ = false
end

function ObjectBase:isPlay()
    return self.play_
end

function ObjectBase:hasBehavior(behaviorName)
    return self.behaviorObjects_ and self.behaviorObjects_[behaviorName] ~= nil
end

function ObjectBase:bindBehavior(behaviorName)
    if not self.behaviorObjects_ then self.behaviorObjects_ = {} end
    if self.behaviorObjects_[behaviorName] then return end

    local behavior = BehaviorFactory.createBehavior(behaviorName)
    for i, dependBehaviorName in pairs(behavior:getDepends()) do
        self:bindBehavior(dependBehaviorName)

        if not self.behaviorDepends_ then
            self.behaviorDepends_ = {}
        end
        if not self.behaviorDepends_[dependBehaviorName] then
            self.behaviorDepends_[dependBehaviorName] = {}
        end
        table.insert(self.behaviorDepends_[dependBehaviorName], behaviorName)
    end

    behavior:bind(self)
    self.behaviorObjects_[behaviorName] = behavior
    self:resetAllBehaviors()
end

function ObjectBase:unbindBehavior(behaviorName)
    assert(self.behaviorObjects_ and self.behaviorObjects_[behaviorName] ~= nil,
           string.format("ObjectBase:unbindBehavior() - behavior %s not binding", behaviorName))
    assert(not self.behaviorDepends_ or not self.behaviorDepends_[behaviorName],
           string.format("ObjectBase:unbindBehavior() - behavior %s depends by other binding", behaviorName))

    local behavior = self.behaviorObjects_[behaviorName]
    for i, dependBehaviorName in pairs(behavior:getDepends()) do
        for j, name in ipairs(self.behaviorDepends_[dependBehaviorName]) do
            if name == behaviorName then
                table.remove(self.behaviorDepends_[dependBehaviorName], j)
                if #self.behaviorDepends_[dependBehaviorName] < 1 then
                    self.behaviorDepends_[dependBehaviorName] = nil
                end
                break
            end
        end
    end

    behavior:unbind(self)
    self.behaviorObjects_[behaviorName] = nil
end

function ObjectBase:resetAllBehaviors()
    if not self.behaviorObjects_ then return end

    local behaviors = {}
    for i, behavior in pairs(self.behaviorObjects_) do
        behaviors[#behaviors + 1] = behavior
    end
    table.sort(behaviors, function(a, b)
        return a:getPriority() > b:getPriority()
    end)
    for i, behavior in ipairs(behaviors) do
        behavior:reset(self)
    end
end

function ObjectBase:bindMethod(behavior, methodName, method, callOriginMethodLast)
    local originMethod = self[methodName]
    if not originMethod then
        self[methodName] = method
        return
    end

    if not self.bindingMethods_ then self.bindingMethods_ = {} end
    if not self.bindingMethods_[methodName] then self.bindingMethods_[methodName] = {} end

    local chain = {behavior, originMethod}
    local newMethod
    if callOriginMethodLast then
        newMethod = function(...)
            method(...)
            chain[2](...)
        end
    else
        newMethod = function(...)
            local ret = chain[2](...)
            if ret then
                local args = {...}
                args[#args + 1] = ret
                return method(unpack(args))
            else
                return method(...)
            end
        end
    end

    self[methodName] = newMethod
    chain[3] = newMethod
    table.insert(self.bindingMethods_[methodName], chain)

    -- print(string.format("[%s]:bindMethod(%s, %s)", tostring(self), behavior:getName(), methodName))
    -- for i, chain in ipairs(self.bindingMethods_[methodName]) do
    --     print(string.format("  index: %d, origin: %s, new: %s", i, tostring(chain[2]), tostring(chain[3])))
    -- end
    -- print(string.format("  current: %s", tostring(self[methodName])))
end

function ObjectBase:unbindMethod(behavior, methodName)
    if not self.bindingMethods_ or not self.bindingMethods_[methodName] then
        self[methodName] = nil
        return
    end

    local methods = self.bindingMethods_[methodName]
    local count = #methods
    for i = count, 1, -1 do
        local chain = methods[i]

        if chain[1] == behavior then
            -- print(string.format("[%s]:unbindMethod(%s, %s)", tostring(self), behavior:getName(), methodName))
            if i < count then
                -- 如果移除了中间的节点，则将后一个节点的 origin 指向前一个节点的 origin
                -- 并且对象的方法引用的函数不变
                -- print(string.format("  remove method from index %d", i))
                methods[i + 1][2] = chain[2]
            elseif count > 1 then
                -- 如果移除尾部的节点，则对象的方法引用的函数指向前一个节点的 new
                self[methodName] = methods[i - 1][3]
            elseif count == 1 then
                -- 如果移除了最后一个节点，则将对象的方法指向节点的 origin
                self[methodName] = chain[2]
                self.bindingMethods_[methodName] = nil
            end

            -- 移除节点
            table.remove(methods, i)

            -- if self.bindingMethods_[methodName] then
            --     for i, chain in ipairs(self.bindingMethods_[methodName]) do
            --         print(string.format("  index: %d, origin: %s, new: %s", i, tostring(chain[2]), tostring(chain[3])))
            --     end
            -- end
            -- print(string.format("  current: %s", tostring(self[methodName])))

            break
        end
    end
end

function ObjectBase:vardump()
    local state = {
        x   = self.x_,
        y   = self.y_,
        tag = self.tag_,
    }

    if self.behaviorObjects_ then
        local behaviors = table.keys(self.behaviorObjects_)
        for i = #behaviors, 1, -1 do
            if not BehaviorFactory.isStaticObjectBehavior(behaviors[i]) then
                table.remove(behaviors, i)
            end
        end
        if #behaviors > 0 then
            table.sort(behaviors)
            state.behaviors = behaviors
        end
    end

    return state
end

function ObjectBase:dump(label)
    return dump(self:vardump(), label)
end

return ObjectBase
