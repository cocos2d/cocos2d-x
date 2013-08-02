/**
 *
 * Cocos2D-X Qt 5 Platform
 *
 * Copyright (C) 2013 Jolla Ltd.
 * Contact: Thomas Perl <thomas.perl@jollamobile.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **/


#ifndef CCAPPLICATION_QT5_H
#define CCAPPLICATION_QT5_H

#include "platform/CCCommon.h"
#include "platform/CCApplicationProtocol.h"
#include <string>

class QGuiApplication;
class Cocos2DQt5MainloopIntegration;

NS_CC_BEGIN

class Application : public ApplicationProtocol {
    public:
        Application();
        virtual ~Application();

        /**
          @brief	Callback by Director for limit FPS.
          @param interval   The time, which expressed in second in second, between current frame and next.
          */
        void setAnimationInterval(double interval);

        /**
          @brief	Run the message loop.
          */
        int run();

        /**
          @brief	Get current application instance.
          @return Current application instance pointer.
          */
        static Application* getInstance();

        /** @deprecated Use getInstance() instead */
        CC_DEPRECATED_ATTRIBUTE static Application* sharedApplication();

        /* override functions */
        virtual LanguageType getCurrentLanguage();

        /**
         *  Sets the Resource root path.
         *  @deprecated Please use CCFileUtils::sharedFileUtils()->setSearchPaths() instead.
         */
        CC_DEPRECATED_ATTRIBUTE void setResourceRootPath(const std::string &rootResDir);

        /**
         *  Gets the Resource root path.
         *  @deprecated Please use CCFileUtils::sharedFileUtils()->getSearchPaths() instead.
         */
        CC_DEPRECATED_ATTRIBUTE const std::string &getResourceRootPath();

        /**
          @brief Get target platform
          */
        virtual Platform getTargetPlatform();

    protected:
        QGuiApplication *m_application;
        long m_animationInterval;
        std::string m_resourceRootPath;
        Cocos2DQt5MainloopIntegration *m_mainloop;
};

NS_CC_END

#endif /* CCAPPLICATION_QT5_H */
