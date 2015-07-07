local scene = {
    -- add a new enemy every second
    durationOfAddEnemy = 1.0,
    -- how long past after last time of adding a new enemy
    totalDt = 0,

    update = function(self, dt)
        self.totalDt = self.totalDt + dt
        if self.totalDt > self.durationOfAddEnemy then
            self:addNewEnemy()
            self.totalDt = 0
        end
    end,

    addNewEnemy = function(self)
        local owner = self:getOwner()
        local enemy = cc.Sprite:create("res/Target.png")
        local enemyLuaComponent = cc.ComponentLua:create("src/enemy.lua")
        enemy:addComponent(enemyLuaComponent)
        owner:addChild(enemy)
    end,
}

return scene
