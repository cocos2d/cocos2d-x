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


#ifndef _CC_MATERIALMANAGER_H_
#define _CC_MATERIALMANAGER_H_

#include "CCPlatformMacros.h"
#include "CCObject.h"
#include "ccTypes.h"
#include <map>

NS_CC_BEGIN

class MaterialManager : public Object
{
public:
    static MaterialManager* getInstance();
    static void destroyInstance();


    void getMaterialID(GLuint textureID, GLuint shaderID, BlendFunc blendFunc);

    void registerTexture(GLuint textureID);
    void unregisterTexture(GLuint textureID);

    void registerShader(GLuint shaderID);
    void unregisterShader(GLuint shaderID);

protected:
    MaterialManager();
    virtual ~MaterialManager();

    bool init();

    int getTextureID(GLuint textureID);
    int getShaderID(GLuint shaderID);
    int getBlendFuncID(GLint blendFunc);

    std::map<GLuint, int> _textureIDMapping;
    std::map<GLuint, int> _shaderIDMapping;
    std::map<BlendFunc, int> _blendFuncMapping;
};

NS_CC_END

#endif //_CC_MATERIALMANAGER_H_
