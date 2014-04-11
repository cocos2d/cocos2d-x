

#include "UIButtonTest_Editor.h"


// UIButtonTest_Editor

UIButtonTest_Editor::UIButtonTest_Editor()
: _displayValueLabel(nullptr)
{
    
}

UIButtonTest_Editor::~UIButtonTest_Editor()
{
    
}

bool UIButtonTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UIButton_Editor/UIButton_Editor_1.json"));
        _touchGroup->addChild(_layout);
        Size screenSize = CCDirector::getInstance()->getWinSize();
        Size rootSize = _layout->getSize();
        _touchGroup->setPosition(Point((screenSize.width - rootSize.width) / 2,
                                       (screenSize.height - rootSize.height) / 2));
        
        Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));

        Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
        back_label->addTouchEventListener(this, toucheventselector(UIScene_Editor::toGUIEditorTestScene));
        
        _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
        
        Button* button = static_cast<Button*>(Helper::seekWidgetByName(root, "Button_123"));
        button->addTouchEventListener(this, toucheventselector(UIButtonTest_Editor::touchEvent));
        
        Button* title_button = static_cast<Button*>(Helper::seekWidgetByName(root, "Button_126"));
        title_button->addTouchEventListener(this, toucheventselector(UIButtonTest_Editor::touchEvent));
        
        Button* scale9_button = static_cast<Button*>(Helper::seekWidgetByName(root, "Button_129"));
        scale9_button->addTouchEventListener(this, toucheventselector(UIButtonTest_Editor::touchEvent));
        
        _displayValueLabel = Text::create();
        _displayValueLabel->setFontName("fonts/Marker Felt.ttf");
        _displayValueLabel->setFontSize(30);
        _displayValueLabel->setText("No event");
        _displayValueLabel->setPosition(Point(_layout->getSize().width / 2,
                                              _layout->getSize().height - _displayValueLabel->getSize().height * 1.75f));
        _touchGroup->addChild(_displayValueLabel);
        
        return true;
    }
    
    return false;
}

void UIButtonTest_Editor::touchEvent(Ref *pSender, TouchEventType type)
{
    switch (type)
    {
        case TOUCH_EVENT_BEGAN:
            _displayValueLabel->setText("Touch Down");
            break;
            
        case TOUCH_EVENT_MOVED:
            _displayValueLabel->setText("Touch Moved");
            break;
            
        case TOUCH_EVENT_ENDED:
            _displayValueLabel->setText("Touch Ended");
            break;
            
        case TOUCH_EVENT_CANCELED:
            _displayValueLabel->setText("Touch Canceled");
            break;
            
        default:
            break;
    }
}
