/****************************************************************************
Copyright (c) 2012 Zynga Inc.
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#ifndef __JSB_LOCALSTORAGE_H
#define __JSB_LOCALSTORAGE_H

#include <string>
#include "platform/CCPlatformMacros.h"

/**
 * @addtogroup storage
 * @{
 */

/** Local Storage support for the JS Bindings.*/

/** Initializes the database. If path is null, it will create an in-memory DB. */
void CC_DLL localStorageInit( const std::string& fullpath = "");

/** Frees the allocated resources. */
void CC_DLL localStorageFree();

/** Sets an item in the JS. */
void CC_DLL localStorageSetItem( const std::string& key, const std::string& value);

/** Gets an item from the JS. */
bool CC_DLL localStorageGetItem( const std::string& key, std::string *outItem );

/** Removes an item from the JS. */
void CC_DLL localStorageRemoveItem( const std::string& key );

/** Removes all items from the JS. */
void CC_DLL localStorageClear();

// end group
/// @}

#endif // __JSB_LOCALSTORAGE_H
