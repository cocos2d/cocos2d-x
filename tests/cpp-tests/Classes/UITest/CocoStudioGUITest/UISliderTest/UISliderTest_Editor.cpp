

#include "UISliderTest_Editor.h"


// UISliderTest_Editor

UISliderTest_Editor::UISliderTest_Editor()
: _displayValueLabel(nullptr)
{
    
}

UISliderTest_Editor::~UISliderTest_Editor()
{
    
}

void UISliderTest_Editor::switchLoadMethod(cocos2d::Ref *pSender)
{
    MenuItemToggle *item = (MenuItemToggle*)pSender;
    
    switch (item->getSelectedIndex())
    {
        case 0:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UISlider/windows_ui_slider_editor_1.json"));
            
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 1:
        {
            _layout->removeFromParentAndCleanup(true);
            
            _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UIEditorTest/UISlider/windows_ui_slider_editor_1.csb"));
            
            _touchGroup->addChild(_layout);
            
            this->configureGUIScene();
            
            break;
        }
            
        case 2:
        {
            _layout->removeFromParentAndCleanup(true);
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UISlider/crossplatform_UISlider_Editor_1.ExportJson");
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
            
            Node* node = CSLoader::createNode("cocosui/UIEditorTest/UISlider/crossplatform_UISlider_Editor_1.csb");
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

void UISliderTest_Editor::configureGUIScene()
{
    Size screenSize = CCDirector::getInstance()->getWinSize();
    Size rootSize = _layout->getContentSize();
    _touchGroup->setPosition(Vec2((screenSize.width - rootSize.width) / 2,
                                  (screenSize.height - rootSize.height) / 2));
    
    Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
    
    Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
    back_label->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::toGUIEditorTestScene, this));
    
    _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
    
    
    Slider* slider = static_cast<Slider*>(Helper::seekWidgetByName(root, "Slider_738"));
    slider->addEventListener(CC_CALLBACK_2(UISliderTest_Editor::sliderEvent, this));
    
    Slider* scale9_slider = static_cast<Slider*>(Helper::seekWidgetByName(root, "Slider_740"));
    scale9_slider->addEventListener(CC_CALLBACK_2(UISliderTest_Editor::sliderEvent, this));
}

bool UISliderTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UISlider/crossplatform_UISlider_Editor_1.csb");
        Node* child = node->getChildByTag(5);
        child->removeFromParent();
        _layout = static_cast<Layout*>(child);
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
        
        _displayValueLabel = Text::create();
        _displayValueLabel->setFontName("fonts/Marker Felt.ttf");
        _displayValueLabel->setFontSize(30);
        _displayValueLabel->setString("No event");
        _displayValueLabel->setPosition(Vec2(_layout->getContentSize().width / 2,
                                              _layout->getContentSize().height - _displayValueLabel->getContentSize().height * 1.75f));
        _touchGroup->addChild(_displayValueLabel, 20);
        
        return true;
    }
    
    return false;
}

void UISliderTest_Editor::sliderEvent(Ref *pSender, Slider::EventType type)
{
    switch (type)
    {
        case Slider::EventType::ON_PERCENTAGE_CHANGED:
        {
            Slider* slider = static_cast<Slider*>(pSender);
            _displayValueLabel->setString(CCString::createWithFormat("percent %d", slider->getPercent())->getCString());
        }
            break;
            
        default:
            break;
    }
}
