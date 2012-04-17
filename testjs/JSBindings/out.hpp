
#ifndef __out__h
#define __out__h

#include "ScriptingCore.h"
#include "cocos2d.h"

using namespace cocos2d;

typedef struct {
	uint32_t flags;
	void* data;
} pointerShell_t;

typedef enum {
	kPointerTemporary = 1
} pointerShellFlags;

#define JSGET_PTRSHELL(type, cobj, jsobj) do { \
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(jsobj); \
	if (pt) { \
		cobj = (type *)pt->data; \
	} else { \
		cobj = NULL; \
	} \
} while (0)

class S_CCAnimate : public CCAnimate
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	S_CCAnimate(JSObject *obj) : CCAnimate(), m_jsobj(obj) {};
	enum {
		kAnimation = 1,
		kOrigFrame,
		kRestoreOriginalFrame
	};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp);
	static void jsFinalize(JSContext *cx, JSObject *obj);
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val);
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val);
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name);
	static JSBool jsinitWithAnimation(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsstop(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsupdate(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsreverse(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsactionWithAnimation(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp);

};

class S_CCLayer : public CCLayer
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	S_CCLayer(JSObject *obj) : CCLayer(), m_jsobj(obj) {};
	enum {
		kIsTouchEnabled = 1,
		kIsAccelerometerEnabled,
		kIsKeypadEnabled,
		kScriptHandlerEntry
	};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp);
	static void jsFinalize(JSContext *cx, JSObject *obj);
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val);
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val);
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name);
	static JSBool jsinit(JSContext *cx, uint32_t argc, jsval *vp);
	virtual void onEnter();
	virtual void onExit();
	virtual void onEnterTransitionDidFinish();
	virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
	virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
	virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);
	virtual void ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent);
	virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* pEvent);
	virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* pEvent);
	virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* pEvent);
	virtual void ccTouchesCancelled(CCSet* pTouches, CCEvent* pEvent);
	static JSBool jsdidAccelerate(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsregisterWithTouchDispatcher(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsregisterScriptTouchHandler(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsunregisterScriptTouchHandler(JSContext *cx, uint32_t argc, jsval *vp);
	virtual void update(ccTime delta);

};

class S_CCAction : public CCAction
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	S_CCAction(JSObject *obj) : CCAction(), m_jsobj(obj) {};
	enum {
		kOriginalTarget = 1,
		kTarget,
		kTag
	};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp);
	static void jsFinalize(JSContext *cx, JSObject *obj);
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val);
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val);
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name);
	static JSBool jsisDone(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsstop(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsaction(JSContext *cx, uint32_t argc, jsval *vp);

};

class S_CCSpriteFrame : public CCSpriteFrame
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	S_CCSpriteFrame(JSObject *obj) : CCSpriteFrame(), m_jsobj(obj) {};
	enum {
		kRectInPixels = 1,
		kRotated,
		kRect,
		kOffsetInPixels,
		kOriginalSizeInPixels,
		kTexture
	};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp);
	static void jsFinalize(JSContext *cx, JSObject *obj);
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val);
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val);
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name);
	static JSBool jsisRotated(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsframeWithTexture(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsinitWithTexture(JSContext *cx, uint32_t argc, jsval *vp);

};

class S_CCAnimation : public CCAnimation
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	S_CCAnimation(JSObject *obj) : CCAnimation(), m_jsobj(obj) {};
	enum {
		kNameStr = 1,
		kDelay,
		kFrames
	};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp);
	static void jsFinalize(JSContext *cx, JSObject *obj);
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val);
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val);
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name);
	static JSBool jsinitWithFrames(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsaddFrame(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsaddFrameWithFileName(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsaddFrameWithTexture(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsinit(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsanimation(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsanimationWithFrames(JSContext *cx, uint32_t argc, jsval *vp);

};

class S_CCRotateBy : public CCRotateBy
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	S_CCRotateBy(JSObject *obj) : CCRotateBy(), m_jsobj(obj) {};
	enum {
		kAngle = 1,
		kStartAngle
	};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp);
	static void jsFinalize(JSContext *cx, JSObject *obj);
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val);
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val);
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name);
	static JSBool jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsupdate(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsreverse(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp);

};

class S_CCPoint : public CCPoint
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	S_CCPoint(JSObject *obj) : CCPoint(), m_jsobj(obj) {};
	enum {
		kX = 1,
		kY
	};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp);
	static void jsFinalize(JSContext *cx, JSObject *obj);
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val);
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val);
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name);
	static JSBool jsCCPointEqualToPoint(JSContext *cx, uint32_t argc, jsval *vp);

};

class S_CCSize : public CCSize
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	S_CCSize(JSObject *obj) : CCSize(), m_jsobj(obj) {};
	enum {
		kWidth = 1,
		kHeight
	};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp);
	static void jsFinalize(JSContext *cx, JSObject *obj);
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val);
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val);
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name);
	static JSBool jsCCSizeEqualToSize(JSContext *cx, uint32_t argc, jsval *vp);

};

