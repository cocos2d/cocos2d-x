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

#ifndef __CCNAV_MESH_DEBUG_DRAW_H__
#define __CCNAV_MESH_DEBUG_DRAW_H__

#include "base/ccConfig.h"
#if CC_USE_NAVMESH

#include "renderer/CCGLProgram.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCRenderState.h"
#include "math/Vec3.h"
#include "recast/DebugUtils/DebugDraw.h"
#include <string>
#include <vector>

NS_CC_BEGIN

/**
 * @addtogroup 3d
 * @{
 */
class Renderer;
class NavMeshDebugDraw : public duDebugDraw
{
public:
    NavMeshDebugDraw();
    virtual ~NavMeshDebugDraw();

    virtual void depthMask(bool state)override;
    virtual void texture(bool state)override{};
    virtual void begin(duDebugDrawPrimitives prim, float size = 1.0f) override;

    virtual void vertex(const float* pos, unsigned int color) override;
    virtual void vertex(const float x, const float y, const float z, unsigned int color) override;

    virtual void vertex(const float* pos, unsigned int color, const float* uv) override;
    virtual void vertex(const float x, const float y, const float z, unsigned int color, const float u, const float v) override;

    virtual void end() override;

    void draw(Renderer* renderer);

    void clear();

private:

    GLenum getPrimitiveType(duDebugDrawPrimitives prim);
    void drawImplement(const cocos2d::Mat4& transform, uint32_t flags);
    static Vec4 getColor(unsigned int col);

private:

    struct V3F_C4F
    {
        Vec3 position;
        Vec4 color;
    };

    struct Primitive
    {
        GLenum type;
        bool depthMask;
        unsigned short start;
        unsigned short end;
        float size;
    };

    std::vector<V3F_C4F> _vertices;
    std::vector<Primitive*> _primitiveList;
    Primitive *_currentPrimitive;
    GLProgram *_program;
    CustomCommand _customCmd;
    RenderState::StateBlock* _stateBlock;
    GLenum _primitiveType;
    bool _currentDepthMask;
    GLuint _vbo;
    bool _dirtyBuffer;
};

/** @} */

NS_CC_END

#endif //CC_USE_NAVMESH

#endif // __CCNAV_MESH_DEBUG_DRAW_H__
