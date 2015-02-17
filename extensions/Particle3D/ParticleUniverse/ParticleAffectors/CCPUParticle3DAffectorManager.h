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

#ifndef __CC_PU_PARTICLE_3D_AFFECTOR_MANAGER_H__
#define __CC_PU_PARTICLE_3D_AFFECTOR_MANAGER_H__

#include "base/CCRef.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DScriptTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DAffector.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DAlignAffectorTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DBaseColliderTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DBaseForceAffectorTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DBoxColliderTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DCollisionAvoidanceAffectorTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DColorAffectorTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DFlockCenteringAffectorTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DForceFieldAffectorTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DGeometryRotatorTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DGravityAffectorTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DInterParticleColliderTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DJetAffectorTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DLineAffectorTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DLinearForceAffectorTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DParticleFollowerTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DPathFollowerTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DPlaneColliderTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DRandomiserTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DScaleAffectorTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DScaleVelocityAffectorTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DSineForceAffectorTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DSphereColliderTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DTextureAnimatorTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DTextureRotatorTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DVelocityMatchingAffectorTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DVortexAffectorTranslator.h"

using namespace std;
NS_CC_BEGIN

class PUParticle3DAffectorManager
{
public:
    
    static PUParticle3DAffectorManager* Instance();

    /**
     */
    PUScriptTranslator* getTranslator(const std::string &type);
    PUParticle3DAffector* createAffector(const std::string &type);

    
CC_CONSTRUCTOR_ACCESS:
    PUParticle3DAffectorManager();
    ~PUParticle3DAffectorManager();

protected:

    PUParticle3DAlignAffectorTranslator _alignAffectorTranslator;
    PUParticle3DBaseColliderTranslator _baseColliderTranslator;
    PUParticle3DBaseForceAffectorTranslator _baseForceAffectorTranslator;
    PUParticle3DBoxColliderTranslator _boxColliderTranslator;
    PUParticle3DCollisionAvoidanceAffectorTranslator _collisionAvoidanceAffectorTranstor;
    PUParticle3DColorAffectorTranslator _colorAffectorTranslator; 
    PUParticle3DFlockCenteringAffectorTranslator _flockCenteringAffectorTranslator;
    PUParticle3DForceFieldAffectorTranslator _forceFieldAffectorTranslator;
    PUParticle3DGeometryRotatorTranslator _geometryRotatorTranslator; 
    PUParticle3DGravityAffectorTranslator _gravityAffectorTranslator;
    PUParticle3DInterParticleColliderTranslator _interParticleColliderTranslator;
    PUParticle3DJetAffectorTranslator _jetAffectorTranslator;
    PUParticle3DLineAffectorTranslator _lineAffectorTranslator;
    PUParticle3DLinearForceAffectorTranslator _linearForceAffectorTranslator;
    PUParticle3DParticleFollowerTranslator _particleFollowerTranslator;
    PUParticle3DPathFollowerTranslator _pathFollowerTranslator;
    PUParticle3DPlaneColliderTranslator _planeColliderTranslator;
    PUParticle3DRandomiserTranslator _randomiserTranslator;
    PUParticle3DScaleAffectorTranslator _scaleAffectorTranslator;
    PUParticle3DScaleVelocityAffectorTranslator _scaleVelocityAffectorTranslator;
    PUParticle3DSineForceAffectorTranslator _sineForceAffectorTranslator;
    PUParticle3DSphereColliderTranslator _sphereColliderTranslator;
    PUParticle3DTextureAnimatorTranslator _textureAnimatorTranslator;
    PUParticle3DTextureRotatorTranslator _textureRotatorTranslator;
    PUParticle3DVelocityMatchingAffectorTranslator _velocityMatchingAffectorTranslator;
    PUParticle3DVortexAffectorTranslator _vortexAffectorTranslator;
};

NS_CC_END


#endif 
