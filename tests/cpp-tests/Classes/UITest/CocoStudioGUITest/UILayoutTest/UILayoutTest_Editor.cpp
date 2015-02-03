

#include "UILayoutTest_Editor.h"
#include "VisibleRect.h"


// UILayoutTest_Editor

UILayoutTest_Editor::UILayoutTest_Editor()
{
    
}

UILayoutTest_Editor::~UILayoutTest_Editor()
{
    
}

void UILayoutTest_Editor::switchLoadMethod(cocos2d::Ref *pSender)
{
    MenuItemToggle *item = (MenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout/Layout/windows_ui_layout_editor_1.json"));
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UIEditorTest/UILayout/Layout/windows_ui_layout_editor_1.csb"));
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/Layout/crossplatform_UILayout_Editor_1.ExportJson");
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
         
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/Layout/crossplatform_UILayout_Editor_1.csb");
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

void UILayoutTest_Editor::configureGUIScene()
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
                                  left_button->getContentSize().height));
    left_button->setTouchEnabled(true);
    left_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::previousCallback, this));
    left_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
    _layout->addChild(left_button);
    
    Button* right_button = Button::create();
    right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
    right_button->setPosition(Vec2(_layout->getContentSize().width / 2 + right_button->getContentSize().width,
                                   right_button->getContentSize().height));
    right_button->setTouchEnabled(true);
    right_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
    right_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::nextCallback, this));
    _layout->addChild(right_button);

    
}

bool UILayoutTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/Layout/crossplatform_UILayout_Editor_1.csb");
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


// UILayoutTest_Color_Editor

UILayoutTest_Color_Editor::UILayoutTest_Color_Editor()
{
    
}

UILayoutTest_Color_Editor::~UILayoutTest_Color_Editor()
{
    
}

void UILayoutTest_Color_Editor::switchLoadMethod(cocos2d::Ref *pSender)
{
    MenuItemToggle *item = (MenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout/Color/windows_ui_color.json"));
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UIEditorTest/UILayout/Color/windows_ui_color.csb"));
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/Color/crossplatform_Colo.ExportJson");
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
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/Color/crossplatform_UILayout_Color_Editor_1.csb");
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

void UILayoutTest_Color_Editor::configureGUIScene()
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
                                  left_button->getContentSize().height));
    left_button->setTouchEnabled(true);
    left_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::previousCallback, this));
    left_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
    _layout->addChild(left_button);
    
    Button* right_button = Button::create();
    right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
    right_button->setPosition(Vec2(_layout->getContentSize().width / 2 + right_button->getContentSize().width,
                                   right_button->getContentSize().height));
    right_button->setTouchEnabled(true);
    right_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
    right_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::nextCallback, this));
    _layout->addChild(right_button);
}

bool UILayoutTest_Color_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/Color/crossplatform_UILayout_Color_Editor_1.csb");
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


// UILayoutTest_Gradient_Editor

UILayoutTest_Gradient_Editor::UILayoutTest_Gradient_Editor()
{
    
}

UILayoutTest_Gradient_Editor::~UILayoutTest_Gradient_Editor()
{
    
}

void UILayoutTest_Gradient_Editor::switchLoadMethod(cocos2d::Ref *pSender)
{
    MenuItemToggle *item = (MenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout/Gradient_Color/windows_ui_gradient_color.json"));
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UIEditorTest/UILayout/Gradient_Color/windows_ui_gradient_color.csb"));
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/Gradient_Color/crossplatform_Gradient_Color.ExportJson");
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
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/Gradient_Color/crossplatform_Gradient_Color.csb");
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

void UILayoutTest_Gradient_Editor::configureGUIScene()
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
                                  left_button->getContentSize().height));
    left_button->setTouchEnabled(true);
    left_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::previousCallback, this));
    left_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
    _layout->addChild(left_button);
    
    Button* right_button = Button::create();
    right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
    right_button->setPosition(Vec2(_layout->getContentSize().width / 2 + right_button->getContentSize().width,
                                   right_button->getContentSize().height));
    right_button->setTouchEnabled(true);
    right_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
    right_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::nextCallback, this));
    _layout->addChild(right_button);

}

bool UILayoutTest_Gradient_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/Gradient_Color/crossplatform_Gradient_Color.csb");
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


// UILayoutTest_BackGroundImage_Editor

