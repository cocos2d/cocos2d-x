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

#include "CCApplication.h"
#include <unistd.h>
#include <sys/time.h>
#include <string>
#include "CCDirector.h"
#include "platform/CCFileUtils.h"

#include <QGuiApplication>
#include <QLocale>
#include <QObject>
#include <QDir>

class Cocos2DQt5MainloopIntegration : public QObject {
    public:
        Cocos2DQt5MainloopIntegration()
            : QObject()
            , m_timer(0)
        {
        }

        void setInterval(int interval_ms)
        {
            if (m_timer != 0) {
                killTimer(m_timer);
            }

            m_timer = startTimer(interval_ms);
        }

    protected:
        virtual void timerEvent(QTimerEvent *event)
        {
            cocos2d::Director::getInstance()->mainLoop();
        }

    private:
        int m_timer;
};


NS_CC_BEGIN

// Application singleton
static Application *
application = NULL;

static int
global_fake_argc = 1;

static char *
global_fake_argv[1];

// @deprecated Use getInstance() instead
Application *
Application::sharedApplication()
{
    return getInstance();
}

Application *
Application::getInstance()
{
    CC_ASSERT(application != NULL);
    return application;
}

Application::Application()
    : m_application(NULL)
    , m_animationInterval(1000 / 60)
    , m_resourceRootPath("")
    , m_mainloop(new Cocos2DQt5MainloopIntegration)
{
    // Inject argv[0] by resolving /proc/self/exe
    QString filename = QDir("/proc/self/exe").canonicalPath();
    QByteArray utf8 = filename.toUtf8();
    global_fake_argv[0] = strdup(utf8.data());

    m_application = new QGuiApplication(global_fake_argc, global_fake_argv);

    CC_ASSERT(application == NULL);
    application = this;
}

Application::~Application()
{
    delete m_mainloop;
    delete m_application;

    CC_ASSERT(application == this);
    application = NULL;
}

int
Application::run()
{
    // Initialize instance and cocos2d.
    if (!applicationDidFinishLaunching()) {
        return 0;
    }

    m_mainloop->setInterval(m_animationInterval);

    return m_application->exec();
}

void
Application::setAnimationInterval(double interval)
{
    // Interval is expressed in seconds
    m_animationInterval = interval * 1000;

    m_mainloop->setInterval(m_animationInterval);
}

void
Application::setResourceRootPath(const std::string &rootResDir)
{
    m_resourceRootPath = rootResDir;
    if (m_resourceRootPath[m_resourceRootPath.length() - 1] != '/') {
        m_resourceRootPath += '/';
    }
    FileUtils* pFileUtils = FileUtils::getInstance();
    std::vector<std::string> searchPaths = pFileUtils->getSearchPaths();
    searchPaths.insert(searchPaths.begin(), m_resourceRootPath);
    pFileUtils->setSearchPaths(searchPaths);
}

const std::string &
Application::getResourceRootPath()
{
    return m_resourceRootPath;
}

Application::Platform
Application::getTargetPlatform()
{
    return Platform::OS_LINUX;
}

LanguageType
Application::getCurrentLanguage()
{
    QLocale locale;

    switch (locale.language()) {
        case QLocale::English:
            return LanguageType::ENGLISH;
        case QLocale::Chinese:
            return LanguageType::CHINESE;
        case QLocale::French:
            return LanguageType::FRENCH;
        case QLocale::Italian:
            return LanguageType::ITALIAN;
        case QLocale::German:
            return LanguageType::GERMAN;
        case QLocale::Spanish:
            return LanguageType::SPANISH;
        case QLocale::Russian:
            return LanguageType::RUSSIAN;
        case QLocale::Korean:
            return LanguageType::KOREAN;
        case QLocale::Japanese:
            return LanguageType::JAPANESE;
        case QLocale::Hungarian:
            return LanguageType::HUNGARIAN;
        case QLocale::Portuguese:
            return LanguageType::PORTUGUESE;
        case QLocale::Arabic:
            return LanguageType::ARABIC;
        default:
            break;
    }

    return LanguageType::ENGLISH;
}

NS_CC_END
