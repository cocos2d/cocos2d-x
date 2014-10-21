#pragma once

#include "pch.h"

class AppDelegate;

namespace cocos2d
{
    class Cocos2dRenderer
    {
    public:
        Cocos2dRenderer(const int width, const int height);
        ~Cocos2dRenderer();
        void Draw(GLsizei width, GLsizei height);
        void QueuePointerEvent(PointerEventType type, Windows::UI::Core::PointerEventArgs^ args);

    private:

        int mWidth;
        int mHeight;
        // The AppDelegate for the Cocos2D app
        AppDelegate* mApp;
    };
}