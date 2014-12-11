
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
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UIListView/Vertical/windows_ui_listview_editor_1.json"));
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UIEditorTest/UIListView/Vertical/windows_ui_listview_editor_1.csb"));
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIListView/Vertical/crossplatform_UIListView_Vertical_Editor_1.ExportJson");
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
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIListView/Vertical/crossplatform_UIListView_Vertical_Editor_1.csb");
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
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIListView/New/crossplatform_UIListView_Editor_Vertical.csb");
        Node* child = node->getChildByTag(5);
        child->removeFromParent();
        _layout = dynamic_cast<Layout*>(child);
        _touchGroup->addChild(_layout);

        this->configureGUIScene();
        auto listView1 = dynamic_cast<ListView*>(Helper::seekWidgetByName(_layout, "ListView1"));
        auto listView2 = dynamic_cast<ListView*>(Helper::seekWidgetByName(_layout, "ListView2"));
        auto listView3 = dynamic_cast<ListView*>(Helper::seekWidgetByName(_layout, "ListView3"));
        setupListView(listView1);
        setupListView(listView2);
        setupListView(listView3);
        
        return true;
    }
    
    return false;
}

void UIListViewTest_Vertical_Editor::setupListView(ListView* listView)
{
    float scale = 0.5f;
    float itemMargin = listView->getItemsMargin();

    auto item0 = Text::create();
    item0->setString(String::createWithFormat("Item margin: %d", static_cast<int>(itemMargin))->getCString());
    listView->addChild(item0);

    auto item1 = Layout::create();
    auto checkbox = CheckBox::create("selected01.png", "selected01.png", "selected02.png", "selected01.png", "selected01.png");
    checkbox->setPosition(Vec2(checkbox->getCustomSize().width / 2, checkbox->getCustomSize().height / 2));
    item1->addChild(checkbox);
    auto checkboxText = Text::create();
    checkboxText->setString("CheckBox");
    checkboxText->setFontSize(checkbox->getCustomSize().width * .8f);
    checkboxText->setPosition(Vec2(checkbox->getCustomSize().width + checkboxText->getCustomSize().width / 2, checkbox->getCustomSize().height / 2));
    item1->addChild(checkboxText);
    float item1Width = scale * (checkbox->getCustomSize().width + checkboxText->getCustomSize().width);
    float item1Height = scale * checkbox->getCustomSize().height;
    item1->setContentSize(Size(item1Width, item1Height));
    item1->setScale(scale);
    listView->addChild(item1);

    auto item2 = Text::create();
    item2->setString("Text2");
    item2->setFontSize(checkbox->getCustomSize().width * .4f);
    item2->setTextColor(Color4B(0, 255, 0, 255));
    listView->addChild(item2);

    auto item3 = Layout::create();
    auto imageview0 = ImageView::create("image.png");
    auto imageview1 = ImageView::create("image.png");
    imageview1->setPositionX(imageview1->getCustomSize().width * 2);
    imageview0->setAnchorPoint(Vec2(0, 0));
    imageview1->setAnchorPoint(Vec2(0, 0));
    item3->setContentSize(Size(imageview0->getCustomSize().width * 3 * scale, imageview0->getCustomSize().height * scale));
    item3->addChild(imageview0);
    item3->addChild(imageview1);
    item3->setScale(scale);
    listView->addChild(item3);

    auto item4 = Button::create("button.png", "button_p.png");
    item4->setTitleText("Button");
    listView->pushBackCustomItem(item4);

    auto itemModel = Text::create();
    itemModel->setTextColor(Color4B(255, 0, 0, 125));
    itemModel->setString("List item model");
    listView->setItemModel(itemModel);
    listView->pushBackDefaultItem();
    listView->pushBackDefaultItem();
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
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UIListView/Horizontal/windows_ui_listview_horizontal_editor_1.json"));
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UIEditorTest/UIListView/Horizontal/windows_ui_listview_horizontal_editor_1.csb"));
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIListView/Horizontal/crossplatform_UIListView_Horizontal_Editor_1.ExportJson");
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
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIListView/Horizontal/crossplatform_UIListView_Horizontal_Editor_1.csb");
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
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIListView/New/crossplatform_UIListView_Editor_Horizontal.csb");
        Node* child = node->getChildByTag(5);
        child->removeFromParent();
        _layout = dynamic_cast<Layout*>(child);
        _touchGroup->addChild(_layout);

        this->configureGUIScene();
        auto listView1 = dynamic_cast<ListView*>(Helper::seekWidgetByName(_layout, "ListView1"));
        auto listView2 = dynamic_cast<ListView*>(Helper::seekWidgetByName(_layout, "ListView2"));
        auto listView3 = dynamic_cast<ListView*>(Helper::seekWidgetByName(_layout, "ListView3"));
        UIListViewTest_Vertical_Editor::setupListView(listView1);
        UIListViewTest_Vertical_Editor::setupListView(listView2);
        UIListViewTest_Vertical_Editor::setupListView(listView3);

        return true;
    }
    
    return false;
}
