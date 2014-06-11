/*
 * Copyright (C) 2009 Matt Oswald
 * Copyright (c) 2009-2010 Ricardo Quesada
 * Copyright (c) 2010-2012 cocos2d-x.org
 * Copyright (c) 2011      Zynga Inc.
 * Copyright (c) 2011      Marco Tillemans
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
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

#include "2d/CCParticleBatchNode.h"

#include "renderer/CCTextureAtlas.h"
#include "2d/CCGrid.h"
#include "2d/CCParticleSystem.h"
#include "platform/CCFileUtils.h"
#include "base/CCProfiling.h"
#include "base/ccConfig.h"
#include "base/ccMacros.h"
#include "base/base64.h"
#include "base/ZipUtils.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCGLProgram.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCQuadCommand.h"
#include "renderer/CCRenderer.h"


NS_CC_BEGIN

ParticleBatchNode::ParticleBatchNode()
: _textureAtlas(nullptr)
{

}

ParticleBatchNode::~ParticleBatchNode()
{
    CC_SAFE_RELEASE(_textureAtlas);
}
/*
 * creation with Texture2D
 */

ParticleBatchNode* ParticleBatchNode::createWithTexture(Texture2D *tex, int capacity/* = kParticleDefaultCapacity*/)
{
    ParticleBatchNode * p = new ParticleBatchNode();
    if( p && p->initWithTexture(tex, capacity))
    {
        p->autorelease();
        return p;
    }
    CC_SAFE_DELETE(p);
    return nullptr;
}

/*
 * creation with File Image
 */

ParticleBatchNode* ParticleBatchNode::create(const std::string& imageFile, int capacity/* = kParticleDefaultCapacity*/)
{
    ParticleBatchNode * p = new ParticleBatchNode();
    if( p && p->initWithFile(imageFile, capacity))
    {
        p->autorelease();
        return p;
    }
    CC_SAFE_DELETE(p);
    return nullptr;
}

/*
 * init with Texture2D
 */
bool ParticleBatchNode::initWithTexture(Texture2D *tex, int capacity)
{
    _textureAtlas = new TextureAtlas();
    _textureAtlas->initWithTexture(tex, capacity);

    _children.reserve(capacity);
    
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;

    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));

    return true;
}

/*
 * init with FileImage
 */
bool ParticleBatchNode::initWithFile(const std::string& fileImage, int capacity)
{
    Texture2D *tex = Director::getInstance()->getTextureCache()->addImage(fileImage);
    return initWithTexture(tex, capacity);
}

// ParticleBatchNode - composition

// override visit.
// Don't call visit on it's children
void ParticleBatchNode::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
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

    uint32_t flags = processParentFlags(parentTransform, parentFlags);

    // IMPORTANT:
    // To ease the migration to v3.0, we still support the Mat4 stack,
    // but it is deprecated and your code should not rely on it
    Director* director = Director::getInstance();
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);

    draw(renderer, _modelViewTransform, flags);

    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

