/****************************************************************************
Copyright (c) 2010гн2011 cocos2d-x.org
Copyright (c) 2009       On-Core
 
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
#include "CCActionTiledGrid.h"
#include "CCDirector.h"
#include "ccMacros.h"
#include "effects/CCGrid.h"
#include <stdlib.h>

NS_CC_BEGIN

struct Tile
{
    Point    position;
    Point    startPosition;
    Size    delta;
};

// implementation of ShakyTiles3D

ShakyTiles3D* ShakyTiles3D::create(float duration, const Size& gridSize, int nRange, bool bShakeZ)
{
    ShakyTiles3D *pAction = new ShakyTiles3D();

    if (pAction)
    {
        if (pAction->initWithDuration(duration, gridSize, nRange, bShakeZ))
        {
            pAction->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pAction);
        }
    }

    return pAction;    
}

bool ShakyTiles3D::initWithDuration(float duration, const Size& gridSize, int nRange, bool bShakeZ)
{
    if (TiledGrid3DAction::initWithDuration(duration, gridSize))
    {
        _randrange = nRange;
        _shakeZ = bShakeZ;

        return true;
    }

    return false;
}

ShakyTiles3D* ShakyTiles3D::clone() const
{
	// no copy constructor	
	auto a = new ShakyTiles3D();
    a->initWithDuration(_duration, _gridSize, _randrange, _shakeZ);
	a->autorelease();
	return a;
}

void ShakyTiles3D::update(float time)
{
    CC_UNUSED_PARAM(time);
    int i, j;

    for (i = 0; i < _gridSize.width; ++i)
    {
        for (j = 0; j < _gridSize.height; ++j)
        {
            Quad3 coords = getOriginalTile(Point(i, j));

            // X
            coords.bl.x += ( rand() % (_randrange*2) ) - _randrange;
            coords.br.x += ( rand() % (_randrange*2) ) - _randrange;
            coords.tl.x += ( rand() % (_randrange*2) ) - _randrange;
            coords.tr.x += ( rand() % (_randrange*2) ) - _randrange;

            // Y
            coords.bl.y += ( rand() % (_randrange*2) ) - _randrange;
            coords.br.y += ( rand() % (_randrange*2) ) - _randrange;
            coords.tl.y += ( rand() % (_randrange*2) ) - _randrange;
            coords.tr.y += ( rand() % (_randrange*2) ) - _randrange;

            if (_shakeZ)
            {
                coords.bl.z += ( rand() % (_randrange*2) ) - _randrange;
                coords.br.z += ( rand() % (_randrange*2) ) - _randrange;
                coords.tl.z += ( rand() % (_randrange*2) ) - _randrange;
                coords.tr.z += ( rand() % (_randrange*2) ) - _randrange;
            }
                        
            setTile(Point(i, j), coords);
        }
    }
}

// implementation of ShatteredTiles3D

ShatteredTiles3D* ShatteredTiles3D::create(float duration, const Size& gridSize, int nRange, bool bShatterZ)
{
    ShatteredTiles3D *pAction = new ShatteredTiles3D();

    if (pAction)
    {
        if (pAction->initWithDuration(duration, gridSize, nRange, bShatterZ))
        {
            pAction->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pAction);
        }
    }

    return pAction;    
}

bool ShatteredTiles3D::initWithDuration(float duration, const Size& gridSize, int nRange, bool bShatterZ)
{
    if (TiledGrid3DAction::initWithDuration(duration, gridSize))
    {
        _once = false;
        _randrange = nRange;
        _shatterZ = bShatterZ;

        return true;
    }

    return false;
}

ShatteredTiles3D* ShatteredTiles3D::clone() const
{
	// no copy constructor	
	auto a = new ShatteredTiles3D();
	a->initWithDuration(_duration, _gridSize, _randrange, _shatterZ);
	a->autorelease();
	return a;
}

void ShatteredTiles3D::update(float time)
{
    CC_UNUSED_PARAM(time);
    int i, j;

    if (_once == false)
    {
        for (i = 0; i < _gridSize.width; ++i)
        {
            for (j = 0; j < _gridSize.height; ++j)
            {
                Quad3 coords = getOriginalTile(Point(i ,j));
                
                // X
                coords.bl.x += ( rand() % (_randrange*2) ) - _randrange;
                coords.br.x += ( rand() % (_randrange*2) ) - _randrange;
                coords.tl.x += ( rand() % (_randrange*2) ) - _randrange;
                coords.tr.x += ( rand() % (_randrange*2) ) - _randrange;
                
                // Y
                coords.bl.y += ( rand() % (_randrange*2) ) - _randrange;
                coords.br.y += ( rand() % (_randrange*2) ) - _randrange;
                coords.tl.y += ( rand() % (_randrange*2) ) - _randrange;
                coords.tr.y += ( rand() % (_randrange*2) ) - _randrange;

                if (_shatterZ) 
                {
                    coords.bl.z += ( rand() % (_randrange*2) ) - _randrange;
                    coords.br.z += ( rand() % (_randrange*2) ) - _randrange;                
                    coords.tl.z += ( rand() % (_randrange*2) ) - _randrange;
                    coords.tr.z += ( rand() % (_randrange*2) ) - _randrange;
                }
                
                setTile(Point(i, j), coords);
            }
        }
        
        _once = true;
    }
}

// implementation of ShuffleTiles

ShuffleTiles* ShuffleTiles::create(float duration, const Size& gridSize, unsigned int seed)
{
    ShuffleTiles *pAction = new ShuffleTiles();

    if (pAction)
    {
        if (pAction->initWithDuration(duration, gridSize, seed))
        {
            pAction->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pAction);
        }
    }

    return pAction;    
}

bool ShuffleTiles::initWithDuration(float duration, const Size& gridSize, unsigned int seed)
{
    if (TiledGrid3DAction::initWithDuration(duration, gridSize))
    {
        _seed = seed;
        _tilesOrder = NULL;
        _tiles = NULL;

        return true;
    }

    return false;
}

ShuffleTiles* ShuffleTiles::clone() const
{
	// no copy constructor
	auto a = new ShuffleTiles();
	a->initWithDuration(_duration, _gridSize, _seed);
	a->autorelease();
	return a;
}

ShuffleTiles::~ShuffleTiles(void)
{
    CC_SAFE_DELETE_ARRAY(_tilesOrder);
    CC_SAFE_DELETE_ARRAY(_tiles);
}

void ShuffleTiles::shuffle(unsigned int *pArray, unsigned int nLen)
{
    int i;
    for( i = nLen - 1; i >= 0; i-- )
    {
        unsigned int j = rand() % (i+1);
        unsigned int v = pArray[i];
        pArray[i] = pArray[j];
        pArray[j] = v;
    }
}

Size ShuffleTiles::getDelta(const Size& pos) const
{
    Point    pos2;

    unsigned int idx = pos.width * _gridSize.height + pos.height;

    pos2.x = (float)(_tilesOrder[idx] / (int)_gridSize.height);
    pos2.y = (float)(_tilesOrder[idx] % (int)_gridSize.height);

    return Size((int)(pos2.x - pos.width), (int)(pos2.y - pos.height));
}

void ShuffleTiles::placeTile(const Point& pos, Tile *t)
{
    Quad3 coords = getOriginalTile(pos);

    Point step = _target->getGrid()->getStep();
    coords.bl.x += (int)(t->position.x * step.x);
    coords.bl.y += (int)(t->position.y * step.y);

    coords.br.x += (int)(t->position.x * step.x);
    coords.br.y += (int)(t->position.y * step.y);

    coords.tl.x += (int)(t->position.x * step.x);
    coords.tl.y += (int)(t->position.y * step.y);

    coords.tr.x += (int)(t->position.x * step.x);
    coords.tr.y += (int)(t->position.y * step.y);

    setTile(pos, coords);
}

void ShuffleTiles::startWithTarget(Node *target)
{
    TiledGrid3DAction::startWithTarget(target);

    if (_seed != (unsigned int)-1)
    {
        srand(_seed);
    }

    _tilesCount = _gridSize.width * _gridSize.height;
    _tilesOrder = new unsigned int[_tilesCount];
    int i, j;
    unsigned int k;

    /**
     * Use k to loop. Because _tilesCount is unsigned int,
     * and i is used later for int.
     */
    for (k = 0; k < _tilesCount; ++k)
    {
        _tilesOrder[k] = k;
    }

    shuffle(_tilesOrder, _tilesCount);

    _tiles = (struct Tile *)new Tile[_tilesCount];
    Tile *tileArray = (Tile*) _tiles;

    for (i = 0; i < _gridSize.width; ++i)
    {
        for (j = 0; j < _gridSize.height; ++j)
        {
            tileArray->position = Point((float)i, (float)j);
            tileArray->startPosition = Point((float)i, (float)j);
            tileArray->delta = getDelta(Size(i, j));
            ++tileArray;
        }
    }
}

