ccui = ccui or {}

ccui.BrightStyle = 
{
    none = -1,
    normal = 0,
    highlight = 1,
}

ccui.WidgetType = 
{
    widget = 0, --control
    container = 1, --container
}

ccui.TextureResType = 
{
    localType = 0,
    plistType = 1,
}

ccui.TouchEventType = 
{
    began = 0,
    moved = 1,
    ended = 2,
    canceled = 3,
}

ccui.SizeType = 
{
    absolute = 0,
    percent = 1,
}

ccui.PositionType = {
    absolute = 0,
    percent = 1,
}

ccui.CheckBoxEventType = 
{
    selected = 0,
    unselected = 1,
}

ccui.TextFiledEventType = 
{
    attach_with_ime = 0,
    detach_with_ime = 1,
    insert_text = 2,
    delete_backward = 3,
}

ccui.LayoutBackGroundColorType = 
{
    none = 0,
    solid = 1,
    gradient = 2,
}

ccui.LayoutType = 
{
    absolute = 0,
    linearVertical = 1,
    linearHorizontal = 2,
    relative = 3,
}

ccui.LayoutParameterType = 
{
    none = 0,
    linear = 1,
    relative = 2,
}

ccui.LinearGravity = 
{
    none = 0,
    left = 1,
    top = 2,
    right = 3,
    bottom = 4,
    centerVertical = 5,
    centerHorizontal = 6,
}

ccui.RelativeAlign = 
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

ccui.SliderEventType = {percentChanged = 0}

ccui.LoadingBarType = { left = 0, right = 1}

ccui.ScrollViewDir = {
    none = 0,
    vertical = 1,
    horizontal = 2,
    both = 3,
}

ccui.ScrollViewMoveDir = {
    none = 0,
    up = 1,
    down = 2,
    left = 3,
    right = 4,
}

ccui.ScrollviewEventType = {
    scrollToTop =  0,
    scrollToBottom =  1,
    scrollToLeft = 2,
    scrollToRight = 3,
    scrolling = 4,
    bounceTop = 5,
    bounceBottom = 6,
    bounceLeft = 7,
    bounceRight = 8,
}

ccui.ListViewDirection = {
    none = 0,
    vertical = 1,
    horizontal = 2,
}

ccui.ListViewMoveDirection = {
    none = 0,
    up = 1,
    down = 2,
    left = 3,
    right = 4,
}

ccui.ListViewEventType = {
    onsSelectedItem = 0,
}

ccui.PageViewEventType = {
   turning = 0,  
}

ccui.PVTouchDir = {
    touchLeft = 0,
    touchRight = 1,
}

ccui.ListViewGravity = {
    left = 0,
    right = 1,
    centerHorizontal = 2,
    top = 3,
    bottom = 4 ,
    centerVertical = 5,
}
