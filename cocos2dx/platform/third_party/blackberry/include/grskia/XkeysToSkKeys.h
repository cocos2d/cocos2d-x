#include "X11/Xlib.h"
#include "X11/keysym.h"

#include "SkKey.h"

#ifndef XKEYS_TOSKKEYS_H
#define XKEYS_TOSKKEYS_H

SkKey XKeyToSkKey(KeySym keysym) {
    switch (keysym) {
        case XK_BackSpace:
            return kBack_SkKey;
        case XK_Return:
            return kOK_SkKey;
        case XK_Home:
            return kHome_SkKey;
        case XK_End:
            return kEnd_SkKey;
        case XK_Right:
            return kRight_SkKey;
        case XK_Left:
            return kLeft_SkKey;
        case XK_Down:
            return kDown_SkKey;
        case XK_Up:
            return kUp_SkKey;
        default:
            return kNONE_SkKey;
    }
}
#endif
