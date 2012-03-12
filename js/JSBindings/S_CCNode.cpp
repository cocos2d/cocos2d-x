//
//  ZDirector.cpp
//  TestCocos2dX
//
//  Created by Rolando Abarca on 12/6/11.
//  Copyright (c) 2011 Zynga Inc. All rights reserved.
//

#include <string.h>
#include <JavaScriptCore/JavaScriptCore.h>
#include "S_CCNode.h"
#include "S_Classes.h"

#pragma mark - S_CCNode

JSClassRef js_S_CCNode_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCNode)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCNode, CCNode)

JSStaticFunction* S_CCNode::jsStaticFunctions()
{
	static JSStaticFunction funcs[] = {
		{"addChild", S_CCNode::jsAddChild, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"addChildren", S_CCNode::jsAddChild, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"removeChild", S_CCNode::jsRemoveChild, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"removeChildByTag", S_CCNode::jsRemoveChildByTag, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"removeAllChildrenWithCleanup", S_CCNode::jsRemoveAllChildrenWithCleanup, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setPosition", S_CCNode::jsSetPosition, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"getPosition", S_CCNode::jsGetPosition, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setRotation", S_CCNode::jsSetRotation, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"getRotation", S_CCNode::jsGetRotation, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"getAnchorPoint", S_CCNode::jsGetAnchorPoint, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setAnchorPoint", S_CCNode::jsSetAnchorPoint, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setIsVisible", S_CCNode::jsSetIsVisible, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"isVisible", S_CCNode::jsGetIsVisible, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setScale", S_CCNode::jsSetScale, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"getScale", S_CCNode::jsGetScale, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setScaleX", S_CCNode::jsSetScaleX, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"getScaleX", S_CCNode::jsGetScaleX, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setScaleY", S_CCNode::jsSetScaleY, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"getScaleY", S_CCNode::jsGetScaleY, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setSkewX", S_CCNode::jsSetSkewX, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"getSkewX", S_CCNode::jsGetSkewX, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setSkewY", S_CCNode::jsSetSkewY, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"getSkewY", S_CCNode::jsGetSkewY, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"runAction", S_CCNode::jsRunAction, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setColor", S_CCNode::jsSetColor, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"getColor", S_CCNode::jsGetColor, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setOpacity", S_CCNode::jsSetOpacity, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"getOpacity", S_CCNode::jsGetOpacity, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setTag", S_CCNode::jsSetTag, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"getTag", S_CCNode::jsGetTag, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"getChildByTag", S_CCNode::jsGetChildByTag, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"registerAsTouchHandler", S_CCNode::jsRegisterAsTouchHandler, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"unregisterAsTouchHandler", S_CCNode::jsUnregisterAsTouchHandler, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{0, 0, 0}
	};
	return funcs;
}

bool S_CCNode::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	if (obj) {
		setUserData(obj);
	}
	return true;
}

