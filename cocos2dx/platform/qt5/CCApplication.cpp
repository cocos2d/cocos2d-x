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

#include <QLocale>
#include <QObject>
#include <QDir>

NS_CC_BEGIN

class Cocos2DQt5MainloopIntegration : public QObject {
    public:
        Cocos2DQt5MainloopIntegration(long interval_ms)
            : QObject()
        {
            startTimer(interval_ms);
        }

    protected:
        virtual void timerEvent(QTimerEvent *event)
        {
            CCDirector::sharedDirector()->mainLoop();
        }
};


// Application singleton
static CCApplication *
application = NULL;

static int
global_fake_argc = 1;

static char *
global_fake_argv[1];

CCApplication *
CCApplication::sharedApplication()
{
    CC_ASSERT(application != NULL);
    return application;
}

CCApplication::CCApplication()
    : m_application(NULL)
    , m_animationInterval(1000 / 60)
    , m_resourceRootPath("")
{
    // Inject argv[0] by resolving /proc/self/exe
    QString filename = QDir("/proc/self/exe").canonicalPath();
    QByteArray utf8 = filename.toUtf8();
    global_fake_argv[0] = strdup(utf8.data());

    m_application = new QGuiApplication(global_fake_argc, global_fake_argv);

    CC_ASSERT(application == NULL);
    application = this;
}

CCApplication::~CCApplication()
{
    delete m_application;

    CC_ASSERT(application == this);
    application = NULL;
}

int
CCApplication::run()
{
    // Initialize instance and cocos2d.
    if (!applicationDidFinishLaunching()) {
        return 0;
    }

    Cocos2DQt5MainloopIntegration mainloopIntegration(m_animationInterval);

    return m_application->exec();
}

void
CCApplication::setAnimationInterval(double interval)
{
    // Interval is expressed in seconds
    m_animationInterval = interval * 1000;

    // XXX: Update animation interval if changed while running
}

void
CCApplication::setResourceRootPath(const std::string &rootResDir)
{
    m_resourceRootPath = rootResDir;
    if (m_resourceRootPath[m_resourceRootPath.length() - 1] != '/') {
        m_resourceRootPath += '/';
    }
    CCFileUtils* pFileUtils = CCFileUtils::sharedFileUtils();
    std::vector<std::string> searchPaths = pFileUtils->getSearchPaths();
    searchPaths.insert(searchPaths.begin(), m_resourceRootPath);
    pFileUtils->setSearchPaths(searchPaths);
}

const std::string &
CCApplication::getResourceRootPath()
{
    return m_resourceRootPath;
}

TargetPlatform
CCApplication::getTargetPlatform()
{
    return kTargetLinux;
}

ccLanguageType
CCApplication::getCurrentLanguage()
{
    QLocale locale;

    switch (locale.language()) {
        case QLocale::Chinese:
            return kLanguageChinese;
        case QLocale::English:
            return kLanguageEnglish;
        case QLocale::French:
            return kLanguageFrench;
        case QLocale::Italian:
            return kLanguageItalian;
        case QLocale::German:
            return kLanguageGerman;
        case QLocale::Spanish:
            return kLanguageSpanish;
        case QLocale::Russian:
            return kLanguageRussian;
        case QLocale::Korean:
            return kLanguageKorean;
        case QLocale::Japanese:
            return kLanguageJapanese;
        case QLocale::Hungarian:
            return kLanguageHungarian;
        case QLocale::Portuguese:
            return kLanguagePortuguese;
        case QLocale::Arabic:
            return kLanguageArabic;
        // XXX: Add missing
        default:
            break;
    }

    return kLanguageEnglish;
}

NS_CC_END
