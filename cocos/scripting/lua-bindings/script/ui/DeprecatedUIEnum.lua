if nil == ccui then
    return
end

ccui.LoadingBarType                    = ccui.LoadingBarDirection
ccui.LoadingBarType.left               = ccui.LoadingBarDirection.LEFT
ccui.LoadingBarType.right              = ccui.LoadingBarDirection.RIGHT

ccui.LayoutType.absolute               = ccui.LayoutType.ABSOLUTE
ccui.LayoutType.linearVertical         = ccui.LayoutType.VERTICAL
ccui.LayoutType.linearHorizontal       = ccui.LayoutType.HORIZONTAL
ccui.LayoutType.relative               = ccui.LayoutType.RELATIVE

ccui.ListViewEventType.onsSelectedItem = ccui.ListViewEventType.ONSELECTEDITEM_START
