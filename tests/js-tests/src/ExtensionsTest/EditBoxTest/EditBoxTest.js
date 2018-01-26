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

var EditBoxTestLayer = cc.Layer.extend({
    _box1: null,
    _box2: null,
    _box3: null,
    _box4: null,

    ctor: function () {
        this._super();
        cc.associateWithNative(this, cc.Layer);
        this.init();
    },

    init: function () {
        this._box1 = new cc.EditBox(cc.size(170, 50), new cc.Scale9Sprite("extensions/green_edit.png"), new cc.Scale9Sprite("extensions/orange_edit.png"));
        this._box1.setString("EditBoxs");
        this._box1.x = 220;
        this._box1.y = 50;
        this._box1.setFontColor(cc.color(251, 250, 0));
        this._box1.setDelegate(this);
        this.addChild(this._box1);

        this._box2 = new cc.EditBox(cc.size(130, 50), new cc.Scale9Sprite("extensions/green_edit.png"));
        this._box2.setString("EditBox Sample");
        this._box2.x = 220;
        this._box2.y = 190;
        this._box2.setInputFlag(cc.EDITBOX_INPUT_FLAG_PASSWORD);
        this._box2.setFontColor(cc.color(255, 250, 0));
        this._box2.setPlaceHolder("please enter password");
        this._box2.setPlaceholderFontColor(cc.color(255, 255, 255));
        this._box2.setDelegate(this);
        this.addChild(this._box2);

        this._box3 = new cc.EditBox(cc.size(65, 50), new cc.Scale9Sprite("extensions/orange_edit.png"));
        this._box3.setString("Image");
        this._box3.x = 220;
        this._box3.y = 250;
        this._box3.setFontColor(cc.color(15, 250, 245));
        this._box3.setDelegate(this);
        this._box3.setTouchEnabled(false);
        this._box3.setTouchEnabled(true);
        this.addChild(this._box3);

        this._box4 = new cc.EditBox(cc.size(180, 50), new cc.Scale9Sprite("extensions/yellow_edit.png"));
        this._box4.setPlaceholderFontColor(cc.color(255, 0, 0));
        this._box4.setPlaceHolder("This editBox can't be touched!");
        this._box4.x = 40;
        this._box4.y = -100;
        this._box4.setDelegate(this);
        this._box4.setFontColor(cc.color(5, 4, 10));
        this._box4.setMaxLength(10);
        this._box4.setTouchEnabled(false);
        this._box3.addChild(this._box4);

        var itemBack = new cc.MenuItemFont("Back", this.toExtensionsMainLayer, this);
        itemBack.x = winSize.width - 50;
        itemBack.y = 25;
        var menuBack = new cc.Menu(itemBack);
        menuBack.x = 0;
        menuBack.y = 0;
        this.addChild(menuBack);

        return true;
    },

    toExtensionsMainLayer: function (sender) {
        var scene = new ExtensionsTestScene();
        scene.runThisTest();
    },

    editBoxEditingDidBegin: function (editBox) {
        cc.log("editBox " + this._getEditBoxName(editBox) + " DidBegin !");
    },

    editBoxEditingDidEnd: function (editBox) {
        cc.log("editBox " + this._getEditBoxName(editBox) + " DidEnd !");
    },

    editBoxTextChanged: function (editBox, text) {
        cc.log("editBox " + this._getEditBoxName(editBox) + ", TextChanged, text: " + text);
    },

    editBoxReturn: function (editBox) {
        cc.log("editBox " + this._getEditBoxName(editBox) + " was returned !");
    },

    _getEditBoxName :function(editBox){
        if (this._box1 == editBox) {
            return "box1";
        } else if (this._box2 == editBox) {
            return "box2";
        } else if (this._box3 == editBox) {
            return "box3";
        } else if (this._box4 == editBox) {
            return "box4";
        }
        return "Unknown EditBox";
    }
});

var runEditBoxTest = function () {
    var pScene = new cc.Scene();
    var pLayer = new EditBoxTestLayer();
    pScene.addChild(pLayer);
	cc.director.runScene(pScene);
};
