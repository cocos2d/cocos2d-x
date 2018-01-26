/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

Player = cc.ComponentJS.extend({
    generateProjectile: function (x, y) {
        var projectile = new cc.Sprite("components/Projectile.png", cc.rect(0, 0, 20, 20));
        var scriptComponent = new cc.ComponentJS("src/ComponentTest/projectile.js");
        projectile.addComponent(scriptComponent);
        this.getOwner().getParent().addChild(projectile);

        // set position
        var winSize = cc.director.getVisibleSize();
        var visibleOrigin = cc.director.getVisibleOrigin();
        projectile.setPosition(cc.p(visibleOrigin.x + 20, visibleOrigin.y + winSize.height/2));

        // run action
        var posX = projectile.getPositionX();
        var posY = projectile.getPositionY();
        var offX = x - posX;
        var offY = y - posY;

        if (offX <= 0) {
            return;
        }

        var contentSize = projectile.getContentSize();
        var realX = visibleOrigin.x + winSize.width + contentSize.width/2;
        var ratio = offY / offX;
        var realY = (realX * ratio) + posY;
        var realDest = cc.p(realX, realY);

        var offRealX = realX - posX;
        var offRealY = realY - posY;
        var length = Math.sqrt((offRealX * offRealX) + (offRealY * offRealY));
        var velocity = 960;
        var realMoveDuration = length / velocity;

        projectile.runAction(cc.moveTo(realMoveDuration, realDest));
    },

    onEnter: function() {
        var owner = this.getOwner();
        owner.playerComponent = this;
        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesEnded: function (touches, event) {
                var target = event.getCurrentTarget();
                if (target.playerComponent) {
                    var location = touches[0].getLocation();
                    target.playerComponent.generateProjectile(location.x, location.y);
                    jsb.AudioEngine.play2d("pew-pew-lei.wav");
                }
            }
        }, owner);
    }
});