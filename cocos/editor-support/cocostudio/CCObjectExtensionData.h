/****************************************************************************
 Copyright (c) 2015 cocos2d-x.org
 
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

#ifndef __cocos2d_libs__CCObjectExtensionData__
#define __cocos2d_libs__CCObjectExtensionData__

#include <string>

#include "base/CCRef.h"

#include "cocostudio/CocosStudioExport.h"

namespace cocostudio
{
    namespace timeline
    {
        class ActionTimelineData;
    }
}

namespace cocostudio
{
    class CC_STUDIO_DLL ObjectExtensionData : public cocos2d::Ref
    {

    public:
        /**
        * @~english Allocates and initializes a ObjectExtensionData.
        * @~chinese 分配并且初始化一个ObjectExtensionData.
        * @return @~english A initialized ObjectExtensionData which is marked as "autorelease".
        * @~chinese 一个初始化的ObjectExtensionData，该节点会自动被标记为“autorelease”(自动释放).
        */
        static ObjectExtensionData* create();

        /**
        * @~english Set custom property.
        * @~chinese 设定用户自定义属性.
        *
        * @param customProperty    @~english custom property @~chinese 用户自定义属性
        */
        virtual void setCustomProperty(const std::string& customProperty) { _customProperty = customProperty; }
        /**
        * @~english Get custom property.
        * @~chinese 获取用户自定义属性.
        *
        * @return @~english custom property @~chinese 用户自定义属性
        */
        virtual std::string getCustomProperty() const { return _customProperty; };

        /**
        * @~english Set tag for timeline data
        * @~chinese 设置时间轴数据的Tag
        *
        * @param tag    @~english tag of timeline data @~chinese 间轴数据的Tag
        */
        virtual void setActionTag(int actionTag);
        /**
        * @~english Get tag for timeline data
        * @~chinese 获取时间轴数据的Tag
        *
        * @return @~english tag of timeline data @~chinese 间轴数据的Tag
        */
        virtual const int getActionTag() const;

    CC_CONSTRUCTOR_ACCESS:
        ObjectExtensionData();
        ~ObjectExtensionData();
        virtual bool init();

    protected:
        std::string _customProperty;
        cocostudio::timeline::ActionTimelineData* _timelineData;
    };
}


#endif /* defined(__cocos2d_libs__CCObjectExtensionData__) */
