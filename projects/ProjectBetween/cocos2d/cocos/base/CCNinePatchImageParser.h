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
 * A class for paring Android .9 patch image.
 * For more about Android .9 patch image format, please refer to
 * http://developer.android.com/tools/help/draw9patch.html
 *
 * The class could parse a single .9 patch image and produce the capInsets
 * as well as a sprite atlas and store all the capInsets infos in a Texture2D.
 *  Note:
 *  - Currently only PixelFormat::RGBA8888 is supported.
 *  - TexturePacker Trim mode is not supported at the moment.
 */

class CC_DLL NinePatchImageParser
{
public:
    /**
     * Determines whether a filename contains ".9.png" suffix.
     * @param filename A 9-patch image name.
     *
     * @return If the filename contains ".9.png", then return true, otherwise false.
     */
    static bool isNinePatchImage(const std::string& filename);

    /**
     * Default constructor.
     *
     */
    NinePatchImageParser();

    /**
     * Instantiate a NinePatchImageParser with a Image object.
     *
     * @param image A Image object pointer.
     *
     * @return A NinePatchImageParser instance.
     */
    explicit NinePatchImageParser(Image* image);

    /**
     * Instantiate a NinePatchImageParser with a Image object and the spriteFrame info.
     * The spriteFrame contains the frame rect in the image atlas and whether it
     * is rotated or not.
     *
     * @param image A Image object pointer.
     * @param frameRect The sprite frame rect in the image atlas.
     * @param rotated Whether is sprite frame is rotated in the image atlas.
     *
     * @return
     */
    NinePatchImageParser(Image* image, const Rect& frameRect, bool rotated);

    /**
     * Change the sprite frame info.
     * It is useful when parsing multiple sprite frame with only on NinePatchImageParser.
     *
     * @param frameRect The sprite frame rect in the image atlas.
     * @param rotated Whether is sprite frame is rotated in the image atlas.
     */
    void setSpriteFrameInfo(Image* image, const Rect& frameRect, bool rotated);

    /**
     * Default destructor.
     */
    virtual ~NinePatchImageParser();

    /**
     * Parsing the image data and extract the capInsets info.
     * @return The capInsets Rect.
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
