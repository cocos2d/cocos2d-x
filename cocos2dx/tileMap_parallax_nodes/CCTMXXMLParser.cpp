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
#include "CCTMXXMLParser.h"
#include "ccMacros.h"
#include "CCXFileUtils.h"
#include "CGPointExtension.h"
#include "support/base64.h"
#include "platform/platform.h"

namespace cocos2d {

	void tmx_startElement(void *ctx, const xmlChar *name, const xmlChar **atts);
	void tmx_endElement(void *ctx, const xmlChar *name);
	void tmx_characters(void *ctx, const xmlChar *ch, int len);

	// implementation CCTMXLayerInfo
	CCTMXLayerInfo::CCTMXLayerInfo()
	{
		m_bOwnTiles = true;
		m_uMinGID = 100000;
		m_uMaxGID = 0;
		m_sName = "";
		m_pTiles = NULL;
		m_tOffset = CGPointZero;
		m_pProperties= new StringToStringDictionary();;
	}
	CCTMXLayerInfo::~CCTMXLayerInfo()
	{
		CCLOGINFO("cocos2d: deallocing.");
		if (m_pProperties)
		{
			m_pProperties->clear();
			delete m_pProperties;
		}
		if( m_bOwnTiles && m_pTiles )
		{
			delete [] m_pTiles;
			m_pTiles = NULL;
		}
	}

	// implementation CCTMXTilesetInfo
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
		m_sFilename = CCFileUtils::fullPathFromRelativePath(tmxFile);
		m_pObjectGroups = new NSMutableArray<CCTMXObjectGroup*>();
		m_pProperties = new StringToStringDictionary();
		m_pTileProperties = new std::map<int, StringToStringDictionary*>();

		// tmp vars
		m_sCurrentString = "";
		m_bStoringCharacters = false;
		m_nLayerAttribs = TMXLayerAttribNone;
		m_nParentElement = TMXPropertyNone;

