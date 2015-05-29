#include "UIListViewTest_Editor.h"
#include "VisibleRect.h"

USING_NS_CC;
using namespace cocos2d::ui;

UIListViewEditorTests::UIListViewEditorTests()
{
    ADD_TEST_CASE(UIListViewTest_Vertical_Editor);
    ADD_TEST_CASE(UIListViewTest_Horizontal_Editor);
}
// UIListViewTest_Vertical_Editor

UIListViewTest_Vertical_Editor::UIListViewTest_Vertical_Editor()
: _displayValueLabel(nullptr)
{
    
}

UIListViewTest_Vertical_Editor::~UIListViewTest_Vertical_Editor()
{
    
}

bool UIListViewTest_Vertical_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIListView/New/resV.csb");
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

UIListViewTest_Horizontal_Editor::~UIListViewTest_Horizontal_Editor()
{
    
}

bool UIListViewTest_Horizontal_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIListView/New/resH.csb");
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
