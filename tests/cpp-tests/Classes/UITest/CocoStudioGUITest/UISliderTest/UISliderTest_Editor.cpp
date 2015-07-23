#include "UISliderTest_Editor.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

UISliderEditorTests::UISliderEditorTests()
{
    ADD_TEST_CASE(UISliderTest_Editor);
}
// UISliderTest_Editor

UISliderTest_Editor::UISliderTest_Editor()
: _displayValueLabel(nullptr)
{
    
}

UISliderTest_Editor::~UISliderTest_Editor()
{
    
}

void UISliderTest_Editor::configureGUIScene()
{
    UIScene_Editor::configureGUIScene();
    
    Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));

    Slider* slider = static_cast<Slider*>(Helper::seekWidgetByName(root, "Slider_738"));
    slider->addEventListener(CC_CALLBACK_2(UISliderTest_Editor::sliderEvent, this));
}

bool UISliderTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UISlider/res.csb");
        Node* child = node->getChildByTag(5);
        child->removeFromParent();
        _layout = static_cast<Layout*>(child);
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
        
        _displayValueLabel = Text::create();
        _displayValueLabel->setFontName("fonts/Marker Felt.ttf");
        _displayValueLabel->setFontSize(30);
        _displayValueLabel->setString("No event");
        _displayValueLabel->setPosition(Vec2(_layout->getContentSize().width / 2,
                                              _layout->getContentSize().height - _displayValueLabel->getContentSize().height * 1.75f));
        _touchGroup->addChild(_displayValueLabel, 20);
        
        return true;
    }
    
    return false;
}

void UISliderTest_Editor::sliderEvent(Ref *pSender, Slider::EventType type)
{
    switch (type)
    {
        case Slider::EventType::ON_PERCENTAGE_CHANGED:
        {
            Slider* slider = static_cast<Slider*>(pSender);
            _displayValueLabel->setString(StringUtils::format("percent %d", slider->getPercent()));
        }
            break;
            
        default:
            break;
    }
}
