/*
* cocos2d-x   http://www.cocos2d-x.org
*
* Copyright (c) 2010-2014 - cocos2d-x community
*
* Portions Copyright (c) Microsoft Open Technologies, Inc.
* All Rights Reserved
*
* Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
*/
#pragma once

#include "pch.h"
#include <agile.h>

class AppDelegate;

namespace cocos2d
{
    class Cocos2dRenderer
    {
    public:
        Cocos2dRenderer(const int width, const int height, Windows::UI::Core::CoreDispatcher^ dispathcer);
        ~Cocos2dRenderer();
        void Draw(GLsizei width, GLsizei height);
        void QueuePointerEvent(PointerEventType type, Windows::UI::Core::PointerEventArgs^ args);

    private:

        int mWidth;
        int mHeight;
        // The AppDelegate for the Cocos2D app
        AppDelegate* mApp;
        Platform::Agile<Windows::UI::Core::CoreDispatcher> m_dispatcher;

    };
}