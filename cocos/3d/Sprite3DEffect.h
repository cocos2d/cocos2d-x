
#ifndef __SPRITE3DEFFECT_H_
#define __SPRITE3DEFFECT_H_

#include <vector>

#include "ccTypes.h"
#include "CCNode.h"
#include "MeshMaterial.h"
#include "CCMath.h"


NS_CC_BEGIN

class GLProgram;
class VertexDeclaration;
class Mesh;
class Sprite3D;

class Sprite3DEffect : public MeshMaterial
{
public:
    enum EffectType
    {
        OUT_LINE,
        MAX_EFFECT,
    };
    static Sprite3DEffect* create(EffectType type);
    
    virtual bool init(Sprite3D* sprite) = 0;
    
protected:
    Sprite3DEffect(){}
    virtual ~Sprite3DEffect(){}
    
};

class Sprite3DOutlineEffect: public Sprite3DEffect
{
public:
    static Sprite3DOutlineEffect* create();
    
    virtual bool init(Sprite3D* sprite);
    
    virtual void bind();
    
    virtual void unbind();
    
    void setOutlineColor(const math::Vector3& color);
    
    void setOutlineWidth(float width);
    
    
protected:
    
    Sprite3DOutlineEffect();
    virtual ~Sprite3DOutlineEffect();
    
    math::Vector3 _outlineColor;
    float _outlineWidth;
    
};

NS_CC_END
#endif // __SPRITE3DEFFECT_H_
