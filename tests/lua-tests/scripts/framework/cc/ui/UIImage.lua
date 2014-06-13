
local UIImage = class("UIImage", function(filename, options)
    if options and options.scale9 then
        return display.newScale9Sprite(filename)
    else
        return display.newSprite(filename)
    end
end)

function UIImage:ctor(filename, options)
    makeUIControl_(self)
    self:align(display.LEFT_BOTTOM)
    local contentSize = self:getContentSize()
    self:getComponent("components.ui.LayoutProtocol"):setLayoutSize(contentSize.width, contentSize.height)
    self.isScale9_ = options and options.scale9
    if self.isScale9_ then
        self:setLayoutSizePolicy(display.AUTO_SIZE, display.AUTO_SIZE)
    end
end

function UIImage:setLayoutSize(width, height)
    self:getComponent("components.ui.LayoutProtocol"):setLayoutSize(width, height)
    local width, height = self:getLayoutSize()
    local top, right, bottom, left = self:getLayoutPadding()
    width = width - left - right
    height = height - top - bottom

    if self.isScale9_ then
        self:setContentSize(CCSize(width, height))
    else
        local boundingSize = self:getBoundingBox().size
        local sx = width / (boundingSize.width / self:getScaleX())
        local sy = height / (boundingSize.height / self:getScaleY())
        if sx > 0 and sy > 0 then
            self:setScaleX(sx)
            self:setScaleY(sy)
        end
    end

    if self.layout_ then
        self:setLayout(self.layout_)
    end

    return self
end

return UIImage
