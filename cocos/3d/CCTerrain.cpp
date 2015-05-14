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

#include "CCTerrain.h"

USING_NS_CC;
#include <stdlib.h>
#include <CCImage.h>
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCGLProgramStateCache.h"
#include "renderer/ccGLStateCache.h"
#include "base/CCDirector.h"
#include "2d/CCCamera.h"

#include "base/CCEventType.h"

NS_CC_BEGIN

// check a number is power of two.
static bool isPOT(int number)
{
    bool flag = false;  
    if((number>0)&&(number&(number-1))==0)  
        flag = true;  
    return flag;  
}

Terrain * Terrain::create(TerrainData &parameter, CrackFixedType fixedType)
{
    Terrain * terrain = new (std::nothrow)Terrain();
    terrain->setSkirtHeightRatio(parameter._skirtHeightRatio);
    terrain->_terrainData = parameter;
    terrain->_crackFixedType = fixedType;
    terrain->_isCameraViewChanged = true;
    //chunksize
    terrain->_chunkSize = parameter._chunkSize;
    bool initResult =true;

    //init heightmap
    initResult &= terrain->initHeightMap(parameter._heightMapSrc.c_str());
    //init textures alpha map,detail Maps
    initResult &= terrain->initTextures();
    initResult &= terrain->initProperties();
    terrain->autorelease();
    if(!initResult)
    {
        CC_SAFE_DELETE(terrain);
    }    
    return terrain;
}

bool Terrain::initProperties()
{
    auto shader = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_TERRAIN);
    auto state = GLProgramState::create(shader);

    setGLProgramState(state);
    setDrawWire(false);
    setIsEnableFrustumCull(true);
    setAnchorPoint(Vec2(0,0));
    return true;
}

void Terrain::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    _customCommand.func = CC_CALLBACK_0(Terrain::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void Terrain::onDraw(const Mat4 &transform, uint32_t flags)
{
    auto glProgram = getGLProgram();
    glProgram->use();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    if(_isDrawWire)
    {
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    }else
    {
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    }
#endif
    GLboolean blendCheck = glIsEnabled(GL_BLEND);
    if(blendCheck)
    {
        glDisable(GL_BLEND);
    }
    GL::enableVertexAttribs(1<<_positionLocation | 1 << _texcordLocation | 1<<_normalLocation);
    glProgram->setUniformsForBuiltins(transform);
    GLboolean depthMaskCheck;
    glGetBooleanv(GL_DEPTH_WRITEMASK, &depthMaskCheck);
    if(!depthMaskCheck)
    {
        glDepthMask(GL_TRUE);
    }
    GLboolean CullFaceCheck =glIsEnabled(GL_CULL_FACE);
    if(!CullFaceCheck)
    {
        glEnable(GL_CULL_FACE);
    }
    GLboolean depthTestCheck;
    depthTestCheck = glIsEnabled(GL_DEPTH_TEST);
    if(!depthTestCheck)
    {
        glEnable(GL_DEPTH_TEST);
    }
    if(!_alphaMap)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,_detailMapTextures[0]->getName());
        glUniform1i(_detailMapLocation[0],0);
        glUniform1i(_alphaIsHasAlphaMapLocation,0);
    }else
    {
        for(int i =0;i<_maxDetailMapValue;i++)
        {
            glActiveTexture(GL_TEXTURE0+i);
            glBindTexture(GL_TEXTURE_2D,_detailMapTextures[i]->getName());
            glUniform1i(_detailMapLocation[i],i);

            glUniform1f(_detailMapSizeLocation[i],_terrainData._detailMaps[i]._detailMapSize);
        }

        glUniform1i(_alphaIsHasAlphaMapLocation,1);

        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D,_alphaMap->getName());
        glUniform1i(_alphaMapLocation,4);
    }

    auto camera = Camera::getVisitingCamera();

    if(memcmp(&_CameraMatrix,&camera->getViewMatrix(),sizeof(Mat4))!=0)
    {
        _isCameraViewChanged = true;
        _CameraMatrix = camera->getViewMatrix();
    }


    if(_isCameraViewChanged )
    {
        auto camPos = camera->getPosition3D();
        //set lod
        setChunksLOD(camPos);
    }

    if(_isCameraViewChanged )
    {
        _quadRoot->resetNeedDraw(true);//reset it 
        //camera frustum culling
        _quadRoot->cullByCamera(camera,_terrainModelMatrix);
    }
    _quadRoot->draw();
    if(_isCameraViewChanged)
    {
        _isCameraViewChanged = false;
    }
    glActiveTexture(GL_TEXTURE0);
    if(depthTestCheck)
    {
    }else
    {
        glDisable(GL_DEPTH_TEST);
    }
    if(depthMaskCheck)
    {
    }else
    {
        glDepthMask(GL_FALSE);
    }
    if(CullFaceCheck)
    {
    }else
    {
        glEnable(GL_CULL_FACE);
    }
    if(blendCheck)
    {
        glEnable(GL_BLEND);
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    if(_isDrawWire)//reset state.
    {
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    }
#endif
}

bool Terrain::initHeightMap(const char * heightMap)
{
    _heightMapImage = new Image();
    _heightMapImage->initWithImageFile(heightMap);
    _data = _heightMapImage->getData();
    _imageWidth =_heightMapImage->getWidth();
    _imageHeight =_heightMapImage->getHeight();

    //only the image size  is the Powers Of Two(POT) or POT+1
    if((isPOT(_imageWidth) &&isPOT(_imageHeight)) || (isPOT(_imageWidth-1) &&isPOT(_imageHeight -1)))
    {
        int chunk_amount_y = _imageHeight/_chunkSize.height;
        int chunk_amount_x = _imageWidth/_chunkSize.width;
        loadVertices();
        calculateNormal();
        memset(_chunkesArray, 0, sizeof(_chunkesArray));

        for(int m =0;m<chunk_amount_y;m++)
        {
            for(int n =0; n<chunk_amount_x;n++)
            {
                _chunkesArray[m][n] = new Chunk();
                _chunkesArray[m][n]->_terrain = this;
                _chunkesArray[m][n]->_size = _chunkSize;
                _chunkesArray[m][n]->generate(_imageWidth,_imageHeight,m,n,_data);
            }
        }

        //calculate the neighbor
        for(int m =0;m<chunk_amount_y;m++)
        {
            for(int n =0; n<chunk_amount_x;n++)
            {
                if(n-1>=0) _chunkesArray[m][n]->_left = _chunkesArray[m][n-1];
                if(n+1<chunk_amount_x) _chunkesArray[m][n]->_right = _chunkesArray[m][n+1];
                if(m-1>=0) _chunkesArray[m][n]->_back = _chunkesArray[m-1][n];
                if(m+1<chunk_amount_y) _chunkesArray[m][n]->_front = _chunkesArray[m+1][n];
            }
        }
        _quadRoot = new QuadTree(0,0,_imageWidth,_imageHeight,this);
        setLODDistance(_chunkSize.width,2*_chunkSize.width,3*_chunkSize.width);
        return true;
    }else
    {
        CCLOG("warning: the height map size is not POT or POT + 1");
        return false;
    }
}

