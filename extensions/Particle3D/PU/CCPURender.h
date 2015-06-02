/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015 Chukong Technologies Inc.
 
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

#ifndef __CC_PU_PARTICLE_3D_RENDER_H__
#define __CC_PU_PARTICLE_3D_RENDER_H__

#include <vector>

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "extensions/Particle3D/CCParticle3DRender.h"
#include "renderer/CCRenderState.h"

NS_CC_BEGIN

struct PUParticle3D;

/**
* @addtogroup _3d
* @{
*/

/** @class PURender
*@brief @~english PURender inherit from Particle3DRender, is base class of pu renderer.
Specific implementation decisions by different renderers.

@~chinese PURender 继承自Particle3DRender，是pu渲染器的基类。
具体的实现由不同的渲染器类型定义。
*/
class CC_DLL PURender : public Particle3DRender
{
public:

    /**
    * @~english The function is automatically called during initialisation (prepare) activities of a ParticleSystem(internal method).
    * @~chinese 当一个粒子系统初始化时自动执行(内部方法)。
    */
    virtual void prepare(){};

    /**
    * @~english The function is automatically called when a ParticleSystem is expired(internal method).
    * @~chinese 当一个粒子系统失效时自动执行(内部方法)。
    */
    virtual void unPrepare(){};

    /**
    * @~english This function is called when the ParticleSystem update-loop where all particles are traversed(internal method).
    * @~chinese 在粒子系统更新循环粒子遍历时执行(内部方法)。
    * @param particle   @~english The current traversed particle. @~chinese 当前遍历到的粒子。
    * @param deltaTime   @~english The delta time between two frames. @~chinese 两帧之间的时间间隔。
    * @param firstParticle   @~english Is first update particle. @~chinese 是否是第一个更新的粒子。
    */
    virtual void updateRender(PUParticle3D *particle, float deltaTime, bool firstParticle){};

    /**
    * @~english Get render type.
    * quad,model,box,sphere,beam, or ribbon trail.
    * @~chinese 获取渲染类型。
    * 四边形，模型，箱形，球形，光线形，拖尾形。
    * @return   @~english The type name. @~chinese 类型名称。
    */
    const std::string& getRenderType(void) const {return _renderType;};

    /**
    * @~english Set render type.
    * @~chinese 设置渲染类型。
    * @param observerType   @~english The type name. @~chinese 类型名称。
    */
    void setRenderType(const std::string& observerType) {_renderType = observerType;};

    /**
    * @~english Clone this renderer.
    * @~chinese 拷贝当前渲染器。
    */
    virtual PURender* clone() = 0;

    /**
    * @~english Copy one renderer's attributes to another's(internal method).
    * @~chinese 拷贝一个渲染器的属性到另外一个(内部方法)。
    * @param render @~english the renderer need be copied. @~chinese 拷贝属性的渲染器。
    */
    void copyAttributesTo(PURender* render);

public:

    bool autoRotate; ///< Means that the objects to render automatically rotate if the node to which the particle system is attached, rotates.

protected:

    std::string _renderType;
};

/** @class PUParticle3DEntityRender
*@brief @~english PUParticle3DEntityRender inherit from PURender, is base class of entity renderer.
entity include：
quad(billboard).
box.
sphere.

@~chinese PUParticle3DEntityRender 继承自PURender，是实体渲染器的基类。
实体包括：
四边形（公告板）
箱形
球形
*/
class CC_DLL PUParticle3DEntityRender : public PURender
{
public:

    /**
    * @~english Copy one entity renderer's attributes to another's(internal method).
    * @~chinese 拷贝一个实体渲染器的属性到另外一个(内部方法)。
    * @param render @~english the renderer need be copied. @~chinese 拷贝属性的渲染器。
    */
    void copyAttributesTo(PUParticle3DEntityRender *render);

CC_CONSTRUCTOR_ACCESS:
    PUParticle3DEntityRender();
    virtual ~PUParticle3DEntityRender();

protected:

