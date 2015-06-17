/****************************************************************************
Copyright (c) 2009      On-Core
Copyright (c) 2010-2012 cocos2d-x.org
CopyRight (c) 2013-2014 Chukong Technologies Inc.
 
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
#include "2d/CCActionTiledGrid.h"
#include "2d/CCGrid.h"
#include "2d/CCNodeGrid.h"
#include "base/CCDirector.h"
#include "base/ccMacros.h"

NS_CC_BEGIN

struct Tile
{
    Vec2    position;
    Vec2    startPosition;
    Size    delta;
};

// implementation of ShakyTiles3D

ShakyTiles3D* ShakyTiles3D::create(float duration, const Size& gridSize, int range, bool shakeZ)
{
    ShakyTiles3D *action = new (std::nothrow) ShakyTiles3D();

    if (action)
    {
        if (action->initWithDuration(duration, gridSize, range, shakeZ))
        {
            action->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(action);
        }
    }

    return action;
}

bool ShakyTiles3D::initWithDuration(float duration, const Size& gridSize, int range, bool shakeZ)
{
    if (TiledGrid3DAction::initWithDuration(duration, gridSize))
    {
        _randrange = range;
        _shakeZ = shakeZ;

        return true;
    }

    return false;
}

ShakyTiles3D* ShakyTiles3D::clone() const
{
    // no copy constructor    
    auto a = new (std::nothrow) ShakyTiles3D();
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
            Quad3 coords = getOriginalTile(Vec2(i, j));

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
                        
            setTile(Vec2(i, j), coords);
        }
    }
}

// implementation of ShatteredTiles3D

ShatteredTiles3D* ShatteredTiles3D::create(float duration, const Size& gridSize, int range, bool shatterZ)
{
    ShatteredTiles3D *action = new (std::nothrow) ShatteredTiles3D();

    if (action)
    {
        if (action->initWithDuration(duration, gridSize, range, shatterZ))
        {
            action->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(action);
        }
    }

    return action;
}

bool ShatteredTiles3D::initWithDuration(float duration, const Size& gridSize, int range, bool shatterZ)
{
    if (TiledGrid3DAction::initWithDuration(duration, gridSize))
    {
        _once = false;
        _randrange = range;
        _shatterZ = shatterZ;

        return true;
    }

    return false;
}

ShatteredTiles3D* ShatteredTiles3D::clone() const
{
    // no copy constructor    
    auto a = new (std::nothrow) ShatteredTiles3D();
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
                Quad3 coords = getOriginalTile(Vec2(i ,j));
                
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
                
                setTile(Vec2(i, j), coords);
            }
        }
        
        _once = true;
    }
}

// implementation of ShuffleTiles

ShuffleTiles* ShuffleTiles::create(float duration, const Size& gridSize, unsigned int seed)
{
    ShuffleTiles *action = new (std::nothrow) ShuffleTiles();

    if (action)
    {
        if (action->initWithDuration(duration, gridSize, seed))
        {
            action->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(action);
        }
    }

    return action;
}

bool ShuffleTiles::initWithDuration(float duration, const Size& gridSize, unsigned int seed)
{
    if (TiledGrid3DAction::initWithDuration(duration, gridSize))
    {
        _seed = seed;
        _tilesOrder = nullptr;
        _tiles = nullptr;

        return true;
    }

    return false;
}

ShuffleTiles* ShuffleTiles::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) ShuffleTiles();
    a->initWithDuration(_duration, _gridSize, _seed);
    a->autorelease();
    return a;
}

ShuffleTiles::~ShuffleTiles()
{
    CC_SAFE_DELETE_ARRAY(_tilesOrder);
    CC_SAFE_DELETE_ARRAY(_tiles);
}

void ShuffleTiles::shuffle(unsigned int *array, unsigned int len)
{
    for (int i = len - 1; i >= 0; i-- )
    {
        unsigned int j = rand() % (i+1);
        unsigned int v = array[i];
        array[i] = array[j];
        array[j] = v;
    }
}

Size ShuffleTiles::getDelta(const Size& pos) const
{
    Vec2    pos2;

    unsigned int idx = pos.width * _gridSize.height + pos.height;

    pos2.x = (float)(_tilesOrder[idx] / (int)_gridSize.height);
    pos2.y = (float)(_tilesOrder[idx] % (int)_gridSize.height);

    return Size((int)(pos2.x - pos.width), (int)(pos2.y - pos.height));
}

void ShuffleTiles::placeTile(const Vec2& pos, Tile *t)
{
    Quad3 coords = getOriginalTile(pos);

    Vec2 step = _gridNodeTarget->getGrid()->getStep();
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

    /**
     * Use k to loop. Because _tilesCount is unsigned int,
     * and i is used later for int.
     */
    for (unsigned int k = 0; k < _tilesCount; ++k)
    {
        _tilesOrder[k] = k;
    }

    shuffle(_tilesOrder, _tilesCount);

    _tiles = (struct Tile *)new Tile[_tilesCount];
    Tile *tileArray = (Tile*) _tiles;

    for (int i = 0; i < _gridSize.width; ++i)
    {
        for ( int j = 0; j < _gridSize.height; ++j)
        {
            tileArray->position.set((float)i, (float)j);
            tileArray->startPosition.set((float)i, (float)j);
            tileArray->delta = getDelta(Size(i, j));
            ++tileArray;
        }
    }
}

