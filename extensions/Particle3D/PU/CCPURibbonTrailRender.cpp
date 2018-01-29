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

#include "extensions/Particle3D/CCParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPURibbonTrailRender.h"
#include "extensions/Particle3D/PU/CCPUUtil.h"
#include "extensions/Particle3D/PU/CCPUSimpleSpline.h"
#include "renderer/CCMeshCommand.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/CCVertexIndexBuffer.h"
#include "base/CCDirector.h"
#include "3d/CCSprite3D.h"
#include "3d/CCMesh.h"
#include "2d/CCCamera.h"
#include <sstream>

NS_CC_BEGIN

// Constants
const bool PURibbonTrailRender::DEFAULT_USE_VERTEX_COLOURS = true;
const size_t PURibbonTrailRender::DEFAULT_MAX_ELEMENTS = 10;
const float PURibbonTrailRender::DEFAULT_LENGTH = 400;
const float PURibbonTrailRender::DEFAULT_WIDTH = 5;
const bool PURibbonTrailRender::DEFAULT_RANDOM_INITIAL_COLOUR = true;
const Vec4 PURibbonTrailRender::DEFAULT_INITIAL_COLOUR(1, 1, 1, 1);
const Vec4 PURibbonTrailRender::DEFAULT_COLOUR_CHANGE(0.5, 0.5, 0.5, 0.5);

PURibbonTrailRender* PURibbonTrailRender::create( const std::string &texFile )
{
    auto br = new (std::nothrow) PURibbonTrailRender();
    br->autorelease();
    br->_texFile = texFile;
    return br;
}

void PURibbonTrailRender::render( Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem )
{
    if (!_isVisible || !_trail)
        return;

    bool needDraw = false;
    const ParticlePool &particlePool = particleSystem->getParticlePool();
    if (!particlePool.empty()){
        updateParticles(particlePool);
        needDraw = true;
    }

    const PUParticleSystem3D::ParticlePoolMap &emitterPool = static_cast<PUParticleSystem3D *>(particleSystem)->getEmittedEmitterParticlePool();
    if (!emitterPool.empty()){
        for (auto iter : emitterPool){
            updateParticles(iter.second);
            needDraw = true;
        }
    }

    const PUParticleSystem3D::ParticlePoolMap &systemPool = static_cast<PUParticleSystem3D *>(particleSystem)->getEmittedSystemParticlePool();
    if (!systemPool.empty()){
        for (auto iter : systemPool){
            updateParticles(iter.second);
            needDraw = true;
        }
    }

    if (needDraw)
        _trail->render(renderer, transform, particleSystem);
}

PURibbonTrailRender::PURibbonTrailRender() : 
    _quota(0),
    _trail(0),
    _useVertexColours(DEFAULT_USE_VERTEX_COLOURS),
    _maxChainElements(DEFAULT_MAX_ELEMENTS),
    _trailLength(DEFAULT_LENGTH),
    _trailWidth(DEFAULT_WIDTH),
    _randomInitialColor(DEFAULT_RANDOM_INITIAL_COLOUR),
    _setLength(false),
    _setWidth(false),
    _initialColor(DEFAULT_INITIAL_COLOUR),
    _colorChange(DEFAULT_COLOUR_CHANGE),
    _childNode(0)
{
    std::stringstream ss; 
    ss << this;
    _ribbonTrailName = "RibbonTrail" + ss.str();
    autoRotate = false;
}

PURibbonTrailRender::~PURibbonTrailRender()
{
    if (!_particleSystem)
        return;

    destroyAll();
}

void PURibbonTrailRender::particleEmitted( PUParticleSystem3D* /*particleSystem*/, PUParticle3D* /*particle*/ )
{
    // Assigning visual data already done in _updateRenderQueue()
}

void PURibbonTrailRender::particleExpired( PUParticleSystem3D* /*particleSystem*/, PUParticle3D* particle )
{
    if (particle->visualData)
    {
        PURibbonTrailVisualData* ribbonTrailRendererVisualData = static_cast<PURibbonTrailVisualData*>(particle->visualData);
        ribbonTrailRendererVisualData->setVisible(false);
    }
}

