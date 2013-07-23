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
#include "support/base64.h"

using namespace std;

NS_CC_BEGIN

static const char* valueForKey(const char *key, std::map<std::string, std::string>* dict)
{
    if (dict)
    {
        std::map<std::string, std::string>::iterator it = dict->find(key);
        return it!=dict->end() ? it->second.c_str() : "";
    }
    return "";
}
// implementation TMXLayerInfo
TMXLayerInfo::TMXLayerInfo()
: _name("")
, _tiles(NULL)
, _ownTiles(true)
, _minGID(100000)
, _maxGID(0)        
, _offset(Point::ZERO)
{
    _properties= new Dictionary();;
}

TMXLayerInfo::~TMXLayerInfo()
{
    CCLOGINFO("cocos2d: deallocing: %p", this);
    CC_SAFE_RELEASE(_properties);
    if( _ownTiles && _tiles )
    {
        delete [] _tiles;
        _tiles = NULL;
    }
}

Dictionary * TMXLayerInfo::getProperties()
{
    return _properties;
}
void TMXLayerInfo::setProperties(Dictionary* var)
{
    CC_SAFE_RETAIN(var);
    CC_SAFE_RELEASE(_properties);
    _properties = var;
}

// implementation TMXTilesetInfo
TMXTilesetInfo::TMXTilesetInfo()
    :_firstGid(0)
    ,_tileSize(Size::ZERO)
    ,_spacing(0)
    ,_margin(0)
    ,_imageSize(Size::ZERO)
{
}

TMXTilesetInfo::~TMXTilesetInfo()
{
    CCLOGINFO("cocos2d: deallocing: %p", this);
}

Rect TMXTilesetInfo::rectForGID(unsigned int gid)
{
    Rect rect;
    rect.size = _tileSize;
    gid &= kFlippedMask;
    gid = gid - _firstGid;
    int max_x = (int)((_imageSize.width - _margin*2 + _spacing) / (_tileSize.width + _spacing));
    //    int max_y = (imageSize.height - margin*2 + spacing) / (tileSize.height + spacing);
    rect.origin.x = (gid % max_x) * (_tileSize.width + _spacing) + _margin;
    rect.origin.y = (gid / max_x) * (_tileSize.height + _spacing) + _margin;
    return rect;
}

// implementation TMXMapInfo

