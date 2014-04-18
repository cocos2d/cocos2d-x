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


NS_CC_BEGIN

namespace ui {
    
static int _calcCharCount(const char * pszText)
{
    int n = 0;
    char ch = 0;
    while ((ch = *pszText))
    {
        CC_BREAK_IF(! ch);
        
        if (0x80 != (0xC0 & ch))
        {
            ++n;
        }
        ++pszText;
    }
    return n;
}
    
bool RichElement::init(int tag, const Color3B &color, GLubyte opacity)
{
    _tag = tag;
    _color = color;
    _opacity = opacity;
    return true;
}
    
    
RichElementText* RichElementText::create(int tag, const Color3B &color, GLubyte opacity, const char *text, const char *fontName, float fontSize)
{
    RichElementText* element = new RichElementText();
    if (element && element->init(tag, color, opacity, text, fontName, fontSize))
    {
        element->autorelease();
        return element;
    }
    CC_SAFE_DELETE(element);
    return NULL;
}
    
bool RichElementText::init(int tag, const Color3B &color, GLubyte opacity, const char *text, const char *fontName, float fontSize)
{
    if (RichElement::init(tag, color, opacity))
    {
        _text = text;
        _fontName = fontName;
        _fontSize = fontSize;
        return true;
    }
    return false;
}

RichElementImage* RichElementImage::create(int tag, const Color3B &color, GLubyte opacity, const char *filePath)
{
    RichElementImage* element = new RichElementImage();
    if (element && element->init(tag, color, opacity, filePath))
    {
        element->autorelease();
        return element;
    }
    CC_SAFE_DELETE(element);
    return NULL;
}
    
bool RichElementImage::init(int tag, const Color3B &color, GLubyte opacity, const char *filePath)
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
    RichElementCustomNode* element = new RichElementCustomNode();
    if (element && element->init(tag, color, opacity, customNode))
    {
        element->autorelease();
        return element;
    }
    CC_SAFE_DELETE(element);
    return NULL;
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
}
    
