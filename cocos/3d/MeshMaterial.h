#ifndef MESHMATERIAL_H_
#define MESHMATERIAL_H_

#include <vector>
#include <map>
#include "CCRef.h"
#include "CCMath.h"
#include "ccTypes.h"

NS_CC_BEGIN

class Mesh;

class GLProgram;

class Texture2D;

extern const char* s_attribute_Normal_Name;
extern int s_attribute_Normal;

/**
 * Defines a vertexdeclaration for vertex bind.
 * This class provide a binding between the vertex layout of a Mesh and the vertex
 * input attributes of a vertex shader.Two Ways:
 * 1.software binding:vertex layout definition,which set when per frame.
 * 2.hardware binding:VAO per VBO.which set only once when init.
 *
 */
class VertexDeclaration: public Ref
{
protected:
    class VertexAttribute
    {
    public:
        bool enabled;
        int size;
        GLenum type;
        bool normalized;
        unsigned int stride;
        void* pointer;
        
        VertexAttribute(): enabled(GL_FALSE), size(4), stride(0), type(GL_FLOAT), normalized(GL_FALSE), pointer(nullptr)
        {
            
        }
    };
    
public:
    struct Uniform
    {
        Uniform(): _location(-1), _type(0)
        {
        }
        Uniform(GLint location, GLenum type): _location(location), _type(type)
        {
        }
        GLint _location;
        GLenum _type;
    };
    
public:
    //create
    static VertexDeclaration* create(Mesh* mesh, GLProgram* program = nullptr);
    
    void setAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalize, GLsizei stride, void* pointer);
    
    //bind vertex attribute, position, normal, coordinate and so on
    void bind();
    
    void unbind();
    
    GLProgram* getProgram() { return _program; }
    
    //query uniforms from shader
    std::map<std::string, Uniform*>& getUniforms() { return _uniforms; }
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    static void restoreAllVertexDecl();
#endif
    
protected:
    
    VertexDeclaration();
    
    virtual ~VertexDeclaration();
    
    void setupUniforms();
    
    bool buildBuffer();
    
    GLProgram* getDefProgram(bool textured);
    
    VertexAttribute* _attributes;
    Mesh* _mesh;
    GLProgram* _program;
    int _attribFlag;
    GLuint _vao;
    
    //uniforms parsed from shader
    std::map<std::string, Uniform*> _uniforms;
    
    //default shader
    static GLProgram* s_defProgramTex;
    static GLProgram* s_defProgram;
    
};

class MeshMaterial : public Ref
{
public:

    //create material, if program = nullptr use default shader
    static MeshMaterial* create(Mesh* mesh, GLProgram* program = nullptr);
    
    //set texture
    void setTexture(Texture2D* texture);
    
    //set texture by file name
    void setTexture(const std::string& filename);
    
    //set color
    void setColor(const math::Vector4& color);

    //bind shader parameter
    virtual void bind();

    //unbind
    virtual void unbind();
    
    //set vertex declaration
    void setVertexDeclaration(VertexDeclaration* vertexDec);
    
    //get program
    virtual GLProgram* getProgram() { return _vertexDeclaration->getProgram(); }
    
    //get UniformValue and set the value. It will keep the value untill changed. Do not need to change every frame
    UniformValue* getUniformValue(const std::string& uniformName);

protected:
    
    MeshMaterial();

    ~MeshMaterial();
    
    void releaseUniformValues();
    
    void updateBlendFunc();
    

    //vertex declaration
    VertexDeclaration* _vertexDeclaration;
    
    //uniforms value map, store the values so do not need set it every frame
    std::map<std::string, UniformValue*> _uniformValueMap;
    
    //texture
    Texture2D* _texture;
    
    // opengl state
    BlendFunc _blendFunc;
};

NS_CC_END
#endif
