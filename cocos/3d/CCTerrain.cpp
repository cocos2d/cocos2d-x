#include "CCTerrain.h"
#include <CCImage.h>
USING_NS_CC;

#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCGLProgramStateCache.h"
#include "renderer/ccGLStateCache.h"
#include "2d/CCCamera.h"
#include <stdlib.h>
static const char * vertex_shader = "\
                                    attribute vec4 a_position;\
                                    attribute vec2 a_texCoord;\
                                    attribute vec3 a_normal;\
                                    \n#ifdef GL_ES\n\
                                    varying mediump vec2 v_texCoord;\
                                    varying mediump vec3 v_normal;\
                                    \n#else\n\
                                    varying vec2 v_texCoord;\
                                    varying vec3 v_normal;\
                                    \n#endif\n\
                                    void main()\
                                    {\
                                    gl_Position = CC_MVPMatrix * a_position;\
                                    v_texCoord = a_texCoord;\
                                    v_normal = a_normal;\
                                    }\
                                    ";

static const char * fragment_shader_RGB_4_DETAIL ="\n#ifdef GL_ES\n\
                                                  precision lowp float;\
                                                  \n#endif\n\
                                                  uniform vec3 u_color;\
                                                  varying vec2 v_texCoord;\
                                                  varying vec3 v_normal;\
                                                  uniform int u_has_alpha;\
                                                  uniform sampler2D u_alphaMap;\
                                                  uniform sampler2D u_texture0;\
                                                  uniform sampler2D u_texture1;\
                                                  uniform sampler2D u_texture2;\
                                                  uniform sampler2D u_texture3;\
                                                  uniform float u_detailSize[4];\
                                                  void main()\
                                                  {\
                                                  vec3 light_direction = vec3(-1,-1,0);\
                                                  float lightFactor = dot(-light_direction,v_normal);\
                                                  if(u_has_alpha<=0)\
                                                  {\
                                                  gl_FragColor =  texture2D(u_texture0, v_texCoord)*lightFactor;\
                                                  }else\
                                                  {\
                                                  vec4 blendFactor =texture2D(u_alphaMap,v_texCoord);\
                                                  vec4 color = vec4(0,0,0,0);\
                                                  color = texture2D(u_texture0, v_texCoord*u_detailSize[0])*blendFactor.r +\
                                                  texture2D(u_texture1, v_texCoord*u_detailSize[1])*blendFactor.g + texture2D(u_texture2, v_texCoord*u_detailSize[2])*blendFactor.b;\n\
                                                  float grayFactor =dot(blendFactor.rgb, vec3(1, 1, 1));\
                                                  color +=texture2D(u_texture3, v_texCoord*u_detailSize[3])*(1.0-grayFactor);\
                                                  gl_FragColor = color*lightFactor;\
                                                  }\
                                                  }";
NS_CC_BEGIN
    Terrain * Terrain::create(TerrainData &parameter)
{
    Terrain * obj = new (std::nothrow)Terrain();
    obj->_terrainData = parameter;
    //chunksize
    obj->_chunkSize = parameter.chunkSize;
    //heightmap
    obj->initHeightMap(parameter.heightMapSrc.c_str());
    if(!parameter.alphaMapSrc)
    {
        auto textImage = new (std::nothrow)Image();
        textImage->initWithImageFile(parameter.detailMaps[0].detailMapSrc);
        auto texture = new (std::nothrow)Texture2D();
        texture->initWithImage(textImage);
        obj->textures.push_back(texture);
    }else
    {
        //alpha map
        auto textImage = new (std::nothrow)Image(); 
        textImage->initWithImageFile(parameter.alphaMapSrc);
        obj->_alphaMap = new (std::nothrow)Texture2D();
        obj->_alphaMap->initWithImage(textImage);
        for(int i =0;i<4;i++)
        {
            auto textImage = new (std::nothrow)Image();
            textImage->initWithImageFile(parameter.detailMaps[i].detailMapSrc);
            auto texture = new (std::nothrow)Texture2D();
            texture->initWithImage(textImage);
            obj->textures.push_back(texture);
            obj->detailSize[i] = parameter.detailMaps[i].detailMapSize;
        }
    }
    obj->init();
    obj->setAnchorPoint(Vec2(0,0));
    return obj;
}

