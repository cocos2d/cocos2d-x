#ifndef _ATLAS_TEST_NEW_H_
#define _ATLAS_TEST_NEW_H_

#include "../testBasic.h"
#include "../BaseTest.h"


class AtlasDemoNew : public BaseTest
{
protected:

public:
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
    LabelTTFAlignmentNew();
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelFNTColorAndOpacity : public AtlasDemoNew
{
    float        _time;
public:
    LabelFNTColorAndOpacity();

    virtual void step(float dt);

    virtual std::string title();
    virtual std::string subtitle();
};

class LabelFNTSpriteActions : public AtlasDemoNew
{
    float        _time;
public:
    LabelFNTSpriteActions();
    virtual void step(float dt);
    virtual void draw();

    virtual std::string title();
    virtual std::string subtitle();
};

class LabelFNTPadding : public AtlasDemoNew
{
public:
    LabelFNTPadding();
    virtual std::string title();
    virtual std::string subtitle();
};


class LabelFNTOffset : public AtlasDemoNew
{
public:
    LabelFNTOffset();
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelFNTColor : public AtlasDemoNew
{
public:
    LabelFNTColor();
    virtual std::string title();

    virtual std::string subtitle();
};

class LabelFNTHundredLabels : public AtlasDemoNew
{
public:
    LabelFNTHundredLabels();
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelFNTMultiLine : public AtlasDemoNew
{
public:
    LabelFNTMultiLine();
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelFNTandTTFEmpty : public AtlasDemoNew
{
public:
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
    LabelFNTRetina();
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelFNTGlyphDesigner : public AtlasDemoNew
{
public:
    LabelFNTGlyphDesigner();
    virtual std::string title();
    virtual std::string subtitle();
};

class AtlasTestSceneNew : public TestScene
{
public:
    virtual void runThisTest();
};

class LabelTTFUnicodeChinese : public AtlasDemoNew
{
public:
    LabelTTFUnicodeChinese();
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelFNTUnicodeChinese : public AtlasDemoNew
{
public:
    LabelFNTUnicodeChinese();
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelFNTMultiLineAlignment : public AtlasDemoNew
{
public:
    LabelFNTMultiLineAlignment();
    ~LabelFNTMultiLineAlignment();
    void snapArrowsToEdge();
    virtual std::string title();
    virtual std::string subtitle();
    void stringChanged(Object *sender);
    void alignmentChanged(Object *sender);
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event  *event);
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);

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
    LabelFNTUNICODELanguages();

    virtual std::string title();
    virtual std::string subtitle();
};

class LabelFNTBounds : public AtlasDemoNew
{
public:
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

    LabelTTFLongLineWrapping();

    virtual std::string title();
    virtual std::string subtitle();
};

class LabelTTFColor : public AtlasDemoNew
{
public:

    LabelTTFColor();

    virtual std::string title();
    virtual std::string subtitle();
};

class LabelTTFUnicodeNew : public AtlasDemoNew
{
public:
    
    LabelTTFUnicodeNew();
    
    virtual std::string title();
    virtual std::string subtitle();
};

class LabelTTFDynamicAlignment : public AtlasDemoNew
{
public:
    
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

    LabelTTFFontsTestNew();

    virtual std::string title();
    virtual std::string subtitle();
};


class LabelBMFontTestNew : public AtlasDemoNew
{
public:

    LabelBMFontTestNew();

    virtual std::string title();
    virtual std::string subtitle();

private:
};

class LabelFontDefTestNew : public AtlasDemoNew
{
public:

    LabelFontDefTestNew();

    virtual std::string title();
    virtual std::string subtitle();

private:
};



// we don't support linebreak mode

#endif
