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

bool CCGridAction::initWithDuration(float duration, const CCSize& gridSize)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        _gridSize = gridSize;

        return true;
    }

    return false;
}

void CCGridAction::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);

    CCGridBase *newgrid = this->getGrid();

    CCNode *t = _target;
    CCGridBase *targetGrid = t->getGrid();

    if (targetGrid && targetGrid->getReuseGrid() > 0)
    {
        if (targetGrid->isActive() && targetGrid->getGridSize().width == _gridSize.width
            && targetGrid->getGridSize().height == _gridSize.height /*&& dynamic_cast<CCGridBase*>(targetGrid) != NULL*/)
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

CCGridAction* CCGridAction::reverse() const
{
	return (CCGridAction*)CCReverseTime::create( this->clone() );
}

CCGridBase* CCGridAction::getGrid(void)
{
    // Abstract class needs implementation
    CCAssert(0, "");

    return NULL;
}

// implementation of Grid3DAction

CCGridBase* CCGrid3DAction::getGrid(void)
{
    return CCGrid3D::create(_gridSize);
}

ccVertex3F CCGrid3DAction::vertex(const CCPoint& position)
{
    CCGrid3D *g = (CCGrid3D*)_target->getGrid();
    return g->vertex(position);
}

ccVertex3F CCGrid3DAction::originalVertex(const CCPoint& position)
{
    CCGrid3D *g = (CCGrid3D*)_target->getGrid();
    return g->originalVertex(position);
}

void CCGrid3DAction::setVertex(const CCPoint& position, const ccVertex3F& vertex)
{
    CCGrid3D *g = (CCGrid3D*)_target->getGrid();
    g->setVertex(position, vertex);
}

// implementation of TiledGrid3DAction

CCGridBase* CCTiledGrid3DAction::getGrid(void)
{
    return CCTiledGrid3D::create(_gridSize);
}

ccQuad3 CCTiledGrid3DAction::tile(const CCPoint& pos)
{
    CCTiledGrid3D *g = (CCTiledGrid3D*)_target->getGrid();
    return g->tile(pos);
}

ccQuad3 CCTiledGrid3DAction::originalTile(const CCPoint& pos)
{
    CCTiledGrid3D *g = (CCTiledGrid3D*)_target->getGrid();
    return g->originalTile(pos);
}

void CCTiledGrid3DAction::setTile(const CCPoint& pos, const ccQuad3& coords)
{
    CCTiledGrid3D *g = (CCTiledGrid3D*)_target->getGrid();
    return g->setTile(pos, coords);
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
        _rate = 1.0f;
        _other = (CCActionInterval*)(pAction);
        pAction->retain();

        return true;
    }

    return false;
}

CCAccelDeccelAmplitude* CCAccelDeccelAmplitude::clone() const
{
	auto a = new CCAccelDeccelAmplitude(*this);
	a->initWithAction(_other->clone(), _rate);
	a->autorelease();
	return a;
}

CCAccelDeccelAmplitude::~CCAccelDeccelAmplitude(void)
{
    CC_SAFE_RELEASE(_other);
}

void CCAccelDeccelAmplitude::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    _other->startWithTarget(pTarget);
}

void CCAccelDeccelAmplitude::update(float time)
{
    float f = time * 2;

    if (f > 1)
    {
        f -= 1;
        f = 1 - f;
    }

    ((CCAccelDeccelAmplitude*)(_other))->setAmplitudeRate(powf(f, _rate));
}

CCAccelDeccelAmplitude* CCAccelDeccelAmplitude::reverse() const
{
    return CCAccelDeccelAmplitude::create(_other->reverse(), _duration);
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
        _rate = 1.0f;
        _other = (CCActionInterval*)(pAction);
        pAction->retain();

        return true;
    }

    return false;
}

CCAccelAmplitude* CCAccelAmplitude::clone() const
{
	auto a = new CCAccelAmplitude(*this);
	a->initWithAction(_other->clone(), _duration);
	a->autorelease();
	return a;
}

CCAccelAmplitude::~CCAccelAmplitude(void)
{
    CC_SAFE_DELETE(_other);
}

void CCAccelAmplitude::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    _other->startWithTarget(pTarget);
}

void CCAccelAmplitude::update(float time)
{
    ((CCAccelAmplitude*)(_other))->setAmplitudeRate(powf(time, _rate));
    _other->update(time);
}

CCAccelAmplitude* CCAccelAmplitude::reverse() const
{
    return CCAccelAmplitude::create(_other->reverse(), _duration);
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
        _rate = 1.0f;
        _other = (CCActionInterval*)(pAction);
        pAction->retain();

        return true;
    }

    return false;
}

CCDeccelAmplitude::~CCDeccelAmplitude(void)
{
    CC_SAFE_RELEASE(_other);
}

void CCDeccelAmplitude::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    _other->startWithTarget(pTarget);
}

void CCDeccelAmplitude::update(float time)
{
    ((CCDeccelAmplitude*)(_other))->setAmplitudeRate(powf((1 - time), _rate));
    _other->update(time);
}

CCDeccelAmplitude* CCDeccelAmplitude::clone() const
{
	auto a = new CCDeccelAmplitude(*this);
	a->initWithAction(_other->clone(), _duration);
	a->autorelease();
	return a;
}

CCDeccelAmplitude* CCDeccelAmplitude::reverse() const
{
    return CCDeccelAmplitude::create(_other->reverse(), _duration);
}

// implementation of StopGrid

void CCStopGrid::startWithTarget(CCNode *pTarget)
{
    CCActionInstant::startWithTarget(pTarget);

    CCGridBase *pGrid = _target->getGrid();
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

CCStopGrid* CCStopGrid::clone() const
{
	return CCStopGrid::create();
}

CCStopGrid* CCStopGrid::reverse() const
{
	// no reverse, just clone it
	return this->clone();
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
    _times = times;

    return true;
}

void CCReuseGrid::startWithTarget(CCNode *pTarget)
{
    CCActionInstant::startWithTarget(pTarget);

    if (_target->getGrid() && _target->getGrid()->isActive())
    {
        _target->getGrid()->setReuseGrid(_target->getGrid()->getReuseGrid() + _times);
    }
}

CCReuseGrid* CCReuseGrid::clone() const
{
	return CCReuseGrid::create(_times);
}

CCReuseGrid* CCReuseGrid::reverse() const
{
	// no reverse, just clone it
	return this->clone();
}

NS_CC_END
