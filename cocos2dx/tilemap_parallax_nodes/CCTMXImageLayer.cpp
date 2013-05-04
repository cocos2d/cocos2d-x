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
#include "sprite_nodes/CCSprite.h"
#include "textures/CCTextureCache.h"
#include "CCDirector.h"

NS_CC_BEGIN


// CCTMXImageLayer - init & alloc & dealloc

CCTMXImageLayer* CCTMXImageLayer::create( CCTMXImageLayerInfo* imageLayerInfo, CCTMXMapInfo* mapInfo )
{
    CCTMXImageLayer* pRet = new CCTMXImageLayer();
    if ( pRet->init( imageLayerInfo, mapInfo ) )
    {
        pRet->autorelease();
        return pRet;
    }
    return nullptr;
}


bool CCTMXImageLayer::init( CCTMXImageLayerInfo* imageLayerInfo, CCTMXMapInfo* mapInfo )
{   
    CCAssert( !imageLayerInfo->m_sSourceImage.empty(), "Background file is absent." );

    CCSprite*     sprite  = nullptr;
    CCTexture2D*  texture = nullptr;
    if ( imageLayerInfo )
    {
        sprite = CCSprite::create( imageLayerInfo->m_sSourceImage.c_str() );
        CCAssert( sprite, "Background file is not loaded." );
        sprite->setAnchorPoint( CCPointZero );
        texture = sprite->getTexture();
    }

    if ( CCSpriteBatchNode::initWithTexture( texture, 1 ) )
    {
        // imageLayerInfo
        m_sName = imageLayerInfo->m_sName;
        m_tSize = imageLayerInfo->m_tSize;
        setProperties( CCDictionary::createWithDictionary( imageLayerInfo->getProperties() ) );
        m_fContentScaleFactor = CCDirector::sharedDirector()->getContentScaleFactor(); 

        // mapInfo
        m_tMapTileSize = mapInfo->getTileSize();
        m_uOrientation = mapInfo->getOrientation();

        // # Size of imagelayer always = size of image source.
        const CCSize s = texture->getContentSize();
        setContentSize( CC_SIZE_PIXELS_TO_POINTS( s ) );

        // final configure texture
        m_pobTextureAtlas->getTexture()->setAliasTexParameters();
        insertQuadFromSprite( sprite, 0 );

        return true;
    }

    return false;
}


CCTMXImageLayer::CCTMXImageLayer():
      m_tSize( CCSizeZero )
    , m_tMapTileSize( CCSizeZero )
    , m_pProperties( nullptr )
    , m_sName( "" )
{}


CCTMXImageLayer::~CCTMXImageLayer()
{
    CC_SAFE_RELEASE(m_pProperties);
}


void CCTMXImageLayer::addChild( CCNode* child, int zOrder, int tag )
{
    CC_UNUSED_PARAM( child );
    CC_UNUSED_PARAM( zOrder );
    CC_UNUSED_PARAM( tag );
    CCAssert( false, "addChild: is not supported on CCTMXImageLayer.");
}


void CCTMXImageLayer::removeChild( CCNode* node, bool cleanup )
{
    CCSprite* sprite = (CCSprite*)node;
    // allows removing null-objects
    if ( !sprite )
    {
        return;
    }

    CCAssert( m_pChildren->containsObject( sprite ), "Tile does not belong to TMXImageLayer" );
    CCSpriteBatchNode::removeChild( sprite, cleanup );
}


CCTMXImageLayerInfo* CCTMXImageLayer::getInfo()
{
    return m_pInfo;
}


void CCTMXImageLayer::setInfo( CCTMXImageLayerInfo* var )
{
    CC_SAFE_RETAIN( var );
    CC_SAFE_RELEASE( m_pInfo );
    m_pInfo = var;
}


CCDictionary* CCTMXImageLayer::getProperties()
{
    return m_pProperties;
}


void CCTMXImageLayer::setProperties( CCDictionary* var )
{
    CC_SAFE_RETAIN( var );
    CC_SAFE_RELEASE( m_pProperties );
    m_pProperties = var;
}

NS_CC_END
