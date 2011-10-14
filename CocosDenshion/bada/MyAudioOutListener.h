/*
 * MyAudioOutListener.h
 *
 *  Created on: 2011-1-21
 *      Author: Administrator
 */

#ifndef MYAUDIOOUTLISTENER_H_
#define MYAUDIOOUTLISTENER_H_

#include <FBase.h>
#include <FMedia.h>



class MyAudioOutEventListener :
	public Osp::Media::IAudioOutEventListener
{

public:
	MyAudioOutEventListener();

	virtual ~MyAudioOutEventListener();

	result Construct(const char* pszFilePath);

	void play();
	void stop();
	void setVolume(int volume);
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
