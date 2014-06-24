
local Registry = import(".Registry")

local GameObject = {}

function GameObject.extend(target)
    target.components_ = {}

    function target:checkComponent(name)
        return self.components_[name] ~= nil
    end

    function target:addComponent(name)
        local component = Registry.newObject(name)
        self.components_[name] = component
        component:bind_(self)
        return component
    end

    function target:removeComponent(name)
        local component = self.components_[name]
        if component then component:unbind_() end
        self.components_[name] = nil
    end

    function target:getComponent(name)
        return self.components_[name]
    end

    return target
end

return GameObject
