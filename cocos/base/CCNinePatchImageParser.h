/****************************************************************************
 Copyright (c) 2013-2015 Chukong Technologies Inc.

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
#include "platform/CCPlatformMacros.h"
#include "math/CCGeometry.h"

NS_CC_BEGIN

class Image;
class SpriteFrame;


/**
 * @~english
 * A class for paring Android .9 patch image.
 * For more about Android .9 patch image format, please refer to
 * http://developer.android.com/tools/help/draw9patch.html
 *
 * The class could parse a single .9 patch image and produce the capInsets
 * as well as a sprite atlas and store all the capInsets infos in a Texture2D.
 *  Note:
 *  - Currently only PixelFormat::RGBA8888 is supported.
 *  - TexturePacker Trim mode is not supported at the moment.
 * @~chinese 
 * Android类 .9 patch image.
 * 更多关于Android。9 patch 图像格式,请参考
 * 网址:
 * http://developer.android.com/tools/help/draw9patch.html
 *
 * 类可以解析一个.9patch图像和产生capInsets
 * 以及一个Sprite地图集和存储所有capInsets Texture2D信息。
 * 注意:
 * ——目前只有PixelFormat::RGBA8888支持。
 * ——TexturePacker修剪模式不支持。
 */
class CC_DLL NinePatchImageParser
{
public:
    /**
     * @~english
     * Determines whether a filename contains ".9.png" suffix.
     * @~chinese 
     * 在决定是否一个文件名包含“.9.png”后缀。
     *
     * @param filename @~english A 9-patch image name.
     * @~chinese 9-patch图片的名字。
     * 
     * @return @~english If the filename contains ".9.png", then return true, otherwise false.
     * @~chinese 如果文件名包含“.9.png”,则返回true,否则返回false。
     */
    static bool isNinePatchImage(const std::string& filename);

    /**
     * @~english
     * Default constructor.
     *
     * @~chinese 
     * 默认构造函数。
     */
    NinePatchImageParser();

    /**
     * @~english
     * Instantiate a NinePatchImageParser with a Image object.
     *
     * @~chinese 
     * 实例化一个NinePatchImageParser图像对象。
     * 
     * @param image @~english A Image object pointer.
     *
     * @~chinese 一个图像对象的指针。
     * 
     * @return @~english A NinePatchImageParser instance.
     * @~chinese 一个NinePatchImageParser实例.
     */
    explicit NinePatchImageParser(Image* image);

    /**
     * @~english
     * Instantiate a NinePatchImageParser with a Image object and the spriteFrame info.
     * The spriteFrame contains the frame rect in the image atlas and whether it is rotated or not.
     *
     * @~chinese 
     * 实例化一个NinePatchImageParser图像对象和spriteFrame信息。
     * spriteFrame包含框架矩形图像中的atlas,无论是否旋转。
     * 
     * @param image @~english A Image object pointer.
     * @~chinese 一个图像对象的指针。
     * @param frameRect @~english The sprite frame rect in the image atlas.
     * @~chinese 从一个地图集中创建精灵框架矩形。
     * @param ratated @~english Whether is sprite frame is rotated in the image atlas.
     * @~chinese 地图集中的精灵帧图像是否旋转
     *
     * @return @~english Been is Sprite frame is rotated in the image atlas.
     * @~chinese 在图像集合中旋转过后的Sprite frame.
     */
    NinePatchImageParser(Image* image,  const Rect& frameRect, bool ratated);

    /**@~english
     * Change the sprite frame info.
     * It is useful when parsing multiple sprite frame with only on NinePatchImageParser.
     *
     * @~chinese 
     * 改变精灵帧信息。
     * 当解析多个精灵NinePatchImageParser帧是非常有用的。
     * 
     * @param frameRect @~english The sprite frame rect in the image atlas.
     * @~chinese 图片集中的精灵框架矩形图像。
     * @param rotated @~english Whether is sprite frame is rotated in the image atlas.
     * @~chinese 图像集中的图片是否旋转。
     */
    void setSpriteFrameInfo(Image* image, const Rect& frameRect, bool rotated);

    /**
     * @~english
     * Default destructor.
     * @~chinese 
     * 默认的析构函数。
     */
    virtual ~NinePatchImageParser();

    /**
     * @~english
     * Parsing the image data and extract the capInsets info.
     * @~chinese 
     * 解析图像数据并提取capInsets信息。
     * @return @~english The capInsets Rect.
     * @~chinese capInsets矩形。
     */
    Rect parseCapInset()const;
private:
    enum class Direction
    {
        HORIZONTAL,
        VERTICAL
    };
    int getPixelOriginOffset(Direction direction)const;
    Vec2 parseHorizontalMargin()const;
    Vec2 parseVerticalMargin()const;
    int getFrameWidth()const;
    int getFrameHeight()const;

    Image* _image;
    Rect _imageFrame;
    bool _isRotated;
};

NS_CC_END
