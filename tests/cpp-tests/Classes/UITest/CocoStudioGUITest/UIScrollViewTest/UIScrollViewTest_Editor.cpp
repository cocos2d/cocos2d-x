

#include "UIScrollViewTest_Editor.h"


// UIScrollViewTest_Vertical_Editor

UIScrollViewTest_Vertical_Editor::UIScrollViewTest_Vertical_Editor()
{
    
}

UIScrollViewTest_Vertical_Editor::~UIScrollViewTest_Vertical_Editor()
{
    
}

bool UIScrollViewTest_Vertical_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UIScrollView_Editor/UIScrollView_Vertical_Editor/ui_scrollview_editor_1.json"));
        _touchGroup->addChild(_layout);
        Size screenSize = CCDirector::getInstance()->getWinSize();
        Size rootSize = _layout->getSize();
        _touchGroup->setPosition(Vec2((screenSize.width - rootSize.width) / 2,
                                       (screenSize.height - rootSize.height) / 2));
        
        Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
        
        Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
        back_label->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::toGUIEditorTestScene, this));
        
        _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
        
        Button* left_button = Button::create();
        left_button->loadTextures("Images/b1.png", "Images/b2.png", "");
        left_button->setPosition(Vec2(_layout->getSize().width / 2 - left_button->getSize().width,
                                     left_button->getSize().height * 0.625));
        left_button->setTouchEnabled(true);
        left_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::previousCallback, this));
        left_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
        _layout->addChild(left_button);
        
        Button* right_button = Button::create();
        right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
        right_button->setPosition(Vec2(_layout->getSize().width / 2 + right_button->getSize().width,
                                      right_button->getSize().height * 0.625));
        right_button->setTouchEnabled(true);
        right_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
        right_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::nextCallback, this));
        _layout->addChild(right_button);
        
        return true;
    }
    
    return false;
}


// UIScrollViewTest_Horizontal_Editor

UIScrollViewTest_Horizontal_Editor::UIScrollViewTest_Horizontal_Editor()
{
    
}

UIScrollViewTest_Horizontal_Editor::~UIScrollViewTest_Horizontal_Editor()
{
    
}

bool UIScrollViewTest_Horizontal_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UIScrollView_Editor/UIScrollView_Horizontal_Editor/ui_scrollview_horizontal_editor_1.json"));
        _touchGroup->addChild(_layout);
        Size screenSize = CCDirector::getInstance()->getWinSize();
        Size rootSize = _layout->getSize();
        _touchGroup->setPosition(Vec2((screenSize.width - rootSize.width) / 2,
                                        (screenSize.height - rootSize.height) / 2));
        
        Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
        
        Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
        back_label->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::toGUIEditorTestScene, this));
        
        _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
        
        Button* left_button = Button::create();
        left_button->loadTextures("Images/b1.png", "Images/b2.png", "");
        left_button->setPosition(Vec2(_layout->getSize().width / 2 - left_button->getSize().width,
                                     left_button->getSize().height * 0.625));
        left_button->setTouchEnabled(true);
        left_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::previousCallback, this));
		left_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
        _layout->addChild(left_button);
        
        Button* right_button = Button::create();
        right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
        right_button->setPosition(Vec2(_layout->getSize().width / 2 + right_button->getSize().width,
                                      right_button->getSize().height * 0.625));
        right_button->setTouchEnabled(true);
        right_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
        right_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::nextCallback, this));
        _layout->addChild(right_button);
        
        return true;
    }
    
    return false;
}


// UIScrollViewTest_Both_Editor

UIScrollViewTest_Both_Editor::UIScrollViewTest_Both_Editor()
{
    
}

UIScrollViewTest_Both_Editor::~UIScrollViewTest_Both_Editor()
{
    
}

