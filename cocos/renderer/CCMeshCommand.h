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

#ifndef _CC_MESHCOMMAND_H_
#define _CC_MESHCOMMAND_H_

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

    typedef std::function<void()> CallBackFunc;

    MeshCommand();
    virtual ~MeshCommand();

    /**
    Init function. The render command will be in 2D mode.
    @param globalZOrder GlobalZOrder of the render command.
    */
    void init(float globalZOrder);

    /**
    * set a callback which will be invoke before rendering
    */
    void setBeforeCallback(const CallBackFunc &before) { _beforeCallback = before; }

    /**
    * set a callback which will be invoke after rendering
    */
    void setAfterCallback(const CallBackFunc &after){ _afterCallback = after; }

    const CallBackFunc &getBeforeCallback() { return _beforeCallback; }

    const CallBackFunc &getAfterCallback() { return _afterCallback; }

#if CC_ENABLE_CACHE_TEXTURE_DATA
    void listenRendererRecreated(EventCustom* event);
#endif

protected:

    CallBackFunc _beforeCallback    = nullptr;
    CallBackFunc _afterCallback     = nullptr;

#if CC_ENABLE_CACHE_TEXTURE_DATA
    EventListenerCustom* _rendererRecreatedListener;
#endif
};

NS_CC_END

#endif //_CC_MESHCOMMAND_H_
