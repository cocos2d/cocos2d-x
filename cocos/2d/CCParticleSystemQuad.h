/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Leonardo Kasperavičius
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2016 Chukong Technologies Inc.
 
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
 * @brief ParticleSystemQuad is a subclass of ParticleSystem.

It includes all the features of ParticleSystem.

Special features and Limitations:    
- Particle size can be any float number.
- The system can be scaled.
- The particles can be rotated.
- It supports subrects.
- It supports batched rendering since 1.1.
@since v0.8
@js NA
*/
class CC_DLL ParticleSystemQuad : public ParticleSystem
{
public:

    /** Creates a Particle Emitter.
     *
     * @return An autoreleased ParticleSystemQuad object.
     */
    static ParticleSystemQuad * create();
    /** Creates a Particle Emitter with a number of particles.
     *
     * @param numberOfParticles A given number of particles.
     * @return An autoreleased ParticleSystemQuad object.
     */
    static ParticleSystemQuad * createWithTotalParticles(int numberOfParticles);
    /** Creates an initializes a ParticleSystemQuad from a plist file.
     This plist files can be created manually or with Particle Designer.
     *
     * @param filename Particle plist file name.
     * @return An autoreleased ParticleSystemQuad object.
     */
    static ParticleSystemQuad * create(const std::string& filename);
    /** Creates a Particle Emitter with a dictionary.
     * 
     * @param dictionary Particle dictionary.
     * @return An autoreleased ParticleSystemQuad object.
     */
    static ParticleSystemQuad * create(ValueMap &dictionary);

    /** Sets a new SpriteFrame as particle.
    WARNING: this method is experimental. Use setTextureWithRect instead.
     *
     * @param spriteFrame A given sprite frame as particle texture.
    @since v0.99.4
    */
    void setDisplayFrame(SpriteFrame *spriteFrame);

    /** Sets a new texture with a rect. The rect is in Points.
     @since v0.99.4
     * @js NA
     * @lua NA
     *
     * @param texture A given texture.
     8 @param rect A given rect, in points.
     */
    void setTextureWithRect(Texture2D *texture, const Rect& rect);

    /** Listen the event that renderer was recreated on Android/WP8.
     * @js NA
     * @lua NA
     *
     * @param event the event that renderer was recreated on Android/WP8.
     */
    void listenRendererRecreated(EventCustom* event);

    /**
     * @js NA
     * @lua NA
     */
    virtual void setTexture(Texture2D* texture) override;
    /**
     * @js NA
     * @lua NA
     */    
    virtual void updateParticleQuads() override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void postStep() override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

    /**
     * @js NA
     * @lua NA
     */
    virtual void setBatchNode(ParticleBatchNode* batchNode) override;
    /**
     * @js NA
     * @lua NA
     */
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
    
    // Overrides
    /**
     * @js NA
     * @lua NA
     */
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

