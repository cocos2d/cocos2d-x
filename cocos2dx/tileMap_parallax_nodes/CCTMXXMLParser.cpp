/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include <map>
#include "CCTMXXMLParser.h"
#include "CCTMXTiledMap.h"
#include "ccMacros.h"
#include "support/file_support/FileData.h"
#include "support/zip_support/ZipUtils.h"
#include "CGPointExtension.h"
#include "support/base64.h"
#include "platform/platform.h"

namespace cocos2d {

	void tmx_startElement(void *ctx, const xmlChar *name, const xmlChar **atts);
	void tmx_endElement(void *ctx, const xmlChar *name);
	void tmx_characters(void *ctx, const xmlChar *ch, int len);
	const char* valueForKey(const char *key, std::map<std::string, std::string>* dict)
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
		:m_bOwnTiles(true)
		,m_uMinGID(100000)
		,m_uMaxGID(0)
		,m_sName("")
		,m_pTiles(NULL)
		,m_tOffset(CGPointZero)
	{
		m_pProperties= new CCXStringToStringDictionary();;
	}
	CCTMXLayerInfo::~CCTMXLayerInfo()
	{
		CCLOGINFO("cocos2d: deallocing.");
		CCX_SAFE_RELEASE(m_pProperties);
		if( m_bOwnTiles && m_pTiles )
		{
			delete [] m_pTiles;
			m_pTiles = NULL;
		}
	}
	CCXStringToStringDictionary * CCTMXLayerInfo::getProperties()
	{
		return m_pProperties;
	}
	void CCTMXLayerInfo::setProperties(CCXStringToStringDictionary* var)
	{
		CCX_SAFE_RETAIN(var);
		CCX_SAFE_RELEASE(m_pProperties);
		m_pProperties = var;
	}

