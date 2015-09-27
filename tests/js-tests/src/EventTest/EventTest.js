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

var TEXT_INPUT_FONT_NAME = "Thonburi";
var TEXT_INPUT_FONT_SIZE = 36;

var sceneIdx = -1;

/**
 @brief EventTest for retain prev, reset, next, main menu buttons.
 */
var EventTest = cc.Layer.extend({
    ctor:function() {
        this._super();
        this.init();
    },

    restartCallback:function (sender) {
        var s = new EventTestScene();
        s.addChild(restartEventsTest());
        director.runScene(s);
    },
    nextCallback:function (sender) {
        var s = new EventTestScene();
        s.addChild(nextEventsTest());
        director.runScene(s);
    },
    backCallback:function (sender) {
        var s = new EventTestScene();
        s.addChild(previousEventsTest());
        director.runScene(s);
    },

    title:function () {
        return "Event Test";
    },

    onEnter:function () {
        this._super();

        var s = director.getWinSize();

        var label = new cc.LabelTTF(this.title(), "Arial", 24);
        this.addChild(label);
        label.x = s.width / 2;
        label.y = s.height - 50;

        var subTitle = this.subtitle();
        if (subTitle && subTitle !== "") {
            var l = new cc.LabelTTF(subTitle, "Thonburi", 16);
            this.addChild(l, 1);
            l.x = s.width / 2;
            l.y = s.height - 80;
        }

        var item1 = new cc.MenuItemImage(s_pathB1, s_pathB2, this.backCallback, this);
        var item2 = new cc.MenuItemImage(s_pathR1, s_pathR2, this.restartCallback, this);
        var item3 = new cc.MenuItemImage(s_pathF1, s_pathF2, this.nextCallback, this);

        var menu = new cc.Menu(item1, item2, item3);
        menu.x = 0;
        menu.y = 0;
        item1.x = s.width / 2 - 100;
        item1.y = 30;
        item2.x = s.width / 2;
        item2.y = 30;
        item3.x = s.width / 2 + 100;
        item3.y = 30;

        this.addChild(menu, 1);
    }
});

//------------------------------------------------------------------
//
// OneByOne Touches
//
//------------------------------------------------------------------
var TouchOneByOneTest = EventTest.extend({
    init:function () {
        this._super();
        this.ids = {};
        this.unused_sprites = [];

        if( 'touches' in cc.sys.capabilities ) {
            cc.eventManager.addListener({
                event: cc.EventListener.TOUCH_ONE_BY_ONE,
                swallowTouches: true,
                onTouchBegan: this.onTouchBegan,
                onTouchMoved: this.onTouchMoved,
                onTouchEnded: this.onTouchEnded,
                onTouchCancelled: this.onTouchCancelled
            }, this);
        } else {
            cc.log("TOUCH-ONE-BY-ONE test is not supported on desktop");
        }

        for( var i=0; i < 5;i++) {
            var sprite = this.sprite = new cc.Sprite(s_pathR2);
            this.addChild(sprite,i+10);
            sprite.x = 0;
            sprite.y = 0;
            sprite.scale = 1;
            sprite.color = cc.color( Math.random()*200+55, Math.random()*200+55, Math.random()*200+55 );
            this.unused_sprites.push(sprite);
        }
    },
    subtitle:function () {
        return "Touches One by One. Touch the left / right and see console";
    },

    new_id:function( id, pos) {
        var s = this.unused_sprites.pop();
        this.ids[ id ] = s;
        s.x = pos.x;
        s.y = pos.y;
    },
    update_id:function(id, pos) {
        var s = this.ids[ id ];
        s.x = pos.x;
        s.y = pos.y;
    },
    release_id:function(id, pos) {
        var s = this.ids[ id ];
        this.ids[ id ] = null;
        this.unused_sprites.push( s );
        s.x = 0;
        s.y = 0;
    },

    onTouchBegan:function(touch, event) {
        var pos = touch.getLocation();
        var id = touch.getID();
        cc.log("onTouchBegan at: " + pos.x + " " + pos.y + " Id:" + id );
        if( pos.x < winSize.width/2) {
            event.getCurrentTarget().new_id(id,pos);
            return true;
        }
        return false;
    },
    onTouchMoved:function(touch, event) {
        var pos = touch.getLocation();
        var id = touch.getID();
        cc.log("onTouchMoved at: " + pos.x + " " + pos.y + " Id:" + id );
        event.getCurrentTarget().update_id(id,pos);
    },
    onTouchEnded:function(touch, event) {
        var pos = touch.getLocation();
        var id = touch.getID();
        cc.log("onTouchEnded at: " + pos.x + " " + pos.y + " Id:" + id );
        event.getCurrentTarget().release_id(id,pos);
    },
    onTouchCancelled:function(touch, event) {
        var pos = touch.getLocation();
        var id = touch.getID();
        cc.log("onTouchCancelled at: " + pos.x + " " + pos.y + " Id:" + id );
        event.getCurrentTarget().update_id(id,pos);
    }
});