void ShuffleTiles::update(float time)
{
    Tile *tileArray = (Tile*)_tiles;

    for (int i = 0; i < _gridSize.width; ++i)
    {
        for (int j = 0; j < _gridSize.height; ++j)
        {
            tileArray->position = Vec2((float)tileArray->delta.width, (float)tileArray->delta.height) * time;
            placeTile(Vec2(i, j), tileArray);
            ++tileArray;
        }
    }
}

// implementation of FadeOutTRTiles

FadeOutTRTiles* FadeOutTRTiles::create(float duration, const Size& gridSize)
{
    FadeOutTRTiles *action = new (std::nothrow) FadeOutTRTiles();

    if (action)
    {
        if (action->initWithDuration(duration, gridSize))
        {
            action->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(action);
        }
    }

    return action;
}

FadeOutTRTiles* FadeOutTRTiles::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) FadeOutTRTiles();
    a->initWithDuration(_duration, _gridSize);
    a->autorelease();
    return a;
}

float FadeOutTRTiles::testFunc(const Size& pos, float time)
{
    Vec2 n = Vec2((float)_gridSize.width, (float)_gridSize.height) * time;
    if ((n.x + n.y) == 0.0f)
    {
        return 1.0f;
    }

    return powf((pos.width + pos.height) / (n.x + n.y), 6);
}

void FadeOutTRTiles::turnOnTile(const Vec2& pos)
{
    setTile(pos, getOriginalTile(pos));
}

void FadeOutTRTiles::turnOffTile(const Vec2& pos)
{
    Quad3 coords;
    memset(&coords, 0, sizeof(Quad3));
    setTile(pos, coords);
}

void FadeOutTRTiles::transformTile(const Vec2& pos, float distance)
{
    Quad3 coords = getOriginalTile(pos);
    Vec2 step = _gridNodeTarget->getGrid()->getStep();

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
    for (int i = 0; i < _gridSize.width; ++i)
    {
        for (int j = 0; j < _gridSize.height; ++j)
        {
            float distance = testFunc(Size(i, j), time);
            if ( distance == 0 )
            {
                turnOffTile(Vec2(i, j));
            } else 
            if (distance < 1)
            {
                transformTile(Vec2(i, j), distance);
            }
            else
            {
                turnOnTile(Vec2(i, j));
            }
        }
    }
}

// implementation of FadeOutBLTiles

FadeOutBLTiles* FadeOutBLTiles::create(float duration, const Size& gridSize)
{
    FadeOutBLTiles *action = new (std::nothrow) FadeOutBLTiles();

    if (action)
    {
        if (action->initWithDuration(duration, gridSize))
        {
            action->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(action);
        }
    }

    return action;
}

FadeOutBLTiles* FadeOutBLTiles::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) FadeOutBLTiles();
    a->initWithDuration(_duration, _gridSize);
    a->autorelease();
    return a;
}

float FadeOutBLTiles::testFunc(const Size& pos, float time)
{
    Vec2 n = Vec2((float)_gridSize.width, (float)_gridSize.height) * (1.0f - time);
    if ((pos.width + pos.height) == 0)
    {
        return 1.0f;
    }

    return powf((n.x + n.y) / (pos.width + pos.height), 6);
}

// implementation of FadeOutUpTiles

FadeOutUpTiles* FadeOutUpTiles::create(float duration, const Size& gridSize)
{
    FadeOutUpTiles *action = new (std::nothrow) FadeOutUpTiles();

    if (action)
    {
        if (action->initWithDuration(duration, gridSize))
        {
            action->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(action);
        }
    }

    return action;
}

