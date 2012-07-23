/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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
#include "textures/CCTextureCache.h"
#include "support/CCPointExtension.h"
#include "shaders/CCShaderCache.h"
#include "shaders/CCGLProgram.h"
#include "shaders/ccGLStateCache.h"
#include "CCDirector.h"
#include "support/TransformUtils.h"
#include "support/CCProfiling.h"
// external
#include "kazmath/GL/matrix.h"

NS_CC_BEGIN

/*
* creation with CCTexture2D
*/

CCSpriteBatchNode* CCSpriteBatchNode::batchNodeWithTexture(CCTexture2D* tex, unsigned int capacity/* = kDefaultSpriteBatchCapacity*/)
{
    return CCSpriteBatchNode::createWithTexture(tex, capacity);
}

CCSpriteBatchNode* CCSpriteBatchNode::createWithTexture(CCTexture2D* tex, unsigned int capacity/* = kDefaultSpriteBatchCapacity*/)
{
    CCSpriteBatchNode *batchNode = new CCSpriteBatchNode();
    batchNode->initWithTexture(tex, capacity);
    batchNode->autorelease();

    return batchNode;
}

/*
* creation with File Image
*/
CCSpriteBatchNode* CCSpriteBatchNode::batchNodeWithFile(const char *fileImage, unsigned int capacity/* = kDefaultSpriteBatchCapacity*/)
{
    return CCSpriteBatchNode::create(fileImage, capacity);
}

CCSpriteBatchNode* CCSpriteBatchNode::create(const char *fileImage, unsigned int capacity/* = kDefaultSpriteBatchCapacity*/)
{
    CCSpriteBatchNode *batchNode = new CCSpriteBatchNode();
    batchNode->initWithFile(fileImage, capacity);
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

    if (0 == capacity)
    {
        capacity = kDefaultSpriteBatchCapacity;
    }
    
    m_pobTextureAtlas->initWithTexture(tex, capacity);

    updateBlendFunc();

    // no lazy alloc in this node
    m_pChildren = new CCArray();
    m_pChildren->initWithCapacity(capacity);

    m_pobDescendants = new CCArray();
    m_pobDescendants->initWithCapacity(capacity);

    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
    return true;
}

bool CCSpriteBatchNode::init()
{
    CCTexture2D * texture = new CCTexture2D();
    texture->autorelease();
    return this->initWithTexture(texture, 0);
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
    CC_PROFILER_START_CATEGORY(kCCProfilerCategoryBatchSprite, "CCSpriteBatchNode - visit");

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

    kmGLPushMatrix();

    if (m_pGrid && m_pGrid->isActive())
    {
        m_pGrid->beforeDraw();
        transformAncestors();
    }

    sortAllChildren();
    transform();

    draw();

    if (m_pGrid && m_pGrid->isActive())
    {
        m_pGrid->afterDraw(this);
    }

    kmGLPopMatrix();
    setOrderOfArrival(0);

    CC_PROFILER_STOP_CATEGORY(kCCProfilerCategoryBatchSprite, "CCSpriteBatchNode - visit");

}

void CCSpriteBatchNode::addChild(CCNode *child, int zOrder, int tag)
{
    CCAssert(child != NULL, "child should not be null");
    CCAssert(dynamic_cast<CCSprite*>(child) != NULL, "CCSpriteBatchNode only supports CCSprites as children");
    CCSprite *pSprite = (CCSprite*)(child);
    // check CCSprite is using the same texture id
    CCAssert(pSprite->getTexture()->getName() == m_pobTextureAtlas->getTexture()->getName(), "CCSprite is not using the same texture id");

    CCNode::addChild(child, zOrder, tag);

    appendChild(pSprite);
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
    CCAssert(m_pChildren->containsObject(child), "Child doesn't belong to Sprite");

    if (zOrder == child->getZOrder())
    {
        return;
    }

    //set the z-order and sort later
    CCNode::reorderChild(child, zOrder);
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
    // useSelfRender should be performed on all descendants. issue #1216
    arrayMakeObjectsPerformSelectorWithObject(m_pobDescendants, setBatchNode, NULL, CCSprite*);

    CCNode::removeAllChildrenWithCleanup(bCleanup);

    m_pobDescendants->removeAllObjects();
    m_pobTextureAtlas->removeAllQuads();
}

