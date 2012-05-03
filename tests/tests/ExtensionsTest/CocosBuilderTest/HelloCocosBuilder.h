/****************************************************************************
 Copyright (c) 2012 Xiaolong Zhang, Chukong Inc.
 
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

#ifndef cocos2dXReflection_HelloCocosBuilder_h
#define cocos2dXReflection_HelloCocosBuilder_h

#include "cocos2d.h"
//#include "CGenDynamic.h"
#include "CObject.h"

using namespace std ;
namespace cocos2d{
    class HelloCocosBuilder : public CObject
    {
    private:
        DECLARE_RUNTIME(HelloCocosBuilder) ;
    public:
        SET(HelloCocosBuilder, CCSprite*, sprtBurst)
        SET(HelloCocosBuilder, CCSprite*, sprtIcon)
        
    public:
        HelloCocosBuilder(){}
        
        static void* createInstance() 
        {
            return new HelloCocosBuilder ;
        }
    public:
        //virtual method
        virtual void didLoadFromCCB() ;
        //@1:注册函数
        virtual void registMethod()
        {
//            REGISTMETHOD(pressedButton) ;
//            methodMap.insert(pair<string, callBack>("pressedButton", HelloCocosBuilder::pressedButton)) ;
//            methodMap["pressedButton"] = pressedButton ;
//            REGISTMETHOD(pressedButton2) ;
        }
        virtual void registProperty() 
        {
            //propertyMap.insert(pair<string, setValue>("setSprtBurst", setSprtBurst)) ;
            REGISTPROPERTY(setsprtBurst)
            REGISTPROPERTY(setsprtIcon)
        }
        //按钮点击首先会调到此处，然后分发给相应的消息
        virtual void menuCallBack(CCObject *sender) ;
    //private:
        void pressedButton(CCObject*sender) ;
        void pressedButton2(CCObject*sender) ;
    protected:
        static CCSprite* sprtBurst ;
        static CCSprite* sprtIcon ;

    } ;
}


#endif
