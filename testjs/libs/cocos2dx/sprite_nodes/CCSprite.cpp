/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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

#include "CCSpriteBatchNode.h"
#include "CCAnimation.h"
#include "CCAnimationCache.h"
#include "ccConfig.h"
#include "CCSprite.h"
#include "CCSpriteFrame.h"
#include "CCSpriteFrameCache.h"
#include "CCTextureCache.h"
#include "CCPointExtension.h"
#include "CCDrawingPrimitives.h"
#include "CCGeometry.h"
#include "CCTexture2D.h"
#include "CCAffineTransform.h"
#include "CCDirector.h"

#include <string.h>

using namespace std;
namespace   cocos2d {

#if CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
#define RENDER_IN_SUBPIXEL
#else
#define RENDER_IN_SUBPIXEL(__A__) ( (int)(__A__))
#endif

// XXX: Optmization
struct transformValues_ {
	CCPoint pos;		// position x and y
	CCPoint	scale;		// scale x and y
	float	rotation;
    CCPoint skew;		// skew x and y
	CCPoint ap;			// anchor point in pixels
	bool    visible;    
};


CCSprite* CCSprite::spriteWithBatchNode(CCSpriteBatchNode *batchNode, const CCRect& rect)
{
	CCSprite *pobSprite = new CCSprite();
	if (pobSprite && pobSprite->initWithBatchNode(batchNode, rect))
	{
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
	return NULL;
}

bool CCSprite::initWithBatchNode(CCSpriteBatchNode *batchNode, const CCRect& rect)
{
	if (initWithTexture(batchNode->getTexture(), rect))
    {
	    useBatchNode(batchNode);
        return true;
    }
	return false;
}

bool CCSprite::initWithBatchNodeRectInPixels(CCSpriteBatchNode *batchNode, const CCRect& rect)
{
	if (initWithTexture(batchNode->getTexture()))
    {
	    setTextureRectInPixels(rect, false, rect.size);
	    useBatchNode(batchNode);
        return true;
    }
	return false;
}

CCSprite* CCSprite::spriteWithTexture(CCTexture2D *pTexture)
{
	CCSprite *pobSprite = new CCSprite();
	if (pobSprite && pobSprite->initWithTexture(pTexture))
    {
	    pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCSprite* CCSprite::spriteWithTexture(CCTexture2D *pTexture, const CCRect& rect)
{
    CCSprite *pobSprite = new CCSprite();
	if (pobSprite && pobSprite->initWithTexture(pTexture, rect))
    {
	    pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCSprite* CCSprite::spriteWithTexture(CCTexture2D *pTexture, const CCRect& rect, const CCPoint& offset)
{
    CC_UNUSED_PARAM(pTexture);
    CC_UNUSED_PARAM(rect);
    CC_UNUSED_PARAM(offset);
	// not implement
	CCAssert(0, "");
	return NULL;
}

CCSprite* CCSprite::spriteWithFile(const char *pszFileName)
{
    CCSprite *pobSprite = new CCSprite();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCSprite* CCSprite::spriteWithFile(const char *pszFileName, const CCRect& rect)
{
    CCSprite *pobSprite = new CCSprite();
	if (pobSprite && pobSprite->initWithFile(pszFileName, rect))
    {
	    pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCSprite* CCSprite::spriteWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
{
    CCSprite *pobSprite = new CCSprite();
    if (pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
    {
	    pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCSprite* CCSprite::spriteWithSpriteFrameName(const char *pszSpriteFrameName)
{
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);

    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
    CCAssert(pFrame != NULL, msg);
	return spriteWithSpriteFrame(pFrame);
}

bool CCSprite::init(void)
{
	m_bDirty = m_bRecursiveDirty = false;

	// by default use "Self Render".
	// if the sprite is added to an batchnode, then it will automatically switch to "SpriteSheet Render"
    useSelfRender();

	m_bOpacityModifyRGB = true;
	m_nOpacity = 255;
	m_sColor = m_sColorUnmodified = ccWHITE;

	m_sBlendFunc.src = CC_BLEND_SRC;
	m_sBlendFunc.dst = CC_BLEND_DST;

	// update texture (calls updateBlendFunc)
	setTexture(NULL);

	// clean the Quad
	memset(&m_sQuad, 0, sizeof(m_sQuad));

	m_bFlipX = m_bFlipY = false;

	// default transform anchor: center
	setAnchorPoint(ccp(0.5f, 0.5f));

	// zwoptex default values
    m_obOffsetPositionInPixels = CCPointZero;

	m_eHonorParentTransform = CC_HONOR_PARENT_TRANSFORM_ALL;
	m_bHasChildren = false;

	// Atlas: Color
	ccColor4B tmpColor = { 255, 255, 255, 255 };
	m_sQuad.bl.colors = tmpColor;
	m_sQuad.br.colors = tmpColor;
	m_sQuad.tl.colors = tmpColor;
	m_sQuad.tr.colors = tmpColor;

	// Atlas: Vertex
		
	// updated in "useSelfRender"
		
	// Atlas: TexCoords
	setTextureRectInPixels(CCRectZero, false, CCSizeZero);

	return true;
}

bool CCSprite::initWithTexture(CCTexture2D *pTexture, const CCRect& rect)
{
	CCAssert(pTexture != NULL, "");
	// IMPORTANT: [self init] and not [super init];
	init();
	setTexture(pTexture);
	setTextureRect(rect);

	return true;
}

bool CCSprite::initWithTexture(CCTexture2D *pTexture)
{
	CCAssert(pTexture != NULL, "");

	CCRect rect = CCRectZero;
	rect.size = pTexture->getContentSize();
	
	return initWithTexture(pTexture, rect);
}

bool CCSprite::initWithFile(const char *pszFilename)
{
	CCAssert(pszFilename != NULL, "");

	CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(pszFilename);
	if (pTexture)
	{
		CCRect rect = CCRectZero;
		rect.size = pTexture->getContentSize();
		return initWithTexture(pTexture, rect);
	}

	// don't release here.
	// when load texture failed, it's better to get a "transparent" sprite then a crashed program
	// this->release(); 
	return false;
}

bool CCSprite::initWithFile(const char *pszFilename, const CCRect& rect)
{
	CCAssert(pszFilename != NULL, "");

	CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(pszFilename);
	if (pTexture)
	{
		return initWithTexture(pTexture, rect);
	}

	// don't release here.
	// when load texture failed, it's better to get a "transparent" sprite then a crashed program
	// this->release(); 
	return false;
}

bool CCSprite::initWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
{
	CCAssert(pSpriteFrame != NULL, "");

	bool bRet = initWithTexture(pSpriteFrame->getTexture(), pSpriteFrame->getRect());
	setDisplayFrame(pSpriteFrame);

	return bRet;
}

bool CCSprite::initWithSpriteFrameName(const char *pszSpriteFrameName)
{
	CCAssert(pszSpriteFrameName != NULL, "");

	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
	return initWithSpriteFrame(pFrame);
}

// XXX: deprecated
/*
CCSprite* CCSprite::initWithCGImage(CGImageRef pImage)
{
	// todo
	// because it is deprecated, so we do not impelment it

	return NULL;
}
*/

/*
CCSprite* CCSprite::initWithCGImage(CGImageRef pImage, const char *pszKey)
{
	CCAssert(pImage != NULL);

	// XXX: possible bug. See issue #349. New API should be added
	CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addCGImage(pImage, pszKey);

	const CCSize& size = pTexture->getContentSize();
	CCRect rect = CCRectMake(0 ,0, size.width, size.height);

	return initWithTexture(texture, rect);
}
*/

CCSprite::CCSprite(void)
: m_pobTexture(NULL)
{
}

CCSprite::~CCSprite(void)
{
	CC_SAFE_RELEASE(m_pobTexture);
}

void CCSprite::useSelfRender(void)
{
    m_uAtlasIndex = CCSpriteIndexNotInitialized;
	m_bUsesBatchNode = false;
	m_pobTextureAtlas = NULL;
    m_pobBatchNode = NULL;
	m_bDirty = m_bRecursiveDirty = false;

	float x1 = 0 + m_obOffsetPositionInPixels.x;
	float y1 = 0 + m_obOffsetPositionInPixels.y;
	float x2 = x1 + m_obRectInPixels.size.width;
	float y2 = y1 + m_obRectInPixels.size.height;
	m_sQuad.bl.vertices = vertex3(x1, y1, 0);
	m_sQuad.br.vertices = vertex3(x2, y1, 0);
	m_sQuad.tl.vertices = vertex3(x1, y2, 0);
	m_sQuad.tr.vertices = vertex3(x2, y2, 0);
}

void CCSprite::useBatchNode(CCSpriteBatchNode *batchNode)
{
    m_bUsesBatchNode = true;
	m_pobTextureAtlas = batchNode->getTextureAtlas(); // weak ref
    m_pobBatchNode = batchNode;
}

void CCSprite::setTextureRect(const CCRect& rect)
{
	CCRect rectInPixels = CC_RECT_POINTS_TO_PIXELS(rect);
	setTextureRectInPixels(rectInPixels, false, rectInPixels.size);
}


void CCSprite::setTextureRectInPixels(const CCRect& rect, bool rotated, const CCSize& size)
{
	m_obRectInPixels = rect;
	m_obRect = CC_RECT_PIXELS_TO_POINTS(rect);
	m_bRectRotated = rotated;

	setContentSizeInPixels(size);
	updateTextureCoords(m_obRectInPixels);

	CCPoint relativeOffsetInPixels = m_obUnflippedOffsetPositionFromCenter;

	// issue #732
	if (m_bFlipX)
	{
		relativeOffsetInPixels.x = -relativeOffsetInPixels.x;
	}
	if (m_bFlipY)
	{
		relativeOffsetInPixels.y = -relativeOffsetInPixels.y;
	}

	m_obOffsetPositionInPixels.x = relativeOffsetInPixels.x + (m_tContentSizeInPixels.width - m_obRectInPixels.size.width) / 2;
	m_obOffsetPositionInPixels.y = relativeOffsetInPixels.y + (m_tContentSizeInPixels.height - m_obRectInPixels.size.height) / 2;

	// rendering using batch node
	if (m_bUsesBatchNode)
	{
		// update dirty_, don't update recursiveDirty_
		m_bDirty = true;
	}
	else
	{
		// self rendering
		
		// Atlas: Vertex
		float x1 = 0 + m_obOffsetPositionInPixels.x;
		float y1 = 0 + m_obOffsetPositionInPixels.y;
		float x2 = x1 + m_obRectInPixels.size.width;
		float y2 = y1 + m_obRectInPixels.size.height;

		// Don't update Z.
		m_sQuad.bl.vertices = vertex3(x1, y1, 0);
		m_sQuad.br.vertices = vertex3(x2, y1, 0);
		m_sQuad.tl.vertices = vertex3(x1, y2, 0);
		m_sQuad.tr.vertices = vertex3(x2, y2, 0);
	}
}


void CCSprite::updateTextureCoords(const CCRect& rect)
{
	CCTexture2D *tex = m_bUsesBatchNode ? m_pobTextureAtlas->getTexture() : m_pobTexture;
	if (! tex)
	{
		return;
	}

	float atlasWidth = (float)tex->getPixelsWide();
	float atlasHeight = (float)tex->getPixelsHigh();

	float left, right, top, bottom;

	if (m_bRectRotated)
	{
#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
		left	= (2*rect.origin.x+1)/(2*atlasWidth);
		right	= left+(rect.size.height*2-2)/(2*atlasWidth);
		top		= (2*rect.origin.y+1)/(2*atlasHeight);
		bottom	= top+(rect.size.width*2-2)/(2*atlasHeight);
#else
		left	= rect.origin.x/atlasWidth;
		right	= left+(rect.size.height/atlasWidth);
		top		= rect.origin.y/atlasHeight;
		bottom	= top+(rect.size.width/atlasHeight);
#endif // CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL

		if (m_bFlipX)
		{
			CC_SWAP(top, bottom, float);
		}

		if (m_bFlipY)
		{
			CC_SWAP(left, right, float);
		}

		m_sQuad.bl.texCoords.u = left;
		m_sQuad.bl.texCoords.v = top;
		m_sQuad.br.texCoords.u = left;
		m_sQuad.br.texCoords.v = bottom;
		m_sQuad.tl.texCoords.u = right;
		m_sQuad.tl.texCoords.v = top;
		m_sQuad.tr.texCoords.u = right;
		m_sQuad.tr.texCoords.v = bottom;
	}
	else
	{
#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
		left	= (2*rect.origin.x+1)/(2*atlasWidth);
		right	= left + (rect.size.width*2-2)/(2*atlasWidth);
		top		= (2*rect.origin.y+1)/(2*atlasHeight);
		bottom	= top + (rect.size.height*2-2)/(2*atlasHeight);
#else
		left	= rect.origin.x/atlasWidth;
		right	= left + rect.size.width/atlasWidth;
		top		= rect.origin.y/atlasHeight;
		bottom	= top + rect.size.height/atlasHeight;
#endif // ! CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL

		if(m_bFlipX)
		{
			CC_SWAP(left,right,float);
		}

		if(m_bFlipY)
		{
			CC_SWAP(top,bottom,float);
		}

		m_sQuad.bl.texCoords.u = left;
		m_sQuad.bl.texCoords.v = bottom;
		m_sQuad.br.texCoords.u = right;
		m_sQuad.br.texCoords.v = bottom;
		m_sQuad.tl.texCoords.u = left;
		m_sQuad.tl.texCoords.v = top;
		m_sQuad.tr.texCoords.u = right;
		m_sQuad.tr.texCoords.v = top;
	}
}

void CCSprite::updateTransform(void)
{
	CCAssert(m_bUsesBatchNode, "");

	// optimization. Quick return if not dirty
	if (! m_bDirty)
	{
		return;
	}

	CCAffineTransform matrix;

	// Optimization: if it is not visible, then do nothing
	if (! m_bIsVisible)
	{
		m_sQuad.br.vertices = m_sQuad.tl.vertices = m_sQuad.tr.vertices = m_sQuad.bl.vertices = vertex3(0,0,0);
		m_pobTextureAtlas->updateQuad(&m_sQuad, m_uAtlasIndex);
		m_bDirty = m_bRecursiveDirty = false;
		return;
	}

	// Optimization: If parent is batchnode, or parent is nil
	// build Affine transform manually
	if (! m_pParent || m_pParent == m_pobBatchNode)
	{
		float radians = -CC_DEGREES_TO_RADIANS(m_fRotation);
		float c = cosf(radians);
		float s = sinf(radians);

        matrix = CCAffineTransformMake(c * m_fScaleX, s * m_fScaleX,
			-s * m_fScaleY, c * m_fScaleY,
			m_tPositionInPixels.x, m_tPositionInPixels.y);
        if( m_fSkewX || m_fSkewY )
        {
            CCAffineTransform skewMatrix = CCAffineTransformMake(1.0f, tanf(CC_DEGREES_TO_RADIANS(m_fSkewY)),
                tanf(CC_DEGREES_TO_RADIANS(m_fSkewX)), 1.0f,
                0.0f, 0.0f);
            matrix = CCAffineTransformConcat(skewMatrix, matrix);
        }
		matrix = CCAffineTransformTranslate(matrix, -m_tAnchorPointInPixels.x, -m_tAnchorPointInPixels.y);
	} else // parent_ != batchNode_ 
	{
		// else do affine transformation according to the HonorParentTransform
		matrix = CCAffineTransformIdentity;
		ccHonorParentTransform prevHonor = CC_HONOR_PARENT_TRANSFORM_ALL;

		for (CCNode *p = this; p && p != m_pobBatchNode; p = p->getParent())
		{
			// Might happen. Issue #1053
			// how to implement, we can not use dynamic
			// CCAssert( [p isKindOfClass:[CCSprite class]], @"CCSprite should be a CCSprite subclass. Probably you initialized an sprite with a batchnode, but you didn't add it to the batch node." );
			struct transformValues_ tv;
			((CCSprite*)p)->getTransformValues(&tv);

			// If any of the parents are not visible, then don't draw this node
			if (! tv.visible)
			{
				m_sQuad.br.vertices = m_sQuad.tl.vertices = m_sQuad.tr.vertices = m_sQuad.bl.vertices = vertex3(0,0,0);
				m_pobTextureAtlas->updateQuad(&m_sQuad, m_uAtlasIndex);
				m_bDirty = m_bRecursiveDirty = false;

				return;
			}

			CCAffineTransform newMatrix = CCAffineTransformIdentity;

			// 2nd: Translate, Skew, Rotate, Scale
			if( prevHonor & CC_HONOR_PARENT_TRANSFORM_TRANSLATE )
			{
				newMatrix = CCAffineTransformTranslate(newMatrix, tv.pos.x, tv.pos.y);
			}

			if( prevHonor & CC_HONOR_PARENT_TRANSFORM_ROTATE )
			{
				newMatrix = CCAffineTransformRotate(newMatrix, -CC_DEGREES_TO_RADIANS(tv.rotation));
			}

            if ( prevHonor & CC_HONOR_PARENT_TRANSFORM_SKEW )
            {
                CCAffineTransform skew = CCAffineTransformMake(1.0f, tanf(CC_DEGREES_TO_RADIANS(tv.skew.y)), tanf(CC_DEGREES_TO_RADIANS(tv.skew.x)), 1.0f, 0.0f, 0.0f);
                // apply the skew to the transform
                newMatrix = CCAffineTransformConcat(skew, newMatrix);
            }

			if( prevHonor & CC_HONOR_PARENT_TRANSFORM_SCALE ) 
			{
				newMatrix = CCAffineTransformScale(newMatrix, tv.scale.x, tv.scale.y);
			}

			// 3rd: Translate anchor point
			newMatrix = CCAffineTransformTranslate(newMatrix, -tv.ap.x, -tv.ap.y);

			// 4th: Matrix multiplication
			matrix = CCAffineTransformConcat( matrix, newMatrix);

			prevHonor = ((CCSprite*)p)->getHonorParentTransform();
		}
	}

	//
	// calculate the Quad based on the Affine Matrix
	//
	CCSize size = m_obRectInPixels.size;

	float x1 = m_obOffsetPositionInPixels.x;
	float y1 = m_obOffsetPositionInPixels.y;

	float x2 = x1 + size.width;
	float y2 = y1 + size.height;
    float x = matrix.tx;
	float y = matrix.ty;
	
	float cr = matrix.a;
	float sr = matrix.b;
	float cr2 = matrix.d;
	float sr2 = -matrix.c;
	float ax = x1 * cr - y1 * sr2 + x;
	float ay = x1 * sr + y1 * cr2 + y;
	
	float bx = x2 * cr - y1 * sr2 + x;
	float by = x2 * sr + y1 * cr2 + y;
	
	float cx = x2 * cr - y2 * sr2 + x;
	float cy = x2 * sr + y2 * cr2 + y;
	
	float dx = x1 * cr - y2 * sr2 + x;
	float dy = x1 * sr + y2 * cr2 + y;

	m_sQuad.bl.vertices = vertex3((float)RENDER_IN_SUBPIXEL(ax), (float)RENDER_IN_SUBPIXEL(ay), m_fVertexZ);
	m_sQuad.br.vertices = vertex3((float)RENDER_IN_SUBPIXEL(bx), (float)RENDER_IN_SUBPIXEL(by), m_fVertexZ);
	m_sQuad.tl.vertices = vertex3((float)RENDER_IN_SUBPIXEL(dx), (float)RENDER_IN_SUBPIXEL(dy), m_fVertexZ);
	m_sQuad.tr.vertices = vertex3((float)RENDER_IN_SUBPIXEL(cx), (float)RENDER_IN_SUBPIXEL(cy), m_fVertexZ);

	m_pobTextureAtlas->updateQuad(&m_sQuad, m_uAtlasIndex);
	m_bDirty = m_bRecursiveDirty = false;
}

// XXX: Optimization: instead of calling 5 times the parent sprite to obtain: position, scale.x, scale.y, anchorpoint and rotation,
// this fuction return the 5 values in 1 single call
void CCSprite::getTransformValues(struct transformValues_ *tv)
{
	tv->pos = m_tPositionInPixels;
	tv->scale.x = m_fScaleX;
	tv->scale.y = m_fScaleY;
	tv->rotation = m_fRotation;
    tv->skew.x	 = m_fSkewX;
    tv->skew.y	 = m_fSkewY;
	tv->ap = m_tAnchorPointInPixels;
	tv->visible = m_bIsVisible;
}

// draw

void CCSprite::draw(void)
{
	CCNode::draw();

	CCAssert(! m_bUsesBatchNode, "");

	// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	// Needed states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	// Unneeded states: -
	bool newBlend = m_sBlendFunc.src != CC_BLEND_SRC || m_sBlendFunc.dst != CC_BLEND_DST;
	if (newBlend)
	{
		glBlendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);
	}

#define kQuadSize sizeof(m_sQuad.bl)
    if (m_pobTexture)
    {
        glBindTexture(GL_TEXTURE_2D, m_pobTexture->getName());
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

	long offset = (long)&m_sQuad;

	// vertex
	int diff = offsetof(ccV3F_C4B_T2F, vertices);
	glVertexPointer(3, GL_FLOAT, kQuadSize, (void*)(offset + diff));

	// color
	diff = offsetof( ccV3F_C4B_T2F, colors);
	glColorPointer(4, GL_UNSIGNED_BYTE, kQuadSize, (void*)(offset + diff));
	
	// tex coords
	diff = offsetof( ccV3F_C4B_T2F, texCoords);
	glTexCoordPointer(2, GL_FLOAT, kQuadSize, (void*)(offset + diff));
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
	if( newBlend )
	{
		glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
	}

#if CC_SPRITE_DEBUG_DRAW == 1
    // draw bounding box
    CCSize s = m_tContentSize;
    CCPoint vertices[4] = {
        ccp(0,0), ccp(s.width,0),
        ccp(s.width,s.height), ccp(0,s.height)
    };
    ccDrawPoly(vertices, 4, true);
#elif CC_SPRITE_DEBUG_DRAW == 2
    // draw texture box
    const CCSize& s = m_obRect.size;
    const CCPoint& offsetPix = getOffsetPositionInPixels();
    CCPoint vertices[4] = {
        ccp(offsetPix.x,offsetPix.y), ccp(offsetPix.x+s.width,offsetPix.y),
        ccp(offsetPix.x+s.width,offsetPix.y+s.height), ccp(offsetPix.x,offsetPix.y+s.height)
    };
    ccDrawPoly(vertices, 4, true);
#endif // CC_SPRITE_DEBUG_DRAW
}

// CCNode overrides

void CCSprite::addChild(CCNode* pChild)
{
	CCNode::addChild(pChild);
}

void CCSprite::addChild(CCNode *pChild, int zOrder)
{
	CCNode::addChild(pChild, zOrder);
}

void CCSprite::addChild(CCNode *pChild, int zOrder, int tag)
{
	CCAssert(pChild != NULL, "");
	CCNode::addChild(pChild, zOrder, tag);

	if (m_bUsesBatchNode)
	{
		CCAssert(((CCSprite*)pChild)->getTexture()->getName() == m_pobTextureAtlas->getTexture()->getName(), "");
		unsigned int index = m_pobBatchNode->atlasIndexForChild((CCSprite*)(pChild), zOrder);
		m_pobBatchNode->insertChild((CCSprite*)(pChild), index);
	}

	m_bHasChildren = true;
}

void CCSprite::reorderChild(CCNode *pChild, int zOrder)
{
    CCAssert(pChild != NULL, "");
	CCAssert(m_pChildren->containsObject(pChild), "");

	if (zOrder == pChild->getZOrder())
	{
		return;
	}

	if (m_bUsesBatchNode)
	{
		// XXX: Instead of removing/adding, it is more efficient to reorder manually
		pChild->retain();
		removeChild(pChild, false);
		addChild(pChild, zOrder);
		pChild->release();
	}
	else
	{
		CCNode::reorderChild(pChild, zOrder);
	}
}

void CCSprite::removeChild(CCNode *pChild, bool bCleanup)
{
	if (m_bUsesBatchNode)
	{
		m_pobBatchNode->removeSpriteFromAtlas((CCSprite*)(pChild));
	}

	CCNode::removeChild(pChild, bCleanup);
	
}

void CCSprite::removeAllChildrenWithCleanup(bool bCleanup)
{
	if (m_bUsesBatchNode)
	{
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(m_pChildren, pObject)
        {
            CCSprite* pChild = dynamic_cast<CCSprite*>(pObject);
            if (pChild)
            {
                m_pobBatchNode->removeSpriteFromAtlas(pChild);
            }
        }
	}

	CCNode::removeAllChildrenWithCleanup(bCleanup);
	
	m_bHasChildren = false;
}

//
// CCNode property overloads
// used only when parent is CCSpriteBatchNode
//

void CCSprite::setDirtyRecursively(bool bValue)
{
	m_bDirty = m_bRecursiveDirty = bValue;
	// recursively set dirty
	if (m_bHasChildren)
	{
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(m_pChildren, pObject)
        {
            CCSprite* pChild = dynamic_cast<CCSprite*>(pObject);
            if (pChild)
            {
                pChild->setDirtyRecursively(true);
            }
        }
	}
}

// XXX HACK: optimization
#define SET_DIRTY_RECURSIVELY() {									\
					if (m_bUsesBatchNode && ! m_bRecursiveDirty) {	\
						m_bDirty = m_bRecursiveDirty = true;				\
						if ( m_bHasChildren)							\
							setDirtyRecursively(true);			\
						}											\
					}

void CCSprite::setPosition(const CCPoint& pos)
{
	CCNode::setPosition(pos);
    SET_DIRTY_RECURSIVELY();
}

void CCSprite::setPositionInPixels(const CCPoint& pos)
{
	CCNode::setPositionInPixels(pos);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::setRotation(float fRotation)
{
	CCNode::setRotation(fRotation);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::setSkewX(float sx)
{
    CCNode::setSkewX(sx);
    SET_DIRTY_RECURSIVELY();
}

void CCSprite::setSkewY(float sy)
{
    CCNode::setSkewY(sy);
    SET_DIRTY_RECURSIVELY();
}

void CCSprite::setScaleX(float fScaleX)
{
	CCNode::setScaleX(fScaleX);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::setScaleY(float fScaleY)
{
	CCNode::setScaleY(fScaleY);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::setScale(float fScale)
{
	CCNode::setScale(fScale);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::setVertexZ(float fVertexZ)
{
	CCNode::setVertexZ(fVertexZ);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::setAnchorPoint(const CCPoint& anchor)
{
	CCNode::setAnchorPoint(anchor);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::setIsRelativeAnchorPoint(bool bRelative)
{
	CCAssert(! m_bUsesBatchNode, "");
	CCNode::setIsRelativeAnchorPoint(bRelative);
}

void CCSprite::setIsVisible(bool bVisible)
{
	CCNode::setIsVisible(bVisible);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::setFlipX(bool bFlipX)
{
	if (m_bFlipX != bFlipX)
	{
		m_bFlipX = bFlipX;
		setTextureRectInPixels(m_obRectInPixels, m_bRectRotated, m_tContentSizeInPixels);
	}
}

bool CCSprite::isFlipX(void)
{
	return m_bFlipX;
}

void CCSprite::setFlipY(bool bFlipY)
{
	if (m_bFlipY != bFlipY)
	{
		m_bFlipY = bFlipY;
		setTextureRectInPixels(m_obRectInPixels, m_bRectRotated, m_tContentSizeInPixels);
	}
}

bool CCSprite::isFlipY(void)
{
	return m_bFlipY;
}

//
// RGBA protocol
//

void CCSprite::updateColor(void)
{
	ccColor4B color4 = { m_sColor.r, m_sColor.g, m_sColor.b, m_nOpacity };

	m_sQuad.bl.colors = color4;
	m_sQuad.br.colors = color4;
	m_sQuad.tl.colors = color4;
	m_sQuad.tr.colors = color4;

	// renders using Sprite Manager
	if (m_bUsesBatchNode)
	{
		if (m_uAtlasIndex != CCSpriteIndexNotInitialized)
		{
			m_pobTextureAtlas->updateQuad(&m_sQuad, m_uAtlasIndex);
		}
		else
		{
			// no need to set it recursively
			// update dirty_, don't update recursiveDirty_
			m_bDirty = true;
		}
	}

	// self render
	// do nothing
}

GLubyte CCSprite::getOpacity(void)
{
	return m_nOpacity;
}

void CCSprite::setOpacity(GLubyte opacity)
{
	m_nOpacity = opacity;

	// special opacity for premultiplied textures
	if (m_bOpacityModifyRGB)
	{
		setColor(m_sColorUnmodified);
	}

	updateColor();
}

const ccColor3B& CCSprite::getColor(void)
{
	if (m_bOpacityModifyRGB)
	{
		return m_sColorUnmodified;
	}

	return m_sColor;
}

void CCSprite::setColor(const ccColor3B& color3)
{
    m_sColor = m_sColorUnmodified = color3;

	if (m_bOpacityModifyRGB)
	{
		m_sColor.r = color3.r * m_nOpacity/255;
		m_sColor.g = color3.g * m_nOpacity/255;
		m_sColor.b = color3.b * m_nOpacity/255;
	}

	updateColor();
}

void CCSprite::setIsOpacityModifyRGB(bool bValue)
{
	ccColor3B oldColor = m_sColor;
	m_bOpacityModifyRGB = bValue;
	m_sColor = oldColor;
}

bool CCSprite::getIsOpacityModifyRGB(void)
{
	return m_bOpacityModifyRGB;
}

// Frames

void CCSprite::setDisplayFrame(CCSpriteFrame *pNewFrame)
{
	m_obUnflippedOffsetPositionFromCenter = pNewFrame->getOffsetInPixels();

	CCTexture2D *pNewTexture = pNewFrame->getTexture();
	// update texture before updating texture rect
    if (pNewTexture != m_pobTexture)
    {
        setTexture(pNewTexture);
    }

	// update rect
	m_bRectRotated = pNewFrame->isRotated();
	setTextureRectInPixels(pNewFrame->getRectInPixels(), pNewFrame->isRotated(), pNewFrame->getOriginalSizeInPixels());
}

void CCSprite::setDisplayFrameWithAnimationName(const char *animationName, int frameIndex)
{
	CCAssert(animationName, "");

	CCAnimation *a = CCAnimationCache::sharedAnimationCache()->animationByName(animationName);

	CCAssert(a, "");

	CCSpriteFrame *frame = a->getFrames()->getObjectAtIndex(frameIndex);

	CCAssert(frame, "");

	setDisplayFrame(frame);
}

bool CCSprite::isFrameDisplayed(CCSpriteFrame *pFrame)
{
	CCRect r = pFrame->getRect();

	return (CCRect::CCRectEqualToRect(r, m_obRect) &&
		pFrame->getTexture()->getName() == m_pobTexture->getName());
}

CCSpriteFrame* CCSprite::displayedFrame(void)
{
	return CCSpriteFrame::frameWithTexture(m_pobTexture,
                                           m_obRectInPixels,
                                           m_bRectRotated,
                                           m_obUnflippedOffsetPositionFromCenter,
                                           m_tContentSizeInPixels);
}

// Texture protocol

void CCSprite::updateBlendFunc(void)
{
	CCAssert (! m_bUsesBatchNode, "CCSprite: updateBlendFunc doesn't work when the sprite is rendered using a CCSpriteSheet");

	// it's possible to have an untextured sprite
	if (! m_pobTexture || ! m_pobTexture->getHasPremultipliedAlpha())
	{
		m_sBlendFunc.src = GL_SRC_ALPHA;
		m_sBlendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
		setIsOpacityModifyRGB(false);
	}
	else
	{
		m_sBlendFunc.src = CC_BLEND_SRC;
		m_sBlendFunc.dst = CC_BLEND_DST;
		setIsOpacityModifyRGB(true);
	}
}

void CCSprite::setTexture(CCTexture2D *texture)
{
	// CCSprite: setTexture doesn't work when the sprite is rendered using a CCSpriteSheet
	CCAssert(! m_bUsesBatchNode, "setTexture doesn't work when the sprite is rendered using a CCSpriteSheet");

	// we can not use RTTI, so we do not known the type of object
	// accept texture==nil as argument
	/*CCAssert((! texture) || dynamic_cast<CCTexture2D*>(texture));*/

	CC_SAFE_RELEASE(m_pobTexture);

	m_pobTexture = texture;
	if (texture)
	{
	    texture->retain();
	}

	updateBlendFunc();
}

CCTexture2D* CCSprite::getTexture(void)
{
	return m_pobTexture;
}
}//namespace   cocos2d 
