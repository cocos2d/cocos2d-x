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

var TEXT_FIELD_TTF_DEFAULT_TEST = 0;
var TEXT_FIELD_TTF_ACTION_TEST = 1;
var TEXT_INPUT_TESTS_COUNT = 2;

var TEXT_INPUT_FONT_NAME = "Thonburi";
var TEXT_INPUT_FONT_SIZE = 36;

var inputTestIdx = -1;

var createTextInputTest = function (index) {
    switch (index) {
        case TEXT_FIELD_TTF_DEFAULT_TEST:
            return new TextFieldTTFDefaultTest();
        case TEXT_FIELD_TTF_ACTION_TEST:
            return new TextFieldTTFActionTest();
        default:
            return 0;
    }
};

var restartTextInputTest = function () {
    var containerLayer = new TextInputTest();

    var testLayer = createTextInputTest(inputTestIdx);
    containerLayer.addKeyboardNotificationLayer(testLayer);

    return containerLayer;
};

var nextTextInputTest = function () {
    inputTestIdx++;
    inputTestIdx = inputTestIdx % TEXT_INPUT_TESTS_COUNT;

    return restartTextInputTest();
};

var backTextInputTest = function () {
    inputTestIdx--;
    if (inputTestIdx < 0)
        inputTestIdx += TEXT_INPUT_TESTS_COUNT;

    return restartTextInputTest();
};

var textInputGetRect = function (node) {
    var rc = cc.rect(node.getPosition().x, node.getPosition().y, node.getContentSize().width, node.getContentSize().height);
    rc.origin.x -= rc.size.width / 2;
    rc.origin.y -= rc.size.height / 2;
    return rc;
};

/**
 @brief    TextInputTest for retain prev, reset, next, main menu buttons.
 */
var TextInputTest = cc.Layer.extend({
    notificationLayer:null,
    ctor:function () {
    },

    restartCallback:function (sender) {
        var s = new TextInputTestScene();
        s.addChild(restartTextInputTest());
        cc.Director.getInstance().replaceScene(s);
    },
    nextCallback:function (sender) {
        var s = new TextInputTestScene();
        s.addChild(nextTextInputTest());
        cc.Director.getInstance().replaceScene(s);
    },
    backCallback:function (sender) {
        var s = new TextInputTestScene();
        s.addChild(backTextInputTest());
        cc.Director.getInstance().replaceScene(s);
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

        var s = cc.Director.getInstance().getWinSize();

        var label = cc.LabelTTF.create(this.title(), "Arial", 24);
        this.addChild(label);
        label.setPosition(cc.p(s.width / 2, s.height - 50));

        var subTitle = this.notificationLayer.subtitle();
        if (subTitle && subTitle != "") {
            var l = cc.LabelTTF.create(subTitle, "Thonburi", 16);
            this.addChild(l, 1);
            l.setPosition(cc.p(s.width / 2, s.height - 80));
        }

        var item1 = cc.MenuItemImage.create(s_pathB1, s_pathB2, this, this.backCallback);
        var item2 = cc.MenuItemImage.create(s_pathR1, s_pathR2, this, this.restartCallback);
        var item3 = cc.MenuItemImage.create(s_pathF1, s_pathF2, this, this.nextCallback);

        var menu = cc.Menu.create(item1, item2, item3);
        menu.setPosition(cc.p(0,0));
        item1.setPosition(cc.p(s.width / 2 - 100, 30));
        item2.setPosition(cc.p(s.width / 2, 30));
        item3.setPosition(cc.p(s.width / 2 + 100, 30));

        this.addChild(menu, 1);
    }
});

