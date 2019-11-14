/****************************************************************************
 Copyright (c) 2019 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

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

#include "ZipTests.h"

#include <sstream>

#include "unzip/unzip.h"
#include "unzip/crypt.h"

using namespace cocos2d;

ZipTests::ZipTests() {
    ADD_TEST_CASE(UnZipNormalFile);
    ADD_TEST_CASE(UnZipWithPassword);
}

std::string ZipTest::title() const {
    return "Unzip Test";
}


static void unzipTest(Label *label, const std::string &originFile, const std::string &tmpName, const std::string &zipFile, const std::string& password = "")
{

    auto fu = FileUtils::getInstance();
    cocos2d::Data origContent;
    const int BUFF_SIZE = 1024;
    char *buff = nullptr;
    std::vector<char> fileData;
    bool hasError = false;
    unz_file_info fileInfo = {0};
    char fileName[40] = {0};

    auto newLocal = fu->getWritablePath() + tmpName;
    //copy file to support android

    if(fu->isFileExist(newLocal)) {
        CCLOG("Remove file %s", newLocal.c_str());
        fu->removeFile(newLocal);
    }

    CCLOG("Copy %s to %s", zipFile.c_str(), newLocal.c_str());
    auto writeSuccess = fu->writeDataToFile(fu->getDataFromFile(zipFile), newLocal);
    if(!writeSuccess) {
        label->setString("Failed to copy zip file to writable path");
        return;
    }

    unzFile fp = unzOpen(newLocal.c_str());
    if(!fp) {
        CCLOG("Failed to open zip file %s", newLocal.c_str());
        label->setString("Failed to open zip file");
        return;
    }

    int err = unzGoToFirstFile(fp);
    if(err != UNZ_OK) {
        label->setString("Failed to local first file");
        goto close_and_return;
    }

    unzGetCurrentFileInfo(fp, &fileInfo, fileName, sizeof(fileName) -1, nullptr, 0, nullptr, 0 );

    CCASSERT(strncmp("10k.txt", fileName, 7) == 0, "file name should be 10k.txt");

    if(password.empty())
    {
        err = unzOpenCurrentFile(fp);
    }
    else
    {
        err = unzOpenCurrentFilePassword(fp, password.c_str());
    }

    if(err != UNZ_OK) {
        label->setString("failed to open zip file");
        goto close_and_return;
    }

    buff = new char[BUFF_SIZE];

    for(;;) {
        int retSize =  unzReadCurrentFile(fp, buff, BUFF_SIZE);
        if(retSize < 0) {
            hasError = true;
            break;
        }
        else if(retSize == 0) {
            break;
        }

        fileData.insert(fileData.end(), buff, buff + retSize);
    }

    delete[] buff;

    if(hasError) {
        label->setString("unzip error! read error!");
        goto close_and_return;
    }

    origContent = FileUtils::getInstance()->getDataFromFile(originFile);

    if(origContent.getSize() == fileData.size() &&
       memcmp(origContent.getBytes(), fileData.data(), fileData.size()) == 0) {
        label->setString("unzip ok!");
    } else {
        label->setString("unzip error! data mismatch!");
    }
close_and_return:
    unzClose(fp);
}


void UnZipNormalFile::onEnter() {
    TestCase::onEnter();

    const auto winSize = Director::getInstance()->getWinSize();

    Label *label = Label::createWithTTF("unziping file", "fonts/Marker Felt.ttf", 23);
    label->setPosition(winSize.width/2, winSize.height/2);
    addChild(label);

    unzipTest(label, "zip/10k.txt", "10-nopasswd.zip", "zip/10k-nopass.zip");
}

std::string UnZipNormalFile::subtitle() const {
    return "unzip without password";
}

void UnZipWithPassword::onEnter() {
    TestCase::onEnter();

    const auto winSize = Director::getInstance()->getWinSize();

    Label *label = Label::createWithTTF("unziping file", "fonts/Marker Felt.ttf", 23);
    label->setPosition(winSize.width/2, winSize.height/2);
    addChild(label);

    unzipTest(label, "zip/10k.txt", "10.zip", "zip/10k.zip", "123456");
}

std::string UnZipWithPassword::subtitle() const {
    return "unzip with password";
}
