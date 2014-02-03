/****************************************************************************
Copyright (c) 2009      On-Core
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (C) 2013-2014 Chukong Technologies Inc. 
 
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
#include "ccMacros.h"
#include "CCGrid.h"
#include "CCDirector.h"
#include "CCGrabber.h"
#include "ccUtils.h"
#include "CCGLProgram.h"
#include "CCShaderCache.h"
#include "ccGLStateCache.h"
#include "CCGL.h"
#include "TransformUtils.h"
#include "kazmath/kazmath.h"
#include "kazmath/GL/matrix.h"

NS_CC_BEGIN
// implementation of GridBase

GridBase* GridBase::create(const Size& gridSize)
{
    GridBase *pGridBase = new GridBase();

    if (pGridBase)
    {
        if (pGridBase->initWithSize(gridSize))
        {
            pGridBase->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pGridBase);
        }
    }

    return pGridBase;
}

GridBase* GridBase::create(const Size& gridSize, Texture2D *texture, bool flipped)
{
    GridBase *pGridBase = new GridBase();

    if (pGridBase)
    {
        if (pGridBase->initWithSize(gridSize, texture, flipped))
        {
            pGridBase->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pGridBase);
        }
    }

    return pGridBase;
}

bool GridBase::initWithSize(const Size& gridSize, Texture2D *texture, bool flipped)
{
    bool ret = true;

    _active = false;
    _reuseGrid = 0;
    _gridSize = gridSize;

    _texture = texture;
    CC_SAFE_RETAIN(_texture);
    _isTextureFlipped = flipped;

    Size texSize = _texture->getContentSize();
    _step.x = texSize.width / _gridSize.width;
    _step.y = texSize.height / _gridSize.height;

    _grabber = new Grabber();
    if (_grabber)
    {
        _grabber->grab(_texture);
    }
    else
    {
        ret = false;
    }
    
    _shaderProgram = ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE);
    calculateVertexPoints();

    return ret;
}

bool GridBase::initWithSize(const Size& gridSize)
{
    Director *director = Director::getInstance();
    Size s = director->getWinSizeInPixels();
    
    auto POTWide = ccNextPOT((unsigned int)s.width);
    auto POTHigh = ccNextPOT((unsigned int)s.height);

    // we only use rgba8888
    Texture2D::PixelFormat format = Texture2D::PixelFormat::RGBA8888;

    auto dataLen = POTWide * POTHigh * 4;
    void *data = calloc(dataLen, 1);
    if (! data)
    {
        CCLOG("cocos2d: Grid: not enough memory.");
        this->release();
        return false;
    }

    Texture2D *texture = new Texture2D();
    texture->initWithData(data, dataLen,  format, POTWide, POTHigh, s);

    free(data);

    if (! texture)
    {
        CCLOG("cocos2d: Grid: error creating texture");
        return false;
    }

    initWithSize(gridSize, texture, false);

    texture->release();

    return true;
}

GridBase::~GridBase(void)
{
    CCLOGINFO("deallocing GridBase: %p", this);

//TODO: ? why 2.0 comments this line        setActive(false);
    CC_SAFE_RELEASE(_texture);
    CC_SAFE_RELEASE(_grabber);
}

// properties
void GridBase::setActive(bool active)
{
    _active = active;
    if (! active)
    {
        Director *pDirector = Director::getInstance();
        Director::Projection proj = pDirector->getProjection();
        pDirector->setProjection(proj);
    }
}

void GridBase::setTextureFlipped(bool flipped)
{
    if (_isTextureFlipped != flipped)
    {
        _isTextureFlipped = flipped;
        calculateVertexPoints();
    }
}

void GridBase::set2DProjection()
{
    Director *director = Director::getInstance();

    Size    size = director->getWinSizeInPixels();

    glViewport(0, 0, (GLsizei)(size.width), (GLsizei)(size.height) );
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLLoadIdentity();

    kmMat4 orthoMatrix;
    kmMat4OrthographicProjection(&orthoMatrix, 0, size.width, 0, size.height, -1, 1);
    kmGLMultMatrix( &orthoMatrix );

    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLLoadIdentity();

    GL::setProjectionMatrixDirty();
}

void GridBase::beforeDraw(void)
{
    // save projection
    Director *director = Director::getInstance();
    _directorProjection = director->getProjection();

    // 2d projection
    //    [director setProjection:Director::Projection::_2D];
    set2DProjection();
    _grabber->beforeRender(_texture);
}

void GridBase::afterDraw(cocos2d::Node *target)
{
    _grabber->afterRender(_texture);

    // restore projection
    Director *director = Director::getInstance();
    director->setProjection(_directorProjection);

//    if (target->getCamera()->isDirty())
//    {
//        Point offset = target->getAnchorPointInPoints();
//
//        //
//        // XXX: Camera should be applied in the AnchorPoint
//        //
//        kmGLTranslatef(offset.x, offset.y, 0);
//        target->getCamera()->locate();
//        kmGLTranslatef(-offset.x, -offset.y, 0);
//    }

    GL::bindTexture2D(_texture->getName());

    // restore projection for default FBO .fixed bug #543 #544
//TODO:         Director::getInstance()->setProjection(Director::getInstance()->getProjection());
//TODO:         Director::getInstance()->applyOrientation();
    blit();
}

void GridBase::blit(void)
{
    CCASSERT(0, "");
}

void GridBase::reuse(void)
{
    CCASSERT(0, "");
}

void GridBase::calculateVertexPoints(void)
{
    CCASSERT(0, "");
}

// implementation of Grid3D

Grid3D* Grid3D::create(const Size& gridSize, Texture2D *texture, bool flipped)
{
    Grid3D *ret= new Grid3D();

    if (ret)
    {
        if (ret->initWithSize(gridSize, texture, flipped))
        {
            ret->autorelease();
        }
        else
        {
            delete ret;
            ret = nullptr;
        }
    }

    return ret;
}

Grid3D* Grid3D::create(const Size& gridSize)
{
    Grid3D *ret= new Grid3D();

    if (ret)
    {
        if (ret->initWithSize(gridSize))
        {
            ret->autorelease();
        }
        else
        {
            delete ret;
            ret = nullptr;
        }
    }

    return ret;
}


Grid3D::Grid3D()
    : _texCoordinates(nullptr)
    , _vertices(nullptr)
    , _originalVertices(nullptr)
    , _indices(nullptr)
{

}

Grid3D::~Grid3D(void)
{
    CC_SAFE_FREE(_texCoordinates);
    CC_SAFE_FREE(_vertices);
    CC_SAFE_FREE(_indices);
    CC_SAFE_FREE(_originalVertices);
}

void Grid3D::blit(void)
{
    int n = _gridSize.width * _gridSize.height;

    GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_TEX_COORDS );
    _shaderProgram->use();
    _shaderProgram->setUniformsForBuiltins();;

    //
    // Attributes
    //
#ifdef EMSCRIPTEN
    // Size calculations from calculateVertexPoints().
    unsigned int numOfPoints = (_gridSize.width+1) * (_gridSize.height+1);

    // position
    setGLBufferData(_vertices, numOfPoints * sizeof(Vertex3F), 0);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // texCoords
    setGLBufferData(_texCoordinates, numOfPoints * sizeof(Vertex2F), 1);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, 0, 0);

    setGLIndexData(_indices, n * 12, 0);
    glDrawElements(GL_TRIANGLES, (GLsizei) n*6, GL_UNSIGNED_SHORT, 0);
#else
    // position
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, _vertices);

    // texCoords
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, 0, _texCoordinates);

    glDrawElements(GL_TRIANGLES, (GLsizei) n*6, GL_UNSIGNED_SHORT, _indices);
#endif // EMSCRIPTEN
    CC_INCREMENT_GL_DRAWS(1);
}

void Grid3D::calculateVertexPoints(void)
{
    float width = (float)_texture->getPixelsWide();
    float height = (float)_texture->getPixelsHigh();
    float imageH = _texture->getContentSizeInPixels().height;

    int x, y, i;
    CC_SAFE_FREE(_vertices);
    CC_SAFE_FREE(_originalVertices);
    CC_SAFE_FREE(_texCoordinates);
    CC_SAFE_FREE(_indices);

    unsigned int numOfPoints = (_gridSize.width+1) * (_gridSize.height+1);

    _vertices = malloc(numOfPoints * sizeof(Vertex3F));
    _originalVertices = malloc(numOfPoints * sizeof(Vertex3F));
    _texCoordinates = malloc(numOfPoints * sizeof(Vertex2F));
    _indices = (GLushort*)malloc(_gridSize.width * _gridSize.height * sizeof(GLushort) * 6);

    GLfloat *vertArray = (GLfloat*)_vertices;
    GLfloat *texArray = (GLfloat*)_texCoordinates;
    GLushort *idxArray = _indices;

    for (x = 0; x < _gridSize.width; ++x)
    {
        for (y = 0; y < _gridSize.height; ++y)
        {
            int idx = (y * _gridSize.width) + x;

            GLfloat x1 = x * _step.x;
            GLfloat x2 = x1 + _step.x;
            GLfloat y1 = y * _step.y;
            GLfloat y2= y1 + _step.y;

            GLushort a = (GLushort)(x * (_gridSize.height + 1) + y);
            GLushort b = (GLushort)((x + 1) * (_gridSize.height + 1) + y);
            GLushort c = (GLushort)((x + 1) * (_gridSize.height + 1) + (y + 1));
            GLushort d = (GLushort)(x * (_gridSize.height + 1) + (y + 1));

            GLushort tempidx[6] = {a, b, d, b, c, d};

            memcpy(&idxArray[6*idx], tempidx, 6*sizeof(GLushort));

            int l1[4] = {a*3, b*3, c*3, d*3};
            Vertex3F e(x1, y1, 0);
            Vertex3F f(x2, y1, 0);
            Vertex3F g(x2, y2, 0);
            Vertex3F h(x1, y2, 0);

            Vertex3F l2[4] = {e, f, g, h};

            int tex1[4] = {a*2, b*2, c*2, d*2};
            Point Tex2F[4] = {Point(x1, y1), Point(x2, y1), Point(x2, y2), Point(x1, y2)};

            for (i = 0; i < 4; ++i)
            {
                vertArray[l1[i]] = l2[i].x;
                vertArray[l1[i] + 1] = l2[i].y;
                vertArray[l1[i] + 2] = l2[i].z;

                texArray[tex1[i]] = Tex2F[i].x / width;
                if (_isTextureFlipped)
                {
                    texArray[tex1[i] + 1] = (imageH - Tex2F[i].y) / height;
                }
                else
                {
                    texArray[tex1[i] + 1] = Tex2F[i].y / height;
                }
            }
        }
    }

    memcpy(_originalVertices, _vertices, (_gridSize.width+1) * (_gridSize.height+1) * sizeof(Vertex3F));
}

Vertex3F Grid3D::getVertex(const Point& pos) const
{
    CCASSERT( pos.x == (unsigned int)pos.x && pos.y == (unsigned int) pos.y , "Numbers must be integers");
    
    int index = (pos.x * (_gridSize.height+1) + pos.y) * 3;
    float *vertArray = (float*)_vertices;

    Vertex3F vert(vertArray[index], vertArray[index+1], vertArray[index+2]);

    return vert;
}

Vertex3F Grid3D::getOriginalVertex(const Point& pos) const
{
    CCASSERT( pos.x == (unsigned int)pos.x && pos.y == (unsigned int) pos.y , "Numbers must be integers");
    
    int index = (pos.x * (_gridSize.height+1) + pos.y) * 3;
    float *vertArray = (float*)_originalVertices;

    Vertex3F vert(vertArray[index], vertArray[index+1], vertArray[index+2]);

    return vert;
}

void Grid3D::setVertex(const Point& pos, const Vertex3F& vertex)
{
    CCASSERT( pos.x == (unsigned int)pos.x && pos.y == (unsigned int) pos.y , "Numbers must be integers");
    int index = (pos.x * (_gridSize.height + 1) + pos.y) * 3;
    float *vertArray = (float*)_vertices;
    vertArray[index] = vertex.x;
    vertArray[index+1] = vertex.y;
    vertArray[index+2] = vertex.z;
}

void Grid3D::reuse(void)
{
    if (_reuseGrid > 0)
    {
        memcpy(_originalVertices, _vertices, (_gridSize.width+1) * (_gridSize.height+1) * sizeof(Vertex3F));
        --_reuseGrid;
    }
}

// implementation of TiledGrid3D

TiledGrid3D::TiledGrid3D()
    : _texCoordinates(nullptr)
    , _vertices(nullptr)
    , _originalVertices(nullptr)
    , _indices(nullptr)
{

}

TiledGrid3D::~TiledGrid3D(void)
{
    CC_SAFE_FREE(_texCoordinates);
    CC_SAFE_FREE(_vertices);
    CC_SAFE_FREE(_originalVertices);
    CC_SAFE_FREE(_indices);
}

TiledGrid3D* TiledGrid3D::create(const Size& gridSize, Texture2D *texture, bool flipped)
{
    TiledGrid3D *ret= new TiledGrid3D();

    if (ret)
    {
        if (ret->initWithSize(gridSize, texture, flipped))
        {
            ret->autorelease();
        }
        else
        {
            delete ret;
            ret = nullptr;
        }
    }

    return ret;
}

TiledGrid3D* TiledGrid3D::create(const Size& gridSize)
{
    TiledGrid3D *ret= new TiledGrid3D();

    if (ret)
    {
        if (ret->initWithSize(gridSize))
        {
            ret->autorelease();
        }
        else
        {
            delete ret;
            ret = nullptr;
        }
    }

    return ret;
}

void TiledGrid3D::blit(void)
{
    int n = _gridSize.width * _gridSize.height;

    
    _shaderProgram->use();
    _shaderProgram->setUniformsForBuiltins();

    //
    // Attributes
    //
    GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_TEX_COORDS );
#ifdef EMSCRIPTEN
    int numQuads = _gridSize.width * _gridSize.height;

    // position
    setGLBufferData(_vertices, (numQuads*4*sizeof(Vertex3F)), 0);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // texCoords
    setGLBufferData(_texCoordinates, (numQuads*4*sizeof(Vertex2F)), 1);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, 0, 0);

    setGLIndexData(_indices, n * 12, 0);
    glDrawElements(GL_TRIANGLES, (GLsizei) n*6, GL_UNSIGNED_SHORT, 0);
#else
    // position
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, _vertices);

    // texCoords
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, 0, _texCoordinates);

    glDrawElements(GL_TRIANGLES, (GLsizei)n*6, GL_UNSIGNED_SHORT, _indices);
#endif // EMSCRIPTEN


    CC_INCREMENT_GL_DRAWS(1);
}

void TiledGrid3D::calculateVertexPoints(void)
{
    float width = (float)_texture->getPixelsWide();
    float height = (float)_texture->getPixelsHigh();
    float imageH = _texture->getContentSizeInPixels().height;
    
    int numQuads = _gridSize.width * _gridSize.height;
    CC_SAFE_FREE(_vertices);
    CC_SAFE_FREE(_originalVertices);
    CC_SAFE_FREE(_texCoordinates);
    CC_SAFE_FREE(_indices);

    _vertices = malloc(numQuads*4*sizeof(Vertex3F));
    _originalVertices = malloc(numQuads*4*sizeof(Vertex3F));
    _texCoordinates = malloc(numQuads*4*sizeof(Vertex2F));
    _indices = (GLushort*)malloc(numQuads*6*sizeof(GLushort));

    GLfloat *vertArray = (GLfloat*)_vertices;
    GLfloat *texArray = (GLfloat*)_texCoordinates;
    GLushort *idxArray = _indices;
    
    int x, y;
    
    for( x = 0; x < _gridSize.width; x++ )
    {
        for( y = 0; y < _gridSize.height; y++ )
        {
            float x1 = x * _step.x;
            float x2 = x1 + _step.x;
            float y1 = y * _step.y;
            float y2 = y1 + _step.y;
            
            *vertArray++ = x1;
            *vertArray++ = y1;
            *vertArray++ = 0;
            *vertArray++ = x2;
            *vertArray++ = y1;
            *vertArray++ = 0;
            *vertArray++ = x1;
            *vertArray++ = y2;
            *vertArray++ = 0;
            *vertArray++ = x2;
            *vertArray++ = y2;
            *vertArray++ = 0;
            
            float newY1 = y1;
            float newY2 = y2;
            
            if (_isTextureFlipped) 
            {
                newY1 = imageH - y1;
                newY2 = imageH - y2;
            }

            *texArray++ = x1 / width;
            *texArray++ = newY1 / height;
            *texArray++ = x2 / width;
            *texArray++ = newY1 / height;
            *texArray++ = x1 / width;
            *texArray++ = newY2 / height;
            *texArray++ = x2 / width;
            *texArray++ = newY2 / height;
        }
    }
    
    for (x = 0; x < numQuads; x++)
    {
        idxArray[x*6+0] = (GLushort)(x * 4 + 0);
        idxArray[x*6+1] = (GLushort)(x * 4 + 1);
        idxArray[x*6+2] = (GLushort)(x * 4 + 2);
        
        idxArray[x*6+3] = (GLushort)(x * 4 + 1);
        idxArray[x*6+4] = (GLushort)(x * 4 + 2);
        idxArray[x*6+5] = (GLushort)(x * 4 + 3);
    }
    
    memcpy(_originalVertices, _vertices, numQuads * 12 * sizeof(GLfloat));
}

void TiledGrid3D::setTile(const Point& pos, const Quad3& coords)
{
    CCASSERT( pos.x == (unsigned int)pos.x && pos.y == (unsigned int) pos.y , "Numbers must be integers");
    int idx = (_gridSize.height * pos.x + pos.y) * 4 * 3;
    float *vertArray = (float*)_vertices;
    memcpy(&vertArray[idx], &coords, sizeof(Quad3));
}

Quad3 TiledGrid3D::getOriginalTile(const Point& pos) const
{
    CCASSERT( pos.x == (unsigned int)pos.x && pos.y == (unsigned int) pos.y , "Numbers must be integers");
    int idx = (_gridSize.height * pos.x + pos.y) * 4 * 3;
    float *vertArray = (float*)_originalVertices;

    Quad3 ret;
    memcpy(&ret, &vertArray[idx], sizeof(Quad3));

    return ret;
}

Quad3 TiledGrid3D::getTile(const Point& pos) const
{
    CCASSERT( pos.x == (unsigned int)pos.x && pos.y == (unsigned int) pos.y , "Numbers must be integers");
    int idx = (_gridSize.height * pos.x + pos.y) * 4 * 3;
    float *vertArray = (float*)_vertices;

    Quad3 ret;
    memcpy(&ret, &vertArray[idx], sizeof(Quad3));

    return ret;
}

void TiledGrid3D::reuse(void)
{
    if (_reuseGrid > 0)
    {
        int numQuads = _gridSize.width * _gridSize.height;

        memcpy(_originalVertices, _vertices, numQuads * 12 * sizeof(GLfloat));
        --_reuseGrid;
    }
}

NS_CC_END