JS_STATIC_FUNC_IMP(S_CCNode, jsAddChild)
{
	if (argumentCount > 0) {
		// support for addChildren(...)
		CCNode *self = (CCNode *)JSObjectGetPrivate(thisObject);
		for (int i=0; i < argumentCount; i++) {
			JSObjectRef val = JSValueToObject(ctx, arguments[i], NULL);
			// we do this and not test for the subclass because we assume we're the
			// only ones adding private objects to the JS objects
			CCNode *node = (CCNode *)JSObjectGetPrivate(val);
			if (node) {
				self->addChild(node);
			}
		}
		// return this (we might want to chaing methods)
		return thisObject;
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsRemoveChild)
{
	if (argumentCount == 1)
	{
		JSObjectRef val = JSValueToObject(ctx, arguments[0], NULL);
		CCNode *node = (CCNode *)JSObjectGetPrivate(val);
		if (node)
		{
			CCNode *self = (CCNode *)JSObjectGetPrivate(thisObject);
			self->removeChild(node, true);
		}
		return thisObject;
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsRemoveChildByTag)
{
	if (argumentCount == 1)
	{
		CCNode *self = (CCNode *)JSObjectGetPrivate(thisObject);
		if (self)
		{
			self->removeChildByTag(JSValueToNumber(ctx, arguments[0], NULL), true);
		}
		return thisObject;
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsRemoveAllChildrenWithCleanup)
{
	if (argumentCount == 1)
	{
		CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
		if (node)
		{
			bool cleanup = JSValueToBoolean(ctx, arguments[0]);
			node->removeAllChildrenWithCleanup(cleanup);
		}
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsSetPosition)
{
	CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
	if (node) {
		if (argumentCount == 1) {
			CCPoint *pt = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
			node->setPosition(*pt);
		}
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsGetPosition)
{
	CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
	if (node) {
		// make a new jsobject and add the point to that
		CCPoint npos = node->getPosition();
		CCPoint *pt = new CCPoint(npos.x, npos.y);
		return JSObjectMake(ctx, __jsCCPoint_class, pt);
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsSetSkewX)
{
	CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
	if (node && argumentCount == 1) {
		node->setSkewX(JSValueToNumber(ctx, arguments[0], NULL));
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsGetSkewX)
{
	CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
	if (node) {
		return JSValueMakeNumber(ctx, node->getSkewX());
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsSetSkewY)
{
	CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
	if (node && argumentCount == 1) {
		node->setSkewY(JSValueToNumber(ctx, arguments[0], NULL));
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsGetSkewY)
{
	CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
	if (node) {
		return JSValueMakeNumber(ctx, node->getSkewY());
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsSetRotation)
{
	CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
	if (node && argumentCount == 1) {
		node->setRotation(JSValueToNumber(ctx, arguments[0], NULL));
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsGetRotation)
{
	CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
	if (node) {
		return JSValueMakeNumber(ctx, node->getRotation());
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsSetAnchorPoint)
{
	CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
	if (node) {
		if (argumentCount == 1) {
			CCPoint *pt = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
			node->setAnchorPoint(*pt);
		}
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsGetAnchorPoint)
{
	CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
	if (node) {
		CCPoint nanchor = node->getAnchorPoint();
		CCPoint *pt = new CCPoint(nanchor.x, nanchor.y);
		return JSObjectMake(ctx, __jsCCPoint_class, pt);
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsSetIsVisible)
{
	CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
	if (node && argumentCount == 1) {
		bool visible = JSValueToBoolean(ctx, arguments[0]);
		node->setIsVisible(visible);
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsGetIsVisible)
{
	CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
	if (node) {
		return JSValueMakeBoolean(ctx, node->getIsVisible());
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsSetScale)
{
	CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
	if (node && argumentCount == 1) {
		node->setScale(JSValueToNumber(ctx, arguments[0], NULL));
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsGetScale)
{
	CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
	if (node) {
		return JSValueMakeNumber(ctx, node->getScale());
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsSetScaleX)
{
	CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
	if (node && argumentCount == 1) {
		node->setScaleX(JSValueToNumber(ctx, arguments[0], NULL));
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsGetScaleX)
{
	CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
	if (node) {
		return JSValueMakeNumber(ctx, node->getScaleX());
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsSetScaleY)
{
	CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
	if (node && argumentCount == 1) {
		node->setScaleY(JSValueToNumber(ctx, arguments[0], NULL));
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsGetScaleY)
{
	CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
	if (node) {
		return JSValueMakeNumber(ctx, node->getScaleY());
	}
	return JSValueMakeUndefined(ctx);
}

/**
 * // simple action (will move by -100 points in the Y axis, and will take 0.5 seconds
 * var action = new CCMoveBy(0.5, 0, -100);
 * node.runAction(action);
 */
JS_STATIC_FUNC_IMP(S_CCNode, jsRunAction)
{
	if (argumentCount == 1) {
		JSObjectRef jsAction = JSValueToObject(ctx, arguments[0], NULL);
		if (jsAction) {
			CCAction *action = (CCAction *)JSObjectGetPrivate(jsAction);
			CCNode *self = (CCNode *)JSObjectGetPrivate(thisObject);
			if (action && self) {
				self->runAction(action);
			}
			JSValueProtect(ctx, arguments[0]);
		}
	}
	return thisObject;
}

JS_STATIC_FUNC_IMP(S_CCNode, jsSetColor)
{
	if (argumentCount == 1) {
		CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
		if (node) {
			// try to cast to the CCRGBAProtocol
			CCRGBAProtocol *rgbanode = dynamic_cast<CCRGBAProtocol *>(node);
			if (rgbanode) {
				ccColor3B *color = (ccColor3B *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
				rgbanode->setColor(*color);
			}
		}
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsGetColor)
{
	CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
	if (node) {
		// try to cast to the CCRGBAProtocol
		CCRGBAProtocol *rgbanode = dynamic_cast<CCRGBAProtocol *>(node);
		if (rgbanode) {
			ccColor3B ncolor = rgbanode->getColor();
			ccColor3B *color = (ccColor3B *)malloc(sizeof(ccColor3B));
			memcpy(color, &ncolor, sizeof(ccColor3B));
			return JSObjectMake(ctx, __jsCCColor_class, color);
		}
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsSetOpacity)
{
	if (argumentCount == 1)
	{
		CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
		if (node) {
			CCRGBAProtocol *rgbanode = dynamic_cast<CCRGBAProtocol *>(node);
			if (rgbanode) {
				rgbanode->setOpacity(JSValueToNumber(ctx, arguments[0], NULL));
			}
		}
		return arguments[0];
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsGetOpacity)
{
	CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
	if (node) {
		CCRGBAProtocol *rgbanode = dynamic_cast<CCRGBAProtocol *>(node);
		if (rgbanode) {
			return JSValueMakeNumber(ctx, rgbanode->getOpacity());
		}
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsSetTag)
{
	CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
	if (node && argumentCount == 1) {
		int tag = JSValueToNumber(ctx, arguments[0], NULL);
		node->setTag(tag);
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsGetTag)
{
	CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
	if (node) {
		return JSValueMakeNumber(ctx, node->getTag());
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsGetChildByTag)
{
	CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
	if (node && argumentCount == 1) {
		int tag = JSValueToNumber(ctx, arguments[0], NULL);
		CCNode *child = (CCNode *)node->getChildByTag(tag);
		if (child) {
			return (JSObjectRef)child->getUserData();
		}
		return JSValueMakeNull(ctx);
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsRegisterAsTouchHandler)
{
	// by default we have the worst priority
	CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
	S_TouchDelegate *delegate = dynamic_cast<S_TouchDelegate *>(node);
	if (node && delegate) {
		int priority = INT_MAX;
		if (argumentCount == 1) {
			priority = JSValueToNumber(ctx, arguments[0], NULL);
		}
		CCTouchDispatcher::sharedDispatcher()->addStandardDelegate(delegate, priority);
	}
	
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCNode, jsUnregisterAsTouchHandler)
{
	CCNode *node = (CCNode *)JSObjectGetPrivate(thisObject);
	S_TouchDelegate *delegate = dynamic_cast<S_TouchDelegate *>(node);
	if (node && delegate) {
		CCTouchDispatcher::sharedDispatcher()->removeDelegate(delegate);
	}
	return JSValueMakeUndefined(ctx);
}

#pragma mark - S_CCScene

JSClassRef js_S_CCScene_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCScene)

void S_CCScene::onExit()
{
	CCScene::onExit();
}

void S_CCScene::setParent(CCNode *var)
{
	JSContextRef ctx = ScriptingCore::getInstance().getGlobalContext();
	JSObjectRef thisObject = (JSObjectRef)this->getUserData();
	if (!var && thisObject) {
		JSValueUnprotect(ctx, thisObject);
	} else if (var && thisObject) {
		JSValueProtect(ctx, thisObject);
	}
	CCScene::setParent(var);
}

JSStaticFunction* S_CCScene::jsStaticFunctions()
{
	return NULL;
}

bool S_CCScene::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	if (obj) {
		setUserData(obj);
	}
	return true;
}
