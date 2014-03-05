/****************************************************************************
 Copyright (c) 2013      Zynga Inc.
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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

#include "CCSpriteBatchNode.h"
#include "ccTypes.h"
#include "renderer/CCCustomCommand.h"
#include "CCFontAtlas.h"

NS_CC_BEGIN

enum class GlyphCollection {
    
    DYNAMIC,
    NEHE,
    ASCII,
    CUSTOM
};

enum class LabelEffect {

    NORMAL,
    OUTLINE,
    SHADOW,
    GLOW
};

typedef struct _ttfConfig
{
    std::string fontFilePath;
    int fontSize;
    GlyphCollection glyphs;
    const char *customGlyphs;
    bool distanceFieldEnabled;
    int outlineSize;

    _ttfConfig(const char* filePath = "",int size = 36, const GlyphCollection& glyphCollection = GlyphCollection::NEHE,
        const char *customGlyphCollection = nullptr,bool useDistanceField = false,int outline = 0)
        :fontFilePath(filePath)
        ,fontSize(size)
        ,glyphs(glyphCollection)
        ,customGlyphs(customGlyphCollection)
        ,distanceFieldEnabled(useDistanceField)
        ,outlineSize(outline)
    {
        if(outline > 0)
        {
            distanceFieldEnabled = false;
        }
    }
}TTFConfig;

class CC_DLL Label : public SpriteBatchNode, public LabelProtocol
{
public:
    static const int DefultFontSize;

    static Label* create();

    CC_DEPRECATED_ATTRIBUTE static Label* createWithTTF(const std::string& label, const std::string& fontFilePath, int fontSize, int lineSize = 0, TextHAlignment alignment = TextHAlignment::LEFT, GlyphCollection glyphs = GlyphCollection::NEHE, const char *customGlyphs = 0, bool useDistanceField = false);
    static Label* createWithTTF(const TTFConfig& ttfConfig, const std::string& text, TextHAlignment alignment = TextHAlignment::LEFT, int lineWidth = 0);
    
    static Label* createWithBMFont(const std::string& bmfontFilePath, const std::string& text,const TextHAlignment& alignment = TextHAlignment::LEFT, int lineWidth = 0, const Point& imageOffset = Point::ZERO);
    
    static Label * createWithCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);
    static Label * createWithCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap);
    static Label * createWithCharMap(const std::string& plistFile);

    virtual bool setTTFConfig(const TTFConfig& ttfConfig);

    virtual bool setBMFontFilePath(const std::string& bmfontFilePath, const Point& imageOffset = Point::ZERO);

    virtual bool setCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);
    virtual bool setCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap);
    virtual bool setCharMap(const std::string& plistFile);

    virtual void setString(const std::string& text) override;

    CC_DEPRECATED_ATTRIBUTE void setLabelEffect(LabelEffect effect,const Color3B& effectColor);

    /**
     * Enable shadow for the label
     *
     * @todo support blur for shadow effect
     */
    virtual void enableShadow(const Color3B& shadowColor = Color3B::BLACK,const Size &offset = Size(2,-2), float opacity = 0.75f, int blurRadius = 0);

    /** only support for TTF */
    virtual void enableOutline(const Color4B& outlineColor,int outlineSize = -1);

    /** only support for TTF */
    virtual void enableGlow(const Color3B& glowColor);

    /** disable shadow/outline/glow rendering */
    virtual void disableEffect();
    
    virtual void setAlignment(TextHAlignment alignment);
    CC_DEPRECATED_ATTRIBUTE void setWidth(float width) { setMaxLineWidth(width);}
    virtual void setMaxLineWidth(float width);
    virtual void setLineBreakWithoutSpace(bool breakWithoutSpace);
    virtual void setScale(float scale) override;
    virtual void setScaleX(float scaleX) override;
    virtual void setScaleY(float scaleY) override;
    virtual float getScaleX() const;
    virtual float getScaleY() const;

    virtual bool isOpacityModifyRGB() const override;
    virtual void setOpacityModifyRGB(bool isOpacityModifyRGB) override;
    virtual void setColor(const Color3B& color) override;

    virtual Sprite * getLetter(int lettetIndex);

    // font related stuff
    int getCommonLineHeight() const;  
    
    // string related stuff
    int getStringNumLines() const;
    int getStringLenght() const;
    TextHAlignment getTextAlignment() const;
    
    // label related stuff
    CC_DEPRECATED_ATTRIBUTE float getWidth() const { return getMaxLineWidth(); }
    float getMaxLineWidth() const;
    bool breakLineWithoutSpace() const;
    
    virtual const std::string& getString() const override {  return _originalUTF8String; }
    virtual void addChild(Node * child, int zOrder=0, int tag=0) override;

    virtual std::string getDescription() const override;
    virtual void visit(Renderer *renderer, const kmMat4 &parentTransform, bool parentTransformUpdated) override;
    virtual void draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated) override;

    FontAtlas* getFontAtlas() const {return _fontAtlas;}

protected:
    void onDraw(const kmMat4& transform, bool transformUpdated);

    struct LetterInfo
    {
        FontLetterDefinition def;

        Point position;
        Size  contentSize;
    };
    /**
    * @js NA
    */
    Label(FontAtlas *atlas = nullptr, TextHAlignment alignment = TextHAlignment::LEFT, bool useDistanceField = false,bool useA8Shader = false);
    /**
    * @js NA
    * @lua NA
    */
    virtual ~Label();

    virtual bool initWithFontAtlas(FontAtlas* atlas,bool distanceFieldEnabled = false, bool useA8Shader = false);

    // CCLabelTextFormat protocol implementation
    bool recordLetterInfo(const cocos2d::Point& point,const FontLetterDefinition& letterDef, int spriteIndex);
    bool recordPlaceholderInfo(int spriteIndex);

    void setFontScale(float fontScale);

    virtual bool init();
    
    virtual void alignText();
    
    bool computeHorizontalKernings(unsigned short int *stringToRender);
    bool setCurrentString(unsigned short *stringToSet);
    bool setOriginalString(unsigned short *stringToSet);
    void resetCurrentString();
    void computeStringNumLines();

    void updateSpriteWithLetterDefinition(const FontLetterDefinition &theDefinition, Texture2D *theTexture);

    virtual void updateColor() override;

    virtual void initProgram();

    void drawShadowWithoutBlur();

    //! used for optimization
    Sprite *_reusedLetter;
    Rect _reusedRect;
    std::vector<LetterInfo> _lettersInfo;

    float _commonLineHeight;
    bool  _lineBreakWithoutSpaces;
    float _maxLineWidth;
    TextHAlignment _alignment;
    unsigned short int * _currentUTF16String;
    unsigned short int * _originalUTF16String;
    std::string          _originalUTF8String;
    int * _horizontalKernings;
    FontAtlas * _fontAtlas;
    bool _isOpacityModifyRGB;

    bool _useDistanceField;
    bool _useA8Shader;
    float _fontScale;

    LabelEffect _currLabelEffect;
    Color3B _effectColor;

    GLuint _uniformEffectColor;

    CustomCommand _customCommand;
    int           _currNumLines;

    std::vector<SpriteBatchNode*> _batchNodes;

    Size    _shadowOffset;
    float   _shadowOpacity;
    int     _shadowBlurRadius;

    Color4B _outlineColor;

    TTFConfig _fontConfig;

    kmMat4 _parentTransform;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Label);

    friend class LabelTextFormatter;
};


NS_CC_END

#endif /*__COCOS2D_CCLABEL_H */
