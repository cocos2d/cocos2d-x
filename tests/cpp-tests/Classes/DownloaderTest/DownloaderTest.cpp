/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
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

#include "DownloaderTest.h"

#include "../testResource.h"

#include "ui/UILoadingBar.h"
#include "ui/UIButton.h"
#include "network/CCDownloader.h"

USING_NS_CC;

static const char* sURLList[] =
{
    "http://www.cocos2d-x.org/attachments/802/cocos2dx_landscape.png",
    "http://www.cocos2d-x.org/docs/manual/framework/native/wiki/logo-resources-of-cocos2d-x/res/2dx_icon_512_rounded.png",
    "http://www.cocos2d-x.org/attachments/1503/no_exist.txt",  // try to download no exist file
    "http://download.sdkbox.com/installer/v1/sdkbox-iap_v2.3.6.1.tar.gz",
};
const static int sListSize = (sizeof(sURLList)/sizeof(sURLList[0]));
static const char* sNameList[sListSize] =
{
    "cocos2dx_landscape.png",
    "2dx_icon_512_rounded.png",
    "inexist file",
    "big file",
};

struct DownloaderTest : public TestCase
{
    CREATE_FUNC(DownloaderTest);
    
    virtual std::string title() const override { return "Downloader Test"; }
    
    std::unique_ptr<network::Downloader> downloader;
    
    DownloaderTest()
    {
        downloader.reset(new network::Downloader());
    }
    
    enum {
        TAG_TITLE = 1,
        TAG_BUTTON,
        TAG_PROGRESS_BAR,
        TAG_STATUS,
        TAG_SPRITE,
    };
    
