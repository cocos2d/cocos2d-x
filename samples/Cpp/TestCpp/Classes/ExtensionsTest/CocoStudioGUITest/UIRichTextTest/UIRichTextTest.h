

#ifndef __TestCpp__UIRichTextTest__
#define __TestCpp__UIRichTextTest__

#include "../UIScene.h"

class UIRichTextTest : public UIScene
{
public:
    UIRichTextTest();
    ~UIRichTextTest();
    bool init();
    void touchEvent(CCObject *pSender, TouchEventType type);
    
protected:
    UI_SCENE_CREATE_FUNC(UIRichTextTest)
    
protected:
    RichText* _richText;
};

#endif /* defined(__TestCpp__UIRichTextTest__) */
