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
#include "Types.h"
#include "base/CCRef.h"

#include <string>

CC_BACKEND_BEGIN
/**
 * @addtogroup _backend
 * @{
 */

enum Uniform : uint32_t
{
    MVP_MATRIX,
    TEXTURE,
    TEXTURE1,
    TEXTURE2,
    TEXTURE3,
    TEXT_COLOR,
    EFFECT_TYPE,
    EFFECT_COLOR,
    UNIFORM_MAX //Maximum uniforms
};

enum Attribute : uint32_t
{
    POSITION,
    COLOR,
    TEXCOORD,
    TEXCOORD1,
    TEXCOORD2,
    TEXCOORD3,
    ATTRIBUTE_MAX //Maximum attributes
};
/**
 * Create shader.
 */
class ShaderModule : public cocos2d::Ref
{
public:
    /**
     * Get shader stage. The symbolic constant can be either VERTEX or FRAGMENT.
     * @return Shader stage.
     */
    ShaderStage getShaderStage() const;

    std::size_t getHashValue() const { return _hash; }
    
protected:
    ShaderModule(ShaderStage stage);
    virtual ~ShaderModule();
    void setHashValue(std::size_t hash) { _hash = hash; }
    
    friend class ShaderCache;
    ShaderStage _stage = ShaderStage::VERTEX;
    std::size_t _hash = 0;
};

//end of _backend group
/// @}
CC_BACKEND_END