//------------------------------------------------------------------
//
// All At Once Touches
//
//------------------------------------------------------------------
var TouchAllAtOnce = EventTest.extend({
    init:function () {
        this._super();

        this.ids = {};
        this.unused_sprites = [];

        if( 'touches' in cc.sys.capabilities ) {
            // this is the default behavior. No need to set it explicitly.
            cc.eventManager.addListener({
                event: cc.EventListener.TOUCH_ALL_AT_ONCE,
                onTouchesBegan: this.onTouchesBegan,
                onTouchesMoved: this.onTouchesMoved,
                onTouchesEnded: this.onTouchesEnded,
                onTouchesCancelled: this.onTouchesCancelled
            }, this);
        } else {
            cc.log("TOUCHES not supported");
        }

        for( var i=0; i < 5;i++) {
            var sprite = this.sprite = new cc.Sprite(s_pathR2);
            this.addChild(sprite,i+10);
            sprite.x = 0;
            sprite.y = 0;
            sprite.scale = 1;
            sprite.color = cc.color( Math.random()*200+55, Math.random()*200+55, Math.random()*200+55 );
            this.unused_sprites.push(sprite);
        }
    },
    subtitle:function () {
        return "Touches All At Once. Touch and see console";
    },

    new_id:function( id, pos) {
        var s = this.unused_sprites.pop();
        this.ids[ id ] = s;
        s.x = pos.x;
        s.y = pos.y;
    },
    update_id:function(id, pos) {
        var s = this.ids[ id ];
        s.x = pos.x;
        s.y = pos.y;
    },
    release_id:function(id, pos) {
        var s = this.ids[ id ];
        this.ids[ id ] = null;
        this.unused_sprites.push( s );
        s.x = 0;
        s.y = 0;
    },

    onTouchesBegan:function(touches, event) {
        var target = event.getCurrentTarget();
        for (var i=0; i < touches.length;i++ ) {
            var touch = touches[i];
            var pos = touch.getLocation();
            var id = touch.getID();
            cc.log("Touch #" + i + ". onTouchesBegan at: " + pos.x + " " + pos.y + " Id:" + id);
            target.new_id(id,pos);
        }
    },
    onTouchesMoved:function(touches, event) {
        var target = event.getCurrentTarget();
        for (var i=0; i < touches.length;i++ ) {
            var touch = touches[i];
            var pos = touch.getLocation();
            var id = touch.getID();
            cc.log("Touch #" + i + ". onTouchesMoved at: " + pos.x + " " + pos.y + " Id:" + id);
            target.update_id(id, pos);
        }
    },
    onTouchesEnded:function(touches, event) {
        var target = event.getCurrentTarget();
        for (var i=0; i < touches.length;i++ ) {
            var touch = touches[i];
            var pos = touch.getLocation();
            var id = touch.getID();
            cc.log("Touch #" + i + ". onTouchesEnded at: " + pos.x + " " + pos.y + " Id:" + id);
            target.release_id(id);
        }
    },
    onTouchesCancelled:function(touches, event) {
        var target = event.getCurrentTarget();
        for (var i=0; i < touches.length;i++ ) {
            var touch = touches[i];
            var pos = touch.getLocation();
            var id = touch.getID();
            cc.log("Touch #" + i + ". onTouchesCancelled at: " + pos.x + " " + pos.y + " Id:" + id);
            target.release_id(id);
        }
    }
});

//------------------------------------------------------------------
//
// Accelerometer test
//
//------------------------------------------------------------------
var AccelerometerTest = EventTest.extend({
    _logIndex:0,
    init:function () {
        this._super();

        if( 'accelerometer' in cc.sys.capabilities ) {
            var self = this;
            // call is called 30 times per second
            cc.inputManager.setAccelerometerInterval(1/30);
            cc.inputManager.setAccelerometerEnabled(true);
            cc.eventManager.addListener({
                event: cc.EventListener.ACCELERATION,
                callback: function(accelEvent, event){
                    var target = event.getCurrentTarget();
                    self._logIndex++;
                    if (self._logIndex > 20)
                    {
                        cc.log('Accel x: '+ accelEvent.x + ' y:' + accelEvent.y + ' z:' + accelEvent.z + ' time:' + accelEvent.timestamp );    
                        self._logIndex = 0;
                    }
                    

                    var w = winSize.width;
                    var h = winSize.height;

                    var x = w * accelEvent.x + w/2;
                    var y = h * accelEvent.y + h/2;

                    // Low pass filter
                    x = x*0.2 + target.prevX*0.8;
                    y = y*0.2 + target.prevY*0.8;

                    target.prevX = x;
                    target.prevY = y;
                    target.sprite.x = x;
                    target.sprite.y = y ;
                }
            }, this);

            var sprite = this.sprite = new cc.Sprite(s_pathR2);
            this.addChild( sprite );
            sprite.x = winSize.width/2;
            sprite.y = winSize.height/2;

            // for low-pass filter
            this.prevX = 0;
            this.prevY = 0;
        } else {
            cc.log("ACCELEROMETER not supported");
        }
    },

    onExit: function(){
        this._super();
        if( 'accelerometer' in cc.sys.capabilities )
            cc.inputManager.setAccelerometerEnabled(false);
    },

    subtitle:function () {
        return "Accelerometer test. Move device and see console";
    }
});

