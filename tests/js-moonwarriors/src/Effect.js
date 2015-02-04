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

var flareEffect = function (flare,target, callback) {
    flare.stopAllActions();
    flare.setBlendFunc(cc.SRC_ALPHA, cc.ONE);
    flare.attr({
	    x: -45,
	    y: MW.FLAREY,
	    visible: true,
	    opacity: 0,
		rotation: -120,
		scale: 0.3
	});

    var opacityAnim = cc.fadeTo(0.5, 255);
    var opacDim = cc.fadeTo(1, 0);
    var biggerEase = cc.scaleBy(0.7, 1.2, 1.2).easing(cc.easeSineOut());
    var easeMove = cc.moveBy(0.5, cc.p(490, 0)).easing(cc.easeSineOut());
    var rotateEase = cc.rotateBy(2.5, 90).easing(cc.easeExponentialOut());
    var bigger = cc.scaleTo(0.5, 1);

    var onComplete = cc.callFunc(callback, target);
    var killflare = cc.callFunc(function () {
        this.parent.removeChild(this,true);
    }, flare);
    flare.runAction(cc.sequence(opacityAnim, biggerEase, opacDim, killflare, onComplete));
    flare.runAction(easeMove);
    flare.runAction(rotateEase);
    flare.runAction(bigger);
};

var removeFromParent = function( sprite )
{
    sprite.removeFromParent();
};

var spark = function (x, y, parent, scale, duration) {
    scale = scale || 0.3;
    duration = duration || 0.5;

    var one = new cc.Sprite("#explode1.png");
    var two = new cc.Sprite("#explode2.png");
    var three = new cc.Sprite("#explode3.png");

    one.attr({
	    x: x,
	    y: y,
	    scale: scale
    });
	two.attr({
		x: x,
		y: y,
		scale: scale
	});
	three.attr({
		x: x,
		y: y,
		scale: scale,
		rotation: Math.random() * 360
	});

    //parent.addChild(one);
    parent.addSpark(two);
    parent.addSpark(three);

    var left = cc.rotateBy(duration, -45);
    var right = cc.rotateBy(duration, 45);
    var scaleBy = cc.scaleBy(duration, 3, 3);
    var fadeOut = cc.fadeOut(duration);
    var remove = cc.callFunc(removeFromParent, this);
    var seq = cc.sequence( fadeOut, remove );

    one.runAction(left);
    two.runAction(right);

    one.runAction(scaleBy);
    two.runAction(scaleBy.clone());
    three.runAction(scaleBy.clone());

    one.runAction(seq);
    two.runAction(seq.clone() );
    three.runAction(seq.clone());
};

