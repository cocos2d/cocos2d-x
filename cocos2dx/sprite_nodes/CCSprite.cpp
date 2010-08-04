/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "CCSpriteSheet.h"
#include "ccConfig.h"
#include "CCSprite.h"
#include "CCSpriteFrame.h"
#include "CCSpriteFrameCache.h"
#include "CCTextureCache.h"
#include "support/CGPointExtension.h"
#include "CCDrawingPrimitives.h"
#include "cocoa/CGGeometry.h"
#include "CCTexture2D.h"
#include "cocoa/CGAffineTransform.h"
#include "sstsd.h"
#include <string.h>

using namespace std;
namespace   cocos2d {

#if CC_SPRITESHEET_RENDER_SUBPIXEL
#define RENDER_IN_SUBPIXEL
#else
#define RENDER_IN_SUBPIXEL(__A__) ( (int)(__A__))
#endif

// XXX: Optmization
struct transformValues_ {
	CGPoint pos;		// position x and y
	CGPoint	scale;		// scale x and y
	float	rotation;
	CGPoint ap;			// anchor point in pixels
};

CCSprite* CCSprite::spriteWithTexture(CCTexture2D *pTexture)
{
	CCSprite *pobSprite = new CCSprite();
	pobSprite->initWithTexture(pTexture);
	pobSprite->autorelease();

	return pobSprite;
}

CCSprite* CCSprite::spriteWithTexture(CCTexture2D *pTexture, CGRect rect)
{
    CCSprite *pobSprite = new CCSprite();
	pobSprite->initWithTexture(pTexture, rect);
	pobSprite->autorelease();

	return pobSprite;
}

CCSprite* CCSprite::spriteWithTexture(CCTexture2D *pTexture, CGRect rect, CGPoint offset)
{
	// not implement
	assert(0);
	return NULL;
}

CCSprite* CCSprite::spriteWithFile(const char *pszFileName)
{
    CCSprite *pobSprite = new CCSprite();
	pobSprite->initWithFile(pszFileName);
	pobSprite->autorelease();

	return pobSprite;
}

CCSprite* CCSprite::spriteWithFile(const char *pszFileName, CGRect rect)
{
    CCSprite *pobSprite = new CCSprite();
	pobSprite->initWithFile(pszFileName, rect);
	pobSprite->autorelease();

	return pobSprite;
}

CCSprite* CCSprite::spriteWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
{
    CCSprite *pobSprite = new CCSprite();
	pobSprite->initWithSpriteFrame(pSpriteFrame);
	pobSprite->autorelease();

	return pobSprite;
}


///@todo implement
CCSprite* CCSprite::spriteWithSpriteFrameName(const char *pszSpriteFrameName)
{
	/*
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
	return spriteWithSpriteFrame(pFrame);
	*/
	return NULL;
}


// XXX: deprecated
/*
CCSprite* CCSprite::spriteWithCGImage(CGImageRef pImage)
{
    CCSprite *pobSprite = new CCSprite();
	pobSprite->initWithCGImage(pImage);
	pobSprite->autorelease();

	return pobSprite;
}
*/

/*
CCSprite* CCSprite::spriteWithCGImage(CGImageRef pImage, const char *pszKey)
{
    CCSprite *pobSprite = new CCSprite();
	pobSprite->initWithCGImage(pImage, pszKey);
	pobSprite->autorelease();

	return pobSprite;
}
*/

CCSprite* CCSprite::spriteWithSpriteSheet(CCSpriteSheet *pSpriteSheet, CGRect rect)
{
    CCSprite *pobSprite = new CCSprite();
	pobSprite->initWithSpriteSheet(pSpriteSheet, rect);
	pobSprite->autorelease();

	return pobSprite;
}

CCSprite* CCSprite::init(void)
{
	m_bDirty = m_bRecursiveDirty = false;

	// by default use "Self Render".
	// if the sprite is added to an SpriteSheet, then it will automatically switch to "SpriteSheet Render"
    useSelfRender();

	m_bOpacityModifyRGB = true;
	m_nOpacity = 255;
	m_sColor = m_sColorUnmodified = ccWHITE;

	m_sBlendFunc.src = CC_BLEND_SRC;
	m_sBlendFunc.dst = CC_BLEND_DST;

	// update texture (calls updateBlendFunc)
    m_pobTexture = NULL;
	setTexture(NULL);

	// clean the Quad
	memset(&m_sQuad, 0, sizeof(m_sQuad));

	m_bFlipX = m_bFlipY = false;

	// lazy alloc
	m_pAnimations = NULL;

	// default transform anchor: center
	m_tAnchorPoint = ccp(0.5f, 0.5f);

	// zwoptex default values
    m_obOffsetPosition = CGPointZero;

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
	setTextureRect(CGRectZero);

	return this;
}

CCSprite* CCSprite::initWithTexture(CCTexture2D *pTexture, CGRect rect)
{
	assert(pTexture != NULL);
	// IMPORTANT: [self init] and not [super init];
	init();
	setTexture(pTexture);
	setTextureRect(rect);

	return this;
}

CCSprite* CCSprite::initWithTexture(CCTexture2D *pTexture)
{
	assert(pTexture != NULL);

	CGRect rect = CGRectZero;
	rect.size = pTexture->getContentSize();
	
	return initWithTexture(pTexture, rect);
}

CCSprite* CCSprite::initWithFile(const char *pszFilename)
{
	assert(pszFilename != NULL);

	CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(pszFilename);
	if (pTexture)
	{
		CGRect rect = CGRectZero;
		rect.size = pTexture->getContentSize();
		return initWithTexture(pTexture, rect);
	}

	this->release();
	return NULL;
}

CCSprite* CCSprite::initWithFile(const char *pszFilename, CGRect rect)
{
	assert(pszFilename != NULL);

	CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(pszFilename);
	if (pTexture)
	{
		return initWithTexture(pTexture, rect);
	}

	delete this;
	return NULL;
}

CCSprite* CCSprite::initWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
{
	assert(pSpriteFrame != NULL);

	CCSprite* pRet = initWithTexture(pSpriteFrame->getTexture(), pSpriteFrame->getRect());
	setDisplayFrame(pSpriteFrame);

	return pRet;
}

CCSprite* CCSprite::initWithSpriteFrameName(const char *pszSpriteFrameName)
{
	/*
	///@ implement later
	assert(pszSpriteFrameName != NULL);

	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
	return initWithSpriteFrame(pFrame);
	*/
	return NULL;
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
	assert(pImage != NULL);

	// XXX: possible bug. See issue #349. New API should be added
	CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addCGImage(pImage, pszKey);

	CGSize size = pTexture->getContentSize();
	CGRect rect = CGRectMake(0 ,0, size.width, size.height);

	return initWithTexture(texture, rect);
}
*/

CCSprite* CCSprite::initWithSpriteSheet(CCSpriteSheet *pSpriteSheet, CGRect rect)
{
	CCSprite* pRet = initWithTexture(pSpriteSheet->getTexture(), rect);
	useSpriteSheetRender(pSpriteSheet);

	return pRet;
}

CCSprite::~CCSprite(void)
{
	m_pobTexture->release();
    delete m_pAnimations;
}

void CCSprite::useSelfRender(void)
{
    m_uAtlasIndex = CCSpriteIndexNotInitialized;
	m_bUsesSpriteSheet = false;
	m_pobTextureAtlas = NULL;
    m_pobSpriteSheet = NULL;
	m_bDirty = m_bRecursiveDirty = false;

	float x1 = 0 + m_obOffsetPosition.x;
	float y1 = 0 + m_obOffsetPosition.y;
	float x2 = x1 + m_obRect.size.width;
	float y2 = y1 + m_obRect.size.height;
	m_sQuad.bl.vertices = vertex3(x1, y1, 0);
	m_sQuad.br.vertices = vertex3(x2, y1, 0);
	m_sQuad.tl.vertices = vertex3(x1, y2, 0);
	m_sQuad.tr.vertices = vertex3(x2, y2, 0);
}

void CCSprite::useSpriteSheetRender(CCSpriteSheet *pSpriteSheet)
{
	m_bUsesSpriteSheet = true;
	m_pobTextureAtlas = pSpriteSheet->getTextureAtlas();
	m_pobSpriteSheet = pSpriteSheet;
}

void CCSprite::initAnimationDictionary(void)
{
	m_pAnimations = new NSMutableDictionary<string, CCAnimation*>();
}

void CCSprite::setTextureRect(CGRect rect)
{
	setTextureRect(rect, rect.size);
}

void CCSprite::setTextureRect(CGRect rect, CGSize size)
{
	m_obRect = rect;

	setContentSize(size);
	updateTextureCoords(rect);

	// rendering using SpriteSheet
	if (m_bUsesSpriteSheet)
	{
		// update dirty_, don't update recursiveDirty_
		m_bDirty = true;
	}
	else
	{
		// self rendering
		
		// Atlas: Vertex
		float x1 = 0 + m_obOffsetPosition.x;
		float y1 = 0 + m_obOffsetPosition.y;
		float x2 = x1 + m_obRect.size.width;
		float y2 = y1 + m_obRect.size.height;

		// Don't update Z.
		m_sQuad.bl.vertices = vertex3(x1, y1, 0);
		m_sQuad.br.vertices = vertex3(x2, y1, 0);
		m_sQuad.tl.vertices = vertex3(x1, y2, 0);
		m_sQuad.tr.vertices = vertex3(x2, y2, 0);
	}
}

void CCSprite::updateTextureCoords(CGRect rect)
{
	if (m_pobTexture)
	{
		float atlasWidth = (float)m_pobTexture->getPixelsWide();
		float atlasHeight = (float)m_pobTexture->getPixelsHigh();

		float left = m_obRect.origin.x / atlasWidth;
		float right = (m_obRect.origin.x + m_obRect.size.width) / atlasWidth;
		float top = m_obRect.origin.y / atlasHeight;
		float bottom = (m_obRect.origin.y + m_obRect.size.height) / atlasHeight;

		if (m_bFlipX)
		{
			float tmp = left;
			left = right;
			right = tmp;
		}

		if (m_bFlipY)
		{
			float tmp = top;
			top = bottom;
			bottom = tmp;
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
	assert(m_bUsesSpriteSheet);

	CGAffineTransform matrix;

	// Optimization: if it is not visible, then do nothing
	if (! m_bIsVisible)
	{
		m_sQuad.br.vertices = m_sQuad.tl.vertices = m_sQuad.tr.vertices = m_sQuad.bl.vertices = vertex3(0,0,0);
		m_pobTextureAtlas->updateQuad(&m_sQuad, m_uAtlasIndex);
		m_bDirty = m_bRecursiveDirty = false;
		return;
	}

	// Optimization: If parent is spritesheet, or parent is nil
	// build Affine transform manually
	if (! m_pParent || m_pParent == m_pobSpriteSheet)
	{
		float radians = -CC_DEGREES_TO_RADIANS(m_fRotation);
		float c = cosf(radians);
		float s = sinf(radians);

        matrix = CGAffineTransformMake(c * m_fScaleX, s * m_fScaleX,
			-s * m_fScaleY, c * m_fScaleY,
			m_tPosition.x, m_tPosition.y);
		matrix = CGAffineTransformTranslate(matrix, -m_tAnchorPointInPixels.x, -m_tAnchorPointInPixels.y);
	} else
	if (m_pParent != m_pobSpriteSheet)
	{
		// else do affine transformation according to the HonorParentTransform
		matrix = CGAffineTransformIdentity;
		ccHonorParentTransform prevHonor = CC_HONOR_PARENT_TRANSFORM_ALL;

		for (CCNode *p = this; p && p != m_pobSpriteSheet; p = p->getParent())
		{
			struct transformValues_ tv = ((CCSprite*)p)->getTransformValues();

			CGAffineTransform newMatrix = CGAffineTransformIdentity;

			// 2nd: Translate, Rotate, Scale
			if( prevHonor & CC_HONOR_PARENT_TRANSFORM_TRANSLATE )
			{
				newMatrix = CGAffineTransformTranslate(newMatrix, tv.pos.x, tv.pos.y);
			}

			if( prevHonor & CC_HONOR_PARENT_TRANSFORM_ROTATE )
			{
				newMatrix = CGAffineTransformRotate(newMatrix, -CC_DEGREES_TO_RADIANS(tv.rotation));
			}

			if( prevHonor & CC_HONOR_PARENT_TRANSFORM_SCALE ) 
			{
				newMatrix = CGAffineTransformScale(newMatrix, tv.scale.x, tv.scale.y);
			}

			// 3rd: Translate anchor point
			newMatrix = CGAffineTransformTranslate(newMatrix, -tv.ap.x, -tv.ap.y);

			// 4th: Matrix multiplication
			matrix = CGAffineTransformConcat( matrix, newMatrix);

			prevHonor = ((CCSprite*)p)->getHornorParentTransform();
		}
	}

	//
	// calculate the Quad based on the Affine Matrix
	//
	CGSize size = m_obRect.size;

	float x1 = m_obOffsetPosition.x;
	float y1 = m_obOffsetPosition.y;

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

	m_sQuad.bl.vertices = vertex3(RENDER_IN_SUBPIXEL(ax), RENDER_IN_SUBPIXEL(ay), m_fVertexZ);
	m_sQuad.br.vertices = vertex3(RENDER_IN_SUBPIXEL(bx), RENDER_IN_SUBPIXEL(by), m_fVertexZ);
	m_sQuad.tl.vertices = vertex3(RENDER_IN_SUBPIXEL(dx), RENDER_IN_SUBPIXEL(dy), m_fVertexZ);
	m_sQuad.tr.vertices = vertex3(RENDER_IN_SUBPIXEL(cx), RENDER_IN_SUBPIXEL(cy), m_fVertexZ);

	m_pobTextureAtlas->updateQuad(&m_sQuad, m_uAtlasIndex);
	m_bDirty = m_bRecursiveDirty = false;
}

// XXX: Optimization: instead of calling 5 times the parent sprite to obtain: position, scale.x, scale.y, anchorpoint and rotation,
// this fuction return the 5 values in 1 single call
struct transformValues_ CCSprite::getTransformValues(void)
{
	struct transformValues_ tv;
	tv.pos = m_tPosition;
	tv.scale.x = m_fScaleX;
	tv.scale.y = m_fScaleY;
	tv.rotation = m_fRotation;
	tv.ap = m_tAnchorPointInPixels;

	return tv;
}

// draw

void CCSprite::draw(void)
{
	assert(! m_bUsesSpriteSheet);

	// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	// Needed states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	// Unneeded states: -
	bool newBlend = false;
	if (m_sBlendFunc.src != CC_BLEND_SRC || m_sBlendFunc.dst != CC_BLEND_DST)
	{
		newBlend = true;
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

	int offset = (int)&m_sQuad;

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

#if CC_SPRITE_DEBUG_DRAW
	CGSize s = m_tContentSize;
	CGSize s = [self contentSize];
	CGPoint vertices[4]={
		ccp(0,0),ccp(s.width,0),
		ccp(s.width,s.height),ccp(0,s.height),
	};
	ccDrawPoly(vertices, 4, ture);
#endif // CC_SPRITE_DEBUG_DRAW
}

// CCNode overrides

CCNode* CCSprite::addChild(CCNode* pChild)
{
	return __super::addChild(pChild);
}

CCNode* CCSprite::addChild(CCNode *pChild, int zOrder)
{
	return __super::addChild(pChild, zOrder);
}

CCNode* CCSprite::addChild(CCNode *pChild, int zOrder, int tag)
{
	assert(pChild != NULL);
	CCNode* pRet = __super::addChild(pChild, zOrder, tag);

	if (m_bUsesSpriteSheet)
	{
		/*
		///@todo implement after SpriteSheet is implemented
		unsigned int index = m_pobSpriteSheet->atlasIndexForChild(static_cast<CCSprite*>(pChild), zOrder);
		m_pobSpriteSheet->insertChild(static_cast<CCSprite*>(pChild), index);
		*/
	}

	m_bHasChildren = true;

	return pRet;
}

void CCSprite::reorderChild(CCNode *pChild, int zOrder)
{
    assert(pChild != NULL);
	assert(m_pChildren->containsObject(pChild));

	if (zOrder == pChild->getZOrder())
	{
		return;
	}

	if (m_bUsesSpriteSheet)
	{
		// XXX: Instead of removing/adding, it is more efficient to reorder manually
		pChild->retain();
		removeChild(pChild, false);
		addChild(pChild, zOrder);
		pChild->release();
	}
	else
	{
		__super::reorderChild(pChild, zOrder);
	}
}

void CCSprite::removeChild(CCNode *pChild, bool bCleanup)
{
	/*
	///@todo: implement after implementing the sprite sheet
	if (m_bUsesSpriteSheet)
	{
		m_pobSpriteSheet->removeSpriteFromAtlas(static_cast<CCSprite*>(pChild));
	}

	__super::removeChild(pChild, bCleanup);
	*/
}

void CCSprite::removeAllChildrenWithCleanup(bool bCleanup)
{
	/*
	///@todo: implement after the implementation of sprite sheet
	if (m_bUsesSpriteSheet)
	{
		CCSprite *pChild;
		NSMutableArray<CCNode*>::NSMutableArrayIterator iter;
		for (iter = m_pChildren->begin(); iter != m_pChildren->end(); ++iter)
		{
			pChild = static_cast<CCSprite*>(*iter);
			m_pobSpriteSheet->removeSpriteFromAtlas(pChild);
		}
	}

	__super::removeAllChildrenWithCleanup(bCleanup);
	
	m_bHasChildren = false;
	*/
}

//
// CCNode property overloads
// used only when parent is CCSpriteSheet
//

void CCSprite::setDirtyRecursively(bool bValue)
{
	m_bDirty = m_bRecursiveDirty = bValue;
	// recursively set dirty
	if (m_bHasChildren)
	{
		CCSprite *pChild;
		NSMutableArray<CCNode*>::NSMutableArrayIterator iter;
		for (iter = m_pChildren->begin(); iter != m_pChildren->end(); ++iter)
		{
			pChild = static_cast<CCSprite*>(*iter);
			pChild->setDirtyRecursively(true);
		}
	}
}

// XXX HACK: optimization
#define SET_DIRTY_RECURSIVELY() {									\
					if (m_bUsesSpriteSheet && ! m_bRecursiveDirty) {	\
						m_bDirty = m_bRecursiveDirty = true;				\
						if ( m_bHasChildren)							\
							setDirtyRecursively(true);			\
						}											\
					}

void CCSprite::setPosition(CGPoint pos)
{
	__super::setPosition(pos);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::setRotation(float fRotation)
{
	__super::setRotation(fRotation);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::setScaleX(float fScaleX)
{
	__super::setScaleX(fScaleX);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::setScaleY(float fScaleY)
{
	__super::setScaleY(fScaleY);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::setScale(float fScale)
{
	__super::setScale(fScale);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::setVertexZ(float fVertexZ)
{
	__super::setVertexZ(fVertexZ);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::setAnchorPoint(CGPoint anchor)
{
	__super::setAnchorPoint(anchor);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::setIsRelativeAnchorPoint(bool bRelative)
{
	assert(! m_bUsesSpriteSheet);
	__super::setIsRelativeAnchorPoint(bRelative);
}

void CCSprite::setIsVisible(bool bVisible)
{
	if (bVisible != m_bIsVisible)
	{
		__super::setIsVisible(bVisible);
		if (m_bUsesSpriteSheet && m_bRecursiveDirty)
		{
			m_bDirty = m_bRecursiveDirty = true;
			CCNode *pChild;
			NSMutableArray<CCNode*>::NSMutableArrayIterator iter;
			for (iter = m_pChildren->begin(); iter != m_pChildren->end(); ++iter)
			{
				pChild = *iter;
				pChild->setIsVisible(bVisible);
			}
		}
	}
}

void CCSprite::setFlipX(bool bFlipX)
{
	if (m_bFlipX != bFlipX)
	{
		m_bFlipX = bFlipX;
		setTextureRect(m_obRect);
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
		setTextureRect(m_obRect);
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
	if (m_bUsesSpriteSheet)
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

ccColor3B CCSprite::getColor(void)
{
	if (m_bOpacityModifyRGB)
	{
		return m_sColorUnmodified;
	}

	return m_sColor;
}

void CCSprite::setColor(ccColor3B color3)
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

// CCFrameProtocol protocol

void CCSprite::setDisplayFrame(CCSpriteFrame *pNewFrame)
{
	m_obOffsetPosition = pNewFrame->getOffset();

	CGRect rect = pNewFrame->getRect();
	CGSize origSize = pNewFrame->getOriginalSize();
	m_obOffsetPosition.x += (origSize.width - rect.size.width) / 2;
	m_obOffsetPosition.y += (origSize.height - rect.size.height) / 2;

	CCTexture2D *pNewTexture = pNewFrame->getTexture();
	// update texture before updating texture rect
	if (pNewTexture->getName() != m_pobTexture->getName())
	{
        setTexture(pNewTexture);
	}

	// update rect
	setTextureRect(pNewFrame->getRect(), pNewFrame->getOriginalSize());
}

void CCSprite::setDisplayFrame(const char *pszAnimationName, Int32 nFrameIndex)
{
	if (! m_pAnimations)
	{
		initAnimationDictionary();
	}

	CCAnimation *pAnimation = m_pAnimations->objectForKey(pszAnimationName);
	CCSpriteFrame *pFrame = pAnimation->getFrames()->getObjectAtIndex(nFrameIndex);

	assert(pFrame);

	setDisplayFrame(pFrame);
}

bool CCSprite::isFrameDisplayed(CCSpriteFrame *pFrame)
{
	CGRect r = pFrame->getRect();
	CGPoint p = pFrame->getOffset();
	return (CGRect::CGRectEqualToRect(r, m_obRect) &&
		pFrame->getTexture()->getName() == m_pobTexture->getName() &&
		CGPoint::CGPointEqualToPoint(p, m_obOffsetPosition));
}

CCSpriteFrame* CCSprite::displayedFrame(void)
{
	return CCSpriteFrame::frameWithTexture(m_pobTexture, m_obRect, CGPointZero);
}

void CCSprite::addAnimation(CCAnimation *pAnimation)
{
	// lazy alloc
	if (! m_pAnimations)
	{
		initAnimationDictionary();
	}

	m_pAnimations->setObject(pAnimation, pAnimation->getName());
}

CCAnimation* CCSprite::animationByName(const char *pszAnimationName)
{
	assert(pszAnimationName != NULL);

	return m_pAnimations->objectForKey(pszAnimationName);
}

// Texture protocol

void CCSprite::updateBlendFunc(void)
{
	// CCSprite: updateBlendFunc doesn't work when the sprite is rendered using a CCSpriteSheet
	assert (! m_bUsesSpriteSheet);

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
	assert(! m_bUsesSpriteSheet);

	// // accept texture==nil as argument
	assert((! texture) || dynamic_cast<CCTexture2D*>(texture));

	if (m_pobTexture)
	{
	    m_pobTexture->release();
	}

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
