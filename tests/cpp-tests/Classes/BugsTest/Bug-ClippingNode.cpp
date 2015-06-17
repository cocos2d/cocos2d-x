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

        auto bg = LayerColor::create(Color4B(255, 255, 255, 255));
        //bg->setCameraMask((unsigned short)CameraFlag::USER1);
        this->addChild(bg, -1);//1

        //2D 
        {
            auto stencil = Sprite::create("Images/close.png");
            auto clipper = ClippingNode::create();
            clipper->setStencil(stencil);
            clipper->setInverted(true);
            clipper->setAlphaThreshold(0);
            this->addChild(clipper);

            auto content = Sprite::create("Images/HelloWorld.png");
            clipper->addChild(content);//5

            clipper->setPosition(Vec2(size.width / 4, size.height / 2));
        }

        //3D
        {
            auto stencil = Sprite::create("Images/close.png");
            auto clipper = ClippingNode::create();
            clipper->setStencil(stencil);
            clipper->setInverted(true);
            clipper->setAlphaThreshold(0);
            this->addChild(clipper);

            auto content = Sprite3D::create("Sprite3DTest/orc.c3b");
            content->setScale(3.0f);
            clipper->addChild(content);//5

            clipper->setPosition(Vec2(size.width - size.width / 4, size.height / 2));
        }
        return true;
    }

    return false;
}
