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

#include "CCPUEventHandlerTranslator.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUEventHandlerManager.h"
#include "extensions/Particle3D/PU/CCPUObserver.h"

NS_CC_BEGIN

PUEventHandlerTranslator::PUEventHandlerTranslator()
:_handler(nullptr)
{
}
//-------------------------------------------------------------------------
void PUEventHandlerTranslator::translate(PUScriptCompiler* compiler, PUAbstractNode *node)
{
    PUObjectAbstractNode* obj = reinterpret_cast<PUObjectAbstractNode*>(node);
    PUObjectAbstractNode* parent = obj->parent ? reinterpret_cast<PUObjectAbstractNode*>(obj->parent) : 0;

    // The name of the obj is the type of the ParticleEventHandler
    // Remark: This can be solved by using a listener, so that obj->values is filled with type + name. Something for later
    std::string type;
    if(!obj->name.empty())
    {
        type = obj->name;
    }
    else
    {
        return;
    }

    PUScriptTranslator *particleEventHandlerTranlator = PUEventHandlerManager::Instance()->getTranslator(type);
    if (!particleEventHandlerTranlator) return;

    // Create the ParticleEventHandler
    //mParticleEventHandler = ParticleSystemManager::getSingletonPtr()->createEventHandler(type);
    _handler = PUEventHandlerManager::Instance()->createEventHandler(type);
    if (!_handler)
    {
        return;
    }

    _handler->setEventHandlerType(type);
    if (parent && parent->context)
    {
        PUObserver* observer = static_cast<PUObserver *>(parent->context);
        observer->addEventHandler(_handler);
    }
    else
    {
        //// It is an alias
        //mParticleEventHandler->setAliasName(parent->name);
        //ParticleSystemManager::getSingletonPtr()->addAlias(mParticleEventHandler);
    }

    // The first value is the (optional) name
    std::string name;
    if(!obj->values.empty())
    {
        getString(*obj->values.front(), &name);
        _handler->setName(name);
    }

    // Set it in the context
    obj->context = _handler;

    // Run through properties
    for(PUAbstractNodeList::iterator i = obj->children.begin(); i != obj->children.end(); ++i)
    {
        // No properties of its own
        if((*i)->type == ANT_PROPERTY)
        {
            PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>((*i));
            if (particleEventHandlerTranlator->translateChildProperty(compiler, *i))
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
            if (particleEventHandlerTranlator->translateChildObject(compiler, *i))
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
