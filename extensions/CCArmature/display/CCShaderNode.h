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

NS_CC_EXT_BEGIN

class CCShaderNode : public CCNode
{
public:
    CCShaderNode();

    bool initWithVertex(const char *vert, const char *frag);
    void loadShaderVertex(const char *vert, const char *frag);

    virtual void update(float dt);
    virtual void setPosition(const CCPoint &newPosition);
    virtual void translateFormOtherNode(CCAffineTransform &transform);
    virtual void draw();

    static CCShaderNode *shaderNodeWithVertex(const char *vert, const char *frag);

private:

    ccVertex2F m_center;
    ccVertex2F m_resolution;
    float      m_time;
    GLuint     m_uniformCenter, m_uniformResolution, m_uniformTime;
};

NS_CC_EXT_END

#endif /*__CCSHADERNODE_H__*/
