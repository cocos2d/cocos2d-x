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

 THE SOFTWARE IS PROVIDED "AS IS()", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

var s_GuiTestEditorArray = [
    {
        title: "Button",
        layer: function () {
            return new UIButtonEditorTest();
        }
    },
    {
        title: "CheckBox",
        layer: function () {
            return new CEHCK_BOX_SCENE[0]();
        }
    },
    {
        title: "ImageView",
        layer: function () {
            return new UIImageViewEditorTest();
        }
    },
    {
        title: "Text",
        layer: function () {
            return new UITextEditorTest();
        }
    },
    {
        title: "TextAtlas",
        layer: function () {
            return new UITextAtlasEditorTest();
        }
    },
    {
        title: "TextBMFont",
        layer: function () {
            return new UITextBMFontEditorTest();
        }
    },
    {
        title: "LoadingBar",
        layer: function () {
            return new UILoadingBarEditorTest();
        }
    },
    {
        title: "Slider",
        layer: function () {
            return new UISliderEditorTest();
        }
    },
    {
        title: "TextField",
        layer: function () {
            return new UITextFieldEditorTest();
        }
    },
    {
        title: "AddNode",
        layer: function () {
            return new UIWidgetAddNodeEditorTest();
        }
    },
    {
        title: "Layout",
        layer: function () {
            return new UILayoutEditorTest();
        }
    },
    {
        title: "ListView",
        layer: function () {
            return new UIListViewEditorTest();
        }
    },
    {
        title: "PageView",
        layer: function () {
            return new UIPageViewEditorTest();
        }
    },
    {
        title: "ScrollView",
        layer: function () {
            return new UIScrollViewEditorTest();
        }
    }
];

var GuiTestMainLayer = cc.Layer.extend({
    ctor: function () {
        this._super();
        var winSize = cc.winSize;
        var x = 0;
        var y = winSize.height - 10;
        for (var i = 0; i < s_GuiTestEditorArray.length; i++) {
            var guiTest = s_GuiTestEditorArray[i];
            var text = new ccui.Text();
            if (i % 2 == 0) {
                x = winSize.width / 2 - 100;
                y -= 30;
            } else {
                x = winSize.width / 2 + 100;
            }
            text.attr({
                string: guiTest.title,
                font: "20px Arial",
                x: x,
                y: y,
                tag: i
            });
            text.setTouchEnabled(true);
            text.setTouchScaleChangeEnabled(true);
            text.addTouchEventListener(this.touchEvent, this);
            this.addChild(text);
        }

        var backText = new ccui.Text();
        backText.attr({
            string: "Back",
            font: "20px Arial",
            x: winSize.width-50,
            y: 50,
            tag: 10000
        });
        backText.setTouchEnabled(true);
        backText.setTouchScaleChangeEnabled(true);
        backText.addTouchEventListener(this.backEvent, this);
        this.addChild(backText);
    },
    touchEvent:function(sender,type){
        if(type==ccui.Widget.TOUCH_ENDED){
            var tag = sender.tag;
            var scene = new cc.Scene();
             var guiTest = s_GuiTestEditorArray[tag];
             scene.addChild(guiTest.layer());
             cc.director.runScene(scene);
        }
    },
    backEvent:function(sender,type){
        if(type==ccui.Widget.TOUCH_ENDED){
            var scene = new CocoStudioTestScene();
            scene.runThisTest();
        }
    }
});

var runGuiTestMain = function(){
    var scene = new cc.Scene();
    var main = new GuiTestMainLayer();
    scene.addChild(main);
    cc.director.runScene(scene);
}