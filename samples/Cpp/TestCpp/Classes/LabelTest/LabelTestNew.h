#ifndef _ATLAS_TEST_NEW_H_
#define _ATLAS_TEST_NEW_H_

#include "../testBasic.h"
#include "../BaseTest.h"


class AtlasDemoNew : public BaseTest
{
protected:

public:
    CREATE_FUNC(AtlasDemoNew);

    AtlasDemoNew(void);
    ~AtlasDemoNew(void);

    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();

    void restartCallback(Object* sender);
    void nextCallback(Object* sender);
    void backCallback(Object* sender);
};

class LabelTTFAlignmentNew : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelTTFAlignmentNew);

    LabelTTFAlignmentNew();
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelFNTColorAndOpacity : public AtlasDemoNew
{
    float        _time;
public:
    CREATE_FUNC(LabelFNTColorAndOpacity);

    LabelFNTColorAndOpacity();

    virtual void step(float dt);

    virtual std::string title();
    virtual std::string subtitle();
};

class LabelFNTSpriteActions : public AtlasDemoNew
{
    float        _time;
public:
    CREATE_FUNC(LabelFNTSpriteActions);

    LabelFNTSpriteActions();
    virtual void step(float dt);
    virtual void draw();

    virtual std::string title();
    virtual std::string subtitle();
};

class LabelFNTPadding : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelFNTPadding);

    LabelFNTPadding();
    virtual std::string title();
    virtual std::string subtitle();
};


class LabelFNTOffset : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelFNTOffset);

    LabelFNTOffset();
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelFNTColor : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelFNTColor);

    LabelFNTColor();
    virtual std::string title();

    virtual std::string subtitle();
};

class LabelFNTHundredLabels : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelFNTHundredLabels);

    LabelFNTHundredLabels();
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelFNTMultiLine : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelFNTMultiLine);

    LabelFNTMultiLine();
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelFNTandTTFEmpty : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelFNTandTTFEmpty);

    LabelFNTandTTFEmpty();
    void updateStrings(float dt);
    virtual std::string title();
    virtual std::string subtitle();

private:
    bool setEmpty;
};

class LabelFNTRetina : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelFNTRetina);

    LabelFNTRetina();
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelFNTGlyphDesigner : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelFNTGlyphDesigner);

    LabelFNTGlyphDesigner();
    virtual std::string title();
    virtual std::string subtitle();
};

class AtlasTestSceneNew : public TestScene
{
public:
    CREATE_FUNC(AtlasTestSceneNew);

    virtual void runThisTest();
};

class LabelTTFUnicodeChinese : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelTTFUnicodeChinese);

    LabelTTFUnicodeChinese();
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelFNTUnicodeChinese : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelFNTUnicodeChinese);

    LabelFNTUnicodeChinese();
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelFNTMultiLineAlignment : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelFNTMultiLineAlignment);

    LabelFNTMultiLineAlignment();
    ~LabelFNTMultiLineAlignment();
    void snapArrowsToEdge();
    virtual std::string title();
    virtual std::string subtitle();
    void stringChanged(Object *sender);
    void alignmentChanged(Object *sender);
    void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event  *event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);

public:
    Label *_labelShouldRetain;
    Sprite *_arrowsBarShouldRetain;
    Sprite *_arrowsShouldRetain;
    MenuItemFont *_lastSentenceItem, *_lastAlignmentItem;
    bool _drag;
};

class LabelFNTUNICODELanguages : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelFNTUNICODELanguages);

    LabelFNTUNICODELanguages();

    virtual std::string title();
    virtual std::string subtitle();
};

class LabelFNTBounds : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelFNTBounds);

    LabelFNTBounds();
    
    virtual void draw();
    virtual std::string title();
    virtual std::string subtitle();
private:
    Label *label1;
};

class LabelTTFLongLineWrapping : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelTTFLongLineWrapping);

    LabelTTFLongLineWrapping();

    virtual std::string title();
    virtual std::string subtitle();
};

class LabelTTFColor : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelTTFColor);

    LabelTTFColor();

    virtual std::string title();
    virtual std::string subtitle();
};

class LabelTTFUnicodeNew : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelTTFUnicodeNew);

    LabelTTFUnicodeNew();
    
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelTTFDynamicAlignment : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelTTFDynamicAlignment);

    LabelTTFDynamicAlignment();
    virtual std::string title();
    virtual std::string subtitle();
    
private:
    
    void setAlignmentLeft(Object* sender);
    void setAlignmentCenter(Object* sender);
    void setAlignmentRight(Object* sender);
    void updateAlignment();
    
    Label          * _label;
    TextHAlignment   _horizAlign;
    
};


class LabelTTFFontsTestNew : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelTTFFontsTestNew);

    LabelTTFFontsTestNew();

    virtual std::string title();
    virtual std::string subtitle();
};


class LabelBMFontTestNew : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelBMFontTestNew);

    LabelBMFontTestNew();

    virtual std::string title();
    virtual std::string subtitle();

private:
};

class LabelFontDefTestNew : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelFontDefTestNew);

    LabelFontDefTestNew();

    virtual std::string title();
    virtual std::string subtitle();

private:
};

class LabelTTFDistanceField : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelTTFDistanceField);

    LabelTTFDistanceField();

    virtual std::string title();
    virtual std::string subtitle();
};

class LabelTTFDistanceFieldEffect : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelTTFDistanceFieldEffect);

    LabelTTFDistanceFieldEffect();

    virtual std::string title();
    virtual std::string subtitle();
};


// we don't support linebreak mode

#endif
