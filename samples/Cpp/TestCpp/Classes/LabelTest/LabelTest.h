#ifndef _ATLAS_TEST_H_
#define _ATLAS_TEST_H_

#include "../testBasic.h"

class AtlasDemo : public CCLayer
{
protected:

public:
    AtlasDemo(void);
    ~AtlasDemo(void);

    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();

    void restartCallback(CCObject* pSender);
    void nextCallback(CCObject* pSender);
    void backCallback(CCObject* pSender);
};


class Atlas1 : public AtlasDemo
{
    CCTextureAtlas*        m_textureAtlas;
public:
    Atlas1();
    ~Atlas1();
    virtual std::string title();
    virtual std::string subtitle();
    virtual void draw();
};

class LabelAtlasTest : public AtlasDemo
{
    float        m_time;
public:
    LabelAtlasTest();

    virtual void step(float dt);

    virtual std::string title();
    virtual std::string subtitle();
};

class LabelAtlasColorTest : public AtlasDemo
{
    float        m_time;
public:
    LabelAtlasColorTest();
    virtual void step(float dt);
    virtual std::string title();
    virtual std::string subtitle();
    void actionFinishCallback();
};

class LabelTTFAlignment : public AtlasDemo
{
public:
    LabelTTFAlignment();
    virtual std::string title();
    virtual std::string subtitle();
};


class Atlas3 : public AtlasDemo
{
    float        m_time;
public:
    Atlas3();

    virtual void step(float dt);

    virtual std::string title();
    virtual std::string subtitle();
};

class Atlas4 : public AtlasDemo
{
    float        m_time;
public:
    Atlas4();
    virtual void step(float dt);
    virtual void draw();

    virtual std::string title();
    virtual std::string subtitle();
};

class Atlas5 : public AtlasDemo
{
public:
    Atlas5();
    virtual std::string title();
    virtual std::string subtitle();
};


class Atlas6 : public AtlasDemo
{
public:
    Atlas6();
    virtual std::string title();
    virtual std::string subtitle();
};

class AtlasBitmapColor : public AtlasDemo
{
public:
    AtlasBitmapColor();
    virtual std::string title();

    virtual std::string subtitle();
};

class AtlasFastBitmap : public AtlasDemo
{
public:
    AtlasFastBitmap();
    virtual std::string title();
    virtual std::string subtitle();
};

class BitmapFontMultiLine : public AtlasDemo
{
public:
    BitmapFontMultiLine();
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelsEmpty : public AtlasDemo
{
public:
    LabelsEmpty();
    void updateStrings(float dt);
    virtual std::string title();
    virtual std::string subtitle();

private:
    bool setEmpty;
};

class LabelBMFontHD : public AtlasDemo
{
public:
    LabelBMFontHD();
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelAtlasHD : public AtlasDemo
{
public:
    LabelAtlasHD();
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelGlyphDesigner : public AtlasDemo
{
public:
    LabelGlyphDesigner();
    virtual std::string title();
    virtual std::string subtitle();
};

class AtlasTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class LabelTTFTest : public AtlasDemo
{
public:
    LabelTTFTest();
    virtual ~LabelTTFTest();
    virtual std::string title();
    virtual std::string subtitle();
private:
    void  setAlignmentLeft(CCObject* pSender);
    void  setAlignmentCenter(CCObject* pSender);
    void  setAlignmentRight(CCObject* pSender);
    void  setAlignmentTop(CCObject* pSender);
    void  setAlignmentMiddle(CCObject* pSender);
    void  setAlignmentBottom(CCObject* pSender);
    void  updateAlignment();
    const char* getCurrentAlignment();
private:
    CCLabelTTF* m_plabel;
    CCTextAlignment m_eHorizAlign;
    CCVerticalTextAlignment m_eVertAlign;
};

class LabelTTFMultiline : public AtlasDemo
{
public:
    LabelTTFMultiline();
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelTTFChinese : public AtlasDemo
{
public:
    LabelTTFChinese();
    virtual std::string title();
};

class LabelBMFontChinese : public AtlasDemo
{
public:
    LabelBMFontChinese();
    virtual std::string title();
};

class BitmapFontMultiLineAlignment : public AtlasDemo
{
public:
    BitmapFontMultiLineAlignment();
    ~BitmapFontMultiLineAlignment();
    void snapArrowsToEdge();
    virtual std::string title();
    virtual std::string subtitle();
    void stringChanged(CCObject *sender);
    void alignmentChanged(CCObject *sender);
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);

public:
    CCLabelBMFont *m_pLabelShouldRetain;
    CCSprite *m_pArrowsBarShouldRetain;
    CCSprite *m_pArrowsShouldRetain;
    CCMenuItemFont *m_pLastSentenceItem, *m_pLastAlignmentItem;
    bool m_drag;
};

class LabelTTFA8Test : public AtlasDemo
{
public:
    LabelTTFA8Test();

    virtual std::string title();
    virtual std::string subtitle();
};

class BMFontOneAtlas : public AtlasDemo
{
public:
    BMFontOneAtlas();

    virtual std::string title();
    virtual std::string subtitle();
};

class BMFontUnicode : public AtlasDemo
{
public:
    BMFontUnicode();

    virtual std::string title();
    virtual std::string subtitle();
};

class BMFontInit : public AtlasDemo
{
public:
    BMFontInit();

    virtual std::string title();
    virtual std::string subtitle();
};

class TTFFontInit : public AtlasDemo
{
public:
    TTFFontInit();

    virtual std::string title();
    virtual std::string subtitle();
};

class TTFFontShadowAndStroke : public AtlasDemo
{
public:
    TTFFontShadowAndStroke();
    
    virtual std::string title();
    virtual std::string subtitle();
};


class Issue1343 : public AtlasDemo
{
public:
    Issue1343();

    virtual std::string title();
    virtual std::string subtitle();
};

class LabelBMFontBounds : public AtlasDemo
{
public:
    LabelBMFontBounds();
    
    virtual void draw();
    virtual std::string title();
    virtual std::string subtitle();
private:
    CCLabelBMFont *label1;
};

// we don't support linebreak mode

#endif
