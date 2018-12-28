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
        Attribute(const std::string& _name, unsigned int _index, VertexFormat _format, unsigned int _offset, bool needToBeNormallized)
        : name(_name)
        , format(_format)
        , offset(_offset)
        , index(_index)
        , needToBeNormallized(needToBeNormallized)
        {}
        
        // name is used in opengl
        std::string name;
        VertexFormat format = VertexFormat::INT_R32G32B32;
        unsigned int offset = 0;
        // index is used in metal
        unsigned int index = 0;
        bool needToBeNormallized = false;
    };
    
    void setAtrribute(const std::string& name, unsigned int index, VertexFormat format, unsigned int offset, bool needToBeNormallized);
    //FIXME: remove stepMode?
    void setLayout(unsigned int stride, VertexStepMode stepMode);
    
    inline unsigned int getStride() const { return _stride; }
    inline VertexStepMode getVertexStepMode() const { return _stepMode; }
    inline const std::vector<Attribute>& getAttributes() const { return _attributes; }
    inline bool isValid() const { return _stride != 0; }
    
private:
    std::vector<Attribute> _attributes;
    unsigned int _stride = 0;
    VertexStepMode _stepMode = VertexStepMode::VERTEX;
};

CC_BACKEND_END
