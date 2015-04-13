

#ifndef __TestCpp__UIRichTextTest__
#define __TestCpp__UIRichTextTest__

#include "../UIScene.h"

DEFINE_TEST_SUITE(UIRichTextTests);

class UIRichTextTest : public UIScene
{
public:
    CREATE_FUNC(UIRichTextTest);

    UIRichTextTest();
    ~UIRichTextTest();

    virtual bool init() override;
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    
protected:
    cocos2d::ui::RichText* _richText;
};

#endif /* defined(__TestCpp__UIRichTextTest__) */
