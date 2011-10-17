#ifndef __CCAUDIOOUT_H__
#define __CCAUDIOOUT_H__

#include <FBase.h>
#include <FMedia.h>

class MyAudioOutEventListener :
	public Osp::Media::IAudioOutEventListener
{

public:
	MyAudioOutEventListener();

	virtual ~MyAudioOutEventListener();

	result Construct(const char* pszFilePath);

	void Play();
	void Stop();
	void SetVolume(int volume);
	/**
	*	Notifies when the device has written a buffer completely.
	*
	*	@param[in]	src	A pointer to the AudioOut instance that fired the event
	*/
	virtual void OnAudioOutBufferEndReached(Osp::Media::AudioOut& src);
	/**
	 *	Notifies that the output device is being interrupted by a task of higher priority than AudioOut.
	 *
	 *	@param[in]	src							A pointer to the AudioOut instance that fired the event
	 */
	virtual void OnAudioOutInterrupted(Osp::Media::AudioOut& src);

	/**
	 *	Notifies that the interrupted output device has been released.
	 *
	 *	@param[in]	src							A pointer to the AudioOut instance that fired the event
	 */
	virtual void OnAudioOutReleased(Osp::Media::AudioOut& src);

private:
	int	__totalWriteBufferNum;
	int	__playCount;
	Osp::Base::Collection::ArrayList* 	__pDataArray;
	Osp::Media::AudioOut* __pAudioOut;
	char* __pPcmBuffer;
	int __pcmLen;
};

#endif /* MYAUDIOOUTLISTENER_H_ */
