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

#include "CCPUAffectorTranslator.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUAffectorManager.h"

NS_CC_BEGIN

PUAffectorTranslator::PUAffectorTranslator()
:_affector(nullptr)
{
}
//-------------------------------------------------------------------------
void PUAffectorTranslator::translate(PUScriptCompiler* compiler, PUAbstractNode *node)
{
    PUObjectAbstractNode* obj = reinterpret_cast<PUObjectAbstractNode*>(node);
    PUObjectAbstractNode* parent = obj->parent ? reinterpret_cast<PUObjectAbstractNode*>(obj->parent) : 0;
    
    // The name of the obj is the type of the affector
    // Remark: This can be solved by using a listener, so that obj->values is filled with type + name. Something for later
    std::string type;
    if(!obj->name.empty())
    {
        type = obj->name;
    }
    
    //// Get the factory
    //ParticleAffectorFactory* particleAffectorFactory = ParticleSystemManager::getSingletonPtr()->getAffectorFactory(type);
    //if (!particleAffectorFactory)
    //{
    //    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, obj->file, obj->line);
    //    return;
    //}
    PUScriptTranslator *particleAffectorTranlator = PUAffectorManager::Instance()->getTranslator(type);
    if (!particleAffectorTranlator) return;
    //// Create the affector
    //mAffector = ParticleSystemManager::getSingletonPtr()->createAffector(type);
    //if (!mAffector)
    //{
    //    compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, obj->file, obj->line);
    //    return;
    //}
    _affector = PUAffectorManager::Instance()->createAffector(type);
    if (!_affector) return;
    _affector->setAffectorType(type);

    if (parent && parent->context)
    {
        PUParticleSystem3D* system = static_cast<PUParticleSystem3D*>(parent->context);
        system->addAffector(_affector);
    }
    
    // The first value is the (optional) name
    std::string name;
    if(!obj->values.empty())
    {
        getString(*obj->values.front(), &name);
        _affector->setName(name);
    }
    
    // Set it in the context
    obj->context = _affector;
    
    // Run through properties
    for(PUAbstractNodeList::iterator i = obj->children.begin(); i != obj->children.end(); ++i)
    {
        if((*i)->type == ANT_PROPERTY)
        {
            PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>((*i));
            if (prop->name == token[TOKEN_ENABLED])
            {
                // Property: enabled
                if (passValidateProperty(compiler, prop, token[TOKEN_ENABLED], VAL_BOOL))
                {
                    bool val;
                    if(getBoolean(*prop->values.front(), &val))
                    {
                        _affector->setEnabled(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_POSITION])
            {
                // Property: position
                if (passValidateProperty(compiler, prop, token[TOKEN_POSITION], VAL_VECTOR3))
                {
                    Vec3 val;
                    if(getVector3(prop->values.begin(), prop->values.end(), &val))
                    {
                        //mAffector->position = val;
                        //mAffector->originalPosition = val;
                        _affector->setLocalPosition(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_AFFECTOR_MASS])
            {
                if (passValidateProperty(compiler, prop, token[TOKEN_AFFECTOR_MASS], VAL_REAL))
                {
                    float val = 0.0f;
                    if(getFloat(*prop->values.front(), &val))
                    {
                        _affector->setMass(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_AFFECTOR_SPECIALISATION])
            {
                if (passValidateProperty(compiler, prop, token[TOKEN_AFFECTOR_SPECIALISATION], VAL_STRING))
                {
                    std::string val;
                    if(getString(*prop->values.front(), &val))
                    {
                        if (val == token[TOKEN_AFFECTOR_SPEC_DEFAULT])
                        {
                            _affector->setAffectSpecialisation(PUAffector::AFSP_DEFAULT);
                        }
                        else if (val == token[TOKEN_AFFECTOR_SPEC_TTL_INCREASE])
                        {
                            _affector->setAffectSpecialisation(PUAffector::AFSP_TTL_INCREASE);
                        }
                        else if (val == token[TOKEN_AFFECTOR_SPEC_TTL_DECREASE])
                        {
                            _affector->setAffectSpecialisation(PUAffector::AFSP_TTL_DECREASE);
                        }
                    }
                }
            }
            else if (prop->name == token[TOKEN_AFFECTOR_EXCLUDE_EMITTER])
            {
                if (passValidatePropertyNoValues(compiler, prop, token[TOKEN_AFFECTOR_EXCLUDE_EMITTER]))
                {
                    for(PUAbstractNodeList::iterator j = prop->values.begin(); j != prop->values.end(); ++j)
                    {
                        std::string val;
                        if(getString(**j, &val))
                        {
                            _affector->addEmitterToExclude(val);
                        }
                    }
                }
            }
            else if (particleAffectorTranlator->translateChildProperty(compiler, *i))
            {
                // Parsed the property by another translator; do nothing
            }
            else
            {
                errorUnexpectedProperty(compiler, prop);
            }
        }
        else if((*i)->type == ANT_OBJECT)
        {
            if (particleAffectorTranlator->translateChildObject(compiler, *i))
            {
                // Parsed the object by another translator; do nothing
            }
            else
            {
                processNode(compiler, *i);
            }
        }
        else
        {
            errorUnexpectedToken(compiler, *i);
        }
    }
}

NS_CC_END