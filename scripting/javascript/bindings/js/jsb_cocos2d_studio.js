//
// cocos2d studio constants
//
// This helper file should be required after jsb_cocos2d.js
//

var ccs = ccs || {};

ccs.Class = ccs.Class || cc.Class || {};

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

ccs.LayoutClippingType = {
    stencil: 0,
    scissor: 1
};

ccs.LayoutParameterType = {
    none: 0,
    linear: 1,
    relative: 2
};

ccs.LinearGravity = {
    none: 0,
    left: 1,
    top: 2,
    right: 3,
    bottom: 4,
    centerVertical: 5,
    centerHorizontal: 6
};

ccs.RelativeAlign = {
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
    listViewOnselectedItem: 0
};

ccs.ListViewGravity = {
    left: 0,
    right: 1,
    centerHorizontal: 2,
    top: 3,
    bottom: 4,
    centerVertical: 5
};

ccs.PageViewEventType = {
    turning: 0
};

ccs.PVTouchDir = {
    touchLeft: 0,
    touchRight: 1
};

//CompatibleClasses
ccs.UIPanel = ccs.Layout;
ccs.UITextArea = ccs.Label;
ccs.UIContainerWidget = ccs.Layout;
ccs.UITextButton = ccs.Button;
ccs.UINodeContainer = ccs.Widget;
ccs.PanelColorType = ccs.LayoutBackGroundColorType;

ccs.UIWidget = ccs.Widget;

ccs.UILayoutParameter = ccs.LayoutParameter;
ccs.UILinearLayoutParameter = ccs.LinearLayoutParameter;
ccs.UIRelativeLayoutParameter = ccs.RelativeLayoutParameter;

ccs.UILinearGravity = ccs.LinearGravity;
ccs.UIRelativeAlign = ccs.RelativeAlign;

ccs.UIMargin = ccs.Margin;
ccs.UIMarginZero = ccs.MarginZero;

ccs.UIListView = ccs.ListView;
ccs.UIPageView = ccs.PageView;
ccs.UIScrollView = ccs.ScrollView;
ccs.UIButton = ccs.Button;
ccs.UICheckBox = ccs.CheckBox;
ccs.UIImageView = ccs.ImageView;
ccs.UILabel = ccs.Label;
ccs.UILabelAtlas = ccs.LabelAtlas;
ccs.UILabelBMFont = ccs.LabelBMFont;
ccs.UILoadingBar = ccs.LoadingBar;
ccs.UISlider = ccs.Slider;
ccs.UITextField = ccs.TextField;

