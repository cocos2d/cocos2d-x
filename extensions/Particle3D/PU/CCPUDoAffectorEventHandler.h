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

#ifndef __CC_PU_PARTICLE_3D_DO_AFFECTOR_EVENT_HANDLER_H__
#define __CC_PU_PARTICLE_3D_DO_AFFECTOR_EVENT_HANDLER_H__

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "extensions/Particle3D/PU/CCPUEventHandler.h"
#include <vector>
#include <string>

NS_CC_BEGIN

struct PUParticle3D;
class PUObserver;
class PUParticleSystem3D;

class CC_DLL PUDoAffectorEventHandler : public PUEventHandler
{
public:
    // Constants
    static const bool DEFAULT_PRE_POST;

    static PUDoAffectorEventHandler* create();

    /** Get the indication whether pre- and postprocessing must be done.
    */
    bool getPrePost() const {return _prePost;};

    /** Set the indication whether pre- and postprocessing must be done.
    */
    void setPrePost(const bool prePost){_prePost = prePost;};

    /** Get the name of the affector that must be enabled or disabled.
    */
    const std::string& getAffectorName(void) const {return _affectorName;};

    /** Set the name of the affector.
    */
    void setAffectorName(const std::string& affectorName){_affectorName = affectorName;};

    /** If the _handle() function of this class is invoked (by an Observer), it searches the 
        ParticleAffector defined by the its name. 
        The ParticleAffector is either part of the ParticleTechnique in which the 
        DoAffectorEventHandler is defined, or if the Affector is not found, other 
        ParticleTechniques are searched.
    */
    virtual void handle (PUParticleSystem3D* particleSystem, PUParticle3D* particle, float timeElapsed) override;

    virtual void copyAttributesTo (PUEventHandler* eventHandler) override;

CC_CONSTRUCTOR_ACCESS:
    PUDoAffectorEventHandler(void);
    virtual ~PUDoAffectorEventHandler(void) {};

protected:
    // Identifies the name of affector
    std::string _affectorName;

    // Determines whether the pre- and post processing activities must be executed also
    bool _prePost;
};

NS_CC_END

#endif
