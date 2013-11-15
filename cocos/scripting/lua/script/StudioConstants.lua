ccs = ccs or {}


ccs.MovementEventType = {
    START = 0,
    COMPLETE = 1,
    LOOP_COMPLETE = 2, 
}

ccs.BrightStyle = 
{
    none = -1,
    normal = 0,
    highlight = 1,
}

ccs.WidgetType = 
{
    widget = 0, --control
    container = 1, --container
}

-- ccs.TextureResType = 
-- {
--     "local" = 0,
--     "plist" = 1,
-- }

ccs.TouchEventType = 
{
    began = 0,
    moved = 1,
    ended = 2,
    canceled = 3,
}

ccs.SizeType = 
{
    absolute = 0,
    percent = 1,
}

ccs.PositionType = {
    absolute = 0,
    percent = 1,
}

ccs.CheckBoxEventType = 
{
    selected = 0,
    unselected = 1,
}

ccs.TextFiledEventType = 
{
    attach_with_ime = 0,
    detach_with_ime = 1,
    insert_text = 2,
    delete_backward = 3,
}

ccs.LayoutBackGroundColorType = 
{
    none = 0,
    solid = 1,
    gradient = 2,
}

ccs.LayoutType = 
{
    absolute = 0,
    linearVertical = 1,
    linearHorizontal = 2,
    relative = 3,
}

ccs.UILayoutParameterType = 
{
    none = 0,
    linear = 1,
    relative = 2,
}

ccs.UILinearGravity = 
{
    none = 0,
    left = 1,
    top = 2,
    right = 3,
    bottom = 4,
    centerVertical = 5,
    centerHorizontal = 6,
}

ccs.UIRelativeAlign = 
{
    alignNone = 0,
    alignParentTopLeft = 1,
    alignParentTopCenterHorizontal = 2,
    alignParentTopRight = 3,
    alignParentLeftCenterVertical = 4,
    centerInParent = 5,
    alignParentRightCenterVertical = 6,
    alignParentLeftBottom = 7,
    alignParentBottomCenterHorizontal = 8,
    alignParentRightBottom = 9,
    locationAboveLeftAlign = 10,
    locationAboveCenter = 11,
    locationAboveRightAlign = 12,
    locationLeftOfTopAlign = 13,
    locationLeftOfCenter = 14,
    locationLeftOfBottomAlign = 15,
    locationRightOfTopAlign = 16,
    locationRightOfCenter = 17,
    locationRightOfBottomAlign = 18,
    locationBelowLeftAlign = 19,
    locationBelowCenter = 20,
    locationBelowRightAlign = 21,
}

ccs.SliderEventType = {percent_changed = 0}

ccs.LoadingBarType = { left = 0, right = 1}

ccs.SCROLLVIEW_DIR = {
    none = 0,
    vertical = 1,
    horizontal = 2,
    both = 3,
}

ccs.SCROLLVIEW_MOVE_DIR = {
    none = 0,
    up = 1,
    down = 2,
    left = 3,
    right = 4,
}

ccs.ScrollviewEventType = {
    top = 0,
    bottom = 1,
    left = 2,
    right = 3,
}

ccs.ListViewDirection = {
    none = 0,
    vertical = 1,
    horizontal = 2,
}

ccs.ListViewMoveDirection = {
    none = 0,
    up = 1,
    down = 2,
    left = 3,
    right = 4,
}

ccs.ListViewEventType = {
    init_child = 0,
    update_child = 1,
}

ccs.PageViewEventType = {
   turning = 0,  
}

ccs.PVTouchDir = {
    touch_left = 0,
    touch_right = 1,
}

ccs.ListViewGravity = {
    left = 0,
    right = 1,
    center_horizontal = 2,
    top = 3,
    bottom = 4 ,
    center_vertical = 5,
}
