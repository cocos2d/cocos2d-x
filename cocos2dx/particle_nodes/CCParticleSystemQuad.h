/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Leonardo Kasperavičius
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
#ifndef __CC_PARTICLE_SYSTEM_QUAD_H__
#define __CC_PARTICLE_SYSTEM_QUAD_H__

#include  "CCParticleSystem.h"

NS_CC_BEGIN

class SpriteFrame;

/**
 * @addtogroup particle_nodes
 * @{
 */

/** @brief ParticleSystemQuad is a subclass of ParticleSystem

It includes all the features of ParticleSystem.

Special features and Limitations:    
- Particle size can be any float number.
- The system can be scaled
- The particles can be rotated
- It supports subrects
- It supports batched rendering since 1.1
@since v0.8
*/
class CC_DLL ParticleSystemQuad : public ParticleSystem
{
public:

    /** creates a Particle Emitter */
    static ParticleSystemQuad * create();
    /** creates a Particle Emitter with a number of particles */
    static ParticleSystemQuad * createWithTotalParticles(unsigned int numberOfParticles);
    /** creates an initializes a ParticleSystemQuad from a plist file.
     This plist files can be created manually or with Particle Designer:
     */
    static ParticleSystemQuad * create(const char *plistFile);

    ParticleSystemQuad();
    virtual ~ParticleSystemQuad();

    /** initializes the indices for the vertices*/
    void initIndices();

    /** initializes the texture with a rectangle measured Points */
    void initTexCoordsWithRect(const Rect& rect);

    /** Sets a new SpriteFrame as particle.
    WARNING: this method is experimental. Use setTexture:withRect instead.
    @since v0.99.4
    */
    void setDisplayFrame(SpriteFrame *spriteFrame);

    /** Sets a new texture with a rect. The rect is in Points.
    @since v0.99.4
    */
    void setTextureWithRect(Texture2D *texture, const Rect& rect);

    /** listen the event that coming to foreground on Android
     */
    void listenBackToForeground(Object *obj);

    // Overrides
    virtual bool initWithTotalParticles(unsigned int numberOfParticles) override;
    virtual void setTexture(Texture2D* texture) override;
    virtual void updateQuadWithParticle(tParticle* particle, const Point& newPosition) override;
    virtual void postStep() override;
    virtual void draw() override;
    virtual void setBatchNode(ParticleBatchNode* batchNode) override;
    virtual void setTotalParticles(unsigned int tp) override;

private:
#if CC_TEXTURE_ATLAS_USE_VAO
    void setupVBOandVAO();
#else
    void setupVBO();
#endif
    bool allocMemory();
    
protected:
    V3F_C4B_T2F_Quad    *_quads;        // quads to be rendered
    GLushort            *_indices;    // indices
    
#if CC_TEXTURE_ATLAS_USE_VAO
    GLuint                _VAOname;
#endif
    
    GLuint                _buffersVBO[2]; //0: vertex  1: indices
};

// end of particle_nodes group
/// @}

NS_CC_END

#endif //__CC_PARTICLE_SYSTEM_QUAD_H__