bool Terrain::init()
{
    _lodDistance[0]=288;
    _lodDistance[1]=512;
    _lodDistance[2]=1000;
    auto shader = GLProgram::createWithByteArrays(vertex_shader,fragment_shader_RGB_4_DETAIL);
    auto state = GLProgramState::create(shader);
    setGLProgramState(state);
    setDrawWire(false);
    setIsEnableFrustumCull(true);
    return true;
}

void Terrain::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    _customCommand.init(getGlobalZOrder());
    _customCommand.func = CC_CALLBACK_0(Terrain::onDraw, this, transform, flags);
    _customCommand.setTransparent(true);
    renderer->addCommand(&_customCommand);
}

void Terrain::onDraw(const Mat4 &transform, uint32_t flags)
{
    auto glProgram = getGLProgram();
    glProgram->use();
    glProgram->setUniformsForBuiltins(transform);
    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    if(!_alphaMap)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,textures[0]->getName());
        auto texture_location = glGetUniformLocation(glProgram->getProgram(),"u_texture0");
        glUniform1i(texture_location,0);
        auto alpha_location = glGetUniformLocation(glProgram->getProgram(),"u_has_alpha");
        glUniform1i(alpha_location,0);
    }else
    {
        for(int i =0;i<4;i++)
        {
            glActiveTexture(GL_TEXTURE0+i);
            glBindTexture(GL_TEXTURE_2D,textures[i]->getName());
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            char str[20];
            sprintf(str,"u_texture%d",i);
            auto texture_location = glGetUniformLocation(glProgram->getProgram(),str);
            glUniform1i(texture_location,i);

            sprintf(str,"u_detailSize[%d]",i);
            auto detailSizeLocation = glGetUniformLocation(glProgram->getProgram(),str);
            glUniform1f(detailSizeLocation,detailSize[i]);
        }
        auto alpha_location = glGetUniformLocation(glProgram->getProgram(),"u_has_alpha");
        glUniform1i(alpha_location,1);

        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D,_alphaMap->getName());
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
        auto alpha_map_location = glGetUniformLocation(glProgram->getProgram(),"u_alphaMap");
        glUniform1i(alpha_map_location,4);
    }
    //set lod
    setChunksLOD(Camera::getVisitingCamera()->getPosition3D());
    //camera frustum culling
    auto camera = Camera::getVisitingCamera();
    quad->cullByCamera(camera,getNodeToWorldTransform());
    quad->draw();
    quad->resetNeedDraw(true);//reset it 
    glActiveTexture(GL_TEXTURE0);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
}

void Terrain::initHeightMap(const char * heightMap)
{
    _heightMapImage = new Image();
    _heightMapImage->initWithImageFile(heightMap);
    _data = _heightMapImage->getData();
    imageWidth =_heightMapImage->getWidth();
    imageHeight =_heightMapImage->getHeight();
    auto format = _heightMapImage->getRenderFormat();
    int chunk_amount_y = imageHeight/_chunkSize.height;
    int chunk_amount_x = imageWidth/_chunkSize.width;
    loadVertices();
    calculateNormal();

    for(int m =0;m<chunk_amount_y;m++)
    {
        for(int n =0; n<chunk_amount_x;n++)
        {
            _chunkesArray[m][n] = new Chunk();
        }
    }

    for(int m =0;m<chunk_amount_y;m++)
    {
        for(int n =0; n<chunk_amount_x;n++)
        {

            _chunkesArray[m][n]->_terrain = this;
            if(n-1>=0) _chunkesArray[m][n]->left = _chunkesArray[m][n-1];
            if(n+1<chunk_amount_x) _chunkesArray[m][n]->right = _chunkesArray[m][n+1];
            if(m-1>=0) _chunkesArray[m][n]->back = _chunkesArray[m-1][n];
            if(m+1<chunk_amount_y) _chunkesArray[m][n]->front = _chunkesArray[m+1][n];
            _chunkesArray[m][n]->_size = _chunkSize;
            _chunkesArray[m][n]->generate(imageWidth,imageHeight,m,n,_data);
        }
    }
    quad = new QuadTree(0,0,imageWidth,imageHeight,this);
}

