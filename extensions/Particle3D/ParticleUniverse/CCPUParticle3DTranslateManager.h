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

#ifndef __CC_PU_PARTICLE_3D_TRANSLATE_MANAGER_H__
#define __CC_PU_PARTICLE_3D_TRANSLATE_MANAGER_H__

#include "base/CCRef.h"
//#include "extensions/Particle3D/ParticleUniverse/Script/Translater/CCParticle3DSystemTranslator.h"
//#include "extensions/Particle3D/ParticleUniverse/Script/Translater/CCAliasTranslator.h"
//#include "extensions/Particle3D/ParticleUniverse/Script/Translater/CCParticle3DTechniqueTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3DTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DTechniqueTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DRendererTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DMaterialTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DEmitterTranslator.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DAffectorTranslator.h"

using namespace std;
NS_CC_BEGIN
class PUParticle3DMaterialCache;
class PUParticle3DTranslateManager
{
private:
        PUParticleSystem3DTranslator _systemTranslator;
        PUParticle3DTechniqueTranslator _techniqueTranslator;
        //AliasTranslator mAliasTranslator;
        //TechniqueTranslator mTechniqueTranslator;
        PUParticle3DRendererTranslator _rendererTranslator;
        PUParticle3DEmitterTranslator _emitterTranslator;
        PUParticle3DAffectorTranslator _affectorTranslator;
        PUParticle3DMaterialTranslator _materialTranslator;
        //EmitterTranslator mEmitterTranslator;
        //AffectorTranslator mAffectorTranslator;
        //BehaviourTranslator mBehaviourTranslator;
        //ObserverTranslator mObserverTranslator;
        //ParticleEventHandlerTranslator mParticleEventHandlerTranslator;
        //ExternTranslator mExternTranslator;
    

public:
    
    static PUParticle3DTranslateManager* Instance();
    /**
     */
    //virtual size_t getNumTranslators(void) const;
    
    /**
     */
    void translateParticleSystem(PUParticleSystem3D *pu, const PUAbstractNodeList *alist);
    void translateMaterialSystem(PUParticle3DMaterialCache *ms, const PUAbstractNodeList *alist);
    virtual PUScriptTranslator* getTranslator(PUAbstractNode *node);

    
CC_CONSTRUCTOR_ACCESS:
    PUParticle3DTranslateManager();
    ~PUParticle3DTranslateManager();
};

NS_CC_END


#endif /* defined(__cocos2d_libs__CCParticle3DTranslateManager__) */
