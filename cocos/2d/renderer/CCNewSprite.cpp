//
//  CCNewSprite.cpp
//  cocos2d_libs
//
//  Created by NiTe Luo on 10/31/13.
//
//

#include "CCNewSprite.h"
#include "Renderer.h"
#include "Frustum.h"
#include "CCDirector.h"
#include "QuadCommand.h"

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

void NewSprite::updateQuadVertices()
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
        Rect newRect = RectApplyTransform(_rect, _transformToBatch);

        _quad.bl.vertices = Vertex3F( RENDER_IN_SUBPIXEL(newRect.getMinX()), RENDER_IN_SUBPIXEL(newRect.getMinY()), _vertexZ );
        _quad.br.vertices = Vertex3F( RENDER_IN_SUBPIXEL(newRect.getMaxX()), RENDER_IN_SUBPIXEL(newRect.getMinY()), _vertexZ );
        _quad.tl.vertices = Vertex3F( RENDER_IN_SUBPIXEL(newRect.getMinX()), RENDER_IN_SUBPIXEL(newRect.getMaxY()), _vertexZ );
        _quad.tr.vertices = Vertex3F( RENDER_IN_SUBPIXEL(newRect.getMaxX()), RENDER_IN_SUBPIXEL(newRect.getMaxY()), _vertexZ );

        _recursiveDirty = false;
        setDirty(false);
    }
}

void NewSprite::draw(void)
{
    kmMat4 mv;
    kmGLGetMatrix(KM_GL_MODELVIEW, &mv);
    //TODO implement z order
    QuadCommand* renderCommand = QuadCommand::getCommandPool().generateCommand();
    renderCommand->init(0, _vertexZ, _texture->getName(), _shaderProgram, _blendFunc, &_quad, 1, mv);

    if(!culling())
    {
        renderCommand->releaseToCommandPool();
        return;
    }

    Director::getInstance()->getRenderer()->addCommand(renderCommand);
}

bool NewSprite::culling() const
{
    Frustum* frustum = Director::getInstance()->getFrustum();
    //TODO optimize this transformation, should use parent's transformation instead
    kmMat4 worldTM = getNodeToWorldTransform();
    //generate aabb

    //
    // calculate the Quad based on the Affine Matrix
    //
    Rect newRect = RectApplyTransform(_rect, worldTM);

    kmVec3 point = {newRect.getMinX(), newRect.getMinY(), _vertexZ};
    
    AABB aabb(point,point);
    point = {newRect.getMaxX(), newRect.getMinY(), _vertexZ};
    aabb.expand(point);
    point = {newRect.getMinX(), newRect.getMaxY(), _vertexZ};
    aabb.expand(point);
    point = {newRect.getMaxX(), newRect.getMaxY(), _vertexZ};
    aabb.expand(point);
    
    return Frustum::IntersectResult::OUTSIDE !=frustum->intersectAABB(aabb);
}


NS_CC_END