//------------------------------------------------------------------
//
// Mouse test
//
//------------------------------------------------------------------
var MouseTest = EventTest.extend({
    init:function () {
        this._super();
        var sprite = this.sprite = new cc.Sprite(s_pathR2);
        this.addChild(sprite);
        sprite.x = 0;
        sprite.y = 0;
        sprite.scale = 1;
        sprite.color = cc.color(Math.random()*200+55, Math.random()*200+55, Math.random()*200+55);

        if( 'mouse' in cc.sys.capabilities ) {
            cc.eventManager.addListener({
                 event: cc.EventListener.MOUSE,
                onMouseDown: function(event){
                    var pos = event.getLocation(), target = event.getCurrentTarget();
                    if(event.getButton() === cc.EventMouse.BUTTON_RIGHT)
                        cc.log("onRightMouseDown at: " + pos.x + " " + pos.y );
                    else if(event.getButton() === cc.EventMouse.BUTTON_LEFT)
                        cc.log("onLeftMouseDown at: " + pos.x + " " + pos.y );
                    target.sprite.x = pos.x;
                    target.sprite.y = pos.y;
                },
                onMouseMove: function(event){
                    var pos = event.getLocation(), target = event.getCurrentTarget();
                    cc.log("onMouseMove at: " + pos.x + " " + pos.y );
                    target.sprite.x = pos.x;
                    target.sprite.y = pos.y;
                },
                onMouseUp: function(event){
                    var pos = event.getLocation(), target = event.getCurrentTarget();
                    target.sprite.x = pos.x;
                    target.sprite.y = pos.y;
                    cc.log("onMouseUp at: " + pos.x + " " + pos.y );
                }
            }, this);
        } else {
            cc.log("MOUSE Not supported");
        }
    },
    subtitle:function () {
        return "Mouse test. Move mouse and see console";
    }
});

//------------------------------------------------------------------
//
// Keyboard test
//
//------------------------------------------------------------------
var KeyboardTest = EventTest.extend({
    init: function () {
        this._super();
        var self = this;
        var label = new cc.LabelTTF("show key Code");
        var size = cc.director.getWinSize();
        label.setPosition(size.width / 2, size.height / 2);
        this.addChild(label);
        if ('keyboard' in cc.sys.capabilities) {
            cc.eventManager.addListener({
                event: cc.EventListener.KEYBOARD,
                onKeyPressed: function (key, event) {
                    var strTemp = "Key down:" + key;
                    var keyStr = self.getKeyStr(key);
                    if (keyStr.length > 0)
                    {
                        strTemp += " the key name is:" + keyStr;
                    }
                    label.setString(strTemp);
                },
                onKeyReleased: function (key, event) {
                    var strTemp = "Key up:" + key;
                    var keyStr = self.getKeyStr(key);
                    if (keyStr.length > 0)
                    {
                        strTemp += " the key name is:" + keyStr;
                    }
                    label.setString(strTemp);
                }
            }, this);
        } else {
            cc.log("KEYBOARD Not supported");
        }
    },
    getKeyStr: function (keycode)
    {
        if (keycode == cc.KEY.none)
        {
            return "";
        }

        for (var keyTemp in cc.KEY)
        {
            if (cc.KEY[keyTemp] == keycode)
            {
                return keyTemp;
            }
        }
        return "";
    },
    subtitle:function () {
        return "Keyboard test. Press keyboard and see console";
    },

    // this callback is only available on JSB + OS X
    // Not supported on cocos2d-html5
    onKeyFlagsChanged:function(key) {
        cc.log("Key flags changed:" + key);
    }
});


var EventTestScene = TestScene.extend({
    runThisTest:function (num) {
        sceneIdx = (num || num == 0) ? (num - 1) : -1;
        var layer = nextEventsTest();
        // var menu = new EventTest();
        // menu.addKeyboardNotificationLayer( layer );

        this.addChild(layer);
        director.runScene(this);
    }
});

//
// Flow control
//
var arrayOfEventsTest = [
    TouchOneByOneTest,
    TouchAllAtOnce,
    AccelerometerTest,
    MouseTest,
    KeyboardTest
];

var nextEventsTest = function () {
    sceneIdx++;
    sceneIdx = sceneIdx % arrayOfEventsTest.length;

    if(window.sideIndexBar){
        sceneIdx = window.sideIndexBar.changeTest(sceneIdx, 12);
    }

    return new arrayOfEventsTest[sceneIdx]();
};
var previousEventsTest = function () {
    sceneIdx--;
    if (sceneIdx < 0)
        sceneIdx += arrayOfEventsTest.length;

    if(window.sideIndexBar){
        sceneIdx = window.sideIndexBar.changeTest(sceneIdx, 12);
    }

    return new arrayOfEventsTest[sceneIdx]();
};
var restartEventsTest = function () {
    return new arrayOfEventsTest[sceneIdx]();
};

