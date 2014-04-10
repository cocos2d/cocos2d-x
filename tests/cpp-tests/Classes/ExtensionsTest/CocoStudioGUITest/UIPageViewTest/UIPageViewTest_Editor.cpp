

#include "UIPageViewTest_Editor.h"


// UIPageViewTest_Editor

UIPageViewTest_Editor::UIPageViewTest_Editor()
: _displayValueLabel(nullptr)
{
    
}

UIPageViewTest_Editor::~UIPageViewTest_Editor()
{
    
}

bool UIPageViewTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UIPageView_Editor/ui_pageview_editor_1.json"));
        _touchGroup->addChild(_layout);
        Size screenSize = CCDirector::getInstance()->getWinSize();
        Size rootSize = _layout->getSize();
        _touchGroup->setPosition(Point((screenSize.width - rootSize.width) / 2,
                                       (screenSize.height - rootSize.height) / 2));
        
        Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
        
        Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
        back_label->addTouchEventListener(this, toucheventselector(UIScene_Editor::toGUIEditorTestScene));
        
        _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
        
        Button* left_button = Button::create();
        left_button->loadTextures("Images/b1.png", "Images/b2.png", "");
        left_button->setPosition(Point(_layout->getSize().width / 2 - left_button->getSize().width,
                                       left_button->getSize().height * 0.625));
        left_button->setTouchEnabled(true);
        left_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::previousCallback));
        left_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
        _layout->addChild(left_button);
        
        Button* right_button = Button::create();
        right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
        right_button->setPosition(Point(_layout->getSize().width / 2 + right_button->getSize().width,
                                        right_button->getSize().height * 0.625));
        right_button->setTouchEnabled(true);
        right_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
        right_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::nextCallback));
        _layout->addChild(right_button);
        
        return true;
    }
    
    return false;
}
