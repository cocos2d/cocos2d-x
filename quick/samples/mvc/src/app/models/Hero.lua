
--[[--

“英雄”类

从“角色”类继承，增加了经验值等属性

]]

local Actor = import(".Actor")
local Hero = class("Hero", Actor)

Hero.EXP_CHANGED_EVENT = "EXP_CHANGED_EVENT"
Hero.LEVEL_UP_EVENT = "LEVEL_UP_EVENT"

Hero.schema = clone(Actor.schema)
Hero.schema["exp"] = {"number", 0}

-- 升到下一级需要的经验值
Hero.NEXT_LEVEL_EXP = 50

-- 增加经验值，并升级
function Hero:increaseEXP(exp)
    assert(not self:isDead(), string.format("hero %s:%s is dead, can't increase Exp", self:getId(), self:getNickname()))
    assert(exp > 0, "Hero:increaseEXP() - invalid exp")

    self.exp_ = self.exp_ + exp
    -- 简化的升级算法，每一个级别升级的经验值都是固定的
    while self.exp_ >= Hero.NEXT_LEVEL_EXP do
        self.level_ = self.level_ + 1
        self.exp_ = self.exp_ - Hero.NEXT_LEVEL_EXP
        self:setFullHp() -- 每次升级，HP 都完全恢复
        self:dispatchEvent({name = Hero.LEVEL_UP_EVENT})
    end
    self:dispatchEvent({name = Hero.EXP_CHANGED_EVENT})

    return self
end

function Hero:getExp()
    return self.exp_
end

function Hero:hit(target)
    -- 调用父类的 hit() 方法
    local damage = Hero.super.hit(self, target)
    if damage > 0 then
        -- 每次攻击成功，增加 10 点 EXP
        self:increaseEXP(10)
    end
    return damage
end

return Hero
