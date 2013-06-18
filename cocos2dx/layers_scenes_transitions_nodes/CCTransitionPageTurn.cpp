/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2009      Sindesso Pty Ltd http://www.sindesso.com/

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

#include "CCTransitionPageTurn.h"
#include "CCDirector.h"
#include "actions/CCActionInterval.h"
#include "actions/CCActionInstant.h"
#include "actions/CCActionGrid.h"
#include "actions/CCActionPageTurn3D.h"

NS_CC_BEGIN

CCTransitionPageTurn::CCTransitionPageTurn()
{
}

CCTransitionPageTurn::~CCTransitionPageTurn()
{
}

/** creates a base transition with duration and incoming scene */
CCTransitionPageTurn * CCTransitionPageTurn::create(float t, CCScene *scene, bool backwards)
{
    CCTransitionPageTurn * pTransition = new CCTransitionPageTurn();
    pTransition->initWithDuration(t,scene,backwards);
    pTransition->autorelease();
    return pTransition;
}

/** initializes a transition with duration and incoming scene */
bool CCTransitionPageTurn::initWithDuration(float t, CCScene *scene, bool backwards)
{
    // XXX: needed before [super init]
    _back = backwards;

    if (CCTransitionScene::initWithDuration(t, scene))
    {
        // do something
    }
    return true;
}

void CCTransitionPageTurn::sceneOrder()
{
    _isInSceneOnTop = _back;
}

void CCTransitionPageTurn::onEnter()
{
    CCTransitionScene::onEnter();
    CCSize s = CCDirector::sharedDirector()->getWinSize();
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

    CCActionInterval *action  = this->actionWithSize(CCSizeMake(x,y));

    if (! _back )
    {
        _outScene->runAction
        (
            CCSequence::create
            (
                action,
                CCCallFunc::create(this, callfunc_selector(CCTransitionScene::finish)),
                CCStopGrid::create(),
                NULL
            )
        );
    }
    else
    {
        // to prevent initial flicker
        _inScene->setVisible(false);
        _inScene->runAction
        (
            CCSequence::create
            (
                CCShow::create(),
                action,
                CCCallFunc::create(this, callfunc_selector(CCTransitionScene::finish)),
                CCStopGrid::create(),
                NULL
            )
        );
    }
}


CCActionInterval* CCTransitionPageTurn:: actionWithSize(const CCSize& vector)
{
    if (_back)
    {
        // Get hold of the PageTurn3DAction
        return CCReverseTime::create
        (
            CCPageTurn3D::create(_duration, vector)
        );
    }
    else
    {
        // Get hold of the PageTurn3DAction
        return CCPageTurn3D::create(_duration, vector);
    }
}

NS_CC_END
