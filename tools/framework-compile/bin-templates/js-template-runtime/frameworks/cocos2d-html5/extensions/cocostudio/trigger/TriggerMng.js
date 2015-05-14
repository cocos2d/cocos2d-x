/****************************************************************************
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

/**
 * The trigger manager of Cocostudio
 * @class
 * @name ccs.triggerManager
 */
ccs.triggerManager = /** @lends ccs.triggerManager# */{
    _eventTriggers: {},
    _triggerObjs: {},
    _movementDispatches: [],

    /**
     * Parses the triggers.
     * @param {Array} triggers
     */
    parse: function (triggers) {
        for (var i = 0; i < triggers.length; ++i) {
            var subDict = triggers[i];
            var triggerObj = new ccs.TriggerObj();
            triggerObj.serialize(subDict);
            var events = triggerObj.getEvents();
            for (var j = 0; j < events.length; j++) {
                var event = events[j];
                this.add(event, triggerObj);
            }
            this._triggerObjs[triggerObj.getId()] = triggerObj;
        }
    },

    /**
     * Returns the event triggers by event id.
     * @param {Number} event
     * @returns {Array}
     */
    get: function (event) {
        return this._eventTriggers[event];
    },

    /**
     * Returns the trigger object by id
     * @param {Number} id
     * @returns {ccs.TriggerObj}
     */
    getTriggerObj: function (id) {
        return this._triggerObjs[id];
    },

    /**
     * Adds event and trigger object to trigger manager.
     * @param event
     * @param triggerObj
     */
    add: function (event, triggerObj) {
        var eventTriggers = this._eventTriggers[event];
        if (!eventTriggers)
            eventTriggers = [];
        if (eventTriggers.indexOf(triggerObj) === -1) {
            eventTriggers.push(triggerObj);
            this._eventTriggers[event] = eventTriggers;
        }
    },

    /**
     * Removes all event triggers from manager.
     */
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

    /**
     * Removes event object from trigger manager.
     * @param {*} event
     * @param {*} Obj
     * @returns {Boolean}
     */
    remove: function (event, Obj) {
        if (Obj)
            return this._removeObj(event, Obj);

        var bRet = false;
        do {
            var triObjects = this._eventTriggers[event];
            if (!triObjects)
                break;
            for (var i = 0; i < triObjects.length; i++) {
                var triObject = triObjects[i];
                if (triObject)
                    triObject.removeAll();
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

    /**
     * Removes trigger object from manager
     * @param {Number} id
     * @returns {boolean}
     */
    removeTriggerObj: function (id) {
        var obj = this.getTriggerObj(id);
        if (!obj)
            return false;
        var events = obj.getEvents();
        for (var i = 0; i < events.length; i++) {
            var event = events[i];
            this.remove(event, obj);
        }
        return true;
    },

    /**
     * Returns the event triggers whether is empty.
     * @returns {boolean}
     */
    isEmpty: function () {
        return !this._eventTriggers || this._eventTriggers.length <= 0;
    },

    /**
     * Adds an armature movement callback to manager.
     * @param {ccs.Armature} armature
     * @param {function} callFunc
     * @param {Object} target
     */
    addArmatureMovementCallBack: function (armature, callFunc, target) {
        if (armature == null || target == null || callFunc == null)
            return;
        var locAmd, hasADD = false;
        for (var i = 0; i < this._movementDispatches.length; i++) {
            locAmd = this._movementDispatches[i];
            if (locAmd && locAmd[0] === armature) {
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

    /**
     * Removes armature movement callback from manager.
     * @param {ccs.Armature} armature
     * @param {Object} target
     * @param {function} callFunc
     */
    removeArmatureMovementCallBack: function (armature, target, callFunc) {
        if (armature == null || target == null || callFunc == null)
            return;
        var locAmd;
        for (var i = 0; i < this._movementDispatches.length; i++) {
            locAmd = this._movementDispatches[i];
            if (locAmd && locAmd[0] === armature)
                locAmd.removeAnimationEventCallBack(callFunc, target);
        }
    },

    /**
     * Removes an armature's all movement callbacks.
     * @param {ccs.Armature} armature
     */
    removeArmatureAllMovementCallBack: function (armature) {
        if (armature == null)
            return;
        var locAmd;
        for (var i = 0; i < this._movementDispatches.length; i++) {
            locAmd = this._movementDispatches[i];
            if (locAmd && locAmd[0] === armature) {
                this._movementDispatches.splice(i, 1);
                break;
            }
        }
    },

    /**
     * Removes all armature movement callbacks from ccs.triggerManager.
     */
    removeAllArmatureMovementCallBack: function () {
        this._movementDispatches.length = 0;
    },

    /**
     * Returns the version of ccs.triggerManager
     * @returns {string}
     */
	version: function () {
		return "1.2.0.0";
	}
};

/**
 * The armature movement dispatcher for trigger manager.
 * @class
 * @extends ccs.Class
 */
ccs.ArmatureMovementDispatcher = ccs.Class.extend(/** @lends ccs.ArmatureMovementDispatcher# */{
    _mapEventAnimation: null,

    /**
     * Constructor of ArmatureMovementDispatcher.
     */
    ctor: function () {
        this._mapEventAnimation = [];
    },

    /**
     * Calls armature movement events.
     * @param {ccs.Armature} armature
     * @param {Number} movementType
     * @param {String} movementID
     */
    animationEvent: function (armature, movementType, movementID) {
        var locEventAni, locTarget, locFunc;
        for (var i = 0; i < this._mapEventAnimation.length; i++) {
            locEventAni = this._mapEventAnimation[i];
            locTarget = locEventAni[0];
            locFunc = locEventAni[1];
            if (locFunc)
                locFunc.call(locTarget, armature, movementType, movementID);
        }
    },

    /**
     * Adds animation event callback to event animation list
     * @param {function} callFunc
     * @param {Object|null} [target]
     */
    addAnimationEventCallBack: function (callFunc, target) {
        this._mapEventAnimation.push([target, callFunc]);
    },

    /**
     * Removes animation event callback from trigger manager.
     * @param {function} callFunc
     * @param {Object|null} [target]
     */
    removeAnimationEventCallBack: function (callFunc, target) {
        var locEventAni;
        for (var i = 0; i < this._mapEventAnimation.length; i++) {
            locEventAni = this._mapEventAnimation[i];
            if (locEventAni[0] === target) {
                this._mapEventAnimation.splice(i, 1);
            }
        }
    }
});