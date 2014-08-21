/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011      Zynga Inc.
 Copyright (c) 2013      Surith Thekkiam

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

#include "Scale9SpriteTest.h"
#include "testResource.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC_EXT;

static std::function<Layer*()> createFunctions[] = {
    CL(S9BatchNodeBasic),
    CL(S9FrameNameSpriteSheet),
    CL(S9FrameNameSpriteSheetRotated),
    CL(S9BatchNodeScaledNoInsets),
    CL(S9FrameNameSpriteSheetScaledNoInsets),
    CL(S9FrameNameSpriteSheetRotatedScaledNoInsets),
    CL(S9BatchNodeScaleWithCapInsets),
    CL(S9FrameNameSpriteSheetInsets),
    CL(S9FrameNameSpriteSheetInsetsScaled),
    CL(S9FrameNameSpriteSheetRotatedInsets),
    CL(S9_TexturePacker),
    CL(S9FrameNameSpriteSheetRotatedInsetsScaled),
    CL(S9FrameNameSpriteSheetRotatedSetCapInsetLater),
    CL(S9CascadeOpacityAndColor),
    CL(S9ZOrder),
    CL(S9Flip)
};

static int sceneIdx=-1;
#define MAX_LAYER (sizeof(createFunctions) / sizeof(createFunctions[0]))

static Layer* nextAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;
    
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

static Layer* backAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;
    
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

static Layer* restartAction()
{
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

void S9SpriteTestScene::runThisTest()
{
    sceneIdx = -1;
    addChild(nextAction());
    
    Director::getInstance()->replaceScene(this);
}

//------------------------------------------------------------------
//
// S9SpriteTestDemo
//
//------------------------------------------------------------------

void S9SpriteTestDemo::onEnter()
{
    BaseTest::onEnter();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_blocks9_plist);
    CCLOG("sprite frames added to sprite frame cache...");
}

