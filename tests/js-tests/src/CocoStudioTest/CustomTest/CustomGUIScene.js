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

var g_guisTests = [
    {
        title: "custom gui image Test",
        test: function(){
            var pScene = new CustomImageScene();
            pScene.runThisTest();
        }
    },{
        title: "custom gui particle widget Test",
        test: function(){
            var pScene = new CustomParticleWidgetScene();
            pScene.runThisTest();
        }
    }
];

var CustomGUITestMainLayer = cc.Layer.extend({
    onEnter: function(){
        cc.Layer.prototype.onEnter.call(this);

        var winSize = cc.director.getWinSize();

        var pMenu = new cc.Menu();
        pMenu.x = 0;
        pMenu.y = 0;
        cc.MenuItemFont.setFontName("fonts/arial.ttf");
        cc.MenuItemFont.setFontSize(24);

        for (var i = 0; i < g_guisTests.length; ++i) {
            var selItem = g_guisTests[i];
            var pItem = new cc.MenuItemFont(selItem.title,
                selItem.test, this);
            pItem.x = winSize.width / 2;
            pItem.y = winSize.height - (i + 1) * LINE_SPACE;
            pMenu.addChild(pItem, ITEM_TAG_BASIC + i);
        }
        this.addChild(pMenu);

    },
    onTouchesBegan: function(touches, event){
        var touch = touches[0];

        this._beginPos = touch.getLocation();
    },
    touchEvent: function(){

    }

});

var CustomGUITestScene = cc.Scene.extend({
    onEnter: function(){
        cc.Scene.prototype.onEnter.call(this);

        var label = new cc.LabelTTF("Back", "fonts/arial.ttf", 20);
        //#endif
        var pMenuItem = new cc.MenuItemLabel(label, this.BackCallback, this);

        var pMenu = new cc.Menu(pMenuItem);

        pMenu.setPosition( cc.p(0, 0) );
        pMenuItem.setPosition(cc.pAdd(cc.visibleRect.bottomRight,cc.p(-50,25)));

        this.addChild(pMenu, 1);

    },
    runThisTest: function(){
        var pLayer = new CustomGUITestMainLayer();
        this.addChild(pLayer);

        cc.director.runScene(this);
    },
    BackCallback: function(pSender){
        var pScene = new CocoStudioTestScene();
        pScene.runThisTest();

    }
});

var runCustomGUITest = function(){
    var scene = new CustomGUITestScene();
    scene.runThisTest();
};