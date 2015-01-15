#ifndef CC_TERRAIN_H
#define CC_TERRAIN_H
#include "2d/CCNode.h"
#include "renderer/CCTexture2D.h"
#include "renderer/CCCustomCommand.h"
#include "3d/CCAABB.h"
#include "2d/CCCamera.h"
#include <vector>
NS_CC_BEGIN

#define MAX_CHUNKES 256

/*
 *Terrain 
 *
 **/
class CC_DLL Terrain :public Node{
public:
     struct CC_DLL DetailMap{
        DetailMap();
        DetailMap(const char * detailMapSrc , float size = 35);
        std::string detailMapSrc;
        float detailMapSize;
    };
     struct CC_DLL TerrainData
    {
        TerrainData();
        TerrainData(const char* heightMapsrc ,const char * textureSrc,const Size & chunksize = Size(32,32),float mapHeight = 2,float mapScale = 0.1);
        TerrainData(const char* heightMapsrc ,const char * alphamap,const DetailMap& detail1,const DetailMap& detail2,const DetailMap& detail3,const DetailMap& detail4,const Size & chunksize = Size(32,32),float mapHeight = 2,float mapScale = 0.1);
        Size chunkSize;
        std::string heightMapSrc;
        char* alphaMapSrc;
        DetailMap detailMaps[4];
        float mapHeight;
        float mapScale;
    };
private:
    struct TerrainVertexData
    {
        TerrainVertexData(){};
        TerrainVertexData(Vec3 v1 ,Tex2F v2)
        {
            position = v1;
            texcoord = v2;
        };
        cocos2d::Vec3 position;
        cocos2d::Tex2F texcoord;
        cocos2d::Vec3 normal;
    };
    struct Chunk
    {
        Chunk();
        std::vector<TerrainVertexData> vertices;
        
        struct LOD{
        std::vector<GLushort > indices;
        };
        GLuint vbo[2];
        LOD _lod[4];
        AABB _aabb;
        void generate(int map_width,int map_height,int m,int n,const unsigned char * data);
        void calculateAABB();
        void bindAndDraw();
        void finish();
        void updateVerticesForLOD();
        void calculateSlope();
        int _currentLod;
        void updateIndices();
        Chunk * left;
        Chunk * right;
        Chunk * front;
        Chunk * back;
        int pos_x;
        int pos_y;
        Terrain * _terrain;
        Size _size;
        std::vector<TerrainVertexData> vertices_tmp;
        float slope;
    };
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
    bool init();
    void initHeightMap(const char* heightMap);
    static Terrain * create(TerrainData &parameter);
    // Overrides, internal use only
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
    float getHeight(float x,float y, float z);
    float getHeight(Vec3 pos);  
    float getImageHeight(int pixel_x,int pixel_y);
    void setDrawWire(bool bool_value);
    void setLODDistance(float lod_1,float lod_2,float lod_3);
    void setIsEnableFrustumCull(bool bool_value);
private:
    Terrain();
    void onDraw(const Mat4 &transform, uint32_t flags);
    void setChunksLOD(Vec3 cameraPos);
    void loadVertices();
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
};
NS_CC_END
#endif
