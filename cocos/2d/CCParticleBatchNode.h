/*@~english
 * Copyright (C) 2009 Matt Oswald
 * Copyright (c) 2009-2010 Ricardo Quesada
 * Copyright (c) 2010-2012 cocos2d-x.org
 * Copyright (c) 2011      Zynga Inc.
 * Copyright (c) 2011      Marco Tillemans
 * Copyright (c) 2013-2015 Chukong Technologies Inc.
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
#include "base/CCProtocols.h"
#include "renderer/CCBatchCommand.h"

NS_CC_BEGIN

class Texture2D;
class TextureAtlas;
class ParticleSystem;

/**
 * @addtogroup _2d
 * @{
 */

#define kParticleDefaultCapacity 500

/** @class ParticleBatchNode
 * @brief @~english ParticleBatchNode is like a batch node: if it contains children, it will draw them in 1 single OpenGL call
 * (often known as "batch draw").
 *
 * A ParticleBatchNode can reference one and only one texture (one image file, one texture atlas).
 * Only the ParticleSystems that are contained in that texture can be added to the ParticleBatchNode.
 * All ParticleSystems added to a ParticleBatchNode are drawn in one OpenGL ES draw call.
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
 *
 * @~chinese ParticleBatchNode和批处理节点一样，如果它包含有子节点，它会在一次OpenGL call调用里绘制所有子节点。
 * (通常被称为“批处理”)。
 * 
 * 一个ParticleBatchNode只可以引用一个纹理(一个图像文件,或一个纹理贴图集)。
 * ParticleSystems对象引用的纹理和ParticleBatchNode是同一个的时候才可以添加到ParticleBatchNode。
 * 所有添加到ParticleBatchNode的ParticleSystems都会在同一个OpenGL ES调用里被绘制。
 * 如果ParticleSystems没有被添加ParticleBatchNode，那么每一个ParticleSystems都需要调用一次OpenGL ES绘图,这是低效率的。
 * 
 * 
 * 限制:
 * - 目前只支持ParticleSystemQuad
 * - 所有的系统都需要用相同的参数,包含混合模式、走样、纹理
 * 
 * 最有效的用法：
 * - 使用纹理及一个足够容纳所有粒子系统的容量初始化一个ParticleBatchNode。
 * - 初始化粒子系统，然后将它们作为孩子节点添加到ParticleBatchNode。
 * @since v1.1
 */
class CC_DLL ParticleBatchNode : public Node, public TextureProtocol
{
public:
    /** @~english Create the particle system with Texture2D, a capacity of particles, which particle system to use.
     * @~chinese 使用给定的纹理及粒子系统容量创建并初始化一个粒子批处理节点。
     * 
     * @param tex @~english A given texture.
     * @~chinese 一个给定的纹理。
     * @param capacity @~english A capacity of particles.
     * @~chinese 粒子系统容量。
     *
     * @return @~english A initialized ParticleBatchNode object which is marked as "autorelease".
     * @~chinese 一个初始化的ParticleBatchNode对象，该对象会自动被标记为“autorelease”(自动释放).
     * @js NA
     */
    static ParticleBatchNode* createWithTexture(Texture2D *tex, int capacity = kParticleDefaultCapacity);

    /** @~english Create the particle system with the name of a file on disk (for a list of supported formats look at the Texture2D class), a capacity of particles.
     * @~chinese 使用给定的图片文件及粒子系统容量创建并一个粒子批处理节点。
     * 
     * @param fileImage @~english A given file path.
     * @~chinese 一个给定的图片文件的路径。
     * @param capacity @~english A capacity of particles.
     * @~chinese 粒子系统容量。
     *
     * @return @~english A initialized ParticleBatchNode object which is marked as "autorelease".
     * @~chinese 一个初始化的ParticleBatchNode对象，该对象会自动被标记为“autorelease”(自动释放).
     */
    static ParticleBatchNode* create(const std::string& fileImage, int capacity = kParticleDefaultCapacity);

    /** @~english Inserts a child into the ParticleBatchNode.
     * @~chinese 插入一个ParticleSystem子节点到ParticleBatchNode。
     * 
     * @param system @~english A given particle system.
     * @~chinese 一个给定的粒子系统节点。
     * @param index @~english The insert index.
     * @~chinese 索引。
     */
    void insertChild(ParticleSystem* system, int index);

    /** @~english Remove a child of the ParticleBatchNode.
     * @~chinese 按给定的索引删除一个ParticleBatchNode的子节点。
     * 
     * @param index @~english The index of the child.
     * @~chinese 子节点的索引。
     * @param doCleanup @~english True if all actions and callbacks on this node should be removed, false otherwise.
     * @~chinese true 这个节点的所有动作和回调将被删除； false 不删除节点的动作及回调。
     */
    void removeChildAtIndex(int index, bool doCleanup);

    void removeAllChildrenWithCleanup(bool doCleanup) override;

    /** @~english Disables a particle by inserting a 0'd quad into the texture atlas.
     * @~chinese 禁用指定的一个粒子系统。
     * 
     * @param particleIndex @~english The index of the particle.
     * @~chinese 粒子系统的索引。
     */
    void disableParticle(int particleIndex);

    /** @~english Gets the texture atlas used for drawing the quads.
     * @~chinese 获取绘制顶点的纹理贴图集。
     * 
     * @return @~english The texture atlas used for drawing the quads.
     * @~chinese 纹理贴图集。
     */
    inline TextureAtlas* getTextureAtlas() const { return _textureAtlas; };
    
    /** @~english Sets the texture atlas used for drawing the quads.
     * @~chinese 设置绘制顶点的纹理贴图集。
     * 
     * @param atlas @~english The texture atlas used for drawing the quads.
     * @~chinese 纹理贴图集。
     */
    inline void setTextureAtlas(TextureAtlas* atlas) { _textureAtlas = atlas; };
    
    // Overrides
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;

    using Node::addChild;
    virtual void addChild(Node * child, int zOrder, int tag) override;
    virtual void addChild(Node * child, int zOrder, const std::string &name) override;
    virtual void removeChild(Node* child, bool cleanup) override;
    virtual void reorderChild(Node * child, int zOrder) override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    virtual Texture2D* getTexture(void) const override;
    virtual void setTexture(Texture2D *texture) override;
    
    virtual void setBlendFunc(const BlendFunc &blendFunc) override;
    virtual const BlendFunc& getBlendFunc(void) const override;
    
CC_CONSTRUCTOR_ACCESS:
    ParticleBatchNode();
    virtual ~ParticleBatchNode();
    
    bool initWithTexture(Texture2D *tex, int capacity);
    
    bool initWithFile(const std::string& fileImage, int capacity);
    
private:
    void updateAllAtlasIndexes();
    void increaseAtlasCapacityTo(ssize_t quantity);
    int searchNewPositionInChildrenForZ(int z);
    void getCurrentIndex(int* oldIndex, int* newIndex, Node* child, int z);
    int addChildHelper(ParticleSystem* child, int z, int aTag, const std::string &name, bool setTag);
    void addChildByTagOrName(ParticleSystem* child, int z, int tag, const std::string &name, bool setTag);
    void updateBlendFunc(void);
    
    TextureAtlas* _textureAtlas;
    BlendFunc _blendFunc;
    BatchCommand _batchCommand;
};

// end of _2d group
/// @}

NS_CC_END

#endif /* __CCPARTICLEBATCHNODE_H__ */

