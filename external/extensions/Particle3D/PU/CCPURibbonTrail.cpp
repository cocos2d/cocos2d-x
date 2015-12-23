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

#include "extensions/Particle3D/PU/CCPURibbonTrail.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "base/CCDirector.h"
#include "renderer/CCMeshCommand.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/CCVertexIndexBuffer.h"
#include "2d/CCCamera.h"
#include "3d/CCSprite3D.h"

NS_CC_BEGIN

PURibbonTrail::PURibbonTrail(const std::string& name, const std::string &texFile, size_t maxElements, 
    size_t numberOfChains, bool useTextureCoords, bool useColours)
    :PUBillboardChain(name, texFile, maxElements, 0, useTextureCoords, useColours, true),
    _parentNode(nullptr),
    _needTimeUpdate(false)
{
    setTrailLength(100);
    setNumberOfChains(numberOfChains);

    // use V as varying texture coord, so we can use 1D textures to 'smear'
    setTextureCoordDirection(TCD_V);
}
//-----------------------------------------------------------------------
PURibbonTrail::~PURibbonTrail()
{
}
//-----------------------------------------------------------------------
void PURibbonTrail::addNode(Node* n)
{
    if (_nodeList.size() == _chainCount)
    {
        CCAssert(false, " cannot monitor any more nodes, chain count exceeded");
    }

    //if (n->getListener())
    //{
    //	OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, 
    //		mName + " cannot monitor node " + n->getName() + " since it already has a listener.",
    //		"RibbonTrail::addNode");
    //}

    // get chain index
    size_t chainIndex = _freeChains.back();
    _freeChains.pop_back();
    _nodeToChainSegment.push_back(chainIndex);
    _nodeToSegMap[n] = chainIndex;

    // initialise the chain
    resetTrail(chainIndex, n);

    _nodeList.push_back(n);
    //n->setListener(this);

}
//-----------------------------------------------------------------------
size_t PURibbonTrail::getChainIndexForNode(const Node* n)
{
    NodeToChainSegmentMap::const_iterator i = _nodeToSegMap.find(n);
    if (i == _nodeToSegMap.end())
    {
        CCAssert(false, "This node is not being tracked");
    }
    return i->second;
}
//-----------------------------------------------------------------------
void PURibbonTrail::removeNode(Node* n)
{
    NodeList::iterator i = std::find(_nodeList.begin(), _nodeList.end(), n);
    if (i != _nodeList.end())
    {
        // also get matching chain segment
        size_t index = std::distance(_nodeList.begin(), i);
        IndexVector::iterator mi = _nodeToChainSegment.begin();
        std::advance(mi, index);
        size_t chainIndex = *mi;
        PUBillboardChain::clearChain(chainIndex);
        // mark as free now
        _freeChains.push_back(chainIndex);
        //n->setListener(0);
        _nodeList.erase(i);
        _nodeToChainSegment.erase(mi);
        _nodeToSegMap.erase(_nodeToSegMap.find(n));
    }
}
//-----------------------------------------------------------------------
void PURibbonTrail::setTrailLength(float len)
{
    _trailLength = len;
    _elemLength = _trailLength / _maxElementsPerChain;
    _squaredElemLength = _elemLength * _elemLength;
}
//-----------------------------------------------------------------------
void PURibbonTrail::setMaxChainElements(size_t maxElements)
{
    PUBillboardChain::setMaxChainElements(maxElements);
    _elemLength = _trailLength / _maxElementsPerChain;
    _squaredElemLength = _elemLength * _elemLength;

    resetAllTrails();
}
//-----------------------------------------------------------------------
void PURibbonTrail::setNumberOfChains(size_t numChains)
{
    CCAssert(numChains >= _nodeList.size(), "Can't shrink the number of chains less than number of tracking nodes");

    size_t oldChains = getNumberOfChains();

    PUBillboardChain::setNumberOfChains(numChains);

    _initialColor.resize(numChains, Vec4::ONE);
    _deltaColor.resize(numChains, Vec4::ZERO);
    _initialWidth.resize(numChains, 10);
    _deltaWidth.resize(numChains, 0);

    if (oldChains > numChains)
    {
        // remove free chains
        for (IndexVector::iterator i = _freeChains.begin(); i != _freeChains.end();)
        {
            if (*i >= numChains)
                i = _freeChains.erase(i);
            else
                ++i;
        }
    }
    else if (oldChains < numChains)
    {
        // add new chains, at front to preserve previous ordering (pop_back)
        for (size_t i = oldChains; i < numChains; ++i)
            _freeChains.insert(_freeChains.begin(), i);
    }
    resetAllTrails();
}
//-----------------------------------------------------------------------
void PURibbonTrail::clearChain(size_t chainIndex)
{
    PUBillboardChain::clearChain(chainIndex);

    // Reset if we are tracking for this chain
    IndexVector::iterator i = std::find(_nodeToChainSegment.begin(), _nodeToChainSegment.end(), chainIndex);
    if (i != _nodeToChainSegment.end())
    {
        size_t nodeIndex = std::distance(_nodeToChainSegment.begin(), i);
        resetTrail(*i, _nodeList[nodeIndex]);
    }
}
//-----------------------------------------------------------------------
void PURibbonTrail::setInitialColour(size_t chainIndex, const Vec4& col)
{
    setInitialColour(chainIndex, col.x, col.y, col.z, col.w);
}
//-----------------------------------------------------------------------
void PURibbonTrail::setInitialColour(size_t chainIndex, float r, float g, float b, float a)
{
    CCAssert(chainIndex < _chainCount, "chainIndex out of bounds");
    _initialColor[chainIndex].x = r;
    _initialColor[chainIndex].y = g;
    _initialColor[chainIndex].z = b;
    _initialColor[chainIndex].w = a;
}
//-----------------------------------------------------------------------
const Vec4& PURibbonTrail::getInitialColour(size_t chainIndex) const
{
    CCAssert(chainIndex < _chainCount, "chainIndex out of bounds");
    return _initialColor[chainIndex];
}
//-----------------------------------------------------------------------
void PURibbonTrail::setInitialWidth(size_t chainIndex, float width)
{
    CCAssert(chainIndex < _chainCount, "chainIndex out of bounds");
    _initialWidth[chainIndex] = width;
}
//-----------------------------------------------------------------------
float PURibbonTrail::getInitialWidth(size_t chainIndex) const
{
    CCAssert(chainIndex < _chainCount, "chainIndex out of bounds");
    return _initialWidth[chainIndex];
}
//-----------------------------------------------------------------------
void PURibbonTrail::setColourChange(size_t chainIndex, const Vec4& valuePerSecond)
{
    setColourChange(chainIndex, 
        valuePerSecond.x, valuePerSecond.y, valuePerSecond.z, valuePerSecond.w);
}
//-----------------------------------------------------------------------
void PURibbonTrail::setColourChange(size_t chainIndex, float r, float g, float b, float a)
{
    CCAssert(chainIndex < _chainCount, "chainIndex out of bounds");
    _deltaColor[chainIndex].x = r;
    _deltaColor[chainIndex].y = g;
    _deltaColor[chainIndex].z = b;
    _deltaColor[chainIndex].w = a;

    manageController();

}
//-----------------------------------------------------------------------
const Vec4& PURibbonTrail::getColourChange(size_t chainIndex) const
{
    CCAssert(chainIndex < _chainCount, "chainIndex out of bounds");
    return _deltaColor[chainIndex];
}
//-----------------------------------------------------------------------
void PURibbonTrail::setWidthChange(size_t chainIndex, float widthDeltaPerSecond)
{
    CCAssert(chainIndex < _chainCount, "chainIndex out of bounds");
    _deltaWidth[chainIndex] = widthDeltaPerSecond;
    manageController();
}
//-----------------------------------------------------------------------
float PURibbonTrail::getWidthChange(size_t chainIndex) const
{
    CCAssert(chainIndex < _chainCount, "chainIndex out of bounds");
    return _deltaWidth[chainIndex];

}
//-----------------------------------------------------------------------
void PURibbonTrail::manageController(void)
{
    _needTimeUpdate = false;
    for (size_t i = 0; i < _chainCount; ++i)
    {
        if (_deltaWidth[i] != 0 || _deltaColor[i] != Vec4::ZERO)
        {
            _needTimeUpdate = true;
            break;
        }
    }
}
//-----------------------------------------------------------------------
void PURibbonTrail::nodeUpdated(const Node* node)
{
    size_t chainIndex = getChainIndexForNode(node);
    updateTrail(chainIndex, node);
}
//-----------------------------------------------------------------------
void PURibbonTrail::nodeDestroyed(const Node* node)
{
    removeNode(const_cast<Node*>(node));
}
//-----------------------------------------------------------------------
void PURibbonTrail::updateTrail(size_t index, const Node* node)
{
    // Repeat this entire process if chain is stretched beyond its natural length
    bool done = false;
    while (!done)
    {
        // Node has changed somehow, we're only interested in the derived position
        ChainSegment& seg = _chainSegmentList[index];
        Element& headElem = _chainElementList[seg.start + seg.head];
        size_t nextElemIdx = seg.head + 1;
        // wrap
        if (nextElemIdx == _maxElementsPerChain)
            nextElemIdx = 0;
        Element& nextElem = _chainElementList[seg.start + nextElemIdx];

        // Vary the head elem, but bake new version if that exceeds element len
        Mat4 toWMat = node->getNodeToWorldTransform();
        Vec3 newPos = Vec3(toWMat.m[12], toWMat.m[13], toWMat.m[14]);
        if (_parentNode)
        {
            Mat4 toLMat = _parentNode->getWorldToNodeTransform() * toWMat;
            // Transform position to ourself space
            newPos.x = (toLMat).m[12];
            newPos.y = (toLMat).m[13];
            newPos.z = (toLMat).m[14];
        }
        Vec3 diff = newPos - nextElem.position;
        float sqlen = diff.lengthSquared();
        if (sqlen >= _squaredElemLength)
        {
            // Move existing head to mElemLength
            Vec3 scaledDiff = diff * (_elemLength / sqrtf(sqlen));
            headElem.position = nextElem.position + scaledDiff;
            // Add a new element to be the new head
            Element newElem( newPos, _initialWidth[index], 0.0f,
                _initialColor[index], node->getRotationQuat() );
            addChainElement(index, newElem);
            // alter diff to represent new head size
            diff = newPos - headElem.position;
            // check whether another step is needed or not
            if (diff.lengthSquared() <= _squaredElemLength)   
                done = true;

        }
        else
        {
            // Extend existing head
            headElem.position = newPos;
            done = true;
        }

        // Is this segment full?
        if ((seg.tail + 1) % _maxElementsPerChain == seg.head)
        {
            // If so, shrink tail gradually to match head extension
            Element& tailElem = _chainElementList[seg.start + seg.tail];
            size_t preTailIdx;
            if (seg.tail == 0)
                preTailIdx = _maxElementsPerChain - 1;
            else
                preTailIdx = seg.tail - 1;
            Element& preTailElem = _chainElementList[seg.start + preTailIdx];

            // Measure tail diff from pretail to tail
            Vec3 taildiff = tailElem.position - preTailElem.position;
            float taillen = taildiff.length();
            if (taillen > 1e-06)
            {
                float tailsize = _elemLength - diff.length();
                taildiff *= tailsize / taillen;
                tailElem.position = preTailElem.position + taildiff;
            }

        }
    } // end while


    // Need to dirty the parent node, but can't do it using needUpdate() here 
    // since we're in the middle of the scene graph update (node listener), 
    // so re-entrant calls don't work. Queue.
    //if (mParentNode)
    //{
    //	Node::queueNeedUpdate(getParentSceneNode());
    //}

}
//-----------------------------------------------------------------------
void PURibbonTrail::timeUpdate(float time)
{
    // Apply all segment effects
    for (size_t s = 0; s < _chainSegmentList.size(); ++s)
    {
        ChainSegment& seg = _chainSegmentList[s];
        if (seg.head != SEGMENT_EMPTY && seg.head != seg.tail)
        {

            for(size_t e = seg.head + 1;; ++e) // until break
            {
                e = e % _maxElementsPerChain;

                Element& elem = _chainElementList[seg.start + e];
                elem.width = elem.width - (time * _deltaWidth[s]);
                elem.width = 0.0f < elem.width? elem.width: 0.0f;
                elem.color = elem.color - (_deltaColor[s] * time);
                elem.color.clamp(Vec4(0.0f, 0.0f, 0.0f, 0.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f));

                if (e == seg.tail)
                    break;

            }
        }

    }

}
//-----------------------------------------------------------------------
void PURibbonTrail::resetTrail(size_t index, const Node* node)
{
    assert(index < _chainCount);

    ChainSegment& seg = _chainSegmentList[index];
    // set up this segment
    seg.head = seg.tail = SEGMENT_EMPTY;
    // Create new element, v coord is always 0.0f
    // need to convert to take parent node's position into account
    Mat4 toWMat = node->getNodeToWorldTransform();
    Vec3 position = Vec3(toWMat.m[12], toWMat.m[13], toWMat.m[14]);
    if (_parentNode)
    {
        Mat4 toLMat = _parentNode->getWorldToNodeTransform() * toWMat;
        // Transform position to ourself space
        position.x = (toLMat).m[12];
        position.y = (toLMat).m[13];
        position.z = (toLMat).m[14];
    }
    Element e(position,
        _initialWidth[index], 0.0f, _initialColor[index], node->getRotationQuat());
    // Add the start position
    addChainElement(index, e);
    // Add another on the same spot, this will extend
    addChainElement(index, e);
}
//-----------------------------------------------------------------------
void PURibbonTrail::resetAllTrails(void)
{
    for (size_t i = 0; i < _nodeList.size(); ++i)
    {
        resetTrail(i, _nodeList[i]);
    }
}

void PURibbonTrail::update( float deltaTime )
{
    if (_needTimeUpdate){
        static float lastUpdateTime = 0.0f;
        if (0.5f < lastUpdateTime){
            timeUpdate(deltaTime);
            lastUpdateTime = 0.0f;
        }
        lastUpdateTime += deltaTime;
    }

    for (auto iter : _nodeToSegMap){
        updateTrail(iter.second, iter.first);
    }
}

NS_CC_END
