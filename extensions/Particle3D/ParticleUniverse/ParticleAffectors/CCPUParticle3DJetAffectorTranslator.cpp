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

#include "CCPUParticle3DJetAffectorTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttribute.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttributeTranslator.h"

NS_CC_BEGIN

PUParticle3DJetAffectorTranslator::PUParticle3DJetAffectorTranslator()
{
}
//-------------------------------------------------------------------------
bool PUParticle3DJetAffectorTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUParticle3DAffector* af = static_cast<PUParticle3DAffector*>(prop->parent->context);
    PUParticle3DJetAffector* affector = static_cast<PUParticle3DJetAffector*>(af);

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

bool PUParticle3DJetAffectorTranslator::translateChildObject( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUObjectAbstractNode* child = reinterpret_cast<PUObjectAbstractNode*>(node);
    PUParticle3DAffector* af = static_cast<PUParticle3DAffector*>(child->parent->context);
    PUParticle3DJetAffector* affector = static_cast<PUParticle3DJetAffector*>(af);

    PUParticle3DDynamicAttributeTranslator dynamicAttributeTranslator;
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