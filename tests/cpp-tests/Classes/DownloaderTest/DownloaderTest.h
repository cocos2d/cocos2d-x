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

#pragma once

#include "cocos2d.h"
#include "../BaseTest.h"
#include <string>

#include "network/CCDownloader.h"
DEFINE_TEST_SUITE(DownloaderTests);


class DownloaderBaseTest : public TestCase
{
public:
    DownloaderBaseTest();
    virtual std::string title() const override;

    void errorCallback(const cocos2d::network::Downloader::Error& error);
    void progressCallback(double totalToDownload, double nowDownloaded, const std::string& url, const std::string& customId);
    void successCallback(const std::string& url, const std::string& path, const std::string& customId);

protected:
    std::shared_ptr<cocos2d::network::Downloader> _downloader;
};

//
// ---
//
class DownloaderSyncTest : public DownloaderBaseTest
{
public:
    CREATE_FUNC(DownloaderSyncTest);

    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class DownloaderAsyncTest : public DownloaderBaseTest
{
public:
    CREATE_FUNC(DownloaderAsyncTest);

    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class DownloaderBatchSyncTest : public DownloaderBaseTest
{
public:
    CREATE_FUNC(DownloaderBatchSyncTest);

    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class DownloaderBatchAsyncTest : public DownloaderBaseTest
{
public:
    CREATE_FUNC(DownloaderBatchAsyncTest);

    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

