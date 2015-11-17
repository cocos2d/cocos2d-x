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

#include "CCPUOnTimeObserverTranslator.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttribute.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttributeTranslator.h"

NS_CC_BEGIN

PUOnTimeObserverTranslator::PUOnTimeObserverTranslator()
{
}
//-------------------------------------------------------------------------
bool PUOnTimeObserverTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUObserver* ob = static_cast<PUObserver*>(prop->parent->context);
    PUOnTimeObserver* observer = static_cast<PUOnTimeObserver*>(ob);

    if (prop->name == token[TOKEN_ONTIME])
    {
        // Property: on_time
        if (passValidatePropertyNumberOfValues(compiler, prop, token[TOKEN_ONTIME], 2))
        {
            std::string compareType;
            float val = 0.0f;
            PUAbstractNodeList::const_iterator i = prop->values.begin();
            if(getString(**i, &compareType))
            {
                if (compareType == token[TOKEN_LESS_THAN])
                {
                    observer->setCompare(CO_LESS_THAN);
                }
                else if (compareType == token[TOKEN_GREATER_THAN])
                {
                    observer->setCompare(CO_GREATER_THAN);
                }
                else if (compareType == token[TOKEN_EQUALS])
                {
                    observer->setCompare(CO_EQUALS);
                }
                ++i;
                if(getFloat(**i, &val))
                {
                    observer->setThreshold(val);
                    return true;
                }
            }
        }
    }
    else if (prop->name == token[TOKEN_SINCE_START_SYSTEM])
    {
        // Property: since_start_system
        if (passValidateProperty(compiler, prop, token[TOKEN_SINCE_START_SYSTEM], VAL_BOOL))
        {
            bool val;
            if(getBoolean(*prop->values.front(), &val))
            {
                observer->setSinceStartSystem(val);
                return true;
            }
        }
    }

    return false;
}

bool PUOnTimeObserverTranslator::translateChildObject( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    // No objects
    return false;
}

NS_CC_END