Terrain::Terrain()
{
    _alphaMap = nullptr;
}

void Terrain::setChunksLOD(Vec3 cameraPos)
{
    int chunk_amount_y = imageHeight/_chunkSize.height;
    int chunk_amount_x = imageWidth/_chunkSize.width;
    for(int m=0;m<chunk_amount_y;m++)
        for(int n =0;n<chunk_amount_x;n++)
        {
            AABB aabb = _chunkesArray[m][n]->_aabb;
            aabb.transform(this->getNodeToWorldTransform());
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

float Terrain::getHeight(float x, float y ,float z,Vec3 * normal)
{
    Vec2 pos = Vec2(x,z);

    //top-left
    Vec2 tl = Vec2(-1*_terrainData.mapScale*imageWidth/2,-1*_terrainData.mapScale*imageHeight/2);
    auto result  = getNodeToWorldTransform()*Vec4(tl.x,0.0f,tl.y,1.0f);
    tl = Vec2(result.x,result.z);

    Vec2 to_tl = pos - tl;

    //real size
    Vec2 size = Vec2(imageWidth*_terrainData.mapScale,imageHeight*_terrainData.mapScale);
    result = getNodeToWorldTransform()*Vec4(size.x,0.0f,size.y,0.0f);
    size = Vec2(result.x,result.z);

    float width_ratio = to_tl.x/size.x;
    float height_ratio = to_tl.y/size.y;

    float image_x = width_ratio * imageWidth;
    float image_y = height_ratio * imageHeight;
    float u =image_x - (int)image_x;
    float v =image_y - (int)image_y;
    float i = (int)image_x;
    float j = (int)image_y;


    if(image_x>=imageWidth-1 || image_y >=imageHeight-1 || image_x<0 || image_y<0)
    {
        return y;
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

float Terrain::getHeight(Vec3 pos,Vec3*Normal)
{
    return getHeight(pos.x,pos.y,pos.z,Normal);
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
    return _data[(pixel_y*imageWidth+pixel_x)*byte_stride]*1.0/255*_terrainData.mapHeight -0.5*_terrainData.mapHeight;
}

void Terrain::loadVertices()
{
    for(int i =0;i<imageHeight;i++)
    {
        for(int j =0;j<imageWidth;j++)
        {
            TerrainVertexData v;
            v.position = Vec3(j*_terrainData.mapScale- imageWidth/2*_terrainData.mapScale, //x
                getImageHeight(j,i), //y
                i*_terrainData.mapScale - imageHeight/2*_terrainData.mapScale);//z
            v.texcoord = Tex2F(j*1.0/imageWidth,i*1.0/imageHeight);
            vertices.push_back (v);
        }
    }
}

void Terrain::calculateNormal()
{
    indices.clear();
    //we generate whole terrain indices(global indices) for correct normal calculate
    for(int i =0;i<imageHeight-1;i+=1)
    {
        for(int j = 0;j<imageWidth-1;j+=1)
        { 

            int nLocIndex = i * imageWidth + j; 
            indices.push_back (nLocIndex);
            indices.push_back (nLocIndex + imageWidth);
            indices.push_back (nLocIndex + 1);

            indices.push_back (nLocIndex + 1);
            indices.push_back (nLocIndex + imageWidth);
            indices.push_back (nLocIndex + imageWidth+1);
        }
    }
    for (unsigned int i = 0 ; i < indices.size() ; i += 3) {
        unsigned int Index0 = indices[i];
        unsigned int Index1 = indices[i + 1];
        unsigned int Index2 = indices[i + 2];
        Vec3 v1 = vertices[Index1].position - vertices[Index0].position;
        Vec3 v2 = vertices[Index2].position - vertices[Index0].position;
        Vec3 Normal;
        Vec3::cross(v1,v2,&Normal);
        Normal.normalize();
        vertices[Index0].normal += Normal;
        vertices[Index1].normal += Normal;
        vertices[Index2].normal += Normal;
    }

    for (unsigned int i = 0 ; i < vertices.size() ; i++) {
        vertices[i].normal.normalize();
    }
    //global indices no need at all
    indices.clear();
}

void Terrain::setDrawWire(bool bool_value)
{
    _isDrawWire = bool_value;
}

void Terrain::setLODDistance(float lod_1,float lod_2,float lod_3)
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
    free(_data);
    for(int i = 0;i<MAX_CHUNKES;i++)
    {
        for(int j = 0;j<MAX_CHUNKES;j++)
        {
            delete _chunkesArray[i][j];
        }
    }
     free(_chunkesArray);
}

cocos2d::Vec3 Terrain::getNormal(int pixel_x,int pixel_y)
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

void Terrain::Chunk::finish()
{
    //genearate two VBO ,the first for vertices, we just setup datas once ,won't changed at all
    //the second vbo for the indices, because we use level of detail technique to each chunk, so we will modified frequently 
    glGenBuffers(2,vbo);

    //only set for vertices vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TerrainVertexData)*vertices.size(), &vertices[0], GL_STREAM_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER,0);

    calculateSlope();

    for(int i =0;i<4;i++)
    {
        int step = int(powf(2.0f, float(_currentLod)));
        int indicesAmount =(_terrain->_chunkSize.width/step+1)*(_terrain->_chunkSize.height/step+1)*6+(_terrain->_chunkSize.height/step)*3*2
            +(_terrain->_chunkSize.width/step)*3*2;
        _lod[i].indices.reserve(indicesAmount);
    }
}

void Terrain::Chunk::bindAndDraw()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    if(_terrain->_isDrawWire)
    {
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    }else
    {
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    }
#endif

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    updateVerticesForLOD();
    updateIndices();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vbo[1]);
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_TEX_COORD| GL::VERTEX_ATTRIB_FLAG_NORMAL);
    unsigned int offset = 0;
    //position
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(TerrainVertexData), (GLvoid *)offset);
    offset +=sizeof(Vec3);
    //texcoord
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD,2,GL_FLOAT,GL_FALSE,sizeof(TerrainVertexData),(GLvoid *)offset);
    offset +=sizeof(Tex2F);
    auto normal_location = glGetAttribLocation(_terrain->getGLProgram()->getProgram(),"a_normal");
    glEnableVertexAttribArray(normal_location);
    //normal
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_NORMAL,3,GL_FLOAT,GL_FALSE,sizeof(TerrainVertexData),(GLvoid *)offset);
    glDrawElements(GL_TRIANGLES, _lod[_currentLod].indices.size(), GL_UNSIGNED_SHORT, 0);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
