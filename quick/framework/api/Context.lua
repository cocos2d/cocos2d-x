
--[[--

MODULE DOC

@see framework.EventProtocol

]]
local Context = class("Context")

PRINT_DEPRECATED("module api.Context is deprecated")

--[[--

]]
function Context:ctor()
    require(cc.PACKAGE_NAME .. ".api.EventProtocol").extend(self)
    self.config = {}
end

--[[--

Get value from context. if key not exists, return default value.

**Example:**

    local level = context:get("MIN_LEVEL", 1)


@param string key
@param mixed defaultValue

@return mixed

]]
function Context:get(key, defaultValue)
    if self.config[key] == nil then return defaultValue end
    return self.config[key]
end

--[[--

]]
function Context:set(key, value)
    self.config[key] = value
end

return Context
