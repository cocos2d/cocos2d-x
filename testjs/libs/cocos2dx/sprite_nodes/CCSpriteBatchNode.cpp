/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2009-2010 Ricardo Quesada
Copyright (c) 2009      Matt Oswald
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
#include "ccConfig.h"
#include "CCSprite.h"
#include "effects/CCGrid.h"
#include "CCDrawingPrimitives.h"
#include "CCTextureCache.h"
#include "CCPointExtension.h"

namespace cocos2d
{
	const int defaultCapacity = 29;

	/*
	* creation with CCTexture2D
	*/
	CCSpriteBatchNode* CCSpriteBatchNode::batchNodeWithTexture(CCTexture2D *tex)
	{
		CCSpriteBatchNode *batchNode = new CCSpriteBatchNode();
		batchNode->initWithTexture(tex, defaultCapacity);
		batchNode->autorelease();

		return batchNode;
	}

	CCSpriteBatchNode* CCSpriteBatchNode::batchNodeWithTexture(CCTexture2D* tex, unsigned int capacity)
	{
		CCSpriteBatchNode *batchNode = new CCSpriteBatchNode();
		batchNode->initWithTexture(tex, capacity);
		batchNode->autorelease();

		return batchNode;
	}

	/*
	* creation with File Image
	*/
	CCSpriteBatchNode* CCSpriteBatchNode::batchNodeWithFile(const char *fileImage, unsigned int capacity)
	{
		CCSpriteBatchNode *batchNode = new CCSpriteBatchNode();
		batchNode->initWithFile(fileImage, capacity);
		batchNode->autorelease();

		return batchNode;
	}

	CCSpriteBatchNode* CCSpriteBatchNode::batchNodeWithFile(const char *fileImage)
	{
		CCSpriteBatchNode *batchNode = new CCSpriteBatchNode();
		batchNode->initWithFile(fileImage, defaultCapacity);
		batchNode->autorelease();

		return batchNode;
	}

	/*
	* init with CCTexture2D
	*/
	bool CCSpriteBatchNode::initWithTexture(CCTexture2D *tex, unsigned int capacity)
	{
		m_blendFunc.src = CC_BLEND_SRC;
		m_blendFunc.dst = CC_BLEND_DST;
		m_pobTextureAtlas = new CCTextureAtlas();
		m_pobTextureAtlas->initWithTexture(tex, capacity);

		updateBlendFunc();

		// no lazy alloc in this node
        m_pChildren = CCArray::array();
		m_pobDescendants = CCArray::array();
        m_pChildren->retain();
        m_pobDescendants->retain();

		return true;
	}

	/*
	* init with FileImage
	*/
	bool CCSpriteBatchNode::initWithFile(const char* fileImage, unsigned int capacity)
	{
		CCTexture2D *pTexture2D = CCTextureCache::sharedTextureCache()->addImage(fileImage);
		return initWithTexture(pTexture2D, capacity);
	}

	CCSpriteBatchNode::~CCSpriteBatchNode()
	{
		CC_SAFE_RELEASE(m_pobTextureAtlas);
		CC_SAFE_RELEASE(m_pobDescendants);
	}

	// override visit
	// don't call visit on it's children
	void CCSpriteBatchNode::visit(void)
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

	void CCSpriteBatchNode::addChild(CCNode *child, int zOrder, int tag)
	{
		CCAssert(child != NULL, "child should not be null");

		CCSprite *pSprite = (CCSprite*)(child);
		// check CCSprite is using the same texture id
		CCAssert(pSprite->getTexture()->getName() == m_pobTextureAtlas->getTexture()->getName(), "");

		CCNode::addChild(child, zOrder, tag);

		unsigned int uIndex = atlasIndexForChild(pSprite, zOrder);
		insertChild(pSprite, uIndex);
	}

	void CCSpriteBatchNode::addChild(CCNode *child)
	{
		CCNode::addChild(child);
	}

	void CCSpriteBatchNode::addChild(CCNode *child, int zOrder)
	{
		CCNode::addChild(child, zOrder);
	}

