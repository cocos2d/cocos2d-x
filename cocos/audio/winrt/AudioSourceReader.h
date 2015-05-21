/*
* cocos2d-x   http://www.cocos2d-x.org
*
* Copyright (c) 2010-2011 - cocos2d-x community
*
* Portions Copyright (c) Microsoft Open Technologies, Inc.
* All Rights Reserved
*
* Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
*/

#include "platform/CCPlatformConfig.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WINRT

#ifndef __AUDIO_SOURCE_READER_H_
#define __AUDIO_SOURCE_READER_H_

#define NEAR near
#include "MediaStreamer.h"

NS_CC_BEGIN
namespace experimental{

const UINT PCMDATA_CACHEMAXSIZE = 2621440;
const UINT QUEUEBUFFER_NUM = 4;
const UINT CHUNK_SIZE_MAX = PCMDATA_CACHEMAXSIZE / QUEUEBUFFER_NUM;

enum class FileFormat
{
    UNKNOWN,
    WAV,
    MP3,
    OGG
};

typedef struct AudioDataChunk
{
    size_t _dataSize;
    unsigned char *_data;
    bool _endOfStream;
    int _seqNo;
} AudioDataChunk;


class AudioSourceReader
{
public:
    AudioSourceReader();
    virtual ~AudioSourceReader();

    bool isStreamingSource() { return _isStreaming; }
    std::string getFilePath() { return _filePath; }
    virtual size_t getTotalAudioBytes() { return _audioSize; }
    
    virtual bool initialize(const std::string& filePath) = 0;
    virtual FileFormat getFileFormat() = 0;
    virtual  bool consumeChunk(AudioDataChunk& chunk) = 0;
    virtual  void produceChunk() = 0;
    virtual void seekTo(const float ratio) = 0;
    virtual const WAVEFORMATEX& getWaveFormatInfo() { return _wfx; }

protected:
    bool _isStreaming;
    std::string _filePath;
    size_t _audioSize;
    WAVEFORMATEX _wfx;
};

class WAVReader : public AudioSourceReader
 {
 public:
     WAVReader();
     ~WAVReader();

     bool initialize(const std::string& filePath) override;
     FileFormat getFileFormat() override { return FileFormat::WAV; }
     bool consumeChunk(AudioDataChunk& chunk) override;
     void produceChunk() override;
     void seekTo(const float ratio) override;

 protected:
     void enqueueChunk(const AudioDataChunk& chunk);
     void flushChunks();

 private:
     bool _isDirty;
     size_t _bytesRead;
     std::mutex _rwMutex;
     MediaStreamer^ _streamer;
     std::queue<AudioDataChunk> _chnkQ;
 };

class MP3Reader : public AudioSourceReader
 {
 };

}
NS_CC_END
#endif // __AUDIO_SOURCE_READER_H_
#endif

