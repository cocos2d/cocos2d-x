/****************************************************************************
    Copyright (c) 2014 Chukong Technologies Inc.

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

#include "cocos2d.h"

NS_CC_BEGIN

class TextureCube;

class CC_DLL Skybox : public Node
{
public:
    CREATE_FUNC(Skybox);

    void setTexture(TextureCube*);

    void onDraw(const Mat4& transform, uint32_t flags);

    // Overrides
    virtual void draw(Renderer* renderer, const Mat4& transform, uint32_t flags) override;

    void reload();

CC_CONSTRUCTOR_ACCESS:
    Skybox();
    virtual ~Skybox();
    virtual bool init();

protected:

    void initBuffers();

    GLuint      _vao;
    GLuint      _vertexBuffer;
    GLuint      _indexBuffer;

    CustomCommand _customCommand;

    TextureCube*  _texture;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Skybox);
};

NS_CC_END

#endif // __SKYBOX_H__
