/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
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
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

/**
 * Audio support in the browser
 *
 * multichannel : Multiple audio while playing - If it doesn't, you can only play background music
 * webAudio     : Support for WebAudio - Support W3C WebAudio standards, all of the audio can be played
 * auto         : Supports auto-play audio - if Don‘t support it, On a touch detecting background music canvas, and then replay
 * replay       : The first music will fail, must be replay after touchstart
 * emptied      : Whether to use the emptied event to replace load callback
 * delay        : delay created the context object - only webAudio
 *
 * May be modifications for a few browser version
 */
(function(){

    var DEBUG = false;

    var sys = cc.sys;

    var supportTable = {
        "common" : {multichannel: true , webAudio: cc.sys._supportWebAudio , auto: true }
    };
    supportTable[sys.BROWSER_TYPE_IE]  = {multichannel: true , webAudio: cc.sys._supportWebAudio , auto: true, emptied: true};
    //  ANDROID  //
    supportTable[sys.BROWSER_TYPE_ANDROID]  = {multichannel: false, webAudio: false, auto: false};
    supportTable[sys.BROWSER_TYPE_CHROME]   = {multichannel: true , webAudio: true , auto: false};
    supportTable[sys.BROWSER_TYPE_FIREFOX]  = {multichannel: true , webAudio: true , auto: true , delay: true};
    supportTable[sys.BROWSER_TYPE_UC]       = {multichannel: true , webAudio: false, auto: false};
    supportTable[sys.BROWSER_TYPE_QQ]       = {multichannel: false, webAudio: false, auto: true };
    supportTable[sys.BROWSER_TYPE_OUPENG]   = {multichannel: false, webAudio: false, auto: false, replay: true , emptied: true };
    supportTable[sys.BROWSER_TYPE_WECHAT]   = {multichannel: false, webAudio: false, auto: false, replay: true , emptied: true };
    supportTable[sys.BROWSER_TYPE_360]      = {multichannel: false, webAudio: false, auto: true };
    supportTable[sys.BROWSER_TYPE_MIUI]     = {multichannel: false, webAudio: false, auto: true };
    supportTable[sys.BROWSER_TYPE_LIEBAO]   = {multichannel: false, webAudio: false, auto: false, replay: true , emptied: true };
    supportTable[sys.BROWSER_TYPE_SOUGOU]   = {multichannel: false, webAudio: false, auto: false, replay: true , emptied: true };
    //"Baidu" browser can automatically play
    //But because it may be play failed, so need to replay and auto
    supportTable[sys.BROWSER_TYPE_BAIDU]    = {multichannel: false, webAudio: false, auto: false, replay: true , emptied: true };
    supportTable[sys.BROWSER_TYPE_BAIDU_APP]= {multichannel: false, webAudio: false, auto: false, replay: true , emptied: true };

    //  APPLE  //
    supportTable[sys.BROWSER_TYPE_SAFARI]  = {multichannel: true , webAudio: true , auto: false, webAudioCallback: function(realUrl){
        document.createElement("audio").src = realUrl;
    }};

    /* Determine the browser version number */
    var version, tmp;
    try{
        var ua = navigator.userAgent.toLowerCase();
        switch(sys.browserType){
            case sys.BROWSER_TYPE_IE:
                tmp = ua.match(/(msie |rv:)([\d.]+)/);
                break;
            case sys.BROWSER_TYPE_FIREFOX:
                tmp = ua.match(/(firefox\/|rv:)([\d.]+)/);
                break;
            case sys.BROWSER_TYPE_CHROME:
                tmp = ua.match(/chrome\/([\d.]+)/);
                break;
            case sys.BROWSER_TYPE_BAIDU:
                tmp = ua.match(/baidubrowser\/([\d.]+)/);
                break;
            case sys.BROWSER_TYPE_UC:
                tmp = ua.match(/ucbrowser\/([\d.]+)/);
                break;
            case sys.BROWSER_TYPE_QQ:
                tmp = ua.match(/qqbrowser\/([\d.]+)/);
                break;
            case sys.BROWSER_TYPE_OUPENG:
                tmp = ua.match(/oupeng\/([\d.]+)/);
                break;
            case sys.BROWSER_TYPE_WECHAT:
                tmp = ua.match(/micromessenger\/([\d.]+)/);
                break;
            case sys.BROWSER_TYPE_SAFARI:
                tmp = ua.match(/safari\/([\d.]+)/);
                break;
            case sys.BROWSER_TYPE_MIUI:
                tmp = ua.match(/miuibrowser\/([\d.]+)/);
                break;
        }
        version = tmp ? tmp[1] : "";
    }catch(e){
        console.log(e);
    }

    ///////////////////////////
    //  Browser compatibility//
    ///////////////////////////
    if(version){
        switch(sys.browserType){
            case sys.BROWSER_TYPE_CHROME:
                if(parseInt(version) < 30){
                    supportTable[sys.BROWSER_TYPE_CHROME]  = {multichannel: false , webAudio: true , auto: false};
                }
                break;
            case sys.BROWSER_TYPE_MIUI:
                version = version.match(/\d+/g);
                if(version[0] < 2 || (version[0] === 2 && version[1] === 0 && version[2] <= 1)){
                    supportTable[sys.BROWSER_TYPE_MIUI].auto = false;
                }
                break;
        }
    }

    if(cc.sys.isMobile){
        if(cc.sys.os !== cc.sys.OS_IOS)
            cc.__audioSupport = supportTable[sys.browserType] || supportTable["common"];
        else
            cc.__audioSupport = supportTable[sys.BROWSER_TYPE_SAFARI];
    }else{
      switch(sys.browserType){
          case sys.BROWSER_TYPE_IE:
              cc.__audioSupport = supportTable[sys.BROWSER_TYPE_IE];
              break;
          case sys.BROWSER_TYPE_FIREFOX:
              cc.__audioSupport = supportTable[sys.BROWSER_TYPE_FIREFOX];
              break;
          default:
              cc.__audioSupport = supportTable["common"];
      }
    }

    if(DEBUG){
        setTimeout(function(){
            cc.log("browse type: " + sys.browserType);
            cc.log("browse version: " + version);
            cc.log("multichannel: " + cc.__audioSupport.multichannel);
            cc.log("webAudio: " + cc.__audioSupport.webAudio);
            cc.log("auto: " + cc.__audioSupport.auto);
        }, 0);
    }

})();