    bool initRender(const std::string &texFile);

protected:

    struct VertexInfo
    {
        Vec3 position;
        Vec2 uv;
        Vec4 color;
    };
    MeshCommand* _meshCommand;
    RenderState::StateBlock* _stateBlock;
    Texture2D*             _texture;
    GLProgramState*        _glProgramState;
    IndexBuffer*           _indexBuffer; //index buffer
    VertexBuffer*          _vertexBuffer; // vertex buffer

    std::vector<VertexInfo> _vertices;
    std::vector<unsigned short> _indices;

    std::string _texFile;
};

/** @class PUParticle3DQuadRender
*@brief @~english PUParticle3DQuadRender inherit from PUParticle3DEntityRender, , implement pu quad rendering.

@~chinese PUParticle3DQuadRender 继承自PUParticle3DEntityRender，实现了pu的四边形渲染。
*/
class CC_DLL PUParticle3DQuadRender : public PUParticle3DEntityRender
{
public:

    enum Type
    {
        POINT,
        ORIENTED_COMMON,
        ORIENTED_SELF,
        ORIENTED_SHAPE,
        PERPENDICULAR_COMMON,
        PERPENDICULAR_SELF,
    };

    enum Origin
    {
        TOP_LEFT,
        TOP_CENTER,
        TOP_RIGHT,
        CENTER_LEFT,
        CENTER,
        CENTER_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_CENTER,
        BOTTOM_RIGHT
    };

    enum RotateType
    {
        TEXTURE_COORDS,
        VERTEX
    };

    /**
    * @~english Create a new quad renderer.
    * @~chinese 创建一个新的四边形渲染器。
    * @param texFile @~english The texture of particles. @~chinese 粒子使用的纹理。
    */
    static PUParticle3DQuadRender* create(const std::string& texFile = "");
    
    /**
    * @~english Set the orientation type of quad.
    * @~chinese 设置四边形的朝向类型。
    * @param type @~english The orientation type. @~chinese 朝向类型。
    */
    void setType(Type type);

    /**
    * @~english Get the orientation type of quad.
    * @~chinese 获取四边形的朝向类型。
    * @param type @~english The orientation type. @~chinese 朝向类型。
    */
    Type getType() const { return _type; }

    /**
    * @~english Set the center of quad.
    * @~chinese 设置四边形的中心。
    * @param origin @~english The center of quad. @~chinese 四边形中心。
    */
    void setOrigin(Origin origin) { _origin = origin; }

    /**
    * @~english Get the center of quad.
    * @~chinese 获取四边形的中心。
    * @return @~english The center of quad. @~chinese 四边形中心。
    */
    Origin getOrigin() const { return _origin; }

    /**
    * @~english Set the rotation type of quad.
    * @~chinese 设置四边形的旋转类型。
    * @param type @~english The orientation type. @~chinese 旋转类型。
    */
    void setRotateType(RotateType type) { _rotateType = type; }

    /**
    * @~english Get the rotation type of quad.
    * @~chinese 获取四边形的旋转类型。
    * @param type @~english The orientation type. @~chinese 旋转类型。
    */
    RotateType getRotateType() const { return _rotateType; }

    /**
    * @~english Set the direction when type is ORIENTED_COMMON or PERPENDICULAR_COMMON.
    * @~chinese 当朝向类型为ORIENTED_COMMON或PERPENDICULAR_COMMON时设置方向。
    * @param dir @~english The direction. @~chinese 方向。
    */
    void setCommonDirection(const Vec3 &dir) { _commonDir = dir; }

    /**
    * @~english Get the direction when type is ORIENTED_COMMON or PERPENDICULAR_COMMON.
    * @~chinese 当朝向类型为ORIENTED_COMMON或PERPENDICULAR_COMMON时获取方向。
    * @return @~english The direction. @~chinese 方向。
    */
    const Vec3& getCommonDirection() const { return _commonDir; }

