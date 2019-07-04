/****************************************************************************
 Copyright (c) 2018-2019 Xiamen Yaji Software Co., Ltd.

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

#include "Macros.h"
#include "base/CCRef.h"
#include "platform/CCPlatformMacros.h"
#include "Types.h"
#include "ShaderCache.h"

#include <string>
#include <vector>
#include <unordered_map>

CC_BACKEND_BEGIN

class ShaderModule;

class Program : public Ref
{
public:
    virtual const std::unordered_map<std::string, UniformInfo>& getVertexUniformInfos() const = 0;
    virtual const std::unordered_map<std::string, UniformInfo>& getFragmentUniformInfos() const = 0;
    
    virtual UniformLocation getUniformLocation(const std::string& uniform) const = 0;
    
    virtual int getMaxVertexLocation() const = 0;
    virtual int getMaxFragmentLocation() const = 0;
    virtual const std::unordered_map<std::string, AttributeBindInfo> getActiveAttributes() const = 0;

    const std::string& getVertexShader() const { return _vertexShader; }
    const std::string& getFragmentShader() const { return _fragmentShader; }
    
protected:
    Program(const std::string& vs, const std::string& fs);

#if CC_ENABLE_CACHE_TEXTURE_DATA
    virtual int getMappedLocation(int location) const = 0; //get the ture location after opengl program reload
    virtual const std::unordered_map<std::string, UniformLocation> getAllUniformsLocation() const = 0;
    friend class ProgramState;
    friend class ProgramCache;
#endif
    
    std::string _vertexShader;
    std::string _fragmentShader;
};

CC_BACKEND_END