	// implementation CCTMXTilesetInfo
	CCTMXTilesetInfo::CCTMXTilesetInfo()
		:m_uFirstGid(0)
		,m_tTileSize(CGSizeZero)
		,m_uSpacing(0)
		,m_uMargin(0)
		,m_tImageSize(CGSizeZero)
	{
	}
	CCTMXTilesetInfo::~CCTMXTilesetInfo()
	{
		CCLOGINFO("cocos2d: deallocing.");
	}
	CGRect CCTMXTilesetInfo::rectForGID(unsigned int gid)
	{
		CGRect rect;
		rect.size = m_tTileSize;
		gid = gid - m_uFirstGid;
		int max_x = (int)((m_tImageSize.width - m_uMargin*2 + m_uSpacing) / (m_tTileSize.width + m_uSpacing));
		//	int max_y = (imageSize.height - margin*2 + spacing) / (tileSize.height + spacing);
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
		CCX_SAFE_DELETE(pRet);
		return NULL;
	}
	bool CCTMXMapInfo::initWithTMXFile(const char *tmxFile)
	{
		m_pTilesets = new NSMutableArray<CCTMXTilesetInfo*>();
		m_pLayers = new NSMutableArray<CCTMXLayerInfo*>();
		m_sTMXFileName = CCFileUtils::fullPathFromRelativePath(tmxFile);
		m_pObjectGroups = new NSMutableArray<CCTMXObjectGroup*>();
		m_pProperties = new CCXStringToStringDictionary();
		m_pTileProperties = new NSDictionary<int, CCXStringToStringDictionary*>();

		// tmp vars
		m_sCurrentString = "";
		m_bStoringCharacters = false;
		m_nLayerAttribs = TMXLayerAttribNone;
		m_nParentElement = TMXPropertyNone;

		return parseXMLFile(m_sTMXFileName.c_str());
	}
	CCTMXMapInfo::CCTMXMapInfo()
		:m_bStoringCharacters(false)
		,m_nLayerAttribs(0)
		,m_tMapSize(CGSizeZero)
		,m_tTileSize(CGSizeZero)
		,m_pLayers(NULL)
		,m_pTilesets(NULL)
		,m_pObjectGroups(NULL)
		,m_pProperties(NULL)
		,m_pTileProperties(NULL)
	{
	}
	CCTMXMapInfo::~CCTMXMapInfo()
	{
		CCLOGINFO("cocos2d: deallocing.");
		CCX_SAFE_RELEASE(m_pTilesets);
		CCX_SAFE_RELEASE(m_pLayers);
		CCX_SAFE_RELEASE(m_pProperties);
		CCX_SAFE_RELEASE(m_pTileProperties);
		CCX_SAFE_RELEASE(m_pObjectGroups);
	}
	NSMutableArray<CCTMXLayerInfo*> * CCTMXMapInfo::getLayers()
	{
		return m_pLayers;
	}
	void CCTMXMapInfo::setLayers(NSMutableArray<CCTMXLayerInfo*>* var)
	{
		CCX_SAFE_RETAIN(var);
		CCX_SAFE_RELEASE(m_pLayers);
		m_pLayers = var;
	}
	NSMutableArray<CCTMXTilesetInfo*> * CCTMXMapInfo::getTilesets()
	{
		return m_pTilesets;
	}
	void CCTMXMapInfo::setTilesets(NSMutableArray<CCTMXTilesetInfo*>* var)
	{
		CCX_SAFE_RETAIN(var);
		CCX_SAFE_RELEASE(m_pTilesets);
		m_pTilesets = var;
	}
	NSMutableArray<CCTMXObjectGroup*> * CCTMXMapInfo::getObjectGroups()
	{
		return m_pObjectGroups;
	}
	void CCTMXMapInfo::setObjectGroups(NSMutableArray<CCTMXObjectGroup*>* var)
	{
		CCX_SAFE_RETAIN(var);
		CCX_SAFE_RELEASE(m_pObjectGroups);
		m_pObjectGroups = var;
	}
	CCXStringToStringDictionary * CCTMXMapInfo::getProperties()
	{
		return m_pProperties;
	}
	void CCTMXMapInfo::setProperties(CCXStringToStringDictionary* var)
	{
		CCX_SAFE_RETAIN(var);
		CCX_SAFE_RELEASE(m_pProperties);
		m_pProperties = var;
	}
	NSDictionary<int, CCXStringToStringDictionary*> * CCTMXMapInfo::getTileProperties()
	{
		return m_pTileProperties;
	}
	void CCTMXMapInfo::setTileProperties(NSDictionary<int, CCXStringToStringDictionary*> * tileProperties)
	{
		CCX_SAFE_RETAIN(tileProperties);
		CCX_SAFE_RELEASE(m_pTileProperties);
		m_pTileProperties = tileProperties;
	}

	bool CCTMXMapInfo::parseXMLFile(const char *xmlFilename)
	{
        FileData data;
        unsigned long size = 0;
        char *pBuffer = (char*) data.getFileData(xmlFilename, "r", &size);

        if (!pBuffer)
        {
            return false;
        }

		/*
		* this initialize the library and check potential ABI mismatches
		* between the version it was compiled for and the actual shared
		* library used.
		*/
		LIBXML_TEST_VERSION
			xmlSAXHandler saxHandler;
		memset( &saxHandler, 0, sizeof(saxHandler) );
		// Using xmlSAXVersion( &saxHandler, 2 ) generate crash as it sets plenty of other pointers...
		saxHandler.initialized = XML_SAX2_MAGIC;  // so we do this to force parsing as SAX2.
		saxHandler.startElement = &tmx_startElement;
		saxHandler.endElement = &tmx_endElement;
		saxHandler.characters = &tmx_characters;
		
		int result = xmlSAXUserParseMemory( &saxHandler, this, pBuffer, size );
		if ( result != 0 )
		{
			return false;
		}
		/*
		* Cleanup function for the XML library.
		*/
		xmlCleanupParser();
		/*
		* this is to debug memory for regression tests
		*/
		xmlMemoryDump();

		return true;
	}


