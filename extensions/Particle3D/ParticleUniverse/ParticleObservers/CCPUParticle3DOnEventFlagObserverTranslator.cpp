/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
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

#include "CCPUParticle3DOnEventFlagObserverTranslator.h"
#include "Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"
#include "Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttribute.h"
#include "Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttributeTranslator.h"

NS_CC_BEGIN

PUParticle3DOnEventFlagObserverTranslator::PUParticle3DOnEventFlagObserverTranslator()
{
}
//-------------------------------------------------------------------------
bool PUParticle3DOnEventFlagObserverTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUParticle3DObserver* ob = static_cast<PUParticle3DObserver*>(prop->parent->context);
    PUParticle3DOnEventFlagObserver* observer = static_cast<PUParticle3DOnEventFlagObserver*>(ob);

    if (prop->name == token[TOKEN_ONEVENT_FLAG])
    {
        // Property: event_flag
        if (passValidateProperty(compiler, prop, token[TOKEN_ONEVENT_FLAG], VAL_UINT))
        {
            unsigned int val = 0;
            if(getUInt(*prop->values.front(), &val))
            {
                observer->setEventFlag(val);
                return true;
            }
        }
    }

    return false;
}

bool PUParticle3DOnEventFlagObserverTranslator::translateChildObject( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    // No objects
    return false;
}

NS_CC_END