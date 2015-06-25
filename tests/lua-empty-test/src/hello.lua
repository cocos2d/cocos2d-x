
local Movement = {

    update = function(self, dt)
        local owner = self:getOwner()
        local x, y = owner:getPosition()
        owner:setPosition(self:getPos(x, y))
        print(dt)
    end,

    getPos = function(self, x, y)
        return x+1, y+1
    end
}

return Movement