
#ifndef __SPRITE3DEFFECT_H_
#define __SPRITE3DEFFECT_H_

#include <vector>

#include "base/ccTypes.h"
#include "base/CCRef.h"
#include "math/CCMath.h"


NS_CC_BEGIN

class GLProgramState;
class Mesh;
class Sprite3D;

class Sprite3DEffect: public Ref
{
public:
    enum EffectType
    {
        OUT_LINE,
        MAX_EFFECT,
    };
    static Sprite3DEffect* create(EffectType type);
    
    virtual bool initEffect(Sprite3D* sprite) = 0;
    
    virtual void drawSpriteEffect(const Mat4 &transform) = 0;
    
protected:
    Sprite3DEffect();
    virtual ~Sprite3DEffect();
    
    Sprite3D*         _sprite;
    GLProgramState*   _glProgramState;
};

class Sprite3DOutlineEffect: public Sprite3DEffect
{
public:
    static Sprite3DOutlineEffect* create();
    
    virtual bool initEffect(Sprite3D* sprite) override;
    
    void setOutlineColor(const Vec3& color);
    
    void setOutlineWidth(float width);
    
    virtual void drawSpriteEffect(const Mat4 &transform) override;
    
protected:
    
    Sprite3DOutlineEffect();
    virtual ~Sprite3DOutlineEffect();

    Vec3 _outlineColor;
    float _outlineWidth;
    bool _hasNormal;
};

NS_CC_END
#endif // __SPRITE3DEFFECT_H_