//////////////////////////////////////////////////////////////////////////
// KeyboardNotificationLayer for test IME keyboard notification.
//////////////////////////////////////////////////////////////////////////
var KeyboardNotificationLayer = cc.Layer.extend({
    _pTrackNode:null,
    _beginPos:null,

    ctor:function () {
        this.setTouchEnabled(true);
    },

    subtitle:function () {
        return "";
    },
    onClickTrackNode:function (clicked) {
    },

    registerWithTouchDispatcher:function () {
        cc.Director.getInstance().getTouchDispatcher().addTargetedDelegate(this, 0, false);
    },
    keyboardWillShow:function (info) {
        cc.log("TextInputTest:keyboardWillShowAt(origin:" + info.end.origin.x + "," + info.end.origin.y
            + ", size:" + info.end.size.width + "," + info.end.size.height + ")");

        if (!this._pTrackNode) {
            return;
        }

        var rectTracked = textInputGetRect(this._pTrackNode);
        cc.log("TextInputTest:trackingNodeAt(origin:" + info.end.origin.x + "," + info.end.origin.y
            + ", size:" + info.end.size.width + "," + info.end.size.height + ")");

        // if the keyboard area doesn't intersect with the tracking node area, nothing need to do.
        if (!cc.Rect.CCRectIntersectsRect(rectTracked, info.end)) {
            return;
        }

        // assume keyboard at the bottom of screen, calculate the vertical adjustment.
        var adjustVert = cc.Rect.CCRectGetMaxY(info.end) - cc.Rect.CCRectGetMinY(rectTracked);
        cc.log("TextInputTest:needAdjustVerticalPosition(" + adjustVert + ")");

        // move all the children node of KeyboardNotificationLayer
        var children = this.getChildren();
        for (var i = 0; i < children.length; ++i) {
            var node = children[i];
            var pos = node.getPosition();
            pos.y += adjustVert;
            node.setPosition(pos);
        }
    },

    onTouchBegan:function (touch, event) {
        cc.log("++++++++++++++++++++++++++++++++++++++++++++");
        this._beginPos = touch.getLocation();
        this._beginPos = cc.Director.getInstance().convertToGL(this._beginPos);
        return true;
    },

    onTouchEnded:function (touch, event) {
        if (!this._pTrackNode) {
            return;
        }

        var endPos = touch.getLocation();
        endPos = cc.Director.getInstance().convertToGL(endPos);

        var delta = 5.0;
        if (Math.abs(endPos.x - this._beginPos.x) > delta
            || Math.abs(endPos.y - this._beginPos.y) > delta) {
            // not click
            this._beginPos.x = this._beginPos.y = -1;
            return;
        }

        // decide the trackNode is clicked.
        var point = this.convertTouchToNodeSpaceAR(touch);
        //var point = endPos;
        cc.log("KeyboardNotificationLayer:clickedAt(" + point.x + "," + point.y + ")");

        var rect = textInputGetRect(this._pTrackNode);
        cc.log("KeyboardNotificationLayer:TrackNode at(origin:" + rect.origin.x + "," + rect.origin.y
            + ", size:" + rect.size.width + "," + rect.size.height + ")");

        this.onClickTrackNode(cc.Rect.CCRectContainsPoint(rect, point));
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
        var textField = this._pTrackNode;
        if (clicked) {
            // TextFieldTTFTest be clicked
            cc.log("TextFieldTTFDefaultTest:CCTextFieldTTF attachWithIME");
            textField.attachWithIME();
        }
        else {
            // TextFieldTTFTest not be clicked
            cc.log("TextFieldTTFDefaultTest:CCTextFieldTTF detachWithIME");
            textField.detachWithIME();
        }
    },

    onEnter:function () {
        this._super();

        // add CCTextFieldTTF
        var s = cc.Director.getInstance().getWinSize();

        var textField = cc.TextFieldTTF.create("<click here for input>",
            TEXT_INPUT_FONT_NAME,
            TEXT_INPUT_FONT_SIZE);
        this.addChild(textField);
        textField.setPosition(cc.p(s.width / 2, s.height / 2));

        this._pTrackNode = textField;
    }
});

