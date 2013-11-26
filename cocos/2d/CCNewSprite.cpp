//
//  CCNewSprite.cpp
//  cocos2d_libs
//
//  Created by NiTe Luo on 10/31/13.
//
//

#include "CCNewSprite.h"
#include "RenderCommand.h"
#include "Renderer.h"
#include "QuadCommand.h"
#include "CCMenuItem.h"

NS_CC_BEGIN

#if CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
#define RENDER_IN_SUBPIXEL
#else
#define RENDER_IN_SUBPIXEL(__ARGS__) (ceil(__ARGS__))
#endif

NewSprite* NewSprite::create()
{
    NewSprite* sprite = new NewSprite();
    if(sprite && sprite->init())
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

NewSprite* NewSprite::create(const char *filename)
{
    NewSprite* sprite = new NewSprite();
    if(sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

NewSprite::NewSprite()
:Sprite()
{

}

NewSprite::~NewSprite(void)
{
}

bool NewSprite::initWithTexture(Texture2D *texture, const Rect &rect, bool rotated)
{
    bool result = Sprite::initWithTexture(texture, rect, rotated);
    _recursiveDirty = true;
    setDirty(true);
    return result;
}

void NewSprite::updateQuadVerties()
{

#ifdef CC_USE_PHYSICS
    updatePhysicsTransform();
    setDirty(true);
#endif

    //TODO optimize the performance cache affineTransformation

    // recalculate matrix only if it is dirty
    if(isDirty())
    {

//        if( ! _parent || _parent == (Node*)_batchNode )
//        {
//            _transformToBatch = getNodeToParentTransform();
//        }
//        else
//        {
//            CCASSERT( dynamic_cast<NewSprite*>(_parent), "Logic error in Sprite. Parent must be a Sprite");
//            _transformToBatch = AffineTransformConcat( getNodeToParentTransform() , static_cast<NewSprite*>(_parent)->_transformToBatch );
//        }
        
        //TODO optimize this transformation, should use parent's transformation instead
        _transformToBatch = getNodeToWorldTransform();
        
        //
        // calculate the Quad based on the Affine Matrix
        //
        
        Size size = _rect.size;
        
        float x1 = _offsetPosition.x;
        float y1 = _offsetPosition.y;
        
        float x2 = x1 + size.width;
        float y2 = y1 + size.height;
        float x = _transformToBatch.tx;
        float y = _transformToBatch.ty;
        
        float cr = _transformToBatch.a;
        float sr = _transformToBatch.b;
        float cr2 = _transformToBatch.d;
        float sr2 = -_transformToBatch.c;
        float ax = x1 * cr - y1 * sr2 + x;
        float ay = x1 * sr + y1 * cr2 + y;
        
        float bx = x2 * cr - y1 * sr2 + x;
        float by = x2 * sr + y1 * cr2 + y;
        
        float cx = x2 * cr - y2 * sr2 + x;
        float cy = x2 * sr + y2 * cr2 + y;
        
        float dx = x1 * cr - y2 * sr2 + x;
        float dy = x1 * sr + y2 * cr2 + y;
        
        _quad.bl.vertices = Vertex3F( RENDER_IN_SUBPIXEL(ax), RENDER_IN_SUBPIXEL(ay), _vertexZ );
        _quad.br.vertices = Vertex3F( RENDER_IN_SUBPIXEL(bx), RENDER_IN_SUBPIXEL(by), _vertexZ );
        _quad.tl.vertices = Vertex3F( RENDER_IN_SUBPIXEL(dx), RENDER_IN_SUBPIXEL(dy), _vertexZ );
        _quad.tr.vertices = Vertex3F( RENDER_IN_SUBPIXEL(cx), RENDER_IN_SUBPIXEL(cy), _vertexZ );

        _recursiveDirty = false;
        setDirty(false);
    }
}

void NewSprite::draw(void)
{
    updateQuadVerties();
    //TODO implement z order
    QuadCommand* renderCommand = new QuadCommand(0, _vertexZ, _texture->getName(), _shaderProgram, _blendFunc, &_quad, 1);

    Renderer::getInstance()->addCommand(renderCommand);
}

NS_CC_END