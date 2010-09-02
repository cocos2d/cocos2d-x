/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "CCPageTurnTransition.h"
#include "CCDirector.h"
#include "CCIntervalAction.h"
#include "CCInstantAction.h"
#include "CCGridAction.h"
#include "CCPageTurn3DAction.h"

namespace   cocos2d {

CCPageTurnTransition::CCPageTurnTransition()
{
}
CCPageTurnTransition::~CCPageTurnTransition()
{
}

/** creates a base transition with duration and incoming scene */
CCPageTurnTransition * CCPageTurnTransition::transitionWithDuration(ccTime t, CCScene *scene, bool backwards)
{
	CCPageTurnTransition * pTransition = new CCPageTurnTransition();
	pTransition->initWithDuration(t,scene,backwards);
	pTransition->autorelease();
	return pTransition;
}

/** initializes a transition with duration and incoming scene */
CCPageTurnTransition * CCPageTurnTransition::initWithDuration(ccTime t, CCScene *scene, bool backwards)
{
	// XXX: needed before [super init]
	m_bBack = backwards;

	if( CCTransitionScene::initWithDuration(t, scene) )
	{
		// do something
	}
	return this;
}

void CCPageTurnTransition::sceneOrder()
{
	m_bIsInSceneOnTop = m_bBack;
}

void CCPageTurnTransition::onEnter()
{
	CCTransitionScene::onEnter();
	CGSize s = CCDirector::getSharedDirector()->getWinSize();
	int x,y;
	if( s.width > s.height)
	{
		x=16;y=12;
	}
	else
	{
		x=12;y=16;
	}

	CCIntervalAction *action  = this->actionWithSize(ccg(x,y));

	if(! m_bBack )
	{
		m_pOutScene->runAction
		(
			CCSequence::actions
			(
				action,
				CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::finish)),
				CCStopGrid::action(),
				NULL
			)
		);
	}
	else
	{
		// to prevent initial flicker
		m_pInScene->setIsVisible(false);
		m_pInScene->runAction
		(
			CCSequence::actions
			(
				action,
				CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::finish)),
				CCStopGrid::action(),
				NULL
			)
		);
	}
}


CCIntervalAction* CCPageTurnTransition:: actionWithSize(ccGridSize vector)
{
	if( m_bBack )
	{
		// Get hold of the PageTurn3DAction
		return CCReverseTime::actionWithAction
		(
			CCPageTurn3D::actionWithSize(vector, m_fDuration)
		);
	}
	else
	{
		// Get hold of the PageTurn3DAction
		return CCPageTurn3D::actionWithSize(vector, m_fDuration);
	}
}

}//namespace   cocos2d 
