/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2011 Ricardo Quesada
 * Copyright (c) 2011 Zynga Inc.
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
 */

#include "CCShaderCache.h"
#include "CCGLProgram.h"
#include "ccMacros.h"

NS_CC_BEGIN

static CCShaderCache *_sharedShaderCache = 0;

CCShaderCache* CCShaderCache::sharedShaderCache()
{
	if (!_sharedShaderCache) {
		_sharedShaderCache = new CCShaderCache();
		CCAssert(_sharedShaderCache == 0, "Attempted to allocate a second instance of a singleton.");
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
: programs_(0)
{

}

CCShaderCache::~CCShaderCache()
{
	CCLOGINFO("cocos2d deallocing 0x%X", this);
	programs_->release();
}

bool CCShaderCache::init()
{
	programs_ = new CCMutableDictionary<std::string, CCGLProgram*>();
	loadDefaultShaders();
	return true;
}

void CCShaderCache::loadDefaultShaders()
{
	// Position Texture Color shader
	CCGLProgram *p = new CCGLProgram();
	p->initWithVertexShaderFilename("PositionTextureColor.vsh", "PositionTextureColor.fsh");

	p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);

	p->link();
	p->updateUniforms();

	programs_->setObject(p, kCCShader_PositionTextureColor);
	p->release();

	// Position Texture Color alpha test
	p = new CCGLProgram();
	p->initWithVertexShaderFilename("PositionTextureColor.vsh", "PositionTextureColorAlphaTest.fsh");

	p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);

	p->link();
	p->updateUniforms();

	programs_->setObject(p, kCCShader_PositionTextureColorAlphaTest);
	p->release();

	//
	// Position, Color shader
	//
	p = new CCGLProgram();
	p->initWithVertexShaderFilename("PositionColor.vsh" ,"PositionColor.fsh");

	p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);

	p->link();
	p->updateUniforms();

	programs_->setObject(p, kCCShader_PositionColor);
	p->release();

	//
	// Position Texture shader
	//
	p = new CCGLProgram();
	p->initWithVertexShaderFilename("PositionTexture.vsh" ,"PositionTexture.fsh");

	p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);

	p->link();
	p->updateUniforms();

	programs_->setObject(p, kCCShader_PositionTexture);
	p->release();

	//
	// Position, Texture attribs, 1 Color as uniform shader
	//
	p = new CCGLProgram();
	p->initWithVertexShaderFilename("PositionTexture_uColor.vsh", "PositionTexture_uColor.fsh");

	p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);

	p->link();
	p->updateUniforms();

	programs_->setObject(p ,kCCShader_PositionTexture_uColor);
	p->release();

	//
	// Position Texture A8 Color shader
	//
	p = new CCGLProgram();
	p->initWithVertexShaderFilename("PositionTextureA8Color.vsh", "PositionTextureA8Color.fsh");

	p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);

	p->link();
	p->updateUniforms();

	programs_->setObject(p, kCCShader_PositionTextureA8Color);
	p->release();

//TODO:	CHECK_GL_ERROR_DEBUG();
}

CCGLProgram* CCShaderCache::programForKey(const char* key)
{
	return programs_->objectForKey(key);
}

void CCShaderCache::addProgram(CCGLProgram* program, const char* key)
{
    programs_->setObject(program, key);
}

NS_CC_END
