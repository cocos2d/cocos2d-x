//
// Created by NiTe Luo on 11/13/13.
//


#include "NewClippingNode.h"
#include "GroupCommand.h"
#include "Renderer.h"
#include "CustomCommand.h"
#include "CCShaderCache.h"

NS_CC_BEGIN

// store the current stencil layer (position in the stencil buffer),
// this will allow nesting up to n ClippingNode,
// where n is the number of bits of the stencil buffer.
static GLint layer = -1;

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
}

void NewClippingNode::visit()
{
    //Add group command
    GroupCommand* groupCommand = new GroupCommand(0,0);
    Renderer::getInstance()->addCommand(groupCommand, groupCommand->getRenderQueueID());

    _stencil->visit();

    Node::visit();

    CustomCommand* prepareStencil = new CustomCommand(0,0);
    prepareStencil->func = CC_CALLBACK_0(NewClippingNode::beforeVisit, this);
}

void NewClippingNode::beforeVisit()
{
    // store the current stencil layer (position in the stencil buffer),
    // this will allow nesting up to n ClippingNode,
    // where n is the number of bits of the stencil buffer.
    static GLint layer = -1;

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

    //Draw _stencil

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