	// the XML parser calls here with all the elements
	void tmx_startElement(void *ctx, const xmlChar *name, const xmlChar **atts)
	{	
		CCTMXMapInfo *pTMXMapInfo = (CCTMXMapInfo*)(ctx);
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
				CCLOG("cocos2d: TMXFormat: Unsupported TMX version: %@", version);
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

			CGSize s;
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
				externalTilesetFilename = CCFileUtils::fullPathFromRelativeFile(externalTilesetFilename.c_str(), pTMXMapInfo->getTMXFileName());
				pTMXMapInfo->parseXMLFile(externalTilesetFilename.c_str());
			}
			else
			{
				CCTMXTilesetInfo *tileset = new CCTMXTilesetInfo();
				tileset->m_sName = valueForKey("name", attributeDict);
				tileset->m_uFirstGid = (unsigned int)atoi(valueForKey("firstgid", attributeDict));
				tileset->m_uSpacing = (unsigned int)atoi(valueForKey("spacing", attributeDict));
				tileset->m_uMargin = (unsigned int)atoi(valueForKey("margin", attributeDict));
				CGSize s;
				s.width = (float)atof(valueForKey("tilewidth", attributeDict));
				s.height = (float)atof(valueForKey("tileheight", attributeDict));
				tileset->m_tTileSize = s;

				pTMXMapInfo->getTilesets()->addObject(tileset);
				tileset->release();
			}
		}
		else if(elementName == "tile")
		{
			CCTMXTilesetInfo* info = pTMXMapInfo->getTilesets()->getLastObject();
			CCXStringToStringDictionary *dict = new CCXStringToStringDictionary();
			pTMXMapInfo->setParentGID(info->m_uFirstGid + atoi(valueForKey("id", attributeDict)));
			pTMXMapInfo->getTileProperties()->setObject(dict, pTMXMapInfo->getParentGID());
			CCX_SAFE_RELEASE(dict);
			
			pTMXMapInfo->setParentElement(TMXPropertyTile);

		}
		else if(elementName == "layer")
		{
			CCTMXLayerInfo *layer = new CCTMXLayerInfo();
			layer->m_sName = valueForKey("name", attributeDict);

			CGSize s;
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
			CGPoint positionOffset;
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
			CCTMXTilesetInfo *tileset = pTMXMapInfo->getTilesets()->getLastObject();

			// build full path
			std::string imagename = valueForKey("source", attributeDict);		
			tileset->m_sSourceImage = CCFileUtils::fullPathFromRelativeFile(imagename.c_str(), pTMXMapInfo->getTMXFileName());

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
				}
				NSAssert( compression == "" || compression == "gzip", "TMX: unsupported compression method" );
			}
			NSAssert( pTMXMapInfo->getLayerAttribs() != TMXLayerAttribNone, "TMX tile map: Only base64 and/or gzip maps are supported" );

		} 
		else if(elementName == "object")
		{
			char buffer[32];
			CCTMXObjectGroup *objectGroup = pTMXMapInfo->getObjectGroups()->getLastObject();

			// The value for "type" was blank or not a valid class name
			// Create an instance of TMXObjectInfo to store the object and its properties
			CCXStringToStringDictionary *dict = new CCXStringToStringDictionary();

			// Set the name of the object to the value for "name"
			std::string key = "name";
			NSString *value = new NSString(valueForKey("name", attributeDict));
			dict->setObject(value, key);
			value->release();

			// Assign all the attributes as key/name pairs in the properties dictionary
			key = "type";
			value = new NSString(valueForKey("type", attributeDict));
			dict->setObject(value, key);
			value->release();

			int x = atoi(valueForKey("x", attributeDict)) + (int)objectGroup->getPositionOffset().x;
			key = "x";
			sprintf(buffer, "%d", x);
			value = new NSString(buffer);
			dict->setObject(value, key);
			value->release();

			int y = atoi(valueForKey("y", attributeDict)) + (int)objectGroup->getPositionOffset().y;
			// Correct y position. (Tiled uses Flipped, cocos2d uses Standard)
			y = (int)(pTMXMapInfo->getMapSize().height * pTMXMapInfo->getTileSize().height) - y - atoi(valueForKey("height", attributeDict));
			key = "y";
			sprintf(buffer, "%d", y);
			value = new NSString(buffer);
			dict->setObject(value, key);
			value->release();

			key = "width";
			value = new NSString(valueForKey("width", attributeDict));
			dict->setObject(value, key);
			value->release();

			key = "height";
			value = new NSString(valueForKey("height", attributeDict));
			dict->setObject(value, key);
			value->release();

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
				NSString *value = new NSString(valueForKey("value", attributeDict));
				std::string key = valueForKey("name", attributeDict);
				pTMXMapInfo->getProperties()->setObject(value, key);
				value->release();

			} 
			else if ( pTMXMapInfo->getParentElement() == TMXPropertyLayer )
			{
				// The parent element is the last layer
				CCTMXLayerInfo *layer = pTMXMapInfo->getLayers()->getLastObject();
				NSString *value = new NSString(valueForKey("value", attributeDict));
				std::string key = valueForKey("name", attributeDict);
				// Add the property to the layer
				layer->getProperties()->setObject(value, key);
				value->release();

			} 
			else if ( pTMXMapInfo->getParentElement() == TMXPropertyObjectGroup ) 
			{
				// The parent element is the last object group
				CCTMXObjectGroup *objectGroup = pTMXMapInfo->getObjectGroups()->getLastObject();
				NSString *value = new NSString(valueForKey("value", attributeDict));
				std::string key = valueForKey("name", attributeDict);
				objectGroup->getProperties()->setObject(value, key);
				value->release();

			} 
			else if ( pTMXMapInfo->getParentElement() == TMXPropertyObject )
			{
				// The parent element is the last object
				CCTMXObjectGroup *objectGroup = pTMXMapInfo->getObjectGroups()->getLastObject();
				CCXStringToStringDictionary *dict = objectGroup->getObjects()->getLastObject();

				std::string propertyName = valueForKey("name", attributeDict);
				NSString *propertyValue = new NSString(valueForKey("value", attributeDict));
				dict->setObject(propertyValue, propertyName);
				propertyValue->release();
			} 
			else if ( pTMXMapInfo->getParentElement() == TMXPropertyTile ) 
			{
				CCXStringToStringDictionary *dict;
				dict = pTMXMapInfo->getTileProperties()->objectForKey(pTMXMapInfo->getParentGID());

				std::string propertyName = valueForKey("name", attributeDict);
				NSString *propertyValue = new NSString(valueForKey("value", attributeDict));
				dict->setObject(propertyValue, propertyName);
				propertyValue->release();
			}
		}
		if (attributeDict)
		{
			attributeDict->clear();
			delete attributeDict;
		}
	}

	void tmx_endElement(void *ctx, const xmlChar *name)
	{
		CCTMXMapInfo *pTMXMapInfo = (CCTMXMapInfo*)(ctx);
		std::string elementName = (char*)name;

		int len = 0;

		if(elementName == "data" && pTMXMapInfo->getLayerAttribs()&TMXLayerAttribBase64) 
		{
			pTMXMapInfo->setStoringCharacters(false);

			CCTMXLayerInfo *layer = pTMXMapInfo->getLayers()->getLastObject();

			std::string currentString = pTMXMapInfo->getCurrentString();
			unsigned char *buffer;
			len = base64Decode((unsigned char*)currentString.c_str(), currentString.length(), &buffer);
			if( ! buffer ) 
			{
				CCLOG("cocos2d: TiledMap: decode data error");
				return;
			}

			if( pTMXMapInfo->getLayerAttribs() & TMXLayerAttribGzip )
			{
				unsigned char *deflated;
				ZipUtils::ccInflateMemory(buffer, len, &deflated);
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
	void tmx_characters(void *ctx, const xmlChar *ch, int len)
	{
		CCTMXMapInfo *pTMXMapInfo = (CCTMXMapInfo*)(ctx);
		std::string pText((char*)ch,0,len);

		if (pTMXMapInfo->getStoringCharacters())
		{
			std::string currentString = pTMXMapInfo->getCurrentString();
			currentString += pText;
			pTMXMapInfo->setCurrentString(currentString.c_str());
		}
	}

}//namespace cocos2d