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

#ifndef __CC_PU_PARTICLE_3D_BEAM_RENDER_H__
#define __CC_PU_PARTICLE_3D_BEAM_RENDER_H__

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "extensions/Particle3D/CCParticle3DRender.h"
#include "extensions/Particle3D/PU/CCPUListener.h"
#include "extensions/Particle3D/PU/CCPUBillboardChain.h"
#include "extensions/Particle3D/PU/CCPURender.h"
#include <vector>

NS_CC_BEGIN

class PUParticle3DBeamVisualData : public Ref
{
    public:
        PUParticle3DBeamVisualData (size_t index, PUBillboardChain* bbChain) :
            chainIndex(index),
            timeSinceLastUpdate(0.0f),
            billboardChain(bbChain){};

        // Set the chain visible or invisible (PU 1.4)
        void setVisible(bool visible){/* No implementation */};

        /** The is no decent way to make the individual chains/elements invisible. The width of each element is set to 0 to make it invisible.
            PU 1.4
        */
        void setVisible(bool visible, float width)
        {
            if (!billboardChain)
                return;

            // Set width to 0 if not visible
            width = visible ? width : 0;
                
            size_t max = billboardChain->getMaxChainElements();
            PUBillboardChain::Element element;
            for (size_t j = 0; j < max; j++)
            {
                element = billboardChain->getChainElement(chainIndex, j);
                element.width = width;
                billboardChain->updateChainElement(chainIndex, j, element);
            }
        }

        // Index of the chain
        size_t chainIndex;
        Vec3 half[100];
        Vec3 destinationHalf[100];
        float timeSinceLastUpdate;
        PUBillboardChain* billboardChain;
};

// particle render for quad
class CC_DLL PUBeamRender : public PURender, public PUListener
{
public:

    // Constants
    static const bool DEFAULT_USE_VERTEX_COLOURS;
    static const size_t DEFAULT_MAX_ELEMENTS;
    static const float DEFAULT_UPDATE_INTERVAL;
    static const float DEFAULT_DEVIATION;
    static const size_t DEFAULT_NUMBER_OF_SEGMENTS;
    static const PUBillboardChain::TexCoordDirection DEFAULT_TEXTURE_DIRECTION;

    static PUBeamRender* create(const std::string &texFile = "");

    virtual void prepare() override;
    virtual void unPrepare() override;
    virtual void updateRender(PUParticle3D *particle, float deltaTime, bool firstParticle) override;

    virtual void render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem) override;
    virtual void particleEmitted(PUParticleSystem3D* particleSystem, PUParticle3D* particle) override;
    virtual void particleExpired(PUParticleSystem3D* particleSystem, PUParticle3D* particle) override;

        /** Getters and Setters
    */
    bool isUseVertexColours(void) const;
    void setUseVertexColours(bool useVertexColours);

    size_t getMaxChainElements(void) const;
    void setMaxChainElements(size_t maxChainElements);

    float getUpdateInterval(void) const;
    void setUpdateInterval(float updateInterval);

    float getDeviation(void) const;
    void setDeviation(float deviation);

    size_t getNumberOfSegments(void) const;
    void setNumberOfSegments(size_t numberOfSegments);

    bool isJump(void) const;
    void setJump(bool jump);

    PUBillboardChain::TexCoordDirection getTexCoordDirection(void) const;
    void setTexCoordDirection(PUBillboardChain::TexCoordDirection texCoordDirection);

    /** Destroys the BillboarChain
    */
    void destroyAll(void);

    virtual PUBeamRender* clone() override;
    void copyAttributesTo(PUBeamRender *render);

CC_CONSTRUCTOR_ACCESS:
    PUBeamRender();
    virtual ~PUBeamRender();

protected:

    std::string _texFile;
    std::string _billboardChainName;
    PUBillboardChain* _billboardChain;
    std::vector<PUParticle3DBeamVisualData*> _allVisualData;
    std::vector<PUParticle3DBeamVisualData*> _visualData;
    size_t _quota;
    bool _useVertexColours;
    size_t _maxChainElements;
    float _updateInterval;
    float _deviation;
    size_t _numberOfSegments;
    bool _jump;
    PUBillboardChain::TexCoordDirection _texCoordDirection;
};


NS_CC_END
#endif
