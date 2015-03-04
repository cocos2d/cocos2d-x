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

#include "extensions/Particle3D/ParticleUniverse/ParticleEventHandlers/CCPUParticle3DEventHandlerManager.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleEventHandlers/CCPUParticle3DDoAffectorEventHandler.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleEventHandlers/CCPUParticle3DDoEnableComponentEventHandler.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleEventHandlers/CCPUParticle3DDoExpireEventHandler.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleEventHandlers/CCPUParticle3DDoFreezeEventHandler.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleEventHandlers/CCPUParticle3DDoPlacementParticleEventHandler.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleEventHandlers/CCPUParticle3DDoScaleEventHandler.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleEventHandlers/CCPUParticle3DDoStopSystemEventHandler.h"

NS_CC_BEGIN
PUParticle3DEventHandlerManager::PUParticle3DEventHandlerManager()
{
    
}

PUParticle3DEventHandlerManager::~PUParticle3DEventHandlerManager()
{
    
}

PUParticle3DEventHandlerManager* PUParticle3DEventHandlerManager::Instance()
{
    static PUParticle3DEventHandlerManager pem;
    return &pem;
}

PUScriptTranslator* PUParticle3DEventHandlerManager::getTranslator( const std::string &type )
{
    if (type == "DoAffector"){
        return &_doAffectorEventHandlerTranslator;
    }else if (type == "DoEnableComponent"){
        return &_doEnableComponentEventHandlerTranslator;
    }else if (type == "DoExpire"){
        return &_doExpireEventHandlerTranslator;
    }else if (type == "DoFreeze"){
        return &_doFreezeEventHandlerTranslator;
    }else if (type == "DoPlacementParticle"){
        return &_doPlacementParticleEventHandlerTranslator;
    }else if (type == "DoScale"){
        return &_doScaleEventHandlerTranslator;
    }else if (type == "DoStopSystem"){
        return &_doStopSystemEventHandlerTranslator;
    }
    return nullptr;
}

PUParticle3DEventHandler* PUParticle3DEventHandlerManager::createEventHandler( const std::string &type )
{
    if (type == "DoAffector"){
        return PUParticle3DDoAffectorEventHandler::create();
    }else if (type == "DoEnableComponent"){
        return PUParticle3DDoEnableComponentEventHandler::create();
    }else if (type == "DoExpire"){
        return PUParticle3DDoExpireEventHandler::create();
    }else if (type == "DoFreeze"){
        return PUParticle3DDoFreezeEventHandler::create();
    }else if (type == "DoPlacementParticle"){
        return PUParticle3DDoPlacementParticleEventHandler::create();
    }else if (type == "DoScale"){
        return PUParticle3DDoScaleEventHandler::create();
    }else if (type == "DoStopSystem"){
        return PUParticle3DDoStopSystemEventHandler::create();
    }
    return nullptr;
}

NS_CC_END
