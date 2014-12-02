/*
 *
 * Copyright (c) 2014 Nguyen Thai Duong
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
 */
#ifndef __cocos2d_libs__CCBLocalizationManager__
#define __cocos2d_libs__CCBLocalizationManager__

#include <iostream>
#include "cocos2d.h"

namespace spritebuilder {

#define CCBLocalize(key) (CCBLocalizationManager::sharedManager()->localizedStringForKey(key))

class CCBLocalizationManager : public cocos2d::Ref {
public:
    CCBLocalizationManager();
    static CCBLocalizationManager* sharedManager();
    std::string& localizedStringForKey(const char* key);
private:
    void loadStringFile(const char* file);
private:
    
    std::map<std::string, std::string> mTranslation;
};
}
#endif /* defined(__cocos2d_libs__CCBLocalizationManager__) */
