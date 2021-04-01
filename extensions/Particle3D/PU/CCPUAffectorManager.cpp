/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "CCPUAffectorManager.h"
#include "extensions/Particle3D/PU/CCPUAlignAffector.h"
#include "extensions/Particle3D/PU/CCPUBaseCollider.h"
#include "extensions/Particle3D/PU/CCPUBaseForceAffector.h"
#include "extensions/Particle3D/PU/CCPUBoxCollider.h"
#include "extensions/Particle3D/PU/CCPUCollisionAvoidanceAffector.h"
#include "extensions/Particle3D/PU/CCPUColorAffector.h"
#include "extensions/Particle3D/PU/CCPUFlockCenteringAffector.h"
#include "extensions/Particle3D/PU/CCPUForceFieldAffector.h"
#include "extensions/Particle3D/PU/CCPUGeometryRotator.h"
#include "extensions/Particle3D/PU/CCPUGravityAffector.h"
#include "extensions/Particle3D/PU/CCPUInterParticleCollider.h"
#include "extensions/Particle3D/PU/CCPUJetAffector.h"
#include "extensions/Particle3D/PU/CCPULineAffector.h"
#include "extensions/Particle3D/PU/CCPULinearForceAffector.h"
#include "extensions/Particle3D/PU/CCPUParticleFollower.h"
#include "extensions/Particle3D/PU/CCPUPathFollower.h"
#include "extensions/Particle3D/PU/CCPUPlaneCollider.h"
#include "extensions/Particle3D/PU/CCPURandomiser.h"
#include "extensions/Particle3D/PU/CCPUScaleAffector.h"
#include "extensions/Particle3D/PU/CCPUScaleVelocityAffector.h"
#include "extensions/Particle3D/PU/CCPUSineForceAffector.h"
#include "extensions/Particle3D/PU/CCPUSphereCollider.h"
#include "extensions/Particle3D/PU/CCPUTextureAnimator.h"
#include "extensions/Particle3D/PU/CCPUTextureRotator.h"
#include "extensions/Particle3D/PU/CCPUVelocityMatchingAffector.h"
#include "extensions/Particle3D/PU/CCPUVortexAffector.h"

NS_CC_BEGIN
PUAffectorManager::PUAffectorManager()
{
    
}

PUAffectorManager::~PUAffectorManager()
{
    
}

PUAffectorManager* PUAffectorManager::Instance()
{
    static PUAffectorManager pam;
    return &pam;
}

PUScriptTranslator* PUAffectorManager::getTranslator( const std::string &type )
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

PUAffector* PUAffectorManager::createAffector( const std::string &type )
{
    if (type == "Align"){
        return PUAlignAffector::create();
    }else if (type == "Dummy02"){
        return nullptr;
    }else if (type == "Dummy01"){
        return nullptr;
    }else if (type == "BoxCollider"){
        return PUBoxCollider::create();
    }else if (type == "CollisionAvoidance"){
        return PUCollisionAvoidanceAffector::create();
    }else if (type == "Colour"){
        return PUColorAffector::create();
    }else if (type == "FlockCentering"){
        return PUFlockCenteringAffector::create();
    }else if (type == "ForceField"){
        return PUForceFieldAffector::create();
    }else if (type == "GeometryRotator"){
        return PUGeometryRotator::create();
    }else if (type == "Gravity"){
        return PUGravityAffector::create();
    }else if (type == "InterParticleCollider"){
        return PUParticle3DInterParticleCollider::create();
    }else if (type == "Jet"){
        return PUJetAffector::create();
    }else if (type == "Line"){
        return PULineAffector::create();
    }else if (type == "LinearForce"){
        return PULinearForceAffector::create();
    }else if (type == "ParticleFollower"){
        return PUParticleFollower::create();
    }else if (type == "PathFollower"){
        return PUPathFollower::create();
    }else if (type == "PlaneCollider"){
        return PUPlaneCollider::create();
    }else if (type == "Randomiser"){
        return PURandomiser::create();
    }else if (type == "Scale"){
        return PUScaleAffector::create();
    }else if (type == "ScaleVelocity"){
        return PUScaleVelocityAffector::create();
    }else if (type == "SineForce"){
        return PUSineForceAffector::create();
    }else if (type == "SphereCollider"){
        return PUSphereCollider::create();
    }else if (type == "TextureAnimator"){
        return PUTextureAnimator::create();
    }else if (type == "TextureRotator"){
        return PUTextureRotator::create();
    }else if (type == "VelocityMatching"){
        return PUVelocityMatchingAffector::create();
    }else if (type == "Vortex"){
        return PUVortexAffector::create();
    }
    return nullptr;
}

NS_CC_END