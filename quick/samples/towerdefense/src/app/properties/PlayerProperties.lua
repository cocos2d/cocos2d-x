
local BulletType = require("app.map.BulletType")

local PlayerProperties = {}

local defines = {}

local player = {
    maxHp             = 1500,  -- 最大 HP
    maxArmor          = 40,   -- 最大装甲
    speed             = 200,  -- 速度
    maxMagic          = 200,  -- 最大 MP
    minDamage         = 420,  -- 火炮的最小伤害
    maxDamage         = 480,  -- 火炮的最大伤害
    cooldown          = 3.0,  -- 火炮冷却时间
    critical          = 10,   -- 暴击率
    hitrate           = 70,   -- 命中率
    heavyArmorDamage  = 125,  -- 对重甲炮台的伤害（100%）
    lightArmorDamage  = 100,  -- 对轻甲炮台的伤害（100%）
    magicShieldDamage = 80,   -- 对魔法炮台的伤害（100%）
    criticalPower     = 1.5,  -- 暴击伤害的威力 150%
    fireRange         = 130,  -- 射程
    bulletType        = BulletType.RED_CANNON,
    genius            = {A01 = 4, A02 = 4, A03 = 4},
    godSkills         = {GS01 = 1, GS02 = 1, GS03 = 1, GS04 = 1, GS05 = 1},
}
defines["Player001"] = player

------------------

local player = {
    maxHp             = 2500,  -- 最大 HP
    maxArmor          = 60,   -- 最大装甲
    speed             = 220,  -- 速度
    maxMagic          = 400,  -- 最大 MP
    minDamage         = 700,  -- 火炮的最小伤害
    maxDamage         = 900,  -- 火炮的最大伤害
    cooldown          = 2.9,  -- 火炮冷却时间
    critical          = 11,   -- 暴击率
    hitrate           = 69,   -- 命中率
    heavyArmorDamage  = 125,  -- 对重甲炮台的伤害（100%）
    lightArmorDamage  = 100,  -- 对轻甲炮台的伤害（100%）
    magicShieldDamage = 80,   -- 对魔法炮台的伤害（100%）
    criticalPower     = 1.5,  -- 暴击伤害的威力 150%
    fireRange         = 130,  -- 射程
    bulletType        = BulletType.RED_CANNON,
    genius            = {A04 = 5, A05 = 5, A06 = 5, A07 = 5},
    godSkills         = {GS01 = 2, GS02 = 2, GS03 = 2, GS04 = 2, GS05 = 2},
}
defines["Player002"] = player

--------------------

local player = {
    maxHp             = 4000,  -- 最大 HP
    maxArmor          = 100,   -- 最大装甲
    speed             = 240,  -- 速度
    maxMagic          = 600,  -- 最大 MP
    minDamage         = 800,  -- 火炮的最小伤害
    maxDamage         = 1000,  -- 火炮的最大伤害
    cooldown          = 2.5,  -- 火炮冷却时间
    critical          = 12,   -- 暴击率
    hitrate           = 68,   -- 命中率
    heavyArmorDamage  = 125,  -- 对重甲炮台的伤害（100%）
    lightArmorDamage  = 100,  -- 对轻甲炮台的伤害（100%）
    magicShieldDamage = 80,   -- 对魔法炮台的伤害（100%）
    criticalPower     = 1.5,  -- 暴击伤害的威力 150%
    fireRange         = 220,  -- 射程
    bulletType        = BulletType.RED_CANNON,
    genius            = {A08 = 6, A09 = 6, A10 = 6, A11 = 6, A12 = 6},
    godSkills         = {GS01 = 3, GS02 = 3, GS03 = 3, GS04 = 3, GS05 = 3},
}
defines["Player003"] = player

--------------------

