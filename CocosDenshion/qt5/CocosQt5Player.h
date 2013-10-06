#ifndef COCOS2D_COCOSQT5PLAYER_H
#define COCOS2D_COCOSQT5PLAYER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSharedPointer>

namespace cocos2d {

class CocosQt5Player
{
public:
    CocosQt5Player();
    ~CocosQt5Player();

    void setPitch(float pitch);
    void setGain(float gain);
    void setGlobalVolume(float globalVolume);
    void setPan(float pan);
    void setMedia(const char *path, bool looping);

    float getVolume() const;
    bool isPlaying() const;
    bool isStopped() const;
    bool isPaused() const;
    void play();
    void stop(bool releaseData);
    void pause();
    void rewind();

private:
    void applyVolume();

    QMediaPlayer _player;
    bool _looping;
    qreal _pitch;
    qreal _pan;
    qreal _gain;
    qreal _globalVolume;
    QMediaPlaylist _playlist;
    QString _mediaPath;
};

typedef QSharedPointer<CocosQt5Player> CocosQt5PlayerPtr;

} // namespace cocos2d

#endif // COCOS2D_COCOSQT5PLAYER_H
