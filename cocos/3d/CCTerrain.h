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
 * @addtogroup _3d
 * @{
 */

 /**
 * the maximum amount of the chunkes
 **/
#define MAX_CHUNKES 256

  /**
    * Terrain
    * Defines a Terrain that is capable of rendering large landscapes from 2D heightmap images.
    * Terrains can be constructed from several different internal formats heightmap sources:
    *  1. RGB888
    *  2. RGBA8888
    *  3. Luminance(gray-scale)8
    *  
    *  Terrain use TerrainData struct to initialize.the TerrainData struct warp 
    *  all parameters that Terrain initialization need.
    *  TerrainData provide several handy constructor for users
    *  
    * Surface detail is provided via texture splatting, where multiple Detail texture layers can be added
    * along with alpha map to define how different Detail texture blend with each other. These DetailTexture
    * can be defined in TerrainData. The number of supported Detail texture is Four. although typically 2-3 levels is
    * sufficient. For simple usage ,surface detail also is provided via simple Texture.
    * 
    * Internally, Terrain is divide into smaller, more manageable chunks, which can be culled
    * separately for more efficient rendering. The size of the terrain chunks can be controlled
    * via the chunkSize property in TerrainData.
    * 
    * Chunks are managed under the QuadTree.As DE FACTO terminal Node of the QuadTree;
    * let us cull chunks efficientlly to reduce drawCall amount And reduce the VBOs'Size that pass to the GPU.
    * 
    * Level of detail (LOD) is supported using a technique that is similar to texture mipmapping -- called GeoMapping.
    * A distance-to-camera based test used to decide
    * the appropriate LOD for a terrain chunk. The number of LOD levels is 0 by default (which
    * means only the base level is used),the maxium number of LOD levels is 4. Of course ,you can hack the value individually.
    * 
    * Finally, when LOD is enabled, cracks can begin to appear between terrain Chunks of
    * different LOD levels. An acceptable solution might be to simply reduce the lower LOD(high detail,smooth) chunks border,
    * And let the higher LOD(rough) chunks to seamlessly connect it.
    * 
    * We can use ray-terrain intersection to pick a point of the terrain;
    * Also we can get an arbitrary point of the terrain's height and normal vector for convenience .
    **/
class CC_DLL Terrain : public Node
{
public:

    /**the crack fix type. use to fix the gaps between different LOD chunks */
    enum class CrackFixedType{
        SKIRT,
        INCREASE_LOWER,
    };

   /**
    *DetailMap
    *this struct maintain a detail map data ,including source file ,detail size.
    *the DetailMap can use for terrain splatting
    **/
    struct CC_DLL DetailMap{
        /*Constructors*/
        DetailMap();
        DetailMap(const char * detailMapSrc, float size = 35);
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
        /**empty constructor*/
        TerrainData();
        /**constructor, this constructor construct a simple terrain which only have 1 detailmap*/
        TerrainData(const char* heightMapsrc, const char * textureSrc, const Size & chunksize = Size(32,32), float mapHeight = 2, float mapScale = 0.1);
        /**constructor, this constructor construct a terrain which have 4 detailmaps, 1 alpha map*/
        TerrainData(const char* heightMapsrc, const char * alphamap, const DetailMap& detail1,const DetailMap& detail2, const DetailMap& detail3, const DetailMap& detail4, const Size & chunksize = Size(32,32), float mapHeight = 2, float mapScale = 0.1);
        /**constructor, this constructor construct a terrain which have 3 detailmaps, 1 alpha map*/
        TerrainData(const char* heightMapsrc, const char * alphamap, const DetailMap& detail1,const DetailMap& detail2, const DetailMap& detail3, const Size & chunksize = Size(32,32), float mapHeight = 2, float mapScale = 0.1);
        /**
        *deterimine the chunk size,chunk is the minimal subdivision of the Terrain
        */
        Size _chunkSize;
        /**height Map source path*/
        std::string _heightMapSrc;
        /**the source path of the alpha map*/
        char* _alphaMapSrc;
        /**detail maps*/
        DetailMap _detailMaps[4];
        /**terrain Maximum height*/
        float _mapHeight;
        /**terrain scale factor,you can combine setScale later.*/
        float _mapScale;
        /**the amount of detailmap*/
        int _detailMapAmount;
        /**the skirt height ratio, only effect when terrain use skirt to fix crack*/
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
    /*
    *terrain vertices internal data format
    **/
    struct TerrainVertexData
    {
        /*constructor*/
        TerrainVertexData(){};
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
    *the terminal node of quad, use to subdivision terrain mesh and LOD
    **/
    struct Chunk
    {
        /**Constructor*/
        Chunk();
        /**destructor*/
        ~Chunk();
        /*vertices*/
        std::vector<TerrainVertexData> _originalVertices;
        /*LOD indices*/
        struct LOD{
            std::vector<GLushort> _indices;
        };
        GLuint _vbo;
        ChunkIndices _chunkIndices; 
        /**we now support four levels of detail*/
        LOD _lod[4];
        /**AABB in local space*/
        AABB _aabb;
        /**setup Chunk data*/
        void generate(int map_width, int map_height, int m, int n, const unsigned char * data);
        /**calculateAABB*/
        void calculateAABB();
        /**internal use draw function*/
        void bindAndDraw();
        /**finish opengl setup*/
        void finish();
        /*use linear-sample vertices for LOD mesh*/
        void updateVerticesForLOD();
        /*updateIndices */
        void updateIndicesLOD();

        void updateIndicesLODSkirt();

        /**calculate the average slop of chunk*/
        void calculateSlope();

        bool getInsterctPointWithRay(const Ray& ray, Vec3 &interscetPoint);

        /**current LOD of the chunk*/
        int _currentLod;

        int _oldLod;

        int _neighborOldLOD[4];
        /*the left,right,front,back neighbors*/
        Chunk * _left;
        Chunk * _right;
        Chunk * _front;
        Chunk * _back;

        QuadTree * _parent;

        /**the position X in terrain space*/
        int _posX;
        /**the position Y in terrain space*/
        int _posY;
        /**parent terrain*/
        Terrain * _terrain;
        /**chunk size*/
        Size _size;
        /**chunk's estimated slope*/
        float _slope;
        std::vector<TerrainVertexData> _currentVertices;

        std::vector<Triangle> _trianglesList;
    };

   /**
    *QuadTree
    * @breif use to hierarchically frustum culling and set LOD
    **/
    struct QuadTree
    {
        /**constructor*/
        QuadTree(int x, int y, int width, int height, Terrain * terrain);
        /**destructor*/
        ~QuadTree();
        /**recursively draw*/
        void draw();
        /**recursively set itself and its children is need to draw*/
        void resetNeedDraw(bool value);
        /**recursively potential visible culling*/
        void cullByCamera(const Camera * camera, const Mat4 & worldTransform);
        /**precalculate the AABB(In world space) of each quad*/
        void preCalculateAABB(const Mat4 & worldTransform);
        QuadTree * _tl;
        QuadTree * _tr;
        QuadTree * _bl;
        QuadTree * _br;
        /**A flag present current quadTree node whether a terminal node,the terminal node is de facto the chunck*/
        bool _isTerminal;
        Chunk * _chunk;
        int _posX;
        int _posY;
        int _height;
        int _width;
        QuadTree * _parent;
        /**AABB's cache (in local space)*/
        AABB _localAABB;
        /**AABB's cache (in world space)*/
        AABB _worldSpaceAABB;
        Terrain * _terrain;
        /** a flag determine whether a quadTree node need draw*/
        bool _needDraw;
    };
    friend QuadTree;
    friend Chunk;
public:
    /** set light map texture */
    void setLightMap(const std::string& fileName);

    /**
     set directional light for the terrain
     @param lightDir The direction of directional light, Note that lightDir is in the terrain's local space. Most of the time terrain is placed at (0,0,0) and without rotation, so lightDir is also in the world space.
     */
    void setLightDir(const Vec3& lightDir);
    /*init function*/
    /**initialize all Properties which terrain need */
    bool initProperties();
    /**initialize heightMap data */
    bool initHeightMap(const char* heightMap);
    /**initialize alphaMap ,detailMaps textures*/
    bool initTextures();
    /**create entry*/
    static Terrain * create(TerrainData &parameter, CrackFixedType fixedType = CrackFixedType::INCREASE_LOWER);
    /**get specified position's height mapping to the terrain,use bi-linear interpolation method
     * @param x the X position
     * @param y the Z position
     * @param normal the specified position's normal vector in terrain . if this argument is NULL or nullptr,Normal calculation shall be skip.
     * @return the height value of the specified position of the terrain, if the (X,Z) position is out of the terrain bounds,it shall return 0;
     **/
    float getHeight(float x, float z, Vec3 * normal= nullptr) const;

    /**get specified position's height mapping to the terrain,use bi-linear interpolation method
     * @param pos the position (X,Z)
     * @param normal the specified position's normal vector in terrain . if this argument is NULL or nullptr,Normal calculation shall be skip.
     * @return the height value of the specified position of the terrain, if the (X,Z) position is out of the terrain bounds,it shall return 0;
     **/
    float getHeight(Vec2 pos, Vec3*Normal = nullptr) const;

    /**get the normal of the specified pistion in terrain
     * @return the normal vector of the specified position of the terrain.
     * @note the fast normal calculation may not get precise normal vector.
     **/
    Vec3 getNormal(int pixelX, int pixelY) const;
    /**get height from the raw height filed*/
    float getImageHeight(int pixelX, int pixelY) const;
    /**show the wireline instead of the surface,Debug Use only.
     * @Note only support desktop platform
     **/
    void setDrawWire(bool boolValue);
    /**
     * Set threshold distance of each LOD level,must equal or gereater than the chunk size
     * @Note when invoke initHeightMap, the LOD distance will be automatic calculated.
     */
    void setLODDistance(float lod1, float lod2, float lod3);

    /**Switch frustum Culling Flag
     * @Note frustum culling will remarkable improve your terrain rendering performance. 
     */
    void setIsEnableFrustumCull(bool boolValue);

    /** set the alpha map*/
    void setAlphaMap(cocos2d::Texture2D * newAlphaMapTexture);
    /**set the Detail Map */
    void setDetailMap(unsigned int index, DetailMap detailMap);

    // Overrides, internal use only
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
    /**
     * Ray-Terrain intersection.
     * @return the intersection point
     */
    Vec3 getIntersectionPoint(const Ray & ray) const;

   /**
    * Ray-Terrain intersection.
    * @param ray to hit the terrain
    * @param intersectionPoint hit point if hitted
    * @return true if hit, false otherwise
    */
    bool getIntersectionPoint(const Ray & ray, Vec3 & intersectionPoint) const;

    /**
     * set the MaxDetailAmount.
     */
    void setMaxDetailMapAmount(int maxValue);

    /**
     * Convert a world Space position (X,Z) to terrain space position (X,Z)
     */
    Vec2 convertToTerrainSpace(Vec2 worldSpace) const;

    /**
     * reset the heightmap data.
     */
    void resetHeightMap(const char * heightMap);

    /**
     * get the terrain's mininal height.
     */
    float getMinHeight();

    /**
     * get the terrain's maximum height.
     */
    float getMaxHeight();

    /**
     * get the terrain's AABB(in world space)
     */
    AABB getAABB();

    /**
     * set the skirt height ratio
     */
    void setSkirtHeightRatio(float ratio);

    /**
     * get the terrain's quad tree which is also the root node.
     */
    QuadTree * getQuadTree();

    void reload();
    
    /**
     * get the terrain's size
     */
    Size getTerrainSize() const { return Size(_imageWidth, _imageHeight); }
    
    /**
     * get the terrain's height data
     */
    std::vector<float> getHeightData() const;

CC_CONSTRUCTOR_ACCESS:
    Terrain();
    virtual ~Terrain();
    bool initWithTerrainData(TerrainData &parameter, CrackFixedType fixedType);
protected:
    void onDraw(const Mat4 &transform, uint32_t flags);

    /**
     * recursively set each chunk's LOD
     * @param cameraPos the camera postion in world space
     **/
    void setChunksLOD(Vec3 cameraPos);

    /**
     * load Vertices from height filed for the whole terrain.
     **/
    void loadVertices();

    /**
     * calculate Normal Line for each Vertex
     **/
    void calculateNormal();

    //override
    virtual void onEnter() override;

    /**
     * cache all unifrom loactions in GLSL.
     **/
    void cacheUniformAttribLocation();

    //IBO generate & cache
    ChunkIndices lookForIndicesLODSkrit(int selfLod, bool * result);

    ChunkIndices lookForIndicesLOD(int neighborLod[4], int selfLod, bool * result);

    ChunkIndices insertIndicesLOD(int neighborLod[4], int selfLod, GLushort * indices, int size);

    ChunkIndices insertIndicesLODSkirt(int selfLod, GLushort * indices, int size);
    
    Chunk * getChunkByIndex(int x,int y) const;

protected:
    std::vector <ChunkLODIndices> _chunkLodIndicesSet;
    std::vector<ChunkLODIndicesSkirt> _chunkLodIndicesSkirtSet;
    Mat4 _CameraMatrix;
    bool _isCameraViewChanged;
    TerrainData _terrainData;
    bool _isDrawWire;
    unsigned char * _data;
    float _lodDistance[3];
    Texture2D * _detailMapTextures[4];
    Texture2D * _alphaMap;
    Texture2D * _lightMap;
    Vec3 _lightDir;
    CustomCommand _customCommand;
    QuadTree * _quadRoot;
    Chunk * _chunkesArray[MAX_CHUNKES][MAX_CHUNKES];
    std::vector<TerrainVertexData> _vertices;
    std::vector<unsigned int> _indices;
    int _imageWidth;
    int _imageHeight;
    Size _chunkSize;
    bool _isEnableFrustumCull;
    int _maxDetailMapValue;
    cocos2d::Image * _heightMapImage;
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
    GLint _lightMapCheckLocation;
    GLint _lightMapLocation;
    GLint _detailMapSizeLocation[4];
    GLint _lightDirLocation;
    RenderState::StateBlock* _stateBlock;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    EventListenerCustom* _backToForegroundListener;
#endif
};

// end of actions group
/// @}

NS_CC_END
#endif
