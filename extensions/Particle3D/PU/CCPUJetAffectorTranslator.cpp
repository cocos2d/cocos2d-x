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

#include "CCPUJetAffectorTranslator.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttribute.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttributeTranslator.h"

NS_CC_BEGIN

PUJetAffectorTranslator::PUJetAffectorTranslator()
{
}
//-------------------------------------------------------------------------
bool PUJetAffectorTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUAffector* af = static_cast<PUAffector*>(prop->parent->context);
    PUJetAffector* affector = static_cast<PUJetAffector*>(af);

    if (prop->name == token[TOKEN_ACCELERATION])
    {
        // Property: acceleration
        if (passValidateProperty(compiler, prop, token[TOKEN_ACCELERATION], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                PUDynamicAttributeFixed* dynamicAttributeFixed = new (std::nothrow) PUDynamicAttributeFixed();
                dynamicAttributeFixed->setValue(val);
                affector->setDynAcceleration(dynamicAttributeFixed);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_JET_ACCELERATION])
    {
        // Property: jet_aff_accel (deprecated and replaced by 'acceleration')
        if (passValidateProperty(compiler, prop, token[TOKEN_JET_ACCELERATION], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                PUDynamicAttributeFixed* dynamicAttributeFixed = new (std::nothrow) PUDynamicAttributeFixed();
                dynamicAttributeFixed->setValue(val);
                affector->setDynAcceleration(dynamicAttributeFixed);
                return true;
            }
        }
    }

    return false;
}

bool PUJetAffectorTranslator::translateChildObject( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUObjectAbstractNode* child = reinterpret_cast<PUObjectAbstractNode*>(node);
    PUAffector* af = static_cast<PUAffector*>(child->parent->context);
    PUJetAffector* affector = static_cast<PUJetAffector*>(af);

    PUDynamicAttributeTranslator dynamicAttributeTranslator;
    if (child->cls == token[TOKEN_ACCELERATION])
    {
        // Property: acceleration
        dynamicAttributeTranslator.translate(compiler, node);
        PUDynamicAttribute* dynamicAttribute = static_cast<PUDynamicAttribute*>(child->context);
        affector->setDynAcceleration(dynamicAttribute);
        return true;
    }
    else if (child->cls == token[TOKEN_JET_ACCELERATION])
    {
        // Property: jet_aff_accel (deprecated and replaced by 'acceleration')
        dynamicAttributeTranslator.translate(compiler, node);
        PUDynamicAttribute* dynamicAttribute = static_cast<PUDynamicAttribute*>(child->context);
        affector->setDynAcceleration(dynamicAttribute);
        return true;
    }

    return false;
}

NS_CC_END