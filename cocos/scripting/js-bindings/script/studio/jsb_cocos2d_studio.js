/*
 * Copyright (c) 2013-2016 Chukong Technologies Inc.
 * Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

//
// cocos2d studio constants
//
// This helper file should be required after jsb_cocos2d.js
//

var ccs = ccs || {};

ccs.Class = ccs.Class || cc.Class || {};

// Movement event type
ccs.MovementEventType = {
    start: 0,
    complete: 1,
    loopComplete: 2
};

// Inner action type
ccs.InnerActionType = {
    LoopAction: 0,
    NoLoopAction: 1,
    SingleFrame: 2
};

ccs.AnimationInfo = function (name, startIndex, endIndex) {
    this.name = name || "";
    this.startIndex = startIndex != undefined ? startIndex : 0;
    this.endIndex = endIndex != undefined ? endIndex : 0;
};

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

ccs.Armature.prototype._setBlendFunc = ccs.Armature.prototype.setBlendFunc;
ccs.Armature.prototype.setBlendFunc = templateSetBlendFunc;


ccs.sendEvent = function (event) {
    var triggerObjArr = ccs.triggerManager.get(event);
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


ccs.objectFactory = {
    _typeMap: {},
    
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
        ccs.objectFactory.registerType(this);
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
            var con = ccs.objectFactory.createObject(classname);
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
            var act = ccs.objectFactory.createObject(classname);
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

ccs.triggerManager = {
    _eventTriggers: {},
    _triggerObjs: {},
    _movementDispatches: [],

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
        if (eventTriggers.indexOf(triggerObj) == -1) {
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
    },
                                  
    version: function () {
        return "1.2.0.0";
    }
};


// Functions don't support binding
ccs.Bone.prototype.getColliderBodyList = function() {
    var decoDisplay = this.getDisplayManager().getCurrentDecorativeDisplay();
    if (decoDisplay) {
        var detector = decoDisplay.getColliderDetector();
        if (detector) {
            return detector.getColliderBodyList();
        }
    }
    return [];
};

ccs.TweenType = {
    CUSTOM_EASING: -1,
    LINEAR: 0,

    SINE_EASEIN: 1,
    SINE_EASEOUT: 2,
    SINE_EASEINOUT: 3,

    QUAD_EASEIN: 4,
    QUAD_EASEOUT: 5,
    QUAD_EASEINOUT: 6,

    CUBIC_EASEIN: 7,
    CUBIC_EASEOUT: 8,
    CUBIC_EASEINOUT: 9,

    QUART_EASEIN: 10,
    QUART_EASEOUT: 11,
    QUART_EASEINOUT: 12,

    QUINT_EASEIN: 13,
    QUINT_EASEOUT: 14,
    QUINT_EASEINOUT: 15,

    EXPO_EASEIN: 16,
    EXPO_EASEOUT: 17,
    EXPO_EASEINOUT: 18,

    CIRC_EASEIN: 19,
    CIRC_EASEOUT: 20,
    CIRC_EASEINOUT: 21,

    ELASTIC_EASEIN: 22,
    ELASTIC_EASEOUT: 23,
    ELASTIC_EASEINOUT: 24,

    BACK_EASEIN: 25,
    BACK_EASEOUT: 26,
    BACK_EASEINOUT: 27,

    BOUNCE_EASEIN: 28,
    BOUNCE_EASEOUT: 29,
    BOUNCE_EASEINOUT: 30,

    TWEEN_EASING_MAX: 10000
};

ccs.FrameEaseType = {
    CUSTOM : -1,

    LINEAR : 0,

    SINE_EASEIN : 1,
    SINE_EASEOUT : 2,
    SINE_EASEINOUT : 3,

    QUAD_EASEIN : 4,
    QUAD_EASEOUT : 5,
    QUAD_EASEINOUT : 6,

    CUBIC_EASEIN : 7,
    CUBIC_EASEOUT : 8,
    CUBIC_EASEINOUT : 9,

    QUART_EASEIN : 10,
    QUART_EASEOUT : 11,
    QUART_EASEINOUT : 12,

    QUINT_EASEIN : 13,
    QUINT_EASEOUT : 14,
    QUINT_EASEINOUT : 15,

    EXPO_EASEIN : 16,
    EXPO_EASEOUT : 17,
    EXPO_EASEINOUT : 18,

    CIRC_EASEIN : 19,
    CIRC_EASEOUT : 20,
    CIRC_EASEINOUT : 21,

    ELASTIC_EASEIN : 22,
    ELASTIC_EASEOUT : 23,
    ELASTIC_EASEINOUT : 24,

    BACK_EASEIN : 25,
    BACK_EASEOUT : 26,
    BACK_EASEINOUT : 27,

    BOUNCE_EASEIN : 28,
    BOUNCE_EASEOUT : 29,
    BOUNCE_EASEINOUT : 30,

    TWEEN_EASING_MAX: 1000
};
