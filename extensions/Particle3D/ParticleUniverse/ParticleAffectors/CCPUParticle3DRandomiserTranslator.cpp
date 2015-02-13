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

#include "CCPUParticle3DRandomiserTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttribute.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttributeTranslator.h"

NS_CC_BEGIN

PUParticle3DRandomiserTranslator::PUParticle3DRandomiserTranslator()
{
}
//-------------------------------------------------------------------------
bool PUParticle3DRandomiserTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUParticle3DAffector* af = static_cast<PUParticle3DAffector*>(prop->parent->context);
    PUParticle3DRandomiser* affector = static_cast<PUParticle3DRandomiser*>(af);

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
        // Property: rand_aff_max_deviation_x (depreacted and replaced by 'max_deviation_x')
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

bool PUParticle3DRandomiserTranslator::translateChildObject( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    // No objects
    return false;
}

NS_CC_END