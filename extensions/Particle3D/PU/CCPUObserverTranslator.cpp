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

#include "CCPUObserverTranslator.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUObserverManager.h"
#include "extensions/Particle3D/PU/CCPUObserver.h"

NS_CC_BEGIN

PUObserverTranslator::PUObserverTranslator()
:_observer(nullptr)
{
}
//-------------------------------------------------------------------------
void PUObserverTranslator::translate(PUScriptCompiler* compiler, PUAbstractNode *node)
{
    PUObjectAbstractNode* obj = reinterpret_cast<PUObjectAbstractNode*>(node);
    PUObjectAbstractNode* parent = obj->parent ? reinterpret_cast<PUObjectAbstractNode*>(obj->parent) : 0;

    // The name of the obj is the type of the Observer
    // Remark: This can be solved by using a listener, so that obj->values is filled with type + name. Something for later
    std::string type;
    if(!obj->name.empty())
    {
        type = obj->name;
    }
    else
    {
        //compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, obj->file, obj->line);
        return;
    }

    // Get the factory
    //ParticleObserverFactory* particleObserverFactory = ParticleSystemManager::getSingletonPtr()->getObserverFactory(type);
    //if (!particleObserverFactory)
    //{
    //	//compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, obj->file, obj->line);
    //	return;
    //}

    PUScriptTranslator *particleObserverTranlator = PUObserverManager::Instance()->getTranslator(type);
    if (!particleObserverTranlator) return;

    // Create the Observer
    _observer = PUObserverManager::Instance()->createObserver(type);
    if (!_observer)
    {
        //compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, obj->file, obj->line);
        return;
    }
    _observer->setObserverType(type);

    if (parent && parent->context)
    {
        PUParticleSystem3D* system = static_cast<PUParticleSystem3D *>(parent->context);
        system->addObserver(_observer);
    }
    else
    {
        //// It is an alias
        //mObserver->setAliasName(parent->name);
        //ParticleSystemManager::getSingletonPtr()->addAlias(mObserver);
    }

    // The first value is the (optional) name
    std::string name;
    if(!obj->values.empty())
    {
        getString(*obj->values.front(), &name);
        _observer->setName(name);
    }

    // Set it in the context
    obj->context = _observer;

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
                        _observer->setEnabled(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_OBSERVE_PARTICLE_TYPE])
            {
                // Property: observe_particle_type
                if (passValidateProperty(compiler, prop, token[TOKEN_OBSERVE_PARTICLE_TYPE], VAL_STRING))
                {
                    std::string val;
                    if(getString(*prop->values.front(), &val))
                    {
                        if (val == token[TOKEN_VISUAL_PARTICLE])
                        {
                            _observer->setParticleTypeToObserve(PUParticle3D::PT_VISUAL);
                        }
                        else if (val == token[TOKEN_EMITTER_PARTICLE])
                        {
                            _observer->setParticleTypeToObserve(PUParticle3D::PT_EMITTER);
                        }
                        else if (val == token[TOKEN_AFFECTOR_PARTICLE])
                        {
                            _observer->setParticleTypeToObserve(PUParticle3D::PT_AFFECTOR);
                        }
                        else if (val == token[TOKEN_TECHNIQUE_PARTICLE])
                        {
                            _observer->setParticleTypeToObserve(PUParticle3D::PT_TECHNIQUE);
                        }
                        else if (val == token[TOKEN_SYSTEM_PARTICLE])
                        {
                            _observer->setParticleTypeToObserve(PUParticle3D::PT_SYSTEM);
                        }
                    }
                }
            }
            else if (prop->name == token[TOKEN_OBSERVE_INTERVAL])
            {
                // Property: observe_interval
                if (passValidateProperty(compiler, prop, token[TOKEN_OBSERVE_INTERVAL], VAL_REAL))
                {
                    float val;
                    if(getFloat(*prop->values.front(), &val))
                    {
                        _observer->setObserverInterval(val);
                    }
                }
            }
            else if (prop->name == token[TOKEN_OBSERVE_UNTIL_EVENT])
            {
                // Property: observe_until_event
                if (passValidateProperty(compiler, prop, token[TOKEN_OBSERVE_UNTIL_EVENT], VAL_BOOL))
                {
                    bool val;
                    if(getBoolean(*prop->values.front(), &val))
                    {
                        _observer->setObserveUntilEvent(val);
                    }
                }
            }
            else if (particleObserverTranlator->translateChildProperty(compiler, *i))
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
            if (particleObserverTranlator->translateChildObject(compiler, *i))
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
