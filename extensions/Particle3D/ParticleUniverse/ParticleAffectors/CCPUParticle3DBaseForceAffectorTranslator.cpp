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

#include "CCPUParticle3DBaseForceAffectorTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttribute.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttributeTranslator.h"

NS_CC_BEGIN

PUParticle3DBaseForceAffectorTranslator::PUParticle3DBaseForceAffectorTranslator()
{
}
//-------------------------------------------------------------------------
bool PUParticle3DBaseForceAffectorTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUParticle3DAffector* af = static_cast<PUParticle3DAffector*>(prop->parent->context);
    PUParticle3DBaseForceAffector* affector = static_cast<PUParticle3DBaseForceAffector*>(af);

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
                    affector->setForceApplication(PUParticle3DBaseForceAffector::FA_ADD);
                    return true;
                }
                else if (val == token[TOKEN_FORCE_AVERAGE])
                {
                    affector->setForceApplication(PUParticle3DBaseForceAffector::FA_AVERAGE);
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
                    affector->setForceApplication(PUParticle3DBaseForceAffector::FA_ADD);
                    return true;
                }
                else if (val == token[TOKEN_FORCE_AVERAGE])
                {
                    affector->setForceApplication(PUParticle3DBaseForceAffector::FA_AVERAGE);
                    return true;
                }
            }
        }
    }

    return false;
}

bool PUParticle3DBaseForceAffectorTranslator::translateChildObject( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    // No objects
    return false;
}

NS_CC_END