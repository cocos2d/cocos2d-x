
#include "cocos2d.h"
#include "CCSprite3DEffect.h"
#include "renderer/CCGLProgram.h"

#include "CCMesh.h"
#include "CCSprite3D.h"


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

Sprite3DOutlineEffect::Sprite3DOutlineEffect(): _outlineWidth(0.1), _outlineColor(1.f, 1.f, 1.f)
{
    
}
Sprite3DOutlineEffect::~Sprite3DOutlineEffect()
{
}

bool Sprite3DOutlineEffect::init(Sprite3D* sprite)
{
    CC_ASSERT(_sprite == nullptr && sprite != nullptr);
    
    CC_SAFE_RETAIN(sprite);
    _sprite = sprite;
    
    GLProgram* program = GLProgram::createWithByteArrays(outLineShader, blackFrag);
    
    auto glProgramState = GLProgramState::getOrCreateWithGLProgram(program);
    
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

void Sprite3DOutlineEffect::setOutlineColor(const Vector3& color)
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

void Sprite3DOutlineEffect::drawSpriteEffect(const Matrix &transform)
{
    glCullFace(GL_FRONT);
    
    Color4F color(_sprite->getDisplayedColor());
    color.a = _sprite->getDisplayedOpacity() / 255.0f;
    
    _glProgramState->setUniformVec4("u_color", Vector4(color.r, color.g, color.b, color.a));
    
    auto mesh = _sprite->getMesh();
    for (int i = 0; i < mesh->getMeshPartCount(); i++)
    {
        auto meshPart = mesh->getMeshPart(i);
        glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexBuffer());
        _glProgramState->apply(transform);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshPart->getIndexBuffer());
        glDrawElements(meshPart->getPrimitiveType(), meshPart->getIndexCount(), meshPart->getIndexFormat(), 0);
    }
    
    glCullFace(GL_BACK);
}

NS_CC_END
