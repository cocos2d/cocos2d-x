# TestJS

Simple iOS (and soon Android) example of cocos2d-x game running javascript bindings

*NOTE* This is a WIP and the bindings are not yet complete! What's working:

    CCPoint CCSize _ccGridSize CCRect CCDirector CCNode CCSprite CCScene CCSpriteFrameCache
    CCSpriteFrame CCAction CCAnimate CCAnimation CCRepeatForever CCLayer CCTouch
    CCSet CCMoveBy CCMoveTo CCRotateTo CCRotateBy CCRenderTexture CCMenu CCMenuItem
    CCMenuItemLabel CCMenuItemSprite CCMenuItemImage CCLabelTTF CCSequence
    CCActionInterval CCFiniteTimeAction CCFileUtils
    CCEaseBackInOut CCEaseBackOut CCEaseElasticIn CCEaseElastic CCEaseElasticOut CCEaseElasticInOut
    CCEaseBounceIn CCEaseBounce CCEaseBounceInOut CCEaseBackIn CCEaseBounceOut CCEaseIn CCEaseOut
    CCEaseExponentialIn CCEaseInOut CCEaseExponentialOut CCEaseExponentialInOut CCEaseSineIn
    CCEaseSineOut CCEaseSineInOut CCActionEase CCEaseRateAction CCParticleSystem CCParticleSystemQuad
    CCParticleSystemPoint CCDelayTime CCTexture2D CCTextureCache CCSpriteBatchNode CCTextureAtlas
    CCParallaxNode CCTintTo CCTintBy CCLayerColor CCBlink CCSpeed CCWaves3D CCGridAction CCGrid3DAction
    CCTransitionScene CCTransitionSceneOriented CCTransitionRotoZoom CCTransitionFadeDown
    CCTransitionJumpZoom CCTransitionMoveInL CCTransitionMoveInR CCTransitionMoveInT CCTransitionMoveInB
    CCTransitionSlideInL CCTransitionSlideInR CCTransitionSlideInB CCTransitionSlideInT CCTransitionShrinkGrow
    CCTransitionFlipX CCTransitionFlipY CCTransitionFlipAngular CCTransitionZoomFlipX CCTransitionZoomFlipY
    CCTransitionZoomFlipAngular CCTransitionFade CCTransitionCrossFade CCTransitionTurnOffTiles
    CCTransitionSplitCols CCTransitionSplitRows CCTransitionFadeTR CCTransitionFadeBL CCTransitionFadeUp
    CCFadeOutBLTiles CCProgressFromTo CCFadeOutUpTiles CCAnimationCache CCPlace CCLabelBMFont CCReverseTime
    CCFadeOutTRTiles CCCamera CCProgressTo CCWavesTiles3D CCMotionStreak CCTransitionRadialCCW CCFadeOutDownTiles
    CCTurnOffTiles CCDeccelAmplitude CCProgressTimer CCActionInstant CCReuseGrid CCStopGrid CCTwirl
    CCShakyTiles3D CCTransitionRadialCW CCAtlasNode CCWaves CCShow CCOrbitCamera CCShatteredTiles3D CCHide
    CCToggleVisibility CCActionCamera CCShuffleTiles CCLayerGradient CCFlipX CCRepeat CCFlipY CCBezierBy
    CCPageTurn3D CCLens3D CCRipple3D CCApplication CCFlipX3D CCJumpTo CCTransitionPageTurn CCFlipY3D
    CCLiquid CCTiledGrid3DAction CCJumpBy CCFollow CCSkewBy CCAccelDeccelAmplitude CCLabelAtlas CCAccelAmplitude
    CCSkewTo CCShaky3D CCSplitCols CCFadeOut CCTileMapAtlas CCFadeTo CCJumpTiles3D CCFadeIn CCSplitRows
    CCScaleBy CCScaleTo CCBezierTo CCTMXTiledMap CCTMXLayer CCApplication CCUserDefault

This is just a proof of concept and there are plans around this in order to make a more js-friendly API, right now
the bindings were created automatically and the final idea is not to use them as they are but to create a higher
level wrapper.

You can follow the progress of the js-bindings in the current [development fork](https://github.com/funkaster/cocos2d-x/tree/js-bindings).

For a sneak peak, you can take a look at what's in the JS directory.

## How to Build

### Before hitting the "Build" button

In debug mode, (when there's a `#define DEBUG` somewhere), the javascript code will be read from somewhere else and not from the JS directory
in the app bundle. To make sure this works, modify the absolute path in `ScriptingCore.cpp`:

```c++
void ScriptingCore::runScript(const char *path)
{
#ifdef DEBUG
	std::string dpath("/Users/rabarca/Desktop/testjs/testjs/"); // <~ this is what you want to modify!
	dpath += path;
	const char *realPath = dpath.c_str();
#else
	const char *realPath = CCFileUtils::fullPathFromRelativePath(path);
#endif
	...
}
```

Basically, the dpath string should point to wherever the JS directory is located. This affects every script
run through the `runScript` function from `ScriptingCore`. If you don't want that behaviour, then just set
the dpath string to `""`. It also allows for the "reload script" button to work on the demo:

![screenshot 1](http://dl.dropbox.com/u/29043245/testjs1.png)

If you set the dpath string to `""` (empty string, the default setting) then the reload button will try to
reload the script from inside the bundle.

In the test scenes the buttons represent:

* top left: will reload the current script
* left arrow: previous test scene in the script
* center button: will reload the current scene
* right arrow: next test scene in the script

The current test script can be changed in the AppDelegate (or by modifying the source and then hitting reload script):

```c++
# AppDelegate.cpp
bool AppDelegate::applicationDidFinishLaunching()
{
...
	// run the main script
	ScriptingCore::getInstance().runScript("JS/1to1/test_actions.js");
//	ScriptingCore::getInstance().runScript("JS/1to1/test_layer.js");

	return true;
}
```

Change the script name there and relaunch the simulator.

### iOS

Just open the xcode project and run. It's using the latest spidermonkey and js-bindings for cocos2d-x

### Android

Instructions to be added here
