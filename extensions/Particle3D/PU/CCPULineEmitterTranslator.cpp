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

#include "CCPULineEmitterTranslator.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttribute.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttributeTranslator.h"

NS_CC_BEGIN

PULineEmitterTranslator::PULineEmitterTranslator()
{
}
//-------------------------------------------------------------------------
bool PULineEmitterTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUEmitter* em = static_cast<PUEmitter*>(prop->parent->context);
    PULineEmitter* emitter = static_cast<PULineEmitter*>(em);

    if (prop->name == token[TOKEN_END])
    {
        // Property: end
        if (passValidateProperty(compiler, prop, token[TOKEN_END], VAL_VECTOR3))
        {
            Vec3 val;
            if(getVector3(prop->values.begin(), prop->values.end(), &val))
            {
                emitter->setEnd(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_LINE_EMIT_END])
    {
        // Property: line_em_end (deprecated and replaced by 'end')
        if (passValidateProperty(compiler, prop, token[TOKEN_LINE_EMIT_END], VAL_VECTOR3))
        {
            Vec3 val;
            if(getVector3(prop->values.begin(), prop->values.end(), &val))
            {
                emitter->setEnd(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_MAX_INCREMENT])
    {
        // Property: max_increment
        if (passValidateProperty(compiler, prop, token[TOKEN_MAX_INCREMENT], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                emitter->setMaxIncrement(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_LINE_EMIT_MAX_INCREMENT])
    {
        // Property: line_em_max_increment (deprecated and replaced by 'max_increment')
        if (passValidateProperty(compiler, prop, token[TOKEN_LINE_EMIT_MAX_INCREMENT], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                emitter->setMaxIncrement(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_MIN_INCREMENT])
    {
        // Property: min_increment
        if (passValidateProperty(compiler, prop, token[TOKEN_MIN_INCREMENT], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                emitter->setMinIncrement(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_LINE_EMIT_MIN_INCREMENT])
    {
        // Property: line_em_min_increment (deprecated and replaced by 'min_increment')
        if (passValidateProperty(compiler, prop, token[TOKEN_LINE_EMIT_MIN_INCREMENT], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                emitter->setMinIncrement(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_MAX_DEVIATION])
    {
        // Property: max_deviation
        if (passValidateProperty(compiler, prop, token[TOKEN_MAX_DEVIATION], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                emitter->setMaxDeviation(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_LINE_EMIT_MAX_DEVIATION])
    {
        // Property: line_em_max_deviation (deprecated and replaced by 'max_deviation')
        if (passValidateProperty(compiler, prop, token[TOKEN_LINE_EMIT_MAX_DEVIATION], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                emitter->setMaxDeviation(val);
                return true;
            }
        }
    }

    return false;
}

bool PULineEmitterTranslator::translateChildObject( PUScriptCompiler* /*compiler*/, PUAbstractNode* /*node*/ )
{
    // No objects
    return false;
}

NS_CC_END
