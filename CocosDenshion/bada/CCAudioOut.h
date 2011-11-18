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

	result Play(void);
	result Stop(void);
	result Reset(void);
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
	int quiet;
	int bits;
	int endian;
	int raw;
	int sign;
};

}

#endif /* __CCAUDIOOUT_H__ */
