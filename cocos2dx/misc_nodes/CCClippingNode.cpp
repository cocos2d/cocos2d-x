/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 * cocos2d-x: http://www.cocos2d-x.org
 *
 * Copyright (c) 2012 Pierre-David Bélanger
 * Copyright (c) 2012 cocos2d-x.org
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

#include "CCClippingNode.h"
#include "kazmath/GL/matrix.h"
#include "shaders/CCGLProgram.h"
#include "shaders/CCShaderCache.h"
#include "CCDirector.h"
#include "draw_nodes/CCDrawingPrimitives.h"

NS_CC_BEGIN

static GLint g_sStencilBits = -1;

static void setProgram(Node *n, GLProgram *p)
{
    n->setShaderProgram(p);
    if (!n->getChildren()) return;
    
    Object* pObj = NULL;
    CCARRAY_FOREACH(n->getChildren(), pObj)
    {
        setProgram(static_cast<Node*>(pObj), p);
    }
}

ClippingNode::ClippingNode()
: _stencil(NULL)
, _alphaThreshold(0.0f)
, _inverted(false)
{}

ClippingNode::~ClippingNode()
{
    CC_SAFE_RELEASE(_stencil);
}

ClippingNode* ClippingNode::create()
{
    ClippingNode *pRet = new ClippingNode();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

ClippingNode* ClippingNode::create(Node *pStencil)
{
    ClippingNode *pRet = new ClippingNode();
    if (pRet && pRet->init(pStencil))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

bool ClippingNode::init()
{
    return init(NULL);
}

bool ClippingNode::init(Node *pStencil)
{
    CC_SAFE_RELEASE(_stencil);
    _stencil = pStencil;
    CC_SAFE_RETAIN(_stencil);
    
    _alphaThreshold = 1;
    _inverted = false;
    // get (only once) the number of bits of the stencil buffer
    static bool once = true;
    if (once)
    {
        glGetIntegerv(GL_STENCIL_BITS, &g_sStencilBits);
        if (g_sStencilBits <= 0)
        {
            CCLOG("Stencil buffer is not enabled.");
        }
        once = false;
    }
    
    return true;
}

void ClippingNode::onEnter()
{
    Node::onEnter();
    _stencil->onEnter();
}

void ClippingNode::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
    _stencil->onEnterTransitionDidFinish();
}

void ClippingNode::onExitTransitionDidStart()
{
    _stencil->onExitTransitionDidStart();
    Node::onExitTransitionDidStart();
}

void ClippingNode::onExit()
{
    _stencil->onExit();
    Node::onExit();
}

void ClippingNode::drawFullScreenQuadClearStencil()
{
    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLPushMatrix();
    kmGLLoadIdentity();
    
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLPushMatrix();
    kmGLLoadIdentity();
    
    DrawPrimitives::drawSolidRect(Point(-1,-1), Point(1,1), Color4F(1, 1, 1, 1));
    
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLPopMatrix();
    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLPopMatrix();
}

void ClippingNode::visit()
{
    // if stencil buffer disabled
    if (g_sStencilBits < 1)
    {
        // draw everything, as if there where no stencil
        Node::visit();
        return;
    }
    
    // return fast (draw nothing, or draw everything if in inverted mode) if:
    // - nil stencil node
    // - or stencil node invisible:
    if (!_stencil || !_stencil->isVisible())
    {
        if (_inverted)
        {
            // draw everything
            Node::visit();
        }
        return;
    }
    
    // store the current stencil layer (position in the stencil buffer),
    // this will allow nesting up to n ClippingNode,
    // where n is the number of bits of the stencil buffer.
    static GLint layer = -1;
    
    // all the _stencilBits are in use?
    if (layer + 1 == g_sStencilBits)
    {
        // warn once
        static bool once = true;
        if (once)
        {
            char warning[200] = {0};
            snprintf(warning, sizeof(warning), "Nesting more than %d stencils is not supported. Everything will be drawn without stencil for this node and its childs.", g_sStencilBits);
            CCLOG("%s", warning);
            
            once = false;
        }
        // draw everything, as if there where no stencil
        Node::visit();
        return;
    }
    
    ///////////////////////////////////
    // INIT
    
    // increment the current layer
    layer++;
    
    // mask of the current layer (ie: for layer 3: 00000100)
    GLint mask_layer = 0x1 << layer;
    // mask of all layers less than the current (ie: for layer 3: 00000011)
    GLint mask_layer_l = mask_layer - 1;
    // mask of all layers less than or equal to the current (ie: for layer 3: 00000111)
    GLint mask_layer_le = mask_layer | mask_layer_l;
    
    // manually save the stencil state
    GLboolean currentStencilEnabled = GL_FALSE;
    GLuint currentStencilWriteMask = ~0;
    GLenum currentStencilFunc = GL_ALWAYS;
    GLint currentStencilRef = 0;
    GLuint currentStencilValueMask = ~0;
    GLenum currentStencilFail = GL_KEEP;
    GLenum currentStencilPassDepthFail = GL_KEEP;
    GLenum currentStencilPassDepthPass = GL_KEEP;
    currentStencilEnabled = glIsEnabled(GL_STENCIL_TEST);
    glGetIntegerv(GL_STENCIL_WRITEMASK, (GLint *)&currentStencilWriteMask);
    glGetIntegerv(GL_STENCIL_FUNC, (GLint *)&currentStencilFunc);
    glGetIntegerv(GL_STENCIL_REF, &currentStencilRef);
    glGetIntegerv(GL_STENCIL_VALUE_MASK, (GLint *)&currentStencilValueMask);
    glGetIntegerv(GL_STENCIL_FAIL, (GLint *)&currentStencilFail);
    glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL, (GLint *)&currentStencilPassDepthFail);
    glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS, (GLint *)&currentStencilPassDepthPass);
    
    // enable stencil use
    glEnable(GL_STENCIL_TEST);
    // check for OpenGL error while enabling stencil test
    CHECK_GL_ERROR_DEBUG();
    
    // all bits on the stencil buffer are readonly, except the current layer bit,
    // this means that operation like glClear or glStencilOp will be masked with this value
    glStencilMask(mask_layer);
    
    // manually save the depth test state
    //GLboolean currentDepthTestEnabled = GL_TRUE;
    GLboolean currentDepthWriteMask = GL_TRUE;
    //currentDepthTestEnabled = glIsEnabled(GL_DEPTH_TEST);
    glGetBooleanv(GL_DEPTH_WRITEMASK, &currentDepthWriteMask);
    
    // disable depth test while drawing the stencil
    //glDisable(GL_DEPTH_TEST);
    // disable update to the depth buffer while drawing the stencil,
    // as the stencil is not meant to be rendered in the real scene,
    // it should never prevent something else to be drawn,
    // only disabling depth buffer update should do
    glDepthMask(GL_FALSE);
    
    ///////////////////////////////////
    // CLEAR STENCIL BUFFER
    
    // manually clear the stencil buffer by drawing a fullscreen rectangle on it
    // setup the stencil test func like this:
    // for each pixel in the fullscreen rectangle
    //     never draw it into the frame buffer
    //     if not in inverted mode: set the current layer value to 0 in the stencil buffer
    //     if in inverted mode: set the current layer value to 1 in the stencil buffer
    glStencilFunc(GL_NEVER, mask_layer, mask_layer);
    glStencilOp(!_inverted ? GL_ZERO : GL_REPLACE, GL_KEEP, GL_KEEP);
    
    // draw a fullscreen solid rectangle to clear the stencil buffer
    //ccDrawSolidRect(Point::ZERO, ccpFromSize([[Director sharedDirector] winSize]), Color4F(1, 1, 1, 1));
    drawFullScreenQuadClearStencil();
    
    ///////////////////////////////////
    // DRAW CLIPPING STENCIL
    
    // setup the stencil test func like this:
    // for each pixel in the stencil node
    //     never draw it into the frame buffer
    //     if not in inverted mode: set the current layer value to 1 in the stencil buffer
    //     if in inverted mode: set the current layer value to 0 in the stencil buffer
    glStencilFunc(GL_NEVER, mask_layer, mask_layer);
    glStencilOp(!_inverted ? GL_REPLACE : GL_ZERO, GL_KEEP, GL_KEEP);
    
    // enable alpha test only if the alpha threshold < 1,
    // indeed if alpha threshold == 1, every pixel will be drawn anyways
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WINDOWS || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    GLboolean currentAlphaTestEnabled = GL_FALSE;
    GLenum currentAlphaTestFunc = GL_ALWAYS;
    GLclampf currentAlphaTestRef = 1;