//////////////////////////////////////////////////////////////////////////
// TextFieldTTFActionTest
//////////////////////////////////////////////////////////////////////////
var TextFieldTTFActionTest = KeyboardNotificationLayer.extend({
    _pTextField:null,
    _pTextFieldAction:null,
    _bAction:false,
    _nCharLimit:0, // the textfield max char limit

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
        var textField = this._pTrackNode;
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

        this._nCharLimit = 20;
        this._pTextFieldAction = cc.RepeatForever.create(
            cc.Sequence.create(
                cc.FadeOut.create(0.25),
                cc.FadeIn.create(0.25)));
        this._bAction = false;

        // add CCTextFieldTTF
        var s = cc.Director.getInstance().getWinSize();

        this._pTextField = cc.TextFieldTTF.create("<click here for input>",
            TEXT_INPUT_FONT_NAME,
            TEXT_INPUT_FONT_SIZE);
        this.addChild(this._pTextField);
        this._pTextField.setDelegate(this);

        this._pTextField.setPosition(cc.p(s.width / 2, s.height / 2));
        this._pTrackNode = this._pTextField;
    },
    onExit:function () {
        this._super();
    },

    //CCTextFieldDelegate
    onTextFieldAttachWithIME:function (sender) {
        if (!this._bAction) {
            this._pTextField.runAction(this._pTextFieldAction);
            this._bAction = true;
        }
        return false;
    },
    onTextFieldDetachWithIME:function (sender) {
        if (this._bAction) {
            this._pTextField.stopAction(this._pTextFieldAction);
            this._pTextField.setOpacity(255);
            this._bAction = false;
        }
        return false;
    },
    onTextFieldInsertText:function (sender, text, len) {
        // if insert enter, treat as default to detach with ime
        if ('\n' == text) {
            return false;
        }

        // if the textfield's char count more than m_nCharLimit, doesn't insert text anymore.
        if (sender.getCharCount() >= this._nCharLimit) {
            return true;
        }

        // create a insert text sprite and do some action
        var label = cc.LabelTTF.create(text, TEXT_INPUT_FONT_NAME, TEXT_INPUT_FONT_SIZE);
        this.addChild(label);
        var color = new cc.Color3B(226, 121, 7);
        label.setColor(color);

        // move the sprite from top to position
        var endPos = cc.p(sender.getPositionX(), sender.getPositionY());
        if (sender.getCharCount()) {
            endPos.x += sender.getContentSize().width / 2;
        }
        var inputTextSize = label.getContentSize();
        var beginPos = cc.p(endPos.x, cc.Director.getInstance().getWinSize().height - inputTextSize.height * 2);

        var duration = 0.5;
        label.setPosition(beginPos);
        label.setScale(8);

        var seq = cc.Sequence.create(
            cc.Spawn.create(
                cc.MoveTo.create(duration, endPos),
                cc.ScaleTo.create(duration, 1),
                cc.FadeOut.create(duration)),
            cc.CallFunc.create(this, this.callbackRemoveNodeWhenDidAction));
        label.runAction(seq);
        return false;
    },

    onTextFieldDeleteBackward:function (sender, delText, len) {
        // create a delete text sprite and do some action
        var label = cc.LabelTTF.create(delText, TEXT_INPUT_FONT_NAME, TEXT_INPUT_FONT_SIZE);
        this.addChild(label);

        // move the sprite to fly out
        var beginPos = cc.p(sender.getPositionX(), sender.getPositionY());
        var textfieldSize = sender.getContentSize();
        var labelSize = label.getContentSize();
        beginPos.x += (textfieldSize.width - labelSize.width) / 2.0;

        var winSize = cc.Director.getInstance().getWinSize();
        var endPos = cc.p(-winSize.width / 4.0, winSize.height * (0.5 + Math.random() / 2.0));

        var duration = 1;
        var rotateDuration = 0.2;
        var repeatTime = 5;
        label.setPosition(beginPos);

        var seq = cc.Sequence.create(
            cc.Spawn.create(
                cc.MoveTo.create(duration, endPos),
                cc.Repeat.create(
                    cc.RotateBy.create(rotateDuration, (Math.random() % 2) ? 360 : -360),
                    repeatTime),
                cc.FadeOut.create(duration)),
            cc.CallFunc.create(this, this.callbackRemoveNodeWhenDidAction));
        label.runAction(seq);
        return false;
    },
    onDraw:function (sender) {
        return false;
    }
});

var TextInputTestScene = TestScene.extend({
    runThisTest:function () {
        var layer = nextTextInputTest();
        this.addChild(layer);
        cc.Director.getInstance().replaceScene(this);
    }
});
