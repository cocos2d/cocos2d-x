
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
