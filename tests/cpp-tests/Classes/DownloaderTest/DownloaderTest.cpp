/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "DownloaderTest.h"

#include "../testResource.h"

#include "network/CCDownloader.h"

USING_NS_CC;

DownloaderTests::DownloaderTests()
{
    ADD_TEST_CASE(DownloaderSyncTest);
	ADD_TEST_CASE(DownloaderAsyncTest);
    ADD_TEST_CASE(DownloaderBatchSyncTest);
    ADD_TEST_CASE(DownloaderBatchAsyncTest);
};

//
//
//
DownloaderBaseTest::DownloaderBaseTest()
{
    _downloader = std::shared_ptr<network::Downloader>(new network::Downloader);
    _downloader->setErrorCallback(std::bind(&DownloaderBaseTest::errorCallback, this, std::placeholders::_1));
    _downloader->setProgressCallback(std::bind(&DownloaderBaseTest::progressCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    _downloader->setSuccessCallback(std::bind(&DownloaderBaseTest::successCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

std::string DownloaderBaseTest::title() const
{
    return "Downloader Test";
}

void DownloaderBaseTest::errorCallback(const cocos2d::network::Downloader::Error& error)
{
    cocos2d::log("error downloading: %s - %s", error.url.c_str(), error.message.c_str());
}

void DownloaderBaseTest::progressCallback(double totalToDownload, double nowDownloaded, const std::string& url, const std::string& customId)
{
    cocos2d::log("download progress: %d%% - %s", (int)((nowDownloaded/totalToDownload)*100), url.c_str());
}

void DownloaderBaseTest::successCallback(const std::string& url, const std::string& path, const std::string& customId)
{
    cocos2d::log("download finished: %s", path.c_str());
}

//------------------------------------------------------------------
//
// DownloaderSyncTest
//
//------------------------------------------------------------------
void DownloaderSyncTest::onEnter()
{
    DownloaderBaseTest::onEnter();

    auto menuItem = MenuItemFont::create("start download", [=](Ref* sender){

        if (_downloader)
        {

            std::string path = FileUtils::getInstance()->getWritablePath() + "CppTests/DownloaderTest/cocos2d_logo_sync.jpg";
            std::string remote = "http://www.cocos2d-x.org/attachments/802/cocos2dx_landscape.png";
            cocos2d::log("Downloading '%s' into '%s'", remote.c_str(), path.c_str());

            _downloader->downloadSync(remote, path, "download_async_test");
        }
    });
    auto menu = Menu::create(menuItem, nullptr);
    addChild(menu);
    menu->setNormalizedPosition(Vec2(0.5, 0.5));
}

std::string DownloaderSyncTest::title() const
{
    return "Downloader";
}

std::string DownloaderSyncTest::subtitle() const
{
    return "Sync test";
}


//------------------------------------------------------------------
//
// DownloaderAsyncTest
//
//------------------------------------------------------------------
void DownloaderAsyncTest::onEnter()
{
    DownloaderBaseTest::onEnter();

    auto menuItem = MenuItemFont::create("start download", [=](Ref* sender){
        MenuItemFont* item = (MenuItemFont*)sender;
        item->setEnabled(false);
        if (_downloader)
        {
            std::string path = FileUtils::getInstance()->getWritablePath() + "CppTests/DownloaderTest/cocos2d_logo_async.jpg";
            std::string remote = "http://www.cocos2d-x.org/attachments/802/cocos2dx_landscape.png";
            _downloader->downloadAsync(remote, path, "download_async_test");

            cocos2d::log("Downloading '%s' into '%s'", remote.c_str(), path.c_str());
        }
    });
    auto menu = Menu::create(menuItem, nullptr);
    addChild(menu);
    menu->setNormalizedPosition(Vec2(0.5, 0.5));
}

std::string DownloaderAsyncTest::title() const
{
    return "Downloader";
}

std::string DownloaderAsyncTest::subtitle() const
{
    return "Async test";
}

//------------------------------------------------------------------
//
// DownloaderBatchSyncTest
//
//------------------------------------------------------------------
void DownloaderBatchSyncTest::onEnter()
{
    DownloaderBaseTest::onEnter();

    auto menuItem = MenuItemFont::create("start download", [=](Ref* sender){

        if (_downloader)
        {
            std::vector<std::string> images = {
                "http://www.cocos2d-x.org/attachments/802/cocos2dx_landscape.png",
                "http://www.cocos2d-x.org/docs/manual/framework/native/wiki/logo-resources-of-cocos2d-x/res/2dx_icon_512_rounded.png",
                "http://www.cocos2d-x.org/attachments/1503/Cocos2CoordinateRelease.png"
            };

            std::vector<std::string> names = {
                "cocos2dx_landscape.png",
                "2dx_icon_512_rounded.png",
                "Cocos2CoordinateRelease.png"
            };

            network::DownloadUnits units;

            int i=0;
            for(const auto& image: images)
            {
                network::DownloadUnit unit;
                unit.storagePath = FileUtils::getInstance()->getWritablePath() + "CppTests/DownloaderTest/Sync/" + names[i];
                unit.srcUrl = image;
                unit.customId = image;
                i++;
                units[image] = unit;
            }

            _downloader->batchDownloadSync(units, "sync_download");
            cocos2d::log("Downloading...");
        }
    });
    auto menu = Menu::create(menuItem, nullptr);
    addChild(menu);
    menu->setNormalizedPosition(Vec2(0.5, 0.5));
}

std::string DownloaderBatchSyncTest::title() const
{
    return "Downloader";
}

std::string DownloaderBatchSyncTest::subtitle() const
{
    return "Batch Sync test";
}


//------------------------------------------------------------------
//
// DownloaderBatchAsyncTest
//
//------------------------------------------------------------------
void DownloaderBatchAsyncTest::onEnter()
{
    DownloaderBaseTest::onEnter();

    auto menuItem = MenuItemFont::create("start download", [=](Ref* sender){

        if (_downloader)
        {
            std::vector<std::string> images = {
                "http://www.cocos2d-x.org/attachments/802/cocos2dx_landscape.png",
                "http://www.cocos2d-x.org/docs/manual/framework/native/wiki/logo-resources-of-cocos2d-x/res/2dx_icon_512_rounded.png",
                "http://www.cocos2d-x.org/attachments/1503/Cocos2CoordinateRelease.png"
            };

            std::vector<std::string> names = {
                "cocos2dx_landscape.png",
                "2dx_icon_512_rounded.png",
                "Cocos2CoordinateRelease.png"
            };

            network::DownloadUnits units;

            int i=0;
            for(const auto& image: images)
            {
                network::DownloadUnit unit;
                unit.storagePath = FileUtils::getInstance()->getWritablePath() + "CppTests/DownloaderTest/Async/" + names[i];
                unit.srcUrl = image;
                unit.customId = image;
                i++;
                units[image] = unit;
            }

            _downloader->batchDownloadAsync(units, "sync_download");
            cocos2d::log("Downloading...");
        }
    });
    auto menu = Menu::create(menuItem, nullptr);
    addChild(menu);
    menu->setNormalizedPosition(Vec2(0.5, 0.5));
}

std::string DownloaderBatchAsyncTest::title() const
{
    return "Downloader";
}

std::string DownloaderBatchAsyncTest::subtitle() const
{
    return "Batch Async test";
}



