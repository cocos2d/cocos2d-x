/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011        Максим Аксенов 
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

#include <map>
#include <sstream>
#include "CCTMXXMLParser.h"
#include "CCTMXTiledMap.h"
#include "ccMacros.h"
#include "platform/CCFileUtils.h"
#include "support/zip_support/ZipUtils.h"
#include "support/CCPointExtension.h"
#include "support/base64.h"
#include "platform/platform.h"

using namespace std;
/*
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
    #include "expat.h"
#else
    #include <libxml/parser.h>
    #include <libxml/tree.h>
    #include <libxml/xmlmemory.h>
#endif
*/

NS_CC_BEGIN

/*
void tmx_startElement(void *ctx, const xmlChar *name, const xmlChar **atts);
void tmx_endElement(void *ctx, const xmlChar *name);
void tmx_characters(void *ctx, const xmlChar *ch, int len);
*/

static const char* valueForKey(const char *key, std::map<std::string, std::string>* dict)
{
    if (dict)
    {
        std::map<std::string, std::string>::iterator it = dict->find(key);
        return it!=dict->end() ? it->second.c_str() : "";
    }
    return "";
}
// implementation CCTMXLayerInfo
CCTMXLayerInfo::CCTMXLayerInfo()
: _name("")
, _tiles(NULL)
, _ownTiles(true)
, _minGID(100000)
, _maxGID(0)        
, _offset(CCPointZero)
{
    _properties= new CCDictionary();;
}

CCTMXLayerInfo::~CCTMXLayerInfo()
{
    CCLOGINFO("cocos2d: deallocing: %p", this);
    CC_SAFE_RELEASE(_properties);
    if( _ownTiles && _tiles )
    {
        delete [] _tiles;
        _tiles = NULL;
    }
}
CCDictionary * CCTMXLayerInfo::getProperties()
{
    return _properties;
}
void CCTMXLayerInfo::setProperties(CCDictionary* var)
{
    CC_SAFE_RETAIN(var);
    CC_SAFE_RELEASE(_properties);
    _properties = var;
}

// implementation CCTMXTilesetInfo
CCTMXTilesetInfo::CCTMXTilesetInfo()
    :_firstGid(0)
    ,_tileSize(CCSizeZero)
    ,_spacing(0)
    ,_margin(0)
    ,_imageSize(CCSizeZero)
{
}
CCTMXTilesetInfo::~CCTMXTilesetInfo()
{
    CCLOGINFO("cocos2d: deallocing: %p", this);
}
CCRect CCTMXTilesetInfo::rectForGID(unsigned int gid)
{
    CCRect rect;
    rect.size = _tileSize;
    gid &= kCCFlippedMask;
    gid = gid - _firstGid;
    int max_x = (int)((_imageSize.width - _margin*2 + _spacing) / (_tileSize.width + _spacing));
    //    int max_y = (imageSize.height - margin*2 + spacing) / (tileSize.height + spacing);
    rect.origin.x = (gid % max_x) * (_tileSize.width + _spacing) + _margin;
    rect.origin.y = (gid / max_x) * (_tileSize.height + _spacing) + _margin;
    return rect;
}

// implementation CCTMXMapInfo