/**
 * Encapsulate DOM and webAudio
 */
cc.Audio = cc.Class.extend({
    //TODO Maybe loader shift in will be better
    volume: 1,
    loop: false,
    src: null,
    _touch: false,

    _playing: false,
    _AUDIO_TYPE: "AUDIO",
    _pause: false,

    //Web Audio
    _buffer: null,
    _currentSource: null,
    _startTime: null,
    _currentTime: null,
    _context: null,
    _volume: null,

    _ignoreEnded: false,

    //DOM Audio
    _element: null,

    ctor: function(context, volume, url){
        context && (this._context = context);
        volume && (this._volume = volume);
        if(context && volume){
            this._AUDIO_TYPE = "WEBAUDIO";
        }
        this.src = url;
    },

    _setBufferCallback: null,
    setBuffer: function(buffer){
        if(!buffer) return;
        var playing = this._playing;
        this._AUDIO_TYPE = "WEBAUDIO";

        if(this._buffer && this._buffer !== buffer && this.getPlaying())
            this.stop();

        this._buffer = buffer;
        if(playing)
            this.play();

        this._volume["gain"].value = this.volume;
        this._setBufferCallback && this._setBufferCallback(buffer);
    },

    _setElementCallback: null,
    setElement: function(element){
        if(!element) return;
        var playing = this._playing;
        this._AUDIO_TYPE = "AUDIO";

        if(this._element && this._element !== element && this.getPlaying())
            this.stop();

        this._element = element;
        if(playing)
            this.play();

        element.volume = this.volume;
        element.loop = this.loop;
        this._setElementCallback && this._setElementCallback(element);
    },

    play: function(offset, loop){
        this._playing = true;
        this.loop = loop === undefined ? this.loop : loop;
        if(this._AUDIO_TYPE === "AUDIO"){
            this._playOfAudio(offset);
        }else{
            this._playOfWebAudio(offset);
        }
    },

    getPlaying: function(){
        if(!this._playing){
            return this._playing;
        }
        if(this._AUDIO_TYPE === "AUDIO"){
            var audio = this._element;
            if(!audio || this._pause){
                this._playing = false;
                return false;
            }else if(audio.ended){
                this._playing = false;
                return false;
            }else
                return true;
        }else{
            var sourceNode = this._currentSource;
            if(!sourceNode)
                return true;
            if(sourceNode["playbackState"] == null)
                return this._playing;
            else
                return this._currentTime + this._context.currentTime - this._startTime < this._currentSource.buffer.duration;
        }
    },

    _playOfWebAudio: function(offset){
        var cs = this._currentSource;
        if(!this._buffer){
            return;
        }
        if(!this._pause && cs){
            if(this._context.currentTime === 0 || this._currentTime + this._context.currentTime - this._startTime > this._currentSource.buffer.duration)
                this._stopOfWebAudio();
            else
                return;
        }
        var audio = this._context["createBufferSource"]();
        audio.buffer = this._buffer;
        audio["connect"](this._volume);
        audio.loop = this.loop;
        this._startTime = this._context.currentTime;
        this._currentTime = 0;

        /*
         * Safari on iOS 6 only supports noteOn(), noteGrainOn(), and noteOff() now.(iOS 6.1.3)
         * The latest version of chrome has supported start() and stop()
         * start() & stop() are specified in the latest specification (written on 04/26/2013)
         *      Reference: https://dvcs.w3.org/hg/audio/raw-file/tip/webaudio/specification.html
         * noteOn(), noteGrainOn(), and noteOff() are specified in Draft 13 version (03/13/2012)
         *      Reference: http://www.w3.org/2011/audio/drafts/2WD/Overview.html
         */
        if(audio.start){
            audio.start(0, offset || 0);
        }else if(audio["noteGrainOn"]){
            var duration = audio.buffer.duration;
            if (this.loop) {
                /*
                 * On Safari on iOS 6, if loop == true, the passed in @param duration will be the duration from now on.
                 * In other words, the sound will keep playing the rest of the music all the time.
                 * On latest chrome desktop version, the passed in duration will only be the duration in this cycle.
                 * Now that latest chrome would have start() method, it is prepared for iOS here.
                 */
                audio["noteGrainOn"](0, offset, duration);
            } else {
                audio["noteGrainOn"](0, offset, duration - offset);
            }
        }else {
            // if only noteOn() is supported, resuming sound will NOT work
            audio["noteOn"](0);
        }
        this._currentSource = audio;
        var self = this;
        audio["onended"] = function(){
            if(self._ignoreEnded){
                self._ignoreEnded = false;
            }else{
                self._playing = false;
            }
        };
    },

    _playOfAudio: function(){
        var audio = this._element;
        if(audio){
            audio.loop = this.loop;
            audio.play();
        }
    },

    stop: function(){
        this._playing = false;
        if(this._AUDIO_TYPE === "AUDIO"){
            this._stopOfAudio();
        }else{
            this._stopOfWebAudio();
        }
    },

    _stopOfWebAudio: function(){
        var audio = this._currentSource;
        this._ignoreEnded = true;
        if(audio){
            audio.stop(0);
            this._currentSource = null;
        }
    },

    _stopOfAudio: function(){
        var audio = this._element;
        if(audio){
            audio.pause();
            if (audio.duration && audio.duration !== Infinity)
                audio.currentTime = 0;
        }
    },

    pause: function(){
        if(this.getPlaying() === false)
            return;
        this._playing = false;
        this._pause = true;
        if(this._AUDIO_TYPE === "AUDIO"){
            this._pauseOfAudio();
        }else{
            this._pauseOfWebAudio();
        }
    },

    _pauseOfWebAudio: function(){
        this._currentTime += this._context.currentTime - this._startTime;
        var audio = this._currentSource;
        if(audio){
            audio.stop(0);
        }
    },

    _pauseOfAudio: function(){
        var audio = this._element;
        if(audio){
            audio.pause();
        }
    },

    resume: function(){
        if(this._pause){
            if(this._AUDIO_TYPE === "AUDIO"){
                this._resumeOfAudio();
            }else{
                this._resumeOfWebAudio();
            }
            this._pause = false;
            this._playing = true;
        }
    },

    _resumeOfWebAudio: function(){
        var audio = this._currentSource;
        if(audio){
            this._startTime = this._context.currentTime;
            var offset = this._currentTime % audio.buffer.duration;
            this._playOfWebAudio(offset);
        }
    },

    _resumeOfAudio: function(){
        var audio = this._element;
        if(audio){
            audio.play();
        }
    },

    setVolume: function(volume){
        if(volume > 1) volume = 1;
        if(volume < 0) volume = 0;
        this.volume = volume;
        if(this._AUDIO_TYPE === "AUDIO"){
            if(this._element){
                this._element.volume = volume;
            }
        }else{
            if(this._volume){
                this._volume["gain"].value = volume;
            }
        }
    },

    getVolume: function(){
        return this.volume;
    },

    cloneNode: function(){
        var audio, self;
        if(this._AUDIO_TYPE === "AUDIO"){
            audio = new cc.Audio();

            var elem = document.createElement("audio");
            elem.src = this.src;
            audio.setElement(elem);
        }else{
            var volume = this._context["createGain"]();
            volume["gain"].value = 1;
            volume["connect"](this._context["destination"]);
            audio = new cc.Audio(this._context, volume, this.src);
            if(this._buffer){
                audio.setBuffer(this._buffer);
            }else{
                self = this;
                this._setBufferCallback = function(buffer){
                    audio.setBuffer(buffer);
                    self._setBufferCallback = null;
                };
            }
        }
        audio._AUDIO_TYPE = this._AUDIO_TYPE;
        return audio;
    }

});

