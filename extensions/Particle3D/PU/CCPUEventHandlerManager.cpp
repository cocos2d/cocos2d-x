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

#include "extensions/Particle3D/PU/CCPUEventHandlerManager.h"
#include "extensions/Particle3D/PU/CCPUDoAffectorEventHandler.h"
#include "extensions/Particle3D/PU/CCPUDoEnableComponentEventHandler.h"
#include "extensions/Particle3D/PU/CCPUDoExpireEventHandler.h"
#include "extensions/Particle3D/PU/CCPUDoFreezeEventHandler.h"
#include "extensions/Particle3D/PU/CCPUDoPlacementParticleEventHandler.h"
#include "extensions/Particle3D/PU/CCPUDoScaleEventHandler.h"
#include "extensions/Particle3D/PU/CCPUDoStopSystemEventHandler.h"

NS_CC_BEGIN
PUEventHandlerManager::PUEventHandlerManager()
{
    
}

PUEventHandlerManager::~PUEventHandlerManager()
{
    
}

PUEventHandlerManager* PUEventHandlerManager::Instance()
{
    static PUEventHandlerManager pem;
    return &pem;
}

PUScriptTranslator* PUEventHandlerManager::getTranslator( const std::string &type )
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

PUEventHandler* PUEventHandlerManager::createEventHandler( const std::string &type )
{
    if (type == "DoAffector"){
        return PUDoAffectorEventHandler::create();
    }else if (type == "DoEnableComponent"){
        return PUDoEnableComponentEventHandler::create();
    }else if (type == "DoExpire"){
        return PUDoExpireEventHandler::create();
    }else if (type == "DoFreeze"){
        return PUDoFreezeEventHandler::create();
    }else if (type == "DoPlacementParticle"){
        return PUDoPlacementParticleEventHandler::create();
    }else if (type == "DoScale"){
        return PUDoScaleEventHandler::create();
    }else if (type == "DoStopSystem"){
        return PUDoStopSystemEventHandler::create();
    }
    return nullptr;
}

NS_CC_END
