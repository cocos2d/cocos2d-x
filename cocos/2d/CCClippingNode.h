/*Copyright (c) 2012      Pierre-David Bélanger
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
#include "platform/CCGL.h"
#include "renderer/CCGroupCommand.h"
#include "renderer/CCCustomCommand.h"

NS_CC_BEGIN
/**
 *  @addtogroup _2d
 *  @{
 */
/** @~english ClippingNode is a subclass of Node.
 * It draws its content (children) clipped using a stencil.
 * The stencil is an other Node that will not be drawn.
 * The clipping is done using the alpha part of the stencil (adjusted with an alphaThreshold).
 * @~chinese ClippingNode是Node的一个子类。
 * 它使用一个模板来裁剪绘制内容。
 * 模板是一个其他节点,不会被绘制。
 * 使用模板的alpha部分来进行裁剪(通过调整alphaThreshold)。
 */
class CC_DLL ClippingNode : public Node
{
public:
    /** @~english Creates and initializes a clipping node without a stencil.
     *
     * @~chinese 创建并初始化一个裁剪节点，不带模板。
     * 
     * @return @~english An autorelease ClippingNode.
     * @~chinese 一个自动释放的ClippingNode对象。
     */
    static ClippingNode* create();
    
    /** @~english Creates and initializes a clipping node with an other node as its stencil.
     * The stencil node will be retained.
     * @~chinese 使用另一个节点作为模板创建并初始化一个裁剪节点。
     * 模板节点将被retain。
     * @param stencil @~english The stencil node.
     * @~chinese 模板节点。
     * @return @~english An autorelease ClippingNode.
     * @~chinese 一个自动释放的ClippingNode对象。
     */
    static ClippingNode* create(Node *stencil);

    /** @~english The Node to use as a stencil to do the clipping.
     * The stencil node will be retained.
     * This default to nil.
     *
     * @~chinese 作为模板进行裁剪的节点。
     * 模板节点将被retain。
     * 这个默认为空。
     * 
     * @return @~english The stencil node.
     * @~chinese 模板节点。
     */
    Node* getStencil() const;
    
    /** @~english Set the Node to use as a stencil to do the clipping.
     *
     * @~chinese 设置一个作为模板进行裁剪的节点
     * 
     * @param stencil @~english The Node to use as a stencil to do the clipping.
     * @~chinese 作为模板进行裁剪的节点。
     */
    void setStencil(Node *stencil);

    /** @~english If stencil has no childre it will not be drawn.
     * If you have custom stencil-based node with stencil drawing mechanics other then children-based,
     * then this method should return true every time you wish stencil to be visited.
     * By default returns true if has any children attached.
     *
     * @~chinese 如果模板没有子节点，将不会被绘制。
     * 如果你有自定义的基于模板的节点而不是基于子节点,
     * 如果你希望模板被绘制的话，那么这个方法每一次都会返回true。
     * 如果关联了子节点将会默认返回true。
     * 
     * @js NA
     */
    virtual bool hasContent() const;

    /** @~english The alpha threshold.
     * The content is drawn only where the stencil have pixel with alpha greater than the alphaThreshold.
     * Should be a float between 0 and 1.
     * This default to 1 (so alpha test is disabled).
     *
     * @~chinese 透明度阈值。
     * 只有当透明度大于alphaThreshold的内容才会被绘制。
     * 应该是一个在0和1之间的浮点数。
     * 这个默认为1(所以alpha测试是禁用的)。
     * 
     * @return @~english The alpha threshold value,Should be a float between 0 and 1.
     * @~chinese 透明度阈值,应该是一个在0和1之间的浮点数。
     */
    GLfloat getAlphaThreshold() const;
    
    /** @~english Set the alpha threshold. 
     * 
     * @~chinese 设置透明度阈值。
     * 
     * @param alphaThreshold @~english The alpha threshold.
     * @~chinese 透明度阈值。
     */
    void setAlphaThreshold(GLfloat alphaThreshold);
    
    /** @~english Inverted. If this is set to true,
     * the stencil is inverted, so the content is drawn where the stencil is NOT drawn.
     * This default to false.
     *
     * @~chinese 如果设置为真的话模板反转，内容被绘制的部分是对应模板不可见的部分。
     * 默认为假。
     * 
     * @return @~english If the clippingNode is inverted, it will be return true.
     * @~chinese 如果clippingNode反转,它将返回true。
     */
    bool isInverted() const;
    
    /** @~english Set the ClippingNode whether or not invert.
     *
     * @~chinese 设置ClippingNode是否反转。
     * 
     * @param inverted @~english A bool Type,to set the ClippingNode whether or not invert.
     * @~chinese bool类型,用于设置ClippingNode是否反转。
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

    /** @~english Initializes a clipping node without a stencil.
     * @~chinese 不带模板地初始化一个裁剪节点。
     */
    virtual bool init() override;
    
    /** @~english Initializes a clipping node with an other node as its stencil.
     The stencil node will be retained, and its parent will be set to this clipping node.
     * @~chinese 使用另一个节点作为模板初始化一个裁剪节点。
     * 模板节点将被retain,它的父节点将会设置到这个裁剪节点。
     */
    virtual bool init(Node *stencil);

protected:
    /**@~english draw fullscreen quad to clear stencil bits
     * @~chinese 画全屏四模板位
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
/** @~english @}  @~chinese @ }*/
NS_CC_END

#endif // __MISCNODE_CCCLIPPING_NODE_H__