Terrain::Terrain()
{
    _alphaMap = nullptr;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    _customCommand.setTransparent(false);
    _customCommand.set3D(true);
    auto _backToForegroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED,
        [this](EventCustom*)
    {
        reload();
    }
    );
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundListener, 1);
#endif
}

void Terrain::setChunksLOD(Vec3 cameraPos)
{
    int chunk_amount_y = _imageHeight/_chunkSize.height;
    int chunk_amount_x = _imageWidth/_chunkSize.width;
    for(int m=0;m<chunk_amount_y;m++)
        for(int n =0;n<chunk_amount_x;n++)
        {
            AABB aabb = _chunkesArray[m][n]->_parent->_worldSpaceAABB;
            auto center = aabb.getCenter();
            float dist = Vec3(center.x,0,center.z).distance(Vec3(cameraPos.x,0,cameraPos.z));
            _chunkesArray[m][n]->_currentLod = 3;
            for(int i =0;i<3;i++)
            {
                if(dist<=_lodDistance[i])
                {
                    _chunkesArray[m][n]->_currentLod = i;
                    break;
                }
            }
        }
}

float Terrain::getHeight(float x, float z, Vec3 * normal)
{
    Vec2 pos(x,z);

    //top-left
    Vec2 tl(-1*_terrainData._mapScale*_imageWidth/2,-1*_terrainData._mapScale*_imageHeight/2);
    auto result  = getNodeToWorldTransform()*Vec4(tl.x,0.0f,tl.y,1.0f);
    tl.set(result.x, result.z);

    Vec2 to_tl = pos - tl;

    //real size
    Vec2 size(_imageWidth*_terrainData._mapScale,_imageHeight*_terrainData._mapScale);
    result = getNodeToWorldTransform()*Vec4(size.x,0.0f,size.y,0.0f);
    size.set(result.x, result.z);

    float width_ratio = to_tl.x/size.x;
    float height_ratio = to_tl.y/size.y;

    float image_x = width_ratio * _imageWidth;
    float image_y = height_ratio * _imageHeight;
    float u =image_x - (int)image_x;
    float v =image_y - (int)image_y;
    float i = (int)image_x;
    float j = (int)image_y;


    if(image_x>=_imageWidth-1 || image_y >=_imageHeight-1 || image_x<0 || image_y<0)
    {
        return 0;
    }else
    {
        float a = getImageHeight(i,j)*getScaleY();
        float b = getImageHeight(i,j+1)*getScaleY();
        float c = getImageHeight(i+1,j)*getScaleY();
        float d = getImageHeight(i+1,j+1)*getScaleY();
        if(normal)
        {
            normal->x = c - b;
            normal->y = 2;
            normal->z = d - a;
            normal->normalize();
            //(*normal) = (1-u)*(1-v)*getNormal(i,j)+ (1-u)*v*getNormal(i,j+1) + u*(1-v)*getNormal(i+1,j)+ u*v*getNormal(i+1,j+1);
        }
        float reuslt =  (1-u)*(1-v)*getImageHeight(i,j)*getScaleY() + (1-u)*v*getImageHeight(i,j+1)*getScaleY() + u*(1-v)*getImageHeight(i+1,j)*getScaleY() + u*v*getImageHeight(i+1,j+1)*getScaleY();
        return reuslt;
    }
}

float Terrain::getHeight(Vec2 pos, Vec3*Normal)
{
    return getHeight(pos.x,pos.y,Normal);
}

float Terrain::getImageHeight(int pixel_x,int pixel_y)
{
    int byte_stride =1;
    switch (_heightMapImage->getRenderFormat())
    {
    case Texture2D::PixelFormat::BGRA8888:
        byte_stride = 4;
        break;
    case  Texture2D::PixelFormat::RGB888:
        byte_stride =3;
        break;
    case Texture2D::PixelFormat::I8:
        byte_stride =1;
        break;
    default:
        break;
    }
    return _data[(pixel_y*_imageWidth+pixel_x)*byte_stride]*1.0/255*_terrainData._mapHeight -0.5*_terrainData._mapHeight;
}

void Terrain::loadVertices()
{
    _maxHeight = -99999;
    _minHeight = 99999;
    for(int i =0;i<_imageHeight;i++)
    {
        for(int j =0;j<_imageWidth;j++)
        {
            float height = getImageHeight(j,i);
            TerrainVertexData v;
            v._position = Vec3(j*_terrainData._mapScale- _imageWidth/2*_terrainData._mapScale, //x
                height, //y
                i*_terrainData._mapScale - _imageHeight/2*_terrainData._mapScale);//z
            v._texcoord = Tex2F(j*1.0/_imageWidth,i*1.0/_imageHeight);
            _vertices.push_back (v);

            //update the min & max height;
            if(height>_maxHeight) _maxHeight = height;
            if(height<_minHeight) _minHeight = height;
        }
    }
}

void Terrain::calculateNormal()
{
    _indices.clear();
    //we generate whole terrain indices(global indices) for correct normal calculate
    for(int i =0;i<_imageHeight-1;i+=1)
    {
        for(int j = 0;j<_imageWidth-1;j+=1)
        { 

            int nLocIndex = i * _imageWidth + j;
            _indices.push_back (nLocIndex);
            _indices.push_back (nLocIndex + _imageWidth);
            _indices.push_back (nLocIndex + 1);

            _indices.push_back (nLocIndex + 1);
            _indices.push_back (nLocIndex + _imageWidth);
            _indices.push_back (nLocIndex + _imageWidth+1);
        }
    }
    for (unsigned int i = 0 ; i < _indices.size() ; i += 3) {
        unsigned int Index0 = _indices[i];
        unsigned int Index1 = _indices[i + 1];
        unsigned int Index2 = _indices[i + 2];
        Vec3 v1 = _vertices[Index1]._position - _vertices[Index0]._position;
        Vec3 v2 = _vertices[Index2]._position - _vertices[Index0]._position;
        Vec3 Normal;
        Vec3::cross(v1,v2,&Normal);
        Normal.normalize();
        _vertices[Index0]._normal += Normal;
        _vertices[Index1]._normal += Normal;
        _vertices[Index2]._normal += Normal;
    }

    for (unsigned int i = 0 ; i < _vertices.size() ; i++) {
        _vertices[i]._normal.normalize();
    }
    //global indices no need at all
    _indices.clear();
}

