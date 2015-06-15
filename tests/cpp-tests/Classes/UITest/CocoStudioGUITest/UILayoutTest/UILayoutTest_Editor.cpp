#include "UILayoutTest_Editor.h"
#include "VisibleRect.h"

USING_NS_CC;
using namespace cocos2d::ui;

UILayoutEditorTests::UILayoutEditorTests()
{
    ADD_TEST_CASE(UILayoutTest_Editor);
    ADD_TEST_CASE(UILayoutTest_Color_Editor);
    ADD_TEST_CASE(UILayoutTest_Gradient_Editor);
    ADD_TEST_CASE(UILayoutTest_BackGroundImage_Editor);
    ADD_TEST_CASE(UILayoutTest_BackGroundImage_Scale9_Editor);
    ADD_TEST_CASE(UILayoutTest_Layout_Linear_Vertical_Editor);

    ADD_TEST_CASE(UILayoutTest_Layout_Linear_Horizontal_Editor);
    ADD_TEST_CASE(UILayoutTest_Layout_Relative_Align_Parent_Editor);
    ADD_TEST_CASE(UILayoutTest_Layout_Relative_Location_Editor);
    ADD_TEST_CASE(UILayoutComponentTest_Editor);
}
// UILayoutTest_Editor

UILayoutTest_Editor::UILayoutTest_Editor()
{
    
}

UILayoutTest_Editor::~UILayoutTest_Editor()
{
    
}

bool UILayoutTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/Layout/res.csb");
        Node* child = node->getChildByTag(5);
        child->removeFromParent();
        _layout = static_cast<Layout*>(child);
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
        
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

bool UILayoutTest_Color_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/Color/res.csb");
        Node* child = node->getChildByTag(5);
        child->removeFromParent();
        _layout = static_cast<Layout*>(child);
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
        
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

bool UILayoutTest_Gradient_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/Gradient_Color/res.csb");
        Node* child = node->getChildByTag(5);
        child->removeFromParent();
        _layout = static_cast<Layout*>(child);
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
        
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

bool UILayoutTest_BackGroundImage_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/BackgroundImage/res.csb");
        Node* child = node->getChildByTag(5);
        child->removeFromParent();
        _layout = static_cast<Layout*>(child);
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
        
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

bool UILayoutTest_BackGroundImage_Scale9_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/Scale9_BackgroundImage/res.csb");
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

bool UILayoutTest_Layout_Linear_Vertical_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout/Linear_Vertical_Layout/res.json"));

        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
        
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

bool UILayoutTest_Layout_Linear_Horizontal_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout/Linear_Horizontal_Layout/res.json"));
        _touchGroup->addChild(_layout);
      
        this->configureGUIScene();
        
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

bool UILayoutTest_Layout_Relative_Align_Parent_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout/Relative_Align_Parent/res.json"));
        _touchGroup->addChild(_layout);
        this->configureGUIScene();
        
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

bool UILayoutTest_Layout_Relative_Location_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout/Relative_Align_Location/res.json"));
        _touchGroup->addChild(_layout);
        this->configureGUIScene();
        
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
    UIScene_Editor::configureGUIScene();

    _root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));

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
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILayout/LayoutComponent/res.csb");
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
        }, 0.025f, 39, 0, "1");
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
        }, 0.025f, 39, 0, "2");
    }
}
