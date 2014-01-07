#include "C3DVertexDeclaration.h"
#include "C3DMesh.h"
#include "C3DEffect.h"
#include "C3DVertexFormat.h"

// Graphics (GLSL)
#define VERTEX_ATTRIBUTE_POSITION_NAME              "a_position"
#define VERTEX_ATTRIBUTE_NORMAL_NAME                "a_normal"
#define VERTEX_ATTRIBUTE_COLOR_NAME                 "a_color"
#define VERTEX_ATTRIBUTE_TANGENT_NAME               "a_tangent"
#define VERTEX_ATTRIBUTE_BINORMAL_NAME              "a_binormal"
#define VERTEX_ATTRIBUTE_BLENDWEIGHTS_NAME          "a_blendWeights"
#define VERTEX_ATTRIBUTE_BLENDINDICES_NAME          "a_blendIndices"
#define VERTEX_ATTRIBUTE_TEXCOORD_PREFIX_NAME       "a_texCoord"

namespace cocos2d
{

static GLuint __maxVertexAttribs = 0;
static std::vector<C3DVertexDeclaration*> __vertexAttributeBindingCache;

C3DVertexDeclaration::C3DVertexDeclaration() :
    _handle(0), _attributes(nullptr), _mesh(nullptr), _effect(nullptr)
{
}

C3DVertexDeclaration::~C3DVertexDeclaration()
{
    // Delete from the vertex attribute binding cache.
    std::vector<C3DVertexDeclaration*>::iterator itr = std::find(__vertexAttributeBindingCache.begin(), __vertexAttributeBindingCache.end(), this);
    if (itr != __vertexAttributeBindingCache.end())
    {
        __vertexAttributeBindingCache.erase(itr);
    }

    SAFE_RELEASE(_mesh);

  //  SAFE_RELEASE(_effect);

    SAFE_DELETE_ARRAY(_attributes);

#ifdef USE_VAO
    if (_handle)
    {
        /*GL_ASSERT*/( glDeleteVertexArrays(1, &_handle) );
        _handle = 0;
    }
#endif
}

C3DVertexDeclaration* C3DVertexDeclaration::create(C3DMesh* mesh, C3DEffect* effect)
{
    // Search for an existing vertex attribute binding that can be used.
    C3DVertexDeclaration* b;
    for (unsigned int i = 0, count = __vertexAttributeBindingCache.size(); i < count; ++i)
    {
        b = __vertexAttributeBindingCache[i];
        if (b->_mesh == mesh && b->_effect == effect)
        {
            // Found a match!
            b->retain();
            return b;
        }
    }

    b = create(mesh, mesh->getVertexFormat(), 0, effect);

    // Add the new vertex attribute binding to the cache.
    if (b)
    {
        __vertexAttributeBindingCache.push_back(b);
    }

    return b;
}

C3DVertexDeclaration* C3DVertexDeclaration::create(const C3DVertexFormat* vertexFormat, void* vertexPointer, C3DEffect* effect)
{
    return create(nullptr, vertexFormat, vertexPointer, effect);
}

C3DVertexDeclaration* C3DVertexDeclaration::create(C3DMesh* mesh, const C3DVertexFormat* vertexFormat, void* vertexPointer, C3DEffect* effect)
{
    // One-time initialization.
    if (__maxVertexAttribs == 0)
    {
        GLint temp;
        GL_ASSERT( glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &temp) );

        __maxVertexAttribs = temp;
        assert(__maxVertexAttribs > 0);
        if (__maxVertexAttribs <= 0)
        {
            return nullptr;
        }
    }

    // Create a new C3DVertexDeclaration.
    C3DVertexDeclaration* b = new C3DVertexDeclaration();

#ifdef USE_VAO
    if (mesh && glGenVertexArrays)
    {
        GL_ASSERT( glBindBuffer(GL_ARRAY_BUFFER, 0) );
        GL_ASSERT( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );

        // Use hardware VAOs.
        GL_ASSERT( glGenVertexArrays(1, &b->_handle) );

        if (b->_handle == 0)
        {
            SAFE_DELETE(b);
            return NULL;
        }

        // Bind the new VAO.
        GL_ASSERT( glBindVertexArray(b->_handle) );

        // Bind the C3DMesh VBO so our glVertexAttribPointer calls use it.
        GL_ASSERT( glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexBuffer()) );
    }
    else
