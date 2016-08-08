/*
 * Copyright (c) 2012      Pierre-David Bélanger
 * Copyright (c) 2012      cocos2d-x.org
 * Copyright (c) 2013-2016 Chukong Technologies Inc.
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
#include "platform/CCGL.h"
#include "renderer/CCGroupCommand.h"
#include "renderer/CCCustomCommand.h"

NS_CC_BEGIN

class StencilStateManager;
/**
 *  @addtogroup _2d
 *  @{
 */
/** ClippingNode is a subclass of Node.
 * It draws its content (children) clipped using a stencil.
 * The stencil is an other Node that will not be drawn.
 * The clipping is done using the alpha part of the stencil (adjusted with an alphaThreshold).
 */
class CC_DLL ClippingNode : public Node
{
public:
    /** Creates and initializes a clipping node without a stencil.
     *
     * @return An autorelease ClippingNode.
     */
    static ClippingNode* create();
    
    /** Creates and initializes a clipping node with an other node as its stencil.
     * The stencil node will be retained.
     * @param stencil The stencil node.
     */
    static ClippingNode* create(Node *stencil);

    /** The Node to use as a stencil to do the clipping.
     * The stencil node will be retained.
     * This default to nil.
     *
     * @return The stencil node.
     */
    Node* getStencil() const;
    
    /** Set the Node to use as a stencil to do the clipping.
     *
     * @param stencil The Node to use as a stencil to do the clipping.
     */
    void setStencil(Node *stencil);

    /** If stencil has no children it will not be drawn.
     * If you have custom stencil-based node with stencil drawing mechanics other then children-based,
     * then this method should return true every time you wish stencil to be visited.
     * By default returns true if has any children attached.
     *
     * @return If you have custom stencil-based node with stencil drawing mechanics other then children-based,
     *         then this method should return true every time you wish stencil to be visited.
     *         By default returns true if has any children attached.
     * @js NA
     */
    virtual bool hasContent() const;

    /** The alpha threshold.
     * The content is drawn only where the stencil have pixel with alpha greater than the alphaThreshold.
     * Should be a float between 0 and 1.
     * This default to 1 (so alpha test is disabled).
     *
     * @return The alpha threshold value,Should be a float between 0 and 1.
     */
    GLfloat getAlphaThreshold() const;
    
    /** Set the alpha threshold. 
     * 
     * @param alphaThreshold The alpha threshold.
     */
    void setAlphaThreshold(GLfloat alphaThreshold);
    
    /** Inverted. If this is set to true,
     * the stencil is inverted, so the content is drawn where the stencil is NOT drawn.
     * This default to false.
     *
     * @return If the clippingNode is Inverted, it will be return true.
     */
    bool isInverted() const;
    
    /** Set the ClippingNode whether or not invert.
     *
     * @param inverted A bool Type,to set the ClippingNode whether or not invert.
     */
    void setInverted(bool inverted);

    // Overrides
    /**
     * @lua NA
     */
    virtual void onEnter() override;
    /**
     * @lua NA
     */
    virtual void onEnterTransitionDidFinish() override;
    /**
     * @lua NA
     */
    virtual void onExitTransitionDidStart() override;
    /**
     * @lua NA
     */
    virtual void onExit() override;
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
    
    virtual void setCameraMask(unsigned short mask, bool applyChildren = true) override;
    
CC_CONSTRUCTOR_ACCESS:
    ClippingNode();
    
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ClippingNode();

    /** Initializes a clipping node without a stencil.
     */
    virtual bool init() override;
    
    /** Initializes a clipping node with an other node as its stencil.
     The stencil node will be retained, and its parent will be set to this clipping node.
     */
    virtual bool init(Node *stencil);

protected:
    Node* _stencil;
   
    StencilStateManager* _stencilStateManager;
    
    GroupCommand _groupCommand;
    CustomCommand _beforeVisitCmd;
    CustomCommand _afterDrawStencilCmd;
    CustomCommand _afterVisitCmd;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ClippingNode);
};
/** @} */
NS_CC_END

#endif // __MISCNODE_CCCLIPPING_NODE_H__
