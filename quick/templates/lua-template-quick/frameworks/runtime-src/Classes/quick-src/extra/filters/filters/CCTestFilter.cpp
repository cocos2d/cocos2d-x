#include "CCTestFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN


//================== TestFilter

TestFilter* TestFilter::create()
{
	TestFilter* __filter = new TestFilter();
	__filter->autorelease();
	return __filter;
}

TestFilter* TestFilter::create(float $resolation)
{
	TestFilter* __filter = TestFilter::create();
	__filter->setParameter($resolation);
	return __filter;
}

TestFilter::TestFilter()
{
	this->shaderName = kCCFilterShader_test;
}

GLProgram* TestFilter::loadShader()
{
	GLProgram* __p = new GLProgram();
	CCLOG("TestFilter::loadShader, program: %p", __p);
	__p->initWithByteArrays(ccFilterShader_test_vert,
		ccFilterShader_test_frag);
	return __p;
}

void TestFilter::setParameter(float $resolation)
{
	//The initProgram() will perform in initSprite()
}

void TestFilter::initSprite(FilteredSprite* $sprite)
{
	Size __size = $sprite->getContentSize();
	/*_textureWidth = __size.width;
	_textureHeight = __size.height;*/
	_textureWidth = 480;
	_textureHeight = 320;
	initProgram();
}

void TestFilter::setAttributes(GLProgram* $cgp)
{
	CCLOG("TestFilter::setAttributes");
	$cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	$cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	$cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
}

void TestFilter::setUniforms(GLProgram* $cgp)
{
	Texture2D* __maskTex = Director::getInstance()->getTextureCache()->addImage("mask10.png");
	__maskTex->setAntiAliasTexParameters();

	Texture2D* __tex1 = Director::getInstance()->getTextureCache()->addImage("dirt.png");
	__tex1->setAntiAliasTexParameters();

	int u_mask = $cgp->getUniformLocationForName("u_mask");
	int u_texture1 = $cgp->getUniformLocationForName("u_texture1");
	int u_cctexture = $cgp->getUniformLocationForName("CC_Texture0");

	CCLOG("TestFilter::setUniforms u_mask:%d, u_texture1:%d, CC_Texture0:%d", u_mask, u_texture1, u_cctexture);
	$cgp->setUniformLocationWith1i(u_mask, 2);
	$cgp->setUniformLocationWith1i(u_texture1, 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, __maskTex->getName());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, __tex1->getName());
	glActiveTexture(GL_TEXTURE0);

	CCLOG("TestFilter::setUniforms _textureWidth:%.5f,_textureHeight:%.5f",
		_textureWidth, _textureHeight);
}

NS_CC_EXT_END
