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
#ifndef __CC_TM_XML_PARSER__
#define __CC_TM_XML_PARSER__
#include "NSMutableArray.h"
#include "NSMutableDictionary.h"
#include "CGGeometry.h"
#include "CCXCocos2dDefine.h"
namespace cocos2d {

	class CCTMXObjectGroup;

	/** @file
	* Internal TMX parser
	*
	* IMPORTANT: These classed should not be documented using doxygen strings
	* since the user should not use them.
	*
	*/

	enum {
		TMXLayerAttribNone = 1 << 0,
		TMXLayerAttribBase64 = 1 << 1,
		TMXLayerAttribGzip = 1 << 2,
	};

	enum {
		TMXPropertyNone,
		TMXPropertyMap,
		TMXPropertyLayer,
		TMXPropertyObjectGroup,
		TMXPropertyObject,
		TMXPropertyTile
	};

	/** @brief CCTMXLayerInfo contains the information about the layers like:
	- Layer name
	- Layer size
	- Layer opacity at creation time (it can be modified at runtime)
	- Whether the layer is visible (if it's not visible, then the CocosNode won't be created)

	This information is obtained from the TMX file.
	*/
	class CCX_DLL CCTMXLayerInfo : public NSObject
	{
		CCX_PROPERTY(CCXStringToStringDictionary*, m_pProperties, Properties);
	public:
		std::string			m_sName;
		CGSize				m_tLayerSize;
		unsigned int		*m_pTiles;
		bool				m_bVisible;
		unsigned char		m_cOpacity;
		bool				m_bOwnTiles;
		unsigned int		m_uMinGID;
		unsigned int		m_uMaxGID;
		CGPoint				m_tOffset;
	public:
		CCTMXLayerInfo();
		virtual ~CCTMXLayerInfo();
	};

	/** @brief CCTMXTilesetInfo contains the information about the tilesets like:
	- Tileset name
	- Tilset spacing
	- Tileset margin
	- size of the tiles
	- Image used for the tiles
	- Image size

	This information is obtained from the TMX file. 
	*/
	class CCX_DLL CCTMXTilesetInfo : public NSObject
	{
	public:
		std::string		m_sName;
		unsigned int	m_uFirstGid;
		CGSize			m_tTileSize;
		unsigned int	m_uSpacing;
		unsigned int	m_uMargin;
		//! filename containing the tiles (should be spritesheet / texture atlas)
		std::string		m_sSourceImage;
		//! size in pixels of the image
		CGSize			m_tImageSize;
	public:
		CCTMXTilesetInfo();
		virtual ~CCTMXTilesetInfo();
		CGRect rectForGID(unsigned int gid);
	};

	/** @brief CCTMXMapInfo contains the information about the map like:
	- Map orientation (hexagonal, isometric or orthogonal)
	- Tile size
	- Map size

	And it also contains:
	- Layers (an array of TMXLayerInfo objects)
	- Tilesets (an array of TMXTilesetInfo objects)
	- ObjectGroups (an array of TMXObjectGroupInfo objects)

	This information is obtained from the TMX file.

	*/
	class CCX_DLL CCTMXMapInfo : public NSObject
	{	
	public:	
		/// map orientation
		CCX_SYNTHESIZE(int,	m_nOrientation, Orientation);
		/// map width & height
		CCX_SYNTHESIZE(CGSize, m_tMapSize, MapSize);
		/// tiles width & height
		CCX_SYNTHESIZE(CGSize, m_tTileSize, TileSize);
		/// Layers
		CCX_PROPERTY(NSMutableArray<CCTMXLayerInfo*>*, m_pLayers, Layers);
		/// tilesets
		CCX_PROPERTY(NSMutableArray<CCTMXTilesetInfo*>*, m_pTilesets, Tilesets);
		/// ObjectGroups
		CCX_PROPERTY(NSMutableArray<CCTMXObjectGroup*>*, m_pObjectGroups, ObjectGroups);
		/// parent element
		CCX_SYNTHESIZE(int, m_nParentElement, ParentElement);
		/// parent GID
		CCX_SYNTHESIZE(unsigned int, m_uParentGID, ParentGID);
		/// layer attribs
		CCX_SYNTHESIZE(int, m_nLayerAttribs, LayerAttribs);
		/// is stroing characters?
		CCX_SYNTHESIZE(bool, m_bStoringCharacters, StoringCharacters);
		/// properties
		CCX_PROPERTY(CCXStringToStringDictionary*, m_pProperties, Properties);
	public:	
		CCTMXMapInfo();
		virtual ~CCTMXMapInfo();
		/** creates a TMX Format with a tmx file */
		static CCTMXMapInfo * formatWithTMXFile(const char *tmxFile);
		/** initializes a TMX format witha  tmx file */
		bool initWithTMXFile(const char *tmxFile);
		/** initalises parsing of an XML file, either a tmx (Map) file or tsx (Tileset) file */
		bool parseXMLFile(const char *xmlFilename);
	
		NSDictionary<int, CCXStringToStringDictionary*> * getTileProperties();
		void setTileProperties(NSDictionary<int, CCXStringToStringDictionary*> * tileProperties);

		inline const char* getCurrentString(){ return m_sCurrentString.c_str(); }
		inline void setCurrentString(const char *currentString){ m_sCurrentString = currentString; }
		inline const char* getTMXFileName(){ return m_sTMXFileName.c_str(); }
		inline void setTMXFileName(const char *fileName){ m_sTMXFileName = fileName; }

	protected:
		//! tmx filename
		std::string m_sTMXFileName;
		//! current string
		std::string m_sCurrentString;
		//! tile properties
		NSDictionary<int, CCXStringToStringDictionary*>* m_pTileProperties;
	};

}// namespace cocos2d
#endif //__CC_TM_XML_PARSER__



