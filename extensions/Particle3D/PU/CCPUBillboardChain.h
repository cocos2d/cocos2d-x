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

#ifndef __CC_PU_PARTICLE_3D_BILLBOARD_CHAIN_H__
#define __CC_PU_PARTICLE_3D_BILLBOARD_CHAIN_H__

#include <vector>
#include "renderer/CCRenderState.h"
#include "base/CCRef.h"
#include "math/CCMath.h"


NS_CC_BEGIN

class MeshCommand;
class GLProgramState;
class IndexBuffer;
class VertexBuffer;
class Texture2D;
class ParticleSystem3D;
class Renderer;

/**
* @addtogroup _3d
* @{
*/

/** @class PUBillboardChain
*@brief @~english internal class,  the tool class of PUBeamRender.
@~chinese 内部类，PUBeamRender的工具类。
*/
class PUBillboardChain
{

public:

    /**
    * @~english Contains the data of an element of the BillboardChain.
    * @~chinese 包含BillboardChain的数据。
    */
    class Element
    {

    public:

        Element();

        Element(const Vec3& position,
            float width,
            float texCoord,
            const Vec4& colour,
            const Quaternion& orientation);

        Vec3 position;
        float width;
        /// U or V texture coord depending on options
        float texCoord;
        Vec4 color;

        //Only used when mFaceCamera == false
        Quaternion orientation;
    };
    typedef std::vector<Element> ElementList;

    /**
    * @~english Constructor.
    * @~chinese 构造器
    * @param name   @~english The name to give this object. @~chinese 对象名称。
    * @param maxElements   @~english The maximum number of elements per chain. @~chinese 每一个chain包含元素的最大数目。
    * @param numberOfChains   @~english The number of separate chain segments contained in this object. @~chinese 单独的chain中包含该对象的数量。
    * @param useTextureCoords   @~english If true, use texture coordinates from the chain elements. @~chinese 为真时使用纹理坐标。
    * @param useVertexColours   @~english If true, use vertex colours from the chain elements. @~chinese 为真时使用顶点颜色。
    * @param dynamic   @~english If true, buffers are created with the intention of being updated. @~chinese 为真表示缓存区需要动态更新。
    */
    PUBillboardChain(const std::string& name, const std::string& texFile = "", size_t maxElements = 20, size_t numberOfChains = 1,
        bool useTextureCoords = true, bool useColours = true, bool dynamic = true);
    /// destructor
    virtual ~PUBillboardChain();

    /**
    * @~english Set the maximum number of chain elements per chain.
    * @~chinese 设置每一个chain包含元素的最大数目。
    * @param maxElements   @~english The maximum number of elements per chain. @~chinese 每一个chain包含元素的最大数目。
    */
    virtual void setMaxChainElements(size_t maxElements);
    /**
    * @~english Get the maximum number of chain elements per chain.
    * @~chinese 获取每一个chain包含元素的最大数目。
    * @return   @~english The maximum number of elements per chain. @~chinese 每一个chain包含元素的最大数目。
    */
    virtual size_t getMaxChainElements(void) const { return _maxElementsPerChain; }
    /**
    * @~english Set the number of chain segments (this class can render multiple chains at once using the same material).
    * @~chinese 设置每一个chain的分段数（该类可以使用一个材质同时渲染一次多个chains）。
    * @param numChains   @~english The number of chain segments. @~chinese chain的分段数。
    */
    virtual void setNumberOfChains(size_t numChains);
    /**
    * @~english Get the number of chain segments (this class can render multiple chains at once using the same material).
    * @~chinese 获取每一个chain的分段数（该类可以使用一个材质同时渲染一次多个chains）。
    * @return   @~english The number of chain segments. @~chinese chain的分段数。
    */
    virtual size_t getNumberOfChains(void) const { return _chainCount; }
    /**
    * @~english Sets whether texture coordinate information should be included in the final buffers generated.
    * @~chinese 设置是否把纹理坐标信息包含进缓存区。
    * @param use   @~english If use texture coordinate. @~chinese 是否使用纹理坐标。
    * @note You must use either texture coordinates or vertex colour since the
    * vertices have no normals and without one of these there is no source of
    * colour for the vertices.
    */
    virtual void setUseTextureCoords(bool use);
    /**
    * @~english Gets whether texture coordinate information should be included in the final buffers generated.
    * @~chinese 获取纹理坐标信息是否包含进缓存区。
    * @return   @~english If use texture coordinate. @~chinese 是否使用纹理坐标。
    */
    virtual bool getUseTextureCoords(void) const { return _useTexCoords; }

