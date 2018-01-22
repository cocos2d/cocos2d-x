#include "UITileImageViewTest.h"

USING_NS_CC;
using namespace cocos2d::ui;

UITileImageViewTests::UITileImageViewTests()
{
    ADD_TEST_CASE(UITileImageViewTest1);
    ADD_TEST_CASE(UITileImageViewTest2);
    ADD_TEST_CASE(UITileImageViewTest3);
}


bool UITileImageViewTest1::init()
{
    if (UIScene::init())
    {
        Size s = Director::getInstance()->getVisibleSize();
        
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/blocks9ss.plist");
        
        
        auto s1 = TileImageView::create("blocks9.png", Widget::TextureResType::PLIST);
        addChild(s1);
        s1->setPosition(Vec2(s.width/2 - s.width/4, s.height/2));
        s1->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        s1->setContentSize(s1->getContentSize()*1.5);
        
        auto s2 = TileImageView::create("blocks9r.png", Widget::TextureResType::PLIST);
        addChild(s2);
        s2->setPosition(Vec2(s.width/2 + s.width/4, s.height/2));
        s2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        s2->setContentSize(s2->getContentSize()*1.5);
        return true;
    }
    return false;
}

bool UITileImageViewTest2::init()
{
    if (UIScene::init())
    {
        Size s = Director::getInstance()->getVisibleSize();
        
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/blocks9ss.plist");
        
        
        auto s1 = TileImageView::create("blocks9.png", Widget::TextureResType::PLIST);
        addChild(s1);
        s1->setPosition(Vec2(s.width/2-s.width/3, s.height/2));
        s1->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        s1->setContentSize(s1->getContentSize()*1.5);
        
        auto s2 = TileImageView::create("blocks9c.png", Widget::TextureResType::PLIST);
        addChild(s2);
        s2->setPosition(Vec2(s.width/2-s.width/3, s.height/2));
        s2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        s2->setContentSize(s2->getContentSize()*1.5);
        
        auto s3 = TileImageView::create("blocks9.png", Widget::TextureResType::PLIST);
        addChild(s3);
        s3->setPosition(Vec2(s.width/2, s.height/2));
        s3->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        s3->setContentSize(s3->getContentSize()*1.5);
        s3->setFlippedX(true);
        
        auto s4 = TileImageView::create("blocks9c.png", Widget::TextureResType::PLIST);
        addChild(s4);
        s4->setPosition(Vec2(s.width/2, s.height/2));
        s4->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        s4->setContentSize(s4->getContentSize()*1.5);
        s4->setFlippedX(true);
        
        auto s5 = TileImageView::create("blocks9.png", Widget::TextureResType::PLIST);
        addChild(s5);
        s5->setPosition(Vec2(s.width/2+s.width/3, s.height/2));
        s5->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        s5->setContentSize(s5->getContentSize()*1.5);
        s5->setFlippedY(true);
        
        auto s6 = TileImageView::create("blocks9c.png", Widget::TextureResType::PLIST);
        addChild(s6);
        s6->setPosition(Vec2(s.width/2+s.width/3, s.height/2));
        s6->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        s6->setContentSize(s6->getContentSize()*1.5);
        s6->setFlippedY(true);
        return true;
    }
    return false;
}

bool UITileImageViewTest3::init()
{
    if (UIScene::init())
    {
        Size s = Director::getInstance()->getVisibleSize();
        
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/blocks9ss.plist");
        
        
        auto s1 = TileImageView::create("blocks9r.png", Widget::TextureResType::PLIST);
        addChild(s1);
        s1->setPosition(Vec2(s.width/2-s.width/3, s.height/2));
        s1->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        s1->setContentSize(s1->getContentSize()*1.5);
        
        auto s2 = TileImageView::create("blocks9cr.png", Widget::TextureResType::PLIST);
        addChild(s2);
        s2->setPosition(Vec2(s.width/2-s.width/3, s.height/2));
        s2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        s2->setContentSize(s2->getContentSize()*1.5);
        
        auto s3 =TileImageView::create("blocks9r.png", Widget::TextureResType::PLIST);
        addChild(s3);
        s3->setPosition(Vec2(s.width/2, s.height/2));
        s3->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        s3->setContentSize(s3->getContentSize()*1.5);
        s3->setFlippedX(true);
        
        auto s4 = TileImageView::create("blocks9cr.png", Widget::TextureResType::PLIST);
        addChild(s4);
        s4->setPosition(Vec2(s.width/2, s.height/2));
        s4->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        s4->setContentSize(s4->getContentSize()*1.5);
        s4->setFlippedX(true);
        
        auto s5 = TileImageView::create("blocks9r.png", Widget::TextureResType::PLIST);
        addChild(s5);
        s5->setPosition(Vec2(s.width/2+s.width/3, s.height/2));
        s5->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        s5->setContentSize(s5->getContentSize()*1.5);
        s5->setFlippedY(true);
        
        auto s6 = TileImageView::create("blocks9cr.png", Widget::TextureResType::PLIST);
        addChild(s6);
        s6->setPosition(Vec2(s.width/2+s.width/3, s.height/2));
        s6->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        s6->setContentSize(s6->getContentSize()*1.5);
        s6->setFlippedY(true);
        return true;
    }
    return false;
}


