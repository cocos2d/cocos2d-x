#include "CocosQt5Player.h"

#include "platform/CCCommon.h"
#include "platform/CCFileUtils.h"

namespace cocos2d {

static QString fullPath(const char *filename)
{
    return QString::fromStdString(FileUtils::getInstance()->fullPathForFilename(filename));
}

CocosQt5Player::CocosQt5Player()
    : _looping(false)
    , _pitch(1.0)
    , _pan(0.0)
    , _gain(1.0)
    , _globalVolume(1.0)
{
    _player.setPlaylist(&_playlist);
}

CocosQt5Player::~CocosQt5Player()
{
    _player.setPlaylist(nullptr);
}

void CocosQt5Player::setPitch(float pitch)
{
    // TODO: research why pitch breaks playing with gstreamer backend.
#if 0
    if (pitch != _pitch)
    {
        _pitch = pitch;
        _player.setPlaybackRate(pitch);
    }
#else
    CC_UNUSED_PARAM(pitch);
#endif
}

void CocosQt5Player::setGain(float gain)
{
    if (gain != _gain)
    {
        _gain = gain;
        applyVolume();
    }
}

void CocosQt5Player::setGlobalVolume(float globalVolume)
{
    if (globalVolume != _globalVolume)
    {
        _globalVolume = globalVolume;
        applyVolume();
    }
}

void CocosQt5Player::setPan(float pan)
{
    Q_UNUSED(pan);
    // TODO: handle pan.
}

void CocosQt5Player::setMedia(const char *path, bool looping)
{
    QString mediaPath = fullPath(path);
    if (mediaPath != _mediaPath || looping != _looping)
    {
        _looping = looping;
        _mediaPath = mediaPath;
        _playlist.clear();
        _playlist.addMedia(QMediaContent(QUrl::fromLocalFile(mediaPath)));
        _playlist.setPlaybackMode(looping
                                  ? QMediaPlaylist::CurrentItemInLoop
                                  : QMediaPlaylist::CurrentItemOnce);
    }
}

float CocosQt5Player::getVolume() const
{
    const float volume = _player.volume();
    return volume / 100.0;
}

bool CocosQt5Player::isPlaying() const
{
    return _player.state() == QMediaPlayer::PlayingState;
}

bool CocosQt5Player::isStopped() const
{
    return _player.state() == QMediaPlayer::StoppedState;
}

bool CocosQt5Player::isPaused() const
{
    return _player.state() == QMediaPlayer::PausedState;
}

void CocosQt5Player::play()
{
    _player.play();
}

void CocosQt5Player::stop(bool releaseData)
{
    _player.stop();
    if (releaseData)
        _playlist.clear();
}

void CocosQt5Player::pause()
{
    _player.pause();
}

void CocosQt5Player::rewind()
{
    _player.stop();
    _player.setPosition(0);
    _player.play();
}

void CocosQt5Player::applyVolume()
{
    _player.setVolume(_gain * _globalVolume * 100.0);
}

} // namespace cocos2d
