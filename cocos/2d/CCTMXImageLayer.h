/****************************************************************************
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
#ifndef __CCTMX_IMAGE_LAYER_H__
#define __CCTMX_IMAGE_LAYER_H__

#include "CCSpriteBatchNode.h"
#include "CCTMXXMLParser.h"
NS_CC_BEGIN

class TMXMapInfo;
class TMXImageLayerInfo;

/**
 * @addtogroup tilemap_parallax_nodes
 * @{
 */

/** @brief CCTMXImageLayer represents the TMX imagelayer. */
class CC_DLL TMXImageLayer : public SpriteBatchNode
{
public:
    static TMXImageLayer* create( TMXImageLayerInfo*, TMXMapInfo* mapInfo );

    TMXImageLayer();
    virtual ~TMXImageLayer();

    bool init( TMXImageLayerInfo*, TMXMapInfo* );

    /** Information for the image layer */
    inline TMXImageLayerInfo* getTileSet() const { return _info; };
    inline void setTileSet( TMXImageLayerInfo* info ) {
        CC_SAFE_RETAIN( info );
        CC_SAFE_RELEASE( _info );
        _info = info;
    };
    
    /** Layer orientation, which is the same as the map orientation */
    inline int getLayerOrientation() const { return _orientation; };
    inline void setLayerOrientation( int orientation ) { _orientation = orientation; };
    
    // properties from the layer
    inline const ValueMap& getProperties() const { return _properties; };
    inline ValueMap& getProperties() { return _properties; };
    inline void setProperties( const ValueMap& properties ) {
        _properties = properties;
    };

    // TMXImageLayer doesn't support adding a Sprite manually.
    virtual void addChild( Node* child, int zOrder, int tag );

    // super method
    void removeChild( Node* child, bool cleanup );

    inline const char* getImageLayerName() const { return _name.c_str(); }
    inline void setImageLayerName( const char* name ) { _name = name; }

protected:
    // size of the imagelayer in tiles
    Size  _layerSize;

    // size of the map's tile (could be different from the tile's size)
    Size  _mapTileSize;

    // information for the layer
    TMXImageLayerInfo*  _info;

    // imagelayer orientation, which is the same as the map orientation
    int  _orientation;

    // properties from the imagelayer
    ValueMap  _properties;

    // name of the layer
    std::string  _name;
    
    // used for retina display
    float  _contentScaleFactor;            
};

// end of tilemap_parallax_nodes group
/// @}

NS_CC_END

#endif //__CCTMX_IMAGE_LAYER_H__
