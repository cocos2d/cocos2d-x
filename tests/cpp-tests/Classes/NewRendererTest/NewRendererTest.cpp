/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "NewRendererTest.h"

USING_NS_CC;

NewRendererTests::NewRendererTests()
{
    ADD_TEST_CASE(NewSpriteTest);
    ADD_TEST_CASE(GroupCommandTest);
    ADD_TEST_CASE(NewClippingNodeTest);
    ADD_TEST_CASE(NewDrawNodeTest);
    ADD_TEST_CASE(NewCullingTest);
    ADD_TEST_CASE(VBOFullTest);
    ADD_TEST_CASE(CaptureScreenTest);
    ADD_TEST_CASE(BugAutoCulling);
    ADD_TEST_CASE(RendererBatchQuadTri);
};

std::string MultiSceneTest::title() const
{
    return "New Renderer";
}

std::string MultiSceneTest::subtitle() const
{
    return "MultiSceneTest";
}

NewSpriteTest::NewSpriteTest()
{
    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesEnded = CC_CALLBACK_2(NewSpriteTest::onTouchesEnded, this);

    createSpriteTest();
    createNewSpriteTest();
}

NewSpriteTest::~NewSpriteTest()
{

}

void NewSpriteTest::createSpriteTest()
{
    Size winSize = Director::getInstance()->getWinSize();

    Sprite* parent = Sprite::create("Images/grossini.png");
    parent->setPosition(winSize.width/4, winSize.height/2);
    Sprite* child1 = Sprite::create("Images/grossinis_sister1.png");
    child1->setPosition(0.0f, -20.0f);
    Sprite* child2 = Sprite::create("Images/grossinis_sister2.png");
    child2->setPosition(20.0f, -20.0f);
    Sprite* child3 = Sprite::create("Images/grossinis_sister1.png");
    child3->setPosition(40.0f, -20.0f);
    Sprite* child4 = Sprite::create("Images/grossinis_sister2.png");
    child4->setPosition(60.0f, -20.0f);
    Sprite* child5 = Sprite::create("Images/grossinis_sister2.png");
    child5->setPosition(80.0f, -20.0f);
    Sprite* child6 = Sprite::create("Images/grossinis_sister2.png");
    child6->setPosition(100.0f, -20.0f);
    Sprite* child7 = Sprite::create("Images/grossinis_sister2.png");
    child7->setPosition(120.0f, -20.0f);

    parent->addChild(child1);
    parent->addChild(child2);
    parent->addChild(child3);
    parent->addChild(child4);
    parent->addChild(child5);
    parent->addChild(child6);
    parent->addChild(child7);
    addChild(parent);
}

void NewSpriteTest::createNewSpriteTest()
{
    Size winSize = Director::getInstance()->getWinSize();

    Sprite* parent = Sprite::create("Images/grossini.png");
    parent->setPosition(winSize.width*2/3, winSize.height/2);
    Sprite* child1 = Sprite::create("Images/grossinis_sister1.png");
    child1->setPosition(0.0f, -20.0f);
    Sprite* child2 = Sprite::create("Images/grossinis_sister2.png");
    child2->setPosition(20.0f, -20.0f);
    Sprite* child3 = Sprite::create("Images/grossinis_sister1.png");
    child3->setPosition(40.0f, -20.0f);
    Sprite* child4 = Sprite::create("Images/grossinis_sister2.png");
    child4->setPosition(60.0f, -20.0f);
    Sprite* child5 = Sprite::create("Images/grossinis_sister2.png");
    child5->setPosition(80.0f, -20.0f);
    Sprite* child6 = Sprite::create("Images/grossinis_sister2.png");
    child6->setPosition(100.0f, -20.0f);
    Sprite* child7 = Sprite::create("Images/grossinis_sister2.png");
    child7->setPosition(120.0f, -20.0f);

    parent->addChild(child1);
    parent->addChild(child2);
    parent->addChild(child3);
    parent->addChild(child4);
    parent->addChild(child5);
    parent->addChild(child6);
    parent->addChild(child7);
    addChild(parent);
}

void NewSpriteTest::onTouchesEnded(const std::vector<Touch *> &touches, Event *event)
{

}

