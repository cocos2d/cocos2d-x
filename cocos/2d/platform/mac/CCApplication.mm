/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#import "CCApplication.h"
#import <Cocoa/Cocoa.h>
#include <algorithm>
#include "platform/CCFileUtils.h"
#include "CCGeometry.h"
#include "CCDirector.h"
#import "CCDirectorCaller.h"
#include "CCEGLView.h"

NS_CC_BEGIN

Application* Application::sm_pSharedApplication = 0;

Application::Application()
{
    CCASSERT(! sm_pSharedApplication, "sm_pSharedApplication already exist");
    sm_pSharedApplication = this;
}

Application::~Application()
{
    CCASSERT(this == sm_pSharedApplication, "sm_pSharedApplication != this");
    sm_pSharedApplication = 0;
}

int Application::run()
{
    if(!applicationDidFinishLaunching())
    {
        return 0;
    }
    EGLView* pMainWnd = EGLView::getInstance();
    
    while (!pMainWnd->windowShouldClose())
    {
        Director::getInstance()->mainLoop();
        pMainWnd->pollEvents();
    }

    /* Only work on Desktop
    *  Director::mainLoop is really one frame logic
    *  when we want to close the window, we should call Director::end();
    *  then call Director::mainLoop to do release of internal resources
    */
    Director::getInstance()->end();
    Director::getInstance()->mainLoop();
    return true;
}

void Application::setAnimationInterval(double interval)
{
    [[CCDirectorCaller sharedDirectorCaller] setAnimationInterval: interval ];
}

Application::Platform Application::getTargetPlatform()
{
    return Platform::OS_MAC;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////////////////////////////

Application* Application::getInstance()
{
    CCASSERT(sm_pSharedApplication, "sm_pSharedApplication not set");
    return sm_pSharedApplication;
}

// @deprecated Use getInstance() instead
Application* Application::sharedApplication()
{
    return Application::getInstance();
}

LanguageType Application::getCurrentLanguage()
{
    // get the current language and country config
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSArray *languages = [defaults objectForKey:@"AppleLanguages"];
    NSString *currentLanguage = [languages objectAtIndex:0];

    // get the current language code.(such as English is "en", Chinese is "zh" and so on)
    NSDictionary* temp = [NSLocale componentsFromLocaleIdentifier:currentLanguage];
    NSString * languageCode = [temp objectForKey:NSLocaleLanguageCode];

    LanguageType ret = LanguageType::ENGLISH;
    if ([languageCode isEqualToString:@"zh"])
    {
        ret = LanguageType::CHINESE;
    }
    else if ([languageCode isEqualToString:@"en"])
    {
        ret = LanguageType::ENGLISH;
    }
    else if ([languageCode isEqualToString:@"fr"]){
        ret = LanguageType::FRENCH;
    }
    else if ([languageCode isEqualToString:@"it"]){
        ret = LanguageType::ITALIAN;
    }
    else if ([languageCode isEqualToString:@"de"]){
        ret = LanguageType::GERMAN;
    }
    else if ([languageCode isEqualToString:@"es"]){
        ret = LanguageType::SPANISH;
    }
    else if ([languageCode isEqualToString:@"ru"]){
        ret = LanguageType::RUSSIAN;
    }
    else if ([languageCode isEqualToString:@"ko"]){
        ret = LanguageType::KOREAN;
    }
    else if ([languageCode isEqualToString:@"ja"]){
        ret = LanguageType::JAPANESE;
    }
    else if ([languageCode isEqualToString:@"hu"]){
        ret = LanguageType::HUNGARIAN;
    }
    else if ([languageCode isEqualToString:@"pt"])
    {
        ret = LanguageType::PORTUGUESE;
    }
    else if ([languageCode isEqualToString:@"ar"])
    {
        ret = LanguageType::ARABIC;
    }
    else if ([languageCode isEqualToString:@"nb"]){
        ret = LanguageType::NORWEGIAN;
    }
    else if ([languageCode isEqualToString:@"pl"]){
        ret = LanguageType::POLISH;
    }
    return ret;
}

void Application::setResourceRootPath(const std::string& rootResDir)
{
    _resourceRootPath = rootResDir;
    if (_resourceRootPath[_resourceRootPath.length() - 1] != '/')
    {
        _resourceRootPath += '/';
    }
    FileUtils* pFileUtils = FileUtils::getInstance();
    std::vector<std::string> searchPaths = pFileUtils->getSearchPaths();
    searchPaths.insert(searchPaths.begin(), _resourceRootPath);
    pFileUtils->setSearchPaths(searchPaths);
}

const std::string& Application::getResourceRootPath(void)
{
    return _resourceRootPath;
}

void Application::setStartupScriptFilename(const std::string& startupScriptFile)
{
    _startupScriptFilename = startupScriptFile;
    std::replace(_startupScriptFilename.begin(), _startupScriptFilename.end(), '\\', '/');
}

const std::string& Application::getStartupScriptFilename(void)
{
    return _startupScriptFilename;
}

NS_CC_END