	// override reorderChild
	void CCSpriteBatchNode::reorderChild(CCNode *child, int zOrder)
	{
		CCAssert(child != NULL, "the child should not be null");
		CCAssert(m_pChildren->containsObject(child), "sprite batch node should contain the child");

		if (zOrder == child->getZOrder())
		{
			return;
		}

		// xxx: instead of removing/adding, it is more efficient ot reorder manually
		child->retain();
		removeChild((CCSprite*)child, false);
		addChild(child, zOrder);
		child->release();
	}

	// override remove child
	void CCSpriteBatchNode::removeChild(CCNode *child, bool cleanup)
	{
		CCSprite *pSprite = (CCSprite*)(child);

		// explicit null handling
		if (pSprite == NULL)
		{
			return;
		}

		CCAssert(m_pChildren->containsObject(pSprite), "sprite batch node should contain the child");

		// cleanup before removing
		removeSpriteFromAtlas(pSprite);

		CCNode::removeChild(pSprite, cleanup);
	}

	void CCSpriteBatchNode::removeChildAtIndex(unsigned int uIndex, bool bDoCleanup)
	{
		removeChild((CCSprite*)(m_pChildren->objectAtIndex(uIndex)), bDoCleanup);
	}

	void CCSpriteBatchNode::removeAllChildrenWithCleanup(bool bCleanup)
	{
		// Invalidate atlas index. issue #569
		if (m_pChildren && m_pChildren->count() > 0)
		{
            CCObject* pObject = NULL;
            CCARRAY_FOREACH(m_pChildren, pObject)
            {
                CCSprite* pChild = (CCSprite*) pObject;
                if (pChild)
                {
                    removeSpriteFromAtlas(pChild);
                }
            }
		}

		CCNode::removeAllChildrenWithCleanup(bCleanup);

		m_pobDescendants->removeAllObjects();
		m_pobTextureAtlas->removeAllQuads();
	}

	// draw
	void CCSpriteBatchNode::draw(void)
	{
		CCNode::draw();

		// Optimization: Fast Dispatch	
		if (m_pobTextureAtlas->getTotalQuads() == 0)
		{
			return;
		}

		if (m_pobDescendants && m_pobDescendants->count() > 0)
		{
            CCObject* pObject = NULL;
            CCARRAY_FOREACH(m_pobDescendants, pObject)
            {
                CCSprite* pChild = (CCSprite*) pObject;
                if (pChild)
                {
                    // fast dispatch
                    pChild->updateTransform();


#if CC_SPRITEBATCHNODE_DEBUG_DRAW
                    // issue #528
                    CCRect rect = pChild->boundingBox();
                    CCPoint vertices[4]={
                        ccp(rect.origin.x,rect.origin.y),
                        ccp(rect.origin.x+rect.size.width,rect.origin.y),
                        ccp(rect.origin.x+rect.size.width,rect.origin.y+rect.size.height),
                        ccp(rect.origin.x,rect.origin.y+rect.size.height),
                    };
                    ccDrawPoly(vertices, 4, true);
#endif // CC_SPRITEBATCHNODE_DEBUG_DRAW
                }
            }
		}

		// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
		// Needed states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
		// Unneeded states: -
		bool newBlend = m_blendFunc.src != CC_BLEND_SRC || m_blendFunc.dst != CC_BLEND_DST;
		if (newBlend)
		{
			glBlendFunc(m_blendFunc.src, m_blendFunc.dst);
		}

		m_pobTextureAtlas->drawQuads();
		if (newBlend)
		{
			glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
		}
	}

	void CCSpriteBatchNode::increaseAtlasCapacity(void)
	{
		// if we're going beyond the current TextureAtlas's capacity,
		// all the previously initialized sprites will need to redo their texture coords
		// this is likely computationally expensive
		unsigned int quantity = (m_pobTextureAtlas->getCapacity() + 1) * 4 / 3;

        CCLOG("cocos2d: CCSpriteBatchNode: resizing TextureAtlas capacity from [%lu] to [%lu].",
            (long)m_pobTextureAtlas->getCapacity(),
            (long)quantity);

		if (! m_pobTextureAtlas->resizeCapacity(quantity))
		{
			// serious problems
			CCLOG("cocos2d: WARNING: Not enough memory to resize the atlas");
			CCAssert(false, "Not enough memory to resize the atla");
		}
	}