#endif
    if (_alphaThreshold < 1) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WINDOWS || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        // manually save the alpha test state
        currentAlphaTestEnabled = glIsEnabled(GL_ALPHA_TEST);
        glGetIntegerv(GL_ALPHA_TEST_FUNC, (GLint *)&currentAlphaTestFunc);
        glGetFloatv(GL_ALPHA_TEST_REF, &currentAlphaTestRef);
        // enable alpha testing
        glEnable(GL_ALPHA_TEST);
        // check for OpenGL error while enabling alpha test
        CHECK_GL_ERROR_DEBUG();
        // pixel will be drawn only if greater than an alpha threshold
        glAlphaFunc(GL_GREATER, _alphaThreshold);
#else
        // since glAlphaTest do not exists in OES, use a shader that writes
        // pixel only if greater than an alpha threshold
        GLProgram *program = ShaderCache::getInstance()->programForKey(GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST);
        GLint alphaValueLocation = glGetUniformLocation(program->getProgram(), GLProgram::UNIFORM_NAME_ALPHA_TEST_VALUE);
        // set our alphaThreshold
        program->setUniformLocationWith1f(alphaValueLocation, _alphaThreshold);
        // we need to recursively apply this shader to all the nodes in the stencil node
        // XXX: we should have a way to apply shader to all nodes without having to do this
        setProgram(_stencil, program);
       
