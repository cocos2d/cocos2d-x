/*
 * Created by James Chen on 3/11/13.
 * Copyright (c) 2013-2017 Chukong Technologies Inc.
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

#ifndef __jsb_cocos2dx_extension_manual__
#define __jsb_cocos2dx_extension_manual__

#include "jsapi.h"
#include "jsfriendapi.h"
#include "network/CCDownloader.h"
#include "renderer/CCTexture2D.h"

class __JSDownloaderDelegator : cocos2d::Ref
{
public:
    void downloadAsync();
    void download();
    
    static __JSDownloaderDelegator *create(JSContext *cx, JS::HandleObject obj, const std::string &url, JS::HandleObject callback);

protected:
    __JSDownloaderDelegator(JSContext *cx, JS::HandleObject obj, const std::string &url, JS::HandleObject callback);
    ~__JSDownloaderDelegator();
    
    void startDownload();
    
private:
    void onSuccess(cocos2d::Texture2D *tex);
    void onError();
    std::shared_ptr<cocos2d::network::Downloader> _downloader;
    std::string _url;
    JSContext *_cx;
    JS::Heap<JSObject*> _jsCallback;
    JS::Heap<JSObject*> _obj;
};

void register_all_cocos2dx_extension_manual(JSContext* cx, JS::HandleObject global);

#endif /* defined(__jsb_cocos2dx_extension_manual__) */
