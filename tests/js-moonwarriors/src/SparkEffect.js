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

var SparkEffect = cc.Class.extend({
    active:true,
    spark1:null,
    spark2:null,
    scale:1.2,
    duration:0.7,
    ctor:function () {
        this.spark1 = new cc.Sprite("#explode2.png");
        //this.spark1.setBlendFunc(cc.SRC_ALPHA, cc.ONE);
        this.spark2 = new cc.Sprite("#explode3.png");
        //this.spark2.setBlendFunc(cc.SRC_ALPHA, cc.ONE);
    },
    reset:function (x, y) {
        this.spark1.attr({
	        x: x,
	        y: y,
	        scale: this.scale,
	        opacity: 255
        });
        this.spark2.attr({
	        x: x,
	        y: y,
	        scale: this.scale,
	        rotation: Math.random() * 360,
	        opacity: 255
        });

        var right = cc.rotateBy(this.duration, 45);
        var scaleBy = cc.scaleBy(this.duration, 3, 3);
        var seq = cc.sequence(cc.fadeOut(this.duration), cc.callFunc(this.destroy, this));

        this.spark1.runAction(right);
        this.spark1.runAction(scaleBy);
        this.spark1.runAction(seq);

        this.spark2.runAction(scaleBy.clone());
        this.spark2.runAction(seq.clone());
    },
    destroy:function () {
        this.active = false;
        this.spark1.visible = false;
        this.spark2.visible = false;
    }
});

SparkEffect.getOrCreateSparkEffect = function (x, y) {
    var selChild = null;
    for (var j = 0; j < MW.CONTAINER.SPARKS.length; j++) {
        selChild = MW.CONTAINER.SPARKS[j];
        if (selChild.active == false) {
            selChild.active = true;
            selChild.spark1.setVisible(true);
            selChild.spark2.setVisible(true);
            selChild.reset(x, y);
            return selChild;
        }
    }
    var spark = SparkEffect.create();
    spark.reset(x, y);
    return spark;
};

SparkEffect.create = function () {
    var sparkEffect = new SparkEffect();
    g_sharedGameLayer.addSpark(sparkEffect.spark1);
    g_sharedGameLayer.addSpark(sparkEffect.spark2);
    MW.CONTAINER.SPARKS.push(sparkEffect);
    return sparkEffect;
};

SparkEffect.preSet = function () {
    var sparkEffect = null;
    for (var i = 0; i < 6; i++) {
        sparkEffect = SparkEffect.create();
        sparkEffect.active = false;
        sparkEffect.spark1.visible = false;
        sparkEffect.spark2.visible = false;
    }
};
