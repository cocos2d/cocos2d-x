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

#include "CCPUParticle3DGeometryRotatorTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttribute.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttributeTranslator.h"

NS_CC_BEGIN

PUParticle3DGeometryRotatorTranslator::PUParticle3DGeometryRotatorTranslator()
{
}
//-------------------------------------------------------------------------
bool PUParticle3DGeometryRotatorTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUParticle3DAffector* af = static_cast<PUParticle3DAffector*>(prop->parent->context);
    PUParticle3DGeometryRotator* affector = static_cast<PUParticle3DGeometryRotator*>(af);

    if (prop->name == token[TOKEN_USE_OWN_ROTATION])
    {
        // Property: use_own_rotation
        if (passValidateProperty(compiler, prop, token[TOKEN_USE_OWN_ROTATION], VAL_BOOL))
        {
            bool val;
            if(getBoolean(*prop->values.front(), &val))
            {
                affector->setUseOwnRotationSpeed(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_GEOMROT_USE_OWN_ROTATION])
    {
        // Property: geom_rot_use_own_rotation (deprecated and replaced by 'use_own_rotation')
        if (passValidateProperty(compiler, prop, token[TOKEN_GEOMROT_USE_OWN_ROTATION], VAL_BOOL))
        {
            bool val;
            if(getBoolean(*prop->values.front(), &val))
            {
                affector->setUseOwnRotationSpeed(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_ROTATION_SPEED])
    {
        // Property: rotation_speed
        if (passValidateProperty(compiler, prop, token[TOKEN_ROTATION_SPEED], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                PUDynamicAttributeFixed* dynamicAttributeFixed = new (std::nothrow) PUDynamicAttributeFixed();
                dynamicAttributeFixed->setValue(val);
                affector->setRotationSpeed(dynamicAttributeFixed);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_GEOMROT_ROTATION_SPEED])
    {
        // Property: geom_rot_rotation_speed (deprecated and replaced by 'rotation_speed')
        if (passValidateProperty(compiler, prop, token[TOKEN_GEOMROT_ROTATION_SPEED], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                PUDynamicAttributeFixed* dynamicAttributeFixed = new (std::nothrow) PUDynamicAttributeFixed();
                dynamicAttributeFixed->setValue(val);
                affector->setRotationSpeed(dynamicAttributeFixed);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_ROTATION_AXIS])
    {
        // Property: rotation_axis
        if (passValidateProperty(compiler, prop, token[TOKEN_ROTATION_AXIS], VAL_VECTOR3))
        {
            Vec3 val;
            if(getVector3(prop->values.begin(), prop->values.end(), &val))
            {
                affector->setRotationAxis(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_GEOMROT_ROTATION_AXIS])
    {
        // Property: geom_rot_axis (deprecated and replaced by 'rotation_axis')
        if (passValidateProperty(compiler, prop, token[TOKEN_GEOMROT_ROTATION_AXIS], VAL_VECTOR3))
        {
            Vec3 val;
            if(getVector3(prop->values.begin(), prop->values.end(), &val))
            {
                affector->setRotationAxis(val);
                return true;
            }
        }
    }

    return false;
}

bool PUParticle3DGeometryRotatorTranslator::translateChildObject( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUObjectAbstractNode* child = reinterpret_cast<PUObjectAbstractNode*>(node);
    PUParticle3DAffector* af = static_cast<PUParticle3DAffector*>(child->parent->context);
    PUParticle3DGeometryRotator* affector = static_cast<PUParticle3DGeometryRotator*>(af);

    PUParticle3DDynamicAttributeTranslator dynamicAttributeTranslator;
    if (child->cls == token[TOKEN_ROTATION_SPEED])
    {
        // Property: rotation_speed
        dynamicAttributeTranslator.translate(compiler, node);
        PUDynamicAttribute* dynamicAttribute = static_cast<PUDynamicAttribute*>(child->context);
        affector->setRotationSpeed(dynamicAttribute);
        return true;
    }
    else if (child->cls == token[TOKEN_GEOMROT_ROTATION_SPEED])
    {
        // Property: geom_rot_rotation_speed (deprecated and replaced by 'rotation_speed')
        dynamicAttributeTranslator.translate(compiler, node);
        PUDynamicAttribute* dynamicAttribute = static_cast<PUDynamicAttribute*>(child->context);
        affector->setRotationSpeed(dynamicAttribute);
        return true;
    }

    return false;
}

NS_CC_END