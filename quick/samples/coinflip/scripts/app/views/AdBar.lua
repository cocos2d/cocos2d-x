
local AdBar = {}

function AdBar.new()
    local sprite = display.newSprite("#AdBar.png")
    sprite:align(display.BOTTOM_CENTER, display.cx, display.bottom)
    return sprite
end

return AdBar
