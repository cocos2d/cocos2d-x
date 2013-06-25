#include "SimpleAudioEngine.h"

#include <map>
#include <cstdlib>

//#include "MciPlayer.h"
#include "DirectSoundPlayer.h"
USING_NS_CC;

using namespace std;
#define WIN_CLASS_NAME        "CocosDenshionCallbackWnd"
#define BREAK_IF(cond)      if (cond) break;

namespace CocosDenshion {

static HINSTANCE s_hInstance;
static LRESULT WINAPI _SoundPlayProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

typedef map<unsigned int, DSPlayer*> EffectList;
typedef pair<unsigned int, DSPlayer*> Effect;

static char     s_szRootPath[MAX_PATH];
static DWORD    s_dwRootLen;
static char     s_szFullPath[MAX_PATH];

static std::string _FullPath(const char * szPath);
static unsigned int _Hash(const char *key);

#define BREAK_IF(cond)  if (cond) break;

static EffectList& sharedList()
{
    static EffectList s_List;
    return s_List;
}

static DSPlayer& sharedMusic()
{
    static DSPlayer s_Music;
    return s_Music;
}

SimpleAudioEngine::SimpleAudioEngine() : m_hWnd(NULL)
{
	if (! s_hInstance)
    {
        s_hInstance = GetModuleHandle( NULL );            // Grab An Instance For Our Window

        WNDCLASS  wc;        // Windows Class Structure

        // Redraw On Size, And Own DC For Window.
        wc.style          = 0;  
        wc.lpfnWndProc    = _SoundPlayProc;                    // WndProc Handles Messages
        wc.cbClsExtra     = 0;                              // No Extra Window Data
        wc.cbWndExtra     = 0;                                // No Extra Window Data
        wc.hInstance      = s_hInstance;                    // Set The Instance
        wc.hIcon          = 0;                                // Load The Default Icon
        wc.hCursor        = LoadCursor( NULL, IDC_ARROW );    // Load The Arrow Pointer
        wc.hbrBackground  = NULL;                           // No Background Required For GL
        wc.lpszMenuName   = NULL;                           // We Don't Want A Menu
        wc.lpszClassName  = WIN_CLASS_NAME;                 // Set The Class Name

        if (! RegisterClass(&wc)
            && 1410 != GetLastError())
        {
            return;
        }
    }

    m_hWnd = CreateWindowEx(
        WS_EX_APPWINDOW,                                    // Extended Style For The Window
        WIN_CLASS_NAME,                                        // Class Name
        NULL,                                        // Window Title
        WS_POPUPWINDOW,/*WS_OVERLAPPEDWINDOW*/               // Defined Window Style
        0, 0,                                                // Window Position
        0,                                                    // Window Width
        0,                                                    // Window Height
        NULL,                                                // No Parent Window
        NULL,                                                // No Menu
        s_hInstance,                                        // Instance
        NULL );
    if (m_hWnd)
    {
        SetWindowLong(m_hWnd, GWL_USERDATA, (LONG)this);
    }

	if(FAILED(DirectSoundCreate8(NULL, &g_pDS, NULL))) {
		//MessageBoxA(NULL, "No sound device!", "ERROR", MB_ICONERROR);
		g_pDS = NULL;
		g_pDSPrimary = NULL;
		return;
	}

	if(FAILED(g_pDS->SetCooperativeLevel(m_hWnd, DSSCL_PRIORITY))) {
		//MessageBoxA(NULL, "No sound device!", "ERROR", MB_ICONERROR);
		g_pDS = NULL;
		g_pDSPrimary = NULL;
		return;
	}

	DSBUFFERDESC       dsbd;         // Описание буфера

	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC)); // Обнуляем структуру

	dsbd.dwSize        = sizeof(DSBUFFERDESC); // Устанавливаем размер структуры
	dsbd.dwFlags       = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	dsbd.dwBufferBytes = 0;                    // Не задаем размер буфера
	dsbd.lpwfxFormat   = NULL;                 // Не задаем формат
	if(FAILED(g_pDS->CreateSoundBuffer(&dsbd, &g_pDSPrimary, NULL))) {
		int i = 1;
		// Произошла ошибка
	}

	WAVEFORMATEX wfex;
	ZeroMemory(&wfex, sizeof(WAVEFORMATEX));

	wfex.wFormatTag      = WAVE_FORMAT_PCM;
	wfex.nChannels       = 2;           // моно
	wfex.nSamplesPerSec  = 44100;       // 22050 Гц
	wfex.wBitsPerSample  = 16;          // 16 бит
	wfex.nBlockAlign     = (wfex.wBitsPerSample / 8) * wfex.nChannels;
	wfex.nAvgBytesPerSec = wfex.nSamplesPerSec * wfex.nBlockAlign;

	if(FAILED(g_pDSPrimary->SetFormat(&wfex))) {
		int i = 1;
		// Произошла ошибка
	}

	if(FAILED(g_pDSPrimary->Play(0, 0, DSBPLAY_LOOPING))) {
		int i = 1;
		// Произошла ошибка
	}
}

SimpleAudioEngine::~SimpleAudioEngine()
{
	if (g_pDSPrimary) 
	{
		g_pDSPrimary->Stop();
		g_pDSPrimary->Release();
	}
	DestroyWindow(m_hWnd);
}

SimpleAudioEngine* SimpleAudioEngine::sharedEngine()
{
    static SimpleAudioEngine s_SharedEngine;
    return &s_SharedEngine;
}

void SimpleAudioEngine::end()
{
    sharedMusic().Close();
	sharedMusic().~DSPlayer();

    EffectList::iterator p = sharedList().begin();
    while (p != sharedList().end())
    {
        delete p->second;
        p->second = NULL;
        p++;
    }   
    sharedList().clear();	

    return;
}

