

#include "UIScrollViewTest_Editor.h"
#include "VisibleRect.h"


// UIScrollViewTest_Vertical_Editor

UIScrollViewTest_Vertical_Editor::UIScrollViewTest_Vertical_Editor()
{
    
}

UIScrollViewTest_Vertical_Editor::~UIScrollViewTest_Vertical_Editor()
{
    
}

void UIScrollViewTest_Vertical_Editor::switchLoadMethod(cocos2d::Ref *pSender)
{
    MenuItemToggle *item = (MenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UIScrollView_Editor/UIScrollView_Vertical_Editor/windows_ui_scrollview_editor_1.json"));
            
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UIEditorTest/UIScrollView_Editor/UIScrollView_Vertical_Editor/windows_ui_scrollview_editor_1.csb"));
            
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIScrollView_Editor/UIScrollView_Vertical_Editor/crossplatform_UIScrollView_Vertical_Editor_1.ExportJson");
            Node* child = node->getChildByTag(5);
            child->removeFromParent();
            _layout = static_cast<Layout*>(child);
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 3:
        {
            _layout->removeFromParentAndCleanup(true);
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIScrollView_Editor/UIScrollView_Vertical_Editor/crossplatform_UIScrollView_Vertical_Editor_1.csb");
            Node* child = node->getChildByTag(5);
            child->removeFromParent();
            _layout = static_cast<Layout*>(child);
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        default:
            break;
    }
}

void UIScrollViewTest_Vertical_Editor::configureGUIScene()
{
    Size screenSize = CCDirector::getInstance()->getWinSize();
    Size rootSize = _layout->getContentSize();
    _touchGroup->setPosition(Vec2((screenSize.width - rootSize.width) / 2,
                                  (screenSize.height - rootSize.height) / 2));
    
    Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
    
    Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
    back_label->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::toGUIEditorTestScene, this));
    
    _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
    
    Button* left_button = Button::create();
    left_button->loadTextures("Images/b1.png", "Images/b2.png", "");
    left_button->setPosition(Vec2(_layout->getContentSize().width / 2 - left_button->getContentSize().width,
                                  left_button->getContentSize().height * 0.625));
    left_button->setTouchEnabled(true);
    left_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::previousCallback, this));
    left_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
    _layout->addChild(left_button);
    
    Button* right_button = Button::create();
    right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
    right_button->setPosition(Vec2(_layout->getContentSize().width / 2 + right_button->getContentSize().width,
                                   right_button->getContentSize().height * 0.625));
    right_button->setTouchEnabled(true);
    right_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
    right_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::nextCallback, this));
    _layout->addChild(right_button);
    
}

bool UIScrollViewTest_Vertical_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIScrollView_Editor/UIScrollView_Vertical_Editor/crossplatform_UIScrollView_Vertical_Editor_1.csb");
        Node* child = node->getChildByTag(5);
        child->removeFromParent();
        _layout = static_cast<Layout*>(child);
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
        
        /*
        Menu* menu = static_cast<Menu*>(getChildByTag(1));
        MenuItemToggle* menuItemToggle = static_cast<MenuItemToggle*>(menu->getChildByTag(1));
        MenuItem* selectedItem = menuItemToggle->getSelectedItem();
        menuItemToggle->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y + selectedItem->getContentSize().height * 3.75f));
         */
        
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

void UIScrollViewTest_Horizontal_Editor::switchLoadMethod(cocos2d::Ref *pSender)
{
    MenuItemToggle *item = (MenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UIScrollView_Editor/UIScrollView_Horizontal_Editor/windows_ui_scrollview_horizontal_editor_1.json"));
            
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UIEditorTest/UIScrollView_Editor/UIScrollView_Horizontal_Editor/windows_ui_scrollview_horizontal_editor_1.csb"));
            
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIScrollView_Editor/UIScrollView_Horizontal_Editor/crossplatform_UIScrollView_Horizontal_Editor_1.ExportJson");
            Node* child = node->getChildByTag(5);
            child->removeFromParent();
            _layout = static_cast<Layout*>(child);
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 3:
        {
            _layout->removeFromParentAndCleanup(true);
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIScrollView_Editor/UIScrollView_Horizontal_Editor/crossplatform_UIScrollView_Horizontal_Editor_1.csb");
            Node* child = node->getChildByTag(5);
            child->removeFromParent();
            _layout = static_cast<Layout*>(child);
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        default:
            break;
    }
}

void UIScrollViewTest_Horizontal_Editor::configureGUIScene()
{
    Size screenSize = CCDirector::getInstance()->getWinSize();
    Size rootSize = _layout->getContentSize();
    _touchGroup->setPosition(Vec2((screenSize.width - rootSize.width) / 2,
                                  (screenSize.height - rootSize.height) / 2));
    
    Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
    
    Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
    back_label->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::toGUIEditorTestScene, this));
    
    _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
    
    Button* left_button = Button::create();
    left_button->loadTextures("Images/b1.png", "Images/b2.png", "");
    left_button->setPosition(Vec2(_layout->getContentSize().width / 2 - left_button->getContentSize().width,
                                  left_button->getContentSize().height * 0.625));
    left_button->setTouchEnabled(true);
    left_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::previousCallback, this));
    left_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
    _layout->addChild(left_button);
    
    Button* right_button = Button::create();
    right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
    right_button->setPosition(Vec2(_layout->getContentSize().width / 2 + right_button->getContentSize().width,
                                   right_button->getContentSize().height * 0.625));
    right_button->setTouchEnabled(true);
    right_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
    right_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::nextCallback, this));
    _layout->addChild(right_button);

    
}

