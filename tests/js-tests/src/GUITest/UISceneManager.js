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

 THE SOFTWARE IS PROVIDED "AS IS()", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

var s_testArray = [
    {
        title: "UIButtonTest",
        func: function () {
            return new UIButtonTest();
        }
    },
    {
        title: "UIButtonTest_Scale9",
        func: function () {
            return new UIButtonTest_Scale9();
        }
    },
    {
        title: "UIButtonTest_PressedAction",
        func: function () {
            return new UIButtonTest_PressedAction();
        }
    },
    {
        title: "UIButtonTest_Title",
        func: function () {
            return new UIButtonTest_Title();
        }
    },
    {
        title: "UICheckBoxTest",
        func: function () {
            return new UICheckBoxTest();
        }
    },
    {
        title: "UISliderTest",
        func: function () {
            return new UISliderTest();
        }
    },
    {
        title: "UISliderTest_Scale9",
        func: function () {
            return new UISliderTest_Scale9();
        }
    },
    {
        title: "UIImageViewTest",
        func: function () {
            return new UIImageViewTest();
        }
    },
    {
        title: "UIImageViewTest_Scale9",
        func: function () {
            return new UIImageViewTest_Scale9();
        }
    },
    {
        title: "UILoadingBarTest_Left",
        func: function () {
            return new UILoadingBarTest_Left();
        }
    },
    {
        title: "UILoadingBarTest_Right",
        func: function () {
            return new UILoadingBarTest_Right();
        }
    },
    {
        title: "UILoadingBarTest_Fix",
        func: function(){
            return new UILoadingBarTest_Fix();
        }
    },
    {
        title: "UILoadingBarTest_Left_Scale9",
        func: function () {
            return new UILoadingBarTest_Left_Scale9();
        }
    },
    {
        title: "UILoadingBarTest_Right_Scale9",
        func: function () {
            return new UILoadingBarTest_Right_Scale9();
        }
    },
    {
        title: "UILoadingBarTest_Fix_Scale9",
        func: function(){
            return new UILoadingBarTest_Fix_Scale9();
        }
    },
    {
        title: "UILabelAtlasTest",
        func: function () {
            return new UILabelAtlasTest();
        }
    },
    {
        title: "UILabelTest",
        func: function () {
            return new UILabelTest();
        }
    },
    {
        title: "UILabelTest_LineWrap",
        func: function () {
            return new UILabelTest_LineWrap();
        }
    },
    {
        title: "UILabelBMFontTest",
        func: function () {
            return new UILabelBMFontTest();
        }
    },
    {
        title: "UITextFieldTest",
        func: function () {
            return new UITextFieldTest();
        }
    },
    {
        title: "UITextFieldTest_MaxLength",
        func: function () {
            return new UITextFieldTest_MaxLength();
        }
    },
    {
        title: "UITextFieldTest_Password",
        func: function () {
            return new UITextFieldTest_Password();
        }
    },
    {
        title: "UILayoutTest",
        func: function () {
            return new UILayoutTest();
        }
    },
    {
        title: "UILayoutTest_Color",
        func: function () {
            return new UILayoutTest_Color();
        }
    },
    {
        title: "UILayoutTest_Gradient", func: function () {
        return new UILayoutTest_Gradient();
    }
    },
    {
        title: "UILayoutTest_BackGroundImage",
        func: function () {
            return new UILayoutTest_BackGroundImage();
        }
    },
    {
        title: "UILayoutTest_BackGroundImage_Scale9",
        func: function () {
            return new UILayoutTest_BackGroundImage_Scale9();
        }
    },
    {
        title: "UILayoutTest_Layout_Linear_Vertical",
        func: function () {
            return new UILayoutTest_Layout_Linear_Vertical();
        }
    },
    {
        title: "UILayoutTest_Layout_Linear_Horizontal",
        func: function () {
            return new UILayoutTest_Layout_Linear_Horizontal();
        }
    },
    {
        title: "UILayoutTest_Layout_Relative",
        func: function () {
            return new UILayoutTest_Layout_Relative();
        }
    },
    {
        title: "UIScrollViewTest_Vertical",
        func: function () {
            return new UIScrollViewTest_Vertical();
        }
    },
    {
        title: "UIScrollViewTest_Horizontal",
        func: function () {
            return new UIScrollViewTest_Horizontal();
        }
    },
    {
        title: "UIScrollViewTest_Both",
        func: function () {
            return new UIScrollViewTest_Both();
        }
    },
    {
        title: "UIScrollViewTest_ScrollToPercentBothDirection",
        func: function () {
            return new UIScrollViewTest_ScrollToPercentBothDirection();
        }
    },
    {
        title: "UIScrollViewTest_ScrollToPercentBothDirection_Bounce",
        func: function () {
            return new UIScrollViewTest_ScrollToPercentBothDirection_Bounce();
        }
    },
    {
        title: "UIPageViewTest",
        func: function () {
            return new UIPageViewTest();
        }
    },
    {
        title: "UIListViewTest_Vertical",
        func: function () {
            return new UIListViewTest_Vertical();
        }
    },
    {
        title: "UIListViewTest_Horizontal",
        func: function () {
            return new UIListViewTest_Horizontal();
        }
    },
    {
        title: "UIWidgetAddNodeTest",
        func: function () {
            return new UIWidgetAddNodeTest();
        }
    },
    {
        title: "UIRichTextTest",
        func: function () {
            return new UIRichTextTest();
        }
    }
];

UISceneManager = cc.Class.extend({
    _currentUISceneId: 0,
    ctor: function () {
        this._currentUISceneId = 0;
    },
    nextUIScene: function () {
        this._currentUISceneId++;
        if (this._currentUISceneId > s_testArray.length - 1) {
            this._currentUISceneId = 0;
        }
        return this.currentUIScene();
    },
    previousUIScene: function () {
        this._currentUISceneId--;
        if (this._currentUISceneId < 0) {
            this._currentUISceneId = s_testArray.length - 1;
        }
        return this.currentUIScene();
    },
    currentUIScene: function () {
        var test = s_testArray[this._currentUISceneId];
        var sence = test.func();
        sence.init();
        sence.setSceneTitle(test.title);
        return sence;
    }
});
UISceneManager._instance = null;
UISceneManager.getInstance = function () {
    if (!this._instance) {
        this._instance = new UISceneManager();
    }
    return this._instance;
};
UISceneManager.purge = function () {
    this._instance = null;
};

GUITestScene = cc.Class.extend({
    runThisTest:function () {
        var manager = UISceneManager.getInstance();
        var scene = manager.currentUIScene();
        cc.director.runScene(scene);
    }
});
