#include "C3DPostEffect.h"
#include "C3DPostProcess.h"

#include "C3DMaterial.h"
#include "C3DRenderState.h"
#include "C3DTechnique.h"
#include "C3DPass.h"
#include "MaterialParameter.h"

#include "Base.h"
#include "C3DVector3.h"
#include "C3DTexture.h"
#include "C3DSampler.h"
#include "C3DFrameBuffer.h"
#include "C3DMaterial.h"
#include "C3DModel.h"
#include "C3DSkinlessModel.h"
#include "Geo.h"
#include "C3DDepthStencilTarget.h"
#include "C3DRenderTarget.h"

namespace cocos3d
{
    
C3DPostEffect::C3DPostEffect(C3DPostProcess* postProcess, const char* szName)
{
    _name = szName;
    
    _postProcess = postProcess;
    //_postProcess->retain();
    _material = NULL;
    
}
    
bool C3DPostEffect::init(const char* szMaterial)
{
    SAFE_RELEASE(_material);
    _material = C3DMaterial::create(szMaterial);
    if (_material == NULL)
        return false;
    
    _material->retain();
    C3DTechnique* technique = _material->getTechnique(0u);
    
	technique->getPass(0u)->getParameter("u_texture")->setValue(_postProcess->getFramebufferSampler());
    return true;
}

C3DPostEffect::~C3DPostEffect()
{
    SAFE_RELEASE(_material);
	//SAFE_RELEASE(_postProcess);
}

C3DPostEffect* C3DPostEffect::create(PostEffectType type, C3DPostProcess* postProcess, const char* name)
{
	C3DPostEffect* pe = NULL;
    bool bInit = false;
	switch (type) {
        case Post_Effect_Color:
            pe = new C3DColorPE(postProcess, "color post effect");
            bInit = pe->init("posteffect/postprocess_Color.material");
            break;
            
        case Post_Effect_Outline:
            pe = new C3DOutlinePE(postProcess, "outline post effect");
            bInit = pe->init("posteffect/postprocess_Outline.material");
            break;
            
        case Post_Effect_Blur:
            pe = new C3DBlurPE(postProcess, "blur post effect");
            bInit = pe->init("posteffect/postprocess_Blur.material");
            break;
            
        case Post_Effect_SpaceWrap:
            pe = new C3DSpaceWrap(postProcess, "space wrap post effect");
            bInit = pe->init("posteffect/postprocess_SpaceWrap.material");
            break;
            
        case Post_Effect_Bloom:
            pe = new C3DBloomPE(postProcess, "bloom post effect");
            bInit = pe->init("posteffect/postprocess_Bloom.material");
            break;
            
        default:
            break;
    }
    
    if (!bInit)
        SAFE_RELEASE(pe);

	return pe;
}

    
void C3DPostEffect::draw()
{
    if (_material == NULL)
        return;
    
    if(_postProcess->getModel()->getMaterial() != _material)
    {
        _postProcess->getModel()->setMaterial(_material);
    }
    
    setShaderParameter();
    
    _postProcess->getModel()->draw();
}    

C3DBlurPE::~C3DBlurPE()
{
  
}

void C3DBlurPE::setShaderParameter()
{
	_material->getTechnique(0u)->getPass(0u)->getParameter("u_length")->setValue(1.0f / ((float)_postProcess->getFBWidth() / 2.0f));

}

//..
C3DColorPE::~C3DColorPE()
{
  
}

void C3DColorPE::setShaderParameter()
{
	//gray C3DVector3(0.299f, 0.587f, 0.114f)

    
	_material->getTechnique(0u)->getPass(0u)->getParameter("u_rate")->setValue(_colorRate);

}

//......

C3DOutlinePE::~C3DOutlinePE()
{
  
}

void C3DOutlinePE::setShaderParameter()
{
	_material->getTechnique(0u)->getPass(0u)->getParameter("u_w")->setValue(2.0f/(float)_postProcess->getFBWidth());
	_material->getTechnique(0u)->getPass(0u)->getParameter("u_h")->setValue(2.0f/(float)_postProcess->getFBHeight());

}

C3DSpaceWrap::C3DSpaceWrap(C3DPostProcess* postProcess, const char* name) : C3DPostEffect(postProcess,name)
{
	_pixelSize = C3DVector2(1.f / 1024.f, 1.f / 768.f);
	_wrapSpeed = 1.5f;
	_wrapScale = 0.05f;
	
	int w = 256, h = 256;

	unsigned int* data = new unsigned int[w * h];
    int count = sizeof(unsigned int);
	for(int y = 0; y < h; y++)
	{
		for(int x = 0; x < w; x++)
		{
			float fx = x * (1.0f / 256) - 0.5f;
			float fy = y * (1.0f / 256) - 0.5f;
			float r  = sqrtf(fx * fx + fy * fy);

			int iDu = (int)(32 * cosf(4.0f * (fx + fy) * MATH_PI)) + 128;
			int iDv = (int)(32 * sinf(4.0f * (fx + fy) * MATH_PI)) + 128;

			data[y * w + x] = iDu << 16 | iDv << 8 | 0xff << 24;
		}
	}
	C3DTexture* texture = C3DTexture::create(w, h, C3DTexture::RGBA, data, false);
	_wrapSampler = new C3DSampler(texture);
	_wrapSampler->setWrapMode(Texture_Wrap_REPEAT, Texture_Wrap_REPEAT);

	delete[] data;
}

C3DSpaceWrap::~C3DSpaceWrap()
{
	SAFE_RELEASE(_wrapSampler);
}

void C3DSpaceWrap::setShaderParameter()
{
	static C3DVector2 pixelsize(1.f / 1024.f, 1.f / 768.f);
	static float gtime = 0;
	gtime += 0.16f;
    
    C3DPass* pass = _material->getTechnique(0u)->getPass(0u);
	
	pass->getParameter("g_vPixelSize")->setValue(pixelsize);
	pass->getParameter("g_fWarpScale")->setValue(_wrapScale);
	pass->getParameter("g_fWarpSpeed")->setValue(_wrapSpeed);
	pass->getParameter("u_pertubeSampler")->setValue(_wrapSampler);
	pass->getParameter("g_fTime")->setValue(gtime);
}


/////////////
    
C3DBloomPE::C3DBloomPE(C3DPostProcess* postProcess, const char* name): C3DPostEffect(postProcess, name), _brightFrameBuffer(NULL), _blurFrameBufferX(NULL), _blurFrameBufferY(NULL)
{
        
}
    
bool C3DBloomPE::init(const char* szMaterial)
{
    bool bRet = C3DPostEffect::init(szMaterial);
    if (!bRet)
        return false;
    
    CCAssert(_material->getTechniqueCount() == 4, "material error");
    return initBloomParam();
}
    
    
C3DBloomPE::~C3DBloomPE()
{
    SAFE_RELEASE(_blurFrameBufferX);
    SAFE_RELEASE(_blurFrameBufferY);
    SAFE_RELEASE(_brightFrameBuffer);
}
    
bool C3DBloomPE::initBloomParam()
{
    unsigned int fmtColor = C3DTexture::RGBA;
    unsigned int fmtDepth = C3DDepthStencilTarget::DEPTH16;
    
    _brightFrameBuffer = C3DFrameBuffer::create("bloom_postprocess_bright", _postProcess->getFBWidth(), _postProcess->getFBHeight(), fmtColor, fmtDepth);
    _blurFrameBufferX = C3DFrameBuffer::create("bloom_postprocess_blurX", _postProcess->getFBWidth(), _postProcess->getFBHeight(), fmtColor, fmtDepth);
    _blurFrameBufferY = C3DFrameBuffer::create("bloom_postprocess_blurY", _postProcess->getFBWidth(), _postProcess->getFBHeight(), fmtColor, fmtDepth);
        
    if (_brightFrameBuffer == NULL || _blurFrameBufferX == NULL || _blurFrameBufferY == NULL)
    {
        return  false;
    }
    _brightFrameBuffer->retain();
    _blurFrameBufferX->retain();
    _blurFrameBufferY->retain();
        
    setBloomThreshold(0.25f);
        
    C3DSampler* sampler = _postProcess->getFramebufferSampler();
    sampler->setFilterMode(Texture_Filter_LINEAR, Texture_Filter_LINEAR);
    sampler->setWrapMode(Texture_Wrap_CLAMP, Texture_Wrap_CLAMP);
    //C3DPass* pass0 = _material->getTechnique(0u)->getPass(0u);
    C3DPass* pass1 = _material->getTechnique(1u)->getPass(0u);
    C3DPass* pass2 = _material->getTechnique(2u)->getPass(0u);
    C3DPass* pass3 = _material->getTechnique(3u)->getPass(0u);
        
    //pass0->getParameter("u_texture")->setValue(sampler);
    pass3->getParameter("u_texture")->setValue(sampler);
        
    sampler = C3DSampler::create(_brightFrameBuffer->getRenderTarget()->getTexture());
    sampler->setFilterMode(Texture_Filter_LINEAR, Texture_Filter_LINEAR);
    sampler->setWrapMode(Texture_Wrap_CLAMP, Texture_Wrap_CLAMP);
    pass1->getParameter("u_texture")->setValue(sampler);
    SAFE_RELEASE(sampler);
        
    sampler = C3DSampler::create(_blurFrameBufferX->getRenderTarget()->getTexture());
    sampler->setFilterMode(Texture_Filter_LINEAR, Texture_Filter_LINEAR);
    sampler->setWrapMode(Texture_Wrap_CLAMP, Texture_Wrap_CLAMP);
    pass2->getParameter("u_texture")->setValue(sampler);
    SAFE_RELEASE(sampler);
        
    sampler = C3DSampler::create(_blurFrameBufferY->getRenderTarget()->getTexture());
    sampler->setFilterMode(Texture_Filter_LINEAR, Texture_Filter_LINEAR);
    sampler->setWrapMode(Texture_Wrap_CLAMP, Texture_Wrap_CLAMP);
    pass3->getParameter("u_bloomTexture")->setValue(sampler);
    SAFE_RELEASE(sampler);
    
    C3DVector2 vdelta;
    vdelta.x = 1.0f / ((float)_postProcess->getFBWidth() / 2.0f);
    vdelta.y = 0.0f;
    pass1->getParameter("u_delta")->setValue(vdelta);
    vdelta.x = 0.0f;
    vdelta.y = 1.0f / ((float)_postProcess->getFBHeight() / 2.0f);
    pass2->getParameter("u_delta")->setValue(vdelta);
        
    return true;
}
    

void C3DBloomPE::draw()
{
    if (_material == NULL)
        return;
    
    C3DModel* model = _postProcess->getModel();
    if(model->getMaterial() != _material)
    {
        _postProcess->getModel()->setMaterial(_material);
    }
        
    //extract brightness
    _brightFrameBuffer->bind();
    _material->setTechnique(C3DMaterial::TECH_USAGE_SCREEN, 0u);
    model->draw();
    _brightFrameBuffer->unbind();
        
    //blur x
    _blurFrameBufferX->bind();
    _material->setTechnique(C3DMaterial::TECH_USAGE_SCREEN, 1u);
    model->draw();
    _blurFrameBufferX->unbind();
        
    //blur y
    _blurFrameBufferY->bind();
    _material->setTechnique(C3DMaterial::TECH_USAGE_SCREEN, 2u);
    model->draw();
    _blurFrameBufferY->unbind();
        
        
    _material->setTechnique(C3DMaterial::TECH_USAGE_SCREEN, 3u);
    model->draw();
        
        
}
    
void C3DBloomPE::setBloomThreshold(float threshold)
{
    CCAssert(_material, "material null");
    _BloomThreshold = threshold;
        
    C3DTechnique* tech = _material->getTechnique(0u);
    C3DPass* pass = tech->getPass(0u);
        
    pass->getParameter("u_bloomThreshold")->setValue(_BloomThreshold);
}

float C3DBloomPE::getBloomThreshold() const
{
    return _BloomThreshold;
}



	
   


}