
function createTouchableSprite(p)
    local sprite = display.newScale9Sprite(p.image)
    sprite:setContentSize(p.size)

    local cs = sprite:getContentSize()
    local label = cc.ui.UILabel.new({
            UILabelType = 2,
            text = p.label,
            color = p.labelColor})
    label:align(display.CENTER)
    label:setPosition(cs.width / 2, label:getContentSize().height)
    sprite:addChild(label)
    sprite.label = label

    return sprite
end

function createSimpleButton(imageName, name, movable, listener)
    local sprite = display.newSprite(imageName)

    if name then
        local cs = sprite:getContentSize()
        local label = cc.ui.UILabel.new({
            UILabelType = 2,text = name, color = display.COLOR_BLACK})
        label:setPosition(cs.width / 2, cs.height / 2)
        -- sprite:addChild(label)
    end

    sprite:setTouchEnabled(true) -- enable sprite touch
    -- sprite:setTouchMode(cc.TOUCH_ALL_AT_ONCE) -- enable multi touches
    sprite:setTouchSwallowEnabled(false)
    sprite:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        local name, x, y, prevX, prevY = event.name, event.x, event.y, event.prevX, event.prevY
        if name == "began" then
            sprite:setOpacity(128)
            -- return cc.TOUCH_BEGAN -- stop event dispatching
            return cc.TOUCH_BEGAN_NO_SWALLOWS -- continue event dispatching
        end

        local touchInSprite = cc.rectContainsPoint(sprite:getCascadeBoundingBox(), cc.p(x, y))
        if name == "moved" then
            sprite:setOpacity(128)
            if movable then
                local offsetX = x - prevX
                local offsetY = y - prevY
                local sx, sy = sprite:getPosition()
                sprite:setPosition(sx + offsetX, sy + offsetY)
                return cc.TOUCH_MOVED_RELEASE_OTHERS -- stop event dispatching, remove others node
                -- return cc.TOUCH_MOVED_SWALLOWS -- stop event dispatching
            end

        elseif name == "ended" then
            if touchInSprite then listener() end
            sprite:setOpacity(255)
        else
            sprite:setOpacity(255)
        end
    end)

    return sprite
end

function drawBoundingBox(parent, target, color)
    local cbb = target:getCascadeBoundingBox()
    local left, bottom, width, height = cbb.origin.x, cbb.origin.y, cbb.size.width, cbb.size.height
    local points = {
        {left, bottom},
        {left + width, bottom},
        {left + width, bottom + height},
        {left, bottom + height},
        {left, bottom},
    }
    local box = display.newPolygon(points, {borderColor = color})
    parent:addChild(box, 1000)
end