(function(polyfill){

    var SWA = polyfill.webAudio,
        SWB = polyfill.multichannel,
        SWC = polyfill.auto;

    var support = [];

    (function(){
        var audio = document.createElement("audio");
        if(audio.canPlayType) {
            var ogg = audio.canPlayType('audio/ogg; codecs="vorbis"');
            if (ogg && ogg !== "") support.push(".ogg");
            var mp3 = audio.canPlayType("audio/mpeg");
            if (mp3 && mp3 !== "") support.push(".mp3");
            var wav = audio.canPlayType('audio/wav; codecs="1"');
            if (wav && wav !== "") support.push(".wav");
            var mp4 = audio.canPlayType("audio/mp4");
            if (mp4 && mp4 !== "") support.push(".mp4");
            var m4a = audio.canPlayType("audio/x-m4a");
            if (m4a && m4a !== "") support.push(".m4a");
        }
    })();
    try{
        if(SWA){
            var context = new (window.AudioContext || window.webkitAudioContext || window.mozAudioContext)();
            if(polyfill.delay)
                setTimeout(function(){ context = new (window.AudioContext || window.webkitAudioContext || window.mozAudioContext)(); }, 0);
        }
    }catch(error){
        SWA = false;
        cc.log("browser don't support webAudio");
    }

    var loader = {

        cache: {},

        load: function(realUrl, url, res, cb){

            if(support.length === 0)
                return cb("can not support audio!");

            var i;

            var extname = cc.path.extname(realUrl);

            var typeList = [extname];
            for(i=0; i<support.length; i++){
                if(extname !== support[i]){
                    typeList.push(support[i]);
                }
            }

            var audio;

            if(loader.cache[url])
                return cb(null, loader.cache[url]);

            if(SWA){
                try{
                    var volume = context["createGain"]();
                    volume["gain"].value = 1;
                    volume["connect"](context["destination"]);
                    audio = new cc.Audio(context, volume, realUrl);
                }catch(err){
                    SWA = false;
                    cc.log("browser don't support webAudio");
                    audio = new cc.Audio(null, null, realUrl);
                }
            }else{
                audio = new cc.Audio(null, null, realUrl);
            }

            this.loadAudioFromExtList(realUrl, typeList, audio, cb);

            loader.cache[url] = audio;

        },

        loadAudioFromExtList: function(realUrl, typeList, audio, cb){

            if(typeList.length === 0){
                var ERRSTR = "can not found the resource of audio! Last match url is : ";
                ERRSTR += realUrl.replace(/\.(.*)?$/, "(");
                support.forEach(function(ext){
                    ERRSTR += ext + "|";
                });
                ERRSTR = ERRSTR.replace(/\|$/, ")");
                return cb(ERRSTR);
            }

            realUrl = cc.path.changeExtname(realUrl, typeList.splice(0, 1));

            if(SWA){//Buffer
                if(polyfill.webAudioCallback)
                    polyfill.webAudioCallback(realUrl);
                var request = new XMLHttpRequest();
                request.open("GET", realUrl, true);
                request.responseType = "arraybuffer";

                // Our asynchronous callback
                request.onload = function () {
                    context["decodeAudioData"](request.response, function(buffer){
                        //success
                        audio.setBuffer(buffer);
                        cb(null, audio);
                    }, function(){
                        //error
                        loader.loadAudioFromExtList(realUrl, typeList, audio, cb);
                    });
                };
                request.send();
            }else{//DOM

                var element = document.createElement("audio");
                var cbCheck = false;
                var termination = false;

                var timer = setTimeout(function(){
                    if(element.readyState === 0){
                        emptied();
                    }else{
                        termination = true;
                    	element.pause();
                    	document.body.removeChild(element);
                        cb("audio load timeout : " + realUrl, audio);
                    }
                }, 10000);

                var success = function(){
                    if(!cbCheck){
                    	element.pause();
                    	try { element.currentTime = 0;
                    	element.volume = 1; } catch (e) {}
                    	document.body.removeChild(element);
                        audio.setElement(element);
                        element.removeEventListener("canplaythrough", success, false);
                        element.removeEventListener("error", failure, false);
                        element.removeEventListener("emptied", emptied, false);
                        !termination && cb(null, audio);
                        cbCheck = true;
                        clearTimeout(timer);
                    }
                };

                var failure = function(){
                    if(!cbCheck) return;
                	element.pause();
                	document.body.removeChild(element);
                    element.removeEventListener("canplaythrough", success, false);
                    element.removeEventListener("error", failure, false);
                    element.removeEventListener("emptied", emptied, false);
                    !termination && loader.loadAudioFromExtList(realUrl, typeList, audio, cb);
                    cbCheck = true;
                    clearTimeout(timer);
                };

                var emptied = function(){
                    termination = true;
                    success();
                    cb(null, audio);
                };

                cc._addEventListener(element, "canplaythrough", success, false);
                cc._addEventListener(element, "error", failure, false);
                if(polyfill.emptied)
                    cc._addEventListener(element, "emptied", emptied, false);

                element.src = realUrl;
                document.body.appendChild(element);
                element.volume = 0;
                element.play();
            }

        }
    };
    cc.loader.register(["mp3", "ogg", "wav", "mp4", "m4a"], loader);

    /**
     * cc.audioEngine is the singleton object, it provide simple audio APIs.
     * @namespace
     */
    cc.audioEngine = {
        _currMusic: null,
        _musicVolume: 1,

        /**
         * Indicates whether any background music can be played or not.
         * @returns {boolean} <i>true</i> if the background music is playing, otherwise <i>false</i>
         */
        willPlayMusic: function(){return false;},

        /**
         * Play music.
         * @param {String} url The path of the music file without filename extension.
         * @param {Boolean} loop Whether the music loop or not.
         * @example
         * //example
         * cc.audioEngine.playMusic(path, false);
         */
        playMusic: function(url, loop){
            var bgMusic = this._currMusic;
            if(bgMusic && bgMusic.src !== url && bgMusic.getPlaying()){
                bgMusic.stop();
            }
            var audio = loader.cache[url];
            if(!audio){
                cc.loader.load(url);
                audio = loader.cache[url];
            }
            audio.play(0, loop);
            audio.setVolume(this._musicVolume);
            this._currMusic = audio;
        },

        /**
         * Stop playing music.
         * @param {Boolean} [releaseData] If release the music data or not.As default value is false.
         * @example
         * //example
         * cc.audioEngine.stopMusic();
         */
        stopMusic: function(releaseData){
            var audio = this._currMusic;
            if(audio){
                audio.stop();
                if (releaseData)
                    cc.loader.release(audio.src);
            }
        },

        /**
         * Pause playing music.
         * @example
         * //example
         * cc.audioEngine.pauseMusic();
         */
        pauseMusic: function(){
            var audio = this._currMusic;
            if(audio)
                audio.pause();
        },

        /**
         * Resume playing music.
         * @example
         * //example
         * cc.audioEngine.resumeMusic();
         */
        resumeMusic: function(){
            var audio = this._currMusic;
            if(audio)
                audio.resume();
        },

        /**
         * Rewind playing music.
         * @example
         * //example
         * cc.audioEngine.rewindMusic();
         */
        rewindMusic: function(){
            var audio = this._currMusic;
            if(audio){
                audio.stop();
                audio.play();
            }
        },

        /**
         * The volume of the music max value is 1.0,the min value is 0.0 .
         * @return {Number}
         * @example
         * //example
         * var volume = cc.audioEngine.getMusicVolume();
         */
        getMusicVolume: function(){
            return this._musicVolume;
        },

        /**
         * Set the volume of music.
         * @param {Number} volume Volume must be in 0.0~1.0 .
         * @example
         * //example
         * cc.audioEngine.setMusicVolume(0.5);
         */
        setMusicVolume: function(volume){
            volume = volume - 0;
            if(isNaN(volume)) volume = 1;
            if(volume > 1) volume = 1;
            if(volume < 0) volume = 0;

            this._musicVolume = volume;
            var audio = this._currMusic;
            if(audio){
                audio.setVolume(volume);
            }
        },

        /**
         * Whether the music is playing.
         * @return {Boolean} If is playing return true,or return false.
         * @example
         * //example
         *  if (cc.audioEngine.isMusicPlaying()) {
         *      cc.log("music is playing");
         *  }
         *  else {
         *      cc.log("music is not playing");
         *  }
         */
        isMusicPlaying: function(){
            var audio = this._currMusic;
            if(audio){
                return audio.getPlaying();
            }else{
                return false;
            }
        },

        _audioPool: {},
        _maxAudioInstance: 5,
        _effectVolume: 1,
        /**
         * Play sound effect.
         * @param {String} url The path of the sound effect with filename extension.
         * @param {Boolean} loop Whether to loop the effect playing, default value is false
         * @return {Number|null} the audio id
         * @example
         * //example
         * var soundId = cc.audioEngine.playEffect(path);
         */
        playEffect: function(url, loop){
            //If the browser just support playing single audio
            if(!SWB){
                //Must be forced to shut down
                //Because playing multichannel audio will be stuck in chrome 28 (android)
                return null;
            }

            var effectList = this._audioPool[url];
            if(!effectList){
                effectList = this._audioPool[url] = [];
            }

            var i;

            for(i=0; i<effectList.length; i++){
                if(!effectList[i].getPlaying()){
                    break;
                }
            }

            if(effectList[i]){
                audio = effectList[i];
                audio.setVolume(this._effectVolume);
                audio.play(0, loop);
            }else if(!SWA && i > this._maxAudioInstance){
                cc.log("Error: %s greater than %d", url, this._maxAudioInstance);
            }else{
                var audio = loader.cache[url];
                if(!audio){
                    cc.loader.load(url);
                    audio = loader.cache[url];
                }
                audio = audio.cloneNode();
                audio.setVolume(this._effectVolume);
                audio.loop = loop || false;
                audio.play();
                effectList.push(audio);
            }

            return audio;
        },

        /**
         * Set the volume of sound effects.
         * @param {Number} volume Volume must be in 0.0~1.0 .
         * @example
         * //example
         * cc.audioEngine.setEffectsVolume(0.5);
         */
        setEffectsVolume: function(volume){
            volume = volume - 0;
            if(isNaN(volume)) volume = 1;
            if(volume > 1) volume = 1;
            if(volume < 0) volume = 0;

            this._effectVolume = volume;
            var audioPool = this._audioPool;
            for(var p in audioPool){
                var audioList = audioPool[p];
                if(Array.isArray(audioList))
                    for(var i=0; i<audioList.length; i++){
                        audioList[i].setVolume(volume)
                    }
            }
        },

        /**
         * The volume of the effects max value is 1.0,the min value is 0.0 .
         * @return {Number}
         * @example
         * //example
         * var effectVolume = cc.audioEngine.getEffectsVolume();
         */
        getEffectsVolume: function(){
            return this._effectVolume;
        },

        /**
         * Pause playing sound effect.
         * @param {Number} cc.Audio The return value of function playEffect.
         * @example
         * //example
         * cc.audioEngine.pauseEffect(audioID);
         */
        pauseEffect: function(audio){
            if(audio){
                audio.pause();
            }
        },

        /**
         * Pause all playing sound effect.
         * @example
         * //example
         * cc.audioEngine.pauseAllEffects();
         */
        pauseAllEffects: function(){
            var ap = this._audioPool;
            for(var p in ap){
                var list = ap[p];
                for(var i=0; i<ap[p].length; i++){
                    if(list[i].getPlaying()){
                        list[i].pause();
                    }
                }
            }
        },

        /**
         * Resume playing sound effect.
         * @param {Number} cc.Audio The return value of function playEffect.
         * @audioID
         * //example
         * cc.audioEngine.resumeEffect(audioID);
         */
        resumeEffect: function(audio){
            if(audio)
                audio.resume();
        },

        /**
         * Resume all playing sound effect
         * @example
         * //example
         * cc.audioEngine.resumeAllEffects();
         */
        resumeAllEffects: function(){
            var ap = this._audioPool;
            for(var p in ap){
                var list = ap[p];
                for(var i=0; i<ap[p].length; i++){
                    list[i].resume();
                }
            }
        },

        /**
         * Stop playing sound effect.
         * @param {Number} cc.Audio The return value of function playEffect.
         * @example
         * //example
         * cc.audioEngine.stopEffect(audioID);
         */
        stopEffect: function(audio){
            if(audio)
                audio.stop();
        },

        /**
         * Stop all playing sound effects.
         * @example
         * //example
         * cc.audioEngine.stopAllEffects();
         */
        stopAllEffects: function(){
            var ap = this._audioPool;
            for(var p in ap){
                var list = ap[p];
                for(var i=0; i<ap[p].length; i++){
                    list[i].stop();
                }
            }
        },

        /**
         * Unload the preloaded effect from internal buffer
         * @param {String} url
         * @example
         * //example
         * cc.audioEngine.unloadEffect(EFFECT_FILE);
         */
        unloadEffect: function(url){
            if(!url){
                return;
            }

            cc.loader.release(url);
            var pool = this._audioPool[url];
            if(pool) pool.length = 0;
            delete this._audioPool[url];
            delete loader.cache[url];
        },

        /**
         * End music and effects.
         */
        end: function(){
            this.stopMusic();
            this.stopAllEffects();
        },

        _pauseCache: [],
        _pausePlaying: function(){
            var bgMusic = this._currMusic;
            if(bgMusic && bgMusic.getPlaying()){
                bgMusic.pause();
                this._pauseCache.push(bgMusic);
            }
            var ap = this._audioPool;
            for(var p in ap){
                var list = ap[p];
                for(var i=0; i<ap[p].length; i++){
                    if(list[i].getPlaying()){
                        list[i].pause();
                        this._pauseCache.push(list[i]);
                    }
                }
            }
        },

        _resumePlaying: function(){
            var list = this._pauseCache;
            for(var i=0; i<list.length; i++){
                list[i].resume();
            }
            list.length = 0;
        }
    };

    /**
     * ome browsers must click on the page
     */
    if(!SWC){

        //TODO Did not complete loading
        var reBGM = function(){
            var bg = cc.audioEngine._currMusic;
            if(
                bg &&
                bg._touch === false &&
                bg._playing &&
                bg.getPlaying()
            ){
                bg._touch = true;
                bg.play(0, bg.loop);
                !polyfill.replay && cc._canvas.removeEventListener("touchstart", reBGM);
            }

        };

        setTimeout(function(){
            if(cc._canvas){
                cc._canvas.addEventListener("touchstart", reBGM, false);
            }
        }, 150);
    }

    cc.eventManager.addCustomListener(cc.game.EVENT_HIDE, function () {
        cc.audioEngine._pausePlaying();
    });
    cc.eventManager.addCustomListener(cc.game.EVENT_SHOW, function () {
        cc.audioEngine._resumePlaying();
    });

})(cc.__audioSupport);
