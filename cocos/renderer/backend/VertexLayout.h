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

/**
 * Store vertex attribute layout.
 */
class VertexLayout
{
public:
    struct Attribute
    {
        Attribute() = default;
        Attribute(const std::string& _name, std::size_t _index, VertexFormat _format, std::size_t _offset, bool needToBeNormallized)
        : name(_name)
        , format(_format)
        , offset(_offset)
        , index(_index)
        , needToBeNormallized(needToBeNormallized)
        {}
        
        std::string name; ///< name is used in opengl
        VertexFormat format = VertexFormat::INT3; 
        std::size_t offset = 0;
        std::size_t index = 0; ///< index is used in metal
        bool needToBeNormallized = false;
    };

    VertexLayout() = default;
    
    /**
     * Set attribute values to name.
     * @param name Specifies the attribute name.
     * @param index Specifies the index of the generic vertex attribute to be modified.
     * @param format Specifies how the vertex attribute data is laid out in memory.
     * @param offset Specifies the byte offset to the first component of the first generic vertex attribute.
     * @param needToBeNormallized Specifies whether fixed-point data values should be normalized (true) or converted directly as fixed-point values (false) when they are accessed.
     */
    void setAttribute(const std::string& name, std::size_t index, VertexFormat format, std::size_t offset, bool needToBeNormallized);
    
    /**
     * Set stride of vertices.
     * @param stride Specifies the distance between the data of two vertices, in bytes.
     */
    void setLayout(std::size_t stride);
    
    /**
     * Get the distance between the data of two vertices, in bytes.
     * @return The distance between the data of two vertices, in bytes.
     */
    inline std::size_t getStride() const { return _stride; }

    /**
     * Get vertex step function. Default value is VERTEX.
     * @return Vertex step function.
     * @note Used in metal.
     */
    inline VertexStepMode getVertexStepMode() const { return _stepMode; }

    /**
     * Get attribute informations
     * @return Atrribute informations.
     */
    inline const std::unordered_map<std::string, Attribute>& getAttributes() const { return _attributes; }

    /**
     * Check if vertex layout has been set.
     */
    inline bool isValid() const { return _stride != 0; }
    
private:
    std::unordered_map<std::string, Attribute> _attributes;
    std::size_t _stride = 0;
    VertexStepMode _stepMode = VertexStepMode::VERTEX;
};

//end of _backend group
/// @}
CC_BACKEND_END
