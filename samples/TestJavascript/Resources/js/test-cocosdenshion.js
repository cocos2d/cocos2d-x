//
// http://www.cocos2d-iphone.org
// http://www.cocos2d-html5.org
// http://www.cocos2d-x.org
//
// Javascript + CocosDenshion tests
//
//
require("js/helper.js");

director = cc.Director.getInstance();
audioEngine = cc.AudioEngine.getInstance();
winSize = director.getWinSize();
centerPos = cc.p( winSize.width/2, winSize.height/2 );

var MUSIC_FILE = "Cyber Advance!.mp3";
var EFFECT_FILE = "cowbell.wav";

var DenshionTests = [
    {
        title:"playBackgroundMusic",
        playFunc:function () {
            return new playBackgroundMusic();
        }
    },
    {
        title:"stopBackgroundMusic",
        playFunc:function () {
            return new stopBackgroundMusic();
        }
    },
    {
        title:"pauseBackgroundMusic",
        playFunc:function () {
            return new pauseBackgroundMusic();
        }
    },
    {
        title:"resumeBackgroundMusic",
        playFunc:function () {
            return new resumeBackgroundMusic();
        }
    },
    {
        title:"rewindBackgroundMusic",
        playFunc:function () {
            return new rewindBackgroundMusic();
        }
    },
    {
        title:"isBackgroundMusicPlaying",
        playFunc:function () {
            return new isBackgroundMusicPlaying();
        }
    },
    {
        title:"playEffect",
        playFunc:function () {
            return new playEffect();
        }
    },
    {
        title:"playEffectRepeatly",
        playFunc:function () {
            return new playEffectRepeatly();
        }
    },
    {
        title:"stopEffect",
        playFunc:function () {
            return new stopEffect();
        }
    },
    {
        title:"unloadEffect",
        playFunc:function () {
            return new unloadEffect();
        }
    },
    {
        title:"addBackgroundMusicVolume",
        playFunc:function () {
            return new addBackgroundMusicVolume();
        }
    },

    {
        title:"subBackgroundMusicVolume",
        playFunc:function () {
            return new subBackgroundMusicVolume();
        }
    },

    {
        title:"addEffectsVolume",
        playFunc:function () {
            return new addEffectsVolume();
        }
    },

    {
        title:"subEffectsVolume",
        playFunc:function () {
            return new subEffectsVolume();
        }
    },

    {
        title:"pauseEffect",
        playFunc:function () {
            return new pauseEffect();
        }
    },

    {
        title:"resumeEffect",
        playFunc:function () {
            return new resumeEffect();
        }
    },

    {
        title:"pauseAllEffects",
        playFunc:function () {
            return new pauseAllEffects();
        }
    },

    {
        title:"resumeAllEffects",
        playFunc:function () {
            return new resumeAllEffects();
        }
    },

    {
        title:"stopAllEffects",
        playFunc:function () {
            return new stopAllEffects();
        }
    }

];

CocosDenshionTest = cc.LayerGradient.extend({
    _menu:null,
    ctor:function () {

        var parent = new cc.LayerGradient();
        __associateObjWithNative(this, parent);
        this.init(cc.c4b(0, 0, 0, 255), cc.c4b(0, 128, 255, 255));

        // add menu items for tests
        this._menu = cc.Menu.create();
        var s = winSize;
        for (var i = 0; i < DenshionTests.length; i++) {
            var label = cc.LabelTTF.create(DenshionTests[i].title, "Arial", 20);
            var menuItem = cc.MenuItemLabel.create(label, this, this.menuCallback);
            this._menu.addChild(menuItem, i + 10000);
        }
        this._menu.setPosition(cc.p(winSize.width/2, winSize.height/2) );
        this._menu.alignItemsVertically()
        this.addChild(this._menu);

        // set default volume
        audioEngine.setEffectsVolume(0.5);
        audioEngine.setBackgroundMusicVolume(0.5);

        // Back button
        var itemBack = cc.MenuItemFont.create("back", this, function() { require("js/main.js"); } );
        itemBack.setPosition( cc.p(winSize.width - 60, winSize.height - 30 ) );
        itemBack.setFontSize( 22 );
        var menuBack = cc.Menu.create( itemBack );
        menuBack.setPosition( cc.p(0,0) );
        this.addChild( menuBack, 10 );

    },
    menuCallback:function (sender) {
        var idx = sender.getZOrder() - 10000;
        // create the test scene and run it
        var scene = DenshionTests[idx].playFunc();
    },

});

var soundId = null;

var playBackgroundMusic = function () {
    cc.log("play background music");
    audioEngine.playBackgroundMusic(MUSIC_FILE, false);
};

var stopBackgroundMusic = function () {
    cc.log("stop background music");
    audioEngine.stopBackgroundMusic();
};

var pauseBackgroundMusic = function () {
    cc.log("pause background music");
    audioEngine.pauseBackgroundMusic();
};

var resumeBackgroundMusic = function () {
    cc.log("resume background music");
    audioEngine.resumeBackgroundMusic();
};

var rewindBackgroundMusic = function () {
    cc.log("rewind background music");
    audioEngine.rewindBackgroundMusic();
};

// is background music playing
var isBackgroundMusicPlaying = function () {
    if (audioEngine.isBackgroundMusicPlaying()) {
        cc.log("background music is playing");
    }
    else {
        cc.log("background music is not playing");
    }
};

var playEffect = function () {
    cc.log("play effect");
    soundId = audioEngine.playEffect(EFFECT_FILE);
};

var playEffectRepeatly = function () {
    cc.log("play effect repeatly");
    soundId = audioEngine.playEffect(EFFECT_FILE, true);
};

var stopEffect = function () {
    cc.log("stop effect");
    audioEngine.stopEffect(soundId);
};

var unloadEffect = function () {
    cc.log("unload effect");
    audioEngine.unloadEffect(EFFECT_FILE);
};

var addBackgroundMusicVolume = function () {
    cc.log("add bakcground music volume");
    audioEngine.setBackgroundMusicVolume(audioEngine.getBackgroundMusicVolume() + 0.1);
};

var subBackgroundMusicVolume = function () {
    cc.log("sub backgroud music volume");
    audioEngine.setBackgroundMusicVolume(audioEngine.getBackgroundMusicVolume() - 0.1);
};

var addEffectsVolume = function () {
    cc.log("add effects volume");
    audioEngine.setEffectsVolume(audioEngine.getEffectsVolume() + 0.1);
};

var subEffectsVolume = function () {
    cc.log("sub effects volume");
    audioEngine.setEffectsVolume(audioEngine.getEffectsVolume() - 0.1);
};

var pauseEffect = function () {
    cc.log("pause effect");
    audioEngine.pauseEffect(soundId);
};

var resumeEffect = function () {
    cc.log("resume effect");
    audioEngine.resumeEffect(soundId);
};

var pauseAllEffects = function () {
    cc.log("pause all effects");
    audioEngine.pauseAllEffects();
};
var resumeAllEffects = function () {
    cc.log("resume all effects");
    audioEngine.resumeAllEffects();
};
var stopAllEffects = function () {
    cc.log("stop all effects");
    audioEngine.stopAllEffects();
};


//------------------------------------------------------------------
//
// Main entry point
//
//------------------------------------------------------------------
function run()
{
    var scene = cc.Scene.create();
    var layer = new CocosDenshionTest();
    scene.addChild( layer );

    var runningScene = director.getRunningScene();
    if( runningScene == null )
        director.runWithScene( scene );
    else
        director.replaceScene( cc.TransitionSplitCols.create(1, scene ) );
}

run();

