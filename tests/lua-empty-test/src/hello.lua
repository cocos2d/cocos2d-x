
function cc.ComponentLua:update()

    local owner = self:getOwner()
    local x, y = owner:getPosition()
    owner:setPosition(x+1, y+1)

end