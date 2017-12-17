if nil == ccui then
    return
end

ccui.BrightStyle =
{
    none = -1,
    normal = 0,
    highlight = 1,
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

ccui.RadioButtonEventType=
{
        selected = 0,
        unselected = 1
}

ccui.RadioButtonGroupEventType=
{
    select_changed = 0
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
    ABSOLUTE = 0,
    VERTICAL = 1,
    HORIZONTAL = 2,
    RELATIVE = 3,
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

ccui.SliderEventType = {
    percentChanged = 0,
    slideBallDown = 1,
    slideBallUp = 2,
    slideBallCancel = 3
}

ccui.LoadingBarDirection = { LEFT = 0, RIGHT = 1}

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
    containerMoved = 9,
    autoscrollEnded = 10,
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
    ONSELECTEDITEM_START = 0,
    ONSELECTEDITEM_END   = 1,
}

ccui.PageViewEventType = {
   turning = 0,
}

ccui.PageViewDirection = {
  NONE = 0,
  VERTICAL = 1,
  HORIZONTAL = 2,
  BOTH = 3
}

ccui.PVTouchDir = {
    touchLeft = 0,
    touchRight = 1,
    touchUp = 2,
    touchDown = 3
}

ccui.ListViewGravity = {
    left = 0,
    right = 1,
    centerHorizontal = 2,
    top = 3,
    bottom = 4 ,
    centerVertical = 5,
}

ccui.TextType = {
    SYSTEM = 0,
    TTF    = 1,
}

ccui.LayoutComponent.HorizontalEdge = {
    None = 0,
    Left = 1,
    Right = 2,
    Center = 3,
}

ccui.LayoutComponent.VerticalEdge = {
    None = 0,
    Bottom = 1,
    Top = 2,
    Center = 3,
}
