
#ifndef __SPRITE3DEFFECT_H_
#define __SPRITE3DEFFECT_H_

#include <vector>

#include "base/ccTypes.h"
#include "2d/CCNode.h"
#include "math/CCMath.h"


NS_CC_BEGIN

class GLProgramState;
class Mesh;
class Sprite3D;

class Sprite3DEffect: public Node
{
public:
    enum EffectType
    {
        OUT_LINE,
        MAX_EFFECT,
    };
    static Sprite3DEffect* create(EffectType type);
    
    virtual bool init(Sprite3D* sprite) = 0;
    
    virtual void drawSpriteEffect(const Matrix &transform) = 0;
    
protected:
    Sprite3DEffect();
    virtual ~Sprite3DEffect();
    
    Sprite3D*         _sprite;
};

class Sprite3DOutlineEffect: public Sprite3DEffect
{
public:
    static Sprite3DOutlineEffect* create();
    
    virtual bool init(Sprite3D* sprite);
    
    void setOutlineColor(const Vector3& color);
    
    void setOutlineWidth(float width);
    
    virtual void drawSpriteEffect(const Matrix &transform);
    
protected:
    
    Sprite3DOutlineEffect();
    virtual ~Sprite3DOutlineEffect();

    Vector3 _outlineColor;
    float _outlineWidth;
};

NS_CC_END
#endif // __SPRITE3DEFFECT_H_
