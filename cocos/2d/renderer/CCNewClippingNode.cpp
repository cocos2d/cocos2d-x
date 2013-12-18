/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org

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

#include "CCNewClippingNode.h"
#include "CCGroupCommand.h"
#include "CCRenderer.h"
#include "CCCustomCommand.h"
#include "CCShaderCache.h"
#include "CCDirector.h"

NS_CC_BEGIN

// store the current stencil layer (position in the stencil buffer),
// this will allow nesting up to n ClippingNode,
// where n is the number of bits of the stencil buffer.
static GLint layer = -1;

static void setProgram(Node *n, GLProgram *p)
{
    n->setShaderProgram(p);

    for(const auto &child : n->getChildren())
        setProgram(child, p);
}

NewClippingNode *NewClippingNode::create()
{
    NewClippingNode* pRet = new NewClippingNode();
    if(pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

NewClippingNode *NewClippingNode::create(Node *pStencil)
{
    NewClippingNode* pRet = new NewClippingNode();
    if(pRet && pRet->init(pStencil))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

NewClippingNode::~NewClippingNode()
{

}

NewClippingNode::NewClippingNode()
:ClippingNode()
{
    currentStencilEnabled = GL_FALSE;
    currentStencilWriteMask = ~0;
    currentStencilFunc = GL_ALWAYS;
    currentStencilRef = 0;
    currentStencilValueMask = ~0;
    currentStencilFail = GL_KEEP;
    currentStencilPassDepthFail = GL_KEEP;
    currentStencilPassDepthPass = GL_KEEP;
    currentDepthWriteMask = GL_TRUE;

    currentAlphaTestEnabled = GL_FALSE;
    currentAlphaTestFunc = GL_ALWAYS;
    currentAlphaTestRef = 1;
}

void NewClippingNode::visit()
{
    //Add group command
    
    Renderer* renderer = Director::getInstance()->getRenderer();
    
    GroupCommand* groupCommand = GroupCommand::getCommandPool().generateCommand();
    groupCommand->init(0,_vertexZ);
    renderer->addCommand(groupCommand);

    renderer->pushGroup(groupCommand->getRenderQueueID());

    CustomCommand* beforeVisitCmd = CustomCommand::getCommandPool().generateCommand();
    beforeVisitCmd->init(0,_vertexZ);
    beforeVisitCmd->func = CC_CALLBACK_0(NewClippingNode::beforeVisit, this);
    renderer->addCommand(beforeVisitCmd);

    _stencil->visit();

    CustomCommand* afterDrawStencilCmd = CustomCommand::getCommandPool().generateCommand();
    afterDrawStencilCmd->init(0,_vertexZ);
    afterDrawStencilCmd->func = CC_CALLBACK_0(NewClippingNode::afterDrawStencil, this);
    renderer->addCommand(afterDrawStencilCmd);

    Node::visit();

    CustomCommand* afterVisitCmd = CustomCommand::getCommandPool().generateCommand();
    afterVisitCmd->init(0,_vertexZ);
    afterVisitCmd->func = CC_CALLBACK_0(NewClippingNode::afterVisit, this);
    renderer->addCommand(afterVisitCmd);

    renderer->popGroup();
}

void NewClippingNode::beforeVisit()
{
    ///////////////////////////////////
    // INIT

    // increment the current layer
    layer++;

    // mask of the current layer (ie: for layer 3: 00000100)
    GLint mask_layer = 0x1 << layer;
    // mask of all layers less than the current (ie: for layer 3: 00000011)
    GLint mask_layer_l = mask_layer - 1;
    // mask of all layers less than or equal to the current (ie: for layer 3: 00000111)
    mask_layer_le = mask_layer | mask_layer_l;

    // manually save the stencil state

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
//    GLboolean currentAlphaTestEnabled = GL_FALSE;
//    GLenum currentAlphaTestFunc = GL_ALWAYS;
//    GLclampf currentAlphaTestRef = 1;
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
        GLProgram *program = ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST);
        GLint alphaValueLocation = glGetUniformLocation(program->getProgram(), GLProgram::UNIFORM_NAME_ALPHA_TEST_VALUE);
        // set our alphaThreshold
        program->use();
        program->setUniformLocationWith1f(alphaValueLocation, _alphaThreshold);
        // we need to recursively apply this shader to all the nodes in the stencil node
        // XXX: we should have a way to apply shader to all nodes without having to do this
        setProgram(_stencil, program);

#endif
    }

    //Draw _stencil
}

void NewClippingNode::afterDrawStencil()
{
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
}


void NewClippingNode::afterVisit()
{
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

NS_CC_END
