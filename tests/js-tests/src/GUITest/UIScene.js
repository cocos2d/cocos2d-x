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

UIScene = cc.Scene.extend({
    _widget: null,
    _sceneTitle: null,
    _topDisplayLabel:null,
    _bottomDisplayLabel:null,
    _mainNode:null,
    ctor: function () {
        cc.Scene.prototype.ctor.call(this);
        this._widget = null;
    },
    init: function () {
        if (this._super()) {
            var winSize = cc.director.getWinSize();

            //add main node
            var mainNode = new cc.Node();
            var scale = winSize.height / 320;
            mainNode.attr({anchorX: 0, anchorY: 0, scale: scale, x: (winSize.width - 480 * scale) / 2, y: (winSize.height - 320 * scale) / 2});
            this.addChild(mainNode);

            var widget;
            if(cocoStudioOldApiFlag == 0){
                var json = ccs.load("res/cocosui/UITest/UITest.json");
                widget = json.node;
            }else{
                //old api
                widget = ccs.uiReader.widgetFromJsonFile("res/cocosui/UITest/UITest.json");
            }
            mainNode.addChild(widget,-1);

            this._sceneTitle = widget.getChildByName("UItest");

            var back_label = widget.getChildByName("back");
            back_label.addTouchEventListener(this.toExtensionsMainLayer, this);

            var left_button = widget.getChildByName("left_Button");
            left_button.addTouchEventListener(this.previousCallback ,this);

            var middle_button = widget.getChildByName("middle_Button");
            middle_button.addTouchEventListener(this.restartCallback ,this);

            var right_button = widget.getChildByName("right_Button");
            right_button.addTouchEventListener(this.nextCallback ,this);

            //add topDisplayLabel
            var widgetSize = widget.getContentSize();
            var topDisplayText = new ccui.Text();
            topDisplayText.attr({
	            string: "",
	            fontName: "Marker Felt",
	            fontSize: 32,
	            anchorX: 0.5,
	            anchorY: -1,
	            x: widgetSize.width / 2.0,
	            y: widgetSize.height / 2.0
            });
            mainNode.addChild(topDisplayText);

            //add bottomDisplayLabel
            var bottomDisplayText = new ccui.Text();
            bottomDisplayText.attr({
	            string: "INIT",
	            fontName: "Marker Felt",
	            fontSize: 30,
	            color: cc.color(159, 168, 176),
	            x: widgetSize.width / 2.0
            });
            bottomDisplayText.y = widgetSize.height / 2.0 - bottomDisplayText.height * 1.75;
            mainNode.addChild(bottomDisplayText);

            this._topDisplayLabel = topDisplayText;
            this._bottomDisplayLabel = bottomDisplayText;
            this._mainNode = mainNode;
            this._widget = widget;
            return true;
        }
        return false;
    },
    setSceneTitle: function (title) {
        this._sceneTitle.setString(title);
    },
    toExtensionsMainLayer: function (sender, type) {
        if (type == ccui.Widget.TOUCH_ENDED) {
            UISceneManager.purge();
            /*
            var scene = new cc.Scene();
            var layer = new TestController();
            scene.addChild(layer);
            var transition = new cc.TransitionProgressRadialCCW(0.5,scene);
            director.runScene(transition);
            */
            GUITestScene.prototype.runThisTest();
        }
    },

    previousCallback: function (sender, type) {
        if (type == ccui.Widget.TOUCH_ENDED) {
            cc.director.runScene(UISceneManager.getInstance().previousUIScene());
        }
    },

    restartCallback: function (sender, type) {
        if (type == ccui.Widget.TOUCH_ENDED) {
            cc.director.runScene(UISceneManager.getInstance().currentUIScene());
        }
    },

    nextCallback: function (sender, type) {
        if (type == ccui.Widget.TOUCH_ENDED) {
            cc.director.runScene(UISceneManager.getInstance().nextUIScene());
        }
    }
});