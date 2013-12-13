#ifndef _ATLAS_TEST_H_
#define _ATLAS_TEST_H_

#include "../testBasic.h"
#include "../BaseTest.h"


class AtlasDemo : public BaseTest
{
protected:

public:
    CREATE_FUNC(AtlasDemo);

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
    CREATE_FUNC(Atlas1);

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
    CREATE_FUNC(LabelAtlasTest);

    LabelAtlasTest();

    virtual void step(float dt);

    virtual std::string title();
    virtual std::string subtitle();
};

class LabelAtlasColorTest : public AtlasDemo
{
    float        _time;
public:
    CREATE_FUNC(LabelAtlasColorTest);

    LabelAtlasColorTest();
    virtual void step(float dt);
    virtual std::string title();
    virtual std::string subtitle();
    void actionFinishCallback();
};

class LabelTTFAlignment : public AtlasDemo
{
public:
    CREATE_FUNC(LabelTTFAlignment);

    LabelTTFAlignment();
    virtual std::string title();
    virtual std::string subtitle();
};


class Atlas3 : public AtlasDemo
{
    float        _time;
public:
    CREATE_FUNC(Atlas3);

    Atlas3();

    virtual void step(float dt);

    virtual std::string title();
    virtual std::string subtitle();
};

class Atlas4 : public AtlasDemo
{
    float        _time;
public:
    CREATE_FUNC(Atlas4);

    Atlas4();
    virtual void step(float dt);
    virtual void draw();

    virtual std::string title();
    virtual std::string subtitle();
};

class Atlas5 : public AtlasDemo
{
public:
    CREATE_FUNC(Atlas5);

    Atlas5();
    virtual std::string title();
    virtual std::string subtitle();
};


class Atlas6 : public AtlasDemo
{
public:
    CREATE_FUNC(Atlas6);

    Atlas6();
    virtual std::string title();
    virtual std::string subtitle();
};

class AtlasBitmapColor : public AtlasDemo
{
public:
    CREATE_FUNC(AtlasBitmapColor);

    AtlasBitmapColor();
    virtual std::string title();

    virtual std::string subtitle();
};

class AtlasFastBitmap : public AtlasDemo
{
public:
    CREATE_FUNC(AtlasFastBitmap);

    AtlasFastBitmap();
    virtual std::string title();
    virtual std::string subtitle();
};

class BitmapFontMultiLine : public AtlasDemo
{
public:
    CREATE_FUNC(BitmapFontMultiLine);

    BitmapFontMultiLine();
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelsEmpty : public AtlasDemo
{
public:
    CREATE_FUNC(LabelsEmpty);

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
    CREATE_FUNC(LabelBMFontHD);

    LabelBMFontHD();
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelAtlasHD : public AtlasDemo
{
public:
    CREATE_FUNC(LabelAtlasHD);

    LabelAtlasHD();
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelGlyphDesigner : public AtlasDemo
{
public:
    CREATE_FUNC(LabelGlyphDesigner);

    LabelGlyphDesigner();
    virtual std::string title();
    virtual std::string subtitle();
};

class AtlasTestScene : public TestScene
{
public:
    CREATE_FUNC(AtlasTestScene);

    virtual void runThisTest();
};

class LabelTTFTest : public AtlasDemo
{
public:
    CREATE_FUNC(LabelTTFTest);

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
    TextHAlignment _horizAlign;
    TextVAlignment _vertAlign;
};

class LabelTTFMultiline : public AtlasDemo
{
public:
    CREATE_FUNC(LabelTTFMultiline);

    LabelTTFMultiline();
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelTTFChinese : public AtlasDemo
{
public:
    CREATE_FUNC(LabelTTFChinese);

    LabelTTFChinese();
    virtual std::string title();
};

class LabelBMFontChinese : public AtlasDemo
{
public:
    CREATE_FUNC(LabelBMFontChinese);

    LabelBMFontChinese();
    virtual std::string title();
};

class BitmapFontMultiLineAlignment : public AtlasDemo
{
public:
    CREATE_FUNC(BitmapFontMultiLineAlignment);

    BitmapFontMultiLineAlignment();
    ~BitmapFontMultiLineAlignment();
    void snapArrowsToEdge();
    virtual std::string title();
    virtual std::string subtitle();
    void stringChanged(Object *sender);
    void alignmentChanged(Object *sender);
    void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event  *event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);

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
    CREATE_FUNC(LabelTTFA8Test);

    LabelTTFA8Test();

    virtual std::string title();
    virtual std::string subtitle();
};

class BMFontOneAtlas : public AtlasDemo
{
public:
    CREATE_FUNC(BMFontOneAtlas);

    BMFontOneAtlas();

    virtual std::string title();
    virtual std::string subtitle();
};

class BMFontUnicode : public AtlasDemo
{
public:
    CREATE_FUNC(BMFontUnicode);

    BMFontUnicode();

    virtual std::string title();
    virtual std::string subtitle();
};

class BMFontInit : public AtlasDemo
{
public:
    CREATE_FUNC(BMFontInit);

    BMFontInit();

    virtual std::string title();
    virtual std::string subtitle();
};

class TTFFontInit : public AtlasDemo
{
public:
    CREATE_FUNC(TTFFontInit);

    TTFFontInit();

    virtual std::string title();
    virtual std::string subtitle();
};

class TTFFontShadowAndStroke : public AtlasDemo
{
public:
    CREATE_FUNC(TTFFontShadowAndStroke);

    TTFFontShadowAndStroke();
    
    virtual std::string title();
    virtual std::string subtitle();
};


class Issue1343 : public AtlasDemo
{
public:
    CREATE_FUNC(Issue1343);

    Issue1343();

    virtual std::string title();
    virtual std::string subtitle();
};

class LabelBMFontBounds : public AtlasDemo
{
public:
    CREATE_FUNC(LabelBMFontBounds);

    LabelBMFontBounds();
    
    virtual void draw();
    virtual std::string title();
    virtual std::string subtitle();
private:
    LabelBMFont *label1;
};

class NewLabelTTFUnicode : public AtlasDemo
{
public:
    CREATE_FUNC(NewLabelTTFUnicode);

    NewLabelTTFUnicode();
    
    virtual std::string title();
    virtual std::string subtitle();
};

class NewLabelBMFontTest : public AtlasDemo
{
public:
    CREATE_FUNC(NewLabelBMFontTest);

    NewLabelBMFontTest();

    virtual std::string title();
    virtual std::string subtitle();

private:
};

class NewLabelFontDefTest : public AtlasDemo
{
public:
    CREATE_FUNC(NewLabelFontDefTest);

    NewLabelFontDefTest();

    virtual std::string title();
    virtual std::string subtitle();

private:
};

class LabelBMFontCrashTest : public AtlasDemo
{
public:
    CREATE_FUNC(LabelBMFontCrashTest);

    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
};


// we don't support linebreak mode

#endif