FadeOutUpTiles* FadeOutUpTiles::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) FadeOutUpTiles();
    a->initWithDuration(_duration, _gridSize);
    a->autorelease();
    return a;
}

float FadeOutUpTiles::testFunc(const Size& pos, float time)
{
    Vec2 n = Vec2((float)_gridSize.width, (float)_gridSize.height) * time;
    if (n.y == 0.0f)
    {
        return 1.0f;
    }

    return powf(pos.height / n.y, 6);
}

void FadeOutUpTiles::transformTile(const Vec2& pos, float distance)
{
    Quad3 coords = getOriginalTile(pos);
    Vec2 step = _gridNodeTarget->getGrid()->getStep();

    coords.bl.y += (step.y / 2) * (1.0f - distance);
    coords.br.y += (step.y / 2) * (1.0f - distance);
    coords.tl.y -= (step.y / 2) * (1.0f - distance);
    coords.tr.y -= (step.y / 2) * (1.0f - distance);

    setTile(pos, coords);
}

// implementation of FadeOutDownTiles

FadeOutDownTiles* FadeOutDownTiles::create(float duration, const Size& gridSize)
{
    FadeOutDownTiles *action = new (std::nothrow) FadeOutDownTiles();

    if (action)
    {
        if (action->initWithDuration(duration, gridSize))
        {
            action->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(action);
        }
    }

    return action;
}

FadeOutDownTiles* FadeOutDownTiles::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) FadeOutDownTiles();
    a->initWithDuration(_duration, _gridSize);
    a->autorelease();
    return a;
}

float FadeOutDownTiles::testFunc(const Size& pos, float time)
{
    Vec2 n = Vec2((float)_gridSize.width, (float)_gridSize.height) * (1.0f - time);
    if (pos.height == 0)
    {
        return 1.0f;
    }

    return powf(n.y / pos.height, 6);
}

// implementation of TurnOffTiles

TurnOffTiles* TurnOffTiles::create(float duration, const Size& gridSize)
{
    TurnOffTiles* pAction = new (std::nothrow) TurnOffTiles();
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
    TurnOffTiles *action = new (std::nothrow) TurnOffTiles();

    if (action)
    {
        if (action->initWithDuration(duration, gridSize, seed))
        {
            action->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(action);
        }
    }

    return action;
}

bool TurnOffTiles::initWithDuration(float duration, const Size& gridSize, unsigned int seed)
{
    if (TiledGrid3DAction::initWithDuration(duration, gridSize))
    {
        _seed = seed;
        _tilesOrder = nullptr;

        return true;
    }

    return false;
}

TurnOffTiles* TurnOffTiles::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) TurnOffTiles();
    a->initWithDuration(_duration, _gridSize, _seed );
    a->autorelease();
    return a;
}

TurnOffTiles::~TurnOffTiles(void)
{
    CC_SAFE_DELETE_ARRAY(_tilesOrder);
}

void TurnOffTiles::shuffle(unsigned int *array, unsigned int len)
{
    for (int i = len - 1; i >= 0; i--)
    {
        unsigned int j = rand() % (i+1);
        unsigned int v = array[i];
        array[i] = array[j];
        array[j] = v;
    }
}

void TurnOffTiles::turnOnTile(const Vec2& pos)
{
    setTile(pos, getOriginalTile(pos));
}

void TurnOffTiles::turnOffTile(const Vec2& pos)
{
    Quad3 coords;

    memset(&coords, 0, sizeof(Quad3));
    setTile(pos, coords);
}

void TurnOffTiles::startWithTarget(Node *target)
{
    TiledGrid3DAction::startWithTarget(target);

    if (_seed != (unsigned int)-1)
    {
        srand(_seed);
    }

    _tilesCount = _gridSize.width * _gridSize.height;
    _tilesOrder = new unsigned int[_tilesCount];

    for (unsigned int i = 0; i < _tilesCount; ++i)
    {
        _tilesOrder[i] = i;
    }

    shuffle(_tilesOrder, _tilesCount);
}

