/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
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

#include "CCPUSineForceAffectorTranslator.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttribute.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttributeTranslator.h"
#include "extensions/Particle3D/PU/CCPUBaseForceAffectorTranslator.h"

NS_CC_BEGIN

PUSineForceAffectorTranslator::PUSineForceAffectorTranslator()
{
}
//-------------------------------------------------------------------------
bool PUSineForceAffectorTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUAffector* af = static_cast<PUAffector*>(prop->parent->context);
    PUSineForceAffector* affector = static_cast<PUSineForceAffector*>(af);

    if (prop->name == token[TOKEN_MIN_FREQUENCY])
    {
        // Property: min_frequency
        if (passValidateProperty(compiler, prop, token[TOKEN_MIN_FREQUENCY], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setFrequencyMin(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_SINE_MIN_FREQUENCY])
    {
        // Property: sinef_aff_frequency_min (deprecated and replaced by 'min_frequency')
        if (passValidateProperty(compiler, prop, token[TOKEN_SINE_MIN_FREQUENCY], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setFrequencyMin(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_MAX_FREQUENCY])
    {
        // Property: max_frequency
        if (passValidateProperty(compiler, prop, token[TOKEN_MAX_FREQUENCY], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setFrequencyMax(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_SINE_MAX_FREQUENCY])
    {
        // Property: sinef_aff_frequency_max (deprecated and replaced by 'max_frequency')
        if (passValidateProperty(compiler, prop, token[TOKEN_SINE_MAX_FREQUENCY], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setFrequencyMax(val);
                return true;
            }
        }
    }
    else
    {
        // Parse the BaseForceAffector
        PUBaseForceAffectorTranslator BaseForceAffectorTranslator;
        return BaseForceAffectorTranslator.translateChildProperty(compiler, node); // Must be the last
    }

    return false;
}

bool PUSineForceAffectorTranslator::translateChildObject( PUScriptCompiler* /*compiler*/, PUAbstractNode* /*node*/ )
{
    // No objects
    return false;
}

NS_CC_END