UILayoutTest_BackGroundImage_Editor::UILayoutTest_BackGroundImage_Editor()
{
    
}

UILayoutTest_BackGroundImage_Editor::~UILayoutTest_BackGroundImage_Editor()
{
    
}

void UILayoutTest_BackGroundImage_Editor::switchLoadMethod(cocos2d::Ref *pSender)
{
    MenuItemToggle *item = (MenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout/BackgroundImage/windows_ui_backgroundimage.json"));
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UIEditorTest/UILayout/BackgroundImage/windows_ui_backgroundimage.csb"));
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/BackgroundImage/crossplatform_BackgroundImage.ExportJson");
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
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/BackgroundImage/crossplatform_BackgroundImage.csb");
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

void UILayoutTest_BackGroundImage_Editor::configureGUIScene()
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

bool UILayoutTest_BackGroundImage_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/BackgroundImage/crossplatform_BackgroundImage.csb");
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


// UILayoutTest_BackGroundImage_Scale9_Editor

UILayoutTest_BackGroundImage_Scale9_Editor::UILayoutTest_BackGroundImage_Scale9_Editor()
{
    
}

UILayoutTest_BackGroundImage_Scale9_Editor::~UILayoutTest_BackGroundImage_Scale9_Editor()
{
    
}

void UILayoutTest_BackGroundImage_Scale9_Editor::switchLoadMethod(cocos2d::Ref *pSender)
{
    MenuItemToggle *item = (MenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout/Scale9_BackgroundImage/windows_ui_scale9_backgroundimage.json"));
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UIEditorTest/UILayout/Scale9_BackgroundImage/windows_ui_scale9_backgroundimage.csb"));
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/Scale9_BackgroundImage/crossplatform_Scale9_BackgroundImage.ExportJson");
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
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/Scale9_BackgroundImage/crossplatform_Scale9_BackgroundImage.csb");
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

void UILayoutTest_BackGroundImage_Scale9_Editor::configureGUIScene()
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
                                  left_button->getContentSize().height));
    left_button->setTouchEnabled(true);
    left_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::previousCallback, this));
    left_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
    _layout->addChild(left_button);
    
    Button* right_button = Button::create();
    right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
    right_button->setPosition(Vec2(_layout->getContentSize().width / 2 + right_button->getContentSize().width,
                                   right_button->getContentSize().height));
    right_button->setTouchEnabled(true);
    right_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
    right_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::nextCallback, this));
    _layout->addChild(right_button);
    
}

bool UILayoutTest_BackGroundImage_Scale9_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/Scale9_BackgroundImage/crossplatform_Scale9_BackgroundImage.csb");
        Node* child = node->getChildByTag(5);
        child->removeFromParent();
        _layout = static_cast<Layout*>(child);
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
        
        /*
        Menu* menu = static_cast<Menu*>(getChildByTag(1));
        MenuItemToggle* menuItemToggle = static_cast<MenuItemToggle*>(menu->getChildByTag(1));
        MenuItem* selectedItem = menuItemToggle->getSelectedItem();
        menuItemToggle->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y + selectedItem->getContentSize().height * 4.25f));
         */
        
        return true;
    }
    
    return false;
}


// UILayoutTest_Layout_Linear_Vertical_Editor

UILayoutTest_Layout_Linear_Vertical_Editor::UILayoutTest_Layout_Linear_Vertical_Editor()
{
    
}

UILayoutTest_Layout_Linear_Vertical_Editor::~UILayoutTest_Layout_Linear_Vertical_Editor()
{
    
}

void UILayoutTest_Layout_Linear_Vertical_Editor::switchLoadMethod(cocos2d::Ref *pSender)
{
    MenuItemToggle *item = (MenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout/Linear_Vertical_Layout/windows_ui_linear_vertical_layout.json"));
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UIEditorTest/UILayout/Linear_Vertical_Layout/windows_ui_linear_vertical_layout.csb"));
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
         
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/Linear_Vertical_Layout/crossplatform_Linear_Vertical_Layout.ExportJson");
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
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/Linear_Vertical_Layout/crossplatform_Linear_Vertical_Layout.csb");
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

void UILayoutTest_Layout_Linear_Vertical_Editor::configureGUIScene()
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

bool UILayoutTest_Layout_Linear_Vertical_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout/Linear_Vertical_Layout/windows_ui_linear_vertical_layout.json"));

        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
        
        Menu* menu = static_cast<Menu*>(getChildByTag(1));
        MenuItemToggle* menuItemToggle = static_cast<MenuItemToggle*>(menu->getChildByTag(1));
        MenuItem* selectedItem = menuItemToggle->getSelectedItem();
        menuItemToggle->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y + selectedItem->getContentSize().height * 4.25f));
        
        return true;
    }
    
    return false;
}


