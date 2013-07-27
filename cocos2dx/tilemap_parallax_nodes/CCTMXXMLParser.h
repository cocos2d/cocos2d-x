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


#ifndef __CC_TM_XML_PARSER__
#define __CC_TM_XML_PARSER__

#include "cocoa/CCArray.h"
#include "cocoa/CCDictionary.h"
#include "cocoa/CCGeometry.h"
#include "platform/CCSAXParser.h"

#include <string>

NS_CC_BEGIN

class TMXObjectGroup;

/** @file
* Internal TMX parser
*
* IMPORTANT: These classed should not be documented using doxygen strings
* since the user should not use them.
*
*/

/**
 * @addtogroup tilemap_parallax_nodes
 * @{
 */

enum {
    TMXLayerAttribNone = 1 << 0,
    TMXLayerAttribBase64 = 1 << 1,
    TMXLayerAttribGzip = 1 << 2,
    TMXLayerAttribZlib = 1 << 3,
};

enum {
    TMXPropertyNone,
    TMXPropertyMap,
    TMXPropertyLayer,
    TMXPropertyObjectGroup,
    TMXPropertyObject,
    TMXPropertyTile
};

typedef enum ccTMXTileFlags_ {
    kTMXTileHorizontalFlag        = 0x80000000,
    kTMXTileVerticalFlag            = 0x40000000,
    kTMXTileDiagonalFlag            = 0x20000000,
    kFlipedAll                    = (kTMXTileHorizontalFlag|kTMXTileVerticalFlag|kTMXTileDiagonalFlag),
    kFlippedMask                    = ~(kFlipedAll)
} ccTMXTileFlags;

// Bits on the far end of the 32-bit global tile ID (GID's) are used for tile flags

/** @brief TMXLayerInfo contains the information about the layers like:
- Layer name
- Layer size
- Layer opacity at creation time (it can be modified at runtime)
- Whether the layer is visible (if it's not visible, then the CocosNode won't be created)

This information is obtained from the TMX file.
*/
class CC_DLL TMXLayerInfo : public Object
{
public:
    TMXLayerInfo();
    virtual ~TMXLayerInfo();

    void setProperties(Dictionary *properties);
    Dictionary* getProperties();

    Dictionary          *_properties;
    std::string         _name;
    Size                _layerSize;
    unsigned int        *_tiles;
    bool                _visible;
    unsigned char       _opacity;
    bool                _ownTiles;
    unsigned int        _minGID;
    unsigned int        _maxGID;
    Point               _offset;
};

/** @brief TMXTilesetInfo contains the information about the tilesets like:
- Tileset name
- Tileset spacing
- Tileset margin
- size of the tiles
- Image used for the tiles
- Image size

This information is obtained from the TMX file. 
*/
class CC_DLL TMXTilesetInfo : public Object
{
public:
    std::string     _name;
    unsigned int    _firstGid;
    Size          _tileSize;
    unsigned int    _spacing;
    unsigned int    _margin;
    //! filename containing the tiles (should be spritesheet / texture atlas)
    std::string     _sourceImage;
    //! size in pixels of the image
    Size          _imageSize;
public:
    TMXTilesetInfo();
    virtual ~TMXTilesetInfo();
    Rect rectForGID(unsigned int gid);
};

/** @brief TMXMapInfo contains the information about the map like:
- Map orientation (hexagonal, isometric or orthogonal)
- Tile size
- Map size

And it also contains:
- Layers (an array of TMXLayerInfo objects)
- Tilesets (an array of TMXTilesetInfo objects)
- ObjectGroups (an array of TMXObjectGroupInfo objects)

This information is obtained from the TMX file.

*/
class CC_DLL TMXMapInfo : public Object, public SAXDelegator
{    
public:    
    /** creates a TMX Format with a tmx file */
    static TMXMapInfo * create(const char *tmxFile);
    /** creates a TMX Format with an XML string and a TMX resource path */
    static TMXMapInfo * createWithXML(const char* tmxString, const char* resourcePath);
    
    /** creates a TMX Format with a tmx file */
    CC_DEPRECATED_ATTRIBUTE static TMXMapInfo * formatWithTMXFile(const char *tmxFile) { return TMXMapInfo::create(tmxFile); };
    /** creates a TMX Format with an XML string and a TMX resource path */
    CC_DEPRECATED_ATTRIBUTE static TMXMapInfo * formatWithXML(const char* tmxString, const char* resourcePath) { return TMXMapInfo::createWithXML(tmxString, resourcePath); };
    
    TMXMapInfo();
    virtual ~TMXMapInfo();
    
