#pragma once

#include "Macros.h"
#include "Types.h"
#include "base/CCRef.h"

#include <string>
#include <cstdint>
#include <vector>

CC_BACKEND_BEGIN

class VertexLayout
{
public:
    struct Attribute
    {
        Attribute(const std::string& _name, uint32_t _index, VertexFormat _format, uint32_t _offset)
        : name(_name)
        , index(_index)
        , format(_format)
        , offset(_offset)
        {}
        
        // name is used in opengl
        std::string name;
        VertexFormat format = VertexFormat::INT_R32G32B32;
        uint32_t offset = 0;
        // index is used in metal
        uint32_t index = 0;
    };
    
    void setAtrribute(const std::string& name, uint32_t index, VertexFormat format, uint32_t offset);
    //FIXME: remove stepMode?
    void setLayout(uint32_t stride, VertexStepMode stepMode);
    
    inline uint32_t getStride() const { return _stride; }
    inline VertexStepMode getVertexStepMode() const { return _stepMode; }
    inline const std::vector<Attribute>& getAttributes() const { return _attributes; }
    inline bool isValid() const { return _stride != 0; }
    
private:
    std::vector<Attribute> _attributes;
    uint32_t _stride = 0;
    VertexStepMode _stepMode = VertexStepMode::VERTEX;
};

CC_BACKEND_END
