#ifndef VERTEXFORMAT_H_
#define VERTEXFORMAT_H_

#include <vector>
namespace cocos2d
{

      /**
     * Defines a set of usages for vertex elements.
     */
    enum Vertex_Usage
    {
        Vertex_Usage_POSITION = 1,
        Vertex_Usage_NORMAL = 2,
        Vertex_Usage_COLOR = 3,
        Vertex_Usage_TANGENT = 4,
        Vertex_Usage_BINORMAL = 5,
        Vertex_Usage_BLENDWEIGHTS = 6,
        Vertex_Usage_BLENDINDICES = 7,
        Vertex_Usage_TEXCOORD0 = 8,
        Vertex_Usage_TEXCOORD1 = 9,
        Vertex_Usage_TEXCOORD2 = 10,
        Vertex_Usage_TEXCOORD3 = 11,
        Vertex_Usage_TEXCOORD4 = 12,
        Vertex_Usage_TEXCOORD5 = 13,
        Vertex_Usage_TEXCOORD6 = 14,
        Vertex_Usage_TEXCOORD7 = 15
    };

    /**
     * Defines a single element within a vertex format.
     *
     * All vertex elements are assumed to be of type float, but can
     * have a varying number of float values (1-4), which is represented
     * by the size attribute. Additionally, vertex elements are assumed
     * to be tightly packed.
     */
    class C3DVertexElement
    {
    public:

        Vertex_Usage usage;//The vertex element usage semantic.

        unsigned int size;//The number of values in the vertex element.

        C3DVertexElement();

        C3DVertexElement(Vertex_Usage usage, unsigned int size);

        ~C3DVertexElement();

        bool operator == (const C3DVertexElement& e) const;

        bool operator != (const C3DVertexElement& e) const;
    };


//Defines the format of a vertex layout used by a mesh.
class C3DVertexFormat
{
public:
    
    C3DVertexFormat(const C3DVertexElement* elements, unsigned int elementCount);

    C3DVertexFormat(const C3DVertexFormat* vertexformat);

    ~C3DVertexFormat();

    /**
     * Gets the vertex element at the specified index.
     *
     * @param index The index of the element to retreive.
     */
    const C3DVertexElement* getElement(unsigned int index) const;

    /**
     * Gets the number of elements in this C3DVertexFormat.
     *
     * @return The number of items in the elements array.
     */
    unsigned int getElementCount() const;

    /**
     * Gets the size (in bytes) of a single vertex using this format.
     */
    unsigned int getVertexSize() const;

    bool operator == (const C3DVertexFormat& f) const;


    bool operator != (const C3DVertexFormat& f) const;

    /**
     * Returns a string representation of a Usage enumeration value.
     */
    static const char* toString(Vertex_Usage usage);

private:

    std::vector<C3DVertexElement*> _elements;
    unsigned int _vertexSize;
};

}

#endif