local player = {
    maxHp             = 6000,  -- 最大 HP
    maxArmor          = 200,   -- 最大装甲
    speed             = 260,  -- 速度
    maxMagic          = 800,  -- 最大 MP
    minDamage         = 1500,  -- 火炮的最小伤害
    maxDamage         = 1900,  -- 火炮的最大伤害
    cooldown          = 2.7,  -- 火炮冷却时间
    critical          = 13,   -- 暴击率
    hitrate           = 67,   -- 命中率
    heavyArmorDamage  = 125,  -- 对重甲炮台的伤害（100%）
    lightArmorDamage  = 100,  -- 对轻甲炮台的伤害（100%）
    magicShieldDamage = 80,  -- 对魔法炮台的伤害（100%）
    criticalPower     = 1.5,  -- 暴击伤害的威力 150%
    fireRange         = 130,  -- 射程
    bulletType        = BulletType.RED_CANNON,
    genius            = {A08 = 6, A09 = 6, A10 = 6, A11 = 6, A12 = 6},
    godSkills         = {GS01 = 4, GS02 = 4, GS03 = 4, GS04 = 4, GS05 = 4},
}
defines["Player004"] = player

--------------------

local player = {
    maxHp             = 8500,  -- 最大 HP
    maxArmor          = 300,   -- 最大装甲
    speed             = 280,  -- 速度
    maxMagic          = 1000,  -- 最大 MP
    minDamage         = 2200,  -- 火炮的最小伤害
    maxDamage         = 2600,  -- 火炮的最大伤害
    cooldown          = 2.6,  -- 火炮冷却时间
    critical          = 14,   -- 暴击率
    hitrate           = 66,   -- 命中率
    heavyArmorDamage  = 125,  -- 对重甲炮台的伤害（100%）
    lightArmorDamage  = 100,  -- 对轻甲炮台的伤害（100%）
    magicShieldDamage = 80,  -- 对魔法炮台的伤害（100%）
    criticalPower     = 1.5,  -- 暴击伤害的威力 150%
    fireRange         = 130,  -- 射程
    bulletType        = BulletType.RED_CANNON,
    genius            = {A12 = 7, A13 = 7, A14 = 7, A15 = 7, A16 = 7, A17 = 7},
    godSkills         = {GS01 = 5, GS02 = 5, GS03 = 5, GS04 = 5, GS05 = 5},
}
defines["Player005"] = player

--------------------

local player = {
    maxHp             = 11500,  -- 最大 HP
    maxArmor          = 400,   -- 最大装甲
    speed             = 300,  -- 速度
    maxMagic          = 1200,  -- 最大 MP
    minDamage         = 2800,  -- 火炮的最小伤害
    maxDamage         = 3400,  -- 火炮的最大伤害
    cooldown          = 2.5,  -- 火炮冷却时间
    critical          = 15,   -- 暴击率
    hitrate           = 65,   -- 命中率
    heavyArmorDamage  = 125,  -- 对重甲炮台的伤害（100%）
    lightArmorDamage  = 100,  -- 对轻甲炮台的伤害（100%）
    magicShieldDamage = 80,  -- 对魔法炮台的伤害（100%）
    criticalPower     = 1.5,  -- 暴击伤害的威力 150%
    fireRange         = 130,  -- 射程
    bulletType        = BulletType.RED_CANNON,
    genius            = {A12 = 7, A13 = 7, A14 = 7, A15 = 7, A16 = 7, A17 = 7},
    godSkills         = {GS01 = 6, GS02 = 6, GS03 = 6, GS04 = 6, GS05 = 6},
}
defines["Player006"] = player

--------------------

local player = {
    maxHp             = 15000,  -- 最大 HP
    maxArmor          = 520,   -- 最大装甲
    speed             = 320,  -- 速度
    maxMagic          = 1400,  -- 最大 MP
    minDamage         = 3400,  -- 火炮的最小伤害
    maxDamage         = 4000,  -- 火炮的最大伤害
    cooldown          = 2.4,  -- 火炮冷却时间
    critical          = 16,   -- 暴击率
    hitrate           = 64,   -- 命中率
    heavyArmorDamage  = 125,  -- 对重甲炮台的伤害（100%）
    lightArmorDamage  = 100,  -- 对轻甲炮台的伤害（100%）
    magicShieldDamage = 80,  -- 对魔法炮台的伤害（100%）
    criticalPower     = 1.5,  -- 暴击伤害的威力 150%
    fireRange         = 130,  -- 射程
    bulletType        = BulletType.RED_CANNON,
    genius            = {A12 = 7, A13 = 7, A14 = 7, A15 = 7, A16 = 7, A17 = 7},
    godSkills         = {GS01 = 7, GS02 = 7, GS03 = 7, GS04 = 7, GS05 = 7},
}
defines["Player007"] = player

