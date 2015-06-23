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
            _clipSprite = ClippingNode::create();
            _clipSprite->setStencil(stencil);
            _clipSprite->setInverted(true);
            _clipSprite->setAlphaThreshold(0);
            this->addChild(_clipSprite);

            auto sprite = Sprite::create("Images/HelloWorld.png");
            _clipSprite->addChild(sprite);//5

            _clipSprite->setPosition(Vec2(size.width / 4, size.height / 2));
        }

        //3D
        {
            auto stencil = Sprite::create("Images/close.png");
            _clipSprite3D = ClippingNode::create();
            _clipSprite3D->setStencil(stencil);
            _clipSprite3D->setInverted(true);
            _clipSprite3D->setAlphaThreshold(0);
            this->addChild(_clipSprite3D);

            auto sprite3D = Sprite3D::create("Sprite3DTest/orc.c3b");
            sprite3D->setScale(3.0f);
            _clipSprite3D->addChild(sprite3D);//5

            _clipSprite3D->setPosition(Vec2(size.width - size.width / 4, size.height / 2));
        }
        return true;
    }

    return false;
}

void BugClippingNodeLayer::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
    //In cocos v3.3, ClippingNode can clip sprite3D, but can not now.
    //_defaultState changed by sprite3D, but not changed by Sprite. 
    //For example, in ClippingNode, we enable stencil test to clip node,
    //if the node type is sprite, it work well, because the _defaultState is not changed by rendering sprite
    //but the _defaultState is changed by rendering sprite3D, so the stencil test is failure.

    {
        // enable stencil use
        bool enableStencil = true;
        glEnable(GL_STENCIL_TEST);
        RenderState::StateBlock::_defaultState->setStencilTest(enableStencil);
        _clipSprite->visit(renderer, transform, flags);
        renderer->render();
        bool currentEnabledStencil = glIsEnabled(GL_STENCIL_TEST);
        if (currentEnabledStencil == enableStencil){
            CCLOG("Sprite: stencil test is still enabled");
        }
        else{
            CCLOG("Sprite: stencil test is  disabled");
        }
    }

    {
        // enable stencil use
        bool enableStencil = true;
        glEnable(GL_STENCIL_TEST);
        RenderState::StateBlock::_defaultState->setStencilTest(enableStencil);
        _clipSprite3D->visit(renderer, transform, flags);
        renderer->render();
        bool currentEnabledStencil = glIsEnabled(GL_STENCIL_TEST);
        if (currentEnabledStencil == enableStencil){
            CCLOG("Sprite3D: stencil test is still enabled");
        }
        else{
            CCLOG("Sprite3D: stencil test is  disabled");
        }
    }

    //BugsTestBase::draw(renderer, transform, flags);
}