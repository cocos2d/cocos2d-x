

#ifndef __TestCpp__UITextAtlasTest__
#define __TestCpp__UITextAtlasTest__

#include "../UIScene.h"

DEFINE_TEST_SUITE(UITextAtlasTests);

class UITextAtlasTest : public UIScene
{
public:
    CREATE_FUNC(UITextAtlasTest);

    virtual bool init() override;
    void printWidgetResources(cocos2d::Ref* sender);
protected:
    cocos2d::ui::TextAtlas* _textAtlas;
};

#endif /* defined(__TestCpp__UITextAtlasTest__) */
