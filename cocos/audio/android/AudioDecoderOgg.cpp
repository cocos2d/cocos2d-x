/****************************************************************************
 Copyright (c) 2016-2017 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2018 x-studio365 @HALX99.

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

#include "audio/android/AudioDecoderOgg.h"
#include "audio/android/AudioMacros.h"
#include "platform/CCFileUtils.h"

#include "platform/android/CCFileUtils-android.h"
#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <unistd.h>
#include <errno.h>

#define LOG_TAG "AudioDecoderOgg"
#include "audio/android/log.h"

namespace cocos2d { namespace experimental {

    static AAsset*  ov_fopen_r(const char* path)
    {
        AAssetManager* asMgr = FileUtilsAndroid::getAssetManager();
        AAsset* asset = AAssetManager_open(FileUtilsAndroid::getAssetManager(), path, AASSET_MODE_UNKNOWN);
        return asset;
    };

    static size_t ov_fread_r(void* buffer, size_t element_size, size_t element_count, void* handle)
    {
        return AAsset_read((AAsset*)handle, buffer, element_size * element_count);
    }

    static int ov_fseek_r(void * handle, ogg_int64_t offset, int whence)
    {
        auto n = AAsset_seek((AAsset*)handle, offset, whence);
        return n >= 0 ? 0 : -1;
    }
    
    static long ov_ftell_r(void * handle)
    {
        return AAsset_seek((AAsset*)handle, 0, SEEK_CUR);
    }

    static int ov_fclose_r(void* handle) {
        AAsset_close((AAsset*)handle);
        return 0;
    }
    
    AudioDecoderOgg::AudioDecoderOgg()
    {
    }

    AudioDecoderOgg::~AudioDecoderOgg()
    {
        close();
    }

    bool AudioDecoderOgg::open(const char* path)
    {
        std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);
        int iret = -1;
        if(fullPath[0] != '/') {
            off_t start = 0, length = 0;
            std::string relativePath;
            size_t position = fullPath.find("assets/");
            if (0 == position)
            {
                // "assets/" is at the beginning of the path and we don't want it
                relativePath = fullPath.substr(strlen("assets/"));
            } else
            {
                relativePath = fullPath;
            }
            auto stream = ov_fopen_r(relativePath.c_str());
            if(stream == nullptr) {
                ALOGE("Trouble with ogg(1): %s\n", strerror(errno) );
                return false;
            }
            
            static ov_callbacks OV_CALLBACKS_AASSET = {
                ov_fread_r,
                ov_fseek_r,
                ov_fclose_r,
                ov_ftell_r
            };
            
            iret = ov_open_callbacks(stream, &_vf, nullptr, 0, OV_CALLBACKS_AASSET);
        }
        else {
            iret = ov_fopen(fullPath.c_str(), &_vf);
        }
        
        if (0 == iret)
        {
            // header
            vorbis_info* vi = ov_info(&_vf, -1);
            _sampleRate = static_cast<uint32_t>(vi->rate);
            _channelCount = vi->channels;
            _bytesPerFrame = vi->channels * sizeof(short);
            _totalFrames = static_cast<uint32_t>(ov_pcm_total(&_vf, -1));
            _isOpened = true;
            return true;
        }
        return false;
    }

    void AudioDecoderOgg::close()
    {
        if (isOpened())
        {
            ov_clear(&_vf);
            _isOpened = false;
        }
    }

    uint32_t AudioDecoderOgg::read(uint32_t framesToRead, char* pcmBuf)
    {
        int currentSection = 0;
        int bytesToRead = framesToRead * _bytesPerFrame;
        long bytesRead = ov_read(&_vf, pcmBuf, bytesToRead, 0, 2, 1, &currentSection);
        return static_cast<uint32_t>(bytesRead / _bytesPerFrame);
    }

    bool AudioDecoderOgg::seek(uint32_t frameOffset)
    {
        return 0 == ov_pcm_seek(&_vf, frameOffset);
    }

    uint32_t AudioDecoderOgg::tell() const
    {
        return static_cast<uint32_t>(ov_pcm_tell(const_cast<OggVorbis_File*>(&_vf)));
    }

}} // namespace cocos2d { namespace experimental {
