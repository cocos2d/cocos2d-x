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

var TEXT_INPUT_FONT_NAME = "Thonburi";
var TEXT_INPUT_FONT_SIZE = 36;

var sceneIdx = -1;

var textInputGetRect = function (node) {
    var rc = cc.rect(node.x, node.y, node.width, node.height);
    rc.x -= rc.width / 2;
    rc.y -= rc.height / 2;
    return rc;
};

/**
 @brief    TextInputTest for retain prev, reset, next, main menu buttons.
 */
var TextInputTest = cc.Layer.extend({
    notificationLayer:null,
    ctor:function() {
        this._super();
        this.init();
    },

    restartCallback:function (sender) {
        var scene = new TextInputTestScene();
        scene.addChild(restartTextInputTest());
        cc.director.runScene(scene);
    },
    nextCallback:function (sender) {
        var scene = new TextInputTestScene();
        scene.addChild(nextTextInputTest());
        cc.director.runScene(scene);
    },
    backCallback:function (sender) {
        var scene = new TextInputTestScene();
        scene.addChild(previousTextInputTest());
        cc.director.runScene(scene);
    },

    title:function () {
        return "text input test";
    },

    addKeyboardNotificationLayer:function (layer) {
        this.notificationLayer = layer;
        this.addChild(layer);
    },

    onEnter:function () {
        this._super();

        var winSize = cc.director.getWinSize();

        var label = new cc.LabelTTF(this.title(), "Arial", 24);
        this.addChild(label);
        label.x = winSize.width / 2;
        label.y = winSize.height - 50;

        var subTitle = this.subtitle();
        if (subTitle && subTitle !== "") {
            var l = new cc.LabelTTF(subTitle, "Thonburi", 16);
            this.addChild(l, 1);
            l.x = winSize.width / 2;
            l.y = winSize.height - 80;
        }

        var item1 = new cc.MenuItemImage(s_pathB1, s_pathB2, this.backCallback, this);
        var item2 = new cc.MenuItemImage(s_pathR1, s_pathR2, this.restartCallback, this);
        var item3 = new cc.MenuItemImage(s_pathF1, s_pathF2, this.nextCallback, this);

        var menu = new cc.Menu(item1, item2, item3);
        menu.x = 0;
        menu.y = 0;
        item1.x = winSize.width / 2 - 100;
        item1.y = 30;
        item2.x = winSize.width / 2;
        item2.y = 30;
        item3.x = winSize.width / 2 + 100;
        item3.y = 30;

        this.addChild(menu, 1);
    }
});

//////////////////////////////////////////////////////////////////////////
// KeyboardNotificationLayer for test IME keyboard notification.
//////////////////////////////////////////////////////////////////////////
var KeyboardNotificationLayer = TextInputTest.extend({
    _trackNode:null,
    _beginPos:null,

    ctor:function () {
        this._super();

        if( 'touches' in cc.sys.capabilities ){
            cc.eventManager.addListener({
                event: cc.EventListener.TOUCH_ALL_AT_ONCE,
                onTouchesEnded: this.onTouchesEnded
            }, this);
        } else if ('mouse' in cc.sys.capabilities )
            cc.eventManager.addListener({
                event: cc.EventListener.MOUSE,
                onMouseUp: this.onMouseUp
            }, this);
    },

    subtitle:function () {
        return "";
    },

    onClickTrackNode:function (clicked) {
    },

    keyboardWillShow:function (info) {
        cc.log("TextInputTest:keyboardWillShowAt(origin:" + info.end.x + "," + info.end.y
            + ", size:" + info.end.width + "," + info.end.height + ")");

        if (!this._trackNode)
            return;

        var rectTracked = textInputGetRect(this._trackNode);
        cc.log("TextInputTest:trackingNodeAt(origin:" + info.end.x + "," + info.end.y
            + ", size:" + info.end.width + "," + info.end.height + ")");

        // if the keyboard area doesn't intersect with the tracking node area, nothing need to do.
        if (!cc.rectIntersectsRect(rectTracked, info.end))
            return;

        // assume keyboard at the bottom of screen, calculate the vertical adjustment.
        var adjustVert = cc.rectGetMaxY(info.end) - cc.rectGetMinY(rectTracked);
        cc.log("TextInputTest:needAdjustVerticalPosition(" + adjustVert + ")");

        // move all the children node of KeyboardNotificationLayer
        var children = this.children;
        for (var i = 0; i < children.length; ++i) {
            var node = children[i];
            node.y += adjustVert;
        }
    },

    onTouchesEnded:function (touches, event) {
        var target = event.getCurrentTarget();
        if (!target._trackNode)
            return;

        // grab first touch
        if(touches.length == 0)
            return;

        var touch = touches[0];
        var point = touch.getLocation();

        // decide the trackNode is clicked.
        cc.log("KeyboardNotificationLayer:clickedAt(" + point.x + "," + point.y + ")");

        var rect = textInputGetRect(target._trackNode);
        cc.log("KeyboardNotificationLayer:TrackNode at(origin:" + rect.x + "," + rect.y
            + ", size:" + rect.width + "," + rect.height + ")");

        target.onClickTrackNode(cc.rectContainsPoint(rect, point));
        cc.log("----------------------------------");
    },

    onMouseUp:function (event) {
        var target = event.getCurrentTarget();
        if (!target._trackNode)
            return;

        var point = event.getLocation();

        // decide the trackNode is clicked.
        cc.log("KeyboardNotificationLayer:clickedAt(" + point.x + "," + point.y + ")");

        var rect = textInputGetRect(target._trackNode);
        cc.log("KeyboardNotificationLayer:TrackNode at(origin:" + rect.x + "," + rect.y
            + ", size:" + rect.width + "," + rect.height + ")");

        target.onClickTrackNode(cc.rectContainsPoint(rect, point));
        cc.log("----------------------------------");
    }
});

