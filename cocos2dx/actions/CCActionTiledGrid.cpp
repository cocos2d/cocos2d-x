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
        m_nRandrange = nRange;
        m_bShakeZ = bShakeZ;

        return true;
    }

    return false;
}

CCObject* CCShakyTiles3D::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCShakyTiles3D* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCShakyTiles3D*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCShakyTiles3D();
        pZone = pNewZone = new CCZone(pCopy);
    }
    
    CCTiledGrid3DAction::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, m_sGridSize, m_nRandrange, m_bShakeZ);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCShakyTiles3D::update(float time)
{
    CC_UNUSED_PARAM(time);
    int i, j;

    for (i = 0; i < m_sGridSize.width; ++i)
    {
        for (j = 0; j < m_sGridSize.height; ++j)
        {
            ccQuad3 coords = originalTile(ccp(i, j));

            // X
            coords.bl.x += ( rand() % (m_nRandrange*2) ) - m_nRandrange;
            coords.br.x += ( rand() % (m_nRandrange*2) ) - m_nRandrange;
            coords.tl.x += ( rand() % (m_nRandrange*2) ) - m_nRandrange;
            coords.tr.x += ( rand() % (m_nRandrange*2) ) - m_nRandrange;

            // Y
            coords.bl.y += ( rand() % (m_nRandrange*2) ) - m_nRandrange;
            coords.br.y += ( rand() % (m_nRandrange*2) ) - m_nRandrange;
            coords.tl.y += ( rand() % (m_nRandrange*2) ) - m_nRandrange;
            coords.tr.y += ( rand() % (m_nRandrange*2) ) - m_nRandrange;

            if (m_bShakeZ)
            {
                coords.bl.z += ( rand() % (m_nRandrange*2) ) - m_nRandrange;
                coords.br.z += ( rand() % (m_nRandrange*2) ) - m_nRandrange;
                coords.tl.z += ( rand() % (m_nRandrange*2) ) - m_nRandrange;
                coords.tr.z += ( rand() % (m_nRandrange*2) ) - m_nRandrange;
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
        m_bOnce = false;
        m_nRandrange = nRange;
        m_bShatterZ = bShatterZ;

        return true;
    }

    return false;
}

CCObject* CCShatteredTiles3D::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCShatteredTiles3D* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        pCopy = (CCShatteredTiles3D*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCShatteredTiles3D();
        pZone = pNewZone = new CCZone(pCopy);
    }

    //copy super class's member
    CCTiledGrid3DAction::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, m_sGridSize, m_nRandrange, m_bShatterZ);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCShatteredTiles3D::update(float time)
{
    CC_UNUSED_PARAM(time);
    int i, j;

    if (m_bOnce == false)
    {
        for (i = 0; i < m_sGridSize.width; ++i)
        {
            for (j = 0; j < m_sGridSize.height; ++j)
            {
                ccQuad3 coords = originalTile(ccp(i ,j));
                
                // X
                coords.bl.x += ( rand() % (m_nRandrange*2) ) - m_nRandrange;
                coords.br.x += ( rand() % (m_nRandrange*2) ) - m_nRandrange;
                coords.tl.x += ( rand() % (m_nRandrange*2) ) - m_nRandrange;
                coords.tr.x += ( rand() % (m_nRandrange*2) ) - m_nRandrange;
                
                // Y
                coords.bl.y += ( rand() % (m_nRandrange*2) ) - m_nRandrange;
                coords.br.y += ( rand() % (m_nRandrange*2) ) - m_nRandrange;
                coords.tl.y += ( rand() % (m_nRandrange*2) ) - m_nRandrange;
                coords.tr.y += ( rand() % (m_nRandrange*2) ) - m_nRandrange;

                if (m_bShatterZ) 
                {
                    coords.bl.z += ( rand() % (m_nRandrange*2) ) - m_nRandrange;
                    coords.br.z += ( rand() % (m_nRandrange*2) ) - m_nRandrange;                
                    coords.tl.z += ( rand() % (m_nRandrange*2) ) - m_nRandrange;
                    coords.tr.z += ( rand() % (m_nRandrange*2) ) - m_nRandrange;
                }
                
                setTile(ccp(i, j), coords);
            }
        }
        
        m_bOnce = true;
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
        m_nSeed = seed;
        m_pTilesOrder = NULL;
        m_pTiles = NULL;

        return true;
    }

    return false;
}

CCObject* CCShuffleTiles::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCShuffleTiles* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        pCopy = (CCShuffleTiles*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCShuffleTiles();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCTiledGrid3DAction::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, m_sGridSize, m_nSeed);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

CCShuffleTiles::~CCShuffleTiles(void)
{
    CC_SAFE_DELETE_ARRAY(m_pTilesOrder);
    CC_SAFE_DELETE_ARRAY(m_pTiles);
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

    unsigned int idx = pos.width * m_sGridSize.height + pos.height;

    pos2.x = (float)(m_pTilesOrder[idx] / (int)m_sGridSize.height);
    pos2.y = (float)(m_pTilesOrder[idx] % (int)m_sGridSize.height);

    return CCSizeMake((int)(pos2.x - pos.width), (int)(pos2.y - pos.height));
}

void CCShuffleTiles::placeTile(const CCPoint& pos, Tile *t)
{
    ccQuad3 coords = originalTile(pos);

    CCPoint step = m_pTarget->getGrid()->getStep();
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

    if (m_nSeed != (unsigned int)-1)
    {
        srand(m_nSeed);
    }

    m_nTilesCount = m_sGridSize.width * m_sGridSize.height;
    m_pTilesOrder = new unsigned int[m_nTilesCount];
    int i, j;
    unsigned int k;

    /**
     * Use k to loop. Because m_nTilesCount is unsigned int,
     * and i is used later for int.
     */
    for (k = 0; k < m_nTilesCount; ++k)
    {
        m_pTilesOrder[k] = k;
    }

    shuffle(m_pTilesOrder, m_nTilesCount);

    m_pTiles = (struct Tile *)new Tile[m_nTilesCount];
    Tile *tileArray = (Tile*) m_pTiles;

    for (i = 0; i < m_sGridSize.width; ++i)
    {
        for (j = 0; j < m_sGridSize.height; ++j)
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

    Tile *tileArray = (Tile*)m_pTiles;

    for (i = 0; i < m_sGridSize.width; ++i)
    {
        for (j = 0; j < m_sGridSize.height; ++j)
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

float CCFadeOutTRTiles::testFunc(const CCSize& pos, float time)
{
    CCPoint n = ccpMult(ccp((float)m_sGridSize.width, (float)m_sGridSize.height), time);
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
    CCPoint step = m_pTarget->getGrid()->getStep();

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

    for (i = 0; i < m_sGridSize.width; ++i)
    {
        for (j = 0; j < m_sGridSize.height; ++j)
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

float CCFadeOutBLTiles::testFunc(const CCSize& pos, float time)
{
    CCPoint n = ccpMult(ccp((float)m_sGridSize.width, (float)m_sGridSize.height), (1.0f - time));
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

float CCFadeOutUpTiles::testFunc(const CCSize& pos, float time)
{
    CCPoint n = ccpMult(ccp((float)m_sGridSize.width, (float)m_sGridSize.height), time);
    if (n.y == 0.0f)
    {
        return 1.0f;
    }

    return powf(pos.height / n.y, 6);
}

void CCFadeOutUpTiles::transformTile(const CCPoint& pos, float distance)
{
    ccQuad3 coords = originalTile(pos);
    CCPoint step = m_pTarget->getGrid()->getStep();

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

float CCFadeOutDownTiles::testFunc(const CCSize& pos, float time)
{
    CCPoint n = ccpMult(ccp((float)m_sGridSize.width, (float)m_sGridSize.height), (1.0f - time));
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
        m_nSeed = seed;
        m_pTilesOrder = NULL;

        return true;
    }

    return false;
}

CCObject* CCTurnOffTiles::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCTurnOffTiles* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        pCopy = (CCTurnOffTiles*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCTurnOffTiles();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCTiledGrid3DAction::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, m_sGridSize, m_nSeed );

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

CCTurnOffTiles::~CCTurnOffTiles(void)
{
    CC_SAFE_DELETE_ARRAY(m_pTilesOrder);
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

    if (m_nSeed != (unsigned int)-1)
    {
        srand(m_nSeed);
    }

    m_nTilesCount = m_sGridSize.width * m_sGridSize.height;
    m_pTilesOrder = new unsigned int[m_nTilesCount];

    for (i = 0; i < m_nTilesCount; ++i)
    {
        m_pTilesOrder[i] = i;
    }

    shuffle(m_pTilesOrder, m_nTilesCount);
}

void CCTurnOffTiles::update(float time)
{
    unsigned int i, l, t;

    l = (unsigned int)(time * (float)m_nTilesCount);

    for( i = 0; i < m_nTilesCount; i++ )
    {
        t = m_pTilesOrder[i];
        CCPoint tilePos = ccp( (unsigned int)(t / m_sGridSize.height), t % (unsigned int)m_sGridSize.height );

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
        m_nWaves = waves;
        m_fAmplitude = amplitude;
        m_fAmplitudeRate = 1.0f;

        return true;
    }

    return false;
}

CCObject* CCWavesTiles3D::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCWavesTiles3D* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        pCopy = (CCWavesTiles3D*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCWavesTiles3D();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCTiledGrid3DAction::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, m_sGridSize, m_nWaves, m_fAmplitude);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCWavesTiles3D::update(float time)
{
    int i, j;

    for( i = 0; i < m_sGridSize.width; i++ )
    {
        for( j = 0; j < m_sGridSize.height; j++ )
        {
            ccQuad3 coords = originalTile(ccp(i, j));

            coords.bl.z = (sinf(time * (float)M_PI  *m_nWaves * 2 + 
                (coords.bl.y+coords.bl.x) * .01f) * m_fAmplitude * m_fAmplitudeRate );
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
        m_nJumps = numberOfJumps;
        m_fAmplitude = amplitude;
        m_fAmplitudeRate = 1.0f;

        return true;
    }

    return false;
}

CCObject* CCJumpTiles3D::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCJumpTiles3D* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        pCopy = (CCJumpTiles3D*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCJumpTiles3D();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCTiledGrid3DAction::copyWithZone(pZone);
    pCopy->initWithDuration(m_fDuration, m_sGridSize, m_nJumps, m_fAmplitude);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCJumpTiles3D::update(float time)
{
    int i, j;

    float sinz =  (sinf((float)M_PI * time * m_nJumps * 2) * m_fAmplitude * m_fAmplitudeRate );
    float sinz2 = (sinf((float)M_PI * (time * m_nJumps * 2 + 1)) * m_fAmplitude * m_fAmplitudeRate );

    for( i = 0; i < m_sGridSize.width; i++ )
    {
        for( j = 0; j < m_sGridSize.height; j++ )
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
    m_nRows = nRows;

    return CCTiledGrid3DAction::initWithDuration(duration, CCSizeMake(1, nRows));
}

CCObject* CCSplitRows::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCSplitRows* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        pCopy = (CCSplitRows*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCSplitRows();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCTiledGrid3DAction::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, m_nRows);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCSplitRows::startWithTarget(CCNode *pTarget)
{
    CCTiledGrid3DAction::startWithTarget(pTarget);
    m_winSize = CCDirector::sharedDirector()->getWinSizeInPixels();
}

void CCSplitRows::update(float time)
{
    unsigned int j;

    for (j = 0; j < m_sGridSize.height; ++j)
    {
        ccQuad3 coords = originalTile(ccp(0, j));
        float    direction = 1;

        if ( (j % 2 ) == 0 )
        {
            direction = -1;
        }

        coords.bl.x += direction * m_winSize.width * time;
        coords.br.x += direction * m_winSize.width * time;
        coords.tl.x += direction * m_winSize.width * time;
        coords.tr.x += direction * m_winSize.width * time;

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
    m_nCols = nCols;
    return CCTiledGrid3DAction::initWithDuration(duration, CCSizeMake(nCols, 1));
}

CCObject* CCSplitCols::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCSplitCols* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        pCopy = (CCSplitCols*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCSplitCols();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCTiledGrid3DAction::copyWithZone(pZone);
    pCopy->initWithDuration(m_fDuration, m_nCols);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCSplitCols::startWithTarget(CCNode *pTarget)
{
    CCTiledGrid3DAction::startWithTarget(pTarget);
    m_winSize = CCDirector::sharedDirector()->getWinSizeInPixels();
}

void CCSplitCols::update(float time)
{
    unsigned int i;

    for (i = 0; i < m_sGridSize.width; ++i)
    {
        ccQuad3 coords = originalTile(ccp(i, 0));
        float    direction = 1;

        if ( (i % 2 ) == 0 )
        {
            direction = -1;
        }

        coords.bl.y += direction * m_winSize.height * time;
        coords.br.y += direction * m_winSize.height * time;
        coords.tl.y += direction * m_winSize.height * time;
        coords.tr.y += direction * m_winSize.height * time;

        setTile(ccp(i, 0), coords);
    }
}

NS_CC_END
