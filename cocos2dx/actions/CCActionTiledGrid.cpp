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
#include "support/CCPointExtension.h"
#include "effects/CCGrid.h"
#include "cocoa/CCZone.h"
#include <stdlib.h>

NS_CC_BEGIN

struct Tile
{
    CCPoint    position;
    CCPoint    startPosition;
    CCSize    delta;
};

// implementation of ShakyTiles3D

CCShakyTiles3D* CCShakyTiles3D::create(float duration, const CCSize& gridSize, int nRange, bool bShakeZ)
{
    CCShakyTiles3D *pAction = new CCShakyTiles3D();

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

bool CCShakyTiles3D::initWithDuration(float duration, const CCSize& gridSize, int nRange, bool bShakeZ)
{
    if (CCTiledGrid3DAction::initWithDuration(duration, gridSize))
    {
        _randrange = nRange;
        _shakeZ = bShakeZ;

        return true;
    }

    return false;
}

CCShakyTiles3D* CCShakyTiles3D::clone() const
{
	// no copy constructor	
	auto a = new CCShakyTiles3D();
    a->initWithDuration(_duration, _gridSize, _randrange, _shakeZ);
	a->autorelease();
	return a;
}

CCObject* CCShakyTiles3D::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCShakyTiles3D* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCShakyTiles3D*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCShakyTiles3D();
        pZone = pNewZone = new CCZone(pCopy);
    }
    
    CCTiledGrid3DAction::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _gridSize, _randrange, _shakeZ);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCShakyTiles3D::update(float time)
{
    CC_UNUSED_PARAM(time);
    int i, j;

    for (i = 0; i < _gridSize.width; ++i)
    {
        for (j = 0; j < _gridSize.height; ++j)
        {
            ccQuad3 coords = originalTile(ccp(i, j));

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
                        
            setTile(ccp(i, j), coords);
        }
    }
}

// implementation of CCShatteredTiles3D

