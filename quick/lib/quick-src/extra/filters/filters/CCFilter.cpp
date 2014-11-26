/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2014      Jacky Tsang (zengrong.net)

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

#include "CCFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN

//================== Filter

Filter::Filter()
: shaderName(NULL)
, _pProgramState(NULL)
{
}


Filter::~Filter()
{
	CC_SAFE_RELEASE_NULL(_pProgramState);
}

GLProgram* Filter::getProgram()
{
	return _pProgramState->getGLProgram();
}

GLProgramState* Filter::getGLProgramState() {
    return _pProgramState;
}

void Filter::initProgram()
{
    if (nullptr != _pProgramState) {
        return;
    }
    
    GLProgram* __pProgram = nullptr;
    if (nullptr != shaderName) {
        __pProgram = GLProgramCache::getInstance()->getGLProgram(shaderName);
    }
	//CCLOG("CCFilter::initProgram %s, program:%d", shaderName, __pProgram);
	if (nullptr == __pProgram)
	{
		__pProgram = loadShader();

        if (nullptr != shaderName) {
            GLProgramCache::getInstance()->addGLProgram(__pProgram, this->shaderName);
        }
	}

    _pProgramState = GLProgramState::getOrCreateWithGLProgram(__pProgram);
    _pProgramState->retain();
}

void Filter::initSprite(FilteredSprite* $sprite)
{
    setUniforms(nullptr);
}

void Filter::draw()
{
	//setUniforms(getProgram());
}

GLProgram* Filter::loadShader()
{
	//CCLOG("Filter::loadShader");
	return NULL;
}

void Filter::setAttributes(GLProgram* $glp)
{
}

void Filter::setUniforms(GLProgram* $glp)
{
}

//================== SingleFloatParamFilter

SingleFloatParamFilter::SingleFloatParamFilter()
: _param(0.f)
{
}


void SingleFloatParamFilter::setParameter(float $param)
{
	_param = $param;
	initProgram();
}

NS_CC_EXT_END