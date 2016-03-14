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

#ifndef TapRecorder_RecordAdapter_h
#define TapRecorder_RecordAdapter_h

#include "extensions/ExtensionMacros.h"
#include "base/CCDirector.h"
#include "math/Vec2.h"
#include "math/CCGeometry.h"
#include "json/document.h"
#include "extensions/TapRecorder/CCRecord.h"

NS_CC_EXT_BEGIN

namespace TapRecorder { namespace RecordAdapter {
    
    struct MetaData
    {
        MetaData()
        : adapterVersion(0)
        , designResolutionPolicy(ResolutionPolicy::UNKNOWN)
        , designResolutionSize(cocos2d::Size::ZERO)
        , scale(cocos2d::Size::ZERO)
        , animationInterval(cocos2d::Director::getInstance()->getAnimationInterval())
        {}
        
        std::string name() { return "meta"; }
        
        int              adapterVersion;
        ResolutionPolicy designResolutionPolicy;
        cocos2d::Size    designResolutionSize;
        cocos2d::Vec2    scale;
        float            animationInterval;
    };
    
    /**
     * Tap records are saved with plain text by default.
     * Expand this if any other format is prefered.
     *
     * TODO: split classes to each file when new format is added.
     */
    class Interface
    {
    public:
        virtual ~Interface() {};
        
        virtual bool save(const std::string&, Records&, std::vector<std::string>&) = 0;
        virtual bool load(const std::string&, Records&, MetaData&) = 0;
        std::string designResolutionPolicyToString(ResolutionPolicy policy)
        {
            switch (policy) {
                case ResolutionPolicy::EXACT_FIT    : return "EXACT_FIT";
                case ResolutionPolicy::NO_BORDER    : return "NO_BORDER";
                case ResolutionPolicy::SHOW_ALL     : return "SHOW_ALL";
                case ResolutionPolicy::FIXED_HEIGHT : return "FIXED_HEIGHT";
                case ResolutionPolicy::FIXED_WIDTH  : return "FIXED_WIDTH";
                case ResolutionPolicy::UNKNOWN      :
                default                             : return "UNKNOWN";
            }
        }
        ResolutionPolicy stringToDesignResolutionPolicy(std::string policy)
        {
            
            if      (policy == "EXACT_FIT")    return ResolutionPolicy::EXACT_FIT;
            else if (policy == "NO_BORDER")    return ResolutionPolicy::NO_BORDER;
            else if (policy == "SHOW_ALL")     return ResolutionPolicy::SHOW_ALL;
            else if (policy == "FIXED_HEIGHT") return ResolutionPolicy::FIXED_HEIGHT;
            else if (policy == "FIXED_WIDTH")  return ResolutionPolicy::FIXED_WIDTH;
            else                               return ResolutionPolicy::UNKNOWN;
        }
    };
    
    class Text : public Interface
    {
    public:
        static const int version = 0x00010002;
        
        static const std::string RECORD_FILE_EXT;
        static const std::string KEY_ARRAY_TAPS;
        static const std::string KEY_OBJECT_META;
        
        // meta info keys
        static const std::string KEY_META_VERSION;
        static const std::string KEY_META_DESIGN_RESOLUTION_POLICY;
        static const std::string KEY_META_DESIGN_RESOLUTION_SIZE_W;
        static const std::string KEY_META_DESIGN_RESOLUTION_SIZE_H;
        static const std::string KEY_META_SCALE_X;
        static const std::string KEY_META_SCALE_Y;
        static const std::string KEY_META_ANIMATION_INTERVAL;
        
        /**
         * To reduce file buffer, tap info is stored as array.
         * This vector indicates order of record elements.
         */
        static std::vector<std::string> tapArrayElementOrder();
        
        virtual ~Text() {}
        
        static std::string defaultRecordFileName();
        
        bool save(const std::string&, Records&);
        virtual bool save(const std::string&, Records&, std::vector<std::string>&);
        virtual bool load(const std::string&, Records&, MetaData&);
        
        std::string getRecordFilePath(const std::string& filename);
        
    private:
        void getMetaDataFromDocument(rapidjson::Document&, MetaData&);
        void getTapsRecordsFromDocument(rapidjson::Document&, Records&);
    };
}}

NS_CC_EXT_END

#endif /* TapRecorder_RecordAdapter_h */
