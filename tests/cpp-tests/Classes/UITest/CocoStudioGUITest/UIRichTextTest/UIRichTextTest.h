

#ifndef __TestCpp__UIRichTextTest__
#define __TestCpp__UIRichTextTest__

#include "../UIScene.h"

DEFINE_TEST_SUITE(UIRichTextTests);

class UIRichTextTest : public UIScene
{
public:
    CREATE_FUNC(UIRichTextTest);

    bool init() override;
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void switchWrapMode(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

protected:
    cocos2d::ui::RichText* _richText;
};

class UIRichTextXMLBasic : public UIScene
{
public:
    CREATE_FUNC(UIRichTextXMLBasic);

    bool init() override;
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void switchWrapMode(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

protected:
    cocos2d::ui::RichText* _richText;
};

class UIRichTextXMLSmallBig : public UIScene
{
public:
    CREATE_FUNC(UIRichTextXMLSmallBig);

    bool init() override;
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void switchWrapMode(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

protected:
    cocos2d::ui::RichText* _richText;
};

class UIRichTextXMLColor : public UIScene
{
public:
    CREATE_FUNC(UIRichTextXMLColor);

    bool init() override;
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void switchWrapMode(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

protected:
    cocos2d::ui::RichText* _richText;
};

class UIRichTextXMLSUIB : public UIScene
{
public:
    CREATE_FUNC(UIRichTextXMLSUIB);

    bool init() override;
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void switchWrapMode(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

protected:
    cocos2d::ui::RichText* _richText;
};

class UIRichTextXMLSUIB2 : public UIScene
{
public:
    CREATE_FUNC(UIRichTextXMLSUIB2);

    bool init() override;
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void switchWrapMode(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

protected:
    cocos2d::ui::RichText* _richText;
};

class UIRichTextXMLSUIB3 : public UIScene
{
public:
    CREATE_FUNC(UIRichTextXMLSUIB3);

    bool init() override;
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void switchWrapMode(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

protected:
    cocos2d::ui::RichText* _richText;
};

class UIRichTextXMLImg : public UIScene
{
public:
    CREATE_FUNC(UIRichTextXMLImg);

    bool init() override;
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void switchWrapMode(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

protected:
    cocos2d::ui::RichText* _richText;
};

class UIRichTextXMLUrl : public UIScene
{
public:
    CREATE_FUNC(UIRichTextXMLUrl);

    bool init() override;
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void switchWrapMode(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

protected:
    cocos2d::ui::RichText* _richText;
};

class UIRichTextXMLFace : public UIScene
{
public:
    CREATE_FUNC(UIRichTextXMLFace);

    bool init() override;
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void switchWrapMode(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

protected:
    cocos2d::ui::RichText* _richText;
};

class UIRichTextXMLBR : public UIScene
{
public:
    CREATE_FUNC(UIRichTextXMLBR);

    bool init() override;
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void switchWrapMode(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

protected:
    cocos2d::ui::RichText* _richText;
};

class UIRichTextXMLInvalid : public UIScene
{
public:
    CREATE_FUNC(UIRichTextXMLInvalid);

    bool init() override;

protected:
    cocos2d::ui::RichText* _richText;
};



#endif /* defined(__TestCpp__UIRichTextTest__) */
