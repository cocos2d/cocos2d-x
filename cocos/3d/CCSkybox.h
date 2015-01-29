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

class CC_DLL Skybox : public Node
{
public:
    static Skybox* create();

    void drawSphere(const Vec3& origin, const float radius, const float M, const float N, const Color4F& color);

    void setTexture(Texture2D*);

    /** Clear the geometry in the node's buffer. */
    void clear();

    void onDraw(const Mat4& transform, uint32_t flags);

    // Overrides
    virtual void draw(Renderer* renderer, const Mat4& transform, uint32_t flags) override;

CC_CONSTRUCTOR_ACCESS:
    Skybox();
    virtual ~Skybox();
    virtual bool init();

protected:
    struct V3F_C4B
    {
        Vec3     vertices;
        Color4B  colors;
        Tex2F    texcoord;
    };

    void ensureCapacity(int count);
	void drawSlice(Vec3* points, const Color4F& color);

    GLuint      _vao;
    GLuint      _vbo;

    int         _bufferCapacity;
    GLsizei     _bufferCount;
    V3F_C4B*    _buffer;

    CustomCommand _customCommand;

    bool        _dirty;

    Texture2D*  _texture;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Skybox);
};

NS_CC_END

#endif // __SKYBOX_H__
