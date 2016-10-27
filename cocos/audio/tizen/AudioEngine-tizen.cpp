/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN

#include "audio/tizen/AudioEngine-tizen.h"

// for native asset manager
#include <condition_variable>
#include <sys/types.h>
#include <sound_manager.h>
#include "audio/include/AudioEngine.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "platform/CCFileUtils.h"
#include "platform/tizen/CCApplication-tizen.h"

#include <queue>

class AudioEngineThreadPool
{
public:
    AudioEngineThreadPool()
    : _running(true) {
        _threads = std::thread(std::bind(&AudioEngineThreadPool::threadFunc, this));
    }

    ~AudioEngineThreadPool()
    {
        _running = false;
        _sleepCondition.notify_one();
        _threads.join();
    }

    void addTask(const std::function<void()> &task) {
        _tasks.push(task);
        _sleepCondition.notify_one();
    }
private:
    bool _running;
    std::thread _threads;
    std::queue< std::function<void ()> > _tasks;

    void threadFunc(void) {
        while (true) {
            std::function<void ()> task = nullptr;

            if (_tasks.empty())
            {
                if (!_running)
                {
                    break;
                }
                std::unique_lock<std::mutex> lk(_sleepMutex);
                _sleepCondition.wait(lk);
                continue;
            }

            task = _tasks.front();

            task();

            _tasks.pop();
        }
    }

    std::mutex _sleepMutex;
    std::condition_variable _sleepCondition;
};

static AudioEngineThreadPool* _threadPool = nullptr;

using namespace cocos2d;
using namespace cocos2d::experimental;

static void sessionInterruptedCallback(sound_session_interrupted_code_e code, void *user_data)
{
	Application* app = Application::getInstance();
	if(app && app->isPaused())
	{
		return;
	}
	if(code == SOUND_SESSION_INTERRUPTED_COMPLETED)
	{
		AudioEngine::resumeAll();
	}
	else
	{
		AudioEngine::pauseAll();
		if (code == SOUND_SESSION_INTERRUPTED_BY_EARJACK_UNPLUG)
		{
			AudioEngine::resumeAll();
		}
	}
}

AudioPlayer::AudioPlayer()
    : _playerHandle(nullptr)
    , _finishCallback(nullptr)
    , _initCallback(nullptr)
    , _duration(0.0f)
    , _playOver(false)
    , _initSucceed(false)
{
}

static void _stopPlayer(player_h player)
{
    player_state_e state = PLAYER_STATE_NONE;
    player_get_state(player, &state);
    if (state == PLAYER_STATE_PLAYING || state == PLAYER_STATE_PAUSED)
    {
        player_stop(player);
    }
    player_unprepare(player);
}

static void _pausePlayer(player_h player)
{
    player_state_e state;
    player_get_state(player, &state);

    if(state == PLAYER_STATE_PLAYING)
    {
        player_pause(player);
    }
}

static void _resumePlayer(player_h player)
{
    player_state_e state;
    player_get_state(player, &state);

    if(state != PLAYER_STATE_PLAYING)
    {
        player_start(player);
    }
}

AudioPlayer::~AudioPlayer()
{
    _taskMutex.lock();
    _threadPool->addTask(std::bind(_stopPlayer, _playerHandle));
    _threadPool->addTask(std::bind(player_destroy, _playerHandle));
    _taskMutex.unlock();
}

void AudioPlayer::stopPlayer()
{
    _playOver = true;
}

static void completed_callback(void* user_data)
{
    AudioPlayer* player = (AudioPlayer*)user_data;
    player->stopPlayer();
}

void AudioPlayer::init(const std::string& fileFullPath, float volume, bool loop)
{
    do
    {
        player_h player;
        auto playerRet = player_create(&player);
        if(playerRet != PLAYER_ERROR_NONE)
        {
            log("Fail to create player.Error code:%d",playerRet);
            break;
        }

        _playerHandle = player;
        playerRet = player_set_uri(player, fileFullPath.c_str());
        if(playerRet != PLAYER_ERROR_NONE)
        {
            log("Fail to sets the data source for player.Error code:%d",playerRet);
            break;
        }

        player_set_volume(player, volume, volume);
        player_set_completed_cb(player, completed_callback, this);
        if (loop)
        {
            player_set_looping(player, true);
        }
        playerRet = player_prepare(player);
        if(playerRet != PLAYER_ERROR_NONE){
            log("Fail to prepares the media player for playback.Error code:%d",playerRet);
            break;
        }

        playerRet = player_start(player);
        if(playerRet != PLAYER_ERROR_NONE){
            log("Fail to starts playback.Error code:%d",playerRet);
            break;
        }

        _initSucceed = true;
    } while (0);

    if (_initCallback)
    {
        _initCallback();
    }
    _taskMutex.unlock();
}

//====================================================
AudioEngineImpl::AudioEngineImpl()
    : currentAudioID(0)
    , _lazyInitLoop(true)
{

}

AudioEngineImpl::~AudioEngineImpl()
{
    this->stopAll();

    if (_threadPool)
    {
        delete _threadPool;
        _threadPool = nullptr;
    }
    auto scheduler = Director::getInstance()->getScheduler();
    scheduler->unschedule(schedule_selector(AudioEngineImpl::update), this);
}