TMXMapInfo * TMXMapInfo::create(const char *tmxFile)
{
    TMXMapInfo *pRet = new TMXMapInfo();
    if(pRet->initWithTMXFile(tmxFile))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

TMXMapInfo * TMXMapInfo::createWithXML(const char* tmxString, const char* resourcePath)
{
    TMXMapInfo *pRet = new TMXMapInfo();
    if(pRet->initWithXML(tmxString, resourcePath))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void TMXMapInfo::internalInit(const char* tmxFileName, const char* resourcePath)
{
    _tilesets = Array::create();
    _tilesets->retain();

    _layers = Array::create();
    _layers->retain();

    if (tmxFileName != NULL)
    {
        _TMXFileName = FileUtils::getInstance()->fullPathForFilename(tmxFileName);
    }
    
    if (resourcePath != NULL)
    {
        _resources = resourcePath;
    }
    
    _objectGroups = Array::createWithCapacity(4);
    _objectGroups->retain();

    _properties = new Dictionary();
    _tileProperties = new Dictionary();

    // tmp vars
    _currentString = "";
    _storingCharacters = false;
    _layerAttribs = TMXLayerAttribNone;
    _parentElement = TMXPropertyNone;
    _currentFirstGID = 0;
}
bool TMXMapInfo::initWithXML(const char* tmxString, const char* resourcePath)
{
    internalInit(NULL, resourcePath);
    return parseXMLString(tmxString);
}

bool TMXMapInfo::initWithTMXFile(const char *tmxFile)
{
    internalInit(tmxFile, NULL);
    return parseXMLFile(_TMXFileName.c_str());
}

TMXMapInfo::TMXMapInfo()
: _mapSize(Size::ZERO)    
, _tileSize(Size::ZERO)
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

TMXMapInfo::~TMXMapInfo()
{
    CCLOGINFO("cocos2d: deallocing: %p", this);
    CC_SAFE_RELEASE(_tilesets);
    CC_SAFE_RELEASE(_layers);
    CC_SAFE_RELEASE(_properties);
    CC_SAFE_RELEASE(_tileProperties);
    CC_SAFE_RELEASE(_objectGroups);
}

bool TMXMapInfo::parseXMLString(const char *xmlString)
{
    int len = strlen(xmlString);
    if (xmlString == NULL || len <= 0) 
    {
        return false;
    }

    SAXParser parser;

    if (false == parser.init("UTF-8") )
    {
        return false;
    }

    parser.setDelegator(this);

    return parser.parse(xmlString, len);
}

bool TMXMapInfo::parseXMLFile(const char *xmlFilename)
{
    SAXParser parser;
    
    if (false == parser.init("UTF-8") )
    {
        return false;
    }
    
    parser.setDelegator(this);

    return parser.parse(FileUtils::getInstance()->fullPathForFilename(xmlFilename).c_str());
}


// the XML parser calls here with all the elements
void TMXMapInfo::startElement(void *ctx, const char *name, const char **atts)
{    
    CC_UNUSED_PARAM(ctx);
    TMXMapInfo *pTMXMapInfo = this;
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
            pTMXMapInfo->setOrientation(TMXOrientationOrtho);
        else if (orientationStr  == "isometric")
            pTMXMapInfo->setOrientation(TMXOrientationIso);
        else if(orientationStr == "hexagonal")
            pTMXMapInfo->setOrientation(TMXOrientationHex);
        else
            CCLOG("cocos2d: TMXFomat: Unsupported orientation: %d", pTMXMapInfo->getOrientation());

        Size s;
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
            externalTilesetFilename = FileUtils::getInstance()->fullPathForFilename(externalTilesetFilename.c_str());
            
            _currentFirstGID = (unsigned int)atoi(valueForKey("firstgid", attributeDict));
            
            pTMXMapInfo->parseXMLFile(externalTilesetFilename.c_str());
        }
        else
        {
            TMXTilesetInfo *tileset = new TMXTilesetInfo();
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
            Size s;
            s.width = (float)atof(valueForKey("tilewidth", attributeDict));
            s.height = (float)atof(valueForKey("tileheight", attributeDict));
            tileset->_tileSize = s;

            pTMXMapInfo->getTilesets()->addObject(tileset);
            tileset->release();
        }
    }
    else if (elementName == "tile")
    {
        TMXTilesetInfo* info = (TMXTilesetInfo*)pTMXMapInfo->getTilesets()->lastObject();
        Dictionary *dict = new Dictionary();
        pTMXMapInfo->setParentGID(info->_firstGid + atoi(valueForKey("id", attributeDict)));
        pTMXMapInfo->getTileProperties()->setObject(dict, pTMXMapInfo->getParentGID());
        CC_SAFE_RELEASE(dict);
        
        pTMXMapInfo->setParentElement(TMXPropertyTile);

    }
    else if (elementName == "layer")
    {
        TMXLayerInfo *layer = new TMXLayerInfo();
        layer->_name = valueForKey("name", attributeDict);

        Size s;
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
        layer->_offset = Point(x,y);

        pTMXMapInfo->getLayers()->addObject(layer);
        layer->release();

        // The parent element is now "layer"
        pTMXMapInfo->setParentElement(TMXPropertyLayer);

    } 
    else if (elementName == "objectgroup")
    {
        TMXObjectGroup *objectGroup = new TMXObjectGroup();
        objectGroup->setGroupName(valueForKey("name", attributeDict));
        Point positionOffset;
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
        TMXTilesetInfo* tileset = (TMXTilesetInfo*)pTMXMapInfo->getTilesets()->lastObject();

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
            CCASSERT( compression == "" || compression == "gzip" || compression == "zlib", "TMX: unsupported compression method" );
        }
        CCASSERT( pTMXMapInfo->getLayerAttribs() != TMXLayerAttribNone, "TMX tile map: Only base64 and/or gzip/zlib maps are supported" );

    } 
    else if (elementName == "object")
    {
        char buffer[32] = {0};
        TMXObjectGroup* objectGroup = (TMXObjectGroup*)pTMXMapInfo->getObjectGroups()->lastObject();

        // The value for "type" was blank or not a valid class name
        // Create an instance of TMXObjectInfo to store the object and its properties
        Dictionary *dict = new Dictionary();
        // Parse everything automatically
        const char* pArray[] = {"name", "type", "width", "height", "gid"};
        
        for(size_t i = 0; i < sizeof(pArray)/sizeof(pArray[0]); ++i )
        {
            const char* key = pArray[i];
            String* obj = new String(valueForKey(key, attributeDict));
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
            String* pStr = new String(buffer);
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
            String* pStr = new String(buffer);
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
            String *value = new String(valueForKey("value", attributeDict));
            std::string key = valueForKey("name", attributeDict);
            pTMXMapInfo->getProperties()->setObject(value, key.c_str());
            value->release();

        } 
        else if ( pTMXMapInfo->getParentElement() == TMXPropertyLayer )
        {
            // The parent element is the last layer
            TMXLayerInfo* layer = (TMXLayerInfo*)pTMXMapInfo->getLayers()->lastObject();
            String *value = new String(valueForKey("value", attributeDict));
            std::string key = valueForKey("name", attributeDict);
            // Add the property to the layer
            layer->getProperties()->setObject(value, key.c_str());
            value->release();

        } 
        else if ( pTMXMapInfo->getParentElement() == TMXPropertyObjectGroup ) 
        {
            // The parent element is the last object group
            TMXObjectGroup* objectGroup = (TMXObjectGroup*)pTMXMapInfo->getObjectGroups()->lastObject();
            String *value = new String(valueForKey("value", attributeDict));
            const char* key = valueForKey("name", attributeDict);
            objectGroup->getProperties()->setObject(value, key);
            value->release();

        } 
        else if ( pTMXMapInfo->getParentElement() == TMXPropertyObject )
        {
            // The parent element is the last object
            TMXObjectGroup* objectGroup = (TMXObjectGroup*)pTMXMapInfo->getObjectGroups()->lastObject();
            Dictionary* dict = (Dictionary*)objectGroup->getObjects()->lastObject();

            const char* propertyName = valueForKey("name", attributeDict);
            String *propertyValue = new String(valueForKey("value", attributeDict));
            dict->setObject(propertyValue, propertyName);
            propertyValue->release();
        } 
        else if ( pTMXMapInfo->getParentElement() == TMXPropertyTile ) 
        {
            Dictionary* dict = (Dictionary*)pTMXMapInfo->getTileProperties()->objectForKey(pTMXMapInfo->getParentGID());

            const char* propertyName = valueForKey("name", attributeDict);
            String *propertyValue = new String(valueForKey("value", attributeDict));
            dict->setObject(propertyValue, propertyName);
            propertyValue->release();
        }
    }
    else if (elementName == "polygon") 
    {
        // find parent object's dict and add polygon-points to it
        TMXObjectGroup* objectGroup = (TMXObjectGroup*)_objectGroups->lastObject();
        Dictionary* dict = (Dictionary*)objectGroup->getObjects()->lastObject();

        // get points value string
        const char* value = valueForKey("points", attributeDict);
        if(value)
        {
            Array* pPointsArray = new Array;

            // parse points string into a space-separated set of points
            stringstream pointsStream(value);
            string pointPair;
            while(std::getline(pointsStream, pointPair, ' '))
            {
                // parse each point combo into a comma-separated x,y point
                stringstream pointStream(pointPair);
                string xStr,yStr;
                char buffer[32] = {0};
                
                Dictionary* pPointDict = new Dictionary;

                // set x
                if(std::getline(pointStream, xStr, ','))
                {
                    int x = atoi(xStr.c_str()) + (int)objectGroup->getPositionOffset().x;
                    sprintf(buffer, "%d", x);
                    String* pStr = new String(buffer);
                    pStr->autorelease();
                    pPointDict->setObject(pStr, "x");
                }

                // set y
                if(std::getline(pointStream, yStr, ','))
                {
                    int y = atoi(yStr.c_str()) + (int)objectGroup->getPositionOffset().y;
                    sprintf(buffer, "%d", y);
                    String* pStr = new String(buffer);
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
        // TMXObjectGroup* objectGroup = (TMXObjectGroup*)_objectGroups->lastObject();
        // Dictionary* dict = (Dictionary*)objectGroup->getObjects()->lastObject();
        // TODO: dict->setObject:[attributeDict objectForKey:@"points"] forKey:@"polylinePoints"];
    }

    if (attributeDict)
    {
        attributeDict->clear();
        delete attributeDict;
    }
}

void TMXMapInfo::endElement(void *ctx, const char *name)
{
    CC_UNUSED_PARAM(ctx);
    TMXMapInfo *pTMXMapInfo = this;
    std::string elementName = (char*)name;

    int len = 0;

    if(elementName == "data" && pTMXMapInfo->getLayerAttribs()&TMXLayerAttribBase64) 
    {
        pTMXMapInfo->setStoringCharacters(false);

        TMXLayerInfo* layer = (TMXLayerInfo*)pTMXMapInfo->getLayers()->lastObject();

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
            Size s = layer->_layerSize;
            // int sizeHint = s.width * s.height * sizeof(uint32_t);
            int sizeHint = (int)(s.width * s.height * sizeof(unsigned int));

            int inflatedLen = ZipUtils::ccInflateMemoryWithHint(buffer, len, &deflated, sizeHint);
            CCASSERT(inflatedLen == sizeHint, "");

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

void TMXMapInfo::textHandler(void *ctx, const char *ch, int len)
{
    CC_UNUSED_PARAM(ctx);
    TMXMapInfo *pTMXMapInfo = this;
    std::string pText((char*)ch,0,len);

    if (pTMXMapInfo->isStoringCharacters())
    {
        std::string currentString = pTMXMapInfo->getCurrentString();
        currentString += pText;
        pTMXMapInfo->setCurrentString(currentString.c_str());
    }
}

NS_CC_END

