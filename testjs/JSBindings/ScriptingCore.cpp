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
#include "out.hpp"

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
	S_CCSet::jsCreateClass(this->cx, cocos, "Set");
	S_CCTouch::jsCreateClass(this->cx, cocos, "Touch");
	S_CCDirector::jsCreateClass(this->cx, cocos, "Director");
	S_CCNode::jsCreateClass(this->cx, cocos, "Node");
	S_CCScene::jsCreateClass(this->cx, cocos, "Scene");
	S_CCLayer::jsCreateClass(this->cx, cocos, "Layer");
	S_CCSprite::jsCreateClass(this->cx, cocos, "Sprite");
	S_CCRenderTexture::jsCreateClass(this->cx, cocos, "RenderTexture");
	S_CCMenu::jsCreateClass(this->cx, cocos, "Menu");
	S_CCMenuItem::jsCreateClass(this->cx, cocos, "MenuItem");
	S_CCMenuItemImage::jsCreateClass(this->cx, cocos, "MenuItemImage");
	S_CCMenuItemLabel::jsCreateClass(this->cx, cocos, "MenuItemLabel");
	S_CCMenuItemSprite::jsCreateClass(this->cx, cocos, "MenuItemSprite");
	S_CCSpriteFrame::jsCreateClass(this->cx, cocos, "SpriteFrame");
	S_CCSpriteFrameCache::jsCreateClass(this->cx, cocos, "SpriteFrameCache");
	S_CCAnimation::jsCreateClass(this->cx, cocos, "Animation");
	S_CCAction::jsCreateClass(this->cx, cocos, "Action");
	S_CCAnimate::jsCreateClass(this->cx, cocos, "Animate");
	S_CCMoveBy::jsCreateClass(this->cx, cocos, "MoveBy");
	S_CCMoveTo::jsCreateClass(this->cx, cocos, "MoveTo");
	S_CCRotateBy::jsCreateClass(this->cx, cocos, "RotateBy");
	S_CCRotateTo::jsCreateClass(this->cx, cocos, "RotateTo");
	S_CCRepeatForever::jsCreateClass(this->cx, cocos, "RepeatForever");
	S_CCSequence::jsCreateClass(this->cx, cocos, "Sequence");
	S_CCLabelTTF::jsCreateClass(this->cx, cocos, "LabelTTF");

	// register some global functions
	JS_DefineFunction(this->cx, cocos, "log", ScriptingCore::log, 0, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(this->cx, cocos, "executeScript", ScriptingCore::executeScript, 1, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(this->cx, cocos, "addGCRootObject", ScriptingCore::addRootJS, 1, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(this->cx, cocos, "removeGCRootObject", ScriptingCore::removeRootJS, 1, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(this->cx, cocos, "forceGC", ScriptingCore::forceGC, 0, JSPROP_READONLY | JSPROP_PERMANENT);
}

void ScriptingCore::evalString(const char *string)
{
	jsval rval;
	JSString *str;
	JSBool ok;
	const char *filename = "noname";
	uint32_t lineno = 0;
	ok = JS_EvaluateScript(cx, global, string, strlen(string), filename, lineno, &rval);
	if (JSVAL_IS_NULL(rval) || rval == JSVAL_FALSE) {
		CCLog("error evaluating script:\n%s", string);
	}
	str = JS_ValueToString(cx, rval);
	printf("js result: %s\n", JS_EncodeString(cx, str));
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
//	std::string dpath("/Users/rabarca/Desktop/testjs/testjs/");
	std::string dpath("");
	dpath += path;
	const char *realPath = CCFileUtils::fullPathFromRelativePath(dpath.c_str());
#else
	const char *realPath = CCFileUtils::fullPathFromRelativePath(path);
#endif
	unsigned char *content = NULL;
	size_t contentSize = CCFileUtils::ccLoadFileIntoMemory(realPath, &content);
	if (content && contentSize) {
		JSBool ok;
		jsval rval;
		ok = JS_EvaluateScript(this->cx, this->global, (char *)content, contentSize, path, 1, &rval);
		if (JSVAL_IS_NULL(rval) || rval == JSVAL_FALSE) {
			CCLog("error evaluating script:\n%s", content);
		}
		free(content);
	}
}

ScriptingCore::~ScriptingCore()
{
	JS_DestroyContext(cx);
	JS_DestroyRuntime(rt);
	JS_ShutDown();
}
