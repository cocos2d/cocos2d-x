/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

http://www.cocos2d+x.org

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

#import "AdsWrapper.h"
#include "PluginUtilsIOS.h"
#include "ProtocolAds.h"

using namespace cocos2d::plugin;

@implementation AdsWrapper

+ (void) onAdsResult:(id) obj withRet:(AdsResult) ret withMsg:(NSString*) msg
{
    PluginProtocol* plugin = PluginUtilsIOS::getPluginPtr(obj);
    ProtocolAds* adsPlugin = dynamic_cast<ProtocolAds*>(plugin);
    if (adsPlugin) {
        const char* chMsg = [msg UTF8String];
        AdsResultCode cRet = (AdsResultCode) ret;
        AdsListener* listener = adsPlugin->getAdsListener();
        if (listener)
        {
            listener->onAdsResult(cRet, chMsg);
        }
    } else {
        PluginUtilsIOS::outputLog("Can't find the C++ object of the ads plugin");
    }
}

+ (void) onPlayerGetPoints:(id) obj withPoints: (int) points
{
    PluginProtocol* plugin = PluginUtilsIOS::getPluginPtr(obj);
    ProtocolAds* adsPlugin = dynamic_cast<ProtocolAds*>(plugin);
    if (adsPlugin) {
        AdsListener* listener = adsPlugin->getAdsListener();
        if (listener)
        {
            listener->onPlayerGetPoints(adsPlugin, points);
        }
    } else {
        PluginUtilsIOS::outputLog("Can't find the C++ object of the ads plugin");
    }
}

+ (void) addAdView:(UIView*) view atPos:(AdsPosEnum) pos
{
    UIViewController* controller = [AdsWrapper getCurrentRootViewController];

    if (nil == controller) {
        PluginUtilsIOS::outputLog("Can't get the UIViewController object");
        return;
    }

    CGSize rootSize = controller.view.frame.size;
    CGSize viewSize = view.frame.size;
    CGPoint viewOrigin;

    if (UIInterfaceOrientationIsLandscape(controller.interfaceOrientation)){
        CGFloat temp = rootSize.width;
        rootSize.width = rootSize.height;
        rootSize.height = temp;
    }

    switch (pos) {
    case kPosTop:
        viewOrigin.x = (rootSize.width - viewSize.width) / 2;
        viewOrigin.y = 0.0f;
        break;
    case kPosTopLeft:
        viewOrigin.x = 0.0f;
        viewOrigin.y = 0.0f;
        break;
    case kPosTopRight:
        viewOrigin.x = rootSize.width - viewSize.width;
        viewOrigin.y = 0.0f;
        break;
    case kPosBottom:
        viewOrigin.x = (rootSize.width - viewSize.width) / 2;
        viewOrigin.y = rootSize.height - viewSize.height;
        break;
    case kPosBottomLeft:
        viewOrigin.x = 0.0f;
        viewOrigin.y = rootSize.height - viewSize.height;
        break;
    case kPosBottomRight:
        viewOrigin.x = rootSize.width - viewSize.width;
        viewOrigin.y = rootSize.height - viewSize.height;
        break;
    case kPosCenter:
    default:
        viewOrigin.x = (rootSize.width - viewSize.width) / 2;
        viewOrigin.y = (rootSize.height - viewSize.height) / 2;
        break;
    }

    CGRect rect = CGRectMake(viewOrigin.x, viewOrigin.y, viewSize.width, viewSize.height);
    view.frame = rect;
    [controller.view addSubview:view];
}

+ (UIViewController *)getCurrentRootViewController {
    
    UIViewController *result = nil;
    
    // Try to find the root view controller programmically
    
    // Find the top window (that is not an alert view or other window)
    UIWindow *topWindow = [[UIApplication sharedApplication] keyWindow];
    if (topWindow.windowLevel != UIWindowLevelNormal)
    {
        NSArray *windows = [[UIApplication sharedApplication] windows];
        for(topWindow in windows)
        {
            if (topWindow.windowLevel == UIWindowLevelNormal)
                break;
        }
    }
    
    UIView *rootView = [[topWindow subviews] objectAtIndex:0];
    id nextResponder = [rootView nextResponder];
    
    if ([nextResponder isKindOfClass:[UIViewController class]])
        result = nextResponder;
    else if ([topWindow respondsToSelector:@selector(rootViewController)] && topWindow.rootViewController != nil)
        result = topWindow.rootViewController;
    else
        NSAssert(NO, @"Could not find a root view controller.");
    
    return result;
}

@end
