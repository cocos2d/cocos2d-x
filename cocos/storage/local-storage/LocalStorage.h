/*
 
 Copyright (c) 2012 - Zynga Inc.
 
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
 
 */

/*
 本地存储在iOS上支持JS绑定。
 工作在cocos2d-iphone 和 cocos2d-x 上.
 */

#ifndef __JSB_LOCALSTORAGE_H
#define __JSB_LOCALSTORAGE_H

#include <string>

/** 初始化数据库. 如果路径为空, 将会在内存中创建一数据库 */
void localStorageInit( const std::string& fullpath = "");

/** 释放分配的资源 */
void localStorageFree();

/** 使用键值对保存一个项到本地存储 */
void localStorageSetItem( const std::string& key, const std::string& value);

/** 使用键从本地存储获取项 */
std::string localStorageGetItem( const std::string& key );

/** 使用键从本地存储中移除一个项 */
void localStorageRemoveItem( const std::string& key );

#endif // __JSB_LOCALSTORAGE_H