CCShatteredTiles3D* CCShatteredTiles3D::create(float duration, const CCSize& gridSize, int nRange, bool bShatterZ)
{
    CCShatteredTiles3D *pAction = new CCShatteredTiles3D();

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

bool CCShatteredTiles3D::initWithDuration(float duration, const CCSize& gridSize, int nRange, bool bShatterZ)
{
    if (CCTiledGrid3DAction::initWithDuration(duration, gridSize))
    {
        _once = false;
        _randrange = nRange;
        _shatterZ = bShatterZ;

        return true;
    }

    return false;
}

CCShatteredTiles3D* CCShatteredTiles3D::clone() const
{
	// no copy constructor	
	auto a = new CCShatteredTiles3D();
	a->initWithDuration(_duration, _gridSize, _randrange, _shatterZ);
	a->autorelease();
	return a;
}

CCObject* CCShatteredTiles3D::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCShatteredTiles3D* pCopy = NULL;
    if(pZone && pZone->_copyObject)
    {
        pCopy = (CCShatteredTiles3D*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCShatteredTiles3D();
        pZone = pNewZone = new CCZone(pCopy);
    }

    //copy super class's member
    CCTiledGrid3DAction::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _gridSize, _randrange, _shatterZ);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCShatteredTiles3D::update(float time)
{
    CC_UNUSED_PARAM(time);
    int i, j;

    if (_once == false)
    {
        for (i = 0; i < _gridSize.width; ++i)
        {
            for (j = 0; j < _gridSize.height; ++j)
            {
                ccQuad3 coords = originalTile(ccp(i ,j));
                
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
                
                setTile(ccp(i, j), coords);
            }
        }
        
        _once = true;
    }
}

// implementation of CCShuffleTiles

CCShuffleTiles* CCShuffleTiles::create(float duration, const CCSize& gridSize, unsigned int seed)
{
    CCShuffleTiles *pAction = new CCShuffleTiles();

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

bool CCShuffleTiles::initWithDuration(float duration, const CCSize& gridSize, unsigned int seed)
{
    if (CCTiledGrid3DAction::initWithDuration(duration, gridSize))
    {
        _seed = seed;
        _tilesOrder = NULL;
        _tiles = NULL;

        return true;
    }

    return false;
}

CCShuffleTiles* CCShuffleTiles::clone() const
{
	// no copy constructor
	auto a = new CCShuffleTiles();
	a->initWithDuration(_duration, _gridSize, _seed);
	a->autorelease();
	return a;
}

CCObject* CCShuffleTiles::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCShuffleTiles* pCopy = NULL;
    if(pZone && pZone->_copyObject)
    {
        pCopy = (CCShuffleTiles*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCShuffleTiles();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCTiledGrid3DAction::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _gridSize, _seed);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

CCShuffleTiles::~CCShuffleTiles(void)
{
    CC_SAFE_DELETE_ARRAY(_tilesOrder);
    CC_SAFE_DELETE_ARRAY(_tiles);
}

void CCShuffleTiles::shuffle(unsigned int *pArray, unsigned int nLen)
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

CCSize CCShuffleTiles::getDelta(const CCSize& pos)
{
    CCPoint    pos2;

    unsigned int idx = pos.width * _gridSize.height + pos.height;

    pos2.x = (float)(_tilesOrder[idx] / (int)_gridSize.height);
    pos2.y = (float)(_tilesOrder[idx] % (int)_gridSize.height);

    return CCSizeMake((int)(pos2.x - pos.width), (int)(pos2.y - pos.height));
}

void CCShuffleTiles::placeTile(const CCPoint& pos, Tile *t)
{
    ccQuad3 coords = originalTile(pos);

    CCPoint step = _target->getGrid()->getStep();
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

void CCShuffleTiles::startWithTarget(CCNode *pTarget)
{
    CCTiledGrid3DAction::startWithTarget(pTarget);

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
            tileArray->position = ccp((float)i, (float)j);
            tileArray->startPosition = ccp((float)i, (float)j);
            tileArray->delta = getDelta(CCSizeMake(i, j));
            ++tileArray;
        }
    }
}

void CCShuffleTiles::update(float time)
{
    int i, j;

    Tile *tileArray = (Tile*)_tiles;

    for (i = 0; i < _gridSize.width; ++i)
    {
        for (j = 0; j < _gridSize.height; ++j)
        {
            tileArray->position = ccpMult(ccp((float)tileArray->delta.width, (float)tileArray->delta.height), time);
            placeTile(ccp(i, j), tileArray);
            ++tileArray;
        }
    }
}

// implementation of CCFadeOutTRTiles

CCFadeOutTRTiles* CCFadeOutTRTiles::create(float duration, const CCSize& gridSize)
{
    CCFadeOutTRTiles *pAction = new CCFadeOutTRTiles();

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

CCFadeOutTRTiles* CCFadeOutTRTiles::clone() const
{
	// no copy constructor
	auto a = new CCFadeOutTRTiles();
	a->initWithDuration(_duration, _gridSize);
	a->autorelease();
	return a;
}

float CCFadeOutTRTiles::testFunc(const CCSize& pos, float time)
{
    CCPoint n = ccpMult(ccp((float)_gridSize.width, (float)_gridSize.height), time);
    if ((n.x + n.y) == 0.0f)
    {
        return 1.0f;
    }

    return powf((pos.width + pos.height) / (n.x + n.y), 6);
}

void CCFadeOutTRTiles::turnOnTile(const CCPoint& pos)
{
    setTile(pos, originalTile(pos));
}

void CCFadeOutTRTiles::turnOffTile(const CCPoint& pos)
{
    ccQuad3 coords;
    memset(&coords, 0, sizeof(ccQuad3));
    setTile(pos, coords);
}

void CCFadeOutTRTiles::transformTile(const CCPoint& pos, float distance)
{
    ccQuad3 coords = originalTile(pos);
    CCPoint step = _target->getGrid()->getStep();

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

void CCFadeOutTRTiles::update(float time)
{
    int i, j;

    for (i = 0; i < _gridSize.width; ++i)
    {
        for (j = 0; j < _gridSize.height; ++j)
        {
            float distance = testFunc(CCSizeMake(i, j), time);
            if ( distance == 0 )
            {
                turnOffTile(ccp(i, j));
            } else 
            if (distance < 1)
            {
                transformTile(ccp(i, j), distance);
            }
            else
            {
                turnOnTile(ccp(i, j));
            }
        }
    }
}

// implementation of CCFadeOutBLTiles

CCFadeOutBLTiles* CCFadeOutBLTiles::create(float duration, const CCSize& gridSize)
{
    CCFadeOutBLTiles *pAction = new CCFadeOutBLTiles();

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

CCFadeOutBLTiles* CCFadeOutBLTiles::clone() const
{
	// no copy constructor
	auto a = new CCFadeOutBLTiles();
	a->initWithDuration(_duration, _gridSize);
	a->autorelease();
	return a;
}

float CCFadeOutBLTiles::testFunc(const CCSize& pos, float time)
{
    CCPoint n = ccpMult(ccp((float)_gridSize.width, (float)_gridSize.height), (1.0f - time));
    if ((pos.width + pos.height) == 0)
    {
        return 1.0f;
    }

    return powf((n.x + n.y) / (pos.width + pos.height), 6);
}

// implementation of CCFadeOutUpTiles

CCFadeOutUpTiles* CCFadeOutUpTiles::create(float duration, const CCSize& gridSize)
{
    CCFadeOutUpTiles *pAction = new CCFadeOutUpTiles();

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

CCFadeOutUpTiles* CCFadeOutUpTiles::clone() const
{
	// no copy constructor
	auto a = new CCFadeOutUpTiles();
	a->initWithDuration(_duration, _gridSize);
	a->autorelease();
	return a;
}

float CCFadeOutUpTiles::testFunc(const CCSize& pos, float time)
{
    CCPoint n = ccpMult(ccp((float)_gridSize.width, (float)_gridSize.height), time);
    if (n.y == 0.0f)
    {
        return 1.0f;
    }

    return powf(pos.height / n.y, 6);
}

void CCFadeOutUpTiles::transformTile(const CCPoint& pos, float distance)
{
    ccQuad3 coords = originalTile(pos);
    CCPoint step = _target->getGrid()->getStep();

    coords.bl.y += (step.y / 2) * (1.0f - distance);
    coords.br.y += (step.y / 2) * (1.0f - distance);
    coords.tl.y -= (step.y / 2) * (1.0f - distance);
    coords.tr.y -= (step.y / 2) * (1.0f - distance);

    setTile(pos, coords);
}

// implementation of CCFadeOutDownTiles

CCFadeOutDownTiles* CCFadeOutDownTiles::create(float duration, const CCSize& gridSize)
{
    CCFadeOutDownTiles *pAction = new CCFadeOutDownTiles();

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

CCFadeOutDownTiles* CCFadeOutDownTiles::clone() const
{
	// no copy constructor
	auto a = new CCFadeOutDownTiles();
	a->initWithDuration(_duration, _gridSize);
	a->autorelease();
	return a;
}

float CCFadeOutDownTiles::testFunc(const CCSize& pos, float time)
{
    CCPoint n = ccpMult(ccp((float)_gridSize.width, (float)_gridSize.height), (1.0f - time));
    if (pos.height == 0)
    {
        return 1.0f;
    }

    return powf(n.y / pos.height, 6);
}

// implementation of TurnOffTiles

CCTurnOffTiles* CCTurnOffTiles::create(float duration, const CCSize& gridSize)
{
    CCTurnOffTiles* pAction = new CCTurnOffTiles();
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

CCTurnOffTiles* CCTurnOffTiles::create(float duration, const CCSize& gridSize, unsigned int seed)
{
    CCTurnOffTiles *pAction = new CCTurnOffTiles();

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

bool CCTurnOffTiles::initWithDuration(float duration, const CCSize& gridSize, unsigned int seed)
{
    if (CCTiledGrid3DAction::initWithDuration(duration, gridSize))
    {
        _seed = seed;
        _tilesOrder = NULL;

        return true;
    }

    return false;
}

CCTurnOffTiles* CCTurnOffTiles::clone() const
{
	// no copy constructor
	auto a = new CCTurnOffTiles();
    a->initWithDuration(_duration, _gridSize, _seed );
	a->autorelease();
	return a;
}

CCObject* CCTurnOffTiles::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCTurnOffTiles* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        pCopy = (CCTurnOffTiles*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCTurnOffTiles();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCTiledGrid3DAction::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _gridSize, _seed );

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

CCTurnOffTiles::~CCTurnOffTiles(void)
{
    CC_SAFE_DELETE_ARRAY(_tilesOrder);
}

void CCTurnOffTiles::shuffle(unsigned int *pArray, unsigned int nLen)
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

void CCTurnOffTiles::turnOnTile(const CCPoint& pos)
{
    setTile(pos, originalTile(pos));
}

void CCTurnOffTiles::turnOffTile(const CCPoint& pos)
{
    ccQuad3 coords;

    memset(&coords, 0, sizeof(ccQuad3));
    setTile(pos, coords);
}

void CCTurnOffTiles::startWithTarget(CCNode *pTarget)
{
    unsigned int i;

    CCTiledGrid3DAction::startWithTarget(pTarget);

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

void CCTurnOffTiles::update(float time)
{
    unsigned int i, l, t;

    l = (unsigned int)(time * (float)_tilesCount);

    for( i = 0; i < _tilesCount; i++ )
    {
        t = _tilesOrder[i];
        CCPoint tilePos = ccp( (unsigned int)(t / _gridSize.height), t % (unsigned int)_gridSize.height );

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

// implementation of CCWavesTiles3D

CCWavesTiles3D* CCWavesTiles3D::create(float duration, const CCSize& gridSize, unsigned int waves, float amplitude)
{
    CCWavesTiles3D *pAction = new CCWavesTiles3D();

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

bool CCWavesTiles3D::initWithDuration(float duration, const CCSize& gridSize, unsigned int waves, float amplitude)
{
    if (CCTiledGrid3DAction::initWithDuration(duration, gridSize))
    {
        _waves = waves;
        _amplitude = amplitude;
        _amplitudeRate = 1.0f;

        return true;
    }

    return false;
}

CCWavesTiles3D* CCWavesTiles3D::clone() const
{
	// no copy constructor
	auto a = new CCWavesTiles3D();
    a->initWithDuration(_duration, _gridSize, _waves, _amplitude);
	a->autorelease();
	return a;
}

CCObject* CCWavesTiles3D::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCWavesTiles3D* pCopy = NULL;
    if(pZone && pZone->_copyObject)
    {
        pCopy = (CCWavesTiles3D*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCWavesTiles3D();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCTiledGrid3DAction::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _gridSize, _waves, _amplitude);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCWavesTiles3D::update(float time)
{
    int i, j;

    for( i = 0; i < _gridSize.width; i++ )
    {
        for( j = 0; j < _gridSize.height; j++ )
        {
            ccQuad3 coords = originalTile(ccp(i, j));

            coords.bl.z = (sinf(time * (float)M_PI  *_waves * 2 + 
                (coords.bl.y+coords.bl.x) * .01f) * _amplitude * _amplitudeRate );
            coords.br.z    = coords.bl.z;
            coords.tl.z = coords.bl.z;
            coords.tr.z = coords.bl.z;

            setTile(ccp(i, j), coords);
        }
    }
}

// implementation of CCJumpTiles3D

CCJumpTiles3D* CCJumpTiles3D::create(float duration, const CCSize& gridSize, unsigned int numberOfJumps, float amplitude)
{
    CCJumpTiles3D *pAction = new CCJumpTiles3D();

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

bool CCJumpTiles3D::initWithDuration(float duration, const CCSize& gridSize, unsigned int numberOfJumps, float amplitude)
{
    if (CCTiledGrid3DAction::initWithDuration(duration, gridSize))
    {
        _jumps = numberOfJumps;
        _amplitude = amplitude;
        _amplitudeRate = 1.0f;

        return true;
    }

    return false;
}

CCJumpTiles3D* CCJumpTiles3D::clone() const
{
	// no copy constructor
	auto a = new CCJumpTiles3D();
    a->initWithDuration(_duration, _gridSize, _jumps, _amplitude);
	a->autorelease();
	return a;
}

CCObject* CCJumpTiles3D::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCJumpTiles3D* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        pCopy = (CCJumpTiles3D*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCJumpTiles3D();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCTiledGrid3DAction::copyWithZone(pZone);
    pCopy->initWithDuration(_duration, _gridSize, _jumps, _amplitude);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCJumpTiles3D::update(float time)
{
    int i, j;

    float sinz =  (sinf((float)M_PI * time * _jumps * 2) * _amplitude * _amplitudeRate );
    float sinz2 = (sinf((float)M_PI * (time * _jumps * 2 + 1)) * _amplitude * _amplitudeRate );

    for( i = 0; i < _gridSize.width; i++ )
    {
        for( j = 0; j < _gridSize.height; j++ )
        {
            ccQuad3 coords = originalTile(ccp(i, j));

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

            setTile(ccp(i, j), coords);
        }
    }
}

// implementation of CCSplitRows

CCSplitRows* CCSplitRows::create(float duration, unsigned int nRows)
{
    CCSplitRows *pAction = new CCSplitRows();

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

bool CCSplitRows::initWithDuration(float duration, unsigned int nRows)
{
    _rows = nRows;

    return CCTiledGrid3DAction::initWithDuration(duration, CCSizeMake(1, nRows));
}

CCSplitRows* CCSplitRows::clone() const
{
	// no copy constructor
	auto a = new CCSplitRows();
    a->initWithDuration(_duration, _rows);
	a->autorelease();
	return a;
}

CCObject* CCSplitRows::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCSplitRows* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        pCopy = (CCSplitRows*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCSplitRows();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCTiledGrid3DAction::copyWithZone(pZone);

    pCopy->initWithDuration(_duration, _rows);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCSplitRows::startWithTarget(CCNode *pTarget)
{
    CCTiledGrid3DAction::startWithTarget(pTarget);
    _winSize = CCDirector::sharedDirector()->getWinSizeInPixels();
}

void CCSplitRows::update(float time)
{
    unsigned int j;

    for (j = 0; j < _gridSize.height; ++j)
    {
        ccQuad3 coords = originalTile(ccp(0, j));
        float    direction = 1;

        if ( (j % 2 ) == 0 )
        {
            direction = -1;
        }

        coords.bl.x += direction * _winSize.width * time;
        coords.br.x += direction * _winSize.width * time;
        coords.tl.x += direction * _winSize.width * time;
        coords.tr.x += direction * _winSize.width * time;

        setTile(ccp(0, j), coords);
    }
}

// implementation of CCSplitCols

CCSplitCols* CCSplitCols::create(float duration, unsigned int nCols)
{
    CCSplitCols *pAction = new CCSplitCols();

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

bool CCSplitCols::initWithDuration(float duration, unsigned int nCols)
{
    _cols = nCols;
    return CCTiledGrid3DAction::initWithDuration(duration, CCSizeMake(nCols, 1));
}

CCSplitCols* CCSplitCols::clone() const
{
	// no copy constructor	
	auto a = new CCSplitCols();
    a->initWithDuration(_duration, _cols);
	a->autorelease();
	return a;
}

CCObject* CCSplitCols::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCSplitCols* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        pCopy = (CCSplitCols*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCSplitCols();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCTiledGrid3DAction::copyWithZone(pZone);
    pCopy->initWithDuration(_duration, _cols);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCSplitCols::startWithTarget(CCNode *pTarget)
{
    CCTiledGrid3DAction::startWithTarget(pTarget);
    _winSize = CCDirector::sharedDirector()->getWinSizeInPixels();
}

void CCSplitCols::update(float time)
{
    unsigned int i;

    for (i = 0; i < _gridSize.width; ++i)
    {
        ccQuad3 coords = originalTile(ccp(i, 0));
        float    direction = 1;

        if ( (i % 2 ) == 0 )
        {
            direction = -1;
        }

        coords.bl.y += direction * _winSize.height * time;
        coords.br.y += direction * _winSize.height * time;
        coords.tl.y += direction * _winSize.height * time;
        coords.tr.y += direction * _winSize.height * time;

        setTile(ccp(i, 0), coords);
    }
}

NS_CC_END
