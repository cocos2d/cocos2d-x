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

NS_CC_BEGIN
// implementation of GridAction

bool GridAction::initWithDuration(float duration, const Size& gridSize)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _gridSize = gridSize;

        return true;
    }

    return false;
}

void GridAction::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);

    GridBase *newgrid = this->getGrid();

    Node *t = _target;
    GridBase *targetGrid = t->getGrid();

    if (targetGrid && targetGrid->getReuseGrid() > 0)
    {
        if (targetGrid->isActive() && targetGrid->getGridSize().width == _gridSize.width
            && targetGrid->getGridSize().height == _gridSize.height /*&& dynamic_cast<GridBase*>(targetGrid) != NULL*/)
        {
            targetGrid->reuse();
        }
        else
        {
            CCASSERT(0, "");
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

GridAction* GridAction::reverse() const
{
    // FIXME: This conversion isn't safe.
	return (GridAction*)ReverseTime::create( this->clone() );
}

GridBase* GridAction::getGrid(void)
{
    // Abstract class needs implementation
    CCASSERT(0, "");

    return NULL;
}

// implementation of Grid3DAction

GridBase* Grid3DAction::getGrid(void)
{
    return Grid3D::create(_gridSize);
}

Vertex3F Grid3DAction::getVertex(const Point& position) const
{
    Grid3D *g = (Grid3D*)_target->getGrid();
    return g->getVertex(position);
}

Vertex3F Grid3DAction::getOriginalVertex(const Point& position) const
{
    Grid3D *g = (Grid3D*)_target->getGrid();
    return g->getOriginalVertex(position);
}

void Grid3DAction::setVertex(const Point& position, const Vertex3F& vertex)
{
    Grid3D *g = (Grid3D*)_target->getGrid();
    g->setVertex(position, vertex);
}

// implementation of TiledGrid3DAction

GridBase* TiledGrid3DAction::getGrid(void)
{
    return TiledGrid3D::create(_gridSize);
}

Quad3 TiledGrid3DAction::getTile(const Point& pos) const
{
    TiledGrid3D *g = (TiledGrid3D*)_target->getGrid();
    return g->getTile(pos);
}

Quad3 TiledGrid3DAction::getOriginalTile(const Point& pos) const
{
    TiledGrid3D *g = (TiledGrid3D*)_target->getGrid();
    return g->getOriginalTile(pos);
}

void TiledGrid3DAction::setTile(const Point& pos, const Quad3& coords)
{
    TiledGrid3D *g = (TiledGrid3D*)_target->getGrid();
    return g->setTile(pos, coords);
}

// implementation AccelDeccelAmplitude

AccelDeccelAmplitude* AccelDeccelAmplitude::create(Action *pAction, float duration)
{
    AccelDeccelAmplitude *pRet = new AccelDeccelAmplitude();
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

bool AccelDeccelAmplitude::initWithAction(Action *pAction, float duration)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _rate = 1.0f;
        _other = (ActionInterval*)(pAction);
        pAction->retain();

        return true;
    }

    return false;
}

AccelDeccelAmplitude* AccelDeccelAmplitude::clone() const
{
	// no copy constructor
	auto a = new AccelDeccelAmplitude();
	a->initWithAction(_other->clone(), _rate);
	a->autorelease();
	return a;
}

AccelDeccelAmplitude::~AccelDeccelAmplitude(void)
{
    CC_SAFE_RELEASE(_other);
}

void AccelDeccelAmplitude::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    _other->startWithTarget(target);
}

void AccelDeccelAmplitude::update(float time)
{
    float f = time * 2;

    if (f > 1)
    {
        f -= 1;
        f = 1 - f;
    }

    ((AccelDeccelAmplitude*)(_other))->setAmplitudeRate(powf(f, _rate));
}

AccelDeccelAmplitude* AccelDeccelAmplitude::reverse() const
{
    return AccelDeccelAmplitude::create(_other->reverse(), _duration);
}

// implementation of AccelAmplitude

AccelAmplitude* AccelAmplitude::create(Action *pAction, float duration)
{
    AccelAmplitude *pRet = new AccelAmplitude();
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

bool AccelAmplitude::initWithAction(Action *pAction, float duration)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _rate = 1.0f;
        _other = (ActionInterval*)(pAction);
        pAction->retain();

        return true;
    }

    return false;
}

AccelAmplitude* AccelAmplitude::clone() const
{
	// no copy constructor
	auto a = new AccelAmplitude();
	a->initWithAction(_other->clone(), _duration);
	a->autorelease();
	return a;
}

AccelAmplitude::~AccelAmplitude(void)
{
    CC_SAFE_DELETE(_other);
}

void AccelAmplitude::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    _other->startWithTarget(target);
}

void AccelAmplitude::update(float time)
{
    ((AccelAmplitude*)(_other))->setAmplitudeRate(powf(time, _rate));
    _other->update(time);
}

AccelAmplitude* AccelAmplitude::reverse() const
{
    return AccelAmplitude::create(_other->reverse(), _duration);
}

// DeccelAmplitude

DeccelAmplitude* DeccelAmplitude::create(Action *pAction, float duration)
{
    DeccelAmplitude *pRet = new DeccelAmplitude();
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

bool DeccelAmplitude::initWithAction(Action *pAction, float duration)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _rate = 1.0f;
        _other = (ActionInterval*)(pAction);
        pAction->retain();

        return true;
    }

    return false;
}

DeccelAmplitude::~DeccelAmplitude(void)
{
    CC_SAFE_RELEASE(_other);
}

void DeccelAmplitude::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    _other->startWithTarget(target);
}

void DeccelAmplitude::update(float time)
{
    ((DeccelAmplitude*)(_other))->setAmplitudeRate(powf((1 - time), _rate));
    _other->update(time);
}

DeccelAmplitude* DeccelAmplitude::clone() const
{
	// no copy constructor	
	auto a = new DeccelAmplitude();
	a->initWithAction(_other->clone(), _duration);
	a->autorelease();
	return a;
}

DeccelAmplitude* DeccelAmplitude::reverse() const
{
    return DeccelAmplitude::create(_other->reverse(), _duration);
}

// implementation of StopGrid

void StopGrid::startWithTarget(Node *target)
{
    ActionInstant::startWithTarget(target);

    GridBase *pGrid = _target->getGrid();
    if (pGrid && pGrid->isActive())
    {
        pGrid->setActive(false);
    }
}

StopGrid* StopGrid::create(void)
{
    StopGrid* pAction = new StopGrid();
    pAction->autorelease();

    return pAction;
}

StopGrid* StopGrid::clone() const
{
	return StopGrid::create();
}

StopGrid* StopGrid::reverse() const
{
	// no reverse, just clone it
	return this->clone();
}

// implementation of ReuseGrid

ReuseGrid* ReuseGrid::create(int times)
{
    ReuseGrid *pAction = new ReuseGrid();
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

bool ReuseGrid::initWithTimes(int times)
{
    _times = times;

    return true;
}

void ReuseGrid::startWithTarget(Node *target)
{
    ActionInstant::startWithTarget(target);

    if (_target->getGrid() && _target->getGrid()->isActive())
    {
        _target->getGrid()->setReuseGrid(_target->getGrid()->getReuseGrid() + _times);
    }
}

ReuseGrid* ReuseGrid::clone() const
{
	return ReuseGrid::create(_times);
}

ReuseGrid* ReuseGrid::reverse() const
{
	// no reverse, just clone it
	return this->clone();
}

NS_CC_END
