/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 
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

NS_CC_BEGIN

Application* Application::sm_pSharedApplication = 0;

Application::Application()
{
    CCAssert(! sm_pSharedApplication, "sm_pSharedApplication already exist");
    sm_pSharedApplication = this;
}

Application::~Application()
{
    CCAssert(this == sm_pSharedApplication, "sm_pSharedApplication != this");
    sm_pSharedApplication = 0;
}

int Application::run()
{
    if (/*initInstance() &&*/ applicationDidFinishLaunching()) 
    {
        [[DirectorCaller sharedDirectorCaller] startMainLoop];
    }
    return 0;
}

void Application::setAnimationInterval(double interval)
{
    [[DirectorCaller sharedDirectorCaller] setAnimationInterval: interval ];
}

TargetPlatform Application::getTargetPlatform()
{
    return kTargetMacOS;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////////////////////////////

Application* Application::sharedApplication()
{
    CCAssert(sm_pSharedApplication, "sm_pSharedApplication not set");
    return sm_pSharedApplication;
}

ccLanguageType Application::getCurrentLanguage()
{
    // get the current language and country config
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSArray *languages = [defaults objectForKey:@"AppleLanguages"];
    NSString *currentLanguage = [languages objectAtIndex:0];

    // get the current language code.(such as English is "en", Chinese is "zh" and so on)
    NSDictionary* temp = [NSLocale componentsFromLocaleIdentifier:currentLanguage];
    NSString * languageCode = [temp objectForKey:NSLocaleLanguageCode];

    ccLanguageType ret = kLanguageEnglish;
    if ([languageCode isEqualToString:@"zh"])
    {
        ret = kLanguageChinese;
    }
    else if ([languageCode isEqualToString:@"en"])
    {
        ret = kLanguageEnglish;
    }
    else if ([languageCode isEqualToString:@"fr"]){
        ret = kLanguageFrench;
    }
    else if ([languageCode isEqualToString:@"it"]){
        ret = kLanguageItalian;
    }
    else if ([languageCode isEqualToString:@"de"]){
        ret = kLanguageGerman;
    }
    else if ([languageCode isEqualToString:@"es"]){
        ret = kLanguageSpanish;
    }
    else if ([languageCode isEqualToString:@"ru"]){
        ret = kLanguageRussian;
    }
    else if ([languageCode isEqualToString:@"ko"]){
        ret = kLanguageKorean;
    }
    else if ([languageCode isEqualToString:@"ja"]){
        ret = kLanguageJapanese;
    }
    else if ([languageCode isEqualToString:@"hu"]){
        ret = kLanguageHungarian;
    }
    else if ([languageCode isEqualToString:@"pt"])
    {
        ret = kLanguagePortuguese;
    }
    else if ([languageCode isEqualToString:@"ar"])
    {
        ret = kLanguageArabic;
    }
    else if ([languageCode isEqualToString:@"nb"]){
        ret = kLanguageNorwegian;
    }
    else if ([languageCode isEqualToString:@"pl"]){
        ret = kLanguagePolish;
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
    FileUtils* pFileUtils = FileUtils::sharedFileUtils();
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
