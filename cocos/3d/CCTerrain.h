/****************************************************************************
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
#ifndef CC_TERRAIN_H
#define CC_TERRAIN_H

#include <vector>

#include "2d/CCNode.h"
#include "2d/CCCamera.h"
#include "renderer/CCTexture2D.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCRenderState.h"
#include "3d/CCAABB.h"
#include "3d/CCRay.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"

NS_CC_BEGIN

/**
    @addtogroup _3d
    @{
*/

/**
    the maximum amount of the chunkes
**/
#define MAX_CHUNKES 256

/** @class Terrain
    @brief @~english Defines a Terrain that is capable of rendering large landscapes from 2D heightmap images.
    Terrains can be constructed from several different internal formats heightmap sources:
     1. RGB888
     2. RGBA8888
     3. Luminance(gray-scale)8

     Terrain use TerrainData struct to initialize.the TerrainData struct warp
     all parameters that Terrain initialization need.
     TerrainData provide several handy constructor for users

    Surface detail is provided via texture splatting, where multiple Detail texture layers can be added
    along with alpha map to define how different Detail texture blend with each other. These DetailTexture
    can be defined in TerrainData. The number of supported Detail texture is Four. although typically 2-3 levels is
    sufficient. For simple usage ,surface detail also is provided via simple Texture.

    Internally, Terrain is divide into smaller, more manageable chunks, which can be culled
    separately for more efficient rendering. The size of the terrain chunks can be controlled
    via the chunkSize property in TerrainData.

    Chunks are managed under the QuadTree.As DE FACTO terminal Node of the QuadTree;
    let us cull chunks efficientlly to reduce drawCall amount And reduce the VBOs'Size that pass to the GPU.

    Level of detail (LOD) is supported using a technique that is similar to texture mipmapping -- called GeoMapping.
    A distance-to-camera based test used to decide
    the appropriate LOD for a terrain chunk. The number of LOD levels is 0 by default (which
    means only the base level is used),the maxium number of LOD levels is 4. Of course ,you can hack the value individually.

    Finally, when LOD is enabled, cracks can begin to appear between terrain Chunks of
    different LOD levels. An acceptable solution might be to simply reduce the lower LOD(high detail,smooth) chunks border,
    And let the higher LOD(rough) chunks to seamlessly connect it.

    We can use ray-terrain intersection to pick a point of the terrain;
    Also we can get an arbitrary point of the terrain's height and normal vector for convenience .
    @~chinese 定义一个地形，它能够从2D图像高度图生成。
    地形可以从几个不同的内部格式高度图来构成：
     1. RGB888
     2. RGBA8888
     3.亮度（灰度等级）8

    表面细节是通过多个细节的纹理叠加实现
  **/
class CC_DLL Terrain : public Node
{
public:

    /** @~english the crack fix type. use to fix the gaps between different LOD chunks
        @~chinese 裂纹修复类型。用来修复不同LOD块之间的间隙
    */
    enum class CrackFixedType
    {
        SKIRT,
        INCREASE_LOWER,
    };

    /**
     *DetailMap
     *this struct maintain a detail map data ,including source file ,detail size.
     *the DetailMap can use for terrain splatting
     **/
    struct CC_DLL DetailMap
    {
        /*Constructors*/
        DetailMap();
        DetailMap(const char* detailMapSrc, float size = 35);
        /*detail Image source file path*/
        std::string _detailMapSrc;
        /*detailMapSize determine how many tiles that Terrain represent*/
        float _detailMapSize;
    };

    /**
     * Triangle
     */
    struct Triangle
    {
        Triangle(Vec3 p1, Vec3 p2, Vec3 p3);
        bool getInsterctPoint(const Ray &ray, Vec3& interScetPoint) const;
        void transform(Mat4 matrix);
        Vec3 _p1, _p2, _p3;
    };


