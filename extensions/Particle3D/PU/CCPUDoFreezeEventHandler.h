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

#ifndef __CC_PU_PARTICLE_3D_DO_FREEZE_EVENT_HANDLER_H__
#define __CC_PU_PARTICLE_3D_DO_FREEZE_EVENT_HANDLER_H__

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "extensions/Particle3D/PU/CCPUEventHandler.h"
#include <vector>
#include <string>

NS_CC_BEGIN

struct PUParticle3D;
class PUObserver;
class PUParticleSystem3D;

class CC_DLL PUDoFreezeEventHandler : public PUEventHandler
{
public:

    static PUDoFreezeEventHandler* create();

    /** 
    */
    virtual void handle (PUParticleSystem3D* particleSystem, PUParticle3D* particle, float timeElapsed) override;

CC_CONSTRUCTOR_ACCESS:
    PUDoFreezeEventHandler(void) : PUEventHandler()
    {
    }
    virtual ~PUDoFreezeEventHandler(void) {};
};

NS_CC_END

#endif
