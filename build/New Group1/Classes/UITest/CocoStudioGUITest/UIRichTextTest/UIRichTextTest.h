/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/



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
    void switchAlignment(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

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
    void switchAlignment(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

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
    void switchAlignment(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

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
    void switchAlignment(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

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
    void switchAlignment(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

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
    void switchAlignment(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

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
    void switchAlignment(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

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
    void switchAlignment(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

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
    void switchAlignment(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

protected:
    cocos2d::ui::RichText* _richText;
};

class UIRichTextXMLUrlImg : public UIScene
{
public:
    CREATE_FUNC(UIRichTextXMLUrlImg);
    
    bool init() override;
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void switchWrapMode(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void switchAlignment(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

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
    void switchAlignment(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

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
    void switchAlignment(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

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

class UIRichTextXMLOutline : public UIScene
{
public:
    CREATE_FUNC(UIRichTextXMLOutline);
    
    bool init() override;
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void switchWrapMode(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void switchAlignment(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

protected:
    cocos2d::ui::RichText* _richText;
};

class UIRichTextXMLShadow : public UIScene
{
public:
    CREATE_FUNC(UIRichTextXMLShadow);
    
    bool init() override;
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void switchWrapMode(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void switchAlignment(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

protected:
    cocos2d::ui::RichText* _richText;
};

class UIRichTextXMLGlow : public UIScene
{
public:
    CREATE_FUNC(UIRichTextXMLGlow);
    
    bool init() override;
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void switchWrapMode(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void switchAlignment(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

protected:
    cocos2d::ui::RichText* _richText;
};

class UIRichTextXMLExtend : public UIScene
{
public:
    CREATE_FUNC(UIRichTextXMLExtend);
    
    bool init() override;
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void switchWrapMode(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void switchAlignment(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

protected:
    cocos2d::ui::RichText* _richText;
};

class UIRichTextXMLSpace : public UIScene
{
public:
    CREATE_FUNC(UIRichTextXMLSpace);
    
    bool init() override;
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void switchWrapMode(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void switchAlignment(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

protected:
    cocos2d::ui::RichText* _richText;
};

#endif /* defined(__TestCpp__UIRichTextTest__) */