   /**
    *TerrainData
    *This TerrainData struct warp all parameter that Terrain need to create
    */
    struct CC_DLL TerrainData
    {
        /** @~english empty constructor
            @~chinese 空的构造函数
        */
        TerrainData();
        /** @~english constructor, this constructor construct a simple terrain which only have 1 detailmap
            @~chinese 构造函数，该构造函数构造一个简单的地形，只有1 detailmap
        */
        TerrainData(const char* heightMapsrc, const char* textureSrc, const Size& chunksize = Size(32,32), float mapHeight = 2, float mapScale = 0.1);
        /** @~english constructor, this constructor construct a terrain which have 4 detailmaps, 1 alpha map
            @~chinese 构造函数，该构造函数构造一个地形，有4个detailmaps，1个Alpha地图
        */
        TerrainData(const char* heightMapsrc, const char* alphamap, const DetailMap& detail1,const DetailMap& detail2, const DetailMap& detail3, const DetailMap& detail4, const Size& chunksize = Size(32,32), float mapHeight = 2, float mapScale = 0.1);
        /** @~english constructor, this constructor construct a terrain which have 3 detailmaps, 1 alpha map
            @~chinese 构造函数，该构造函数构造一个地形，有3个detailmaps，1个Alpha地图
        */
        TerrainData(const char* heightMapsrc, const char* alphamap, const DetailMap& detail1,const DetailMap& detail2, const DetailMap& detail3, const Size& chunksize = Size(32,32), float mapHeight = 2, float mapScale = 0.1);
        /** @~english deterimine the chunk size,chunk is the minimal subdivision of the Terrain
            @~chinese 确定块大小，块是地形的最小细分
        */
        Size _chunkSize;
        /** @~english height Map source path
            @~chinese 高度图的源路径
        */
        std::string _heightMapSrc;
        /** @~english the source path of the alpha map
            @~chinese alpha通道贴图的源路径
        */
        char* _alphaMapSrc;
        /** @~english detail maps
            @~chinese 详细的地图
        */
        DetailMap _detailMaps[4];
        /** @~english terrain Maximum height
            @~chinese 地形最大高度
        */
        float _mapHeight;
        /** @~english terrain scale factor,you can combine setScale later.
            @~chinese 地形因子，你可以结合setScale以后。
        */
        float _mapScale;
        /** @~english the amount of detailmap
            @~chinese 对detailmap量
        */
        int _detailMapAmount;
        /** @~english the skirt height ratio, only effect when terrain use skirt to fix crack
            @~chinese 裙边的高度比，仅当地形使用裙边类型修复裂缝时有效
        */
        float _skirtHeightRatio;
    };
private:

    struct ChunkIndices
    {
        GLuint _indices;
        unsigned short _size;
    };

    struct ChunkLODIndices
    {
        int _relativeLod[5];
        ChunkIndices _chunkIndices;
    };


    struct ChunkLODIndicesSkirt
    {
        int _selfLod;
        ChunkIndices _chunkIndices;
    };

    /**
    *terrain vertices internal data format
    */
    struct TerrainVertexData
    {
        /*constructor*/
        TerrainVertexData() {};
        TerrainVertexData(Vec3 v1, Tex2F v2)
        {
            _position = v1;
            _texcoord = v2;
        };
        /*the vertex's attributes*/
        cocos2d::Vec3 _position;
        cocos2d::Tex2F _texcoord;
        cocos2d::Vec3 _normal;
    };

