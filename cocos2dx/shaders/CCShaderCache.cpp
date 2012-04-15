/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2011      Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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

#include "CCShaderCache.h"
#include "CCGLProgram.h"
#include "ccMacros.h"
#include "ccShaders.h"

NS_CC_BEGIN

static CCShaderCache *_sharedShaderCache = 0;

CCShaderCache* CCShaderCache::sharedShaderCache()
{
	if (!_sharedShaderCache) {
		_sharedShaderCache = new CCShaderCache();
		if (!_sharedShaderCache->init())
		{
			CC_SAFE_DELETE(_sharedShaderCache);
		}
	}
	return _sharedShaderCache;
}

void CCShaderCache::purgeSharedShaderCache()
{
	CC_SAFE_RELEASE_NULL(_sharedShaderCache);
}

CCShaderCache::CCShaderCache()
: m_pPrograms(0)
{

}

CCShaderCache::~CCShaderCache()
{
	CCLOGINFO("cocos2d deallocing 0x%X", this);
	m_pPrograms->release();
}

bool CCShaderCache::init()
{
	m_pPrograms = new CCDictionary();
	loadDefaultShaders();
	return true;
}
#define ENABLE_ALL_SHADER 1
void CCShaderCache::loadDefaultShaders()
{
	// Position Texture Color shader
	CCGLProgram *p = new CCGLProgram();
	p->initWithVertexShaderByteArray(ccPositionTextureColor_vert, ccPositionTextureColor_frag);

	p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);

	p->link();
	p->updateUniforms();

	m_pPrograms->setObject(p, kCCShader_PositionTextureColor);
	p->release();

	CHECK_GL_ERROR_DEBUG();
#if ENABLE_ALL_SHADER
	// Position Texture Color alpha test
	p = new CCGLProgram();
	p->initWithVertexShaderByteArray(ccPositionTextureColor_vert, ccPositionTextureColorAlphaTest_frag);

	p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);

	p->link();
	p->updateUniforms();

	m_pPrograms->setObject(p, kCCShader_PositionTextureColorAlphaTest);
	p->release();

	CHECK_GL_ERROR_DEBUG();

	//
	// Position, Color shader
	//
	p = new CCGLProgram();
	p->initWithVertexShaderByteArray(ccPositionColor_vert ,ccPositionColor_frag);

	p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);

	p->link();
	p->updateUniforms();

	m_pPrograms->setObject(p, kCCShader_PositionColor);
	p->release();

	CHECK_GL_ERROR_DEBUG();
	//
	// Position Texture shader
	//
	p = new CCGLProgram();
	p->initWithVertexShaderByteArray(ccPositionTexture_vert ,ccPositionTexture_frag);

	p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);

	p->link();
	p->updateUniforms();

	m_pPrograms->setObject(p, kCCShader_PositionTexture);
	p->release();

	CHECK_GL_ERROR_DEBUG();
#endif
	//
	// Position, Texture attribs, 1 Color as uniform shader
	//
	p = new CCGLProgram();
	p->initWithVertexShaderByteArray(ccPositionTexture_uColor_vert, ccPositionTexture_uColor_frag);

	p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);

	p->link();
	p->updateUniforms();

	m_pPrograms->setObject(p ,kCCShader_PositionTexture_uColor);
	p->release();

	CHECK_GL_ERROR_DEBUG();
#if ENABLE_ALL_SHADER
	//
	// Position Texture A8 Color shader
	//
	p = new CCGLProgram();
	p->initWithVertexShaderByteArray(ccPositionTextureA8Color_vert, ccPositionTextureA8Color_frag);

	p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);

	p->link();
	p->updateUniforms();

	m_pPrograms->setObject(p, kCCShader_PositionTextureA8Color);
	p->release();

	CHECK_GL_ERROR_DEBUG();

	//
	// Position and 1 color passed as a uniform (to similate glColor4ub )
	//
	p = new CCGLProgram();
	p->initWithVertexShaderByteArray(ccPosition_uColor_vert, ccPosition_uColor_frag);	

	p->addAttribute("aVertex", kCCVertexAttrib_Position);	

	p->link();	
	p->updateUniforms();	

	m_pPrograms->setObject(p, kCCShader_Position_uColor);	
	p->release();	

	CHECK_GL_ERROR_DEBUG();
#endif
}

CCGLProgram* CCShaderCache::programForKey(const char* key)
{
	return (CCGLProgram*)m_pPrograms->objectForKey(key);
}

void CCShaderCache::addProgram(CCGLProgram* program, const char* key)
{
    m_pPrograms->setObject(program, key);
}

NS_CC_END
