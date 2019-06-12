/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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
#include "renderer/backend/Texture.h"

#include <string>
#include <unordered_map>
#include "base/ccTypes.h"

NS_CC_BEGIN

/**
 * @addtogroup _3d
 * @{
 */

/**
 TextureCube is a collection of six separate square textures that are put 
 onto the faces of an imaginary cube.
*/
class CC_DLL TextureCube : public Ref
{
public:
    /** create cube texture from 6 textures.
       @param positive_x texture for the right side of the texture cube face.
       @param negative_x texture for the up side of the texture cube face.
       @param positive_y texture for the top side of the texture cube face
       @param negative_y texture for the bottom side of the texture cube face
       @param positive_z texture for the forward side of the texture cube face.
       @param negative_z texture for the rear side of the texture cube face.
       @return  A new texture cube inited with given parameters.
    */
    static TextureCube* create(const std::string& positive_x, const std::string& negative_x,
                               const std::string& positive_y, const std::string& negative_y,
                               const std::string& positive_z, const std::string& negative_z);

    /** Sets the min filter, mag filter, wrap s and wrap t texture parameters.
    If the texture size is NPOT (non power of 2), then in can only use GL_CLAMP_TO_EDGE in GL_TEXTURE_WRAP_{S,T}.
    */
    void setTexParameters(const Texture2D::TexParams&);

    backend::TextureBackend* getBackendTexture() { return _texture; }

    /** reload texture cube after GLESContext reconstructed.*/
    bool reloadTexture();
CC_CONSTRUCTOR_ACCESS:
    /**
    * Constructor.
    */
    TextureCube();

    /**
    * Destructor.
    */
    virtual ~TextureCube();
protected:

    bool init(const std::string& positive_x, const std::string& negative_x,
              const std::string& positive_y, const std::string& negative_y,
              const std::string& positive_z, const std::string& negative_z);
private:
    std::vector<std::string> _imgPath;
    backend::TextureCubemapBackend *_texture = nullptr;
};

// end of 3d group
/// @}

NS_CC_END

#endif // __CCTEXTURECUBE_H__
