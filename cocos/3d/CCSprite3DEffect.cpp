
#include "cocos2d.h"
#include "CCSprite3DEffect.h"
#include "renderer/CCGLProgram.h"

#include "CCMesh.h"
#include "CCSprite3D.h"


#define STRINGIFY(A)  #A
//#include "../Shaders/TexturedLighting.es2.vert.h"
#include "Textured.es2.vert.h"
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

Sprite3DEffect::Sprite3DEffect()
:_sprite(nullptr)
{
}
Sprite3DEffect::~Sprite3DEffect()
{
    CC_SAFE_RELEASE(_sprite);
}

Sprite3DOutlineEffect* Sprite3DOutlineEffect::create()
{
    Sprite3DOutlineEffect* effect = new Sprite3DOutlineEffect();
    effect->autorelease();
    
    return effect;
}

Sprite3DOutlineEffect::Sprite3DOutlineEffect()
: _outlineWidth(0.1)
, _outlineColor(1.f, 1.f, 1.f)
, _hasNormal(false)
{
    
}
Sprite3DOutlineEffect::~Sprite3DOutlineEffect()
{
}

bool Sprite3DOutlineEffect::initEffect(Sprite3D* sprite)
{
    CC_ASSERT(_sprite == nullptr && sprite != nullptr);
    
    CC_SAFE_RETAIN(sprite);
    _sprite = sprite;
    
    _hasNormal = _sprite->getMesh()->hasVertexAttrib(GLProgram::VERTEX_ATTRIB_NORMAL);
    
    static GLProgram s_defGLProgram;
    if(s_defGLProgram.getProgram() == 0)
    {
        s_defGLProgram.initWithByteArrays(outLineShader, blackFrag);
        s_defGLProgram.link();
        s_defGLProgram.updateUniforms();
    }
    
    auto glProgramState = GLProgramState::getOrCreateWithGLProgram(&s_defGLProgram);
    
    setGLProgramState(glProgramState);
    
    auto mesh = _sprite->getMesh();
    int offset = 0;
    for (auto i = 0; i < mesh->getMeshVertexAttribCount(); i++) {
        auto meshvertexattrib = mesh->getMeshVertexAttribute(i);
        
        glProgramState->setVertexAttribPointer(s_attributeNames[meshvertexattrib.vertexAttrib], meshvertexattrib.size, meshvertexattrib.type, GL_FALSE, mesh->getVertexSizeInBytes(), (void*)offset);
        offset += meshvertexattrib.attribSizeBytes;
    }
    
    glProgramState->setUniformVec3("OutLineColor", _outlineColor);
    glProgramState->setUniformFloat("OutlineWidth", _outlineWidth);
    
    return true;
}
//
//void Sprite3DOutlineEffect::bind()
//{
//    //change render state
//    glCullFace(GL_FRONT);
//    
//    Sprite3DEffect::bind();
//}
//
//void Sprite3DOutlineEffect::unbind()
//{
//    Sprite3DEffect::unbind();
//    glCullFace(GL_BACK);
//}

void Sprite3DOutlineEffect::setOutlineColor(const Vec3& color)
{
    if (_outlineColor != color)
    {
        _outlineColor = color;
        _glProgramState->setUniformVec3("OutLineColor", _outlineColor);
    }
}

void Sprite3DOutlineEffect::setOutlineWidth(float width)
{
    if (_outlineWidth != width)
    {
        _outlineWidth = width;
        _glProgramState->setUniformFloat("OutlineWidth", _outlineWidth);
    }
}

void Sprite3DOutlineEffect::drawSpriteEffect(const Mat4 &transform)
{
    if (_hasNormal)
    {
        glCullFace(GL_FRONT);
        
        Color4F color(_sprite->getDisplayedColor());
        color.a = _sprite->getDisplayedOpacity() / 255.0f;
        
        _glProgramState->setUniformVec4("u_color", Vec4(color.r, color.g, color.b, color.a));
        
        auto mesh = _sprite->getMesh();
        glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexBuffer());
        _glProgramState->apply(transform);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndexBuffer());
        glDrawElements(mesh->getPrimitiveType(), mesh->getIndexCount(), mesh->getIndexFormat(), 0);
        
        glCullFace(GL_BACK);
    }
    else
    {
        CCLOGWARN("normal not exist, outline effect is not avaliable");
    }
}

NS_CC_END
