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
#include <map>
#include <unordered_map>

#include "2d/CCNode.h"
#include "base/ccTypes.h"
#include "math/CCGeometry.h"
#include "renderer/CCTexture2D.h"
#include "renderer/CCCustomCommand.h"

NS_CC_BEGIN
class ParticleEmitter;
class Particle;

class ParticleEffector : public Node
{
public:
    enum class ShapeType
    {
        CIRCLE,
        RECTANGLE,
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
                float radius;
            }circle;

            struct
            {
                float width;
                float height;
            }rectangle;
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

class Particle : public Ref
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
    Vec2 anchor;
    float positionZ;
    float rotationZ_X;
    float rotationZ_Y;
    float frame;
    Color4B color;
    ParticleEffector::ShapeType shapeType;
    Vector<ParticleEmitter*> emitters;
    
    Vec2 psPosition;
    Vec2 psSize;
    float psPositionZ;
    float psRotationZ_X;
    float psRotationZ_Y;
    
    Mat4 psEmitTransform;
    bool follow;
    
    //! the time particle can exist
    float life;
    //! the time particle already exist
    float live;
    //! when a particle life is end or deleted by emitter, it will be set to true
    bool dead;
    
CC_CONSTRUCTOR_ACCESS:
    Particle();
    virtual ~Particle();
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Particle);
};

class ParticleRendererProtocol;

class ParticleEmitter : public Node, public Clonable
{
public:
    enum { PARTICLEFRAME_MAX = 32 };
    
public:
    void setParticleParent(Node* parent) { _particleParent = parent; }
    Node* getParticleParent() const { return _particleParent; }
    /** set shapeType for frame, if particle set to this frame, it will be treat as the shape you specified.
     *  Default is ParticleEffector::ShapeType::RECTANGLE
    */
    void setParticleShape(int frame, ParticleEffector::ShapeType type, bool updateExist = false);
    
    int getParticlesCount() const { return (int)_particles.size(); }
    const Vector<Particle*>& getParticles() const { return _particles; }
    
    /** How many seconds the emitter will run. -1 means 'forever' */
    inline float getDuration() const { return _duration; }
    inline void setDuration(float duration) { _duration = duration; }
    
    inline float getFollow() const { return _follow; }
    inline void setFollow(bool follow) { _follow = follow; }
    
    virtual void clearParticles();
    
    virtual void addEffector(ParticleEffector* effector);
    virtual void removeEffector(ParticleEffector* effector);
    virtual void setRenderer(ParticleRendererProtocol* renderer);
    
    virtual void updateParticlesLife(float delta);
    virtual int spawnParticles(int need);
    virtual void updateParticles(float delta) = 0;
    virtual void updateEmitterTransform();
    virtual void updateParticlesTransform();
    virtual void updateEffectors(float delta);
    virtual void updateQuads();
    virtual void update(float delta) override;
    virtual void onEnter() override;
    virtual void onExit() override;
    
    virtual void start();
    virtual void stop();
    virtual void pause();
    virtual void reset();
    virtual void end();
    
    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags) override;
    
CC_CONSTRUCTOR_ACCESS:
    ParticleEmitter();
    virtual ~ParticleEmitter();
    
protected:
    virtual void spawnParticlesHelper(int need) = 0;
    
protected:
    Vector<Particle*> _particles;
    Vector<ParticleEffector*> _effectors;
    Vector<ParticleEmitter*> _emitters;
    ParticleRendererProtocol* _renderer;
    Node* _particleParent;
    //! position in particle coordinate system.
    Vec2 _psPosition;
    //! rotation in particle coordinate system.
    float _psPositionZ;
    float _psRotationZ_X;
    float _psRotationZ_Y;
    float _psScaleX;
    float _psScaleY;
    float _psScaleZ;
    bool _follow;
    int _need;
    bool _running;
    bool _active;
    //! time elapsed since the start of the system (in seconds)
    float _elapsed;
    /** How many seconds the emitter will run. -1 means 'forever' */
    float _duration;
    
    ParticleEffector::ShapeType _particleShapeType[PARTICLEFRAME_MAX];
    
    Mat4 _emitterTransform;
};

class ParticleRendererProtocol : public Ref
{
public:
    virtual void updateQuads(ParticleEmitter* emitter) = 0;
    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags) = 0;
    
CC_CONSTRUCTOR_ACCESS:
    ParticleRendererProtocol(){}
    virtual ~ParticleRendererProtocol(){}
};

class ParticleTextureAtlasRenderer : public ParticleRendererProtocol
{
public:
    static ParticleTextureAtlasRenderer* create(Texture2D* texture);
    
public:
    virtual void updateQuads(ParticleEmitter* emitter) override;
    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags) override;
    
    void setTexture(Texture2D* texture);
    Texture2D* getTexture();
    virtual void setTextureRectForFrame(int frame, const Rect& rect);
    virtual Rect getTextureRectForFrame(int frame);
    
protected:
    struct RenderStruct;
    void initIndices(RenderStruct* render);
    void updateVertexBuffer(RenderStruct* render);
    void updateIndexBuffer(RenderStruct* render);
    
    void onDraw(RenderStruct* render, int num);
    
CC_CONSTRUCTOR_ACCESS:
    ParticleTextureAtlasRenderer();
    virtual ~ParticleTextureAtlasRenderer();
    
    bool init(Texture2D* texture);
    
protected:
    struct RenderStruct
    {
        std::vector<V2F_C4B_T2F_Quad>   quads;        // quads to be rendered
        std::vector<GLushort> indices;      // indices
        GLuint              buffersVBO[2]; //0: vertex  1: indices
        CustomCommand command;           //command
        int nextAvalibleQuads;
        
        RenderStruct()
        : nextAvalibleQuads(0)
        {
            buffersVBO[0] = 0;
            buffersVBO[1] = 0;
        }
    };
    
    std::map<int, RenderStruct*> _render;   // each global z use a render command
    std::unordered_map<int, Rect> _rectForFrame;
    
    Texture2D* _texture;
    bool _lock;
};

NS_CC_END

#endif /* defined(__cocos2d_libs__CCParticleBase__) */