RichText* RichText::create()
{
    RichText* widget = new RichText();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
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
    _elementRenderersContainer->setAnchorPoint(Vector2(0.5f, 0.5f));
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
    
void RichText::formatText()
{
    if (_formatTextDirty)
    {
        _elementRenderersContainer->removeAllChildren();
        _elementRenders.clear();
        if (_ignoreSize)
        {
            addNewLine();
            for (ssize_t i=0; i<_richElements.size(); i++)
            {
                RichElement* element = _richElements.at(i);
                Node* elementRenderer = NULL;
                switch (element->_type)
                {
                    case RICH_TEXT:
                    {
                        RichElementText* elmtText = static_cast<RichElementText*>(element);
                        if (FileUtils::getInstance()->isFileExist(elmtText->_fontName))
                        {
                            elementRenderer = Label::createWithTTF(elmtText->_text.c_str(), elmtText->_fontName, elmtText->_fontSize);
                        }
                        else
                        {
                            elementRenderer = Label::createWithSystemFont(elmtText->_text.c_str(), elmtText->_fontName, elmtText->_fontSize);
                        }
                        break;
                    }
                    case RICH_IMAGE:
                    {
                        RichElementImage* elmtImage = static_cast<RichElementImage*>(element);
                        elementRenderer = Sprite::create(elmtImage->_filePath.c_str());
                        break;
                    }
                    case RICH_CUSTOM:
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
                    case RICH_TEXT:
                    {
                        RichElementText* elmtText = static_cast<RichElementText*>(element);
                        handleTextRenderer(elmtText->_text.c_str(), elmtText->_fontName.c_str(), elmtText->_fontSize, elmtText->_color, elmtText->_opacity);
                        break;
                    }
                    case RICH_IMAGE:
                    {
                        RichElementImage* elmtImage = static_cast<RichElementImage*>(element);
                        handleImageRenderer(elmtImage->_filePath.c_str(), elmtImage->_color, elmtImage->_opacity);
                        break;
                    }
                    case RICH_CUSTOM:
                    {
                        RichElementCustomNode* elmtCustom = static_cast<RichElementCustomNode*>(element);
                        handleCustomRenderer(elmtCustom->_customNode);
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
    
void RichText::handleTextRenderer(const char *text, const char *fontName, float fontSize, const Color3B &color, GLubyte opacity)
{
    auto fileExist = FileUtils::getInstance()->isFileExist(fontName);
    Label* textRenderer = nullptr;
    if (fileExist)
    {
        textRenderer = Label::createWithTTF(text, fontName, fontSize);
    } 
    else
    {
        textRenderer = Label::createWithSystemFont(text, fontName, fontSize);
    }
    float textRendererWidth = textRenderer->getContentSize().width;
    _leftSpaceWidth -= textRendererWidth;
    if (_leftSpaceWidth < 0.0f)
    {
        float overstepPercent = (-_leftSpaceWidth) / textRendererWidth;
        std::string curText = text;
        size_t stringLength = _calcCharCount(text);
        int leftLength = stringLength * (1.0f - overstepPercent);
        std::string leftWords = curText.substr(0, leftLength);
        std::string cutWords = curText.substr(leftLength, curText.length()-1);
        if (leftLength > 0)
        {
            Label* leftRenderer = nullptr;
            if (fileExist)
            {
                leftRenderer = Label::createWithTTF(leftWords.substr(0, leftLength).c_str(), fontName, fontSize);
            } 
            else
            {
                leftRenderer = Label::createWithSystemFont(leftWords.substr(0, leftLength).c_str(), fontName, fontSize);
            }
            if (leftRenderer)
            {
                leftRenderer->setColor(color);
                leftRenderer->setOpacity(opacity);
                pushToContainer(leftRenderer);
            }
        }

        addNewLine();
        handleTextRenderer(cutWords.c_str(), fontName, fontSize, color, opacity);
    }
    else
    {
        textRenderer->setColor(color);
        textRenderer->setOpacity(opacity);
        pushToContainer(textRenderer);
    }
}
    
void RichText::handleImageRenderer(const char *fileParh, const Color3B &color, GLubyte opacity)
{
    Sprite* imageRenderer = Sprite::create(fileParh);
    handleCustomRenderer(imageRenderer);
}
    
void RichText::handleCustomRenderer(cocos2d::Node *renderer)
{
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
            l->setAnchorPoint(Vector2::ZERO);
            l->setPosition(Vector2(nextPosX, 0.0f));
            _elementRenderersContainer->addChild(l, 1, (int)j);
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
                l->setAnchorPoint(Vector2::ZERO);
                l->setPosition(Vector2(nextPosX, nextPosY));
                _elementRenderersContainer->addChild(l, 1, (int)(i*10 + j));
                nextPosX += l->getContentSize().width;
            }
        }
        _elementRenderersContainer->setContentSize(_size);
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
        _size = s;
    }
    else
    {
        _size = _customSize;
    }
    updateContentSizeWithTextureSize(_size);
    _elementRenderersContainer->setPosition(_contentSize.width / 2.0f, _contentSize.height / 2.0f);
}
    
void RichText::pushToContainer(cocos2d::Node *renderer)
{
    if (_elementRenders.size() <= 0)
    {
        return;
    }
    _elementRenders[_elementRenders.size()-1]->pushBack(renderer);
}

void RichText::visit(cocos2d::Renderer *renderer, const Matrix &parentTransform, bool parentTransformUpdated)
{
    if (_enabled)
    {
        formatText();
        Widget::visit(renderer, parentTransform, parentTransformUpdated);
    }
}
    
void RichText::setVerticalSpace(float space)
{
    _verticalSpace = space;
}
    
void RichText::setAnchorPoint(const Vector2 &pt)
{
    Widget::setAnchorPoint(pt);
    _elementRenderersContainer->setAnchorPoint(pt);
}
    
const Size& RichText::getVirtualRendererSize() const
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

}

NS_CC_END