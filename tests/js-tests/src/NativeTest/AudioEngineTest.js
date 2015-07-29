/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.

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

(function (window) {

//------------------------------------------------------------------
//
// AudioEngineBase
//
//------------------------------------------------------------------
var AudioEngineBase = BaseTestLayer.extend({
    _title:"New Audio Engine Test",
    _subtitle:"",

    ctor:function() {
        this._super(cc.color(0,0,0,255), cc.color(98,99,117,255));
        var label = new cc.LabelTTF("Back", "Arial", 20);
        var menuItem = new cc.MenuItemLabel(label, this.backtoNativeTest, this);
        var menu = new cc.Menu(menuItem);
        menu.x = 0;
        menu.y = 0;
        menuItem.x = winSize.width - 50;
        menuItem.y = 25;
        this.addChild(menu, 1);
    },
    backtoNativeTest:function(sender) {
        new NativeTestScene().runThisTest();
    },
    onRestartCallback:function (sender) {
        var s = new cc.Scene();
        s.addChild(FlowControl.current());
        director.runScene(s);
    },
    onNextCallback:function (sender) {
        var s = new cc.Scene();
        s.addChild(FlowControl.next());
        director.runScene(s);
    },
    onBackCallback:function (sender) {
        var s = new cc.Scene();
        s.addChild(FlowControl.previous());
        director.runScene(s);
    },
    // automation
    numberOfPendingTests:function() {
        return ( (AudioTestFlow.length-1) - AudioTestFlow.getId() );
    },
    getTestNumber:function() {
        return AudioTestFlow.getId();
    },
    onExit: function () {
        jsb.AudioEngine.stopAll();
        this._super();
    }
});

var TextButton = ccui.Button.extend({
    ctor: function (text, callback) {
        this._super();

        this.setTouchEnabled(true);
        this.loadTextures("ccs-res/cocosui/animationbuttonnormal.png", "ccs-res/cocosui/animationbuttonpressed.png", "");
        this.setTitleText(text);
        this.addTouchEventListener(callback, this);
    }
});

var Slider = ccui.Slider.extend({
    _ratio: 0,
    ctor: function () {
        this._super();
        this.setTouchEnabled(true);
        this.loadBarTexture("ccs-res/cocosui/sliderTrack.png");
        this.loadSlidBallTextures("ccs-res/cocosui/sliderThumb.png", "ccs-res/cocosui/sliderThumb.png", "");
        this.loadProgressBarTexture("ccs-res/cocosui/sliderProgress.png");
    },
    setRatio: function(ratio) {
        ratio = cc.clampf(ratio, 0, 1);
        
        this._ratio = ratio;
        this.setPercent(100 * this._ratio);
    },
    getRatio: function () {
        return this._ratio;
    }
});

var AudioControlTest = AudioEngineBase.extend({
    _title:"Audio control test",
    
    _audioID: jsb.AudioEngine.INVALID_AUDIO_ID,
    _loopEnabled: false,
    _volume: 1,
    _duration: jsb.AudioEngine.TIME_UNKNOWN,
    _timeRatio: 0,
    _updateTimeSlider: true,

    _playItem: null,
    _timeSlider: null,

    ctor: function () {
        this._super();
        
        var fontFilePath = "fonts/arial.ttf";
        
        var layerSize = this.getContentSize();
        
        var self = this;
        this._playItem = new TextButton("play", function(button){
            if (self._audioID === jsb.AudioEngine.INVALID_AUDIO_ID) {
                self._audioID = jsb.AudioEngine.play2d("background.mp3", self._loopEnabled, self._volume);
                
                if(self._audioID !== jsb.AudioEngine.INVALID_AUDIO_ID) {
                    button.setEnabled(false);
                    jsb.AudioEngine.setFinishCallback(self._audioID, function(id, filePath){
                        self._audioID = jsb.AudioEngine.INVALID_AUDIO_ID;
                        self._playItem.setEnabled(true);
                        
                        self._timeRatio = 0;
                        self._timeSlider.setRatio(self._timeRatio);
                    });
                }
            }
        });
        this._playItem.setPosition(layerSize.width * 0.3, layerSize.height * 0.8);
        this.addChild(this._playItem);
        
        var stopItem = new TextButton("stop", function(button) {
            if (self._audioID !== jsb.AudioEngine.INVALID_AUDIO_ID ) {
                jsb.AudioEngine.stop(self._audioID);
                
                self._audioID = jsb.AudioEngine.INVALID_AUDIO_ID;
                self._playItem.setEnabled(true);
            }
        });
        stopItem.setPosition(layerSize.width * 0.7, layerSize.height * 0.8);
        this.addChild(stopItem);
        
        var pauseItem = new TextButton("pause", function(button) {
            if (self._audioID !== jsb.AudioEngine.INVALID_AUDIO_ID ) {
                jsb.AudioEngine.pause(self._audioID);
            }
        });
        pauseItem.setPosition(layerSize.width * 0.3, layerSize.height * 0.7);
        this.addChild(pauseItem);
        
        var resumeItem = new TextButton("resume", function(button) {
            if (self._audioID !== jsb.AudioEngine.INVALID_AUDIO_ID ) {
                jsb.AudioEngine.resume(self._audioID);
            }
        });
        resumeItem.setPosition(layerSize.width * 0.7, layerSize.height * 0.7);
        this.addChild(resumeItem);
        
        var loopItem = new TextButton("enable-loop", function(button) {
            self._loopEnabled = !self._loopEnabled;

            if (self._audioID !== jsb.AudioEngine.INVALID_AUDIO_ID) {
                jsb.AudioEngine.setLoop(self._audioID, self._loopEnabled);
            }
            if (self._loopEnabled){
                button.setTitleText("disable-loop");
            }
            else {
                button.setTitleText("enable-loop");
            }
        });
        loopItem.setPosition(cc.p(layerSize.width * 0.5, layerSize.height * 0.5));
        this.addChild(loopItem);
        
        var preloadItem = new TextButton("preload", function(button){
            jsb.AudioEngine.preload("background.mp3");
        });
        preloadItem.setPosition(layerSize.width * 0.3, layerSize.height * 0.6);
        this.addChild(preloadItem);

        var uncacheItem = new TextButton("uncache", function(button){
            jsb.AudioEngine.uncache("background.mp3");
            
            self._audioID = jsb.AudioEngine.INVALID_AUDIO_ID;
            self._playItem.setEnabled(true);
        });
        uncacheItem.setPosition(layerSize.width * 0.7, layerSize.height * 0.6);
        this.addChild(uncacheItem);
        
        var volumeSlider = new Slider();
        volumeSlider.setPercent(100);
        volumeSlider.addEventListener(function(slider, event){
            self._volume = slider.getRatio();
            if (self._audioID !== jsb.AudioEngine.INVALID_AUDIO_ID ) {
                jsb.AudioEngine.setVolume(self._audioID, self._volume);
            }
        });
        volumeSlider.setPosition(cc.p(layerSize.width * 0.5, layerSize.height * 0.35));
        this.addChild(volumeSlider);
        
        var timeSlider = new Slider();
        timeSlider.addEventListener(function(slider, event) {
            switch(event){
                case ccui.Slider.EventType.ON_PERCENTAGE_CHANGED:
                case ccui.Slider.EventType.ON_SLIDEBALL_DOWN:
                    self._updateTimeSlider = false;
                    break;
                case ccui.Slider.EventType.ON_SLIDEBALL_UP:
                    if (self._audioID !== jsb.AudioEngine.INVALID_AUDIO_ID && 
                        self._duration !== jsb.AudioEngine.TIME_UNKNOWN) {
                        var ratio = slider.getPercent() / 100;
                        ratio = cc.clampf(ratio, 0, 1);
                        jsb.AudioEngine.setCurrentTime(self._audioID, self._duration * ratio);
                        slider.setRatio(ratio);
                    }
                case ccui.Slider.EventType.ON_SLIDEBALL_CANCEL:
                    self._updateTimeSlider = true;
                    break;
            }
        });
        timeSlider.setPosition(cc.p(layerSize.width * 0.5, layerSize.height * 0.25));
        this.addChild(timeSlider);
        this._timeSlider = timeSlider;
        
        var volumeSliderPos = volumeSlider.getPosition();
        var sliderSize = volumeSlider.getContentSize();
        var volumeLabel = new cc.LabelTTF("volume:  ", "Arial", 20);
        volumeLabel.setAnchorPoint(cc.p(1, 0.5));
        volumeLabel.setPosition(volumeSliderPos.x - sliderSize.width / 2, volumeSliderPos.y);
        this.addChild(volumeLabel);
        
        var timeSliderPos = timeSlider.getPosition();
        var timeLabel = new cc.LabelTTF("time:  ", "Arial", 20);
        timeLabel.setAnchorPoint(cc.p(1, 0.5));
        timeLabel.setPosition(timeSliderPos.x - sliderSize.width / 2, timeSliderPos.y);
        this.addChild(timeLabel);
        
        this.schedule(this.update, 0.1);
    },

    update: function (dt) {
        if (this._audioID !== jsb.AudioEngine.INVALID_AUDIO_ID ) {
            if(this._duration === jsb.AudioEngine.TIME_UNKNOWN){
                this._duration = jsb.AudioEngine.getDuration(_audioID);
            }
            if(this._duration != jsb.AudioEngine.TIME_UNKNOWN){
                var time = jsb.AudioEngine.getCurrentTime(this._audioID);
                this._timeRatio = time / this._duration;
                if(this._updateTimeSlider){
                    this._timeSlider.setRatio(this._timeRatio);
                }
            }
        }
    }
});

window.AudioTestFlow = new FlowControl([
    AudioControlTest,
    PlaySimultaneouslyTest,
    AudioProfileTest,
    InvalidAudioFileTest,
    LargeAudioFileTest
]);

})(window);