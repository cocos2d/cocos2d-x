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
#include "CCParticleSystem.h"
#include "shaders/CCShaderCache.h"
#include "shaders/CCGLProgram.h"
#include "shaders/ccGLStateCache.h"
#include "support/base64.h"
#include "support/zip_support/ZipUtils.h"
#include "platform/CCFileUtils.h"
#include "kazmath/GL/matrix.h"
#include "support/CCProfiling.h"

NS_CC_BEGIN

ParticleBatchNode::ParticleBatchNode()
: _textureAtlas(NULL)
{

}

ParticleBatchNode::~ParticleBatchNode()
{
    CC_SAFE_RELEASE(_textureAtlas);
}
/*
 * creation with Texture2D
 */

ParticleBatchNode* ParticleBatchNode::createWithTexture(Texture2D *tex, unsigned int capacity/* = kParticleDefaultCapacity*/)
{
    ParticleBatchNode * p = new ParticleBatchNode();
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

ParticleBatchNode* ParticleBatchNode::create(const char* imageFile, unsigned int capacity/* = kParticleDefaultCapacity*/)
{
    ParticleBatchNode * p = new ParticleBatchNode();
    if( p && p->initWithFile(imageFile, capacity))
    {
        p->autorelease();
        return p;
    }
    CC_SAFE_DELETE(p);
    return NULL;
}

/*
 * init with Texture2D
 */
bool ParticleBatchNode::initWithTexture(Texture2D *tex, unsigned int capacity)
{
    _textureAtlas = new TextureAtlas();
    _textureAtlas->initWithTexture(tex, capacity);

    // no lazy alloc in this node
    _children = new Array();
    _children->initWithCapacity(capacity);

    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;

    setShaderProgram(ShaderCache::getInstance()->programForKey(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
    
    return true;
}

/*
 * init with FileImage
 */
bool ParticleBatchNode::initWithFile(const char* fileImage, unsigned int capacity)
{
    Texture2D *tex = TextureCache::getInstance()->addImage(fileImage);
    return initWithTexture(tex, capacity);
}

// ParticleBatchNode - composition

// override visit.
// Don't call visit on it's children
void ParticleBatchNode::visit()
{
    // CAREFUL:
    // This visit is almost identical to Node#visit
    // with the exception that it doesn't call visit on it's children
    //
    // The alternative is to have a void Sprite#visit, but
    // although this is less maintainable, is faster
    //
    if (!_visible)
    {
        return;
    }

    kmGLPushMatrix();

    if ( _grid && _grid->isActive())
    {
        _grid->beforeDraw();
        transformAncestors();
    }

    transform();

    draw();

    if ( _grid && _grid->isActive())
    {
        _grid->afterDraw(this);
    }

    kmGLPopMatrix();
}

// override addChild:
void ParticleBatchNode::addChild(Node * child)
{
    Node::addChild(child);
}

void ParticleBatchNode::addChild(Node * child, int zOrder)
{
    Node::addChild(child, zOrder);
}

void ParticleBatchNode::addChild(Node * aChild, int zOrder, int tag)
{
    CCASSERT( aChild != NULL, "Argument must be non-NULL");
    CCASSERT( dynamic_cast<ParticleSystem*>(aChild) != NULL, "CCParticleBatchNode only supports QuadParticleSystems as children");
    ParticleSystem* child = static_cast<ParticleSystem*>(aChild);
    CCASSERT( child->getTexture()->getName() == _textureAtlas->getTexture()->getName(), "CCParticleSystem is not using the same texture id");
    // If this is the 1st children, then copy blending function
    if( _children->count() == 0 ) 
    {
        setBlendFunc(child->getBlendFunc());
    }

    CCASSERT( _blendFunc.src  == child->getBlendFunc().src && _blendFunc.dst  == child->getBlendFunc().dst, "Can't add a PaticleSystem that uses a different blending function");

    //no lazy sorting, so don't call super addChild, call helper instead
    unsigned int pos = addChildHelper(child,zOrder,tag);

    //get new atlasIndex
    int atlasIndex = 0;

    if (pos != 0) 
    {
        ParticleSystem* p = (ParticleSystem*)_children->objectAtIndex(pos-1);
        atlasIndex = p->getAtlasIndex() + p->getTotalParticles();

    }
    else
    {
        atlasIndex = 0;
    }

    insertChild(child, atlasIndex);

    // update quad info
    child->setBatchNode(this);
}

// don't use lazy sorting, reordering the particle systems quads afterwards would be too complex
// XXX research whether lazy sorting + freeing current quads and calloc a new block with size of capacity would be faster
// XXX or possibly using vertexZ for reordering, that would be fastest
// this helper is almost equivalent to Node's addChild, but doesn't make use of the lazy sorting
unsigned int ParticleBatchNode::addChildHelper(ParticleSystem* child, int z, int aTag)
{
    CCASSERT( child != NULL, "Argument must be non-nil");
    CCASSERT( child->getParent() == NULL, "child already added. It can't be added again");

    if( ! _children ) 
    {
        _children = new Array();
        _children->initWithCapacity(4);
    }

    //don't use a lazy insert
    unsigned int pos = searchNewPositionInChildrenForZ(z);

    _children->insertObject(child, pos);

    child->setTag(aTag);
    child->_setZOrder(z);

    child->setParent(this);

    if( _running ) 
    {
        child->onEnter();
        child->onEnterTransitionDidFinish();
    }
    return pos;
}

// Reorder will be done in this function, no "lazy" reorder to particles
void ParticleBatchNode::reorderChild(Node * aChild, int zOrder)
{
    CCASSERT( aChild != NULL, "Child must be non-NULL");
    CCASSERT( dynamic_cast<ParticleSystem*>(aChild) != NULL, "CCParticleBatchNode only supports QuadParticleSystems as children");
    CCASSERT( _children->containsObject(aChild), "Child doesn't belong to batch" );

    ParticleSystem* child = static_cast<ParticleSystem*>(aChild);

    if( zOrder == child->getZOrder() ) 
    {
        return;
    }

    // no reordering if only 1 child
    if( _children->count() > 1)
    {
        unsigned int newIndex = 0, oldIndex = 0;

        getCurrentIndex(&oldIndex, &newIndex, child, zOrder);

        if( oldIndex != newIndex )
        {

            // reorder _children->array
            child->retain();
            _children->removeObjectAtIndex(oldIndex);
            _children->insertObject(child, newIndex);
            child->release();

            // save old altasIndex
            int oldAtlasIndex = child->getAtlasIndex();

            // update atlas index
            updateAllAtlasIndexes();

            // Find new AtlasIndex
            int newAtlasIndex = 0;
            for( unsigned int i=0;i < _children->count();i++)
            {
                ParticleSystem* pNode = (ParticleSystem*)_children->objectAtIndex(i);
                if( pNode == child ) 
                {
                    newAtlasIndex = child->getAtlasIndex();
                    break;
                }
            }

            // reorder textureAtlas quads
            _textureAtlas->moveQuadsFromIndex(oldAtlasIndex, child->getTotalParticles(), newAtlasIndex);

            child->updateWithNoTime();
        }
    }

    child->_setZOrder(zOrder);
}

void ParticleBatchNode::getCurrentIndex(unsigned int* oldIndex, unsigned int* newIndex, Node* child, int z)
{
    bool foundCurrentIdx = false;
    bool foundNewIdx = false;

    int  minusOne = 0;
    unsigned int count = _children->count();

    for( unsigned int i=0; i < count; i++ ) 
    {
        Node* pNode = (Node *)_children->objectAtIndex(i);

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

unsigned int ParticleBatchNode::searchNewPositionInChildrenForZ(int z)
{
    unsigned int count = _children->count();

    for( unsigned int i=0; i < count; i++ ) 
    {
        Node *child = (Node *)_children->objectAtIndex(i);
        if (child->getZOrder() > z)
        {
            return i;
        }
    }
    return count;
}

// override removeChild:
void  ParticleBatchNode::removeChild(Node* aChild, bool cleanup)
{
    // explicit nil handling
    if (aChild == NULL)
        return;
    
    CCASSERT( dynamic_cast<ParticleSystem*>(aChild) != NULL, "CCParticleBatchNode only supports QuadParticleSystems as children");
    CCASSERT(_children->containsObject(aChild), "CCParticleBatchNode doesn't contain the sprite. Can't remove it");

    ParticleSystem* child = static_cast<ParticleSystem*>(aChild);
    Node::removeChild(child, cleanup);

    // remove child helper
    _textureAtlas->removeQuadsAtIndex(child->getAtlasIndex(), child->getTotalParticles());

    // after memmove of data, empty the quads at the end of array
    _textureAtlas->fillWithEmptyQuadsFromIndex(_textureAtlas->getTotalQuads(), child->getTotalParticles());

    // particle could be reused for self rendering
    child->setBatchNode(NULL);

    updateAllAtlasIndexes();
}

void ParticleBatchNode::removeChildAtIndex(unsigned int index, bool doCleanup)
{
    removeChild((ParticleSystem *)_children->objectAtIndex(index),doCleanup);
}

void ParticleBatchNode::removeAllChildrenWithCleanup(bool doCleanup)
{
    arrayMakeObjectsPerformSelectorWithObject(_children, setBatchNode, NULL, ParticleSystem*);

    Node::removeAllChildrenWithCleanup(doCleanup);

    _textureAtlas->removeAllQuads();
}

void ParticleBatchNode::draw(void)
{
    CC_PROFILER_START("CCParticleBatchNode - draw");

    if( _textureAtlas->getTotalQuads() == 0 )
    {
        return;
    }

    CC_NODE_DRAW_SETUP();

    GL::blendFunc( _blendFunc.src, _blendFunc.dst );

    _textureAtlas->drawQuads();

    CC_PROFILER_STOP("CCParticleBatchNode - draw");
}



void ParticleBatchNode::increaseAtlasCapacityTo(unsigned int quantity)
{
    CCLOG("cocos2d: ParticleBatchNode: resizing TextureAtlas capacity from [%lu] to [%lu].",
          (long)_textureAtlas->getCapacity(),
          (long)quantity);

    if( ! _textureAtlas->resizeCapacity(quantity) ) {
        // serious problems
        CCLOGWARN("cocos2d: WARNING: Not enough memory to resize the atlas");
        CCASSERT(false,"XXX: ParticleBatchNode #increaseAtlasCapacity SHALL handle this assert");
    }
}

//sets a 0'd quad into the quads array
void ParticleBatchNode::disableParticle(unsigned int particleIndex)
{
    V3F_C4B_T2F_Quad* quad = &((_textureAtlas->getQuads())[particleIndex]);
    quad->br.vertices.x = quad->br.vertices.y = quad->tr.vertices.x = quad->tr.vertices.y = quad->tl.vertices.x = quad->tl.vertices.y = quad->bl.vertices.x = quad->bl.vertices.y = 0.0f;
}

// ParticleBatchNode - add / remove / reorder helper methods

// add child helper
void ParticleBatchNode::insertChild(ParticleSystem* system, int index)
{
    system->setAtlasIndex(index);

    if(_textureAtlas->getTotalQuads() + system->getTotalParticles() > _textureAtlas->getCapacity())
    {
        increaseAtlasCapacityTo(_textureAtlas->getTotalQuads() + system->getTotalParticles());

        // after a realloc empty quads of textureAtlas can be filled with gibberish (realloc doesn't perform calloc), insert empty quads to prevent it
        _textureAtlas->fillWithEmptyQuadsFromIndex(_textureAtlas->getCapacity() - system->getTotalParticles(), system->getTotalParticles());
    }

    // make room for quads, not necessary for last child
    if (system->getAtlasIndex() + system->getTotalParticles() != _textureAtlas->getTotalQuads())
    {
        _textureAtlas->moveQuadsFromIndex(index, index+system->getTotalParticles());
    }

    // increase totalParticles here for new particles, update method of particle-system will fill the quads
    _textureAtlas->increaseTotalQuadsWith(system->getTotalParticles());

    updateAllAtlasIndexes();
}

//rebuild atlas indexes
void ParticleBatchNode::updateAllAtlasIndexes()
{
    Object *pObj = NULL;
    unsigned int index = 0;

    CCARRAY_FOREACH(_children,pObj)
    {
        ParticleSystem* child = static_cast<ParticleSystem*>(pObj);
        child->setAtlasIndex(index);
        index += child->getTotalParticles();
    }
}

// ParticleBatchNode - CocosNodeTexture protocol

void ParticleBatchNode::updateBlendFunc(void)
{
    if( ! _textureAtlas->getTexture()->hasPremultipliedAlpha())
        _blendFunc = BlendFunc::ALPHA_NON_PREMULTIPLIED;
}

void ParticleBatchNode::setTexture(Texture2D* texture)
{
    _textureAtlas->setTexture(texture);

    // If the new texture has No premultiplied alpha, AND the blendFunc hasn't been changed, then update it
    if( texture && ! texture->hasPremultipliedAlpha() && ( _blendFunc.src == CC_BLEND_SRC && _blendFunc.dst == CC_BLEND_DST ) )
    {
        _blendFunc = BlendFunc::ALPHA_NON_PREMULTIPLIED;
    }
}

Texture2D* ParticleBatchNode::getTexture(void) const
{
    return _textureAtlas->getTexture();
}

void ParticleBatchNode::setBlendFunc(const BlendFunc &blendFunc)
{
    _blendFunc = blendFunc;
}
// returns the blending function used for the texture
const BlendFunc& ParticleBatchNode::getBlendFunc(void) const
{
    return _blendFunc;
}

NS_CC_END
