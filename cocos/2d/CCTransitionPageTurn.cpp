/****************************************************************************
Copyright (c) 2009      Sindesso Pty Ltd http://www.sindesso.com/
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "2d/CCTransitionPageTurn.h"
#include "base/CCDirector.h"
#include "2d/CCActionInterval.h"
#include "2d/CCActionInstant.h"
#include "2d/CCActionGrid.h"
#include "2d/CCActionPageTurn3D.h"
#include "2d/CCNodeGrid.h"
#include "renderer/CCRenderer.h"

NS_CC_BEGIN

float TransitionPageTurn::POLYGON_OFFSET_FACTOR = -20.f;
float TransitionPageTurn::POLYGON_OFFSET_UNITS = -20.f;

TransitionPageTurn::TransitionPageTurn()
{
    _inSceneProxy = NodeGrid::create();
    _outSceneProxy = NodeGrid::create();
    
    _inSceneProxy->retain();
    _outSceneProxy->retain();
}

TransitionPageTurn::~TransitionPageTurn()
{
    CC_SAFE_RELEASE(_inSceneProxy);
    CC_SAFE_RELEASE(_outSceneProxy);
}

/** creates a base transition with duration and incoming scene */
TransitionPageTurn * TransitionPageTurn::create(float t, Scene *scene, bool backwards)
{
    TransitionPageTurn * transition = new TransitionPageTurn();
    transition->initWithDuration(t,scene,backwards);
    transition->autorelease();
    return transition;
}

/** initializes a transition with duration and incoming scene */
bool TransitionPageTurn::initWithDuration(float t, Scene *scene, bool backwards)
{
    // XXX: needed before [super init]
    _back = backwards;

    if (TransitionScene::initWithDuration(t, scene))
    {
        // do something
    }
    return true;
}

void TransitionPageTurn::sceneOrder()
{
    _isInSceneOnTop = _back;
}

void TransitionPageTurn::onEnablePolygonOffset()
{
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(POLYGON_OFFSET_FACTOR, POLYGON_OFFSET_UNITS);
}

void TransitionPageTurn::onDisablePolygonOffset()
{
    glDisable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(0, 0);
}

void TransitionPageTurn::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    Scene::draw(renderer, transform, flags);
    
    if( _isInSceneOnTop ) {
        _outSceneProxy->visit(renderer, transform, flags);
        _enableOffsetCmd.init(_globalZOrder);
        _enableOffsetCmd.func = CC_CALLBACK_0(TransitionPageTurn::onEnablePolygonOffset, this);
        renderer->addCommand(&_enableOffsetCmd);
        _inSceneProxy->visit(renderer, transform, flags);
        _disableOffsetCmd.init(_globalZOrder);
        _disableOffsetCmd.func = CC_CALLBACK_0(TransitionPageTurn::onDisablePolygonOffset, this);
        renderer->addCommand(&_disableOffsetCmd);
    } else {
        _inSceneProxy->visit(renderer, transform, flags);
        
        _enableOffsetCmd.init(_globalZOrder);
        _enableOffsetCmd.func = CC_CALLBACK_0(TransitionPageTurn::onEnablePolygonOffset, this);
        renderer->addCommand(&_enableOffsetCmd);
        
        _outSceneProxy->visit(renderer, transform, flags);
        
        _disableOffsetCmd.init(_globalZOrder);
        _disableOffsetCmd.func = CC_CALLBACK_0(TransitionPageTurn::onDisablePolygonOffset, this);
        renderer->addCommand(&_disableOffsetCmd);
    }
}

void TransitionPageTurn::onEnter()
{
    TransitionScene::onEnter();

    _inSceneProxy->setTarget(_inScene);
    _outSceneProxy->setTarget(_outScene);

    _inSceneProxy->onEnter();
    _outSceneProxy->onEnter();
    
    Size s = Director::getInstance()->getWinSize();
    int x,y;
    if (s.width > s.height)
    {
        x=16;
        y=12;
    }
    else
    {
        x=12;
        y=16;
    }

    ActionInterval *action  = this->actionWithSize(Size(x,y));

    if (! _back )
    {
        _outSceneProxy->runAction
        (
            Sequence::create
            (
                action,
                CallFunc::create(CC_CALLBACK_0(TransitionScene::finish,this)),
                StopGrid::create(),
                nullptr
            )
        );
    }
    else
    {
        // to prevent initial flicker
        _inSceneProxy->setVisible(false);
        _inSceneProxy->runAction
        (
            Sequence::create
            (
                Show::create(),
                action,
                CallFunc::create(CC_CALLBACK_0(TransitionScene::finish,this)),
                StopGrid::create(),
                nullptr
            )
        );
    }
}
void TransitionPageTurn::onExit()
{
    _outSceneProxy->setTarget(nullptr);
    _outSceneProxy->setTarget(nullptr);
    _outSceneProxy->onExit();
    _inSceneProxy->onExit();
    
    TransitionScene::onExit();
}

ActionInterval* TransitionPageTurn:: actionWithSize(const Size& vector)
{
    if (_back)
    {
        // Get hold of the PageTurn3DAction
        return ReverseTime::create
        (
            PageTurn3D::create(_duration, vector)
        );
    }
    else
    {
        // Get hold of the PageTurn3DAction
        return PageTurn3D::create(_duration, vector);
    }
}

NS_CC_END
