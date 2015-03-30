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
#ifndef __CC_PU_PARTICLE_3D_EVENT_HANDLER_MANAGER_H__
#define __CC_PU_PARTICLE_3D_EVENT_HANDLER_MANAGER_H__

#include "base/CCRef.h"
#include "extensions/Particle3D/PU/CCPUScriptTranslator.h"
#include "extensions/Particle3D/PU/CCPUEventHandler.h"
#include "extensions/Particle3D/PU/CCPUDoAffectorEventHandlerTranslator.h"
#include "extensions/Particle3D/PU/CCPUDoEnableComponentEventHandlerTranslator.h"
#include "extensions/Particle3D/PU/CCPUDoExpireEventHandlerTranslator.h"
#include "extensions/Particle3D/PU/CCPUDoFreezeEventHandlerTranslator.h"
#include "extensions/Particle3D/PU/CCPUDoPlacementParticleEventHandlerTranslator.h"
#include "extensions/Particle3D/PU/CCPUDoScaleEventHandlerTranslator.h"
#include "extensions/Particle3D/PU/CCPUDoStopSystemEventHandlerTranslator.h"


NS_CC_BEGIN
class PUEventHandlerManager
{
public:
    
    static PUEventHandlerManager* Instance();

    /**
     */
    PUScriptTranslator* getTranslator(const std::string &type);
    PUEventHandler* createEventHandler(const std::string &type);

    
CC_CONSTRUCTOR_ACCESS:

    PUEventHandlerManager();
    ~PUEventHandlerManager();

protected:

    PUDoAffectorEventHandlerTranslator _doAffectorEventHandlerTranslator;
    PUDoEnableComponentEventHandlerTranslator _doEnableComponentEventHandlerTranslator;
    PUDoExpireEventHandlerTranslator _doExpireEventHandlerTranslator;
    PUDoFreezeEventHandlerTranslator _doFreezeEventHandlerTranslator;
    PUDoPlacementParticleEventHandlerTranslator _doPlacementParticleEventHandlerTranslator;
    PUDoScaleEventHandlerTranslator _doScaleEventHandlerTranslator;
    PUDoStopSystemEventHandlerTranslator _doStopSystemEventHandlerTranslator;

};

NS_CC_END


#endif 
