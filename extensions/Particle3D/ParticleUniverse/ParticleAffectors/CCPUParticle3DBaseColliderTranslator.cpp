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

#include "CCPUParticle3DBaseColliderTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttribute.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttributeTranslator.h"

NS_CC_BEGIN

PUParticle3DBaseColliderTranslator::PUParticle3DBaseColliderTranslator()
{
}
//-------------------------------------------------------------------------
bool PUParticle3DBaseColliderTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUParticle3DAffector* af = static_cast<PUParticle3DAffector*>(prop->parent->context);
    PUParticle3DBaseCollider* affector = static_cast<PUParticle3DBaseCollider*>(af);

    if (prop->name == token[TOKEN_FRICTION])
    {
        if (passValidateProperty(compiler, prop, token[TOKEN_FRICTION], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setFriction(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_COLLIDER_FRICTION])
    {
        if (passValidateProperty(compiler, prop, token[TOKEN_COLLIDER_FRICTION], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setFriction(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_BOUNCYNESS])
    {
        if (passValidateProperty(compiler, prop, token[TOKEN_BOUNCYNESS], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setBouncyness(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_COLLIDER_BOUNCYNESS])
    {
        if (passValidateProperty(compiler, prop, token[TOKEN_COLLIDER_BOUNCYNESS], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setBouncyness(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_INTERSECTION] || prop->name == token[TOKEN_COLLIDER_INTERSECTION])
    {
        if (passValidateProperty(compiler, prop, token[TOKEN_INTERSECTION], VAL_STRING))
        {
            std::string val;
            if(getString(*prop->values.front(), &val))
            {
                if (val == token[TOKEN_COLLIDER_INTERSECTION_POINT])
                {
                    affector->setIntersectionType(PUParticle3DBaseCollider::IT_POINT);
                    return true;
                }
                else if (val == token[TOKEN_COLLIDER_INTERSECTION_BOX])
                {
                    affector->setIntersectionType(PUParticle3DBaseCollider::IT_BOX);
                    return true;
                }
            }
        }
    }
    else if (prop->name == token[TOKEN_COLLIDER_COLLISION_TYPE])
    {
        if (passValidateProperty(compiler, prop, token[TOKEN_COLLIDER_COLLISION_TYPE], VAL_STRING))
        {
            std::string val;
            if(getString(*prop->values.front(), &val))
            {
                if (val == token[TOKEN_COLLIDER_BOUNCE])
                {
                    affector->setCollisionType(PUParticle3DBaseCollider::CT_BOUNCE);
                    return true;
                }
                else if (val == token[TOKEN_COLLIDER_FLOW])
                {
                    affector->setCollisionType(PUParticle3DBaseCollider::CT_FLOW);
                    return true;
                }
            }
        }
    }

    return false;
}

bool PUParticle3DBaseColliderTranslator::translateChildObject( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    // No objects
    return false;
}

NS_CC_END