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

#ifndef __CC_PU_PARTICLE_3D_RIBBON_TRAIL_H__
#define __CC_PU_PARTICLE_3D_RIBBON_TRAIL_H__

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "extensions/Particle3D/PU/CCPUBillboardChain.h"
#include <vector>

NS_CC_BEGIN

class PURibbonTrail : public PUBillboardChain
{

public:
    /** Constructor
    @param name The name to give this object
    @param maxElements The maximum number of elements per chain
    @param numberOfChains The number of separate chain segments contained in this object,
        ie the maximum number of nodes that can have trails attached
    @param useTextureCoords If true, use texture coordinates from the chain elements
    @param useVertexColors If true, use vertex colors from the chain elements (must
        be true if you intend to use fading)
    */
    PURibbonTrail(const std::string& name, const std::string &texFile = "", size_t maxElements = 20, size_t numberOfChains = 1, 
        bool useTextureCoords = true, bool useColours = true);
    /// destructor
    virtual ~PURibbonTrail();

    typedef std::vector<Node*> NodeList;

    /** Add a node to be tracked.
    @param n The node that will be tracked.
    */
    virtual void addNode(Node* n);
    /** Remove tracking on a given node. */
    virtual void removeNode(Node* n);
    /** Get the chain index for a given Node being tracked. */
    virtual size_t getChainIndexForNode(const Node* n);

    void setAttachedNode(Node *parent) { _parentNode = parent; }

    /** Set the length of the trail. 
    @remarks
        This sets the length of the trail, in world units. It also sets how
        far apart each segment will be, ie length / max_elements. 
    @param len The length of the trail in world units
    */
    virtual void setTrailLength(float len);
    /** Get the length of the trail. */
    virtual float getTrailLength(void) const { return _trailLength; }

    /** @copydoc BillboardChain::setMaxChainElements */
    void setMaxChainElements(size_t maxElements);
    /** @copydoc BillboardChain::setNumberOfChains */
    virtual void setNumberOfChains(size_t numChains) override;
    /** @copydoc BillboardChain::clearChain */
    void clearChain(size_t chainIndex);

    /** Set the starting ribbon colour for a given segment. 
    @param chainIndex The index of the chain
    @param col The initial colour
    @note
        Only used if this instance is using vertex colours.
    */
    virtual void setInitialColour(size_t chainIndex, const Vec4& col);
    /** Set the starting ribbon colour. 
    @param chainIndex The index of the chain
    @param r,b,g,a The initial colour
    @note
        Only used if this instance is using vertex colours.
    */
    virtual void setInitialColour(size_t chainIndex, float r, float g, float b, float a = 1.0);
    /** Get the starting ribbon colour. */
    virtual const Vec4& getInitialColour(size_t chainIndex) const;

    /** Enables / disables fading the trail using colour. 
    @param chainIndex The index of the chain
    @param valuePerSecond The amount to subtract from colour each second
    */
    virtual void setColourChange(size_t chainIndex, const Vec4& valuePerSecond);

    /** Set the starting ribbon width in world units. 
    @param chainIndex The index of the chain
    @param width The initial width of the ribbon
    */
    virtual void setInitialWidth(size_t chainIndex, float width);
    /** Get the starting ribbon width in world units. */
    virtual float getInitialWidth(size_t chainIndex) const;
        
    /** Set the change in ribbon width per second. 
    @param chainIndex The index of the chain
    @param widthDeltaPerSecond The amount the width will reduce by per second
    */
    virtual void setWidthChange(size_t chainIndex, float widthDeltaPerSecond);
    /** Get the change in ribbon width per second. */
    virtual float getWidthChange(size_t chainIndex) const;

    /** Enables / disables fading the trail using colour. 
    @param chainIndex The index of the chain
    @param r,g,b,a The amount to subtract from each colour channel per second
    */
    virtual void setColourChange(size_t chainIndex, float r, float g, float b, float a);

    /** Get the per-second fading amount */
    virtual const Vec4& getColourChange(size_t chainIndex) const;

    void update(float deltaTime);

    /// @see Node::Listener::nodeUpdated
    void nodeUpdated(const Node* node);
    /// @see Node::Listener::nodeDestroyed
    void nodeDestroyed(const Node* node);

    /// Perform any fading / width delta required; internal method
    void timeUpdate(float time);

protected:

    /// Manage updates to the time controller
    void manageController(void);
    /// Node has changed position, update
    void updateTrail(size_t index, const Node* node);
    /// Reset the tracked chain to initial state
    void resetTrail(size_t index, const Node* node);
    /// Reset all tracked chains to initial state
    void resetAllTrails(void);

protected:

    /// List of nodes being trailed
    NodeList _nodeList;
    /// Mapping of nodes to chain segments
    typedef std::vector<size_t> IndexVector;
    /// Ordered like mNodeList, contains chain index
    IndexVector _nodeToChainSegment;
    // chains not in use
    IndexVector _freeChains;

    // fast lookup node->chain index
    // we use positional map too because that can be useful
    typedef std::map<const Node*, size_t> NodeToChainSegmentMap;
    NodeToChainSegmentMap _nodeToSegMap;

    /// Total length of trail in world units
    float _trailLength;
    /// length of each element
    float _elemLength;
    /// Squared length of each element
    float _squaredElemLength;
    typedef std::vector<Vec4> ColorValueList;
    typedef std::vector<float> RealList;
    /// Initial colour of the ribbon
    ColorValueList _initialColor;
    /// fade amount per second
    ColorValueList _deltaColor;
    /// Initial width of the ribbon
    RealList _initialWidth;
    /// Delta width of the ribbon
    RealList _deltaWidth;

    Node *_parentNode;
    bool _needTimeUpdate;

};

NS_CC_END
#endif
