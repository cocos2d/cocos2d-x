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

#include "CCPUDoScaleEventHandlerTranslator.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttribute.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttributeTranslator.h"

NS_CC_BEGIN

PUDoScaleEventHandlerTranslator::PUDoScaleEventHandlerTranslator()
{
}
//-------------------------------------------------------------------------
bool PUDoScaleEventHandlerTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUEventHandler* evt = static_cast<PUEventHandler *>(prop->parent->context);
    PUDoScaleEventHandler* handler = static_cast<PUDoScaleEventHandler*>(evt);

    if (prop->name == token[TOKEN_DOSCALE_FRACTION])
    {
        // Property: scale_fraction
        if (passValidateProperty(compiler, prop, token[TOKEN_DOSCALE_FRACTION], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                handler->setScaleFraction(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_DOSCALE_TYPE])
    {
        // Property: scale_type
        if (passValidateProperty(compiler, prop, token[TOKEN_DOSCALE_TYPE], VAL_STRING))
        {
            std::string val;
            if(getString(*prop->values.front(), &val))
            {
                if (val == token[TOKEN_TIME_TO_LIVE] || val == token[TOKEN_DOSCALE_TIME_TO_LIVE])
                {
                    handler->setScaleType(PUDoScaleEventHandler::ST_TIME_TO_LIVE);
                    return true;
                }
                else if (val == token[TOKEN_VELOCITY] || val == token[TOKEN_DOSCALE_VELOCITY])
                {
                    handler->setScaleType(PUDoScaleEventHandler::ST_VELOCITY);
                    return true;
                }
            }
        }
    }

    return false;
}

bool PUDoScaleEventHandlerTranslator::translateChildObject( PUScriptCompiler* /*compiler*/, PUAbstractNode* /*node*/ )
{
    // No objects
    return false;
}

NS_CC_END
