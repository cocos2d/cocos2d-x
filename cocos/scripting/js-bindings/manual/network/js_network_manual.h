/*
 * Copyright (c) 2016 Chukong Technologies Inc.
 * Created by panda on 1/13/17.
 *
 * Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
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

#ifndef js_network_manual_h
#define js_network_manual_h

#include "jsapi.h"
#include "jsfriendapi.h"

#include "network/CCDownloader.h"

bool jsval_to_DownloaderHints(JSContext *cx, JS::HandleValue v, cocos2d::network::DownloaderHints* ret);

jsval downloadTask_to_jsval(JSContext *cx, const cocos2d::network::DownloadTask& v);

#endif /* js_network_manual_hpp */
