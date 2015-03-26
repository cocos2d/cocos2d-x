/****************************************************************************
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
    texture cube map.
    It wraps the cocos2d::Texture2D
*/
class CC_DLL TextureCube: public Texture2D
{
public:
    /**
        create cube texture from 6 textures.

        @param path The image resource path.
        @create cube texture from 6 textures.
    */
    static TextureCube* create(const std::string& positive_x, const std::string& negative_x,
                               const std::string& positive_y, const std::string& negative_y,
                               const std::string& positive_z, const std::string& negative_z);

    void setTexParameters(const TexParams&);

    bool reloadTexture();
CC_CONSTRUCTOR_ACCESS:
    TextureCube();
    TextureCube(const TextureCube&);
    virtual ~TextureCube();
protected:

    bool init(const std::string& positive_x, const std::string& negative_x,
              const std::string& positive_y, const std::string& negative_y,
              const std::string& positive_z, const std::string& negative_z);
private:
    std::vector<std::string> _imgPath;
};

NS_CC_END

#endif // __CCTEXTURECUBE_H__
