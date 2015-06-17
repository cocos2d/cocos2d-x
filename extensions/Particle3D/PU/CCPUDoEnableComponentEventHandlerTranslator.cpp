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

#include "CCPUDoEnableComponentEventHandlerTranslator.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttribute.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttributeTranslator.h"

NS_CC_BEGIN

PUDoEnableComponentEventHandlerTranslator::PUDoEnableComponentEventHandlerTranslator()
{
}
//-------------------------------------------------------------------------
bool PUDoEnableComponentEventHandlerTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUEventHandler* evt = static_cast<PUEventHandler *>(prop->parent->context);
    PUDoEnableComponentEventHandler* handler = static_cast<PUDoEnableComponentEventHandler*>(evt);

    if (prop->name == token[TOKEN_DOENABLE_COMPONENT])
    {
        // Property: enable_component
        if (passValidatePropertyNumberOfValues(compiler, prop, token[TOKEN_DOENABLE_COMPONENT], 3))
        {
            std::string componentType;
            std::string name;
            bool enabled = true;
            PUAbstractNodeList::const_iterator i = prop->values.begin();
            if(getString(**i, &componentType))
            {
                if (componentType == token[TOKEN_DOENABLE_EMITTER_COMPONENT])
                {
                    handler->setComponentType(CT_EMITTER);
                }
                else if (componentType == token[TOKEN_DOENABLE_AFFECTOR_COMPONENT])
                {
                    handler->setComponentType(CT_AFFECTOR);
                }
                else if (componentType == token[TOKEN_DOENABLE_OBSERVER_COMPONENT])
                {
                    handler->setComponentType(CT_OBSERVER);
                }
                else if (componentType == token[TOKEN_DOENABLE_TECHNIQUE_COMPONENT])
                {
                    handler->setComponentType(CT_TECHNIQUE);
                }
                ++i;
                if(getString(**i, &name))
                {
                    handler->setComponentName(name);
                    ++i;
                    if (getBoolean(**i, &enabled))
                    {
                        handler->setComponentEnabled(enabled);
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool PUDoEnableComponentEventHandlerTranslator::translateChildObject( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    // No objects
    return false;
}

NS_CC_END