CCTMXMapInfo * CCTMXMapInfo::formatWithTMXFile(const char *tmxFile)
{
    CCTMXMapInfo *pRet = new CCTMXMapInfo();
    if(pRet->initWithTMXFile(tmxFile))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCTMXMapInfo * CCTMXMapInfo::formatWithXML(const char* tmxString, const char* resourcePath)
{
    CCTMXMapInfo *pRet = new CCTMXMapInfo();
    if(pRet->initWithXML(tmxString, resourcePath))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void CCTMXMapInfo::internalInit(const char* tmxFileName, const char* resourcePath)
{
    _tilesets = CCArray::create();
    _tilesets->retain();

    _layers = CCArray::create();
    _layers->retain();

    if (tmxFileName != NULL)
    {
        _TMXFileName = CCFileUtils::sharedFileUtils()->fullPathForFilename(tmxFileName);
    }
    
    if (resourcePath != NULL)
    {
        _resources = resourcePath;
    }
    
    _objectGroups = CCArray::createWithCapacity(4);
    _objectGroups->retain();

    _properties = new CCDictionary();
    _tileProperties = new CCDictionary();

    // tmp vars
    _currentString = "";
    _storingCharacters = false;
    _layerAttribs = TMXLayerAttribNone;
    _parentElement = TMXPropertyNone;
    _currentFirstGID = 0;
}
bool CCTMXMapInfo::initWithXML(const char* tmxString, const char* resourcePath)
{
    internalInit(NULL, resourcePath);
    return parseXMLString(tmxString);
}

bool CCTMXMapInfo::initWithTMXFile(const char *tmxFile)
{
    internalInit(tmxFile, NULL);
    return parseXMLFile(_TMXFileName.c_str());
}

CCTMXMapInfo::CCTMXMapInfo()
: _mapSize(CCSizeZero)    
, _tileSize(CCSizeZero)
, _layers(NULL)
, _tilesets(NULL)
, _objectGroups(NULL)
, _layerAttribs(0)
, _storingCharacters(false)
, _properties(NULL)
, _tileProperties(NULL)
, _currentFirstGID(0)
{
}

CCTMXMapInfo::~CCTMXMapInfo()
{
    CCLOGINFO("cocos2d: deallocing: %p", this);
    CC_SAFE_RELEASE(_tilesets);
    CC_SAFE_RELEASE(_layers);
    CC_SAFE_RELEASE(_properties);
    CC_SAFE_RELEASE(_tileProperties);
    CC_SAFE_RELEASE(_objectGroups);
}

CCArray* CCTMXMapInfo::getLayers()
{
    return _layers;
}

void CCTMXMapInfo::setLayers(CCArray* var)
{
    CC_SAFE_RETAIN(var);
    CC_SAFE_RELEASE(_layers);
    _layers = var;
}

CCArray* CCTMXMapInfo::getTilesets()
{
    return _tilesets;
}

void CCTMXMapInfo::setTilesets(CCArray* var)
{
    CC_SAFE_RETAIN(var);
    CC_SAFE_RELEASE(_tilesets);
    _tilesets = var;
}

CCArray* CCTMXMapInfo::getObjectGroups()
{
    return _objectGroups;
}

void CCTMXMapInfo::setObjectGroups(CCArray* var)
{
    CC_SAFE_RETAIN(var);
    CC_SAFE_RELEASE(_objectGroups);
    _objectGroups = var;
}

CCDictionary * CCTMXMapInfo::getProperties()
{
    return _properties;
}

void CCTMXMapInfo::setProperties(CCDictionary* var)
{
    CC_SAFE_RETAIN(var);
    CC_SAFE_RELEASE(_properties);
    _properties = var;
}

CCDictionary* CCTMXMapInfo::getTileProperties()
{
    return _tileProperties;
}

void CCTMXMapInfo::setTileProperties(CCDictionary* tileProperties)
{
    CC_SAFE_RETAIN(tileProperties);
    CC_SAFE_RELEASE(_tileProperties);
    _tileProperties = tileProperties;
}

bool CCTMXMapInfo::parseXMLString(const char *xmlString)
{
    int len = strlen(xmlString);
    if (xmlString == NULL || len <= 0) 
    {
        return false;
    }

    CCSAXParser parser;

    if (false == parser.init("UTF-8") )
    {
        return false;
    }

    parser.setDelegator(this);

    return parser.parse(xmlString, len);
}

bool CCTMXMapInfo::parseXMLFile(const char *xmlFilename)
{
    CCSAXParser parser;
    
    if (false == parser.init("UTF-8") )
    {
        return false;
    }
    
    parser.setDelegator(this);

    return parser.parse(CCFileUtils::sharedFileUtils()->fullPathForFilename(xmlFilename).c_str());
}


// the XML parser calls here with all the elements
void CCTMXMapInfo::startElement(void *ctx, const char *name, const char **atts)
{    
    CC_UNUSED_PARAM(ctx);
    CCTMXMapInfo *pTMXMapInfo = this;
    std::string elementName = (char*)name;
    std::map<std::string, std::string> *attributeDict = new std::map<std::string, std::string>();
    if (atts && atts[0])
    {
        for(int i = 0; atts[i]; i += 2) 
        {
            std::string key = (char*)atts[i];
            std::string value = (char*)atts[i+1];
            attributeDict->insert(pair<std::string, std::string>(key, value));
        }
    }
    if (elementName == "map")
    {
        std::string version = valueForKey("version", attributeDict);
        if ( version != "1.0")
        {
            CCLOG("cocos2d: TMXFormat: Unsupported TMX version: %s", version.c_str());
        }
        std::string orientationStr = valueForKey("orientation", attributeDict);
        if (orientationStr == "orthogonal")
            pTMXMapInfo->setOrientation(CCTMXOrientationOrtho);
        else if (orientationStr  == "isometric")
            pTMXMapInfo->setOrientation(CCTMXOrientationIso);
        else if(orientationStr == "hexagonal")
            pTMXMapInfo->setOrientation(CCTMXOrientationHex);
        else
            CCLOG("cocos2d: TMXFomat: Unsupported orientation: %d", pTMXMapInfo->getOrientation());

        CCSize s;
        s.width = (float)atof(valueForKey("width", attributeDict));
        s.height = (float)atof(valueForKey("height", attributeDict));
        pTMXMapInfo->setMapSize(s);

        s.width = (float)atof(valueForKey("tilewidth", attributeDict));
        s.height = (float)atof(valueForKey("tileheight", attributeDict));
        pTMXMapInfo->setTileSize(s);

        // The parent element is now "map"
        pTMXMapInfo->setParentElement(TMXPropertyMap);
    } 
    else if (elementName == "tileset") 
    {
        // If this is an external tileset then start parsing that
        std::string externalTilesetFilename = valueForKey("source", attributeDict);
        if (externalTilesetFilename != "")
        {
            // Tileset file will be relative to the map file. So we need to convert it to an absolute path
            if (_TMXFileName.find_last_of("/") != string::npos)
            {
                string dir = _TMXFileName.substr(0, _TMXFileName.find_last_of("/") + 1);
                externalTilesetFilename = dir + externalTilesetFilename;
            }
            else 
            {
                externalTilesetFilename = _resources + "/" + externalTilesetFilename;
            }
            externalTilesetFilename = CCFileUtils::sharedFileUtils()->fullPathForFilename(externalTilesetFilename.c_str());
            
            _currentFirstGID = (unsigned int)atoi(valueForKey("firstgid", attributeDict));
            
            pTMXMapInfo->parseXMLFile(externalTilesetFilename.c_str());
        }
        else
        {
            CCTMXTilesetInfo *tileset = new CCTMXTilesetInfo();
            tileset->_name = valueForKey("name", attributeDict);
            if (_currentFirstGID == 0)
            {
                tileset->_firstGid = (unsigned int)atoi(valueForKey("firstgid", attributeDict));
            }
            else
            {
                tileset->_firstGid = _currentFirstGID;
                _currentFirstGID = 0;
            }
            tileset->_spacing = (unsigned int)atoi(valueForKey("spacing", attributeDict));
            tileset->_margin = (unsigned int)atoi(valueForKey("margin", attributeDict));
            CCSize s;
            s.width = (float)atof(valueForKey("tilewidth", attributeDict));
            s.height = (float)atof(valueForKey("tileheight", attributeDict));
            tileset->_tileSize = s;

            pTMXMapInfo->getTilesets()->addObject(tileset);
            tileset->release();
        }
    }
    else if (elementName == "tile")
    {
        CCTMXTilesetInfo* info = (CCTMXTilesetInfo*)pTMXMapInfo->getTilesets()->lastObject();
        CCDictionary *dict = new CCDictionary();
        pTMXMapInfo->setParentGID(info->_firstGid + atoi(valueForKey("id", attributeDict)));
        pTMXMapInfo->getTileProperties()->setObject(dict, pTMXMapInfo->getParentGID());
        CC_SAFE_RELEASE(dict);
        
        pTMXMapInfo->setParentElement(TMXPropertyTile);

    }
    else if (elementName == "layer")
    {
        CCTMXLayerInfo *layer = new CCTMXLayerInfo();
        layer->_name = valueForKey("name", attributeDict);

        CCSize s;
        s.width = (float)atof(valueForKey("width", attributeDict));
        s.height = (float)atof(valueForKey("height", attributeDict));
        layer->_layerSize = s;

        std::string visible = valueForKey("visible", attributeDict);
        layer->_visible = !(visible == "0");

        std::string opacity = valueForKey("opacity", attributeDict);
        if( opacity != "" )
        {
            layer->_opacity = (unsigned char)(255 * atof(opacity.c_str()));
        }
        else
        {
            layer->_opacity = 255;
        }

        float x = (float)atof(valueForKey("x", attributeDict));
        float y = (float)atof(valueForKey("y", attributeDict));
        layer->_offset = ccp(x,y);

        pTMXMapInfo->getLayers()->addObject(layer);
        layer->release();

        // The parent element is now "layer"
        pTMXMapInfo->setParentElement(TMXPropertyLayer);

    } 
    else if (elementName == "objectgroup")
    {
        CCTMXObjectGroup *objectGroup = new CCTMXObjectGroup();
        objectGroup->setGroupName(valueForKey("name", attributeDict));
        CCPoint positionOffset;
        positionOffset.x = (float)atof(valueForKey("x", attributeDict)) * pTMXMapInfo->getTileSize().width;
        positionOffset.y = (float)atof(valueForKey("y", attributeDict)) * pTMXMapInfo->getTileSize().height;
        objectGroup->setPositionOffset(positionOffset);

        pTMXMapInfo->getObjectGroups()->addObject(objectGroup);
        objectGroup->release();

        // The parent element is now "objectgroup"
        pTMXMapInfo->setParentElement(TMXPropertyObjectGroup);

    }
    else if (elementName == "image")
    {
        CCTMXTilesetInfo* tileset = (CCTMXTilesetInfo*)pTMXMapInfo->getTilesets()->lastObject();

        // build full path
        std::string imagename = valueForKey("source", attributeDict);

        if (_TMXFileName.find_last_of("/") != string::npos)
        {
            string dir = _TMXFileName.substr(0, _TMXFileName.find_last_of("/") + 1);
            tileset->_sourceImage = dir + imagename;
        }
        else 
        {
            tileset->_sourceImage = _resources + (_resources.size() ? "/" : "") + imagename;
        }
    } 
    else if (elementName == "data")
    {
        std::string encoding = valueForKey("encoding", attributeDict);
        std::string compression = valueForKey("compression", attributeDict);

        if( encoding == "base64" )
        {
            int layerAttribs = pTMXMapInfo->getLayerAttribs();
            pTMXMapInfo->setLayerAttribs(layerAttribs | TMXLayerAttribBase64);
            pTMXMapInfo->setStoringCharacters(true);

            if( compression == "gzip" )
            {
                layerAttribs = pTMXMapInfo->getLayerAttribs();
                pTMXMapInfo->setLayerAttribs(layerAttribs | TMXLayerAttribGzip);
            } else
            if (compression == "zlib")
            {
                layerAttribs = pTMXMapInfo->getLayerAttribs();
                pTMXMapInfo->setLayerAttribs(layerAttribs | TMXLayerAttribZlib);
            }
            CCAssert( compression == "" || compression == "gzip" || compression == "zlib", "TMX: unsupported compression method" );
        }
        CCAssert( pTMXMapInfo->getLayerAttribs() != TMXLayerAttribNone, "TMX tile map: Only base64 and/or gzip/zlib maps are supported" );

    } 
    else if (elementName == "object")
    {
        char buffer[32] = {0};
        CCTMXObjectGroup* objectGroup = (CCTMXObjectGroup*)pTMXMapInfo->getObjectGroups()->lastObject();

        // The value for "type" was blank or not a valid class name
        // Create an instance of TMXObjectInfo to store the object and its properties
        CCDictionary *dict = new CCDictionary();
        // Parse everything automatically
        const char* pArray[] = {"name", "type", "width", "height", "gid"};
        
        for(size_t i = 0; i < sizeof(pArray)/sizeof(pArray[0]); ++i )
        {
            const char* key = pArray[i];
            CCString* obj = new CCString(valueForKey(key, attributeDict));
            if( obj )
            {
                obj->autorelease();
                dict->setObject(obj, key);
            }
        }

        // But X and Y since they need special treatment
        // X

        const char* value = valueForKey("x", attributeDict);
        if (value) 
        {
            int x = atoi(value) + (int)objectGroup->getPositionOffset().x;
            sprintf(buffer, "%d", x);
            CCString* pStr = new CCString(buffer);
            pStr->autorelease();
            dict->setObject(pStr, "x");
        }

        // Y
        value = valueForKey("y", attributeDict);
        if (value)  {
            int y = atoi(value) + (int)objectGroup->getPositionOffset().y;

            // Correct y position. (Tiled uses Flipped, cocos2d uses Standard)
            y = (int)(_mapSize.height * _tileSize.height) - y - atoi(valueForKey("height", attributeDict));
            sprintf(buffer, "%d", y);
            CCString* pStr = new CCString(buffer);
            pStr->autorelease();
            dict->setObject(pStr, "y");
        }

        // Add the object to the objectGroup
        objectGroup->getObjects()->addObject(dict);
        dict->release();

         // The parent element is now "object"
         pTMXMapInfo->setParentElement(TMXPropertyObject);

    } 
    else if (elementName == "property")
    {
        if ( pTMXMapInfo->getParentElement() == TMXPropertyNone ) 
        {
            CCLOG( "TMX tile map: Parent element is unsupported. Cannot add property named '%s' with value '%s'",
                valueForKey("name", attributeDict), valueForKey("value",attributeDict) );
        } 
        else if ( pTMXMapInfo->getParentElement() == TMXPropertyMap )
        {
            // The parent element is the map
            CCString *value = new CCString(valueForKey("value", attributeDict));
            std::string key = valueForKey("name", attributeDict);
            pTMXMapInfo->getProperties()->setObject(value, key.c_str());
            value->release();

        } 
        else if ( pTMXMapInfo->getParentElement() == TMXPropertyLayer )
        {
            // The parent element is the last layer
            CCTMXLayerInfo* layer = (CCTMXLayerInfo*)pTMXMapInfo->getLayers()->lastObject();
            CCString *value = new CCString(valueForKey("value", attributeDict));
            std::string key = valueForKey("name", attributeDict);
            // Add the property to the layer
            layer->getProperties()->setObject(value, key.c_str());
            value->release();

        } 
        else if ( pTMXMapInfo->getParentElement() == TMXPropertyObjectGroup ) 
        {
            // The parent element is the last object group
            CCTMXObjectGroup* objectGroup = (CCTMXObjectGroup*)pTMXMapInfo->getObjectGroups()->lastObject();
            CCString *value = new CCString(valueForKey("value", attributeDict));
            const char* key = valueForKey("name", attributeDict);
            objectGroup->getProperties()->setObject(value, key);
            value->release();

        } 
        else if ( pTMXMapInfo->getParentElement() == TMXPropertyObject )
        {
            // The parent element is the last object
            CCTMXObjectGroup* objectGroup = (CCTMXObjectGroup*)pTMXMapInfo->getObjectGroups()->lastObject();
            CCDictionary* dict = (CCDictionary*)objectGroup->getObjects()->lastObject();

            const char* propertyName = valueForKey("name", attributeDict);
            CCString *propertyValue = new CCString(valueForKey("value", attributeDict));
            dict->setObject(propertyValue, propertyName);
            propertyValue->release();
        } 
        else if ( pTMXMapInfo->getParentElement() == TMXPropertyTile ) 
        {
            CCDictionary* dict = (CCDictionary*)pTMXMapInfo->getTileProperties()->objectForKey(pTMXMapInfo->getParentGID());

            const char* propertyName = valueForKey("name", attributeDict);
            CCString *propertyValue = new CCString(valueForKey("value", attributeDict));
            dict->setObject(propertyValue, propertyName);
            propertyValue->release();
        }
    }
    else if (elementName == "polygon") 
    {
        // find parent object's dict and add polygon-points to it
        CCTMXObjectGroup* objectGroup = (CCTMXObjectGroup*)_objectGroups->lastObject();
        CCDictionary* dict = (CCDictionary*)objectGroup->getObjects()->lastObject();

        // get points value string
        const char* value = valueForKey("points", attributeDict);
        if(value)
        {
            CCArray* pPointsArray = new CCArray;

            // parse points string into a space-separated set of points
            stringstream pointsStream(value);
            string pointPair;
            while(std::getline(pointsStream, pointPair, ' '))
            {
                // parse each point combo into a comma-separated x,y point
                stringstream pointStream(pointPair);
                string xStr,yStr;
                char buffer[32] = {0};
                
                CCDictionary* pPointDict = new CCDictionary;

                // set x
                if(std::getline(pointStream, xStr, ','))
                {
                    int x = atoi(xStr.c_str()) + (int)objectGroup->getPositionOffset().x;
                    sprintf(buffer, "%d", x);
                    CCString* pStr = new CCString(buffer);
                    pStr->autorelease();
                    pPointDict->setObject(pStr, "x");
                }

                // set y
                if(std::getline(pointStream, yStr, ','))
                {
                    int y = atoi(yStr.c_str()) + (int)objectGroup->getPositionOffset().y;
                    sprintf(buffer, "%d", y);
                    CCString* pStr = new CCString(buffer);
                    pStr->autorelease();
                    pPointDict->setObject(pStr, "y");
                }
                
                // add to points array
                pPointsArray->addObject(pPointDict);
                pPointDict->release();
            }
            
            dict->setObject(pPointsArray, "points");
            pPointsArray->release();
        }
    } 
    else if (elementName == "polyline")
    {
        // find parent object's dict and add polyline-points to it
        // CCTMXObjectGroup* objectGroup = (CCTMXObjectGroup*)_objectGroups->lastObject();
        // CCDictionary* dict = (CCDictionary*)objectGroup->getObjects()->lastObject();
        // TODO: dict->setObject:[attributeDict objectForKey:@"points"] forKey:@"polylinePoints"];
    }

    if (attributeDict)
    {
        attributeDict->clear();
        delete attributeDict;
    }
}

void CCTMXMapInfo::endElement(void *ctx, const char *name)
{
    CC_UNUSED_PARAM(ctx);
    CCTMXMapInfo *pTMXMapInfo = this;
    std::string elementName = (char*)name;

    int len = 0;

    if(elementName == "data" && pTMXMapInfo->getLayerAttribs()&TMXLayerAttribBase64) 
    {
        pTMXMapInfo->setStoringCharacters(false);

        CCTMXLayerInfo* layer = (CCTMXLayerInfo*)pTMXMapInfo->getLayers()->lastObject();

        std::string currentString = pTMXMapInfo->getCurrentString();
        unsigned char *buffer;
        len = base64Decode((unsigned char*)currentString.c_str(), (unsigned int)currentString.length(), &buffer);
        if( ! buffer ) 
        {
            CCLOG("cocos2d: TiledMap: decode data error");
            return;
        }

        if( pTMXMapInfo->getLayerAttribs() & (TMXLayerAttribGzip | TMXLayerAttribZlib) )
        {
            unsigned char *deflated;
            CCSize s = layer->_layerSize;
            // int sizeHint = s.width * s.height * sizeof(uint32_t);
            int sizeHint = (int)(s.width * s.height * sizeof(unsigned int));

            int inflatedLen = ZipUtils::ccInflateMemoryWithHint(buffer, len, &deflated, sizeHint);
            CCAssert(inflatedLen == sizeHint, "");

            inflatedLen = (size_t)&inflatedLen; // XXX: to avoid warnings in compiler
            
            delete [] buffer;
            buffer = NULL;

            if( ! deflated ) 
            {
                CCLOG("cocos2d: TiledMap: inflate data error");
                return;
            }

            layer->_tiles = (unsigned int*) deflated;
        }
        else
        {
            layer->_tiles = (unsigned int*) buffer;
        }

        pTMXMapInfo->setCurrentString("");

    } 
    else if (elementName == "map")
    {
        // The map element has ended
        pTMXMapInfo->setParentElement(TMXPropertyNone);
    }    
    else if (elementName == "layer")
    {
        // The layer element has ended
        pTMXMapInfo->setParentElement(TMXPropertyNone);
    }
    else if (elementName == "objectgroup")
    {
        // The objectgroup element has ended
        pTMXMapInfo->setParentElement(TMXPropertyNone);
    } 
    else if (elementName == "object") 
    {
        // The object element has ended
        pTMXMapInfo->setParentElement(TMXPropertyNone);
    }
}

void CCTMXMapInfo::textHandler(void *ctx, const char *ch, int len)
{
    CC_UNUSED_PARAM(ctx);
    CCTMXMapInfo *pTMXMapInfo = this;
    std::string pText((char*)ch,0,len);

    if (pTMXMapInfo->getStoringCharacters())
    {
        std::string currentString = pTMXMapInfo->getCurrentString();
        currentString += pText;
        pTMXMapInfo->setCurrentString(currentString.c_str());
    }
}

NS_CC_END

