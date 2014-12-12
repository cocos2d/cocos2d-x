
local MapEvent        = require("app.map.MapEvent")
local MapEventHandler = require("app.map.MapEventHandler")

local MAX_ENEMY_COUNT = 30

local MyMapEventHandler = class("MyMapEventHandler", MapEventHandler)

function MyMapEventHandler:preparePlay()
    MyMapEventHandler.super.preparePlay(self)

    self.createNextEnemyDelay_    = 0.1 -- 等待多少时间创建下一个敌人
    self.createNextEnemyInterval_ = 0.5 -- 创建下一个敌人前的间隔时间
    self.enemyCount_              = 0 -- 敌人总数
end

function MyMapEventHandler:time(time, dt)
    MyMapEventHandler.super.time(self, time, dt)

    self.createNextEnemyDelay_ = self.createNextEnemyDelay_ - dt
    if self.createNextEnemyDelay_ <= 0 and self.enemyCount_ < MAX_ENEMY_COUNT then
        self.createNextEnemyDelay_ = self.createNextEnemyDelay_ + self.createNextEnemyInterval_

        local state = {
            defineId = "EnemyShip01",
            behaviors = "NPCBehavior",
        }
        local enemy = self.runtime_:newObject("static", state)
        local pathId = string.format("path:%d", math.random(1, 2))
        enemy:bindPath(self.map_:getObject(pathId), 1)
        enemy:startMoving()

        self.enemyCount_ = self.enemyCount_ + 1
    end
end

function MyMapEventHandler:objectEnterRange(object, range)
    MyMapEventHandler.super.objectEnterRange(self, object, range)

    local rid = range:getId()
    if object.defineId_ == "EnemyShip01" and (rid == "range:28" or rid == "range:30") then
        self.runtime_:removeObject(object)
        self.enemyCount_ = self.enemyCount_ - 1
    end
end

function MyMapEventHandler:objectDestroyed(object)
    MyMapEventHandler.super.objectDestroyed(self, object)
    self.enemyCount_ = self.enemyCount_ - 1
end

return MyMapEventHandler