#endif
    {
        // Construct a software representation of a VAO.
        C3DVertexDeclaration::C3DVertexAttribute* attribs = new C3DVertexDeclaration::C3DVertexAttribute[__maxVertexAttribs];
        for (unsigned int i = 0; i < __maxVertexAttribs; ++i)
        {
            // Set GL defaults
            attribs[i].enabled = GL_FALSE;
            attribs[i].size = 4;
            attribs[i].stride = 0;
            attribs[i].type = GL_FLOAT;
            attribs[i].normalized = GL_FALSE;
            attribs[i].pointer = 0;
        }
        b->_attributes = attribs;
    }

    if (mesh)
    {
        b->_mesh = mesh;
        mesh->retain();
    }
    
    b->_effect = effect;
    //effect->retain();

    // Call setVertexAttribPointer for each vertex element.
    std::string name;
    unsigned int offset = 0;
    for (unsigned int i = 0, count = vertexFormat->getElementCount(); i < count; ++i)
    {
        const C3DVertexElement* e = vertexFormat->getElement(i);

        cocos2d::VertexAttribute attrib;

        // Constructor vertex attribute name expected in shader.
        switch (e->usage)
        {
        case Vertex_Usage_POSITION:
            attrib = effect->getVertexAttribute(VERTEX_ATTRIBUTE_POSITION_NAME);
            break;
        case Vertex_Usage_NORMAL:
            attrib = effect->getVertexAttribute(VERTEX_ATTRIBUTE_NORMAL_NAME);
            break;
        case Vertex_Usage_COLOR:
            attrib = effect->getVertexAttribute(VERTEX_ATTRIBUTE_COLOR_NAME);
            break;
        case Vertex_Usage_TANGENT:
            attrib = effect->getVertexAttribute(VERTEX_ATTRIBUTE_TANGENT_NAME);
            break;
        case Vertex_Usage_BINORMAL:
            attrib = effect->getVertexAttribute(VERTEX_ATTRIBUTE_BINORMAL_NAME);
            break;
        case Vertex_Usage_BLENDWEIGHTS:
            attrib = effect->getVertexAttribute(VERTEX_ATTRIBUTE_BLENDWEIGHTS_NAME);
            break;
        case Vertex_Usage_BLENDINDICES:
            attrib = effect->getVertexAttribute(VERTEX_ATTRIBUTE_BLENDINDICES_NAME);
            break;
        case Vertex_Usage_TEXCOORD0:
            attrib = effect->getVertexAttribute(VERTEX_ATTRIBUTE_TEXCOORD_PREFIX_NAME);
            // Try adding a "0" after the texcoord attrib name (flexible name for this case).
            if (attrib == -1)
            {
                name = VERTEX_ATTRIBUTE_TEXCOORD_PREFIX_NAME;
                name += "0";
                attrib = effect->getVertexAttribute(name.c_str());
            }
            break; 
        case Vertex_Usage_TEXCOORD1:
        case Vertex_Usage_TEXCOORD2:
        case Vertex_Usage_TEXCOORD3:
        case Vertex_Usage_TEXCOORD4:
        case Vertex_Usage_TEXCOORD5:
        case Vertex_Usage_TEXCOORD6:
        case Vertex_Usage_TEXCOORD7:
            name = VERTEX_ATTRIBUTE_TEXCOORD_PREFIX_NAME;
            name += (e->usage - Vertex_Usage_TEXCOORD0) + '0';
            attrib = effect->getVertexAttribute(name.c_str());
            break;
        default:
            attrib = -1;
            break;
        }

        if (attrib == -1)
        {
            //WARN_VARG("Warning: Vertex element with usage '%s' in mesh '%s' does not correspond to an attribute in effect '%s'.", VertexFormat::toString(e.usage), mesh->getUrl(), effect->getId());
        }
        else
        {
            void* pointer = vertexPointer ? (void*)(((unsigned char*)vertexPointer) + offset) : (void*)offset;
            b->setVertexAttribPointer(attrib, (GLint)e->size, GL_FLOAT, GL_FALSE, (GLsizei)vertexFormat->getVertexSize(), pointer);
        }

        offset += e->size * sizeof(float);
    }

#ifdef USE_VAO
    if (b->_handle)
    {
        GL_ASSERT( glBindBuffer(GL_ARRAY_BUFFER, 0) );
        GL_ASSERT( glBindVertexArray(0) );
    }
#endif

    return b;
}

void C3DVertexDeclaration::setVertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalize, GLsizei stride, void* pointer)
{
    assert(indx < (GLuint)__maxVertexAttribs);

    if (_handle)
    {
        // Hardware mode
        GL_ASSERT( glEnableVertexAttribArray(indx) );
        GL_ASSERT( glVertexAttribPointer(indx, size, type, normalize, stride, pointer) );

    }
    else
    {
        // Software mode
        _attributes[indx].enabled = true;
        _attributes[indx].size = size;
        _attributes[indx].type = type;
        _attributes[indx].normalized = normalize;
        _attributes[indx].stride = stride;
        _attributes[indx].pointer = pointer;
    }
}

void C3DVertexDeclaration::bind()
{
#ifdef USE_VAO
    if (_handle)
    {
        // Hardware mode
        GL_ASSERT( glBindVertexArray(_handle) );
    }
    else
#endif
    {
        // Software mode
        if (_mesh)
        {
            GL_ASSERT( glBindBuffer(GL_ARRAY_BUFFER, _mesh->getVertexBuffer()) );
        }
        else
        {
            GL_ASSERT( glBindBuffer(GL_ARRAY_BUFFER, 0) );
        }

        for (unsigned int i = 0; i < __maxVertexAttribs; ++i)
        {
            C3DVertexAttribute& a = _attributes[i];
            if (a.enabled)
            {
                GL_ASSERT( glVertexAttribPointer(i, a.size, a.type, a.normalized, a.stride, a.pointer) );
                GL_ASSERT( glEnableVertexAttribArray(i) );
            }
        }
    }
}

void C3DVertexDeclaration::unbind()
{
#ifdef USE_VAO
    if (_handle)
    {
        // Hardware mode
        GL_ASSERT( glBindVertexArray(0) );
    }
    else
#endif
    {
        // Software mode
        if (_mesh)
        {
            GL_ASSERT( glBindBuffer(GL_ARRAY_BUFFER, 0) );
        }

        for (unsigned int i = 0; i < __maxVertexAttribs; ++i)
        {
            if (_attributes[i].enabled)
            {
                GL_ASSERT( glDisableVertexAttribArray(i) );
            }
        }
    }
}

}
