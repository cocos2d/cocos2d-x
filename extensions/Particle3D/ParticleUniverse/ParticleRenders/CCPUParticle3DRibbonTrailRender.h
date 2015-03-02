/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
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

#ifndef __CC_PU_PARTICLE_3D_RIBBON_TRAIL_RENDER_H__
#define __CC_PU_PARTICLE_3D_RIBBON_TRAIL_RENDER_H__

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "Particle3D/CCParticle3DRender.h"
#include "Particle3D/ParticleUniverse/CCPUParticle3DListener.h"
#include "Particle3D/ParticleUniverse/ParticleRenders/CCPUParticle3DRender.h"
#include "Particle3D/ParticleUniverse/ParticleRenders/CCPUParticle3DRibbonTrail.h"
#include "Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"
#include <vector>

NS_CC_BEGIN

class PUParticle3DRibbonTrailVisualData : public Ref
{
public:

    //Constructor
    PUParticle3DRibbonTrailVisualData (Node* sceneNode, PURibbonTrail* ribbonTrail) : 
        node(sceneNode),
        trail(ribbonTrail),
        addedToTrail(false),
        index(0){};

    Node* node;
    bool addedToTrail;
    PURibbonTrail* trail;
    size_t index;
    virtual void setVisible(bool visible)
    {
        if (visible)
        {
            if (!addedToTrail)
            {
                trail->addNode(node);
                addedToTrail = true;
            }
        }
        else
        {
            if (addedToTrail)
            {
                trail->removeNode(node);
                addedToTrail = false;
            }
        }
    };
};

// particle render for quad
class CC_DLL PUParticle3DRibbonTrailRender : public PUParticle3DRender, public PUParticle3DListener
{
public:

    // Constants
    static const bool DEFAULT_USE_VERTEX_COLOURS;
    static const size_t DEFAULT_MAX_ELEMENTS;
    static const float DEFAULT_LENGTH;
    static const float DEFAULT_WIDTH;
    static const bool DEFAULT_RANDOM_INITIAL_COLOUR;
    static const Vec4 DEFAULT_INITIAL_COLOUR;
    static const Vec4 DEFAULT_COLOUR_CHANGE;

    static PUParticle3DRibbonTrailRender* create(const std::string &texFile = "");

    virtual void notifyRescaled(const Vec3& scale);
    virtual void prepare();
    virtual void unPrepare();
    virtual void updateRender(PUParticle3D *particle, float deltaTime, bool firstParticle);

    virtual void render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem) override;
    virtual void particleEmitted(PUParticleSystem3D* particleSystem, PUParticle3D* particle) override;
    virtual void particleExpired(PUParticleSystem3D* particleSystem, PUParticle3D* particle) override;

    /** Getters and Setters
    */
    bool isUseVertexColors(void) const;
    void setUseVertexColors(bool useVertexColours);

    size_t getMaxChainElements(void) const;
    void setMaxChainElements(size_t maxChainElements);

    float getTrailLength(void) const;
    void setTrailLength(float trailLength);

    float getTrailWidth(void) const;
    void setTrailWidth(float trailWidth);

    bool isRandomInitialColor(void) const;
    void setRandomInitialColor(bool randomInitialColour);

    const Vec4& getInitialColor(void) const;
    void setInitialColor(const Vec4& initialColour);

    const Vec4& getColorChange(void) const;
    void setColorChange(const Vec4& colourChange);

        /** Deletes all ChildSceneNodes en Entities.
    */
    void destroyAll(void);

    virtual PUParticle3DRibbonTrailRender* clone();
    virtual void copyAttributesTo (PUParticle3DRender *render);

CC_CONSTRUCTOR_ACCESS:
    PUParticle3DRibbonTrailRender();
    virtual ~PUParticle3DRibbonTrailRender();

    void updateParticles(const ParticlePool &pool);

protected:

    std::vector<PUParticle3DRibbonTrailVisualData*> _allVisualData;
    std::vector<PUParticle3DRibbonTrailVisualData*> _visualData;
    size_t _quota;
    PURibbonTrail* _trail;
    std::string _ribbonTrailName;
    bool _useVertexColours;
    size_t _maxChainElements;
    float _trailLength;
    float _trailWidth;
    bool _randomInitialColor;
    bool _setLength;
    bool _setWidth;
    Vec4 _initialColor;
    Vec4 _colorChange;
    Node* _childNode;
    std::string _texFile;
};


NS_CC_END
#endif
