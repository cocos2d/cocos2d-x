/****************************************************************************
Copyright (c) 2013 Zynga Inc.

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

// SimpleAudioEngine implemented here as a thin wrapper over SoundManager 2,
// which will use HTML5 audio where available, and fallback to Flash where
// necessary. Gives a much more reliable audio experience without needing to
// sacrifice clients that do not have Flash available.

var LibrarySimpleAudioEngine = {
    SimpleAudioEngine_init: function()
    {
        Module.CocosDensionState = {
            effectMap: {},
            effectMapNum: {},
            effectVolume: 100,
            numEffectCount: 0,

            musicMap: {},
            musicVolume: 100,
            curBackgroundMusic: null,
            formats: []
        };
    },

    SimpleAudioEngine_setUseFileExt: function(extFiles)
    {
        var exts = Pointer_stringify(extFiles);
        Module.CocosDensionState.formats = exts.split(',');
    },

    SimpleAudioEngine_end: function()
    {
        buzz.all().stop();
    },

    SimpleAudioEngine_isBackgroundMusicPlaying: function()
    {
        if (Module.CocosDensionState.curBackgroundMusic)
        {
            return !Module.CocosDensionState.curBackgroundMusic.isEnded();
        }

        return false;
    },

    SimpleAudioEngine_stopBackgroundMusic: function()
    {
        if (Module.CocosDensionState.curBackgroundMusic)
        {
            Module.CocosDensionState.curBackgroundMusic.stop();
            Module.CocosDensionState.curBackgroundMusic = null;
        }
    },

    SimpleAudioEngine_setBackgroundMusicVolume: function(volume)
    {
        if(volume > 100) volume = 100;
        if(volume < 0) volume = 0;

        Module.CocosDensionState.musicVolume = volume;

        if (Module.CocosDensionState.curBackgroundMusic)
        {
            Module.CocosDensionState.curBackgroundMusic.setVolume(Module.CocosDensionState.musicVolume);
        }
    },    

    SimpleAudioEngine_playBackgroundMusic__deps: [ 'SimpleAudioEngine_stopBackgroundMusic' ],
    SimpleAudioEngine_playBackgroundMusic: function(filenameP, loop)
    {
        var filename = Pointer_stringify(filenameP);
        if(Module.CocosDensionState.formats.length > 0)
            filename = filename.substr(0, filename.lastIndexOf('.'));

        _SimpleAudioEngine_stopBackgroundMusic();

        if(Module.CocosDensionState.musicMap[filename] === undefined)
        {
            var sound = new buzz.sound(filename, {
                                                formats: Module.CocosDensionState.formats,
                                                preload: true,
                                                autoplay: true,
                                                loop: loop,
                                                volume: Module.CocosDensionState.musicVolume
                                                });

            Module.CocosDensionState.curBackgroundMusic = sound;
            Module.CocosDensionState.musicMap[filename] = sound;
        }
        else
        {
            Module.CocosDensionState.curBackgroundMusic = Module.CocosDensionState.musicMap[filename];

            if (loop) 
            {
                Module.CocosDensionState.curBackgroundMusic.loop();
            }
            else
            {
                Module.CocosDensionState.curBackgroundMusic.unloop();
            }

            Module.CocosDensionState.curBackgroundMusic.setVolume(Module.CocosDensionState.musicVolume);            
            Module.CocosDensionState.curBackgroundMusic.play();
        }
    },

    SimpleAudioEngine_preloadBackgroundMusic: function(filenameP)
    {
        var filename = Pointer_stringify(filenameP);
        if(Module.CocosDensionState.formats.length > 0)
            filename = filename.substr(0, filename.lastIndexOf('.'));

        if(Module.CocosDensionState.musicMap[filename] === undefined)
        {
            var sound = new buzz.sound(filename, {
                                                formats: Module.CocosDensionState.formats,
                                                preload: true,
                                                autoplay: false,
                                                volume: Module.CocosDensionState.musicVolume
                                                });
            sound.load();
            Module.CocosDensionState.musicMap[filename] = sound;
        }
    },

    SimpleAudioEngine_pauseBackgroundMusic: function()
    {
        if (Module.CocosDensionState.curBackgroundMusic)
        {
            Module.CocosDensionState.curBackgroundMusic.pause();
        }
    },

    SimpleAudioEngine_rewindBackgroundMusic: function()
    {
        if (Module.CocosDensionState.curBackgroundMusic)
        {
            Module.CocosDensionState.curBackgroundMusic.setTime(0);
        }
    },

    SimpleAudioEngine_resumeBackgroundMusic: function()
    {
        if (Module.CocosDensionState.curBackgroundMusic)
        {
            if (Module.CocosDensionState.curBackgroundMusic.isPaused())
                Module.CocosDensionState.curBackgroundMusic.togglePlay();
        }
    },

    SimpleAudioEngine_playEffect: function(filenameP, loop)
    {
        // XXX: Note that effects, unlike background music, are indexed by an
        // ID number in CocosDenshion, hence we need to maintain a mapping of
        // generated IDs from their filenames in order for this all to
        // function.
        var filename = Pointer_stringify(filenameP);
        if( Module.CocosDensionState.formats.length > 0)
            filename = filename.substr(0, filename.lastIndexOf('.'));
        var numEffect = Module.CocosDensionState.numEffectCount;

        if(Module.CocosDensionState.effectMap[filename] === undefined)
        {
            var sound = new buzz.sound(filename, {
                                                formats: Module.CocosDensionState.formats,
                                                preload: true,
                                                autoplay: true,
                                                loop: loop,
                                                volume: Module.CocosDensionState.effectVolume
                                                });

            Module.CocosDensionState.effectMap[filename] = sound;
            Module.CocosDensionState.effectMapNum[filename] = numEffect;
            Module.CocosDensionState.numEffectCount++;
        }
        else
        {
            numEffect = Module.CocosDensionState.effectMapNum[filename];
            var sound = Module.CocosDensionState.effectMap[filename];

            if (loop) 
            {
                sound.loop();
            }
            else
            {
                sound.unloop();
            }

            sound.setVolume(Module.CocosDensionState.effectVolume);            
            sound.play();
        }

        return numEffect;
    },
    
    SimpleAudioEngine_preloadEffect: function(filenameP)
    {
        var filename = Pointer_stringify(filenameP);
        if( Module.CocosDensionState.formats.length > 0)
            filename = filename.substr(0, filename.lastIndexOf('.'));

        if(Module.CocosDensionState.effectMap[filename] === undefined)
        {
            var sound = new buzz.sound(filename, {
                                                formats: Module.CocosDensionState.formats,
                                                preload: true,
                                                autoplay: false,
                                                volume: Module.CocosDensionState.effectVolume
                                                });
            sound.load();
            Module.CocosDensionState.effectMap[filename] = sound;
            Module.CocosDensionState.effectMapNum[filename] = Module.CocosDensionState.numEffectCount;
            Module.CocosDensionState.numEffectCount++;
        }
    },

    SimpleAudioEngine_stopEffect: function(effectId)
    {
        for(var key in Module.CocosDensionState.effectMapNum)
        {
            var value = Module.CocosDensionState.effectMapNum[key];

            if (value == effectId)
            {
                Module.CocosDensionState.effectMap[key].stop();
            }
        }
    },

    SimpleAudioEngine_setEffectsVolume: function(volume)
    {
        if(volume > 100) volume = 100;
        if(volume < 0) volume = 0;

        Module.CocosDensionState.effectVolume = volume;

        for(var key in Module.CocosDensionState.effectMapNum)
        {
            Module.CocosDensionState.effectMap[key].setVolume(Module.CocosDensionState.effectVolume);
        }
    },

    SimpleAudioEngine_pauseEffect: function(effectId)
    {
        for(var key in Module.CocosDensionState.effectMapNum)
        {
            var value = Module.CocosDensionState.effectMapNum[key];

            if (value == effectId)
            {
                Module.CocosDensionState.effectMap[key].pause();
            }
        }
    },

    SimpleAudioEngine_resumeEffect: function(effectId)
    {
        for(var key in Module.CocosDensionState.effectMapNum)
        {
            var value = Module.CocosDensionState.effectMapNum[key];

            if (value == effectId)
            {
                if (Module.CocosDensionState.effectMap[key].isPaused())
                {
                    Module.CocosDensionState.effectMap[key].togglePlay();
                }
            }
        }
    },

    SimpleAudioEngine_pauseAllEffects: function()
    {
        for(var key in Module.CocosDensionState.effectMapNum)
        {
            Module.CocosDensionState.effectMap[key].pause();
        }
    },

    SimpleAudioEngine_resumeAllEffects: function()
    {
        for(var key in Module.CocosDensionState.effectMapNum)
        {
            if (Module.CocosDensionState.effectMap[key].isPaused())
            {
                Module.CocosDensionState.effectMap[key].togglePlay();
            }
        }
    },

    SimpleAudioEngine_stopAllEffects: function()
    {
        for(var key in Module.CocosDensionState.effectMapNum)
        {
            Module.CocosDensionState.effectMap[key].stop();
        }
    }
};

mergeInto(LibraryManager.library, LibrarySimpleAudioEngine);

