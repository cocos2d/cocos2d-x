/*
 * LuaSkeletonAnimation.h
 *
 *  Created on: 2013?11?21?
 *      Author: edwardzhou
 */

#ifndef LUASKELETONANIMATION_H_
#define LUASKELETONANIMATION_H_
#include "spine/spine-cocos2dx.h"

#define SCRIPT_SPINE_EVENT 10001

class LuaSkeletonAnimation: public spine::CCSkeletonAnimation {
private:
	void animationStateEvent (spine::CCSkeletonAnimation* node, int trackIndex, spEventType type, spEvent* event, int loopCount);

public:
	static LuaSkeletonAnimation* createWithFile (const char* skeletonDataFile, const char* atlasFile, float scale = 1);

	LuaSkeletonAnimation (const char* skeletonDataFile, const char* atlasFile, float scale = 1);

	//LuaSkeletonAnimation();
	virtual ~LuaSkeletonAnimation();
};

#endif /* LUASKELETONANIMATION_H_ */