--------------------

local player = {
    maxHp             = 19000,  -- 最大 HP
    maxArmor          = 660,   -- 最大装甲
    speed             = 340,  -- 速度
    maxMagic          = 1600,  -- 最大 MP
    minDamage         = 4020,  -- 火炮的最小伤害
    maxDamage         = 4820,  -- 火炮的最大伤害
    cooldown          = 2.3,  -- 火炮冷却时间
    critical          = 17,   -- 暴击率
    hitrate           = 63,   -- 命中率
    heavyArmorDamage  = 125,  -- 对重甲炮台的伤害（100%）
    lightArmorDamage  = 100,  -- 对轻甲炮台的伤害（100%）
    magicShieldDamage = 80,  -- 对魔法炮台的伤害（100%）
    criticalPower     = 1.5,  -- 暴击伤害的威力 150%
    fireRange         = 130,  -- 射程
    bulletType        = BulletType.RED_CANNON,
    genius            = {A18 = 8, A19 = 8, A20 = 8, A01 = 8, A02 = 8, A03 = 8, A04 = 8},
    godSkills         = {GS01 = 8, GS02 = 8, GS03 = 8, GS04 = 8, GS05 = 8},
}
defines["Player008"] = player

--------------------

local player = {
    maxHp             = 23500,  -- 最大 HP
    maxArmor          = 820,   -- 最大装甲
    speed             = 360,  -- 速度
    maxMagic          = 1800,  -- 最大 MP
    minDamage         = 4680,  -- 火炮的最小伤害
    maxDamage         = 5480,  -- 火炮的最大伤害
    cooldown          = 2.2,  -- 火炮冷却时间
    critical          = 18,   -- 暴击率
    hitrate           = 62,   -- 命中率
    heavyArmorDamage  = 125,  -- 对重甲炮台的伤害（100%）
    lightArmorDamage  = 100,  -- 对轻甲炮台的伤害（100%）
    magicShieldDamage = 80,  -- 对魔法炮台的伤害（100%）
    criticalPower     = 1.5,  -- 暴击伤害的威力 150%
    fireRange         = 130,  -- 射程
    bulletType        = BulletType.RED_CANNON,
    genius            = {A04 = 9, A05 = 9, A06 = 9, A08 = 9, A09 = 9, A10 = 9, A12 = 9, A13 = 9},
    godSkills         = {GS01 = 9, GS02 = 9, GS03 = 9, GS04 = 9, GS05 = 9},
}
defines["Player009"] = player

--------------------

local player = {
    maxHp             = 29500,  -- 最大 HP
    maxArmor          = 1000,   -- 最大装甲
    speed             = 380,  -- 速度
    maxMagic          = 2000,  -- 最大 MP
    minDamage         = 5320,  -- 火炮的最小伤害
    maxDamage         = 6120,  -- 火炮的最大伤害
    cooldown          = 2.1,  -- 火炮冷却时间
    critical          = 19,   -- 暴击率
    hitrate           = 61,   -- 命中率
    heavyArmorDamage  = 125,  -- 对重甲炮台的伤害（100%）
    lightArmorDamage  = 100,  -- 对轻甲炮台的伤害（100%）
    magicShieldDamage = 80,  -- 对魔法炮台的伤害（100%）
    criticalPower     = 1.5,  -- 暴击伤害的威力 150%
    fireRange         = 130,  -- 射程
    bulletType        = BulletType.RED_CANNON,
    genius            = {A14 = 10, A11 = 10, A13 = 10, A18 = 10, A09 = 10, A15 = 10, A17 = 10, A10 = 10, A20 = 10},
    godSkills         = {GS01 = 10, GS02 = 10, GS03 = 10, GS04 = 10, GS05 = 10},
}
defines["Player010"] = player

--------------------

function PlayerProperties.get(id)
    return clone(defines[id])
end

return PlayerProperties
