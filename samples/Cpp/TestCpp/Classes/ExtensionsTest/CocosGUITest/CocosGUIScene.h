#ifndef __TestCpp__CocosGUIScene__
#define __TestCpp__CocosGUIScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../../testBasic.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class CocosGUITestScene : public TestScene
{
public:
	CocosGUITestScene(bool bPortrait = false);
    virtual ~CocosGUITestScene();
	virtual void runThisTest();
    
	// The CallBack for back to the main menu scene
	virtual void MainMenuCallback(CCObject* pSender);
    
    void toCocosGUIExampleScene(CCObject* pSender);
    
    UILayer* ul;
};

#endif /* defined(__TestCpp__CocosGUIScene__) */
