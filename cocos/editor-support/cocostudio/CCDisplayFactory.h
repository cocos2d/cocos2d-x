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

#ifndef __CCDISPLAYFACTORY_H__
#define __CCDISPLAYFACTORY_H__

#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCDatas.h"
#include "cocostudio/CocosStudioExport.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {

class Skin;
class Bone;
class DecorativeDisplay;
class DisplayData;
/**
 *  @js NA
 *  @lua NA
 */
class CC_STUDIO_DLL DisplayFactory
{
public:
    /*
    * @~english Add display.
    * @~chinese 增加显示。
    * @param bone @~english The bone.
    * @~chinese 骨头。
    * @param decoDisplay @~english `DecorativeDisplay` object.
    * @~chinese `DecorativeDisplay`对象。
    * @param displayData @~english Display data.
    * @~chinese 显示数据。
    */
    static void addDisplay(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData);
    /*
    * @~english Create display.
    * @~chinese 创建显示。
    * @param bone @~english The bone.
    * @~chinese 骨头。
    * @param decoDisplay @~english `DecorativeDisplay` object.
    * @~chinese `DecorativeDisplay`对象。
    */
    static void createDisplay(Bone *bone, DecorativeDisplay *decoDisplay);
    /*
    * @~english Update display.
    * @~chinese 更新显示。
    * @param bone @~english The bone.
    * @~chinese 骨头。
    * @param dt, @~english Delta time.
    * @~chinese 间隔时间。
    * @param dirty @~english Is dirty.
    * @~chinese 是否为脏。
    */
    static void updateDisplay(Bone *bone, float dt, bool dirty);

    /*
    * @~english Add sprite display.
    * @~chinese 增加精灵显示。
    * @param bone @~english The bone.
    * @~chinese 骨头。
    * @param decoDisplay @~english `DecorativeDisplay` object.
    * @~chinese `DecorativeDisplay`对象。
    * @param displayData @~english Display data.
    * @~chinese 显示数据。
    */
    static void addSpriteDisplay(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData);
    /*
    * @~english Create sprite display.
    * @~chinese 创建精灵显示。
    * @param bone @~english The bone.
    * @~chinese 骨头。
    * @param decoDisplay @~english `DecorativeDisplay` object.
    * @~chinese `DecorativeDisplay`对象。
    */
    static void createSpriteDisplay(Bone *bone, DecorativeDisplay *decoDisplay);
    /*
    * @~english Initialize sprite display.
    * @~chinese 初始化精灵显示。
    * @param bone @~english The bone.
    * @~chinese 骨头。
    * @param decoDisplay @~english `DecorativeDisplay` object.
    * @~chinese `DecorativeDisplay`对象。
    * @param displayName @~english Display name.
    * @~chinese 显示名称。
    * @param skin @~english The skin.
    * @~chinese 皮肤。
    */
    static void initSpriteDisplay(Bone *bone, DecorativeDisplay *decoDisplay, const char *displayName, Skin *skin);

    /*
    * @~english Add armature display.
    * @~chinese 增加骨骼显示。
    * @param bone @~english The bone.
    * @~chinese 骨头。
    * @param decoDisplay @~english `DecorativeDisplay` object.
    * @~chinese `DecorativeDisplay`对象。
    * @param displayData @~english Display data.
    * @~chinese 显示数据。
    */
    static void addArmatureDisplay(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData);
    /*
    * @~english Create armature display.
    * @~chinese 创建骨骼显示。
    * @param bone @~english The bone.
    * @~chinese 骨头。
    * @param decoDisplay @~english `DecorativeDisplay` object.
    * @~chinese `DecorativeDisplay`对象。
    */
    static void createArmatureDisplay(Bone *bone, DecorativeDisplay *decoDisplay);
    /*
    * @~english Update armature display.
    * @~chinese 更新骨骼显示。
    * @param bone @~english The bone.
    * @~chinese 骨头。
    * @param display @~english Display node.
    * @~chinese 显示节点。
    * @param dt, @~english Delta time.
    * @~chinese 间隔时间。
    */
    static void updateArmatureDisplay(Bone *bone, cocos2d::Node *display, float dt);

    /*
    * @~english Add particle display.
    * @~chinese 增加粒子显示。
    * @param bone @~english The bone.
    * @~chinese 骨头。
    * @param decoDisplay @~english `DecorativeDisplay` object.
    * @~chinese `DecorativeDisplay`对象。
    * @param displayData @~english Display data.
    * @~chinese 显示数据。
    */
    static void addParticleDisplay(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData);
    /*
    * @~english Create particle display.
    * @~chinese 创建粒子显示。
    * @param bone @~english The bone.
    * @~chinese 骨头。
    * @param decoDisplay @~english `DecorativeDisplay` object.
    * @~chinese `DecorativeDisplay`对象。
    */
    static void createParticleDisplay(Bone *bone, DecorativeDisplay *decoDisplay);
    /*
    * @~english Update particle display.
    * @~chinese 更新粒子显示。
    * @param bone @~english The bone.
    * @~chinese 骨头。
    * @param display @~english Display node.
    * @~chinese 显示节点。
    * @param dt, @~english Delta time.
    * @~chinese 间隔时间。
    */
    static void updateParticleDisplay(Bone *bone, cocos2d::Node *display, float dt);
};


}

#endif /*__CCDISPLAYFACTORY_H__*/