bool UIScrollViewTest_Both_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UIScrollView_Editor/UIScrollView_Both_Editor/ui_scrollview_both_editor_1.json"));
        _touchGroup->addChild(_layout);
        Size screenSize = CCDirector::getInstance()->getWinSize();
        Size rootSize = _layout->getSize();
        _touchGroup->setPosition(Vec2((screenSize.width - rootSize.width) / 2,
                                        (screenSize.height - rootSize.height) / 2));
        
        Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
        
        Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
        back_label->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::toGUIEditorTestScene, this));
        
        _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
        
        Button* left_button = Button::create();
        left_button->loadTextures("Images/b1.png", "Images/b2.png", "");
        left_button->setPosition(Vec2(_layout->getSize().width / 2 - left_button->getSize().width,
                                     left_button->getSize().height * 0.625));
        left_button->setTouchEnabled(true);
        left_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::previousCallback, this));
        left_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
        _layout->addChild(left_button);
        
        Button* right_button = Button::create();
        right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
        right_button->setPosition(Vec2(_layout->getSize().width / 2 + right_button->getSize().width,
                                      right_button->getSize().height * 0.625));
        right_button->setTouchEnabled(true);
        right_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
        right_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::nextCallback, this));
        _layout->addChild(right_button);
        
        return true;
    }
    
    return false;
}


// UIScrollViewTest_ScrollToPercentBothDirection_Editor

UIScrollViewTest_ScrollToPercentBothDirection_Editor::UIScrollViewTest_ScrollToPercentBothDirection_Editor()
{
    
}

UIScrollViewTest_ScrollToPercentBothDirection_Editor::~UIScrollViewTest_ScrollToPercentBothDirection_Editor()
{
    
}

bool UIScrollViewTest_ScrollToPercentBothDirection_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UITest/UITest.json"));
        _touchGroup->addChild(_layout);
        Size screenSize = CCDirector::getInstance()->getWinSize();
        Size rootSize = _layout->getSize();
        _touchGroup->setPosition(Vec2((screenSize.width - rootSize.width) / 2,
                                        (screenSize.height - rootSize.height) / 2));
        
        Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
        
        Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
        back_label->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::toGUIEditorTestScene, this));
        
        _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
        
        Button* left_button = static_cast<Button*>(Helper::seekWidgetByName(root, "left_Button"));
        left_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::previousCallback, this));
        
        Button* middle_button = static_cast<Button*>(Helper::seekWidgetByName(root, "middle_Button"));
        middle_button->setVisible(false);
        
        Button* right_button = static_cast<Button*>(Helper::seekWidgetByName(root, "right_Button"));
        right_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::nextCallback, this));
        
        return true;
    }
    
    return false;
}


// UIScrollViewTest_ScrollToPercentBothDirection_Bounce_Editor

UIScrollViewTest_ScrollToPercentBothDirection_Bounce_Editor::UIScrollViewTest_ScrollToPercentBothDirection_Bounce_Editor()
{
    
}

UIScrollViewTest_ScrollToPercentBothDirection_Bounce_Editor::~UIScrollViewTest_ScrollToPercentBothDirection_Bounce_Editor()
{
    
}

bool UIScrollViewTest_ScrollToPercentBothDirection_Bounce_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UITest/UITest.json"));
        _touchGroup->addChild(_layout);
        Size screenSize = CCDirector::getInstance()->getWinSize();
        Size rootSize = _layout->getSize();
        _touchGroup->setPosition(Vec2((screenSize.width - rootSize.width) / 2,
                                        (screenSize.height - rootSize.height) / 2));
        
        Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
        
        Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
        back_label->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::toGUIEditorTestScene, this));
        
        _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
        
        Button* left_button = static_cast<Button*>(Helper::seekWidgetByName(root, "left_Button"));
        left_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::previousCallback, this));
        
        Button* middle_button = static_cast<Button*>(Helper::seekWidgetByName(root, "middle_Button"));
        middle_button->setVisible(false);
        
        Button* right_button = static_cast<Button*>(Helper::seekWidgetByName(root, "right_Button"));
        right_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::nextCallback, this));
        
        return true;
    }
    
    return false;
}
