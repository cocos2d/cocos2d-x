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

#include "CCPUTranslateManager.h"
#include "extensions/Particle3D/PU/CCPUScriptCompiler.h"

NS_CC_BEGIN
PUTranslateManager::PUTranslateManager()
{
    
}

PUTranslateManager::~PUTranslateManager()
{
    
}



PUScriptTranslator* PUTranslateManager::getTranslator(PUAbstractNode *node)
{
    PUScriptTranslator* translator = 0;
   
    
    //add//
    
    if(node->type == ANT_OBJECT)
    {
        PUObjectAbstractNode* obj = reinterpret_cast<PUObjectAbstractNode*>(node);
        PUObjectAbstractNode* parent = obj->parent ? reinterpret_cast<PUObjectAbstractNode*>(obj->parent) : 0;
        if(obj->cls == token[TOKEN_SYSTEM])
        {
            // Parse Particle System
            translator = &_systemTranslator;
        }
        else if(obj->cls == token[TOKEN_MATERIAL])
        {
            // Parse Particle System
            translator = &_materialTranslator;
        }
        //else if(obj->cls == token[TOKEN_ALIAS])
        //{
        //    // Parse the Alias
        //    translator = &mAliasTranslator;
        //}
        else if(obj->cls == token[TOKEN_TECHNIQUE] && parent && (parent->cls == token[TOKEN_SYSTEM] || parent->cls == token[TOKEN_ALIAS]))
        {
            // Parse Particle Technique
            translator = &_techniqueTranslator;
        }
        else if(obj->cls == token[TOKEN_RENDERER] && parent && (parent->cls == token[TOKEN_TECHNIQUE] || parent->cls == token[TOKEN_ALIAS]))
        {
            // Parse Particle Renderer
            translator = &_rendererTranslator;
        }
        else if(obj->cls == token[TOKEN_EMITTER] && parent && (parent->cls == token[TOKEN_TECHNIQUE] || parent->cls == token[TOKEN_ALIAS]))
        {
            // Parse Particle Emitter
            translator = &_emitterTranslator;
        }
        else if(obj->cls == token[TOKEN_AFFECTOR] && parent && (parent->cls == token[TOKEN_TECHNIQUE] || parent->cls == token[TOKEN_ALIAS]))
        {
            // Parse Particle Affector
            translator = &_affectorTranslator;
        }
        else if(obj->cls == token[TOKEN_BEHAVIOUR] && parent && (parent->cls == token[TOKEN_TECHNIQUE] || parent->cls == token[TOKEN_ALIAS]))
        {
            // Parse Particle Behaviour
            translator = &_behaviourTranslator;
        }
        else if(obj->cls == token[TOKEN_OBSERVER] && parent && (parent->cls == token[TOKEN_TECHNIQUE] || parent->cls == token[TOKEN_ALIAS]))
        {
            // Parse Particle Observer
            translator = &_observerTranslator;
        }
        else if(obj->cls == token[TOKEN_HANDLER] && parent && (parent->cls == token[TOKEN_OBSERVER] || parent->cls == token[TOKEN_ALIAS]))
        {
            // Parse Particle Event Handler
            translator = &_eventHandlerTranslator;
        }
        //else if(obj->cls == token[TOKEN_EXTERN] && parent && (parent->cls == token[TOKEN_TECHNIQUE] || parent->cls == token[TOKEN_ALIAS]))
        //{
        //    // Parse Extern
        //    translator = &mExternTranslator;
        //}
    }
    
    return translator;
}

PUTranslateManager* PUTranslateManager::Instance()
{
    static PUTranslateManager ptm;
    return &ptm;
}

void PUTranslateManager::translateParticleSystem( PUParticleSystem3D *pu, const PUAbstractNodeList *alist )
{
    for(PUAbstractNodeList::const_iterator i = alist->begin(); i != alist->end(); ++i)
    {
        _systemTranslator.setParticleSystem3D(pu);
        _systemTranslator.translate(PUScriptCompiler::Instance(), *i);
    }
}

void PUTranslateManager::translateMaterialSystem( PUMaterialCache *ms, const PUAbstractNodeList *alist )
{
    for(PUAbstractNodeList::const_iterator i = alist->begin(); i != alist->end(); ++i)
    {
        _materialTranslator.setMaterialSystem(ms);
        _materialTranslator.translate(PUScriptCompiler::Instance(), *i);
    }
}


NS_CC_END