ccs.Margin = cc.Class.extend({
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
  
  ccs.ArmatureAnimation.prototype.playWithNames = function() {
    return ccs.ArmatureAnimation.prototype.playWithArray.apply(this, arguments);
  };
  
  ccs.ArmatureAnimation.prototype.playWithIndexes = function() {
  	return ccs.ArmatureAnimation.prototype.playWithIndexArray.apply(this, arguments);
  };

  ccs.ComController.extend = cc.Class.extend;
  ccs.Armature.extend = cc.Class.extend;
}


ccs.sendEvent = function (event) {
    var triggerObjArr = ccs.TriggerMng.getInstance().get(event);
    if (triggerObjArr == null) {
        return;
    }
    for (var i = 0; i < triggerObjArr.length; i++) {
        var triObj = triggerObjArr[i];
        if (triObj != null && triObj.detect()) {
            triObj.done();
        }
    }
};


ccs.ObjectFactory = ccs.Class.extend({
    _typeMap: null,
    ctor: function () {
        this._typeMap = {};
    },
    destroyInstance: function () {
        this._sharedFactory = null;
    },

    createObject: function (className) {
        var o = null;
        var t = this._typeMap[className];
        if (t) {
            o = new t._fun();
        }
        return o;
    },

    registerType: function (t) {
        this._typeMap[t._className] = t;
    }
});

ccs.ObjectFactory._sharedFactory = null;

ccs.ObjectFactory.getInstance = function () {
    if (!this._sharedFactory) {
        this._sharedFactory = new ccs.ObjectFactory();
    }
    return this._sharedFactory;
};

ccs.TInfo = ccs.Class.extend({
    _className: "",
    _fun: null,
    /**
     *
     * @param {String|ccs.TInfo}c
     * @param {Function}f
     */
    ctor: function (c, f) {
        if (f) {
            this._className = c;
            this._fun = f;
        }else{
            this._className = c._className;
            this._fun = c._fun;
        }
        ccs.ObjectFactory.getInstance().registerType(this);
    }
});

ccs.registerTriggerClass = function(className, createFunc) {
    new ccs.TInfo(className, createFunc);
}

ccs.BaseTriggerCondition = ccs.Class.extend({
    init: function () {
        return true;
    },

    detect: function () {
        return true;
    },

    serialize: function (jsonVal) {
    },

    removeAll: function () {
    }
});
ccs.BaseTriggerAction = ccs.Class.extend({

    init: function () {
        return true;
    },

    done: function () {

    },

    serialize: function (jsonVal) {
    },

    removeAll: function () {
    }
});

ccs.TriggerObj = ccs.Class.extend({
    _cons: null,
    _acts: null,
    _id: 0,
    _enable: true,
    _vInt: null,

    ctor: function () {
        this._id = 0;
        this._enable = true;
    },

    init: function () {
        this._cons = [];
        this._acts = [];
        this._vInt = [];
        return true;
    },

    detect: function () {
        if (!this._enable || this._cons.length == 0) {
            return true;
        }
        var ret = true;
        var obj = null;
        for (var i = 0; i < this._cons.length; i++) {
            obj = this._cons[i];
            if (obj && obj.detect) {
                ret = ret && obj.detect();
            }
        }
        return ret;
    },

    done: function () {
        if (!this._enable || this._acts.length == 0) {
            return;
        }
        var obj;
        for (var i = 0; i < this._acts.length; i++) {
            obj = this._acts[i];
            if (obj && obj.done) {
                obj.done();
            }
        }
    },

    removeAll: function () {
        var obj = null;
        for (var i = 0; i < this._cons.length; i++) {
            obj = this._cons[i];
            if (obj)
                obj.removeAll();
        }
        this._cons = [];
        for (var i = 0; i < this._acts.length; i++) {
            obj = this._acts[i];
            if (obj)
                obj.removeAll();
        }
        this._acts = [];
    },

    serialize: function (jsonVal) {
        this._id = jsonVal["id"] || 0;
        var conditions = jsonVal["conditions"] || [];
        for (var i = 0; i < conditions.length; i++) {
            var subDict = conditions[i];
            var classname = subDict["classname"];
            if (!classname) {
                continue;
            }
            var con = ccs.ObjectFactory.getInstance().createObject(classname);
            if (!con) {
                cc.log("class named classname(" + classname + ") can not implement!");
            }

            con.serialize(subDict);
            con.init();
            this._cons.push(con);
        }

        var actions = jsonVal["actions"] || [];
        for (var i = 0; i < actions.length; i++) {
            var subDict = actions[i];
            var classname = subDict["classname"];
            if (!classname) {
                continue;
            }
            var act = ccs.ObjectFactory.getInstance().createObject(classname);
            if (!act) {
                cc.log("class named classname(" + classname + ") can not implement!");
            }

            act.serialize(subDict);
            act.init();
            this._acts.push(act);
        }

        var events = jsonVal["events"] || [];
        for (var i = 0; i < events.length; i++) {
            var subDict = events[i];
            var event = subDict["id"];
            if (event < 0) {
                continue;
            }
            this._vInt.push(event);
        }
    },

    getId: function () {
        return this._id;
    },

    setEnable: function (enable) {
        this._enable = enable;
    },

    getEvents: function () {
        return this._vInt;
    }
});

ccs.TriggerObj.create = function() {
  var ret = new ccs.TriggerObj();
  if (ret.init())
    return ret;
  return null;
}

ccs.TriggerMng = ccs.Class.extend({
    _eventTriggers: null,
    _triggerObjs: null,
    _movementDispatches: null,
    ctor: function () {
        this._eventTriggers = {};
        this._triggerObjs = {};
        this._movementDispatches = [];
    },

    destroyInstance: function () {
        this.removeAll();
        this._instance = null;
    },

    parse: function (root) {
        var triggers = root;//["Triggers"];
        for (var i = 0; i < triggers.length; ++i) {
            var subDict = triggers[i];
            var triggerObj = ccs.TriggerObj.create();
            triggerObj.serialize(subDict);
            var events = triggerObj.getEvents();
            for (var j = 0; j < events.length; j++) {
                var event = events[j];
                this.add(event, triggerObj);
            }
            this._triggerObjs[triggerObj.getId()] = triggerObj;
        }
    },

    get: function (event) {
        return this._eventTriggers[event];
    },

    getTriggerObj: function (id) {
        return this._triggerObjs[id];
    },

    add: function (event, triggerObj) {
        var eventTriggers = this._eventTriggers[event];
        if (!eventTriggers) {
            eventTriggers = [];
        }
        if (!cc.ArrayContainsObject(eventTriggers, triggerObj)) {
            eventTriggers.push(triggerObj);
            this._eventTriggers[event] = eventTriggers;
        }
    },

    removeAll: function () {
        for (var key in this._eventTriggers) {
            var triObjArr = this._eventTriggers[key];
            for (var j = 0; j < triObjArr.length; j++) {
                var obj = triObjArr[j];
                obj.removeAll();
            }
        }
        this._eventTriggers = {};
    },

    remove: function (event, Obj) {
        if (Obj) {
            return this._removeObj(event, Obj);
        }
        var bRet = false;
        do
        {
            var triObjects = this._eventTriggers[event];
            if (!triObjects) break;
            for (var i = 0; i < triObjects.length; i++) {
                var triObject = triObjects[i];
                if (triObject) {
                    triObject.removeAll();
                }
            }
            delete this._eventTriggers[event];
            bRet = true;
        } while (0);
        return bRet;
    },

    _removeObj: function (event, Obj) {
        var bRet = false;
        do
        {
            var triObjects = this._eventTriggers[event];
            if (!triObjects) break;
            for (var i = 0; i < triObjects.length; i++) {
                var triObject = triObjects[i];
                if (triObject && triObject == Obj) {
                    triObject.removeAll();
                    triObjects.splice(i, 1);
                    break;
                }
            }
            bRet = true;
        } while (0);
        return bRet;
    },

    removeTriggerObj: function (id) {
        var obj = this.getTriggerObj(id);
        if (!obj) {
            return false;
        }
        var events = obj.getEvents();
        for (var i = 0; i < events.length; i++) {
            var event = events[i];
            this.remove(event, obj);
        }
        return true;
    },
    isEmpty: function () {
        return !this._eventTriggers || this._eventTriggers.length <= 0;
    },

    addArmatureMovementCallBack: function (armature, callFunc, target) {
        if (armature == null || target == null || callFunc == null) {
            return;
        }
        var locAmd, hasADD = false;
        for (var i = 0; i < this._movementDispatches.length; i++) {
            locAmd = this._movementDispatches[i];
            if (locAmd && locAmd[0] == armature) {
                locAmd.addAnimationEventCallBack(callFunc, target);
                hasADD = true;
            }
        }
        if (!hasADD) {
            var newAmd = new ccs.ArmatureMovementDispatcher();
            armature.getAnimation().setMovementEventCallFunc(newAmd.animationEvent, newAmd);
            newAmd.addAnimationEventCallBack(callFunc, target);
            this._movementDispatches.push([armature, newAmd]);
        }
    },

    removeArmatureMovementCallBack: function (armature, target, callFunc) {
        if (armature == null || target == null || callFunc == null) {
            return;
        }
        var locAmd;
        for (var i = 0; i < this._movementDispatches.length; i++) {
            locAmd = this._movementDispatches[i];
            if (locAmd && locAmd[0] == armature) {
                locAmd.removeAnimationEventCallBack(callFunc, target);
            }
        }
    },

    removeArmatureAllMovementCallBack: function (armature) {
        if (armature == null) {
            return;
        }
        var locAmd;
        for (var i = 0; i < this._movementDispatches.length; i++) {
            locAmd = this._movementDispatches[i];
            if (locAmd && locAmd[0] == armature) {
                this._movementDispatches.splice(i, 1);
                break;
            }
        }
    },

    removeAllArmatureMovementCallBack: function () {
        this._movementDispatches = [];
    }
});

ccs.TriggerMng.triggerMngVersion = function () {
    return "1.2.0.0";
};
ccs.TriggerMng._instance = null;
ccs.TriggerMng.getInstance = function () {
    if (null == this._instance) {
        this._instance = new ccs.TriggerMng();
    }
    return this._instance;
};

