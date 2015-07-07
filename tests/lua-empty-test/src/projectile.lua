
local ENEMY_TAG = 2

local projectile = {
    update = function(self, dt)
        -- if there is any enemy collides with this projectile, then
        -- remove this projectile and all collided enemies

        local owner = self:getOwner()
        local projectileX, projectileY = owner:getPosition()
        local projectileContentSize = owner:getContentSize()
        local projectileRect = cc.rect(projectileX, projectileY, 
                projectileContentSize.width/2, projectileContentSize.height/2)

        local scene = owner:getParent()
        local enemies = self:getEnemies(scene)
        local removeOwner = false
        
        for _, enemy in pairs(enemies) do
            local enemyX, enemyY = enemy:getPosition()
            local enemyContentSize = enemy:getContentSize()
            local enemyRect = cc.rect(enemyX, enemyY, 
                    enemyContentSize.width/2, enemyContentSize.height/2)

            if cc.rectIntersectsRect(projectileRect, enemyRect) then
                scene:removeChild(enemy, true)

                removeOwner = true
            end
        end

        if removeOwner == true then
            scene:removeChild(owner, true)
        end
    end,

    getEnemies = function(self, scene)
        local children = scene:getChildren()
        local enemies = {}

        for _, child in pairs(children) do
            local tag = child:getTag()

            if tag == ENEMY_TAG then
                table.insert(enemies, v)
            end
        end

        return enemies
    end,
}

return projectile
