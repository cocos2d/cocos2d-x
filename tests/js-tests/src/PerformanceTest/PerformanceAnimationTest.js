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

var s_nAnimationCurCase = 0;
////////////////////////////////////////////////////////
//
// AnimationLayer
//
////////////////////////////////////////////////////////
var AnimationMenuLayer = PerformBasicLayer.extend({
    showCurrentTest:function () {
        var scene = null;
        switch (this._curCase) {
            case 0:
                scene = AnimationTest.scene();
                break;
        }
        s_nAnimationCurCase = this._curCase;

        if (scene) {
            cc.director.runScene(scene);
        }
    },

    onEnter:function () {
        this._super();

        var s = cc.director.getWinSize();

        // Title
        var label = new cc.LabelTTF(this.title(), "Arial", 40);
        this.addChild(label, 1);
        label.x = s.width / 2;
        label.y = s.height - 32;
        label.color = cc.color(255, 255, 40);

        // Subtitle
        var strSubTitle = this.subtitle();
        if (strSubTitle.length) {
            var l = new cc.LabelTTF(strSubTitle, "Thonburi", 16);
            this.addChild(l, 1);
            l.x = s.width / 2;
            l.y = s.height - 80;
        }

    },
    title:function () {
        return "no title";
    },
    subtitle:function () {
        return "no subtitle";
    },
    performTests:function () {

    }
});

////////////////////////////////////////////////////////
//
// AnimationTest
//
////////////////////////////////////////////////////////
var AnimationTest = AnimationMenuLayer.extend({
    numNodes:null,
    lastRenderedCount:null,
    moveLayerList:null,
    init:function () {
        this._super();

        var size = cc.director.getWinSize();

        cc.MenuItemFont.setFontSize(65);
        var decrease = new cc.MenuItemFont(" - ", this.onDecrease, this);
        decrease.color = cc.color(0, 200, 20);
        var increase = new cc.MenuItemFont(" + ", this.onIncrease, this);
        increase.color = cc.color(0, 200, 20);

        var menu = new cc.Menu(decrease, increase);
        menu.alignItemsHorizontally();
        menu.x = size.width / 2;
        menu.y = size.height / 2 + 100;
        this.addChild(menu, 1);

        var infoLabel = new cc.LabelTTF("0 nodes", "Marker Felt", 24);
        infoLabel.color = cc.color(0, 200, 20);
        infoLabel.x = size.width / 2;
        infoLabel.y = size.height - 90;
        this.addChild(infoLabel, 1, TAG_INFO_LAYER);
        this.numNodes = 0;
        this.moveLayerList = [];
        this.createMovieClip();
        //this.scheduleUpdate();
    },
    performTests:function () {
        this.init();
    },
    title:function () {
        return "Animation Performance Test";
    },
    subtitle:function () {
        return "";
    },
    createMovieClip:function () {
        var moveLayer = new cc.Node();
        this.addChild(moveLayer);
        this.moveLayerList.push(moveLayer);
        var size = cc.director.getWinSize();
        for(var i=0; i<10; i++) {
            var character = new CharacterView();
            character.init();
            character.x = size.width /2 - i*15 - 200;
            character.y = size.height /2 - i*15;
            this.numNodes++;
            cc.log("create"+this.numNodes);
            moveLayer.addChild(character, 0, this.numNodes);
        }
        var action = cc.moveBy(1, cc.p(20,0));
        moveLayer.runAction(action.repeatForever());
        this.updateNodes();
    },
    onIncrease:function () {
        this.createMovieClip();
    },
    onDecrease:function () {
        if(this.numNodes > 0) {
            var moveLayer = this.moveLayerList[this.moveLayerList.length-1];
            for(var i=0;i<10;i++) {
                cc.log("remove"+this.numNodes);
                moveLayer.removeChildByTag(this.numNodes, true);
                this.numNodes--;
            }
            moveLayer.removeFromParent(true);
            this.moveLayerList.pop();
        }
        this.updateNodes();
    },
    updateNodes:function () {
        if (this.numNodes != this.lastRenderedCount) {
            var infoLabel = this.getChildByTag(TAG_INFO_LAYER);
            var str = this.numNodes + " nodes";
            infoLabel.setString(str);

            this.lastRenderedCount = this.numNodes;
        }
    }
});

var CharacterView = cc.Node.extend({
    leftData:null,
    leftItem:null,
    rightData:null,
    rightItem:null,
    leftX:null,

    init: function() {
        this._super();
        cc.spriteFrameCache.addSpriteFrames("animations/crystals.plist");
        var i = 0;
        rightData = new Array(10);
        for (i = 0; i < 10; i++) {
            var right = new cc.Sprite("#crystals/4.png");
            right.x = 50;
            right.y = i * 10 - 40;
            right.rotation = -90;
            right.scale = 1;
            this.addChild(right);

            rightData[i] = right;
            if (i == 0) {
                rightItem = right;
            }
        }

        for(i=0; i<10; i++){
            var head = new cc.Sprite("#crystals/1.png");
            head.x = i * 5;
            head.y = 50;
            this.addChild(head);
            head.scale = 1.5;
            head.rotation = 350;
            var rotateToA = cc.rotateBy(0.01, 5);
            head.runAction(rotateToA.repeatForever());
        }

        leftData = new Array(10);
        for(i=0; i<10; i++){
            var left = new cc.Sprite("#crystals/2.png");
            left.x = 10;
            left.y = i * 5 - 20;
            left.rotation = 90;
            this.addChild(left);
            //var moveStep = cc.moveBy(0.01, cc.p(-5,0));
        //  left.runAction(moveStep);
            leftData[i] = left;
            if(i==0){
                leftItem = left;
            }
        }

    },

    setDistance: function(){
        leftX = leftItem.x;
    }
});

AnimationTest.scene = function () {
    var scene = new cc.Scene();
    var layer = new AnimationTest(false, 1, s_nAnimationCurCase);
    scene.addChild(layer);
    return scene;
};
function runAnimationTest() {
    s_nAnimationCurCase = 0;
    var scene = AnimationTest.scene();
    cc.director.runScene(scene);
}
