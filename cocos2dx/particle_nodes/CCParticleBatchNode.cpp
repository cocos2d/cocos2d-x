/*
 * Copyright (c) 2010-2012 cocos2d-x.org
 * Copyright (C) 2009 Matt Oswald
 * Copyright (c) 2009-2010 Ricardo Quesada
 * Copyright (c) 2011 Zynga Inc.
 * Copyright (c) 2011 Marco Tillemans
 *
 * http://www.cocos2d-x.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "CCParticleBatchNode.h"
#include "textures/CCTextureCache.h"
#include "textures/CCTextureAtlas.h"
#include "ccConfig.h"
#include "ccMacros.h"
#include "effects/CCGrid.h"
#include "support/CCPointExtension.h"
#include "CCParticleSystem.h"
#include "shaders/CCShaderCache.h"
#include "shaders/CCGLProgram.h"
#include "shaders/ccGLStateCache.h"
#include "support/base64.h"
#include "support/zip_support/ZipUtils.h"
#include "platform/CCFileUtils.h"
#include "kazmath/GL/matrix.h"

NS_CC_BEGIN

CCParticleBatchNode::CCParticleBatchNode()
: m_pTextureAtlas(NULL)
{

}

CCParticleBatchNode::~CCParticleBatchNode()
{
    CC_SAFE_RELEASE(m_pTextureAtlas);
}
/*
 * creation with CCTexture2D
 */
CCParticleBatchNode* CCParticleBatchNode::batchNodeWithTexture(CCTexture2D *tex, unsigned int capacity/* = kCCParticleDefaultCapacity*/)
{
    return CCParticleBatchNode::createWithTexture(tex, capacity);
}

CCParticleBatchNode* CCParticleBatchNode::createWithTexture(CCTexture2D *tex, unsigned int capacity/* = kCCParticleDefaultCapacity*/)
{
    CCParticleBatchNode * p = new CCParticleBatchNode();
    if( p && p->initWithTexture(tex, capacity))
    {
        p->autorelease();
        return p;
    }
    CC_SAFE_DELETE(p);
    return NULL;
}

/*
 * creation with File Image
 */
CCParticleBatchNode* CCParticleBatchNode::batchNodeWithFile(const char* imageFile, unsigned int capacity/* = kCCParticleDefaultCapacity*/)
{
    return CCParticleBatchNode::create(imageFile, capacity);
}

CCParticleBatchNode* CCParticleBatchNode::create(const char* imageFile, unsigned int capacity/* = kCCParticleDefaultCapacity*/)
{
    CCParticleBatchNode * p = new CCParticleBatchNode();
    if( p && p->initWithFile(imageFile, capacity))
    {
        p->autorelease();
        return p;
    }
    CC_SAFE_DELETE(p);
    return NULL;
}

/*
 * init with CCTexture2D
 */
bool CCParticleBatchNode::initWithTexture(CCTexture2D *tex, unsigned int capacity)
{
    m_pTextureAtlas = new CCTextureAtlas();
    m_pTextureAtlas->initWithTexture(tex, capacity);

    // no lazy alloc in this node
    m_pChildren = new CCArray();
    m_pChildren->initWithCapacity(capacity);

    m_tBlendFunc.src = CC_BLEND_SRC;
    m_tBlendFunc.dst = CC_BLEND_DST;

    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
    
    return true;
}

/*
 * init with FileImage
 */
bool CCParticleBatchNode::initWithFile(const char* fileImage, unsigned int capacity)
{
    CCTexture2D *tex = CCTextureCache::sharedTextureCache()->addImage(fileImage);
    return initWithTexture(tex, capacity);
}

// CCParticleBatchNode - composition

// override visit.
// Don't call visit on it's children
void CCParticleBatchNode::visit()
{
    // CAREFUL:
    // This visit is almost identical to CCNode#visit
    // with the exception that it doesn't call visit on it's children
    //
    // The alternative is to have a void CCSprite#visit, but
    // although this is less maintainable, is faster
    //
    if (!m_bIsVisible)
    {
        return;
    }

    kmGLPushMatrix();

    if ( m_pGrid && m_pGrid->isActive())
    {
        m_pGrid->beforeDraw();
        transformAncestors();
    }

    transform();

    draw();

    if ( m_pGrid && m_pGrid->isActive())
    {
        m_pGrid->afterDraw(this);
    }

    kmGLPopMatrix();
}