void Terrain::setDrawWire(bool bool_value)
{
    _isDrawWire = bool_value;
}

void Terrain::setLODDistance(float lod_1, float lod_2, float lod_3)
{
    _lodDistance[0] = lod_1;
    _lodDistance[1] = lod_2;
    _lodDistance[2] = lod_3;
}

void Terrain::setIsEnableFrustumCull(bool bool_value)
{
    _isEnableFrustumCull = bool_value;
}

Terrain::~Terrain()
{
    _alphaMap->release();
    _heightMapImage->release();
    delete _quadRoot;
    for(int i=0;i<4;i++)
    {
        if(_detailMapTextures[i])
        {
            _detailMapTextures[i]->release();
        }
    }
    for(int i = 0;i<MAX_CHUNKES;i++)
    {
        for(int j = 0;j<MAX_CHUNKES;j++)
        {
            if(_chunkesArray[i][j])
            {
                delete _chunkesArray[i][j];
            }
        }
    }

    for(int i =0;i<_chunkLodIndicesSet.size();i++)
    {
        glDeleteBuffers(1,&(_chunkLodIndicesSet[i]._chunkIndices._indices));
    }

    for(int i =0;i<_chunkLodIndicesSkirtSet.size();i++)
    {
        glDeleteBuffers(1,&(_chunkLodIndicesSkirtSet[i]._chunkIndices._indices));
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundListener);
#endif
}

cocos2d::Vec3 Terrain::getNormal(int pixel_x, int pixel_y)
{
    float a = getImageHeight(pixel_x,pixel_y)*getScaleY();
    float b = getImageHeight(pixel_x,pixel_y+1)*getScaleY();
    float c = getImageHeight(pixel_x+1,pixel_y)*getScaleY();
    float d = getImageHeight(pixel_x+1,pixel_y+1)*getScaleY();
    Vec3 normal;
    normal.x = c - b;
    normal.y = 2;
    normal.z = d - a;
    normal.normalize();
    return normal;
}

cocos2d::Vec3 Terrain::getIntersectionPoint(const Ray & ray)
{
    Vec3 dir = ray._direction;
    dir.normalize();
    Vec3 rayStep = _terrainData._chunkSize.width*0.25*dir;
    Vec3 rayPos =  ray._origin;
    Vec3 rayStartPosition = ray._origin;
    Vec3 lastRayPosition =rayPos;
    rayPos += rayStep; 
    // Linear search - Loop until find a point inside and outside the terrain Vector3 
    float height = getHeight(rayPos.x,rayPos.z); 

    while (rayPos.y > height)
    {
        lastRayPosition = rayPos; 
        rayPos += rayStep; 
        height = getHeight(rayPos.x,rayPos.z); 
    } 

    Vec3 startPosition = lastRayPosition;
    Vec3 endPosition = rayPos;

    for (int i= 0; i< 32; i++) 
    { 
        // Binary search pass 
        Vec3 middlePoint = (startPosition + endPosition) * 0.5f;
        if (middlePoint.y < height) 
            endPosition = middlePoint; 
        else 
            startPosition = middlePoint;
    } 
    Vec3 collisionPoint = (startPosition + endPosition) * 0.5f; 
    return collisionPoint;
}

void Terrain::setMaxDetailMapAmount(int max_value)
{
    _maxDetailMapValue = max_value;
}

cocos2d::Vec2 Terrain::convertToTerrainSpace(Vec2 worldSpaceXZ)
{
    Vec2 pos(worldSpaceXZ.x,worldSpaceXZ.y);

    //top-left
    Vec2 tl(-1*_terrainData._mapScale*_imageWidth/2,-1*_terrainData._mapScale*_imageHeight/2);
    auto result  = getNodeToWorldTransform()*Vec4(tl.x,0.0f,tl.y,1.0f);
    tl.set(result.x, result.z);

    Vec2 to_tl = pos - tl;

    //real size
    Vec2 size(_imageWidth*_terrainData._mapScale,_imageHeight*_terrainData._mapScale);
    result = getNodeToWorldTransform()*Vec4(size.x,0.0f,size.y,0.0f);
    size.set(result.x, result.z);

    float width_ratio = to_tl.x/size.x;
    float height_ratio = to_tl.y/size.y;

    float image_x = width_ratio * _imageWidth;
    float image_y = height_ratio * _imageHeight;
    return Vec2(image_x,image_y);
}

void Terrain::resetHeightMap(const char * heightMap)
{
    _heightMapImage->release();
    _vertices.clear();
    free(_data);
    for(int i = 0;i<MAX_CHUNKES;i++)
    {
        for(int j = 0;j<MAX_CHUNKES;j++)
        {
            if(_chunkesArray[i][j])
            {
                delete _chunkesArray[i][j];
            }
        }
    }
    delete _quadRoot;
    initHeightMap(heightMap);
}

float Terrain::getMinHeight()
{
    return _minHeight;
}

float Terrain::getMaxHeight()
{
    return _maxHeight;
}

cocos2d::AABB Terrain::getAABB()
{
    return _quadRoot->_worldSpaceAABB;
}

Terrain::QuadTree * Terrain::getQuadTree()
{
    return _quadRoot;
}


std::vector<float> Terrain::getHeightData() const
{
    std::vector<float> data;
    data.resize(_imageWidth * _imageHeight);
    for (int i = 0; i < _imageHeight; i++) {
        for (int j = 0; j < _imageWidth; j++) {
            int idx = i * _imageWidth + j;
            data[idx] = (_vertices[idx]._position.y);
        }
    }
    return data;
}

void Terrain::setAlphaMap(cocos2d::Texture2D * newAlphaMapTexture)
{
    _alphaMap->release();
    _alphaMap = newAlphaMapTexture;
}

void Terrain::setDetailMap(unsigned int index, DetailMap detailMap)
{
    if(index>4)
    {
        CCLOG("invalid DetailMap index %d\n",index);
    }
    _terrainData._detailMaps[index] = detailMap;
    if(_detailMapTextures[index])
    {

        _detailMapTextures[index]->release();
    }
    _detailMapTextures[index] = new (std::nothrow)Texture2D();
    auto textImage = new (std::nothrow)Image();
    textImage->initWithImageFile(detailMap._detailMapSrc);
    _detailMapTextures[index]->initWithImage(textImage);
    delete textImage;
}

