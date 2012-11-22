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

var ControlScene = cc.Layer.extend({
    _sceneTitleLabel:null,

    ctor:function(){},

    getSceneTitleLabel:function(){return this._sceneTitleLabel;},
    setSceneTitleLabel:function(sceneTitleLabel){this._sceneTitleLabel = sceneTitleLabel;},

    init:function(){
        if (this._super()) {
            // Get the sceensize
            var screensize = cc.Director.getInstance().getWinSize();

            var pBackItem = cc.MenuItemFont.create("Back", this,this.toExtensionsMainLayer);
            pBackItem.setPosition(cc.p(screensize.width - 50, 25));
            var pBackMenu = cc.Menu.create(pBackItem);
            pBackMenu.setPosition( cc.p(0,0));
            this.addChild(pBackMenu, 10);

            // Add the generated background
            var background = cc.Sprite.create(s_extensions_background);
            background.setPosition(cc.p(screensize.width / 2, screensize.height / 2));
            var bgRect = background.getTextureRect();
            background.setScaleX(screensize.width/bgRect.size.width);
            background.setScaleY(screensize.height/bgRect.size.height);
            this.addChild(background);

            // Add the ribbon
            var ribbon = cc.Scale9Sprite.create(s_extensions_ribbon, cc.RectMake(1, 1, 48, 55));
            ribbon.setContentSize(cc.SizeMake(screensize.width, 57));
            ribbon.setPosition(cc.p(screensize.width / 2.0, screensize.height - ribbon.getContentSize().height / 2.0));
            this.addChild(ribbon);

            // Add the title
            this.setSceneTitleLabel(cc.LabelTTF.create("Title", "Arial", 12));
            this._sceneTitleLabel.setPosition(cc.p (screensize.width / 2, screensize.height - this._sceneTitleLabel.getContentSize().height / 2 - 5));
            this.addChild(this._sceneTitleLabel, 1);

            // Add the menu
            var item1 = cc.MenuItemImage.create(s_pathB1, s_pathB2, this, this.previousCallback);
            var item2 = cc.MenuItemImage.create(s_pathR1, s_pathR2, this, this.restartCallback);
            var item3 = cc.MenuItemImage.create(s_pathF1, s_pathF2, this, this.nextCallback);

            var menu = cc.Menu.create(item1, item3, item2);
            menu.setPosition(cc.p(0,0));
            item1.setPosition(cc.p(screensize.width / 2 - 100, 37));
            item2.setPosition(cc.p(screensize.width / 2, 35));
            item3.setPosition(cc.p(screensize.width / 2 + 100, 37));

            this.addChild(menu ,1);

            return true;
        }
        return false;
    },

    toExtensionsMainLayer:function(sender){
        var pScene = new ExtensionsTestScene();
        pScene.runThisTest();
    },

    previousCallback:function(sender){
        cc.Director.getInstance().replaceScene(ControlSceneManager.getInstance().previousControlScene());
    },
    restartCallback:function(sender){
        cc.Director.getInstance().replaceScene(ControlSceneManager.getInstance().currentControlScene());
    },
    nextCallback:function(sender){
        cc.Director.getInstance().replaceScene(ControlSceneManager.getInstance().nextControlScene());
    }
});

ControlScene.create = function(title){
   var scene = cc.Scene.create();
    var controlLayer = new ControlScene();
    if(controlLayer && controlLayer.init()){
        controlLayer.getSceneTitleLabel().setString(title);
        scene.addChild(controlLayer);
    }
    return scene;
};
