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

var HitEffect = cc.Sprite.extend({
    active:true,
    ctor:function () {
        this._super("#hit.png");
        this.setBlendFunc(cc.SRC_ALPHA, cc.ONE);
    },
    reset:function (x, y, rotation, scale) {
        this.attr({
	        x: x,
	        y: y,
	        rotation: rotation,
	        scale: scale
        });
        this.runAction(cc.scaleBy(0.3, 2, 2));
        this.runAction(cc.sequence(cc.fadeOut(0.3), cc.callFunc(this.destroy, this)));
    },
    destroy:function () {
        this.visible = false;
        this.active = false;
    }
});

HitEffect.getOrCreateHitEffect = function (x, y, rotation, scale) {
    var selChild = null;
    for (var j = 0; j < MW.CONTAINER.HITS.length; j++) {
        selChild = MW.CONTAINER.HITS[j];
        if (selChild.active == false) {
            selChild.visible = true;
            selChild.active = true;
            selChild.reset(x, y, rotation, scale);
            return selChild;
        }
    }
    selChild = HitEffect.create();
    selChild.reset(x, y, rotation, scale);
    return selChild;
};

HitEffect.create = function () {
    var hitEffect = new HitEffect();
    g_sharedGameLayer.addBulletHits(hitEffect, 9999);
    MW.CONTAINER.HITS.push(hitEffect);
    return hitEffect;
};

HitEffect.preSet = function () {
    var hitEffect = null;
    for (var i = 0; i < 10; i++) {
        hitEffect = HitEffect.create();
        hitEffect.setVisible(false);
        hitEffect.active = false;
    }
};
