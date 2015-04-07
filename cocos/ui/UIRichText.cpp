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

#include "UIRichText.h"
#include "platform/CCFileUtils.h"
#include "base/ccUTF8.h"
#include "ui/UIHelper.h"
#include "2d/CCDrawingPrimitives.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCCustomCommand.h"
#include "CCDirector.h"

NS_CC_BEGIN

namespace ui {

bool RichElement::init(int tag, const Color3B &color, GLubyte opacity)
{
    _tag = tag;
    _color = color;
    _opacity = opacity;
    return true;
}
    
    
RichElementText* RichElementText::create(int tag, const Color3B &color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize,bool isUnderLine)
{
    RichElementText* element = new (std::nothrow) RichElementText();
    if (element && element->init(tag, color, opacity, text, fontName, fontSize,isUnderLine))
    {
        element->autorelease();
        return element;
    }
    CC_SAFE_DELETE(element);
    return nullptr;
}
    
bool RichElementText::init(int tag, const Color3B &color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize,bool isUnderLine)
{
    if (RichElement::init(tag, color, opacity))
    {
        _text = text;
        _fontName = fontName;
        _fontSize = fontSize;
		_isUnderLine = isUnderLine;
        return true;
    }
    return false;
}

RichElementImage* RichElementImage::create(int tag, const Color3B &color, GLubyte opacity, const std::string& filePath)
{
    RichElementImage* element = new (std::nothrow) RichElementImage();
    if (element && element->init(tag, color, opacity, filePath))
    {
        element->autorelease();
        return element;
    }
    CC_SAFE_DELETE(element);
    return nullptr;
}
    
bool RichElementImage::init(int tag, const Color3B &color, GLubyte opacity, const std::string& filePath)
{
    if (RichElement::init(tag, color, opacity))
    {
        _filePath = filePath;
        return true;
    }
    return false;
}

RichElementCustomNode* RichElementCustomNode::create(int tag, const Color3B &color, GLubyte opacity, cocos2d::Node *customNode)
{
    RichElementCustomNode* element = new (std::nothrow) RichElementCustomNode();
    if (element && element->init(tag, color, opacity, customNode))
    {
        element->autorelease();
        return element;
    }
    CC_SAFE_DELETE(element);
    return nullptr;
}
    
bool RichElementCustomNode::init(int tag, const Color3B &color, GLubyte opacity, cocos2d::Node *customNode)
{
    if (RichElement::init(tag, color, opacity))
    {
        _customNode = customNode;
        _customNode->retain();
        return true;
    }
    return false;
}
    
bool RichCacheElement::init( bool isUse, Node* node )
{
	_isUse = isUse;
	_node = node;
	_node->retain();
	return true;
}

RichCacheElement* RichCacheElement::create( bool isUse, Node* node )
{
	RichCacheElement* element = new (std::nothrow) RichCacheElement();
	if (element && element->init(isUse,node))
	{
		element->autorelease();
		return element;
	}
	CC_SAFE_DELETE(element);
	return nullptr;
}

RichCacheElement::~RichCacheElement()
{
	if (_node) _node->release();
}


RichText::RichText():
_formatTextDirty(true),
_leftSpaceWidth(0.0f),
_verticalSpace(0.0f),
_elementRenderersContainer(nullptr)
{
    
}
    
RichText::~RichText()
{
    _richElements.clear();
	_cacheLabElements.clear();
	_cacheImgElements.clear();
}
    
RichText* RichText::create()
{
    RichText* widget = new (std::nothrow) RichText();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}
    
bool RichText::init()
{
    if (Widget::init())
    {
        return true;
    }
    return false;
}
    
void RichText::initRenderer()
{
    _elementRenderersContainer = Node::create();
    _elementRenderersContainer->setAnchorPoint(Vec2(0.5f, 0.5f));
    addProtectedChild(_elementRenderersContainer, 0, -1);
}

void RichText::insertElement(RichElement *element, int index)
{
    _richElements.insert(index, element);
    _formatTextDirty = true;
}
    
void RichText::pushBackElement(RichElement *element)
{
    _richElements.pushBack(element);
    _formatTextDirty = true;
}
    
void RichText::removeElement(int index)
{
    _richElements.erase(index);
    _formatTextDirty = true;
}
    
void RichText::removeElement(RichElement *element)
{
    _richElements.eraseObject(element);
    _formatTextDirty = true;
}

void RichText::cleanAllElement()
{
	_richElements.clear();
	auto len = _cacheImgElements.size();
	for (int i=0;i<len;i++)
	{
		_cacheImgElements.at(i)->_isUse = false;
		_cacheImgElements.at(i)->_node->removeFromParentAndCleanup(false);
	}

	len = _cacheLabElements.size();
	for (int i=0;i<len;i++)
	{
		_cacheLabElements.at(i)->_isUse = false;
		_cacheLabElements.at(i)->_node->removeFromParentAndCleanup(false);
	}
    _underLineTags.clear();
	_formatTextDirty = true;
}

void RichText::formatText()
{
    if (_formatTextDirty)
    {
        _elementRenderersContainer->removeAllChildrenWithCleanup(false);
        _elementRenders.clear();
        if (_ignoreSize)
        {
            addNewLine();
            for (ssize_t i=0; i<_richElements.size(); i++)
            {
                RichElement* element = _richElements.at(i);
                Node* elementRenderer = nullptr;
                switch (element->_type)
                {
                    case RichElement::Type::TEXT:
                    {
						RichElementText* elmtText = static_cast<RichElementText*>(element);
						elementRenderer = makeLabel(getCacheLabel(),elmtText->_text.c_str(), elmtText->_fontName, elmtText->_fontSize,elmtText->_isUnderLine,elmtText->_tag);
                        break;
                    }
                    case RichElement::Type::IMAGE:
                    {
                        RichElementImage* elmtImage = static_cast<RichElementImage*>(element);
						elementRenderer = makeImage(getCacheImage(),elmtImage->_filePath,elmtImage->_tag);
                        break;
                    }
                    case RichElement::Type::CUSTOM:
                    {
                        RichElementCustomNode* elmtCustom = static_cast<RichElementCustomNode*>(element);
                        elementRenderer = elmtCustom->_customNode;
                        break;
                    }
                    default:
                        break;
                }
                elementRenderer->setColor(element->_color);
                elementRenderer->setOpacity(element->_opacity);
                pushToContainer(elementRenderer);
            }
        }
        else
        {
            addNewLine();
            for (ssize_t i=0; i<_richElements.size(); i++)
            {
                
                RichElement* element = static_cast<RichElement*>(_richElements.at(i));
                switch (element->_type)
                {
                    case RichElement::Type::TEXT:
                    {
                        RichElementText* elmtText = static_cast<RichElementText*>(element);
                        handleTextRenderer(elmtText->_text.c_str(), elmtText->_fontName.c_str(), elmtText->_fontSize,elmtText->_isUnderLine, elmtText->_color, elmtText->_opacity,elmtText->_tag);
                        break;
                    }
                    case RichElement::Type::IMAGE:
                    {
                        RichElementImage* elmtImage = static_cast<RichElementImage*>(element);
                        handleImageRenderer(elmtImage->_filePath.c_str(), elmtImage->_color, elmtImage->_opacity,elmtImage->_tag);
                        break;
                    }
                    case RichElement::Type::CUSTOM:
                    {
                        RichElementCustomNode* elmtCustom = static_cast<RichElementCustomNode*>(element);
                        handleCustomRenderer(elmtCustom->_customNode,elmtCustom->_tag);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
        formarRenderers();
        _formatTextDirty = false;
    }
}
    
void RichText::handleTextRenderer(const std::string& text, const std::string& fontName, float fontSize, bool isUnder, const Color3B &color, GLubyte opacity,int tag)
{
    Node* textRenderer = nullptr;
    float textRendererWidth = 0;
    
    stringVector vect = split(text,"\n");
    if (vect.size() == 1 ){
        textRenderer = makeLabel(getCacheLabel(),text, fontName, fontSize,isUnder,tag);
        
        textRendererWidth = textRenderer->getContentSize().width;
        _leftSpaceWidth -= textRendererWidth;
        
        
        if (_leftSpaceWidth < 0.0f)
        {
            float overstepPercent = (-_leftSpaceWidth) / textRendererWidth;
            std::string curText = text;
            size_t stringLength = StringUtils::getCharacterCountInUTF8String(text);
            int leftLength = stringLength * (1.0f - overstepPercent);
            std::string leftWords = Helper::getSubStringOfUTF8String(curText,0,leftLength);
            std::string cutWords = Helper::getSubStringOfUTF8String(curText, leftLength, stringLength - leftLength);
            if (leftLength > 0)
            {
                Node* leftRenderer = nullptr;
                leftRenderer = makeLabel(getCacheLabel(),leftWords, fontName, fontSize,isUnder,tag);
                if (leftRenderer)
                {
                    leftRenderer->setColor(color);
                    leftRenderer->setOpacity(opacity);
                    pushToContainer(leftRenderer);
                }
            }
            
            addNewLine();
            handleTextRenderer(cutWords.c_str(), fontName, fontSize,isUnder, color, opacity,tag);
        }
        else
        {
            textRenderer->setColor(color);
            textRenderer->setOpacity(opacity);
            pushToContainer(textRenderer);
        }
        
    }else{
        auto len = vect.size();
        for (int i=0;i<len;i++)
        {
            std::string s = vect.at(i);
            textRenderer = makeLabel(getCacheLabel(),s, fontName, fontSize,isUnder,tag);
            textRenderer->setTag(tag);
            
            if (s == "") {
                ((Label*)textRenderer)->setString(" ");//hold on the new line
                pushToContainer(textRenderer);
                addNewLine();
                continue;
            }
            
            textRendererWidth = textRenderer->getContentSize().width;
            _leftSpaceWidth -= textRendererWidth;
            if (_leftSpaceWidth < 0.0f)
            {
                float overstepPercent = (-_leftSpaceWidth) / textRendererWidth;
                std::string curText = s;
                size_t stringLength = StringUtils::getCharacterCountInUTF8String(s);
                int leftLength = stringLength * (1.0f - overstepPercent);
                std::string leftWords = Helper::getSubStringOfUTF8String(curText,0,leftLength);
                std::string cutWords = Helper::getSubStringOfUTF8String(curText, leftLength, stringLength - leftLength);
                if (leftLength > 0)
                {
                    Node* leftRenderer = nullptr;
                    leftRenderer = makeLabel(getCacheLabel(),leftWords, fontName, fontSize,isUnder,tag);
                    if (leftRenderer)
                    {
                        leftRenderer->setColor(color);
                        leftRenderer->setOpacity(opacity);
                        pushToContainer(leftRenderer);
                    }
                }
                
                addNewLine();
                handleTextRenderer(cutWords.c_str(), fontName, fontSize,isUnder, color, opacity,tag);
            }else{		
                textRenderer->setColor(color);
                textRenderer->setOpacity(opacity);
                pushToContainer(textRenderer);
                addNewLine();
            }
        }
    }

}

    void RichText::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags)
    {
        _customCommand.init(_globalZOrder);
        _customCommand.func = CC_CALLBACK_0(RichText::onDraw, this, transform, flags);
        renderer->addCommand(&_customCommand);
    }
    
    void RichText::onDraw(const Mat4 &transform, uint32_t flags)
    {
        Director* director = Director::getInstance();
        director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
        director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
        
        auto children = _elementRenderersContainer->getChildren();
        int len = children.size();
            for (int i=0; i<len; i++) {
                Node* pChild = children.at(i);
                if (_underLineTags.count(pChild->getTag()) >= 1){
                    DrawPrimitives::setDrawColor4B(pChild->getDisplayedColor().r,
                                                   pChild->getDisplayedColor().g,
                                                   pChild->getDisplayedColor().b,
                                                   pChild->getDisplayedOpacity());
                    DrawPrimitives::setPointSize(2);
                    DrawPrimitives::drawLine(pChild->getPosition(),
                                            Vec2(pChild->getContentSize().width+pChild->getPosition().x,pChild->getPosition().y));
                }
        }
        //end draw
        director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    }
    
void RichText::handleImageRenderer(const std::string& fileParh, const Color3B &color, GLubyte opacity,int tag)
{
	Node* imageRenderer = makeImage(getCacheImage(),fileParh,tag);
    handleCustomRenderer(imageRenderer,tag);
}
    
void RichText::handleCustomRenderer(cocos2d::Node *renderer,int tag)
{
	renderer->setTag(tag);
    Size imgSize = renderer->getContentSize();
    _leftSpaceWidth -= imgSize.width;
    if (_leftSpaceWidth < 0.0f)
    {
        addNewLine();
        pushToContainer(renderer);
        _leftSpaceWidth -= imgSize.width;
    }
    else
    {
        pushToContainer(renderer);
    }
}
    
void RichText::addNewLine()
{
    _leftSpaceWidth = _customSize.width;
    _elementRenders.push_back(new Vector<Node*>());
}
    
void RichText::formarRenderers()
{
    if (_ignoreSize)
    {
        float newContentSizeWidth = 0.0f;
        float newContentSizeHeight = 0.0f;
        
        Vector<Node*>* row = (_elementRenders[0]);
        float nextPosX = 0.0f;
        for (ssize_t j=0; j<row->size(); j++)
        {
            Node* l = row->at(j);
            l->setAnchorPoint(Vec2::ZERO);
            l->setPosition(nextPosX, 0.0f);
            _elementRenderersContainer->addChild(l, 1);
            Size iSize = l->getContentSize();
            newContentSizeWidth += iSize.width;
            newContentSizeHeight = MAX(newContentSizeHeight, iSize.height);
            nextPosX += iSize.width;
        }
        _elementRenderersContainer->setContentSize(Size(newContentSizeWidth, newContentSizeHeight));
    }
    else
    {
        float newContentSizeHeight = 0.0f;
        float *maxHeights = new float[_elementRenders.size()];
        
        for (size_t i=0; i<_elementRenders.size(); i++)
        {
            Vector<Node*>* row = (_elementRenders[i]);
            float maxHeight = 0.0f;
            for (ssize_t j=0; j<row->size(); j++)
            {
                Node* l = row->at(j);
                maxHeight = MAX(l->getContentSize().height, maxHeight);
            }
            maxHeights[i] = maxHeight;
            newContentSizeHeight += maxHeights[i];
        }
        
        
        float nextPosY = _customSize.height;
        for (size_t i=0; i<_elementRenders.size(); i++)
        {
            Vector<Node*>* row = (_elementRenders[i]);
            float nextPosX = 0.0f;
            nextPosY -= (maxHeights[i] + _verticalSpace);
            
            for (ssize_t j=0; j<row->size(); j++)
            {
                Node* l = row->at(j);
                l->setAnchorPoint(Vec2::ZERO);
                l->setPosition(nextPosX, nextPosY);
                _elementRenderersContainer->addChild(l, 1);
                nextPosX += l->getContentSize().width;
            }
        }
        _elementRenderersContainer->setContentSize(_contentSize);
        delete [] maxHeights;
    }
    
    size_t length = _elementRenders.size();
    for (size_t i = 0; i<length; i++)
	{
        Vector<Node*>* l = _elementRenders[i];
        l->clear();
        delete l;
	}    
    _elementRenders.clear();
    
    if (_ignoreSize)
    {
        Size s = getVirtualRendererSize();
        this->setContentSize(s);
    }
    else
    {
        this->setContentSize(_customSize);
    }
    updateContentSizeWithTextureSize(_contentSize);
    _elementRenderersContainer->setPosition(_contentSize.width / 2.0f, _contentSize.height / 2.0f);
}
    
void RichText::adaptRenderers()
{
    this->formatText();
}
    
void RichText::pushToContainer(cocos2d::Node *renderer)
{
    if (_elementRenders.size() <= 0)
    {
        return;
    }
    _elementRenders[_elementRenders.size()-1]->pushBack(renderer);
}
    
void RichText::setVerticalSpace(float space)
{
    _verticalSpace = space;
}
    
void RichText::setAnchorPoint(const Vec2 &pt)
{
    Widget::setAnchorPoint(pt);
    _elementRenderersContainer->setAnchorPoint(pt);
}
    
Size RichText::getVirtualRendererSize() const
{
    return _elementRenderersContainer->getContentSize();
}
    
void RichText::ignoreContentAdaptWithSize(bool ignore)
{
    if (_ignoreSize != ignore)
    {
        _formatTextDirty = true;
        Widget::ignoreContentAdaptWithSize(ignore);
    }
}
    
std::string RichText::getDescription() const
{
    return "RichText";
}

Label* RichText::getCacheLabel()
{
	Label* ret = nullptr;
	auto len = _cacheLabElements.size();
	for (int i=0;i<len;i++)
	{
		RichCacheElement* pElement = _cacheLabElements.at(i);
		if (pElement->_isUse == false)
		{
			pElement->_isUse = true;
			ret = (Label*)pElement->_node;
			break;
		}
	}
	if (ret == nullptr){
		ret = Label::create();
		_cacheLabElements.pushBack(RichCacheElement::create(true,ret));
	}
	return ret;
}

Sprite* RichText::getCacheImage()
{
	Sprite* ret = nullptr;
	auto len = _cacheImgElements.size();
	for (int i=0;i<len;i++)
	{
		RichCacheElement* pElement = _cacheImgElements.at(i);
		if (pElement->_isUse == false)
		{
			pElement->_isUse = true;
			ret = (Sprite*)pElement->_node;
			break;
		}
	}
	if (ret == nullptr){
		ret = Sprite::create();
		_cacheImgElements.pushBack(RichCacheElement::create(true,ret));
	}
	return ret;
}

Node* RichText::makeLabel( Label* pTarget, const std::string& text, const std::string& fontName, int fontSize,bool isUnder,int tag)
{
    bool fileExist = FileUtils::getInstance()->isFileExist(fontName);
    if (fileExist) {
        TTFConfig ttfConfig(fontName.c_str(),fontSize,GlyphCollection::DYNAMIC);
        pTarget->setTTFConfig(ttfConfig);
    }else{
        pTarget->setSystemFontName(fontName);
        pTarget->setSystemFontSize(fontSize);
    }
    if (isUnder) {
        _underLineTags.insert(tag);
    }
    pTarget->setString(text);
    pTarget->setTag(tag);
	return pTarget;
}

Node* RichText::makeImage( Sprite* pTarget, const std::string& filePath,int tag )
{
	pTarget->setTexture(filePath);
    pTarget->setTag(tag);
	return pTarget;
}

//////////////////////////////////////////////////////////////////////////
std::vector< std::string > RichText::split(const std::string& s,const std::string& delim)
{
	std::vector< std::string > ret;
	size_t last = 0;
	size_t index=s.find_first_of(delim,last);
	while (index!=std::string::npos)
	{
		ret.push_back(s.substr(last,index-last));
		last=index+1;
		index=s.find_first_of(delim,last);
	}
	if (index-last>0)
	{
		ret.push_back(s.substr(last,index-last));
	}
	return ret;
}

}

NS_CC_END
