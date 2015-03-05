//
//  CCController-desktop.h
//  cocos2d_libs
//
//  Created by Chad Ata on 2/10/15.
//
//

#ifndef cocos2d_libs_CCController_desktop_h
#define cocos2d_libs_CCController_desktop_h
#include "CCController.h"

NS_CC_BEGIN

/**
 * Controller implementation for desktop controller support
 */
class ControllerImpl
{
public:
    ControllerImpl(Controller* controller);
    static void pollJoystick( int id );

private:
    Controller* _controller;
};

NS_CC_END
#endif