Terrain::ChunkIndices Terrain::lookForIndicesLOD(int neighborLod[4], int selfLod, bool * result)
{
    (* result) =false;
    ChunkIndices tmp;
    tmp._indices = 0;
    tmp._size = 0;
    if(_chunkLodIndicesSet.empty())
    {
        (* result) =false;
        return tmp;
    }else
    {
        int test[5];
        memcpy(test,neighborLod,sizeof(int [4]));
        test[4] = selfLod;
        for(int i =0;i<_chunkLodIndicesSet.size();i++)
        {
            if(memcmp(test,_chunkLodIndicesSet[i]._relativeLod,sizeof(test))==0)
            {
                (*result) = true;
                return _chunkLodIndicesSet[i]._chunkIndices;
            }
        }
    }
    (* result) =false;
    return tmp;
}

Terrain::ChunkIndices Terrain::insertIndicesLOD(int neighborLod[4], int selfLod, GLushort * indices,int size)
{
    ChunkLODIndices lodIndices;
    memcpy(lodIndices._relativeLod,neighborLod,sizeof(int [4]));
    lodIndices._relativeLod[4] = selfLod;
    lodIndices._chunkIndices._size = size;
    glGenBuffers(1,&(lodIndices._chunkIndices._indices));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lodIndices._chunkIndices._indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLushort)*size,indices,GL_STATIC_DRAW);
    this->_chunkLodIndicesSet.push_back(lodIndices);
    return lodIndices._chunkIndices;
}

Terrain::ChunkIndices Terrain::lookForIndicesLODSkrit(int selfLod, bool * result)
{
    ChunkIndices badResult;
    badResult._indices = 0;
    badResult._size = 0;
    if(this->_chunkLodIndicesSkirtSet.empty())
    {
    (*result) = false;
    return badResult;
    }

    for(int i =0;i<_chunkLodIndicesSkirtSet.size();i++)
    {
        if(_chunkLodIndicesSkirtSet[i]._selfLod == selfLod)
        {
            (*result) = true;
            return _chunkLodIndicesSkirtSet[i]._chunkIndices;
        }
    }
    (*result) = false;
    return badResult;
}

Terrain::ChunkIndices Terrain::insertIndicesLODSkirt(int selfLod, GLushort * indices, int size)
{
    ChunkLODIndicesSkirt skirtIndices;
    skirtIndices._selfLod = selfLod;
    skirtIndices._chunkIndices._size = size;
    glGenBuffers(1,&(skirtIndices._chunkIndices._indices));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skirtIndices._chunkIndices._indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLushort)*size,indices,GL_STATIC_DRAW);
    this->_chunkLodIndicesSkirtSet.push_back(skirtIndices);
    return skirtIndices._chunkIndices;
}

void Terrain::setSkirtHeightRatio(float ratio)
{
    _skirtRatio = ratio;
}

void Terrain::onEnter()
{
    Node::onEnter();
    _terrainModelMatrix = getNodeToWorldTransform();
    _quadRoot->preCalculateAABB(_terrainModelMatrix);
    cacheUniformAttribLocation();
}

void Terrain::cacheUniformAttribLocation()
{

    _positionLocation = glGetAttribLocation(this->getGLProgram()->getProgram(),"a_position");
    _texcordLocation = glGetAttribLocation(this->getGLProgram()->getProgram(),"a_texCoord");
    _normalLocation = glGetAttribLocation(this->getGLProgram()->getProgram(),"a_normal");
    _alphaMapLocation = -1;
    for(int i =0;i<4;i++)
    {
        _detailMapLocation[i] = -1;
        _detailMapSizeLocation[i] = -1;
    }
    auto glProgram = getGLProgram();
    _alphaIsHasAlphaMapLocation = glGetUniformLocation(glProgram->getProgram(),"u_has_alpha");
    if(!_alphaMap)
    {
        _detailMapLocation[0] = glGetUniformLocation(glProgram->getProgram(),"u_texture0");
        
    }else
    {
        for(int i =0;i<_maxDetailMapValue;i++)
        {
            char str[20];
            sprintf(str,"u_texture%d",i);
            _detailMapLocation[i] = glGetUniformLocation(glProgram->getProgram(),str);

            sprintf(str,"u_detailSize[%d]",i);
            _detailMapSizeLocation[i] = glGetUniformLocation(glProgram->getProgram(),str);
        }
        _alphaMapLocation = glGetUniformLocation(glProgram->getProgram(),"u_alphaMap");
    }
}

bool Terrain::initTextures()
{
    Texture2D::TexParams texParam;
    texParam.wrapS = GL_REPEAT;
    texParam.wrapT = GL_REPEAT;
    if(!_terrainData._alphaMapSrc)
    {
        auto textImage = new (std::nothrow)Image();
        textImage->initWithImageFile(_terrainData._detailMaps[0]._detailMapSrc);
        auto texture = new (std::nothrow)Texture2D();
        texture->initWithImage(textImage);
        texture->generateMipmap();
        _detailMapTextures[0] = texture;
        texParam.minFilter = GL_LINEAR_MIPMAP_LINEAR;
        texParam.magFilter = GL_LINEAR;
        texture->setTexParameters(texParam);
        delete textImage;
    }else
    {
        //alpha map
        auto image = new (std::nothrow)Image(); 
        image->initWithImageFile(_terrainData._alphaMapSrc);
        _alphaMap = new (std::nothrow)Texture2D();
        _alphaMap->initWithImage(image);
        texParam.wrapS = GL_CLAMP_TO_EDGE;
        texParam.wrapT = GL_CLAMP_TO_EDGE;
        texParam.minFilter = GL_LINEAR;
        texParam.magFilter = GL_LINEAR;
        _alphaMap->setTexParameters(texParam);
        delete image;

        for(int i =0;i<_terrainData._detailMapAmount;i++)
        {
            auto textImage = new (std::nothrow)Image();
            textImage->initWithImageFile(_terrainData._detailMaps[i]._detailMapSrc);
            auto texture = new (std::nothrow)Texture2D();
            texture->initWithImage(textImage);
            delete textImage;
            texture->generateMipmap();
            _detailMapTextures[i] = texture;

            texParam.wrapS = GL_REPEAT;
            texParam.wrapT = GL_REPEAT;
            texParam.minFilter = GL_LINEAR_MIPMAP_LINEAR;
            texParam.magFilter = GL_LINEAR;
            texture->setTexParameters(texParam);
        }
    }
    setMaxDetailMapAmount(_terrainData._detailMapAmount);
    return true;
}

void Terrain::reload()
{
    int chunk_amount_y = _imageHeight/_chunkSize.height;
    int chunk_amount_x = _imageWidth/_chunkSize.width;

    for(int m =0;m<chunk_amount_y;m++)
    {
        for(int n =0; n<chunk_amount_x;n++)
        {
            _chunkesArray[m][n]->finish();
        }
    }

    CCLOG("recreate");
    initTextures();
    _chunkLodIndicesSet.clear();
    _chunkLodIndicesSkirtSet.clear();
}

