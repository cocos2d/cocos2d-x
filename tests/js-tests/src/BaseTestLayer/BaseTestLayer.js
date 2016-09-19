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

var BASE_TEST_MENUITEM_PREV_TAG = 1;
var BASE_TEST_MENUITEM_RESET_TAG = 2;
var BASE_TEST_MENUITEM_NEXT_TAG = 3;

var BASE_TEST_MENU_TAG = 10;
var BASE_TEST_TITLE_TAG = 11;
var BASE_TEST_SUBTITLE_TAG = 12;


var autoTestEnabled = autoTestEnabled || false;
var autoTestCurrentTestName = autoTestCurrentTestName || "N/A";

var BaseTestLayerProps = {

    ctor:function(colorA, colorB ) {

        // default gradient colors
        var a = cc.color(98,99,117,255);
        var b = cc.color(0,0,0,255);

        if( arguments.length >= 1 )
            a = colorA;
        if( arguments.length == 2 )
            b = colorB;

        // for automation, no gradient. helps for grabbing the screen if needed
        if( autoTestEnabled ) {
            a = cc.color(0,0,0,255);
            b = cc.color(0,0,0,255);
        }

        this._super( a, b );

        // Update winsize in case it was resized
        winSize = director.getWinSize();

        if( autoTestEnabled ) {
            this.totalNumberOfTests = this.numberOfPendingTests();
            this.scheduleOnce( this.endTest, this.testDuration );

            this.setupAutomation();
        }
    },

    setupAutomation:function() {
        // override me
        // Will be called only if automation is activated
    },

    getTitle:function() {
        var t = "";

        // some tests use "this.title()" and others use "this._title";
        if( 'title' in this )
            t = this.title();
        else if('_title' in this || this._title)
            t = this._title;
        return t;
    },
    getSubtitle:function() {
        var st = "";
        // some tests use "this.subtitle()" and others use "this._subtitle";
        if(this.subtitle)
            st = this.subtitle();
        else if(this._subtitle)
            st = this._subtitle;

        return st;
    },
    log:function(str) {
        if( !autoTestEnabled )
            cc.log(str);
    },
    //
    // Menu
    //
    onEnter:function () {
        this._super();

        cc.sys.garbageCollect();

        var t = this.getTitle();
        var label = new cc.LabelTTF(t, "Arial", 28);
        this.addChild(label, 100, BASE_TEST_TITLE_TAG);
        label.x = winSize.width / 2;
        label.y = winSize.height - 50;

        var st = this.getSubtitle();
        if (st) {
            var l = new cc.LabelTTF(st.toString(), "Thonburi", 16);
            this.addChild(l, 101, BASE_TEST_SUBTITLE_TAG);
            l.x = winSize.width / 2;
            l.y = winSize.height - 80;
        }

        var item1 = new cc.MenuItemImage(s_pathB1, s_pathB2, this.onBackCallback, this);
        var item2 = new cc.MenuItemImage(s_pathR1, s_pathR2, this.onRestartCallback, this);
        var item3 = new cc.MenuItemImage(s_pathF1, s_pathF2, this.onNextCallback, this);

        item1.tag = BASE_TEST_MENUITEM_PREV_TAG;
        item2.tag = BASE_TEST_MENUITEM_RESET_TAG;
        item3.tag = BASE_TEST_MENUITEM_NEXT_TAG;

        var menu = new cc.Menu(item1, item2, item3);

        menu.x = 0;
        menu.y = 0;
        var width = item2.width, height = item2.height;
        item1.x =  winSize.width/2 - width*2;
        item1.y = height/2 ;
        item2.x =  winSize.width/2;
        item2.y = height/2 ;
        item3.x =  winSize.width/2 + width*2;
        item3.y = height/2 ;

        this.addChild(menu, 102, BASE_TEST_MENU_TAG);
    },
    onRestartCallback:function (sender) {
        // override me
    },
    onNextCallback:function (sender) {
        // override me
    },
    onBackCallback:function (sender) {
        // override me
    },
    //------------------------------------------
    //
    // Automation Test code
    //
    //------------------------------------------

    // How many seconds should this test run
    testDuration:0.25,

    // Automated test
    getExpectedResult:function() {
        // Override me
        throw "Not Implemented";
    },

    // Automated test
    getCurrentResult:function() {
        // Override me
        throw "Not Implemented";
    },

    compareResults:function(current, expected) {
        return (current == expected);
    },

    tearDown:function(dt) {

        // Override to have a different behavior
        var current = this.getCurrentResult();
        var expected = this.getExpectedResult();

        var ret = this.compareResults(current, expected);
        if( ! ret )
            this.errorDescription = "Expected value: '" + expected + "'. Current value'" + current +  "'.";

        return ret;
    },

    endTest:function(dt) {

        this.errorDescription = "";
        var title = this.getTitle();

        try {
            if( this.tearDown(dt) ) {
                // Test OK
                cc.log( autoTestCurrentTestName + " - " + this.getTestNumber() + ": Test '" + title + "':' OK");
            } else {
                // Test failed
                cc.log( autoTestCurrentTestName + " - " +this.getTestNumber() + ": Test '" + title + "': Error: " + this.errorDescription );
            }
        } catch(err) {
            cc.log( autoTestCurrentTestName + " - " +this.getTestNumber() + ": Test '" + title + "':'" + err);
        }

        this.runNextTest();
    },

    numberOfPendingTests:function() {
        // override me. Should return true if the last test was executed
        throw "Override me: numberOfPendingTests";
    },

    getTestNumber:function() {
        throw "Override me: getTestNumber";
    },

    runNextTest:function() {
        if( this.numberOfPendingTests() <= 0 ) {
            var scene = new cc.Scene();
            var layer = new TestController();
            scene.addChild(layer);
            director.runScene(scene);
        } else
            try {
                this.onNextCallback(this);
            } catch (err) {
                cc.log( autoTestCurrentTestName + " - " +this.getTestNumber() + ": Test '" + this.getTitle() + "':'" + err);
                this.runNextTest();
            }
    },


    containsPixel: function(arr, pix, approx, range) {

    range = range || 50.0;
    approx = approx || false;

        var abs = function(a,b) {
        return ((a-b) > 0) ? (a-b) : (b-a);
    };

    var pixelEqual = function(pix1, pix2) {
        if(approx && abs(pix1, pix2) < range) return true;
        else if(!approx && pix1 == pix2) return true;
        return false;
    };


        for(var i=0; i < arr.length; i += 4) {
        if(pixelEqual(arr[i], pix[0]) && pixelEqual(arr[i + 1], pix[1]) &&
           pixelEqual(arr[i + 2], pix[2]) && pixelEqual(arr[i + 3], pix[3])) {
                return true;
            }
        }
        return false;
    },

    readPixels:function(x,y,w,h) {
        if( 'opengl' in cc.sys.capabilities) {
            var size = 4 * w * h;
            var array = new Uint8Array(size);
            gl.readPixels(x, y, w, h, gl.RGBA, gl.UNSIGNED_BYTE, array);
            return array;
        } else {
            // implement a canvas-html5 readpixels
            return cc._renderContext.getImageData(x, winSize.height-y-h, w, h).data;
        }
    },

    //
    // Useful for comparing results
    // From: http://stackoverflow.com/a/1359808
    //
    sortObject:function(o) {
        var sorted = {},
        key, a = [];

        for (key in o) {
            if (o.hasOwnProperty(key)) {
                a.push(key);
            }
        }

        a.sort();

        for (key = 0; key < a.length; key++) {
            sorted[a[key]] = o[a[key]];
        }
        return sorted;
    }
};

var BaseTestLayer = cc.LayerGradient.extend(BaseTestLayerProps);

var FlowControl = function (testArray) {

    var sceneIdx = 0;

    return {
        length: testArray.length,
        getId: function () {
            return sceneIdx;
        },
        next: function () {
            sceneIdx++;
            sceneIdx = sceneIdx % testArray.length;

            return new testArray[sceneIdx]();
        },
        previous: function () {
            sceneIdx--;
            if (sceneIdx < 0)
                sceneIdx += testArray.length;

            return new testArray[sceneIdx]();
        },
        current: function () {
            return new testArray[sceneIdx]();
        },
        start: function() {
            sceneIdx = 0;
            var s = new cc.Scene();
            s.addChild(this.current());
            cc.director.runScene(s);
        }
    }
};