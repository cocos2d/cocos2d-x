/*
 * Copyright (C) 2014 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef MP3READER_H_
#define MP3READER_H_

typedef struct {
  size_t (*read)  (void *ptr, size_t size, size_t nmemb, void *datasource);
  int    (*seek)  (void *datasource, int64_t offset, int whence);
  int    (*close) (void *datasource);
  long   (*tell)  (void *datasource);
} mp3_callbacks;

class Mp3Reader {
public:
    Mp3Reader();
    bool init(mp3_callbacks *callback, void* source);
    bool getFrame(void *buffer, uint32_t *size);
    uint32_t getSampleRate() { return mSampleRate;}
    uint32_t getNumChannels() { return mNumChannels;}
    void close();
    ~Mp3Reader();
private:
    void *mSource;
    mp3_callbacks* mCallback;
    uint32_t mFixedHeader;
    off64_t  mCurrentPos;
    uint32_t mSampleRate;
    uint32_t mNumChannels;
    uint32_t mBitrate;
};

int decodeMP3(mp3_callbacks* cb, void* source, std::vector<char>& pcmBuffer, int* numChannels, int* sampleRate, int* numFrames);


#endif /* MP3READER_H_ */
