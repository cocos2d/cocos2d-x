require "cocos.init"
require "ComponentTest/gameoverscene"

local scene = {
    -- add a new enemy every second
    durationOfAddEnemy = 1.0,
    -- how long past after last time of adding a new enemy
    totalDt = 0,
    numEnemyDestroyed = 0,
    enemies = {},

    onEnter = function(self)
        cc.AudioEngine:play2d("background-music-aac.mp3", true)
    end,

    update = function(self, dt)
        self.totalDt = self.totalDt + dt
        if self.totalDt > self.durationOfAddEnemy then
            self:addNewEnemy()
            self.totalDt = 0
        end
    end,

    addNewEnemy = function(self)
        local owner = self:getOwner()
        local enemy = cc.Sprite:create("components/Target.png")
        local enemyLuaComponent = cc.ComponentLua:create("ComponentTest/enemy.lua")
        enemy:addComponent(enemyLuaComponent)
        owner:addChild(enemy)
        table.insert(self.enemies, enemy)
    end,

    looseGame = function(node)
        local scene = GameOverScene.create("You Lose :[")
        cc.Director:getInstance():replaceScene(scene)
    end,

    inscreaseCount = function(self)
        self.numEnemyDestroyed = self.numEnemyDestroyed + 1
        if self.numEnemyDestroyed >=5 then
            local scene = GameOverScene.create("You Win!")
            cc.Director:getInstance():replaceScene(scene)
        end
    end
}

return scene