#endif
}

void Terrain::Chunk::generate(int imageWidth,int imageHeight,int m,int n,const unsigned char * data)
{
    pos_y = m;
    pos_x = n;
    for(int i=_size.height*m;i<=_size.height*(m+1);i++)
    {
        if(i>=imageHeight) break;
        for(int j=_size.width*n;j<=_size.width*(n+1);j++)
        {
            if(j>=imageWidth)break;
            auto v =_terrain->vertices[i*imageWidth + j];
            vertices.push_back (v);
        }
    }
    calculateAABB();
    finish();
}

Terrain::Chunk::Chunk()
{
    _currentLod = 0;
    left = nullptr;
    right = nullptr;
    back = nullptr;
    front = nullptr;
}

void Terrain::Chunk::updateIndices()
{
    int gridY = _size.height;
    int gridX = _size.width;

    int step = int(powf(2.0f, float(_currentLod)));
    if((left&&left->_currentLod > _currentLod) ||(right&&right->_currentLod > _currentLod)
        ||(back&&back->_currentLod > _currentLod) || (front && front->_currentLod > _currentLod))
        //need update indices.
    {
        //t-junction inner 
        _lod[_currentLod].indices.clear();
        for(int i =step;i<gridY-step;i+=step)
        {
            for(int j = step;j<gridX-step;j+=step)
            {  
                int nLocIndex = i * (gridX+1) + j;
                _lod[_currentLod].indices.push_back (nLocIndex);
                _lod[_currentLod].indices.push_back (nLocIndex + step * (gridX+1));
                _lod[_currentLod].indices.push_back (nLocIndex + step);

                _lod[_currentLod].indices.push_back (nLocIndex + step);
                _lod[_currentLod].indices.push_back (nLocIndex + step * (gridX+1));
                _lod[_currentLod].indices.push_back (nLocIndex + step * (gridX+1) + step);
FINISH_INNER_INDICES_SET:
                ;
            }
        }
        //fix T-crack
        int next_step = int(powf(2.0f, float(_currentLod+1)));
        if(left&&left->_currentLod > _currentLod)//left
        {
            for(int i =0;i<gridY;i+=next_step)
            {
                _lod[_currentLod].indices.push_back(i*(gridX+1)+step);
                _lod[_currentLod].indices.push_back(i*(gridX+1));
                _lod[_currentLod].indices.push_back((i+next_step)*(gridX+1));

                _lod[_currentLod].indices.push_back(i*(gridX+1)+step);
                _lod[_currentLod].indices.push_back((i+next_step)*(gridX+1));
                _lod[_currentLod].indices.push_back((i+step)*(gridX+1)+step);

                _lod[_currentLod].indices.push_back((i+step)*(gridX+1)+step);
                _lod[_currentLod].indices.push_back((i+next_step)*(gridX+1));
                _lod[_currentLod].indices.push_back((i+next_step)*(gridX+1)+step);
            }
        }else{
            int start=0;
            int end =gridY;
            if(front&&front->_currentLod > _currentLod) end -=step;
            if(back&&back->_currentLod > _currentLod) start +=step;
            for(int i =start;i<end;i+=step)
            {
                _lod[_currentLod].indices.push_back(i*(gridX+1)+step);
                _lod[_currentLod].indices.push_back(i*(gridX+1));
                _lod[_currentLod].indices.push_back((i+step)*(gridX+1));

                _lod[_currentLod].indices.push_back(i*(gridX+1)+step);
                _lod[_currentLod].indices.push_back((i+step)*(gridX+1));
                _lod[_currentLod].indices.push_back((i+step)*(gridX+1)+step);
            }
        }

        if(right&&right->_currentLod > _currentLod)//LEFT
        {
            for(int i =0;i<gridY;i+=next_step)
            {
                _lod[_currentLod].indices.push_back(i*(gridX+1)+gridX);
                _lod[_currentLod].indices.push_back(i*(gridX+1)+gridX-step);
                _lod[_currentLod].indices.push_back((i+step)*(gridX+1)+gridX-step);

                _lod[_currentLod].indices.push_back(i*(gridX+1)+gridX);
                _lod[_currentLod].indices.push_back((i+step)*(gridX+1)+gridX-step);
                _lod[_currentLod].indices.push_back((i+next_step)*(gridX+1)+gridX-step);

                _lod[_currentLod].indices.push_back(i*(gridX+1)+gridX);
                _lod[_currentLod].indices.push_back((i+next_step)*(gridX+1)+gridX-step);
                _lod[_currentLod].indices.push_back((i+next_step)*(gridX+1)+gridX);
            }
        }else{
            int start=0;
            int end =gridY;
            if(front&&front->_currentLod > _currentLod) end -=step;
            if(back&&back->_currentLod > _currentLod) start +=step;
            for(int i =start;i<end;i+=step)
            {
                _lod[_currentLod].indices.push_back(i*(gridX+1)+gridX);
                _lod[_currentLod].indices.push_back(i*(gridX+1)+gridX-step);
                _lod[_currentLod].indices.push_back((i+step)*(gridX+1)+gridX-step);

                _lod[_currentLod].indices.push_back(i*(gridX+1)+gridX);
                _lod[_currentLod].indices.push_back((i+step)*(gridX+1)+gridX-step);
                _lod[_currentLod].indices.push_back((i+step)*(gridX+1)+gridX);
            }
        }

        if(front&&front->_currentLod > _currentLod)//front
        {
            for(int i =0;i<gridX;i+=next_step)
            {
                _lod[_currentLod].indices.push_back((gridY-step)*(gridX+1)+i);
                _lod[_currentLod].indices.push_back(gridY*(gridX+1)+i);
                _lod[_currentLod].indices.push_back((gridY-step)*(gridX+1)+i+step);

                _lod[_currentLod].indices.push_back((gridY-step)*(gridX+1)+i+step);
                _lod[_currentLod].indices.push_back(gridY*(gridX+1)+i);
                _lod[_currentLod].indices.push_back(gridY*(gridX+1)+i+next_step);

                _lod[_currentLod].indices.push_back((gridY-step)*(gridX+1)+i+step);
                _lod[_currentLod].indices.push_back(gridY*(gridX+1)+i+next_step);
                _lod[_currentLod].indices.push_back((gridY-step)*(gridX+1)+i+next_step);
            }
        }else
        {
            for(int i =step;i<gridX-step;i+=step)
            {
                _lod[_currentLod].indices.push_back((gridY-step)*(gridX+1)+i);
                _lod[_currentLod].indices.push_back(gridY*(gridX+1)+i);
                _lod[_currentLod].indices.push_back((gridY-step)*(gridX+1)+i+step);

                _lod[_currentLod].indices.push_back((gridY-step)*(gridX+1)+i+step);
                _lod[_currentLod].indices.push_back(gridY*(gridX+1)+i);
                _lod[_currentLod].indices.push_back(gridY*(gridX+1)+i+step);
            }
        }
        if(back&&back->_currentLod > _currentLod)//back
        {
            for(int i =0;i<gridX;i+=next_step)
            {
                _lod[_currentLod].indices.push_back(i);
                _lod[_currentLod].indices.push_back(step*(gridX+1) +i);
                _lod[_currentLod].indices.push_back(step*(gridX+1) +i+step);

                _lod[_currentLod].indices.push_back(i);
                _lod[_currentLod].indices.push_back(step*(gridX+1) +i+step);
                _lod[_currentLod].indices.push_back(i+next_step);

                _lod[_currentLod].indices.push_back(i+next_step);
                _lod[_currentLod].indices.push_back(step*(gridX+1) +i+step);
                _lod[_currentLod].indices.push_back(step*(gridX+1) +i+next_step);
            }
        }else{
            for(int i =step;i<gridX-step;i+=step)
            {
                _lod[_currentLod].indices.push_back(i);
                _lod[_currentLod].indices.push_back(step*(gridX+1)+i);
                _lod[_currentLod].indices.push_back(step*(gridX+1)+i+step);

                _lod[_currentLod].indices.push_back(i);
                _lod[_currentLod].indices.push_back(step*(gridX+1)+i+step);
                _lod[_currentLod].indices.push_back(i+step);
            }
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLushort)*_lod[_currentLod].indices.size(),&_lod[_currentLod].indices[0],GL_STATIC_DRAW);
    }else{
        //No lod difference, use simple method
        _lod[_currentLod].indices.clear();
        for(int i =0;i<gridY;i+=step)
        {
            for(int j = 0;j<gridX;j+=step)
            { 

                int nLocIndex = i * (gridX+1) + j; 
                _lod[_currentLod].indices.push_back (nLocIndex);
                _lod[_currentLod].indices.push_back (nLocIndex + step * (gridX+1));
                _lod[_currentLod].indices.push_back (nLocIndex + step);

                _lod[_currentLod].indices.push_back (nLocIndex + step);
                _lod[_currentLod].indices.push_back (nLocIndex + step * (gridX+1));
                _lod[_currentLod].indices.push_back (nLocIndex + step * (gridX+1) + step);
            }
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vbo[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLushort)*_lod[_currentLod].indices.size(),&_lod[_currentLod].indices[0],GL_STATIC_DRAW);
    }
}

