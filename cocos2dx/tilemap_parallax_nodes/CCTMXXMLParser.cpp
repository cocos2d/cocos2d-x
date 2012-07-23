/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
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
#endf
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
    : m_sName("")
    , m_pTiles(NULL)
    , m_bOwnTiles(true)
    , m_uMinGID(100000)
    , m_uMaxGID(0)        
    , m_tOffset(CCPointZero)
{
    m_pProperties= new CCDictionary();;
}
CCTMXLayerInfo::~CCTMXLayerInfo()
{
    CCLOGINFO("cocos2d: deallocing.");
    CC_SAFE_RELEASE(m_pProperties);
    if( m_bOwnTiles && m_pTiles )
    {
        delete [] m_pTiles;
        m_pTiles = NULL;
    }
}
CCDictionary * CCTMXLayerInfo::getProperties()
{
    return m_pProperties;
}
void CCTMXLayerInfo::setProperties(CCDictionary* var)
{
    CC_SAFE_RETAIN(var);
    CC_SAFE_RELEASE(m_pProperties);
    m_pProperties = var;
}

// implementation CCTMXTilesetInfo
CCTMXTilesetInfo::CCTMXTilesetInfo()
    :m_uFirstGid(0)
    ,m_tTileSize(CCSizeZero)
    ,m_uSpacing(0)
    ,m_uMargin(0)
    ,m_tImageSize(CCSizeZero)
{
}
CCTMXTilesetInfo::~CCTMXTilesetInfo()
{
    CCLOGINFO("cocos2d: deallocing.");
}
CCRect CCTMXTilesetInfo::rectForGID(unsigned int gid)
{
    CCRect rect;
    rect.size = m_tTileSize;
    gid &= kCCFlippedMask;
    gid = gid - m_uFirstGid;
    int max_x = (int)((m_tImageSize.width - m_uMargin*2 + m_uSpacing) / (m_tTileSize.width + m_uSpacing));
    //    int max_y = (imageSize.height - margin*2 + spacing) / (tileSize.height + spacing);
    rect.origin.x = (gid % max_x) * (m_tTileSize.width + m_uSpacing) + m_uMargin;
    rect.origin.y = (gid / max_x) * (m_tTileSize.height + m_uSpacing) + m_uMargin;
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
    m_pTilesets = CCArray::create();
    m_pTilesets->retain();

    m_pLayers = CCArray::create();
    m_pLayers->retain();

    if (tmxFileName != NULL)
    {
        m_sTMXFileName = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(tmxFileName);
    }
    
    if (resourcePath != NULL)
    {
        m_sResources = resourcePath;
    }
    
    m_pObjectGroups = CCArray::createWithCapacity(4);
    m_pObjectGroups->retain();

    m_pProperties = new CCDictionary();
    m_pTileProperties = new CCDictionary();

    // tmp vars
    m_sCurrentString = "";
    m_bStoringCharacters = false;
    m_nLayerAttribs = TMXLayerAttribNone;
    m_nParentElement = TMXPropertyNone;
}
bool CCTMXMapInfo::initWithXML(const char* tmxString, const char* resourcePath)
{
    internalInit(NULL, resourcePath);
    return parseXMLString(tmxString);
}

bool CCTMXMapInfo::initWithTMXFile(const char *tmxFile)
{
    internalInit(tmxFile, NULL);
    return parseXMLFile(m_sTMXFileName.c_str());
}

CCTMXMapInfo::CCTMXMapInfo()
    :m_tMapSize(CCSizeZero)    
    ,m_tTileSize(CCSizeZero)
    ,m_pLayers(NULL)
    ,m_pTilesets(NULL)
    ,m_pObjectGroups(NULL)
    ,m_nLayerAttribs(0)
    ,m_bStoringCharacters(false)        
    ,m_pProperties(NULL)
    ,m_pTileProperties(NULL)
{
}
CCTMXMapInfo::~CCTMXMapInfo()
{
    CCLOGINFO("cocos2d: deallocing.");
    CC_SAFE_RELEASE(m_pTilesets);
    CC_SAFE_RELEASE(m_pLayers);
    CC_SAFE_RELEASE(m_pProperties);
    CC_SAFE_RELEASE(m_pTileProperties);
    CC_SAFE_RELEASE(m_pObjectGroups);
}
CCArray* CCTMXMapInfo::getLayers()
{
    return m_pLayers;
}
void CCTMXMapInfo::setLayers(CCArray* var)
{
    CC_SAFE_RETAIN(var);
    CC_SAFE_RELEASE(m_pLayers);
    m_pLayers = var;
}
CCArray* CCTMXMapInfo::getTilesets()
{
    return m_pTilesets;
}
void CCTMXMapInfo::setTilesets(CCArray* var)
{
    CC_SAFE_RETAIN(var);
    CC_SAFE_RELEASE(m_pTilesets);
    m_pTilesets = var;
}
CCArray* CCTMXMapInfo::getObjectGroups()
{
    return m_pObjectGroups;
}
void CCTMXMapInfo::setObjectGroups(CCArray* var)
{
    CC_SAFE_RETAIN(var);
    CC_SAFE_RELEASE(m_pObjectGroups);
    m_pObjectGroups = var;
}
CCDictionary * CCTMXMapInfo::getProperties()
{
    return m_pProperties;
}
void CCTMXMapInfo::setProperties(CCDictionary* var)
{
    CC_SAFE_RETAIN(var);
    CC_SAFE_RELEASE(m_pProperties);
    m_pProperties = var;
}

