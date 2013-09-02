/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#include "CCSkin.h"
#include "../utils/CCTransformHelp.h"
#include "../utils/CCSpriteFrameCacheHelper.h"
#include "../CCArmature.h"

NS_CC_EXT_BEGIN

#if CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
#define RENDER_IN_SUBPIXEL
#else
#define RENDER_IN_SUBPIXEL(__ARGS__) (ceil(__ARGS__))
#endif

CCSkin *CCSkin::create()
{
    CCSkin *skin = new CCSkin();
    if(skin && skin->init())
    {
        skin->autorelease();
        return skin;
    }
    CC_SAFE_DELETE(skin);
    return NULL;
}

CCSkin *CCSkin::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
    CCSkin *skin = new CCSkin();
    if(skin && skin->initWithSpriteFrameName(pszSpriteFrameName))
    {
        skin->autorelease();
        return skin;
    }
    CC_SAFE_DELETE(skin);
    return NULL;
}

CCSkin *CCSkin::create(const char *pszFileName)
{
	CCSkin *skin = new CCSkin();
	if(skin && skin->initWithFile(pszFileName))
	{
		skin->autorelease();
		return skin;
	}
	CC_SAFE_DELETE(skin);
	return NULL;
}

CCSkin::CCSkin()
    : m_pBone(NULL)
	, m_strDisplayName("")
{
	m_tSkinTransform = CCAffineTransformIdentity;
}

bool CCSkin::initWithSpriteFrameName(const char *pszSpriteFrameName)
{
	bool ret = CCSprite::initWithSpriteFrameName(pszSpriteFrameName);

	CCTextureAtlas *atlas = CCSpriteFrameCacheHelper::sharedSpriteFrameCacheHelper()->getTexureAtlasWithTexture(m_pobTexture);
	setTextureAtlas(atlas);

	m_strDisplayName = pszSpriteFrameName;

	return ret;
}

bool CCSkin::initWithFile(const char *pszFilename)
{
	bool ret = CCSprite::initWithFile(pszFilename);

	CCTextureAtlas *atlas = CCSpriteFrameCacheHelper::sharedSpriteFrameCacheHelper()->getTexureAtlasWithTexture(m_pobTexture);
	setTextureAtlas(atlas);

	m_strDisplayName = pszFilename;

	return ret;
}

void CCSkin::setSkinData(const CCBaseData &var)
{
    m_sSkinData = var;

    setScaleX(m_sSkinData.scaleX);
    setScaleY(m_sSkinData.scaleY);
    setRotation(CC_RADIANS_TO_DEGREES(m_sSkinData.skewX));
    setPosition(ccp(m_sSkinData.x, m_sSkinData.y));

    m_tSkinTransform = nodeToParentTransform();
}

const CCBaseData &CCSkin::getSkinData()
{
    return m_sSkinData;
}

void CCSkin::updateArmatureTransform()
{
    m_sTransform = CCAffineTransformConcat(m_tSkinTransform, m_pBone->nodeToArmatureTransform());
}

void CCSkin::updateTransform()
{
    // If it is not visible, or one of its ancestors is not visible, then do nothing:
    if( !m_bVisible)
    {
        m_sQuad.br.vertices = m_sQuad.tl.vertices = m_sQuad.tr.vertices = m_sQuad.bl.vertices = vertex3(0, 0, 0);
    }
    else
    {
        //
        // calculate the Quad based on the Affine Matrix
        //

        CCSize &size = m_obRect.size;

        float x1 = m_obOffsetPosition.x;
        float y1 = m_obOffsetPosition.y;

        float x2 = x1 + size.width;
        float y2 = y1 + size.height;

        float x = m_sTransform.tx;
        float y = m_sTransform.ty;

        float cr = m_sTransform.a;
        float sr = m_sTransform.b;
        float cr2 = m_sTransform.d;
        float sr2 = -m_sTransform.c;
        float ax = x1 * cr - y1 * sr2 + x;
        float ay = x1 * sr + y1 * cr2 + y;

        float bx = x2 * cr - y1 * sr2 + x;
        float by = x2 * sr + y1 * cr2 + y;

        float cx = x2 * cr - y2 * sr2 + x;
        float cy = x2 * sr + y2 * cr2 + y;

        float dx = x1 * cr - y2 * sr2 + x;
        float dy = x1 * sr + y2 * cr2 + y;

        m_sQuad.bl.vertices = vertex3( RENDER_IN_SUBPIXEL(ax), RENDER_IN_SUBPIXEL(ay), m_fVertexZ );
        m_sQuad.br.vertices = vertex3( RENDER_IN_SUBPIXEL(bx), RENDER_IN_SUBPIXEL(by), m_fVertexZ );
        m_sQuad.tl.vertices = vertex3( RENDER_IN_SUBPIXEL(dx), RENDER_IN_SUBPIXEL(dy), m_fVertexZ );
        m_sQuad.tr.vertices = vertex3( RENDER_IN_SUBPIXEL(cx), RENDER_IN_SUBPIXEL(cy), m_fVertexZ );
    }

    // MARMALADE CHANGE: ADDED CHECK FOR NULL, TO PERMIT SPRITES WITH NO BATCH NODE / TEXTURE ATLAS
    if (m_pobTextureAtlas)
    {
        m_pobTextureAtlas->updateQuad(&m_sQuad, m_pobTextureAtlas->getTotalQuads());
    }
}

CCAffineTransform CCSkin::nodeToWorldTransform()
{
	return CCAffineTransformConcat(m_sTransform, m_pBone->getArmature()->nodeToWorldTransform());
}

CCAffineTransform CCSkin::nodeToWorldTransformAR()
{
	CCAffineTransform displayTransform = m_sTransform;
	CCPoint anchorPoint =  m_obAnchorPointInPoints;

	anchorPoint = CCPointApplyAffineTransform(anchorPoint, displayTransform);
	
	displayTransform.tx = anchorPoint.x;
	displayTransform.ty = anchorPoint.y;

	return CCAffineTransformConcat(displayTransform, m_pBone->getArmature()->nodeToWorldTransform());
}

NS_CC_EXT_END
