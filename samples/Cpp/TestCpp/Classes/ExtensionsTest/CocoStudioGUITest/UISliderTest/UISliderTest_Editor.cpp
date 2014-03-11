

#include "UISliderTest_Editor.h"


// UISliderTest_Editor

UISliderTest_Editor::UISliderTest_Editor()
: _displayValueLabel(NULL)
{
    
}

UISliderTest_Editor::~UISliderTest_Editor()
{
    
}

bool UISliderTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosgui/UIEditorTest/UISlider_Editor/ui_slider_editor_1.json"));
        _touchGroup->addWidget(_layout);
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        CCSize rootSize = _layout->getSize();
        _touchGroup->setPosition(CCPoint((screenSize.width - rootSize.width) / 2,
                                         (screenSize.height - rootSize.height) / 2));
        
        Layout* root = static_cast<Layout*>(_touchGroup->getWidgetByName("root_Panel"));
        
        ui::Label* back_label = static_cast<ui::Label*>(UIHelper::seekWidgetByName(root, "back"));
        back_label->addTouchEventListener(this, toucheventselector(UIScene_Editor::toGUIEditorTestScene));
        
        _sceneTitle = static_cast<ui::Label*>(UIHelper::seekWidgetByName(root, "UItest"));
        
        
        Slider* slider = static_cast<Slider*>(UIHelper::seekWidgetByName(root, "Slider_738"));
        slider->addEventListenerSlider(this, sliderpercentchangedselector(UISliderTest_Editor::sliderEvent));
        
        Slider* scale9_slider = static_cast<Slider*>(UIHelper::seekWidgetByName(root, "Slider_740"));
        scale9_slider->addEventListenerSlider(this, sliderpercentchangedselector(UISliderTest_Editor::sliderEvent));
        
        
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

void UISliderTest_Editor::sliderEvent(cocos2d::CCObject *pSender, SliderEventType type)
{
    switch (type)
    {
        case SLIDER_PERCENTCHANGED:
        {
            Slider* slider = static_cast<Slider*>(pSender);
            _displayValueLabel->setText(CCString::createWithFormat("percent %d", slider->getPercent())->getCString());
        }
            break;
            
        default:
            break;
    }
}
