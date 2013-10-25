//
//  C3DShadowMap.h

#ifndef SHADOWMAP_H
#define SHADOWMAP_H

#include "C3DNode.h"


namespace cocos3d
{
class C3DFrameBuffer;
class C3DTexture;
class C3DSampler;

/**
*Defines the shadow map.
*One model casts the shadow through rendering the depth of models into texture.
*One model receive the shadow through compare the value between self depth and the depth from the depth textue. 
*/
class C3DShadowMap : public C3DNode
{
public:  
	
    static C3DShadowMap* create(const char* id, unsigned int texWidth, unsigned int texHeight);
        
    C3DTexture* getDepthTexture() const;
    C3DSampler* getSampler() const;
    const C3DMatrix& getViewProjectionMatrix();
    const C3DMatrix& getTextureMatrix();
    const C3DVector3& getDimension() const { return _dimension; }
    void setDimension(float width, float height, float depth);
    bool beginDraw();
    void endDraw();
        
    virtual void transformChanged();

    void updateMatrix();

    virtual C3DNode* clone(C3DNode::CloneContext& context) const;
    virtual C3DNode::Type getType() const { return C3DNode::NodeType_ShadowMap; };

private:
    C3DShadowMap(const char* id);
    virtual ~C3DShadowMap();

    C3DFrameBuffer* _framebuffer;
    C3DMatrix _viewProjMatrix;
    C3DMatrix _textureMatrix;
    unsigned int _texWidth;
    unsigned int _texHeight;
    C3DVector3 _dimension;
    C3DSampler* _sampler;
    int _dirty;
};
}

#endif