    /** initializes a TMX format with a  tmx file */
    bool initWithTMXFile(const char *tmxFile);
    /** initializes a TMX format with an XML string and a TMX resource path */
    bool initWithXML(const char* tmxString, const char* resourcePath);
    /** initializes parsing of an XML file, either a tmx (Map) file or tsx (Tileset) file */
    bool parseXMLFile(const char *xmlFilename);
    /* initializes parsing of an XML string, either a tmx (Map) string or tsx (Tileset) string */
    bool parseXMLString(const char *xmlString);

    Dictionary* getTileProperties() { return _tileProperties; };
    void setTileProperties(Dictionary* tileProperties) {
        CC_SAFE_RETAIN(tileProperties);
        CC_SAFE_RELEASE(_tileProperties);
        _tileProperties = tileProperties;
    };

    /// map orientation
    inline int getOrientation() const { return _orientation; };
    inline void setOrientation(int orientation) { _orientation = orientation; };

    /// map width & height
    inline const Size& getMapSize() const { return _mapSize; };
    inline void setMapSize(const Size& mapSize) { _mapSize = mapSize; };

    /// tiles width & height
    inline const Size& getTileSize() const { return _tileSize; };
    inline void setTileSize(const Size& tileSize) { _tileSize = tileSize; };
    
    /// Layers
    inline Array* getLayers() const { return _layers; };
    inline void setLayers(Array* layers) {
        CC_SAFE_RETAIN(layers);
        CC_SAFE_RELEASE(_layers);
        _layers = layers;
    };

    /// tilesets
    inline Array* getTilesets() const { return _tilesets; };
    inline void setTilesets(Array* tilesets) {
        CC_SAFE_RETAIN(tilesets);
        CC_SAFE_RELEASE(_tilesets);
        _tilesets = tilesets;
    };

    /// ObjectGroups
    inline Array* getObjectGroups() const { return _objectGroups; };
    inline void setObjectGroups(Array* groups) {
        CC_SAFE_RETAIN(groups);
        CC_SAFE_RELEASE(_objectGroups);
        _objectGroups = groups;
    };

    /// parent element
    inline int getParentElement() const { return _parentElement; };
    inline void setParentElement(int element) { _parentElement = element; };

    /// parent GID
    inline unsigned int getParentGID() const { return _parentGID; };
    inline void setParentGID(unsigned int gid) { _parentGID = gid; };

    /// layer attribs
    inline int getLayerAttribs() const { return _layerAttribs; };
    inline void setLayerAttribs(int layerAttribs) { _layerAttribs = layerAttribs; };

    /// is storing characters?
    inline bool isStoringCharacters() const { return _storingCharacters; };
    CC_DEPRECATED_ATTRIBUTE inline bool getStoringCharacters() const { return isStoringCharacters(); };
    inline void setStoringCharacters(bool storingCharacters) { _storingCharacters = storingCharacters; };

    /// properties
    inline Dictionary* getProperties() const { return _properties; };
    inline void setProperties(Dictionary* properties) {
        CC_SAFE_RETAIN(properties);
        CC_SAFE_RELEASE(_properties);
        _properties = properties;
    };
    
    // implement pure virtual methods of SAXDelegator
    void startElement(void *ctx, const char *name, const char **atts);
    void endElement(void *ctx, const char *name);
    void textHandler(void *ctx, const char *ch, int len);
    
    inline const char* getCurrentString(){ return _currentString.c_str(); }
    inline void setCurrentString(const char *currentString){ _currentString = currentString; }
    inline const char* getTMXFileName(){ return _TMXFileName.c_str(); }
    inline void setTMXFileName(const char *fileName){ _TMXFileName = fileName; }
private:
    void internalInit(const char* tmxFileName, const char* resourcePath);
protected:

    /// map orientation
    int    _orientation;
    /// map width & height
    Size _mapSize;
    /// tiles width & height
    Size _tileSize;
    /// Layers
    Array* _layers;
    /// tilesets
    Array* _tilesets;
    /// ObjectGroups
    Array* _objectGroups;
    /// parent element
    int _parentElement;
    /// parent GID
    unsigned int _parentGID;
    /// layer attribs
    int _layerAttribs;
    /// is storing characters?
    bool _storingCharacters;
    /// properties
    Dictionary* _properties;
    
    //! tmx filename
    std::string _TMXFileName;
    // tmx resource path
    std::string _resources;
    //! current string
    std::string _currentString;
    //! tile properties
    Dictionary* _tileProperties;
    unsigned int _currentFirstGID;
};

// end of tilemap_parallax_nodes group
/// @}

NS_CC_END

#endif