void ShuffleTiles::update(float time)
{
    int i, j;

    Tile *tileArray = (Tile*)_tiles;

    for (i = 0; i < _gridSize.width; ++i)
    {
        for (j = 0; j < _gridSize.height; ++j)
        {
            tileArray->position = Point((float)tileArray->delta.width, (float)tileArray->delta.height) * time;
            placeTile(Point(i, j), tileArray);
            ++tileArray;
        }
    }
}

// implementation of FadeOutTRTiles

FadeOutTRTiles* FadeOutTRTiles::create(float duration, const Size& gridSize)
{
    FadeOutTRTiles *pAction = new FadeOutTRTiles();

    if (pAction)
    {
        if (pAction->initWithDuration(duration, gridSize))
        {
            pAction->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pAction);
        }
    }

    return pAction;    
}

FadeOutTRTiles* FadeOutTRTiles::clone() const
{
	// no copy constructor
	auto a = new FadeOutTRTiles();
	a->initWithDuration(_duration, _gridSize);
	a->autorelease();
	return a;
}

float FadeOutTRTiles::testFunc(const Size& pos, float time)
{
    Point n = Point((float)_gridSize.width, (float)_gridSize.height) * time;
    if ((n.x + n.y) == 0.0f)
    {
        return 1.0f;
    }

    return powf((pos.width + pos.height) / (n.x + n.y), 6);
}