    /** The direction in which texture coordinates from elements of the
        chain are used.
    */
    enum TexCoordDirection
    {
        /** Tex coord in elements is treated as the 'u' texture coordinate */
        TCD_U,
        /** Tex coord in elements is treated as the 'v' texture coordinate */
        TCD_V
    };
    /**
    * @~english Sets the direction in which texture coords specified on each element are deemed to run along the length of the chain.
    * @~chinese 设置纹理坐标的方向上指定每个chain的元素长度。
    * @param dir   @~english The direction, default is TCD_U. @~chinese 纹理坐标方向，默认值为TCD_U。
    */
    virtual void setTextureCoordDirection(TexCoordDirection dir);
    /**
    * @~english Gets the direction in which texture coords specified on each element are deemed to run.
    * @~chinese 获取纹理坐标的方向上指定每个chain的元素长度。
    * @return   @~english The direction. @~chinese 纹理坐标方向。
    */
    virtual TexCoordDirection getTextureCoordDirection(void) { return _texCoordDir; }
    /**
    * @~english Set the range of the texture coordinates generated across the width of the chain elements.
    * @~chinese 设置每一个chain的元素生成的纹理坐标范围。
    * @param start   @~english Start coordinate, default 0.0. @~chinese 开始坐标，默认值为0。
    * @param end   @~english End coordinate, default 1.0. @~chinese 结束坐标，默认值为0。
    */
    virtual void setOtherTextureCoordRange(float start, float end);
    /**
    * @~english Get the range of the texture coordinates generated across the width of the chain elements.
    * @~chinese 获取每一个chain的元素生成的纹理坐标范围。
    * @return   @~english Start and End coordinate. @~chinese 开始结束坐标。
    */
    virtual const float* getOtherTextureCoordRange(void) const { return _otherTexCoordRange; }

    /**
    * @~english Sets whether vertex colour information should be included in the final buffers generated.
    * @~chinese 设置是否把顶点颜色信息包含进缓存区。
    * @param use   @~english If use vertex colour. @~chinese 是否使用顶点颜色。
    * @note You must use either texture coordinates or vertex colour since the
    * vertices have no normals and without one of these there is no source of
    * colour for the vertices.
    */
    virtual void setUseVertexColours(bool use);
    /**
    * @~english Gets whether vertex colour information should be included in the final buffers generated.
    * @~chinese 获取是否把顶点颜色信息包含进缓存区。
    * @return   @~english If use vertex colour. @~chinese 是否使用顶点颜色。
    */
    virtual bool getUseVertexColours(void) const { return _useVertexColour; }
    /**
    * @~english Sets whether or not the buffers created for this object are suitable for dynamic alteration.
    * @~chinese 设置是否把缓存作为动态缓存使用。
    * @param dyn   @~english If use dynamic buffers. @~chinese 是否使用动态缓存。
    */
    virtual void setDynamic(bool dyn);
    /**
    * @~english Gets whether or not the buffers created for this object are suitable for dynamic alteration.
    * @~chinese 获取是否把缓存作为动态缓存使用。
    * @return   @~english If use dynamic buffers. @~chinese 是否使用动态缓存。
    */
    virtual bool getDynamic(void) const { return _dynamic; }
        
