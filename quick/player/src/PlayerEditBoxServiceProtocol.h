//
//  PlayerEditBoxServiceProtocol.h
//  player
//

#ifndef player_PlayerEditBoxServiceProtocol_h
#define player_PlayerEditBoxServiceProtocol_h

#include "PlayerMacros.h"
#include "PlayerServiceProtocol.h"

#include <string>

PLAYER_NS_BEGIN

class PlayerEditBoxServiceProtocol : public PlayerServiceProtocol
{
public:
    PlayerEditBoxServiceProtocol() {}
    virtual ~PlayerEditBoxServiceProtocol() {}
    
    virtual void setPosition(int x, int y) = 0;
    virtual void setSize(int width, int height) = 0;
    virtual void setRect(int x, int y, int width, int height) = 0;
    virtual void setText(std::string text) = 0;
    virtual void setFont(const char* pFontName, int fontSize) = 0;
    // @r / @g / @b [0,255]
    virtual void setFontColor(int r, int g, int b) = 0;
    
    // hide editbox
    virtual void hide() = 0;
    virtual void show() = 0;
    
    //
//    void setFilter(int filter);
};

PLAYER_NS_END

#endif
