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

#include "CCPUGeometryRotatorTranslator.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttribute.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttributeTranslator.h"

NS_CC_BEGIN

PUGeometryRotatorTranslator::PUGeometryRotatorTranslator()
{
}
//-------------------------------------------------------------------------
bool PUGeometryRotatorTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUAffector* af = static_cast<PUAffector*>(prop->parent->context);
    PUGeometryRotator* affector = static_cast<PUGeometryRotator*>(af);

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

bool PUGeometryRotatorTranslator::translateChildObject( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUObjectAbstractNode* child = reinterpret_cast<PUObjectAbstractNode*>(node);
    PUAffector* af = static_cast<PUAffector*>(child->parent->context);
    PUGeometryRotator* affector = static_cast<PUGeometryRotator*>(af);

    PUDynamicAttributeTranslator dynamicAttributeTranslator;
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