		return parseXMLFile(m_sFilename.c_str());
	}
	CCTMXMapInfo::~CCTMXMapInfo()
	{
		CCLOGINFO("cocos2d: deallocing.");
		m_pTilesets->release();
		m_pLayers->release();
		m_pObjectGroups->release();
		CCX_SAFE_DELETE(m_pProperties);
		CCX_SAFE_DELETE(m_pTileProperties);
	}

	bool CCTMXMapInfo::parseXMLFile(const char *xmlFilename)
	{
		FILE *fp = NULL;
		if( !(fp = fopen(xmlFilename, "r")) )
		{
			return NULL;
		}
		fseek(fp,0,SEEK_END);
		int size = ftell(fp);
		fseek(fp,0,SEEK_SET);
		char *buffer = new char[size+1];
		fread(buffer,sizeof(char),size,fp);
		fclose(fp);
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
		
		int result = xmlSAXUserParseMemory( &saxHandler, this, buffer, size );
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
		delete []buffer;
		return true;
	}

	/** Possible oritentations of the TMX map */
	enum
	{
		/** Orthogonal orientation */
		CCTMXOrientationOrtho,

		/** Hexagonal orientation */
		CCTMXOrientationHex,

		/** Isometric orientation */
		CCTMXOrientationIso,
	};/// @todo to be deleted


	// the XML parser calls here with all the elements
	void tmx_startElement(void *ctx, const xmlChar *name, const xmlChar **atts)
	{	
		CCTMXMapInfo *pTMXMapInfo = (CCTMXMapInfo*)(ctx);
		std::string elementName = (char*)name;
		StringToStringDictionary attributeDict;
		if(atts && atts[0])
		{
			for(int i = 0; atts[i]; i += 2) 
			{
				std::string key = (char*)atts[i];
				std::string value = (char*)atts[i+1];
				attributeDict.insert(StringToStringPair(key, value));
			}
		}
		if(elementName == "map")
		{
			std::string version = valueForKey("version", &attributeDict);
			if ( version != "1.0")
			{
				CCLOG("cocos2d: TMXFormat: Unsupported TMX version: %@", version);
			}
			std::string orientationStr = valueForKey("orientation", &attributeDict);
			if( orientationStr == "orthogonal")
				pTMXMapInfo->setOrientation(CCTMXOrientationOrtho);
			else if ( orientationStr  == "isometric")
				pTMXMapInfo->setOrientation(CCTMXOrientationIso);
			else if( orientationStr == "hexagonal")
				pTMXMapInfo->setOrientation(CCTMXOrientationHex);
			else
				CCLOG("cocos2d: TMXFomat: Unsupported orientation: %d", pTMXMapInfo->getOrientation());

			CGSize s;
			s.width = (float)atof(valueForKey("width", &attributeDict));
			s.height = (float)atof(valueForKey("height", &attributeDict));
			pTMXMapInfo->setMapSize(s);

			s.width = (float)atof(valueForKey("tilewidth", &attributeDict));
			s.height = (float)atof(valueForKey("tileheight", &attributeDict));
			pTMXMapInfo->setTileSize(s);

			// The parent element is now "map"
			pTMXMapInfo->setParentElement(TMXPropertyMap);
		} 
		else if(elementName == "tileset") 
		{
			// If this is an external tileset then start parsing that
			std::string externalTilesetFilename = valueForKey("source", &attributeDict);
			if (externalTilesetFilename != "")
			{
				externalTilesetFilename = CCFileUtils::fullPathFromRelativePath(externalTilesetFilename.c_str());
				pTMXMapInfo->parseXMLFile(externalTilesetFilename.c_str());
			}
			else
			{
				CCTMXTilesetInfo *tileset = new CCTMXTilesetInfo();
				tileset->m_sName = valueForKey("name", &attributeDict);
				tileset->m_uFirstGid = (unsigned int)atoi(valueForKey("firstgid", &attributeDict));
				tileset->m_uSpacing = (unsigned int)atoi(valueForKey("spacing", &attributeDict));
				tileset->m_uMargin = (unsigned int)atoi(valueForKey("margin", &attributeDict));
				CGSize s;
				s.width = (float)atof(valueForKey("tilewidth", &attributeDict));
				s.height = (float)atof(valueForKey("tileheight", &attributeDict));
				tileset->m_tTileSize = s;

				pTMXMapInfo->getTilesets()->addObject(tileset);
				tileset->release();
			}
		}
		else if(elementName == "tile")
		{
			CCTMXTilesetInfo* info = pTMXMapInfo->getTilesets()->getLastObject();
			StringToStringDictionary *dict = new StringToStringDictionary();
			pTMXMapInfo->setParentGID(info->m_uFirstGid + atoi(valueForKey("id", &attributeDict)));
			pTMXMapInfo->getTileProperties()->insert(std::pair<int, StringToStringDictionary*>(pTMXMapInfo->getParentGID(), dict));

			pTMXMapInfo->setParentElement(TMXPropertyTile);

		}
		else if(elementName == "layer")
		{
			CCTMXLayerInfo *layer = new CCTMXLayerInfo();
			layer->m_sName = valueForKey("name", &attributeDict);

			CGSize s;
			s.width = (float)atof(valueForKey("width", &attributeDict));
			s.height = (float)atof(valueForKey("height", &attributeDict));
			layer->m_tLayerSize = s;

			std::string visible = valueForKey("visible", &attributeDict);
			layer->m_bVisible = !(visible == "0");

			std::string opacity = valueForKey("opacity", &attributeDict);
			if( opacity != "" )
			{
				layer->m_cOpacity = (unsigned char)(255 * atof(opacity.c_str()));
			}
			else
			{
				layer->m_cOpacity = 255;
			}

			float x = (float)atof(valueForKey("x", &attributeDict));
			float y = (float)atof(valueForKey("y", &attributeDict));
			layer->m_tOffset = ccp(x,y);

			pTMXMapInfo->getLayers()->addObject(layer);
			layer->release();

			// The parent element is now "layer"
			pTMXMapInfo->setParentElement(TMXPropertyLayer);

		} 
		else if(elementName == "objectgroup")
		{
			CCTMXObjectGroup *objectGroup = new CCTMXObjectGroup();
			objectGroup->setGroupName(valueForKey("name", &attributeDict));
			CGPoint positionOffset;
			positionOffset.x = (float)atof(valueForKey("x", &attributeDict)) * pTMXMapInfo->getTileSize().width;
			positionOffset.y = (float)atof(valueForKey("y", &attributeDict)) * pTMXMapInfo->getTileSize().height;
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
			std::string imagename = valueForKey("source", &attributeDict);		
			tileset->m_sSourceImage = CCFileUtils::fullPathFromRelativePath(imagename.c_str());

		} 
		else if(elementName == "data")
		{
			std::string encoding = valueForKey("encoding", &attributeDict);
			std::string compression = valueForKey("compression", &attributeDict);

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
				NSAssert( compression == "gzip", "TMX: unsupported compression method" );
			}
			NSAssert( pTMXMapInfo->getLayerAttribs() != TMXLayerAttribNone, "TMX tile map: Only base64 and/or gzip maps are supported" );

		} 
		else if(elementName == "object")
		{
			char buffer[32];
			CCTMXObjectGroup *objectGroup = pTMXMapInfo->getObjectGroups()->getLastObject();

			// The value for "type" was blank or not a valid class name
			// Create an instance of TMXObjectInfo to store the object and its properties
			StringToStringDictionary *dict = new StringToStringDictionary();

			// Set the name of the object to the value for "name"
			std::string key = "name";
			std::string value = valueForKey("name", &attributeDict);
			dict->insert(StringToStringPair(key, value));

			// Assign all the attributes as key/name pairs in the properties dictionary
			key = "type";
			value = valueForKey("type", &attributeDict);
			dict->insert(StringToStringPair(key, value));

			int x = atoi(valueForKey("x", &attributeDict)) + (int)objectGroup->getPositionOffset().x;
			key = "x";
			value = itoa(x, buffer, 10);
			dict->insert(StringToStringPair(key, value));

			int y = atoi(valueForKey("y", &attributeDict)) + (int)objectGroup->getPositionOffset().y;
			// Correct y position. (Tiled uses Flipped, cocos2d uses Standard)
			y = (int)(pTMXMapInfo->getMapSize().height * pTMXMapInfo->getTileSize().height) - y - atoi(valueForKey("height", &attributeDict));
			key = "y";
			value = itoa(y, buffer, 10);
			dict->insert(StringToStringPair(key, value));

			key = "width";
			value = valueForKey("width", &attributeDict);
			dict->insert(StringToStringPair(key, value));

			key = "height";
			value = valueForKey("height", &attributeDict);
			dict->insert(StringToStringPair(key, value));

			// Add the object to the objectGroup
			objectGroup->getObjects()->insert(objectGroup->getObjects()->begin(), dict);

			// The parent element is now "object"
			pTMXMapInfo->setParentElement(TMXPropertyObject);

		} 
		else if(elementName == "property")
		{
			if ( pTMXMapInfo->getParentElement() == TMXPropertyNone ) 
			{
				CCLOG( "TMX tile map: Parent element is unsupported. Cannot add property named '%s' with value '%s'",
					valueForKey("name", &attributeDict), valueForKey("value",&attributeDict) );
			} 
			else if ( pTMXMapInfo->getParentElement() == TMXPropertyMap )
			{
				// The parent element is the map
				std::string value = valueForKey("value", &attributeDict);
				std::string key = valueForKey("name", &attributeDict);
				pTMXMapInfo->getProperties()->insert(StringToStringPair(key, value));

			} 
			else if ( pTMXMapInfo->getParentElement() == TMXPropertyLayer )
			{
				// The parent element is the last layer
				CCTMXLayerInfo *layer = pTMXMapInfo->getLayers()->getLastObject();
				std::string value = valueForKey("value", &attributeDict);
				std::string key = valueForKey("name", &attributeDict);
				// Add the property to the layer
				layer->m_pProperties->insert(StringToStringPair(key, value));

			} 
			else if ( pTMXMapInfo->getParentElement() == TMXPropertyObjectGroup ) 
			{
				// The parent element is the last object group
				CCTMXObjectGroup *objectGroup = pTMXMapInfo->getObjectGroups()->getLastObject();
				std::string key = valueForKey("name", &attributeDict);
				std::string value = valueForKey("value", &attributeDict);
				objectGroup->getProperties()->insert(StringToStringPair(key, value));

			} 
			else if ( pTMXMapInfo->getParentElement() == TMXPropertyObject )
			{
				// The parent element is the last object
				CCTMXObjectGroup *objectGroup = pTMXMapInfo->getObjectGroups()->getLastObject();
				StringToStringDictionary *dict = *objectGroup->getObjects()->begin();

				std::string propertyName = valueForKey("name", &attributeDict);
				std::string propertyValue = valueForKey("value", &attributeDict);

				dict->insert(StringToStringPair(propertyName, propertyValue));
			} 
			else if ( pTMXMapInfo->getParentElement() == TMXPropertyTile ) 
			{
				StringToStringDictionary *dict;
				dict = pTMXMapInfo->getTileProperties()->find(pTMXMapInfo->getParentGID())->second;
				std::string propertyName = valueForKey("name", &attributeDict);
				std::string propertyValue = valueForKey("value", &attributeDict);
				dict->insert(StringToStringPair(propertyName, propertyValue));
			}
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
				ZipUtils::inflateMemory(buffer, len, &deflated);
				free( buffer );

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
			pTMXMapInfo->setCurrentString(currentString);
		}
	}

}//namespace cocos2d