void FadeOutTRTiles::turnOnTile(const Point& pos)
{
    setTile(pos, getOriginalTile(pos));
}

void FadeOutTRTiles::turnOffTile(const Point& pos)
{
    Quad3 coords;
    memset(&coords, 0, sizeof(Quad3));
    setTile(pos, coords);
}

void FadeOutTRTiles::transformTile(const Point& pos, float distance)
{
    Quad3 coords = getOriginalTile(pos);
    Point step = _target->getGrid()->getStep();

    coords.bl.x += (step.x / 2) * (1.0f - distance);
    coords.bl.y += (step.y / 2) * (1.0f - distance);

    coords.br.x -= (step.x / 2) * (1.0f - distance);
    coords.br.y += (step.y / 2) * (1.0f - distance);

    coords.tl.x += (step.x / 2) * (1.0f - distance);
    coords.tl.y -= (step.y / 2) * (1.0f - distance);

    coords.tr.x -= (step.x / 2) * (1.0f - distance);
    coords.tr.y -= (step.y / 2) * (1.0f - distance);

    setTile(pos, coords);
}

void FadeOutTRTiles::update(float time)
{
    int i, j;

    for (i = 0; i < _gridSize.width; ++i)
    {
        for (j = 0; j < _gridSize.height; ++j)
        {
            float distance = testFunc(Size(i, j), time);
            if ( distance == 0 )
            {
                turnOffTile(Point(i, j));
            } else 
            if (distance < 1)
            {
                transformTile(Point(i, j), distance);
            }
            else
            {
                turnOnTile(Point(i, j));
            }
        }
    }
}

// implementation of FadeOutBLTiles

FadeOutBLTiles* FadeOutBLTiles::create(float duration, const Size& gridSize)
{
    FadeOutBLTiles *pAction = new FadeOutBLTiles();

    if (pAction)
    {
        if (pAction->initWithDuration(duration, gridSize))
        {
            pAction->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pAction);
        }
    }

    return pAction;
}

