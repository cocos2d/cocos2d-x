#ifndef _ATLAS_TEST_NEW_H_
#define _ATLAS_TEST_NEW_H_

#include "../testBasic.h"
#include "../BaseTest.h"
#include "2d/renderer/CCCustomCommand.h"
#include "ui/CocosGUI.h"


class AtlasDemoNew : public BaseTest
{
protected:

public:
    CREATE_FUNC(AtlasDemoNew);

    AtlasDemoNew(void);
    ~AtlasDemoNew(void);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onEnter() override;

    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);
};

class LabelTTFAlignmentNew : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelTTFAlignmentNew);

    LabelTTFAlignmentNew();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelFNTColorAndOpacity : public AtlasDemoNew
{
    float        _time;
public:
    CREATE_FUNC(LabelFNTColorAndOpacity);

    LabelFNTColorAndOpacity();

    virtual void step(float dt);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelFNTSpriteActions : public AtlasDemoNew
{
    float        _time;
public:
    CREATE_FUNC(LabelFNTSpriteActions);

    LabelFNTSpriteActions();
    virtual void step(float dt);
    virtual void draw(Renderer *renderer, const Matrix &transform, bool transformUpdated) override;

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:
    CustomCommand _renderCmd;
    void onDraw(const Matrix &transform, bool transformUpdated);
};

class LabelFNTPadding : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelFNTPadding);

    LabelFNTPadding();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};


class LabelFNTOffset : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelFNTOffset);

    LabelFNTOffset();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelFNTColor : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelFNTColor);

    LabelFNTColor();
    virtual std::string title() const override;

    virtual std::string subtitle() const override;
};

class LabelFNTHundredLabels : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelFNTHundredLabels);

    LabelFNTHundredLabels();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelFNTMultiLine : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelFNTMultiLine);

    LabelFNTMultiLine();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelFNTandTTFEmpty : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelFNTandTTFEmpty);

    LabelFNTandTTFEmpty();
    void updateStrings(float dt);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

private:
    bool setEmpty;
};

class LabelFNTRetina : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelFNTRetina);

    LabelFNTRetina();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelFNTGlyphDesigner : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelFNTGlyphDesigner);

    LabelFNTGlyphDesigner();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
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
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelFNTUnicodeChinese : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelFNTUnicodeChinese);

    LabelFNTUnicodeChinese();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelFNTMultiLineAlignment : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelFNTMultiLineAlignment);

    LabelFNTMultiLineAlignment();
    ~LabelFNTMultiLineAlignment();
    void snapArrowsToEdge();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void stringChanged(Ref *sender);
    void alignmentChanged(Ref *sender);
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

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelFNTBounds : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelFNTBounds);

    LabelFNTBounds();
    
    virtual void draw(Renderer *renderer, const Matrix &transform, bool transformUpdated) override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:
    CustomCommand _renderCmd;
    void onDraw(const Matrix &transform, bool transformUpdated);
    Label *label1;
};

class LabelTTFLongLineWrapping : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelTTFLongLineWrapping);

    LabelTTFLongLineWrapping();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelTTFColor : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelTTFColor);

    LabelTTFColor();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelTTFUnicodeNew : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelTTFUnicodeNew);

    LabelTTFUnicodeNew();
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelTTFDynamicAlignment : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelTTFDynamicAlignment);

    LabelTTFDynamicAlignment();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
private:
    
    void setAlignmentLeft(Ref* sender);
    void setAlignmentCenter(Ref* sender);
    void setAlignmentRight(Ref* sender);
    void updateAlignment();
    
    Label          * _label;
    TextHAlignment   _horizAlign;
    
};


class LabelTTFCJKWrappingTest : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelTTFCJKWrappingTest);

    LabelTTFCJKWrappingTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

private:
};


class LabelTTFFontsTestNew : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelTTFFontsTestNew);

    LabelTTFFontsTestNew();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};


class LabelBMFontTestNew : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelBMFontTestNew);

    LabelBMFontTestNew();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

private:
};

class LabelFontDefTestNew : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelFontDefTestNew);

    LabelFontDefTestNew();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

private:
};

class LabelTTFDistanceField : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelTTFDistanceField);

    LabelTTFDistanceField();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelOutlineAndGlowTest : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelOutlineAndGlowTest);

    LabelOutlineAndGlowTest();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelShadowTest : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelShadowTest);

    LabelShadowTest();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void sliderEvent(Ref *pSender, ui::SliderEventType type);
private:
    Label* shadowLabelOutline;
    Label* shadowLabelTTF;
    Label* shadowLabelBMFont;
};

class LabelCharMapTest : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelCharMapTest);

    LabelCharMapTest();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void step(float dt);

private:
    float _time; 
};

class LabelCharMapColorTest : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelCharMapColorTest);

    LabelCharMapColorTest();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void step(float dt);
    void actionFinishCallback();

private:
    float _time; 
};

class LabelCrashTest : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelCrashTest);

    LabelCrashTest();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelTTFOldNew : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelTTFOldNew);

    LabelTTFOldNew();

    virtual void draw(Renderer *renderer, const Matrix &transform, bool transformUpdated) override;

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:
    CustomCommand _renderCmd;
    void onDraw(const Matrix &transform, bool transformUpdated);
};

class LabelTTFLargeText : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelTTFLargeText);

    LabelTTFLargeText();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelFontNameTest : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelFontNameTest);

    LabelFontNameTest();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelAlignmentTest : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelAlignmentTest);

    LabelAlignmentTest();
    virtual ~LabelAlignmentTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
private:
    void  setAlignmentLeft(Ref* sender);
    void  setAlignmentCenter(Ref* sender);
    void  setAlignmentRight(Ref* sender);
    void  setAlignmentTop(Ref* sender);
    void  setAlignmentMiddle(Ref* sender);
    void  setAlignmentBottom(Ref* sender);
    const char* getCurrentAlignment();

    Label* _label;
    TextHAlignment _horizAlign;
    TextVAlignment _vertAlign;
};

class LabelIssue4428Test : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelIssue4428Test);

    LabelIssue4428Test();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

// we don't support linebreak mode

#endif
