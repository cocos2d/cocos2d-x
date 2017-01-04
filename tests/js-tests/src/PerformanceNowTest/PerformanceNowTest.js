var scenePerformanceNowTestIdx = -1;

var PerformanceNowBaseLayer = BaseTestLayer.extend({
    ctor:function () {
        this._super(cc.color(0,0,0,255), cc.color(98,99,117,255) );
    },

    title:function () {
        return "performance.now";
    },

    subtitle:function () {
        return "";
    },

    code:function () {
        return "";
    },

    // callbacks
    onRestartCallback:function (sender) {
        var s = new PerformanceNowTestScene();
        s.addChild(restartPerformanceNowTest());
        director.runScene(s);
    },
    onNextCallback:function (sender) {
        var s = new PerformanceNowTestScene();
        s.addChild(nextPerformanceNowTest());
        director.runScene(s);
    },
    onBackCallback:function (sender) {
        var s = new PerformanceNowTestScene();
        s.addChild(previousPerformanceNowTest());
        director.runScene(s);
    },

    // automation
    numberOfPendingTests:function() {
        return ( (arrayOfPerformanceNowTest.length-1) - scenePerformanceNowTestIdx );
    },

    getTestNumber:function() {
        return scenePerformanceNowTestIdx;
    }
});

//------------------------------------------------------------------
//
// Tests
//
//------------------------------------------------------------------
var BasicPerformanceNowTest = PerformanceNowBaseLayer.extend({
    onEnter:function () {
        this._super();
        if (performance && typeof performance.now === 'function') {
            var currentPerformanceNow = new cc.LabelTTF("Current time since start : " + performance.now());
            this.addChild(currentPerformanceNow);   
            currentPerformanceNow.attr({
                x: cc.winSize.width/2,
                y: cc.winSize.height/2
            });            
        } else {
            var errLabel = new cc.LabelTTF("On browser that does not support performance.now");
            this.addChild(errLabel);   
            errLabel.attr({
                x: cc.winSize.width/2,
                y: cc.winSize.height/2
            });            

        }
    },

    title: function() {
        return "Basic performance.now functionality";
    },

    subtitle:function () {
        return "Should display number, or say not supported";
    }
});

var MonotonicIncreaseTest = PerformanceNowBaseLayer.extend({
    ctor:function () {
        this._super();
        if (performance && typeof performance.now !== 'function') {
             var errLabel = new cc.LabelTTF("On browser that does not support performance.now");
            this.addChild(errLabel);   
            errLabel.attr({
                x: cc.winSize.width/2,
                y: cc.winSize.height/2
            });          
            return;
        }


        var performanceValues = [];
        for (var i = 0; i < 20; ++i) {
            performanceValues.push(performance.now().toFixed(3));
        }

        var monotonicIncrease = false;
        for (var i = 1; i < performanceValues.length; ++i) {
            monotonicIncrease = performanceValues[i] >= performanceValues[i - 1];
        }

        var label = new cc.LabelTTF("Result that values are montonically increasing : " + monotonicIncrease);
        label.attr({
            x: cc.winSize.width/2,
            y: cc.winSize.height/2
        });
        this.addChild(label);

        var values = new cc.LabelTTF("Result Values : " + JSON.stringify(performanceValues));
        values.attr({
            x: cc.winSize.width/2,
            y: (cc.winSize.height/2) - 40
        });        
        this.addChild(values);

    },

    title:function () {
        return "Testing monotonic increase of performance.now";
    },

    subtitle:function () {
        return "Listed values should all be increasing";
    }
});

var PerformanceNowTestScene = TestScene.extend({
    runThisTest:function (num) {
        scenePerformanceNowTestIdx = (num || num == 0) ? (num - 1) : -1;
        var layer = nextPerformanceNowTest();
        this.addChild(layer);

        director.runScene(this);
    }
});

//
// Flow control
//
var arrayOfPerformanceNowTest = [
    BasicPerformanceNowTest,
    MonotonicIncreaseTest
];

var nextPerformanceNowTest = function () {
    scenePerformanceNowTestIdx++;
    scenePerformanceNowTestIdx = scenePerformanceNowTestIdx % arrayOfPerformanceNowTest.length;

    return new arrayOfPerformanceNowTest[scenePerformanceNowTestIdx]();
};
var previousPerformanceNowTest = function () {
    scenePerformanceNowTestIdx--;
    if (scenePerformanceNowTestIdx < 0)
        scenePerformanceNowTestIdx += arrayOfPerformanceNowTest.length;

    return new arrayOfPerformanceNowTest[scenePerformanceNowTestIdx]();
};
var restartPerformanceNowTest = function () {
    return new arrayOfPerformanceNowTest[scenePerformanceNowTestIdx]();
};
