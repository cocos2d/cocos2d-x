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
#include <vector>
NS_CC_BEGIN
    /*
    *the maximum amount of the chunkes
    **/
#define MAX_CHUNKES 256

    /*
    *Terrain
    *use to render outdoor or large scene via heightMap
    **/
class CC_DLL Terrain :public Node{
public:

    /*
    *DetailMap
    *this struct maintain a detail map data ,including source file ,detail size.
    *the DetailMap can use for terrain splatting
    **/
    struct CC_DLL DetailMap{
        /*Constructors*/
        DetailMap();
        DetailMap(const char * detailMapSrc , float size = 35);
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
        TerrainData(const char* heightMapsrc ,const char * textureSrc,const Size & chunksize = Size(32,32),float mapHeight = 2,float mapScale = 0.1);
        TerrainData(const char* heightMapsrc ,const char * alphamap,const DetailMap& detail1,const DetailMap& detail2,const DetailMap& detail3,const DetailMap& detail4,const Size & chunksize = Size(32,32),float mapHeight = 2,float mapScale = 0.1);
        TerrainData(const char* heightMapsrc ,const char * alphamap,const DetailMap& detail1,const DetailMap& detail2,const DetailMap& detail3,const Size & chunksize = Size(32,32),float mapHeight = 2,float mapScale = 0.1);
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

    /*
    *terrain vertices internal data format
    **/
    struct TerrainVertexData
    {
        /*constructor*/
        TerrainVertexData(){};
        TerrainVertexData(Vec3 v1 ,Tex2F v2)
        {
            position = v1;
            texcoord = v2;
        };
        /*the vertex's attributes*/
        cocos2d::Vec3 position;
        cocos2d::Tex2F texcoord;
        cocos2d::Vec3 normal;
    };

    /*
    *the terminal node of quad, use to subdivision terrain mesh and LOD
    **/
    struct Chunk
    {
        /*Constructor*/
        Chunk();
        /*vertices*/
        std::vector<TerrainVertexData> vertices;
        /*LOD indices*/
        struct LOD{
            std::vector<GLushort> indices;
        };
        GLuint vbo[2];
        /*we now have four levels of detail*/
        LOD _lod[4];
        /*AABB in local space*/
        AABB _aabb;
        /*setup Chunk data*/
        void generate(int map_width,int map_height,int m,int n,const unsigned char * data);
        /*calculateAABB*/
        void calculateAABB();
        /*internal use draw function*/
        void bindAndDraw();
        /*finish opengl setup*/
        void finish();
        /*use linear-sample vertices for LOD mesh*/
        void updateVerticesForLOD();
        /*calculate the average slope of the chunk*/
        void calculateSlope();
        /*updateIndices for every frame*/
        void updateIndices();

        /*current LOD of the chunk*/
        int _currentLod;
        /*the left,right,front,back neighbors*/
        Chunk * left;
        Chunk * right;
        Chunk * front;
        Chunk * back;

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
        QuadTree(int x,int y,int width,int height,Terrain * terrain);
        void draw();
        void resetNeedDraw(bool value);
        void cullByCamera(const Camera * camera,const Mat4 & worldTransform);
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
        bool _needDraw;
    };

    friend QuadTree;
    friend Chunk;
public:
    /*init function*/
    bool init();
    void initHeightMap(const char* heightMap);
    /*create entry*/
    static Terrain * create(TerrainData &parameter);
    /*get specified position's height mapping to the terrain*/
    float getHeight(float x, float y, float z);
    float getHeight(Vec3 pos);  

    /*get height from the raw height map*/
    float getImageHeight(int pixel_x,int pixel_y);
    /*Debug Use only, show the wireline instead of the surface. only support desktop platform*/
    void setDrawWire(bool bool_value);
    /*Set threshold distance of each LOD level,must equal or gereater than the chunk size*/
    void setLODDistance(float lod_1,float lod_2,float lod_3);
    /*Switch frustumCulling Flag*/
    void setIsEnableFrustumCull(bool bool_value);
    // Overrides, internal use only
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
private:
    Terrain();
    virtual ~Terrain();
    void onDraw(const Mat4 &transform, uint32_t flags);
    //set each chunk's LOD
    void setChunksLOD(Vec3 cameraPos);
    //load vertices for whole height map
    void loadVertices();
    //calculate Normal Line for each Vertex
    void calculateNormal();
private:
    TerrainData _terrainData;
    bool _isDrawWire;
    unsigned char * _data;
    float _lodDistance[3];
    std::vector<Texture2D *>textures;
    Texture2D * _alphaMap;
    CustomCommand _customCommand;
    GLuint vbo[2];
    QuadTree * quad;
    int detailSize[4];
    Chunk * _chunkesArray[256][256];
    std::vector<TerrainVertexData> vertices;
    std::vector<GLushort > indices;
    int imageWidth;
    int imageHeight;
    Size _chunkSize;
    bool _isEnableFrustumCull;
    cocos2d::Image * _heightMapImage;
};
NS_CC_END
#endif
