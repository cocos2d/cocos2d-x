
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
