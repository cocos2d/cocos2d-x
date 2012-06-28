//
//  ScriptingCore.cpp
//  testmonkey
//
//  Created by Rolando Abarca on 3/14/12.
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//

#include <iostream>
#include "cocos2d.h"
#include "ScriptingCore.h"
#include "cocos2d_generated.hpp"
#include "cocos_denshion_generated.hpp"

using namespace cocos2d;


static JSClass global_class = {
    "global", JSCLASS_GLOBAL_FLAGS,
    JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
    JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
    JSCLASS_NO_OPTIONAL_MEMBERS
};

ScriptingCore::ScriptingCore()
{
    this->rt = JS_NewRuntime(8 * 1024 * 1024);
    this->cx = JS_NewContext(rt, 8192);
    JS_SetOptions(this->cx, JSOPTION_VAROBJFIX);
    JS_SetVersion(this->cx, JSVERSION_LATEST);
    JS_SetErrorReporter(this->cx, ScriptingCore::reportError);
    global = JS_NewCompartmentAndGlobalObject(cx, &global_class, NULL);
    if (!JS_InitStandardClasses(cx, global)) {
        CCLog("js error");
    }
    // create the cocos namespace
    JSObject *cocos = JS_NewObject(cx, NULL, NULL, NULL);
    jsval cocosVal = OBJECT_TO_JSVAL(cocos);
    JS_SetProperty(cx, global, "cocos", &cocosVal);

    // register the internal classes
    S_CCPoint::jsCreateClass(this->cx, cocos, "Point");
    S_CCSize::jsCreateClass(this->cx, cocos, "Size");
    S_CCRect::jsCreateClass(this->cx, cocos, "Rect");
    S__ccGridSize::jsCreateClass(this->cx, cocos, "GridSize");
    S_CCSet::jsCreateClass(this->cx, cocos, "Set");
    S_CCTouch::jsCreateClass(this->cx, cocos, "Touch");
    S_CCDirector::jsCreateClass(this->cx, cocos, "Director");
    S_CCNode::jsCreateClass(this->cx, cocos, "Node");
    S_CCTextureAtlas::jsCreateClass(this->cx, cocos, "TextureAtlas");
    S_CCSpriteBatchNode::jsCreateClass(this->cx, cocos, "SpriteBatchNode");
    S_CCScene::jsCreateClass(this->cx, cocos, "Scene");
    S_CCLayer::jsCreateClass(this->cx, cocos, "Layer");
    S_CCSprite::jsCreateClass(this->cx, cocos, "Sprite");
    S_CCRenderTexture::jsCreateClass(this->cx, cocos, "RenderTexture");
    S_CCMenu::jsCreateClass(this->cx, cocos, "Menu");
    S_CCMenuItem::jsCreateClass(this->cx, cocos, "MenuItem");
    S_CCMenuItemLabel::jsCreateClass(this->cx, cocos, "MenuItemLabel");
    S_CCMenuItemSprite::jsCreateClass(this->cx, cocos, "MenuItemSprite");
    S_CCMenuItemImage::jsCreateClass(this->cx, cocos, "MenuItemImage");
    S_CCSpriteFrame::jsCreateClass(this->cx, cocos, "SpriteFrame");
    S_CCSpriteFrameCache::jsCreateClass(this->cx, cocos, "SpriteFrameCache");
    S_CCAnimation::jsCreateClass(this->cx, cocos, "Animation");
    S_CCAction::jsCreateClass(this->cx, cocos, "Action");
    S_CCActionInterval::jsCreateClass(this->cx, cocos, "ActionInterval");
    S_CCFiniteTimeAction::jsCreateClass(this->cx, cocos, "FiniteTimeAction");
    S_CCActionInstant::jsCreateClass(this->cx, cocos, "ActionInstant");
    S_CCDelayTime::jsCreateClass(this->cx, cocos, "DelayTime");
    S_CCAnimate::jsCreateClass(this->cx, cocos, "Animate");
    S_CCMoveTo::jsCreateClass(this->cx, cocos, "MoveTo");
    S_CCMoveBy::jsCreateClass(this->cx, cocos, "MoveBy");
    S_CCRotateBy::jsCreateClass(this->cx, cocos, "RotateBy");
    S_CCRotateTo::jsCreateClass(this->cx, cocos, "RotateTo");
    S_CCActionEase::jsCreateClass(this->cx, cocos, "ActionEase");
    S_CCEaseRateAction::jsCreateClass(this->cx, cocos, "EaseRateAction");
    S_CCEaseIn::jsCreateClass(this->cx, cocos, "EaseIn");
    S_CCEaseOut::jsCreateClass(this->cx, cocos, "EaseOut");
    S_CCEaseInOut::jsCreateClass(this->cx, cocos, "EaseInOut");
    S_CCEaseBackInOut::jsCreateClass(this->cx, cocos, "EaseBackInOut");
    S_CCEaseBackOut::jsCreateClass(this->cx, cocos, "EaseBackOut");
    S_CCEaseElasticIn::jsCreateClass(this->cx, cocos, "EaseElasticIn");
    S_CCEaseElastic::jsCreateClass(this->cx, cocos, "EaseElastic");
    S_CCEaseElasticOut::jsCreateClass(this->cx, cocos, "EaseElasticOut");
    S_CCEaseElasticInOut::jsCreateClass(this->cx, cocos, "EaseElasticInOut");
    S_CCEaseBounce::jsCreateClass(this->cx, cocos, "EaseBounce");
    S_CCEaseBounceIn::jsCreateClass(this->cx, cocos, "EaseBounceIn");
    S_CCEaseBounceInOut::jsCreateClass(this->cx, cocos, "EaseBounceInOut");
    S_CCEaseBackIn::jsCreateClass(this->cx, cocos, "EaseBackIn");
    S_CCEaseBounceOut::jsCreateClass(this->cx, cocos, "EaseBounceOut");
    S_CCEaseExponentialIn::jsCreateClass(this->cx, cocos, "EaseExponentialIn");
    S_CCEaseExponentialOut::jsCreateClass(this->cx, cocos, "EaseExponentialOut");
    S_CCEaseExponentialInOut::jsCreateClass(this->cx, cocos, "EaseExponentialInOut");
    S_CCEaseSineIn::jsCreateClass(this->cx, cocos, "EaseSineIn");
    S_CCEaseSineOut::jsCreateClass(this->cx, cocos, "EaseSineOut");
    S_CCEaseSineInOut::jsCreateClass(this->cx, cocos, "EaseSineInOut");
    S_CCRepeatForever::jsCreateClass(this->cx, cocos, "RepeatForever");
    S_CCSequence::jsCreateClass(this->cx, cocos, "Sequence");
    S_CCLabelTTF::jsCreateClass(this->cx, cocos, "LabelTTF");
    S_CCParticleSystem::jsCreateClass(this->cx, cocos, "ParticleSystem");
    S_CCFileUtils::jsCreateClass(this->cx, cocos, "FileUtils");
    S_CCTexture2D::jsCreateClass(this->cx, cocos, "Texture2D");
    S_CCTextureCache::jsCreateClass(this->cx, cocos, "TextureCache");
    S_CCParallaxNode::jsCreateClass(this->cx, cocos, "ParallaxNode");
    S_CCTintBy::jsCreateClass(this->cx, cocos, "TintBy");
    S_CCTintTo::jsCreateClass(this->cx, cocos, "TintTo");
    S_CCLayerColor::jsCreateClass(this->cx, cocos, "LayerColor");
    S_CCBlink::jsCreateClass(this->cx, cocos, "Blink");
    S_CCSpeed::jsCreateClass(this->cx, cocos, "Speed");
    S_CCGridAction::jsCreateClass(this->cx, cocos, "GridAction");
    S_CCGrid3DAction::jsCreateClass(this->cx, cocos, "Grid3DAction");
    S_CCWaves3D::jsCreateClass(this->cx, cocos, "Waves3D");
    S_CCTransitionScene::jsCreateClass(this->cx, cocos, "TransitionScene");
    S_CCTransitionSceneOriented::jsCreateClass(this->cx, cocos, "TransitionSceneOriented");
    S_CCTransitionRotoZoom::jsCreateClass(this->cx, cocos, "TransitionRotoZoom");
    S_CCTransitionFadeDown::jsCreateClass(this->cx, cocos, "TransitionFadeDown");
    S_CCTransitionJumpZoom::jsCreateClass(this->cx, cocos, "TransitionJumpZoom");
    S_CCTransitionMoveInL::jsCreateClass(this->cx, cocos, "TransitionMoveInL");
    S_CCTransitionMoveInR::jsCreateClass(this->cx, cocos, "TransitionMoveInR");
    S_CCTransitionMoveInT::jsCreateClass(this->cx, cocos, "TransitionMoveInT");
    S_CCTransitionMoveInB::jsCreateClass(this->cx, cocos, "TransitionMoveInB");
    S_CCTransitionSlideInL::jsCreateClass(this->cx, cocos, "TransitionSlideInL");
    S_CCTransitionSlideInR::jsCreateClass(this->cx, cocos, "TransitionSlideInR");
    S_CCTransitionSlideInB::jsCreateClass(this->cx, cocos, "TransitionSlideInB");
    S_CCTransitionSlideInT::jsCreateClass(this->cx, cocos, "TransitionSlideInT");
    S_CCTransitionShrinkGrow::jsCreateClass(this->cx, cocos, "TransitionShrinkGrow");
    S_CCTransitionFlipX::jsCreateClass(this->cx, cocos, "TransitionFlipX");
    S_CCTransitionFlipY::jsCreateClass(this->cx, cocos, "TransitionFlipY");
    S_CCTransitionFlipAngular::jsCreateClass(this->cx, cocos, "TransitionFlipAngular");
    S_CCTransitionZoomFlipX::jsCreateClass(this->cx, cocos, "TransitionZoomFlipX");
    S_CCTransitionZoomFlipY::jsCreateClass(this->cx, cocos, "TransitionZoomFlipY");
    S_CCTransitionZoomFlipAngular::jsCreateClass(this->cx, cocos, "TransitionZoomFlipAngular");
    S_CCTransitionFade::jsCreateClass(this->cx, cocos, "TransitionFade");
    S_CCTransitionCrossFade::jsCreateClass(this->cx, cocos, "TransitionCrossFade");
    S_CCTransitionTurnOffTiles::jsCreateClass(this->cx, cocos, "TransitionTurnOffTiles");
    S_CCTransitionSplitCols::jsCreateClass(this->cx, cocos, "TransitionSplitCols");
    S_CCTransitionSplitRows::jsCreateClass(this->cx, cocos, "TransitionSplitRows");
    S_CCTransitionFadeTR::jsCreateClass(this->cx, cocos, "TransitionFadeTR");
    S_CCTransitionFadeBL::jsCreateClass(this->cx, cocos, "TransitionFadeBL");
    S_CCTransitionFadeUp::jsCreateClass(this->cx, cocos, "TransitionFadeUp");
    S_CCFadeOutBLTiles::jsCreateClass(this->cx, cocos, "FadeOutBLTiles");
    S_CCProgressFromTo::jsCreateClass(this->cx, cocos, "ProgressFromTo");
    S_CCFadeOutUpTiles::jsCreateClass(this->cx, cocos, "FadeOutUpTiles");
    S_CCAnimationCache::jsCreateClass(this->cx, cocos, "AnimationCache");
    S_CCPlace::jsCreateClass(this->cx, cocos, "Place");
    S_CCLabelBMFont::jsCreateClass(this->cx, cocos, "LabelBMFont");
    S_CCReverseTime::jsCreateClass(this->cx, cocos, "ReverseTime");
    S_CCFadeOutTRTiles::jsCreateClass(this->cx, cocos, "FadeOutTRTiles");
    S_CCCamera::jsCreateClass(this->cx, cocos, "Camera");
    S_CCProgressTo::jsCreateClass(this->cx, cocos, "ProgressTo");
    S_CCWavesTiles3D::jsCreateClass(this->cx, cocos, "WavesTiles3D");
    S_CCMotionStreak::jsCreateClass(this->cx, cocos, "MotionStreak");
    S_CCTransitionProgressRadialCCW::jsCreateClass(this->cx, cocos, "TransitionRadialProgressCCW");
    S_CCFadeOutDownTiles::jsCreateClass(this->cx, cocos, "FadeOutDownTiles");
    S_CCTurnOffTiles::jsCreateClass(this->cx, cocos, "TurnOffTiles");
    S_CCDeccelAmplitude::jsCreateClass(this->cx, cocos, "DeccelAmplitude");
    S_CCProgressTimer::jsCreateClass(this->cx, cocos, "ProgressTimer");
    S_CCReuseGrid::jsCreateClass(this->cx, cocos, "ReuseGrid");
    S_CCStopGrid::jsCreateClass(this->cx, cocos, "StopGrid");
    S_CCTwirl::jsCreateClass(this->cx, cocos, "Twirl");
    S_CCShakyTiles3D::jsCreateClass(this->cx, cocos, "ShakyTiles3D");
    S_CCTransitionProgressRadialCW::jsCreateClass(this->cx, cocos, "TransitionProgressRadialCW");
    S_CCAtlasNode::jsCreateClass(this->cx, cocos, "AtlasNode");
    S_CCWaves::jsCreateClass(this->cx, cocos, "Waves");
    S_CCShow::jsCreateClass(this->cx, cocos, "Show");
    S_CCOrbitCamera::jsCreateClass(this->cx, cocos, "OrbitCamera");
    S_CCShatteredTiles3D::jsCreateClass(this->cx, cocos, "ShatteredTiles3D");
    S_CCHide::jsCreateClass(this->cx, cocos, "Hide");
    S_CCToggleVisibility::jsCreateClass(this->cx, cocos, "ToggleVisibility");
    S_CCActionCamera::jsCreateClass(this->cx, cocos, "ActionCamera");
    S_CCShuffleTiles::jsCreateClass(this->cx, cocos, "ShuffleTiles");
    S_CCLayerGradient::jsCreateClass(this->cx, cocos, "LayerGradient");
    S_CCFlipX::jsCreateClass(this->cx, cocos, "FlipX");
    S_CCRepeat::jsCreateClass(this->cx, cocos, "Repeat");
    S_CCFlipY::jsCreateClass(this->cx, cocos, "FlipY");
    S_CCBezierBy::jsCreateClass(this->cx, cocos, "BezierBy");
    S_CCPageTurn3D::jsCreateClass(this->cx, cocos, "PageTurn3D");
    S_CCLens3D::jsCreateClass(this->cx, cocos, "Lens3D");
    S_CCRipple3D::jsCreateClass(this->cx, cocos, "Ripple3D");
    S_CCApplication::jsCreateClass(this->cx, cocos, "Application");
    S_CCFlipX3D::jsCreateClass(this->cx, cocos, "FlipX3D");
    S_CCJumpTo::jsCreateClass(this->cx, cocos, "JumpTo");
    S_CCTransitionPageTurn::jsCreateClass(this->cx, cocos, "TransitionPageTurn");
    S_CCFlipY3D::jsCreateClass(this->cx, cocos, "FlipY3D");
    S_CCLiquid::jsCreateClass(this->cx, cocos, "Liquid");
    S_CCTiledGrid3DAction::jsCreateClass(this->cx, cocos, "TiledGrid3DAction");
    S_CCJumpBy::jsCreateClass(this->cx, cocos, "JumpBy");
    S_CCFollow::jsCreateClass(this->cx, cocos, "Follow");
    S_CCSkewBy::jsCreateClass(this->cx, cocos, "SkewBy");
    S_CCAccelDeccelAmplitude::jsCreateClass(this->cx, cocos, "AccelDeccelAmplitude");
    S_CCLabelAtlas::jsCreateClass(this->cx, cocos, "LabelAtlas");
    S_CCAccelAmplitude::jsCreateClass(this->cx, cocos, "AccelAmplitude");
    S_CCSkewTo::jsCreateClass(this->cx, cocos, "SkewTo");
    S_CCShaky3D::jsCreateClass(this->cx, cocos, "Shaky3D");
    S_CCSplitCols::jsCreateClass(this->cx, cocos, "SplitCols");
    S_CCFadeOut::jsCreateClass(this->cx, cocos, "FadeOut");
    S_CCTileMapAtlas::jsCreateClass(this->cx, cocos, "TileMapAtlas");
    S_CCFadeTo::jsCreateClass(this->cx, cocos, "FadeTo");
    S_CCJumpTiles3D::jsCreateClass(this->cx, cocos, "JumpTiles3D");
    S_CCFadeIn::jsCreateClass(this->cx, cocos, "FadeIn");
    S_CCSplitRows::jsCreateClass(this->cx, cocos, "SplitRows");
    S_CCScaleBy::jsCreateClass(this->cx, cocos, "ScaleBy");
    S_CCScaleTo::jsCreateClass(this->cx, cocos, "ScaleTo");
    S_CCBezierTo::jsCreateClass(this->cx, cocos, "BezierTo");
    S_CCTMXTiledMap::jsCreateClass(this->cx, cocos, "TMXTiledMap");
    S_CCTMXLayer::jsCreateClass(this->cx, cocos, "TMXLayer");

    S_SimpleAudioEngine::jsCreateClass(this->cx, cocos, "SimpleAudioEngine");

    // register some global functions
    JS_DefineFunction(this->cx, global, "require", ScriptingCore::executeScript, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(this->cx, cocos, "log", ScriptingCore::log, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(this->cx, cocos, "executeScript", ScriptingCore::executeScript, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(this->cx, cocos, "addGCRootObject", ScriptingCore::addRootJS, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(this->cx, cocos, "removeGCRootObject", ScriptingCore::removeRootJS, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(this->cx, cocos, "forceGC", ScriptingCore::forceGC, 0, JSPROP_READONLY | JSPROP_PERMANENT);
}

bool ScriptingCore::evalString(const char *string, jsval *outVal)
{
    jsval rval;
    JSString *str;
    JSBool ok;
    const char *filename = "noname";
    uint32_t lineno = 0;
    if (outVal == NULL) {
        outVal = &rval;
    }
    ok = JS_EvaluateScript(cx, global, string, strlen(string), filename, lineno, outVal);
    if (ok == JS_FALSE) {
        CCLog("error evaluating script:\n%s", string);
    }
    str = JS_ValueToString(cx, rval);
    return ok;
}

void ScriptingCore::runScript(const char *path)
{
#ifdef DEBUG
    /**
     * dpath should point to the parent directory of the "JS" folder. If this is
     * set to "" (as it is now) then it will take the scripts from the app bundle.
     * By setting the absolute path you can iterate the development only by
     * modifying those scripts and reloading from the simulator (no recompiling/
     * relaunching)
     */
//    std::string dpath("/Users/rabarca/Desktop/testjs/testjs/");
    std::string dpath("");
    dpath += path;
    const char *realPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(dpath.c_str());
#else
    const char *realPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(path);
#endif
    const char* content = CCString::createWithContentsOfFile(realPath)->getCString();
    if (content && strlen(content) > 0) {
        JSBool ok;
        jsval rval;
        ok = JS_EvaluateScript(this->cx, this->global, (char *)content, strlen(content), path, 1, &rval);
        if (ok == JS_FALSE) {
            CCLog("error evaluating script:\n%s", content);
        }
    }
}

ScriptingCore::~ScriptingCore()
{
    JS_DestroyContext(cx);
    JS_DestroyRuntime(rt);
    JS_ShutDown();
}
