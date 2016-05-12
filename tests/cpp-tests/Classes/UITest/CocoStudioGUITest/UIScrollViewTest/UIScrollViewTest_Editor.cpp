#include "UIScrollViewTest_Editor.h"
#include "VisibleRect.h"

USING_NS_CC;
using namespace cocos2d::ui;

UIScrollViewEditorTests::UIScrollViewEditorTests()
{
    ADD_TEST_CASE(UIScrollViewTest_Vertical_Editor);
    ADD_TEST_CASE(UIScrollViewTest_Horizontal_Editor);
    ADD_TEST_CASE(UIScrollViewTest_Both_Editor);
//    ADD_TEST_CASE(UIScrollViewTest_ScrollToPercentBothDirection_Editor);
//    ADD_TEST_CASE(UIScrollViewTest_ScrollToPercentBothDirection_Bounce_Editor);
    ADD_TEST_CASE(UIScrollViewTest_ClippingWithNode);
    ADD_TEST_CASE(UISscrollViewTestBar);
}

// UIScrollViewTest_Vertical_Editor

UIScrollViewTest_Vertical_Editor::UIScrollViewTest_Vertical_Editor()
{
    
}

UIScrollViewTest_Vertical_Editor::~UIScrollViewTest_Vertical_Editor()
{
    
}

bool UIScrollViewTest_Vertical_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIScrollView/Vertical/res.csb");
        Node* child = node->getChildByTag(5);
        child->removeFromParent();
        _layout = static_cast<Layout*>(child);
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
        
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

bool UIScrollViewTest_Horizontal_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIScrollView/Horizontal/res.csb");
        Node* child = node->getChildByTag(5);
        child->removeFromParent();
        _layout = static_cast<Layout*>(child);
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();

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

bool UIScrollViewTest_Both_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIScrollView/Both/res.csb");
        Node* child = node->getChildByTag(5);
        child->removeFromParent();
        _layout = static_cast<Layout*>(child);
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();

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
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UITest/UITest.csb"));
        _touchGroup->addChild(_layout);
        Size screenSize = Director::getInstance()->getWinSize();
        Size rootSize = _layout->getContentSize();
        _touchGroup->setPosition(Vec2((screenSize.width - rootSize.width) / 2,
                                        (screenSize.height - rootSize.height) / 2));
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
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UITest/UITest.csb"));
        _touchGroup->addChild(_layout);
        Size screenSize = Director::getInstance()->getWinSize();
        Size rootSize = _layout->getContentSize();
        _touchGroup->setPosition(Vec2((screenSize.width - rootSize.width) / 2,
                                        (screenSize.height - rootSize.height) / 2));
        return true;
    }
    
    return false;
}

// UIScrollViewTest_Vertical_Editor

UIScrollViewTest_ClippingWithNode::UIScrollViewTest_ClippingWithNode()
{

}

UIScrollViewTest_ClippingWithNode::~UIScrollViewTest_ClippingWithNode()
{

}

bool UIScrollViewTest_ClippingWithNode::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIScrollView/ScrollViewAndButton/MainScene.csb");
        _layout = static_cast<Layout*>(node);
        _touchGroup->addChild(_layout);

        return true;
    }

    return false;
}

UISscrollViewTestBar::UISscrollViewTestBar()
{
}

UISscrollViewTestBar::~UISscrollViewTestBar()
{
}

bool UISscrollViewTestBar::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIScrollView/Both/ScrollBarTests.csb");
        _touchGroup->addChild(node);
        return true;
    }
    return false;
}
