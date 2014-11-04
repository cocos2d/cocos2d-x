local ModelBase = class("ModelBase")
ModelBase.idkey = "id"
ModelBase.schema = {
    id = {"string"}
}
ModelBase.fields = {"id"}

local function filterProperties(properties, filter)
    for i, field in ipairs(filter) do
        properties[field] = nil
    end
end

function ModelBase:ctor(properties)
    cc(self):addComponent("components.behavior.EventProtocol"):exportMethods()

    self.isModelBase_ = true
    if type(properties) ~= "table" then properties = {} end
    self:setProperties(properties)
end

function ModelBase:getId()
    local id = self[self.class.idkey .. "_"]
    assert(id ~= nil, string.format("%s:getId() - invalid id", self.class.__cname))
    return id
end

function ModelBase:isValidId()
    local propname = self.class.idkey .. "_"
    local id = self[propname]
    return type(id) == "string" and id ~= ""
end

function ModelBase:setProperties(properties)
    assert(type(properties) == "table", string.format("%s:setProperties() - invalid properties", self.class.__cname))

    for field, schema in pairs(self.class.schema) do
        local typ, def = schema[1], schema[2]
        local propname = field .. "_"

        local val = properties[field]
        if val ~= nil then
            if typ == "number" then val = tonumber(val) end
            assert(type(val) == typ, string.format("%s:setProperties() - type mismatch, %s expected %s, actual is %s", self.class.__cname, field, typ, type(val)))
            self[propname] = val
        elseif self[propname] == nil and def ~= nil then
            if type(def) == "table" then
                val = clone(def)
            elseif type(def) == "function" then
                val = def()
            else
                val = def
            end
            self[propname] = val
        end
    end

    return self
end

function ModelBase:getProperties(fields, filter)
    local schema = self.class.schema
    if type(fields) ~= "table" then fields = self.class.fields end

    local properties = {}
    for i, field in ipairs(fields) do
        local propname = field .. "_"
        local typ = schema[field][1]
        local val = self[propname]
        assert(type(val) == typ, string.format("%s:getProperties() - type mismatch, %s expected %s, actual is %s", self.class.__cname, field, typ, type(val)))
        properties[field] = val
    end

    if type(filter) == "table" then
        filterProperties(properties, filter)
    end

    return properties
end

return ModelBase