class S_CCMoveTo : public CCMoveTo
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	S_CCMoveTo(JSObject *obj) : CCMoveTo(), m_jsobj(obj) {};
	enum {
		kEndPosition = 1,
		kPosition,
		kDelta
	};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp);
	static void jsFinalize(JSContext *cx, JSObject *obj);
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val);
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val);
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name);
	static JSBool jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsupdate(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp);

};

class S_CCRect : public CCRect
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	S_CCRect(JSObject *obj) : CCRect(), m_jsobj(obj) {};
	enum {
		kOrigin = 1,
		kSize
	};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp);
	static void jsFinalize(JSContext *cx, JSObject *obj);
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val);
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val);
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name);
	static JSBool jsCCRectGetMinX(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsCCRectGetMaxX(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsCCRectGetMidX(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsCCRectGetMinY(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsCCRectGetMaxY(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsCCRectGetMidY(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsCCRectEqualToRect(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsCCRectContainsPoint(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsCCRectIntersectsRect(JSContext *cx, uint32_t argc, jsval *vp);

};

class S_CCRotateTo : public CCRotateTo
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	S_CCRotateTo(JSObject *obj) : CCRotateTo(), m_jsobj(obj) {};
	enum {
		kDstAngle = 1,
		kStartAngle,
		kDiffAngle
	};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp);
	static void jsFinalize(JSContext *cx, JSObject *obj);
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val);
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val);
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name);
	static JSBool jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsupdate(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp);

};

class S_CCSpriteFrameCache : public CCSpriteFrameCache
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	enum {
		kSpriteFrames = 1,
		kSpriteFramesAliases
	};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp);
	static void jsFinalize(JSContext *cx, JSObject *obj);
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val);
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val);
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name);
	static JSBool jsinit(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsaddSpriteFramesWithDictionary(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsaddSpriteFramesWithFile(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsaddSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsremoveSpriteFrames(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsremoveUnusedSpriteFrames(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsremoveSpriteFrameByName(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsremoveSpriteFramesFromFile(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsremoveSpriteFramesFromDictionary(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsremoveSpriteFramesFromTexture(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsspriteFrameByName(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jssharedSpriteFrameCache(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jspurgeSharedSpriteFrameCache(JSContext *cx, uint32_t argc, jsval *vp);

};

class S_CCNode : public CCNode
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	S_CCNode(JSObject *obj) : CCNode(), m_jsobj(obj) {};
	enum {
		kZOrder = 1,
		kVertexZ,
		kRotation,
		kScaleX,
		kScaleY,
		kPosition,
		kPositionInPixels,
		kSkewX,
		kSkewY,
		kChildren,
		kCamera,
		kGrid,
		kIsVisible,
		kAnchorPoint,
		kAnchorPointInPixels,
		kContentSize,
		kContentSizeInPixels,
		kIsRunning,
		kParent,
		kIsRelativeAnchorPoint,
		kTag,
		kUserData,
		kTransform,
		kInverse,
		kTransformGL,
		kIsTransformDirty,
		kIsInverseDirty,
		kIsTransformGLDirty,
		kScriptHandler
	};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp);
	static void jsFinalize(JSContext *cx, JSObject *obj);
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val);
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val);
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name);
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	static JSBool jsregisterScriptHandler(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsunregisterScriptHandler(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsaddChild(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsremoveFromParentAndCleanup(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsremoveChild(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsremoveChildByTag(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsremoveAllChildrenWithCleanup(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsreorderChild(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jscleanup(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsdraw(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsvisit(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jstransform(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jstransformAncestors(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsboundingBox(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsboundingBoxInPixels(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsrunAction(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsstopAllActions(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsstopAction(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsstopActionByTag(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsnumberOfRunningActions(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsisScheduled(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsscheduleUpdate(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsscheduleUpdateWithPriority(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsunscheduleUpdate(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsschedule(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsunschedule(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsunscheduleAllSelectors(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsresumeSchedulerAndActions(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jspauseSchedulerAndActions(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsparentToNodeTransform(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsworldToNodeTransform(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsconvertToNodeSpace(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsconvertToWorldSpace(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsconvertToNodeSpaceAR(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsconvertToWorldSpaceAR(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsconvertTouchToNodeSpace(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsconvertTouchToNodeSpaceAR(JSContext *cx, uint32_t argc, jsval *vp);
	virtual void update(ccTime delta);

};

class S_CCScene : public CCScene
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	S_CCScene(JSObject *obj) : CCScene(), m_jsobj(obj) {};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp);
	static void jsFinalize(JSContext *cx, JSObject *obj);
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val);
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val);
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name);
	static JSBool jsinit(JSContext *cx, uint32_t argc, jsval *vp);
	virtual void update(ccTime delta);

};

class S_CCDirector : public CCDirector
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	enum {
		kPurgeDirecotorInNextLoop = 1,
		kOpenGLView,
		kInterval,
		kLandscape,
		kDisplayFPS,
		kAccumDt,
		kFrameRate,
		kFPSLabel,
		kPaused,
		kTotalFrames,
		kFrames,
		kRunningScene,
		kNextScene,
		kSendCleanupToScene,
		kScenesStack,
		kLastUpdate,
		kDeltaTime,
		kNextDeltaTimeZero,
		kEProjection,
		kWinSizeInPoints,
		kWinSizeInPixels,
		kContentScaleFactor,
		kPszFPS,
		kNotificationNode,
		kProjectionDelegate,
		kEDeviceOrientation,
		kIsContentScaleSupported,
		kRetinaDisplay
	};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp);
	static void jsFinalize(JSContext *cx, JSObject *obj);
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val);
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val);
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name);
	static JSBool jsinit(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsisDisplayFPS(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsisNextDeltaTimeZero(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsisPaused(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsisSendCleanupToScene(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsreshapeProjection(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsconvertToGL(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsconvertToUI(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsrunWithScene(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jspushScene(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jspopScene(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsreplaceScene(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsendToLua(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsend(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jspause(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsresume(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsstopAnimation(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsstartAnimation(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsdrawScene(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jspurgeCachedData(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsmainLoop(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsshowProfilers(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsapplyOrientation(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsenableRetinaDisplay(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsisRetinaDisplay(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jssharedDirector(JSContext *cx, uint32_t argc, jsval *vp);

};

class S_CCMoveBy : public CCMoveBy
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	S_CCMoveBy(JSObject *obj) : CCMoveBy(), m_jsobj(obj) {};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp);
	static void jsFinalize(JSContext *cx, JSObject *obj);
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val);
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val);
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name);
	static JSBool jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsreverse(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp);

};

class S_CCRepeatForever : public CCRepeatForever
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	S_CCRepeatForever(JSObject *obj) : CCRepeatForever(), m_jsobj(obj) {};
	enum {
		kInnerAction = 1
	};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp);
	static void jsFinalize(JSContext *cx, JSObject *obj);
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val);
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val);
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name);
	static JSBool jsinitWithAction(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsstep(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsisDone(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsreverse(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp);

};

class S_CCRenderTexture : public CCRenderTexture
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	S_CCRenderTexture(JSObject *obj) : CCRenderTexture(), m_jsobj(obj) {};
	enum {
		kSprite = 1,
		kFBO,
		kOldFBO,
		kTexture,
		kUITextureImage,
		kEPixelFormat
	};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp);
	static void jsFinalize(JSContext *cx, JSObject *obj);
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val);
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val);
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name);
	static JSBool jsrenderTextureWithWidthAndHeight(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsinitWithWidthAndHeight(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsbegin(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsbeginWithClear(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsendToLua(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsend(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsclear(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jssaveBuffer(JSContext *cx, uint32_t argc, jsval *vp);
	virtual void update(ccTime delta);

};

class S_CCSet : public CCSet
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	S_CCSet(JSObject *obj) : CCSet(), m_jsobj(obj) {};
	enum {
		kSet = 1
	};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp);
	static void jsFinalize(JSContext *cx, JSObject *obj);
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val);
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val);
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name);
	static JSBool jscopy(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jscount(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsaddObject(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsremoveObject(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jscontainsObject(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsbegin(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsend(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsanyObject(JSContext *cx, uint32_t argc, jsval *vp);

};

class S_CCTouch : public CCTouch
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	S_CCTouch(JSObject *obj) : CCTouch(), m_jsobj(obj) {};
	enum {
		kPoint = 1,
		kPrevPoint
	};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp);
	static void jsFinalize(JSContext *cx, JSObject *obj);
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val);
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val);
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name);
	static JSBool jslocationInView(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jspreviousLocationInView(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsSetTouchInfo(JSContext *cx, uint32_t argc, jsval *vp);

};

class S_CCSprite : public CCSprite
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	S_CCSprite(JSObject *obj) : CCSprite(), m_jsobj(obj) {};
	enum {
		kOpacity = 1,
		kColor,
		kTextureAtlas,
		kAtlasIndex,
		kBatchNode,
		kTransform,
		kDirty,
		kRecursiveDirty,
		kHasChildren,
		kBlendFunc,
		kTexture,
		kUsesBatchNode,
		kRect,
		kRectInPixels,
		kRectRotated,
		kOffsetPositionInPixels,
		kUnflippedOffsetPositionFromCenter,
		kQuad,
		kColorUnmodified,
		kOpacityModifyRGB,
		kFlipX,
		kFlipY
	};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp);
	static void jsFinalize(JSContext *cx, JSObject *obj);
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val);
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val);
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name);
	static JSBool jsdraw(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsisDirty(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsisTextureRectRotated(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsisUsesBatchNode(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsspriteWithTexture(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsspriteWithSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsspriteWithSpriteFrameName(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsspriteWithFile(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsspriteWithBatchNode(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsinit(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsremoveChild(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsremoveAllChildrenWithCleanup(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsreorderChild(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsaddChild(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsisFlipX(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsisFlipY(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsupdateColor(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsinitWithTexture(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsinitWithSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsinitWithSpriteFrameName(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsinitWithFile(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsinitWithBatchNode(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsinitWithBatchNodeRectInPixels(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsupdateTransform(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsuseSelfRender(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsuseBatchNode(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsisFrameDisplayed(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsdisplayedFrame(JSContext *cx, uint32_t argc, jsval *vp);
	virtual void update(ccTime delta);

};

#endif