//override sortAllChildren
void CCSpriteBatchNode::sortAllChildren()
{
    if (m_bReorderChildDirty)
    {
        int i = 0,j = 0,length = m_pChildren->data->num;
        CCNode ** x = (CCNode**)m_pChildren->data->arr;
        CCNode *tempItem = NULL;

        //insertion sort
        for(i=1; i<length; i++)
        {
            tempItem = x[i];
            j = i-1;

            //continue moving element downwards while zOrder is smaller or when zOrder is the same but orderOfArrival is smaller
            while(j>=0 && ( tempItem->getZOrder() < x[j]->getZOrder() || ( tempItem->getZOrder() == x[j]->getZOrder() && tempItem->getOrderOfArrival() < x[j]->getOrderOfArrival() ) ) )
            {
                x[j+1] = x[j];
                j--;
            }

            x[j+1] = tempItem;
        }

        //sorted now check all children
        if (m_pChildren->count() > 0)
        {
            //first sort all children recursively based on zOrder
            arrayMakeObjectsPerformSelector(m_pChildren, sortAllChildren, CCSprite*);

            int index=0;

            CCObject* pObj = NULL;
            //fast dispatch, give every child a new atlasIndex based on their relative zOrder (keep parent -> child relations intact)
            // and at the same time reorder descedants and the quads to the right index
            CCARRAY_FOREACH(m_pChildren, pObj)
            {
                CCSprite* pChild = (CCSprite*)pObj;
                updateAtlasIndex(pChild, &index);
            }
        }

        m_bReorderChildDirty=false;
    }
}

void CCSpriteBatchNode::updateAtlasIndex(CCSprite* sprite, int* curIndex)
{
    unsigned int count = 0;
    CCArray* pArray = sprite->getChildren();
    if (pArray != NULL)
    {
        count = pArray->count();
    }
    
    int oldIndex = 0;

    if( count == 0 )
    {
        oldIndex = sprite->getAtlasIndex();
        sprite->setAtlasIndex(*curIndex);
        sprite->setOrderOfArrival(0);
        if (oldIndex != *curIndex){
            swap(oldIndex, *curIndex);
        }
        (*curIndex)++;
    }
    else
    {
        bool needNewIndex=true;

        if (((CCSprite*) (pArray->data->arr[0]))->getZOrder() >= 0)
        {
            //all children are in front of the parent
            oldIndex = sprite->getAtlasIndex();
            sprite->setAtlasIndex(*curIndex);
            sprite->setOrderOfArrival(0);
            if (oldIndex != *curIndex)
            {
                swap(oldIndex, *curIndex);
            }
            (*curIndex)++;

            needNewIndex = false;
        }

        CCObject* pObj = NULL;
        CCARRAY_FOREACH(pArray,pObj)
        {
            CCSprite* child = (CCSprite*)pObj;
            if (needNewIndex && child->getZOrder() >= 0)
            {
                oldIndex = sprite->getAtlasIndex();
                sprite->setAtlasIndex(*curIndex);
                sprite->setOrderOfArrival(0);
                if (oldIndex != *curIndex) {
                    this->swap(oldIndex, *curIndex);
                }
                (*curIndex)++;
                needNewIndex = false;

            }

            updateAtlasIndex(child, curIndex);
        }

        if (needNewIndex)
        {//all children have a zOrder < 0)
            oldIndex=sprite->getAtlasIndex();
            sprite->setAtlasIndex(*curIndex);
            sprite->setOrderOfArrival(0);
            if (oldIndex!=*curIndex) {
                swap(oldIndex, *curIndex);
            }
            (*curIndex)++;
        }
    }
}

void CCSpriteBatchNode::swap(int oldIndex, int newIndex)
{
    CCObject** x = m_pobDescendants->data->arr;
    ccV3F_C4B_T2F_Quad* quads = m_pobTextureAtlas->getQuads();

    CCObject* tempItem = x[oldIndex];
    ccV3F_C4B_T2F_Quad tempItemQuad=quads[oldIndex];

    //update the index of other swapped item
    ((CCSprite*) x[newIndex])->setAtlasIndex(oldIndex);

    x[oldIndex]=x[newIndex];
    quads[oldIndex]=quads[newIndex];
    x[newIndex]=tempItem;
    quads[newIndex]=tempItemQuad;
}

void CCSpriteBatchNode::reorderBatch(bool reorder)
{
    m_bReorderChildDirty=reorder;
}

