#ifndef _HELLOWORLD_LAYER_H_
#define _HELLOWORLD_LAYER_H_

#include "cocos2d.h"

[! if CCX_USE_BOX2D]
#include "Box2D.h"
[! endif]
[! if CCX_USE_CHIPMUNK]
#include "chipmunk.h"
[! endif]
[! if CCX_USE_COCOS_DENSHION_SIMPLE_AUDIO_ENGINE]
#include "SimpleAudioEngine.h"
[! endif]

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    virtual void menuCloseCallback(NSObject* pSender);

    // implement the "static node()" method manually
    LAYER_NODE_FUNC(HelloWorld);
};

#endif  // _HELLOWORLD_SCENE_H_
