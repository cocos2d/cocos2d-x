/****************************************************************************
Copyright (c) 2013-2017 Chukong Technologies Inc.

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
#include "ui/GUIExport.h"

NS_CC_BEGIN

/**
 * @addtogroup ui
 * @{
 */

class Label;
struct CC_DLL ResourceData;

namespace ui {
    
/**
 * @brief UI TextAtlas widget.
 */
class CC_GUI_DLL TextAtlas : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * Default constructor.
     *
     * @lua new
     */
    TextAtlas();
    
    /**
     * Default destructor.
     *
     * @lua NA
     */
    virtual ~TextAtlas();
    
    /**
     * Create a TexAtlas object.
     *
     * @return An autoreleased TextAtlas object.
     */
    static TextAtlas* create();
    
    /**
     * Create a LabelAtlas from a char map file.
     *
     * @param stringValue A given string needs to be displayed.
     * @param charMapFile A given char map file name.
     * @param itemWidth The element width.
     * @param itemHeight The element height.
     * @param startCharMap The starting char of the atlas.
     * @return An autoreleased TextAtlas object.
     */
    static TextAtlas* create(const std::string& stringValue,
                             const std::string& charMapFile,
                             int itemWidth,
                             int itemHeight,
                             const std::string& startCharMap);
    
    /** Initializes the LabelAtlas with a string, a char map file(the atlas), the width and height of each element and the starting char of the atlas.
     *
     * @param stringValue A given string needs to be displayed.
     * @param charMapFile A given char map file name.
     * @param itemWidth The element width.
     * @param itemHeight The element height.
     * @param startCharMap The starting char of the atlas.
     */
    
    void setProperty(const std::string& stringValue,
                     const std::string& charMapFile,
                     int itemWidth,
                     int itemHeight,
                     const std::string& startCharMap);
    
    /**Set string value for labelatlas.
     *
     * @param value A given string needs to be displayed.
     */
    CC_DEPRECATED_ATTRIBUTE void setStringValue(const std::string& value){this->setString(value);}
    void setString(const std::string& value);
    
    /**Get string value for labelatlas.
     *
     * @return The string value of TextAtlas.
     */
    CC_DEPRECATED_ATTRIBUTE const std::string& getStringValue() const{return this->getString();}
    const std::string& getString() const;
    
    /**
     * Gets the string length of the label.
     * Note: This length will be larger than the raw string length,
     * if you want to get the raw string length, you should call this->getString().size() instead
     *
     * @return  string length.
     */
    ssize_t getStringLength()const;
    
    //override "getVirtualRendererSize" method of widget.
    virtual Size getVirtualRendererSize() const override;
    
    //override "getVirtualRenderer" method of widget.
    virtual Node* getVirtualRenderer() override;
    
    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const override;
    
    /**
     * @js NA
     */
    virtual void adaptRenderers() override;

    ResourceData getRenderFile();

protected:
    virtual void initRenderer() override;
    virtual void onSizeChanged() override;
  
    void labelAtlasScaleChangedWithSize();
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
protected:
    Label* _labelAtlasRenderer;
    std::string _stringValue;
    std::string _charMapFileName;
    int _itemWidth;
    int _itemHeight;
    std::string _startCharMap;
    bool _labelAtlasRendererAdaptDirty;
};

}

// end of ui group
/// @}

NS_CC_END

#endif /* defined(__CocoGUI__LabelAtlas__) */
