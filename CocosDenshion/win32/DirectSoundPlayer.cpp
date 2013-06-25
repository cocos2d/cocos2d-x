#include "DirectSoundPlayer.h"
#include <stdio.h>

namespace CocosDenshion {

DSPlayer::DSPlayer()
: m_nSoundID(0)
, m_uTimes(0)
, m_bPlaying(false)
{

}

DSPlayer::~DSPlayer()
{
  if (g_pDSBuffer) 
	{
		g_pDSBuffer->Stop();
		g_pDSBuffer->Release();
		g_pDSBuffer = NULL;
	}
}


void DSPlayer::Open(const char* pFileName, UINT uId)
{
	if (!SimpleAudioEngine::sharedEngine()->getDS())
	{
		g_pDSBuffer = NULL;
		return;
	}

	IDirectSoundBuffer  *pDSB;        // Локальный звуковой буфер

	// Инициализируем структуру WAVEFORMATEX

	WAVEFORMATEX wfex;
	ZeroMemory(&wfex, sizeof(WAVEFORMATEX));
/*
	wfex.wFormatTag      = WAVE_FORMAT_PCM;
	wfex.nChannels       = 1;        // моно
	wfex.nSamplesPerSec  = 22050;    // 22050 Гц
	wfex.wBitsPerSample  = 16;       // 16 бит
	wfex.nBlockAlign     = (wfex.wBitsPerSample / 8) * wfex.nChannels;
	wfex.nAvgBytesPerSec = wfex.nSamplesPerSec * wfex.nBlockAlign;
*/
	// Инициализируем структуру DSBUFFERDESC
	DSBUFFERDESC dsbd;
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC)); // Обнуляем структуру

	HMMIO hMmio = mmioOpen((LPSTR)pFileName, NULL, MMIO_READ | MMIO_ALLOCBUF);
	MMCKINFO mmCkInfoRiff;
	mmCkInfoRiff.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	MMRESULT mmRes = mmioDescend(hMmio, &mmCkInfoRiff, NULL, MMIO_FINDRIFF);
	MMCKINFO mmCkInfo;
	mmCkInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmRes = mmioDescend(hMmio, &mmCkInfo, &mmCkInfoRiff, MMIO_FINDCHUNK);
	mmioRead(hMmio, (char*)&wfex, sizeof(wfex));
	mmRes = mmioAscend(hMmio, &mmCkInfo, 0);
	mmCkInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmRes = mmioDescend(hMmio, &mmCkInfo, &mmCkInfoRiff, MMIO_FINDCHUNK);
	
/*	FILE *fp;
	long len;	

	fp=fopen(pFileName,"rb");
	fseek(fp,0,SEEK_END); //go to end
	len=ftell(fp); //get position at end (length)
	fseek(fp,0,SEEK_SET); //go to beg.
*/
	dsbd.dwSize        = sizeof(DSBUFFERDESC); // Задаем размер
	dsbd.dwFlags       = DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN;
	dsbd.dwBufferBytes = mmCkInfo.cksize; //len;// 2 секунды
	dsbd.lpwfxFormat   = &wfex;

	// Создаем первую версию объекта
	if(FAILED(SimpleAudioEngine::sharedEngine()->getDS()->CreateSoundBuffer(&dsbd, &pDSB, NULL))) {
		// Произошла ошибка
	} else {
		// Получаем 8 версию интерфейса
		if(FAILED(pDSB->QueryInterface(IID_IDirectSoundBuffer8,
			(void**)&g_pDSBuffer))) {
				// Произошла ошибка - прежде чем делать
				// что-либо еще освобождаем первый интерфейс
				pDSB->Release();
		} else {
			// Освобождаем исходный интерфейс - все успешно!
			pDSB->Release();
		}
	}
	
	LPVOID pBuf = VirtualAlloc(NULL, mmCkInfo.cksize, MEM_COMMIT, PAGE_READWRITE);
	DWORD Size = mmCkInfo.cksize;
	if(SUCCEEDED(g_pDSBuffer->Lock(0, 0, (LPVOID*)&pBuf, (DWORD*)&Size, NULL, 0, DSBLOCK_ENTIREBUFFER)))
	{			
		mmioRead(hMmio, (HPSTR)pBuf, mmCkInfo.cksize);
		if(FAILED(g_pDSBuffer->Unlock((LPVOID)pBuf, Size, NULL, 0))) {
			int i = 0;
			// Произошла ошибка
		}
	}
/*	if (pBuf) 
	{
		VirtualFree(pBuf, 0, MEM_RELEASE);
		pBuf = NULL;
	}*/

	// Блокируем буфер

/*	char *Ptr = (char*)malloc(len); //malloc buffer;	
	DWORD Size = len;
	
	if(SUCCEEDED(g_pDSBuffer->Lock(0, 0, (void**)&Ptr, (DWORD*)&Size, NULL, 0, DSBLOCK_ENTIREBUFFER)))
	{		
		fread(Ptr,len,1,fp); //read into buffer
		fclose(fp);
		for (int i(0); i<100; ++i) Ptr[i] = 0;

		if(FAILED(g_pDSBuffer->Unlock((void*)Ptr, Size, NULL, 0))) {
			// Произошла ошибка
		}
	}
*/
	m_nSoundID = uId;
    m_bPlaying = false;

	if(FAILED(g_pDSBuffer->SetCurrentPosition(0))) {		
		// Произошла ошибка
	}

	
}

void DSPlayer::Play(UINT uTimes /* = 1 */)
{
	if (!g_pDSBuffer) return;
	DWORD flags = 0;
	if (uTimes > 1) flags = DSBPLAY_LOOPING;
	g_pDSBuffer->SetCurrentPosition(0);
	if(!FAILED(g_pDSBuffer->Play(0,0,flags)))
	{	
		m_bPlaying = true;
        m_uTimes = uTimes;
	}
}

void DSPlayer::SetVolume(int vol)
{
	if (g_pDSBuffer) 
	{
		g_pDSBuffer->SetVolume(vol);	
	}
}

LONG DSPlayer::GetVolume()
{
	LONG vol = 0;
	if (g_pDSBuffer) g_pDSBuffer->GetVolume(&vol);
	return vol;
}

void DSPlayer::Close()
{
	if (m_bPlaying)
    {
        Stop();
    }
	
    m_bPlaying = false;
}

void DSPlayer::Pause()
{
	if (g_pDSBuffer)
	{
		DWORD pos;
		g_pDSBuffer->GetCurrentPosition(&pos, NULL);
		if (pos >= DSBPN_OFFSETSTOP || pos == 0) m_bPlaying = false;
		g_pDSBuffer->Stop();
	}
}

void DSPlayer::Resume()
{
	if (m_bPlaying) 
		g_pDSBuffer->Play(0,0,0);
}

void DSPlayer::Stop()
{
	if (g_pDSBuffer) g_pDSBuffer->Stop();
	m_bPlaying = false;
}

void DSPlayer::Rewind()
{
	if (!g_pDSBuffer) return;
	g_pDSBuffer->SetCurrentPosition(0);
	m_bPlaying = !FAILED(g_pDSBuffer->Play(0,0,0)) ? false : true;
}

bool DSPlayer::IsPlaying()
{
    return m_bPlaying;
}

UINT DSPlayer::GetSoundID()
{
    return m_nSoundID;
}

}
