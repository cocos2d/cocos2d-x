
local AutoLayout = {}

function AutoLayout.alignItemsHorizontally(items, x, y, padding, lines)
    local separatorPadding = math.abs(math.floor(padding / 4) * 2)
    local first, last, step = 1, #items, 1
    if padding < 0 then
        first, last, step = last, first, - 1
    end

    local left = x
    y = y + (padding + separatorPadding / 2) * (lines - 1)
    for index = first, last, step do
        local item = items[index]
        if type(item) ~= "string" then
            item:setPosition(x, y)
            x = x + padding
        elseif item == "-" then
            x = x + separatorPadding
        elseif item == "#" then
            x = left
            y = y - padding - separatorPadding / 2
        end
    end
end

return AutoLayout