void TurnOffTiles::update(float time)
{
    unsigned int l = (unsigned int)(time * (float)_tilesCount);

    unsigned int t = 0;
    for (unsigned int i = 0; i < _tilesCount; i++ )
    {
        t = _tilesOrder[i];
        Vec2 tilePos( (unsigned int)(t / _gridSize.height), t % (unsigned int)_gridSize.height );

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
    WavesTiles3D *action = new (std::nothrow) WavesTiles3D();

    if (action)
    {
        if (action->initWithDuration(duration, gridSize, waves, amplitude))
        {
            action->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(action);
        }
    }

    return action;
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
    auto a = new (std::nothrow) WavesTiles3D();
    a->initWithDuration(_duration, _gridSize, _waves, _amplitude);
    a->autorelease();
    return a;
}

void WavesTiles3D::update(float time)
{
    for (int i = 0; i < _gridSize.width; i++ )
    {
        for (int j = 0; j < _gridSize.height; j++ )
        {
            Quad3 coords = getOriginalTile(Vec2(i, j));

            coords.bl.z = (sinf(time * (float)M_PI  *_waves * 2 + 
                (coords.bl.y+coords.bl.x) * .01f) * _amplitude * _amplitudeRate );
            coords.br.z    = coords.bl.z;
            coords.tl.z = coords.bl.z;
            coords.tr.z = coords.bl.z;

            setTile(Vec2(i, j), coords);
        }
    }
}

// implementation of JumpTiles3D

JumpTiles3D* JumpTiles3D::create(float duration, const Size& gridSize, unsigned int numberOfJumps, float amplitude)
{
    JumpTiles3D *action = new (std::nothrow) JumpTiles3D();

    if (action)
    {
        if (action->initWithDuration(duration, gridSize, numberOfJumps, amplitude))
        {
            action->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(action);
        }
    }

    return action;
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
    auto a = new (std::nothrow) JumpTiles3D();
    a->initWithDuration(_duration, _gridSize, _jumps, _amplitude);
    a->autorelease();
    return a;
}

void JumpTiles3D::update(float time)
{
    float sinz =  (sinf((float)M_PI * time * _jumps * 2) * _amplitude * _amplitudeRate );
    float sinz2 = (sinf((float)M_PI * (time * _jumps * 2 + 1)) * _amplitude * _amplitudeRate );

    for (int i = 0; i < _gridSize.width; i++ )
    {
        for (int j = 0; j < _gridSize.height; j++ )
        {
            Quad3 coords = getOriginalTile(Vec2(i, j));

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

            setTile(Vec2(i, j), coords);
        }
    }
}

// implementation of SplitRows

SplitRows* SplitRows::create(float duration, unsigned int nRows)
{
    SplitRows *action = new (std::nothrow) SplitRows();

    if (action)
    {
        if (action->initWithDuration(duration, nRows))
        {
            action->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(action);
        }
    }

    return action;
}

bool SplitRows::initWithDuration(float duration, unsigned int rows)
{
    _rows = rows;

    return TiledGrid3DAction::initWithDuration(duration, Size(1, rows));
}

SplitRows* SplitRows::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) SplitRows();
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
    for (unsigned int j = 0; j < _gridSize.height; ++j)
    {
        Quad3 coords = getOriginalTile(Vec2(0, j));
        float    direction = 1;

        if ( (j % 2 ) == 0 )
        {
            direction = -1;
        }

        coords.bl.x += direction * _winSize.width * time;
        coords.br.x += direction * _winSize.width * time;
        coords.tl.x += direction * _winSize.width * time;
        coords.tr.x += direction * _winSize.width * time;

        setTile(Vec2(0, j), coords);
    }
}

// implementation of SplitCols

SplitCols* SplitCols::create(float duration, unsigned int cols)
{
    SplitCols *action = new (std::nothrow) SplitCols();

    if (action)
    {
        if (action->initWithDuration(duration, cols))
        {
            action->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(action);
        }
    }

    return action;
}

bool SplitCols::initWithDuration(float duration, unsigned int cols)
{
    _cols = cols;
    return TiledGrid3DAction::initWithDuration(duration, Size(cols, 1));
}

SplitCols* SplitCols::clone() const
{
    // no copy constructor    
    auto a = new (std::nothrow) SplitCols();
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
    for (unsigned int i = 0; i < _gridSize.width; ++i)
    {
        Quad3 coords = getOriginalTile(Vec2(i, 0));
        float    direction = 1;

        if ( (i % 2 ) == 0 )
        {
            direction = -1;
        }

        coords.bl.y += direction * _winSize.height * time;
        coords.br.y += direction * _winSize.height * time;
        coords.tl.y += direction * _winSize.height * time;
        coords.tr.y += direction * _winSize.height * time;

        setTile(Vec2(i, 0), coords);
    }
}

NS_CC_END
