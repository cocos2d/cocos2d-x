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
 * @class
 * @extends cc.Class
 * @example
 * var element = new cc.HashElement();
 */
cc.HashElement = cc.Class.extend(/** @lends cc.HashElement# */{
    actions:null,
    target:null, //ccobject
    actionIndex:0,
    currentAction:null, //CCAction
    currentActionSalvaged:false,
    paused:false,
    hh:null, //ut hash handle
    /**
     * Constructor
     */
    ctor:function () {
        this.actions = [];
        this.target = null;
        this.actionIndex = 0;
        this.currentAction = null; //CCAction
        this.currentActionSalvaged = false;
        this.paused = false;
        this.hh = null; //ut hash handle
    }
});

/**
 * cc.ActionManager is a class that can manage actions.<br/>
 * Normally you won't need to use this class directly. 99% of the cases you will use the CCNode interface,
 * which uses this class's singleton object.
 * But there are some cases where you might need to use this class. <br/>
 * Examples:<br/>
 * - When you want to run an action where the target is different from a CCNode.<br/>
 * - When you want to pause / resume the actions<br/>
 * @class
 * @extends cc.Class
 * @example
 * var mng = new cc.ActionManager();
 */
cc.ActionManager = cc.Class.extend(/** @lends cc.ActionManager# */{
    _hashTargets:null,
    _arrayTargets:null,
    _currentTarget:null,
    _currentTargetSalvaged:false,

    _searchElementByTarget:function (arr, target) {
        for (var k = 0; k < arr.length; k++) {
            if (target === arr[k].target)
                return arr[k];
        }
        return null;
    },

    ctor:function () {
        this._hashTargets = {};
        this._arrayTargets = [];
        this._currentTarget = null;
        this._currentTargetSalvaged = false;
    },

    /** Adds an action with a target.
     * If the target is already present, then the action will be added to the existing target.
     * If the target is not present, a new instance of this target will be created either paused or not, and the action will be added to the newly created target.
     * When the target is paused, the queued actions won't be 'ticked'.
     * @param {cc.Action} action
     * @param {cc.Node} target
     * @param {Boolean} paused
     */
    addAction:function (action, target, paused) {
        if(!action)
            throw "cc.ActionManager.addAction(): action must be non-null";
        if(!target)
            throw "cc.ActionManager.addAction(): action must be non-null";

        //check if the action target already exists
        var element = this._hashTargets[target.__instanceId];
        //if doesnt exists, create a hashelement and push in mpTargets
        if (!element) {
            element = new cc.HashElement();
            element.paused = paused;
            element.target = target;
            this._hashTargets[target.__instanceId] = element;
            this._arrayTargets.push(element);
        }
        //creates a array for that eleemnt to hold the actions
        this._actionAllocWithHashElement(element);

        element.actions.push(action);
        action.startWithTarget(target);
    },

    /**
     * Removes all actions from all the targets.
     */
    removeAllActions:function () {
        var locTargets = this._arrayTargets;
        for (var i = 0; i < locTargets.length; i++) {
            var element = locTargets[i];
            if (element)
                this.removeAllActionsFromTarget(element.target, true);
        }
    },
    /** Removes all actions from a certain target. <br/>
     * All the actions that belongs to the target will be removed.
     * @param {object} target
     * @param {boolean} forceDelete
     */
    removeAllActionsFromTarget:function (target, forceDelete) {
        // explicit null handling
        if (target == null)
            return;
        var element = this._hashTargets[target.__instanceId];
        if (element) {
            if (element.actions.indexOf(element.currentAction) !== -1 && !(element.currentActionSalvaged))
                element.currentActionSalvaged = true;

            element.actions.length = 0;
            if (this._currentTarget === element && !forceDelete) {
                this._currentTargetSalvaged = true;
            } else {
                this._deleteHashElement(element);
            }
        }
    },
    /** Removes an action given an action reference.
     * @param {cc.Action} action
     */
    removeAction:function (action) {
        // explicit null handling
        if (action == null)
            return;
        var target = action.getOriginalTarget();
        var element = this._hashTargets[target.__instanceId];

        if (element) {
            for (var i = 0; i < element.actions.length; i++) {
                if (element.actions[i] === action) {
                    element.actions.splice(i, 1);
                    break;
                }
            }
        } else {
            cc.log(cc._LogInfos.ActionManager_removeAction);
        }
    },

    /** Removes an action given its tag and the target
     * @param {Number} tag
     * @param {object} target
     */
    removeActionByTag:function (tag, target) {
        if(tag === cc.ACTION_TAG_INVALID)
            cc.log(cc._LogInfos.ActionManager_addAction);

        cc.assert(target, cc._LogInfos.ActionManager_addAction);

        var element = this._hashTargets[target.__instanceId];

        if (element) {
            var limit = element.actions.length;
            for (var i = 0; i < limit; ++i) {
                var action = element.actions[i];
                if (action && action.getTag() === tag && action.getOriginalTarget() === target) {
                    this._removeActionAtIndex(i, element);
                    break;
                }
            }
        }
    },

    /** Gets an action given its tag an a target
     * @param {Number} tag
     * @param {object} target
     * @return {cc.Action|Null}  return the Action with the given tag on success
     */
    getActionByTag:function (tag, target) {
        if(tag === cc.ACTION_TAG_INVALID)
            cc.log(cc._LogInfos.ActionManager_getActionByTag);

        var element = this._hashTargets[target.__instanceId];
        if (element) {
            if (element.actions != null) {
                for (var i = 0; i < element.actions.length; ++i) {
                    var action = element.actions[i];
                    if (action && action.getTag() === tag)
                        return action;
                }
            }
            cc.log(cc._LogInfos.ActionManager_getActionByTag_2, tag);
        }
        return null;
    },


    /** Returns the numbers of actions that are running in a certain target. <br/>
     * Composable actions are counted as 1 action. <br/>
     * Example: <br/>
     * - If you are running 1 Sequence of 7 actions, it will return 1. <br/>
     * - If you are running 7 Sequences of 2 actions, it will return 7.
     * @param {object} target
     * @return {Number}
     */
    numberOfRunningActionsInTarget:function (target) {
        var element = this._hashTargets[target.__instanceId];
        if (element)
            return (element.actions) ? element.actions.length : 0;

        return 0;
    },
    /** Pauses the target: all running actions and newly added actions will be paused.
     * @param {object} target
     */
    pauseTarget:function (target) {
        var element = this._hashTargets[target.__instanceId];
        if (element)
            element.paused = true;
    },
    /** Resumes the target. All queued actions will be resumed.
     * @param {object} target
     */
    resumeTarget:function (target) {
        var element = this._hashTargets[target.__instanceId];
        if (element)
            element.paused = false;
    },

    /**
     * Pauses all running actions, returning a list of targets whose actions were paused.
     * @return {Array}  a list of targets whose actions were paused.
     */
    pauseAllRunningActions:function(){
        var idsWithActions = [];
        var locTargets = this._arrayTargets;
        for(var i = 0; i< locTargets.length; i++){
            var element = locTargets[i];
            if(element && !element.paused){
                element.paused = true;
                idsWithActions.push(element.target);
            }
        }
        return idsWithActions;
    },

    /**
     * Resume a set of targets (convenience function to reverse a pauseAllRunningActions call)
     * @param {Array} targetsToResume
     */
    resumeTargets:function(targetsToResume){
        if(!targetsToResume)
            return;

        for(var i = 0 ; i< targetsToResume.length; i++){
            if(targetsToResume[i])
                this.resumeTarget(targetsToResume[i]);
        }
    },

    /** purges the shared action manager. It releases the retained instance. <br/>
     * because it uses this, so it can not be static
     */
    purgeSharedManager:function () {
        cc.director.getScheduler().unscheduleUpdate(this);
    },

    //protected
    _removeActionAtIndex:function (index, element) {
        var action = element.actions[index];

        if ((action === element.currentAction) && (!element.currentActionSalvaged))
            element.currentActionSalvaged = true;

        element.actions.splice(index, 1);

        // update actionIndex in case we are in tick. looping over the actions
        if (element.actionIndex >= index)
            element.actionIndex--;

        if (element.actions.length === 0) {
            if (this._currentTarget === element) {
                this._currentTargetSalvaged = true;
            } else {
                this._deleteHashElement(element);
            }
        }
    },

    _deleteHashElement:function (element) {
        if (element) {
            delete this._hashTargets[element.target.__instanceId];
            cc.arrayRemoveObject(this._arrayTargets, element);
            element.actions = null;
            element.target = null;
        }
    },

    _actionAllocWithHashElement:function (element) {
        // 4 actions per Node by default
        if (element.actions == null) {
            element.actions = [];
        }
    },

    /**
     * @param {Number} dt delta time in seconds
     */
    update:function (dt) {
        var locTargets = this._arrayTargets , locCurrTarget;
        for (var elt = 0; elt < locTargets.length; elt++) {
            this._currentTarget = locTargets[elt];
            locCurrTarget = this._currentTarget;
            //this._currentTargetSalvaged = false;
            if (!locCurrTarget.paused) {
                // The 'actions' CCMutableArray may change while inside this loop.
                for (locCurrTarget.actionIndex = 0;
                     locCurrTarget.actionIndex < (locCurrTarget.actions ? locCurrTarget.actions.length : 0);
                     locCurrTarget.actionIndex++) {
                    locCurrTarget.currentAction = locCurrTarget.actions[locCurrTarget.actionIndex];
                    if (!locCurrTarget.currentAction)
                        continue;

                    locCurrTarget.currentActionSalvaged = false;
                    //use for speed
                    locCurrTarget.currentAction.step(dt * ( locCurrTarget.currentAction._speedMethod ? locCurrTarget.currentAction._speed : 1 ) );
                    if (locCurrTarget.currentActionSalvaged) {
                        // The currentAction told the node to remove it. To prevent the action from
                        // accidentally deallocating itself before finishing its step, we retained
                        // it. Now that step is done, it's safe to release it.
                        locCurrTarget.currentAction = null;//release
                    } else if (locCurrTarget.currentAction.isDone()) {
                        locCurrTarget.currentAction.stop();
                        var action = locCurrTarget.currentAction;
                        // Make currentAction nil to prevent removeAction from salvaging it.
                        locCurrTarget.currentAction = null;
                        this.removeAction(action);
                    }

                    locCurrTarget.currentAction = null;
                }
            }

            // elt, at this moment, is still valid
            // so it is safe to ask this here (issue #490)

            // only delete currentTarget if no actions were scheduled during the cycle (issue #481)
            if (this._currentTargetSalvaged && locCurrTarget.actions.length === 0) {
                this._deleteHashElement(locCurrTarget);
            }
        }
    }
});
