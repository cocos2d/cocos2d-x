
local scheduler = require(cc.PACKAGE_NAME .. ".scheduler")

--[[--

“角色”类

level 是角色的等级，角色的攻击力、防御力、初始 Hp 都和 level 相关

]]

local Actor = class("Actor", cc.mvc.ModelBase)

-- 常量
Actor.FIRE_COOLDOWN = 0.2 -- 开火冷却时间

-- 定义事件
Actor.CHANGE_STATE_EVENT = "CHANGE_STATE_EVENT"
Actor.START_EVENT         = "START_EVENT"
Actor.READY_EVENT         = "READY_EVENT"
Actor.FIRE_EVENT          = "FIRE_EVENT"
Actor.FREEZE_EVENT        = "FREEZE_EVENT"
Actor.THAW_EVENT          = "THAW_EVENT"
Actor.KILL_EVENT          = "KILL_EVENT"
Actor.RELIVE_EVENT        = "RELIVE_EVENT"
Actor.HP_CHANGED_EVENT    = "HP_CHANGED_EVENT"
Actor.ATTACK_EVENT        = "ATTACK_EVENT"
Actor.UNDER_ATTACK_EVENT  = "UNDER_ATTACK_EVENT"

-- 定义属性
Actor.schema = clone(cc.mvc.ModelBase.schema)
Actor.schema["nickname"] = {"string"} -- 字符串类型，没有默认值
Actor.schema["level"]    = {"number", 1} -- 数值类型，默认值 1
Actor.schema["hp"]       = {"number", 1}

function Actor:ctor(properties, events, callbacks)
    Actor.super.ctor(self, properties)

    -- 因为角色存在不同状态，所以这里为 Actor 绑定了状态机组件
    self:addComponent("components.behavior.StateMachine")
    -- 由于状态机仅供内部使用，所以不应该调用组件的 exportMethods() 方法，改为用内部属性保存状态机组件对象
    self.fsm__ = self:getComponent("components.behavior.StateMachine")

    -- 设定状态机的默认事件
    local defaultEvents = {
        -- 初始化后，角色处于 idle 状态
        {name = "start",  from = "none",    to = "idle" },
        -- 开火
        {name = "fire",   from = "idle",    to = "firing"},
        -- 开火冷却结束
        {name = "ready",  from = "firing",  to = "idle"},
        -- 角色被冰冻
        {name = "freeze", from = "idle",    to = "frozen"},
        -- 从冰冻状态恢复
        {name = "thaw",   form = "frozen",  to = "idle"},
        -- 角色在正常状态和冰冻状态下都可能被杀死
        {name = "kill",   from = {"idle", "frozen"}, to = "dead"},
        -- 复活
        {name = "relive", from = "dead",    to = "idle"},
    }
    -- 如果继承类提供了其他事件，则合并
    table.insertto(defaultEvents, checktable(events))

    -- 设定状态机的默认回调
    local defaultCallbacks = {
        onchangestate = handler(self, self.onChangeState_),
        onstart       = handler(self, self.onStart_),
        onfire        = handler(self, self.onFire_),
        onready       = handler(self, self.onReady_),
        onfreeze      = handler(self, self.onFreeze_),
        onthaw        = handler(self, self.onThaw_),
        onkill        = handler(self, self.onKill_),
        onrelive      = handler(self, self.onRelive_),
        onleavefiring = handler(self, self.onLeaveFiring_),
    }
    -- 如果继承类提供了其他回调，则合并
    table.merge(defaultCallbacks, checktable(callbacks))

    self.fsm__:setupState({
        events = defaultEvents,
        callbacks = defaultCallbacks
    })

    self.fsm__:doEvent("start") -- 启动状态机
end

function Actor:getNickname()
    return self.nickname_
end

function Actor:getLevel()
    return self.level_
end

function Actor:getHp()
    return self.hp_
end

function Actor:getMaxHp()
    -- 简化算法：最大 Hp = 等级 x 100
    return self.level_ * 100
end

function Actor:getAttack()
    -- 简化算法：攻击力是等级 x 5
    return self.level_ * 5
end

function Actor:getArmor()
    -- 简化算法：防御是等级 x 2
    return self.level_ * 2
end

function Actor:getState()
    return self.fsm__:getState()
end

function Actor:canFire()
    return self.fsm__:canDoEvent("fire")
end

function Actor:isDead()
    return self.fsm__:getState() == "dead"
end

function Actor:isFrozen()
    return self.fsm__:getState() == "frozen"
