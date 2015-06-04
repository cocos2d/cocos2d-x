﻿﻿/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
 
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

#ifndef __CCTEXTURECUBE_H__
#define __CCTEXTURECUBE_H__

#include "renderer/CCTexture2D.h"

#include <string>
#include <unordered_map>
#include "base/ccTypes.h"

NS_CC_BEGIN

/**
    @addtogroup _3d
    @{
*/

/** @class TextureCube
    TextureCube is a collection of six separate square textures that are put
    onto the faces of an imaginary cube.
*/
class CC_DLL TextureCube: public Texture2D
{
public:
    /** @~english create cube texture from 6 textures.
        @~chinese 6纹理创建立方体纹理。
        @param positive_x @~english  texture for the right side of the texture cube face. @~chinese 立方体的右侧纹理。
        @param negative_x @~english  texture for the left side of the texture cube face. @~chinese 立方体的左侧纹理。
        @param positive_y @~english  texture for the top side of the texture cube face @~chinese 立方体的上侧纹理
        @param negative_y @~english  texture for the bottom side of the texture cube face @~chinese 立方体的底侧纹理
        @param positive_z @~english  texture for the forward side of the texture cube face. @~chinese 立方体的前侧纹理。
        @param negative_z @~english  texture for the rear side of the texture cube face. @~chinese 立方体的背侧纹理。
        @return @~english  A new texture cube inited with given parameters. @~chinese 一种新的纹理的立方体。
    */
    static TextureCube* create(const std::string& positive_x, const std::string& negative_x,
                               const std::string& positive_y, const std::string& negative_y,
                               const std::string& positive_z, const std::string& negative_z);

    /** @~english Sets the min filter, mag filter, wrap s and wrap t texture parameters.
        @~chinese 设置min滤波器，mag滤波器，纹理包裹参数。
        If the texture size is NPOT (non power of 2), then in can only use GL_CLAMP_TO_EDGE in GL_TEXTURE_WRAP_{S,T}.
        @param TexParams @~english  the min/mag filter of TextureCube @~chinese texturecube min/mag过滤器
    */
    void setTexParameters(const TexParams&);

    /** @~english reload texture cube after GLESContext reconstructed.
        @~chinese 在glescontext重建后重新加载纹理。
        @return @~english True if the reloading is succeed, otherwise return false. @~chinese 如果重装成功真，否则返回假。
    */
    bool reloadTexture();
CC_CONSTRUCTOR_ACCESS:
    /**
        Constructor.
    */
    TextureCube();

    /**
        Destructor.
    */
    virtual ~TextureCube();
protected:

    bool init(const std::string& positive_x, const std::string& negative_x,
              const std::string& positive_y, const std::string& negative_y,
              const std::string& positive_z, const std::string& negative_z);
private:
    std::vector<std::string> _imgPath;
};

// end of 3d group
/// @}

NS_CC_END

#endif // __CCTEXTURECUBE_H__
