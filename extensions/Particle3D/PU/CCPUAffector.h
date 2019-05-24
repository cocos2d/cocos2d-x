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

#ifndef __CC_PU_PARTICLE_3D_AFFECTOR_H__
#define __CC_PU_PARTICLE_3D_AFFECTOR_H__

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "extensions/Particle3D/CCParticle3DAffector.h"
#include <vector>
#include <string>

NS_CC_BEGIN

struct PUParticle3D;
class PUParticleSystem3D;

class CC_DLL PUAffector : public Particle3DAffector
{
    friend class PUParticleSystem3D;
public:
        /**
        The AffectSpecialisation enumeration is used to specialise the affector even more. This enumeration 
        isn't used by all affectors; in some cases it isn't even applicable.
    */
    enum AffectSpecialisation
    {
        AFSP_DEFAULT,
        AFSP_TTL_INCREASE,
        AFSP_TTL_DECREASE
    };
    
    virtual void notifyStart();
    virtual void notifyStop();
    virtual void notifyPause();
    virtual void notifyResume();
    virtual void notifyRescaled(const Vec3& scale);
    virtual void prepare();
    virtual void unPrepare();
    virtual void preUpdateAffector(float deltaTime);
    virtual void updatePUAffector(PUParticle3D* particle, float delta);
    virtual void postUpdateAffector(float deltaTime);
    virtual void firstParticleUpdate(PUParticle3D *particle, float deltaTime);
    virtual void initParticleForEmission(PUParticle3D* particle);
    void process(PUParticle3D* particle, float delta, bool firstParticle);

    void setLocalPosition(const Vec3 &pos) { _position = pos; };
    const Vec3 getLocalPosition() const { return _position; };
    void setMass(float mass);
    float getMass() const;

    /** Calculate the derived position of the affector.
    @remarks
        Note, that in script, the position is set as localspace, while if the affector is
        emitted, its position is automatically transformed. This function always returns 
        the derived position.
    */
    const Vec3& getDerivedPosition();

    /** Todo
    */
    const AffectSpecialisation& getAffectSpecialisation() const {return _affectSpecialisation;};
    void setAffectSpecialisation(const AffectSpecialisation& affectSpecialisation) {_affectSpecialisation = affectSpecialisation;};

    /** Todo
    */
    const std::string& getAffectorType() const {return _affectorType;};
    void setAffectorType(const std::string& affectorType) {_affectorType = affectorType;};

    /** Add a ParticleEmitter name that excludes Particles emitted by this ParticleEmitter from being
        affected.
    */
    void addEmitterToExclude(const std::string& emitterName);

    /** Remove a ParticleEmitter name that excludes Particles emitted by this ParticleEmitter.
    */
    void removeEmitterToExclude(const std::string& emitterName);

    /** Todo
    */
    const std::string& getName() const {return _name;};
    void setName(const std::string& name) {_name = name;};

    virtual void copyAttributesTo (PUAffector* affector);

CC_CONSTRUCTOR_ACCESS:
    PUAffector();
    virtual ~PUAffector();

protected:

    float calculateAffectSpecialisationFactor (const PUParticle3D* particle);
    
protected:

    Vec3 _position;
        /** Although the scale is on a Particle System level, the affector can also be scaled.
    */
    Vec3 _affectorScale;
        /** Because the public attribute position is sometimes used for both localspace and worldspace
        position, the mDerivedPosition attribute is introduced.
    */
    Vec3 _derivedPosition;

    /** The mAffectSpecialisation is used to specialise the affector. This attribute is comparable with the 
        mAutoDirection of the ParticleEmitter, it is an optional attribute and used in some of the Particle
        Affectors.
    */
    AffectSpecialisation _affectSpecialisation;

        // Type of the affector
    std::string _affectorType;

    std::vector<std::string> _excludedEmitters;

    // Name of the affector (optional)
    std::string _name;

    float _mass;
};

NS_CC_END

#endif