    struct QuadTree;
    /*
        the terminal node of quad, use to subdivision terrain mesh and LOD
    **/
    struct Chunk
    {
        /** @~english Constructor
            @~chinese 构造函数
        */
        Chunk();
        /** @~english destructor
            @~chinese 析构函数
        */
        ~Chunk();
        /*  @~english vertices
            @~chinese 顶点
        */
        std::vector<TerrainVertexData> _originalVertices;
        /*  @~english LOD indices
            @~chinese LOD索引
        */
        struct LOD
        {
            std::vector<GLushort> _indices;
        };
        GLuint _vbo;
        ChunkIndices _chunkIndices;
        /** @~english we now support four levels of detail
            @~chinese 我们现在支持四个级别的详细
        */
        LOD _lod[4];
        /** @~english AABB in local space
            @~chinese 在局部空间AABB
        */
        AABB _aabb;
        /** @~english setup Chunk data
            @~chinese 设置数据块
        */
        void generate(int map_width, int map_height, int m, int n, const unsigned char* data);
        /** @~english calculateAABB
            @~chinese calculateaabb
        */
        void calculateAABB();
        /** @~english internal use draw function
            @~chinese 内部使用的绘制函数
        */
        void bindAndDraw();
        /** @~english finish opengl setup
            @~chinese OpenGL设置完成
        */
        void finish();
        /*  @~english use linear-sample vertices for LOD mesh
            @~chinese 使用线性采样LOD网格顶点
        */
        void updateVerticesForLOD();
        /*  @~english updateIndices
            @~chinese updateindices
        */
        void updateIndicesLOD();

        void updateIndicesLODSkirt();

        /** @~english calculate the average slop of chunk
            @~chinese 计算块的平均斜率
        */
        void calculateSlope();

        bool getInsterctPointWithRay(const Ray& ray, Vec3 &interscetPoint);

        /** @~english current LOD of the chunk
            @~chinese 当前的块LOD
        */
        int _currentLod;

        int _oldLod;

        int _neighborOldLOD[4];
        /*the left,right,front,back neighbors*/
        Chunk* _left;
        Chunk* _right;
        Chunk* _front;
        Chunk* _back;

        QuadTree* _parent;

        /** @~english the position X in terrain space
            @~chinese 位置x在地形空间
        */
        int _posX;
        /** @~english the position Y in terrain space
            @~chinese 位置在地形空间
        */
        int _posY;
        /** @~english parent terrain
            @~chinese 父母的地形
        */
        Terrain* _terrain;
        /** @~english chunk size
            @~chinese 块的大小
        */
        Size _size;
        /** @~english chunk's estimated slope
            @~chinese 大块的斜率估计值
        */
        float _slope;
        std::vector<TerrainVertexData> _currentVertices;

        std::vector<Triangle> _trianglesList;
    };

    /**
        QuadTree
        @breif use to hierarchically frustum culling and set LOD
     **/
    struct QuadTree
    {
        /** @~english constructor
            @~chinese 构造函数
        */
        QuadTree(int x, int y, int width, int height, Terrain* terrain);
        /** @~english destructor
            @~chinese 析构函数
        */
        ~QuadTree();
        /** @~english recursively draw
            @~chinese 递归画
        */
        void draw();
        /** @~english recursively set itself and its children is need to draw
            @~chinese 递归的绘制自己和它的孩子
        */
        void resetNeedDraw(bool value);
        /** @~english recursively potential visible culling
            @~chinese 递归重置可见性
        */
        void cullByCamera(const Camera* camera, const Mat4& worldTransform);
        /** @~english precalculate the AABB(In world space) of each quad
            @~chinese 预先计算的AABB（世界空间）
        */
        void preCalculateAABB(const Mat4& worldTransform);
        QuadTree* _tl;
        QuadTree* _tr;
        QuadTree* _bl;
        QuadTree* _br;

        bool _isTerminal;
        Chunk* _chunk;
        int _posX;
        int _posY;
        int _height;
        int _width;
        QuadTree* _parent;
        /** @~english AABB's cache (in local space)
            @~chinese AABB的缓存（局部空间）
        */
        AABB _localAABB;
        /** @~english AABB's cache (in world space)
            @~chinese AABB的缓存（世界空间）
        */
        AABB _worldSpaceAABB;
        Terrain* _terrain;
        /** @~english  a flag determine whether a quadTree node need draw
            @~chinese 一个标志确定是否需要绘制四叉树节点
        */
        bool _needDraw;
    };
    friend QuadTree;
    friend Chunk;
public:

