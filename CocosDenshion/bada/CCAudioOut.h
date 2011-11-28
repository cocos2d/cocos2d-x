/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#ifndef __CCAUDIOOUT_H__
#define __CCAUDIOOUT_H__

#include <FBase.h>
#include <FMedia.h>
#include <FIo.h>

namespace CocosDenshion {

class CCAudioOut:
	public Osp::Media::IAudioOutEventListener
{

public:
	CCAudioOut();
	virtual ~CCAudioOut();

	virtual void OnAudioOutBufferEndReached(Osp::Media::AudioOut& src);
	virtual void OnAudioOutInterrupted(Osp::Media::AudioOut& src);
	virtual void OnAudioOutReleased(Osp::Media::AudioOut& src);

	int DecodeOgg(const char *infile);
	result Initialize(const char* pszFilePath);
	result FeedBuffer (void);
	result ReWriteBuffer(void);
	void ReFeedBuffer(void);
	void Finalize(void);

	result Play(bool bLoop = false);
	result Stop(void);
	result Pause(void);
	result Resume(void);

	void SetVolume(int volume);
	int GetVolume(void) const;
	Osp::Media::AudioOutState GetState(void) const;
private:
	Osp::Media::AudioOut 	*__pAudioOut;
	Osp::Base::ByteBuffer  	__byteBuffer [4];
	bool __bBufferConstruted;
	int __iUsedBufferCount;
	Osp::Io::File 			*__pFile;
	Osp::Media::AudioChannelType __sampleChannelType;
	Osp::Media::AudioSampleType __sampleBitdepth;
	bool					__checkInitFiniPair;
	int	__bufferSize;
	int __finishChecker;
	int __buffWriteCnt;
	int __buffReadCnt;
	int __bufWrittenCnt;
	int __volumeLevel;
	bool __bShortPcmBuffer;

	int __iFileType; // 0: wav; 1:ogg
	int __sampleRate;
	char* __pAllPcmBuffer;
	int __iAllPcmBufferSize;
	int __iAllPcmPos;
	bool __bLoop;
	bool __bPause;
};

}

#endif /* __CCAUDIOOUT_H__ */