//-----------------------------------------------------------------------
bool PURibbonTrailRender::isUseVertexColors(void) const
{
    return _useVertexColours;
} 
//-----------------------------------------------------------------------
void PURibbonTrailRender::setUseVertexColors(bool useVertexColours)
{
    _useVertexColours = useVertexColours;
} 
//-----------------------------------------------------------------------
size_t PURibbonTrailRender::getMaxChainElements(void) const
{
    return _maxChainElements;
} 
//-----------------------------------------------------------------------
void PURibbonTrailRender::setMaxChainElements(size_t maxChainElements)
{
    _maxChainElements = maxChainElements;
} 
//-----------------------------------------------------------------------
float PURibbonTrailRender::getTrailLength(void) const
{
    return _trailLength;
} 
//-----------------------------------------------------------------------
void PURibbonTrailRender::setTrailLength(float trailLength)
{
    _trailLength = trailLength;
    _setLength = true;
} 
//-----------------------------------------------------------------------
float PURibbonTrailRender::getTrailWidth(void) const
{
    return _trailWidth;
} 
//-----------------------------------------------------------------------
void PURibbonTrailRender::setTrailWidth(float trailWidth)
{
    _trailWidth = trailWidth;
    _setWidth = true;
} 
//-----------------------------------------------------------------------
bool PURibbonTrailRender::isRandomInitialColor(void) const
{
    return _randomInitialColor;
} 
//-----------------------------------------------------------------------
void PURibbonTrailRender::setRandomInitialColor(bool randomInitialColour)
{
    _randomInitialColor = randomInitialColour;
} 
//-----------------------------------------------------------------------
const Vec4& PURibbonTrailRender::getInitialColor(void) const
{
    return _initialColor;
} 
//-----------------------------------------------------------------------
void PURibbonTrailRender::setInitialColor(const Vec4& initialColour)
{
    _initialColor = initialColour;
} 
//-----------------------------------------------------------------------
const Vec4& PURibbonTrailRender::getColorChange(void) const
{
    return _colorChange;
} 
//-----------------------------------------------------------------------
void PURibbonTrailRender::setColorChange(const Vec4& colourChange)
{
    _colorChange = colourChange;
} 
//-----------------------------------------------------------------------

void PURibbonTrailRender::prepare()
{
    if (!_particleSystem)
        return;

    // Register itself to the technique
    if (_particleSystem)
    {
        // Although it is safe to assume that technique == mParentTechnique, use the mParentTechnique, because the mParentTechnique is
        // also used for unregistering.
        static_cast<PUParticleSystem3D *>(_particleSystem)->addListener(this);
    }

    _quota = _particleSystem->getParticleQuota();
    if (!_childNode)
    {
        // Create a childnode if not created earlier
        std::stringstream ss; 
        ss << this;
        std::string childNodeNodeName = "ParticleUniverse" + ss.str();
        //_childNode = mParentTechnique->getParentSystem()->getParentSceneNode()->createChildSceneNode(childNodeNodeName);
        //_childNode->setInheritOrientation(false);
        auto parent = _particleSystem->getParent();
        if (parent)
        {
            _childNode = Node::create();
            parent->addChild(_childNode);
        }
    }

    if (_childNode)
    {
        // Create RibbonTrail
        //Ogre::SceneManager* sceneManager = mParentTechnique->getParentSystem()->getSceneManager();
        _trail = new (std::nothrow) PURibbonTrail(_ribbonTrailName, _texFile);
        _trail->setNumberOfChains(_quota);
        _trail->setMaxChainElements(_maxChainElements);
        if (_setLength)
        {
            _trail->setTrailLength(_rendererScale.y * _trailLength);
        }
        else
        {
            _trail->setTrailLength(_rendererScale.y * static_cast<PUParticleSystem3D *>(_particleSystem)->getDefaultHeight());
        }
        _trail->setUseVertexColours(_useVertexColours);

        // Create number of VisualData objects
        std::string sceneNodeName;
        std::stringstream ss; 
        ss << this;
        for (size_t i = 0; i < _quota; i++)
        {
            //sceneNodeName = "ParticleUniverse" + ss.str() + StringConverter::toString(i);
            //RibbonTrailRendererVisualData* visualData = 
            //	PU_NEW_T(RibbonTrailRendererVisualData, MEMCATEGORY_SCENE_OBJECTS)(_childNode->createChildSceneNode(sceneNodeName), _trail);
            //visualData->node->setInheritOrientation(false);
            auto node = Node::create();
            _childNode->addChild(node);
            PURibbonTrailVisualData* visualData = new (std::nothrow) PURibbonTrailVisualData(node, _trail);
            visualData->index = i;
            _allVisualData.push_back(visualData); // Managed by this renderer
            _visualData.push_back(visualData); // Used to assign to a particle
            if (_randomInitialColor)
            {
                _trail->setInitialColour(i, CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1());
            }
            else
            {
                _trail->setInitialColour(i, _initialColor);
            }
            _trail->setColourChange(i, _colorChange);
            if (_setWidth)
            {
                _trail->setInitialWidth(i, _rendererScale.x * _trailWidth);
            }
            else
            {
                _trail->setInitialWidth(i, _rendererScale.x * static_cast<PUParticleSystem3D *>(_particleSystem)->getDefaultWidth());
            }
        }
        //_childNode->attachObject(_trail);
        _trail->setAttachedNode(_childNode);
        _trail->setDepthTest(_depthTest);
        _trail->setDepthWrite(_depthWrite);
    }
}

