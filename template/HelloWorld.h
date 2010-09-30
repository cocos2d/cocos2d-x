
#ifndef _HELLOWORLD_SCENE_H_
#define _HELLOWORLD_SCENE_H_

#include "cocos2d.h"

class HelloWorld  // Here's not a child of CCScene!
{
public:
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
};

#endif // _HELLOWORLD_SCENE_H_