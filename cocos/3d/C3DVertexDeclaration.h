#ifndef VERTEXATTRIBUTEBINDING_H_
#define VERTEXATTRIBUTEBINDING_H_

#include "Base.h"

#include "cocos2d.h"

namespace cocos2d
{

class C3DMesh;
class C3DEffect;
class C3DVertexFormat;

/**
 * Defines a vertexdeclaration.
 * This class provide a binding between the vertex layout of a Mesh and the vertex
 * input attributes of a vertex shader.Two Ways:
 * 1.software binding:vertex layout definition,which set when per frame.
 * 2.hardware binding:VAO per VBO.which set only once when init.
 *
 */
class C3DVertexDeclaration : public cocos2d::CCObject
{
public:

    static C3DVertexDeclaration* create(C3DMesh* mesh, C3DEffect* effect);

    static C3DVertexDeclaration* create(const C3DVertexFormat* vertexFormat, void* vertexPointer, C3DEffect* effect);

    static C3DVertexDeclaration* create(C3DMesh* mesh, const C3DVertexFormat* vertexFormat, void* vertexPointer, C3DEffect* effect);

    void bind();

    void unbind();

private:

    class C3DVertexAttribute
    {
    public:
        bool enabled;
        int size;
        GLenum type;
        bool normalized;
        unsigned int stride;
        void* pointer;
    };

    C3DVertexDeclaration();

    ~C3DVertexDeclaration();

    
    void setVertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalize, GLsizei stride, void* pointer);

    GLuint _handle;
    C3DVertexDeclaration::C3DVertexAttribute* _attributes;
    C3DMesh* _mesh;
    C3DEffect* _effect;
};

}

#endif
