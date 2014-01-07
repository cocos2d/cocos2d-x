#include "Base.h"
#include "C3DVertexFormat.h"

namespace cocos2d
{

C3DVertexFormat::C3DVertexFormat(const C3DVertexElement* elements, unsigned int elementCount)
    : _vertexSize(0)
{
    // Copy elements and compute vertex size
    for (unsigned int i = 0; i < elementCount; ++i)
    {
        _elements.push_back( new C3DVertexElement());

        memcpy(_elements.back(), &elements[i], sizeof(C3DVertexElement));       

        _vertexSize += elements[i].size * sizeof(float);
    }
}

C3DVertexFormat::C3DVertexFormat(const C3DVertexFormat* vertexformat)
    : _vertexSize(0)
{
    // Copy elements and compute vertex size
    for (unsigned int i = 0; i < vertexformat->getElementCount(); ++i)
    {
        _elements.push_back( new C3DVertexElement() );

        memcpy(_elements.back(), vertexformat->getElement(i), sizeof(C3DVertexElement));       

        _vertexSize += vertexformat->getElement(i)->size * sizeof(float);
    }

}

C3DVertexFormat::~C3DVertexFormat()
{
    C3DVertexElement* element = nullptr;
    for( auto iter=_elements.begin(); iter!=_elements.end(); iter++ )
    {
        element = *iter;
        delete element;
    }
    _elements.clear();

}

const C3DVertexElement* C3DVertexFormat::getElement(unsigned int index) const
{
    assert(index < _elements.size());

    return _elements[index];
}

unsigned int C3DVertexFormat::getElementCount() const
{
    return _elements.size();
}

unsigned int C3DVertexFormat::getVertexSize() const
{
    return _vertexSize;
}

bool C3DVertexFormat::operator == (const C3DVertexFormat& f) const
{
    if (_elements.size() != f._elements.size())
        return false;

    for (unsigned int i = 0, count = _elements.size(); i < count; ++i)
    {
        if (*_elements[i] != *f._elements[i])
            return false;
    }

    return true;
}


bool C3DVertexFormat::operator != (const C3DVertexFormat& f) const
{
    return !(*this == f);
}

const char* C3DVertexFormat::toString(Vertex_Usage usage)
{
    switch (usage)
    {
    case Vertex_Usage_POSITION:
        return "POSITION";
    case Vertex_Usage_NORMAL:
        return "NORMAL";
    case Vertex_Usage_COLOR:
        return "COLOR";
    case Vertex_Usage_TANGENT:
        return "TANGENT";
    case Vertex_Usage_BINORMAL:
        return "BINORMAL";
    case Vertex_Usage_BLENDWEIGHTS:
        return "BLENDWEIGHTS";
    case Vertex_Usage_BLENDINDICES:
        return "BLENDINDICES";
    case Vertex_Usage_TEXCOORD0:
        return "TEXCOORD0";
    case Vertex_Usage_TEXCOORD1:
        return "TEXCOORD1";
    case Vertex_Usage_TEXCOORD2:
        return "TEXCOORD2";
    case Vertex_Usage_TEXCOORD3:
        return "TEXCOORD3";
    case Vertex_Usage_TEXCOORD4:
        return "TEXCOORD4";
    case Vertex_Usage_TEXCOORD5:
        return "TEXCOORD5";
    case Vertex_Usage_TEXCOORD6:
        return "TEXCOORD6";
    case Vertex_Usage_TEXCOORD7:
        return "TEXCOORD7";
    default:
        return "UNKNOWN";
    }
}

C3DVertexElement::C3DVertexElement() :
    usage(Vertex_Usage_POSITION), size(0)
{
}

C3DVertexElement::C3DVertexElement(Vertex_Usage usage, unsigned int size) :
    usage(usage), size(size)
{
}

C3DVertexElement::~C3DVertexElement()    
{

}

bool C3DVertexElement::operator == (const C3DVertexElement& e) const
{
    return (size == e.size && usage == e.usage);
}

bool C3DVertexElement::operator != (const C3DVertexElement& e) const
{
    return !(*this == e);
}

}
