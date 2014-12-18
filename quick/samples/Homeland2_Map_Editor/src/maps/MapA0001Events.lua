local MapEvent        = require("app.map.MapEvent")
local MapEventHandler = require("app.map.MapEventHandler")

local MyMapEventHandler = class("MyMapEventHandler", MapEventHandler)

function MyMapEventHandler:preparePlay()
    MyMapEventHandler.super.preparePlay(self)

    self.createNextEnemyDelay_    = 0.1 -- 等待多少时间创建下一个敌人
    self.createNextEnemyInterval_ = 3.0 -- 创建下一个敌人前的间隔时间
    self.createNextEnemyOnPathIndex_ = 2 -- 下一个敌人在哪一条路径
end

function MyMapEventHandler:time(time, dt)
    MyMapEventHandler.super.time(self, time, dt)

    self.createNextEnemyDelay_ = self.createNextEnemyDelay_ - dt
    if self.createNextEnemyDelay_ <= 0 then
        self.createNextEnemyDelay_ = self.createNextEnemyDelay_ + self.createNextEnemyInterval_

        local state = {
            defineId = "EnemyShip01",
            behaviors = "NPCBehavior",
        }
        local enemy = self.runtime_:newObject("static", state)
        local pathId = string.format("path:%d", self.createNextEnemyOnPathIndex_)
        enemy:bindPath(self.map_:getObject(pathId), 1)
        enemy:startMoving()

        self.createNextEnemyOnPathIndex_ = self.createNextEnemyOnPathIndex_ + 1
        if self.createNextEnemyOnPathIndex_ > 2 then
            self.createNextEnemyOnPathIndex_ = 1
        end
    end
end

function MyMapEventHandler:objectEnterRange(object, range)
    MyMapEventHandler.super.objectEnterRange(self, object, range)

    if object.defineId_ == "EnemyShip01" and range:getId() == "range:21" then
        self.runtime_:removeObject(object)
    end
end

return MyMapEventHandler