void Terrain::Chunk::finish()
{
    //genearate two VBO ,the first for vertices, we just setup datas once ,won't changed at all
    //the second vbo for the indices, because we use level of detail technique to each chunk, so we will modified frequently 
    glGenBuffers(1,&_vbo);

    //only set for vertices vbo
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TerrainVertexData)*_originalVertices.size(), &_originalVertices[0], GL_STREAM_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER,0);

    calculateSlope();

    for(int i =0;i<4;i++)
    {
        int step = 1<<_currentLod;
        //reserve the indices size, the first part is the core part of the chunk, the second part & thid part is for fix crack 
        int indicesAmount =(_terrain->_chunkSize.width/step+1)*(_terrain->_chunkSize.height/step+1)*6+(_terrain->_chunkSize.height/step)*6
            +(_terrain->_chunkSize.width/step)*6;
        _lod[i]._indices.reserve(indicesAmount);
    }
    _oldLod = -1;
}

void Terrain::Chunk::bindAndDraw()
{
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    if(_terrain->_isCameraViewChanged || _oldLod <0)
    {
        switch (_terrain->_crackFixedType)
        {
        case CrackFixedType::SKIRT:

            updateIndicesLODSkirt();
            break;
        case CrackFixedType::INCREASE_LOWER:
            updateVerticesForLOD();
            updateIndicesLOD();
            break;
        default:
            break;
        }
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_chunkIndices._indices);
    unsigned long offset = 0;
    //position
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(TerrainVertexData), (GLvoid *)offset);
    offset +=sizeof(Vec3);
    //texcoord
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD,2,GL_FLOAT,GL_FALSE,sizeof(TerrainVertexData),(GLvoid *)offset);
    offset +=sizeof(Tex2F);
    //normal
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_NORMAL,3,GL_FLOAT,GL_FALSE,sizeof(TerrainVertexData),(GLvoid *)offset);
    glDrawElements(GL_TRIANGLES, (GLsizei)_chunkIndices._size, GL_UNSIGNED_SHORT, 0);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _chunkIndices._size);
}

void Terrain::Chunk::generate(int imgWidth, int imageHei, int m, int n, const unsigned char * data)
{
    _posY = m;
    _posX = n;
    switch (_terrain->_crackFixedType)
    {
    case CrackFixedType::SKIRT:
        {
            for(int i=_size.height*m;i<=_size.height*(m+1);i++)
            {
                if(i>=imageHei) break;
                for(int j=_size.width*n;j<=_size.width*(n+1);j++)
                {
                    if(j>=imgWidth)break;
                    auto v =_terrain->_vertices[i*imgWidth + j];
                    _originalVertices.push_back (v);
                }
            }
            // add four skirts
           
            float skirtHeight =  _terrain->_skirtRatio *_terrain->_terrainData._mapScale*8;
            //#1
            _terrain->_skirtVerticesOffset[0] = (int)_originalVertices.size();
            for(int i =_size.height*m;i<=_size.height*(m+1);i++)
            {
                auto v = _terrain->_vertices[i*imgWidth +_size.width*(n+1)];
                v._position.y -= skirtHeight;
                _originalVertices.push_back (v);
            }

            //#2
            _terrain->_skirtVerticesOffset[1] = (int)_originalVertices.size();
            for(int j =_size.width*n;j<=_size.width*(n+1);j++)
            {
                auto v = _terrain->_vertices[_size.height*(m+1)*imgWidth + j];
                v._position.y -=skirtHeight;
                _originalVertices.push_back (v);
            }

            //#3
            _terrain->_skirtVerticesOffset[2] = (int)_originalVertices.size();
            for(int i =_size.height*m;i<=_size.height*(m+1);i++)
            {
                auto v = _terrain->_vertices[i*imgWidth + _size.width*n];
                v._position.y -= skirtHeight;
                _originalVertices.push_back (v);
            }

            //#4
            _terrain->_skirtVerticesOffset[3] = (int)_originalVertices.size();
            for(int j =_size.width*n;j<=_size.width*(n+1);j++)
            {
                auto v = _terrain->_vertices[_size.height*m*imgWidth+j];
                v._position.y -= skirtHeight;
                //v.position.y = -5;
                _originalVertices.push_back (v);
            }
        }
        break;
    case CrackFixedType::INCREASE_LOWER:
        {
            for(int i=_size.height*m;i<=_size.height*(m+1);i++)
            {
                if(i>=imageHei) break;
                for(int j=_size.width*n;j<=_size.width*(n+1);j++)
                {
                    if(j>=imgWidth)break;
                    auto v =_terrain->_vertices[i*imgWidth + j];
                    _originalVertices.push_back (v);
                }
            }
        }
        break;
    }

    calculateAABB();
    finish();
}

Terrain::Chunk::Chunk()
{
    _currentLod = 0;
    _left = nullptr;
    _right = nullptr;
    _back = nullptr;
    _front = nullptr;
    _oldLod = -1;
    for(int i =0;i<4;i++)
    {
        _neighborOldLOD[i] = -1;
    }
}

