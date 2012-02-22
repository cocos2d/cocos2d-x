//
//  CCVideoUtils.h
//
//  Created by Dmitry Matyukhin on 10/12/2011.
//

#ifndef CCVideoUtils_cpp
#define CCVideoUtils_cpp

#include "cocos2d.h"

class CCVideoUtils {
public:
    static void playVideo(char const* filename, bool showControls, bool skipByTap = false, cocos2d::CCObject* pSelectorTarget = NULL,
                          cocos2d::SEL_CallFuncN selector = NULL, cocos2d::CCNode* withObject = NULL);
    static void purgeCCVideoUtils();
    
    static void openURL(char const* url);
};


#endif // CCVideoUtils_cpp