    /**
    * @~english Set the up when type is ORIENTED_COMMON or PERPENDICULAR_COMMON.
    * @~chinese 当朝向类型为ORIENTED_COMMON或PERPENDICULAR_COMMON时设置四边形上朝向。
    * @param up @~english The up. @~chinese 四边形上朝向。
    */
    void setCommonUp(const Vec3 &up) { _commonUp = up; }

    /**
    * @~english Get the up when type is ORIENTED_COMMON or PERPENDICULAR_COMMON.
    * @~chinese 当朝向类型为ORIENTED_COMMON或PERPENDICULAR_COMMON时获取四边形上朝向。
    * @return @~english The up. @~chinese 四边形上朝向。
    */
    const Vec3& getCommonUp() const { return _commonUp; }

    /**
    * @~english Get frame texture row count.
    * @~chinese 获取序列帧纹理的行数。
    * @return @~english The row count. @~chinese 行数。
    */
    unsigned short getTextureCoordsRows() const;

    /**
    * @~english Set frame texture row count.
    * @~chinese 设置序列帧纹理的行数。
    * @param textureCoordsRows @~english The row count. @~chinese 行数。
    */
    void setTextureCoordsRows(unsigned short textureCoordsRows);

    /**
    * @~english Get frame texture column count.
    * @~chinese 获取序列帧纹理的列数。
    * @param textureCoordsRows @~english The column count. @~chinese 列数。
    */
    unsigned short getTextureCoordsColumns() const;

    /**
    * @~english Set frame texture column count.
    * @~chinese 设置序列帧纹理的列数。
    * @param textureCoordsColumns @~english The column count. @~chinese 列数。
    */
    void setTextureCoordsColumns(unsigned short textureCoordsColumns);

    /**
    * @~english Get frame texture count(row x column).
    * @~chinese 获取序列帧纹理总数（行数x列数）。
    * @return @~english The total count. @~chinese 总数。
    */
    unsigned int getNumTextureCoords();

    /**
    * @~english Overwrite function.
    * @~chinese 重写的函数。
    * @see Particle3DRender render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem);
    */
    virtual void render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem) override;

    /**
    * @~english Clone this renderer.
    * @~chinese 拷贝当前渲染器。
    */
    virtual PUParticle3DQuadRender* clone() override;

    /**
    * @~english Copy one quad renderer's attributes to another's(internal method).
    * @~chinese 拷贝一个四边形渲染器的属性到另外一个(内部方法)。
    * @param render @~english The renderer need be copied. @~chinese 拷贝属性的渲染器。
    */
    void copyAttributesTo(PUParticle3DQuadRender *render);
    
CC_CONSTRUCTOR_ACCESS:
    PUParticle3DQuadRender();
    virtual ~PUParticle3DQuadRender();

protected:

    void getOriginOffset(int &offsetX, int &offsetY);
    void determineUVCoords(PUParticle3D *particle);
    void fillVertex(unsigned short index, const Vec3 &pos, const Vec4 &color, const Vec2 &uv);
    void fillTriangle(unsigned short index, unsigned short v0, unsigned short v1, unsigned short v2);

protected:

    Type _type;
    Origin _origin;
    RotateType _rotateType;
    Vec3 _commonDir;
    Vec3 _commonUp;

    unsigned short _textureCoordsRows;
    unsigned short _textureCoordsColumns;
    float _textureCoordsRowStep;
    float _textureCoordsColStep;
};

/** @class PUParticle3DModelRender
*@brief @~english PUParticle3DModelRender inherit from PURender, , implement pu model rendering.

@~chinese PUParticle3DModelRender 继承自PURender，实现了pu的模型渲染。
*/
class CC_DLL PUParticle3DModelRender : public PURender
{
public:

