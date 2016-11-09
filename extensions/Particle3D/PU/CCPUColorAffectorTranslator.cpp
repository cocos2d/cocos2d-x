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

#include "CCPUColorAffectorTranslator.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttribute.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttributeTranslator.h"

NS_CC_BEGIN

PUColorAffectorTranslator::PUColorAffectorTranslator()
{
}
//-------------------------------------------------------------------------
bool PUColorAffectorTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUAffector* af = static_cast<PUAffector*>(prop->parent->context);
    PUColorAffector* affector = static_cast<PUColorAffector*>(af);

    if (prop->name == token[TOKEN_TIME_COLOUR] || prop->name == token[TOKEN_COLOUR_TIME_COLOUR])
    {
        if (passValidatePropertyNumberOfValuesRange(compiler, prop, token[TOKEN_TIME_COLOUR], 4, 5))
        {
            int n = 0;
            float time;
            Vec4 colour;
            PUAbstractNodeList::const_iterator i = prop->values.begin();
            PUAbstractNodeList::const_iterator end = prop->values.end();
            while(i != end)
            {
                float v = 0;
                if(getFloat(**i, &v))
                {
                    switch(n)
                    {
                    case 0:
                        time = v;
                        break;
                    case 1:
                        colour.x = v;
                        break;
                    case 2:
                        colour.y = v;
                        break;
                    case 3:
                        colour.z = v;
                        break;
                    case 4:
                        colour.w = v;
                        break;
                    }
                }
                ++n;
                ++i;
            }
            affector->addColor(time, colour);
            return true;
        }
    }
    else if (prop->name == token[TOKEN_COLOUR_OPERATION])
    {
        if (passValidateProperty(compiler, prop, token[TOKEN_COLOUR_OPERATION], VAL_STRING))
        {
            std::string val;
            if(getString(*prop->values.front(), &val))
            {
                if (val == token[TOKEN_COLOUR_SET])
                {
                    affector->setColorOperation(PUColorAffector::CAO_SET);
                    return true;
                }
                else if (val == token[TOKEN_COLOUR_MULTIPLY])
                {
                    affector->setColorOperation(PUColorAffector::CAO_MULTIPLY);
                    return true;
                }
            }
        }
    }

    return false;
}

bool PUColorAffectorTranslator::translateChildObject( PUScriptCompiler* /*compiler*/, PUAbstractNode* /*node*/ )
{
    // No objects
    return false;
}

NS_CC_END
