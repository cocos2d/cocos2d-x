

#ifndef __TestCpp__CCBParseScene__
#define __TestCpp__CCBParseScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../../testBasic.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CCBParseScene : public CCScene
{
public:
    CCBParseScene();
    ~CCBParseScene();
    
    virtual void onEnter();
    virtual void onExit();

    virtual void runThisTest();

protected:
    UILayer* m_pUILayer;

};

#endif /* defined(__TestCpp__CCBParseScene__) */
