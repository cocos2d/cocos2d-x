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

#include "CCPUCircleEmitterTranslator.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttribute.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttributeTranslator.h"

NS_CC_BEGIN

PUCircleEmitterTranslator::PUCircleEmitterTranslator()
{
}
//-------------------------------------------------------------------------
bool PUCircleEmitterTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUEmitter* em = static_cast<PUEmitter*>(prop->parent->context);
    PUCircleEmitter* emitter = static_cast<PUCircleEmitter*>(em);

    if (prop->name == token[TOKEN_RADIUS])
    {
        // Property: radius
        if (passValidateProperty(compiler, prop, token[TOKEN_RADIUS], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                emitter->setRadius(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_CIRCLE_RADIUS])
    {
        // Property: circle_em_radius (deprecated and replaced by radius)
        if (passValidateProperty(compiler, prop, token[TOKEN_CIRCLE_RADIUS], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                emitter->setRadius(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_STEP])
    {
        // Property: step
        if (passValidateProperty(compiler, prop, token[TOKEN_STEP], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                emitter->setStep(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_CIRCLE_STEP])
    {
        // Property: circle_em_step (deprecated and replaced by 'step')
        if (passValidateProperty(compiler, prop, token[TOKEN_CIRCLE_STEP], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                emitter->setStep(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_ANGLE])
    {
        // Property: angle
        if (passValidateProperty(compiler, prop, token[TOKEN_ANGLE], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                emitter->setCircleAngle(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_CIRCLE_ANGLE])
    {
        // Property: circle_em_angle
        if (passValidateProperty(compiler, prop, token[TOKEN_CIRCLE_ANGLE], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                emitter->setCircleAngle(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_EMIT_RANDOM])
    {
        // Property: emit_random
        if (passValidateProperty(compiler, prop, token[TOKEN_EMIT_RANDOM], VAL_BOOL))
        {
            bool val;
            if(getBoolean(*prop->values.front(), &val))
            {
                emitter->setRandom(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_CIRCLE_RANDOM])
    {
        // Property: circle_em_random (deprecated and replaced by 'emit_random'))
        if (passValidateProperty(compiler, prop, token[TOKEN_CIRCLE_RANDOM], VAL_BOOL))
        {
            bool val;
            if(getBoolean(*prop->values.front(), &val))
            {
                emitter->setRandom(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_NORMAL])
    {
        // Property: normal
        {
            Vec3 val;
            if(getVector3(prop->values.begin(), prop->values.end(), &val))
            {
                emitter->setNormal(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_CIRCLE_NORMAL])
    {
        // Property: circle_em_normal (deprecated and replaced by 'normal')
        {
            Vec3 val;
            if(getVector3(prop->values.begin(), prop->values.end(), &val))
            {
                emitter->setNormal(val);
                return true;
            }
        }
    }

    return false;
}

bool PUCircleEmitterTranslator::translateChildObject( PUScriptCompiler* /*compiler*/, PUAbstractNode* /*node*/ )
{
    // No objects
    return false;
}

NS_CC_END