void Terrain::Chunk::updateIndicesLOD()
{
    int currentNeighborLOD[4];
    if(_left)
    {
        currentNeighborLOD[0] = _left->_currentLod;
    }else{currentNeighborLOD[0] = -1;}
    if(_right)
    {
        currentNeighborLOD[1] = _right->_currentLod;
    }else{currentNeighborLOD[1] = -1;}
    if(_back)
    {
        currentNeighborLOD[2] = _back->_currentLod;
    }else{currentNeighborLOD[2] = -1;}
    if(_front)
    {
        currentNeighborLOD[3] = _front->_currentLod;
    }else{currentNeighborLOD[3] = -1;}

    if(_oldLod == _currentLod &&(memcmp(currentNeighborLOD,_neighborOldLOD,sizeof(currentNeighborLOD))==0) )
    {
        return;// no need to update
    }
    bool isOk;
    _chunkIndices = _terrain->lookForIndicesLOD(currentNeighborLOD,_currentLod,&isOk);
    if(isOk)
    {
        return;
    }
    memcpy(_neighborOldLOD,currentNeighborLOD,sizeof(currentNeighborLOD)); 
    _oldLod = _currentLod;
    int gridY = _size.height;
    int gridX = _size.width;

    int step = 1<<_currentLod;
    if((_left&&_left->_currentLod > _currentLod) ||(_right&&_right->_currentLod > _currentLod)
        ||(_back&&_back->_currentLod > _currentLod) || (_front && _front->_currentLod > _currentLod))
        //need update indices.
    {
        //t-junction inner 
        _lod[_currentLod]._indices.clear();
        for(int i =step;i<gridY-step;i+=step)
        {
            for(int j = step;j<gridX-step;j+=step)
            {  
                int nLocIndex = i * (gridX+1) + j;
                _lod[_currentLod]._indices.push_back (nLocIndex);
                _lod[_currentLod]._indices.push_back (nLocIndex + step * (gridX+1));
                _lod[_currentLod]._indices.push_back (nLocIndex + step);

                _lod[_currentLod]._indices.push_back (nLocIndex + step);
                _lod[_currentLod]._indices.push_back (nLocIndex + step * (gridX+1));
                _lod[_currentLod]._indices.push_back (nLocIndex + step * (gridX+1) + step);
            }
        }
        //fix T-crack
        int next_step = 1<<(_currentLod+1);
        if(_left&&_left->_currentLod > _currentLod)//left
        {
            for(int i =0;i<gridY;i+=next_step)
            {
                _lod[_currentLod]._indices.push_back(i*(gridX+1)+step);
                _lod[_currentLod]._indices.push_back(i*(gridX+1));
                _lod[_currentLod]._indices.push_back((i+next_step)*(gridX+1));

                _lod[_currentLod]._indices.push_back(i*(gridX+1)+step);
                _lod[_currentLod]._indices.push_back((i+next_step)*(gridX+1));
                _lod[_currentLod]._indices.push_back((i+step)*(gridX+1)+step);

                _lod[_currentLod]._indices.push_back((i+step)*(gridX+1)+step);
                _lod[_currentLod]._indices.push_back((i+next_step)*(gridX+1));
                _lod[_currentLod]._indices.push_back((i+next_step)*(gridX+1)+step);
            }
        }else{
            int start=0;
            int end =gridY;
            if(_front&&_front->_currentLod > _currentLod) end -=step;
            if(_back&&_back->_currentLod > _currentLod) start +=step;
            for(int i =start;i<end;i+=step)
            {
                _lod[_currentLod]._indices.push_back(i*(gridX+1)+step);
                _lod[_currentLod]._indices.push_back(i*(gridX+1));
                _lod[_currentLod]._indices.push_back((i+step)*(gridX+1));

                _lod[_currentLod]._indices.push_back(i*(gridX+1)+step);
                _lod[_currentLod]._indices.push_back((i+step)*(gridX+1));
                _lod[_currentLod]._indices.push_back((i+step)*(gridX+1)+step);
            }
        }

        if(_right&&_right->_currentLod > _currentLod)//LEFT
        {
            for(int i =0;i<gridY;i+=next_step)
            {
                _lod[_currentLod]._indices.push_back(i*(gridX+1)+gridX);
                _lod[_currentLod]._indices.push_back(i*(gridX+1)+gridX-step);
                _lod[_currentLod]._indices.push_back((i+step)*(gridX+1)+gridX-step);

                _lod[_currentLod]._indices.push_back(i*(gridX+1)+gridX);
                _lod[_currentLod]._indices.push_back((i+step)*(gridX+1)+gridX-step);
                _lod[_currentLod]._indices.push_back((i+next_step)*(gridX+1)+gridX-step);

                _lod[_currentLod]._indices.push_back(i*(gridX+1)+gridX);
                _lod[_currentLod]._indices.push_back((i+next_step)*(gridX+1)+gridX-step);
                _lod[_currentLod]._indices.push_back((i+next_step)*(gridX+1)+gridX);
            }
        }else{
            int start=0;
            int end =gridY;
            if(_front&&_front->_currentLod > _currentLod) end -=step;
            if(_back&&_back->_currentLod > _currentLod) start +=step;
            for(int i =start;i<end;i+=step)
            {
                _lod[_currentLod]._indices.push_back(i*(gridX+1)+gridX);
                _lod[_currentLod]._indices.push_back(i*(gridX+1)+gridX-step);
                _lod[_currentLod]._indices.push_back((i+step)*(gridX+1)+gridX-step);

                _lod[_currentLod]._indices.push_back(i*(gridX+1)+gridX);
                _lod[_currentLod]._indices.push_back((i+step)*(gridX+1)+gridX-step);
                _lod[_currentLod]._indices.push_back((i+step)*(gridX+1)+gridX);
            }
        }
        if(_front&&_front->_currentLod > _currentLod)//front
        {
            for(int i =0;i<gridX;i+=next_step)
            {
                _lod[_currentLod]._indices.push_back((gridY-step)*(gridX+1)+i);
                _lod[_currentLod]._indices.push_back(gridY*(gridX+1)+i);
                _lod[_currentLod]._indices.push_back((gridY-step)*(gridX+1)+i+step);

                _lod[_currentLod]._indices.push_back((gridY-step)*(gridX+1)+i+step);
                _lod[_currentLod]._indices.push_back(gridY*(gridX+1)+i);
                _lod[_currentLod]._indices.push_back(gridY*(gridX+1)+i+next_step);

                _lod[_currentLod]._indices.push_back((gridY-step)*(gridX+1)+i+step);
                _lod[_currentLod]._indices.push_back(gridY*(gridX+1)+i+next_step);
                _lod[_currentLod]._indices.push_back((gridY-step)*(gridX+1)+i+next_step);
            }
        }else
        {
            for(int i =step;i<gridX-step;i+=step)
            {
                _lod[_currentLod]._indices.push_back((gridY-step)*(gridX+1)+i);
                _lod[_currentLod]._indices.push_back(gridY*(gridX+1)+i);
                _lod[_currentLod]._indices.push_back((gridY-step)*(gridX+1)+i+step);

                _lod[_currentLod]._indices.push_back((gridY-step)*(gridX+1)+i+step);
                _lod[_currentLod]._indices.push_back(gridY*(gridX+1)+i);
                _lod[_currentLod]._indices.push_back(gridY*(gridX+1)+i+step);
            }
        }
        if(_back&&_back->_currentLod > _currentLod)//back
        {
            for(int i =0;i<gridX;i+=next_step)
            {
                _lod[_currentLod]._indices.push_back(i);
                _lod[_currentLod]._indices.push_back(step*(gridX+1) +i);
                _lod[_currentLod]._indices.push_back(step*(gridX+1) +i+step);

                _lod[_currentLod]._indices.push_back(i);
                _lod[_currentLod]._indices.push_back(step*(gridX+1) +i+step);
                _lod[_currentLod]._indices.push_back(i+next_step);

                _lod[_currentLod]._indices.push_back(i+next_step);
                _lod[_currentLod]._indices.push_back(step*(gridX+1) +i+step);
                _lod[_currentLod]._indices.push_back(step*(gridX+1) +i+next_step);
            }
        }else{
            for(int i =step;i<gridX-step;i+=step)
            {
                _lod[_currentLod]._indices.push_back(i);
                _lod[_currentLod]._indices.push_back(step*(gridX+1)+i);
                _lod[_currentLod]._indices.push_back(step*(gridX+1)+i+step);

                _lod[_currentLod]._indices.push_back(i);
                _lod[_currentLod]._indices.push_back(step*(gridX+1)+i+step);
                _lod[_currentLod]._indices.push_back(i+step);
            }
        }

        _chunkIndices = _terrain->insertIndicesLOD(currentNeighborLOD,_currentLod,&_lod[_currentLod]._indices[0],(int)_lod[_currentLod]._indices.size());
    }else{
        //No lod difference, use simple method
        _lod[_currentLod]._indices.clear();
        for(int i =0;i<gridY;i+=step)
        {
            for(int j = 0;j<gridX;j+=step)
            { 

                int nLocIndex = i * (gridX+1) + j; 
                _lod[_currentLod]._indices.push_back (nLocIndex);
                _lod[_currentLod]._indices.push_back (nLocIndex + step * (gridX+1));
                _lod[_currentLod]._indices.push_back (nLocIndex + step);

                _lod[_currentLod]._indices.push_back (nLocIndex + step);
                _lod[_currentLod]._indices.push_back (nLocIndex + step * (gridX+1));
                _lod[_currentLod]._indices.push_back (nLocIndex + step * (gridX+1) + step);
            }
        }
        _chunkIndices = _terrain->insertIndicesLOD(currentNeighborLOD,_currentLod,&_lod[_currentLod]._indices[0],(int)_lod[_currentLod]._indices.size());
    }
}

