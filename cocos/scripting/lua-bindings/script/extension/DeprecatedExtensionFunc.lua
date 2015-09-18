if nil == cc.Control then
    return
end

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
CCControl.addHandleOfControlEvent = CCControlDeprecated.addHandleOfControlEvent
--functions of CCControl will be deprecated end

--Enums of CCTableView will be deprecated begin
CCTableView.kTableViewScroll = cc.SCROLLVIEW_SCRIPT_SCROLL
CCTableView.kTableViewZoom = cc.SCROLLVIEW_SCRIPT_ZOOM
CCTableView.kTableCellTouched = cc.TABLECELL_TOUCHED
CCTableView.kTableCellSizeForIndex = cc.TABLECELL_SIZE_FOR_INDEX
CCTableView.kTableCellSizeAtIndex = cc.TABLECELL_SIZE_AT_INDEX
CCTableView.kNumberOfCellsInTableView = cc.NUMBER_OF_CELLS_IN_TABLEVIEW
--Enums of CCTableView will be deprecated end

--Enums of CCScrollView will be deprecated begin
CCScrollView.kScrollViewScroll = cc.SCROLLVIEW_SCRIPT_SCROLL
CCScrollView.kScrollViewZoom = cc.SCROLLVIEW_SCRIPT_ZOOM
--Enums of CCScrollView will be deprecated end
