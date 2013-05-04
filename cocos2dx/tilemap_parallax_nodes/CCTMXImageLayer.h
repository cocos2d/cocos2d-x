/****************************************************************************
Copyright (c) 2013 Andrey Syrokomsky

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

#include "sprite_nodes/CCSpriteBatchNode.h"
#include "CCTMXXMLParser.h"
NS_CC_BEGIN

class CCTMXMapInfo;
class CCTMXImageLayerInfo;
struct _ccCArray;

/**
 * @addtogroup tilemap_parallax_nodes
 * @{
 */

/** @brief CCTMXImageLayer represents the TMX imagelayer. */
class CC_DLL CCTMXImageLayer : public CCSpriteBatchNode
{
    /** size of the imagelayer in tiles */
    CC_SYNTHESIZE_PASS_BY_REF( CCSize, m_tSize, ImageLayerSize );
    /** size of the map's tile (could be different from the tile's size) */
    CC_SYNTHESIZE_PASS_BY_REF( CCSize, m_tMapTileSize, MapTileSize );
    /** information for the layer */
    CC_PROPERTY( CCTMXImageLayerInfo*, m_pInfo, Info );
    /** imagelayer orientation, which is the same as the map orientation */
    CC_SYNTHESIZE( unsigned int, m_uOrientation, ImageLayerOrientation );
    /** properties from the imagelayer */
    CC_PROPERTY( CCDictionary*, m_pProperties, Properties );


public:
    CCTMXImageLayer();
    virtual ~CCTMXImageLayer();
  
    static CCTMXImageLayer* create( CCTMXImageLayerInfo*, CCTMXMapInfo* mapInfo );

    bool init( CCTMXImageLayerInfo*, CCTMXMapInfo* );

    // CCTMXImageLayer doesn't support adding a CCSprite manually.
    virtual void addChild( CCNode * child, int zOrder, int tag );

    // super method
    void removeChild( CCNode* child, bool cleanup );

    inline const char* getImageLayerName() { return m_sName.c_str(); }
    inline void setImageLayerName( const char* name ) { m_sName = name; }

protected:
    //! name of the layer
    std::string  m_sName;
    
    // used for retina display
    float  m_fContentScaleFactor;            
};

// end of tilemap_parallax_nodes group
/// @}

NS_CC_END

#endif //__CCTMX_IMAGE_LAYER_H__