void Terrain::Chunk::calculateAABB()
{
    std::vector<Vec3>pos;
    for(int i =0;i<_originalVertices.size();i++)
    {
        pos.push_back(_originalVertices[i]._position);
    }
    _aabb.updateMinMax(&pos[0],pos.size());
}

void Terrain::Chunk::calculateSlope()
{
    //find max slope
    auto lowest = _originalVertices[0]._position;
    for(int i = 0;i<_originalVertices.size();i++)
    {
        if(_originalVertices[i]._position.y< lowest.y)
        {
            lowest = _originalVertices[i]._position;
        }
    }
    auto highest = _originalVertices[0]._position;
    for(int i = 0;i<_originalVertices.size();i++)
    {
        if(_originalVertices[i]._position.y> highest.y)
        {
            highest = _originalVertices[i]._position;
        }
    }
    Vec2 a(lowest.x,lowest.z);
    Vec2 b(highest.x,highest.z);
    float dist = a.distance(b);
    _slope = (highest.y - lowest.y)/dist;
}

void Terrain::Chunk::updateVerticesForLOD()
{
    if(_oldLod == _currentLod){ return;} // no need to update vertices
    _currentVertices = _originalVertices;
    int gridY = _size.height;
    int gridX = _size.width;

    if(_currentLod>=2 && std::abs(_slope)>1.2)
    {
        int step = 1<<_currentLod;
        for(int i =step;i<gridY-step;i+=step)
            for(int j = step; j<gridX-step;j+=step)
            {
                // use linear-sample adjust vertices height
                float height = 0;
                float count = 0;
                for(int n = i-step/2;n<i+step/2;n++)
                {
                    for(int m = j-step/2;m<j+step/2;m++)
                    {
                        float weight = (step/2 - std::abs(n-i))*(step/2 - std::abs(m-j));
                        height += _originalVertices[m*(gridX+1)+n]._position.y;
                        count += weight;
                    }
                }
                _currentVertices[i*(gridX+1)+j]._position.y = height/count;
            }
    }

    glBufferData(GL_ARRAY_BUFFER, sizeof(TerrainVertexData)*_currentVertices.size(), &_currentVertices[0], GL_STREAM_DRAW);

}

Terrain::Chunk::~Chunk()
{
    glDeleteBuffers(1,&_vbo);
}

void Terrain::Chunk::updateIndicesLODSkirt()
{
    if(_oldLod == _currentLod) return;
    _oldLod = _currentLod;
    bool isOk;
    _chunkIndices =  _terrain->lookForIndicesLODSkrit(_currentLod,&isOk);
    if(isOk) return;

    int gridY = _size.height;
    int gridX = _size.width;
    int step = 1<<_currentLod;
    int k =0;
    for(int i =0;i<gridY;i+=step,k+=step)
    {
        for(int j = 0;j<gridX;j+=step)
        {  
            int nLocIndex = i * (gridX+1) + j;
            _lod[_currentLod]._indices.push_back (nLocIndex);
            _lod[_currentLod]._indices.push_back (nLocIndex + step * (gridX+1));
            _lod[_currentLod]._indices.push_back (nLocIndex + step);

            _lod[_currentLod]._indices.push_back (nLocIndex + step);
            _lod[_currentLod]._indices.push_back (nLocIndex + step * (gridX+1));
            _lod[_currentLod]._indices.push_back (nLocIndex + step * (gridX+1) + step);
        }
    }
    //add skirt
    //#1
    for(int i =0;i<gridY;i+=step)
    {
        int nLocIndex = i * (gridX+1) + gridX;
        _lod[_currentLod]._indices.push_back (nLocIndex);
        _lod[_currentLod]._indices.push_back (nLocIndex + step * (gridX+1));
        _lod[_currentLod]._indices.push_back ((gridY+1) *(gridX+1)+i);

        _lod[_currentLod]._indices.push_back ((gridY+1) *(gridX+1)+i);
        _lod[_currentLod]._indices.push_back (nLocIndex + step * (gridX+1));
        _lod[_currentLod]._indices.push_back ((gridY+1) *(gridX+1)+i+step);
    }

    //#2
    for(int j =0;j<gridX;j+=step)
    {
        int nLocIndex = (gridY)* (gridX+1) + j;
        _lod[_currentLod]._indices.push_back (nLocIndex);
        _lod[_currentLod]._indices.push_back (_terrain->_skirtVerticesOffset[1] +j);
        _lod[_currentLod]._indices.push_back (nLocIndex + step);

        _lod[_currentLod]._indices.push_back (nLocIndex + step);
        _lod[_currentLod]._indices.push_back (_terrain->_skirtVerticesOffset[1] +j);
        _lod[_currentLod]._indices.push_back (_terrain->_skirtVerticesOffset[1] +j + step);
    }

    //#3
    for(int i =0;i<gridY;i+=step)
    {
        int nLocIndex = i * (gridX+1);
        _lod[_currentLod]._indices.push_back (nLocIndex);
        _lod[_currentLod]._indices.push_back (_terrain->_skirtVerticesOffset[2]+i);
        _lod[_currentLod]._indices.push_back ((i+step)*(gridX+1));

        _lod[_currentLod]._indices.push_back ((i+step)*(gridX+1));
        _lod[_currentLod]._indices.push_back (_terrain->_skirtVerticesOffset[2]+i);
        _lod[_currentLod]._indices.push_back (_terrain->_skirtVerticesOffset[2]+i +step);
    }

    //#4
    for(int j =0;j<gridX;j+=step)
    {
        int nLocIndex = j;
        _lod[_currentLod]._indices.push_back (nLocIndex + step);
        _lod[_currentLod]._indices.push_back (_terrain->_skirtVerticesOffset[3]+j); 
        _lod[_currentLod]._indices.push_back (nLocIndex);


        _lod[_currentLod]._indices.push_back (_terrain->_skirtVerticesOffset[3] + j + step);
        _lod[_currentLod]._indices.push_back (_terrain->_skirtVerticesOffset[3] +j);
        _lod[_currentLod]._indices.push_back (nLocIndex + step);
    }

    _chunkIndices = _terrain->insertIndicesLODSkirt(_currentLod,&_lod[_currentLod]._indices[0], (int)_lod[_currentLod]._indices.size());
}

