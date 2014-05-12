
#include "cocos2d.h"
#include "Sprite3DEffect.h"
#include "CCGLProgram.h"

#include "MeshMaterial.h"
#include "Mesh.h"
#include "Sprite3D.h"


#define STRINGIFY(A)  #A
//#include "../Shaders/TexturedLighting.es2.vert.h"
#include "Textured.es2.vert.h"
#include "Textured.es2.frag.h"
#include "Colored.es2.frag.h"


NS_CC_BEGIN

Sprite3DEffect* Sprite3DEffect::create(Sprite3DEffect::EffectType type)
{
    switch (type) {
        case Sprite3DEffect::OUT_LINE:
            return Sprite3DOutlineEffect::create();
            break;
            
        default:
            break;
    }
    return nullptr;
}

Sprite3DOutlineEffect* Sprite3DOutlineEffect::create()
{
    Sprite3DOutlineEffect* effect = new Sprite3DOutlineEffect();
    
    
    effect->autorelease();
    return effect;
}

Sprite3DOutlineEffect::Sprite3DOutlineEffect(): _outlineWidth(0.1), _outlineColor(0.f, 0.f, 0.f)
{
    
}
Sprite3DOutlineEffect::~Sprite3DOutlineEffect()
{
}

bool Sprite3DOutlineEffect::init(Sprite3D* sprite)
{
    GLProgram* program = new GLProgram();
    program->initWithByteArrays(outLineShader, blackFrag);
    
    program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
    program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
    
    program->bindAttribLocation(s_attribute_Normal_Name, s_attribute_Normal);
    
    program->link();
    
    program->updateUniforms();
    
    auto vertexDec = VertexDeclaration::create(sprite->getMesh(), program);
    
    setVertexDeclaration(vertexDec);
    return true;
}

void Sprite3DOutlineEffect::bind()
{
    //change render state
    glCullFace(GL_FRONT);
    
    Sprite3DEffect::bind();
}

void Sprite3DOutlineEffect::unbind()
{
    Sprite3DEffect::unbind();
    glCullFace(GL_BACK);
}

void Sprite3DOutlineEffect::setOutlineColor(const math::Vector3& color)
{
    getUniformValue("OutLineColor")->setValue(color);
    
    _outlineColor = color;
}

void Sprite3DOutlineEffect::setOutlineWidth(float width)
{
    getUniformValue("OutlineWidth")->setValue(width);
    
    _outlineWidth = width;
}

NS_CC_END