FadeOutBLTiles* FadeOutBLTiles::clone() const
{
	// no copy constructor
	auto a = new FadeOutBLTiles();
	a->initWithDuration(_duration, _gridSize);
	a->autorelease();
	return a;
}

float FadeOutBLTiles::testFunc(const Size& pos, float time)
{
    Point n = Point((float)_gridSize.width, (float)_gridSize.height) * (1.0f - time);
    if ((pos.width + pos.height) == 0)
    {
        return 1.0f;
    }

    return powf((n.x + n.y) / (pos.width + pos.height), 6);
}

// implementation of FadeOutUpTiles

FadeOutUpTiles* FadeOutUpTiles::create(float duration, const Size& gridSize)
{
    FadeOutUpTiles *pAction = new FadeOutUpTiles();

    if (pAction)
    {
        if (pAction->initWithDuration(duration, gridSize))
        {
            pAction->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pAction);
        }
    }

    return pAction;
}

FadeOutUpTiles* FadeOutUpTiles::clone() const
{
	// no copy constructor
	auto a = new FadeOutUpTiles();
	a->initWithDuration(_duration, _gridSize);
	a->autorelease();
	return a;
}

float FadeOutUpTiles::testFunc(const Size& pos, float time)
{
    Point n = Point((float)_gridSize.width, (float)_gridSize.height) * time;
    if (n.y == 0.0f)
    {
        return 1.0f;
    }

    return powf(pos.height / n.y, 6);
}

void FadeOutUpTiles::transformTile(const Point& pos, float distance)
{
    Quad3 coords = getOriginalTile(pos);
    Point step = _target->getGrid()->getStep();

    coords.bl.y += (step.y / 2) * (1.0f - distance);
    coords.br.y += (step.y / 2) * (1.0f - distance);
    coords.tl.y -= (step.y / 2) * (1.0f - distance);
    coords.tr.y -= (step.y / 2) * (1.0f - distance);

    setTile(pos, coords);
}

// implementation of FadeOutDownTiles

FadeOutDownTiles* FadeOutDownTiles::create(float duration, const Size& gridSize)
{
    FadeOutDownTiles *pAction = new FadeOutDownTiles();

    if (pAction)
    {
        if (pAction->initWithDuration(duration, gridSize))
        {
            pAction->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pAction);
        }
    }

    return pAction;
}

FadeOutDownTiles* FadeOutDownTiles::clone() const
{
	// no copy constructor
	auto a = new FadeOutDownTiles();
	a->initWithDuration(_duration, _gridSize);
	a->autorelease();
	return a;
}

float FadeOutDownTiles::testFunc(const Size& pos, float time)
{
    Point n = Point((float)_gridSize.width, (float)_gridSize.height) * (1.0f - time);
    if (pos.height == 0)
    {
        return 1.0f;
    }

    return powf(n.y / pos.height, 6);
}

// implementation of TurnOffTiles

TurnOffTiles* TurnOffTiles::create(float duration, const Size& gridSize)
{
    TurnOffTiles* pAction = new TurnOffTiles();
    if (pAction->initWithDuration(duration, gridSize, 0))
    {
        pAction->autorelease();
    }
    else
    {
        CC_SAFE_RELEASE_NULL(pAction);
    }
    return pAction;
}

TurnOffTiles* TurnOffTiles::create(float duration, const Size& gridSize, unsigned int seed)
{
    TurnOffTiles *pAction = new TurnOffTiles();

    if (pAction)
    {
        if (pAction->initWithDuration(duration, gridSize, seed))
        {
            pAction->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pAction);
        }
    }

    return pAction;
}

bool TurnOffTiles::initWithDuration(float duration, const Size& gridSize, unsigned int seed)
{
    if (TiledGrid3DAction::initWithDuration(duration, gridSize))
    {
        _seed = seed;
        _tilesOrder = NULL;

        return true;
    }

    return false;
}

TurnOffTiles* TurnOffTiles::clone() const
{
	// no copy constructor
	auto a = new TurnOffTiles();
    a->initWithDuration(_duration, _gridSize, _seed );
	a->autorelease();
	return a;
}

