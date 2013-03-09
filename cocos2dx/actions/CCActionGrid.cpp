/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2009      On-Core 

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
#include "CCActionGrid.h"
#include "CCDirector.h"
#include "effects/CCGrid.h"
#include "cocoa/CCZone.h"

NS_CC_BEGIN
// implementation of CCGridAction

CCGridAction* CCGridAction::create(float duration, const CCSize& gridSize)
{
    CCGridAction *pAction = new CCGridAction();
    if (pAction)
    {
        if (pAction->initWithDuration(duration, gridSize))
        {
            pAction->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(pAction);
        }
    }

    return pAction;
}

bool CCGridAction::initWithDuration(float duration, const CCSize& gridSize)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        m_sGridSize = gridSize;

        return true;
    }

    return false;
}

void CCGridAction::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);

    CCGridBase *newgrid = this->getGrid();

    CCNode *t = m_pTarget;
    CCGridBase *targetGrid = t->getGrid();

    if (targetGrid && targetGrid->getReuseGrid() > 0)
    {
        if (targetGrid->isActive() && targetGrid->getGridSize().width == m_sGridSize.width
            && targetGrid->getGridSize().height == m_sGridSize.height /*&& dynamic_cast<CCGridBase*>(targetGrid) != NULL*/)
        {
            targetGrid->reuse();
        }
        else
        {
            CCAssert(0, "");
        }
    }
    else
    {
        if (targetGrid && targetGrid->isActive())
        {
            targetGrid->setActive(false);
        }

        t->setGrid(newgrid);
        t->getGrid()->setActive(true);
    }
}

CCGridBase* CCGridAction::getGrid(void)
{
    // Abstract class needs implementation
    CCAssert(0, "");

    return NULL;
}

CCActionInterval* CCGridAction::reverse(void)
{
    return CCReverseTime::create(this);
}

CCObject* CCGridAction::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCGridAction* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCGridAction*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCGridAction();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, m_sGridSize);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

// implementation of Grid3DAction

CCGridBase* CCGrid3DAction::getGrid(void)
{
    return CCGrid3D::create(m_sGridSize);
}

ccVertex3F CCGrid3DAction::vertex(const CCPoint& position)
{
    CCGrid3D *g = (CCGrid3D*)m_pTarget->getGrid();
    return g->vertex(position);
}

ccVertex3F CCGrid3DAction::originalVertex(const CCPoint& position)
{
    CCGrid3D *g = (CCGrid3D*)m_pTarget->getGrid();
    return g->originalVertex(position);
}

void CCGrid3DAction::setVertex(const CCPoint& position, const ccVertex3F& vertex)
{
    CCGrid3D *g = (CCGrid3D*)m_pTarget->getGrid();
    g->setVertex(position, vertex);
}

// implementation of TiledGrid3DAction

CCGridBase* CCTiledGrid3DAction::getGrid(void)
{
    return CCTiledGrid3D::create(m_sGridSize);
}

ccQuad3 CCTiledGrid3DAction::tile(const CCPoint& pos)
{
    CCTiledGrid3D *g = (CCTiledGrid3D*)m_pTarget->getGrid();
    return g->tile(pos);
}

ccQuad3 CCTiledGrid3DAction::originalTile(const CCPoint& pos)
{
    CCTiledGrid3D *g = (CCTiledGrid3D*)m_pTarget->getGrid();
    return g->originalTile(pos);
}

void CCTiledGrid3DAction::setTile(const CCPoint& pos, const ccQuad3& coords)
{
    CCTiledGrid3D *g = (CCTiledGrid3D*)m_pTarget->getGrid();
    return g->setTile(pos, coords);
}

CCTiledGrid3DAction* CCTiledGrid3DAction::create(float duration, const CCSize& gridSize)
{
    CCTiledGrid3DAction* pRet = new CCTiledGrid3DAction();
    if (pRet && pRet->initWithDuration(duration, gridSize))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

// implementation CCAccelDeccelAmplitude

CCAccelDeccelAmplitude* CCAccelDeccelAmplitude::create(CCAction *pAction, float duration)
{
    CCAccelDeccelAmplitude *pRet = new CCAccelDeccelAmplitude();
    if (pRet)
    {
        if (pRet->initWithAction(pAction, duration))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(pRet);
        }
    }

    return pRet;
}

bool CCAccelDeccelAmplitude::initWithAction(CCAction *pAction, float duration)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        m_fRate = 1.0f;
        m_pOther = (CCActionInterval*)(pAction);
        pAction->retain();

        return true;
    }

    return false;
}