Terrain::QuadTree::QuadTree(int x, int y, int w, int h, Terrain * terrain)
{
    _terrain = terrain;
    _needDraw = true;
    _parent = nullptr;
    _tl =nullptr;
    _tr =nullptr;
    _bl =nullptr;
    _br =nullptr;
    _posX = x;
    _posY = y;
    this->_height = h;
    this->_width = w;
    if(_width> terrain->_chunkSize.width &&_height >terrain->_chunkSize.height) //subdivision
    {
        _isTerminal = false;
        this->_tl = new QuadTree(x,y,_width/2,_height/2,terrain);
        this->_tl->_parent = this;
        this->_tr = new QuadTree(x+_width/2,y,_width/2,_height/2,terrain);
        this->_tr->_parent = this;
        this->_bl = new QuadTree(x,y+_height/2,_width/2,_height/2,terrain);
        this->_bl->_parent = this;
        this->_br = new QuadTree(x+_width/2,y+_height/2,_width/2,_height/2,terrain);
        this->_br->_parent = this;

        _localAABB.merge(_tl->_localAABB);
        _localAABB.merge(_tr->_localAABB);
        _localAABB.merge(_bl->_localAABB);
        _localAABB.merge(_br->_localAABB);
    }else // is terminal Node
    {
        int m = _posY/terrain->_chunkSize.height;
        int n = _posX/terrain->_chunkSize.width;
        _chunk = terrain->_chunkesArray[m][n];
        _isTerminal = true;
        _localAABB = _chunk->_aabb;
        _chunk->_parent = this;
    }
    _worldSpaceAABB = _localAABB;
    _worldSpaceAABB.transform(_terrain->getNodeToWorldTransform());
}

void Terrain::QuadTree::draw()
{
    if(!_needDraw)return;
    if(_isTerminal){
        this->_chunk->bindAndDraw();
    }else
    {
        this->_tl->draw();
        this->_tr->draw();
        this->_br->draw();
        this->_bl->draw();
    }
}

void Terrain::QuadTree::resetNeedDraw(bool value)
{
    this->_needDraw = value;
    if(!_isTerminal)
    {
        _tl->resetNeedDraw(value);
        _tr->resetNeedDraw(value);
        _bl->resetNeedDraw(value);
        _br->resetNeedDraw(value);
    }
}

void Terrain::QuadTree::cullByCamera(const Camera * camera, const Mat4 & worldTransform)
{
    if(!camera->isVisibleInFrustum(&_worldSpaceAABB))
    {
        this->resetNeedDraw(false);
    }else
    {
        if(!_isTerminal){
            _tl->cullByCamera(camera,worldTransform);
            _tr->cullByCamera(camera,worldTransform);
            _bl->cullByCamera(camera,worldTransform);
            _br->cullByCamera(camera,worldTransform);
        }
    }
}

void Terrain::QuadTree::preCalculateAABB(const Mat4 & worldTransform)
{

    _worldSpaceAABB = _localAABB;
    _worldSpaceAABB.transform(worldTransform);
    if(!_isTerminal){
        _tl->preCalculateAABB(worldTransform);
        _tr->preCalculateAABB(worldTransform);
        _bl->preCalculateAABB(worldTransform);
        _br->preCalculateAABB(worldTransform);
    }
}

Terrain::QuadTree::~QuadTree()
{
    if(_tl) delete _tl;
    if(_tr) delete _tr;
    if(_bl) delete _bl;
    if(_br) delete _br;
}

Terrain::TerrainData::TerrainData(const char * heightMapsrc , const char * textureSrc, const Size & chunksize, float height, float scale)
{ 
    this->_heightMapSrc = heightMapsrc;
    this->_detailMaps[0]._detailMapSrc = textureSrc;
    this->_alphaMapSrc = nullptr;
    this->_chunkSize = chunksize;
    this->_mapHeight = height;
    this->_mapScale = scale; 
    _skirtHeightRatio = 1;
}

Terrain::TerrainData::TerrainData(const char * heightMapsrc, const char * alphamap, const DetailMap& detail1, const DetailMap& detail2, const DetailMap& detail3, const DetailMap& detail4, const Size & chunksize, float height, float scale)
{
    this->_heightMapSrc = heightMapsrc;
    this->_alphaMapSrc = const_cast<char *>(alphamap);
    this->_detailMaps[0] = detail1;
    this->_detailMaps[1] = detail2;
    this->_detailMaps[2] = detail3;
    this->_detailMaps[3] = detail4;
    this->_chunkSize = chunksize;
    this->_mapHeight = height;
    this->_mapScale = scale;
    _detailMapAmount = 4;
    _skirtHeightRatio = 1;
}

Terrain::TerrainData::TerrainData(const char* heightMapsrc, const char * alphamap, const DetailMap& detail1, const DetailMap& detail2, const DetailMap& detail3, const Size & chunksize /*= Size(32,32)*/, float height /*= 2*/, float scale /*= 0.1*/)
{
    this->_heightMapSrc = heightMapsrc;
    this->_alphaMapSrc = const_cast<char *>(alphamap);
    this->_detailMaps[0] = detail1;
    this->_detailMaps[1] = detail2;
    this->_detailMaps[2] = detail3;
    this->_detailMaps[3] = nullptr;
    this->_chunkSize = chunksize;
    this->_mapHeight = height;
    this->_mapScale = scale;
    _detailMapAmount = 3;
    _skirtHeightRatio = 1;
}

Terrain::TerrainData::TerrainData()
{

}

Terrain::DetailMap::DetailMap(const char * detailMapPath, float size /*= 35*/)
{
    this->_detailMapSrc = detailMapPath;
    this->_detailMapSize = size;
}

Terrain::DetailMap::DetailMap()
{
    _detailMapSrc = ""; 
    _detailMapSize = 35;
}

NS_CC_END
