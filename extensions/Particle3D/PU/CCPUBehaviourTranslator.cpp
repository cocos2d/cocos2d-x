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

#include "CCPUBehaviourTranslator.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUBehaviourManager.h"

NS_CC_BEGIN

PUBehaviourTranslator::PUBehaviourTranslator()
:_behaviour(nullptr)
{
}
//-------------------------------------------------------------------------
void PUBehaviourTranslator::translate(PUScriptCompiler* compiler, PUAbstractNode *node)
{
    PUObjectAbstractNode* obj = reinterpret_cast<PUObjectAbstractNode*>(node);
    PUObjectAbstractNode* parent = obj->parent ? reinterpret_cast<PUObjectAbstractNode*>(obj->parent) : 0;

    // The name of the obj is the type of the Behaviour
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

    //// Get the factory
    //ParticleBehaviourFactory* behaviourFactory = ParticleSystemManager::getSingletonPtr()->getBehaviourFactory(type);
    //if (!behaviourFactory)
    //{
    //	//compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, obj->file, obj->line);
    //	return;
    //}

    PUScriptTranslator *particleBehaviourTranlator = PUBehaviourManager::Instance()->getTranslator(type);
    if (!particleBehaviourTranlator) return;

    // Create the Behaviour
    _behaviour = PUBehaviourManager::Instance()->createBehaviour(type);
    if (!_behaviour)
    {
        //compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, obj->file, obj->line);
        return;
    }

    _behaviour->setBehaviourType(type);
    if (parent && parent->context)
    {
        PUParticleSystem3D* system = static_cast<PUParticleSystem3D*>(parent->context);
        system->addBehaviourTemplate(_behaviour);
    }
    else
    {
        //// It is an alias
        //_behaviour->setAliasName(parent->name);
        //ParticleSystemManager::getSingletonPtr()->addAlias(mBehaviour);
    }

    // Set it in the context
    obj->context = _behaviour;

    // Run through properties
    for(PUAbstractNodeList::iterator i = obj->children.begin(); i != obj->children.end(); ++i)
    {
        // No properties of its own
        if((*i)->type == ANT_PROPERTY)
        {
            PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>((*i));
            if (particleBehaviourTranlator->translateChildProperty(compiler, *i))
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
            if (particleBehaviourTranlator->translateChildObject(compiler, *i))
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
