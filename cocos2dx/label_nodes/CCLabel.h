///****************************************************************************
// Copyright (c) 2013      Zynga Inc.
//
// http://www.cocos2d-x.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// ****************************************************************************/
//
//
//#ifndef __COCOS2D_CCLABEL_H
//#define __COCOS2D_CCLABEL_H
//
//#include "CCSpriteBatchNode.h"
//
//NS_CC_BEGIN
//
//enum class GlyphCollection {
//    DYNAMIC,
//    NEHE,
//    ASCII,
//    CUSTOM
//};
//
//class CC_DLL Label : public SpriteBatchNode, public LabelProtocol, public RGBAProtocol
//{
//public:
//    static Label* createWithTTF( const char* label, const char* tttFilePath, int size, GlyphCollection glyphs = GlyphCollection::NEHE );
//    static Label* createWithBMFont( const char* label, const char* bmfontFilePath );
//
//    virtual ~Label();
//
//    bool initWithTTF( const char* label, const char* tttFilePath, int size, GlyphCollection glyphs = GlyphCollection::NEHE );
//    bool initWithBMFont( const char* label, const char* bmfontFilePath );
//
//    // UTF-8 collection
//    void setGlyphCollection( const char* glyphCollection  );
//    virtual void setHorizontalAlignment(TextAlignment alignment);
//    virtual void setVerticalAlignment(VerticalTextAlignment alignment);
//    virtual void setLineBreakWithoutSpace(bool breakWithoutSpace);
//
//    // Overrides
//    virtual void setString(const char *newString) override;
//    virtual const char* getString(void) const override;
//    virtual bool isOpacityModifyRGB() const override;
//    virtual void setOpacityModifyRGB(bool isOpacityModifyRGB) override;
//    virtual GLubyte getOpacity() const override;
//    virtual GLubyte getDisplayedOpacity() const override;
//    virtual void setOpacity(GLubyte opacity) override;
//    virtual void updateDisplayedOpacity(GLubyte parentOpacity) override;
//    virtual bool isCascadeOpacityEnabled() const override;
//    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled) override;
//    virtual const Color3B& getColor(void) const override;
//    virtual const Color3B& getDisplayedColor() const override;
//    virtual void setColor(const Color3B& color) override;
//    virtual void updateDisplayedColor(const Color3B& parentColor) override;
//    virtual bool isCascadeColorEnabled() const override;
//    virtual void setCascadeColorEnabled(bool cascadeColorEnabled) override;
//
//protected:
//
//private:
//    Label();
//
//};
//
//NS_CC_END
//
//#endif /*__COCOS2D_CCLABEL_H */
