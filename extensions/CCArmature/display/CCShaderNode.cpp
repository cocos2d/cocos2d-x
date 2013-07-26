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

#include "CCShaderNode.h"

namespace cocos2d { namespace extension { namespace armature {

enum
{
    SIZE_X = 128,
    SIZE_Y = 128,
};

ShaderNode::ShaderNode()
    : _center(Vertex2F(0.0f, 0.0f))
    , _resolution(Vertex2F(0.0f, 0.0f))
    , _time(0.0f)
    , _uniformCenter(0)
    , _uniformResolution(0)
    , _uniformTime(0)
{
}

ShaderNode *ShaderNode::shaderNodeWithVertex(const char *vert, const char *frag)
{
    ShaderNode *node = new ShaderNode();
    node->initWithVertex(vert, frag);
    node->autorelease();

    return node;
}

bool ShaderNode::initWithVertex(const char *vert, const char *frag)
{

    loadShaderVertex(vert, frag);

    _time = 0;
    _resolution = Vertex2F(SIZE_X, SIZE_Y);

    scheduleUpdate();

    setContentSize(Size(SIZE_X, SIZE_Y));
    setAnchorPoint(Point(0.5f, 0.5f));

    return true;
}

void ShaderNode::loadShaderVertex(const char *vert, const char *frag)
{
    GLProgram *shader = new GLProgram();
    shader->initWithVertexShaderFilename(vert, frag);

    shader->addAttribute("aVertex", GLProgram::VERTEX_ATTRIB_POSITION);
    shader->link();

    shader->updateUniforms();

    _uniformCenter = glGetUniformLocation(shader->getProgram(), "center");
    _uniformResolution = glGetUniformLocation(shader->getProgram(), "resolution");
    _uniformTime = glGetUniformLocation(shader->getProgram(), "time");

    this->setShaderProgram(shader);

    shader->release();
}

void ShaderNode::update(float dt)
{
    _time += dt;
}

void ShaderNode::translateFormOtherNode(AffineTransform &transform)
{
    Node::setAdditionalTransform(transform);

    _center = Vertex2F(_additionalTransform.tx * CC_CONTENT_SCALE_FACTOR(), _additionalTransform.ty * CC_CONTENT_SCALE_FACTOR());
    _resolution = Vertex2F( SIZE_X * _additionalTransform.a, SIZE_Y * _additionalTransform.d);
}

void ShaderNode::setPosition(const Point &newPosition)
{
    Node::setPosition(newPosition);
    Point position = getPosition();
    _center = Vertex2F(position.x * CC_CONTENT_SCALE_FACTOR(), position.y * CC_CONTENT_SCALE_FACTOR());
}

void ShaderNode::draw()
{
    CC_NODE_DRAW_SETUP();

    float w = SIZE_X, h = SIZE_Y;
    GLfloat vertices[12] = {0, 0, w, 0, w, h, 0, 0, 0, h, w, h};

    //
    // Uniforms
    //
    getShaderProgram()->setUniformLocationWith2f(_uniformCenter, _center.x, _center.y);
    getShaderProgram()->setUniformLocationWith2f(_uniformResolution, _resolution.x, _resolution.y);


    // time changes all the time, so it is Ok to call OpenGL directly, and not the "cached" version
    glUniform1f(_uniformTime, _time);

    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION);

    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    CC_INCREMENT_GL_DRAWS(1);
}


}}} // namespace cocos2d { namespace extension { namespace armature {
