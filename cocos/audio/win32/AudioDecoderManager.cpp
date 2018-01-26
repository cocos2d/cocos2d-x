/****************************************************************************
Copyright (c) 2016-2017 Chukong Technologies Inc.

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

#define LOG_TAG "AudioDecoderManager"

#include "audio/win32/AudioDecoderManager.h"
#include "audio/win32/AudioDecoderOgg.h"
#include "audio/win32/AudioDecoderMp3.h"
#include "audio/win32/AudioMacros.h"
#include "platform/CCFileUtils.h"
#include "base/CCConsole.h"
#include "mpg123.h"

namespace cocos2d { namespace experimental {

static bool __mp3Inited = false;

bool AudioDecoderManager::init()
{
    return true;
}

void AudioDecoderManager::destroy()
{
    AudioDecoderMp3::destroy();
}

AudioDecoder* AudioDecoderManager::createDecoder(const char* path)
{
    std::string suffix = FileUtils::getInstance()->getFileExtension(path);
    if (suffix == ".ogg")
    {
        return new (std::nothrow) AudioDecoderOgg();
    }
    else if (suffix == ".mp3")
    {
        return new (std::nothrow) AudioDecoderMp3();
    }

    return nullptr;
}

void AudioDecoderManager::destroyDecoder(AudioDecoder* decoder)
{
    delete decoder;
}

}} // namespace cocos2d { namespace experimental {