// UITileImageViewTest
/*
bool UIImageViewTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        Text* alert = Text::create("ImageView", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                 widgetSize.height / 2.0f - alert->getContentSize().height * 1.75f));
        
        _uiLayer->addChild(alert);        
        
        // Create the imageview
        ImageView* imageView = ImageView::create("cocosui/ccicon.png");
        imageView->setPosition(Vec2(widgetSize.width / 2.0f,
                                     widgetSize.height / 2.0f));
        
        _uiLayer->addChild(imageView);
        
        _image = imageView;

        TTFConfig ttfConfig("fonts/arial.ttf", 15);
        auto label1 = Label::createWithTTF(ttfConfig, "Print Resources");
        auto item1 = MenuItemLabel::create(label1, CC_CALLBACK_1(UIImageViewTest::printWidgetResources, this));
        item1->setPosition(Vec2(VisibleRect::left().x + 60, VisibleRect::bottom().y + item1->getContentSize().height * 3));
        auto pMenu1 = Menu::create(item1, nullptr);
        pMenu1->setPosition(Vec2(0, 0));
        this->addChild(pMenu1, 10);
        
        return true;
    }
    return false;
}

void UIImageViewTest::printWidgetResources(cocos2d::Ref* sender)
{
    cocos2d::ResourceData textureFile = _image->getRenderFile();
    CCLOG("textureFile  Name : %s, Type: %d", textureFile.file.c_str(), textureFile.type);
}

// UIImageViewTest_Scale9

bool UIImageViewTest_Scale9::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        Text* alert = Text::create("ImageView scale9 render", "fonts/Marker Felt.ttf", 26);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                 widgetSize.height / 2.0f - alert->getContentSize().height * 2.125f));
        
        _uiLayer->addChild(alert);        
        
        // Create the imageview
        ImageView* imageView = ImageView::create("cocosui/buttonHighlighted.png");
        imageView->setScale9Enabled(true);
        imageView->setContentSize(Size(200, 115));
        imageView->setPosition(Vec2(widgetSize.width / 2.0f - 100,
                                     widgetSize.height / 2.0f));
        
        _uiLayer->addChild(imageView);

        auto imageCopy = imageView->clone();
        imageCopy->setPosition(Vec2(widgetSize.width / 2.0f + 100,
                                    widgetSize.height / 2.0f));
        _uiLayer->addChild(imageCopy);
        
        return true;
    }
    return false;
}

// UIImageViewTest_Scale9_State_Change

bool UIImageViewTest_Scale9_State_Change::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        Text* alert = Text::create("Click The Image", "fonts/Marker Felt.ttf", 26);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
            widgetSize.height / 2.0f - alert->getContentSize().height * 2.125f));

        _uiLayer->addChild(alert);

        // Create the imageview
        ImageView* imageView = ImageView::create("cocosui/ccicon.png");
        imageView->ignoreContentAdaptWithSize(false);
        imageView->setScale9Enabled(true);
        imageView->setContentSize(Size(100, 100));
        imageView->setCapInsets(Rect(20,20,20,20));
        imageView->setPosition(Vec2(widgetSize.width / 2.0f,
            widgetSize.height / 2.0f));

        imageView->setTouchEnabled(true);
        imageView->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type){
            if (type == Widget::TouchEventType::ENDED) {
                if (imageView->isScale9Enabled())
                {
                    imageView->setScale9Enabled(false);
                }
                else
                    imageView->setScale9Enabled(true);
            }
        });

        _uiLayer->addChild(imageView);

        return true;
    }
    return false;
}


// UIImageViewTest_ContentSize

bool UIImageViewTest_ContentSize::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        Text* alert = Text::create("ImageView ContentSize Change", "fonts/Marker Felt.ttf", 26);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f - alert->getContentSize().height * 2.125f));
        
        _uiLayer->addChild(alert);
        
        Text *status = Text::create("child ImageView position percent", "fonts/Marker Felt.ttf", 16);
        status->setColor(Color3B::RED);
        status->setPosition(Vec2(widgetSize.width/2, widgetSize.height/2 + 80));
        _uiLayer->addChild(status,20);
        
        // Create the imageview
        ImageView* imageView = ImageView::create("cocosui/buttonHighlighted.png");
        imageView->setScale9Enabled(true);
        imageView->setContentSize(Size(200, 80));
        imageView->setPosition(Vec2(widgetSize.width / 2.0f,
                                    widgetSize.height / 2.0f ));
       
        
        ImageView* imageViewChild = ImageView::create("cocosui/buttonHighlighted.png");
        imageViewChild->setScale9Enabled(true);
        imageViewChild->setSizeType(Widget::SizeType::PERCENT);
        imageViewChild->setPositionType(Widget::PositionType::PERCENT);
        imageViewChild->setSizePercent(Vec2::ANCHOR_MIDDLE);
        imageViewChild->setPositionPercent(Vec2::ANCHOR_MIDDLE);
        imageViewChild->setPosition(Vec2(widgetSize.width / 2.0f,
                                    widgetSize.height / 2.0f));
        
        ImageView* imageViewChild2 = ImageView::create("cocosui/buttonHighlighted.png");
        imageViewChild2->setScale9Enabled(true);
        imageViewChild2->setSizeType(Widget::SizeType::PERCENT);
        imageViewChild2->setPositionType(Widget::PositionType::PERCENT);
        imageViewChild2->setSizePercent(Vec2::ANCHOR_MIDDLE);
        imageViewChild2->setPositionPercent(Vec2::ANCHOR_MIDDLE);
        imageViewChild->addChild(imageViewChild2);
        
        
        imageView->addChild(imageViewChild);
        
        imageView->setTouchEnabled(true);
        imageView->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type){
            if (type == Widget::TouchEventType::ENDED) {
                float width = CCRANDOM_0_1() * 200 + 50;
                float height = CCRANDOM_0_1() * 80 + 30;
                imageView->setContentSize(Size(width, height));
                
                imageViewChild->setPositionPercent(Vec2(CCRANDOM_0_1(), CCRANDOM_0_1()));
                status->setString(StringUtils::format("child ImageView position percent: %f, %f",
                                                      imageViewChild->getPositionPercent().x, imageViewChild->getPositionPercent().y));
            }
        });
        
        _uiLayer->addChild(imageView);
        
        return true;
    }
    return false;
}


// UIImageViewFlipTest

bool UIImageViewFlipTest::init()
{
    if (UIScene::init())
    {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/blocks9ss.plist");
        Size widgetSize = _widget->getContentSize();
        
        Text* alert = Text::create("ImageView flip test", "fonts/Marker Felt.ttf", 26);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f - alert->getContentSize().height * 2.125f));
        
        _uiLayer->addChild(alert);
        
        // Create the imageview
        ImageView* imageView = ImageView::create("blocks9r.png", Widget::TextureResType::PLIST);
        imageView->setScale9Enabled(true);
        imageView->setContentSize(Size(250, 115));
        imageView->setFlippedX(true);
        imageView->setScale(0.5);
        imageView->ignoreContentAdaptWithSize(false);
        imageView->setPosition(Vec2(widgetSize.width / 2.0f,
                                    widgetSize.height / 2.0f));
        
        _uiLayer->addChild(imageView);
        
        auto toggleButton = Button::create();
        toggleButton->setTitleText("Toggle FlipX");
        toggleButton->setPosition(imageView->getPosition() + Vec2(-50, - imageView->getContentSize().height/2 - 20));
        this->addChild(toggleButton);
        toggleButton->addClickEventListener([=](Ref*){
            imageView->setFlippedX(!imageView->isFlippedX());
        });
        
        auto toggleScale9 = Button::create();
        toggleScale9->setTitleText("Toggle Scale9");
        toggleScale9->setPosition(imageView->getPosition() + Vec2(+50, - imageView->getContentSize().height/2- 20));
        this->addChild(toggleScale9);
        toggleScale9->addClickEventListener([=](Ref*){
            imageView->setScale9Enabled(!imageView->isScale9Enabled());
            //after switching scale9, you must call setContentSize to keep the size not change
             imageView->setContentSize(Size(250, 115));
        });
        
        return true;
    }
    return false;
}


// UIImageViewIssue12249Test

bool UIImageViewIssue12249Test::init()
{
    if (UIScene::init())
    {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/blocks9ss.plist");
        Size widgetSize = _widget->getContentSize();
        
        Text* alert = Text::create("UIImageViewIssue12249Test", "fonts/Marker Felt.ttf", 26);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f - alert->getContentSize().height * 2.125f));
        
        _uiLayer->addChild(alert);
        
        // Create the imageview
        ImageView* imageView = ImageView::create("blocks9r.png", Widget::TextureResType::PLIST);
        imageView->setScale9Enabled(true);
        imageView->setContentSize(Size(250, imageView->getContentSize().height * 2));
        imageView->setFlippedX(true);
        imageView->setScale(0.5);
        imageView->setPosition(Vec2(widgetSize.width / 2.0f - 80,
                                    widgetSize.height / 2.0f));
        
        _uiLayer->addChild(imageView);
        
        ImageView* imageView2 = ImageView::create();
        imageView2->setScale9Enabled(true);
        imageView2->loadTexture("blocks9r.png", Widget::TextureResType::PLIST);
        imageView2->setContentSize(Size(250, imageView2->getContentSize().height * 2));
        imageView2->setFlippedX(true);
        imageView2->setScale(0.5);
        imageView2->setPosition(Vec2(widgetSize.width / 2.0f + 80,
                                    widgetSize.height / 2.0f));
        
        _uiLayer->addChild(imageView2);
        
        
        return true;
    }
    return false;
}
 */

