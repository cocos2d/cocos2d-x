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

#ifndef __UIPANEL_H__
#define __UIPANEL_H__

#include "../BaseClasses/UIContainerWidget.h"

NS_CC_EXT_BEGIN

typedef enum
{
    PANEL_COLOR_NONE,
    PANEL_COLOR_SOLID,
    PANEL_COLOR_GRADIENT
}PanelColorType;

class UIPanel : public UIContainerWidget
{
public:
    UIPanel();
    virtual ~UIPanel();
    static UIPanel* create();
    void setBackGroundImage(const char* fileName,TextureResType texType = UI_TEX_TYPE_LOCAL);
    void setBackGroundImageCapInsets(const CCRect& capInsets);
    virtual void setBackGroundColorType(PanelColorType type);
    virtual void setSize(const CCSize &size);
    void setBackGroundImageScale9Enable(bool able);
    void setBackGroundColor(const ccColor3B &color);
    void setBackGroundColor(const ccColor3B &startColor, const ccColor3B &endColor);
    void setBackGroundColorOpacity(int opacity);
    void setBackGroundColorVector(const CCPoint &vector);
    virtual void setColor(const ccColor3B &color);
    virtual void setOpacity(int opacity);
    void removeBackGroundImage();
protected:
    virtual void initNodes();
    void addBackGroundImage();
protected:
    bool m_bBackGroundScale9Enable;
    CCNode* m_pBackGroundImage;
    std::string m_strBackGroundImageFileName;
    CCRect m_backGroundImageCapInsets;
    PanelColorType m_colorType;
    TextureResType m_eBGImageTexType;
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__UIPanel__) */
