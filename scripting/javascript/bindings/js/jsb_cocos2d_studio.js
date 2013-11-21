//
// cocos2d studio constants
//
// This helper file should be required after jsb_cocos2d.js
//

var ccs = ccs || {};

//movement event type
ccs.MovementEventType = {
    start: 0,
    complete: 1,
    loopComplete: 2
};

ccs.BrightStyle = {
    none: -1,
    normal: 0,
    highlight: 1
};

ccs.WidgetType = {
    widget: 0, //control
    container: 1 //container
};

ccs.TextureResType = {
    local: 0,
    plist: 1
};

ccs.TouchEventType = {
    began: 0,
    moved: 1,
    ended: 2,
    canceled: 3
};

ccs.SizeType = {
    absolute: 0,
    percent: 1
};

ccs.PositionType = {
    absolute: 0,
    percent: 1
};

ccs.CheckBoxEventType = {
    selected: 0,
    unselected: 1
};

ccs.TextFiledEventType = {
    attach_with_me: 0,
    detach_with_ime: 1,
    insert_text: 2,
    delete_backward: 3
};

ccs.LayoutBackGroundColorType = {
    none: 0,
    solid: 1,
    gradient: 2
};

ccs.LayoutType = {
    absolute: 0,
    linearVertical: 1,
    linearHorizontal: 2,
    relative: 3
};

ccs.UILayoutParameterType = {
    none: 0,
    linear: 1,
    relative: 2
};

ccs.UILinearGravity = {
    none: 0,
    left: 1,
    top: 2,
    right: 3,
    bottom: 4,
    centerVertical: 5,
    centerHorizontal: 6
};

ccs.UIRelativeAlign = {
    alignNone: 0,
    alignParentTopLeft: 1,
    alignParentTopCenterHorizontal: 2,
    alignParentTopRight: 3,
    alignParentLeftCenterVertical: 4,
    centerInParent: 5,
    alignParentRightCenterVertical: 6,
    alignParentLeftBottom: 7,
    alignParentBottomCenterHorizontal: 8,
    alignParentRightBottom: 9,
    locationAboveLeftAlign: 10,
    locationAboveCenter: 11,
    locationAboveRightAlign: 12,
    locationLeftOfTopAlign: 13,
    locationLeftOfCenter: 14,
    locationLeftOfBottomAlign: 15,
    locationRightOfTopAlign: 16,
    locationRightOfCenter: 17,
    locationRightOfBottomAlign: 18,
    locationBelowLeftAlign: 19,
    locationBelowCenter: 20,
    locationBelowRightAlign: 21
};

ccs.SliderEventType = {percent_changed: 0};

ccs.LoadingBarType = { left: 0, right: 1};

ccs.ScrollViewDir = {
    none: 0,
    vertical: 1,
    horizontal: 2,
    both: 3
};

ccs.ScrollviewEventType = {
    scrollToTop: 0,
    scrollToBottom: 1,
    scrollToLeft: 2,
    scrollToRight: 3,
    scrolling: 4,
    bounceTop: 5,
    bounceBottom: 6,
    bounceLeft: 7,
    bounceRight: 8
};

ccs.ListViewEventType = {
    init_child: 0,
    update_child: 1
};

ccs.PageViewEventType = {
    turning: 0
};

ccs.PVTouchDir = {
    touchLeft: 0,
    touchRight: 1
};

ccs.UIPanel = ccs.UILayout;
ccs.UITextArea = ccs.UILabel;
ccs.UIContainerWidget = ccs.UILayout;
ccs.UITextButton = ccs.UIButton;
ccs.UINodeContainer = ccs.UIWidget;
ccs.PanelColorType = ccs.LayoutBackGroundColorType;

ccs.UILayout = ccs.Layout;

ccs.UIMargin = cc.Class.extend({
    left: 0,
    top: 0,
    right: 0,
    bottom: 0,
    ctor: function () {
        if (arguments.length == 1) {
            var uiMargin = arguments[0];
            this.left = uiMargin.left;
            this.top = uiMargin.top;
            this.right = uiMargin.right;
            this.bottom = uiMargin.bottom;
        }
        if (arguments.length == 4) {
            this.left = arguments[0];
            this.top = arguments[1];
            this.right = arguments[2];
            this.bottom = arguments[3];
        }
    },
    setMargin: function (l, t, r, b) {
        this.left = l;
        this.top = t;
        this.right = r;
        this.bottom = b;
    },
    equals: function (target) {
        return (this.left == target.left && this.top == target.top && this.right == target.right && this.bottom == target.bottom);
    }
});

// Armature
if(ccs.Armature){
	ccs.Armature.prototype.setBody = function( body ) {
    var b = body;
    if( body.handle !== undefined )
        b = body.handle;
    return this._setCPBody( b );
  };
  
  ccs.ComController.extend = cc.Class.extend;
  ccs.Armature.extend = cc.Class.extend;
}
