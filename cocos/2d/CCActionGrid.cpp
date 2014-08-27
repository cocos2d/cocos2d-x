/****************************************************************************
Copyright (c) 2009      On-Core
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

#include "2d/CCActionGrid.h"

#include "2d/CCGrid.h"
#include "2d/CCNodeGrid.h"
#include "base/CCDirector.h"

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
    cacheTargetAsGridNode();

    GridBase *newgrid = this->getGrid();

    GridBase *targetGrid = _gridNodeTarget->getGrid();

    if (targetGrid && targetGrid->getReuseGrid() > 0)
    {
        if (targetGrid->isActive() && targetGrid->getGridSize().width == _gridSize.width
            && targetGrid->getGridSize().height == _gridSize.height /*&& dynamic_cast<GridBase*>(targetGrid) != nullptr*/)
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

        _gridNodeTarget->setGrid(newgrid);
        _gridNodeTarget->getGrid()->setActive(true);
    }
}

void GridAction::cacheTargetAsGridNode()
{
    _gridNodeTarget = dynamic_cast<NodeGrid*> (_target);
    CCASSERT(_gridNodeTarget, "GridActions can only used on NodeGrid");
}

GridAction* GridAction::reverse() const
{
    // FIXME: This conversion isn't safe.
	return (GridAction*)ReverseTime::create( this->clone() );
}

GridBase* GridAction::getGrid()
{
    // Abstract class needs implementation
    CCASSERT(0, "");

    return nullptr;
}

// implementation of Grid3DAction

GridBase* Grid3DAction::getGrid()
{
    return Grid3D::create(_gridSize);
}

Vec3 Grid3DAction::getVertex(const Vec2& position) const
{
    Grid3D *g = (Grid3D*)_gridNodeTarget->getGrid();
    return g->getVertex(position);
}

Vec3 Grid3DAction::getOriginalVertex(const Vec2& position) const
{
    Grid3D *g = (Grid3D*)_gridNodeTarget->getGrid();
    return g->getOriginalVertex(position);
}

void Grid3DAction::setVertex(const Vec2& position, const Vec3& vertex)
{
    Grid3D *g = (Grid3D*)_gridNodeTarget->getGrid();
    g->setVertex(position, vertex);
}

// implementation of TiledGrid3DAction

GridBase* TiledGrid3DAction::getGrid(void)
{
    return TiledGrid3D::create(_gridSize);
}

Quad3 TiledGrid3DAction::getTile(const Vec2& pos) const
{
    TiledGrid3D *g = (TiledGrid3D*)_gridNodeTarget->getGrid();
    return g->getTile(pos);
}

Quad3 TiledGrid3DAction::getOriginalTile(const Vec2& pos) const
{
    TiledGrid3D *g = (TiledGrid3D*)_gridNodeTarget->getGrid();
    return g->getOriginalTile(pos);
}

void TiledGrid3DAction::setTile(const Vec2& pos, const Quad3& coords)
{
    TiledGrid3D *g = (TiledGrid3D*)_gridNodeTarget->getGrid();
    return g->setTile(pos, coords);
}

// implementation AccelDeccelAmplitude

AccelDeccelAmplitude* AccelDeccelAmplitude::create(Action *action, float duration)
{
    AccelDeccelAmplitude *ret = new (std::nothrow) AccelDeccelAmplitude();
    if (ret)
    {
        if (ret->initWithAction(action, duration))
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(ret);
        }
    }

    return ret;
}

bool AccelDeccelAmplitude::initWithAction(Action *action, float duration)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _rate = 1.0f;
        _other = (ActionInterval*)(action);
        action->retain();

        return true;
    }

    return false;
}

AccelDeccelAmplitude* AccelDeccelAmplitude::clone() const
{
	// no copy constructor
	auto a = new (std::nothrow) AccelDeccelAmplitude();
	a->initWithAction(_other->clone(), _rate);
	a->autorelease();
	return a;
}

AccelDeccelAmplitude::~AccelDeccelAmplitude()
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

AccelAmplitude* AccelAmplitude::create(Action *action, float duration)
{
    AccelAmplitude *ret = new (std::nothrow) AccelAmplitude();
    if (ret)
    {
        if (ret->initWithAction(action, duration))
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(ret);
        }
    }

    return ret;
}

bool AccelAmplitude::initWithAction(Action *action, float duration)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _rate = 1.0f;
        _other = (ActionInterval*)(action);
        action->retain();

        return true;
    }

    return false;
}

AccelAmplitude* AccelAmplitude::clone() const
{
	// no copy constructor
	auto a = new (std::nothrow) AccelAmplitude();
	a->initWithAction(_other->clone(), _duration);
	a->autorelease();
	return a;
}

AccelAmplitude::~AccelAmplitude()
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

DeccelAmplitude* DeccelAmplitude::create(Action *action, float duration)
{
    DeccelAmplitude *ret = new (std::nothrow) DeccelAmplitude();
    if (ret)
    {
        if (ret->initWithAction(action, duration))
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(ret);
        }
    }

    return ret;
}

bool DeccelAmplitude::initWithAction(Action *action, float duration)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _rate = 1.0f;
        _other = (ActionInterval*)(action);
        action->retain();

        return true;
    }

    return false;
}

DeccelAmplitude::~DeccelAmplitude()
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
	auto a = new (std::nothrow) DeccelAmplitude();
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
    cacheTargetAsGridNode();
    GridBase *grid = _gridNodeTarget->getGrid();
    if (grid && grid->isActive())
    {
        grid->setActive(false);
    }
}

void StopGrid::cacheTargetAsGridNode()
{
    _gridNodeTarget = dynamic_cast<NodeGrid*> (_target);
    CCASSERT(_gridNodeTarget, "GridActions can only used on NodeGrid");
}

StopGrid* StopGrid::create()
{
    StopGrid* pAction = new (std::nothrow) StopGrid();
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
    ReuseGrid *action = new (std::nothrow) ReuseGrid();
    if (action)
    {
        if (action->initWithTimes(times))
        {
            action->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(action);
        }
    }

    return action;
}

bool ReuseGrid::initWithTimes(int times)
{
    _times = times;

    return true;
}

void ReuseGrid::startWithTarget(Node *target)
{
    ActionInstant::startWithTarget(target);
    cacheTargetAsGridNode();

    if (_gridNodeTarget->getGrid() && _gridNodeTarget->getGrid()->isActive())
    {
        _gridNodeTarget->getGrid()->setReuseGrid(_gridNodeTarget->getGrid()->getReuseGrid() + _times);
    }
}

void ReuseGrid::cacheTargetAsGridNode()
{
    _gridNodeTarget = dynamic_cast<NodeGrid*> (_target);
    CCASSERT(_gridNodeTarget, "GridActions can only used on NodeGrid");
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