// draw
void CCSpriteBatchNode::draw(void)
{
    CC_PROFILER_START("CCSpriteBatchNode - draw");

    // Optimization: Fast Dispatch
    if( m_pobTextureAtlas->getTotalQuads() == 0 )
    {
        return;
    }

    CC_NODE_DRAW_SETUP();

    arrayMakeObjectsPerformSelector(m_pChildren, updateTransform, CCSprite*);

    ccGLBlendFunc( m_blendFunc.src, m_blendFunc.dst );

    m_pobTextureAtlas->drawQuads();

    CC_PROFILER_STOP("CCSpriteBatchNode - draw");
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
        CCLOGWARN("cocos2d: WARNING: Not enough memory to resize the atlas");
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

void CCSpriteBatchNode::insertChild(CCSprite *pSprite, unsigned int uIndex)
{
    pSprite->setBatchNode(this);
    pSprite->setAtlasIndex(uIndex);
    pSprite->setDirty(true);

    if(m_pobTextureAtlas->getTotalQuads() == m_pobTextureAtlas->getCapacity())
    {
        increaseAtlasCapacity();
    }

    ccV3F_C4B_T2F_Quad quad = pSprite->getQuad();
    m_pobTextureAtlas->insertQuad(&quad, uIndex);

    ccArray *descendantsData = m_pobDescendants->data;

    ccArrayInsertObjectAtIndex(descendantsData, pSprite, uIndex);

    // update indices
    unsigned int i = uIndex+1;
    
    CCSprite* pChild = NULL;
    for(; i<descendantsData->num; i++){
        pChild = (CCSprite*)descendantsData->arr[i];
        pChild->setAtlasIndex(pChild->getAtlasIndex() + 1);
    }

    // add children recursively
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(pSprite->getChildren(), pObj)
    {
        pChild = (CCSprite*)pObj;
        unsigned int idx = atlasIndexForChild(pChild, pChild->getZOrder());
        insertChild(pChild, idx);
    }
}

// addChild helper, faster than insertChild
void CCSpriteBatchNode::appendChild(CCSprite* sprite)
{
    m_bReorderChildDirty=true;
    sprite->setBatchNode(this);
    sprite->setDirty(true);

    if(m_pobTextureAtlas->getTotalQuads() == m_pobTextureAtlas->getCapacity()) {
        increaseAtlasCapacity();
    }

    ccArray *descendantsData = m_pobDescendants->data;

    ccArrayAppendObjectWithResize(descendantsData, sprite);

    unsigned int index=descendantsData->num-1;

    sprite->setAtlasIndex(index);

    ccV3F_C4B_T2F_Quad quad = sprite->getQuad();
    m_pobTextureAtlas->insertQuad(&quad, index);

    // add children recursively
    
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(sprite->getChildren(), pObj)
    {
        CCSprite* child = (CCSprite*)pObj;
        appendChild(child);
    }
}

void CCSpriteBatchNode::removeSpriteFromAtlas(CCSprite *pobSprite)
{
    // remove from TextureAtlas
    m_pobTextureAtlas->removeQuadAtIndex(pobSprite->getAtlasIndex());

    // Cleanup sprite. It might be reused (issue #569)
    pobSprite->setBatchNode(NULL);

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
    if (! m_pobTextureAtlas->getTexture()->hasPremultipliedAlpha())
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
    CCAssert( sprite != NULL, "Argument must be non-NULL");
    CCAssert( dynamic_cast<CCSprite*>(sprite), "CCSpriteBatchNode only supports CCSprites as children");

    while(index >= m_pobTextureAtlas->getCapacity() || m_pobTextureAtlas->getCapacity() == m_pobTextureAtlas->getTotalQuads())
    {
        this->increaseAtlasCapacity();
    }
    //
    // update the quad directly. Don't add the sprite to the scene graph
    //
    sprite->setBatchNode(this);
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
    CCAssert( child != NULL, "Argument must be non-NULL");
    CCAssert( dynamic_cast<CCSprite*>(child), "CCSpriteBatchNode only supports CCSprites as children");

    // quad index is Z
    child->setAtlasIndex(z);

    // XXX: optimize with a binary search
    int i=0;
 
    CCObject* pObject = NULL;
    CCARRAY_FOREACH(m_pobDescendants, pObject)
    {
        CCSprite* pChild = (CCSprite*) pObject;
        if (pChild && (pChild->getAtlasIndex() >= z))
        {
            ++i;
        }
    }
    
    m_pobDescendants->insertObject(child, i);

    // IMPORTANT: Call super, and not self. Avoid adding it to the texture atlas array
    CCNode::addChild(child, z, aTag);
    //#issue 1262 don't use lazy sorting, tiles are added as quads not as sprites, so sprites need to be added in order
    reorderBatch(false);

    return this;
}

NS_CC_END
