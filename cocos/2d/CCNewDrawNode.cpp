//
// Created by NiTe Luo on 11/14/13.
//


#include "CCNewDrawNode.h"
#include "QuadCommand.h"
#include "Renderer.h"

NS_CC_BEGIN

NewDrawNode *NewDrawNode::create()
{
    NewDrawNode* pRet = new NewDrawNode();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

NewDrawNode::NewDrawNode()
{

}

NewDrawNode::~NewDrawNode()
{

}

bool NewDrawNode::init()
{
    return DrawNode::init();
}

void NewDrawNode::updateTransform()
{
    if(_dirty && _visible)
    {
        //TODO optimize this transformation, should use parent's transformation instead
        AffineTransform _transformToBatch = getNodeToWorldTransform();

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
    }

    _recursiveDirty = false;
    setDirty(false);
}

void NewDrawNode::draw()
{
    updateTransform();

//    QuadCommand* quadCommand = new QuadCommand(0, _vertexZ, CC_NO_TEXTURE, _shaderProgram, _blendFunc, &_quads, _bufferCount);
//    Renderer::getInstance()->
}

NS_CC_END