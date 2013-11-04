#include "C3DShadowMap.h"
#include "C3DFrameBuffer.h"
#include "C3DDepthStencilTarget.h"
#include "C3DTexture.h"
#include "C3DSampler.h"

namespace cocos3d
{
    enum 
    {
        DIRTY_DIMENSION = 1,
        DIRTY_MATRIX = 2,
    };
    
    C3DShadowMap::C3DShadowMap(const char* id) : C3DNode(id), _framebuffer(NULL), _texWidth(0), _texHeight(0), 
        _dimension(1.0f, 1.0f, 1.0f), _dirty(0), _sampler(NULL)
    {

    }

    C3DShadowMap::~C3DShadowMap()
    {
        SAFE_RELEASE(_sampler);
        SAFE_RELEASE(_framebuffer);
    }

    C3DShadowMap* C3DShadowMap::create(const char* id, unsigned int texWidth, unsigned int texHeight)
    {
        unsigned int fmtColor = 0;
        unsigned int fmtDepth = C3DDepthStencilTarget::DEPTH16;
        bool supportNullColor = false;

        if (!supportNullColor)
        {
            fmtColor = C3DTexture::RGBA;
        }
        C3DFrameBuffer* framebuffer = C3DFrameBuffer::create(id, texWidth, texHeight, fmtColor, fmtDepth);

        if (!framebuffer)
            return NULL;

        framebuffer->retain();
        C3DShadowMap* shadowMap = new C3DShadowMap(id);
        shadowMap->_framebuffer = framebuffer;
        shadowMap->_texWidth = texWidth;
        shadowMap->_texHeight = texHeight;

        C3DSampler* samp = C3DSampler::create(shadowMap->getDepthTexture());
        //samp->retain();
        samp->setFilterMode(Texture_Filter_LINEAR, Texture_Filter_LINEAR);
        samp->setWrapMode(Texture_Wrap_CLAMP, Texture_Wrap_CLAMP);

        shadowMap->_sampler = samp;
        shadowMap->autorelease();
        return shadowMap;
    }

    C3DTexture* C3DShadowMap::getDepthTexture() const
    {
        if (!_framebuffer || !_framebuffer->getDepthStencilTarget())
            return NULL;

        return _framebuffer->getDepthStencilTarget()->getTexture();
    }

    const C3DMatrix& C3DShadowMap::getViewProjectionMatrix()
    {
        if (_dirty)
            updateMatrix();
        return _viewProjMatrix;
    }

    const C3DMatrix& C3DShadowMap::getTextureMatrix()
    {
        if (_dirty)
            updateMatrix();
        return _textureMatrix;
    }

    bool C3DShadowMap::beginDraw()
    {
        CCAssert(_framebuffer, "Empty frame buffer");;
        _framebuffer->bind();
        
        glClear(GL_DEPTH_BUFFER_BIT);
        return true;
    }

    void C3DShadowMap::endDraw()
    {
        CCAssert(_framebuffer, "Empty frame buffer");;
        _framebuffer->unbind();
    }

    void C3DShadowMap::transformChanged()
    {
        C3DNode::transformChanged();
        _dirty |= DIRTY_MATRIX;

    }

    C3DNode* C3DShadowMap::clone(C3DNode::CloneContext& context) const
    {
        C3DShadowMap* other = C3DShadowMap::create(_id.c_str(), _texWidth, _texHeight);
        other->copyFrom(this, context);
        other->setDimension(_dimension.x, _dimension.y, _dimension.z);
        return other;
    }

    void C3DShadowMap::setDimension(float width, float height, float depth) 
    {
        _dimension.set(width, height, depth);
        _dirty |= DIRTY_DIMENSION;
    }

    void C3DShadowMap::updateMatrix()
    {
        C3DMatrix viewMatrix = getWorldMatrix();
        viewMatrix.invert();

        C3DMatrix projMatrix;

        C3DMatrix::createOrthographic(_dimension.x * 2, _dimension.y * 2, 0.0, _dimension.z, &projMatrix);
        

        C3DMatrix::multiply(projMatrix, viewMatrix, &_viewProjMatrix);

        C3DMatrix texBiasMatrix(
            0.5f, 0, 0, 0.5f,
            0, 0.5f, 0, 0.5f,
            0, 0, 0.5f, 0.5f,
            0, 0, 0, 1
            );

        C3DMatrix::multiply(texBiasMatrix, _viewProjMatrix, &_textureMatrix);

        _dirty = 0;
    }

    C3DSampler* C3DShadowMap::getSampler() const
    {
        return _sampler;
    }


}