CCDictionary* CCTMXMapInfo::getTileProperties()
{
    return m_pTileProperties;
}

void CCTMXMapInfo::setTileProperties(CCDictionary* tileProperties)
{
    CC_SAFE_RETAIN(tileProperties);
    CC_SAFE_RELEASE(m_pTileProperties);
    m_pTileProperties = tileProperties;
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

    return parser.parse(xmlFilename);    
}


// the XML parser calls here with all the elements
void CCTMXMapInfo::startElement(void *ctx, const char *name, const char **atts)
{    
    CC_UNUSED_PARAM(ctx);
    CCTMXMapInfo *pTMXMapInfo = this;
    std::string elementName = (char*)name;
    std::map<std::string, std::string> *attributeDict = new std::map<std::string, std::string>();
    if(atts && atts[0])
    {
        for(int i = 0; atts[i]; i += 2) 
        {
            std::string key = (char*)atts[i];
            std::string value = (char*)atts[i+1];
            attributeDict->insert(pair<std::string, std::string>(key, value));
        }
    }
    if(elementName == "map")
    {
        std::string version = valueForKey("version", attributeDict);
        if ( version != "1.0")
        {
            CCLOG("cocos2d: TMXFormat: Unsupported TMX version: %@", version.c_str());
        }
        std::string orientationStr = valueForKey("orientation", attributeDict);
        if( orientationStr == "orthogonal")
            pTMXMapInfo->setOrientation(CCTMXOrientationOrtho);
        else if ( orientationStr  == "isometric")
            pTMXMapInfo->setOrientation(CCTMXOrientationIso);
        else if( orientationStr == "hexagonal")
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
    else if(elementName == "tileset") 
    {
        // If this is an external tileset then start parsing that
        std::string externalTilesetFilename = valueForKey("source", attributeDict);
        if (externalTilesetFilename != "")
        {
            if (m_sTMXFileName.length() == 0)
            {
                string pszFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(m_sResources.c_str());
                if (pszFullPath.find_last_of("/\\") != pszFullPath.length()-1)
                {
                    pszFullPath.append("/");
                }
                
                externalTilesetFilename = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(externalTilesetFilename.c_str(), pszFullPath.c_str()  );
            }
            else
            {
                externalTilesetFilename = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(externalTilesetFilename.c_str(), pTMXMapInfo->getTMXFileName());
            }
            pTMXMapInfo->parseXMLFile(externalTilesetFilename.c_str());
        }
        else
        {
            CCTMXTilesetInfo *tileset = new CCTMXTilesetInfo();
            tileset->m_sName = valueForKey("name", attributeDict);
            tileset->m_uFirstGid = (unsigned int)atoi(valueForKey("firstgid", attributeDict));
            tileset->m_uSpacing = (unsigned int)atoi(valueForKey("spacing", attributeDict));
            tileset->m_uMargin = (unsigned int)atoi(valueForKey("margin", attributeDict));
            CCSize s;
            s.width = (float)atof(valueForKey("tilewidth", attributeDict));
            s.height = (float)atof(valueForKey("tileheight", attributeDict));
            tileset->m_tTileSize = s;

            pTMXMapInfo->getTilesets()->addObject(tileset);
            tileset->release();
        }
    }
    else if(elementName == "tile")
    {
        CCTMXTilesetInfo* info = (CCTMXTilesetInfo*)pTMXMapInfo->getTilesets()->lastObject();
        CCDictionary *dict = new CCDictionary();
        pTMXMapInfo->setParentGID(info->m_uFirstGid + atoi(valueForKey("id", attributeDict)));
        pTMXMapInfo->getTileProperties()->setObject(dict, pTMXMapInfo->getParentGID());
        CC_SAFE_RELEASE(dict);
        
        pTMXMapInfo->setParentElement(TMXPropertyTile);

    }
    else if(elementName == "layer")
    {
        CCTMXLayerInfo *layer = new CCTMXLayerInfo();
        layer->m_sName = valueForKey("name", attributeDict);

        CCSize s;
        s.width = (float)atof(valueForKey("width", attributeDict));
        s.height = (float)atof(valueForKey("height", attributeDict));
        layer->m_tLayerSize = s;

        std::string visible = valueForKey("visible", attributeDict);
        layer->m_bVisible = !(visible == "0");

        std::string opacity = valueForKey("opacity", attributeDict);
        if( opacity != "" )
        {
            layer->m_cOpacity = (unsigned char)(255 * atof(opacity.c_str()));
        }
        else
        {
            layer->m_cOpacity = 255;
        }

        float x = (float)atof(valueForKey("x", attributeDict));
        float y = (float)atof(valueForKey("y", attributeDict));
        layer->m_tOffset = ccp(x,y);

        pTMXMapInfo->getLayers()->addObject(layer);
        layer->release();

        // The parent element is now "layer"
        pTMXMapInfo->setParentElement(TMXPropertyLayer);

    } 
    else if(elementName == "objectgroup")
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
    else if(elementName == "image")
    {
        CCTMXTilesetInfo* tileset = (CCTMXTilesetInfo*)pTMXMapInfo->getTilesets()->lastObject();

        // build full path
        std::string imagename = valueForKey("source", attributeDict);
        if (m_sTMXFileName.length() == 0)
        {
            string pszFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(m_sResources.c_str());
            if (pszFullPath.find_last_of("/\\") != pszFullPath.length()-1)
            {
                pszFullPath.append("/");
            }

            tileset->m_sSourceImage = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(imagename.c_str(), pszFullPath.c_str()  );
        }
        else
        {
            tileset->m_sSourceImage = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(imagename.c_str(), pTMXMapInfo->getTMXFileName());
        }
    } 
    else if(elementName == "data")
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
    else if(elementName == "object")
    {
        char buffer[32] = {0};
        CCTMXObjectGroup* objectGroup = (CCTMXObjectGroup*)pTMXMapInfo->getObjectGroups()->lastObject();

        // The value for "type" was blank or not a valid class name
        // Create an instance of TMXObjectInfo to store the object and its properties
        CCDictionary *dict = new CCDictionary();
        // Parse everything automatically
        const char* pArray[] = {"name", "type", "width", "height", "gid"};
        
        for( int i = 0; i < sizeof(pArray)/sizeof(pArray[0]); ++i )
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
        if( value ) 
        {
            int x = atoi(value) + (int)objectGroup->getPositionOffset().x;
            sprintf(buffer, "%d", x);
            CCString* pStr = new CCString(buffer);
            pStr->autorelease();
            dict->setObject(pStr, "x");
        }

        // Y
        value = valueForKey("y", attributeDict);
        if( value )  {
            int y = atoi(value) + (int)objectGroup->getPositionOffset().y;

            // Correct y position. (Tiled uses Flipped, cocos2d uses Standard)
            y = (int)(m_tMapSize.height * m_tTileSize.height) - y - atoi(valueForKey("height", attributeDict));
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
    else if(elementName == "property")
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
        // CCTMXObjectGroup* objectGroup = (CCTMXObjectGroup*)m_pObjectGroups->lastObject();
        // CCDictionary* dict = (CCDictionary*)objectGroup->getObjects()->lastObject();
        // TODO: dict->setObject(attributeDict objectForKey:@"points"] forKey:@"polygonPoints"];

    } 
    else if (elementName == "polyline")
    {
        // find parent object's dict and add polyline-points to it
        // CCTMXObjectGroup* objectGroup = (CCTMXObjectGroup*)m_pObjectGroups->lastObject();
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
            CCSize s = layer->m_tLayerSize;
            // int sizeHint = s.width * s.height * sizeof(uint32_t);
            int sizeHint = (int)(s.width * s.height * sizeof(unsigned int));

            int inflatedLen = ZipUtils::ccInflateMemoryWithHint(buffer, len, &deflated, sizeHint);
            CCAssert(inflatedLen == sizeHint, "");

            inflatedLen = (size_t)&inflatedLen; // XXX: to avoid warings in compiler
            
            delete [] buffer;
            buffer = NULL;

            if( ! deflated ) 
            {
                CCLOG("cocos2d: TiledMap: inflate data error");
                return;
            }

            layer->m_pTiles = (unsigned int*) deflated;
        }
        else
        {
            layer->m_pTiles = (unsigned int*) buffer;
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

