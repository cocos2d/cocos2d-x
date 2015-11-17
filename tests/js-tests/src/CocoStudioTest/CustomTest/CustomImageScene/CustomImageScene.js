/****************************************************************************
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

var CustomImageLayer = cc.Layer.extend({

    onEnter: function(){
        cc.Layer.prototype.onEnter.call(this);

        var guiReader = ccs.uiReader;
        guiReader.registerTypeAndCallBack("CustomImageView",
            CustomImageView,
            customImageViewReader,
            customImageViewReader.setProperties);

        var layout = guiReader.widgetFromJsonFile("ccs-res/cocosui/CustomImageViewTest/NewProject_2_1.ExportJson");
        this.addChild(layout);
    }
});

var CustomImageScene = cc.Scene.extend({

    onEnter: function(){
        cc.Scene.prototype.onEnter.call(this);

        var label = new cc.LabelTTF("Back", "fonts/arial.ttf", 20);
        //#endif
        var pMenuItem = new cc.MenuItemLabel(label, this.BackCallback, this);

        var pMenu = new cc.Menu(pMenuItem);

        pMenu.setPosition( cc.p(0, 0) );
        pMenuItem.setPosition( cc.p( 750, 25) );

        this.addChild(pMenu, 1);
    },
    runThisTest: function(){
        var pLayer = new CustomImageLayer();
        this.addChild(pLayer);

        cc.director.runScene(this);
    },
    BackCallback: function(pSender){
        var pScene = new CustomGUITestScene();
        pScene.runThisTest();
    }
});