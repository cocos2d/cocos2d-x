
local ToolBase = class("ToolBase")

ToolBase.TOUCH_IGNORED       = "ignored"
ToolBase.DEFAULT_TOUCH_ENDED = "ended"

function ToolBase:ctor(name, toolbar, map)
    self.name_               = name
    self.toolbar_            = toolbar
    self.map_                = map
    self.selectedButtonName_ = nil
end

function ToolBase:getName()
    return self.name_
end

function ToolBase:selected(selectedButtonName)
    self.selectedButtonName_ = selectedButtonName
end

function ToolBase:unselected()
end

function ToolBase:onTouch(event, x, y)
    return ToolBase.TOUCH_IGNORED
end

return ToolBase
