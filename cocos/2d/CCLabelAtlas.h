/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2015 Chukong Technologies Inc.
 
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
#ifndef __CCLABEL_ATLAS_H__
#define __CCLABEL_ATLAS_H__

#include "CCAtlasNode.h"
#if CC_LABELATLAS_DEBUG_DRAW
#include "renderer/CCCustomCommand.h"
#include "2d/CCDrawNode.h"
#endif
NS_CC_BEGIN

/**
 * @addtogroup _2d
 * @{
 */

/** 
 * @class LabelAtlas
 * @brief LabelAtlas is a subclass of AtlasNode.
 *
 * It can be as a replacement of Label since it is MUCH faster.
 * 
 * LabelAtlas versus Label:
 * - LabelAtlas is MUCH faster than Label.
 * - LabelAtlas "characters" have a fixed height and width.
 * - LabelAtlas "characters" can be anything you want since they are taken from an image file.
 * 
 * A more flexible class is LabelBMFont. It supports variable width characters and it also has a nice editor.
 */
class CC_DLL LabelAtlas : public AtlasNode, public LabelProtocol
{
public:
    /** 
     * Creates an empty LabelAtlas.
     * User need to call initWithString(...) later to make this object work properly.
     */
    static LabelAtlas* create();
    
    /** Creates the LabelAtlas with a string, a char map file(the atlas), the width and height of each element and the starting char of the atlas. */
    static LabelAtlas* create(const std::string& string, const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);
    
    /**
     * Creates the LabelAtlas with a string and a configuration file.
     * @since v2.0
     */
    static LabelAtlas* create(const std::string& string, const std::string& fntFile);

    /** Initializes the LabelAtlas with a string, a char map file(the atlas), the width and height of each element and the starting char of the atlas. */
    bool initWithString(const std::string& string, const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);
    
    /** 
     * Initializes the LabelAtlas with a string and a configuration file.
     * @since v2.0
     */
    bool initWithString(const std::string& string, const std::string& fntFile);
    
    /** Initializes the LabelAtlas with a string, a texture, the width and height in points of each element and the starting char of the atlas */
    bool initWithString(const std::string& string, Texture2D* texture, int itemWidth, int itemHeight, int startCharMap);
    
    virtual void setString(const std::string &label) override;
    virtual const std::string& getString(void) const override;

    virtual void updateAtlasValues() override;
	/**
     * @js NA
     */
    virtual std::string getDescription() const override;

#if CC_LABELATLAS_DEBUG_DRAW
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
#endif

CC_CONSTRUCTOR_ACCESS:
    LabelAtlas()
    :_string("")
    {
#if CC_LABELATLAS_DEBUG_DRAW
        _debugDrawNode = DrawNode::create();
        addChild(_debugDrawNode);
#endif
    }

    virtual ~LabelAtlas()
    {
        _string.clear();
    }
    
protected:
    virtual void updateColor() override;

#if CC_LABELATLAS_DEBUG_DRAW
    DrawNode *_debugDrawNode;
#endif

    // string to render
    std::string _string;
    // the first char in the char map
    int _mapStartChar;
};

// end group
/// @}


NS_CC_END

#endif //__CCLABEL_ATLAS_H__