    Node* createDownloadView(const char *name, const cocos2d::ui::Button::ccWidgetClickCallback &callback)
    {
        Size viewSize(220, 120);
        float margin = 5;
        
        // create background
        auto bg = ui::Scale9Sprite::createWithSpriteFrameName("button_actived.png");
        bg->setContentSize(viewSize);
        
        // add a title on the top
        auto title = Label::createWithTTF(name,"fonts/arial.ttf",16);
        title->setTag(TAG_TITLE);
        title->setAnchorPoint(Vec2(0.5, 1));
        title->setPosition(viewSize.width / 2, viewSize.height - margin);
        bg->addChild(title, 10);
        
        // add a button on the bottom
        auto btn = ui::Button::create("cocosui/animationbuttonnormal.png",
                                      "cocosui/animationbuttonpressed.png");
        btn->setTag(TAG_BUTTON);
        btn->setTitleText("Download");
        btn->setAnchorPoint(Vec2(0.5, 0));
        btn->setPosition(Vec2(viewSize.width / 2, margin));
        btn->addClickEventListener(callback);
        bg->addChild(btn, 10);
        
        // add a progress bar
        auto bar = ui::LoadingBar::create("ccs-res/cocosui/sliderProgress.png");
        bar->setTag(TAG_PROGRESS_BAR);
        bar->ignoreContentAdaptWithSize(false);
        bar->setAnchorPoint(Vec2(0.5, 0));
        bar->setContentSize(Size(viewSize.width - margin * 2, btn->getContentSize().height));
        bar->setPosition(btn->getPosition());
        bar->setVisible(false);
        bg->addChild(bar, 10);

        // add a status label
        auto label = Label::createWithTTF("","fonts/arial.ttf",14);
        label->setTag(TAG_STATUS);
        label->setAnchorPoint(Vec2(0.5, 0.5));
        label->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2));
        label->setContentSize(Size(viewSize.width, 0));
        label->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
        label->setDimensions(viewSize.width, viewSize.height);
        bg->addChild(label, 20);
        
        return bg;
    }
    
    virtual void onEnter() override
    {
        TestCase::onEnter();
        _restartTestItem->setVisible(true);
        
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_s9s_ui_plist);

        // add four download view in test case
        Node* topRightView = createDownloadView(sNameList[0], [this](Ref*)
        {
            auto view = this->getChildByName(sNameList[0]);
            auto sprite = view->getChildByTag(TAG_SPRITE);
            if (sprite)
            {
                sprite->removeFromParentAndCleanup(true);
            }
            auto btn = (ui::Button*)view->getChildByTag(TAG_BUTTON);
            btn->setEnabled(false);
            btn->setVisible(false);
            auto bar = (ui::LoadingBar*)view->getChildByTag(TAG_PROGRESS_BAR);
            bar->setPercent(0);
            bar->setVisible(true);
            this->downloader->createDownloadDataTask(sURLList[0], sNameList[0]);
        });
        topRightView->setName(sNameList[0]);
        topRightView->setAnchorPoint(Vec2(0, 0));
        topRightView->setPosition(VisibleRect::center());
        this->addChild(topRightView);

        Node* topLeftView = createDownloadView(sNameList[1], [this](Ref*)
        {
            auto view = this->getChildByName(sNameList[1]);
            auto sprite = view->getChildByTag(TAG_SPRITE);
            if (sprite)
            {
                sprite->removeFromParentAndCleanup(true);
            }
            auto btn = (ui::Button*)view->getChildByTag(TAG_BUTTON);
            btn->setEnabled(false);
            btn->setVisible(false);
            auto bar = (ui::LoadingBar*)view->getChildByTag(TAG_PROGRESS_BAR);
            bar->setPercent(0);
            bar->setVisible(true);
            bar->setEnabled(true);
            this->downloader->createDownloadDataTask(sURLList[1], sNameList[1]);
        });
        topLeftView->setName(sNameList[1]);
        topLeftView->setAnchorPoint(Vec2(1, 0));
        topLeftView->setPosition(VisibleRect::center());
        this->addChild(topLeftView);

        Node* bottomLeftView = createDownloadView(sNameList[2], [this](Ref*)
        {
            auto view = this->getChildByName(sNameList[2]);
            auto sprite = view->getChildByTag(TAG_SPRITE);
            if (sprite)
            {
                sprite->removeFromParentAndCleanup(true);
            }
            auto btn = (ui::Button*)view->getChildByTag(TAG_BUTTON);
            btn->setEnabled(false);
            btn->setVisible(false);
            auto bar = (ui::LoadingBar*)view->getChildByTag(TAG_PROGRESS_BAR);
            bar->setPercent(0);
            bar->setVisible(true);
            bar->setEnabled(true);
            auto path = FileUtils::getInstance()->getWritablePath() + "CppTests/DownloaderTest/" + sNameList[2];
            this->downloader->createDownloadFileTask(sURLList[2], path, sNameList[2]);
        });
        bottomLeftView->setName(sNameList[2]);
        bottomLeftView->setAnchorPoint(Vec2(1, 1));
        bottomLeftView->setPosition(VisibleRect::center());
        this->addChild(bottomLeftView);

        Node* bottomRightView = createDownloadView(sNameList[3], [this](Ref*)
        {
            auto view = this->getChildByName(sNameList[3]);
            auto btn = (ui::Button*)view->getChildByTag(TAG_BUTTON);
            btn->setEnabled(false);
            btn->setVisible(false);
            auto bar = (ui::LoadingBar*)view->getChildByTag(TAG_PROGRESS_BAR);
            bar->setPercent(0);
            bar->setVisible(true);
            bar->setEnabled(true);
            auto path = FileUtils::getInstance()->getWritablePath() + "CppTests/DownloaderTest/" + sNameList[3];
            this->downloader->createDownloadFileTask(sURLList[3], path, sNameList[3]);
        });
        bottomRightView->setName(sNameList[3]);
        bottomRightView->setAnchorPoint(Vec2(0, 1));
        bottomRightView->setPosition(VisibleRect::center());
        this->addChild(bottomRightView);

        // define progress callback
        downloader->onTaskProgress = [this](const network::DownloadTask& task,
                                          int64_t bytesReceived,
                                          int64_t totalBytesReceived,
                                          int64_t totalBytesExpected)
        {
            Node* view = this->getChildByName(task.identifier);
            auto bar = (ui::LoadingBar*)view->getChildByTag(TAG_PROGRESS_BAR);
            float percent = float(totalBytesReceived * 100) / totalBytesExpected;
            bar->setPercent(percent);
            char buf[32];
            sprintf(buf, "%.1f%%[total %d KB]", percent, int(totalBytesExpected/1024));
            auto status = (Label*)view->getChildByTag(TAG_STATUS);
            status->setString(buf);
        };
        
        // define success callback
        downloader->onDataTaskSuccess = [this](const cocos2d::network::DownloadTask& task,
                                               std::vector<unsigned char>& data)
        {
            // create texture from data
            Texture2D* texture = nullptr;
            do
            {
                Image img;
                if (false == img.initWithImageData(data.data(), data.size()))
                {
                    break;
                }
                
                texture = new Texture2D();
                if (false == texture->initWithImage(&img))
                {
                    break;
                }
                auto sprite = Sprite::createWithTexture(texture);
                auto view = this->getChildByName(task.identifier);
                auto viewSize = view->getContentSize();
                sprite->setPosition(viewSize.width / 2, viewSize.height / 2);
                auto spriteSize = sprite->getContentSize();
                float scale = MIN((viewSize.height - 20) / spriteSize.height, (viewSize.width - 20) / spriteSize.width);
                sprite->setScale(scale);
                view->addChild(sprite, 5, TAG_SPRITE);
                
                auto btn = (ui::Button*)view->getChildByTag(TAG_BUTTON);
                btn->setEnabled(true);
                btn->setVisible(true);
                auto bar = (ui::LoadingBar*)view->getChildByTag(TAG_PROGRESS_BAR);
                bar->setVisible(false);
            } while (0);
            CC_SAFE_RELEASE(texture);
        };
        
        downloader->onFileTaskSuccess = [this](const cocos2d::network::DownloadTask& task)
        {
            Texture2D* texture = nullptr;
            do
            {
                auto view = this->getChildByName(task.identifier);
                if (std::string::npos == task.storagePath.find(".png"))
                {
                    // download big file success
                    char buf[32];
                    sprintf(buf, "Download [%s] success.", task.identifier.c_str());
                    auto status = (Label*)view->getChildByTag(TAG_STATUS);
                    status->setString(buf);
                    break;
                }
                // create sprite from file
                auto sprite = Sprite::create(task.storagePath);
                auto viewSize = view->getContentSize();
                sprite->setPosition(viewSize.width / 2, viewSize.height / 2);
                auto spriteSize = sprite->getContentSize();
                float scale = MIN((viewSize.height - 20) / spriteSize.height, (viewSize.width - 20) / spriteSize.width);
                sprite->setScale(scale);
                view->addChild(sprite, 5, TAG_SPRITE);
                
                auto btn = (ui::Button*)view->getChildByTag(TAG_BUTTON);
                btn->setEnabled(true);
                btn->setVisible(true);
                auto bar = (ui::LoadingBar*)view->getChildByTag(TAG_PROGRESS_BAR);
                bar->setVisible(false);
            } while (0);
            CC_SAFE_RELEASE(texture);
        };
        
        // define failed callback
        downloader->onTaskError = [this](const cocos2d::network::DownloadTask& task,
                                         int errorCode,
                                         int errorCodeInternal,
                                         const std::string& errorStr)
        {
            log("Failed to download : %s, identifier(%s) error code(%d), internal error code(%d) desc(%s)"
                , task.requestURL.c_str()
                , task.identifier.c_str()
                , errorCode
                , errorCodeInternal
                , errorStr.c_str());
            auto view = this->getChildByName(task.identifier);
            auto status = (Label*)view->getChildByTag(TAG_STATUS);
            status->setString(errorStr.length() ? errorStr : "Download failed.");
            
            auto btn = (ui::Button*)view->getChildByTag(TAG_BUTTON);
            btn->setEnabled(true);
            btn->setVisible(true);
        };
    }
};