void Terrain::Chunk::calculateAABB()
{
    std::vector<Vec3>pos;
    for(int i =0;i<vertices.size();i++)
    {
        pos.push_back(vertices[i].position);
    }
    _aabb.updateMinMax(&pos[0],pos.size());
}

void Terrain::Chunk::calculateSlope()
{
    //find max slope
    auto lowest = vertices[0].position;
    for(int i = 0;i<vertices.size();i++)
    {
        if(vertices[i].position.y< lowest.y)
        {
            lowest = vertices[i].position;
        }
    }
    auto highest = vertices[0].position;
    for(int i = 0;i<vertices.size();i++)
    {
        if(vertices[i].position.y> highest.y)
        {
            highest = vertices[i].position;
        }
    }
    auto a = Vec2(lowest.x,lowest.z);
    auto b = Vec2(highest.x,highest.z);
    float dist = a.distance(b);
    slope = (highest.y - lowest.y)/dist;
}

void Terrain::Chunk::updateVerticesForLOD()
{
    vertices_tmp = vertices;
    int gridY = _size.height;
    int gridX = _size.width;

    if(_currentLod>=2 && abs(slope)>1.2)
    {
        int step = int(powf(2.0f, float(_currentLod)));
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
                        float weight = (step/2 - abs(n-i))*(step/2 - abs(m-j));
                        height += vertices[m*(gridX+1)+n].position.y;
                        count += weight;
                    }
                }
                vertices_tmp[i*(gridX+1)+j].position.y = height/count;
            }
    }

    glBufferData(GL_ARRAY_BUFFER, sizeof(TerrainVertexData)*vertices_tmp.size(), &vertices_tmp[0], GL_STREAM_DRAW);

}