bool AudioEngineImpl::init()
{
    sound_manager_set_session_type(SOUND_SESSION_TYPE_MEDIA);
    sound_manager_set_media_session_option(SOUND_SESSION_OPTION_MIX_WITH_OTHERS_WHEN_START,
            SOUND_SESSION_OPTION_INTERRUPTIBLE_DURING_PLAY);
    sound_manager_set_media_session_resumption_option(SOUND_SESSION_OPTION_RESUMPTION_BY_SYSTEM_OR_MEDIA_PAUSED);

	sound_manager_set_session_interrupted_cb(sessionInterruptedCallback, this);

	if (!_threadPool)
	{
		_threadPool = new (std::nothrow) AudioEngineThreadPool();
	}

    return true;
}

int AudioEngineImpl::play2d(const std::string &filePath ,bool loop ,float volume)
{
    auto audioId = AudioEngine::INVALID_AUDIO_ID;

    do
    {
        audioId = currentAudioID++;

        auto& player = _audioPlayers[audioId];
        player._audioID = audioId;
        player._initCallback = std::bind(&AudioEngineImpl::initPlayerCallback,this,&player,audioId);

        player._taskMutex.lock();
        _threadPool->addTask(std::bind(&AudioPlayer::init,&player,FileUtils::getInstance()->fullPathForFilename(filePath), volume, loop));

        if (_lazyInitLoop) {
            _lazyInitLoop = false;

            auto scheduler = Director::getInstance()->getScheduler();
            scheduler->schedule(schedule_selector(AudioEngineImpl::update), this, 0.03f, false);
        }
    } while (0);

    return audioId;
}

void AudioEngineImpl::initPlayerCallback(AudioPlayer *player, int audioID)
{
    if (player->_initSucceed)
    {
        AudioEngine::_audioIDInfoMap[audioID].state = AudioEngine::AudioState::PLAYING;
    }
    else
    {
        _threadMutex.lock();
        _toRemoveAudioIDs.push_back(audioID);
        _threadMutex.unlock();
    }
}

void AudioEngineImpl::update(float dt)
{
    if (_threadMutex.try_lock()) {
        int audioID;
        size_t removeAudioCount = _toRemoveAudioIDs.size();
        for (size_t index = 0; index < removeAudioCount; ++index) {
            audioID = _toRemoveAudioIDs[index];
            auto playerIt = _audioPlayers.find(audioID);
            if (playerIt != _audioPlayers.end()) {
                if(playerIt->second._finishCallback) {
                    auto& audioInfo = AudioEngine::_audioIDInfoMap[audioID];
                    playerIt->second._finishCallback(audioID, *audioInfo.filePath);
                }
                _audioPlayers.erase(audioID);
                AudioEngine::remove(audioID);
            }
        }
        _threadMutex.unlock();
    }

    auto itend = _audioPlayers.end();
    for (auto iter = _audioPlayers.begin(); iter != itend; ++iter)
    {
        if(iter->second._playOver)
        {
            if (iter->second._finishCallback)
                iter->second._finishCallback(iter->second._audioID, *AudioEngine::_audioIDInfoMap[iter->second._audioID].filePath);

            AudioEngine::remove(iter->second._audioID);
            _audioPlayers.erase(iter);
            break;
        }
    }

    if(_audioPlayers.empty()){
        _lazyInitLoop = true;

        auto scheduler = Director::getInstance()->getScheduler();
        scheduler->unschedule(schedule_selector(AudioEngineImpl::update), this);
    }
}

void AudioEngineImpl::setVolume(int audioID,float volume)
{
    auto& player = _audioPlayers[audioID];
    player_set_volume(player._playerHandle, volume, volume);
}

void AudioEngineImpl::setLoop(int audioID, bool loop)
{
    auto& player = _audioPlayers[audioID];
    player_set_looping(player._playerHandle, loop);
}

void AudioEngineImpl::pause(int audioID)
{
    auto& player = _audioPlayers[audioID];
    _threadPool->addTask(std::bind(_pausePlayer, player._playerHandle));
}

void AudioEngineImpl::resume(int audioID)
{
    auto& player = _audioPlayers[audioID];
    _threadPool->addTask(std::bind(_resumePlayer, player._playerHandle));
}

void AudioEngineImpl::stop(int audioID)
{
    _audioPlayers.erase(audioID);
}

void AudioEngineImpl::stopAll()
{
     _audioPlayers.clear();
}

float AudioEngineImpl::getDuration(int audioID)
{
    int duration;
    auto& player = _audioPlayers[audioID];
    auto ret = player_get_duration(player._playerHandle, &duration);
    if(ret != PLAYER_ERROR_NONE)
    {
        log("Fail to get duration:%d",ret);
    }
    return duration / 1000.0f;
}

float AudioEngineImpl::getCurrentTime(int audioID)
{
    int currPos;
    auto& player = _audioPlayers[audioID];
    auto ret = player_get_play_position(player._playerHandle, &currPos);
    if(ret != PLAYER_ERROR_NONE)
    {
        CCLOG("Fail to get position:%d",ret);
    }
    return currPos / 1000.0f;
}

bool AudioEngineImpl::setCurrentTime(int audioID, float time)
{
    auto& player = _audioPlayers[audioID];
    int pos = 1000 * time;
    player_set_play_position(player._playerHandle, pos, true, NULL, NULL);

    return true;
}

void AudioEngineImpl::setFinishCallback(int audioID, const std::function<void (int, const std::string &)> &callback)
{
    _audioPlayers[audioID]._finishCallback = callback;
}

void AudioEngineImpl::preload(const std::string& filePath, std::function<void(bool)> callback)
{
    //TODO: implement preload on Tizen platform.
}

#endif
