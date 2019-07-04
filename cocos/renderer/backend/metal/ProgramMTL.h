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

#include "../Program.h"
#import <Metal/Metal.h>

CC_BACKEND_BEGIN

class ShaderModuleMTL;

class ProgramMTL : public Program
{
public:
    ProgramMTL(id<MTLDevice> mtlDevice, const std::string& vertexShader, const std::string& fragmentShader);
    virtual ~ProgramMTL();

    virtual const std::unordered_map<std::string, UniformInfo>& getVertexUniformInfos() const override;
    virtual const std::unordered_map<std::string, UniformInfo>& getFragmentUniformInfos() const override;
    
    virtual UniformLocation getUniformLocation(const std::string& uniform) const override;
    
    virtual ShaderModuleMTL* getVertexShader() const { return _vertexShader; }
    virtual ShaderModuleMTL* getFragmentShader() const { return _fragmentShader; }
    
    const std::unordered_map<std::string, AttributeBindInfo> getActiveAttributes() const override;

    virtual int getMaxVertexLocation() const override;
    virtual int getMaxFragmentLocation() const override;

private:
    ShaderModuleMTL* _vertexShader = nullptr;
    ShaderModuleMTL* _fragmentShader = nullptr;
};

CC_BACKEND_END