Terrain::Chunk::~Chunk()
{
    glDeleteBuffers(2,vbo);
}

Terrain::QuadTree::QuadTree(int x,int y,int width,int height,Terrain * terrain)
{
    _needDraw = true;
    parent = nullptr;
    tl =nullptr;
    tr =nullptr;
    bl =nullptr;
    br =nullptr;
    pos_x = x;
    pos_y = y;
    this->height = height;
    this->width = width;
    if(width> terrain->_chunkSize.width &&height >terrain->_chunkSize.height) //subdivision
    {
        _isTerminal = false;
        this->tl = new QuadTree(x,y,width/2,height/2,terrain);
        this->tl->parent = this;
        this->tr = new QuadTree(x+width/2,y,width/2,height/2,terrain);
        this->tr->parent = this;
        this->bl = new QuadTree(x,y+height/2,width/2,height/2,terrain);
        this->bl->parent = this;
        this->br = new QuadTree(x+width/2,y+height/2,width/2,height/2,terrain);
        this->br->parent = this;

        _aabb.merge(tl->_aabb);
        _aabb.merge(tr->_aabb);
        _aabb.merge(bl->_aabb);
        _aabb.merge(br->_aabb);
    }else // is terminal Node
    {
        int m = pos_y/terrain->_chunkSize.height;
        int n = pos_x/terrain->_chunkSize.width;
        _chunk = terrain->_chunkesArray[m][n];
        _isTerminal = true;
        _aabb = _chunk->_aabb;
    }
}