    /**
    * @~english Add an element to the 'head' of a chain.
    * @~chinese 添加一个元素到chain的前端。
    * @param chainIndex   @~english The index of the chain. @~chinese chain的索引。
    * @param billboardChainElement   @~english The details to add. @~chinese 元素的内容。
    * @remarks
    * If this causes the number of elements to exceed the maximum elements
    * per chain, the last element in the chain (the 'tail') will be removed
    * to allow the additional element to be added.
    */
    virtual void addChainElement(size_t chainIndex, 
        const Element& billboardChainElement);
    /**
    * @~english Remove an element from the 'tail' of a chain.
    * @~chinese 从chain中移除一个元素。
    * @param chainIndex @~english The index of the chain. @~chinese chain的索引。
    */
    virtual void removeChainElement(size_t chainIndex);
    /**
    * @~english Update the details of an existing chain element.
    * @~chinese 更新Chain中的元素。
    * @param chainIndex @~english The index of the chain. @~chinese chain的索引。
    * @param elementIndex @~english The element index within the chain, measured from the 'head' of the chain. @~chinese element在chain中的索引。
    * @param billboardChainElement @~english The details to set. @~chinese 元素的内容。
    */
    virtual void updateChainElement(size_t chainIndex, size_t elementIndex, 
        const Element& billboardChainElement);
    /**
    * @~english Get the detail of a chain element.
    * @~chinese 获取Chain中的元素内容。
    * @param chainIndex @~english The index of the chain. @~chinese chain的索引。
    * @param elementIndex @~english The element index within the chain, measured from the 'head' of the chain. @~chinese element在chain中的索引。
    * @return @~english The details to set. @~chinese 元素的内容。
    */
    virtual const Element& getChainElement(size_t chainIndex, size_t elementIndex) const;

    /**
    * @~english Returns the number of chain elements.
    * @~chinese 返回chain中元素的数量。
    * @param chainIndex @~english The index of the chain. @~chinese chain的索引。
    */
    virtual size_t getNumChainElements(size_t chainIndex) const;
    /**
    * @~english Remove all elements of a given chain (but leave the chain intact).
    * @~chinese 移除指定chain中的所有元素。
    * @param chainIndex @~english The index of the chain. @~chinese chain的索引。
    */
    virtual void clearChain(size_t chainIndex);
    /**
    * @~english Remove all elements from all chains (but leave the chains themselves intact).
    * @~chinese 移除所有chain中的所有元素。
    */
    virtual void clearAllChains(void);
    /**
    * @~english Sets whether the billboard should always be facing the camera or a custom direction set by each point element.
    * @~chinese 是否让公告板始终面向摄像机或者自定义的方向。
    * @param faceCamera @~english If facing the camera. @~chinese 是否面向相机。
    * @param normalVector @~english Only used when faceCamera == false. Must be a non-zero vector. @~chinese 自定义的朝向。
    * @remarks
    * Billboards facing the camera are useful for smoke trails, light beams, etc by
    * simulating a cylinder. However, because of this property, wide trails can cause
    * several artefacts unless the head is properly covered.
    * Therefore, non-camera-facing billboards are much more convenient for leaving big
    * trails of movement from thin objects, for example a sword swing as seen in many
    * fighting games.
    */
    void setFaceCamera( bool faceCamera, const Vec3& normalVector=Vec3::UNIT_X );

    /**
    * @~english Set whether use depth test.
    * @~chinese 设置是否使用深度测试。
    * @param isDepthTest @~english Whether use depth test. @~chinese 是否使用深度测试。
    */
    void setDepthTest(bool isDepthTest);
    /**
    * @~english Set whether use depth write.
    * @~chinese 设置是否使用深度写。
    * @param isDepthWrite @~english Whether use depth write. @~chinese 是否使用深度写。
    */
    void setDepthWrite(bool isDepthWrite);
    /**
    * @~english Set whether use blend.
    * @~chinese 设置是否使用混合。
    * @param blendFunc @~english The blend function. @~chinese 混合方程。
    */
    void setBlendFunc(const BlendFunc& blendFunc);

