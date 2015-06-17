/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
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
 * <p>
 *  cc.pool is a singleton object serves as an object cache pool.<br/>
 *  It can helps you to improve your game performance for objects which need frequent release and recreate operations<br/>
 *  Some common use case is :
 *      1. Bullets in game (die very soon, massive creation and recreation, no side effect on other objects)
 *      2. Blocks in candy crash (massive creation and recreation)
 *      etc...
 * </p>
 *
 * @example
 * var sp = new cc.Sprite("a.png");
 * this.addChild(sp);
 * cc.pool.putInPool(sp);
 *
 * cc.pool.getFromPool(cc.Sprite, "a.png");
 * @class
 * @name cc.pool
 */
cc.pool = /** @lends cc.pool# */{
    _pool: {},

    _releaseCB: function () {
        this.release();
    },

    _autoRelease: function (obj) {
        var running = obj._running === undefined ? false : !obj._running;
        cc.director.getScheduler().scheduleCallbackForTarget(obj, this._releaseCB, 0, 0, 0, running)
    },

    /**
     * Put the obj in pool
     * @param obj
     */
    putInPool: function (obj) {
        var pid = obj.constructor.prototype.__pid;
        if (!pid) {
            var desc = { writable: true, enumerable: false, configurable: true };
            desc.value = ClassManager.getNewID();
            Object.defineProperty(obj.constructor.prototype, '__pid', desc);
        }
        if (!this._pool[pid]) {
            this._pool[pid] = [];
        }
        // JSB retain to avoid being auto released
        obj.retain && obj.retain();
        // User implementation for disable the object
        obj.unuse && obj.unuse();
        this._pool[pid].push(obj);
    },

    /**
     * Check if this kind of obj has already in pool
     * @param objClass
     * @returns {boolean} if this kind of obj is already in pool return true,else return false;
     */
    hasObject: function (objClass) {
        var pid = objClass.prototype.__pid;
        var list = this._pool[pid];
        if (!list || list.length == 0) {
            return false;
        }
        return true;
    },

    /**
     * Remove the obj if you want to delete it;
     * @param obj
     */
    removeObject: function (obj) {
        var pid = obj.constructor.prototype.__pid;
        if (pid) {
            var list = this._pool[pid];
            if (list) {
                for (var i = 0; i < list.length; i++) {
                    if (obj === list[i]) {
                        // JSB release to avoid memory leak
                        obj.release && obj.release();
                        list.splice(i, 1);
                    }
                }
            }
        }
    },

    /**
     * Get the obj from pool
     * @param args
     * @returns {*} call the reuse function an return the obj
     */
    getFromPool: function (objClass/*,args*/) {
        if (this.hasObject(objClass)) {
            var pid = objClass.prototype.__pid;
            var list = this._pool[pid];
            var args = Array.prototype.slice.call(arguments);
            args.shift();
            var obj = list.pop();
            // User implementation for re-enable the object
            obj.reuse && obj.reuse.apply(obj, args);
            // JSB release to avoid memory leak
            cc.sys.isNative && obj.release && this._autoRelease(obj);
            return obj;
        }
    },

    /**
     *  remove all objs in pool and reset the pool
     */
    drainAllPools: function () {
        for (var i in this._pool) {
            for (var j = 0; j < this._pool[i].length; j++) {
                var obj = this._pool[i][j];
                // JSB release to avoid memory leak
                obj.release && obj.release();
            }
        }
        this._pool = {};
    }
};