//////////////////////////////////////////////////////////////////////////
// TextFieldTTFDefaultTest for test TextFieldTTF default behavior.
//////////////////////////////////////////////////////////////////////////
var TextFieldTTFDefaultTest = KeyboardNotificationLayer.extend({
    subtitle:function () {
        return "TextFieldTTF with default behavior test";
    },
    onClickTrackNode:function (clicked) {
        var textField = this._trackNode;
        if (clicked) {
            // TextFieldTTFTest be clicked
            cc.log("TextFieldTTFDefaultTest:CCTextFieldTTF attachWithIME");
            textField.attachWithIME();
        } else {
            // TextFieldTTFTest not be clicked
            cc.log("TextFieldTTFDefaultTest:CCTextFieldTTF detachWithIME");
            textField.detachWithIME();
        }
    },

    onEnter:function () {
        this._super();

        // add CCTextFieldTTF
        var winSize = cc.director.getWinSize();

        var textField = new cc.TextFieldTTF("<click here for input>",
            TEXT_INPUT_FONT_NAME,
            TEXT_INPUT_FONT_SIZE);
        this.addChild(textField);
        textField.x = winSize.width / 2;
        textField.y = winSize.height / 2;

        this._trackNode = textField;
    }
});

//////////////////////////////////////////////////////////////////////////
// TextFieldTTFActionTest
//////////////////////////////////////////////////////////////////////////
var TextFieldTTFActionTest = KeyboardNotificationLayer.extend({
    _textField:null,
    _textFieldAction:null,
    _action:false,
    _charLimit:0, // the textfield max char limit

    ctor:function () {
        this._super();
    },

    callbackRemoveNodeWhenDidAction:function (node) {
        this.removeChild(node, true);
    },

    // KeyboardNotificationLayer
    subtitle:function () {
        return "CCTextFieldTTF with action and char limit test";
    },
    onClickTrackNode:function (clicked) {
        var textField = this._trackNode;
        if (clicked) {
            // TextFieldTTFTest be clicked
            cc.log("TextFieldTTFActionTest:CCTextFieldTTF attachWithIME");
            textField.attachWithIME();
        } else {
            // TextFieldTTFTest not be clicked
            cc.log("TextFieldTTFActionTest:CCTextFieldTTF detachWithIME");
            textField.detachWithIME();
        }
    },

    //CCLayer
    onEnter:function () {
        this._super();

        this._charLimit = 20;
        this._textFieldAction = cc.sequence(
            cc.fadeOut(0.25),
            cc.fadeIn(0.25)
        ).repeatForever();
        this._action = false;

        // add CCTextFieldTTF
        var winSize = cc.director.getWinSize();

        this._textField = new cc.TextFieldTTF("<click here for input>",
            TEXT_INPUT_FONT_NAME,
            TEXT_INPUT_FONT_SIZE);
        this.addChild(this._textField);
        this._textField.setDelegate(this);

        this._textField.x = winSize.width / 2;
        this._textField.y = winSize.height / 2;
        this._trackNode = this._textField;
    },

    //CCTextFieldDelegate
    onTextFieldAttachWithIME:function (sender) {
        if (!this._action) {
            this._textField.runAction(this._textFieldAction);
            this._action = true;
        }
        return false;
    },
    onTextFieldDetachWithIME:function (sender) {
        if (this._action) {
            this._textField.stopAction(this._textFieldAction);
            this._textField.opacity = 255;
            this._action = false;
        }
        return false;
    },
    onTextFieldInsertText:function (sender, text, len) {
        // if insert enter, treat as default to detach with ime
        if ('\n' == text) {
            return false;
        }

        // if the textfield's char count more than m_nCharLimit, doesn't insert text anymore.
        if (sender.getCharCount() >= this._charLimit) {
            return true;
        }

        // create a insert text sprite and do some action
        var label = new cc.LabelTTF(text, TEXT_INPUT_FONT_NAME, TEXT_INPUT_FONT_SIZE);
        this.addChild(label);
        var color = cc.color(226, 121, 7);
        label.color = color;

        // move the sprite from top to position
        var endX = sender.x, endY = sender.y;
        if (sender.getCharCount()) {
            endX += sender.width / 2;
        }

        var duration = 0.5;
        label.x = endX;
        label.y = cc.director.getWinSize().height - label.height * 2;
        label.scale = 8;

        var seq = cc.sequence(
            cc.spawn(
                cc.moveTo(duration, cc.p(endX, endY)),
                cc.scaleTo(duration, 1),
                cc.fadeOut(duration)),
            cc.callFunc(this.callbackRemoveNodeWhenDidAction, this));
        label.runAction(seq);
        return false;
    },

    onTextFieldDeleteBackward:function (sender, delText, len) {
        // create a delete text sprite and do some action
        var label = new cc.LabelTTF(delText, TEXT_INPUT_FONT_NAME, TEXT_INPUT_FONT_SIZE);
        this.addChild(label);

        // move the sprite to fly out
        var beginX = sender.x, beginY = sender.y;
        beginX += (sender.width - label.width) / 2.0;

        var winSize = cc.director.getWinSize();
        var endPos = cc.p(-winSize.width / 4.0, winSize.height * (0.5 + Math.random() / 2.0));

        var duration = 1;
        var rotateDuration = 0.2;
        var repeatTime = 5;
        label.x = beginX;
        label.y = beginY;

        var seq = cc.sequence(
            cc.spawn(
                cc.moveTo(duration, endPos),
                cc.rotateBy(rotateDuration, (Math.random() % 2) ? 360 : -360).repeat(repeatTime),
                cc.fadeOut(duration)),
            cc.callFunc(this.callbackRemoveNodeWhenDidAction, this));
        label.runAction(seq);
        return false;
    },
    onDraw:function (sender) {
        return false;
    }
});

var TextInputTestScene = TestScene.extend({
    runThisTest:function (num) {
        sceneIdx = (num || num == 0) ? (num - 1) : -1;
        var layer = nextTextInputTest();

        this.addChild(layer);
        cc.director.runScene(this);
    }
});

//
// Flow control
//
var arrayOfTextInputTest = [
    TextFieldTTFDefaultTest,
    TextFieldTTFActionTest
];

var nextTextInputTest = function () {
    sceneIdx++;
    sceneIdx = sceneIdx % arrayOfTextInputTest.length;

    return new arrayOfTextInputTest[sceneIdx]();
};
var previousTextInputTest = function () {
    sceneIdx--;
    if (sceneIdx < 0)
        sceneIdx += arrayOfTextInputTest.length;

    return new arrayOfTextInputTest[sceneIdx]();
};
var restartTextInputTest = function () {
    return new arrayOfTextInputTest[sceneIdx]();
};

