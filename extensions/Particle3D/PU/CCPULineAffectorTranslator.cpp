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

#include "CCPULineAffectorTranslator.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttribute.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttributeTranslator.h"

NS_CC_BEGIN

PULineAffectorTranslator::PULineAffectorTranslator()
{
}
//-------------------------------------------------------------------------
bool PULineAffectorTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUAffector* af = static_cast<PUAffector*>(prop->parent->context);
    PULineAffector* affector = static_cast<PULineAffector*>(af);

    if (prop->name == token[TOKEN_MAX_DEVIATION])
    {
        // Property: max_deviation
        if (passValidateProperty(compiler, prop, token[TOKEN_MAX_DEVIATION], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setMaxDeviation(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_LINE_AFF_MAX_DEVIATION])
    {
        // Property: line_aff_max_deviation (deprecated and replaced by 'max_deviation')
        if (passValidateProperty(compiler, prop, token[TOKEN_LINE_AFF_MAX_DEVIATION], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setMaxDeviation(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_TIME_STEP])
    {
        // Property: time_step
        if (passValidateProperty(compiler, prop, token[TOKEN_TIME_STEP], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setTimeStep(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_LINE_AFF_TIME_STEP])
    {
        // Property: line_aff_time_step (deprecated and replaced by 'time_step')
        if (passValidateProperty(compiler, prop, token[TOKEN_LINE_AFF_TIME_STEP], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setTimeStep(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_END])
    {
        // Property: end
        if (passValidateProperty(compiler, prop, token[TOKEN_END], VAL_VECTOR3))
        {
            Vec3 val;
            if(getVector3(prop->values.begin(), prop->values.end(), &val))
            {
                affector->setEnd(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_LINE_AFF_END])
    {
        // Property: line_aff_end (deprecated and replaced by 'end')
        if (passValidateProperty(compiler, prop, token[TOKEN_LINE_AFF_END], VAL_VECTOR3))
        {
            Vec3 val;
            if(getVector3(prop->values.begin(), prop->values.end(), &val))
            {
                affector->setEnd(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_DRIFT])
    {
        // Property: drift
        if (passValidateProperty(compiler, prop, token[TOKEN_DRIFT], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setDrift(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_LINE_AFF_DRIFT])
    {
        // Property: line_aff_drift (deprecated and replaced by 'drift')
        if (passValidateProperty(compiler, prop, token[TOKEN_LINE_AFF_DRIFT], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setDrift(val);
                return true;
            }
        }
    }

    return false;
}

bool PULineAffectorTranslator::translateChildObject( PUScriptCompiler* /*compiler*/, PUAbstractNode* /*node*/ )
{
    // No objects
    return false;
}

NS_CC_END
