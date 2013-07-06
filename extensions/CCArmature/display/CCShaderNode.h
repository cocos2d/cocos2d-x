/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#ifndef __CCSHADERNODE_H__
#define __CCSHADERNODE_H__

#include "../utils/CCArmatureDefine.h"

namespace cocos2d { namespace extension { namespace armature {

class ShaderNode : public Node
{
public:
    ShaderNode();

    bool initWithVertex(const char *vert, const char *frag);
    void loadShaderVertex(const char *vert, const char *frag);

    virtual void update(float dt);
    virtual void setPosition(const Point &newPosition);
    virtual void translateFormOtherNode(AffineTransform &transform);
    virtual void draw();

    static ShaderNode *shaderNodeWithVertex(const char *vert, const char *frag);

private:

    Vertex2F _center;
    Vertex2F _resolution;
    float      _time;
    GLuint     _uniformCenter, _uniformResolution, _uniformTime;
};

}}} // namespace cocos2d { namespace extension { namespace armature {

#endif /*__CCSHADERNODE_H__*/