TurnOffTiles::~TurnOffTiles(void)
{
    CC_SAFE_DELETE_ARRAY(_tilesOrder);
}

void TurnOffTiles::shuffle(unsigned int *pArray, unsigned int nLen)
{
    int i;
    for (i = nLen - 1; i >= 0; i--)
    {
        unsigned int j = rand() % (i+1);
        unsigned int v = pArray[i];
        pArray[i] = pArray[j];
        pArray[j] = v;
    }
}

void TurnOffTiles::turnOnTile(const Point& pos)
{
    setTile(pos, getOriginalTile(pos));
}

void TurnOffTiles::turnOffTile(const Point& pos)
{
    Quad3 coords;

    memset(&coords, 0, sizeof(Quad3));
    setTile(pos, coords);
}

void TurnOffTiles::startWithTarget(Node *target)
{
    unsigned int i;

    TiledGrid3DAction::startWithTarget(target);

    if (_seed != (unsigned int)-1)
    {
        srand(_seed);
    }

    _tilesCount = _gridSize.width * _gridSize.height;
    _tilesOrder = new unsigned int[_tilesCount];

    for (i = 0; i < _tilesCount; ++i)
    {
        _tilesOrder[i] = i;
    }

    shuffle(_tilesOrder, _tilesCount);
}

void TurnOffTiles::update(float time)
{
    unsigned int i, l, t;

    l = (unsigned int)(time * (float)_tilesCount);

    for( i = 0; i < _tilesCount; i++ )
    {
        t = _tilesOrder[i];
        Point tilePos = Point( (unsigned int)(t / _gridSize.height), t % (unsigned int)_gridSize.height );

        if ( i < l )
        {
            turnOffTile(tilePos);
        }
        else
        {
            turnOnTile(tilePos);
        }
    }
}

// implementation of WavesTiles3D

WavesTiles3D* WavesTiles3D::create(float duration, const Size& gridSize, unsigned int waves, float amplitude)
{
    WavesTiles3D *pAction = new WavesTiles3D();

    if (pAction)
    {
        if (pAction->initWithDuration(duration, gridSize, waves, amplitude))
        {
            pAction->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pAction);
        }
    }

    return pAction;
}

bool WavesTiles3D::initWithDuration(float duration, const Size& gridSize, unsigned int waves, float amplitude)
{
    if (TiledGrid3DAction::initWithDuration(duration, gridSize))
    {
        _waves = waves;
        _amplitude = amplitude;
        _amplitudeRate = 1.0f;

        return true;
    }

    return false;
}

WavesTiles3D* WavesTiles3D::clone() const
{
	// no copy constructor
	auto a = new WavesTiles3D();
    a->initWithDuration(_duration, _gridSize, _waves, _amplitude);
	a->autorelease();
	return a;
}

void WavesTiles3D::update(float time)
{
    int i, j;

    for( i = 0; i < _gridSize.width; i++ )
    {
        for( j = 0; j < _gridSize.height; j++ )
        {
            Quad3 coords = getOriginalTile(Point(i, j));

            coords.bl.z = (sinf(time * (float)M_PI  *_waves * 2 + 
                (coords.bl.y+coords.bl.x) * .01f) * _amplitude * _amplitudeRate );
            coords.br.z    = coords.bl.z;
            coords.tl.z = coords.bl.z;
            coords.tr.z = coords.bl.z;

            setTile(Point(i, j), coords);
        }
    }
}

// implementation of JumpTiles3D

JumpTiles3D* JumpTiles3D::create(float duration, const Size& gridSize, unsigned int numberOfJumps, float amplitude)
{
    JumpTiles3D *pAction = new JumpTiles3D();

    if (pAction)
    {
        if (pAction->initWithDuration(duration, gridSize, numberOfJumps, amplitude))
        {
            pAction->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pAction);
        }
    }

    return pAction;
}

bool JumpTiles3D::initWithDuration(float duration, const Size& gridSize, unsigned int numberOfJumps, float amplitude)
{
    if (TiledGrid3DAction::initWithDuration(duration, gridSize))
    {
        _jumps = numberOfJumps;
        _amplitude = amplitude;
        _amplitudeRate = 1.0f;

        return true;
    }

    return false;
}

