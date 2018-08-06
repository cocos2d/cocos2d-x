/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

var controTestItemNames = [
    {
        itemTitle:"ControlSliderTest",
        testScene:function () {
            return ControlSliderTest.create(this.itemTitle);
        }
    },
    {
        itemTitle:"ControlColourPickerTest",
        testScene:function () {
            return ControlColourPickerTest.create(this.itemTitle);
        }
    },
    {
        itemTitle:"ControlSwitchTest",
        testScene:function () {
            return ControlSwitchTest.create(this.itemTitle);
        }
    },
    {
        itemTitle:"ControlButtonTest_HelloVariableSize",
        testScene:function () {
            return ControlButtonTest_HelloVariableSize.create(this.itemTitle);
        }
    },
    {
        itemTitle:"ControlButtonTest_Event",
        testScene:function () {
            return ControlButtonTest_Event.create(this.itemTitle);
        }
    },
    {
        itemTitle:"ControlButtonTest_Styling",
        testScene:function () {
            return ControlButtonTest_Styling.create(this.itemTitle);
        }
    },
    {
        itemTitle:"ControlPotentiometerTest",
        testScene:function () {
            return ControlPotentiometerTest.create(this.itemTitle);
        }
    },
    {
        itemTitle:"ControlStepperTest",
        testScene:function () {
            return ControlStepperTest.create(this.itemTitle);
        }
    }
];

var ControlSceneManager = cc.Class.extend({
    _currentControlSceneId:0,

    ctor:function () {
        this._currentControlSceneId = 0;
    },

    getCurrentControlSceneId:function () {
        return this._currentControlSceneId;
    },
    setCurrentControlSceneId:function (currentControlSceneId) {
        this._currentControlSceneId = currentControlSceneId
    },

    nextControlScene:function () {
        this._currentControlSceneId = (this._currentControlSceneId + 1) % controTestItemNames.length;
        return this.currentControlScene();
    },

    previousControlScene:function () {
        this._currentControlSceneId = this._currentControlSceneId - 1;
        if (this._currentControlSceneId < 0) {
            this._currentControlSceneId = controTestItemNames.length - 1;
        }

        return this.currentControlScene();
    },

    currentControlScene:function () {
        return controTestItemNames[this._currentControlSceneId].testScene();
    }
});

ControlSceneManager.sharedInstance = null;
/**
 * Returns the singleton of the control scene manager.
 */
ControlSceneManager.getInstance = function () {
    if (ControlSceneManager.sharedInstance == null) {
        ControlSceneManager.sharedInstance = new ControlSceneManager();
    }
    return ControlSceneManager.sharedInstance;
};