    /** @~english initialize all Properties which terrain need
        @~chinese 初始化所有地形需要的属性
    */
    bool initProperties();

    /** @~english initialize heightMap data
        @~chinese 高度图数据初始化
    */
    bool initHeightMap(const char* heightMap);

    /** @~english initialize alphaMap ,detailMaps textures
        @~chinese 初始化alphamap，detailmaps纹理
    */
    bool initTextures();

    /** @~english create and initialize terrain
        @~chinese 创建和初始化的地形
        @param parameter @~english  all parameter that Terrain need to create @~chinese 创建地形需要的所有参数
        @param fixedType @~english  the crack fix type. use to fix the gaps between different LOD chunks @~chinese 裂纹修复型，用来修复不同LOD块之间的间隙
        @return @~english A initialized terrain which is marked as "autorelease @~chinese 一个初始化的地形被标记为“自动释放
    */
    static Terrain* create(TerrainData& parameter, CrackFixedType fixedType = CrackFixedType::INCREASE_LOWER);

    /** @~english get specified position's height mapping to the terrain,use bi-linear interpolation method
        @~chinese 获取指定位置的高度映射到地形，使用双线性插值方法
        @param x @~english  the X position @~chinese X的位置
        @param z @~english  the Z position @~chinese Z位置
        @param normal @~english  the specified position's normal vector in terrain . if this argument is NULL or nullptr,Normal calculation shall be skip. @~chinese 在指定位置的法线矢量地形。如果这个参数为空或nullptr，正常计算应跳过。
        @return @~english the height value of the specified position of the terrain, if the (X,Z) position is out of the terrain bounds,it shall return 0; @~chinese 地形的指定位置的高度值，如果（x，z）位置的地形边界，它将返回0；
     **/
    float getHeight(float x, float z, Vec3 * normal= nullptr) const;

    /** @~english get specified position's height mapping to the terrain,use bi-linear interpolation method
        @~chinese 获取指定位置的高度映射到地形，使用双线性插值方法
        @param pos @~english  the position (X,Z) @~chinese 的位置（x，z）
        @param normal @~english  the specified position's normal vector in terrain . if this argument is NULL or nullptr,Normal calculation shall be skip. @~chinese 在指定位置的法线矢量地形。如果这个参数为空或nullptr，正常计算应跳过。
        @return @~english the height value of the specified position of the terrain, if the (X,Z) position is out of the terrain bounds,it shall return 0; @~chinese 地形的指定位置的高度值，如果（x，z）位置的地形边界，它将返回0；
     **/
    float getHeight(Vec2 pos, Vec3*Normal = nullptr) const;

    /** @~english get the normal of the specified pistion in terrain
        @~chinese 得到指定位置的法线
        @return @~english the normal vector of the specified position of the terrain. @~chinese 地形的指定位置的法向量。
        @note the fast normal calculation may not get precise normal vector.
     **/
    Vec3 getNormal(int pixelX, int pixelY) const;

    /** @~english get height from the raw height filed
        @~chinese 得到高度
        @param pixelX @~english  the position of x in raw height @~chinese X在原高度的位置
        @param pixelY @~english  the position of y in raw height @~chinese Y在原高度的位置
        @return @~english the height of position(x,y) @~chinese 位置（x，y）的高度
    */
    float getImageHeight(int pixelX, int pixelY) const;

    /** @~english show the wireline instead of the surface,Debug Use only
        @~chinese 显示线框模式，调试使用
        @param value @~english  the switching vale of method. @~chinese 方法的切。
        @Note only support desktop platform
     **/
    void setDrawWire(bool boolValue);

