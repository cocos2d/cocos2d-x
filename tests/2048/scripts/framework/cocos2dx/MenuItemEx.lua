
local c = cc
local MenuItem = c.MenuItem

function MenuItem:registerScriptTapHandler(handler)
    PRINT_DEPRECATED("MenuItem.registerScriptTapHandler() is deprecated, please use MenuItem.addNodeEventListener()")
    return self:addNodeEventListener(c.MENU_ITEM_CLICKED_EVENT, handler)
end
