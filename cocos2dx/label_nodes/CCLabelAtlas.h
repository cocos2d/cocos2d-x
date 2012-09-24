/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
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
#ifndef __CCLABEL_ATLAS_H__
#define __CCLABEL_ATLAS_H__

#include "base_nodes/CCAtlasNode.h"

NS_CC_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup label
 * @{
 */

/** @brief CCLabelAtlas is a subclass of CCAtlasNode.

It can be as a replacement of CCLabel since it is MUCH faster.

CCLabelAtlas versus CCLabel:
- CCLabelAtlas is MUCH faster than CCLabel
- CCLabelAtlas "characters" have a fixed height and width
- CCLabelAtlas "characters" can be anything you want since they are taken from an image file

A more flexible class is CCLabelBMFont. It supports variable width characters and it also has a nice editor.
*/
class CC_DLL CCLabelAtlas : public CCAtlasNode, public CCLabelProtocol
{
public:
    CCLabelAtlas()
        :m_sString("")
    {}
    virtual ~CCLabelAtlas()
    { 
        m_sString.clear(); 
    }
    /** creates the CCLabelAtlas with a string, a char map file(the atlas), the width and height of each element and the starting char of the atlas 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCLabelAtlas * labelWithString(const char *string, const char *charMapFile, unsigned int itemWidth, unsigned int itemHeight, unsigned int startCharMap);
    
    /** creates the CCLabelAtlas with a string and a configuration file
    @deprecated: This interface will be deprecated sooner or later.
    @since v2.0
    */
    CC_DEPRECATED_ATTRIBUTE static CCLabelAtlas* labelWithString(const char *string, const char *fntFile);

    /** creates the CCLabelAtlas with a string, a char map file(the atlas), the width and height of each element and the starting char of the atlas */
    static CCLabelAtlas * create(const char *string, const char *charMapFile, unsigned int itemWidth, unsigned int itemHeight, unsigned int startCharMap);
    
    /** creates the CCLabelAtlas with a string and a configuration file
     @since v2.0
     */
    static CCLabelAtlas* create(const char *string, const char *fntFile);

    /** initializes the CCLabelAtlas with a string, a char map file(the atlas), the width and height of each element and the starting char of the atlas */
    bool initWithString(const char *string, const char *charMapFile, unsigned int itemWidth, unsigned int itemHeight, unsigned int startCharMap);
    
    /** initializes the CCLabelAtlas with a string and a configuration file
     @since v2.0
     */
    bool initWithString(const char *string, const char *fntFile);
    // super methods
    virtual void updateAtlasValues();
    virtual void setString(const char *label);
    virtual const char* getString(void);
#if CC_LABELATLAS_DEBUG_DRAW
    virtual void draw();
#endif

protected:
    // string to render
    std::string m_sString;
    // the first char in the charmap
    unsigned int m_uMapStartChar;
};

// end of GUI group
/// @}
/// @}


NS_CC_END

#endif //__CCLABEL_ATLAS_H__
