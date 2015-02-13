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

#include "CCPUParticle3DAffectorManager.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DAlignAffector.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DBaseCollider.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DBaseForceAffector.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DBoxCollider.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DCollisionAvoidanceAffector.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DColorAffector.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DFlockCenteringAffector.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DForceFieldAffector.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DGeometryRotator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DGravityAffector.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DInterParticleCollider.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DJetAffector.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DLineAffector.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DLinearForceAffector.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DParticleFollower.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DPathFollower.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DPlaneCollider.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DRandomiser.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DScaleAffector.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DScaleVelocityAffector.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DSineForceAffector.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DSphereCollider.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DTextureAnimator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DTextureRotator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DVelocityMatchingAffector.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DVortexAffector.h"

NS_CC_BEGIN
PUParticle3DAffectorManager::PUParticle3DAffectorManager()
{
    
}

PUParticle3DAffectorManager::~PUParticle3DAffectorManager()
{
    
}

PUParticle3DAffectorManager* PUParticle3DAffectorManager::Instance()
{
    static PUParticle3DAffectorManager pam;
    return &pam;
}

PUScriptTranslator* PUParticle3DAffectorManager::getTranslator( const std::string &type )
{
    if (type == "Align"){
        return &_alignAffectorTranslator;
    }else if (type == "Dummy02"){
        return &_baseColliderTranslator;
    }else if (type == "Dummy01"){
        return &_baseForceAffectorTranslator;
    }else if (type == "BoxCollider"){
        return &_boxColliderTranslator;
    }else if (type == "CollisionAvoidance"){
        return &_collisionAvoidanceAffectorTranstor;
    }else if (type == "Colour"){
        return &_colorAffectorTranslator;
    }else if (type == "FlockCentering"){
        return &_flockCenteringAffectorTranslator;
    }else if (type == "ForceField"){
        return &_forceFieldAffectorTranslator;
    }else if (type == "GeometryRotator"){
        return &_geometryRotatorTranslator;
    }else if (type == "Gravity"){
        return &_gravityAffectorTranslator;
    }else if (type == "InterParticleCollider"){
        return &_interParticleColliderTranslator;
    }else if (type == "Jet"){
        return &_jetAffectorTranslator;
    }else if (type == "Line"){
        return &_lineAffectorTranslator;
    }else if (type == "LinearForce"){
        return &_linearForceAffectorTranslator;
    }else if (type == "ParticleFollower"){
        return &_particleFollowerTranslator;
    }else if (type == "PathFollower"){
        return &_pathFollowerTranslator;
    }else if (type == "PlaneCollider"){
        return &_planeColliderTranslator;
    }else if (type == "Randomiser"){
        return &_randomiserTranslator;
    }else if (type == "Scale"){
        return &_scaleAffectorTranslator;
    }else if (type == "ScaleVelocity"){
        return &_scaleVelocityAffectorTranslator;
    }else if (type == "SineForce"){
        return &_sineForceAffectorTranslator;
    }else if (type == "SphereCollider"){
        return &_sphereColliderTranslator;
    }else if (type == "TextureAnimator"){
        return &_textureAnimatorTranslator;
    }else if (type == "TextureRotator"){
        return &_textureRotatorTranslator;
    }else if (type == "VelocityMatching"){
        return &_velocityMatchingAffectorTranslator;
    }else if (type == "Vortex"){
        return &_vortexAffectorTranslator;
    }
    return nullptr;
}

PUParticle3DAffector* PUParticle3DAffectorManager::createAffector( const std::string &type )
{
    if (type == "Align"){
        return PUParticle3DAlignAffector::create();
    }else if (type == "Dummy02"){
        return nullptr;
    }else if (type == "Dummy01"){
        return nullptr;
    }else if (type == "BoxCollider"){
        return PUParticle3DBoxCollider::create();
    }else if (type == "CollisionAvoidance"){
        return PUParticle3DCollisionAvoidanceAffector::create();
    }else if (type == "Colour"){
        return PUParticle3DColorAffector::create();
    }else if (type == "FlockCentering"){
        return PUParticle3DFlockCenteringAffector::create();
    }else if (type == "ForceField"){
        return PUParticle3DForceFieldAffector::create();
    }else if (type == "GeometryRotator"){
        return PUParticle3DGeometryRotator::create();
    }else if (type == "Gravity"){
        return PUParticle3DGravityAffector::create();
    }else if (type == "InterParticleCollider"){
        return PUParticle3DInterParticleCollider::create();
    }else if (type == "Jet"){
        return PUParticle3DJetAffector::create();
    }else if (type == "Line"){
        return PUParticle3DLineAffector::create();
    }else if (type == "LinearForce"){
        return PUParticle3DLinearForceAffector::create();
    }else if (type == "ParticleFollower"){
        return PUParticle3DParticleFollower::create();
    }else if (type == "PathFollower"){
        return PUParticle3DPathFollower::create();
    }else if (type == "PlaneCollider"){
        return PUParticle3DPlaneCollider::create();
    }else if (type == "Randomiser"){
        return PUParticle3DRandomiser::create();
    }else if (type == "Scale"){
        return PUParticle3DScaleAffector::create();
    }else if (type == "ScaleVelocity"){
        return PUParticle3DScaleVelocityAffector::create();
    }else if (type == "SineForce"){
        return PUParticle3DSineForceAffector::create();
    }else if (type == "SphereCollider"){
        return PUParticle3DSphereCollider::create();
    }else if (type == "TextureAnimator"){
        return PUParticle3DTextureAnimator::create();
    }else if (type == "TextureRotator"){
        return PUParticle3DTextureRotator::create();
    }else if (type == "VelocityMatching"){
        return PUParticle3DVelocityMatchingAffector::create();
    }else if (type == "Vortex"){
        return PUParticle3DVortexAffector::create();
    }
    return nullptr;
}

NS_CC_END