struct DownloaderMultiTask : public TestCase
{
    CREATE_FUNC(DownloaderMultiTask);

    virtual std::string title() const override { return "Downloader Multi Task"; }
    virtual std::string subtitle() const override { return "see the console output"; }

    std::unique_ptr<network::Downloader> downloader;

    DownloaderMultiTask()
    {
        // countOfMaxProcessingTasks 32
        network::DownloaderHints hints = {32, 60, ".going"};
        downloader.reset(new network::Downloader(hints));
    }

    virtual void onEnter() override
    {
        TestCase::onEnter();
        char path[256];
        char name[64];
        // add 64 download task at same time.
        for(int i=0; i< 64;i++){
            sprintf(name, "%d_%s", i, sNameList[0]);
            sprintf(path, "%sCppTests/DownloaderTest/%s", FileUtils::getInstance()->getWritablePath().c_str(), name);
            log("downloader task create: %s", name);
            this->downloader->createDownloadFileTask(sURLList[0], path, name);
        }

        downloader->onFileTaskSuccess = ([] (const network::DownloadTask& task) {
            log("downloader task success: %s", task.identifier.c_str());
        });

        downloader->onTaskError = ([] (const network::DownloadTask& task, int errorCode, int errorCodeInternal, const std::string& errorStr) {
            log("downloader task failed : %s, identifier(%s) error code(%d), internal error code(%d) desc(%s)"
                , task.requestURL.c_str()
                , task.identifier.c_str()
                , errorCode
                , errorCodeInternal
                , errorStr.c_str());
        });
    }
};

DownloaderTests::DownloaderTests()
{
    ADD_TEST_CASE(DownloaderTest);
    ADD_TEST_CASE(DownloaderMultiTask);
};
