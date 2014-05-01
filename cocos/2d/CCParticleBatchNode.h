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
#ifndef __CCPARTICLEBATCHNODE_H__
#define __CCPARTICLEBATCHNODE_H__

#include "2d/CCNode.h"
#include "2d/CCProtocols.h"
#include "renderer/CCBatchCommand.h"

NS_CC_BEGIN

class Texture2D;
class TextureAtlas;
class ParticleSystem;

/**
 * @addtogroup particle_nodes
 * @{
 */

#define kParticleDefaultCapacity 500

/** ParticleBatchNode is like a batch node: if it contains children, it will draw them in 1 single OpenGL call
 * (often known as "batch draw").
 *
 * A ParticleBatchNode can reference one and only one texture (one image file, one texture atlas).
 * Only the ParticleSystems that are contained in that texture can be added to the SpriteBatchNode.
 * All ParticleSystems added to a SpriteBatchNode are drawn in one OpenGL ES draw call.
 * If the ParticleSystems are not added to a ParticleBatchNode then an OpenGL ES draw call will be needed for each one, which is less efficient.
 *
 *
 * Limitations:
 * - At the moment only ParticleSystemQuad is supported
 * - All systems need to be drawn with the same parameters, blend function, aliasing, texture
 *
 * Most efficient usage
 * - Initialize the ParticleBatchNode with the texture and enough capacity for all the particle systems
 * - Initialize all particle systems and add them as child to the batch node
 * @since v1.1
 */

class CC_DLL ParticleBatchNode : public Node, public TextureProtocol
{
public:
    /** initializes the particle system with Texture2D, a capacity of particles, which particle system to use */
    static ParticleBatchNode* createWithTexture(Texture2D *tex, int capacity = kParticleDefaultCapacity);

    /** initializes the particle system with the name of a file on disk (for a list of supported formats look at the Texture2D class), a capacity of particles */
    static ParticleBatchNode* create(const std::string& fileImage, int capacity = kParticleDefaultCapacity);

    /** Inserts a child into the ParticleBatchNode */
    void insertChild(ParticleSystem* system, int index);

    void removeChildAtIndex(int index, bool doCleanup);
    void removeAllChildrenWithCleanup(bool doCleanup);

    /** disables a particle by inserting a 0'd quad into the texture atlas */
    void disableParticle(int particleIndex);

    /** Gets the texture atlas used for drawing the quads */
    inline TextureAtlas* getTextureAtlas() const { return _textureAtlas; };
    
    /** Sets the texture atlas used for drawing the quads */
    inline void setTextureAtlas(TextureAtlas* atlas) { _textureAtlas = atlas; };
    
    // Overrides
    virtual void visit(Renderer *renderer, const Matrix &parentTransform, bool parentTransformUpdated) override;

    using Node::addChild;
    virtual void addChild(Node * child, int zOrder, int tag) override;
    virtual void removeChild(Node* child, bool cleanup) override;
    virtual void reorderChild(Node * child, int zOrder) override;
    virtual void draw(Renderer *renderer, const Matrix &transform, bool transformUpdated) override;
    virtual Texture2D* getTexture(void) const override;
    virtual void setTexture(Texture2D *texture) override;
    /**
    * @code
    * When this function bound into js or lua,the parameter will be changed
    * In js: var setBlendFunc(var src, var dst)
    * @endcode
    * @lua NA
    */
    virtual void setBlendFunc(const BlendFunc &blendFunc) override;
    /**
    * @js NA
    * @lua NA
    */
    virtual const BlendFunc& getBlendFunc(void) const override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    ParticleBatchNode();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleBatchNode();
    
    /** initializes the particle system with Texture2D, a capacity of particles */
    bool initWithTexture(Texture2D *tex, int capacity);
    
    /** initializes the particle system with the name of a file on disk (for a list of supported formats look at the Texture2D class), a capacity of particles */
    bool initWithFile(const std::string& fileImage, int capacity);
    
private:
    void updateAllAtlasIndexes();
    void increaseAtlasCapacityTo(ssize_t quantity);
    int searchNewPositionInChildrenForZ(int z);
    void getCurrentIndex(int* oldIndex, int* newIndex, Node* child, int z);
    int addChildHelper(ParticleSystem* child, int z, int aTag);
    void updateBlendFunc(void);
    /** the texture atlas used for drawing the quads */
    TextureAtlas* _textureAtlas;

    /** the blend function used for drawing the quads */
    BlendFunc _blendFunc;
    // quad command
    BatchCommand _batchCommand;
};

// end of particle_nodes group
/// @}

NS_CC_END

#endif /* __CCPARTICLEBATCHNODE_H__ */

