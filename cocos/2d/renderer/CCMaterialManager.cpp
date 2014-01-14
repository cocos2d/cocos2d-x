/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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


#include "CCMaterialManager.h"

NS_CC_BEGIN

using namespace std;

static MaterialManager* s_instance = nullptr;

MaterialManager *MaterialManager::getInstance()
{
    if(!s_instance)
    {
        s_instance = new MaterialManager();
        if(!s_instance->init())
        {
            CC_SAFE_DELETE(s_instance);
        }
    }
    return s_instance;
}

void MaterialManager::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(s_instance);
}

void MaterialManager::getMaterialID(GLuint textureID, GLuint shaderID, BlendFunc blendFunc)
{

}

void MaterialManager::registerTexture(GLuint textureID)
{

}

void MaterialManager::unregisterTexture(GLuint textureID)
{

}

void MaterialManager::registerShader(GLuint shaderID)
{

}

void MaterialManager::unregisterShader(GLuint shaderID)
{

}

MaterialManager::MaterialManager()
{

}

MaterialManager::~MaterialManager()
{

}

bool MaterialManager::init()
{
    return false;
}

int MaterialManager::getTextureID(GLuint textureID)
{
    return 0;
}

int MaterialManager::getShaderID(GLuint shaderID)
{
    return 0;
}

int MaterialManager::getBlendFuncID(GLint blendFunc)
{
    return 0;
}

NS_CC_END