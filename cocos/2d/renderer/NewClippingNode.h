//
// Created by NiTe Luo on 11/13/13.
//



#ifndef __NewClippingNode_H_
#define __NewClippingNode_H_

#include "CCPlatformMacros.h"
#include "CCClippingNode.h"


NS_CC_BEGIN

class NewClippingNode : public ClippingNode
{
public:
    static NewClippingNode* create();
    static NewClippingNode* create(Node* pStencil);

    virtual ~NewClippingNode();

    virtual void visit() override;

protected:
    NewClippingNode();

    void beforeVisit();
    void afterDrawStencil();
    void afterVisit();

protected:
    GLboolean currentStencilEnabled;
    GLuint currentStencilWriteMask;
    GLenum currentStencilFunc;
    GLint currentStencilRef;
    GLuint currentStencilValueMask;
    GLenum currentStencilFail;
    GLenum currentStencilPassDepthFail;
    GLenum currentStencilPassDepthPass;
    GLboolean currentDepthWriteMask;

    GLboolean currentAlphaTestEnabled;
    GLenum currentAlphaTestFunc;
    GLclampf currentAlphaTestRef;

    GLint mask_layer_le;
};

NS_CC_END

#endif //__NewClippingNode_H_
