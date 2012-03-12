//
//  S_CCMenu.cpp
//  TestCocos2dX
//
//  Created by Rolando Abarca on 12/20/11.
//  Copyright (c) 2011 Zynga Inc. All rights reserved.
//

#include <iostream>
#include "S_CCMenu.h"

using namespace cocos2d;

#pragma mark - CCMenu

JSClassRef js_S_CCMenu_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCMenu)

/**
 * manually implement onExit and setParent to avoid the confusion for menu
 * onExit
 */

void S_CCMenu::onExit()
{
	CCMenu::onExit();
}

void S_CCMenu::setParent(CCNode *var)
{
	JSContextRef ctx = ScriptingCore::getInstance().getGlobalContext();
	JSObjectRef thisObject = (JSObjectRef)this->getUserData();
	if (!var && thisObject) {
		JSValueUnprotect(ctx, thisObject);
	} else if (var && thisObject) {
		JSValueProtect(ctx, thisObject);
	}
	CCMenu::setParent(var);
}

JSStaticFunction* S_CCMenu::jsStaticFunctions()
{
	return NULL;
}

bool S_CCMenu::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool ret = false;
	if (CCMenu::init()) {
		this->m_bIsTouchEnabled = true;
		this->m_pSelectedItem = NULL;
		this->m_eState = kCCMenuStateWaiting;
		ret = true;
	}
	if (ret)
		setUserData(obj);
	return ret;
}

#pragma mark - CCMenuItem

JSClassRef js_S_CCMenuItem_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCMenuItem)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCMenuItem, CCMenuItem)

JSStaticFunction* S_CCMenuItem::jsStaticFunctions()
{
	static JSStaticFunction funcs[] = {
		{"getIsEnabled", S_CCMenuItem::jsGetIsEnabled, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setIsEnabled", S_CCMenuItem::jsSetIsEnabled, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{0, 0, 0}
	};
	
	return funcs;
}

JS_STATIC_FUNC_IMP(S_CCMenuItem, jsGetIsEnabled)
{
	CCMenuItem *itm = (CCMenuItem *)JSObjectGetPrivate(thisObject);
	if (itm) {
		bool enabled = itm->getIsEnabled();
		return JSValueMakeBoolean(ctx, enabled);
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCMenuItem, jsSetIsEnabled)
{
	CCMenuItem *itm = (CCMenuItem *)JSObjectGetPrivate(thisObject);
	if (itm && argumentCount == 1) {
		itm->setIsEnabled(JSValueToBoolean(ctx, arguments[0]));
	}
	return JSValueMakeUndefined(ctx);
}

bool S_CCMenuItem::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	if (argumentCount == 1) {
		JSObjectRef func = JSValueToObject(ctx, arguments[0], NULL);
		if (!JSObjectIsFunction(ctx, func) || !CCMenuItem::initWithTarget(this, menu_selector(S_CCMenuItem::menuHandler))) {
			return false;
		}
		m_Callback = func;
		JSValueProtect(ctx, m_Callback);
		setUserData(obj);
		return true;
	}
	return false;
}

void S_CCMenuItem::menuHandler(CCObject* pSender)
{
	JSContextRef ctx = ScriptingCore::getInstance().getGlobalContext();
	JSObjectCallAsFunction(ctx, m_Callback, NULL, 0, NULL, NULL);
}

#pragma mark - CCMenuItemLabel

JSClassRef js_S_CCMenuItemLabel_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCMenuItemLabel)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCMenuItemLabel, CCMenuItemLabel)

JSStaticFunction* S_CCMenuItemLabel::jsStaticFunctions()
{
	return NULL;
}

/**
 * var item1 = new CCMenuItemLabel(label, callback);
 */
bool S_CCMenuItemLabel::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef *arguments)
{
	if (argumentCount == 2) {
		CCNode *label = (CCNode *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		if (!label ||
			!CCMenuItemLabel::initWithLabel(label, this, menu_selector(S_CCMenuItemLabel::menuHandler))) {
			return false;
		}
		m_Callback = (JSObjectRef)arguments[1];
		JSValueProtect(ctx, m_Callback);
		setUserData(obj);
		return true;
	}
	return false;
}

void S_CCMenuItemLabel::menuHandler(CCObject* pSender)
{
	JSContextRef ctx = ScriptingCore::getInstance().getGlobalContext();
	JSObjectCallAsFunction(ctx, m_Callback, NULL, 0, NULL, NULL);
}

#pragma mark - CCMenuItemSprite

JSClassRef js_S_CCMenuItemSprite_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCMenuItemSprite)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCMenuItemSprite, CCMenuItemSprite)

JSStaticFunction* S_CCMenuItemSprite::jsStaticFunctions()
{
	return NULL;
}

/**
 * var item1 = new CCMenuItemSprite(normalSprite, selectedSprite, callback);
 */
bool S_CCMenuItemSprite::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	// TODO: add disabled sprite, perhaps based on the number of arguments
	if (argumentCount == 3) {
		JSObjectRef jsNormalSprite   = JSValueToObject(ctx, arguments[0], NULL);
		JSObjectRef jsSelectedSprite = JSValueToObject(ctx, arguments[1], NULL);
		JSObjectRef func = JSValueToObject(ctx, arguments[2], NULL);
		CCNode *normalSprite   = (CCNode *)JSObjectGetPrivate(jsNormalSprite);
		CCNode *selectedSprite = (CCNode *)JSObjectGetPrivate(jsSelectedSprite);
		// we only require normal and selected, disabled can be NULL
		if (!normalSprite ||
			!selectedSprite ||
			!JSObjectIsFunction(ctx, func) ||
			!CCMenuItemSprite::initFromNormalSprite(normalSprite, selectedSprite, NULL, this, menu_selector(S_CCMenuItemSprite::menuHandler)))
		{
			return false;
		}
		m_Callback = func;
		JSValueProtect(ctx, m_Callback);
		setUserData(obj);
		return true;
	}
	return false;
}

void S_CCMenuItemSprite::menuHandler(CCObject* pSender)
{
	JSContextRef ctx = ScriptingCore::getInstance().getGlobalContext();
	JSObjectCallAsFunction(ctx, m_Callback, NULL, 0, NULL, NULL);
}