void S9SpriteTestDemo::restartCallback(Ref* sender)
{
    auto s = new S9SpriteTestScene();
    s->addChild( restartAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void S9SpriteTestDemo::nextCallback(Ref* sender)
{
    auto s = new S9SpriteTestScene();
    s->addChild( nextAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void S9SpriteTestDemo::backCallback(Ref* sender)
{
    auto s = new S9SpriteTestScene();
    s->addChild( backAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}


// S9BatchNodeBasic

void S9BatchNodeBasic::onEnter()
{
    S9SpriteTestDemo::onEnter();
    auto winSize = Director::getInstance()->getWinSize();
    float x = winSize.width / 2;
    float y = 0 + (winSize.height / 2);
    
    log("S9BatchNodeBasic ...");
    
    auto batchNode = SpriteBatchNode::create("Images/blocks9.png");
    log("batchNode created with : Images/blocks9.png");
    
    auto blocks = Scale9Sprite::create();
    log("... created");
    
    blocks->updateWithBatchNode(batchNode, Rect(0, 0, 96, 96), false, Rect(0, 0, 96, 96));
    log("... updateWithBatchNode");
    
    blocks->setPosition(Vec2(x, y));
    log("... setPosition");
    
    this->addChild(blocks);
    log("this->addChild");
    
    log("... S9BatchNodeBasic done.");
}

std::string S9BatchNodeBasic::title() const
{
    return "Scale9Sprite created empty and updated from SpriteBatchNode";
}

std::string S9BatchNodeBasic::subtitle() const
{
    return "updateWithBatchNode(); capInsets=full size";
}


// S9FrameNameSpriteSheet

void S9FrameNameSpriteSheet::onEnter()
{
    S9SpriteTestDemo::onEnter();
    auto winSize = Director::getInstance()->getWinSize();
    float x = winSize.width / 2;
    float y = 0 + (winSize.height / 2);

    log("S9FrameNameSpriteSheet ...");

    auto blocks = Scale9Sprite::createWithSpriteFrameName("blocks9.png");
    log("... created");

    blocks->setPosition(Vec2(x, y));
    log("... setPosition");

    this->addChild(blocks);
    log("this->addChild");

    log("... S9FrameNameSpriteSheet done.");
}

std::string S9FrameNameSpriteSheet::title() const
{
    return "Scale9Sprite from sprite sheet";
}

std::string S9FrameNameSpriteSheet::subtitle() const
{
    return "createWithSpriteFrameName(); default cap insets";
}

//
//// S9FrameNameSpriteSheetRotated
//
void S9FrameNameSpriteSheetRotated::onEnter()
{
    S9SpriteTestDemo::onEnter();
    auto winSize = Director::getInstance()->getWinSize();
    float x = winSize.width / 2;
    float y = 0 + (winSize.height / 2);

    log("S9FrameNameSpriteSheetRotated ...");

    auto blocks = Scale9Sprite::createWithSpriteFrameName("blocks9r.png");
    log("... created");

    blocks->setPosition(Vec2(x, y));
    log("... setPosition");

    this->addChild(blocks);
    log("this->addChild");

    log("... S9FrameNameSpriteSheetRotated done.");
}

std::string S9FrameNameSpriteSheetRotated::title() const
{
    return "Scale9Sprite from sprite sheet (stored rotated)";
}

std::string S9FrameNameSpriteSheetRotated::subtitle() const
{
    return "createWithSpriteFrameName(); default cap insets";
}

//
//// S9BatchNodeScaledNoInsets
//

void S9BatchNodeScaledNoInsets::onEnter()
{
    S9SpriteTestDemo::onEnter();
    auto winSize = Director::getInstance()->getWinSize();
    float x = winSize.width / 2;
    float y = 0 + (winSize.height / 2);

    log("S9BatchNodeScaledNoInsets ...");

    // scaled without insets
    auto batchNode_scaled = SpriteBatchNode::create("Images/blocks9.png");
    log("batchNode_scaled created with : Images/blocks9.png");

    auto blocks_scaled = Scale9Sprite::create();
    log("... created");
    blocks_scaled->updateWithBatchNode(batchNode_scaled, Rect(0, 0, 96, 96), false, Rect(0, 0, 96, 96));
    log("... updateWithBatchNode");

    blocks_scaled->setPosition(Vec2(x, y));
    log("... setPosition");

    blocks_scaled->setContentSize(Size(96 * 4, 96*2));
    log("... setContentSize");

    this->addChild(blocks_scaled);
    log("this->addChild");

    log("... S9BtchNodeScaledNoInsets done.");
}

std::string S9BatchNodeScaledNoInsets::title() const
{
    return "Scale9Sprite created empty and updated from SpriteBatchNode";
}

std::string S9BatchNodeScaledNoInsets::subtitle() const
{
    return "updateWithBatchNode(); capInsets=full size; rendered 4 X width, 2 X height";
}

//
//// S9FrameNameSpriteSheetScaledNoInsets
//

void S9FrameNameSpriteSheetScaledNoInsets::onEnter()
{
    S9SpriteTestDemo::onEnter();
    auto winSize = Director::getInstance()->getWinSize();
    float x = winSize.width / 2;
    float y = 0 + (winSize.height / 2);

    log("S9FrameNameSpriteSheetScaledNoInsets ...");

    auto blocks_scaled = Scale9Sprite::createWithSpriteFrameName("blocks9.png");
    log("... created");

    blocks_scaled->setPosition(Vec2(x, y));
    log("... setPosition");

    blocks_scaled->setContentSize(Size(96 * 4, 96*2));
    log("... setContentSize");

    this->addChild(blocks_scaled);
    log("this->addChild");

    log("... S9FrameNameSpriteSheetScaledNoInsets done.");
}

std::string S9FrameNameSpriteSheetScaledNoInsets::title() const
{
    return "Scale9Sprite from sprite sheet";
}

std::string S9FrameNameSpriteSheetScaledNoInsets::subtitle() const
{
    return "createWithSpriteFrameName(); default cap insets; rendered 4 X width, 2 X height";
}


//
//// S9FrameNameSpriteSheetRotatedScaledNoInsets
//

void S9FrameNameSpriteSheetRotatedScaledNoInsets::onEnter()
{
    S9SpriteTestDemo::onEnter();
    auto winSize = Director::getInstance()->getWinSize();
    float x = winSize.width / 2;
    float y = 0 + (winSize.height / 2);

    log("S9FrameNameSpriteSheetRotatedScaledNoInsets ...");

    auto blocks_scaled = Scale9Sprite::createWithSpriteFrameName("blocks9r.png");
    log("... created");

    blocks_scaled->setPosition(Vec2(x, y));
    log("... setPosition");

    blocks_scaled->setContentSize(Size(96 * 4, 96*2));
    log("... setContentSize");

    this->addChild(blocks_scaled);
    log("this->addChild");

    log("... S9FrameNameSpriteSheetRotatedScaledNoInsets done.");
}

std::string S9FrameNameSpriteSheetRotatedScaledNoInsets::title() const
{
    return "Scale9Sprite from sprite sheet (stored rotated)";
}

std::string S9FrameNameSpriteSheetRotatedScaledNoInsets::subtitle() const
{
    return "createWithSpriteFrameName(); default cap insets; rendered 4 X width, 2 X height";
}

//
//
//// S9BatchNodeScaleWithCapInsets
//

void S9BatchNodeScaleWithCapInsets::onEnter()
{
    S9SpriteTestDemo::onEnter();
    auto winSize = Director::getInstance()->getWinSize();
    float x = winSize.width / 2;
    float y = 0 + (winSize.height / 2);

    log("S9BatchNodeScaleWithCapInsets ...");

    auto batchNode_scaled_with_insets = SpriteBatchNode::create("Images/blocks9.png");
    log("batchNode_scaled_with_insets created with : Images/blocks9.png");

    auto blocks_scaled_with_insets = Scale9Sprite::create();
    log("... created");

    blocks_scaled_with_insets->updateWithBatchNode(batchNode_scaled_with_insets, Rect(0, 0, 96, 96), false, Rect(32, 32, 32, 32));
    log("... updateWithBatchNode");

    blocks_scaled_with_insets->setContentSize(Size(96 * 4.5, 96 * 2.5));
    log("... setContentSize");

    blocks_scaled_with_insets->setPosition(Vec2(x, y));
    log("... setPosition");

    this->addChild(blocks_scaled_with_insets);
    log("this->addChild");

    log("... S9BatchNodeScaleWithCapInsets done.");
}

std::string S9BatchNodeScaleWithCapInsets::title() const
{
    return "Scale9Sprite created empty and updated from SpriteBatchNode";
}

std::string S9BatchNodeScaleWithCapInsets::subtitle() const
{
    return "updateWithBatchNode(); capInsets=(32, 32, 32, 32)";
}

//
//// S9FrameNameSpriteSheetInsets
//

void S9FrameNameSpriteSheetInsets::onEnter()
{
    S9SpriteTestDemo::onEnter();
    auto winSize = Director::getInstance()->getWinSize();
    float x = winSize.width / 2;
    float y = 0 + (winSize.height / 2);

    log("S9FrameNameSpriteSheetInsets ...");

    auto blocks_with_insets = Scale9Sprite::createWithSpriteFrameName("blocks9.png", Rect(32, 32, 32, 32));
    log("... created");

    blocks_with_insets->setPosition(Vec2(x, y));
    log("... setPosition");

    this->addChild(blocks_with_insets);
    log("this->addChild");

    log("... S9FrameNameSpriteSheetInsets done.");
}

std::string S9FrameNameSpriteSheetInsets::title() const
{
    return "Scale9Sprite scaled with insets sprite sheet";
}

std::string S9FrameNameSpriteSheetInsets::subtitle() const
{
    return "createWithSpriteFrameName(); cap insets=(32, 32, 32, 32)";
}

//
//// S9FrameNameSpriteSheetInsetsScaled
//
void S9FrameNameSpriteSheetInsetsScaled::onEnter()
{
    S9SpriteTestDemo::onEnter();
    auto winSize = Director::getInstance()->getWinSize();
    float x = winSize.width / 2;
    float y = 0 + (winSize.height / 2);

    log("S9FrameNameSpriteSheetInsetsScaled ...");

    auto blocks_scaled_with_insets = Scale9Sprite::createWithSpriteFrameName("blocks9.png", Rect(32, 32, 32, 32));
    log("... created");

    blocks_scaled_with_insets->setContentSize(Size(96 * 4.5, 96 * 2.5));
    log("... setContentSize");

    blocks_scaled_with_insets->setPosition(Vec2(x, y));
    log("... setPosition");

    this->addChild(blocks_scaled_with_insets);
    log("this->addChild");

    log("... S9FrameNameSpriteSheetInsetsScaled done.");
}

std::string S9FrameNameSpriteSheetInsetsScaled::title() const
{
    return "Scale9Sprite scaled with insets sprite sheet";
}

std::string S9FrameNameSpriteSheetInsetsScaled::subtitle() const
{
    return "createWithSpriteFrameName(); default cap insets; rendered scaled 4.5 X width, 2.5 X height";
}

//// S9FrameNameSpriteSheetRotatedInsets
//

void S9FrameNameSpriteSheetRotatedInsets::onEnter()
{
    S9SpriteTestDemo::onEnter();
    auto winSize = Director::getInstance()->getWinSize();
    float x = winSize.width / 2;
    float y = 0 + (winSize.height / 2);

    log("S9FrameNameSpriteSheetRotatedInsets ...");

    auto blocks_with_insets = Scale9Sprite::createWithSpriteFrameName("blocks9r.png", Rect(32, 32, 32, 32));
    log("... created");

    blocks_with_insets->setPosition(Vec2(x, y));
    log("... setPosition");

    this->addChild(blocks_with_insets);
    log("this->addChild");

    log("... S9FrameNameSpriteSheetRotatedInsets done.");
}

std::string S9FrameNameSpriteSheetRotatedInsets::title() const
{
    return "Scale9Sprite scaled with insets sprite sheet (stored rotated)";
}

std::string S9FrameNameSpriteSheetRotatedInsets::subtitle() const
{
    return "createWithSpriteFrameName(); cap insets=(32, 32, 32, 32)";
}

//
//// S9_TexturePacker
//

void S9_TexturePacker::onEnter()
{
    S9SpriteTestDemo::onEnter();
    auto winSize = Director::getInstance()->getWinSize();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_ui_plist);

    float x = winSize.width / 4;
    float y = 0 + (winSize.height / 2);

    log("S9_TexturePacker ...");

    auto s = Scale9Sprite::createWithSpriteFrameName("button_normal.png");
    log("... created");

    s->setPosition(Vec2(x, y));
    log("... setPosition");

    s->setContentSize(Size(14 * 16, 10 * 16));
    log("... setContentSize");

    this->addChild(s);
    log("this->addChild");

    x = winSize.width * 3/4;

    auto s2 = Scale9Sprite::createWithSpriteFrameName("button_actived.png");
    log("... created");

    s2->setPosition(Vec2(x, y));
    log("... setPosition");

    s2->setContentSize(Size(14 * 16, 10 * 16));
    log("... setContentSize");

    this->addChild(s2);
    log("this->addChild");

    log("... S9_TexturePacker done.");
}

std::string S9_TexturePacker::title() const
{
    return "Scale9Sprite from a spritesheet created with TexturePacker";
}

std::string S9_TexturePacker::subtitle() const
{
    return "createWithSpriteFrameName('button_normal.png');createWithSpriteFrameName('button_actived.png');";
}

//
//// S9FrameNameSpriteSheetRotatedInsetsScaled
//

void S9FrameNameSpriteSheetRotatedInsetsScaled::onEnter()
{
    S9SpriteTestDemo::onEnter();
    auto winSize = Director::getInstance()->getWinSize();
    float x = winSize.width / 2;
    float y = 0 + (winSize.height / 2);

    log("S9FrameNameSpriteSheetRotatedInsetsScaled ...");

    auto blocks_scaled_with_insets = Scale9Sprite::createWithSpriteFrameName("blocks9.png", Rect(32, 32, 32, 32));
    log("... created");

    blocks_scaled_with_insets->setContentSize(Size(96 * 4.5, 96 * 2.5));
    log("... setContentSize");

    blocks_scaled_with_insets->setPosition(Vec2(x, y));
    log("... setPosition");

    this->addChild(blocks_scaled_with_insets);
    log("this->addChild");

    log("... S9FrameNameSpriteSheetRotatedInsetsScaled done.");
}

std::string S9FrameNameSpriteSheetRotatedInsetsScaled::title() const
{
    return "Scale9Sprite scaled with insets sprite sheet (stored rotated)";
}

std::string S9FrameNameSpriteSheetRotatedInsetsScaled::subtitle() const
{
    return "createWithSpriteFrameName(); default cap insets; rendered scaled 4.5 X width, 2.5 X height";
}

//
//// Scale9FrameNameSpriteSheetRotatedSetCapInsetLater
//

void S9FrameNameSpriteSheetRotatedSetCapInsetLater::onEnter()
{
    S9SpriteTestDemo::onEnter();
    auto winSize = Director::getInstance()->getWinSize();
    float x = winSize.width / 2;
    float y = 0 + (winSize.height / 2);
    
    log("Scale9FrameNameSpriteSheetRotatedSetCapInsetLater ...");
    
    auto blocks_scaled_with_insets = Scale9Sprite::createWithSpriteFrameName("blocks9r.png");
    log("... created");
    
    blocks_scaled_with_insets->setInsetLeft(32);
    blocks_scaled_with_insets->setInsetRight(32);

    blocks_scaled_with_insets->setPreferredSize(Size(32*5.5f, 32*4));
    blocks_scaled_with_insets->setPosition(Vec2(x, y));
    log("... setPosition");
    
    this->addChild(blocks_scaled_with_insets);
    log("this->addChild");
    
    log("... Scale9FrameNameSpriteSheetRotatedSetCapInsetLater done.");
}

std::string S9FrameNameSpriteSheetRotatedSetCapInsetLater::title() const
{
    return "Scale9Sprite from sprite sheet (stored rotated), with setting CapInset later";
}

std::string S9FrameNameSpriteSheetRotatedSetCapInsetLater::subtitle() const
{
    return "createWithSpriteFrameName(); setInsetLeft(32); setInsetRight(32);";
}

//
//// S9CascadeOpacityAndColor
//

void S9CascadeOpacityAndColor::onEnter()
{
    S9SpriteTestDemo::onEnter();
    auto winSize = Director::getInstance()->getWinSize();
    float x = winSize.width / 2;
    float y = 0 + (winSize.height / 2);
    auto rgba = Layer::create();
    rgba->setCascadeColorEnabled(true);
    rgba->setCascadeOpacityEnabled(true);
    this->addChild(rgba);
    
    log("S9CascadeOpacityAndColor ...");
    
    auto blocks_scaled_with_insets = Scale9Sprite::createWithSpriteFrameName("blocks9r.png");
    log("... created");
    
    blocks_scaled_with_insets->setPosition(Vec2(x, y));
    log("... setPosition");
    
    rgba->addChild(blocks_scaled_with_insets);
    auto actions = Sequence::create(FadeIn::create(1),
                                         TintTo::create(1, 0, 255, 0),
                                         TintTo::create(1, 255, 255, 255),
                                         FadeOut::create(1),
                                         nullptr);
    auto repeat = RepeatForever::create(actions);
    rgba->runAction(repeat);
    log("this->addChild");
    
    log("... S9CascadeOpacityAndColor done.");
}

std::string S9CascadeOpacityAndColor::title() const
{
    return "Scale9Sprite and a Layer parent with setCascadeOpacityEnable(true) and setCascadeColorEnable(true)";
}

std::string S9CascadeOpacityAndColor::subtitle() const
{
    return "when parent change color/opacity, Scale9Sprite should also change";
}

//
//// S9ZOrder
//

void S9ZOrder::onEnter()
{
    S9SpriteTestDemo::onEnter();
    auto winSize = Director::getInstance()->getWinSize();
    float x = winSize.width / 2;
    float y = 0 + (winSize.height / 2);
  
    auto blocks_scaled_with_insets = Scale9Sprite::createWithSpriteFrameName("blocks9r.png");
    
    blocks_scaled_with_insets->setPosition(Vec2(x, y));
    this->addChild(blocks_scaled_with_insets);
    
    Sprite *normalSprite = Sprite::createWithSpriteFrameName("blocks9r.png");
    normalSprite->setColor(Color3B::RED);
    blocks_scaled_with_insets->addChild(normalSprite);
    
    auto topLabel = Label::createWithSystemFont("I Must be On the Top", "Arial", 15);
    topLabel->setPosition(Vec2(20,20));
    blocks_scaled_with_insets->addChild(topLabel);
    
    auto bottomLabel = Label::createWithSystemFont("I Must be On the Bottom", "Arial", 15);
    bottomLabel->setPosition(Vec2(80,80));
    bottomLabel->setColor(Color3B::BLUE);
    blocks_scaled_with_insets->addChild(bottomLabel,-1);
    
}

std::string S9ZOrder::title() const
{
    return "Scale9Sprite ZOrder issue";
}

std::string S9ZOrder::subtitle() const
{
    return "When adding nodes to Scale9Sprite, it should be added on top itself";
}

//
//// S9Flip
//

void S9Flip::onEnter()
{
    S9SpriteTestDemo::onEnter();
    auto winSize = Director::getInstance()->getWinSize();
    float x = winSize.width / 2;
    float y = 0 + (winSize.height / 2);
    
    
    auto normalSprite = Scale9Sprite::createWithSpriteFrameName("blocks9r.png");
    
    normalSprite->setPosition(Vec2(x, y ));
    this->addChild(normalSprite);
    
    
    auto normalLabel = Label::createWithSystemFont("Normal Sprite","Airal",10);
    normalLabel->setPosition(normalSprite->getPosition() + Vec2(0, normalSprite->getContentSize().height/2 + 10));
    this->addChild(normalLabel);
    
    
    
    auto flipXSprite = Scale9Sprite::createWithSpriteFrameName("blocks9r.png");
    
    flipXSprite->setPosition(Vec2(x - 120, y ));
    this->addChild(flipXSprite);
    
    flipXSprite->setScaleX(-1);
    
    auto flipXLabel = Label::createWithSystemFont("Sprite FlipX","Airal",10);
    flipXLabel->setPosition(flipXSprite->getPosition() + Vec2(0, flipXSprite->getContentSize().height/2 + 10));
    this->addChild(flipXLabel);
    
    
    auto flipYSprite = Scale9Sprite::createWithSpriteFrameName("blocks9r.png");
    
    flipYSprite->setPosition(Vec2(x + 120, y));
    this->addChild(flipYSprite);
    
    flipYSprite->setScaleY(-1);

    auto flipYLabel = Label::createWithSystemFont("Sprite FlipY","Airal",10);
    flipYLabel->setPosition(flipYSprite->getPosition() + Vec2(0, flipYSprite->getContentSize().height/2 + 10));
    this->addChild(flipYLabel);

    
}

std::string S9Flip::title() const
{
    return "Scale9Sprite Flip issue";
}

std::string S9Flip::subtitle() const
{
    return "When Flipped, the scale9Sprite should behavior like a normal node";
}