end

function Actor:setFullHp()
    self.hp_ = self:getMaxHp()
    return sef
end

function Actor:increaseHp(hp)
    assert(not self:isDead(), string.format("actor %s:%s is dead, can't change Hp", self:getId(), self:getNickname()))
    assert(hp > 0, "Actor:increaseHp() - invalid hp")

    local newhp = self.hp_ + hp
    if newhp > self:getMaxHp() then
        newhp = self:getMaxHp()
    end

    if newhp > self.hp_ then
        self.hp_ = newhp
        self:dispatchEvent({name = Actor.HP_CHANGED_EVENT})
    end

    return self
end

function Actor:decreaseHp(hp)
    assert(not self:isDead(), string.format("actor %s:%s is dead, can't change Hp", self:getId(), self:getNickname()))
    assert(hp > 0, "Actor:increaseHp() - invalid hp")

    local newhp = self.hp_ - hp
    if newhp <= 0 then
        newhp = 0
    end

    if newhp < self.hp_ then
        self.hp_ = newhp
        self:dispatchEvent({name = Actor.HP_CHANGED_EVENT})
        if newhp == 0 then
            self.fsm__:doEvent("kill")
        end
    end

    return self
end

-- 开火
function Actor:fire()
    print("----------")
    self.fsm__:doEvent("fire")
    self.fsm__:doEvent("ready", Actor.FIRE_COOLDOWN)
end

-- 命中目标
function Actor:hit(enemy)
    assert(not self:isDead(), string.format("actor %s:%s is dead, can't change Hp", self:getId(), self:getNickname()))

    -- 简化算法：伤害 = 自己的攻击力 - 目标防御
    local damage = 0
    if math.random(1, 100) <= 80 then -- 命中率 80%
        local armor = 0
        if not enemy:isFrozen() then -- 如果目标被冰冻，则无视防御
            armor = enemy:getArmor()
        end
        damage = self:getAttack() - armor
        if damage <= 0 then damage = 1 end -- 只要命中，强制扣 HP
    end
    -- 触发事件，damage <= 0 可以视为 miss
    self:dispatchEvent({name = Actor.ATTACK_EVENT, enemy = enemy, damage = damage})
    if damage > 0 then
        -- 扣除目标 HP，并触发事件
        enemy:decreaseHp(damage) -- 扣除目标 Hp
        enemy:dispatchEvent({name = Actor.UNDER_ATTACK_EVENT, source = self, damage = damage})
    end

    return damage
end

---- state callbacks

function Actor:onChangeState_(event)
    printf("actor %s:%s state change from %s to %s", self:getId(), self.nickname_, event.from, event.to)
    event = {name = Actor.CHANGE_STATE_EVENT, from = event.from, to = event.to}
    self:dispatchEvent(event)
end

-- 启动状态机时，设定角色默认 Hp
function Actor:onStart_(event)
    printf("actor %s:%s start", self:getId(), self.nickname_)
    self:setFullHp()
    self:dispatchEvent({name = Actor.START_EVENT})
end

function Actor:onReady_(event)
    printf("actor %s:%s ready", self:getId(), self.nickname_)
    self:dispatchEvent({name = Actor.READY_EVENT})
end

function Actor:onFire_(event)
    printf("actor %s:%s fire", self:getId(), self.nickname_)
    self:dispatchEvent({name = Actor.FIRE_EVENT})
end

function Actor:onFreeze_(event)
    printf("actor %s:%s frozen", self:getId(), self.nickname_)
    self:dispatchEvent({name = Actor.FREEZE_EVENT})
end

function Actor:onThaw_(event)
    printf("actor %s:%s thawing", self:getId(), self.nickname_)
    self:dispatchEvent({name = Actor.THAW_EVENT})
end

function Actor:onKill_(event)
    printf("actor %s:%s dead", self:getId(), self.nickname_)
    self.hp_ = 0
    self:dispatchEvent({name = Actor.KILL_EVENT})
end

function Actor:onRelive_(event)
    printf("actor %s:%s relive", self:getId(), self.nickname_)
    self:setFullHp()
    self:dispatchEvent({name = Actor.RELIVE_EVENT})
end

function Actor:onLeaveFiring_(event)
    local cooldown = checknumber(event.args[1])
    if cooldown > 0 then
        -- 如果开火后的冷却时间大于 0，则需要等待
        scheduler.performWithDelayGlobal(function()
            event.transition()
        end, cooldown)
        return "async"
    end
end

return Actor