JumpTiles3D* JumpTiles3D::clone() const
{
	// no copy constructor
	auto a = new JumpTiles3D();
    a->initWithDuration(_duration, _gridSize, _jumps, _amplitude);
	a->autorelease();
	return a;
}

void JumpTiles3D::update(float time)
{
    int i, j;

    float sinz =  (sinf((float)M_PI * time * _jumps * 2) * _amplitude * _amplitudeRate );
    float sinz2 = (sinf((float)M_PI * (time * _jumps * 2 + 1)) * _amplitude * _amplitudeRate );

    for( i = 0; i < _gridSize.width; i++ )
    {
        for( j = 0; j < _gridSize.height; j++ )
        {
            Quad3 coords = getOriginalTile(Point(i, j));

            if ( ((i+j) % 2) == 0 )
            {
                coords.bl.z += sinz;
                coords.br.z += sinz;
                coords.tl.z += sinz;
                coords.tr.z += sinz;
            }
            else
            {
                coords.bl.z += sinz2;
                coords.br.z += sinz2;
                coords.tl.z += sinz2;
                coords.tr.z += sinz2;
            }

            setTile(Point(i, j), coords);
        }
    }
}

// implementation of SplitRows

SplitRows* SplitRows::create(float duration, unsigned int nRows)
{
    SplitRows *pAction = new SplitRows();

    if (pAction)
    {
        if (pAction->initWithDuration(duration, nRows))
        {
            pAction->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pAction);
        }
    }

    return pAction;
}

bool SplitRows::initWithDuration(float duration, unsigned int nRows)
{
    _rows = nRows;

    return TiledGrid3DAction::initWithDuration(duration, Size(1, nRows));
}

SplitRows* SplitRows::clone() const
{
	// no copy constructor
	auto a = new SplitRows();
    a->initWithDuration(_duration, _rows);
	a->autorelease();
	return a;
}

void SplitRows::startWithTarget(Node *target)
{
    TiledGrid3DAction::startWithTarget(target);
    _winSize = Director::getInstance()->getWinSizeInPixels();
}

void SplitRows::update(float time)
{
    unsigned int j;

    for (j = 0; j < _gridSize.height; ++j)
    {
        Quad3 coords = getOriginalTile(Point(0, j));
        float    direction = 1;

        if ( (j % 2 ) == 0 )
        {
            direction = -1;
        }

        coords.bl.x += direction * _winSize.width * time;
        coords.br.x += direction * _winSize.width * time;
        coords.tl.x += direction * _winSize.width * time;
        coords.tr.x += direction * _winSize.width * time;

        setTile(Point(0, j), coords);
    }
}

// implementation of SplitCols

SplitCols* SplitCols::create(float duration, unsigned int nCols)
{
    SplitCols *pAction = new SplitCols();

    if (pAction)
    {
        if (pAction->initWithDuration(duration, nCols))
        {
            pAction->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pAction);
        }
    }

    return pAction;
}

bool SplitCols::initWithDuration(float duration, unsigned int nCols)
{
    _cols = nCols;
    return TiledGrid3DAction::initWithDuration(duration, Size(nCols, 1));
}

SplitCols* SplitCols::clone() const
{
	// no copy constructor	
	auto a = new SplitCols();
    a->initWithDuration(_duration, _cols);
	a->autorelease();
	return a;
}

void SplitCols::startWithTarget(Node *target)
{
    TiledGrid3DAction::startWithTarget(target);
    _winSize = Director::getInstance()->getWinSizeInPixels();
}

void SplitCols::update(float time)
{
    unsigned int i;

    for (i = 0; i < _gridSize.width; ++i)
    {
        Quad3 coords = getOriginalTile(Point(i, 0));
        float    direction = 1;

        if ( (i % 2 ) == 0 )
        {
            direction = -1;
        }

        coords.bl.y += direction * _winSize.height * time;
        coords.br.y += direction * _winSize.height * time;
        coords.tl.y += direction * _winSize.height * time;
        coords.tr.y += direction * _winSize.height * time;

        setTile(Point(i, 0), coords);
    }
}

NS_CC_END