    /**
    * @~english Rendering Chain.
    * @~chinese 渲染Chain。
    * @param renderer @~english The Renderer. @~chinese 渲染器。
    * @param transform @~english The transform to world. @~chinese 到世界坐标系的变换矩阵。
    * @param particleSystem @~english The current particle system. @~chinese 当前的粒子系统。
    */
    void render(Renderer* renderer, const Mat4& transform, ParticleSystem3D* particleSystem);

    // Overridden members follow
    //void _updateRenderQueue(RenderQueue*);
    //void getRenderOperation(RenderOperation&);
    //virtual bool preRender(SceneManager* sm, RenderSystem* rsys);
    //void getWorldTransforms(Matrix4*) const;
    /// @copydoc MovableObject::visitRenderables

    GLuint getTextureName();

protected:

    /** Setup the STL collections */
    virtual void setupChainContainers(void);
    /** Setup vertex declaration */
    virtual void setupVertexDeclaration(void);
    /** Setup buffers */
    virtual void setupBuffers(void);
    /** Update the contents of the vertex buffer */
    virtual void updateVertexBuffer(const Mat4& camMat);
    /** Update the contents of the index buffer */
    virtual void updateIndexBuffer(void);

    void init(const std::string& texFile);

protected:

    /** Maximum length of each chain */
    size_t _maxElementsPerChain;
    /** Number of chains */
    size_t _chainCount;
    /** Use texture coords? */
    bool _useTexCoords;
    /** Use vertex colour? */
    bool _useVertexColour;
    /** Dynamic use? */
    bool _dynamic;
    /** Is the vertex declaration dirty? */
    bool _vertexDeclDirty;
    /** Do the buffers need recreating? */
    bool _buffersNeedRecreating;
    /** Do the bounds need redefining? */
    mutable bool _boundsDirty;
    /** Is the index buffer dirty? */
    bool _indexContentDirty;
    /** Is the vertex buffer dirty? */
    bool _vertexContentDirty;
    /** Texture coord direction */
    TexCoordDirection _texCoordDir;
    /** Other texture coord range */
    float _otherTexCoordRange[2];
    /** When true, the billboards always face the camera */
    bool _faceCamera;
    /** Used when mFaceCamera == false; determines the billboard's "normal". i.e.
    * when the orientation is identity, the billboard is perpendicular to this
    * vector
    */
    Vec3 _normalBase;


    /** The list holding the chain elements */
    ElementList _chainElementList;

    /** Simple struct defining a chain segment by referencing a subset of
    *   the preallocated buffer (which will be mMaxElementsPerChain * mChainCount
    *   long), by it's chain index, and a head and tail value which describe
    *   the current chain. The buffer subset wraps at mMaxElementsPerChain
    *   so that head and tail can move freely. head and tail are inclusive,
    *   when the chain is empty head and tail are filled with high-values.
    */
    struct ChainSegment
    {
        /** The start of this chains subset of the buffer */
        size_t start;
        /** The 'head' of the chain, relative to start */
        size_t head;
        /** The 'tail' of the chain, relative to start */
        size_t tail;
    };
    typedef std::vector<ChainSegment> ChainSegmentList;
    ChainSegmentList _chainSegmentList;

    /** Chain segment has no elements */
    static const size_t SEGMENT_EMPTY;


    struct VertexInfo
    {
        Vec3 position;
        Vec2 uv;
        Vec4 color;
    };
    MeshCommand*            _meshCommand;
    RenderState::StateBlock* _stateBlock;
    Texture2D*              _texture;
    GLProgramState*         _glProgramState;
    IndexBuffer*            _indexBuffer;
    VertexBuffer*           _vertexBuffer;

    std::vector<VertexInfo> _vertices;
    std::vector<unsigned short> _indices;

    std::string            _texFile;
};

// end of _3d group
/// @}

NS_CC_END
#endif