std::string NewSpriteTest::title() const
{
    return "Renderer";
}

std::string NewSpriteTest::subtitle() const
{
    return "SpriteTest";
}

class SpriteInGroupCommand : public Sprite
{
protected:
    GroupCommand _spriteWrapperCommand;
public:
    static SpriteInGroupCommand* create(const std::string& filename);
    
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
};

SpriteInGroupCommand* SpriteInGroupCommand::create(const std::string &filename)
{
    SpriteInGroupCommand* sprite = new (std::nothrow) SpriteInGroupCommand();
    sprite->initWithFile(filename);
    sprite->autorelease();
    return sprite;
}

void SpriteInGroupCommand::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    CCASSERT(renderer, "Render is null");
    _spriteWrapperCommand.init(_globalZOrder);
    renderer->addCommand(&_spriteWrapperCommand);
    renderer->pushGroup(_spriteWrapperCommand.getRenderQueueID());
    Sprite::draw(renderer, transform, flags);
    renderer->popGroup();
}

GroupCommandTest::GroupCommandTest()
{
    auto sprite = SpriteInGroupCommand::create("Images/grossini.png");
    Size winSize = Director::getInstance()->getWinSize();
    sprite->setPosition(winSize.width/2,winSize.height/2);
    addChild(sprite);
}

GroupCommandTest::~GroupCommandTest()
{
}

std::string GroupCommandTest::title() const
{
    return "Renderer";
}

std::string GroupCommandTest::subtitle() const
{
    return "GroupCommandTest: You should see a sprite";
}