CCAccelDeccelAmplitude::~CCAccelDeccelAmplitude(void)
{
    CC_SAFE_RELEASE(m_pOther);
}

void CCAccelDeccelAmplitude::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    m_pOther->startWithTarget(pTarget);
}

void CCAccelDeccelAmplitude::update(float time)
{
    float f = time * 2;

    if (f > 1)
    {
        f -= 1;
        f = 1 - f;
    }

    ((CCAccelDeccelAmplitude*)(m_pOther))->setAmplitudeRate(powf(f, m_fRate));
}

CCActionInterval* CCAccelDeccelAmplitude::reverse(void)
{
    return CCAccelDeccelAmplitude::create(m_pOther->reverse(), m_fDuration);
}

// implementation of AccelAmplitude

CCAccelAmplitude* CCAccelAmplitude::create(CCAction *pAction, float duration)
{
    CCAccelAmplitude *pRet = new CCAccelAmplitude();
    if (pRet)
    {
        if (pRet->initWithAction(pAction, duration))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(pRet);
        }
    }

    return pRet;
}

bool CCAccelAmplitude::initWithAction(CCAction *pAction, float duration)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        m_fRate = 1.0f;
        m_pOther = (CCActionInterval*)(pAction);
        pAction->retain();

        return true;
    }

    return false;
}

CCAccelAmplitude::~CCAccelAmplitude(void)
{
    CC_SAFE_DELETE(m_pOther);
}

void CCAccelAmplitude::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    m_pOther->startWithTarget(pTarget);
}

void CCAccelAmplitude::update(float time)
{
    ((CCAccelAmplitude*)(m_pOther))->setAmplitudeRate(powf(time, m_fRate));
    m_pOther->update(time);
}

CCActionInterval* CCAccelAmplitude::reverse(void)
{
    return CCAccelAmplitude::create(m_pOther->reverse(), m_fDuration);
}

// DeccelAmplitude

CCDeccelAmplitude* CCDeccelAmplitude::create(CCAction *pAction, float duration)
{
    CCDeccelAmplitude *pRet = new CCDeccelAmplitude();
    if (pRet)
    {
        if (pRet->initWithAction(pAction, duration))
        {
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(pRet);
        }
    }

    return pRet;
}


bool CCDeccelAmplitude::initWithAction(CCAction *pAction, float duration)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        m_fRate = 1.0f;
        m_pOther = (CCActionInterval*)(pAction);
        pAction->retain();

        return true;
    }

    return false;
}

CCDeccelAmplitude::~CCDeccelAmplitude(void)
{
    CC_SAFE_RELEASE(m_pOther);
}

void CCDeccelAmplitude::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    m_pOther->startWithTarget(pTarget);
}

void CCDeccelAmplitude::update(float time)
{
    ((CCDeccelAmplitude*)(m_pOther))->setAmplitudeRate(powf((1 - time), m_fRate));
    m_pOther->update(time);
}

CCActionInterval* CCDeccelAmplitude::reverse(void)
{
    return CCDeccelAmplitude::create(m_pOther->reverse(), m_fDuration);
}

// implementation of StopGrid

void CCStopGrid::startWithTarget(CCNode *pTarget)
{
    CCActionInstant::startWithTarget(pTarget);

    CCGridBase *pGrid = m_pTarget->getGrid();
    if (pGrid && pGrid->isActive())
    {
        pGrid->setActive(false);
    }
}

CCStopGrid* CCStopGrid::create(void)
{
    CCStopGrid* pAction = new CCStopGrid();
    pAction->autorelease();

    return pAction;
}
// implementation of CCReuseGrid

CCReuseGrid* CCReuseGrid::create(int times)
{
    CCReuseGrid *pAction = new CCReuseGrid();
    if (pAction)
    {
        if (pAction->initWithTimes(times))
        {
            pAction->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(pAction);
        }
    }

    return pAction;
}

bool CCReuseGrid::initWithTimes(int times)
{
    m_nTimes = times;

    return true;
}

void CCReuseGrid::startWithTarget(CCNode *pTarget)
{
    CCActionInstant::startWithTarget(pTarget);

    if (m_pTarget->getGrid() && m_pTarget->getGrid()->isActive())
    {
        m_pTarget->getGrid()->setReuseGrid(m_pTarget->getGrid()->getReuseGrid() + m_nTimes);
    }
}

NS_CC_END
