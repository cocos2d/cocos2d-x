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

#ifndef __UILABELATLAS_H__
#define __UILABELATLAS_H__

#include "gui/UIWidget.h"

namespace gui {

/**
 *   @js NA
 *   @lua NA
 */
class UICCLabelAtlas : public cocos2d::LabelAtlas
{
public:
    /**
     * Default constructor
     */
    UICCLabelAtlas();
    
    /**
     * Default destructor
     */
    virtual ~UICCLabelAtlas();
    
    /**
     * Allocates and initializes.
     */
    static UICCLabelAtlas* create();
    void setProperty(const std::string& string, const std::string& charMapFile, unsigned int itemWidth, unsigned int itemHeight, unsigned int startCharMap);
    void setProperty(const std::string& string, cocos2d::Texture2D *texture, unsigned int itemWidth, unsigned int itemHeight, unsigned int startCharMap);
    virtual void updateDisplayedOpacity(GLubyte opacity) override;
    virtual void draw(void) override;
};
/**
 *   @js NA
 *   @lua NA
 */
class UILabelAtlas : public UIWidget
{
public:
    /**
     * Default constructor
     */
    UILabelAtlas();
    
    /**
     * Default destructor
     */
    virtual ~UILabelAtlas();
    
    /**
     * Allocates and initializes.
     */
    static UILabelAtlas* create();
    
    /** initializes the UILabelAtlas with a string, a char map file(the atlas), the width and height of each element and the starting char of the atlas */
    void setProperty(const std::string& stringValue,const std::string& charMapFile, int itemWidth, int itemHeight, const std::string& startCharMap);
    
    //set string value for labelatlas.
    void setStringValue(const std::string& value);
    
    //get string value for labelatlas.
    const std::string& getStringValue() const;
    
    //override "setAnchorPoint" method of widget.
    virtual void setAnchorPoint(const cocos2d::Point &pt) override;
    
    //override "getContentSize" method of widget.
    virtual const cocos2d::Size& getContentSize() const override;
    
    //override "getVirtualRenderer" method of widget.
    virtual cocos2d::Node* getVirtualRenderer() override;
    
    /**
     * Returns the "class name" of widget.
     */
    virtual const char* getDescription() const override;
    
protected:
    virtual void initRenderer() override;
    virtual void onSizeChanged() override;
    void labelAtlasScaleChangedWithSize();
    virtual UIWidget* createCloneInstance() override;
    virtual void copySpecialProperties(UIWidget* model) override;
protected:
    UICCLabelAtlas* _laberAtlasRenderer;
    std::string _stringValue;
    std::string _charMapFileName;
    int _itemWidth;
    int _itemHeight;
    std::string _startCharMap;
};

}

#endif /* defined(__CocoGUI__UILabelAtlas__) */
