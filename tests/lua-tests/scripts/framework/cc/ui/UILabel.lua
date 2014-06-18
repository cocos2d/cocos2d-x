
local UILabel = class("UILabel", function(options)
    return ui.newTTFLabel(options)
end)

function UILabel:ctor(options)
    makeUIControl_(self)
    self:setLayoutSizePolicy(display.FIXED_SIZE, display.FIXED_SIZE)
    self:align(display.LEFT_CENTER)
end

function UILabel:setLayoutSize(width, height)
    self:getComponent("components.ui.LayoutProtocol"):setLayoutSize(width, height)
    return self
end

return UILabel
