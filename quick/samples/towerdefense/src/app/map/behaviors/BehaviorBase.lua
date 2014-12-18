
local BehaviorBase = class("BehaviorBase")

function BehaviorBase:ctor(behaviorName, depends, priority, conflictions)
    self.name_         = behaviorName
    self.depends_      = checktable(depends)
    self.priority_     = checkint(priority) -- 行为集合初始化时的优先级，越大越先初始化
    self.conflictions_ = checktable(conflictions)
end

function BehaviorBase:getName()
    return self.name_
end

function BehaviorBase:getDepends()
    return self.depends_
end

function BehaviorBase:getPriority()
    return self.priority_
end

function BehaviorBase:getConflictions()
    return self.conflictions_
end

function BehaviorBase:bind(object)
end

function BehaviorBase:unbind(object)
end

function BehaviorBase:reset(object)
end

return BehaviorBase
