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

#include "CCPUDoAffectorEventHandlerTranslator.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttribute.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttributeTranslator.h"

NS_CC_BEGIN

PUDoAffectorEventHandlerTranslator::PUDoAffectorEventHandlerTranslator()
{
}
//-------------------------------------------------------------------------
bool PUDoAffectorEventHandlerTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUEventHandler* evt = static_cast<PUEventHandler *>(prop->parent->context);
    PUDoAffectorEventHandler* handler = static_cast<PUDoAffectorEventHandler*>(evt);

    if (prop->name == token[TOKEN_FORCE_AFFECTOR])
    {
        // Property: force_affector
        if (passValidateProperty(compiler, prop, token[TOKEN_FORCE_AFFECTOR], VAL_STRING))
        {
            std::string val;
            if(getString(*prop->values.front(), &val))
            {
                handler->setAffectorName(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_FORCE_AFFECTOR_PRE_POST])
    {
        // Property: pre_post
        if (passValidateProperty(compiler, prop, token[TOKEN_FORCE_AFFECTOR_PRE_POST], VAL_BOOL))
        {
            bool val;
            if(getBoolean(*prop->values.front(), &val))
            {
                handler->setPrePost(val);
                return true;
            }
        }
    }

    return false;
}

bool PUDoAffectorEventHandlerTranslator::translateChildObject( PUScriptCompiler* /*compiler*/, PUAbstractNode* /*node*/ )
{
    // No objects
    return false;
}

NS_CC_END
