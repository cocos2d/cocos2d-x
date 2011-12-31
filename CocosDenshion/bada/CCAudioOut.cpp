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

#include "CCAudioOut.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <FSystem.h>

#define OGG_SUPPORT

#ifdef OGG_SUPPORT
#include "vorbis/vorbisfile.h"
#endif

using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Media;
using namespace Osp::Io;

namespace CocosDenshion {

#define PRE_BUFFERING_NUM 2
#define DEFAULT_VOLUME_LEVEL 5

typedef struct wave_tag
{
    char              ChunkID[5];
    unsigned long int ChunkSize;
    char              Format[5];
    char              SubChunk1ID[5];
    unsigned long int SubChunk1Size;
    unsigned short int   AudioFormat;
    unsigned short int   NumChannels;
    unsigned long int    SampleRate;
    unsigned long int    ByteRate;
    unsigned short int   BlockAlign;
    unsigned short int   BitsPerSample;
    char              SubChunk2ID[5];
    unsigned long int SubChunk2Size;
}WAVE;

static void GetWaveHeadInfo(File* pFile, WAVE& outWavHead)
{
	char szTmp[100] = {0};
	int i = 0;
	memset(&outWavHead, 0, sizeof(WAVE));
    pFile->Read(outWavHead.ChunkID, 4);
    pFile->Read(&(outWavHead.ChunkSize),4);
    pFile->Read(outWavHead.Format, 4);
    pFile->Read(outWavHead.SubChunk1ID, 4);
    pFile->Read(&(outWavHead.SubChunk1Size), 4);
    pFile->Read(&(outWavHead.AudioFormat),   2);
    pFile->Read(&(outWavHead.NumChannels),   2);
    pFile->Read(&(outWavHead.SampleRate), 4);
    pFile->Read(&(outWavHead.ByteRate),      4);
    pFile->Read(&(outWavHead.BlockAlign), 2);
    pFile->Read(&(outWavHead.BitsPerSample), 2);

	pFile->Seek(FILESEEKPOSITION_BEGIN, 0);
	pFile->Read(szTmp, 64);

	for (i = 0; i <= 60; i++)
	{
		if (szTmp[i] == 'd' && szTmp[i+1] == 'a' && szTmp[i+2] == 't' && szTmp[i+3] == 'a')
		{
			break;
		}
	}

	pFile->Seek(FILESEEKPOSITION_BEGIN, i);
    pFile->Read(outWavHead.SubChunk2ID, 4);
    pFile->Read(&(outWavHead.SubChunk2Size), 4);
}

int CCAudioOut::DecodeOgg(const char *infile)
{
#ifdef OGG_SUPPORT
    FILE *in=NULL;
    OggVorbis_File vf;
    int bs = 0;
    char buf[8192];
    int buflen = 8192;
    unsigned int written = 0;
    int ret;
    ogg_int64_t length = 0;
    ogg_int64_t done = 0;
    int size;
    int seekable = 0;
    int percent = 0;

	in = fopen(infile, "rb");
	if(!in) {
		AppLog("ERROR: Failed to open input file:\n");
		return 1;
	}

    if(ov_open(in, &vf, NULL, 0) < 0) {
    	AppLog("ERROR: Failed to open input as vorbis\n");
        fclose(in);
        return 1;
    }

    if(ov_seekable(&vf)) {
        seekable = 1;
        length = ov_pcm_total(&vf, 0);
        size = 16/8 * ov_info(&vf, 0)->channels;
    }

    if (ov_info(&vf,0)->channels == 2)
    {
    	__sampleChannelType = AUDIO_CHANNEL_TYPE_STEREO;
    }
    else
    {
    	__sampleChannelType = AUDIO_CHANNEL_TYPE_MONO;
    }

    __sampleRate = ov_info(&vf,0)->rate;
    __sampleBitdepth = AUDIO_TYPE_PCM_S16_LE;


    while((ret = ov_read(&vf, buf, buflen, 0, 16/8, 1, &bs)) != 0) {
        if(bs != 0) {
            AppLog("Only one logical bitstream currently supported\n");
            break;
        }

        if(ret < 0) {
            AppLog("Warning: hole in data\n");
            continue;
        }

        if (__pAllPcmBuffer == null)
        {
        	__pAllPcmBuffer = (char*)malloc(ret);
        }
        else
        {
			__pAllPcmBuffer = (char*)realloc(__pAllPcmBuffer, written+ret);
        }

        memcpy(__pAllPcmBuffer+written, buf, ret);

        written += ret;
        if(seekable) {
            done += ret/size;
            if((double)done/(double)length * 200. > (double)percent) {
                percent = (double)done/(double)length *200;
//                //AppLog("[%5.1f%%]", (double)percent/2.);
            }
        }
    }

    __iAllPcmBufferSize = written;

    ov_clear(&vf);
    fclose(in);

#endif

    return 0;
}


CCAudioOut::CCAudioOut()
{

	__volumeLevel = -1;
	__pAllPcmBuffer = null;
	__iAllPcmBufferSize = 0;
	__iAllPcmPos = 0;
	__pAudioOut = null;
	__iFileType = 0;
	__pFile = null;
	__bShortPcmBuffer = false;
	__bBufferConstruted = false;
	__checkInitFiniPair = false;
	__iUsedBufferCount = 0;
	__bLoop = false;
	__bPause = false;
}

CCAudioOut::~CCAudioOut()
{

	Finalize();
	if(__pAudioOut)
	{
		delete __pAudioOut;
		__pAudioOut = null;
	}

	if (__pAllPcmBuffer)
	{
		free(__pAllPcmBuffer);
		__pAllPcmBuffer = null;
	}
}

result CCAudioOut::Initialize(const char* pszFilePath)
{

	// This is called when AudioOut form is moving on the foreground.
	result r = E_SUCCESS;

	__pAllPcmBuffer = null;
	__iAllPcmBufferSize = 0;
	__iAllPcmPos = 0;
	__iUsedBufferCount = 0;

	if(__checkInitFiniPair == false)
	{
		// Reset the configure variables
		__finishChecker =0;
		__bufWrittenCnt = PRE_BUFFERING_NUM;
		__buffReadCnt = 0;
		__buffWriteCnt = 0;


		result r = E_FAILURE;
		if (__pAudioOut == NULL)
		{
			__pAudioOut = new AudioOut();
			if (!__pAudioOut)
			{
				AppLog("[E_OUT_OF_MEMORY] m_pAudio new failed\n");
				return r;
			}

			r = __pAudioOut->Construct(*this);
			if (IsFailed(r))
			{
				AppLog("[Error] m_AudioOut.Construct failed");
				return r;
			}
		}
		else
		{
			AppLog("[Error] __pAudioOut is already existed\n");
		}

		String strFile(pszFilePath);
		if (strFile.EndsWith(".wav"))
		{
			__iFileType = 0;
			// Construct File for feeding buffers
			__pFile = new File();
			if(!__pFile)
			{
				AppLog("[Error] __pFile new failed\n");
				return E_SYSTEM;
			}

			r = __pFile->Construct(pszFilePath, L"rb");
			if (IsFailed(r)) {
				AppLog("[Error] __pFile.Construct failed : %d \n", r);
				return r;
			}

			WAVE wavHead;
			GetWaveHeadInfo(__pFile, wavHead);
			__iAllPcmBufferSize = wavHead.SubChunk2Size;

			if (wavHead.BitsPerSample == 8)
			{
				__sampleBitdepth = AUDIO_TYPE_PCM_U8;

			}
			else if (wavHead.BitsPerSample == 16)
			{
				__sampleBitdepth = AUDIO_TYPE_PCM_S16_LE;
			}
			else
			{
				__sampleBitdepth = AUDIO_TYPE_NONE;
			}

			if (wavHead.NumChannels == 1)
			{
				__sampleChannelType = AUDIO_CHANNEL_TYPE_MONO;
			}
			else if (wavHead.NumChannels == 2)
			{
				__sampleChannelType = AUDIO_CHANNEL_TYPE_STEREO;
			}
			else
			{
				__sampleChannelType = AUDIO_CHANNEL_TYPE_NONE;
			}

			__sampleRate = wavHead.SampleRate;
			__pAllPcmBuffer = (char*)malloc(__iAllPcmBufferSize);
			if (__pAllPcmBuffer != NULL)
			{
				__pFile->Read(__pAllPcmBuffer, __iAllPcmBufferSize);
			}
			else
			{
				AppLog("not more memory...");
			}
		}
		else if (strFile.EndsWith(".ogg"))
		{
			__iFileType = 1;
			long long curTick, oldTick;
			Osp::System::SystemTime::GetTicks(oldTick);
			DecodeOgg(pszFilePath);
			Osp::System::SystemTime::GetTicks(curTick);
			//AppLog("decode ogg to pcm waste %ld", (long)(curTick-oldTick));
		}
		// Prepare AudioOut
		r = __pAudioOut->Prepare( __sampleBitdepth, __sampleChannelType, __sampleRate );
		if (IsFailed(r))
		{
			AppLog("[Error] m_AudioOut.Prepare failed");
			return r;
		}

		__bufferSize = __pAudioOut->GetMinBufferSize();
		//AppLog("[Info] __bufferSize=%d (MaxBuf=%d Min Size %d)\n", __bufferSize, __pAudioOut->GetMaxBufferSize(),__pAudioOut->GetMinBufferSize());

		// Reset Volume or keeping a volume level
		__volumeLevel = __volumeLevel == -1 ? DEFAULT_VOLUME_LEVEL : __volumeLevel;
		r = __pAudioOut->SetVolume(DEFAULT_VOLUME_LEVEL);
		if (IsFailed(r))
		{
			AppLog("[Error] m_AudioOut.SetVolume failed");
			return r;
		}

		if (!__bBufferConstruted)
		{
			__bBufferConstruted = true;
			r = __byteBuffer[0].Construct(__bufferSize);
			if (E_SUCCESS != r)
			{
				AppLog( "[Error] __byteBuffer[0].Construct failed..%d ",r);
				return E_OUT_OF_MEMORY;
			}
			r = __byteBuffer[1].Construct(__bufferSize);
			if (E_SUCCESS != r)
			{
				AppLog( "[Error] __byteBuffer[1].Construct failed..%d ",r);
				return E_OUT_OF_MEMORY;
			}
			r = __byteBuffer[2].Construct(__bufferSize);
			if (E_SUCCESS != r)
			{
				AppLog( "[Error] __byteBuffer[2].Construct failed..%d ",r);
				return E_OUT_OF_MEMORY;
			}
			r = __byteBuffer[3].Construct(__bufferSize);
			if (E_SUCCESS != r)
			{
				AppLog( "[Error] __byteBuffer[3].Construct failed..%d ",r);
				return E_OUT_OF_MEMORY;
			}
		}

		if (__iAllPcmBufferSize <= __bufferSize * 4)
		{
			__bShortPcmBuffer = true;
		}
		else
		{
			__bShortPcmBuffer = false;
		}

		ReWriteBuffer();
		__checkInitFiniPair = true;

	}else{
		//AppLog("[WANRNING] The application state is not proper");
	}
	return r;
}

result CCAudioOut::FeedBuffer (void)
{
	result ret = E_FAILURE;

//	if (__iFileType == 0)
//	{
//		/*
//		 *  Read buffer from file
//		 */
//		if(__pFile)
//		{
//			readSize = __pFile->Read((char *)__byteBuffer[__buffWriteCnt].GetPointer (), __bufferSize);
//			if(readSize != 0)
//			{
//				__buffWriteCnt ++;
//				if (4 == __buffWriteCnt)
//				{
//					__buffWriteCnt = 0;
//				}
//			}else
//			{
//				__finishChecker = PRE_BUFFERING_NUM;
//				__buffWriteCnt = 0;
//			}
//		}
//	}
//	else if (__iFileType == 1)
	{// ogg
		int iRemainSize = __iAllPcmBufferSize - __iAllPcmPos;
		if (iRemainSize < __bufferSize)
		{
			memcpy((void*)__byteBuffer[__buffWriteCnt].GetPointer (), __pAllPcmBuffer+__iAllPcmPos, iRemainSize);
			__iAllPcmPos += iRemainSize;
		}
		else
		{
			memcpy((void*)__byteBuffer[__buffWriteCnt].GetPointer (), __pAllPcmBuffer+__iAllPcmPos, __bufferSize);
			__iAllPcmPos += __bufferSize;
		}

		__iUsedBufferCount++;

		if (__iAllPcmPos < __iAllPcmBufferSize)
		{
			__buffWriteCnt ++;
			if (4 == __buffWriteCnt)
			{
				__buffWriteCnt = 0;
			}
		}
		else
		{
			__finishChecker = PRE_BUFFERING_NUM;
			__buffWriteCnt = 0;
			__iAllPcmPos = 0;
			ret = E_SUCCESS;
		}
	}

	return ret;
}

result CCAudioOut::ReWriteBuffer(void)
{
	int i = 0;
	result r = E_FAILURE;
	__iAllPcmPos = 0;
	__iUsedBufferCount = 0;
	if (__bShortPcmBuffer)
	{
		for (i=0; i<4; i++)
		{
			r = FeedBuffer();
			if (!IsFailed(r)) // Feeding buffers(4)
			{
				break;
			}
		}

		for (i = 0; i < __iUsedBufferCount; i++)
		{
			r = __pAudioOut->WriteBuffer(__byteBuffer[i]);
			if (IsFailed(r))
			{
				AppLog("[Error] m_AudioOut.WriteBuffer failed : %d\n", r);
				return r;
			}
		}
	}
	else
	{
		for (i=0; i<4; i++)
		{
			FeedBuffer(); // Feeding buffers(4)
		}

		for (i = 0; i < 2; i++)
		{
			r = __pAudioOut->WriteBuffer(__byteBuffer[i]);
			if (IsFailed(r))
			{
				AppLog("[Error] m_AudioOut.WriteBuffer failed : %d\n", r);
				return r;
			}
		}
	}
	return r;
}

void CCAudioOut::ReFeedBuffer(void)
{
	result r = E_SUCCESS;
	for (int i=0; i<4; i++)
	{
		FeedBuffer(); // Feeding buffers(4)
	}

	r = __pAudioOut->WriteBuffer(__byteBuffer[0]);
	if (IsFailed(r))
	{
		//AppLog("[Error] m_AudioOut.WriteBuffer failed : %d\n", r);
	}

	r = __pAudioOut->WriteBuffer(__byteBuffer[1]);
	if (IsFailed(r))
	{
		//AppLog("[Error] m_AudioOut.WriteBuffer failed : %d\n", r);
	}
}

result CCAudioOut::Play(bool bLoop/* = false*/)
{
	result ret = E_FAILURE;
	AudioOutState state = __pAudioOut->GetState();

	if(state == AUDIOOUT_STATE_PREPARED || state == AUDIOOUT_STATE_STOPPED)
	{
		__bLoop = bLoop;
		ret = __pAudioOut->Start();
		if (IsFailed(ret))
		{
			AppLog("[Error] m_AudioOut.Start failed : %d\n", ret);
		}
	}
	return ret;
}

result CCAudioOut::Stop(void)
{
	AudioOutState state = __pAudioOut->GetState();
	result r = E_SUCCESS;

	__bPause = false;
	if(state == AUDIOOUT_STATE_PLAYING)
	{
		r = __pAudioOut->Reset();
		if(IsFailed(r))
		{
			AppLog("[Error] AudioOut Reset is failed");
		}
		ReWriteBuffer();
	}

	return r;
}

result CCAudioOut::Pause(void)
{
	result ret = E_FAILURE;

	if( __pAudioOut->GetState() == AUDIOOUT_STATE_PLAYING )
	{
		__bPause = true;
		ret = __pAudioOut->Stop();
		if (IsFailed(ret))
		{
			AppLog("[Error] m_AudioOut.Stop failed : %d\n", ret);
		}
	}

	return ret;
}

result CCAudioOut::Resume(void)
{
	result ret = E_FAILURE;

	if(__bPause && __pAudioOut->GetState() == AUDIOOUT_STATE_STOPPED )
	{
		__bPause = false;
		ret = __pAudioOut->Start();
		if (IsFailed(ret))
		{
			AppLog("[Error] m_AudioOut.Stop failed : %d\n", ret);
		}
	}

	return ret;
}

void CCAudioOut::OnAudioOutBufferEndReached(Osp::Media::AudioOut& src)
{
	if (__bShortPcmBuffer)
	{
		__iUsedBufferCount--;
		if (__iUsedBufferCount <= 0)
		{
			Stop();
			if (__bLoop)
			{
				Play(__bLoop);
			}
		}
	}
	else
	{
		int ret = 0;
	//	//AppLog("thread name is %S", Thread::GetCurrentThread()->GetName().GetPointer());
		//AppLog("__buffReadCnt = %d", __buffReadCnt);
		__byteBuffer[__buffReadCnt++].Clear ();

		if (4 == __buffReadCnt)
				__buffReadCnt = 0;

		if(__finishChecker == 0)
		{
			ret = src.WriteBuffer(__byteBuffer[__bufWrittenCnt++]);
			if (4 == __bufWrittenCnt)
				__bufWrittenCnt = 0;
			FeedBuffer();

		}
		else
		{
			//AppLog("__finishChecker = %d", __finishChecker);
			__finishChecker--;
			if(__finishChecker == 0)
			{
				Stop();
				__bufWrittenCnt = PRE_BUFFERING_NUM;
				__buffReadCnt = 0;
				__buffWriteCnt = 0;
				if (__bLoop)
				{
					Play(__bLoop);
				}
			}
		}
	}

}

void CCAudioOut::OnAudioOutInterrupted(Osp::Media::AudioOut& src)
{
	Pause();
}

void CCAudioOut::OnAudioOutReleased(Osp::Media::AudioOut& src)
{
	Resume();
}

void CCAudioOut::Finalize(void)
{
	if(__checkInitFiniPair)
	{

		// Set OnAudioOutBufferEndReached stop.
		__finishChecker = PRE_BUFFERING_NUM;

		if(__pAudioOut)
		{

			AudioOutState state = __pAudioOut->GetState();
			result r = E_SUCCESS;

			if(state == AUDIOOUT_STATE_PLAYING)
			{
				r = __pAudioOut->Reset();
				if(IsFailed(r))
				{
					AppLog("[Error] AudioOut Reset is failed");
				}

			}

			state = __pAudioOut->GetState();

			if(state == AUDIOOUT_STATE_PREPARED || state == AUDIOOUT_STATE_STOPPED)
			{
				r = __pAudioOut->Unprepare();
				if(IsFailed(r))
				{
					AppLog("[Error] AudioOut UnPrepare is failed");
				}
			}
		}

		if(__pFile)
		{
			delete __pFile;
			__pFile = null;
		}

		__checkInitFiniPair = false;
	}else{
		AppLog("[WANRNING] This application state is not proper");
	}
}

void CCAudioOut::SetVolume(int volume)
{
	if (__pAudioOut)
		__pAudioOut->SetVolume(volume);
}

int CCAudioOut::GetVolume(void) const
{
	int ret = 0;
	if (__pAudioOut)
		ret = __pAudioOut->GetVolume();
	return ret;
}

Osp::Media::AudioOutState CCAudioOut::GetState(void) const
{
	AudioOutState state = AUDIOOUT_STATE_ERROR;
	if (__pAudioOut)
		state = __pAudioOut->GetState();
	return state;
}

}

