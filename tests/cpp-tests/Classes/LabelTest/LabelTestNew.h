#ifndef _ATLAS_TEST_NEW_H_
#define _ATLAS_TEST_NEW_H_

#include "../BaseTest.h"
#include "renderer/CCCustomCommand.h"
#include "ui/CocosGUI.h"

DEFINE_TEST_SUITE(NewLabelTests);

class AtlasDemoNew : public TestCase
{
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

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
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
    void stringChanged(cocos2d::Ref* sender);
    void alignmentChanged(cocos2d::Ref* sender);
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

public:
    cocos2d::Label* _labelShouldRetain;
    cocos2d::Sprite* _arrowsBarShouldRetain;
    cocos2d::Sprite* _arrowsShouldRetain;
    cocos2d::MenuItemFont *_lastSentenceItem, *_lastAlignmentItem;
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
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
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
    
    void setAlignmentLeft(cocos2d::Ref* sender);
    void setAlignmentCenter(cocos2d::Ref* sender);
    void setAlignmentRight(cocos2d::Ref* sender);
    void updateAlignment();
    
    cocos2d::Label* _label;
    cocos2d::TextHAlignment   _horizAlign;
    
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

    void sliderEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
private:
    cocos2d::Label* shadowLabelOutline;
    cocos2d::Label* shadowLabelTTF;
    cocos2d::Label* shadowLabelBMFont;
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
    void  setAlignmentLeft(cocos2d::Ref* sender);
    void  setAlignmentCenter(cocos2d::Ref* sender);
    void  setAlignmentRight(cocos2d::Ref* sender);
    void  setAlignmentTop(cocos2d::Ref* sender);
    void  setAlignmentMiddle(cocos2d::Ref* sender);
    void  setAlignmentBottom(cocos2d::Ref* sender);
    const char* getCurrentAlignment();

    cocos2d::Label* _label;
    cocos2d::TextHAlignment _horizAlign;
    cocos2d::TextVAlignment _vertAlign;
};

class LabelIssue4428Test : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelIssue4428Test);

    LabelIssue4428Test();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelIssue4999Test : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelIssue4999Test);

    LabelIssue4999Test();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelLineHeightTest : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelLineHeightTest);

    LabelLineHeightTest();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void sliderEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
private:
    cocos2d::Label* label;
};

class LabelAdditionalKerningTest : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelAdditionalKerningTest);

    LabelAdditionalKerningTest();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void sliderEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
private:
    cocos2d::Label* label;
};

class LabelIssue8492Test : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelIssue8492Test);

    LabelIssue8492Test();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelMultilineWithOutline : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelMultilineWithOutline);

    LabelMultilineWithOutline();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

// we don't support linebreak mode

class LabelIssue9255Test : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelIssue9255Test);

    LabelIssue9255Test();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelSmallDimensionsTest : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelSmallDimensionsTest);

    LabelSmallDimensionsTest();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelIssue10089Test : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelIssue10089Test);

    LabelIssue10089Test();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelSystemFontColor : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelSystemFontColor);

    LabelSystemFontColor();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelIssue10773Test : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelIssue10773Test);

    LabelIssue10773Test();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelIssue11576Test : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelIssue11576Test);

    LabelIssue11576Test();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelIssue11699Test : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelIssue11699Test);

    LabelIssue11699Test();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LabelIssue12409Test : public AtlasDemoNew
{
public:
    CREATE_FUNC(LabelIssue12409Test);

    LabelIssue12409Test();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

#endif