#endif
    }
    
    // draw the stencil node as if it was one of our child
    // (according to the stencil test func/op and alpha (or alpha shader) test)
    kmGLPushMatrix();
    transform();
    _stencil->visit();
    kmGLPopMatrix();
    
    // restore alpha test state
    if (_alphaThreshold < 1)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WINDOWS || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        // manually restore the alpha test state
        glAlphaFunc(currentAlphaTestFunc, currentAlphaTestRef);
        if (!currentAlphaTestEnabled)
        {
            glDisable(GL_ALPHA_TEST);
        }
#else
// XXX: we need to find a way to restore the shaders of the stencil node and its childs
#endif
    }
    
    // restore the depth test state
    glDepthMask(currentDepthWriteMask);
    //if (currentDepthTestEnabled) {
    //    glEnable(GL_DEPTH_TEST);
    //}
    
    ///////////////////////////////////
    // DRAW CONTENT
    
    // setup the stencil test func like this:
    // for each pixel of this node and its childs
    //     if all layers less than or equals to the current are set to 1 in the stencil buffer
    //         draw the pixel and keep the current layer in the stencil buffer
    //     else
    //         do not draw the pixel but keep the current layer in the stencil buffer
    glStencilFunc(GL_EQUAL, mask_layer_le, mask_layer_le);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    
    // draw (according to the stencil test func) this node and its childs
    Node::visit();
    
    ///////////////////////////////////
    // CLEANUP
    
    // manually restore the stencil state
    glStencilFunc(currentStencilFunc, currentStencilRef, currentStencilValueMask);
    glStencilOp(currentStencilFail, currentStencilPassDepthFail, currentStencilPassDepthPass);
    glStencilMask(currentStencilWriteMask);
    if (!currentStencilEnabled)
    {
        glDisable(GL_STENCIL_TEST);
    }
    
    // we are done using this layer, decrement
    layer--;
}

Node* ClippingNode::getStencil() const
{
    return _stencil;
}

void ClippingNode::setStencil(Node *pStencil)
{
    CC_SAFE_RELEASE(_stencil);
    _stencil = pStencil;
    CC_SAFE_RETAIN(_stencil);
}

GLfloat ClippingNode::getAlphaThreshold() const
{
    return _alphaThreshold;
}

void ClippingNode::setAlphaThreshold(GLfloat fAlphaThreshold)
{
    _alphaThreshold = fAlphaThreshold;
}

bool ClippingNode::isInverted() const
{
    return _inverted;
}

void ClippingNode::setInverted(bool bInverted)
{
    _inverted = bInverted;
}

NS_CC_END
