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

#include "ccConfig.h"
#include "CCSprite.h"
#include "CCSpriteSheet.h"
#include "effects/CCGrid.h"
#include "CCDrawingPrimitives.h"
#include "CCTextureCache.h"
#include "CGPointExtension.h"

namespace   cocos2d {

const int defaultCapacity = 29;

// creation with CCTexture2D
CCSpriteSheet* CCSpriteSheet::spriteSheetWithTexture(CCTexture2D *pobTexture)
{
	CCSpriteSheet *pSpriteSheet = new CCSpriteSheet();
	pSpriteSheet->initWithTexture(pobTexture, defaultCapacity);
	pSpriteSheet->autorelease();

	return pSpriteSheet;
}

CCSpriteSheet* CCSpriteSheet::spriteSheetWithTexture(CCTexture2D *pobTexture, unsigned int uCapacity)
{
	CCSpriteSheet *pSpriteSheet = new CCSpriteSheet();
	pSpriteSheet->initWithTexture(pobTexture, uCapacity);
	pSpriteSheet->autorelease();

	return pSpriteSheet;
}

// creation with file image
CCSpriteSheet* CCSpriteSheet::spriteSheetWithFile(const char *pszFileImage, unsigned int uCapacity)
{
	CCSpriteSheet *pSpriteSheet = new CCSpriteSheet();
	pSpriteSheet->initWithFile(pszFileImage, uCapacity);
	pSpriteSheet->autorelease();

	return pSpriteSheet;
}

CCSpriteSheet* CCSpriteSheet::spriteSheetWithFile(const char *pszFileImage)
{
	CCSpriteSheet *pSpriteSheet = new CCSpriteSheet();
	pSpriteSheet->initWithFile(pszFileImage, defaultCapacity);
	pSpriteSheet->autorelease();

	return pSpriteSheet;
}

// init with CCTexture2D
CCSpriteSheet* CCSpriteSheet::initWithTexture(CCTexture2D *pobTexture, unsigned int uCapacity)
{
	m_blendFunc.src = CC_BLEND_SRC;
	m_blendFunc.dst = CC_BLEND_DST;
	m_pobTextureAtlas = new CCTextureAtlas();
	m_pobTextureAtlas->initWithTexture(pobTexture, uCapacity);
	m_pobTextureAtlas->autorelease();

	updateBlendFunc();

	// no lazy alloc in this node
	m_pChildren = new NSMutableArray<CCNode*>();
	m_pobDescendants = new NSMutableArray<CCSprite*>();

	return this;
}

// init with FileImage
CCSpriteSheet* CCSpriteSheet::initWithFile(const char *pszFileImage, unsigned int uCapacity)
{
	CCTexture2D *pTexture2D = CCTextureCache::sharedTextureCache()->addImage(pszFileImage);
	return initWithTexture(pTexture2D, uCapacity);
}

CCSpriteSheet::~CCSpriteSheet(void)
{
	m_pobTextureAtlas->release();
	m_pobDescendants->release();
}

// composition

// override visit
// don't call visit on it's children
void CCSpriteSheet::visit(void)
{
	// CAREFUL:
	// This visit is almost identical to CocosNode#visit
	// with the exception that it doesn't call visit on it's children
	//
	// The alternative is to have a void CCSprite#visit, but
	// although this is less mantainable, is faster
	//
	if (! m_bIsVisible)
	{
		return;
	}

	glPushMatrix();

	if (m_pGrid && m_pGrid->isActive())
	{
		m_pGrid->beforeDraw();
        transformAncestors();
	}

	transform();

	draw();

	if (m_pGrid && m_pGrid->isActive())
	{
		m_pGrid->afterDraw(this);
	}

	glPopMatrix();
}

// xxx deprecated
CCSprite* CCSpriteSheet::createSpriteWithRect(CGRect rect)
{
	CCSprite *pSprite = new CCSprite();
	pSprite->spriteWithTexture(m_pobTextureAtlas->getTexture(), rect);
	pSprite->useSpriteSheetRender(this);

	return pSprite;
}

// override add child
CCNode* CCSpriteSheet::addChild(CCNode *child)
{
	return __super::addChild(child);
}

CCNode* CCSpriteSheet::addChild(CCNode *child, int zOrder)
{
	return __super::addChild(child, zOrder);
}

CCNode* CCSpriteSheet::addChild(CCNode *child, int zOrder, int tag)
{
	assert(child != NULL);
	
 	CCSprite *pSprite = (CCSprite*)(child);
	// check CCSprite is using the same texture id
	assert(pSprite->getTexture()->getName() == m_pobTextureAtlas->getTexture()->getName());

	CCNode *pRet = __super::addChild(child, zOrder, tag);

	unsigned int uIndex = atlasIndexForChild(pSprite, zOrder);
	insertChild(pSprite, uIndex);

	return pRet;
}

// override reorderChild
void CCSpriteSheet::reorderChild(CCNode *child, int zOrder)
{
	assert(child != NULL);
	assert(m_pChildren->containsObject(child));

	if (zOrder == child->getZOrder())
	{
		return;
	}

	// xxx: instead of removing/adding, it is more efficient ot reorder manually
	child->retain();
	removeChild(child, false);
	addChild(child, zOrder);
	child->release();
}

// override remove child
void CCSpriteSheet::removeChild(CCNode *child, bool cleanup)
{
	CCSprite *pSprite = (CCSprite*)(child);

	// explicit null handling
	if (pSprite == NULL)
	{
		return;
	}

	assert(m_pChildren->containsObject(pSprite));

	// cleanup before removing
	removeSpriteFromAtlas(pSprite);

	__super::removeChild(pSprite, cleanup);
}

void CCSpriteSheet::removeChildAtIndex(unsigned int uIndex, bool bDoCleanup)
{
	removeChild((CCSprite*)(m_pChildren->getObjectAtIndex(uIndex)), bDoCleanup);
}

void CCSpriteSheet::removeAllChildrenWithCleanup(bool bCleanup)
{
	// Invalidate atlas index. issue #569
	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCSprite *pSprite;
		NSMutableArray<CCNode*>::NSMutableArrayIterator iter;
		for (iter = m_pChildren->begin(); iter != m_pChildren->end(); ++iter)
		{
			pSprite = (CCSprite*)(*iter);

			if (! pSprite)
			{
				break;
			}

			pSprite->useSelfRender();
		}
	}
	
