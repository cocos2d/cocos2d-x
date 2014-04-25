/****************************************************************************
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

#ifndef __UILABELATLAS_H__
#define __UILABELATLAS_H__

#include "ui/UIWidget.h"

NS_CC_BEGIN

namespace ui {
    
/**
 *   @js NA
 *   @lua NA
 */
class TextAtlas : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * Default constructor
     */
    TextAtlas();
    
    /**
     * Default destructor
     */
    virtual ~TextAtlas();
    
    /**
     * Allocates and initializes.
     */
    static TextAtlas* create();
    
    /**
     * create a LabelAtlas from a char map file
     */
    static TextAtlas* create(const std::string& stringValue,
                             const std::string& charMapFile,
                             int itemWidth,
                             int itemHeight,
                             const std::string& startCharMap);
    
    /** initializes the LabelAtlas with a string, a char map file(the atlas), the width and height of each element and the starting char of the atlas */
    void setProperty(const std::string& stringValue,
                     const std::string& charMapFile,
                     int itemWidth,
                     int itemHeight,
                     const std::string& startCharMap);
    
    //set string value for labelatlas.
    void setStringValue(const std::string& value);
    
    //get string value for labelatlas.
    const std::string& getStringValue() const;
    
    //override "getVirtualRendererSize" method of widget.
    virtual const Size& getVirtualRendererSize() const override;
    
    //override "getVirtualRenderer" method of widget.
    virtual Node* getVirtualRenderer() override;
    
    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const override;
    
    virtual void adaptRenderers() override;
protected:
    virtual void initRenderer() override;
    virtual void onSizeChanged() override;
    virtual void updateTextureColor() override;
    virtual void updateTextureOpacity() override;
    virtual void updateTextureRGBA() override;
    void labelAtlasScaleChangedWithSize();
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
protected:
    LabelAtlas* _labelAtlasRenderer;
    std::string _stringValue;
    std::string _charMapFileName;
    int _itemWidth;
    int _itemHeight;
    std::string _startCharMap;
    bool _labelAtlasRendererAdaptDirty;
};

}
NS_CC_END

#endif /* defined(__CocoGUI__LabelAtlas__) */
