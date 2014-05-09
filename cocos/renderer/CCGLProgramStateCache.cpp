/****************************************************************************
Copyright 2013-2014 Chukong Technologies Inc.

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
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN false EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "renderer/CCGLProgramStateCache.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCGLProgram.h"


NS_CC_BEGIN

GLProgramStateCache* GLProgramStateCache::s_instance = nullptr;

GLProgramStateCache::GLProgramStateCache()
{
    s_instance = nullptr;
}

GLProgramStateCache::~GLProgramStateCache()
{
    for (auto itr = _glProgramStates.begin(); itr != _glProgramStates.end(); itr++) {
        itr->second->release();
    }
    _glProgramStates.clear();
    s_instance = nullptr;
}

GLProgramStateCache* GLProgramStateCache::getInstance()
{
    if (s_instance == nullptr)
        s_instance = new GLProgramStateCache();
    
    return s_instance;
}

void GLProgramStateCache::destroyInstance()
{
    delete s_instance;
}

GLProgramState* GLProgramStateCache::getProgramState(GLProgram* glprogram)
{
    const auto& itr = _glProgramStates.find(glprogram);
    if (itr != _glProgramStates.end())
    {
        return itr->second;
    }
    
    auto ret = new (std::nothrow) GLProgramState;
    if(ret && ret->init(glprogram)) {
        _glProgramStates[glprogram] = ret;
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_RELEASE(ret);
    return ret;
}

void GLProgramStateCache::removeProgramState(GLProgram* program)
{
    auto itr = _glProgramStates.find(program);
    if (itr != _glProgramStates.end())
    {
        _glProgramStates.erase(itr);
    }
}

NS_CC_END
