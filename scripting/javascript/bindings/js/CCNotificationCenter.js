/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011      Zynga Inc.

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

cc.s_sharedNotificationCenter = null;

cc.NotificationCenter = cc.Class.extend({
    ctor:function() {
        this._observers = [];
    },

    /**
     * @param {cc.Class} target
     * @param {String} selector
     * @param {String} name
     * @param {cc.Class} obj
     */
    addObserver:function(target, selector, name, obj) {
        if (this._observerExisted(target, name))
            return;

        var observer = new cc.NotificationObserver(target, selector, name, obj);
        if (!observer)
            return;

        this._observers.push(observer);
    },

    /**
     * Removes the observer by the specified target and name.
     * @param {cc.Class} target
     * @param {String} name
     */
    removeObserver:function(target, name) {
        for (var i = 0; i < this._observers.length; i++) {
            var observer = this._observers[i];
            if (!observer)
                continue;
            if (observer.getName() == name && observer.getTarget() == target) {
                this._observers.splice(i, 1);
                return;
            }
        }
    },

    /**
     * Removes all notifications registered by this target
     * @param {cc.Class} target  The target of this notification.
     * @returns {number} the number of observers removed
     */
    removeAllObservers:function(target){
        var removes = [];
        for(var i = 0; i< this._observers.length;i++){
            var selObserver = this._observers[i];
            if(selObserver.getTarget() == target)
                removes.push(selObserver);
        }
        cc.ArrayRemoveArray(this._observers, removes);
        return removes.length;
    },

    /**
     * @param {String} name
     * @param {cc.Class} object
     */
    postNotification:function(name, object) {
        for (var i = 0; i < this._observers.length; i++) {
            var observer = this._observers[i];
            if (!observer)
                continue;
            if (observer.getName() == name)
                observer.performSelector(object);
        }
    },

    /**
     * @param {cc.Class} target
     * @param {String} name
     * @return {Boolean}
     * @private
     */
    _observerExisted:function(target, name) {
        for (var i = 0; i < this._observers.length; i++)
        {
            var observer = this._observers[i];
            if (!observer)
                continue;
            if (observer.getName() == name && observer.getTarget() == target)
                return true;
        }
        return false;
    },
    _observers:null
});

/**
 * @return {cc.NotificationCenter}
 */
cc.NotificationCenter.getInstance = function() {
    if (!cc.s_sharedNotificationCenter) {
        cc.s_sharedNotificationCenter = new cc.NotificationCenter();
    }
    return cc.s_sharedNotificationCenter;
};

cc.NotificationObserver = cc.Class.extend({
    /**
     * @param {cc.Class} target
     * @param {String} selector
     * @param {String} name
     * @param {cc.Class} obj
     */
    ctor:function (target, selector, name, obj) {
        this._target = target;
        this._selector = selector;
        this._name = name;
        this._object = obj;
    },

    /**
     * @param {cc.Class} obj
     */
    performSelector:function (obj) {
        cc.doCallback(this._selector, this._target,obj);
    },

    _target:null,
    _selector:null,
    _name:null,
    _object:null,

    /**
     * @return {cc.Class}
     */
    getTarget:function () {
        return this._target;
    },

    /**
     * @return {String}
     */
    getSelector:function () {
        return this._selector;
    },

    /**
     * @return {String}
     */
    getName:function () {
        return this._name;
    },

    /**
     * @return {cc.Class}
     */
    getObject:function () {
        return this._object;
    }
});