//////////////////////////////////////////////////////////////////////////
// BackgroundMusic
//////////////////////////////////////////////////////////////////////////

void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
    if (! pszFilePath)
    {
        return;
    }

	sharedMusic().Stop();
    sharedMusic().Open(_FullPath(pszFilePath), _Hash(pszFilePath));
	sharedMusic().SetVolume(musicVolume);
    sharedMusic().Play((bLoop) ? -1 : 1);
}

void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData)
{
    if (bReleaseData)
    {
        sharedMusic().Close();
    }
    else
    {
        sharedMusic().Stop();
    }
}

void SimpleAudioEngine::pauseBackgroundMusic()
{
    sharedMusic().Pause();
}

void SimpleAudioEngine::resumeBackgroundMusic()
{
    sharedMusic().Resume();
}

void SimpleAudioEngine::rewindBackgroundMusic()
{
    sharedMusic().Rewind();
}

bool SimpleAudioEngine::willPlayBackgroundMusic()
{
    return false;
}

bool SimpleAudioEngine::isBackgroundMusicPlaying()
{
    return sharedMusic().IsPlaying();
}

//////////////////////////////////////////////////////////////////////////
// effect function
//////////////////////////////////////////////////////////////////////////

unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop)
{
    unsigned int nRet = _Hash(pszFilePath);

    preloadEffect(pszFilePath);

    EffectList::iterator p = sharedList().find(nRet);
    if (p != sharedList().end())
    {	
        p->second->Play((bLoop) ? -1 : 1);
		p->second->SetVolume(effectsVolume);
    }

    return nRet;
}

void SimpleAudioEngine::stopEffect(unsigned int nSoundId)
{
    EffectList::iterator p = sharedList().find(nSoundId);
    if (p != sharedList().end())
    {
        p->second->Stop();
    }
}

void SimpleAudioEngine::preloadEffect(const char* pszFilePath)
{
    int nRet = 0;
    do 
    {
        BREAK_IF(! pszFilePath);

        nRet = _Hash(pszFilePath);

        BREAK_IF(sharedList().end() != sharedList().find(nRet));

        sharedList().insert(Effect(nRet, new DSPlayer()));
        DSPlayer * pPlayer = sharedList()[nRet];
        pPlayer->Open(_FullPath(pszFilePath).c_str(), nRet);

        BREAK_IF(nRet == pPlayer->GetSoundID());

        delete pPlayer;
        sharedList().erase(nRet);
        nRet = 0;
    } while (0);
}

void SimpleAudioEngine::pauseEffect(unsigned int nSoundId)
{
    EffectList::iterator p = sharedList().find(nSoundId);
    if (p != sharedList().end())
    {
        p->second->Pause();
    }
}

void SimpleAudioEngine::pauseAllEffects()
{
    EffectList::iterator iter;
    for (iter = sharedList().begin(); iter != sharedList().end(); iter++)
    {
        iter->second->Pause();
    }
}

void SimpleAudioEngine::resumeEffect(unsigned int nSoundId)
{
    EffectList::iterator p = sharedList().find(nSoundId);
    if (p != sharedList().end())
    {
        p->second->Resume();
		p->second->SetVolume(effectsVolume);
    }
}

void SimpleAudioEngine::resumeAllEffects()
{
    EffectList::iterator iter;
    for (iter = sharedList().begin(); iter != sharedList().end(); iter++)
    {
        iter->second->Resume();
		iter->second->SetVolume(effectsVolume);
    }
}

void SimpleAudioEngine::stopAllEffects()
{
    EffectList::iterator iter;
    for (iter = sharedList().begin(); iter != sharedList().end(); iter++)
    {
        iter->second->Stop();
    }
}

void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
{

}

void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
{
    unsigned int nID = _Hash(pszFilePath);

    EffectList::iterator p = sharedList().find(nID);
    if (p != sharedList().end())
    {
        delete p->second;
        p->second = NULL;
        sharedList().erase(nID);
    }    
}

//////////////////////////////////////////////////////////////////////////
// volume interface
//////////////////////////////////////////////////////////////////////////

float SimpleAudioEngine::getBackgroundMusicVolume()
{
    return 1.0 - (musicVolume/(DSBVOLUME_MIN/3.5));  
}

void SimpleAudioEngine::setBackgroundMusicVolume(float volume)
{
	musicVolume = DSBVOLUME_MIN/3.5 * (1.0 - volume);
	if (volume == 0.0) musicVolume = DSBVOLUME_MIN; 
	sharedMusic().SetVolume(musicVolume);
}

float SimpleAudioEngine::getEffectsVolume()
{
    return 1.0 - (effectsVolume/(DSBVOLUME_MIN/3.5)); 
}

void SimpleAudioEngine::setEffectsVolume(float volume)
{
	effectsVolume = DSBVOLUME_MIN/3.5 * (1.0 - volume);
	if (volume == 0.0) effectsVolume = DSBVOLUME_MIN;	
	EffectList::iterator p = sharedList().begin();
    if (p != sharedList().end())
    {
        p->second->SetVolume(effectsVolume);
    }    
}

//////////////////////////////////////////////////////////////////////////
// static function
//////////////////////////////////////////////////////////////////////////

static std::string _FullPath(const char * szPath)
{
    return FileUtils::sharedFileUtils()->fullPathForFilename(szPath);
}

unsigned int _Hash(const char *key)
{
    unsigned int len = strlen(key);
    const char *end=key+len;
    unsigned int hash;

    for (hash = 0; key < end; key++)
    {
        hash *= 16777619;
        hash ^= (unsigned int) (unsigned char) toupper(*key);
    }
    return (hash);
}

} // end of namespace CocosDenshion