bool UIScrollViewTest_Horizontal_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIScrollView_Editor/UIScrollView_Horizontal_Editor/crossplatform_UIScrollView_Horizontal_Editor_1.csb");
        Node* child = node->getChildByTag(5);
        child->removeFromParent();
        _layout = static_cast<Layout*>(child);
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
        
        /*
        Menu* menu = static_cast<Menu*>(getChildByTag(1));
        MenuItemToggle* menuItemToggle = static_cast<MenuItemToggle*>(menu->getChildByTag(1));
        MenuItem* selectedItem = menuItemToggle->getSelectedItem();
        menuItemToggle->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y + selectedItem->getContentSize().height * 3.75f));
         */
        
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

void UIScrollViewTest_Both_Editor::switchLoadMethod(cocos2d::Ref *pSender)
{
    MenuItemToggle *item = (MenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UIScrollView_Editor/UIScrollView_Both_Editor/windows_ui_scrollview_both_editor_1.json"));
            
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UIEditorTest/UIScrollView_Editor/UIScrollView_Both_Editor/windows_ui_scrollview_both_editor_1.csb"));
            
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIScrollView_Editor/UIScrollView_Both_Editor/crossplatform_UIScrollView_Both_Editor_1.ExportJson");
            Node* child = node->getChildByTag(5);
            child->removeFromParent();
            _layout = static_cast<Layout*>(child);
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 3:
        {
            _layout->removeFromParentAndCleanup(true);
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIScrollView_Editor/UIScrollView_Both_Editor/crossplatform_UIScrollView_Both_Editor_1.csb");
            Node* child = node->getChildByTag(5);
            child->removeFromParent();
            _layout = static_cast<Layout*>(child);
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        default:
            break;
    }
}

void UIScrollViewTest_Both_Editor::configureGUIScene()
{
    Size screenSize = CCDirector::getInstance()->getWinSize();
    Size rootSize = _layout->getContentSize();
    _touchGroup->setPosition(Vec2((screenSize.width - rootSize.width) / 2,
                                  (screenSize.height - rootSize.height) / 2));
    
    Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
    
    Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
    back_label->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::toGUIEditorTestScene, this));
    
    _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
    
    Button* left_button = Button::create();
    left_button->loadTextures("Images/b1.png", "Images/b2.png", "");
    left_button->setPosition(Vec2(_layout->getContentSize().width / 2 - left_button->getContentSize().width,
                                  left_button->getContentSize().height * 0.625));
    left_button->setTouchEnabled(true);
    left_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::previousCallback, this));
    left_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
    _layout->addChild(left_button);
    
    Button* right_button = Button::create();
    right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
    right_button->setPosition(Vec2(_layout->getContentSize().width / 2 + right_button->getContentSize().width,
                                   right_button->getContentSize().height * 0.625));
    right_button->setTouchEnabled(true);
    right_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
    right_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::nextCallback, this));
    _layout->addChild(right_button);
}

bool UIScrollViewTest_Both_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIScrollView_Editor/UIScrollView_Both_Editor/crossplatform_UIScrollView_Both_Editor_1.csb");
        Node* child = node->getChildByTag(5);
        child->removeFromParent();
        _layout = static_cast<Layout*>(child);
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
        
        /*
        Menu* menu = static_cast<Menu*>(getChildByTag(1));
        MenuItemToggle* menuItemToggle = static_cast<MenuItemToggle*>(menu->getChildByTag(1));
        MenuItem* selectedItem = menuItemToggle->getSelectedItem();
        menuItemToggle->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y + selectedItem->getContentSize().height * 3.75f));
         */
        
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
//        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UITest/UITest.json"));
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UITest/UITest.csb"));
        _touchGroup->addChild(_layout);
        Size screenSize = CCDirector::getInstance()->getWinSize();
        Size rootSize = _layout->getContentSize();
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
//        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UITest/UITest.json"));
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UITest/UITest.csb"));
        _touchGroup->addChild(_layout);
        Size screenSize = CCDirector::getInstance()->getWinSize();
        Size rootSize = _layout->getContentSize();
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
