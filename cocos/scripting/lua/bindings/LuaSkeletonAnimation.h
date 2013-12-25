/*
 * LuaSkeletonAnimation.h
 *
 *  Created on: 2013?11?21?
 *      Author: edwardzhou
 */

#ifndef LUASKELETONANIMATION_H_
#define LUASKELETONANIMATION_H_
#include "spine-cocos2dx.h"

class LuaSkeletonAnimation: public spine::SkeletonAnimation {
private:
	void animationStateEvent (spine::SkeletonAnimation* node, int trackIndex, spEventType type, spEvent* event, int loopCount);

public:
	static LuaSkeletonAnimation* createWithFile (const char* skeletonDataFile, const char* atlasFile, float scale = 1);

	LuaSkeletonAnimation (const char* skeletonDataFile, const char* atlasFile, float scale = 1);

	virtual ~LuaSkeletonAnimation();
};

#endif /* LUASKELETONANIMATION_H_ */
