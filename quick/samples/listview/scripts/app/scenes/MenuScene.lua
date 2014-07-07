
local AdBar = import("..views.AdBar")
local BubbleButton = import("..views.BubbleButton")

local MenuScene = class("MenuScene", function()
    return display.newScene("MenuScene")
end)

function MenuScene:ctor()
    self.bg = display.newSprite("#MenuSceneBg.png", display.cx, display.cy)
    self:addChild(self.bg)

    -- add listview
    self.listview = cc.ui.UIListView:new{rect = cc.rect(10, 50, display.width - 20, display.height - 100)}
        :registerHandler(self.listViewDelegate, cc.ui.UIListView.DELEGATE)
        :addTo(self)

    print("htl MenuScene ctor end")
end

function MenuScene:onEnter()
end

function MenuScene:listViewDelegate(name, idx)
    print("htl listview delegate:", name, idx)
    
    if name == UIListView.CELL_TAG then
        return cc.ui.UILabel.new({text = "text"..idx, size = 20, align = cc.ui.TEXT_ALIGN_CENTER})
    elseif name == UIListView.CELL_SIZE_TAG then
        return 300, 40
    elseif name == UIListView.COUNT_TAG then
        return 3
    end
end

return MenuScene
