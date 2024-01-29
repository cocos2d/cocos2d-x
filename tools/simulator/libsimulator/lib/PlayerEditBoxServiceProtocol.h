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


#ifndef __PLAYER_EDITBOX_SERVICE_PROTOCOL_H_
#define __PLAYER_EDITBOX_SERVICE_PROTOCOL_H_

#include <string>

#include "cocos2d.h"
#include "PlayerMacros.h"
#include "PlayerServiceProtocol.h"

PLAYER_NS_BEGIN

class PlayerEditBoxServiceProtocol : public PlayerServiceProtocol
{
public:
    static const int FORMAT_NONE   = 0;
    static const int FORMAT_NUMBER = 1;
    
    virtual void showSingleLineEditBox(const cocos2d::Rect &rect) = 0;
    virtual void showMultiLineEditBox(const cocos2d::Rect &rect) = 0;
    virtual void hide() = 0;

    virtual void setText(const std::string &text) = 0;
    virtual void setFont(const std::string &name, int size) = 0;
    virtual void setFontColor(const cocos2d::Color3B &color) = 0;
    virtual void setFormator(int formator) = 0;
    
    void registerHandler(int handler)   { _handler = handler; }
    int getHandler()                    { return _handler; }
    
protected:
    int _handler;
};

PLAYER_NS_END

#endif // __PLAYER_EDITBOX_SERVICE_PROTOCOL_H_
