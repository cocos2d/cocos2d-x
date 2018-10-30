/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "ParallaxTest.h"
#include "../testResource.h"

USING_NS_CC;

enum 
{
    kTagNode,
    kTagGrossini,
};

ParallaxTests::ParallaxTests()
{
    ADD_TEST_CASE(Parallax1);
    ADD_TEST_CASE(Parallax2);
    ADD_TEST_CASE(Issue2572);
}

//------------------------------------------------------------------
//
// Parallax1
//
//------------------------------------------------------------------

Parallax1::Parallax1()
{
    // Top Layer, a simple image
    auto cocosImage = Sprite::create(s_Power);
    // scale the image (optional)
    cocosImage->setScale( 2.5f );
    // change the transform anchor point to 0,0 (optional)
    cocosImage->setAnchorPoint( Vec2(0,0) );
    

    // Middle layer: a Tile map atlas
    auto tilemap = TileMapAtlas::create(s_TilesPng, s_LevelMapTga, 16, 16);
    tilemap->releaseMap();
    
    // change the transform anchor to 0,0 (optional)
    tilemap->setAnchorPoint( Vec2(0, 0) );

    // Anti Aliased images
    tilemap->getTexture()->setAntiAliasTexParameters();
    

    // background layer: another image
    auto background = Sprite::create(s_back);
    // scale the image (optional)
    background->setScale( 1.5f );
    // change the transform anchor point (optional)
    background->setAnchorPoint( Vec2(0,0) );

    
    // create a void node, a parent node
    auto voidNode = ParallaxNode::create();
    
    // NOW add the 3 layers to the 'void' node

    // background image is moved at a ratio of 0.4x, 0.5y
    voidNode->addChild(background, -1, Vec2(0.4f,0.5f), Vec2::ZERO);
    
    // tiles are moved at a ratio of 2.2x, 1.0y
    voidNode->addChild(tilemap, 1, Vec2(2.2f,1.0f), Vec2(0,-200) );
    
    // top image is moved at a ratio of 3.0x, 2.5y
    voidNode->addChild(cocosImage, 2, Vec2(3.0f,2.5f), Vec2(200,800) );
    
    
    // now create some actions that will move the 'void' node
    // and the children of the 'void' node will move at different
    // speed, thus, simulation the 3D environment
    auto goUp = MoveBy::create(4, Vec2(0,-500) );
    auto goDown = goUp->reverse();
    auto go = MoveBy::create(8, Vec2(-1000,0) );
    auto goBack = go->reverse();
    auto seq = Sequence::create(goUp, go, goDown, goBack, nullptr);
    voidNode->runAction( (RepeatForever::create(seq) ));
    
    addChild( voidNode );
}

std::string Parallax1::title() const
{
    return "Parallax: parent and 3 children";
}

//------------------------------------------------------------------
//
// Parallax2
//
//------------------------------------------------------------------

Parallax2::Parallax2()
{
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesMoved = CC_CALLBACK_2(Parallax2::onTouchesMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    // Top Layer, a simple image
    auto cocosImage = Sprite::create(s_Power);
    // scale the image (optional)
    cocosImage->setScale( 2.5f );
    // change the transform anchor point to 0,0 (optional)
    cocosImage->setAnchorPoint( Vec2(0,0) );
    
    
    // Middle layer: a Tile map atlas
    auto tilemap = TileMapAtlas::create(s_TilesPng, s_LevelMapTga, 16, 16);
    tilemap->releaseMap();
    
    // change the transform anchor to 0,0 (optional)
    tilemap->setAnchorPoint( Vec2(0, 0) );
    
    // Anti Aliased images
    tilemap->getTexture()->setAntiAliasTexParameters();
    
    
    // background layer: another image
    auto background = Sprite::create(s_back);
    // scale the image (optional)
    background->setScale( 1.5f );
    // change the transform anchor point (optional)
    background->setAnchorPoint( Vec2(0,0) );
    
    
    // create a void node, a parent node
    auto voidNode = ParallaxNode::create();
    
    // NOW add the 3 layers to the 'void' node
    
    // background image is moved at a ratio of 0.4x, 0.5y
    voidNode->addChild(background, -1, Vec2(0.4f,0.5f), Vec2::ZERO);
    
    // tiles are moved at a ratio of 1.0, 1.0y
    voidNode->addChild(tilemap, 1, Vec2(1.0f,1.0f), Vec2(0,-200) );
    
    // top image is moved at a ratio of 3.0x, 2.5y
    voidNode->addChild( cocosImage, 2, Vec2(3.0f,2.5f), Vec2(200,1000) );
    addChild(voidNode, 0, kTagNode);
}

void Parallax2::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event)
{
    auto diff = touches[0]->getDelta();
    
    auto node = getChildByTag(kTagNode);
    auto currentPos = node->getPosition();
    node->setPosition(currentPos + diff);
}

std::string Parallax2::title() const
{
    return "Parallax: drag screen";
}

//------------------------------------------------------------------
//
// Issue2572
//
//------------------------------------------------------------------
Issue2572::Issue2572()
: _moveTimer(0.0f)
, _addTimer(0.0f)
, _preListSize(0)
, _printCount(0)
{
    _addChildStep = 1.0f;
    _wholeMoveTime = 3.0f;
    _wholeMoveSize = Vec2(-300, 0);
    
    // create a parallax node, a parent node
    _paraNode = ParallaxNode::create();
    addChild(_paraNode, 0, kTagNode);

    this->scheduleUpdate();
}

void Issue2572::update(float dt)
{
    _addTimer += dt;
    _moveTimer += dt;
    if (_moveTimer >= _wholeMoveTime) {
        this->unscheduleUpdate();
        return;
    }

    _paraNode->setPosition(_paraNode->getPosition() + _wholeMoveSize * dt / _wholeMoveTime);
    
    if (_addTimer >= _addChildStep) {
        _addTimer = 0.0f;
        
        auto child = Sprite::create("Images/Icon.png");
        Size viewSize = Director::getInstance()->getVisibleSize();
        Vec2 offset = Vec2(viewSize.width / 2, viewSize.height/2);
        _paraNode->addChild(child, 1, Vec2( 1, 0 ), offset );
        
        _childList.pushBack(child);
    }

    // After a child added, output the position of the children 3 times.
    // Bug : The first output is much different with the second one & the third one.
    if (_childList.size() != _preListSize) {
        switch (_printCount) {
            case 0:
            case 1:
            case 2:
                log( "--child count-- %zd", _childList.size());
                for (const auto& obj : _childList)
                {
                    Sprite* obstacle = dynamic_cast<Sprite*>( obj );
                    log("child position : (%.2f, %.2f)", obstacle->getPositionX(), obstacle->getPositionY());
                }
                log("-------------------");
                _printCount++;
                break;
            case 3:
                _preListSize = _childList.size();
                _printCount = 0;
                break;
            default:
                break;
        }
    }
}

std::string Issue2572::title() const
{
    return "Issue 2572";
}

std::string Issue2572::subtitle() const
{
    return "Look at the output in console";
}