// UILayoutTest_Layout_Linear_Horizontal_Editor

UILayoutTest_Layout_Linear_Horizontal_Editor::UILayoutTest_Layout_Linear_Horizontal_Editor()
{
    
}

UILayoutTest_Layout_Linear_Horizontal_Editor::~UILayoutTest_Layout_Linear_Horizontal_Editor()
{
    
}

void UILayoutTest_Layout_Linear_Horizontal_Editor::switchLoadMethod(cocos2d::Ref *pSender)
{
    MenuItemToggle *item = (MenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout/Linear_Horizontal_Layout/windows_ui_linear_horizontal_layout.json"));
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UIEditorTest/UILayout/Linear_Horizontal_Layout/windows_ui_linear_horizontal_layout.csb"));
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/Linear_Horizontal_Layout/crossplatform_Linear_Horizontal_Layout.ExportJson");
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
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/Linear_Horizontal_Layout/crossplatform_Linear_Horizontal_Layout.csb");
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

void UILayoutTest_Layout_Linear_Horizontal_Editor::configureGUIScene()
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

bool UILayoutTest_Layout_Linear_Horizontal_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout/Linear_Horizontal_Layout/windows_ui_linear_horizontal_layout.json"));
        _touchGroup->addChild(_layout);
      
        this->configureGUIScene();
        
        Menu* menu = static_cast<Menu*>(getChildByTag(1));
        MenuItemToggle* menuItemToggle = static_cast<MenuItemToggle*>(menu->getChildByTag(1));
        MenuItem* selectedItem = menuItemToggle->getSelectedItem();
        menuItemToggle->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y + selectedItem->getContentSize().height * 4.25f));
        
        return true;
    }
    
    return false;
}


// UILayoutTest_Layout_Relative_Align_Parent_Editor

UILayoutTest_Layout_Relative_Align_Parent_Editor::UILayoutTest_Layout_Relative_Align_Parent_Editor()
{
    
}

UILayoutTest_Layout_Relative_Align_Parent_Editor::~UILayoutTest_Layout_Relative_Align_Parent_Editor()
{
    
}

void UILayoutTest_Layout_Relative_Align_Parent_Editor::switchLoadMethod(cocos2d::Ref *pSender)
{
    MenuItemToggle *item = (MenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout/Relative_Align_Parent/windows_ui_relative_align_parent.json"));
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UIEditorTest/UILayout/Relative_Align_Parent/windows_ui_relative_align_parent.csb"));
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/Relative_Align_Parent/crossplatform_Relative_Align_Parent.ExportJson");
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
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/Relative_Align_Parent/crossplatform_Relative_Align_Parent.csb");
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

void UILayoutTest_Layout_Relative_Align_Parent_Editor::configureGUIScene()
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

bool UILayoutTest_Layout_Relative_Align_Parent_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout/Relative_Align_Parent/windows_ui_relative_align_parent.json"));
        _touchGroup->addChild(_layout);
        this->configureGUIScene();
        
        Menu* menu = static_cast<Menu*>(getChildByTag(1));
        MenuItemToggle* menuItemToggle = static_cast<MenuItemToggle*>(menu->getChildByTag(1));
        MenuItem* selectedItem = menuItemToggle->getSelectedItem();
        menuItemToggle->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y + selectedItem->getContentSize().height * 4.25f));
        
        return true;
    }
    
    return false;
}


// UILayoutTest_Layout_Relative_Location_Editor

UILayoutTest_Layout_Relative_Location_Editor::UILayoutTest_Layout_Relative_Location_Editor()
{
    
}

UILayoutTest_Layout_Relative_Location_Editor::~UILayoutTest_Layout_Relative_Location_Editor()
{
    
}

