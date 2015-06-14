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

#ifndef __CCDECORATIVEDISPLAY_H__
#define __CCDECORATIVEDISPLAY_H__

#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCDisplayFactory.h"
#include "cocostudio/CCDatas.h"
#include "cocostudio/CocosStudioExport.h"


#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT || ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
#include "cocostudio/CCColliderDetector.h"
#endif

namespace cocos2d {
    class Node;
}

namespace cocostudio {
/**
 *  @js NA
 *  @lua NA
 */
class CC_STUDIO_DLL DecorativeDisplay: public cocos2d::Ref
{
public:
    static DecorativeDisplay *create();
public:
    DecorativeDisplay(void);
    ~DecorativeDisplay(void);

    virtual bool init();

    /*
    * @~english Set display by node.
    * @~chinese 根据节点设置显示。
    * @param display @~english Node for display.
    * @~chinese 节点。
    */
    virtual void setDisplay(cocos2d::Node *display);

    /*
    * @~english Get display by node.
    * @~chinese 获取显示节点。
    * @return @~english Node for display.
    * @~chinese 节点。
    */
    virtual cocos2d::Node *getDisplay() const { return _display; }

    /*
    * @~english Set display data.
    * @~chinese 设置显示数据。
    * @param data @~english Display data.
    * @~chinese 显示数据。
    */
    virtual void setDisplayData(DisplayData *data)
    {
        if (_displayData != data)
        {
            CC_SAFE_RETAIN(data);
            CC_SAFE_RELEASE(_displayData);
            _displayData = data; 
        }
    }

    /*
    * @~english Get display data.
    * @~chinese 获取显示数据。
    * @return @~english Display data.
    * @~chinese 显示数据。
    */
    virtual DisplayData *getDisplayData() const { return _displayData; }

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT || ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    /*
    * @~english Set collider detector.
    * @~chinese 设置碰撞检测器。
    * @param data @~english collider detector.
    * @~chinese 碰撞检测器。
    */
    virtual void setColliderDetector(ColliderDetector *detector)
    {
        if (_colliderDetector != detector)
        {
            CC_SAFE_RETAIN(detector);
            CC_SAFE_RELEASE(_colliderDetector);
            _colliderDetector = detector; 
        }
    }

    /*
    * @~english Get collider detector.
    * @~chinese 获取碰撞检测器。
    * @return @~english collider detector.
    * @~chinese 碰撞检测器。
    */
    virtual ColliderDetector *getColliderDetector() const { return _colliderDetector; }
#endif
protected:
    cocos2d::Node *_display;
    DisplayData *_displayData;

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT || ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    ColliderDetector *_colliderDetector;
#endif
};

}

#endif /*__CCDECORATIVEDISPLAY_H__*/
