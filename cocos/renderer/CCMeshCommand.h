/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
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

#pragma once

#include <unordered_map>
#include "renderer/CCRenderCommand.h"
#include "renderer/CCRenderState.h"
#include "renderer/backend/ProgramState.h"
#include "renderer/backend/Types.h"
#include "renderer/CCCustomCommand.h"
#include "math/CCMath.h"

NS_CC_BEGIN

class GLProgramState;
class EventListenerCustom;
class EventCustom;
class Material;

//it is a common mesh
class CC_DLL MeshCommand : public CustomCommand
{
public:
    //using PrimitiveType = backend::PrimitiveType;
    /**
    Buffer usage of vertex/index buffer. If the contents is not updated every frame,
    then use STATIC, other use DYNAMIC.
    */
    using BufferUsage = backend::BufferUsage;
    /**
    The index format determine the size for index data. U_SHORT is enough for most
    cases.
    */
    using IndexFormat = backend::IndexFormat;

    MeshCommand();
    virtual ~MeshCommand();
    MeshCommand(const MeshCommand &) = default;

    /**
    Init function. The render command will be in 2D mode.
    @param globalZOrder GlobalZOrder of the render command.
    */
    void init(float globalZOrder);

    void init(float globalZOrder, const Mat4 &transform);

#if CC_ENABLE_CACHE_TEXTURE_DATA
    void listenRendererRecreated(EventCustom* event);
#endif

protected:
#if CC_ENABLE_CACHE_TEXTURE_DATA
    EventListenerCustom* _rendererRecreatedListener;
#endif
};

NS_CC_END

