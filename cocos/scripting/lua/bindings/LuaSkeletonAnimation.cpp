/*
 * LuaSkeletonAnimation.cpp
 *
 *  Created on: 2013?11?21?
 *      Author: edwardzhou
 */

#include "LuaSkeletonAnimation.h"
#include "cocos2d.h"
#include "LuaScriptHandlerMgr.h"
#include "CCLuaStack.h"
#include "CCLuaEngine.h"

using namespace spine;
USING_NS_CC;

//LuaSkeletonAnimation::LuaSkeletonAnimation() {
//	// TODO Auto-generated constructor stub
//}

static int SendSpineEventToLua(int nHandler, CCSkeletonAnimation* node, int trackIndex, spEventType type, spEvent* event, int loopCount) {
    if (nHandler <= 0) {
        return 0;
    }

    if (NULL == ScriptEngineManager::getInstance()->getScriptEngine()) {
        return 0;
    }

    LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
    if (NULL == pStack) {
        return 0;
    }

    lua_State *tolua_s = pStack->getLuaState();
    if (NULL == tolua_s) {
        return 0;
    }

    int nRet = 0;

	spTrackEntry* entry = spAnimationState_getCurrent(node->state, trackIndex);
	std::string animationName = (entry && entry->animation) ? entry->animation->name : "";
	std::string eventType = "";

	switch (type) {
	case ANIMATION_START:
		//CCLOG("%d start: %s", trackIndex, animationName.c_str());
		eventType = "start";
		break;
	case ANIMATION_END:
		//CCLOG("%d end: %s", trackIndex, animationName.c_str());
		eventType = "end";
		break;
	case ANIMATION_COMPLETE:
		//CCLOG("%d complete: %s, %d", trackIndex, animationName.c_str(), loopCount);
		eventType = "complete";
		break;
	case ANIMATION_EVENT:
		//CCLOG("%d event: %s, %s: %d, %f, %s", trackIndex, animationName.c_str(), event->data->name, event->intValue, event->floatValue, event->stringValue);
		eventType = "event";
		break;
	}

	LuaValueDict spineEvent;
	spineEvent.insert(spineEvent.end(), LuaValueDict::value_type("type", LuaValue::stringValue(eventType)));
	spineEvent.insert(spineEvent.end(), LuaValueDict::value_type("trackIndex", LuaValue::intValue(trackIndex)));
	spineEvent.insert(spineEvent.end(), LuaValueDict::value_type("animation", LuaValue::stringValue(animationName)));
	spineEvent.insert(spineEvent.end(), LuaValueDict::value_type("loopCount", LuaValue::intValue(loopCount)));

	if (NULL != event) {
		LuaValueDict eventData;
		eventData.insert(eventData.end(), LuaValueDict::value_type("name", LuaValue::stringValue(event->data->name)));
		eventData.insert(eventData.end(), LuaValueDict::value_type("intValue", LuaValue::intValue(event->intValue)));
		eventData.insert(eventData.end(), LuaValueDict::value_type("floatValue", LuaValue::floatValue(event->floatValue)));
		eventData.insert(eventData.end(), LuaValueDict::value_type("stringValue", LuaValue::stringValue(event->stringValue)));
		spineEvent.insert(spineEvent.end(), LuaValueDict::value_type("eventData", LuaValue::dictValue(eventData)));
	}

//    pStack->pushString(eventType.c_str());
//    pStack->pushInt(trackIndex);
//    pStack->pushString(animationName.c_str());
//    pStack->pushInt(loopCount);
	pStack->pushLuaValueDict(spineEvent);
    nRet = pStack->executeFunctionByHandler(nHandler, 1);
    pStack->clean();
    return nRet;

}

LuaSkeletonAnimation::LuaSkeletonAnimation (const char* skeletonDataFile, const char* atlasFile, float scale)
		: CCSkeletonAnimation(skeletonDataFile, atlasFile, scale) {
	CCLOG("LuaSkeletonAnimation::LuaSkeletonAnimation");
	this->setAnimationListener(this, animationStateEvent_selector(LuaSkeletonAnimation::animationStateEvent));
}


LuaSkeletonAnimation::~LuaSkeletonAnimation() {
    ScriptHandlerMgr::getInstance()->removeObjectAllHandlers((void*)this);
}

LuaSkeletonAnimation* LuaSkeletonAnimation::createWithFile (const char* skeletonDataFile, const char* atlasFile, float scale) {
	LuaSkeletonAnimation* node = new LuaSkeletonAnimation(skeletonDataFile, atlasFile, scale);
	node->autorelease();
	return node;
}

void LuaSkeletonAnimation::animationStateEvent (CCSkeletonAnimation* node, int trackIndex, spEventType type, spEvent* event, int loopCount) {

    int nHandler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, static_cast<ScriptHandlerMgr::HandlerType>(SCRIPT_SPINE_EVENT));
    if (0 != nHandler) {
        SendSpineEventToLua(nHandler, node, trackIndex, type, event, loopCount);
    }

//	spTrackEntry* entry = spAnimationState_getCurrent(node->state, trackIndex);
//	std::string animationName = (entry && entry->animation) ? entry->animation->name : "";
//	std::string eventType = "";
//
//	switch (type) {
//	case ANIMATION_START:
//		//CCLOG("%d start: %s", trackIndex, animationName.c_str());
//		eventType = "start";
//		break;
//	case ANIMATION_END:
//		//CCLOG("%d end: %s", trackIndex, animationName.c_str());
//		eventType = "end";
//		break;
//	case ANIMATION_COMPLETE:
//		//CCLOG("%d complete: %s, %d", trackIndex, animationName.c_str(), loopCount);
//		eventType = "complete";
//		break;
//	case ANIMATION_EVENT:
//		//CCLOG("%d event: %s, %s: %d, %f, %s", trackIndex, animationName.c_str(), event->data->name, event->intValue, event->floatValue, event->stringValue);
//		eventType = "event";
//		break;
//	}
//
//    int nHandler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, static_cast<ScriptHandlerMgr::HandlerType>(SCRIPT_SPINE_EVENT));
//    if (0 != nHandler) {
//        SendSpineEventToLua(nHandler, eventType, trackIndex, animationName, loopCount);
//        LuaValueDict eventData;
//        eventData.begin
//    }
	//fflush(stdout);
}
