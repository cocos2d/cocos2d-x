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

#include "2d/CCNode.h"
#include "renderer/CCTexture2D.h"
#include "renderer/CCCustomCommand.h"
#include "3d/CCAABB.h"
#include "2d/CCCamera.h"
#include "3d/CCRay.h"
#include <vector>
#include "vld.h"
NS_CC_BEGIN

/**
 * @addtogroup _3d
 * @{
 */

    /*
    * the maximum amount of the chunkes
    **/
#define MAX_CHUNKES 256

    /*
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
class CC_DLL Terrain :public Node
{
public:

    enum class CrackFixedType{
        SKIRT,
        INCREASE_LOWER,
    };

    /*
    *DetailMap
    *this struct maintain a detail map data ,including source file ,detail size.
    *the DetailMap can use for terrain splatting
    **/
    struct CC_DLL DetailMap{
        /*Constructors*/
        DetailMap();
        DetailMap(const char * detailMapSrc, float size = 35);
        /*detail Image source file path*/
        std::string detailMapSrc;
        /*detailMapSize determine how many tiles that Terrain represent*/
        float detailMapSize;
    };

    /*
    *TerrainData
    *This TerrainData struct warp all parameter that Terrain need to create
    */
    struct CC_DLL TerrainData
    {
        /*Constructors*/
        TerrainData();
        TerrainData(const char* heightMapsrc, const char * textureSrc, const Size & chunksize = Size(32,32), float mapHeight = 2, float mapScale = 0.1);
        TerrainData(const char* heightMapsrc, const char * alphamap, const DetailMap& detail1,const DetailMap& detail2, const DetailMap& detail3, const DetailMap& detail4, const Size & chunksize = Size(32,32), float mapHeight = 2, float mapScale = 0.1);
        TerrainData(const char* heightMapsrc, const char * alphamap, const DetailMap& detail1,const DetailMap& detail2, const DetailMap& detail3, const Size & chunksize = Size(32,32), float mapHeight = 2, float mapScale = 0.1);
        /*
        *deterimine the chunk size,chunk is the minimal subdivision of the Terrain
        */
        Size chunkSize;
        /*height Map source path*/
        std::string heightMapSrc;
        /*the source path of the alpha map*/
        char* alphaMapSrc;
        /*detail maps*/
        DetailMap detailMaps[4];
        /*terrain Maximum height*/
        float mapHeight;
        /*terrain scale factor*/
        float mapScale;
        int _detailMapAmount;
    };
private:

    struct ChunkIndices
    {
        GLuint indices;
        unsigned short size;
    };

    struct ChunkLODIndices
    {
        int relativeLod[5];
        ChunkIndices _chunkIndices;
    };


    struct ChunkLODIndicesSkirt
    {
        int selfLod;
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
            position = v1;
            texcoord = v2;
        };
        /*the vertex's attributes*/
        cocos2d::Vec3 position;
        cocos2d::Tex2F texcoord;
        cocos2d::Vec3 normal;
    };

    struct QuadTree;
    /*
    *the terminal node of quad, use to subdivision terrain mesh and LOD
    **/
    struct Chunk
    {
        /*Constructor*/
        Chunk();
        ~Chunk();
        /*vertices*/
        std::vector<TerrainVertexData> vertices;
        /*LOD indices*/
        struct LOD{
            std::vector<GLushort> indices;
        };
        GLuint vbo[2];
        ChunkIndices _chunkIndices; 
        /*we now have four levels of detail*/
        LOD _lod[4];
        /*AABB in local space*/
        AABB _aabb;
        /*setup Chunk data*/
        void generate(int map_width, int map_height, int m, int n, const unsigned char * data);
        /*calculateAABB*/
        void calculateAABB();
        /*internal use draw function*/
        void bindAndDraw();
        /*finish opengl setup*/
        void finish();
        /*use linear-sample vertices for LOD mesh*/
        void updateVerticesForLOD();
        /*updateIndices for every frame*/
        void updateIndicesLOD();

        void updateIndicesLODSkirt();

        void calculateSlope();
        /*current LOD of the chunk*/
        int _currentLod;

        int _oldLod;

        int _neighborOldLOD[4];
        /*the left,right,front,back neighbors*/
        Chunk * left;
        Chunk * right;
        Chunk * front;
        Chunk * back;

        QuadTree * _parent;

        //the position
        int pos_x;
        int pos_y;
        /*parent terrain*/
        Terrain * _terrain;
        /*chunk size*/
        Size _size;
        /*chunk's estimated slope*/
        float slope;
        std::vector<TerrainVertexData> vertices_tmp;
    };

    /*
    *QuadTree
    *use to frustum culling and set LOD
    **/
    struct QuadTree
    {
        QuadTree(int x, int y, int width, int height, Terrain * terrain);
        ~QuadTree();
        void draw();
        void resetNeedDraw(bool value);
        void cullByCamera(const Camera * camera, const Mat4 & worldTransform);
        void preCalculateAABB(const Mat4 & worldTransform);
        QuadTree * tl;
        QuadTree * tr;
        QuadTree * bl;
        QuadTree * br;
        bool _isTerminal;
        Chunk * _chunk;
        int pos_x;
        int pos_y;
        int height;
        int width;
        QuadTree * parent;
        AABB _aabb;
        AABB _worldSpaceAABB;
        Terrain * _terrain;
        bool _needDraw;
    };
    friend QuadTree;
    friend Chunk;
