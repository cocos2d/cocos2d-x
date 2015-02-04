/****************************************************************************
 Cocos2d-html5 show case : Moon Warriors

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
 FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

 @Authors:
 Programmer: Shengxiang Chen (陈升想), Dingping Lv (吕定平), Ricardo Quesada
 Effects animation: Hao Wu (吴昊)
 Quality Assurance: Sean Lin (林顺)
 ****************************************************************************/

//bullet
var Bullet = cc.Sprite.extend({
    active:true,
    xVelocity:0,
    yVelocity:200,
    power:1,
    HP:1,
    moveType:null,
    zOrder:3000,
    attackMode:MW.ENEMY_MOVE_TYPE.NORMAL,
    parentType:MW.BULLET_TYPE.PLAYER,
    ctor:function (bulletSpeed, weaponType, attackMode) {
        this._super("#"+weaponType);

        this.yVelocity = -bulletSpeed;
        this.attackMode = attackMode;
        //this.setBlendFunc(cc.SRC_ALPHA, cc.ONE);
    },
    update:function (dt) {
        var x = this.x, y = this.y;
        this.x = x - this.xVelocity * dt;
	    this.y = y - this.yVelocity * dt;
        if (x < 0 || x > g_sharedGameLayer.screenRect.width || y < 0 || y > g_sharedGameLayer.screenRect.height || this.HP <= 0) {
            this.destroy();
        }
    },
    destroy:function () {
        var explode = HitEffect.getOrCreateHitEffect(this.x, this.y, Math.random() * 360, 0.75);
        this.active = false;
        this.visible = false;
    },
    hurt:function () {
        this.HP--;
    },
    collideRect:function (x, y) {
        return cc.rect(x - 3, y - 3, 6, 6);
    }
});

Bullet.getOrCreateBullet = function (bulletSpeed, weaponType, attackMode, zOrder, mode) {
    /**/
    var selChild = null;
    if (mode == MW.UNIT_TAG.PLAYER_BULLET) {
        for (var j = 0; j < MW.CONTAINER.PLAYER_BULLETS.length; j++) {
            selChild = MW.CONTAINER.PLAYER_BULLETS[j];
            if (selChild.active == false) {
                selChild.visible = true;
                selChild.HP = 1;
                selChild.active = true;
                return selChild;
            }
        }
    }
    else {
        for (var j = 0; j < MW.CONTAINER.ENEMY_BULLETS.length; j++) {
            selChild = MW.CONTAINER.ENEMY_BULLETS[j];
            if (selChild.active == false) {
                selChild.visible = true;
                selChild.HP = 1;
                selChild.active = true;
                return selChild;
            }
        }
    }
    selChild = Bullet.create(bulletSpeed, weaponType, attackMode, zOrder, mode);
    return selChild;
};

Bullet.create = function (bulletSpeed, weaponType, attackMode, zOrder, mode) {
    var bullet = new Bullet(bulletSpeed, weaponType, attackMode);
    g_sharedGameLayer.addBullet(bullet, zOrder, mode);
    if (mode == MW.UNIT_TAG.PLAYER_BULLET) {
        MW.CONTAINER.PLAYER_BULLETS.push(bullet);
    } else {
        MW.CONTAINER.ENEMY_BULLETS.push(bullet);
    }
    return bullet;
};

Bullet.preSet = function () {
    var bullet = null;
    for (var i = 0; i < 10; i++) {
        var bullet = Bullet.create(MW.BULLET_SPEED.SHIP, "W1.png", MW.ENEMY_ATTACK_MODE.NORMAL, 3000, MW.UNIT_TAG.PLAYER_BULLET);
        bullet.visible = false;
        bullet.active = false;
    }
    for (var i = 0; i < 10; i++) {
        bullet = Bullet.create(MW.BULLET_SPEED.ENEMY, "W2.png", MW.ENEMY_ATTACK_MODE.NORMAL, 3000, MW.UNIT_TAG.ENMEY_BULLET);
        bullet.visible = false;
        bullet.active = false;
    }
};
