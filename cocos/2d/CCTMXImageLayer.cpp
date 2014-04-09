/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2009-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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
#include "CCTMXImageLayer.h"
#include "CCTMXXMLParser.h"
#include "CCTMXObjectGroup.h"
#include "CCSprite.h"
#include "CCDirector.h"

NS_CC_BEGIN


// TMXImageLayer - init & alloc & dealloc

TMXImageLayer* TMXImageLayer::create(
    TMXImageLayerInfo*  imageLayerInfo,
    TMXMapInfo*         mapInfo
) {
    TMXImageLayer* ret = new TMXImageLayer();
    if ( ret->init( imageLayerInfo, mapInfo ) )
    {
        ret->autorelease();
        return ret;
    }
    return nullptr;
}


bool TMXImageLayer::init( TMXImageLayerInfo* imageLayerInfo, TMXMapInfo* mapInfo )
{   
    CCASSERT( !imageLayerInfo->_sourceImage.empty(),
        "Background file is absent." );

    Sprite*     sprite  = nullptr;
    Texture2D*  texture = nullptr;
    if ( imageLayerInfo )
    {
        sprite = Sprite::create( imageLayerInfo->_sourceImage.c_str() );
        CCASSERT( sprite, "Background file is not loaded." );
        sprite->setAnchorPoint( Point::ZERO );
        texture = sprite->getTexture();
    }

    if ( SpriteBatchNode::initWithTexture( texture, 1 ) )
    {
        // imageLayerInfo
        _name = imageLayerInfo->_name;
        _layerSize = imageLayerInfo->_layerSize;
        setProperties( imageLayerInfo->getProperties() );
        _contentScaleFactor = Director::getInstance()->getContentScaleFactor(); 

        // mapInfo
        _mapTileSize = mapInfo->getTileSize();
        _orientation = mapInfo->getOrientation();

        // # Size of imagelayer always = size of image source.
        const Size s = texture->getContentSize();
        setContentSize( CC_SIZE_PIXELS_TO_POINTS( s ) );

        // final configure texture
        _textureAtlas->getTexture()->setAliasTexParameters();
        insertQuadFromSprite( sprite, 0 );

        return true;
    }

    return false;
}


TMXImageLayer::TMXImageLayer():
      _layerSize( Size::ZERO )
    , _mapTileSize( Size::ZERO )
    , _properties()
    , _name( "" )
{}


TMXImageLayer::~TMXImageLayer()
{
}


void TMXImageLayer::addChild( Node* child, int zOrder, int tag )
{
    CC_UNUSED_PARAM( child );
    CC_UNUSED_PARAM( zOrder );
    CC_UNUSED_PARAM( tag );
    CCASSERT( false, "addChild: is not supported on TMXImageLayer.");
}


void TMXImageLayer::removeChild( Node* node, bool cleanup )
{
    Sprite* sprite = (Sprite*)node;
    // allows removing null-objects
    if ( !sprite )
    {
        return;
    }

    CCASSERT( _children.contains( sprite ), "Tile does not belong to TMXImageLayer" );
    SpriteBatchNode::removeChild( sprite, cleanup );
}


NS_CC_END