void UILayoutTest_Layout_Relative_Location_Editor::switchLoadMethod(cocos2d::Ref *pSender)
{
    MenuItemToggle *item = (MenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout/Relative_Align_Location/windows_ui_relative_align_location.json"));
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UIEditorTest/UILayout/Relative_Align_Location/windows_ui_relative_align_location.csb"));
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/Relative_Align_Location/crossplatform_Relative_Align_Location.ExportJson");
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
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/Relative_Align_Location/crossplatform_Relative_Align_Location.csb");
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

void UILayoutTest_Layout_Relative_Location_Editor::configureGUIScene()
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

bool UILayoutTest_Layout_Relative_Location_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout/Relative_Align_Location/windows_ui_relative_align_location.json"));
        _touchGroup->addChild(_layout);
        this->configureGUIScene();
        
        Menu* menu = static_cast<Menu*>(getChildByTag(1));
        MenuItemToggle* menuItemToggle = static_cast<MenuItemToggle*>(menu->getChildByTag(1));
        MenuItem* selectedItem = menuItemToggle->getSelectedItem();
        menuItemToggle->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y + selectedItem->getContentSize().height * 4.25f));
        
        return true;
    }
    
    return false;
}

UILayoutComponentTest_Editor::UILayoutComponentTest_Editor()
{

}

UILayoutComponentTest_Editor::~UILayoutComponentTest_Editor()
{

}

void UILayoutComponentTest_Editor::configureGUIScene()
{
    Size screenSize = Director::getInstance()->getWinSize();
    Size rootSize = _layout->getContentSize();
    _touchGroup->setPosition(Vec2((screenSize.width - rootSize.width) / 2,
        (screenSize.height - rootSize.height) / 2));

    _root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));

    ui::Text* back_label = static_cast<ui::Text*>(Helper::seekWidgetByName(_root, "back"));
    back_label->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::toGUIEditorTestScene, this));

    _sceneTitle = static_cast<ui::Text*>(Helper::seekWidgetByName(_root, "UItest"));

    Button* left_button = Button::create();
    left_button->loadTextures("Images/b1.png", "Images/b2.png", "");
    left_button->setPosition(Vec2(_layout->getContentSize().width / 2 - left_button->getContentSize().width,
        left_button->getContentSize().height));
    left_button->setTouchEnabled(true);
    left_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::previousCallback, this));
    left_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
    _layout->addChild(left_button);

    Button* right_button = Button::create();
    right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
    right_button->setPosition(Vec2(_layout->getContentSize().width / 2 + right_button->getContentSize().width,
        right_button->getContentSize().height));
    right_button->setTouchEnabled(true);
    right_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
    right_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::nextCallback, this));
    _layout->addChild(right_button);

    _hUnchecked = static_cast<ui::Button*>(Helper::seekWidgetByName(_root, "Button_h_unchecked"));
    _vUnchecked = static_cast<ui::Button*>(Helper::seekWidgetByName(_root, "Button_v_unchecked"));
    _hChecked = static_cast<ui::Button*>(Helper::seekWidgetByName(_root, "Button_h_checked"));
    _vChecked = static_cast<ui::Button*>(Helper::seekWidgetByName(_root, "Button_v_checked"));
    _lPinUnchecked = static_cast<ui::Button*>(Helper::seekWidgetByName(_root, "Button_Pin_Left"));
    _rPinUnchecked = static_cast<ui::Button*>(Helper::seekWidgetByName(_root, "Button_Pin_Right"));
    _tPinUnchecked = static_cast<ui::Button*>(Helper::seekWidgetByName(_root, "Button_Pin_Top"));
    _bPinUnchecked = static_cast<ui::Button*>(Helper::seekWidgetByName(_root, "Button_Pin_Bottom"));
    _lPinChecked = static_cast<ui::Button*>(Helper::seekWidgetByName(_root, "Button_Pin_Left_Checked"));
    _rPinChecked = static_cast<ui::Button*>(Helper::seekWidgetByName(_root, "Button_Pin_Right_Checked"));
    _tPinChecked = static_cast<ui::Button*>(Helper::seekWidgetByName(_root, "Button_Pin_Top_Checked"));
    _bPinChecked = static_cast<ui::Button*>(Helper::seekWidgetByName(_root, "Button_Pin_Bottom_Checked"));

    _hUnchecked->addClickEventListener(CC_CALLBACK_1(UILayoutComponentTest_Editor::onChangeLayoutComponent, this));
    _vUnchecked->addClickEventListener(CC_CALLBACK_1(UILayoutComponentTest_Editor::onChangeLayoutComponent, this));
    _hChecked->addClickEventListener(CC_CALLBACK_1(UILayoutComponentTest_Editor::onChangeLayoutComponent, this));
    _vChecked->addClickEventListener(CC_CALLBACK_1(UILayoutComponentTest_Editor::onChangeLayoutComponent, this));
    _lPinUnchecked->addClickEventListener(CC_CALLBACK_1(UILayoutComponentTest_Editor::onChangeLayoutComponent, this));
    _rPinUnchecked->addClickEventListener(CC_CALLBACK_1(UILayoutComponentTest_Editor::onChangeLayoutComponent, this));
    _tPinUnchecked->addClickEventListener(CC_CALLBACK_1(UILayoutComponentTest_Editor::onChangeLayoutComponent, this));
    _bPinUnchecked->addClickEventListener(CC_CALLBACK_1(UILayoutComponentTest_Editor::onChangeLayoutComponent, this));
    _lPinChecked->addClickEventListener(CC_CALLBACK_1(UILayoutComponentTest_Editor::onChangeLayoutComponent, this));
    _rPinChecked->addClickEventListener(CC_CALLBACK_1(UILayoutComponentTest_Editor::onChangeLayoutComponent, this));
    _tPinChecked->addClickEventListener(CC_CALLBACK_1(UILayoutComponentTest_Editor::onChangeLayoutComponent, this));
    _bPinChecked->addClickEventListener(CC_CALLBACK_1(UILayoutComponentTest_Editor::onChangeLayoutComponent, this));

    _textPin = static_cast<ui::Text*>(Helper::seekWidgetByName(_root, "Text_Pin"));
    _textStretch = static_cast<ui::Text*>(Helper::seekWidgetByName(_root, "Text_Stretch"));
    _widget = Helper::seekWidgetByName(_root, "Image_Widget");
    _container = Helper::seekWidgetByName(_root, "background_Panel");

    auto btnSwitch = static_cast<ui::Button*>(Helper::seekWidgetByName(_root, "Button_Switch"));
    btnSwitch->addClickEventListener(CC_CALLBACK_1(UILayoutComponentTest_Editor::onResizeContainer, this));
}

