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
var CEHCK_BOX_INDEX = 0;

var UICheckBoxEditorTest = UIBaseLayer.extend({
    ctor: function () {
        this._super();
        var left_button = new ccui.Button();
        left_button.loadTextures("Images/b1.png", "Images/b2.png", "");
        left_button.x = 240-50;
        left_button.y = 50;
        left_button.anchorX = 0.5;
        left_button.anchorY = 0.5;
        left_button.addTouchEventListener(this.previousCallback, this);
        this._mainNode.addChild(left_button, 999);

        var right_button = new ccui.Button();
        right_button.loadTextures("Images/f1.png", "Images/f2.png", "");
        right_button.x = 240+50;
        right_button.y = 50;
        right_button.anchorX = 0.5;
        right_button.anchorY = 0.5;
        right_button.addTouchEventListener(this.nextCallback, this);
        this._mainNode.addChild(right_button, 999);
    },
    previousCallback: function (render, type) {
        if (type == ccui.Widget.TOUCH_ENDED) {
            CEHCK_BOX_INDEX--;
            if (CEHCK_BOX_INDEX < 0)CEHCK_BOX_INDEX = CEHCK_BOX_SCENE.length-1;
            if (CEHCK_BOX_INDEX >= CEHCK_BOX_SCENE.length)CEHCK_BOX_INDEX = 0;
            this.runNextScene();
        }
    },
    nextCallback: function (render, type) {
        if (type == ccui.Widget.TOUCH_ENDED) {
            CEHCK_BOX_INDEX++;
            if (CEHCK_BOX_INDEX < 0)CEHCK_BOX_INDEX = CEHCK_BOX_SCENE.length-1;
            if (CEHCK_BOX_INDEX >= CEHCK_BOX_SCENE.length)CEHCK_BOX_INDEX = 0;
            this.runNextScene();
        }
    },
    runNextScene: function () {
        var scene = new cc.Scene();
        scene.addChild(new CEHCK_BOX_SCENE[CEHCK_BOX_INDEX]());
        cc.director.runScene(scene);
    },

    selectedStateEvent: function (sender, type) {
        switch (type) {
            case ccui.CheckBox.EVENT_SELECTED:
                this._topDisplayText.setString("Selected");
                break;
            case ccui.CheckBox.EVENT_UNSELECTED:
                this._topDisplayText.setString("Unselected");
                break;

            default:
                break;
        }
    }
});

var UICheckBoxOldTest = UICheckBoxEditorTest.extend({
    ctor: function () {
        this._super();
        var root = this._parseUIFile("ccs-res/cocosui/UIEditorTest/UICheckBox/checkbox_1.json");
        this._mainNode.addChild(root);

        var back_label =ccui.helper.seekWidgetByName(root, "back");
        back_label.addTouchEventListener(this.backEvent,this);

        var checkbox = ccui.helper.seekWidgetByName(root, "CheckBox_540");
        checkbox.addEventListener(this.selectedStateEvent,this);
    }
});

var UICheckBoxNewTest = UICheckBoxEditorTest.extend({
    ctor: function () {
        this._super();
        var root = ccs.load("ccs-res/cocosui/UIEditorTest/UICheckBox/MainScene.json");
        this._mainNode.addChild(root.node);
        var checkbox = ccui.helper.seekWidgetByName(root.node, "CheckBox_1");
        checkbox.addEventListener(this.selectedStateEvent,this);
    }
});

var CEHCK_BOX_SCENE = [
    UICheckBoxOldTest,
    UICheckBoxNewTest
];