// override addChild:
void CCParticleBatchNode::addChild(CCNode * child)
{
    CCNode::addChild(child);
}

void CCParticleBatchNode::addChild(CCNode * child, int zOrder)
{
    CCNode::addChild(child, zOrder);
}

void CCParticleBatchNode::addChild(CCNode * child, int zOrder, int tag)
{
    CCAssert( child != NULL, "Argument must be non-NULL");
    CCAssert( dynamic_cast<CCParticleSystem*>(child) != NULL, "CCParticleBatchNode only supports CCQuadParticleSystems as children");
    CCParticleSystem* pChild = (CCParticleSystem*)child;
    CCAssert( pChild->getTexture()->getName() == m_pTextureAtlas->getTexture()->getName(), "CCParticleSystem is not using the same texture id");
    // If this is the 1st children, then copy blending function
    if( m_pChildren->count() == 0 ) 
    {
        setBlendFunc(pChild->getBlendFunc());
    }

    CCAssert( m_tBlendFunc.src  == pChild->getBlendFunc().src && m_tBlendFunc.dst  == pChild->getBlendFunc().dst, "Can't add a PaticleSystem that uses a different blending function");

    //no lazy sorting, so don't call super addChild, call helper instead
    unsigned int pos = addChildHelper(pChild,zOrder,tag);

    //get new atlasIndex
    unsigned int atlasIndex = 0;

    if (pos != 0) 
    {
        CCParticleSystem* p = (CCParticleSystem*)m_pChildren->objectAtIndex(pos-1);
        atlasIndex = p->getAtlasIndex() + p->getTotalParticles();

    }
    else
    {
        atlasIndex = 0;
    }

    insertChild(pChild, atlasIndex);

    // update quad info
    pChild->setBatchNode(this);
}

// don't use lazy sorting, reordering the particle systems quads afterwards would be too complex
// XXX research whether lazy sorting + freeing current quads and calloc a new block with size of capacity would be faster
// XXX or possibly using vertexZ for reordering, that would be fastest
// this helper is almost equivalent to CCNode's addChild, but doesn't make use of the lazy sorting
unsigned int CCParticleBatchNode::addChildHelper(CCParticleSystem* child, int z, int aTag)
{
    CCAssert( child != NULL, "Argument must be non-nil");
    CCAssert( child->getParent() == NULL, "child already added. It can't be added again");

    if( ! m_pChildren ) 
    {
        m_pChildren = new CCArray();
        m_pChildren->initWithCapacity(4);
    }

    //don't use a lazy insert
    unsigned int pos = searchNewPositionInChildrenForZ(z);

    m_pChildren->insertObject(child, pos);

    child->setTag(aTag);
    child->_setZOrder(z);

    child->setParent(this);

    if( m_bIsRunning ) 
    {
        child->onEnter();
        child->onEnterTransitionDidFinish();
    }
    return pos;
}

// Reorder will be done in this function, no "lazy" reorder to particles
void CCParticleBatchNode::reorderChild(CCNode * child, int zOrder)
{
    CCAssert( child != NULL, "Child must be non-NULL");
    CCAssert( dynamic_cast<CCParticleSystem*>(child) != NULL, "CCParticleBatchNode only supports CCQuadParticleSystems as children");
    CCAssert( m_pChildren->containsObject(child), "Child doesn't belong to batch" );

    CCParticleSystem* pChild = (CCParticleSystem*)(child);

    if( zOrder == child->getZOrder() ) 
    {
        return;
    }

    // no reordering if only 1 child
    if( m_pChildren->count() > 1)
    {
        unsigned int newIndex = 0, oldIndex = 0;

        getCurrentIndex(&oldIndex, &newIndex, pChild, zOrder);

        if( oldIndex != newIndex )
        {

            // reorder m_pChildren->array
            pChild->retain();
            m_pChildren->removeObjectAtIndex(oldIndex);
            m_pChildren->insertObject(pChild, newIndex);
            pChild->release();

            // save old altasIndex
            unsigned int oldAtlasIndex = pChild->getAtlasIndex();

            // update atlas index
            updateAllAtlasIndexes();

            // Find new AtlasIndex
            unsigned int newAtlasIndex = 0;
            for( unsigned int i=0;i < m_pChildren->count();i++)
            {
                CCParticleSystem* pNode = (CCParticleSystem*)m_pChildren->objectAtIndex(i);
                if( pNode == pChild ) 
                {
                    newAtlasIndex = pChild->getAtlasIndex();
                    break;
                }
            }

            // reorder textureAtlas quads
            m_pTextureAtlas->moveQuadsFromIndex(oldAtlasIndex, pChild->getTotalParticles(), newAtlasIndex);

            pChild->updateWithNoTime();
        }
    }

    pChild->_setZOrder(zOrder);
}