NewClippingNodeTest::NewClippingNodeTest()
{
    auto s = Director::getInstance()->getWinSize();

    auto clipper = ClippingNode::create();
    clipper->setTag( kTagClipperNode );
    clipper->setContentSize(  Size(200, 200) );
    clipper->setAnchorPoint(  Vec2(0.5, 0.5) );
    clipper->setPosition( Vec2(s.width / 2, s.height / 2) );

    clipper->runAction(RepeatForever::create(RotateBy::create(1, 45)));
    this->addChild(clipper);

    // TODO: Fix draw node as clip node
//    auto stencil = NewDrawNode::create();
//    Vec2 rectangle[4];
//    rectangle[0] = Vec2(0, 0);
//    rectangle[1] = Vec2(clipper->getContentSize().width, 0);
//    rectangle[2] = Vec2(clipper->getContentSize().width, clipper->getContentSize().height);
//    rectangle[3] = Vec2(0, clipper->getContentSize().height);
//
//    Color4F white(1, 1, 1, 1);
//    stencil->drawPolygon(rectangle, 4, white, 1, white);
//    clipper->setStencil(stencil);

    //Test with alpha Test
    clipper->setAlphaThreshold(0.05f);
    auto stencil = Sprite::create("Images/grossini.png");
    stencil->setPosition(s.width/2, s.height/2);
    clipper->setStencil(stencil);

    auto content = Sprite::create("Images/background2.png");
    content->setTag( kTagContentNode );
    content->setAnchorPoint(  Vec2(0.5, 0.5) );
    content->setPosition( Vec2(clipper->getContentSize().width / 2, clipper->getContentSize().height / 2) );
    clipper->addChild(content);

    _scrolling = false;

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(NewClippingNodeTest::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(NewClippingNodeTest::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(NewClippingNodeTest::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

NewClippingNodeTest::~NewClippingNodeTest()
{

}

std::string NewClippingNodeTest::title() const
{
    return "New Render";
}

std::string NewClippingNodeTest::subtitle() const
{
    return "ClipNode";
}

void NewClippingNodeTest::onTouchesBegan(const std::vector<Touch *> &touches, Event *event)
{
    Touch *touch = touches[0];
    auto clipper = this->getChildByTag(kTagClipperNode);
    Vec2 point = clipper->convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
    auto rect = Rect(0, 0, clipper->getContentSize().width, clipper->getContentSize().height);
    _scrolling = rect.containsPoint(point);
    _lastPoint = point;
}

void NewClippingNodeTest::onTouchesMoved(const std::vector<Touch *> &touches, Event *event)
{
    if (!_scrolling) return;
    Touch *touch = touches[0];
    auto clipper = this->getChildByTag(kTagClipperNode);
    auto point = clipper->convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
    Vec2 diff = point - _lastPoint;
    auto content = clipper->getChildByTag(kTagContentNode);
    content->setPosition(content->getPosition() + diff);
    _lastPoint = point;
}

void NewClippingNodeTest::onTouchesEnded(const std::vector<Touch *> &touches, Event *event)
{
    if (!_scrolling) return;
    _scrolling = false;
}

/**
* NewDrawNode
*/
NewDrawNodeTest::NewDrawNodeTest()
{
    auto s = Director::getInstance()->getWinSize();

    auto parent = Node::create();
    parent->setPosition(s.width/2, s.height/2);
    addChild(parent);

    auto rectNode = DrawNode::create();
    Vec2 rectangle[4];
    rectangle[0] = Vec2(-50, -50);
    rectangle[1] = Vec2(50, -50);
    rectangle[2] = Vec2(50, 50);
    rectangle[3] = Vec2(-50, 50);

    Color4F white(1, 1, 1, 1);
    rectNode->drawPolygon(rectangle, 4, white, 1, white);
    parent->addChild(rectNode);
}

NewDrawNodeTest::~NewDrawNodeTest()
{

}

std::string NewDrawNodeTest::title() const
{
    return "New Render";
}

std::string NewDrawNodeTest::subtitle() const
{
    return "DrawNode";
}

NewCullingTest::NewCullingTest()
{
    Size size = Director::getInstance()->getWinSize();
    auto sprite = Sprite::create("Images/btn-about-normal-vertical.png");
    sprite->setRotation(5);
    sprite->setPosition(Vec2(size.width/2,size.height/3));
    sprite->setScale(2);
    addChild(sprite);

    auto sprite2 = Sprite::create("Images/btn-about-normal-vertical.png");
    sprite2->setRotation(-85);
    sprite2->setPosition(Vec2(size.width/2,size.height * 2/3));
    sprite2->setScale(2);
    addChild(sprite2);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(NewCullingTest::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(NewCullingTest::onTouchMoved, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
}

bool NewCullingTest::onTouchBegan(Touch* touch, Event  *event)
{
    auto pos = touch->getLocation();
    _lastPos = pos;
    return true;
}

void NewCullingTest::onTouchMoved(Touch* touch, Event  *event)
{    
    auto pos = touch->getLocation();
    
    auto offset = pos - _lastPos;
    
    auto layerPos = getPosition();
    auto newPos = layerPos + offset;
    
    setPosition(newPos);
    _lastPos = pos;
}

NewCullingTest::~NewCullingTest()
{
    
}

std::string NewCullingTest::title() const
{
    return "New Render";
}

std::string NewCullingTest::subtitle() const
{
    return "Drag the layer to test the result of culling";
}

VBOFullTest::VBOFullTest()
{
    Size s = Director::getInstance()->getWinSize();
    Node* parent = Node::create();
    parent->setPosition(0,0);
    addChild(parent);
    
    for (int i=0; i< Renderer::VBO_SIZE / 3.9; ++i)
    {
        Sprite* sprite = Sprite::create("Images/grossini_dance_01.png");
        sprite->setScale(0.1f, 0.1f);
        float x = ((float)std::rand()) /RAND_MAX;
        float y = ((float)std::rand()) /RAND_MAX;
        sprite->setPosition(Vec2(x * s.width, y * s.height));
        parent->addChild(sprite);
    }
}

VBOFullTest::~VBOFullTest()
{
    
}

std::string VBOFullTest::title() const
{
    return "New Renderer";
}

std::string VBOFullTest::subtitle() const
{
    return "VBO full Test, everthing should render normally";
}

CaptureScreenTest::CaptureScreenTest()
{
    Size s = Director::getInstance()->getWinSize();
    Vec2 left(s.width / 4, s.height / 2);
    Vec2 right(s.width / 4 * 3, s.height / 2);
	
    auto sp1 = Sprite::create("Images/grossini.png");
    sp1->setPosition(left);
    auto move1 = MoveBy::create(1, Vec2(s.width/2, 0));
    auto seq1 = RepeatForever::create(Sequence::create(move1, move1->reverse(), nullptr));
    addChild(sp1);
    sp1->runAction(seq1);
    auto sp2 = Sprite::create("Images/grossinis_sister1.png");
    sp2->setPosition(right);
    auto move2 = MoveBy::create(1, Vec2(-s.width/2, 0));
    auto seq2 = RepeatForever::create(Sequence::create(move2, move2->reverse(), nullptr));
    addChild(sp2);
    sp2->runAction(seq2);

    auto label1 = Label::createWithTTF(TTFConfig("fonts/arial.ttf"), "capture all");
    auto mi1 = MenuItemLabel::create(label1, CC_CALLBACK_1(CaptureScreenTest::onCaptured, this));
    auto menu = Menu::create(mi1, nullptr);
    addChild(menu);
    menu->setPosition(s.width / 2, s.height / 4);

    _filename = "";
}

CaptureScreenTest::~CaptureScreenTest()
{
    Director::getInstance()->getTextureCache()->removeTextureForKey(_filename);
}

std::string CaptureScreenTest::title() const
{
    return "New Renderer";
}

std::string CaptureScreenTest::subtitle() const
{
    return "Capture screen test, press the menu items to capture the screen";
}

void CaptureScreenTest::onCaptured(Ref*)
{
    Director::getInstance()->getTextureCache()->removeTextureForKey(_filename);
    removeChildByTag(childTag);
    _filename = "CaptureScreenTest.png";
    utils::captureScreen(CC_CALLBACK_2(CaptureScreenTest::afterCaptured, this), _filename);
}

void CaptureScreenTest::afterCaptured(bool succeed, const std::string& outputFile)
{
    if (succeed)
    {
        auto sp = Sprite::create(outputFile);
        addChild(sp, 0, childTag);
        Size s = Director::getInstance()->getWinSize();
        sp->setPosition(s.width / 2, s.height / 2);
        sp->setScale(0.25);
        _filename = outputFile;
    }
    else
    {
        log("Capture screen failed.");
    }
}

BugAutoCulling::BugAutoCulling()
{
    Size s = Director::getInstance()->getWinSize();
    auto fastmap = cocos2d::experimental::TMXTiledMap::create("TileMaps/orthogonal-test2.tmx");
    this->addChild(fastmap);
    for (int i = 0; i < 30; i++) {
        auto sprite = Sprite::create("Images/grossini.png");
        sprite->setPosition(s.width/2 + s.width/10 * i, s.height/2);
        this->addChild(sprite);
        auto label = Label::createWithTTF(TTFConfig("fonts/arial.ttf"), "Label");
        label->setPosition(s.width/2 + s.width/10 * i, s.height/2);
        this->addChild(label);
    }
    this->scheduleOnce([=](float){
        auto camera = Director::getInstance()->getRunningScene()->getCameras().front();
        auto move  = MoveBy::create(2.0, Vec2(2 * s.width, 0));
        camera->runAction(Sequence::create(move, move->reverse(),nullptr));
    }, 1.0f, "lambda-autoculling-bug");
}

std::string BugAutoCulling::title() const
{
    return "Bug-AutoCulling";
}

std::string BugAutoCulling::subtitle() const
{
    return "Moving the camera to the right instead of moving the layer";
}

//
// RendererBatchQuadTri
//

RendererBatchQuadTri::RendererBatchQuadTri()
{
    Size s = Director::getInstance()->getWinSize();

    for (int i=0; i<250; i++)
    {
        int x = CCRANDOM_0_1() * s.width;
        int y = CCRANDOM_0_1() * s.height;

        auto label = LabelAtlas::create("This is a label", "fonts/tuffy_bold_italic-charmap.plist");
        label->setColor(Color3B::RED);
        label->setPosition(Vec2(x,y));
        addChild(label);

        auto sprite = Sprite::create("fonts/tuffy_bold_italic-charmap.png");
        sprite->setTextureRect(Rect(0,0,100,100));
        sprite->setPosition(Vec2(x,y));
        sprite->setColor(Color3B::BLUE);
        addChild(sprite);
    }
}

std::string RendererBatchQuadTri::title() const
{
    return "RendererBatchQuadTri";
}

std::string RendererBatchQuadTri::subtitle() const
{
    return "QuadCommand and TriangleCommands are batched together";
}