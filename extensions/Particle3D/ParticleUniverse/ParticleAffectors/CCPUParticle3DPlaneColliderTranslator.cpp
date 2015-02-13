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

#include "CCPUParticle3DPlaneColliderTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttribute.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttributeTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DBaseColliderTranslator.h"

NS_CC_BEGIN

PUParticle3DPlaneColliderTranslator::PUParticle3DPlaneColliderTranslator()
{
}
//-------------------------------------------------------------------------
bool PUParticle3DPlaneColliderTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUParticle3DAffector* af = static_cast<PUParticle3DAffector*>(prop->parent->context);
    PUParticle3DPlaneCollider* affector = static_cast<PUParticle3DPlaneCollider*>(af);

    if (prop->name == token[TOKEN_NORMAL])
    {
        // Property: normal
        if (passValidateProperty(compiler, prop, token[TOKEN_NORMAL], VAL_VECTOR3))
        {
            Vec3 val;
            if(getVector3(prop->values.begin(), prop->values.end(), &val))
            {
                affector->setNormal(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_PLANECOLL_NORMAL])
    {
        // Property: plane_collider_normal (deprecated and replaced by 'normal')
        if (passValidateProperty(compiler, prop, token[TOKEN_PLANECOLL_NORMAL], VAL_VECTOR3))
        {
            Vec3 val;
            if(getVector3(prop->values.begin(), prop->values.end(), &val))
            {
                affector->setNormal(val);
                return true;
            }
        }
    }
    else
    {
        // Parse the BaseCollider
        PUParticle3DBaseColliderTranslator baseColliderTranslator;
        return baseColliderTranslator.translateChildProperty(compiler, node);
    }

    return false;
}

bool PUParticle3DPlaneColliderTranslator::translateChildObject( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    // No objects
    return false;
}

NS_CC_END