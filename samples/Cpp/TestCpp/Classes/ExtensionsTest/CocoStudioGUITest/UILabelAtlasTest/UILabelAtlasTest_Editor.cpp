

#include "UILabelAtlasTest_Editor.h"

// UILabelAtlasTest_Editor

bool UILabelAtlasTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosgui/UIEditorTest/UILabelAtlas_Editor/ui_labelatlas_editor_1.json"));
        _touchGroup->addWidget(_layout);
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        CCSize rootSize = _layout->getSize();
        _touchGroup->setPosition(CCPoint((screenSize.width - rootSize.width) / 2,
                                         (screenSize.height - rootSize.height) / 2));
        
        Layout* root = static_cast<Layout*>(_touchGroup->getWidgetByName("root_Panel"));
        
        ui::Label* back_label = static_cast<ui::Label*>(UIHelper::seekWidgetByName(root, "back"));
        back_label->addTouchEventListener(this, toucheventselector(UIScene_Editor::toGUIEditorTestScene));
        
        _sceneTitle = static_cast<ui::Label*>(UIHelper::seekWidgetByName(root, "UItest"));
        
        return true;
    }
    
    return false;
}
