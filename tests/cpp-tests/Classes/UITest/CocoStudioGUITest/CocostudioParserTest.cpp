/****************************************************************************
 Copyright (c) 2013-2015 Chukong Technologies Inc.
 
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

#include "CocostudioParserTest.h"
#include "CocostudioParserTest/CocostudioParserJsonTest.h"

CocostudioParserTests::CocostudioParserTests()
{
    addTestCase("cocostudio 1.3", [](){ return CocostudioParserJsonScene::create("cocosui/UIEditorTest/cocostudio1_3/CocostudioV1_3_1.ExportJson"); });
    addTestCase("cocostudio 1.4", [](){ return CocostudioParserJsonScene::create("cocosui/UIEditorTest/cocostudio1_4/Cocostudio1_4_1.ExportJson"); });
    addTestCase("cocostudio 1.5", [](){ return CocostudioParserJsonScene::create("cocosui/UIEditorTest/cocostudio1_5/Cocostudio1_5_1.ExportJson"); });
    addTestCase("cocostudio 1.6", [](){ return CocostudioParserJsonScene::create("cocosui/UIEditorTest/cocostudio1_6/CocoStudio1.6Demo_1.ExportJson"); });
    
}
