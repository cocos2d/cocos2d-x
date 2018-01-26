/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2017 Chukong Technologies Inc.
 
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

#include "CCPUBaseForceAffectorTranslator.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttribute.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttributeTranslator.h"

NS_CC_BEGIN

PUBaseForceAffectorTranslator::PUBaseForceAffectorTranslator()
{
}
//-------------------------------------------------------------------------
bool PUBaseForceAffectorTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUAffector* af = static_cast<PUAffector*>(prop->parent->context);
    PUBaseForceAffector* affector = static_cast<PUBaseForceAffector*>(af);

    if (prop->name == token[TOKEN_FORCE_VECTOR])
    {
        if (passValidateProperty(compiler, prop, token[TOKEN_FORCE_VECTOR], VAL_VECTOR3))
        {
            Vec3 val;
            if(getVector3(prop->values.begin(), prop->values.end(), &val))
            {
                affector->setForceVector(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_FORCE_AFF_VECTOR])
    {
        if (passValidateProperty(compiler, prop, token[TOKEN_FORCE_AFF_VECTOR], VAL_VECTOR3))
        {
            Vec3 val;
            if(getVector3(prop->values.begin(), prop->values.end(), &val))
            {
                affector->setForceVector(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_FORCE_APPLICATION])
    {
        if (passValidateProperty(compiler, prop, token[TOKEN_FORCE_APPLICATION], VAL_STRING))
        {
            std::string val;
            if(getString(*prop->values.front(), &val))
            {
                if (val == token[TOKEN_FORCE_ADD])
                {
                    affector->setForceApplication(PUBaseForceAffector::FA_ADD);
                    return true;
                }
                else if (val == token[TOKEN_FORCE_AVERAGE])
                {
                    affector->setForceApplication(PUBaseForceAffector::FA_AVERAGE);
                    return true;
                }
            }
        }
    }
    else if (prop->name == token[TOKEN_FORCE_AFF_APPLICATION])
    {
        if (passValidateProperty(compiler, prop, token[TOKEN_FORCE_AFF_APPLICATION], VAL_STRING))
        {
            std::string val;
            if(getString(*prop->values.front(), &val))
            {
                if (val == token[TOKEN_FORCE_ADD])
                {
                    affector->setForceApplication(PUBaseForceAffector::FA_ADD);
                    return true;
                }
                else if (val == token[TOKEN_FORCE_AVERAGE])
                {
                    affector->setForceApplication(PUBaseForceAffector::FA_AVERAGE);
                    return true;
                }
            }
        }
    }

    return false;
}

bool PUBaseForceAffectorTranslator::translateChildObject( PUScriptCompiler* /*compiler*/, PUAbstractNode* /*node*/ )
{
    // No objects
    return false;
}

NS_CC_END