// override addChild:
void ParticleBatchNode::addChild(Node * aChild, int zOrder, int tag)
{
    CCASSERT( aChild != nullptr, "Argument must be non-nullptr");
    CCASSERT( dynamic_cast<ParticleSystem*>(aChild) != nullptr, "CCParticleBatchNode only supports QuadParticleSystems as children");
    ParticleSystem* child = static_cast<ParticleSystem*>(aChild);
    CCASSERT( child->getTexture()->getName() == _textureAtlas->getTexture()->getName(), "CCParticleSystem is not using the same texture id");
    // If this is the 1st children, then copy blending function
    if (_children.empty())
    {
        setBlendFunc(child->getBlendFunc());
    }

    CCASSERT( _blendFunc.src  == child->getBlendFunc().src && _blendFunc.dst  == child->getBlendFunc().dst, "Can't add a ParticleSystem that uses a different blending function");

    //no lazy sorting, so don't call super addChild, call helper instead
    auto pos = addChildHelper(child,zOrder,tag);

    //get new atlasIndex
    int atlasIndex = 0;

    if (pos != 0)
    {
        ParticleSystem* p = static_cast<ParticleSystem*>(_children.at(pos-1));
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
int ParticleBatchNode::addChildHelper(ParticleSystem* child, int z, int aTag)
{
    CCASSERT( child != nullptr, "Argument must be non-nil");
    CCASSERT( child->getParent() == nullptr, "child already added. It can't be added again");

    _children.reserve(4);

    //don't use a lazy insert
    auto pos = searchNewPositionInChildrenForZ(z);

    _children.insert(pos, child);

    child->setTag(aTag);
    child->_setLocalZOrder(z);

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
    CCASSERT( aChild != nullptr, "Child must be non-nullptr");
    CCASSERT( dynamic_cast<ParticleSystem*>(aChild) != nullptr, "CCParticleBatchNode only supports QuadParticleSystems as children");
    CCASSERT( _children.contains(aChild), "Child doesn't belong to batch" );

    ParticleSystem* child = static_cast<ParticleSystem*>(aChild);

    if( zOrder == child->getLocalZOrder() )
    {
        return;
    }

    // no reordering if only 1 child
    if (!_children.empty())
    {
        int newIndex = 0, oldIndex = 0;

        getCurrentIndex(&oldIndex, &newIndex, child, zOrder);

        if( oldIndex != newIndex )
        {

            // reorder _children->array
            child->retain();
            _children.erase(oldIndex);
            _children.insert(newIndex, child);
            child->release();

            // save old altasIndex
            int oldAtlasIndex = child->getAtlasIndex();

            // update atlas index
            updateAllAtlasIndexes();

            // Find new AtlasIndex
            int newAtlasIndex = 0;
            for( int i=0;i < _children.size();i++)
            {
                ParticleSystem* node = static_cast<ParticleSystem*>(_children.at(i));
                if( node == child )
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

    child->_setLocalZOrder(zOrder);
}

void ParticleBatchNode::getCurrentIndex(int* oldIndex, int* newIndex, Node* child, int z)
{
    bool foundCurrentIdx = false;
    bool foundNewIdx = false;

    int  minusOne = 0;
    auto count = _children.size();

    for( int i=0; i < count; i++ )
    {
        Node* pNode = _children.at(i);

        // new index
        if( pNode->getLocalZOrder() > z &&  ! foundNewIdx )
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
        *newIndex = static_cast<int>(count);
    }

    *newIndex += minusOne;
}

int ParticleBatchNode::searchNewPositionInChildrenForZ(int z)
{
    auto count = _children.size();

    for( int i=0; i < count; i++ )
    {
        Node *child = _children.at(i);
        if (child->getLocalZOrder() > z)
        {
            return i;
        }
    }
    return static_cast<int>(count);
}

// override removeChild:
void  ParticleBatchNode::removeChild(Node* aChild, bool cleanup)
{
    // explicit nil handling
    if (aChild == nullptr)
        return;

    CCASSERT( dynamic_cast<ParticleSystem*>(aChild) != nullptr, "CCParticleBatchNode only supports QuadParticleSystems as children");
    CCASSERT(_children.contains(aChild), "CCParticleBatchNode doesn't contain the sprite. Can't remove it");

    ParticleSystem* child = static_cast<ParticleSystem*>(aChild);

    // remove child helper
    _textureAtlas->removeQuadsAtIndex(child->getAtlasIndex(), child->getTotalParticles());

    // after memmove of data, empty the quads at the end of array
    _textureAtlas->fillWithEmptyQuadsFromIndex(_textureAtlas->getTotalQuads(), child->getTotalParticles());

    // particle could be reused for self rendering
    child->setBatchNode(nullptr);
    Node::removeChild(child, cleanup);

    updateAllAtlasIndexes();
}

void ParticleBatchNode::removeChildAtIndex(int index, bool doCleanup)
{
    removeChild(_children.at(index), doCleanup);
}

void ParticleBatchNode::removeAllChildrenWithCleanup(bool doCleanup)
{
    for(const auto &child : _children)
        static_cast<ParticleSystem*>(child)->setBatchNode(nullptr);

    Node::removeAllChildrenWithCleanup(doCleanup);

    _textureAtlas->removeAllQuads();
}

void ParticleBatchNode::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    CC_PROFILER_START("CCParticleBatchNode - draw");

    if( _textureAtlas->getTotalQuads() == 0 )
    {
        return;
    }

    _batchCommand.init(
                       _globalZOrder,
                       getGLProgram(),
                       _blendFunc,
                       _textureAtlas,
                       _modelViewTransform);
    renderer->addCommand(&_batchCommand);
    CC_PROFILER_STOP("CCParticleBatchNode - draw");
}



void ParticleBatchNode::increaseAtlasCapacityTo(ssize_t quantity)
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
void ParticleBatchNode::disableParticle(int particleIndex)
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
    int index = 0;
    
    for(const auto &child : _children) {
        ParticleSystem* partiSys = static_cast<ParticleSystem*>(child);
        partiSys->setAtlasIndex(index);
        index += partiSys->getTotalParticles();
    }
}

// ParticleBatchNode - CocosNodeTexture protocol

void ParticleBatchNode::updateBlendFunc()
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

Texture2D* ParticleBatchNode::getTexture() const
{
    return _textureAtlas->getTexture();
}

void ParticleBatchNode::setBlendFunc(const BlendFunc &blendFunc)
{
    _blendFunc = blendFunc;
}
// returns the blending function used for the texture
const BlendFunc& ParticleBatchNode::getBlendFunc() const
{
    return _blendFunc;
}

NS_CC_END
