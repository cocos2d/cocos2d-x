//
//  S_CCSprite.cpp
//  TestCocos2dX
//
//  Created by Rolando Abarca on 12/6/11.
//  Copyright (c) 2011 Zynga Inc. All rights reserved.
//

#include "S_CCNode.h"
#include "S_CCSprite.h"

using namespace cocos2d;

#pragma mark - CCSprite

JSClassRef js_S_CCSprite_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCSprite)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCSprite, CCSprite)

JSStaticFunction* S_CCSprite::jsStaticFunctions()
{
	return NULL;
}

bool S_CCSprite::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 0) {
		if (CCSprite::init())
		{
			result = true;
		}
	} else {
		// init with texture
		JSStringRef str = JSValueToStringCopy(ctx, arguments[0], NULL);
		int len = JSStringGetLength(str);
		char *buff = (char *)malloc(len+1);
		JSStringGetUTF8CString(str, buff, len+1);
		
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buff);
		if (frame) {
			result = CCSprite::initWithSpriteFrame(frame);
		} else {
			result = CCSprite::initWithFile(buff);
		}
		JSStringRelease(str);
		free(buff);
	}
	
	if (obj) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCSpriteBatchNode

JSClassRef js_S_CCSpriteBatchNode_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCSpriteBatchNode)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCSpriteBatchNode, CCSpriteBatchNode)

JSStaticFunction* S_CCSpriteBatchNode::jsStaticFunctions()
{
	return NULL;
}

bool S_CCSpriteBatchNode::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	if (argumentCount > 0) {
		JSStringRef str = JSValueToStringCopy(ctx, arguments[0], NULL);
		size_t len = JSStringGetLength(str)+1;
		char buff[len];
		JSStringGetUTF8CString(str, buff, len);
		unsigned int capacity = 10;
		if (argumentCount > 1) {
			capacity = JSValueToNumber(ctx, arguments[1], NULL);
		}
		bool ok = false;
		if (CCSpriteBatchNode::initWithFile(buff, capacity)) {
			ok = true;
			setUserData(obj);
		}
		JSStringRelease(str);
		return ok;
	}
	return false;
}
