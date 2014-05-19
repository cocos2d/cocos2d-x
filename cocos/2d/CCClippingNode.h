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

/** ClippingNode是Node的子类。
 使用模板（stencil）绘制它裁剪的内容（子节点）。
 模板（stencil）是另一个节点（Node），它不会被绘制。
 裁剪是通过使用模板的（alphaThreshold调节的）alpha部分完成的。
 */
class CC_DLL ClippingNode : public Node
{
public:
    /** 创建并初始化不含模板（stencil）的裁剪节点（clipping node）
     */
    static ClippingNode* create();
    
    /** 使用其他节点（Node）作为模板（stencil）创建并初始化一个裁剪节点（clipping node）。
	模板（stencil）对象将会被retain
     */
    static ClippingNode* create(Node *stencil);

    /** 用来做裁剪的模板（stencil）节点（Node）
	模板（stencil）将会被retain
	模板（stencil）对象默认为空（nil）。
     */
    Node* getStencil() const;
    void setStencil(Node *stencil);
    
    /** alpha阈值（threshold）
	 只有模板（stencil）的alpha像素大于alpha阈值（alphaThreshold）时内容才会被绘制。
	 alpha阈值（threshold）范围应是0到1之间的浮点数。
	 alpha阈值（threshold）默认为1（alpha测试默认关闭）
     */
    GLfloat getAlphaThreshold() const;
    void setAlphaThreshold(GLfloat alphaThreshold);
    
    /** 倒置（Inverted）
	 如果设置为真（true），模板（stencil）会被反转，此时会绘制内容而不绘制模板（stencil）。
	 默认设置为假（false）。
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

    /** 初始化一个不含模板（stencil）的裁剪节点（clipping node）
     */
    virtual bool init();
    
    /** 用另一个模板（stencil）节点（Node）初始化一个裁剪节点（clipping node）。
	 模板（stencil）将会被retain，它的父节点会被设置为此裁剪节点（clipping node）。
     */
    virtual bool init(Node *stencil);

protected:
    /**全屏绘制来清除模版bits
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
