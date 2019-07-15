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
#include <cstdint>
#include <vector>
#include <unordered_map>

CC_BACKEND_BEGIN
/**
 * @addtogroup _backend
 * @{
 */
class VertexLayout
{
public:
    struct Attribute
    {
        Attribute() = default;
        Attribute(const std::string& _name, unsigned int _index, VertexFormat _format, unsigned int _offset, bool needToBeNormallized)
        : name(_name)
        , format(_format)
        , offset(_offset)
        , index(_index)
        , needToBeNormallized(needToBeNormallized)
        {}
        
        // name is used in opengl
        std::string name;
        VertexFormat format = VertexFormat::INT3;
        unsigned int offset = 0;
        // index is used in metal
        unsigned int index = 0;
        bool needToBeNormallized = false;
    };

    VertexLayout() = default;
    
    void setAttribute(const std::string& name, unsigned int index, VertexFormat format, unsigned int offset, bool needToBeNormallized);
    //FIXME: remove stepMode?
    void setLayout(unsigned int stride, VertexStepMode stepMode);
    
    inline unsigned int getStride() const { return _stride; }
    inline VertexStepMode getVertexStepMode() const { return _stepMode; }
    inline const std::unordered_map<std::string, Attribute>& getAttributes() const { return _attributes; }
    inline bool isValid() const { return _stride != 0; }
    
private:
    std::unordered_map<std::string, Attribute> _attributes;
    unsigned int _stride = 0;
    VertexStepMode _stepMode = VertexStepMode::VERTEX;
};

//end of _backend group
/// @}
CC_BACKEND_END
