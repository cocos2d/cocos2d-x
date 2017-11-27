/****************************************************************************
Copyright (c) 2013-2017 Chukong Technologies Inc.

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

#include "ui/UITileImageView.h"
#include "ui/UIScale9Sprite.h"
#include "ui/UIHelper.h"
#include "base/CCDirector.h"
#include "2d/CCSprite.h"
#include "editor-support/cocostudio/CocosStudioExtension.h"

NS_CC_BEGIN

namespace ui {
    
static const int IMAGE_RENDERER_Z = (-1);
    
IMPLEMENT_CLASS_GUI_INFO(TileImageView)

TileImageView::TileImageView():
_dirty(true),
_prevIgnoreSize(true),
_textureFile(""),
_imageRenderer(nullptr),
_imageTexType(TextureResType::LOCAL),
_imageTextureSize(_contentSize),
_imageRendererAdaptDirty(true),
_imageScale(1.0f)
{

}

TileImageView::~TileImageView()
{
    
}
    
TileImageView* TileImageView::create(const std::string &imageFileName, TextureResType texType)
{
    TileImageView *widget = new (std::nothrow) TileImageView;
    if (widget && widget->init(imageFileName, texType))
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

TileImageView* TileImageView::create()
{
    TileImageView* widget = new (std::nothrow) TileImageView();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}
    
bool TileImageView::init()
{
    bool ret = true;
    do
    {
        if (!Widget::init())
        {
            ret = false;
            break;
        }
        _imageTexType = TextureResType::LOCAL;
    } while (0);
    return ret;
}
    
bool TileImageView::init(const std::string &imageFileName, TextureResType texType)
{
    bool bRet = true;
    do
    {
        if (!Widget::init())
        {
            bRet = false;
            break;
        }
        
        this->loadTexture(imageFileName, texType);
    } while (0);
    return bRet;
}
    
void TileImageView::updatePoly()
{
    float u0, u1;
    float v0, v1;
    float uo, vo;
    
    Texture2D *tex = _imageRenderer->getTexture();
    if (tex == nullptr)
        return;
    
    const auto rectInPixels = _imageRenderer->getSpriteFrame()->getRectInPixels();
    
    const float atlasWidth = (float)tex->getPixelsWide();
    const float atlasHeight = (float)tex->getPixelsHigh();
    
    auto originalContentSize = _imageRenderer->getSpriteFrame()->getOriginalSize();
    
    auto originalSizeInPixels = _imageRenderer->getSpriteFrame()->getOriginalSizeInPixels();
    auto offsetInPixels = _imageRenderer->getSpriteFrame()->getOffsetInPixels();
    bool rectRotated = _imageRenderer->getSpriteFrame()->isRotated();
    
    Vec4 offsets;
    offsets.x = offsetInPixels.x + (originalSizeInPixels.width - rectInPixels.size.width) / 2;
    offsets.w = offsetInPixels.y + (originalSizeInPixels.height - rectInPixels.size.height) / 2;
    offsets.z = originalSizeInPixels.width - rectInPixels.size.width - offsets.x;
    offsets.y = originalSizeInPixels.height - rectInPixels.size.height - offsets.w;
    
    cocos2d::Director::getInstance()->getContentScaleFactor();
    
    if (rectRotated) {
        u0 = (rectInPixels.origin.x - offsets.w) / atlasWidth;
        u1 = (rectInPixels.origin.x + rectInPixels.size.height + offsets.y) / atlasWidth;
        
        v1 = (rectInPixels.origin.y - offsets.x) / atlasHeight;
        v0 = (rectInPixels.origin.y + rectInPixels.size.width + offsets.z) / atlasHeight;
        
        uo = offsets.x / atlasHeight;
        vo = offsets.w / atlasWidth;
    }
    else {
        u0 = (rectInPixels.origin.x - offsets.x) / atlasWidth;
        u1 = (rectInPixels.origin.x + rectInPixels.size.width + offsets.z) / atlasWidth;
        
        v1 = (rectInPixels.origin.y - offsets.y) / atlasHeight;
        v0 = (rectInPixels.origin.y + rectInPixels.size.height + offsets.w) / atlasHeight;
        
        uo = offsets.x / atlasWidth;
        vo = offsets.w / atlasHeight;
    }
    
    auto rectWidth = originalContentSize.width;
    auto rectHeight = originalContentSize.height;
    
    //build quads
    auto hRepeat = (getContentSize().width / _imageScale) / rectWidth;
    auto vRepeat = (getContentSize().height / _imageScale) / rectHeight;
    
    float offsetLeft = offsets.x / CC_CONTENT_SCALE_FACTOR();
    float offsetTop = offsets.y / CC_CONTENT_SCALE_FACTOR();
    float offsetRight = offsets.z / CC_CONTENT_SCALE_FACTOR();
    float offsetBottom = offsets.w / CC_CONTENT_SCALE_FACTOR();
    
    float roTop = offsetTop / rectHeight;
    float roBottom = offsetBottom / rectHeight;
    //float roLeft = offsetLeft / rectWidth;
    float roRight = offsetRight / rectWidth;
    
    
    const int vertsStep = 4;
    const int indicesStep = 6;
    int quadsCount = ceilf(hRepeat) * ceilf(vRepeat);
    
    unsigned short slicedTotalVertexCount = quadsCount * vertsStep;
    unsigned short slicedTotalIndices = quadsCount * indicesStep;
    
    V3F_C4B_T2F* sliceVertices = new (std::nothrow) V3F_C4B_T2F[quadsCount * vertsStep];
    
    int quadIndex = 0;
    for (int hindex = 0; hindex < ceilf(hRepeat); ++hindex) {
        for (int vindex = 0; vindex < ceilf(vRepeat); ++vindex) {
            
            V3F_C4B_T2F &quad_bl = sliceVertices[quadIndex];
            V3F_C4B_T2F &quad_br = sliceVertices[quadIndex + 1];
            V3F_C4B_T2F &quad_tl = sliceVertices[quadIndex + 2];
            V3F_C4B_T2F &quad_tr = sliceVertices[quadIndex + 3];
            
            quadIndex += vertsStep;
            
            quad_bl.colors = Color4B::WHITE;
            quad_br.colors = Color4B::WHITE;
            quad_tl.colors = Color4B::WHITE;
            quad_tr.colors = Color4B::WHITE;
            
            float x1 = rectWidth * hindex + offsetLeft;
            float y1 = rectHeight * vindex + offsetBottom;
            float x2 = rectWidth * fminf(hindex + (1 - roRight), hRepeat);
            float y2 = rectHeight * fminf(vindex + (1 - roTop), vRepeat);
            
            if(x2 < x1)
                x2 = x1;
            
            if(y2 < y1)
                y2 = y1;
            
            quad_bl.vertices = cocos2d::Vec3(x1, y1, 0);
            quad_br.vertices = cocos2d::Vec3(x2, y1, 0);
            quad_tl.vertices = cocos2d::Vec3(x1, y2, 0);
            quad_tr.vertices = cocos2d::Vec3(x2, y2, 0);
            
            if (!rectRotated) {
                quad_bl.texCoords = cocos2d::Tex2F(u0 + uo, v0 - vo);
                quad_br.texCoords = cocos2d::Tex2F(u0 + (u1 - u0) * fminf((1 - roRight), hRepeat - hindex), v0 - vo);
                quad_tl.texCoords = cocos2d::Tex2F(u0 + uo, v0 + (v1 - v0) * fminf((1 - roTop), vRepeat - vindex));
                quad_tr.texCoords = cocos2d::Tex2F(u0 + (u1 - u0) * fminf((1 - roRight), hRepeat - hindex), v0 + (v1 - v0) * fminf((1 - roTop), vRepeat - vindex));
            } else {
                quad_bl.texCoords = cocos2d::Tex2F(u0 + vo, v1 + uo);
                quad_br.texCoords = cocos2d::Tex2F(u0 + vo, v1 + (v0 - v1) * fminf((1 - roBottom), hRepeat - hindex));
                quad_tl.texCoords = cocos2d::Tex2F(u0 + (u1 - u0) * fminf((1 - roTop), vRepeat - vindex), v1 + uo);
                quad_tr.texCoords = cocos2d::Tex2F(u0 + (u1 - u0) * fminf((1 - roTop), vRepeat - vindex), v1 + (v0 - v1) * fminf((1 - roBottom), hRepeat - hindex));
                
            }
        }
    }
    
    unsigned short* sliceIndices = new (std::nothrow) unsigned short[slicedTotalIndices];
    
    unsigned short indices[indicesStep];
    for(int index = 0; index < quadsCount; ++index) {
        {
            indices[0] = vertsStep * index;
            indices[1] = vertsStep * index + 1;
            indices[2] = vertsStep * index + 2;
            indices[3] = vertsStep * index + 3;
            indices[4] = vertsStep * index + 2;
            indices[5] = vertsStep * index + 1;
        }
        
        memcpy(&sliceIndices[indicesStep * index], indices, sizeof(unsigned short) * indicesStep);
        
    }
    
    TrianglesCommand::Triangles triangles;
    triangles.vertCount = slicedTotalVertexCount;
    triangles.indexCount = slicedTotalIndices;
    triangles.verts = sliceVertices;
    triangles.indices = sliceIndices;
    
    PolygonInfo polygonInfo;
    polygonInfo.setTriangles(triangles);
    _imageRenderer->setPolygonInfo(polygonInfo);
    
    _imageRenderer->setColor(getDisplayedColor());
    _imageRenderer->setOpacity(getDisplayedOpacity());
}

void TileImageView::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    Widget::visit(renderer, parentTransform, parentFlags);
    if(_dirty)
    {
        updatePoly();
        _dirty = false;
    }
}

void TileImageView::initRenderer()
{
    _imageRenderer = Scale9Sprite::create();
    
    addProtectedChild(_imageRenderer, IMAGE_RENDERER_Z, -1);
}

void TileImageView::loadTexture(const std::string& fileName, TextureResType texType)
{
    if (fileName.empty())
    {
        return;
    }
    _textureFile = fileName;
    _imageTexType = texType;
    switch (_imageTexType)
    {
        case TextureResType::LOCAL:
            _imageRenderer->initWithFile(fileName);
            break;
        case TextureResType::PLIST:
            _imageRenderer->initWithSpriteFrameName(fileName);
            break;
        default:
            break;
    }
    //FIXME: https://github.com/cocos2d/cocos2d-x/issues/12249
    if (!_ignoreSize && _customSize.equals(Size::ZERO)) {
        _customSize = _imageRenderer->getContentSize();
    }
    this->setupTexture();
}

void TileImageView::loadTexture(SpriteFrame* spriteframe)
{
    _imageRenderer->initWithSpriteFrame(spriteframe);
    this->setupTexture();
}

void TileImageView::setupTexture()
{
    _imageTextureSize = _imageRenderer->getSpriteFrame()->getOriginalSize();
    _dirty = true;
    this->updateChildrenDisplayedRGBA();

    updateContentSizeWithTextureSize(_imageTextureSize  / _imageScale);
    _imageRendererAdaptDirty = true;
}

void TileImageView::ignoreContentAdaptWithSize(bool ignore)
{
    if (!ignore)
    {
        Widget::ignoreContentAdaptWithSize(ignore);
        _prevIgnoreSize = ignore;
    }
}

void TileImageView::onSizeChanged()
{
    Widget::onSizeChanged();
    _imageRendererAdaptDirty = true;
}
    
void TileImageView::adaptRenderers()
{
    if (_imageRendererAdaptDirty)
    {
        imageTextureScaleChangedWithSize();
        _imageRendererAdaptDirty = false;
    }
}

Size TileImageView::getVirtualRendererSize() const
{
    return _imageTextureSize;
}

Node* TileImageView::getVirtualRenderer()
{
    return _imageRenderer;
}

void TileImageView::imageTextureScaleChangedWithSize()
{
    _imageRenderer->setScale(_imageScale);
    _imageRenderer->setContentSize(_contentSize / _imageScale);
    _imageRenderer->setPosition(_contentSize.width / 2.0f, _contentSize.height / 2.0f);
}

std::string TileImageView::getDescription() const
{
    return "TileImageView";
}

Widget* TileImageView::createCloneInstance()
{
    return TileImageView::create();
}

void TileImageView::copySpecialProperties(Widget *widget)
{
    TileImageView* imageView = dynamic_cast<TileImageView*>(widget);
    if (imageView)
    {
        _prevIgnoreSize = imageView->_prevIgnoreSize;
        auto imageSprite = imageView->_imageRenderer;
        if(nullptr != imageSprite)
        {
            loadTexture(imageSprite->getSpriteFrame());
        }
        setImageScale(imageView->_imageScale);
    }
}

ResourceData TileImageView::getRenderFile()
{
    ResourceData rData;
    rData.type = (int)_imageTexType;
    rData.file = _textureFile;
    return rData;
}
    
void TileImageView::setGLProgram(GLProgram* glProgram)
{
    Widget::setGLProgram(glProgram);
    _imageRenderer->setGLProgram(glProgram);
}
    
void TileImageView::setGLProgramState(cocos2d::GLProgramState* glProgramState)
{
    Widget::setGLProgramState(glProgramState);
    _imageRenderer->setGLProgramState(glProgramState);
}
    
void TileImageView::setImageScale(float scale)
{
    if(_imageScale != scale)
    {
        _imageScale = scale;
        _imageRendererAdaptDirty = true;
    }
}

float TileImageView::getImageScale() const
{
    return _imageScale;
}

}

NS_CC_END