void Terrain::QuadTree::draw()
{
    if(!_needDraw)return;
    if(_isTerminal){
        this->_chunk->bindAndDraw();
    }else
    {
        this->tl->draw();
        this->tr->draw();
        this->br->draw();
        this->bl->draw();
    }
}

void Terrain::QuadTree::resetNeedDraw(bool value)
{
    this->_needDraw = value;
    if(!_isTerminal)
    {
        tl->resetNeedDraw(value);
        tr->resetNeedDraw(value);
        bl->resetNeedDraw(value);
        br->resetNeedDraw(value);
    }
}

void Terrain::QuadTree::cullByCamera(const Camera * camera,const Mat4 & worldTransform)
{
    auto aabb = _aabb;
    aabb.transform(worldTransform);
    if(!camera->isVisibleInFrustum(&aabb))
    {
        this->resetNeedDraw(false);
    }else
    {
        if(!_isTerminal){
            tl->cullByCamera(camera,worldTransform);
            tr->cullByCamera(camera,worldTransform);
            bl->cullByCamera(camera,worldTransform);
            br->cullByCamera(camera,worldTransform);
        }
    }
}

Terrain::TerrainData::TerrainData(const char * heightMapsrc ,const char * textureSrc,const Size & chunksize,float mapHeight,float mapScale)
{ 
    this->heightMapSrc = heightMapsrc;
    this->detailMaps[0].detailMapSrc = textureSrc;
    this->alphaMapSrc = nullptr;
    this->chunkSize = chunksize;
    this->mapHeight = mapHeight;
    this->mapScale = mapScale; 
}

