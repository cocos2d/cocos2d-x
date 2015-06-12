/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Leonardo Kasperavičius
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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
#ifndef __CC_PARTICLE_SYSTEM_QUAD_H__
#define __CC_PARTICLE_SYSTEM_QUAD_H__

#include "2d/CCParticleSystem.h"
#include "renderer/CCQuadCommand.h"

NS_CC_BEGIN

class SpriteFrame;
class EventCustom;

/**
 * @addtogroup _2d
 * @{
 */

/** @class ParticleSystemQuad
 * @brief @~english ParticleSystemQuad is a subclass of ParticleSystem.
 *
 * It includes all the features of ParticleSystem.
 * 
 * Special features and Limitations:    
 * - Particle size can be any float number.
 * - The system can be scaled.
 * - The particles can be rotated.
 * - It supports subrects.
 * - It supports batched rendering since 1.1.

 * @~chinese ParticleSystemQuad是ParticleSystem的一个子类。
 * 它包含ParticleSystem的所有特性。
 * 
 * 特殊特性和限制:
 * - 粒子大小可以是任意float数值。
 * - 粒子系统可以缩放。
 * - 粒子可以旋转。
 * - 它支持subrects。
 * - 从1.1版本起支持批处理渲染。
 * @since v0.8
 * @js NA
 */
class CC_DLL ParticleSystemQuad : public ParticleSystem
{
public:

    /** @~english Creates a particle emitter.
     * @~chinese 创建一个粒子发射器。
     * 
     * @return @~english An autoreleased ParticleSystemQuad object.
     * @~chinese 一个被标记为自动释放的ParticleSystemQuad对象。
     */
    static ParticleSystemQuad * create();

    /** @~english Creates a particle emitter with a number of particles.
     * @~chinese 基于给定的粒子数创建粒子发射器。
     * 
     * @param numberOfParticles @~english A given number of particles.
     * @~chinese 给定的粒子数。
     *
     * @return @~english An autoreleased ParticleSystemQuad object.
     * @~chinese 一个被标记为自动释放的ParticleSystemQuad对象。
     */
    static ParticleSystemQuad * createWithTotalParticles(int numberOfParticles);

    /** @~english Creates an particle emitter from a plist file.
     * This plist files can be created manually or with Particle Designer.
     *
     * @~chinese 基于给定的plist文件创建一个粒子发射器。
     * 这个plist文件可以是手动创建，或者通过编辑器Particle Designer创建。
     * 
     * @param filename @~english Particle plist file name.
     * @~chinese plist文件名称。
     *
     * @return @~english An autoreleased ParticleSystemQuad object.
     * @~chinese 一个被标记为自动释放的ParticleSystemQuad对象。
     */
    static ParticleSystemQuad * create(const std::string& filename);

    /** @~english Creates a particle emitter with a dictionary.
     * 
     * @~chinese 基于给定的数值映射创建一个粒子发射器。
     * 
     * @param dictionary @~english Particle dictionary.
     * @~chinese 数值映射。
     *
     * @return @~english An autoreleased ParticleSystemQuad object.
     * @~chinese 一个被标记为自动释放的ParticleSystemQuad对象。
     */
    static ParticleSystemQuad * create(ValueMap &dictionary);

    /** @~english Sets a new SpriteFrame as particle.
     * @~chinese 设置一个新的SpriteFrame给粒子使用。
     *
     * @warning: @~english this method is experimental. Use setTextureWithRect instead.
     * @~chinese 警告:该函数是实验性的。请使用setTextureWithRect代替。
     * 
     * @param spriteFrame @~english A given sprite frame as particle texture.
     * @~chinese 一个给定的精灵帧用作粒子的纹理。
     * @since v0.99.4
     */
    void setDisplayFrame(SpriteFrame *spriteFrame);

    /** @~english Sets a new texture with a rect. The rect is in Points.
     * @~chinese 设置一个新的纹理与矩形。矩形单位是点。
     *
     * @param texture @~english A given texture.
     * @~chinese 一个给定的纹理。
     * @param @~english rect A given rect, in points.
     * @~chinese 一个给定的矩形.
     *
     * @since v0.99.4
     * @js NA
     * @lua NA
     */
    void setTextureWithRect(Texture2D *texture, const Rect& rect);

    /** @~english Listen the event that renderer was recreated on Android/WP8.
     *  Don't call this manually. 
     * @~chinese 在Android/WP8平台上监听纹理重新加载事件的回调，不要手动调用这个方法。
     */
    void listenRendererRecreated(EventCustom* event);
    
    virtual void setTexture(Texture2D* texture) override;
    
    virtual void updateQuadWithParticle(tParticle* particle, const Vec2& newPosition) override;
    
    virtual void postStep() override;
    
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

    virtual void setBatchNode(ParticleBatchNode* batchNode) override;
    
    virtual void setTotalParticles(int tp) override;

    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    ParticleSystemQuad();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleSystemQuad();
    
    virtual bool initWithTotalParticles(int numberOfParticles) override;

protected:
    /** initializes the indices for the vertices*/
    void initIndices();
    
    /** initializes the texture with a rectangle measured Points */
    void initTexCoordsWithRect(const Rect& rect);
    
    /** Updates texture coords */
    void updateTexCoords();

    void setupVBOandVAO();
    void setupVBO();
    bool allocMemory();

    V3F_C4B_T2F_Quad    *_quads;        // quads to be rendered
    GLushort            *_indices;      // indices
    GLuint              _VAOname;
    GLuint              _buffersVBO[2]; //0: vertex  1: indices

    QuadCommand _quadCommand;           // quad command

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleSystemQuad);
};

// end of _2d group
/// @}

NS_CC_END

#endif //__CC_PARTICLE_SYSTEM_QUAD_H__