bool UILayoutComponentTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/LayoutComponent/UILayoutComponent.csb");
        Node* child = node->getChildByTag(5);
        child->removeFromParent();
        _layout = static_cast<Layout*>(child);
        _touchGroup->addChild(_layout);
        this->configureGUIScene();

        return true;
    }

    return false;
}

void UILayoutComponentTest_Editor::onChangeLayoutComponent(Ref* sender)
{
    std::string statusStretch = _textStretch->getString();
    std::string statusPin = _textPin->getString();
    std::string hPinStatus = " Left";
    std::string vPinStatus = " Bottom";

    if (sender == _hUnchecked)
    {
        _hUnchecked->setVisible(false);
        _hChecked->setVisible(true);
        statusStretch += " Horizontal";
        _textStretch->setString(statusStretch);
    } 
    else if (sender == _hChecked)
    {
        _hChecked->setVisible(false);
        _hUnchecked->setVisible(true);
        statusStretch.erase(statusStretch.find(" Horizontal"), std::string(" Horizontal").length());
        _textStretch->setString(statusStretch);
    }
    else if (sender == _vUnchecked)
    {
        _vUnchecked->setVisible(false);
        _vChecked->setVisible(true);
        statusStretch += " Vertical";
        _textStretch->setString(statusStretch);
    }
    else if (sender == _vChecked)
    {
        _vChecked->setVisible(false);
        _vUnchecked->setVisible(true);
        statusStretch.erase(statusStretch.find(" Vertical"), std::string(" Vertical").length());
        _textStretch->setString(statusStretch);
    }
    else if (sender == _lPinUnchecked)
    {
        _lPinUnchecked->setVisible(false);
        _lPinChecked->setVisible(true);
    }
    else if (sender == _lPinChecked)
    {
        _lPinChecked->setVisible(false);
        _lPinUnchecked->setVisible(true);
    }
    else if (sender == _rPinUnchecked)
    {
        _rPinUnchecked->setVisible(false);
        _rPinChecked->setVisible(true);
    }
    else if (sender == _rPinChecked)
    {
        _rPinChecked->setVisible(false);
        _rPinUnchecked->setVisible(true);
    }
    else if (sender == _tPinUnchecked)
    {
        _tPinUnchecked->setVisible(false);
        _tPinChecked->setVisible(true);
    }
    else if (sender == _tPinChecked)
    {
        _tPinChecked->setVisible(false);
        _tPinUnchecked->setVisible(true);
    }
    else if (sender == _bPinUnchecked)
    {
        _bPinUnchecked->setVisible(false);
        _bPinChecked->setVisible(true);
    }
    else if (sender == _bPinChecked)
    {
        _bPinChecked->setVisible(false);
        _bPinUnchecked->setVisible(true);
    }

    if (_rPinChecked->isVisible())
    {
        if (_lPinChecked->isVisible())
        {
            hPinStatus = " Left Right";
        }
        else
        {
            hPinStatus = " Right";
        }
    }
    if (_tPinChecked->isVisible())
    {
        if (_bPinChecked->isVisible())
        {
            vPinStatus = " Top Bottom";
        }
        else
        {
            vPinStatus = " Top";
        }
    }

    statusPin = String::createWithFormat("Pin:%s%s", hPinStatus.c_str(), vPinStatus.c_str())->getCString();
    _textPin->setString(statusPin);

    auto layoutComponent = ui::LayoutComponent::bindLayoutComponent(_widget);
    layoutComponent->setStretchWidthEnabled(statusStretch.find("Horizontal") != std::string::npos);
    layoutComponent->setStretchHeightEnabled(statusStretch.find("Vertical") != std::string::npos);

    ui::LayoutComponent::HorizontalEdge horizontalEdgeType = ui::LayoutComponent::HorizontalEdge::None;
    if (statusPin.find("Left") != std::string::npos
        && statusPin.find("Right") == std::string::npos)
    {
        horizontalEdgeType = ui::LayoutComponent::HorizontalEdge::Left;
    }
    else if (statusPin.find("Left") == std::string::npos
        && statusPin.find("Right") != std::string::npos)
    {
        horizontalEdgeType = ui::LayoutComponent::HorizontalEdge::Right;
    }
    else if (statusPin.find("Left") != std::string::npos
        && statusPin.find("Right") != std::string::npos)
    {
        horizontalEdgeType = ui::LayoutComponent::HorizontalEdge::Center;
    }
    layoutComponent->setHorizontalEdge(horizontalEdgeType);

    ui::LayoutComponent::VerticalEdge verticalEdgeType = ui::LayoutComponent::VerticalEdge::None;
    if (statusPin.find("Top") != std::string::npos
        && statusPin.find("Bottom") == std::string::npos)
    {
        verticalEdgeType = ui::LayoutComponent::VerticalEdge::Top;
    }
    else if (statusPin.find("Top") == std::string::npos
        && statusPin.find("Bottom") != std::string::npos)
    {
        verticalEdgeType = ui::LayoutComponent::VerticalEdge::Bottom;
    }
    else if (statusPin.find("Top") != std::string::npos
        && statusPin.find("Bottom") != std::string::npos)
    {
        verticalEdgeType = ui::LayoutComponent::VerticalEdge::Center;
    }
    layoutComponent->setVerticalEdge(verticalEdgeType);
}

void UILayoutComponentTest_Editor::onResizeContainer(Ref* sender)
{
    auto layoutController = Helper::seekWidgetByName(_root, "Panel_Controller");
    Size size = _container->getContentSize();
    auto switchButton = Helper::seekWidgetByName(_root, "Button_Switch");
    switchButton->setEnabled(false);
    switchButton->setBright(false);

    if (size.width < 200)
    {
        layoutController->setVisible(false);
        this->schedule([=](float dt){
            auto size = _container->getContentSize();
            size.width += 303.f / 40.f;
            size.height += 70.f / 40.f;
            _container->setContentSize(size);
            ui::Helper::doLayout(_container);
            if (size.width > 390)
            {
                switchButton->setEnabled(true);
                switchButton->setBright(true);
            }
        }, 0.025, 39, 0, "1");
    } 
    else
    {
        layoutController->setVisible(true);
        this->schedule([=](float dt){
            auto size = _container->getContentSize();
            size.width -= 303.f / 40.f;
            size.height -= 70.f / 40.f;
            _container->setContentSize(size);
            ui::Helper::doLayout(_container);
            if (size.width < 110)
            {
                switchButton->setEnabled(true);
                switchButton->setBright(true);
            }
        }, 0.025, 39, 0, "2");
    }
}