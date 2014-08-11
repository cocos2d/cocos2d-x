require("GuiConstants")

_G.LAYOUT_COLOR_NONE              = ccui.LayoutBackGroundColorType.none
_G.LAYOUT_COLOR_SOLID             = ccui.LayoutBackGroundColorType.solid
_G.LAYOUT_COLOR_GRADIENT          = ccui.LayoutBackGroundColorType.gradient

_G.LAYOUT_ABSOLUTE                = ccui.LayoutType.ABSOLUTE
_G.LAYOUT_LINEAR_VERTICAL         = ccui.LayoutType.VERTICAL
_G.LAYOUT_LINEAR_HORIZONTAL       = ccui.LayoutType.HORIZONTAL
_G.LAYOUT_RELATIVE                = ccui.LayoutType.RELATIVE

_G.BRIGHT_NONE               = ccui.BrightStyle.none
_G.BRIGHT_NORMAL             = ccui.BrightStyle.normal
_G.BRIGHT_HIGHLIGHT          = ccui.BrightStyle.highlight

_G.UI_TEX_TYPE_LOCAL               = ccui.TextureResType.localType
_G.UI_TEX_TYPE_PLIST               = ccui.TextureResType.plistType

_G.TOUCH_EVENT_BEGAN                = ccui.TouchEventType.began
_G.TOUCH_EVENT_MOVED                = ccui.TouchEventType.moved
_G.TOUCH_EVENT_ENDED                = ccui.TouchEventType.ended
_G.TOUCH_EVENT_CANCELED             = ccui.TouchEventType.canceled
 
_G.SIZE_ABSOLUTE                = ccui.SizeType.absolute
_G.SIZE_PERCENT                 = ccui.SizeType.percent

_G.POSITION_ABSOLUTE                = ccui.PositionType.absolute
_G.POSITION_PERCENT                 = ccui.PositionType.percent

_G.CHECKBOX_STATE_EVENT_SELECTED     = ccui.CheckBoxEventType.selected
_G.CHECKBOX_STATE_EVENT_UNSELECTED   = ccui.CheckBoxEventType.unselected

_G.CHECKBOX_STATE_EVENT_SELECTED     = ccui.CheckBoxEventType.selected
_G.CHECKBOX_STATE_EVENT_UNSELECTED   = ccui.CheckBoxEventType.unselected

_G.LoadingBarTypeLeft     = ccui.LoadingBarDirection.LEFT
_G.LoadingBarTypeRight   = ccui.LoadingBarDirection.RIGHT

_G.LoadingBarTypeRight   = ccui.SliderEventType.percent_changed

_G.TEXTFIELD_EVENT_ATTACH_WITH_IME                = ccui.TextFiledEventType.attach_with_ime
_G.TEXTFIELD_EVENT_DETACH_WITH_IME                = ccui.TextFiledEventType.detach_with_ime
_G.TEXTFIELD_EVENT_INSERT_TEXT                 = ccui.TextFiledEventType.insert_text
_G.TEXTFIELD_EVENT_DELETE_BACKWARD             = ccui.TextFiledEventType.delete_backward

_G.SCROLLVIEW_EVENT_SCROLL_TO_TOP                = ccui.ScrollViewDir.none
_G.SCROLLVIEW_DIR_VERTICAL                = ccui.ScrollViewDir.vertical
_G.SCROLLVIEW_DIR_HORIZONTAL                 = ccui.ScrollViewDir.horizontal
_G.SCROLLVIEW_DIR_BOTH             = ccui.ScrollViewDir.both

_G.SCROLLVIEW_EVENT_SCROLL_TO_TOP                = ccui.ScrollviewEventType.scrollToTop
_G.SCROLLVIEW_EVENT_SCROLL_TO_BOTTOM             = ccui.ScrollviewEventType.scrollToBottom
_G.SCROLLVIEW_EVENT_SCROLL_TO_LEFT               = ccui.ScrollviewEventType.scrollToLeft
_G.SCROLLVIEW_EVENT_SCROLL_TO_RIGHT              = ccui.ScrollviewEventType.scrollToRight
_G.SCROLLVIEW_EVENT_SCROLLING                    = ccui.ScrollviewEventType.scrolling
_G.SCROLLVIEW_EVENT_BOUNCE_TOP                   = ccui.ScrollviewEventType.bounceTop
_G.SCROLLVIEW_EVENT_BOUNCE_BOTTOM                = ccui.ScrollviewEventType.bounceBottom
_G.SCROLLVIEW_EVENT_BOUNCE_LEFT                  = ccui.ScrollviewEventType.bounceLeft
_G.SCROLLVIEW_EVENT_BOUNCE_RIGHT                 = ccui.ScrollviewEventType.bounceRight

_G.PAGEVIEW_EVENT_TURNING                 = ccui.PageViewEventType.turning

_G.PAGEVIEW_TOUCHLEFT                  = ccui.PVTouchDir.touch_left
_G.PAGEVIEW_TOUCHRIGHT                 = ccui.PVTouchDir.touch_right

_G.LISTVIEW_DIR_NONE                      = ccui.ListViewDirection.none
_G.LISTVIEW_DIR_VERTICAL                  = ccui.ListViewDirection.vertical
_G.LISTVIEW_DIR_HORIZONTAL                = ccui.ListViewDirection.horizontal

_G.LISTVIEW_MOVE_DIR_NONE                = ccui.ListViewMoveDirection.none
_G.LISTVIEW_MOVE_DIR_UP                  = ccui.ListViewMoveDirection.up
_G.LISTVIEW_MOVE_DIR_DOWN                = ccui.ListViewMoveDirection.down
_G.LISTVIEW_MOVE_DIR_LEFT                = ccui.ListViewMoveDirection.left
_G.LISTVIEW_MOVE_DIR_RIGHT               = ccui.ListViewMoveDirection.right

_G.LISTVIEW_EVENT_INIT_CHILD                 = ccui.ListViewEventType.init_child
_G.LISTVIEW_EVENT_UPDATE_CHILD               = ccui.ListViewEventType.update_child

_G.LAYOUT_PARAMETER_NONE                   = ccui.LayoutParameterType.none
_G.LAYOUT_PARAMETER_LINEAR                 = ccui.LayoutParameterType.linear
_G.LAYOUT_PARAMETER_RELATIVE               = ccui.LayoutParameterType.relative

ccui.LoadingBarType = ccui.LoadingBarDirection 
ccui.LoadingBarType.left = ccui.LoadingBarDirection.LEFT
ccui.LoadingBarType.right = ccui.LoadingBarDirection.RIGHT

ccui.LayoutType.absolute = ccui.LayoutType.ABSOLUTE
ccui.LayoutType.linearVertical = ccui.LayoutType.VERTICAL
ccui.LayoutType.linearHorizontal = ccui.LayoutType.HORIZONTAL
ccui.LayoutType.relative = ccui.LayoutType.RELATIVE

ccui.ListViewEventType.onsSelectedItem = ccui.ListViewEventType.ONSELECTEDITEM_START