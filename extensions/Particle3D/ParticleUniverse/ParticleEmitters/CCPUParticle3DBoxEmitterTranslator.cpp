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

#include "CCPUParticle3DBoxEmitterTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttribute.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttributeTranslator.h"

NS_CC_BEGIN

PUParticle3DBoxEmitterTranslator::PUParticle3DBoxEmitterTranslator()
{
}
//-------------------------------------------------------------------------
bool PUParticle3DBoxEmitterTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUParticle3DEmitter* em = static_cast<PUParticle3DEmitter*>(prop->parent->context);
    PUParticle3DBoxEmitter* emitter = static_cast<PUParticle3DBoxEmitter*>(em);

    if (prop->name == token[TOKEN_BOX_WIDTH])
    {
        // Property: box_width
        if (passValidateProperty(compiler, prop, token[TOKEN_BOX_WIDTH], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                emitter->setWidth(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_EMITTER_BOX_WIDTH])
    {
        // Property: box_em_width (deprecated and replaced by 'box_width')
        if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_BOX_WIDTH], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                emitter->setWidth(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_BOX_HEIGHT])
    {
        // Property: box_height
        if (passValidateProperty(compiler, prop, token[TOKEN_BOX_HEIGHT], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                emitter->setHeight(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_EMITTER_BOX_HEIGHT])
    {
        // Property: box_em_height (deprecated and replaced by 'box_height')
        if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_BOX_HEIGHT], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                emitter->setHeight(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_BOX_DEPTH])
    {
        // Property: box_depth
        if (passValidateProperty(compiler, prop, token[TOKEN_BOX_DEPTH], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                emitter->setDepth(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_EMITTER_BOX_DEPTH])
    {
        // Property: box_em_depth (deprecated and replaced by 'box_depth')
        if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_BOX_DEPTH], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                emitter->setDepth(val);
                return true;
            }
        }
    }

    return false;
}

bool PUParticle3DBoxEmitterTranslator::translateChildObject( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    // No objects
    return false;
}

NS_CC_END