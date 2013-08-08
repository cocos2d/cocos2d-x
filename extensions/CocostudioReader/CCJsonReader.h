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

#ifndef __CCJSONREADER_H__
#define __CCJSONREADER_H__

#include "CCArmature/external_tool/Json/CSContentJsonDictionary.h"
#include "cocos2d.h"
#include "ExtensionMacros.h"

NS_CC_EXT_BEGIN

	class CCJsonReader
	{
		public:
			CCJsonReader(void);
			~CCJsonReader(void);

        public:
            static CCJsonReader* sharedJsonReader();
			static void purgeJsonReader();
    
            cocos2d::CCNode* createNodeWithJsonFile(const char *pszFileName);

			// all version
			cocos2d::CCNode* createObject(cs::CSJsonDictionary * inputFiles, cocos2d::CCNode* parent);
			//version "0.2.4.1"
            cocos2d::CCNode* createObject0241(cs::CSJsonDictionary * inputFiles, cocos2d::CCNode* parent);
			//version "0.2.5.0"
			cocos2d::CCNode* createObject0250(cs::CSJsonDictionary * inputFiles, cocos2d::CCNode* parent);

            void setPropertyFromJsonDict(cocos2d::CCNode *node, cs::CSJsonDictionary* dict);
		public:
            static CCJsonReader* s_sharedJsonReader;
	};


NS_CC_EXT_END

#endif
