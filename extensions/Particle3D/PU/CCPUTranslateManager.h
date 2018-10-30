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

#ifndef __CC_PU_PARTICLE_3D_TRANSLATE_MANAGER_H__
#define __CC_PU_PARTICLE_3D_TRANSLATE_MANAGER_H__

#include "base/CCRef.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3DTranslator.h"
#include "extensions/Particle3D/PU/CCPUTechniqueTranslator.h"
#include "extensions/Particle3D/PU/CCPURendererTranslator.h"
#include "extensions/Particle3D/PU/CCPUMaterialTranslator.h"
#include "extensions/Particle3D/PU/CCPUEmitterTranslator.h"
#include "extensions/Particle3D/PU/CCPUAffectorTranslator.h"
#include "extensions/Particle3D/PU/CCPUEventHandlerTranslator.h"
#include "extensions/Particle3D/PU/CCPUObserverTranslator.h"
#include "extensions/Particle3D/PU/CCPUBehaviourTranslator.h"

NS_CC_BEGIN
class PUMaterialCache;
class PUTranslateManager
{
private:
        PUParticleSystem3DTranslator _systemTranslator;
        PUTechniqueTranslator _techniqueTranslator;
        //AliasTranslator mAliasTranslator;
        //TechniqueTranslator mTechniqueTranslator;
        PURendererTranslator _rendererTranslator;
        PUEmitterTranslator _emitterTranslator;
        PUAffectorTranslator _affectorTranslator;
        CCPUMaterialTranslator _materialTranslator;
        PUEventHandlerTranslator _eventHandlerTranslator;
        PUObserverTranslator _observerTranslator;
        PUBehaviourTranslator _behaviourTranslator;
        //EmitterTranslator mEmitterTranslator;
        //AffectorTranslator mAffectorTranslator;
        //BehaviourTranslator mBehaviourTranslator;
        //ObserverTranslator mObserverTranslator;
        //ParticleEventHandlerTranslator mParticleEventHandlerTranslator;
        //ExternTranslator mExternTranslator;

public:
    
    static PUTranslateManager* Instance();
    /**
     */
    //virtual size_t getNumTranslators(void) const;
    
    /**
     */
    void translateParticleSystem(PUParticleSystem3D *pu, const PUAbstractNodeList *alist);
    void translateMaterialSystem(PUMaterialCache *ms, const PUAbstractNodeList *alist);
    virtual PUScriptTranslator* getTranslator(PUAbstractNode *node);

    
CC_CONSTRUCTOR_ACCESS:
    PUTranslateManager();
    virtual ~PUTranslateManager();
};

NS_CC_END


#endif /* defined(__cocos2d_libs__CCParticle3DTranslateManager__) */