void PURibbonTrailRender::unPrepare()
{
    destroyAll();
}

void PURibbonTrailRender::updateRender( PUParticle3D* /*particle*/, float deltaTime, bool /*firstParticle*/ )
{
    if (_trail)
        _trail->update(deltaTime);
}

//-----------------------------------------------------------------------
void PURibbonTrailRender::destroyAll(void)
{
    if (!_particleSystem || !_trail || !_childNode)
        return;

    // Remove the listener
    static_cast<PUParticleSystem3D *>(_particleSystem)->removeListener(this);

    // Detach the Ribbontrail
    if (_childNode && _trail)
    {
        _trail->setAttachedNode(nullptr);
        //_childNode->detachObject(_trail);
    }

    // Delete the Ribbontrail
    CC_SAFE_DELETE(_trail);

    // Delete the visual data
    std::vector<PURibbonTrailVisualData*>::const_iterator it;
    std::vector<PURibbonTrailVisualData*>::const_iterator itEnd = _allVisualData.end();
    for (it = _allVisualData.begin(); it != itEnd; ++it)
    {
        delete *it;
    }

    _allVisualData.clear();
    _visualData.clear();

    // Destroy the children of the childnode, but not the childnode itself, because this gives a delete-order problem
    if (_childNode)
    {
        //_childNode->removeAndDestroyAllChildren();
        _childNode->removeAllChildren();
        if (_childNode->getParent())
            _childNode->getParent()->removeChild(_childNode);
        _childNode = nullptr;
    }
}


void PURibbonTrailRender::notifyRescaled( const Vec3& scale )
{
    PURender::notifyRescaled(scale);
    if (_trail)
    {
        // Use the average length (is there a good alternative?
        _trail->setTrailLength(scale.y * _trailLength);
        size_t numberOfChains = _trail->getNumberOfChains();
        for (size_t i = 0; i < numberOfChains; ++i)
        {
            _trail->setInitialWidth(i, scale.x * _trailWidth);
        }
    }
}

PURibbonTrailRender* PURibbonTrailRender::clone()
{
    auto tr = PURibbonTrailRender::create(_texFile);
    copyAttributesTo(tr);
    return tr;
}

void PURibbonTrailRender::copyAttributesTo(PURibbonTrailRender *trailRender)
{
    PURender::copyAttributesTo(trailRender);
    trailRender->setUseVertexColors(_useVertexColours);
    trailRender->setMaxChainElements(_maxChainElements);
    trailRender->setTrailLength(_trailLength);
    trailRender->setTrailWidth(_trailWidth);
    trailRender->setRandomInitialColor(_randomInitialColor);
    trailRender->setInitialColor(_initialColor);
    trailRender->setColorChange(_colorChange);
}

void PURibbonTrailRender::updateParticles( const ParticlePool &pool )
{
    PURibbonTrailVisualData* visualData = nullptr;
    Vec3 basePosition = static_cast<PUParticleSystem3D *>(_particleSystem)->getDerivedPosition();
    for (auto iter : pool.getActiveDataList())
    {
        auto particle = static_cast<PUParticle3D *>(iter);
        if (!particle->visualData && !_visualData.empty())
        {
            particle->visualData = _visualData.back();
            _visualData.pop_back();
        }
        visualData = static_cast<PURibbonTrailVisualData*>(particle->visualData);
        if (visualData)
        {
            Node* node = visualData->node;
            node->setPosition3D(particle->position);

            // Set the width of the trail if required
            if (particle->particleType == PUParticle3D::PT_VISUAL)
            {
                if (particle->ownDimensions)
                {
                    _trail->setInitialWidth(visualData->index, particle->width);
                }
            }
            visualData->setVisible(true);
        }
    }
}

NS_CC_END