	unsigned int CCSpriteBatchNode::rebuildIndexInOrder(CCSprite *pobParent, unsigned int uIndex)
	{
		CCArray *pChildren = pobParent->getChildren();

		if (pChildren && pChildren->count() > 0)
		{
            CCObject* pObject = NULL;
            CCARRAY_FOREACH(pChildren, pObject)
            {
                CCSprite* pChild = (CCSprite*) pObject;
                if (pChild && (pChild->getZOrder() < 0))
                {
                    uIndex = rebuildIndexInOrder(pChild, uIndex);
                }
            }
		}	

		// ignore self (batch node)
		if (! pobParent->isEqual(this))
		{
			pobParent->setAtlasIndex(uIndex);
			uIndex++;
		}

		if (pChildren && pChildren->count() > 0)
		{
            CCObject* pObject = NULL;
            CCARRAY_FOREACH(pChildren, pObject)
            {
                CCSprite* pChild = (CCSprite*) pObject;
                if (pChild && (pChild->getZOrder() >= 0))
                {
                    uIndex = rebuildIndexInOrder(pChild, uIndex);
                }
            }
		}

		return uIndex;
	}

	unsigned int CCSpriteBatchNode::highestAtlasIndexInChild(CCSprite *pSprite)
	{
		CCArray *pChildren = pSprite->getChildren();

		if (! pChildren || pChildren->count() == 0)
		{
			return pSprite->getAtlasIndex();
		}
		else
		{
			return highestAtlasIndexInChild((CCSprite*)(pChildren->lastObject()));
		}
	}

	unsigned int CCSpriteBatchNode::lowestAtlasIndexInChild(CCSprite *pSprite)
	{
		CCArray *pChildren = pSprite->getChildren();

		if (! pChildren || pChildren->count() == 0)
		{
			return pSprite->getAtlasIndex();
		}
		else
		{
			return lowestAtlasIndexInChild((CCSprite*)(pChildren->objectAtIndex(0)));
		}
	}

