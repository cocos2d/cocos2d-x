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
                var json = ccs.load("ccs-res/cocosui/UITest/UITest.json");
                widget = json.node;
            }else{
                //old api
                widget = ccs.uiReader.widgetFromJsonFile("ccs-res/cocosui/UITest/UITest.json");
            }
            mainNode.addChild(widget,-1);

            this._sceneTitle = widget.getChildByName("UItest");

            var back_label = widget.getChildByName("back");
            if(back_label){
                back_label.addTouchEventListener(this.toExtensionsMainLayer, this);
            }else{
                var label = new cc.LabelTTF("Back", "Arial", 20);
                var menuItem = new cc.MenuItemLabel(label, this.toExtensionsMainLayer, this);
                var menu = new cc.Menu(menuItem);
                menu.x = 0;
                menu.y = 0;
                menuItem.x = winSize.width - 50;
                menuItem.y = 25;
                this.addChild(menu, 1);
            }

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
    toExtensionsMainLayer: function (sender) {
        UISceneManager.purge();
        GUITestScene.prototype.runThisTest();
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