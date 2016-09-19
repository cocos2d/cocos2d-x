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

var UIS9NinePatchTest = UIMainLayer.extend({
    init: function () {
        if (this._super()) {
            //init text
            this._topDisplayLabel.setString("");
            this._bottomDisplayLabel.setString("");

            cc.spriteFrameCache.addSpriteFrames("ccs-res/cocosui/android9patch.plist");
    
            var winSize = director.getWinSize();
            var x = winSize.width / 2;
            var y = 0 + (winSize.height / 2 + 50);
    
            var preferedSize = cc.size(99,99);
    
            //9-patch sprite with filename
            var playerSprite = new cc.Scale9Sprite("ccs-res/cocosui/player.9.png");
            playerSprite.setPosition(x, y);
            playerSprite.setContentSize(preferedSize);
            var capInsets = playerSprite.getCapInsets();
            cc.log("player sprite capInset = " + capInsets.x + ", " + capInsets.y + " " + capInsets.width + ", " + capInsets.height);
            this.addChild(playerSprite);
    
            var animationBtnSprite = new cc.Scale9Sprite("animationbuttonpressed.png");
            animationBtnSprite.setPosition(x-100, y-100);
            capInsets = animationBtnSprite.getCapInsets();
            cc.log("animationBtnSprite capInset = " + capInsets.x + ", " + capInsets.y + " " + capInsets.width + ", " + capInsets.height);
            this.addChild(animationBtnSprite);
            
            
            var monsterSprite = new cc.Scale9Sprite("monster.9.png");
            monsterSprite.setPosition(x+100, y-100);
            capInsets = monsterSprite.getCapInsets();
            monsterSprite.setContentSize(preferedSize);
            cc.log("monsterSprite capInset = ", + capInsets.x + ", " + capInsets.y + " " + capInsets.width + ", " + capInsets.height);
            this.addChild(monsterSprite);
    
            var spriteFrame = cc.spriteFrameCache.getSpriteFrame("buttonnormal.9.png");
            var buttonScale9Sprite = new cc.Scale9Sprite(spriteFrame);
            buttonScale9Sprite.setContentSize(cc.size(150,80));
            buttonScale9Sprite.setPosition(cc.p(100,200));
            this.addChild(buttonScale9Sprite);

            return true;
        }
        return false;
    }
});
