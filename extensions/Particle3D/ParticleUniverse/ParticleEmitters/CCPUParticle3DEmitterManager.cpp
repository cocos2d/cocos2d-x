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

#include "CCPUParticle3DEmitterManager.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DBoxEmitter.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DCircleEmitter.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DLineEmitter.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DMeshSurfaceEmitter.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DPointEmitter.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DPositionEmitter.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DSlaveEmitter.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DSphereSurfaceEmitter.h"

NS_CC_BEGIN
PUParticle3DEmitterManager::PUParticle3DEmitterManager()
{
    
}

PUParticle3DEmitterManager::~PUParticle3DEmitterManager()
{
    
}

PUParticle3DEmitterManager* PUParticle3DEmitterManager::Instance()
{
    static PUParticle3DEmitterManager ptm;
    return &ptm;
}

PUScriptTranslator* PUParticle3DEmitterManager::getTranslator( const std::string &type )
{
    if (type == "Box"){
        return &_boxEmitterTranlator;
    }else if (type == "Circle"){
        return &_circleEmitterTranlator;
    }else if (type == "Line"){
        return &_lineEmitterTranlator;
    }else if (type == "MeshSurface"){
        return &_meshSurfaceEmitterTranlator;
    }else if (type == "Point"){
        return &_pointEmitterTranlator;
    }else if (type == "Position"){
        return &_positionEmitterTranlator;
    }else if (type == "Slave"){
        return &_slaveEmitterTranlator;
    }else if (type == "SphereSurface"){
        return &_sphereSurfaceEmitterTranlator;
    }else if (type == "Vertex"){
        return nullptr;
    }
    return nullptr;
}

PUParticle3DEmitter* PUParticle3DEmitterManager::createEmitter( const std::string &type )
{
    if (type == "Box"){
        return PUParticle3DBoxEmitter::create();
    }else if (type == "Circle"){
        return PUParticle3DCircleEmitter::create();
    }else if (type == "Line"){
        return PUParticle3DLineEmitter::create();
    }else if (type == "MeshSurface"){
        return PUParticle3DMeshSurfaceEmitter::create();
    }else if (type == "Point"){
        return PUParticle3DPointEmitter::create();
    }else if (type == "Position"){
        return PUParticle3DPositionEmitter::create();
    }else if (type == "Slave"){
        return PUParticle3DSlaveEmitter::create();
    }else if (type == "SphereSurface"){
        return PUParticle3DSphereSurfaceEmitter::create();
    }else if (type == "Vertex"){
        return nullptr;
    }
    return nullptr;
}

NS_CC_END