    /** @~english Set threshold distance of each LOD level,must equal or gereater than the chunk size
        @~chinese 每个级别设置阈值的距离，必须等于或大于块大小gereater
        @param lod1 @~english  the threshold of LOD level 1 @~chinese LOD 1级阈值
        @param lod2 @~english  the threshold of LOD level 2 @~chinese LOD 2级阈值
        @param lod3 @~english  the threshold of LOD level 3 @~chinese LOD 3级阈值
        @Note when invoke initHeightMap, the LOD distance will be automatic calculated.
    */
    void setLODDistance(float lod1, float lod2, float lod3);

    /** @~english Switch frustum Culling Flag
        @~chinese 视锥剔除标志开关
        @param boolValue @~english  the switching vale of method. @~chinese 方法的切换阀。
        @Note frustum culling will remarkable improve your terrain rendering performance.
    */
    void setIsEnableFrustumCull(bool boolValue);

    /** @~english  set the alpha map
        @~chinese 设置alpha地图
        @param newAlphaMapTexture @~english  a texture2d to be used as alpha map. @~chinese 一个Texture2D作为α-地图。
    */
    void setAlphaMap(cocos2d::Texture2D* newAlphaMapTexture);

    /** @~english set the Detail Map
        @~chinese 设置详细的地图
        @param index @~english  the index of detailmap to be seted. @~chinese 对detailmap指数被设定。
        @param detailMap @~english  the detailMap to be seted. @~chinese 要建立的detailmap。
    */
    void setDetailMap(unsigned int index, DetailMap detailMap);

    // Overrides, internal use only
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;

   /**
    * @~english Ray-Terrain intersection.
    * @~chinese 射线地形相交。
    * @param ray @~english  The ray used for intersection @~chinese 射线用于交叉口
    * @param intersectionPoint @~english Hit point if hitted. @~chinese 射线与地形的交点（如果有交点）。
    * @return @~english true if hit, false otherwise. @~chinese 返回true如果有交点，否则返回false。
    */
    bool getIntersectionPoint(const Ray & ray, Vec3 & intersectionPoint) const;

    /** @~english Ray-Terrain intersection.
        @~chinese 射线地形相交。
        @param ray @~english  the ray used for intersection @~chinese 射线用于交叉口
        @return @~english the intersection point @~chinese 交叉点
    */
    Vec3 getIntersectionPoint(const Ray& ray) const;

    /** @~english set the MaxDetailAmount.
        @~chinese 设置maxdetailamount。
        @param maxValue @~english  the maximum of detail map @~chinese 细节图最大
    */
    void setMaxDetailMapAmount(int maxValue);

    /** @~english Convert a world Space position (X,Z) to terrain space position (X,Z)
        @~chinese 将一个世界空间位置（x，z）地形的空间位置（x，z）
        @param worldSpace @~english  a world space position will be converted @~chinese 一个世界空间位置将被转换
        @return @~english a terrain space position @~chinese 地形的空间位置
    */
    Vec2 convertToTerrainSpace(Vec2 worldSpace)const;

    /** @~english reset the heightmap data.
        @~chinese 复位高度图数据。
        @param heightmap @~english  the new height map @~chinese 新的高度图
    */
    void resetHeightMap(const char* heightMap);

    /** @~english get the terrain's mininal height.
        @~chinese 得到地形的最小高度。
        @return @~english the min height of map @~chinese 图的最小高度
    */
    float getMinHeight();

    /** @~english get the terrain's maximum height.
        @~chinese 得到地形的最大高度。
        @return @~english the max height of map @~chinese 地图的最大高度
    */
    float getMaxHeight();

    /** @~english get the terrain's AABB(in world space)
        @~chinese 得到地形的AABB（世界空间）
        @return @~english the AABB of map @~chinese 地图的AABB
    */
    AABB getAABB();

    /** @~english set the skirt height ratio
        @~chinese 把裙子的高度比
        @param ratio @~english  the ratio of skirt height @~chinese 裙座高度比
    */
    void setSkirtHeightRatio(float ratio);

