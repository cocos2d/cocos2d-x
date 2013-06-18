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
#include "CCTMXTiledMap.h"
#include "CCTMXXMLParser.h"
#include "CCTMXLayer.h"
#include "sprite_nodes/CCSprite.h"
#include "support/CCPointExtension.h"

NS_CC_BEGIN

// implementation CCTMXTiledMap

CCTMXTiledMap * CCTMXTiledMap::create(const char *tmxFile)
{
    CCTMXTiledMap *pRet = new CCTMXTiledMap();
    if (pRet->initWithTMXFile(tmxFile))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCTMXTiledMap* CCTMXTiledMap::createWithXML(const char* tmxString, const char* resourcePath)
{
    CCTMXTiledMap *pRet = new CCTMXTiledMap();
    if (pRet->initWithXML(tmxString, resourcePath))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCTMXTiledMap::initWithTMXFile(const char *tmxFile)
{
    CCAssert(tmxFile != NULL && strlen(tmxFile)>0, "TMXTiledMap: tmx file should not bi NULL");
    
    setContentSize(CCSizeZero);

    CCTMXMapInfo *mapInfo = CCTMXMapInfo::formatWithTMXFile(tmxFile);

    if (! mapInfo)
    {
        return false;
    }
    CCAssert( mapInfo->getTilesets()->count() != 0, "TMXTiledMap: Map not found. Please check the filename.");
    buildWithMapInfo(mapInfo);

    return true;
}

bool CCTMXTiledMap::initWithXML(const char* tmxString, const char* resourcePath)
{
    setContentSize(CCSizeZero);

    CCTMXMapInfo *mapInfo = CCTMXMapInfo::formatWithXML(tmxString, resourcePath);

    CCAssert( mapInfo->getTilesets()->count() != 0, "TMXTiledMap: Map not found. Please check the filename.");
    buildWithMapInfo(mapInfo);

    return true;
}

CCTMXTiledMap::CCTMXTiledMap()
    :_mapSize(CCSizeZero)
    ,_tileSize(CCSizeZero)        
    ,_objectGroups(NULL)
    ,_properties(NULL)
    ,_tileProperties(NULL)
{
}
CCTMXTiledMap::~CCTMXTiledMap()
{
    CC_SAFE_RELEASE(_properties);
    CC_SAFE_RELEASE(_objectGroups);
    CC_SAFE_RELEASE(_tileProperties);
}

CCArray* CCTMXTiledMap::getObjectGroups()
{
    return _objectGroups;
}

void CCTMXTiledMap::setObjectGroups(CCArray* var)
{
    CC_SAFE_RETAIN(var);
    CC_SAFE_RELEASE(_objectGroups);
    _objectGroups = var;
}

CCDictionary * CCTMXTiledMap::getProperties()
{
    return _properties;
}

void CCTMXTiledMap::setProperties(CCDictionary* var)
{
    CC_SAFE_RETAIN(var);
    CC_SAFE_RELEASE(_properties);
    _properties = var;
}

// private
CCTMXLayer * CCTMXTiledMap::parseLayer(CCTMXLayerInfo *layerInfo, CCTMXMapInfo *mapInfo)
{
    CCTMXTilesetInfo *tileset = tilesetForLayer(layerInfo, mapInfo);
    CCTMXLayer *layer = CCTMXLayer::create(tileset, layerInfo, mapInfo);

    // tell the layerinfo to release the ownership of the tiles map.
    layerInfo->_ownTiles = false;
    layer->setupTiles();

    return layer;
}

CCTMXTilesetInfo * CCTMXTiledMap::tilesetForLayer(CCTMXLayerInfo *layerInfo, CCTMXMapInfo *mapInfo)
{
    CCSize size = layerInfo->_layerSize;
    CCArray* tilesets = mapInfo->getTilesets();
    if (tilesets && tilesets->count()>0)
    {
        CCTMXTilesetInfo* tileset = NULL;
        CCObject* pObj = NULL;
        CCARRAY_FOREACH_REVERSE(tilesets, pObj)
        {
            tileset = (CCTMXTilesetInfo*)pObj;
            if (tileset)
            {
                for( unsigned int y=0; y < size.height; y++ )
                {
                    for( unsigned int x=0; x < size.width; x++ ) 
                    {
                        unsigned int pos = (unsigned int)(x + size.width * y);
                        unsigned int gid = layerInfo->_tiles[ pos ];

                        // gid are stored in little endian.
                        // if host is big endian, then swap
                        //if( o == CFByteOrderBigEndian )
                        //    gid = CFSwapInt32( gid );
                        /* We support little endian.*/

                        // XXX: gid == 0 --> empty tile
                        if( gid != 0 ) 
                        {
                            // Optimization: quick return
                            // if the layer is invalid (more than 1 tileset per layer) an CCAssert will be thrown later
                            if( (gid & kCCFlippedMask) >= tileset->_firstGid )
                                return tileset;
                        }
                    }
                }        
            }
        }
    }

    // If all the tiles are 0, return empty tileset
    CCLOG("cocos2d: Warning: TMX Layer '%s' has no tiles", layerInfo->_name.c_str());
    return NULL;
}

void CCTMXTiledMap::buildWithMapInfo(CCTMXMapInfo* mapInfo)
{
    _mapSize = mapInfo->getMapSize();
    _tileSize = mapInfo->getTileSize();
    _mapOrientation = mapInfo->getOrientation();

    CC_SAFE_RELEASE(_objectGroups);
    _objectGroups = mapInfo->getObjectGroups();
    CC_SAFE_RETAIN(_objectGroups);

    CC_SAFE_RELEASE(_properties);
    _properties = mapInfo->getProperties();
    CC_SAFE_RETAIN(_properties);

    CC_SAFE_RELEASE(_tileProperties);
    _tileProperties = mapInfo->getTileProperties();
    CC_SAFE_RETAIN(_tileProperties);

    int idx=0;

    CCArray* layers = mapInfo->getLayers();
    if (layers && layers->count()>0)
    {
        CCTMXLayerInfo* layerInfo = NULL;
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(layers, pObj)
        {
            layerInfo = (CCTMXLayerInfo*)pObj;
            if (layerInfo && layerInfo->_visible)
            {
                CCTMXLayer *child = parseLayer(layerInfo, mapInfo);
                addChild((CCNode*)child, idx, idx);

                // update content size with the max size
                const CCSize& childSize = child->getContentSize();
                CCSize currentSize = this->getContentSize();
                currentSize.width = MAX( currentSize.width, childSize.width );
                currentSize.height = MAX( currentSize.height, childSize.height );
                this->setContentSize(currentSize);

                idx++;
            }
        }
    }
}

// public
CCTMXLayer * CCTMXTiledMap::layerNamed(const char *layerName)
{
    CCAssert(layerName != NULL && strlen(layerName) > 0, "Invalid layer name!");
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(_children, pObj) 
    {
        CCTMXLayer* layer = dynamic_cast<CCTMXLayer*>(pObj);
        if(layer)
        {
            if(0 == strcmp(layer->getLayerName(), layerName))
            {
                return layer;
            }
        }
    }

    // layer not found
    return NULL;
}

CCTMXObjectGroup * CCTMXTiledMap::objectGroupNamed(const char *groupName)
{
    CCAssert(groupName != NULL && strlen(groupName) > 0, "Invalid group name!");

    std::string sGroupName = groupName;
    if (_objectGroups && _objectGroups->count()>0)
    {
        CCTMXObjectGroup* objectGroup = NULL;
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(_objectGroups, pObj)
        {
            objectGroup = (CCTMXObjectGroup*)(pObj);
            if (objectGroup && objectGroup->getGroupName() == sGroupName)
            {
                return objectGroup;
            }
        }
    }

    // objectGroup not found
    return NULL;
}

CCString* CCTMXTiledMap::propertyNamed(const char *propertyName)
{
    return (CCString*)_properties->objectForKey(propertyName);
}

CCDictionary* CCTMXTiledMap::propertiesForGID(int GID)
{
    return (CCDictionary*)_tileProperties->objectForKey(GID);
}
        

NS_CC_END

