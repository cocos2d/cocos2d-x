

#include "UILayoutTest_Editor.h"


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
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Editor/ui_layout_editor_1.json"));
        _touchGroup->addChild(_layout);
        Size screenSize = CCDirector::getInstance()->getWinSize();
        Size rootSize = _layout->getSize();
        _touchGroup->setPosition(Vector2((screenSize.width - rootSize.width) / 2,
                                       (screenSize.height - rootSize.height) / 2));
        
        Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
        
        Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
        back_label->addTouchEventListener(this, toucheventselector(UIScene_Editor::toGUIEditorTestScene));
        
        _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
        
        Button* left_button = Button::create();
        left_button->loadTextures("Images/b1.png", "Images/b2.png", "");
        left_button->setPosition(Vector2(_layout->getSize().width / 2 - left_button->getSize().width,
                                     left_button->getSize().height));
        left_button->setTouchEnabled(true);
        left_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::previousCallback));
        left_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
        _layout->addChild(left_button);
        
        Button* right_button = Button::create();
        right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
        right_button->setPosition(Vector2(_layout->getSize().width / 2 + right_button->getSize().width,
                                      right_button->getSize().height));
        right_button->setTouchEnabled(true);
        right_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
        right_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::nextCallback));
        _layout->addChild(right_button);
        
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
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Color_Editor/ui_layout_color_editor_1.json"));
        _touchGroup->addChild(_layout);
        Size screenSize = CCDirector::getInstance()->getWinSize();
        Size rootSize = _layout->getSize();
        _touchGroup->setPosition(Vector2((screenSize.width - rootSize.width) / 2,
                                        (screenSize.height - rootSize.height) / 2));
        
        Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
        
        Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
        back_label->addTouchEventListener(this, toucheventselector(UIScene_Editor::toGUIEditorTestScene));
        
        _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
        
        Button* left_button = Button::create();
        left_button->loadTextures("Images/b1.png", "Images/b2.png", "");
        left_button->setPosition(Vector2(_layout->getSize().width / 2 - left_button->getSize().width,
                                     left_button->getSize().height));
        left_button->setTouchEnabled(true);
        left_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::previousCallback));
        left_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
        _layout->addChild(left_button);
        
        Button* right_button = Button::create();
        right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
        right_button->setPosition(Vector2(_layout->getSize().width / 2 + right_button->getSize().width,
                                      right_button->getSize().height));
        right_button->setTouchEnabled(true);
        right_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
        right_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::nextCallback));
        _layout->addChild(right_button);
        
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
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Gradient_Color_Editor/ui_layout_gradient_color_editor_1_0.json"));
        _touchGroup->addChild(_layout);
        Size screenSize = CCDirector::getInstance()->getWinSize();
        Size rootSize = _layout->getSize();
        _touchGroup->setPosition(Vector2((screenSize.width - rootSize.width) / 2,
                                        (screenSize.height - rootSize.height) / 2));
        
        Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
        
        Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
        back_label->addTouchEventListener(this, toucheventselector(UIScene_Editor::toGUIEditorTestScene));
        
        _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
        
        Button* left_button = Button::create();
        left_button->loadTextures("Images/b1.png", "Images/b2.png", "");
        left_button->setPosition(Vector2(_layout->getSize().width / 2 - left_button->getSize().width,
                                     left_button->getSize().height));
        left_button->setTouchEnabled(true);
        left_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::previousCallback));
        left_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
        _layout->addChild(left_button);
        
        Button* right_button = Button::create();
        right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
        right_button->setPosition(Vector2(_layout->getSize().width / 2 + right_button->getSize().width,
                                      right_button->getSize().height));
        right_button->setTouchEnabled(true);
        right_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
        right_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::nextCallback));
        _layout->addChild(right_button);
        
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
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_BackgroundImage_Editor/ui_layout_backgroundimage_editor_1_0_0.json"));
        _touchGroup->addChild(_layout);
        Size screenSize = CCDirector::getInstance()->getWinSize();
        Size rootSize = _layout->getSize();
        _touchGroup->setPosition(Vector2((screenSize.width - rootSize.width) / 2,
                                        (screenSize.height - rootSize.height) / 2));
        
        Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
        
        Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
        back_label->addTouchEventListener(this, toucheventselector(UIScene_Editor::toGUIEditorTestScene));
        
        _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
        
        Button* left_button = Button::create();
        left_button->loadTextures("Images/b1.png", "Images/b2.png", "");
        left_button->setPosition(Vector2(_layout->getSize().width / 2 - left_button->getSize().width,
                                     left_button->getSize().height * 0.625));
        left_button->setTouchEnabled(true);
        left_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::previousCallback));
        left_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
        _layout->addChild(left_button);
        
        Button* right_button = Button::create();
        right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
        right_button->setPosition(Vector2(_layout->getSize().width / 2 + right_button->getSize().width,
                                      right_button->getSize().height * 0.625));
        right_button->setTouchEnabled(true);
        right_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
        right_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::nextCallback));
        _layout->addChild(right_button);
        
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
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Scale9_BackgroundImage_Editor/ui_layout_scale9_backgroundimage_editor.json"));
        _touchGroup->addChild(_layout);
        Size screenSize = CCDirector::getInstance()->getWinSize();
        Size rootSize = _layout->getSize();
        _touchGroup->setPosition(Vector2((screenSize.width - rootSize.width) / 2,
                                        (screenSize.height - rootSize.height) / 2));
        
        Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
        
        Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
        back_label->addTouchEventListener(this, toucheventselector(UIScene_Editor::toGUIEditorTestScene));
        
        _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
        
        Button* left_button = Button::create();
        left_button->loadTextures("Images/b1.png", "Images/b2.png", "");
        left_button->setPosition(Vector2(_layout->getSize().width / 2 - left_button->getSize().width,
                                     left_button->getSize().height));
        left_button->setTouchEnabled(true);
        left_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::previousCallback));
        left_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
        _layout->addChild(left_button);
        
        Button* right_button = Button::create();
        right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
        right_button->setPosition(Vector2(_layout->getSize().width / 2 + right_button->getSize().width,
                                      right_button->getSize().height));
        right_button->setTouchEnabled(true);
        right_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
        right_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::nextCallback));
        _layout->addChild(right_button);
        
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
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Linear_Vertical_Layout_Editor/ui_layout_linear_vertical_layout_editor.json"));
        _touchGroup->addChild(_layout);
        Size screenSize = CCDirector::getInstance()->getWinSize();
        Size rootSize = _layout->getSize();
        _touchGroup->setPosition(Vector2((screenSize.width - rootSize.width) / 2,
                                        (screenSize.height - rootSize.height) / 2));
        
        Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
        
        Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
        back_label->addTouchEventListener(this, toucheventselector(UIScene_Editor::toGUIEditorTestScene));
        
        _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
        
        Button* left_button = Button::create();
        left_button->loadTextures("Images/b1.png", "Images/b2.png", "");
        left_button->setPosition(Vector2(_layout->getSize().width / 2 - left_button->getSize().width,
                                     left_button->getSize().height * 0.625));
        left_button->setTouchEnabled(true);
        left_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::previousCallback));
        left_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
        _layout->addChild(left_button);
        
        Button* right_button = Button::create();
        right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
        right_button->setPosition(Vector2(_layout->getSize().width / 2 + right_button->getSize().width,
                                      right_button->getSize().height * 0.625));
        right_button->setTouchEnabled(true);
        right_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
        right_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::nextCallback));
        _layout->addChild(right_button);
        
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
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Linear_Horizontal_Layout_Editor/ui_layout_linear_horizontal_layout_editor.json"));
        _touchGroup->addChild(_layout);
        Size screenSize = CCDirector::getInstance()->getWinSize();
        Size rootSize = _layout->getSize();
        _touchGroup->setPosition(Vector2((screenSize.width - rootSize.width) / 2,
                                        (screenSize.height - rootSize.height) / 2));
        
        Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
        
        Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
        back_label->addTouchEventListener(this, toucheventselector(UIScene_Editor::toGUIEditorTestScene));
        
        _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
        
        Button* left_button = Button::create();
        left_button->loadTextures("Images/b1.png", "Images/b2.png", "");
        left_button->setPosition(Vector2(_layout->getSize().width / 2 - left_button->getSize().width,
                                     left_button->getSize().height * 0.625));
        left_button->setTouchEnabled(true);
        left_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::previousCallback));
        left_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
        _layout->addChild(left_button);
        
        Button* right_button = Button::create();
        right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
        right_button->setPosition(Vector2(_layout->getSize().width / 2 + right_button->getSize().width,
                                      right_button->getSize().height * 0.625));
        right_button->setTouchEnabled(true);
        right_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
        right_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::nextCallback));
        _layout->addChild(right_button);

        
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
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Relative_Align_Parent_Editor/ui_layout_relative_align_parent_editor.json"));
        _touchGroup->addChild(_layout);
        Size screenSize = CCDirector::getInstance()->getWinSize();
        Size rootSize = _layout->getSize();
        _touchGroup->setPosition(Vector2((screenSize.width - rootSize.width) / 2,
                                        (screenSize.height - rootSize.height) / 2));
        
        Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
        
        Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
        back_label->addTouchEventListener(this, toucheventselector(UIScene_Editor::toGUIEditorTestScene));
        
        _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
        
        Button* left_button = Button::create();
        left_button->loadTextures("Images/b1.png", "Images/b2.png", "");
        left_button->setPosition(Vector2(_layout->getSize().width / 2 - left_button->getSize().width,
                                     left_button->getSize().height * 0.625));
        left_button->setTouchEnabled(true);
        left_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::previousCallback));
        left_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
        _layout->addChild(left_button);
        
        Button* right_button = Button::create();
        right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
        right_button->setPosition(Vector2(_layout->getSize().width / 2 + right_button->getSize().width,
                                      right_button->getSize().height * 0.625));
        right_button->setTouchEnabled(true);
        right_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
        right_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::nextCallback));
        _layout->addChild(right_button);
        
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
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILayout_Editor/UILayout_Relative_Align_Location_Editor/ui_layout_relative_align_location_editor.json"));
        _touchGroup->addChild(_layout);
        Size screenSize = CCDirector::getInstance()->getWinSize();
        Size rootSize = _layout->getSize();
        _touchGroup->setPosition(Vector2((screenSize.width - rootSize.width) / 2,
                                        (screenSize.height - rootSize.height) / 2));
        
        Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
        
        Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
        back_label->addTouchEventListener(this, toucheventselector(UIScene_Editor::toGUIEditorTestScene));
        
        _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
        
        Button* left_button = Button::create();
        left_button->loadTextures("Images/b1.png", "Images/b2.png", "");
        left_button->setPosition(Vector2(_layout->getSize().width / 2 - left_button->getSize().width,
                                     left_button->getSize().height * 0.625));
        left_button->setTouchEnabled(true);
        left_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::previousCallback));
        left_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
        _layout->addChild(left_button);
        
        Button* right_button = Button::create();
        right_button->loadTextures("Images/f1.png", "Images/f2.png", "");
        right_button->setPosition(Vector2(_layout->getSize().width / 2 + right_button->getSize().width,
                                      right_button->getSize().height * 0.625));
        right_button->setTouchEnabled(true);
        right_button->setLocalZOrder(_layout->getLocalZOrder() + 1);
        right_button->addTouchEventListener(this, toucheventselector(UIScene_Editor::nextCallback));
        _layout->addChild(right_button);
        
        return true;
    }
    
    return false;
}
