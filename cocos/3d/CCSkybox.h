/****************************************************************************
 Copyright (c) 2015-2017 Chukong Technologies Inc.
 
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

#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include "base/ccTypes.h"
#include "platform/CCPlatformMacros.h"
#include "renderer/CCCustomCommand.h"
#include "2d/CCNode.h"

NS_CC_BEGIN

/**
 * @addtogroup _3d
 * @{
 */

class TextureCube;

/**
* Sky box technology is usually used to simulate infinity sky, mountains and other phenomena.
*/
class CC_DLL Skybox : public Node
{
public:
    CREATE_FUNC(Skybox);
    
    /** create skybox from 6 textures.
     @param positive_x texture for the right side of the texture cube face.
     @param negative_x texture for the left side of the texture cube face.
     @param positive_y texture for the top side of the texture cube face
     @param negative_y texture for the bottom side of the texture cube face
     @param positive_z texture for the forward side of the texture cube face.
     @param negative_z texture for the rear side of the texture cube face.
     @return  A new skybox inited with given parameters.
     */
    static Skybox* create(const std::string& positive_x, const std::string& negative_x,
                               const std::string& positive_y, const std::string& negative_y,
                               const std::string& positive_z, const std::string& negative_z);

    /**texture getter and setter*/
    void setTexture(TextureCube*);

    /** draw Skybox object */
    virtual void draw(Renderer* renderer, const Mat4& transform, uint32_t flags) override;

    /** reload sky box after GLESContext reconstructed.*/
    void reload();

CC_CONSTRUCTOR_ACCESS:
    /**
    * Constructor.
    */
    Skybox();

    /**
    * Destructor.
    */
    virtual ~Skybox();

    /**
    * init Skybox.
    */
    virtual bool init() override;
    
    /**
     * initialize with texture path
     */
    bool init(const std::string& positive_x, const std::string& negative_x,
              const std::string& positive_y, const std::string& negative_y,
              const std::string& positive_z, const std::string& negative_z);

protected:

    /**
    * init internal buffers for Skybox.
    */
    void initBuffers();

    void onDraw(const Mat4& transform, uint32_t flags);

    GLuint      _vao;
    GLuint      _vertexBuffer;
    GLuint      _indexBuffer;

    CustomCommand _customCommand;

    TextureCube*  _texture;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Skybox);
};

// end of 3d group
/// @}

NS_CC_END

#endif // __SKYBOX_H__