void CCParticleBatchNode::getCurrentIndex(unsigned int* oldIndex, unsigned int* newIndex, CCNode* child, int z)
{
    bool foundCurrentIdx = false;
    bool foundNewIdx = false;

    int  minusOne = 0;
    unsigned int count = m_pChildren->count();

    for( unsigned int i=0; i < count; i++ ) 
    {
        CCNode* pNode = (CCNode *)m_pChildren->objectAtIndex(i);

        // new index
        if( pNode->getZOrder() > z &&  ! foundNewIdx ) 
        {
            *newIndex = i;
            foundNewIdx = true;

            if( foundCurrentIdx && foundNewIdx )
            {
                break;
            }
        }

        // current index
        if( child == pNode ) 
        {
            *oldIndex = i;
            foundCurrentIdx = true;

            if( ! foundNewIdx )
            {
                minusOne = -1;
            }

            if( foundCurrentIdx && foundNewIdx )
            {
                break;
            }
        }

    }

    if( ! foundNewIdx )
    {
        *newIndex = count;
    }

    *newIndex += minusOne;
}

unsigned int CCParticleBatchNode::searchNewPositionInChildrenForZ(int z)
{
    unsigned int count = m_pChildren->count();

    for( unsigned int i=0; i < count; i++ ) 
    {
        CCNode *child = (CCNode *)m_pChildren->objectAtIndex(i);
        if (child->getZOrder() > z)
        {
            return i;
        }
    }
    return count;
}

// override removeChild:
void  CCParticleBatchNode::removeChild(CCNode* child, bool cleanup)
{
    // explicit nil handling
    if (child == NULL)
    {
        return;
    }
    
    CCAssert( dynamic_cast<CCParticleSystem*>(child) != NULL, "CCParticleBatchNode only supports CCQuadParticleSystems as children");
    CCAssert(m_pChildren->containsObject(child), "CCParticleBatchNode doesn't contain the sprite. Can't remove it");

    CCParticleSystem* pChild = (CCParticleSystem*)child;
    CCNode::removeChild(pChild, cleanup);

    // remove child helper
    m_pTextureAtlas->removeQuadsAtIndex(pChild->getAtlasIndex(), pChild->getTotalParticles());

    // after memmove of data, empty the quads at the end of array
    m_pTextureAtlas->fillWithEmptyQuadsFromIndex(m_pTextureAtlas->getTotalQuads(), pChild->getTotalParticles());

    // particle could be reused for self rendering
    pChild->setBatchNode(NULL);

    updateAllAtlasIndexes();
}

void CCParticleBatchNode::removeChildAtIndex(unsigned int index, bool doCleanup)
{
    removeChild((CCParticleSystem *)m_pChildren->objectAtIndex(index),doCleanup);
}

void CCParticleBatchNode::removeAllChildrenWithCleanup(bool doCleanup)
{
    arrayMakeObjectsPerformSelectorWithObject(m_pChildren, setBatchNode, NULL, CCParticleSystem*);

    CCNode::removeAllChildrenWithCleanup(doCleanup);

    m_pTextureAtlas->removeAllQuads();
}

void CCParticleBatchNode::draw(void)
{
    CC_PROFILER_STOP("CCParticleBatchNode - draw");

    if( m_pTextureAtlas->getTotalQuads() == 0 )
    {
        return;
    }

    CC_NODE_DRAW_SETUP();

    ccGLBlendFunc( m_tBlendFunc.src, m_tBlendFunc.dst );

    m_pTextureAtlas->drawQuads();

    CC_PROFILER_STOP("CCParticleBatchNode - draw");
}



