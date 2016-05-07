/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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

//------------------------------------------------------------------
//
// LoaderTestLayer
//
//------------------------------------------------------------------
var LoaderTestLayer = BaseTestLayer.extend({
    _title:"Loader Test",
    _subtitle:"",

    ctor:function() {
        var self = this;
        self._super(cc.color(0,0,0,255), cc.color(98,99,117,255));

        var winSize = cc.winSize;
        cc.loader.load(s_helloWorld, function(err, results){
            if(err){
                cc.log("Failed to load %s.", s_helloWorld);
                return;
            }
            cc.log(s_helloWorld + "--->");
            cc.log(results[0]);
            var bg = new cc.Sprite(s_helloWorld);
            self.addChild(bg);
            bg.x = winSize.width/2;
            bg.y = winSize.height/2;
        });

        cc.loader.load([s_Cowboy_plist, s_Cowboy_png], function(err, results){
            if(err){
                cc.log("Failed to load %s, %s .", s_Cowboy_plist, s_Cowboy_png);
                return;
            }

            cc.log(s_Cowboy_plist + "--->");
            cc.log(results[0]);
            cc.log(s_Cowboy_png + "--->");
            cc.log(results[1]);
            cc.spriteFrameCache.addSpriteFrames(s_Cowboy_plist);
            var frame = new cc.Sprite("#testAnimationResource/1.png");
            self.addChild(frame);
            frame.x = winSize.width/4;
            frame.y = winSize.height/4;
        });


        var str;
        if(cc.sys.isNative)  {
            str = s_lookup_desktop_plist;
        } else if(cc.sys.isMobile) {
            str = s_lookup_mobile_plist;
        } else {
            str = s_lookup_html5_plist;
        }

        cc.loader.loadAliases(str, function(){
            var sprite = new cc.Sprite("grossini.bmp");
            self.addChild( sprite );
            sprite.x = winSize.width/2;
            sprite.y = winSize.height/2;
        });

    },

    onNextCallback: function(){
        var parent = this.getParent();
        parent.removeChild(this);
        parent.addChild(new LoaderCycleLayer());
    }
});

var LoaderCycleLayer = BaseTestLayer.extend({
    _title:"Failed to load Test",
    _subtitle:"",

    ctor: function(){
        BaseTestLayer.prototype.ctor.call(this);
        var index = 0;

        var winSize = cc.director.getWinSize();

        var resultTTF = new cc.LabelTTF("result: unknown");
        resultTTF.x = winSize.width / 2;
        resultTTF.y = winSize.height / 2;

        var t = this,
            cb = function(num){
                resultTTF.setString("result: " + num + " file load failed");
                if(num === 1)
                    resultTTF.setColor(cc.color.GREEN);
                else
                    resultTTF.setColor(cc.color.RED);
                t.addChild(resultTTF);
                if(index < 4)
                    t.test(cb);
            };
        this.createInfo();
        this.regLoad();
        this.test(cb);
    },

    regLoad: function(){
        cc.loader.register(["_test1"], {
            load: function(realUrl, url, res, cb){
                cc.loader.cache[url] = {};
                setTimeout(function(){
                    cb && cb(null, cc.loader.cache[url]);
                    return cc.loader.cache[url];
                }, Math.random()*1000);

            }
        });
        cc.loader.register(["_test2"], {
            load: function(realUrl, url, res, cb){
                cb && cb({});
                return null;
            }
        });
    },

    list: [
        "1._test2",
        "1._test1",
        "2._test1",
        "3._test1",
        "4._test1"
    ],

    createInfo: function(){
        var winSize = cc.director.getWinSize();
        var info1 = new cc.LabelTTF("Load 5 files");
        info1.x = winSize.width / 2;
        info1.y = winSize.height / 2 + 80;
        var info2 = new cc.LabelTTF("1 file does not exist");
        info2.x = winSize.width / 2;
        info2.y = winSize.height / 2 + 60;
        var info3 = new cc.LabelTTF("The other 4 files should be loaded.");
        info3.x = winSize.width / 2;
        info3.y = winSize.height / 2 + 40;

        this.addChild(info1);
        this.addChild(info2);
        this.addChild(info3);
    },

    test: function(cb){
        this.clearRes();
        var layer = this;
        cc.loader.load(layer.list, function(){
            var num = 0;
            layer.list.forEach(function(item){
                if(!cc.loader.getRes(item)){
                    num++;
                }
            });
            cb(num);
        });
    },

    clearRes: function(){
        this.list.forEach(function(item){
            cc.loader.release(item);
        });
    },

    onRestartCallback: function(){
        var parent = this._parent;
        parent.removeChild(this);
        parent.addChild(new LoaderCycleLayer());
    },

    onBackCallback: function(){
        var parent = this._parent;
        parent.removeChild(this);
        parent.addChild(new LoaderTestLayer());
    }
});

var LoaderTestScene = TestScene.extend({
    runThisTest:function () {
        this.addChild(new LoaderTestLayer());
        director.runScene(this);
    }
});