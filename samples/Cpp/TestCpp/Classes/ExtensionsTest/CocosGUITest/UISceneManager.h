

#ifndef __TestCpp__UISceneManager__
#define __TestCpp__UISceneManager__

#include "cocos2d.h"

USING_NS_CC;

class UISceneManager : public CCObject
{
public:
    UISceneManager();
    ~UISceneManager();
    /** Returns the singleton of the ui scene manager. */
    static UISceneManager * sharedUISceneManager();
	static void purgeUISceneManager();
    
    /** Returns the next ui scene. */
    cocos2d::CCScene *nextUIScene();
    
    /** Returns the previous ui scene. */
    cocos2d::CCScene *previousUIScene();
    
    /** Returns the current control scene. */
    cocos2d::CCScene *currentUIScene();
    
    /** UI scene id. */
    CC_SYNTHESIZE(int, m_nCurrentUISceneId, CurrentUISceneId)
};

#endif /* defined(__TestCpp__UISceneManager__) */
