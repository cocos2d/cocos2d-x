/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#ifndef COCOS_SCRIPTING_LUA_BINDINGS_LUA_COCOS2DX_CUSTOM_GUI_READER_H
#define COCOS_SCRIPTING_LUA_BINDINGS_LUA_COCOS2DX_CUSTOM_GUI_READER_H

#include "editor-support/cocostudio/WidgetReader/WidgetReader.h"

USING_NS_CC;

namespace cocostudio
{
    class CustomGUIReader : public Ref
    {
    public:

        CustomGUIReader();
        virtual ~CustomGUIReader();

        static CustomGUIReader* create(std::string &className, int createFunc, int setPropsFunc);

        void init(std::string &className, int createFunc, int setPropsFunc);

        Ref* createInstance();

        void setCustomProps(const std::string &classType, cocos2d::Ref *widget, const rapidjson::Value &customOptions);

    private:
        std::string _className;
        int _createFunc;
        int _setPropsFunc;
    };
}



#endif
