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

#ifndef __SceneReader_H__
#define __SceneReader_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ExtensionMacros.h"

NS_CC_EXT_BEGIN
/**
*   @js NA
*   @lua NA
*/
class SceneReader
{
public:
	SceneReader(void);
	virtual ~SceneReader(void);

public:
	static SceneReader* sharedSceneReader();
	void purgeSceneReader();
	static const char* sceneReaderVersion();
	cocos2d::CCNode* createNodeWithSceneFile(const char *pszFileName);
private:
    cocos2d::CCNode* createObject(const rapidjson::Value &root, cocos2d::CCNode* parent);
    void setPropertyFromJsonDict(const rapidjson::Value &root, cocos2d::CCNode *node);
    bool readJson(const char *pszFileName, rapidjson::Document &doc);

private:
	static SceneReader* s_sharedReader;
};


NS_CC_EXT_END

#endif
