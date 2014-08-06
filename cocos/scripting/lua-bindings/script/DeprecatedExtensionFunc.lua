--tip
local function deprecatedTip(old_name,new_name)
    print("\n********** \n"..old_name.." was deprecated please use ".. new_name .. " instead.\n**********")
end

--functions of CCControl will be deprecated end
local CCControlDeprecated = { }
function CCControlDeprecated.addHandleOfControlEvent(self,func,controlEvent)
    deprecatedTip("addHandleOfControlEvent","registerControlEventHandler")
    print("come in addHandleOfControlEvent")
    self:registerControlEventHandler(func,controlEvent)
end
rawset(CCControl,"addHandleOfControlEvent",CCControlDeprecated.addHandleOfControlEvent)
--functions of CCControl will be deprecated end

--Enums of CCTableView will be deprecated begin
rawset(CCTableView, "kTableViewScroll",cc.SCROLLVIEW_SCRIPT_SCROLL)
rawset(CCTableView,"kTableViewZoom",cc.SCROLLVIEW_SCRIPT_ZOOM)
rawset(CCTableView,"kTableCellTouched",cc.TABLECELL_TOUCHED)
rawset(CCTableView,"kTableCellSizeForIndex",cc.TABLECELL_SIZE_FOR_INDEX)
rawset(CCTableView,"kTableCellSizeAtIndex",cc.TABLECELL_SIZE_AT_INDEX)
rawset(CCTableView,"kNumberOfCellsInTableView",cc.NUMBER_OF_CELLS_IN_TABLEVIEW)
--Enums of CCTableView will be deprecated end

--Enums of CCScrollView will be deprecated begin
rawset(CCScrollView, "kScrollViewScroll",cc.SCROLLVIEW_SCRIPT_SCROLL)
rawset(CCScrollView,"kScrollViewZoom",cc.SCROLLVIEW_SCRIPT_ZOOM)
--Enums of CCScrollView will be deprecated end
