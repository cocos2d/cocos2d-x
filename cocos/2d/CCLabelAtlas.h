/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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
#ifndef __CCLABEL_ATLAS_H__
#define __CCLABEL_ATLAS_H__

#include "CCAtlasNode.h"
#if CC_LABELATLAS_DEBUG_DRAW
#include "renderer/CCCustomCommand.h"
#endif
NS_CC_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup label
 * @{
 */

/** @brief LabelAtlas 是 AtlasNode 的子类.

可以作为Label的一个替代品，因为LabelAtlas要快得多
 
LabelAtlas 与 Label:
- LabelAtlas 比 Label 要快非常多
- LabelAtlas "字符" 有固定的高度和宽度
- LabelAtlas "字符" 可以是任何你想要的字体效果，因为它们都是图片
 
还有一个更灵活的类是LabelBMFont. 它支持可变宽度的字符，而且他还有一个好用的编辑器
*/
class CC_DLL LabelAtlas : public AtlasNode, public LabelProtocol
{
public:
    /** 创建一个空的LabelAtlas, 用户需要在之后调用 initWithString(...) 方法使这个实例正常工作 **/
    static LabelAtlas* create();
    
    /** 使用字符串，字符映射文件（atlas），每个元素的宽度，高度和atlas起始字符创建LabelAtlas*/
    static LabelAtlas* create(const std::string& string, const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);
    
    /** 使用字符串和配置文件创建LabelAtlas
     @since v2.0
     */
    static LabelAtlas* create(const std::string& string, const std::string& fntFile);

    /** 使用字符串，字符映射文件（atlas），每个元素的宽度，高度和altas起始字符初始化LabelAtlas
     */
    bool initWithString(const std::string& string, const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);
    
    /** 使用字符串和配置文件初始化LabelAtlas
     @since v2.0
     */
    bool initWithString(const std::string& string, const std::string& fntFile);
    
    /** 使用字符串，纹理，每个元素的宽度，高度和atlas起始字符初始化LabelAtlas
     */
    bool initWithString(const std::string& string, Texture2D* texture, int itemWidth, int itemHeight, int startCharMap);
    
    // 父类方法
    virtual void updateAtlasValues();

    virtual void setString(const std::string &label) override;
    virtual const std::string& getString(void) const override;
    virtual std::string getDescription() const override;

#if CC_LABELATLAS_DEBUG_DRAW
    virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;
#endif

protected:
    LabelAtlas()
    :_string("")
    {}

    virtual ~LabelAtlas()
    {
        _string.clear();
    }
    virtual void updateColor() override;

#if CC_LABELATLAS_DEBUG_DRAW
    CustomCommand   _customDebugDrawCommand;
    void drawDebugData(const Mat4& transform, bool transformUpdated);
#endif

    // 渲染文字
    std::string _string;
    // 字符映射中的第一个字符
    int _mapStartChar;
};

// end of GUI group
/// @}
/// @}


NS_CC_END

#endif //__CCLABEL_ATLAS_H__
