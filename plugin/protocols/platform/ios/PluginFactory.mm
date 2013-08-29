/****************************************************************************
Copyright (c) 2012-2013 cocos2d-x.org

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
#include "PluginFactory.h"
#include "ProtocolAds.h"
#include "ProtocolAnalytics.h"
#include "ProtocolIAP.h"
#include "ProtocolSocial.h"
#include "PluginUtilsIOS.h"

#import <Foundation/Foundation.h>
#import "InterfaceAds.h"
#import "InterfaceAnalytics.h"
#import "InterfaceIAP.h"
#import "InterfaceSocial.h"

namespace cocos2d { namespace plugin {

static PluginFactory* s_pFactory = NULL;

PluginFactory::PluginFactory()
{

}

PluginFactory::~PluginFactory()
{

}

PluginFactory* PluginFactory::getInstance()
{
	if (NULL == s_pFactory)
	{
		s_pFactory = new PluginFactory();
	}

	return s_pFactory;
}

void PluginFactory::purgeFactory()
{
	if (NULL != s_pFactory)
	{
		delete s_pFactory;
		s_pFactory = NULL;
	}
}

/** create the plugin by name */
PluginProtocol* PluginFactory::createPlugin(const char* name)
{
	PluginProtocol* pRet = NULL;
	do
	{
		if (name == NULL || strlen(name) == 0) break;

        NSString* className = [NSString stringWithUTF8String:name];
        id obj = [[NSClassFromString(className) alloc] init];
        if (obj == nil) break;

        if ([obj conformsToProtocol:@protocol(InterfaceAds)]) {
            pRet = new ProtocolAds();
        } else
        if ([obj conformsToProtocol:@protocol(InterfaceAnalytics)]) {
            pRet = new ProtocolAnalytics();
        } else
        if ([obj conformsToProtocol:@protocol(InterfaceIAP)]) {
            pRet = new ProtocolIAP();
        } else
        if ([obj conformsToProtocol:@protocol(InterfaceSocial)]) {
            pRet = new ProtocolSocial();
        } else {
            PluginUtilsIOS::outputLog("Plugin %s not implements a right protocol", name);
        }

		if (pRet != NULL)
		{
			pRet->setPluginName(name);
			PluginUtilsIOS::initOCPlugin(pRet, obj, name);
		}
	} while(0);

	return pRet;
}

}} //namespace cocos2d { namespace plugin {