void CCParticleBatchNode::increaseAtlasCapacityTo(unsigned int quantity)
{
    CCLOG("cocos2d: CCParticleBatchNode: resizing TextureAtlas capacity from [%lu] to [%lu].",
          (long)m_pTextureAtlas->getCapacity(),
          (long)quantity);

    if( ! m_pTextureAtlas->resizeCapacity(quantity) ) {
        // serious problems
        CCLOGWARN("cocos2d: WARNING: Not enough memory to resize the atlas");
        CCAssert(false,"XXX: CCParticleBatchNode #increaseAtlasCapacity SHALL handle this assert");
    }
}

//sets a 0'd quad into the quads array
void CCParticleBatchNode::disableParticle(unsigned int particleIndex)
{
    ccV3F_C4B_T2F_Quad* quad = &((m_pTextureAtlas->getQuads())[particleIndex]);
    quad->br.vertices.x = quad->br.vertices.y = quad->tr.vertices.x = quad->tr.vertices.y = quad->tl.vertices.x = quad->tl.vertices.y = quad->bl.vertices.x = quad->bl.vertices.y = 0.0f;
}

// CCParticleBatchNode - add / remove / reorder helper methods

// add child helper
void CCParticleBatchNode::insertChild(CCParticleSystem* pSystem, unsigned int index)
{
    pSystem->setAtlasIndex(index);

    if(m_pTextureAtlas->getTotalQuads() + pSystem->getTotalParticles() > m_pTextureAtlas->getCapacity())
    {
        increaseAtlasCapacityTo(m_pTextureAtlas->getTotalQuads() + pSystem->getTotalParticles());

        // after a realloc empty quads of textureAtlas can be filled with gibberish (realloc doesn't perform calloc), insert empty quads to prevent it
        m_pTextureAtlas->fillWithEmptyQuadsFromIndex(m_pTextureAtlas->getCapacity() - pSystem->getTotalParticles(), pSystem->getTotalParticles());
    }

    // make room for quads, not necessary for last child
    if (pSystem->getAtlasIndex() + pSystem->getTotalParticles() != m_pTextureAtlas->getTotalQuads())
    {
        m_pTextureAtlas->moveQuadsFromIndex(index, index+pSystem->getTotalParticles());
    }

    // increase totalParticles here for new particles, update method of particle-system will fill the quads
    m_pTextureAtlas->increaseTotalQuadsWith(pSystem->getTotalParticles());

    updateAllAtlasIndexes();
}

//rebuild atlas indexes
void CCParticleBatchNode::updateAllAtlasIndexes()
{
    CCObject *pObj = NULL;
    unsigned int index = 0;

    CCARRAY_FOREACH(m_pChildren,pObj)
    {
        CCParticleSystem* child = (CCParticleSystem*)pObj;
        child->setAtlasIndex(index);
        index += child->getTotalParticles();
    }
}

// CCParticleBatchNode - CocosNodeTexture protocol

void CCParticleBatchNode::updateBlendFunc(void)
{
    if( ! m_pTextureAtlas->getTexture()->hasPremultipliedAlpha()) {
        m_tBlendFunc.src = GL_SRC_ALPHA;
        m_tBlendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
    }
}

void CCParticleBatchNode::setTexture(CCTexture2D* texture)
{
    m_pTextureAtlas->setTexture(texture);

    // If the new texture has No premultiplied alpha, AND the blendFunc hasn't been changed, then update it
    if( texture && ! texture->hasPremultipliedAlpha() && ( m_tBlendFunc.src == CC_BLEND_SRC && m_tBlendFunc.dst == CC_BLEND_DST ) )
    {
            m_tBlendFunc.src = GL_SRC_ALPHA;
            m_tBlendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
    }
}

CCTexture2D* CCParticleBatchNode::getTexture(void)
{
    return m_pTextureAtlas->getTexture();
}

void CCParticleBatchNode::setBlendFunc(ccBlendFunc blendFunc)
{
    m_tBlendFunc = blendFunc;
}
// returns the blending function used for the texture
ccBlendFunc CCParticleBatchNode::getBlendFunc(void)
{
    return m_tBlendFunc;
}

NS_CC_END
