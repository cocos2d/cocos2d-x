/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2017 Chukong Technologies Inc.
 
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

#include "CCPURandomiserTranslator.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttribute.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttributeTranslator.h"

NS_CC_BEGIN

PURandomiserTranslator::PURandomiserTranslator()
{
}
//-------------------------------------------------------------------------
bool PURandomiserTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUAffector* af = static_cast<PUAffector*>(prop->parent->context);
    PURandomiser* affector = static_cast<PURandomiser*>(af);

    if (prop->name == token[TOKEN_MAX_DEVIATION_X])
    {
        // Property: max_deviation_x
        if (passValidateProperty(compiler, prop, token[TOKEN_MAX_DEVIATION_X], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setMaxDeviationX(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_RND_MAX_DEVIATION_X])
    {
        // Property: rand_aff_max_deviation_x (deprecated and replaced by 'max_deviation_x')
        if (passValidateProperty(compiler, prop, token[TOKEN_RND_MAX_DEVIATION_X], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setMaxDeviationX(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_MAX_DEVIATION_Y])
    {
        // Property: max_deviation_y
        if (passValidateProperty(compiler, prop, token[TOKEN_MAX_DEVIATION_Y], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setMaxDeviationY(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_RND_MAX_DEVIATION_Y])
    {
        // Property: rand_aff_max_deviation_y (deprecated and replaced by 'max_deviation_y')
        if (passValidateProperty(compiler, prop, token[TOKEN_RND_MAX_DEVIATION_Y], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setMaxDeviationY(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_MAX_DEVIATION_Z])
    {
        // Property: max_deviation_z
        if (passValidateProperty(compiler, prop, token[TOKEN_MAX_DEVIATION_Z], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setMaxDeviationZ(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_RND_MAX_DEVIATION_Z])
    {
        // Property: rand_aff_max_deviation_z (deprecated and replaced by 'max_deviation_z')
        if (passValidateProperty(compiler, prop, token[TOKEN_RND_MAX_DEVIATION_Z], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setMaxDeviationZ(val);
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
    else if (prop->name == token[TOKEN_RND_TIME_STEP])
    {
        // Property: rand_aff_time_step (deprecated and replaced by 'time_step')
        if (passValidateProperty(compiler, prop, token[TOKEN_RND_TIME_STEP], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                affector->setTimeStep(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_USE_DIRECTION])
    {
        // Property: use_direction
        if (passValidateProperty(compiler, prop, token[TOKEN_USE_DIRECTION], VAL_BOOL))
        {
            bool val;
            if(getBoolean(*prop->values.front(), &val))
            {
                affector->setRandomDirection(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_RND_DIRECTION])
    {
        // Property: rand_aff_direction (deprecated and replaced by 'use_direction')
        if (passValidateProperty(compiler, prop, token[TOKEN_RND_DIRECTION], VAL_BOOL))
        {
            bool val;
            if(getBoolean(*prop->values.front(), &val))
            {
                affector->setRandomDirection(val);
                return true;
            }
        }
    }

    return false;
}

bool PURandomiserTranslator::translateChildObject( PUScriptCompiler* /*compiler*/, PUAbstractNode* /*node*/ )
{
    // No objects
    return false;
}

NS_CC_END