Terrain::TerrainData::TerrainData(const char * heightMapsrc ,const char * alphamap,const DetailMap& detail1,const DetailMap& detail2,const DetailMap& detail3,const DetailMap& detail4,const Size & chunksize,float mapHeight,float mapScale)
{
    this->heightMapSrc = heightMapsrc;
    this->alphaMapSrc = const_cast<char *>(alphamap);
    this->detailMaps[0] = detail1;
    this->detailMaps[1] = detail2;
    this->detailMaps[2] = detail3;
    this->detailMaps[3] = detail4;
    this->chunkSize = chunksize;
    this->mapHeight = mapHeight;
    this->mapScale = mapScale;
    _detailMapAmount = 4;
}

Terrain::TerrainData::TerrainData(const char* heightMapsrc ,const char * alphamap,const DetailMap& detail1,const DetailMap& detail2,const DetailMap& detail3,const Size & chunksize /*= Size(32,32)*/,float mapHeight /*= 2*/,float mapScale /*= 0.1*/)
{
    this->heightMapSrc = heightMapsrc;
    this->alphaMapSrc = const_cast<char *>(alphamap);
    this->detailMaps[0] = detail1;
    this->detailMaps[1] = detail2;
    this->detailMaps[2] = detail3;
    this->detailMaps[3] = nullptr;
    this->chunkSize = chunksize;
    this->mapHeight = mapHeight;
    this->mapScale = mapScale;
    _detailMapAmount = 3;
}

Terrain::TerrainData::TerrainData()
{

}

Terrain::DetailMap::DetailMap(const char * detailMapSrc , float size /*= 35*/)
{
    this->detailMapSrc = detailMapSrc;
    this->detailMapSize = size;
}

Terrain::DetailMap::DetailMap()
{
    detailMapSrc = ""; 
    detailMapSize = 35;
}
NS_CC_END
