/****************************************************************************
 Copyright (c) 2016 Yuki Kuwabara <do_low@hotmail.com>
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

#include "CCRecordAdapter.h"
#include "extensions/TapRecorder/CCUtilTapRecorder.h"
#include "platform/CCFileUtils.h"
#include "json/filereadstream.h"
#include "json/filewritestream.h"
#include "json/writer.h"
#include <fstream>

USING_NS_CC_EXT;
using namespace TapRecorder::RecordAdapter;
using namespace rapidjson;

const std::string Text::RECORD_FILE_EXT = "taps";
const std::string Text::KEY_ARRAY_TAPS  = "taps";
const std::string Text::KEY_OBJECT_META = "meta";

const std::string Text::KEY_META_VERSION                  = "adapterVersion";
const std::string Text::KEY_META_DESIGN_RESOLUTION_POLICY = "designResolutionPolicy";
const std::string Text::KEY_META_DESIGN_RESOLUTION_SIZE_W = "designResolutionSizeX";
const std::string Text::KEY_META_DESIGN_RESOLUTION_SIZE_H = "designResolutionSizeY";
const std::string Text::KEY_META_SCALE_X                  = "scaleX";
const std::string Text::KEY_META_SCALE_Y                  = "scaleY";
const std::string Text::KEY_META_ANIMATION_INTERVAL       = "animationInterval";

std::string Text::defaultRecordFileName()
{
    time_t rawtime;
    time(&rawtime);
    
    char buffer[64];
    strftime(buffer, sizeof(buffer), "taprecorder_%Y%m%d%H%M%S", localtime(&rawtime));
    
    return std::string(buffer);
}

std::vector<std::string> Text::tapArrayElementOrder()
{
    return
    {
        Record::KEY_TOUCH_ID,
        Record::KEY_DURATION_UNIT,
        Record::KEY_DURATION,
        Record::KEY_EVENT_TYPE,
        Record::KEY_POSITION_X,
        Record::KEY_POSITION_Y
    };
}
bool Text::save(const std::string& filename, Records& records)
{
    std::vector<std::string> extraInfo = {};
    return this->save(filename, records, extraInfo);
}
bool Text::save(const std::string& filename, Records& records, std::vector<std::string>& extraInfo)
{
    std::string name = filename;
    if (name.empty())
        name = defaultRecordFileName();
    
    std::string path = getRecordFilePath(name);
    
    FileUtils* fileUtils = FileUtils::getInstance();
    
    // over write
    if (fileUtils->isFileExist(path))
        fileUtils->removeFile(path);
    
    Document document;
    document.SetObject();
    
    Document::AllocatorType& allocator =  document.GetAllocator();
    
    rapidjson::Value meta(kObjectType);
    {
        Director* director = Director::getInstance();
        GLView*   glview   = director->getOpenGLView();
        
        cocos2d::Size designResolutionSize = glview->getDesignResolutionSize();
        
        meta.AddMember(rapidjson::Value(KEY_META_VERSION.c_str(), allocator),
                       rapidjson::Value(Util::to_string(version).c_str(), allocator), allocator);
        meta.AddMember(rapidjson::Value(KEY_META_DESIGN_RESOLUTION_POLICY.c_str(), allocator),
                       rapidjson::Value(designResolutionPolicyToString(glview->getResolutionPolicy()).c_str(), allocator), allocator);
        meta.AddMember(rapidjson::Value(KEY_META_DESIGN_RESOLUTION_SIZE_W.c_str(), allocator),
                       rapidjson::Value(Util::to_string<float>(designResolutionSize.width).c_str(), allocator), allocator);
        meta.AddMember(rapidjson::Value(KEY_META_DESIGN_RESOLUTION_SIZE_H.c_str(), allocator),
                       rapidjson::Value(Util::to_string<float>(designResolutionSize.height).c_str(), allocator), allocator);
        meta.AddMember(rapidjson::Value(KEY_META_SCALE_X.c_str(), allocator),
                       rapidjson::Value(Util::to_string<float>(glview->getScaleX()).c_str(), allocator), allocator);
        meta.AddMember(rapidjson::Value(KEY_META_SCALE_Y.c_str(), allocator),
                       rapidjson::Value(Util::to_string<float>(glview->getScaleY()).c_str(), allocator), allocator);
        meta.AddMember(rapidjson::Value(KEY_META_ANIMATION_INTERVAL.c_str(), allocator),
                       rapidjson::Value(Util::to_string<float>(director->getAnimationInterval()).c_str(), allocator), allocator);
    }
    
    document.AddMember(rapidjson::Value(Text::KEY_OBJECT_META.c_str(), allocator), meta, allocator);
    
    
    rapidjson::Value taps(kArrayType);
    
    for (Records::iterator i = records.begin(); i != records.end(); ++i) {
        Record::StringifiedMapRecord record = (*i).toStringifiedMap();
        
        rapidjson::Value tap(kArrayType);
        for (std::string key : tapArrayElementOrder())
            tap.PushBack(rapidjson::Value(record[key].c_str(), allocator), allocator);
        
        taps.PushBack(tap, document.GetAllocator());
    }
    
    document.AddMember(rapidjson::Value(Text::KEY_ARRAY_TAPS.c_str(), allocator), taps, allocator);
    
    FILE* fp = fopen(path.c_str(), "wb");
    char buf[512];
    FileWriteStream ws(fp, buf, sizeof(buf));
    Writer<FileWriteStream> writer(ws);
    document.Accept(writer);
    fclose(fp);
    
    log("saved to : %s", path.c_str());
    
    extraInfo.push_back(path);
    
    return true;
}

bool Text::load(const std::string& filename, Records& records, MetaData& metaData)
{
    std::string path = getRecordFilePath(filename);
    
    FileUtils* fileUtils = FileUtils::getInstance();
    
    // use cocos2d-x file reader
    // since android's assets (apk) can not be searched or be loaded with regular file operation.
    std::string content = fileUtils->getStringFromFile(path);
    if (content.empty()) {
        content = fileUtils->getStringFromFile((filename) + (".") + RECORD_FILE_EXT);
        if (content.empty()) {
            log("counldn't find record file");
            return false;
        }
    }
    
    Document document;
    document.Parse(content.c_str());
    
    if (document.HasParseError()) {
        log("recorde is broken");
        return false;
    }
    
    records.clear();
    
    getMetaDataFromDocument(document, metaData);
    getTapsRecordsFromDocument(document, records);
    
    return true;
}

std::string Text::getRecordFilePath(const std::string& filename)
{
    return FileUtils::getInstance()->getWritablePath()
    .append("/")
    .append(filename)
    .append(".")
    .append(RECORD_FILE_EXT);
}

void Text::getMetaDataFromDocument(rapidjson::Document& document, MetaData& metaData)
{
    if (!document.HasMember(KEY_OBJECT_META.c_str()))
        return;
    
    rapidjson::Value& meta = document[KEY_OBJECT_META.c_str()];
    
    for (rapidjson::Value::ConstMemberIterator it = meta.MemberBegin(); it != meta.MemberEnd(); ++it) {
        if (std::strcmp(it->name.GetString(), KEY_META_VERSION.c_str()) == 0)
            metaData.adapterVersion = atoi(it->value.GetString());
        else if(std::strcmp(it->name.GetString(), KEY_META_DESIGN_RESOLUTION_POLICY.c_str()) == 0)
            metaData.designResolutionPolicy = stringToDesignResolutionPolicy(it->value.GetString());
        else if(std::strcmp(it->name.GetString(), KEY_META_DESIGN_RESOLUTION_SIZE_W.c_str()) == 0)
            metaData.designResolutionSize.width = atof(it->value.GetString());
        else if(std::strcmp(it->name.GetString(), KEY_META_DESIGN_RESOLUTION_SIZE_H.c_str()) == 0)
            metaData.designResolutionSize.height = atof(it->value.GetString());
        else if(std::strcmp(it->name.GetString(), KEY_META_SCALE_X.c_str()) == 0)
            metaData.scale.x = atof(it->value.GetString());
        else if(std::strcmp(it->name.GetString(), KEY_META_SCALE_Y.c_str()) == 0)
            metaData.scale.y = atof(it->value.GetString());
        else if(std::strcmp(it->name.GetString(), KEY_META_ANIMATION_INTERVAL.c_str()) == 0)
            metaData.animationInterval = atof(it->value.GetString());
    }
}
void Text::getTapsRecordsFromDocument(rapidjson::Document& document, Records& records)
{
    rapidjson::Value& taps = document[KEY_ARRAY_TAPS.c_str()];
    
    std::string recordStr;
    
    for (rapidjson::Value::ConstValueIterator it = taps.Begin(); it != taps.End(); ++it) {
        Record::StringifiedMapRecord map;
        
        int index = 0;
        for (std::string key : tapArrayElementOrder())
            map[key] = (*it)[index++].GetString();
        
        records.push_back(Record(map));
    }
}
