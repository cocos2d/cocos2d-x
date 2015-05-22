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
 * Base singleton object for ccs.ActionManager.
 * @class
 * @name ccs.actionManager
 */
ccs.actionManager = /** @lends ccs.actionManager# */{
    _actionDic: {},

    /**
     * Init properties with json dictionary
     * @param {String} jsonName
     * @param {Object} dic
     * @param {Object} root
     */
    initWithDictionary: function (jsonName, dic, root) {
        var path = jsonName;
        var pos = path.lastIndexOf("/");
        var fileName = path.substr(pos + 1, path.length);
        var actionList = dic["actionlist"];
        var locActionList = [];
        for (var i = 0; i < actionList.length; i++) {
            var locAction = new ccs.ActionObject();
            var locActionDic = actionList[i];
            locAction.initWithDictionary(locActionDic, root);
            locActionList.push(locAction);
        }
        this._actionDic[fileName] = locActionList;
    },

    /**
     * Gets an actionObject with a name.
     * @param {String} jsonName
     * @param {String} actionName
     * @returns {ccs.ActionObject}
     */
    getActionByName: function (jsonName, actionName) {
        var path = jsonName;
        var pos = path.lastIndexOf("/");
        var fileName = path.substr(pos + 1, path.length);
        var actionList = this._actionDic[fileName];
        if (!actionList)
            return null;
        for (var i = 0; i < actionList.length; i++) {
            var locAction = actionList[i];
            if (actionName === locAction.getName())
                return locAction;
        }
        return null;
    },

    /**
     * Play an Action with a name.
     * @param {String} jsonName
     * @param {String} actionName
     * @param {cc.CallFunc} fun
     */
    playActionByName: function (jsonName, actionName, fun) {
        var action = this.getActionByName(jsonName, actionName);
        if (action)
            action.play(fun);
    },
    
     /**
     * Stop an Action with a name.
     * @param {String} jsonName
     * @param {String} actionName
     */
    stopActionByName: function (jsonName, actionName) {
        var action = this.getActionByName(jsonName, actionName);
        if (action)
            action.stop();
    },

    /**
     * Release all actions.
     */
    releaseActions: function () {
        this._actionDic = {};
    },

	/**
	 * Clear data: Release all actions.
	 */
	clear: function() {
		this._actionDic = {};
	}
};
