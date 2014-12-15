
local MapConstants    = require("app.map.MapConstants")
local MapEvent        = require("app.map.MapEvent")
local MovableBehavior = require("app.map.behaviors.MovableBehavior")
local BulletBase      = require("app.map.bullets.BulletBase")

local MapEventHandler = class("MapEventHandler")

function MapEventHandler:ctor(runtime, map)
    self.runtime_        = runtime
    self.map_            = map
    self.objectsInRange_ = {}
end

-- 准备开始游戏
function MapEventHandler:preparePlay()
end

-- 开始游戏
function MapEventHandler:startPlay()
end

-- 停止游戏
function MapEventHandler:stopPlay()
end

-- 每秒执行一次 time() 方法
function MapEventHandler:time(time, dt)
    for range, objects in pairs(self.objectsInRange_) do
        for object, times in pairs(objects) do
            local holdTime = time - times[1]
            local holdTimeDt = holdTime - times[2]
            times[2] = holdTime
            self:objectInRange(object, range, holdTime, holdTimeDt)
            self.runtime_:dispatchEvent({
                name       = MapEvent.OBJECT_IN_RANGE,
                object     = object,
                range      = range,
                holdTime   = holdTime,
                holdTimeDt = holdTimeDt,
            })
        end
    end
end

-- 对象进入区域
function MapEventHandler:objectEnterRange(object, range)
    if not self.objectsInRange_[range] then
        self.objectsInRange_[range] = {}
    end
    self.objectsInRange_[range][object] = {self.runtime_.time_, 0}
end

-- 对象退出区域
function MapEventHandler:objectExitRange(object, range)
    if self.objectsInRange_[range] then
        self.objectsInRange_[range][object] = nil
    end
end

-- 对象保持在区域中
-- holdTime 是对象在区域中的持续时间
-- holdTimeDt 是距离上一次 objcetInRange 事件后，对象在区域中的时间
function MapEventHandler:objectInRange(object, range, holdTime, holdTimeDt)
end

-- 对象发生碰撞
function MapEventHandler:objectCollisionBegan(object1, object2)
end

-- 对象结束碰撞
function MapEventHandler:objectCollisionEnded(object1, object2)
end

-- 对目标开火
function MapEventHandler:fire(object, target)
    local bullets = object:fire(target)
    for i, bullet in ipairs(bullets) do
        self.map_:getBatchLayer():addChild(bullet:getView(), MapConstants.BULLET_ZORDER)
        self.runtime_:addBullet(bullet)
    end
end

-- 对象的开火范围内没有目标
function MapEventHandler:noTarget(object)
end

-- 击中目标
function MapEventHandler:hit(object, target, bullet, time)
    if target:isDestroyed() or self.runtime_.over_ then return end

    local damage = bullet.damage_
    local target = bullet.target_

    -- 扣除目标 HP
    target:decreaseHp(damage)
    if target:isDestroyed() then
        if target:hasBehavior("MovableBehavior") then
            target:stopMoving()
        end
        if target.showDestroyedStatus then
            target:showDestroyedStatus()
        end
        target:updateView()
        self:objectDestroyed(target)
    end
end

-- 没有命中目标
function MapEventHandler:miss(object, target, bullet)
end

-- 对象被摧毁
function MapEventHandler:objectDestroyed(object)
    self.runtime_:dispatchEvent({name = MapEvent.OBJECT_DESTROY, object = object})
    if object:hasBehavior("NPCBehavior") then
        self:showShipExplode(object)
    end
end

--[[--

显示舰船被摧毁的动画

]]
function MapEventHandler:showShipExplode(object)
    local runtime = self.runtime_
    local radius = object.radius_ * 100
    object:addCollisionLock()

    for i = 1, 12 do
        local decoration = runtime:newDecoration(string.format("ShipExplodeSmall%02d", math.random(1, 2)), object)
        decoration:setDelay(math.random(2, 5) / 100 * (i - 1))
        decoration:setVisible(true)
        decoration:playAnimationOnceAndRemove()
        local ox = math.random(-radius, radius) / 100
        local oy = math.random(-radius, radius) / 100 * 0.8
        local view = decoration:getView()
        local x, y = view:getPosition()
        view:setPosition(x + ox, y + oy)
    end

    local decoration = runtime:newDecoration("ShipExplode", object)
    decoration:setDelay(decoration.delay_)
    decoration:playAnimationOnceAndRemove()

    self.runtime_:removeObject(object, decoration.delay_)
end

return MapEventHandler
