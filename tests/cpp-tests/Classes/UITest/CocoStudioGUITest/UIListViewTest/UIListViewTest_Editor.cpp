
#include "UIListViewTest_Editor.h"
#include "VisibleRect.h"


// UIListViewTest_Vertical_Editor

UIListViewTest_Vertical_Editor::UIListViewTest_Vertical_Editor()
: _displayValueLabel(nullptr)
{
    
}

UIListViewTest_Vertical_Editor::~UIListViewTest_Vertical_Editor()
{
    
}

void UIListViewTest_Vertical_Editor::switchLoadMethod(cocos2d::Ref *pSender)
{
    MenuItemToggle *item = (MenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UIListView_Editor/UIListView_Vertical_Editor/windows_ui_listview_editor_1.json"));
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UIEditorTest/UIListView_Editor/UIListView_Vertical_Editor/windows_ui_listview_editor_1.csb"));
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIListView_Editor/UIListView_Vertical_Editor/crossplatform_UIListView_Vertical_Editor_1.ExportJson");
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
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIListView_Editor/UIListView_Vertical_Editor/crossplatform_UIListView_Vertical_Editor_1.csb");
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

void UIListViewTest_Vertical_Editor::configureGUIScene()
{
    Size screenSize = CCDirector::getInstance()->getWinSize();
    Size rootSize = _layout->getContentSize();
    _touchGroup->setPosition(Vec2((screenSize.width - rootSize.width) / 2,
                                  (screenSize.height - rootSize.height) / 2));
    
    Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
    
    Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
    back_label->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::toGUIEditorTestScene,this));
    
    _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
    
    //        ListView* listView = static_cast<ListView*>(UIHelper::seekWidgetByName(root, "ListView_1214"));
    //        CCLOG("listView isBounceEnabled = %d", listView->isBounceEnabled());
    
    Button* left_button = Button::create();
    left_button->loadTextures("Images/b1.png", "Images/b2.png", "");
    left_button->setPosition(Vec2(_layout->getContentSize().width / 2 - left_button->getContentSize().width,
                                  left_button->getContentSize().height * 0.625));
    left_button->setTouchEnabled(true);
    left_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::previousCallback,this));
    
    
    left_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
    _layout->addChild(left_button);
    
    Button* right_button = Button::create();
    right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
    right_button->setPosition(Vec2(_layout->getContentSize().width / 2 + right_button->getContentSize().width,
                                   right_button->getContentSize().height * 0.625));
    right_button->setTouchEnabled(true);
    right_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
    right_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::nextCallback,this));
    _layout->addChild(right_button);
    
}

bool UIListViewTest_Vertical_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UIListView_Editor/UIListView_Vertical_Editor/windows_ui_listview_editor_1.json"));
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


// UIListViewTest_Horizontal_Editor

UIListViewTest_Horizontal_Editor::UIListViewTest_Horizontal_Editor()
: _displayValueLabel(nullptr)
{
    
}

void UIListViewTest_Horizontal_Editor::switchLoadMethod(cocos2d::Ref *pSender)
{
    MenuItemToggle *item = (MenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UIListView_Editor/UIListView_Horizontal_Editor/windows_ui_listview_horizontal_editor_1.json"));
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UIEditorTest/UIListView_Editor/UIListView_Horizontal_Editor/windows_ui_listview_horizontal_editor_1.csb"));
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIListView_Editor/UIListView_Horizontal_Editor/crossplatform_UIListView_Horizontal_Editor_1.ExportJson");
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
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIListView_Editor/UIListView_Horizontal_Editor/crossplatform_UIListView_Horizontal_Editor_1.csb");
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

void UIListViewTest_Horizontal_Editor::configureGUIScene()
{
    Size screenSize = CCDirector::getInstance()->getWinSize();
    Size rootSize = _layout->getContentSize();
    _touchGroup->setPosition(Vec2((screenSize.width - rootSize.width) / 2,
                                  (screenSize.height - rootSize.height) / 2));
    
    Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
    
    Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
    back_label->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::toGUIEditorTestScene,this));
    
    _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
    
    Button* left_button = Button::create();
    left_button->loadTextures("Images/b1.png", "Images/b2.png", "");
    left_button->setPosition(Vec2(_layout->getContentSize().width / 2 - left_button->getContentSize().width,
                                  left_button->getContentSize().height * 0.625));
    left_button->setTouchEnabled(true);
    left_button->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::previousCallback,this));
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

UIListViewTest_Horizontal_Editor::~UIListViewTest_Horizontal_Editor()
{
    
}

bool UIListViewTest_Horizontal_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UIListView_Editor/UIListView_Horizontal_Editor/windows_ui_listview_horizontal_editor_1.json"));
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
