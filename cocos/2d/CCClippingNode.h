/*
 * Copyright (c) 2012      Pierre-David Bélanger
 * Copyright (c) 2012      cocos2d-x.org
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 *
 * http://www.cocos2d-x.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef __MISCNODE_CCCLIPPING_NODE_H__
#define __MISCNODE_CCCLIPPING_NODE_H__

#include "2d/CCNode.h"
#include "CCGL.h"
#include "renderer/CCGroupCommand.h"
#include "renderer/CCCustomCommand.h"

NS_CC_BEGIN

/** ClippingNode is a subclass of Node.
 It draws its content (childs) clipped using a stencil.
 The stencil is an other Node that will not be drawn.
 The clipping is done using the alpha part of the stencil (adjusted with an alphaThreshold).
 */
class CC_DLL ClippingNode : public Node
{
public:
    /** Creates and initializes a clipping node without a stencil.
     */
    static ClippingNode* create();
    
    /** Creates and initializes a clipping node with an other node as its stencil.
     The stencil node will be retained.
     */
    static ClippingNode* create(Node *stencil);

    /** The Node to use as a stencil to do the clipping.
     The stencil node will be retained.
     This default to nil.
     */
    Node* getStencil() const;
    void setStencil(Node *stencil);
    
    /** The alpha threshold.
     The content is drawn only where the stencil have pixel with alpha greater than the alphaThreshold.
     Should be a float between 0 and 1.
     This default to 1 (so alpha test is disabled).
     */
    GLfloat getAlphaThreshold() const;
    void setAlphaThreshold(GLfloat alphaThreshold);
    
    /** Inverted. If this is set to true,
     the stencil is inverted, so the content is drawn where the stencil is NOT drawn.
     This default to false.
     */
    bool isInverted() const;
    void setInverted(bool inverted);

    // Overrides
    /**
     * @js NA
     * @lua NA
     */
    virtual void onEnter() override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void onEnterTransitionDidFinish() override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void onExitTransitionDidStart() override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void onExit() override;
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, bool parentTransformUpdated) override;
    
CC_CONSTRUCTOR_ACCESS:
    ClippingNode();
    
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ClippingNode();

    /** Initializes a clipping node without a stencil.
     */
    virtual bool init();
    
    /** Initializes a clipping node with an other node as its stencil.
     The stencil node will be retained, and its parent will be set to this clipping node.
     */
    virtual bool init(Node *stencil);

protected:
    /**draw fullscreen quad to clear stencil bits
    */
    void drawFullScreenQuadClearStencil();

    Node* _stencil;
    GLfloat _alphaThreshold;
    bool    _inverted;

    //renderData and callback
    void onBeforeVisit();
    void onAfterDrawStencil();
    void onAfterVisit();

    GLboolean _currentStencilEnabled;
    GLuint _currentStencilWriteMask;
    GLenum _currentStencilFunc;
    GLint _currentStencilRef;
    GLuint _currentStencilValueMask;
    GLenum _currentStencilFail;
    GLenum _currentStencilPassDepthFail;
    GLenum _currentStencilPassDepthPass;
    GLboolean _currentDepthWriteMask;

    GLboolean _currentAlphaTestEnabled;
    GLenum _currentAlphaTestFunc;
    GLclampf _currentAlphaTestRef;

    GLint _mask_layer_le;
    
    GroupCommand _groupCommand;
    CustomCommand _beforeVisitCmd;
    CustomCommand _afterDrawStencilCmd;
    CustomCommand _afterVisitCmd;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ClippingNode);
};

NS_CC_END

#endif // __MISCNODE_CCCLIPPING_NODE_H__
