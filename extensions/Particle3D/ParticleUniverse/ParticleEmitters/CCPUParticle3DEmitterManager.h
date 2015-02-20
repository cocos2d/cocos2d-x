/****************************************************************************
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

#ifndef __CC_PU_PARTICLE_3D_EMITTER_MANAGER_H__
#define __CC_PU_PARTICLE_3D_EMITTER_MANAGER_H__

#include "base/CCRef.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DScriptTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DEmitter.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DBoxEmitterTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DCircleEmitterTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DLineEmitterTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DMeshSurfaceEmitterTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DPointEmitterTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DPositionEmitterTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DSlaveEmitterTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DSphereSurfaceEmitterTranslator.h"

using namespace std;
NS_CC_BEGIN

class PUParticle3DEmitterManager
{
public:
    
    static PUParticle3DEmitterManager* Instance();

    /**
     */
    PUScriptTranslator* getTranslator(const std::string &type);
    PUParticle3DEmitter* createEmitter(const std::string &type);

    
CC_CONSTRUCTOR_ACCESS:
    PUParticle3DEmitterManager();
    ~PUParticle3DEmitterManager();

protected:

    PUParticle3DBoxEmitterTranslator _boxEmitterTranlator;
    PUParticle3DCircleEmitterTranslator _circleEmitterTranlator;
    PUParticle3DLineEmitterTranslator _lineEmitterTranlator;
    PUParticle3DMeshSurfaceEmitterTranslator _meshSurfaceEmitterTranlator;
    PUParticle3DPointEmitterTranslator _pointEmitterTranlator;
    PUParticle3DPositionEmitterTranslator _positionEmitterTranlator;
    PUParticle3DSlaveEmitterTranslator _slaveEmitterTranlator;
    PUParticle3DSphereSurfaceEmitterTranslator _sphereSurfaceEmitterTranlator;
};

NS_CC_END


#endif 
