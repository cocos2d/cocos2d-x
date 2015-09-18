#include "UIPageViewTest_Editor.h"
#include "VisibleRect.h"

USING_NS_CC;
using namespace cocos2d::ui;

UIPageViewEditorTests::UIPageViewEditorTests()
{
    ADD_TEST_CASE(UIPageViewTest_Editor);
}

// UIPageViewTest_Editor

UIPageViewTest_Editor::UIPageViewTest_Editor()
: _displayValueLabel(nullptr)
{
    
}

UIPageViewTest_Editor::~UIPageViewTest_Editor()
{
    
}

bool UIPageViewTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIPageView/res.csb");
        Node* child = node->getChildByTag(5);
        child->removeFromParent();
        _layout = static_cast<Layout*>(child);
        _touchGroup->addChild(_layout);
        
        auto pageView = (PageView*)(ui::Helper::seekWidgetByName(_layout, "PageView_1269"));
        pageView->scrollToPage(1); // 1->2

        this->configureGUIScene();

        auto button1 = Button::create();
        button1->setTitleText("scrollToPage 3");
        button1->setNormalizedPosition(Vec2(0.8,0.2));
        button1->addClickEventListener([=](Ref*){
            pageView->scrollToPage(2);
        });
        _touchGroup->addChild(button1);

      

        return true;
    }
    
    return false;
}