    /** @~english get the terrain's quad tree which is also the root node.
        @~chinese 得到地形的四叉树的根节点。
        @return @~english the terrain's quad tree @~chinese 地形的四叉树
    */
    QuadTree* getQuadTree();

    /** @~english reload sky box after GLESContext reconstructed.
        @~chinese 天空盒glescontext重装后重建。
    */
    void reload();

    /** @~english get the terrain's size
        @~chinese 得到地形的大小
        @return @~english the size of terrain @~chinese 地形的大小
    */
    Size getTerrainSize() const { return Size(_imageWidth, _imageHeight); }

    /** @~english get the terrain's height data
        @~chinese 得到的地形高度数据
        @return @~english the terrain's height data @~chinese 地形高度数据
    */
    std::vector<float> getHeightData() const;

protected:

    Terrain();
    virtual ~Terrain();
    void onDraw(const Mat4& transform, uint32_t flags);

    /** @~english recursively set each chunk's LOD
        @~chinese 递归的设置每个地形块的LOD
        @param cameraPos @~english  the camera postion in world space @~chinese 在世界空间中的摄像机位置
     **/
    void setChunksLOD(Vec3 cameraPos);

    /** @~english load Vertices from height filed for the whole terrain.
        @~chinese 从高度图加载地形顶点。
     **/
    void loadVertices();

    /** @~english calculate Normal Line for each Vertex
        @~chinese 计算每个顶点的法线
     **/
    void calculateNormal();

    //override
    virtual void onEnter() override;

    /** @~english cache all unifrom loactions in GLSL.
        @~chinese 缓存GLSL中所有uniform的位置。
     **/
    void cacheUniformAttribLocation();

    //IBO generate & cache
    ChunkIndices lookForIndicesLODSkrit(int selfLod, bool* result);

    ChunkIndices lookForIndicesLOD(int neighborLod[4], int selfLod, bool* result);

    ChunkIndices insertIndicesLOD(int neighborLod[4], int selfLod, GLushort* indices, int size);

    ChunkIndices insertIndicesLODSkirt(int selfLod, GLushort * indices, int size);
    
    Chunk * getChunkByIndex(int x,int y) const;

protected:
    std::vector <ChunkLODIndices> _chunkLodIndicesSet;
    std::vector<ChunkLODIndicesSkirt> _chunkLodIndicesSkirtSet;
    Mat4 _CameraMatrix;
    bool _isCameraViewChanged;
    TerrainData _terrainData;
    bool _isDrawWire;
    unsigned char* _data;
    float _lodDistance[3];
    Texture2D* _detailMapTextures[4];
    Texture2D* _alphaMap;
    CustomCommand _customCommand;
    QuadTree* _quadRoot;
    Chunk* _chunkesArray[MAX_CHUNKES][MAX_CHUNKES];
    std::vector<TerrainVertexData> _vertices;
    std::vector<GLushort> _indices;
    int _imageWidth;
    int _imageHeight;
    Size _chunkSize;
    bool _isEnableFrustumCull;
    int _maxDetailMapValue;
    cocos2d::Image* _heightMapImage;
    Mat4 _oldCameraModelMatrix;
    Mat4 _terrainModelMatrix;
    GLuint _normalLocation;
    GLuint _positionLocation;
    GLuint _texcordLocation;
    float _maxHeight;
    float _minHeight;
    CrackFixedType _crackFixedType;
    float _skirtRatio;
    int _skirtVerticesOffset[4];
    GLint _detailMapLocation[4];
    GLint _alphaMapLocation;
    GLint _alphaIsHasAlphaMapLocation;
    GLint _detailMapSizeLocation[4];

    RenderState::StateBlock* _stateBlock;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    EventListenerCustom* _backToForegroundListener;
#endif
};

// end of actions group
/// @}

NS_CC_END
#endif