	__super::removeAllChildrenWithCleanup(bCleanup);

	m_pobDescendants->removeAllObjects();
	m_pobTextureAtlas->removeAllQuads();
}

// draw
void CCSpriteSheet::draw(void)
{
	if (m_pobTextureAtlas->getTotalQuads() == 0)
	{
		return;
	}

	if (m_pobDescendants && m_pobDescendants->count() > 0)
	{
        CCSprite *pSprite;
		NSMutableArray<CCSprite*>::NSMutableArrayIterator iter;
		for (iter = m_pobDescendants->begin(); iter != m_pobDescendants->end(); ++iter)
		{
			pSprite = *iter;

			if (! pSprite)
			{
				break;
			}

			// fast dispatch
			if (pSprite->isDirty())
			{
				pSprite->updateTransform();
			}

#if CC_SPRITESHEET_DEBUG_DRAW
			CGRect rect = [child boundingBox]; //Issue #528
		CGPoint vertices[4]={
			ccp(rect.origin.x,rect.origin.y),
			ccp(rect.origin.x+rect.size.width,rect.origin.y),
			ccp(rect.origin.x+rect.size.width,rect.origin.y+rect.size.height),
			ccp(rect.origin.x,rect.origin.y+rect.size.height),
		};
		ccDrawPoly(vertices, 4, YES);
#endif // CC_SPRITESHEET_DEBUG_DRAW
		}
	}

	// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	// Needed states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	// Unneeded states: -
	bool newBlend = false;
	if (m_blendFunc.src != CC_BLEND_SRC || m_blendFunc.dst != CC_BLEND_DST)
	{
		newBlend = true;
		glBlendFunc(m_blendFunc.src, m_blendFunc.dst);
	}

	m_pobTextureAtlas->drawQuads();
	if (newBlend)
	{
		glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
	}
}

