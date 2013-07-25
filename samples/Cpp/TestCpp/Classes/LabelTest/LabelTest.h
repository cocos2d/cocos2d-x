#ifndef _ATLAS_TEST_H_
#define _ATLAS_TEST_H_

#include "../testBasic.h"
#include "../BaseTest.h"

class AtlasDemo : public BaseTest
{
protected:

public:
    AtlasDemo(void);
    ~AtlasDemo(void);

    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();

    void restartCallback(Object* sender);
    void nextCallback(Object* sender);
    void backCallback(Object* sender);
};


class Atlas1 : public AtlasDemo
{
    TextureAtlas*        _textureAtlas;
public:
    Atlas1();
    ~Atlas1();
    virtual std::string title();
    virtual std::string subtitle();
    virtual void draw();
};

class LabelAtlasTest : public AtlasDemo
{
    float        _time;
public:
    LabelAtlasTest();

    virtual void step(float dt);

    virtual std::string title();
    virtual std::string subtitle();
};

class LabelAtlasColorTest : public AtlasDemo
{
    float        _time;
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
    float        _time;
public:
    Atlas3();

    virtual void step(float dt);

    virtual std::string title();
    virtual std::string subtitle();
};

class Atlas4 : public AtlasDemo
{
    float        _time;
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
    void  setAlignmentLeft(Object* sender);
    void  setAlignmentCenter(Object* sender);
    void  setAlignmentRight(Object* sender);
    void  setAlignmentTop(Object* sender);
    void  setAlignmentMiddle(Object* sender);
    void  setAlignmentBottom(Object* sender);
    void  updateAlignment();
    const char* getCurrentAlignment();
private:
    LabelTTF* _plabel;
    Label::HAlignment _horizAlign;
    Label::VAlignment _vertAlign;
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
    void stringChanged(Object *sender);
    void alignmentChanged(Object *sender);
    virtual void ccTouchesBegan(Set  *touches, Event  *event);
    virtual void ccTouchesEnded(Set  *touches, Event  *event);
    virtual void ccTouchesMoved(Set  *touches, Event  *event);

public:
    LabelBMFont *_labelShouldRetain;
    Sprite *_arrowsBarShouldRetain;
    Sprite *_arrowsShouldRetain;
    MenuItemFont *_lastSentenceItem, *_lastAlignmentItem;
    bool _drag;
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
    LabelBMFont *label1;
};

// we don't support linebreak mode

#endif
