//
// Bug-ClippingNode 
//

#include "Bug-ClippingNode.h"

USING_NS_CC;

bool BugClippingNodeLayer::init()
{
    if (BugsTestBase::init())
    {
        auto size = Director::getInstance()->getWinSize();

        //2D clipping node works
        {
            auto stencil = Sprite::create("Images/close.png");
            _clipSprite = ClippingNode::create();
            _clipSprite->setStencil(stencil);
            this->addChild(_clipSprite);

            auto sprite = Sprite::create("Images/HelloWorld.png");
            _clipSprite->addChild(sprite);//

            _clipSprite->setPosition(Vec2(size.width / 4, size.height / 2));
            
            sprite->runAction(RepeatForever::create(RotateBy::create(2.f, 360.f)));
        }

        //3D clipping node does not work
        {
            auto stencil = Sprite::create("Images/close.png");
            _clipSprite3D = ClippingNode::create();
            _clipSprite3D->setStencil(stencil);
            this->addChild(_clipSprite3D);

            auto sprite3D = Sprite3D::create("Sprite3DTest/orc.c3b");
            sprite3D->setScale(3.0f);
            _clipSprite3D->addChild(sprite3D);//5

            _clipSprite3D->setPosition(Vec2(size.width - size.width / 4, size.height / 2));
            
            sprite3D->runAction(RepeatForever::create(RotateBy::create(2.f, 360.f)));
            
            sprite3D->setForce2DQueue(true);
        }
        return true;
    }

    return false;
}
