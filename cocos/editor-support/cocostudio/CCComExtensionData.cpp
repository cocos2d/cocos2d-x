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

#include "CCComExtensionData.h"
#include "cocostudio/ActionTimeline/CCActionTimeline.h"

namespace cocostudio
{
    IMPLEMENT_CLASS_COMPONENT_INFO(ComExtensionData)

    const std::string ComExtensionData::COMPONENT_NAME = "ComExtensionData";

    ComExtensionData::ComExtensionData()
    : _customProperty("")
    , _timelineData(nullptr)
    {
        _name = COMPONENT_NAME;
    }

    ComExtensionData::~ComExtensionData()
    {
        CC_SAFE_RELEASE(_timelineData);
    }

    ComExtensionData* ComExtensionData::create()
    {
        ComExtensionData * ret = new (std::nothrow) ComExtensionData();
        if (ret && ret->init())
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(ret);
        }
        return ret;
    }
    
    
    bool ComExtensionData::init()
    {
        _timelineData = cocostudio::timeline::ActionTimelineData::create(0);
        CC_SAFE_RETAIN(_timelineData);
        
        return true;
    }
    
    void ComExtensionData::onEnter()
    {
    }

    void ComExtensionData::onExit()
    {
        onRemove();
    }

    void ComExtensionData::onAdd()
    {
    }

    void ComExtensionData::onRemove()
    {
    }

    void ComExtensionData::setActionTag(int actionTag)
    {
        _timelineData->setActionTag(actionTag);
    }
    
    const int ComExtensionData::getActionTag() const
    {
        return _timelineData->getActionTag();
    }
    
}
