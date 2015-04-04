/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#ifndef __UIRICHTEXT_H__
#define __UIRICHTEXT_H__

#include "ui/UIWidget.h"
#include "ui/GUIExport.h"
#include "2d/CCSprite.h"
#include "2d/CCLabel.h"
#include <set>

NS_CC_BEGIN

namespace ui {
    
class CC_GUI_DLL RichElement : public Ref
{
public:
    enum class Type
    {
        TEXT,
        IMAGE,
        CUSTOM
    };
    RichElement(){};
    virtual ~RichElement(){};
    bool init(int tag, const Color3B& color, GLubyte opacity);
protected:
    Type _type;
    int _tag;
    Color3B _color;
    GLubyte _opacity;
    friend class RichText;
};
    
class CC_GUI_DLL RichElementText : public RichElement
{
public:
    RichElementText(){_type = Type::TEXT;};
    virtual ~RichElementText(){};
    bool init(int tag, const Color3B& color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize,bool isUnderLine,bool isOutLine,const Color4B& outLineColor);
    static RichElementText* create(int tag, const Color3B& color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize,bool isUnderLine = false,bool isOutLine = false,const Color4B& outLineColor=Color4B::WHITE);
protected:
    std::string _text;
    std::string _fontName;
    float _fontSize;
	bool _isUnderLine;
    bool _isOutLine;
    Color4B _outLineColor;
    friend class RichText;
    
};
    
class CC_GUI_DLL RichElementImage : public RichElement
{
public:
    RichElementImage(){_type = Type::IMAGE;};
    virtual ~RichElementImage(){};
    bool init(int tag, const Color3B& color, GLubyte opacity, const std::string& filePath);
    static RichElementImage* create(int tag, const Color3B& color, GLubyte opacity, const std::string& filePath);
protected:
    std::string _filePath;
    Rect _textureRect;
    int _textureType;
    friend class RichText;
};
    
class CC_GUI_DLL RichElementCustomNode : public RichElement
{
public:
    RichElementCustomNode(){_type = Type::CUSTOM;};
    virtual ~RichElementCustomNode(){CC_SAFE_RELEASE(_customNode);};
    bool init(int tag, const Color3B& color, GLubyte opacity, Node* customNode);
    static RichElementCustomNode* create(int tag, const Color3B& color, GLubyte opacity, Node* customNode);
protected:
    Node* _customNode;
    friend class RichText;
};
    
class RichCacheElement : public Ref
{
public:
	RichCacheElement():_isUse(false),_node(nullptr){};
	virtual ~RichCacheElement();
	bool init(bool isUse, Node* node);
	static RichCacheElement* create(bool isUse, Node* node);
protected:
	bool _isUse;
	Node* _node;
	friend class RichText;
};

typedef std::vector< std::string > stringVector;
class CC_GUI_DLL RichText : public Widget
{
public:
    RichText();
    virtual ~RichText();
    static RichText* create();
    void insertElement(RichElement* element, int index);
    void pushBackElement(RichElement* element);
    void removeElement(int index);
    void removeElement(RichElement* element);

    void setVerticalSpace(float space);
    virtual void setAnchorPoint(const Vec2 &pt);
    virtual Size getVirtualRendererSize() const override;
	void cleanAllElement();
    void formatText();
    virtual void ignoreContentAdaptWithSize(bool ignore);
    virtual std::string getDescription() const override;
	Node* getContainer(){ return _elementRenderersContainer; };
	stringVector split(const std::string& s,const std::string& delim);
    
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    
protected:
    void onDraw(const Mat4 &transform, uint32_t flags);
    CustomCommand _customCommand;
    virtual void adaptRenderers();

    virtual void initRenderer();
    void pushToContainer(Node* renderer);
    void handleTextRenderer(const std::string& text, const std::string& fontName, float fontSize,bool isUnder, const Color3B& color, GLubyte opacity,int tag,bool isOutLine,const Color4B& outLineColor);
    void handleImageRenderer(const std::string& fileParh, const Color3B& color, GLubyte opacity,int tag);
    void handleCustomRenderer(Node* renderer,int tag);
    void formarRenderers();
    void addNewLine();

	Label* getCacheLabel();
	Sprite* getCacheImage();
	Node* makeLabel(Label* pTarget,const Color3B& color, const std::string& text, const std::string& fontName, int fontSize,bool isUnder, int tag,bool isOutLine,const Color4B& outLineColor);
	Node* makeImage(Sprite* pTarget, const std::string& filePath,int tag);
protected:
    bool _formatTextDirty;
    Vector<RichElement*> _richElements;
    std::vector<Vector<Node*>*> _elementRenders;
	Vector<RichCacheElement*> _cacheLabElements;
	Vector<RichCacheElement*> _cacheImgElements;
    std::set<int> _underLineTags;
    float _leftSpaceWidth;
    float _verticalSpace;
    Node* _elementRenderersContainer;
};
    
}

NS_CC_END

#endif /* defined(__UIRichText__) */