public:
    /*init function*/
    bool init();
    void initHeightMap(const char* heightMap);
    /*create entry*/
    static Terrain * create(TerrainData &parameter, CrackFixedType fixedType = CrackFixedType::INCREASE_LOWER);
    /*get specified position's height mapping to the terrain*/
    float getHeight(float x, float z, Vec3 * normal= nullptr);
    float getHeight(Vec2 pos, Vec3*Normal = nullptr);
    Vec3 getNormal(int pixel_x, int pixel_y);
    /*get height from the raw height map*/
    float getImageHeight(int pixel_x, int pixel_y);
    /*Debug Use only, show the wireline instead of the surface. only support desktop platform*/
    void setDrawWire(bool bool_value);
    /*Set threshold distance of each LOD level,must equal or gereater than the chunk size*/
    void setLODDistance(float lod_1, float lod_2, float lod_3);
    /*Switch frustumCulling Flag*/
    void setIsEnableFrustumCull(bool bool_value);

    /** set the alpha map*/
    void setAlphaMap(cocos2d::Texture2D * newAlphaMapTexture);
    /**set the Detail Map */
    void setDetailMap(unsigned int index, DetailMap detailMap);

    // Overrides, internal use only
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
    //Ray-Terrain intersection.
    Vec3 getIntersectionPoint(const Ray & ray);
    void setMaxDetailMapAmount(int max_value);

    //conver to Terrain space.
    Vec2 convertToTerrainSpace(Vec2 worldSpace);

    //reset the heightmap data
    void resetHeightMap(const char * heightMap);

    // get the terrain's mininal height.
    float getMinHeight();

    // get the terrain's maximum height.
    float getMaxHeight();

    //get terrain's AABB
    AABB getAABB();

    //get the terrain's quad tree which is also the root node
    QuadTree * getQuadTree();

    ChunkIndices lookForIndicesLODSkrit(int selfLod, bool * result);
    ChunkIndices lookForIndicesLOD(int neighborLod[4], int selfLod, bool * result);

    ChunkIndices insertIndicesLOD(int neighborLod[4], int selfLod, GLushort * indices, int size);

    ChunkIndices insertIndicesLODSkirt(int selfLod, GLushort * indices, int size);

    void setSkirtHeightRatio(float ratio);

protected:
    
    Terrain();
    virtual ~Terrain();
    void onDraw(const Mat4 &transform, uint32_t flags);
    //set each chunk's LOD
    void setChunksLOD(Vec3 cameraPos);
    //load vertices for whole height map
    void loadVertices();
    //calculate Normal Line for each Vertex
    void calculateNormal();
    //override
    virtual void onEnter() override;

    void cacheUniformLocation();
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
    CustomCommand _customCommand;
    GLuint vbo[2];
    QuadTree * _quadRoot;
    Chunk * _chunkesArray[MAX_CHUNKES][MAX_CHUNKES];
    std::vector<TerrainVertexData> vertices;
    std::vector<GLushort> indices;
    int imageWidth;
    int imageHeight;
    Size _chunkSize;
    bool _isEnableFrustumCull;
    int _maxDetailMapValue;
    cocos2d::Image * _heightMapImage;
    Mat4 _oldCameraModelMatrix;
    Mat4 _terrainModelMatrix;
    GLuint _normalLocation;
    float m_maxHeight;
    float m_minHeight;
    CrackFixedType _crackFixedType;
    float _skirtRatio;
    int _skirtVerticesOffset[4];
    GLint _detailMapLocation[4];
    GLint _alphaMapLocation;
    GLint _alphaIsHasAlphaMapLocation;
    GLint _detailMapSizeLocation[4];
};

// end of actions group
/// @}

NS_CC_END
#endif
