
local StaticObjectsDecorationProperties = {}

local defines = {}

---------------------------------------- 舰船

local decoration = {
    framesName      = "ShipWaveUpA%04d.png",
    framesBegin     = 1,            -- 从 ShipWaveUp0001.png 开始
    framesLength    = 16,           -- 一共有 16 帧
    framesTime      = 1.0 / 20,     -- 播放速度为每秒 20 帧

    -- 以下为都为可选设定
    zorder          = 1,            -- 在被装饰对象的 ZOrder 基础上 +1，默认值为 0
    playForever     = true,         -- 是否循环播放，默认值为 false
    autoplay        = true,         -- 是否自动开始播放，默认值为 false
    removeAfterPlay = false,        -- 播放一次后自动删除，仅当 playForever = false 时有效，默认值为 false
    hideAfterPlay   = false,        -- 播放一次后隐藏，仅当 playForever = false 时有效，默认值为 false
    visible         = true,         -- 是否默认可见，默认值为 true
    offsetX         = 0,            -- 图像的横向偏移量，默认值为 0
    offsetY         = -4,           -- 图像的纵向偏移量，默认值为 0
}
defines["ShipWavesUp"] = decoration

local decoration = {
    framesName   = "ShipWaveA%04d.png",
    framesBegin  = 1,
    framesLength = 16,
    framesTime   = 1.0 / 20,
    zorder       = -2,
    playForever  = true,
    autoplay     = true,
    offsetX      = 0,
    offsetY      = -4,
}
defines["ShipWaves"] = decoration

local decoration = {
    framesName      = "ShipExplode%04d.png",
    framesBegin     = 1,
    framesLength    = 12,
    framesTime      = 0.6 / 12,
    offsetX         = 14,
    offsetY         = 24,
    scale           = 2,
    zorder          = 5,
    delay           = 0.4,
    removeAfterPlay = true,
}
defines["ShipExplode"] = decoration

local decoration = {
    framesName      = "ShipExplodeSmall01%04d.png",
    framesBegin     = 1,
    framesLength    = 8,
    framesTime      = 0.35 / 8,
    offsetX         = 0,
    offsetY         = 24,
    zorder          = 6,
    scale           = 2,
    removeAfterPlay = true,
}
defines["ShipExplodeSmall01"] = decoration

local decoration = {
    framesName      = "ShipExplodeSmall02%04d.png",
    framesBegin     = 1,
    framesLength    = 6,
    framesTime      = 0.25 / 6,
    offsetX         = -6,
    offsetY         = 30,
    zorder          = 6,
    scale           = 1,
    removeAfterPlay = true,
}
defines["ShipExplodeSmall02"] = decoration

---------------------------------------- 建筑物

local decoration = {
    framesName      = "BuildingExplode%04d.png",
    framesBegin     = 1,
    framesLength    = 22,
    framesTime      = 1.1 / 22,
    zorder          = 1,
    removeAfterPlay = true,
}
defines["TowerExplode"] = decoration

local decoration = {
    imageName = {"#PlayerTower0101Destroyed.png", "#PlayerTower0102Destroyed.png"},
    offsetX   = {-13, -14, -14},
    offsetY   = {5, 5, 5},
    visible   = false,
}
defines["PlayerTower01Destroyed"] = decoration

local decoration = {
    imageName = {"#PlayerTower0201Destroyed.png", "#PlayerTower0202Destroyed.png"},
    offsetX   = {-24, -24, -24},
    offsetY   = {10, 13, 12},
    visible   = false,
}
defines["PlayerTower02Destroyed"] = decoration

local decoration = {
    framesName   = "PlayerTower02Fire%04d.png",
    framesBegin  = 1,
    framesLength = 8,
    framesTime   = 0.48 / 8,
    zorder       = 1,
    offsetY      = 36,
}
defines["PlayerTower02Fire"] = decoration

local decoration = {
    framesName      = "BuildingExplode%04d.png",
    framesBegin     = 1,
    framesLength    = 22,
    framesTime      = 1.3 / 22,
    zorder          = 1,
    scale           = 1.8,
    offsetY         = 30,
    removeAfterPlay = true,
}
defines["BuildingExplode"] = decoration


function StaticObjectsDecorationProperties.get(decorationName)
    return clone(defines[decorationName])
end

return StaticObjectsDecorationProperties
