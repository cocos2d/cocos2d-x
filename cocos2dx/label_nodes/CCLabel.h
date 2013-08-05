/****************************************************************************
 Copyright (c) 2013      Zynga Inc.

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


#ifndef _COCOS2D_CCLABEL_H_
#define _COCOS2D_CCLABEL_H_

#include "sprite_nodes/CCSpriteBatchNode.h"

NS_CC_BEGIN

enum class GlyphCollection {
    
    DYNAMIC,
    NEHE,
    ASCII,
    CUSTOM
    
};

class CC_DLL Label : public SpriteBatchNode, public LabelProtocol, public RGBAProtocol
{
public:
    
    static Label* createWithTTF( const char* label, const char* fntFilePath, int fontSize, GlyphCollection glyphs = GlyphCollection::NEHE, int lineSize = 0, const char *customGlyphs = 0 );
    static Label* createWithBMFont( const char* label, const char* bmfontFilePath, int lineSize = 0 );
    
    virtual ~Label();
             Label();
    
    virtual void setAlignment(TextHAlignment alignment)             = 0;
    virtual void setWidth(float width)                              = 0;
    virtual void setLineBreakWithoutSpace(bool breakWithoutSpace)   = 0;
    virtual void setScale(float scale)                              = 0;
    virtual void setScaleX(float scaleX)                            = 0;
    virtual void setScaleY(float scaleY)                            = 0;
    
    
    // needs to go - TEST STUFF /////////////////////////////////////////////////////////////////////////
    static Label* createWithBMFontOLD( const char* label, const char* bmfontFilePath, int lineSize = 0);
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    
private:
    
    
};

NS_CC_END

#endif /*__COCOS2D_CCLABEL_H */