void CCSpriteSheet::increaseAtlasCapacity(void)
{
	// if we're going beyond the current TextureAtlas's capacity,
	// all the previously initialized sprites will need to redo their texture coords
	// this is likely computationally expensive
	unsigned int quantity = (m_pobTextureAtlas->getCapacity() + 1) * 4 / 3;

	CCLOG("cocos2d: CCSpriteSheet: resizing TextureAtlas capacity from %d to %d.", 
		m_pobTextureAtlas->getCapacity(), quantity);

	if (! m_pobTextureAtlas->resizeCapacity(quantity))
	{
		// serious problems
		CCLOG("cocos2d: WARNING: Not enough memory to resize the atlas");
		assert(false);
	}
}

unsigned int CCSpriteSheet::rebuildIndexInOrder(CCSprite *pobParent, unsigned int uIndex)
{
	NSMutableArray<CCNode*> *pChildren = pobParent->getChildren();

	if (pChildren && pChildren->count() > 0)
	{
		CCSprite *pSprite;
		NSMutableArray<CCNode*>::NSMutableArrayIterator iter;
		for (iter = pChildren->begin(); iter != pChildren->end(); ++iter)
		{
			pSprite = (CCSprite*)(*iter);

			if (! pSprite)
			{
				break;
			}

			if (pSprite->getZOrder() < 0)
			{
				uIndex = rebuildIndexInOrder(pSprite, uIndex);
			}
		}
	}	

	// ignore self (spritesheet)
	if (! pobParent->isEqual(this))
	{
		pobParent->setAtlasIndex(uIndex);
		uIndex++;
	}

	if (pChildren && pChildren->count() > 0)
	{
		CCSprite *pSprite;
		NSMutableArray<CCNode*>::NSMutableArrayIterator iter;
		for (iter = pChildren->begin(); iter != pChildren->end(); ++iter)
		{
			pSprite = (CCSprite*)(*iter);

			if (! pSprite)
			{
				break;
			}

			if (pSprite->getZOrder() >= 0)
			{
				uIndex = rebuildIndexInOrder(pSprite, uIndex);
			}
		}
	}

	return uIndex;
}

unsigned int CCSpriteSheet::highestAtlasIndexInChild(CCSprite *pSprite)
{
	NSMutableArray<CCNode*> *pChildren = pSprite->getChildren();

	if (! pChildren || pChildren->count() == 0)
	{
		return pSprite->getAtlasIndex();
	}
	else
	{
		return highestAtlasIndexInChild((CCSprite*)(pChildren->getLastObject()));
	}
}

unsigned int CCSpriteSheet::lowestAtlasIndexInChild(CCSprite *pSprite)
{
	NSMutableArray<CCNode*> *pChildren = pSprite->getChildren();

	if (! pChildren || pChildren->count() == 0)
	{
		return pSprite->getAtlasIndex();
	}
	else
	{
		return lowestAtlasIndexInChild((CCSprite*)(pChildren->getObjectAtIndex(0)));
	}
}

unsigned int CCSpriteSheet::atlasIndexForChild(CCSprite *pobSprite, int nZ)
{
	NSMutableArray<CCNode*> *pBrothers = pobSprite->getParent()->getChildren();
	unsigned int uChildIndex = pBrothers->getIndexOfObject(pobSprite);

	// ignore parent Z if parent is spriteSheet
	bool bIgnoreParent = (CCSpriteSheet*)(pobSprite->getParent()) == this;
	CCSprite *pPrevious = NULL;
	if (uChildIndex > 0)
	{
		pPrevious = (CCSprite*)(pBrothers->getObjectAtIndex(uChildIndex - 1));
	}

	// first child of the sprite sheet
	if (bIgnoreParent)
	{
		if (uChildIndex == 0)
		{
			return 0;
		}

		return highestAtlasIndexInChild(pPrevious) + 1;
	}

	// parent is a CCSprite, so, it must be taken into account

	// first child of an CCSprite ?
	if (uChildIndex == 0)
	{
		CCSprite *p = (CCSprite*)(pobSprite->getParent());

		// less than parent and brothers
		if (nZ < 0)
		{
			return p->getAtlasIndex();
		}
		else
		{
			return p->getAtlasIndex() + 1;
		}
	}
	else
	{
		// previous & sprite belong to the same branch
		if ((pPrevious->getZOrder() < 0 && nZ < 0) || (pPrevious->getZOrder() >= 0 && nZ >= 0))
		{
			return highestAtlasIndexInChild(pPrevious) + 1;
		}

		// else (previous < 0 and sprite >= 0 )
		CCSprite *p = (CCSprite*)(pobSprite->getParent());
		return p->getAtlasIndex() + 1;
	}

	// Should not happen. Error calculating Z on SpriteSheet
	assert(0);
	return 0;
}

