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

(function(global){

    var currentTestingArray = null;

    var testingItems = {
        "UIButton": [
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
                title: "UIButtonTestRemoveSelf",
                func: function () {
                    return new UIButtonTestRemoveSelf();
                }
            },
            {
                title: "UIButtonTestSwitchScale9",
                func: function () {
                    return new UIButtonTestSwitchScale9();
                }
            },
            {
                title: "UIButtonTestZoomScale",
                func: function () {
                    return new UIButtonTestZoomScale();
                }
            },
            {
                title: "UIButtonTextOnly",
                func: function () {
                    return new UIButtonTextOnly();
                }
            },
            {
                title: "UIButtonIgnoreContentSizeTest",
                func: function () {
                    return new UIButtonIgnoreContentSizeTest();
                }
            },
            {
                title: "UIButtonTitleEffectTest",
                func: function () {
                    return new UIButtonTitleEffectTest();
                }
            },
            {
                title: "UIButtonFlipTest",
                func: function () {
                    return new UIButtonFlipTest();
                }
            },
            {
                title: "UIButtonNormalDefaultTest",
                func: function () {
                    return new UIButtonNormalDefaultTest();
                }
            },
            {
                title: "UIButtonDisableDefaultTest",
                func: function () {
                    return new UIButtonDisableDefaultTest();
                }
            }
        ],
        "UIFocus": [
            {
                title: "UIFocusTestHorizontal",
                func: function () {
                    return new UIFocusTestHorizontal();
                }
            },
            {
                title: "UIFocusTestVertical",
                func: function () {
                    return new UIFocusTestVertical();
                }
            },
            {
                title: "UIFocusTestNestedLayout1",
                func: function () {
                    return new UIFocusTestNestedLayout1();
                }
            },
            {
                title: "UIFocusTestNestedLayout2",
                func: function () {
                    return new UIFocusTestNestedLayout2();
                }
            },
            {
                title: "UIFocusTestNestedLayout3",
                func: function () {
                    return new UIFocusTestNestedLayout3();
                }
            }
            /*{     //need test
                title: "UIFocusTestListView",
                func: function () {
                    return new UIFocusTestListView();
                }
            }*/
        ],
        "UICheckBox": [
            {
                title: "UICheckBoxTest",
                func: function () {
                    return new UICheckBoxTest();
                }
            },
            {
                title: "UICheckBoxDefaultBehaviorTest",
                func: function(){
                    return new UICheckBoxDefaultBehaviorTest();
                }
            }
        ],
        "UISlider": [
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
                title: "UISliderNormalDefaultTest",
                func: function () {
                    return new UISliderNormalDefaultTest();
                }
            },
            {
                title: "UISliderDisabledDefaultTest",
                func: function () {
                    return new UISliderDisabledDefaultTest();
                }
            }
        ],
        "UIImageView": [
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
                title: "UIImageViewTest_ContentSize",
                func: function () {
                    return new UIImageViewTest_ContentSize();
                }
            },
            {
                title: "UIImageViewFlipTest",
                func: function () {
                    return new UIImageViewFlipTest();
                }
            }
        ],
        "UILoadingBar": [
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
            }
        ],
        "UIText": [
            {
                title: "UITextTest",
                func: function(){
                    return new UITextTest();
                }
            },
            {
                title: "UITextTest_LineWrap",
                func: function(){
                    return new UITextTest_LineWrap();
                }
            },
            {
                title: "UILabelTest_Effect",
                func: function(){
                    return new UILabelTest_Effect();
                }
            },
            {
                title: "UITextTest_TTF",
                func: function(){
                    return new UITextTest_TTF();
                }
            },
            {
                title: "UITextTest_IgnoreConentSize",
                func: function(){
                    return new UITextTest_IgnoreConentSize();
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
                title: "UILabelTest_TTF",
                func: function () {
                    return new UILabelTest_TTF();
                }
            }
        ],
        "UITextFiled": [
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
                title: "UITextFieldTest_LineWrap",
                func: function () {
                    return new UITextFieldTest_LineWrap();
                }
            },
            {
                title: "UITextFieldTest_TrueTypeFont",
                func: function () {
                    return new UITextFieldTest_TrueTypeFont();
                }
            },
            {
                title: "UITextFieldTest_PlaceHolderColor",
                func: function () {
                    return new UITextFieldTest_PlaceHolderColor();
                }
            }
        ],
        "UILayout": [
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
                title: "UILayoutTest_Layout_Relative_Align_Parent",
                func: function () {
                    return new UILayoutTest_Layout_Relative_Align_Parent();
                }
            },
            {
                title: "UILayoutTest_Layout_Relative_Location",
                func: function () {
                    return new UILayoutTest_Layout_Relative_Location();
                }
            },
            {
                title: "UILayoutComponent_Berth_Test",
                func: function () {
                    return new UILayoutComponent_Berth_Test();
                }
            },
            {
                title: "UILayoutComponent_Berth_Stretch_Test",
                func: function () {
                    return new UILayoutComponent_Berth_Stretch_Test();
                }
            }
        ],
        "UIScrollView": [
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
                title: "UIScrollViewNestTest",
                func: function () {
                    return new UIScrollViewNestTest();
                }
            },
            {
                title: "UIScrollViewRotated",
                func: function () {
                    return new UIScrollViewRotated();
                }
            }
        ],
        "UIPageView": [
            {
                title: "UIPageViewTest",
                func: function () {
                    return new UIPageViewTest();
                }
            },
            {
                title: "UIPageViewButtonTest",
                func: function () {
                    return new UIPageViewButtonTest();
                }
            },
            {
                title: "UIPageViewCustomScrollThreshold",
                func: function () {
                    return new UIPageViewCustomScrollThreshold();
                }
            },
            {
                title: "UIPageViewTouchPropagationTest",
                func: function () {
                    return new UIPageViewTouchPropagationTest();
                }
            },
            {
                title: "UIPageViewDynamicAddAndRemoveTest",
                func: function () {
                    return new UIPageViewDynamicAddAndRemoveTest();
                }
            }
        ],
        "UIListView": [
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
            }
        ],
        "UIWidget": [
            {
                title: "UIWidgetAddNodeTest",
                func: function () {
                    return new UIWidgetAddNodeTest();
                }
            }
        ],
        "UIRichText": [
            {
                title: "UIRichTextTest",
                func: function () {
                    return new UIRichTextTest();
                }
            }
        ]
    };

    if (cc.sys.isNative) {
        testingItems["UIS9NinePatchTest"] = [
        {
                title: "UIS9NinePatchTest",
                func: function () {
                    return new UIS9NinePatchTest();
                }
            }
        ];
    }

    if (cc.sys.os == cc.sys.OS_ANDROID || cc.sys.os == cc.sys.OS_IOS || !cc.sys.isNative)
    {
        testingItems["UIVideoPlayer"] = [
            {
                title: "UIVideoPlayerTest",
                func: function () {
                    return new UIVideoPlayerTest();
                }
            }
        ];

        testingItems["UIWebViewTest"] = [
            {
                title: "UIWebViewTest",
                func: function () {
                    return new UIWebViewTest();
                }
            }
        ];
    }

    var guiTestScene = null;
    global.GUITestScene = cc.Class.extend({

        runThisTest: function(){
            if(guiTestScene === null || !cc.sys.isObjectValid(guiTestScene))
                guiTestScene = new listScene;
            cc.director.runScene(guiTestScene);
        }

    });

    var listScene = TestScene.extend({

        ctor: function(){
            TestScene.prototype.ctor.call(this);

            var menu = new cc.Menu();
            menu.x = 0;
            menu.y = 0;
            var index = 0;
            for(var p in testingItems){
                (function(name, list){
                    var label = new cc.LabelTTF(name, "Arial", 24);
                    var menuItem = new cc.MenuItemLabel(label, function(){
                        currentTestingArray = list;
                        var manager = global.UISceneManager.getInstance();
                        var scene = manager.currentUIScene();
                        cc.director.runScene(scene);
                    }, this);
                    menuItem.x = winSize.width / 2;
                    menuItem.y = (winSize.height - (index++ + 1) * 25);
                    index++;
                    menu.addChild(menuItem);
                })(p, testingItems[p]);
            }

            this._menu = menu;
            this.addChild(menu);

            this._length = 0;
            for(var p in testingItems){
                this._length++;
            }
        },

        onEnter: function(){
            TestScene.prototype.onEnter.call(this);
            if ('touches' in cc.sys.capabilities)
                cc.eventManager.addListener({
                    event: cc.EventListener.TOUCH_ALL_AT_ONCE,
                    onTouchesMoved: function (touches, event) {
                        var target = event.getCurrentTarget();
                        var delta = touches[0].getDelta();
                        target.moveMenu(delta);
                        return true;
                    }
                }, this);
            else if ('mouse' in cc.sys.capabilities) {
                cc.eventManager.addListener({
                    event: cc.EventListener.MOUSE,
                    onMouseMove: function (event) {
                        if (event.getButton() == cc.EventMouse.BUTTON_LEFT)
                            event.getCurrentTarget().moveMenu(event.getDelta());
                    },
                    onMouseScroll: function (event) {
                        var delta = cc.sys.isNative ? event.getScrollY() * 6 : -event.getScrollY();
                        event.getCurrentTarget().moveMenu({y: delta});
                        return true;
                    }
                }, this);
            }
        },

        moveMenu: function(delta){
            var newY = this._menu.y + delta.y;
            if (newY < 0 )
                newY = 0;

            if( newY > ((this._length + 1) * 49 - winSize.height))
                newY = ((this._length + 1) * 49 - winSize.height);

            this._menu.y = newY;
        }
    });

    global.UISceneManager = {

        _currentUISceneId: 0,

        ctor: function () {
            this._currentUISceneId = 0;
        },

        nextUIScene: function () {
            this._currentUISceneId++;
            if (this._currentUISceneId > currentTestingArray.length - 1) {
                this._currentUISceneId = 0;
            }
            return this.currentUIScene();
        },

        previousUIScene: function () {
            this._currentUISceneId--;
            if (this._currentUISceneId < 0) {
                this._currentUISceneId = currentTestingArray.length - 1;
            }
            return this.currentUIScene();
        },

        currentUIScene: function () {
            var test = currentTestingArray[this._currentUISceneId];
            var sence = test.func();
            sence.init();
            sence.setSceneTitle(test.title);
            return sence;
        }
    };

    global.UISceneManager.getInstance = function () {
        return this;
    };

    global.UISceneManager.purge = function (){
        this._currentUISceneId = 0;
    };

})(window);