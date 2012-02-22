/*
 * CCVideoUtilsJni.h
 *
 *  Created on: Feb 5, 2012
 *      Author: dmitrymatyukhin
 */

#ifndef CCVIDEOUTILSJNI_H_
#define CCVIDEOUTILSJNI_H_


#include <jni.h>
#include "cocos2d.h"

extern "C"
{
    extern void playVideoJNI(const char *path, bool showControls, bool skipByTap, cocos2d::CCObject* pSelectorTarget,
    		cocos2d::SEL_CallFuncN selector, cocos2d::CCNode* withObject);

    extern void openURLJNI(const char *url);
}

#endif /* CCVIDEOUTILSJNI_H_ */
