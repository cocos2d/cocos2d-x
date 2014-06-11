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

#ifndef __CC_EXTENTIONS_CCCOMRENDER_H__
#define __CC_EXTENTIONS_CCCOMRENDER_H__

#include "CCComBase.h"
#include "2d/CCComponent.h"

namespace cocostudio {

class ComRender : public cocos2d::Component
{
    DECLARE_CLASS_COMPONENT_INFO
protected:
    /**
     *  @js ctor
     */
    ComRender(void);
    ComRender(cocos2d::Node *node, const char *comName);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ComRender(void);
    
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual void onEnter() override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void onExit() override;
    virtual bool serialize(void* r) override;
    virtual cocos2d::Node* getNode();
    virtual void setNode(cocos2d::Node *node);

    static ComRender* create(void);
    static ComRender* create(cocos2d::Node *node, const char *comName);
private:
    bool readJson(const std::string &fileName, rapidjson::Document &doc);

private:
    cocos2d::Node *_render;
};

}
#endif  // __FUNDATION__CCCOMPONENT_H__
