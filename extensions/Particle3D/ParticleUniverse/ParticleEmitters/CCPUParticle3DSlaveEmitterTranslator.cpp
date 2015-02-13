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

#include "CCPUParticle3DSlaveEmitterTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttribute.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttributeTranslator.h"

NS_CC_BEGIN

PUParticle3DSlaveEmitterTranslator::PUParticle3DSlaveEmitterTranslator()
{
}
//-------------------------------------------------------------------------
bool PUParticle3DSlaveEmitterTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUParticle3DEmitter* em = static_cast<PUParticle3DEmitter*>(prop->parent->context);
    PUParticle3DSlaveEmitter* emitter = static_cast<PUParticle3DSlaveEmitter*>(em);

    if (prop->name == token[TOKEN_MASTER_TECHNIQUE])
    {
        // Property: master_technique_name
        if (passValidateProperty(compiler, prop, token[TOKEN_MASTER_TECHNIQUE], VAL_STRING))
        {
            std::string val;
            if(getString(*prop->values.front(), &val))
            {
                emitter->setMasterTechniqueName(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_MASTER_EMITTER])
    {
        // Property: master_emitter_name
        if (passValidateProperty(compiler, prop, token[TOKEN_MASTER_EMITTER], VAL_STRING))
        {
            std::string val;
            if(getString(*prop->values.front(), &val))
            {
                emitter->setMasterEmitterName(val);
                return true;
            }
        }
    }

    return false;
}

bool PUParticle3DSlaveEmitterTranslator::translateChildObject( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    // No objects
    return false;
}

NS_CC_END