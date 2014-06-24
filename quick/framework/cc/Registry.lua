
local Registry = class("Registry")

Registry.classes_ = {}
Registry.objects_ = {}

function Registry.add(cls, name)
    assert(type(cls) == "table" and cls.__cname ~= nil, "Registry.add() - invalid class")
    if not name then name = cls.__cname end
    assert(Registry.classes_[name] == nil, string.format("Registry.add() - class \"%s\" already exists", tostring(name)))
    Registry.classes_[name] = cls
end

function Registry.remove(name)
    assert(Registry.classes_[name] ~= nil, string.format("Registry.remove() - class \"%s\" not found", name))
    Registry.classes_[name] = nil
end

function Registry.exists(name)
    return Registry.classes_[name] ~= nil
end

function Registry.newObject(name, ...)
    local cls = Registry.classes_[name]
    if not cls then
        -- auto load
        pcall(function()
            cls = require(name)
            Registry.add(cls, name)
        end)
    end
    assert(cls ~= nil, string.format("Registry.newObject() - invalid class \"%s\"", tostring(name)))
    return cls.new(...)
end

function Registry.setObject(object, name)
    assert(Registry.objects_[name] == nil, string.format("Registry.setObject() - object \"%s\" already exists", tostring(name)))
    assert(object ~= nil, "Registry.setObject() - object \"%s\" is nil", tostring(name))
    Registry.objects_[name] = object
end

function Registry.getObject(name)
    assert(Registry.objects_[name] ~= nil, string.format("Registry.getObject() - object \"%s\" not exists", tostring(name)))
    return Registry.objects_[name]
end

function Registry.removeObject(name)
    assert(Registry.objects_[name] ~= nil, string.format("Registry.removeObject() - object \"%s\" not exists", tostring(name)))
    Registry.objects_[name] = nil
end

function Registry.isObjectExists(name)
    return Registry.objects_[name] ~= nil
end

return Registry
