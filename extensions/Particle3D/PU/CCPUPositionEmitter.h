/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015 Chukong Technologies Inc.
 
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


#ifndef __CC_PU_PARTICLE_3D_POSITION_EMITTER_H__
#define __CC_PU_PARTICLE_3D_POSITION_EMITTER_H__

#include "extensions/Particle3D/PU/CCPUEmitter.h"

NS_CC_BEGIN

class  CC_DLL PUPositionEmitter : public PUEmitter
{
public:
    // Constants
    static const bool DEFAULT_RANDOMIZE;

    static PUPositionEmitter* create();
    /** 
    */
    bool isRandomized(void) const;

    /** 
    */
    void setRandomized(bool randomized);

    /** Returns a list with positions
    */
    const std::vector<Vec3>& getPositions(void) const;

    /** Add a new position to this emitter
    */
    void addPosition(const Vec3& position);

    /** Remove all positions from this emitter
    */
    void removeAllPositions(void);

    /** See ParticleEmitter
    */
    void notifyStart(void) override;

    /** See ParticleEmitter
    */
    virtual unsigned short calculateRequestedParticles(float timeElapsed) override;

    /** Generate a particle position based on the added positions.
    */
    virtual void initParticlePosition(PUParticle3D* particle) override;

    virtual PUPositionEmitter* clone() override;
    virtual void copyAttributesTo (PUEmitter* emitter) override;

CC_CONSTRUCTOR_ACCESS:
    PUPositionEmitter(void);
    virtual ~PUPositionEmitter(void) {};

protected:
    std::vector<Vec3> _positionList;
    bool _randomized;
    size_t _index;

};
NS_CC_END

#endif