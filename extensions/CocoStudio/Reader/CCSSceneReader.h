/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#ifndef __CCSSCENEREADER_H__
#define __CCSSCENEREADER_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ExtensionMacros.h"

NS_CC_EXT_BEGIN

class SceneReader
{
public:
    /**
     * @js ctor
     */
    SceneReader(void);
    /**
     * @js NA
     * @lua NA
     */
    ~SceneReader(void);

public:
    static SceneReader* getInstance();
    void purgeSceneReader();
    static const char* sceneReaderVersion();
    cocos2d::Node* createNodeWithSceneFile(const char *pszFileName);

private:
    cocos2d::Node* createObject(cs::JsonDictionary * inputFiles, cocos2d::Node* parent);
    void setPropertyFromJsonDict(cocos2d::Node *node, cs::JsonDictionary* dict);

private:
    static SceneReader* s_sharedReader;
};


NS_CC_EXT_END

#endif
