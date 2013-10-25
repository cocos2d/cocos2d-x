#include "C3DPostProcess.h"
#include "C3DFrameBuffer.h"
#include "C3DRenderTarget.h"
#include "C3DDepthStencilTarget.h"
#include "C3DTexture.h"
#include "C3DSampler.h"
#include "C3DMaterial.h"
#include "C3DRenderState.h"
#include "C3DTechnique.h"
#include "C3DPass.h"
#include "MaterialParameter.h"
#include "C3DSkinlessModel.h"
#include "Geo.h"
#include "Base.h"
#include "C3DMesh.h"
#include "C3DRenderSystem.h"
#include "C3DVector4.h"
#include "C3DPostEffect.h"
#include <map>

namespace cocos3d
{
   


C3DPostProcess::C3DPostProcess(const char* id,C3DFrameBuffer* buffer) 
	: C3DNode(id), _framebuffer(buffer)      
{	
	
	_curPostEffect = NULL;

	
	C3DMesh* mesh = Geo::createQuadFullscreen();
	_model = C3DSkinlessModel::create(mesh);
	SAFE_RELEASE(mesh);


	_model->setNode(this);

	_isDraw = false;
	
}

C3DPostProcess::~C3DPostProcess()
{
  
    SAFE_RELEASE(_framebuffer);
    
    SAFE_RELEASE(_sampler);

	 SAFE_RELEASE(_model);

	size_t i;
    for (i = 0; i < _postEffects.size(); i++) {
        SAFE_RELEASE(_postEffects[i]);
    }
    _postEffects.clear();


}

C3DPostProcess* C3DPostProcess::create(const char* id, unsigned int texWidth, unsigned int texHeight/*, const char* techniqueId*/)
{
	unsigned int fmtColor = C3DTexture::RGBA;
	//unsigned int fmtDepth = C3DDepthStencilTarget::DEPTH24_STENCIL8;
	unsigned int fmtDepth = C3DDepthStencilTarget::DEPTH16;

	C3DFrameBuffer* framebuffer = C3DFrameBuffer::create(id, texWidth, texHeight, fmtColor, fmtDepth);
	if (!framebuffer)
		return NULL;
	framebuffer->retain();		

		
	C3DPostProcess* pp = new C3DPostProcess(id,framebuffer);
	pp->_fbWidth = texWidth;
	pp->_fbHeight = texHeight;
	pp->autorelease();
    
    C3DSampler* sampler = C3DSampler::create(pp->_framebuffer->getRenderTarget()->getTexture());
	sampler->setFilterMode(Texture_Filter_LINEAR, Texture_Filter_LINEAR);
	sampler->setWrapMode(Texture_Wrap_CLAMP, Texture_Wrap_CLAMP);
    pp->_sampler = sampler;
    
	return pp; 
}
    

bool C3DPostProcess::beginDraw()
{
    if (_curPostEffect == NULL)
        return true;
    
    CCAssert(_framebuffer, "Empty frame buffer");;
    _framebuffer->bind();
        
  //  glClear(GL_DEPTH_BUFFER_BIT);
		
	 static C3DVector4 clearColor =  C3DVector4::zero();
	C3DRenderSystem::getInstance()->clear(CLEAR_COLOR_DEPTH,&clearColor,1.0f,0);

	_isDraw = false;
    return true;
}

void C3DPostProcess::endDraw()
{
    if (_curPostEffect == NULL)
        return;
    
    CCAssert(_framebuffer, "Empty frame buffer");;
    _framebuffer->unbind();

	_isDraw = true;
}

void C3DPostProcess::draw()
{
	if(_isDraw == false)
		return;

    if (_curPostEffect)
        _curPostEffect->draw();
}
    
void C3DPostProcess::setPostEffect(PostEffectType type)
{
    for (size_t i = 0; i < _postEffects.size(); i++) {
        if (_postEffects[i]->getPostEffectType() == type)
        {
            _curPostEffect = _postEffects[i];
            return;
        }
    }
    
    _curPostEffect = C3DPostEffect::create(type, this, "");
    _postEffects.push_back(_curPostEffect);
}

unsigned int C3DPostProcess::getFBWidth()
{
	return _fbWidth;
}

unsigned int C3DPostProcess::getFBHeight()
{
	return _fbHeight;
}

void C3DPostProcess::transformChanged()
{
    C3DNode::transformChanged();
    //  _dirty |= DIRTY_MATRIX;

}
	


}