
local AdBar = import("..views.AdBar")
local BubbleButton = import("..views.BubbleButton")

local MenuScene = class("MenuScene", function()
    return display.newScene("MenuScene")
end)

function MenuScene:ctor()
    -- self.bg = display.newSprite("#MenuSceneBg.png", display.cx, display.cy)
    -- self:addChild(self.bg)

    -- add listview
    self.listview = cc.ui.UIListView.new{rect = cc.rect(10, 50, display.width - 20, display.height - 100)}
        :registerHandler(self.listViewDelegate, cc.ui.UIListView.DELEGATE)
        :addTo(self)
        :reload()

    HDrawRect(self.listview:getViewRect(), self, cc.c4f(1, 0, 0, 1))
    HDrawRect(self.listview:getBoundingBox(), self, cc.c4f(1, 1, 1, 1))

    print("htl MenuScene ctor end")
end

function MenuScene:onEnter()
end

function MenuScene:listViewDelegate(name, idx)
    print("htl listview delegate:", name, idx)
    
    if name == cc.ui.UIListView.CELL_TAG then
        return cc.ui.UILabel.new({text = "text"..idx, size = 20, align = cc.ui.TEXT_ALIGN_CENTER, color = display.COLOR_WHITE})
    elseif name == cc.ui.UIListView.CELL_SIZE_TAG then
        if 1 == idx%2 then
            return 300, 40
        else
            return 240, 60
        end
    elseif name == cc.ui.UIListView.COUNT_TAG then
        return 10
    end
end

return MenuScene
