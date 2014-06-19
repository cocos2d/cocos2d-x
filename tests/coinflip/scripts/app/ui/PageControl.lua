
local ScrollView = import(".ScrollView")
local PageControl = class("PageControl", ScrollView)

function PageControl:onTouchEndedWithoutTap(x, y)
    local offsetX, offsetY = self.offsetX, self.offsetY
    local index = 0
    local count = #self.cells
    if self.direction == ScrollView.DIRECTION_HORIZONTAL then
        offsetX = -offsetX
        local x = 0
        local i = 1
        while i <= count do
            local cell = self.cells[i]
            local size = cell:getContentSize()
            if offsetX < x + size.width / 2 then
                index = i
                break
            end
            x = x + size.width
            i = i + 1
        end
        if i > count then index = count end
    else
        local y = 0
        local i = 1
        while i <= count do
            local cell = self.cells[i]
            local size = cell:getContentSize()
            if offsetY < y + size.height / 2 then
                index = i
                break
            end
            y = y + size.height
            i = i + 1
        end
        if i > count then index = count end
    end

    self:scrollToCell(index, true)
end

return PageControl
