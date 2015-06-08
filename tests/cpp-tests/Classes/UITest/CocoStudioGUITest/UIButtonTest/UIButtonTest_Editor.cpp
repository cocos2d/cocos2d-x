#include "UIButtonTest_Editor.h"

USING_NS_CC;
using namespace cocos2d::ui;

// UIButtonTest_Editor

UIButtonEditorTests::UIButtonEditorTests()
{
    ADD_TEST_CASE(UIButtonTest_Editor);
}

UIButtonTest_Editor::UIButtonTest_Editor()
: _displayValueLabel(nullptr)
{
    
}

UIButtonTest_Editor::~UIButtonTest_Editor()
{
    
}

void UIButtonTest_Editor::configureGUIScene()
{
    UIScene_Editor::configureGUIScene();
    
    Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
    
    Button* button = static_cast<Button*>(Helper::seekWidgetByName(root, "Button_123"));
    button->addTouchEventListener(CC_CALLBACK_2(UIButtonTest_Editor::touchEvent, this));
    
    Button* title_button = static_cast<Button*>(Helper::seekWidgetByName(root, "Button_126"));
    title_button->addTouchEventListener(CC_CALLBACK_2(UIButtonTest_Editor::touchEvent, this));
    
    Button* scale9_button = static_cast<Button*>(Helper::seekWidgetByName(root, "Button_129"));
    scale9_button->addTouchEventListener(CC_CALLBACK_2(UIButtonTest_Editor::touchEvent,this));
}

bool UIButtonTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIButton/res.csb");
        Node* child = node->getChildByTag(4);
        child->removeFromParent();
        _layout = static_cast<Layout*>(child);
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
        
        
        _displayValueLabel = ui::Text::create();
        _displayValueLabel->setFontName("Marker Felt");
        _displayValueLabel->setFontSize(30);
        _displayValueLabel->setString("No event");
        _displayValueLabel->setPosition(Vec2(_layout->getContentSize().width / 2,
                                            _layout->getContentSize().height - _displayValueLabel->getContentSize().height * 1.75f));
        
        _touchGroup->addChild(_displayValueLabel,20);
        
        return true;
    }
    
    return false;
}

void UIButtonTest_Editor::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            _displayValueLabel->setString("Touch Down");
            break;
            
        case Widget::TouchEventType::MOVED:
            _displayValueLabel->setString("Touch Moved");
            break;
            
        case Widget::TouchEventType::ENDED:
            _displayValueLabel->setString("Touch Ended");
            break;
            
        case Widget::TouchEventType::CANCELED:
            _displayValueLabel->setString("Touch Canceled");
            break;
            
        default:
            break;
    }
}