    /**
    * @~english Create a new model renderer.
    * @~chinese 创建一个新的模型渲染器。
    * @param modelFile @~english The model of particles. @~chinese 粒子使用的模型。
    * @param texFile @~english The texture of particles. @~chinese 粒子使用的纹理。
    */
    static PUParticle3DModelRender* create(const std::string& modelFile, const std::string &texFile = "");

    /**
    * @~english Overwrite function.
    * @~chinese 重写的函数。
    * @see Particle3DRender render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem);
    */
    virtual void render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem) override;

    /**
    * @~english Clone this renderer.
    * @~chinese 拷贝当前渲染器。
    */
    virtual PUParticle3DModelRender* clone() override;

    /**
    * @~english Copy one model renderer's attributes to another's(internal method).
    * @~chinese 拷贝一个模型渲染器的属性到另外一个(内部方法)。
    * @param render @~english The renderer need be copied. @~chinese 拷贝属性的渲染器。
    */
    void copyAttributesTo(PUParticle3DModelRender *render);

CC_CONSTRUCTOR_ACCESS:
    PUParticle3DModelRender();
    virtual ~PUParticle3DModelRender();

protected:

    std::vector<Sprite3D *> _spriteList;
    std::string _modelFile;
    std::string _texFile;
    Vec3 _spriteSize;
};

/** @class PUParticle3DBoxRender
*@brief @~english PUParticle3DBoxRender inherit from PUParticle3DEntityRender, , implement pu box rendering.

@~chinese PUParticle3DBoxRender 继承自PUParticle3DEntityRender，实现了pu的箱形渲染。
*/
class CC_DLL PUParticle3DBoxRender : public PUParticle3DEntityRender
{
public:

    /**
    * @~english Create a new box renderer.
    * @~chinese 创建一个新的箱形渲染器。
    * @param texFile @~english The texture of particles. @~chinese 粒子使用的纹理。
    */
    static PUParticle3DBoxRender* create(const std::string &texFile = "");

    /**
    * @~english Overwrite function.
    * @~chinese 重写的函数。
    * @see Particle3DRender render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem);
    */
    virtual void render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem) override;

    /**
    * @~english Clone this renderer.
    * @~chinese 拷贝当前渲染器。
    */
    virtual PUParticle3DBoxRender* clone() override;

CC_CONSTRUCTOR_ACCESS:
    PUParticle3DBoxRender();
    virtual ~PUParticle3DBoxRender();

protected:

    void reBuildIndices(unsigned short count);
};

/** @class PUSphereRender
*@brief @~english PUSphereRender inherit from PUParticle3DEntityRender, , implement pu sphere rendering.

@~chinese PUSphereRender 继承自PUParticle3DEntityRender，实现了pu的球形渲染。
*/
class CC_DLL PUSphereRender : public PUParticle3DEntityRender
{
public:

    /**
    * @~english Create a sphere renderer.
    * @~chinese 创建一个新的球形渲染器。
    * @param texFile @~english The texture of particles. @~chinese 粒子使用的纹理。
    */
    static PUSphereRender* create(const std::string &texFile = "");

    /**
    * @~english Overwrite function.
    * @~chinese 重写的函数。
    * @see Particle3DRender render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem);
    */
    virtual void render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem) override;

    /**
    * @~english Clone this renderer.
    * @~chinese 拷贝当前渲染器。
    */
    virtual PUSphereRender* clone() override;

    /**
    * @~english Copy one sphere renderer's attributes to another's(internal method).
    * @~chinese 拷贝一个球形渲染器的属性到另外一个(内部方法)。
    * @param render @~english The renderer need be copied. @~chinese 拷贝属性的渲染器。
    */
    void copyAttributesTo(PUSphereRender *render);

CC_CONSTRUCTOR_ACCESS:
    PUSphereRender();
    virtual ~PUSphereRender();

protected:

    void buildBuffers(unsigned short count);

protected:

    unsigned short _numberOfRings;
    unsigned short _numberOfSegments;
    std::vector<VertexInfo> _vertexTemplate;
};

// end of _3d group
/// @}

NS_CC_END
#endif