	unsigned int CCSpriteBatchNode::atlasIndexForChild(CCSprite *pobSprite, int nZ)
	{
		CCArray *pBrothers = pobSprite->getParent()->getChildren();
		unsigned int uChildIndex = pBrothers->indexOfObject(pobSprite);

		// ignore parent Z if parent is spriteSheet
		bool bIgnoreParent = (CCSpriteBatchNode*)(pobSprite->getParent()) == this;
		CCSprite *pPrevious = NULL;
		if (uChildIndex > 0 &&
            uChildIndex < UINT_MAX)
		{
			pPrevious = (CCSprite*)(pBrothers->objectAtIndex(uChildIndex - 1));
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
		CCAssert(0, "should not run here");
		return 0;
	}

	// add child helper

	void CCSpriteBatchNode::insertChild(CCSprite *pobSprite, unsigned int uIndex)
	{
		pobSprite->useBatchNode(this);
		pobSprite->setAtlasIndex(uIndex);
		pobSprite->setDirty(true);

		if (m_pobTextureAtlas->getTotalQuads() == m_pobTextureAtlas->getCapacity())
		{
			increaseAtlasCapacity();
		}

		ccV3F_C4B_T2F_Quad quad = pobSprite->getQuad();
		m_pobTextureAtlas->insertQuad(&quad, uIndex);

		m_pobDescendants->insertObject(pobSprite, uIndex);

		// update indices
		unsigned int i = 0;
		if (m_pobDescendants && m_pobDescendants->count() > 0)
		{
            CCObject* pObject = NULL;
            CCARRAY_FOREACH(m_pobDescendants, pObject)
            {
                CCSprite* pChild = (CCSprite*) pObject;
                if (pChild)
                {
                    if (i > uIndex)
                    {
                        pChild->setAtlasIndex(pChild->getAtlasIndex() + 1);
                    }

                    ++i;
                }
            }
		}	

		// add children recursively
		CCArray *pChildren = pobSprite->getChildren();
		if (pChildren && pChildren->count() > 0)
		{
            CCObject* pObject = NULL;
            CCARRAY_FOREACH(pChildren, pObject)
            {
                CCSprite* pChild = (CCSprite*) pObject;
                if (pChild)
                {
                    unsigned int uIndex = atlasIndexForChild(pChild, pChild->getZOrder());
                    insertChild(pChild, uIndex);
                }
            }
		}
	}

	void CCSpriteBatchNode::removeSpriteFromAtlas(CCSprite *pobSprite)
	{
		// remove from TextureAtlas
		m_pobTextureAtlas->removeQuadAtIndex(pobSprite->getAtlasIndex());

		// Cleanup sprite. It might be reused (issue #569)
		pobSprite->useSelfRender();

		unsigned int uIndex = m_pobDescendants->indexOfObject(pobSprite);
		if (uIndex != UINT_MAX)
		{
			m_pobDescendants->removeObjectAtIndex(uIndex);

			// update all sprites beyond this one
			unsigned int count = m_pobDescendants->count();

			for(; uIndex < count; ++uIndex)
			{
				CCSprite* s = (CCSprite*)(m_pobDescendants->objectAtIndex(uIndex));
				s->setAtlasIndex( s->getAtlasIndex() - 1 );
			}
		}

		// remove children recursively
		CCArray *pChildren = pobSprite->getChildren();
		if (pChildren && pChildren->count() > 0)
		{
            CCObject* pObject = NULL;
            CCARRAY_FOREACH(pChildren, pObject)
            {
                CCSprite* pChild = (CCSprite*) pObject;
                if (pChild)
                {
                    removeSpriteFromAtlas(pChild);
                }
            }
		}
	}

	void CCSpriteBatchNode::updateBlendFunc(void)
	{
		if (! m_pobTextureAtlas->getTexture()->getHasPremultipliedAlpha())
		{
			m_blendFunc.src = GL_SRC_ALPHA;
			m_blendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
		}
	}

	// CocosNodeTexture protocol
	void CCSpriteBatchNode::setBlendFunc(ccBlendFunc blendFunc)
	{
		m_blendFunc = blendFunc;
	}

	ccBlendFunc CCSpriteBatchNode::getBlendFunc(void)
	{
		return m_blendFunc;
	}

	CCTexture2D* CCSpriteBatchNode::getTexture(void)
	{
		return m_pobTextureAtlas->getTexture();
	}

	void CCSpriteBatchNode::setTexture(CCTexture2D *texture)
	{
		m_pobTextureAtlas->setTexture(texture);
		updateBlendFunc();
	}


    // CCSpriteSheet Extension
    //implementation CCSpriteSheet (TMXTiledMapExtension)

    void CCSpriteBatchNode::addQuadFromSprite(CCSprite *sprite, unsigned int index)
    {
        CCAssert( sprite != NULL, "Argument must be non-nil");
        /// @todo CCAssert( [sprite isKindOfClass:[CCSprite class]], @"CCSpriteSheet only supports CCSprites as children");

        while(index >= m_pobTextureAtlas->getCapacity() || m_pobTextureAtlas->getCapacity() == m_pobTextureAtlas->getTotalQuads())
        {
            this->increaseAtlasCapacity();
        }
        //
        // update the quad directly. Don't add the sprite to the scene graph
        //
        sprite->useBatchNode(this);
        sprite->setAtlasIndex(index);

        ccV3F_C4B_T2F_Quad quad = sprite->getQuad();
        m_pobTextureAtlas->insertQuad(&quad, index);

        // XXX: updateTransform will update the textureAtlas too using updateQuad.
        // XXX: so, it should be AFTER the insertQuad
        sprite->setDirty(true);
        sprite->updateTransform();
    }

    CCSpriteBatchNode * CCSpriteBatchNode::addSpriteWithoutQuad(CCSprite*child, unsigned int z, int aTag)
    {
        CCAssert( child != NULL, "Argument must be non-nil");
        /// @todo CCAssert( [child isKindOfClass:[CCSprite class]], @"CCSpriteSheet only supports CCSprites as children");

        // quad index is Z
        child->setAtlasIndex(z);

        // XXX: optimize with a binary search
        int i=0;
        if (m_pobDescendants && m_pobDescendants->count() > 0)
        {
            CCObject* pObject = NULL;
            CCARRAY_FOREACH(m_pobDescendants, pObject)
            {
                CCSprite* pChild = (CCSprite*) pObject;
                if (pChild && (pChild->getAtlasIndex() >= z))
                {
                    ++i;
                }
            }
        }
        m_pobDescendants->insertObject(child, i);

        // IMPORTANT: Call super, and not self. Avoid adding it to the texture atlas array
        CCNode::addChild(child, z, aTag);
        return this;
    }

}