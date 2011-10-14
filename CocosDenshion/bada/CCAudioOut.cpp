#include "CCAudioOut.h"
#include <stdio.h>

using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Media;

#define MAX_BUFFER_SIZE	2520 // 840 byte

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

static bool GetWaveHeadInfo(FILE*stream, WAVE& outWavHead)
{
	char szTmp[100] = {0};
	int i = 0;

    fread(outWavHead.ChunkID, 4, 1, stream);
    outWavHead.ChunkID[4] = (char)0;
    fread(&(outWavHead.ChunkSize),4, 1, stream);
    fread(outWavHead.Format, 4, 1, stream);
    outWavHead.Format[4] = (char)0;
    fread(outWavHead.SubChunk1ID, 4, 1, stream);
    outWavHead.SubChunk1ID[4] = (char)0;
    fread(&(outWavHead.SubChunk1Size), 4, 1, stream);
    fread(&(outWavHead.AudioFormat),   2, 1, stream);
    fread(&(outWavHead.NumChannels),   2, 1, stream);
    fread(&(outWavHead.SampleRate), 4, 1, stream);
    fread(&(outWavHead.ByteRate),      4, 1, stream);
    fread(&(outWavHead.BlockAlign), 2, 1, stream);
    fread(&(outWavHead.BitsPerSample), 2, 1, stream);

	fseek(stream, 0, SEEK_SET);
	fread(szTmp, 64, 1, stream);

	for (i = 0; i <= 60; i++)
	{
		if (szTmp[i] == 'd' && szTmp[i+1] == 'a' && szTmp[i+2] == 't' && szTmp[i+3] == 'a')
		{
			break;
		}
	}

	fseek(stream, i, SEEK_SET);
    fread(outWavHead.SubChunk2ID,      4, 1, stream);
    outWavHead.SubChunk2ID[4] = (char)0;

    fread(&(outWavHead.SubChunk2Size), 4, 1, stream);

    return true;
}

MyAudioOutEventListener::MyAudioOutEventListener()
{
	__totalWriteBufferNum = 0;
	__playCount = 0;
	__pDataArray = null;
	__pAudioOut = null;
	__pPcmBuffer = null;
	__pcmLen = 0;
}

MyAudioOutEventListener::~MyAudioOutEventListener()
{
	AppLog("dealoc MyAudioOutEventListener");

	if (__pDataArray != null)
	{
		__pDataArray->RemoveAll(true);
		delete __pDataArray;
		__pDataArray = null;
	}
	if (__pAudioOut != null)
	{
		__pAudioOut->Stop();
		__pAudioOut->Unprepare();
		delete __pAudioOut;
		__pAudioOut = null;
	}
	if (__pPcmBuffer != null)
	{
		delete[] __pPcmBuffer;
		__pPcmBuffer = null;
	}
}

