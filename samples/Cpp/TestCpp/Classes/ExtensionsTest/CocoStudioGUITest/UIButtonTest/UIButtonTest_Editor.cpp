

#include "UIButtonTest_Editor.h"


// UIButtonTest_Editor

UIButtonTest_Editor::UIButtonTest_Editor()
: _displayValueLabel(NULL)
{
    
}

UIButtonTest_Editor::~UIButtonTest_Editor()
{
    
}

bool UIButtonTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosgui/UIEditorTest/UIButton_Editor/UIButton_Editor_1.json"));
        _touchGroup->addWidget(_layout);
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        CCSize rootSize = _layout->getSize();
        _touchGroup->setPosition(CCPoint((screenSize.width - rootSize.width) / 2,
                                         (screenSize.height - rootSize.height) / 2));
        
        Layout* root = static_cast<Layout*>(_touchGroup->getWidgetByName("root_Panel"));

        ui::Label* back_label = static_cast<ui::Label*>(UIHelper::seekWidgetByName(root, "back"));
        back_label->addTouchEventListener(this, toucheventselector(UIScene_Editor::toGUIEditorTestScene));
        
        _sceneTitle = static_cast<ui::Label*>(UIHelper::seekWidgetByName(root, "UItest"));
        
        Button* button = static_cast<Button*>(UIHelper::seekWidgetByName(root, "Button_123"));
        button->addTouchEventListener(this, toucheventselector(UIButtonTest_Editor::touchEvent));
        
        Button* title_button = static_cast<Button*>(UIHelper::seekWidgetByName(root, "Button_126"));
        title_button->addTouchEventListener(this, toucheventselector(UIButtonTest_Editor::touchEvent));
        
        Button* scale9_button = static_cast<Button*>(UIHelper::seekWidgetByName(root, "Button_129"));
        scale9_button->addTouchEventListener(this, toucheventselector(UIButtonTest_Editor::touchEvent));
        
        _displayValueLabel = ui::Label::create();
        _displayValueLabel->setFontName("Marker Felt");
        _displayValueLabel->setFontSize(30);
        _displayValueLabel->setText("No event");
        _displayValueLabel->setPosition(ccp(_layout->getSize().width / 2,
                                            _layout->getSize().height - _displayValueLabel->getSize().height * 1.75f));
        _touchGroup->addWidget(_displayValueLabel);
        
        return true;
    }
    
    return false;
}

void UIButtonTest_Editor::touchEvent(CCObject *pSender, TouchEventType type)
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
