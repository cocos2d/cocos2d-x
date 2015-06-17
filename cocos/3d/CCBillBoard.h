/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

#ifndef __CCBILLBOARD_H__
#define __CCBILLBOARD_H__

#include "2d/CCSprite.h"

NS_CC_BEGIN
/**
 * @addtogroup _3d
 * @{
 */

/**
 * @class BillBoard
 * @brief @~english Inherit from Sprite, achieve BillBoard.
 * @~chinese BillBoard 用于实现3D场景的公告板功能，所谓的公告板，即始终朝向相机所在点，或始终朝向相机局部坐标系的XoY平面的2D精灵
 */
class CC_DLL BillBoard : public Sprite
{
public:

    /**
     * @~english Oriented mode
     * @~chinese 公告板的朝向模式
     */
    enum class Mode
    {
        /**
         * @~english Orient to the camera's position
         * @~chinese 朝向相机的所在位置
         */ 
        VIEW_POINT_ORIENTED, 
        /**
        * @~english Orient to the XOY plane of camera
        * @~chinese 朝向相机局部坐标系下的XoY平面
        */
        VIEW_PLANE_ORIENTED
    };

    /// @name Creators

    /**
     * @~english Creates an empty BillBoard without texture. You can call setTexture method subsequently.
     * @~chinese 创建一个空的，不带纹理的公告板，你可以在创建完成后，再调用setTexture方法赋予其纹理
     * @param mode @~english The BillBoard rotation mode
     * @~chinese 朝向类型
     * @return @~english An autoreleased BillBoard object.
     * @~chinese 被创建的公告板
     */
    static BillBoard* create(Mode mode = Mode::VIEW_POINT_ORIENTED);

    /**
     * @~english Creates a BillBoard with an image filename.
     * After creation, the rect of BillBoard will be the size of the image,
     * and the offset will be (0,0).
     * @~chinese 通过指定的图片文件路径创建一个公告板，在创建完成后，公告板将会和图片尺寸一样大，同时其锚点会被
     * 设置成Vec2(0, 0)
     * @param   filename @~english A path to image file, e.g., "scene1/monster.png"
     * @~chinese 图片文件的路径，如"scene1/monster.png"
     * @param mode @~english The billboard rotation mode
     * @~chinese 公告板的朝向类型
     * @return  @~english An autoreleased BillBoard object.
     * @~chinese 被创建的公告板
     */
    static BillBoard* create(const std::string& filename, Mode mode = Mode::VIEW_POINT_ORIENTED);

    /**
     * @~english Creates a BillBoard with an image filename and a rect.
     * @~chinese 通过指定图片文件路径以及待渲染区域矩形来创建公告板
     * @param   filename @~english A path to image file, e.g., "scene1/monster.png"
     * @~chinese 图片文件的路径
     * @param   rect @~english A subrect of the image file
     * @~chinese 待渲染区域矩形，必须要比图片的尺寸要小
     * @param   mode @~english Billboard mode
     * @~chinese 公告板的模式
     * @return  @~english An autoreleased BillBoard object
     * @~chinese 被创建的公告板
     */
    static BillBoard* create(const std::string& filename, const Rect& rect, Mode mode = Mode::VIEW_POINT_ORIENTED);

     /**
     * @~english Creates a BillBoard with a Texture2D object.
     *
     * After creation, the rect will be the size of the texture, and the offset will be (0,0).
     * @~chinese 通过一个指定的Texture2D对象来创建公告板，创建完成后，公告板将会与纹理尺寸一样大，锚点会被设为Vec2(0, 0)
     * @param   texture @~english A pointer to a Texture2D object.
     * @~chinese Texture2D对象
     * @param mode @~english The billBoard rotation mode.
     * @~chinese 公告板的朝向类型
     * @return @~english An autoreleased BillBoard object
     * @~chinese 被创建的公告板
     */
    static BillBoard* createWithTexture(Texture2D *texture, Mode mode = Mode::VIEW_POINT_ORIENTED);

    /**
     * @~english Set the billboard rotation mode. 
     * @~chinese 设置BillBoard对象的朝向类型
     * @param mode @~english The billboard roation mode.
     * @~chinese 朝向类型
     **/
    void setMode(Mode mode);

    /** 
     * @~english Get the billboard rotation mode. 
     * @~chinese 获取BillBoard的当前朝向类型
     * @return @~english The billboard rotation mode.
     * @~chinese 当前朝向类型
     **/
    Mode getMode() const;

    //override
    
    /** update billboard's transform and turn it towards camera */
    virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags) override;
    
    /** 
     * draw BillBoard object.
     *
     * @lua NA
     */
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;


CC_CONSTRUCTOR_ACCESS:
    BillBoard();
    virtual ~BillBoard();

protected:

    /**
     * calculate a model matrix which keep orignal translate & scaling but always face to the camera
     */
    bool calculateBillbaordTransform();
    
    Mat4 _camWorldMat;
    Mat4 _mvTransform;

    Mode _mode;
    bool _modeDirty;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(BillBoard);

};

// end of 3d group
/// @}

NS_CC_END


#endif // __CCBILLBOARD_H__