result MyAudioOutEventListener::Construct(const char* pszFilePath)
{
	__pAudioOut = new AudioOut();
	__pAudioOut->Construct(*this);
	WAVE wavHead;
	FILE* fp = fopen(pszFilePath, "rb");
	if (fp != NULL)
	{
		if (GetWaveHeadInfo(fp, wavHead))
		{
			__pPcmBuffer = new char[wavHead.SubChunk2Size];
			__pcmLen = wavHead.SubChunk2Size;
			fread(__pPcmBuffer, __pcmLen, 1, fp);
			fclose(fp);
		}
		else
		{
			fclose(fp);
			return E_FAILURE;
		}
	}

	__pDataArray = new ArrayList();

	// AudioOut Preparation
	AudioSampleType audioSampleType;
	AudioChannelType audioChannelType;
	int audioSampleRate = 0;

	if (wavHead.BitsPerSample == 8)
	{
		audioSampleType = AUDIO_TYPE_PCM_U8;

	}
	else if (wavHead.BitsPerSample == 16)
	{
		audioSampleType = AUDIO_TYPE_PCM_S16_LE;
	}
	else
	{
		audioSampleType = AUDIO_TYPE_NONE;
	}

	if (wavHead.NumChannels == 1)
	{
		audioChannelType = AUDIO_CHANNEL_TYPE_MONO;
	}
	else if (wavHead.NumChannels == 2)
	{
		audioChannelType = AUDIO_CHANNEL_TYPE_STEREO;
	}
	else
	{
		audioChannelType = AUDIO_CHANNEL_TYPE_NONE;
	}

	audioSampleRate = wavHead.SampleRate;

	result r = __pAudioOut->Prepare(audioSampleType, audioChannelType, audioSampleRate);
	AppLog("The audio out prepare result is %s", GetErrorMessage(r));
	AppLogDebug("The audio out prepare result in ApplogDebug message");

	ByteBuffer* pTotalData = null;
	pTotalData = new ByteBuffer();
	pTotalData->Construct(__pcmLen);
	pTotalData->SetArray((byte*)__pPcmBuffer, 0, __pcmLen);
	pTotalData->Flip();

	int totalSize = pTotalData->GetLimit();
	int currentPosition = 0;
	ByteBuffer* pItem = null;
	byte givenByte;

	// Binding data buffers into the array
	if(totalSize > MAX_BUFFER_SIZE)
	{
		do
		{
			pItem = new ByteBuffer();
			pItem->Construct(MAX_BUFFER_SIZE);

			for(int i = 0; i < MAX_BUFFER_SIZE; i++)
			{
				// Read it per 1 byte
				pTotalData->GetByte(currentPosition++,givenByte);
				pItem->SetByte(givenByte);
				if(currentPosition == totalSize )
					break;
			}
			__pDataArray->Add(*pItem);

		}while(currentPosition < totalSize);
		__totalWriteBufferNum = __pDataArray->GetCount();
	}
	else
	{
		pItem = new ByteBuffer();
		pItem->Construct(totalSize);
		for(int i = 0; i < totalSize; i++)
		{
			// Read it per 1 byte
			pTotalData->GetByte(i, givenByte);
			pItem->SetByte(givenByte);
		}
		__pDataArray->Add(*pItem);
		__totalWriteBufferNum = __pDataArray->GetCount();
		// non-case for now, may the size of test file is bigger than MAX size
	}
	delete pTotalData;
	pTotalData = null;

	// Start playing until the end of the array
//	__pAudioOut->Start();

	return r;
}

void MyAudioOutEventListener::play()
{
	if (__pAudioOut->GetState() == AUDIOOUT_STATE_PLAYING)
	{
		__pAudioOut->Reset();
	}

	ByteBuffer* pWriteBuffer = null;
	for (int i = 0; i < __totalWriteBufferNum; i++)
	{
		pWriteBuffer = static_cast<ByteBuffer*>(__pDataArray->GetAt(i));
		__pAudioOut->WriteBuffer(*pWriteBuffer);
	}
	__pAudioOut->Start();
	__playCount++;
}

void MyAudioOutEventListener::stop()
{
	__pAudioOut->Stop();
}

void MyAudioOutEventListener::setVolume(int volume)
{
	__pAudioOut->SetVolume(volume);
}

/**
*	Notifies when the device has written a buffer completely.
*
*	@param[in]	src	A pointer to the AudioOut instance that fired the event
*/
void MyAudioOutEventListener::OnAudioOutBufferEndReached(Osp::Media::AudioOut& src)
{
	result r = E_SUCCESS;

	if( __playCount == __totalWriteBufferNum)
	{
		// The End of array, it's time to finish
		//cjh r = src.Unprepare();

		//Reset Variable
		__playCount = 0;
		//cjh __totalWriteBufferNum = 0;

	}else
	{
		//Not yet reached the end of array
		//Write the next buffer
		__playCount++;
//		ByteBuffer* pWriteBuffer = static_cast<ByteBuffer*>(__pDataArray->GetAt(__playCount++));
//		r = src.WriteBuffer(*pWriteBuffer);
	}
}

/**
 *	Notifies that the output device is being interrupted by a task of higher priority than AudioOut.
 *
 *	@param[in]	src							A pointer to the AudioOut instance that fired the event
 */
void MyAudioOutEventListener::OnAudioOutInterrupted(Osp::Media::AudioOut& src)
{
	AppLog("OnAudioOutInterrupted");
	if (__pAudioOut->GetState() == AUDIOOUT_STATE_PLAYING)
	{
		__pAudioOut->Stop();
	}
}

/**
 *	Notifies that the interrupted output device has been released.
 *
 *	@param[in]	src							A pointer to the AudioOut instance that fired the event
 */
void MyAudioOutEventListener::OnAudioOutReleased(Osp::Media::AudioOut& src)
{
	AppLog("OnAudioOutReleased");
}
