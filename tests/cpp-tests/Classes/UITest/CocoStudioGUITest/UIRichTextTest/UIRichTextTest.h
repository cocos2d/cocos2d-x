

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
    void touchEvent(Ref *pSender, Widget::TouchEventType type);
    
protected:
    RichText* _richText;
};

#endif /* defined(__TestCpp__UIRichTextTest__) */
