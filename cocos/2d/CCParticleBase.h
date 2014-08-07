/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 Copyright (c) 2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __cocos2d_libs__CCParticleBase__
#define __cocos2d_libs__CCParticleBase__

#include <vector>

#include "2d/CCNode.h"
#include "base/ccTypes.h"
#include "math/CCGeometry.h"
#include "CCTextureAtlas.h"

NS_CC_BEGIN
class ParticleEmitter;
class Particle;

class ParticleEffector : public Node
{
public:
    enum class ShapeType
    {
        RECTANGLE,
        CIRCLE,
    };
    
    enum class ContactType
    {
        OUT,
        IN,
    };
    
public:
    void setShape(Vec2 position, float width, float height);
    void setShape(Vec2 position, float radius);

    virtual void updateContact(float delta);
    virtual void updateParticles(float delta) = 0;
    virtual void update(float delta);
    
CC_CONSTRUCTOR_ACCESS:
    ParticleEffector();
    virtual ~ParticleEffector();
    
protected:
    struct Shape
    {
        union
        {
            struct
            {
                float width;
                float height;
            }rectangle;
            
            struct
            {
                float radius;
            }circle;
        }shape;
        
        ShapeType type;
    }_shape;
    // position in particle coordinate system.
    Vec2 _psPosition;
    // rotation in particle coordinate system.
    float _psRotation;
    
    // particles first touch effector
    Vector<Particle*> _touch;
    // particles in effector
    Vector<Particle*> _in;
    // particles first seprate from effctor
    Vector<Particle*> _out;
};

class Particle : public Ref, public Clonable
{
public:
    static Particle* create();
    
public:
    /**
     * add emitters to particle.
     * it will add each cloned emitter to _emitters.
     * @note it will clear the _emitters first.
     */
    void setEmitters(const Vector<ParticleEmitter*>& emitters);
    /**
     * add a emitter to particle.
     */
    void addEmitter(ParticleEmitter* emitter);
    
public:
    Vec2 velocity;
    Vec2 position;
    Vec2 size;
    float positionZ;
    float rotationX;
    float rotationY;
    float frame;
    float alpha;
    Color3B color;
    Vector<ParticleEmitter*> emitters;
    ParticleEffector::ShapeType shapeType;
    ParticleEffector::ContactType contactType;
    
CC_CONSTRUCTOR_ACCESS:
    Particle();
    virtual ~Particle();
};

class ParticleRendererProtocol;

class ParticleEmitter : public Node, public Clonable
{
public:
    enum { PARTICLEFRAME_MAX = 32 };
    
public:
    void setParticleParent(Node* parent);
    /** set shapeType for frame, if particle set to this frame, it will be treat as the shape you specified.
     *  Default is ParticleEffector::ShapeType::RECTANGLE
    */
    void setParticleShape(int frame, ParticleEffector::ShapeType type, bool updateExist = false);
    virtual void addEffector(ParticleEffector* effector);
    virtual void removeEffector(ParticleEffector* effector);
    virtual void setRenderer(ParticleRendererProtocol* renderer);
    
    virtual void spawnParticles(float delta, int need) = 0;
    virtual void updateParticles(float delta) = 0;
    virtual void updateEffectors(float delta);
    virtual void update(float delta);
    
    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags) override;
    
CC_CONSTRUCTOR_ACCESS:
    ParticleEmitter();
    virtual ~ParticleEmitter();
    
protected:
    Vector<Particle*> _particles;
    Vector<ParticleEffector*> _effectors;
    Vector<ParticleEmitter*> _emitters;
    ParticleRendererProtocol* _renderer;
    Node* _particleParent;
    // position in particle coordinate system.
    Vec2 _psPosition;
    // rotation in particle coordinate system.
    float _psRotation;
    int _need;
    
    ParticleEffector::ShapeType _particleShapeType[PARTICLEFRAME_MAX];
};

class ParticleRendererProtocol : public Ref
{
public:
    virtual void draw(ParticleEmitter* emitter, Renderer *renderer, const Mat4& transform, uint32_t flags) = 0;
    
CC_CONSTRUCTOR_ACCESS:
    ParticleRendererProtocol(){}
    virtual ~ParticleRendererProtocol(){}
};

class ParticleTextureAtlasRenderer : public ParticleRendererProtocol
{
public:
    virtual void draw(ParticleEmitter* emitter, Renderer *renderer, const Mat4& transform, uint32_t flags) override;
    
CC_CONSTRUCTOR_ACCESS:
    ParticleTextureAtlasRenderer();
    virtual ~ParticleTextureAtlasRenderer();
    
protected:
    V2F_C4B_T2F_Quad* _quads;
    TextureAtlas* _atlas;
};

NS_CC_END

#endif /* defined(__cocos2d_libs__CCParticleBase__) */