// add child helper

void CCSpriteSheet::insertChild(CCSprite *pobSprite, unsigned int uIndex)
{
	pobSprite->useSpriteSheetRender(this);
	pobSprite->setAtlasIndex(uIndex);
	pobSprite->setDirty(true);

	if (m_pobTextureAtlas->getTotalQuads() == m_pobTextureAtlas->getCapacity())
	{
		increaseAtlasCapacity();
	}

	ccV3F_C4B_T2F_Quad quad = pobSprite->getQuad();
	m_pobTextureAtlas->insertQuad(&quad, uIndex);

	m_pobDescendants->insertObjectAtIndex(pobSprite, uIndex);

	// update indices
	unsigned int i = 0;
	if (m_pobDescendants && m_pobDescendants->count() > 0)
	{
		NSMutableArray<CCSprite*>::NSMutableArrayIterator iter;
		for (iter = m_pobDescendants->begin(); iter != m_pobDescendants->end(); ++iter)
		{
			if (! *iter)
			{
				break;
			}

			if (i > uIndex)
			{
				(*iter)->setAtlasIndex((*iter)->getAtlasIndex() + 1);
			}
            
			++i;
		}
	}	

	// add children recursively
	NSMutableArray<CCNode*> *pChildren = pobSprite->getChildren();
	if (pChildren && pChildren->count() > 0)
	{
		NSMutableArray<CCNode*>::NSMutableArrayIterator iterNode;
		CCSprite *pSprite;
		for (iterNode = pChildren->begin(); iterNode != pChildren->end(); ++iterNode)
		{
			pSprite = (CCSprite*)(*iterNode);

			if (! pSprite)
			{
				break;
			}

			unsigned int uIndex = atlasIndexForChild(pSprite, pSprite->getZOrder());
			insertChild(pSprite, uIndex);
		}
	}
	
}

void CCSpriteSheet::removeSpriteFromAtlas(CCSprite *pobSprite)
{
    // remove from TextureAtlas
	m_pobTextureAtlas->removeQuadAtIndex(pobSprite->getAtlasIndex());

	// Cleanup sprite. It might be reused (issue #569)
	pobSprite->useSelfRender();

	unsigned int uIndex = m_pobDescendants->getIndexOfObject(pobSprite);
	if (uIndex != -1)
	{
		m_pobDescendants->removeObjectAtIndex(uIndex);

		// update all sprites beyond this one
		unsigned int count = m_pobDescendants->count();
		
		for(; uIndex < count; ++uIndex)
		{
			CCSprite* s = (CCSprite*)(m_pobDescendants->getObjectAtIndex(uIndex));
			s->setAtlasIndex( s->getAtlasIndex() - 1 );
		}
	}

	// remove children recursively
	NSMutableArray<CCNode*> *pChildren = pobSprite->getChildren();
	
	if (pChildren && pChildren->count() > 0)
	{
		CCSprite *pSprite;
		NSMutableArray<CCNode*>::NSMutableArrayIterator iter;
		for (iter = pChildren->begin(); iter != pChildren->end(); ++iter)
		{
			pSprite = (CCSprite*)(*iter);

			if (! pSprite)
			{
				break;
			}

			removeSpriteFromAtlas(pSprite);
		}
	}
}

void CCSpriteSheet::updateBlendFunc(void)
{
	if (! m_pobTextureAtlas->getTexture()->getHasPremultipliedAlpha())
	{
		m_blendFunc.src = GL_SRC_ALPHA;
		m_blendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
	}
}

// CocosNodeTexture protocol
void CCSpriteSheet::setBlendFunc(ccBlendFunc blendFunc)
{
	m_blendFunc = blendFunc;
}

ccBlendFunc CCSpriteSheet::getBlendFunc(void)
{
	return m_blendFunc;
}

CCTexture2D* CCSpriteSheet::getTexture(void)
{
	return m_pobTextureAtlas->getTexture();
}

void CCSpriteSheet::setTexture(CCTexture2D *texture)
{
	m_pobTextureAtlas->setTexture(texture);
}
}//namespace   cocos2d 
