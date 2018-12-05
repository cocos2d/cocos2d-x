/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
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



var IntervalLayer = cc.LayerGradient.extend({

    label0:null,
    label1:null,
    label2:null,
    label3:null,
    label4:null,

    time0:null,
    time1:null,
    time2:null,
    time3:null,
    time4:null,

    ctor:function () {
        this._super(cc.color(0,0,0,255), cc.color(98,99,117,255));

        this.time0 = this.time1 = this.time2 = this.time3 = this.time4 = 0.0;

        var s = director.getWinSize();
        // sun
        var sun = new cc.ParticleSun();
        sun.texture = cc.textureCache.addImage(s_fire);
        sun.x = s.width - 32;
        sun.y = s.height - 32;

        sun.setTotalParticles(130);
        sun.setLife(0.6);
        this.addChild(sun);

        // timers, font "fonts/bitmapFontTest4.fnt"
        this.label0 = cc.Label.createWithBMFont("fonts/bitmapFontTest4.fnt", 24);
        this.label1 = cc.Label.createWithBMFont("fonts/bitmapFontTest4.fnt", 24);
        this.label2 = cc.Label.createWithBMFont("fonts/bitmapFontTest4.fnt", 24);
        this.label3 = cc.Label.createWithBMFont("fonts/bitmapFontTest4.fnt", 24);
        this.label4 = cc.Label.createWithBMFont("fonts/bitmapFontTest4.fnt", 24);

        this.scheduleUpdate();
        this.schedule(this.step1);
        this.schedule(this.step2, 0);
        this.schedule(this.step3, 1.0);
        this.schedule(this.step4, 2.0);

        this.label0.x = s.width * 1 / 6;
        this.label0.y = s.height / 2;
        this.label1.x = s.width * 2 / 6;
        this.label1.y = s.height / 2;
        this.label2.x = s.width * 3 / 6;
        this.label2.y = s.height / 2;
        this.label3.x = s.width * 4 / 6;
        this.label3.y = s.height / 2;
        this.label4.x = s.width * 5 / 6;
        this.label4.y = s.height / 2;

        this.addChild(this.label0);
        this.addChild(this.label1);
        this.addChild(this.label2);
        this.addChild(this.label3);
        this.addChild(this.label4);

        // Sprite
        var sprite = new cc.Sprite(s_pathGrossini);
        sprite.x = 40;
        sprite.y = 50;

        var jump = cc.jumpBy(3, cc.p(s.width - 80, 0), 50, 4);

        this.addChild(sprite);
        sprite.runAction(cc.sequence(jump, jump.reverse()).repeatForever());

        // pause button
        var item1 = new cc.MenuItemFont("Pause", this.onPause, this);
        var menu = new cc.Menu(item1);
        menu.x = s.width / 2;
        menu.y = s.height - 50;

        this.addChild(menu);

    },

    onPause:function (sender) {
        if (director.isPaused()) {
            director.resume();
        } else {
            director.pause();
        }
    },

    onExit:function () {
        if (director.isPaused()) {
            director.resume();
        }
        this._super();
    },

    step1:function (dt) {
        this.time1 += dt;
        this.label1.setString(this.time1.toFixed(1));
    },
    step2:function (dt) {
        this.time2 += dt;
        this.label2.setString(this.time2.toFixed(1));
    },
    step3:function (dt) {
        this.time3 += dt;
        this.label3.setString(this.time3.toFixed(1));
    },
    step4:function (dt) {
        this.time4 += dt;
        this.label4.setString(this.time4.toFixed(1));
    },
    update:function (dt) {
        this.time0 += dt;

        this.label0.setString(this.time0.toFixed(1));
    }

    //CREATE_NODE(IntervalLayer);
});

var IntervalTestScene = TestScene.extend({

    runThisTest:function () {
        var layer = new IntervalLayer();
        this.addChild(layer);
        director.runScene(this);
    }
});
