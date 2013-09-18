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

#include "../BaseClasses/UIWidget.h"

NS_CC_EXT_BEGIN

class UICCLabelAtlas : public LabelAtlas
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
    void setProperty(const char *string, const char *charMapFile, unsigned int itemWidth, unsigned int itemHeight, unsigned int startCharMap);
    void setProperty(const char *string, Texture2D *texture, unsigned int itemWidth, unsigned int itemHeight, unsigned int startCharMap);
    virtual void updateDisplayedOpacity(GLubyte opacity);
    virtual void draw(void);
};

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
    void setProperty(const char* stringValue,const char* charMapFile, int itemWidth, int itemHeight, const char* startCharMap,bool useSpriteFrame = false);
    
    //set string value for labelatlas.
    void setStringValue(const char* value);
    
    //get string value for labelatlas.
    const char* getStringValue();
    
    //override "setAnchorPoint" method of widget.
    virtual void setAnchorPoint(const Point &pt);
    
    //override "getContentSize" method of widget.
    virtual const Size& getContentSize() const;
    
    //override "getVirtualRenderer" method of widget.
    virtual Node* getVirtualRenderer();
    
    /**
     * Returns the "class name" of widget.
     */
    virtual const char* getDescription() const;
protected:
    virtual void initRenderer();
    virtual void onSizeChanged();
    void labelAtlasScaleChangedWithSize();
protected:
    UICCLabelAtlas* _laberAtlasRenderer;
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__UILabelAtlas__) */
